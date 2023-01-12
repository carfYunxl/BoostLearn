#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <vector>
#include "tcp_server.h"
using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_context io;
        Tcp_server server(io);

        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}