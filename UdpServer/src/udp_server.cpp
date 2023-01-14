#include "CommonHeader.h"

using boost::asio::ip::udp;

int main()
{
    try
    {
        boost::asio::io_context io;
        udp::socket socket(io,udp::endpoint(udp::v4(),8888));

        for (;;)
        {
            boost::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;

            size_t len = socket.receive_from(boost::asio::buffer(recv_buf),remote_endpoint);

            if (len > 0)
            {
                std::cout << remote_endpoint.address().to_string() << std::endl;

                std::cout << remote_endpoint.port() << std::endl;

                std::cout << remote_endpoint.data()->sa_family << std::endl;
            }


            boost::system::error_code ignored_error;
            socket.send_to(
                boost::asio::buffer("Hello UDP Client!"),
                remote_endpoint, 
                0, 
                ignored_error
            );
        }
    }
    catch (...)
    {
    }
    return 0;
}