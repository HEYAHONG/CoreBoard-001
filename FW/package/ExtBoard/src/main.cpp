#include <stdio.h>
#include <stdint.h>
#include <thread>
#include <chrono>
#include "signal.h"
#include "version.h"
#include "DeamonLog.h"
#include "DBusInterface.h"

static bool isrunning=true;
extern "C" void main_stop_running()
{
    isrunning=false;
}
static void signalHandler(int signum)
{
    if(!isrunning)
    {
        return;
    }
    isrunning=false;
}

static void init_signal()
{
    signal(SIGINT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGILL, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGSEGV, signalHandler);
    signal(SIGTERM, signalHandler);
}


int main(int argc,const char *argv[])
{
    //初始化信号
    init_signal();

    DeamonLog_Init();

    DbusInterface_Init();

    while(isrunning)
    {
        while(isrunning)
        {
            //procd要求守护进程不能退出
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    DbusInterface_Deinit();

    DeamonLog_Deinit();

    return 0;
}
