/**
*Author: Steve Zhong
*Creation Date: 2015年09月07日 星期一 22时38分31秒
*Last Modified: 2015年09月20日 星期日 21时29分00秒
*Purpose: common definition for crawler
**/

#ifndef DEFS_H_
#define DEFS_H_

// forward declare
namespace common {
    class logger;
    class xml_config;
    class json_config;
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
    using xml_parser    = common::xml_config;
    using json_parser   = common::json_config;
    using terminal      = common::ui::terminal;
    using stock         = common::instrument::stock;
    using stock_basic   = common::instrument::stock_basic;
    using market        = common::instrument::market;
}
}

#endif
