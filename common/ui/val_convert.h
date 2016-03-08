/*
 * Author: Steve Zhong
 * Creation Date: 2015年07月11日 星期六 22时04分00秒
 * Last Modified: 2016年01月03日 星期日 17时49分46秒
 * Purpose: 显示相关数字转换，主要是
 *   1. 百分号转换
 *   2. 不同单位数字转换
 *   3. 提取字符串中的数字
 */
#ifndef VAL_CONVERT_H_
#define VAL_CONVERT_H_

#include <string>
#include <functional>

#include "../utility.h"

namespace common {
namespace ui {

class val_convert {
public:
    static std::string process_volumn(const double& vol) {
        if (vol < 1e6) { return utility::to_string((uint32_t)(vol / 1e2)); }
        else { return utility::to_string_pcs(vol / 1e6, 2) + "万"; }
    }
    static std::string process_to(const double& to) {
        return (utility::to_string_pcs(to / 1e8, 2) + "亿");
    }
    static std::string process_volumn_market(const double& vol) {
        return utility::to_string_pcs(vol / 1e4, 2) + "万";
    }
    static std::string process_to_market(const double& to) {
        return (utility::to_string_pcs(to / 1e4, 2) + "亿");
    }
    static std::string get_inc(const double& inc) {
        if (inc > 0.0) { return "+" + utility::to_string_pcs(100 * inc, 2) + "%"; }
        else if (inc < 0.0) { return utility::to_string_pcs(100 * inc, 2) + "%"; }
        else { return "0.00"; }
    }
    // wrapper of utility::to_string_pcs(...)
    template <typename T>
    static std::string to_string_pcs(const T& param, const size_t n = 0)
    {
        return utility::to_string_pcs(param, n);
    }
public:
    /*
     * 提取字符串头部double值
     * 1. 0.87blabla -> 0.87
     * 2. 0.87亿 -> 0.87
     */
    static double get_head_double_from_string(const std::string& mix_str)
    {
        return std::stod(mix_str);
    }
};

using process_double_t = std::function<std::string(const double&)>;

}
}

#endif
