/**
*Author: Steve Zhong
*Creation Date: 2015年09月07日 星期一 22时38分31秒
*Last Modified: 2015年11月17日 星期二 00时55分46秒
*Purpose: common definition for crawler
**/

#ifndef DEFS_H_
#define DEFS_H_

// forward declare
namespace common {
    class logger;
    namespace instrument {
        class stock;
        struct stock_basic;
        class market;
    }
    namespace ui {
        class terminal;
    }
}

namespace gateway {
namespace crawler {
    class crawler_impl;
    // usings
    using logger        = common::logger;
    using terminal      = common::ui::terminal;
    using stock         = common::instrument::stock;
    using stock_basic   = common::instrument::stock_basic;
    using market        = common::instrument::market;
}
}

#endif
