/**
*Author: Steve Zhong
*Creation Date: 2015年07月23日 星期四 20时00分08秒
*Last Modified: 2015年11月17日 星期二 01时27分06秒
*Purpose: 日期类封装
**/

#ifndef CCTIME_H_
#define CCTIME_H_

#include <string>
#include <ctime>
#include <time.h>

namespace common {

// 时间封装类
class timewrapper {
public:
    // 获取当前系统日期和时间YYYY-MM-DD HH:MM:SS
    static std::string get_curr_date_time();
private:
    // 获取当前时间和日期
    static void curr_time(tm* &timeinfo) {
        time_t timer;
        time(&timer);
        timeinfo = localtime(&timer);
    }
};

}

#endif
