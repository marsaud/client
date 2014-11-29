#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "tcp_connection.h"

class tcp_client
{
    public:
        tcp_client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint);
        virtual ~tcp_client();
    protected:
    private:
        void connect(boost::asio::ip::tcp::endpoint& endpoint);
        void handle_connect(tcp_connection::pointer new_connection, const boost::system::error_code& error);

        boost::asio::io_service& m_io_service;
};

#endif // TCP_CLIENT_H
