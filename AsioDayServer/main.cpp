#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <vector>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

int main()
{
    int port = 8888;
    try
    {
        boost::asio::io_context io;
        tcp::acceptor acceptor(io,tcp::endpoint(tcp::v4(),port));

        tcp::socket socket(io);

        acceptor.accept(socket);

        std::cout << "Connect!" << std::endl;


        while (1)
        {
            char buf[1024];
            //boost::system::error_code error;
            boost::system::error_code ignored_error;
            size_t len = socket.read_some(boost::asio::buffer(buf), ignored_error);

            if (len > 0)
            {
                std::cout << "len = " << len << std::endl;
                for (int i = 0;i < len;++i)
                {
                    std::cout << "buf = " << buf[i] << std::endl;
                }

                std::string str(buf);
                std::vector<std::string> vec{str,"\nYES"};

                boost::asio::write(socket, boost::asio::buffer(vec), ignored_error);
                std::cout.write(str.c_str(), str.size());
            }
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}