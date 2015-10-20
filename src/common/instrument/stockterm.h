/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年07月26日 星期日 20时11分29秒
*Purpose:
**/

#ifndef COMMON_DEFS_H_
#define COMMON_DEFS_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace common {

static const char* CODE_CH     = "股票代码";
static const char* NAME_CH     = "股票名称";

static const char* CURR_P      = "现价";
static const char* OPEN_P      = "今开";
static const char* CLOSE_P     = "昨收";
static const char* HIGH_P      = "最高";
static const char* LOW_P       = "最低";

static const char* VOL         = "成交量";
static const char* TO          = "成交额";

static const char* INC         = "涨幅";
static const char* INC_V       = "涨跌";

static const std::string all = "A股";
static const std::string cyb = "创业板";
static const std::string zxb = "中小板";
static const std::string sz  = "深市";
static const std::string sh  = "沪市";

enum class stock_type { SH, SZ };

}

#endif
