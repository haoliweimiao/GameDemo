#include "log.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

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
    printf("%s", buf);
#endif

    va_end(params);
}