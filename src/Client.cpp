#include "Client.h"

Client::Client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) :
    m_io_service (io_service),
    m_timer(io_service, boost::posix_time::milliseconds(40))
{
    connect(endpoint);
}

Client::~Client()
{
    //dtor
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
}

void Client::m_drive_events()
{
    m_timer.expires_from_now(boost::posix_time::milliseconds(40));
    m_timer.async_wait(boost::bind(&Client::m_handle_events, this));
}

void Client::m_handle_events()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {


    }

    m_drive_events();

}

void Client::handle_connect(Connection::connection_ptr connection, const boost::system::error_code& error)
{
    if (!error)
    {
        std::cout << "Connected" << std::endl;
        wait_for_data();
    }
}

void Client::wait_for_data()
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
            std::cout << "World state" << std::endl;
            break;
        case DownMessage::DEFAULT_TYPE :
            std::cout << "Default message" << std::endl;
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
