#include "log.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>

void getNowTime(char *timeStr);

///
//    LOG_I()
//
//    Log an message to the debug output for the platform
//
void LOG_I(const char *formatStr, ...)
{
    va_list params;
    char buf[BUFSIZ];

    va_start(params, formatStr);
    vsprintf(buf, formatStr, params);

#ifdef ANDROID
    __android_log_print(ANDROID_LOG_INFO, "esUtil", "%s", buf);
#else
    char timeStr[48];
    getNowTime(timeStr);
    printf("%s %s\n", timeStr, buf);
#endif

    va_end(params);
}

/**
 * 获取当前时间
 */
void getNowTime(char *timeStr)
{
    memset(timeStr, '\0', 1);
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    int year, month, day, hour, min, sec;
    year = 1900 + timeinfo->tm_year;
    month = 1 + timeinfo->tm_mon;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    sprintf(timeStr, "%4d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec);
}

/**
 * printf now time
 */
void LOG_TIME()
{
    char timeStr[48];
    getNowTime(timeStr);
    printf("now: %s\n", timeStr);
}