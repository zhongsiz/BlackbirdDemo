/**
*Author: Steve Zhong
*Creation Date: 2015年07月23日 星期四 20时00分08秒
*Last Modified: 2015年07月30日 星期四 20时59分40秒
*Purpose: 日期类封装
**/

#ifndef CCTIME_H_
#define CCTIME_H_

#include <string>
#include <ctime>
#include <time.h>

// Windows Cygwin Environment
#ifdef __CYGWIN__
  #include "../patch/cpp11.h"
  #include "../patch/strptime_c11.h"
#endif

namespace common {

// 时间封装类
class timewrapper {
public:
    // 默认未当前时间
    timewrapper();
    // 通过YYYY-MM-DD构造
    timewrapper(const std::string& date);
public:
    // 判断日期YYYY-MM-DD是否相等
    bool is_date_equal(const timewrapper& rsh) {
        return timeinfo->tm_year == rsh.timeinfo->tm_year
            && timeinfo->tm_mon == rsh.timeinfo->tm_mon
            && timeinfo->tm_mday == rsh.timeinfo->tm_mday;
    }
public:
    int get_year() { return timeinfo->tm_year + 1900; }
    int get_month() { return timeinfo->tm_mon + 1; }
    int get_day() { return timeinfo->tm_mday; }
public:
    // 时间增加几天
    void add_day(const int n);
    // 静态成员函数
    static void add_day(tm* timeinfo, const int n);
   // 将string类型date转换为tm结构
    static tm* get_tm_from_string(const std::string& date);
    // 将time转换为string结构
    std::string date_to_string();
    // 静态成员函数
    static std::string get_string_from_tm(const tm* timeinfo);
public:
    // 获取当前系统日期YYYY-MM-DD
    static std::string get_curr_date();
    // 获取当前系统日期和时间YYYY-MM-DD HH:MM:SS
    static std::string get_curr_date_time();
private:
    // 获取当前时间和日期
    static void curr_time(tm* &timeinfo) {
        time_t timer;
        time(&timer);
        timeinfo = localtime(&timer);
    }
private:
    char data_ptr[30];
    time_t rawtime;
    tm* timeinfo;
};

// 未完成。。。
class datetime {
public:
    datetime() { }
    datetime(unsigned short year_, unsigned char month_, unsigned char day_)
        : year(year_), month(month_), day(day_)
    { }
    unsigned short get_year() { return year; }
    unsigned short get_month() { return month; }
    unsigned short get_day() { return day; }

    void set_year(unsigned short year_) { year = year_; }
    void set_month(unsigned char month_) { month = month_; }
    void set_day(unsigned char day_) { day = day_; }

    std::string date_to_string() {
        return std::to_string(year) + "-"
            + std::to_string(month) + "-"
            + std::to_string(day);
    }
private:
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
};

}

#endif
