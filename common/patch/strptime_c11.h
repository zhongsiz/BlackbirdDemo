/**
*Author: Steve Zhong
*Creation Date: 2015年08月26日 星期三 23时38分26秒
*Last Modified: 2015年08月26日 星期三 23时38分36秒
*Purpose: strptime Cygwin patch using c++11(get_time)
**/

#ifndef STRPTIME_H_
#define STRPTIME_H_
 
#include <time.h>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sstream>

#include "../logger.h"

/* 
 * cygwin don't support std::get_time(c++11)
static char *
strptime(const char *buf, const char *fmt, struct tm *tm)
{
    std::istringstream ss(std::string(buf));
    ss >> std::get_time(tm, fmt);
    static char return_char[5];
    return return_char;
}
**/

/* only support following condition
 * 1. fmt: %F
 */
static char *
strptime(const char *buf, const char *fmt, struct tm *tm_ptr)
{
    int year, month, day;
    // YYYY-MM-DD
    if (strcmp(fmt, "%F") == 0) {
        sscanf(buf, "%d-%d-%d", &year, &month, &day); 
        tm_ptr->tm_year = year - 1900;
        tm_ptr->tm_mon = month - 1;
        tm_ptr->tm_mday = day;
    }
    else {
        common::logger::log_info_inline("cygwin上strptime的patch暂不支持[");
        common::logger::log_info_inline(fmt);
        common::logger::log_info("]格式参数");
    }
    // for return purpose
    static char return_char[5];
    return return_char;
}

#endif
