/**
*Author: Steve Zhong
*Creation Date: 2015年11月08日 星期日 23时40分24秒
*Last Modified: 2015年12月10日 星期四 22时14分27秒
*Purpose: 同花顺分类数据结构
**/
#ifndef COMMON_INSTRUMENT_CATEGORY_THS_H_
#define COMMON_INSTRUMENT_CATEGORY_THS_H_

#include <string>

namespace common {
namespace instrument {

/*
 * 同花顺行业分类
 */
class ths_hy_category {
public:
    ths_hy_category() { }
    ths_hy_category(const std::string& hy_code_, const std::string& hy_name_)
        : hy_code(hy_code_), hy_name(hy_name_)
    { }
public:
    std::string hy_code; // 行业代码
    std::string hy_name; // 行业名称
};

/*
 * 同花顺概念板块分类
 */
class ths_gn_category {
public:
    ths_gn_category() { }
    ths_gn_category(const std::string& gn_code_, const std::string& gn_name_)
        : gn_code(gn_code_), gn_name(gn_name_)
    { }
public:
    std::string gn_code; // 概念代码
    std::string gn_name; // 概念名称
};

}
}

#endif
