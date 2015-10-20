/**
*Author: Steve Zhong
*Creation Date: 2015年09月08日 星期二 21时54分13秒
*Last Modified: 2015年09月08日 星期二 22时24分09秒
*Purpose:  crawler wrapper
**/

#ifndef CRAWLER_WRAPPER_H_
#define CRAWLER_WRAPPER_H_

#include <memory>

#include "include/sina_crawler.h"

namespace gateway {
namespace crawler {

class sina_crawler;

class crawler_wrapper {
public:
    // sina realtime stock data
    // void get_sina_rt_stock_data(const std::vector<std::string>& code_vec, std::vector<stock>& stock_vec, bool all = false);
private:
    std::shared_ptr<sina_crawler> sina_crawler_ptr;    
};

}
}

#endif
