#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
    try 
    {
        if (argc != 2)
        {
            std::cerr << "Usage: client<host>" << std::endl;
            return 1;
        }

        boost::asio::io_context io;
        tcp::resolver resolver(io);

        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "8888");

        tcp::socket socket(io);
        boost::asio::connect(socket,endpoints);

        char ch;

        while (std::cin >> ch)
        {
            boost::system::error_code ignored_error;

            switch (ch)
            {
            case 'q':
                boost::asio::write(socket, boost::asio::buffer("Hello,World!"), ignored_error);
                std::cout.write("q", 1);
                break;
            case 'w':
                boost::asio::write(socket, boost::asio::buffer("Yes,i send w to you!"), ignored_error);
                std::cout.write("w", 1);
                break;
            case 'e':
                boost::asio::write(socket, boost::asio::buffer("good,e is also ok!"), ignored_error);
                std::cout.write("e", 1);
                break;
            case 's':
                boost::asio::write(socket, boost::asio::buffer("小朋友假日里，去郊游！！！爬爬小山，看看我，开心哟！！！"), ignored_error);
                std::cout.write("e", 1);
                break;
            case 'r':
                boost::asio::write(socket, boost::asio::buffer("你好！"), ignored_error);
                socket.close();
                std::cout.write("Close!", 6);
                return 0;
            }
#if 0
            boost::array<char, 128> buf;
            //boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buf), ignored_error);

            /*if (error == boost::asio::error::eof)
            {
                break;
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }*/
            if(len > 0)
                std::cout.write(buf.data(),len);
#endif
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}