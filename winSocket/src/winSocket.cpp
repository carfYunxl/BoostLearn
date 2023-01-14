#include <iostream>
#include <winSock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
    //初始化WSA
    WORD sockVer = MAKEWORD(2,2);

    WSADATA wsaData;

    if (WSAStartup(sockVer,&wsaData) != 0)
    {
        return 0;
    }

    //创建套接字
    SOCKET sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (sListen == INVALID_SOCKET)
    {
        std::cout << "socket error!" << std::endl;
        return 1;
    }
    //绑定IP和端口
    sockaddr_in in;
    in.sin_family = AF_INET;
    in.sin_port = htons(8888);
    in.sin_addr.S_un.S_addr = INADDR_ANY;

    if (bind(sListen,(LPSOCKADDR)&in,sizeof(in)) == SOCKET_ERROR)
    {
        std::cout << "bind error！" << std::endl;
        return 1;
    }

    //监听
    if (listen(sListen,5) == SOCKET_ERROR)
    {
        std::cout << "listen error！" << std::endl;
        return 1;
    }

    //接受数据
    SOCKET sClient;
    sockaddr_in clientAddr;
    int nAddrLen = sizeof(clientAddr);
    char recv_buf[128];
    while (1)
    {
        std::cout << "Waiting for connecting......" << std::endl;

        //会阻塞在这里
        sClient = accept(sListen,(SOCKADDR*)&clientAddr,&nAddrLen);

        if (sClient == INVALID_SOCKET)
        {
            std::cout << "accept error!" << std::endl;
            return 1;
        }

        std::cout << "Connect Success！" << std::endl;
        
        char ip[128]{0};
        std::cout << "IP:" << inet_ntop(AF_INET,&clientAddr.sin_addr,ip,128) << std::endl;
        std::cout << "Port:" << ntohs(clientAddr.sin_port) << std::endl;

        //读socket数据
        size_t len = recv(sClient,recv_buf,128,0);
        if (len > 0)
        {
            std::cout << std::string(recv_buf) << std::endl;
        }
    }

    closesocket(sClient);
    WSACleanup();
    return 0;
}
