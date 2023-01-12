#ifndef PRINTER_H_
#define PRINTER_H_

#include "CommonHeader.h"

class Printer
{
public:
    Printer(boost::asio::io_context& io) :timer_(io, boost::asio::chrono::seconds(1)), cnt_(0)
    {
        timer_.async_wait(
            boost::bind(&Printer::print, this)
        );
    }

    ~Printer()
    {
        std::cout << "Final count is " << cnt_ << std::endl;
    }

    void print()
    {
        if (cnt_ < 5)
        {
            std::cout << cnt_ << std::endl;
            ++cnt_;

            /**
            * expires_at()  : �����ĵ���ʱ�����õ�
            * expiry()      �������ĵ���ʱ��
            */
            timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
            timer_.async_wait(
                boost::bind(&Printer::print, this)
            );
        }
    }
private:
    boost::asio::steady_timer timer_;
    int cnt_;
};

#endif //PRINTER_H_