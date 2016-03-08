/*
 * Author: Steve Zhong
 * Creation Date: 2016年02月20日 星期六 14时32分17秒
 * Last Modified: 2016年02月20日 星期六 15时27分08秒
 * Purpose:
 */
#include "../basic_term_utility.h"

namespace common {

std::string basic_term_utility::get_market_bk_name(market_bk bk) 
{
    return MARKET_BK_NAME[static_cast<uint8_t>(bk)];
}

stock_type basic_term_utility::get_stock_type(const std::string& code)
{
    return (code[0] == '6' ? stock_type::SH : stock_type::SZ);
}

}
