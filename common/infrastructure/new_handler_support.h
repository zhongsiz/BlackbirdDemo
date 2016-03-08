/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月19日 星期二 23时14分53秒
 * Last Modified: 2016年01月19日 星期二 23时48分33秒
 * Purpose: mixin风格的基类，用于支持class专属的set_new_handler
 *     来自<<Effective C++>>
 */
#ifndef NEW_HANDLER_SUPPORT_H_
#define NEW_HANDLER_SUPPORT_H_

#include <new>

#include "uncopyable.h"

namespace common {
namespace infrastructure {

namespace {

// RAII资源管理类
class new_handler_holder : private uncopyable
{
public:
    explicit new_handler_holder(std::new_handler nh)
        : handler(nh)
    { }
    ~new_handler_holder()
    {
        std::set_new_handler(handler);
    }
private:
    std::new_handler handler;
};

}

/* 使用方法
 * class Widget : public new_handler_support<Widget> {
 *     ...
 * };
 */
template <typename T>
class new_handler_support
{
public:
    static std::new_handler set_new_handler(std::new_handler p) throw()
    {
        std::new_handler old_handler = current_handler;
        current_handler = p;
        return old_handler;
    }
    static void* operator new(std::size_t size) throw(std::bad_alloc)
    {
        new_handler_holder h(std::set_new_handler(current_handler));
        return ::operator new(size);
    }
private:
    static std::new_handler current_handler;
};

// 初始化每个current_handler为null
template <typename T>
std::new_handler new_handler_support<T>::current_handler = 0;

}
}

#endif
