/**
*Author: Steve Zhong
*Creation Date: 2015年07月04日 星期六 22时34分11秒
*Last Modified: 2015年08月29日 星期六 13时48分02秒
*Purpose:
**/

#ifndef CODE_DB_H_
#define CODE_DB_H_

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <cctype>

#include "../logger.h"
#include "../io/datautils.h"
#include "stock.h"

namespace common {
namespace instrument {

// 内存数据库，方便快速查找验证
class code_db {
    using datautils = io::datautils;
public:
    // 配置数据
    bool configure(const std::string& code_path);
    // 检查股票代码是否存在
    bool check_code_exist_multi(const std::vector<std::string>& code_vec);
    // 将简拼转换为代码
    bool from_jp_to_code(std::vector<std::string>& vec);
    // 检查单个股票代码是否存在
    bool check_code_exist(const std::string& code);
    // 获得股票名称
    std::string get_name(const std::string& code);
    // 股票数量
    size_t code_size();
private:
    // 股票信息内部类
    struct inner_stock_info {
        inner_stock_info() { }
        inner_stock_info(const std::string code_, const std::string name_, const std::string market_code_):
            code(code_),
            name(name_),
            market_code(market_code_)
        {
        }
        std::string code;           // 代码
        std::string name;           // 名称
        std::string market_code;    // 加上sh/sz的代码
    };
private:
    // 简拼和代码映射
    static std::unordered_map<std::string, std::string> jp_code_map;
    // 股票简拼和相关信息映射
    static std::unordered_map<std::string, inner_stock_info> code_info_map;
public:
    // code_info_map开始迭代器
    unordered_map<std::string, inner_stock_info>::const_iterator get_codeinfomap_begin()
    {
        return code_info_map.begin();
    }
    // code_info_map结束迭代器
    unordered_map<std::string, inner_stock_info>::const_iterator get_codeinfomap_end()
    {
        return code_info_map.end();
    }
};

}
}

#endif
