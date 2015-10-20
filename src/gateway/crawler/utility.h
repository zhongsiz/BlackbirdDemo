/**
*Author: Steve Zhong
*Creation Date: 2015年09月07日 星期一 21时27分03秒
*Last Modified: 2015年09月12日 星期六 22时24分57秒
*Purpose: crawler tools
**/

#ifndef CRAWLER_UTILITY_H_
#define CRAWLER_UTILITY_H_

#include <string>
#include <vector>

namespace gateway {
namespace crawler {

class utility {
public:
    // 600000,000001
    static std::string get_string_stock_code(const std::vector<std::string>& code_vec)
    {
        if (code_vec.empty()) return "";
        std::string string_code = code_vec[0];
        for (size_t idx = 1; idx < code_vec.size(); ++idx)
            string_code += "," + code_vec[idx];
        return string_code;
    }
    // sz000001,sh600000
    static std::string get_string_stock_code_market(const std::vector<std::string>& code_vec)
    {
        if (code_vec.empty()) return "";
        std::string string_code = market_code(code_vec[0]);
        for (size_t idx = 1; idx < code_vec.size(); ++idx) {
            string_code += "," + market_code(code_vec[idx]);
        }
        return string_code;
    }
    // sz000001
    static std::string market_code(const std::string& code)
    {
        return (code[0] == '6' ? "sh" : "sz") + code;
    }

};

}
}

#endif
