/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月05日 星期二 22时36分17秒
 * Last Modified: 2016年02月21日 星期日 15时33分49秒
 * Purpose: boost program_option封装
 *    注意：该类不能被拷贝
 */
#ifndef PROGRAM_OPTION_H_
#define PROGRAM_OPTION_H_

#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "../logger.h"
#include "uncopyable.h"

namespace common {
namespace infrastructure {

namespace po = boost::program_options;

namespace {
    // 选项描述
    template <typename Type>
    struct option_struct {
        std::string name;
        std::string desc;
        Type value;
    };
    // 无参数选项
    struct plain_option_struct {
        std::string name;
        std::string desc;
    };
}

// 程序选项
class program_option : private uncopyable {
public:
    program_option();
    program_option(const std::string&);
    program_option(program_option&& rsh);
public:
    // 批量添加无参数选项
    // 匿名空间必须内部链接(internal linkage)
    bool add_plain_option(const std::vector<plain_option_struct>& options)
    {
        for (const auto& option : options) {
            desc.add_options()
                (option.name.c_str(), option.desc.c_str())
            ;
        }
        return true;
    }
    // 添加含参数选项
    template <typename Type>
    bool add_option(const option_struct<Type>& option);
    // 批量添加含参数选项
    template <typename Type, typename ...Args>
    bool add_option(const option_struct<Type>& option, option_struct<Args>... options);
public:
    // 选项是否设置
    inline bool is_option_set(const std::string& name);
    // 获取string类型选项值
    std::string get_string_option(const std::string& name);
    // 获取int类型选项值
    int get_int_option(const std::string& name);
public:
    // 解析命令行选项
    bool parse_command_line(char argc, char* argv[]);
    // 解析字符串选项
    bool parse_string_options(const std::string& str_cmd);
public:
    // 增加另一个程序选项
    program_option& add(const program_option& rhs);
    // 打印程序选项
    void show_options() const;
public:
    // 删除所有选项
    void delete_option_value();
private:
    // 选项描述
    po::options_description desc;
    // 选项值
    po::variables_map vm;
};

inline bool program_option::is_option_set(const std::string& name)
{
    return vm.count(name);
}

}
}

#endif
