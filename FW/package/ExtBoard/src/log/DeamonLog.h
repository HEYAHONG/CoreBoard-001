#ifndef DEAMONLOG_H_INCLUDED
#define DEAMONLOG_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define LOG_HOST "ExtBoard"

#ifndef LOGINFO
#include "syslog.h"
#define LOGINFO_REAL(...)  {syslog(LOG_DAEMON|LOG_INFO,__VA_ARGS__);}
#define LOGINFO(fmt,...) LOGINFO_REAL(LOG_HOST " Info:" fmt,##__VA_ARGS__)
#endif // LOGINFO

#ifndef LOGDEBUG
#include "syslog.h"
#define LOGDEBUG_REAL(...)  {syslog(LOG_DAEMON|LOG_DEBUG,__VA_ARGS__);}
#define LOGDEBUG(fmt,...) LOGDEBUG_REAL(LOG_HOST " Debug:" fmt,##__VA_ARGS__)
#endif // LOGDEBUG

/** \brief DeamonLog初始化
 *
 *
 */
    void DeamonLog_Init();

/** \brief DeamonLog反初始化
 *
 *
 */
void DeamonLog_Deinit();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DEAMONLOG_H_INCLUDED
