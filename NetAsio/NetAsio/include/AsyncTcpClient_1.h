#ifndef ASYNC_TCP_CLIENT_1_H_
#define ASYNC_TCP_CLIENT_1_H_

#include "CommonHeader.h"

void Start()
{
    boost::asio::io_context io;
    boost::asio::ip::tcp::resolver resolver(io);

    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve();
}

#endif //ASYNC_TCP_CLIENT_1_H_