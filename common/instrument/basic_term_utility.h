/*
 * Author: Steve Zhong
 * Creation Date: 2016年02月20日 星期六 14时39分27秒
 * Last Modified: 2016年02月20日 星期六 21时44分31秒
 * Purpose:
 */
#ifndef BASIC_TERM_UTILITY_H_
#define BASIC_TERM_UTILITY_H_

#include <string>

#include "basic_term_def.h"
#include "../logger.h"

namespace common {

class basic_term_utility {
public:
    // 市场板块名称
    static std::string get_market_bk_name(market_bk bk);
    // 判断是沪市还是深市股票
    static stock_type get_stock_type(const std::string& code);
};

}

#endif
