/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月05日 星期二 22时39分27秒
 * Last Modified: 2016年02月21日 星期日 15时35分17秒
 * Purpose: boost program_option实现
 */
#include <exception>
#include "../program_option.h"

namespace common {
namespace infrastructure {

namespace po = boost::program_options;

program_option::program_option()
{
    desc.add_options()
        ("help,H", "显示帮助信息")
    ;
}

program_option::program_option(const std::string& name)
    : desc(po::options_description(name))
{
    desc.add_options()
        ("help,H", "显示帮助信息")
    ;
}

program_option::program_option(program_option&& rsh) :
    desc(std::move(rsh.desc)),
    vm(std::move(rsh.vm))
{
}

std::string program_option::get_string_option(const std::string& name)
{
    return vm[name].as<std::string>();
}

int program_option::get_int_option(const std::string& name)
{
    return vm[name].as<int>();
}

bool program_option::parse_command_line(char argc, char* argv[])
{
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
    }
    catch (po::error& err) {
        common::logger::parse_option_error(err.what());
        return false;
    }
    po::notify(vm);
    if (is_option_set("help")) {
        show_options();
    }
    return false;
}

bool program_option::parse_string_options(const std::string& str_cmd)
{
    std::string origin_cmd = str_cmd;
    std::vector<std::string> args = po::split_unix(str_cmd);
    try {
        po::store(po::command_line_parser(args).options(desc).run(), vm);
        po::notify(vm);
    }
    catch(po::error& err) {
        // 显示错误信息
        common::logger::log_info("未知选项：" + origin_cmd);
        return false;
    }
    return true;
}

program_option& program_option::add(const program_option& rhs)
{
    desc.add(rhs.desc);
    return *this;
}

void program_option::show_options() const 
{
    logger::log_info(desc);
}

// 删除所有选项
void program_option::delete_option_value()
{
    vm = po::variables_map();
}

}
}
