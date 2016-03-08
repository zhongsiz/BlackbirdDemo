/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期日 10时55分24秒
*Last Modified: 2015年10月28日 星期三 22时55分11秒
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

timewrapper::timewrapper(const std::string& date, time_type_enum time_type)
{
    timeinfo = new tm();
    switch (time_type) {
        case time_type_enum::DATE:
            strptime(date.c_str(), "%F", timeinfo);
            break;
        case time_type_enum::TIME:
            strptime(date.c_str(), "%T", timeinfo);
            break;
        case time_type_enum::DATETIME:
            strptime(date.c_str(), "%F %T", timeinfo);
            break;
        default:
            break;
    }
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

