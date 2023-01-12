#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

using boost::asio::ip::tcp;

//std::string make_daytime_string()
//{
//    using namespace std; // For time_t, time and ctime;
//    time_t now = time(0);
//    return ctime(&now);
//}

class Tcp_connection : public boost::enable_shared_from_this<Tcp_connection>
{
public:
    typedef boost::shared_ptr<Tcp_connection> pointer;

    static pointer Create(boost::asio::io_context& io)
    {
        return pointer(new Tcp_connection(io));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void Start()
    {
        //message_ = make_daytime_string();

        boost::asio::async_write
        (
            socket_,
            boost::asio::buffer("连接成功！"),
            boost::bind
            (
                &Tcp_connection::Handle_write,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    }

private:
    Tcp_connection(boost::asio::io_context& io)
        :socket_(io)
    {}

    void Handle_write(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/)
    {}

    tcp::socket socket_;
    //std::string message_;
};

class Tcp_server
{
public:
    Tcp_server(boost::asio::io_context& io)
        :io_(io)
        , acceptor_(io, tcp::endpoint(tcp::v4(), 8888))
    {
        Start_accept();

    }
private:
    void Start_accept()
    {
        Tcp_connection::pointer new_connection = Tcp_connection::Create(io_);

        acceptor_.async_accept
        (
            new_connection->socket(),
            boost::bind
            (
                &Tcp_server::Handle_accept,
                this,
                new_connection,
                boost::asio::placeholders::error
            )
        );
    }

    void Handle_accept(Tcp_connection::pointer new_connection,const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->Start();
        }

        Start_accept();
    }

    boost::asio::io_context& io_;
    tcp::acceptor acceptor_;
};



#endif //TCP_SERVER_H_