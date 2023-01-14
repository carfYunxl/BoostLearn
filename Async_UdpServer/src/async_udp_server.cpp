#include "async_udp_server.h"

void print()
{

}

int main()
{
    try
    {
        boost::asio::io_context io;
        
        //< 创建一个本地 udp socket
        udp::socket socket(
            io,                             //IO流对象
            udp::endpoint
            (
                udp::v4(),                  //指定服务器ip地址，INADDR_ANY or in6addr_any
                8888                        //端口
            )  
        );

        //< 准备接受连接
        char recv_buf[1024]{};
        udp::endpoint remote_endpoint;

        auto fun = [=](const boost::system::error_code& error,
            std::size_t /*bytes_transferred*/) {
            std::cout << "IP： " << remote_endpoint.address().to_string() << std::endl;
            std::cout << "port： " << remote_endpoint.port() << std::endl;
        };


        socket.async_receive_from
        (
            boost::asio::buffer(recv_buf),
            remote_endpoint,
            fun
        );


        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}