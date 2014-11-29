#include "tcp_connection.h"

tcp_connection::tcp_connection(boost::asio::io_service& io_service) : m_socket(io_service)
{
    //ctor
}

tcp_connection::~tcp_connection()
{
    //dtor
}

tcp_connection::pointer tcp_connection::create(boost::asio::io_service& ios)
{
    return pointer(new tcp_connection(ios));
}

boost::asio::ip::tcp::socket& tcp_connection::socket()
{
    return m_socket;
}

void tcp_connection::read()
{
    boost::asio::async_read(m_socket, boost::asio::buffer(m_network_buffer),
                            boost::asio::transfer_at_least(20),
                            boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred)
                           );
}

void tcp_connection::handle_read(const boost::system::error_code& error, size_t number_bytes_read)
{
    if (!error)
    {
        std::cout << "Server speaks" << std::endl;
        std::cout.write(&m_network_buffer[0], number_bytes_read);
        read();
    }
    else
    {
        std::cout << error.message();
    }
}
