#ifndef ASYNC_UDP_SERVER_H
#define ASYNC_UDP_SERVER_H

#include "CommonHeader.h"
using boost::asio::ip::udp;
class udp_server
{
public:
    udp_server(boost::asio::io_context& io_context)
        : socket_(io_context, udp::endpoint(udp::v4(), 8888))
    {
        start_receive();
    }
private:
    void start_receive()
    {
        socket_.async_receive_from
        (
            boost::asio::buffer(recv_buffer_), 
            remote_endpoint_,
            boost::bind
            (
                &udp_server::handle_receive, 
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }

    void handle_receive(const boost::system::error_code& error,
        std::size_t /*bytes_transferred*/)
    {
        if (!error)
        {
            boost::shared_ptr<std::string> message(
                new std::string());
            socket_.async_send_to(
                boost::asio::buffer("Hello async UDP Server!!"),
                remote_endpoint_,
                boost::bind
                (
                    &udp_server::handle_send,
                    this, 
                    message,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
            );
            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
        const boost::system::error_code& /*error*/,
        std::size_t /*bytes_transferred*/)
    {
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};


#endif //ASYNC_UDP_SERVER_H