/**
*Author: Steve Zhong
*Creation Date: 2015年08月13日 星期四 23时31分09秒
*Last Modified: 2015年08月29日 星期六 13时49分29秒
*Purpose:
**/

#include "code_db.h"

namespace common {
namespace instrument {

std::unordered_map<std::string, std::string> code_db::jp_code_map;
std::unordered_map<std::string, code_db::inner_stock_info> code_db::code_info_map;

bool code_db::configure(const std::string& code_path)
{
    std::vector<stock_basic> code_info;
    datautils::read_code_jp_name(code_info, code_path);
    for (auto info : code_info) {
        jp_code_map[info.jp] = info.code;
        code_info_map[info.code] = inner_stock_info(info.code, info.name, info.market_code);
    }
    return true;
}

bool code_db::check_code_exist(const string& code)
{
    if (code_info_map.find(code) == code_info_map.end()) {
        logger::code_error(code);
        return false;
    }
    return true;
}

bool code_db::check_code_exist_multi(const std::vector<std::string>& code_vec)
{
    for (auto code : code_vec) {
        if (!check_code_exist(code)) {
            return false;
        }
    }
    return true;
}

bool code_db::from_jp_to_code(std::vector<std::string>& vec)
{
    bool flag = true;
    for (auto &elem : vec) {
        if (isdigit(elem[0])) {
            if (!check_code_exist(elem)) {
                flag = false;
            }
        }
        else {
            auto iter = jp_code_map.find(elem);
            if (iter != jp_code_map.end()) {
                elem = iter->second;
            }
            else {
                logger::code_error(elem);
                flag = false;
            }
        }
    }
    return flag;
}

// 获得股票名称
std::string code_db::get_name(const std::string& code)
{
    return code_info_map[code].name;
}

size_t code_db::code_size()
{
    return code_info_map.size();
}


}
}
