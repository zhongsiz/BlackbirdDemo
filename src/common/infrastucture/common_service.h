/**
*Author: Steve Zhong
*Creation Date: 2015年08月26日 星期三 00时38分59秒
*Last Modified: 2015年08月28日 星期五 00时27分14秒
*Purpose: service基类
**/

#ifndef COMMON_SERVICE_H_
#define COMMON_SERVICE_H_

#include <memory> // shared_ptr

#include <ev.h>

#include "uncopyable.h"

// forward declaration
namespace common {
    class configurator; // 配置器
}

namespace common {
namespace infrastucture {

class service : private uncopyable {
public:
    service();
    // 开始运行服务
    void run();    
protected:
    // 程序配置器
    std::shared_ptr<configurator> config;
    // 事件循环
    struct ev_loop *ev_loop_;
public:
    // provide configurator type
    using config_type = std::shared_ptr<configurator>;
};

}
}

#endif
