/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月04日 星期一 23时32分25秒
 * Last Modified: 2016年01月16日 星期六 09时58分00秒
 * Purpose: XML解析器
 *    注意：该类不能被拷贝
 */
#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "../logger.h"
#include "../infrastructure/uncopyable.h"

namespace common {

namespace pt = boost::property_tree;

class xml_parser : private uncopyable {
public:
    xml_parser();
    xml_parser(const string& xml_file_name);
public:
    // 解析配置文件
    bool parse(const string& xml_file_name);
    // 获取单节点值
    template <typename T>
    T get_value(const std::string& path);
    // 获取多节点值
    template <typename T>
    std::vector<T> get_multi_value(const std::string& path);
    // 获取多节点值
    template <typename T>
    bool obtain_multi_value(const std::string& path, std::vector<T>& multi_val);
private:
    pt::ptree tree;
};

}

#endif
