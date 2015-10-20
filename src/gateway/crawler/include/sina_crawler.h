/**
*Author: Steve Zhong
*Creation Date: 2015年08月09日 星期日 16时52分29秒
*Last Modified: 2015年09月12日 星期六 22时22分27秒
*Purpose: 新浪爬虫
**/

#ifndef SINA_CRAWLER_H_
#define SINA_CRAWLER_H_

#include <string>
#include <vector>
#include <memory>

#include "../defs.h"

namespace gateway {
namespace crawler {

class sina_crawler {
public:
    sina_crawler();
   // 获取个股信息
    void get_stock_data(const std::vector<std::string>& code_vec, std::vector<stock>& stock_vec, bool all = false);
   // 获取大盘行情
    void get_market_data(const std::vector<std::string>& code_vec, std::vector<market>& market_vec);
private:
    // 获取个股接口URL列表-未加上sh/sz前缀
    std::string get_stock_url(const std::vector<std::string>& code_vec);
    // 获取市场接口URL列表-未加上sh/sz前缀
    std::string get_market_url(const std::vector<std::string>& market_codes);
private:
    // 爬虫实现类指针
    std::shared_ptr<crawler_impl> crawler_ptr;
};

}
}

#endif
