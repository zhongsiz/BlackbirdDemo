/*
 * Author: Steve Zhong
 * Creation Date: 2015年08月26日 星期三 00时46分36秒
 * Last Modified: 2016年03月06日 星期日 20时00分22秒
 * Purpose: service基类
 */
#include "../../configurator.h"
#include "../../blackbird_cfg.h"

#include "../common_service.h"

namespace common {
namespace infrastructure {

service::service():
    config(new configurator()),
    bd_config(new xml_parser(blackbird::CFG_FILE))
{
    ev_loop_ = EV_DEFAULT;
}

// 开始运行服务
void service::run()
{
    ev_run(ev_loop_, 0);
}

}
}
