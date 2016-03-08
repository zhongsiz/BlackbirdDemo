/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月04日 星期一 23时38分17秒
 * Last Modified: 2016年01月05日 星期二 00时49分26秒
 * Purpose: XML解析器
 *    注意：该类不能被拷贝
 */
#include <boost/property_tree/xml_parser.hpp>

#include "../xml_parser.h"

namespace common {

xml_parser::xml_parser() { }
xml_parser::xml_parser(const string& xml_file_name)
{
    parse(xml_file_name);
}
// 解析配置文件
bool xml_parser::parse(const string& xml_file_name)
{
    pt::read_xml(xml_file_name, tree, pt::xml_parser::no_comments);
    return true;
}

}
