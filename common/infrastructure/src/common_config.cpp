/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月08日 星期五 22时26分36秒
 * Last Modified: 2016年01月16日 星期六 09时36分51秒
 * Purpose: 通用配置器
 */
#include <utility>

#include "../../logger.h"

#include "../common_config.h"

namespace common {

common_config::common_config():
    xml_config_ptr(new xml_parser())
{
}

bool common_config::config_xml_file(const std::string& file_name)
{
    xml_config_ptr->parse(file_name);
    return true;
}

const std::shared_ptr<xml_parser>& common_config::xml()
{
    return xml_config_ptr;
}

bool common_config::add_program_option(const std::string& key, const std::string& desc)
{
    if (program_options.find(key) != program_options.end()) {
        logger::log_error("已存在，请重新指定选项键值");
        return false;
    }
    program_options.insert(std::make_pair<std::string, program_option>(std::string(key), program_option(desc)));
    
    // program_options.insert(value_type_(key, program_option(desc)));
    return true;
}

common_config::program_option& common_config::get_program_option(const std::string& option_key)
{
    if (program_options.find(option_key) == program_options.end()) {
        logger::log_error("不存在，请重新指定选项键值");
        exit(EXIT_FAILURE);    
    }
    return program_options[option_key];
}


}
