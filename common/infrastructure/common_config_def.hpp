/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月08日 星期五 22时26分36秒
 * Last Modified: 2016年01月16日 星期六 10时13分38秒
 * Purpose: 通用配置器
 *     1. 程序选项 ---封装
 *     2. xml解析器---封装
 *    注意：该类不能被拷贝
 */
#ifndef COMMON_CONFIG_DEF_H_
#define COMMON_CONFIG_DEF_H_

#include "common_config.h"

namespace common {

// 获取单节点值
template <typename T>
T common_config::get_xml_value(const std::string& path)
{
    return xml_config_ptr->get_value<T>(path);
}

// 获取多节点值
template <typename T>
std::vector<T> common_config::get_xml_multi_value(const std::string& path)
{
    return xml_config_ptr->get_multi_value<T>(path);
}

}

#endif
