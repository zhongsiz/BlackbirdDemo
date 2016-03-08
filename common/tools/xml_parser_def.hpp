/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月04日 星期一 23时38分17秒
 * Last Modified: 2016年01月16日 星期六 10时00分10秒
 * Purpose: xml_parser模板部分实现
 */
#ifndef XML_PARSER_DEF_H_
#define XML_PARSER_DEF_H_

#include "xml_parser.h"

namespace common {

// 获取单节点值
template <typename T>
T xml_parser::get_value(const std::string& path)
{
    try {
        return tree.get<T>(path);
    }
    catch(pt::ptree_error& err) {
        // 文件路径不存在
        logger::parse_config_error(err.what());
        exit(EXIT_FAILURE);
    }
    return T();
}

// 获取多节点值
template <typename T>
std::vector<T> xml_parser::get_multi_value(const std::string& path)
{
    std::vector<T> multi_val;
    try {
        for(auto vt : tree.get_child(path)) {
            multi_val.push_back(vt.second.data());
        }
    }
    catch(pt::ptree_error& err) {
        logger::parse_config_error(err.what());
    }
    return multi_val;
}

// 获取多节点值
template <typename T>
bool xml_parser::obtain_multi_value(const std::string& path, std::vector<T>& multi_val)
{
    try {
        for(auto vt : tree.get_child(path)) {
            multi_val.push_back(vt.second.data());
        }
    }
    catch(pt::ptree_error& err) {
        logger::parse_config_error(err.what());
        return false;
    }
    return true;
}

}

#endif
