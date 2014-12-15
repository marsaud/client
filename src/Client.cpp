#include "Client.h"

Client::Client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) :
    m_player(NULL),
    m_world(NULL),
    m_state(StateController::IDLE),
    m_io_service (io_service),
    m_timer(io_service, boost::posix_time::milliseconds(40))
{
    connect(endpoint);
}

Client::~Client()
{
    if (NULL != m_player)
    {
        delete m_player;
        m_player = NULL;
    }

    if (NULL != m_world)
    {
        delete m_world;
        m_world = NULL;
    }
}

void Client::connect(boost::asio::ip::tcp::endpoint& endpoint)
{
    m_connection = Connection::create(m_io_service);
    boost::asio::ip::tcp::socket& socket = m_connection->socket();
    socket.async_connect(endpoint,
                         boost::bind(&Client::handle_connect,
                                     this,
                                     m_connection,
                                     boost::asio::placeholders::error));
    m_state = StateController::CONNECTING;
}

void Client::handle_connect(Connection::connection_ptr connection, const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Connected" << std::endl;
        m_state = StateController::INITIALIZING;
        wait_for_data();
        m_drive_events();
    }
}

void Client::wait_for_data()
{
    if (StateController::EXITING != m_state)
    {
        m_connection->async_read(
            m_downMessage,
            boost::bind(
                &Client::handle_read,
                this,
                boost::asio::placeholders::error
            )
        );
    }
}

void Client::handle_read(const boost::system::error_code& error)
{
    if (!error)
    {
        switch (m_downMessage.m_type)
        {
        case DownMessage::PLAYER_CONNECTED :
        case DownMessage::PLAYER_LEFT :

            std::cout << "Room event : " << m_downMessage.m_info << std::endl;
            break;

        case DownMessage::WORLD_STATE :

            if (StateController::PLAYING == m_state)
            {
                std::cout << "World state" << std::endl;
                for (std::vector<Player>::iterator it = m_downMessage.m_players.begin(); m_downMessage.m_players.end() != it; it++)
                {
                    std::cout << it->m_area << it->m_tile.x << it->m_tile.y << it->m_zone.x << it->m_zone.y << std::endl;
                }
            }
            break;

        case DownMessage::DEFAULT_TYPE :

            std::cout << "Default message" << std::endl;
            break;

        case DownMessage::WELCOME :

            if (StateController::INITIALIZING == m_state)
            {
                m_world = new StaticWorld("scenario1", "data");
                m_player = new Player(m_downMessage.m_players.front());
                m_state = StateController::PLAYING;
                std::cout << "Welcome message" << std::endl;
            }
            break;

        default:

            std::cout << "???" << std::endl;
            break;

        }

        wait_for_data();
    }
    else
    {
        std::cout << error.message() << std::endl;
    }
}

void Client::m_drive_events()
{
    if (StateController::EXITING != m_state)
    {
        m_timer.expires_from_now(boost::posix_time::milliseconds(40));
        m_timer.async_wait(boost::bind(&Client::m_handle_events, this));
    }
}

void Client::m_handle_events()
{
    SDL_Event event;
    Player::Move move = Player::MOVE_NOT;
    Player::Action action = Player::ACTION_NONE;

    while (SDL_PollEvent(&event))
    {
        StateController::handleEvent(event, m_state);
        if (StateController::PLAYING == m_state)
        {
            MovementController::handleEvent(event, move);
            ActionController::handleEvent(event, action);

            MovementProcessor::move(move, m_player, m_world);
            ActionProcessor::process(action, m_player, m_world);
        }
    }

    if (Player::MOVE_NOT != move || Player::ACTION_NONE != action)
    {
        UpMessage msg;

        msg.m_action = action;
        msg.m_move = move;

        m_connection->async_write(msg,
                                  boost::bind(
                                      &Client::handle_write,
                                      this,
                                      boost::asio::placeholders::error));
    }

    m_drive_events();
}

void Client::handle_write(const boost::system::error_code& error)
{
    if (error)
    {
        std::cerr << "Error upstreaming message : " << error.message() << std::endl;
    }
}
