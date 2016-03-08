/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月05日 星期二 22时42分07秒
 * Last Modified: 2016年01月11日 星期一 22时18分00秒
 * Purpose: program_option模板部分实现
 */
#ifndef PROGRAM_OPTION_DEF_H_
#define PROGRAM_OPTION_DEF_H_

#include "program_option.h"

namespace common {
namespace infrastructure {

// 添加选项
template <typename Type> bool program_option::add_option(const option_struct<Type>& option)
{
    if (option.value == Type()) {
        desc.add_options()
            (option.name.c_str(), po::value<Type>(), option.desc.c_str())
        ;
    }
    else {
        desc.add_options()
            (option.name.c_str(),
             po::value<Type>()->default_value(option.value),
             option.desc.c_str())
        ;
    }
    return true;
}

template <typename Type, typename ...Args>
bool program_option::add_option(const option_struct<Type>& option, option_struct<Args>... options)
{
    add_options(option);
    add_options(options...);
    return true;
}

}
}

#endif
