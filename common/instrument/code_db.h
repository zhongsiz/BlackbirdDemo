/**
*Author: Steve Zhong
*Creation Date: 2015年07月04日 星期六 22时34分11秒
*Last Modified: 2015年12月11日 星期五 00时10分26秒
*Purpose:
**/

#ifndef CODE_DB_H_
#define CODE_DB_H_

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <cctype>
#include <utility>

#include "../logger.h"
#include "../io/datautils.h"
#include "stock.h"

#include "category/ths.h"

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
    // 获取股票行业分类
    ths_hy_category get_hy_category(const std::string& code); 
    // 获取股票概念分类
    std::vector<ths_gn_category> get_gn_category(const std::string& code); 
    // 获取股票概念分类名称
    std::vector<std::string> get_gn_name(const std::string& code); 
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
    // 股票分类信息 code->{id, name}
    struct inner_stock_category {
        ths_hy_category hy; // 行业(每只股票只有一个行业分类)
        std::vector<ths_gn_category> gn; // 概念板块(一只股票可能属于多个概念板块)
    }; 
private:
    // 简拼和代码映射
    static std::unordered_map<std::string, std::string> jp_code_map;
    // 股票简拼和相关信息映射
    static std::unordered_map<std::string, inner_stock_info> code_info_map;
    // 股票代码和分类信息映射
    static std::unordered_map<std::string, inner_stock_category> code_category_map;
public:
    // 处理分类数据
    void config_category(const std::string& path);
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
