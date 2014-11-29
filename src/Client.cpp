#include "Client.h"

Client::Client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint) :
    m_io_service (io_service)
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
        m_message,
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
        std::cout << "Data received : " << m_message.m_login <<  " : " << m_message.m_message << std::endl;
        wait_for_data();
    }
    else
    {
        std::cout << error.message() << std::endl;
    }
}
