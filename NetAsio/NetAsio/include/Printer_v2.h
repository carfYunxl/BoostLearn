#ifndef PRINTER_V2_H_
#define PRINTER_V2_H_

#include "CommonHeader.h"

class Printer_V2
{
public:
    Printer_V2(boost::asio::io_context& io) :
        strand_(boost::asio::make_strand(io)),
        timer1_(io, boost::asio::chrono::seconds(1)), 
        timer2_(io, boost::asio::chrono::seconds(1)),
        cnt_(0)
    {
        timer1_.async_wait
        (
            boost::asio::bind_executor(strand_, boost::bind(&Printer_V2::print1, this))
        );

        timer2_.async_wait
        (
            boost::asio::bind_executor(strand_, boost::bind(&Printer_V2::print2, this))
        );
    }

    ~Printer_V2()
    {
        std::cout << "Final count is " << cnt_ << std::endl;
    }

    void print1()
    {
        if (cnt_ < 10)
        {
            std::cout << "Timer 1 : " << cnt_ << std::endl;
            ++cnt_;

            /**
            * expires_at()  : 期望的到期时间设置点
            * expiry()      ：真正的到期时间
            */
            timer1_.async_wait(
                boost::asio::bind_executor(strand_, boost::bind(&Printer_V2::print1, this))
            );
        }
    }

    void print2()
    {
        if (cnt_ < 10)
        {
            std::cout << "Timer 2 : " << cnt_ << std::endl;
            ++cnt_;

            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

            timer2_.async_wait(
                boost::asio::bind_executor(strand_, boost::bind(&Printer_V2::print2, this))
            );
        }
    }

    /**
    * 测试程序主函数
    */
    static void TestStart()
    {
        boost::asio::io_context io;
        Printer_V2 printer(io);

        boost::thread thread(
            boost::bind(&boost::asio::io_context::run, &io)
        );
        //here add other work to do
        std::cout << "YES  " << std::endl;
        int ret = io.run();
        thread.join();
    }
private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int cnt_;
};

#endif //PRINTER_V2_H_