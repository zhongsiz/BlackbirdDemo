/**
*Author: Steve Zhong
*Creation Date: 2015年07月11日 星期六 22时04分00秒
*Last Modified: 2015年08月14日 星期五 23时03分03秒
*Purpose:
**/
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
};

using process_double_t = std::function<std::string(const double&)>;

}
}

#endif
