/**
*Author: Steve Zhong
*Creation Date: 2015年08月09日 星期日 16时52分29秒
*Last Modified: 2015年09月22日 星期二 21时20分07秒
*Purpose: 新浪爬虫
**/

#include <common/instrument/stock.h>

#include "../tools/sina_decoder.h"
#include "../crawler_impl.h"
#include "../utility.h"

#include "../include/sina_crawler.h"

namespace gateway {
namespace crawler {

sina_crawler::sina_crawler():
    crawler_ptr(new crawler_impl())
{
}

// 获取个股信息
void sina_crawler::get_stock_data(const std::vector<std::string>& code_vec, std::vector<stock>& stock_vec, bool all)
{
    // 生成url
    std::string url = get_stock_url(code_vec);
    // 获取行情数据
    std::string md_data = crawler_ptr->get_string_content(url);
    // 解码
    sina_decoder::decode(md_data, stock_vec, all);
}

// 获取大盘行情
void sina_crawler::get_market_data(const std::vector<std::string>& market_codes, std::vector<market>& market_vec) 
{
    // 生成url
    std::string url = get_market_url(market_codes);
    // 获取行情数据
    std::string md_data = crawler_ptr->get_string_content(url);
    // 解码
    sina_decoder::decode_market(md_data, market_vec);
}

// 获取个股接口URL列表-未加上sh/sz前缀
std::string sina_crawler::get_stock_url(const std::vector<std::string>& code_vec) {
    return "http://hq.sinajs.cn/list="
        + utility::get_string_stock_code_market(code_vec);
}

// 获取市场接口URL列表-未加上sh/sz前缀
std::string sina_crawler::get_market_url(const std::vector<std::string>& market_codes) {
    return "http://hq.sinajs.cn/list="
        + utility::get_string_stock_code(market_codes);
}

}

}
