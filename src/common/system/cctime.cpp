/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期日 10时55分24秒
*Last Modified: 2015年11月17日 星期二 01时26分59秒
**/

#include "cctime.h"

namespace common {

std::string timewrapper::get_curr_date_time()
{
    tm* timeinfo = new tm();
    curr_time(timeinfo);
    char data_ptr[20];
    strftime(data_ptr, 20, "%F %T", timeinfo);
    return std::string(data_ptr);
}

}

