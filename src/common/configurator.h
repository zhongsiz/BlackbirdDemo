/**
*Author: Steve Zhong
*Creation Date: 2015年06月23日 星期二 22时30分03秒
*Last Modified: 2015年11月17日 星期二 01时42分22秒
*Purpose: 配置器封装
*    1. Boost::program_option封装
*    2. Boost中xml解析器封装
*    3. Boost中json解析器封装
*   注意：该类不能被拷贝
**/

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <memory>
#include <exception>
#include <sstream>
#include <regex>

#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "logger.h"
#include "infrastucture/uncopyable.h"

namespace common {

namespace po = boost::program_options;
namespace pt = boost::property_tree;

// xml配置文件存储结构
class xml_config : private uncopyable {
public:
    // 解析配置文件
    bool parse(const string& xml_file_name)
    {
        pt::read_xml(xml_file_name, tree, pt::xml_parser::no_comments);
        return true;
    }
    // 获取单节点值
    template <typename T>
    T get_value(const std::string& path, T)
    {
        try {
            return tree.get<T>(path);
        }
        catch(pt::ptree_error& err) {
            // 文件路径不存在
            common::logger::parse_config_error(err.what());
            exit(EXIT_FAILURE);
        }
        return T();
    }
    // 获取多节点值
    template <typename T>
    bool get_multi_value(const std::string& path, std::vector<T>& multi_val)
    {
        try {
            for(auto vt : tree.get_child(path)) {
                multi_val.push_back(vt.second.data());
            }
        }
        catch(pt::ptree_error& err) {
            common::logger::parse_config_error(err.what());
            return false;
        }
        return true;
    }
private:
    pt::ptree tree;
};

// 程序选项配置
class configurator : private uncopyable {
public:
    configurator():
        xml_config_ptr(new xml_config())
    {
        desc.add_options()
            ("help,H", "显示帮助信息")
        ;
    }
    bool add_plain_option(const char* name, const char* opt_desc)
    {
        desc.add_options()
            (name, opt_desc)
        ;
        return true;
    }
    template <typename T>
    bool add_option(const char* name, const char* opt_desc, T val = T())
    {
        if (val == T()) {
            desc.add_options()
                (name, po::value<T>(), opt_desc)
            ;
        }
        else {
            desc.add_options()
                (name, po::value<T>()->default_value(val), opt_desc)
            ;
        }
        return true;
    }
    bool is_option_set(const std::string& name)
    {
        return vm.count(name);
    }
    template <typename T>
    T get_xml_value(const std::string& path, T)
    {
        return xml_config_ptr->get_value(path, T());
    }
    template <typename T>
    bool get_xml_multi_value(const std::string& path, std::vector<T>& multi_val)
    {
        return xml_config_ptr->get_multi_value(path, multi_val);
    }
    std::string get_string_option(const std::string& name)
    {
        return vm[name].as<std::string>();
    }
    int get_int_option(const std::string& name)
    {
        return vm[name].as<int>();
    }
    bool parse_command_line(char argc, char* argv[])
    {
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);
        }
        catch (po::error& err) {
            common::logger::parse_option_error(err.what());
            return false;
        }
        po::notify(vm);
        // show help option
        if (is_option_set("help")) {
            show_options();
        }
        if (is_option_set("config")) {
            xml_config_ptr->parse(get_string_option("config"));
            return true;
        }
        return false;
    }

    /* 解析一行程序选项
     * @param is_plain: 是否加上'-'或者'--'的选项, 默认加上
     */
    bool parse_string_options(std::string& str_cmd, bool is_plain = false)
    {
        // 未加上'-'或者'--'的选项
        if (is_plain)
            str_cmd = (isupper(str_cmd[0]) ? "-" : "--") + str_cmd;
        std::vector<std::string> args = po::split_unix(str_cmd);
        try {
            po::store(po::command_line_parser(args).options(desc).run(), vm);
            po::notify(vm);
        }
        catch(po::error& err) {
            // 显示错误信息
            common::logger::log_info("未知选项：" + std::string(err.what()));
            return false;
        }
        return true;
    }
    void show_options()
    {
        logger::log_info(desc);
    }
public:
    // 删除所有选项
    void delete_option_value()
    {
        vm = po::variables_map();
    }
    // decode inner program option
    const string decode_string_option(string option)
    {
        if (option[0] == '-') {
            // long option
            if (islower(option[1]))
                return option.substr(1);
            // short option
            else if (option[1] == '-' && isupper(option[2]))
                return option.substr(2);
        }
        return option;
    }
private:
    po::options_description desc;
    po::variables_map vm;
    pt::ptree tree;
    // xml 解析器
    std::shared_ptr<xml_config> xml_config_ptr;
};

}

#endif
