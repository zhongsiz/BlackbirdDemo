/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月08日 星期五 22时26分36秒
 * Last Modified: 2016年01月16日 星期六 10时08分33秒
 * Purpose: 通用配置器
 *     1. 程序选项 ---封装
 *     2. xml解析器---封装
 *    注意：该类不能被拷贝
 */
#ifndef COMMON_CONFIG_H_
#define COMMON_CONFIG_H_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "../tools/xml_parser_def.hpp"

#include "program_option_def.hpp"
#include "uncopyable.h"

namespace common {

class common_config : private uncopyable {
    using program_option = infrastructure::program_option;
public:
    common_config();
public:
    // 解析xml文件
    bool config_xml_file(const std::string& file_name);
    // 获取单节点值
    template <typename T>
    T get_xml_value(const std::string& path);
    // 获取多节点值
    template <typename T>
    std::vector<T> get_xml_multi_value(const std::string& path);
    // 增加程序选项
    bool add_program_option(const std::string& key, const std::string& desc); 
public:
    // 获得xml解析器
    const std::shared_ptr<xml_parser>& xml();
    // 获得程序选项
    program_option& get_program_option(const std::string& option_key);
private:
    // xml 解析器
    std::shared_ptr<xml_parser> xml_config_ptr;
public:
    // 程序选项器
    std::unordered_map<std::string, program_option> program_options;
};

}

#endif
