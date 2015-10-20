/**
*Author: Steve Zhong
*Creation Date: 2015年07月12日 星期日 18时05分07秒
*Last Modified: 2015年07月24日 星期五 00时33分32秒
*Purpose:
**/

#ifndef STOCK_UTILS_H_
#define STOCK_UTILS_H_

#include <string>

#include "stockterm.h"
#include "../logger.h"

namespace common {

// 获取板块名称
static const string get_bk_name(const std::string& bk)
{
    if (bk == "all") return all;
    else if (bk == "cyb") return cyb;
    else if (bk == "zxb") return zxb;
    else if (bk == "sz") return sz;
    else if (bk == "sh") return sh;
    else {
        logger::log_info("板块名称[" + bk + "]不存在!请检查");
        return "";
    }
}

// 判断是沪市还是深市股票
static stock_type get_stock_type(const std::string& code) {
    return (code[0] == '6' ? stock_type::SH : stock_type::SZ);
}

}
#endif
