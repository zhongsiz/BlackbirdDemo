/*
 * Author: Steve Zhong
 * Creation Date: 2015年11月12日 星期四 22时18分14秒
 * Last Modified: 2015年11月12日 星期四 22时37分54秒
 * Purpose:
 */

#ifndef HISTORY_DATA_H_
#define HISTORY_DATA_H_

#include <string>
#include <vector>

#include "stock.h"

namespace common {
namespace instrument {

class history_data_item {
public:
    std::string time;
    double open_price; // 开盘价
    double close_price; // 收盘价
    double high_price; // 最高价
    double low_price; // 最低价
    double adj_price; // 复权后价格
    double inc; // 涨跌幅(0.10)
};

class stock_history_record {
public:
    std::string code; // 股票代码
    std::string ipo_time; // 上市时间
    std::string endtime; // 已获得的历史数据的时间: 1990-12-05
};

class stock_history_data {
public:
    stock stock_info; // 基本信息
    std::vector<history_data_item> history_data; // 历史数据集合
};

}
}

#endif
