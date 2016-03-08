/**
 * Author: Steve Zhong
 * Creation Date: 2015年08月13日 星期四 23时31分09秒
 * Last Modified: 2015年12月12日 星期六 23时40分03秒
 * Purpose:
 */
#include "code_db.h"

namespace common {
namespace instrument {

std::unordered_map<std::string, std::string> code_db::jp_code_map;
std::unordered_map<std::string, code_db::inner_stock_info> code_db::code_info_map;
std::unordered_map<std::string, code_db::inner_stock_category> code_db::code_category_map;

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
                logger::log_info("若是新股，则可能与Sina关闭简拼接口有关, Update by Steve, 2015-12-12.");
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

ths_hy_category code_db::get_hy_category(const std::string& code)
{
    return code_category_map[code].hy;
}
std::vector<ths_gn_category> code_db::get_gn_category(const std::string& code)
{
    return code_category_map[code].gn;
}

// 获取股票概念分类名称
std::vector<std::string> code_db::get_gn_name(const std::string& code)
{
    std::vector<std::string> gn_name_vec;
    vector<ths_gn_category> ths_gn_category_vec = get_gn_category(code);
    for (auto gn_category_ : ths_gn_category_vec) {
        gn_name_vec.push_back(gn_category_.gn_name);
    }
    return gn_name_vec;
}

size_t code_db::code_size()
{
    return code_info_map.size();
}

void code_db::config_category(const std::string& path)
{
    logger::log_info("配置股票分类信息...");
    logger::log_info("获取股票行业信息...");
    std::vector<ths_hy_category> ths_hy_vec;        
    std::vector<std::vector<std::string>> ths_hy_code_vec;
    datautils::read_ths_hy_category(path + "hy/", ths_hy_vec, ths_hy_code_vec);
    for (size_t idx = 0; idx < ths_hy_vec.size(); ++idx) {
        for (const auto& code : ths_hy_code_vec[idx]) {
            code_category_map[code].hy = ths_hy_vec[idx];
        }
    }
    logger::log_info("获取股票概念板块分类信息...");
    std::vector<ths_gn_category> ths_gn_vec;        
    std::vector<std::vector<std::string>> ths_gn_code_vec;
    datautils::read_ths_gn_category(path + "gn/", ths_gn_vec, ths_gn_code_vec);
    for (size_t idx = 0; idx < ths_gn_vec.size(); ++idx) {
        for (const auto& code : ths_gn_code_vec[idx]) {
            code_category_map[code].gn.push_back(ths_gn_vec[idx]);
        }
    }
}

}
}
