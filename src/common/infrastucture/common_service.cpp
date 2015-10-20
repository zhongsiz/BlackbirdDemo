/**
*Author: Steve Zhong
*Creation Date: 2015年08月26日 星期三 00时46分36秒
*Last Modified: 2015年08月26日 星期三 01时13分40秒
*Purpose: service基类
**/

#include "common_service.h"

#include "../configurator.h"

namespace common {
namespace infrastucture {

service::service():
    config(new configurator())
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
