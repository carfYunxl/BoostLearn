#include "async_udp_server.h"

void print()
{

}

int main()
{
    try
    {
        boost::asio::io_context io;
        
        //< ����һ������ udp socket
        udp::socket socket(
            io,                             //IO������
            udp::endpoint
            (
                udp::v4(),                  //ָ��������ip��ַ��INADDR_ANY or in6addr_any
                8888                        //�˿�
            )  
        );

        //< ׼����������
        char recv_buf[1024]{};
        udp::endpoint remote_endpoint;

        auto fun = [=](const boost::system::error_code& error,
            std::size_t /*bytes_transferred*/) {
            std::cout << "IP�� " << remote_endpoint.address().to_string() << std::endl;
            std::cout << "port�� " << remote_endpoint.port() << std::endl;
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