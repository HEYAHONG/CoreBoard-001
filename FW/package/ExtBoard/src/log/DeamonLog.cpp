#include "DeamonLog.h"
#include "syslog.h"

void DeamonLog_Init()
{
    //初始化 syslog
    openlog("ExtBoardD", LOG_NDELAY|LOG_NOWAIT|LOG_PID, LOG_DAEMON);
    LOGINFO("DeamonLog Init!");
}

void DeamonLog_Deinit()
{
    LOGINFO("DeamonLog Deinit!");
    //关闭syslog
    closelog();
}
