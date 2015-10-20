/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期日 10时55分24秒
*Last Modified: 2015年07月30日 星期四 21时00分01秒
*Purpose:
**/

#include "cctime.h"

namespace common {

timewrapper::timewrapper()
{
    timeinfo = new tm();
    curr_time(timeinfo);
    std::strftime(data_ptr, 11, "%F", timeinfo);
}

timewrapper::timewrapper(const std::string& date)
{
    timeinfo = new tm();
    strptime(date.c_str(), "%F", timeinfo);
}

void timewrapper::add_day(tm* timeinfo, const int n)
{
    timeinfo->tm_mday += n;
    mktime(timeinfo);
}

void timewrapper::add_day(const int n)
{
    timeinfo->tm_mday += n;
    mktime(timeinfo);
}

tm* timewrapper::get_tm_from_string(const std::string& date)
{
    tm *timeinfo = new tm();
    strptime(date.c_str(), "%F", timeinfo);
    return timeinfo;
}

std::string timewrapper::date_to_string()
{
    strftime(data_ptr, 11, "%F", timeinfo);
    return std::string(data_ptr);
}

std::string timewrapper::get_string_from_tm(const tm *timeinfo)
{
    char data_ptr[11];
    strftime(data_ptr, 11, "%F", timeinfo);
    return std::string(data_ptr);
}

std::string timewrapper::get_curr_date()
{
    tm* timeinfo = new tm();
    curr_time(timeinfo);
    char data_ptr[11];
    strftime(data_ptr, 11, "%F", timeinfo);
    return std::string(data_ptr);
}

std::string timewrapper::get_curr_date_time()
{
    tm* timeinfo = new tm();
    curr_time(timeinfo);
    char data_ptr[20];
    strftime(data_ptr, 20, "%F %T", timeinfo);
    return std::string(data_ptr);
}

}

