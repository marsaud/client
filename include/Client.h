#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Connection.h"
#include "UpMessage.h"

class Client
{
    public:
        Client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint);
        virtual ~Client();
    protected:
    private:
        void connect(boost::asio::ip::tcp::endpoint& endpoint);
        void handle_connect(Connection::connection_ptr connection, const boost::system::error_code& error);
        void wait_for_data();
        void handle_read(const boost::system::error_code& error);

        boost::asio::io_service& m_io_service;
        Connection::connection_ptr m_connection;
        UpMessage m_message;
};

#endif // CLIENT_H
