/*
 * Author: Steve Zhong
 * Creation Date: 2015年06月23日 星期二 22时30分03秒
 * Last Modified: 2016年03月06日 星期日 23时14分42秒
 * Purpose: 配置器封装
 *     1. Boost::program_option封装
 *     2. Boost中xml解析器封装
 *     3. Boost中json解析器封装
 *    注意：该类不能被拷贝
 */
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

#include "patch/boost_patch.h"

#include "logger.h"
#include "infrastructure/uncopyable.h"

namespace common {

namespace {
    // format program option description
    std::string format_desc(std::string&& desc)
    {
        regex pattern_short("(-)([A-Z])");
        regex pattern_full("(--)(\\w+)");
        desc = regex_replace(desc, pattern_short, "$2");
        desc = regex_replace(desc, pattern_full, "$2"); return desc;
    }
}

namespace po = boost::program_options;
namespace pt = boost::property_tree;

// xml配置文件存储结构
class xml_config : private uncopyable {
public:
    xml_config() { }
    xml_config(const string& xml_file_name)
    {
        parse(xml_file_name);
    }
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

// json配置文件存储结构
class json_config : private uncopyable {
public:
    // 解析配置文件
    bool parse(const string& json_file_name)
    {
        pt::read_json(json_file_name, tree);
        return true;
    }
    // 解析json字符串
    bool parse_string(const string& json_string)
    {
        std::stringstream ss;
        ss << json_string;
        pt::read_json(ss, tree);
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
    // 获取根节点
    const pt::ptree get_root()
    {
        return tree;
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
    bool parse_command_string(std::string& cmd_str)
    {
        size_t pos = cmd_str.find_first_of(' ');
        if (pos != std::string::npos) {
            std::string command = cmd_str.substr(0, pos);
            command_option = cmd_str.substr(pos);
            return parse_string_options(command, true);
        }
        command_option = "";
        return parse_string_options(cmd_str, true);
    }
    std::string get_command_option()
    {
        return command_option;
    }
    // 解析一行程序选项
    // @param is_plain: 是否加上'-'或者'--'的选项, 默认加上
    bool parse_string_options(std::string& str_cmd, bool is_plain = false)
    {
        std::string origin_cmd = str_cmd;
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
            // common::logger::log_info("未知选项：" + std::string(err.what()));
            common::logger::log_info("未知选项：" + origin_cmd);
            return false;
        }
        return true;
    }

    bool parse_xml_file(const string& xml_file_name)
    {
        xml_config_ptr->parse(xml_file_name);
        return true;
    }
    void show_options(bool format = false)
    {
        if (format) {
            std::ostringstream oss;
            oss << desc;
            logger::log_info(format_desc(oss.str()));
        }
        else
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
    std::string command_option;
    po::options_description desc;
    po::variables_map vm;
    pt::ptree tree;
    // xml 解析器
    std::shared_ptr<xml_config> xml_config_ptr;
};

}

#endif
