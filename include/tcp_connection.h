#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
    virtual ~tcp_connection();

    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service& ios);
    boost::asio::ip::tcp::socket& socket();
    void read();
protected:
private:
    tcp_connection(boost::asio::io_service& io_service);
    void handle_read(const boost::system::error_code& error, size_t number_bytes_read);

    boost::asio::ip::tcp::socket m_socket;
    boost::array<char, 128> m_network_buffer;
};

#endif // TCP_CONNECTION_H
