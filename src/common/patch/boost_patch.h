/**
*Author: Steve Zhong
*Creation Date: 2015年09月22日 星期二 10时19分21秒
*Last Modified: 2015年09月22日 星期二 10时23分30秒
*Purpose: Boost ygwin patch
**/

#include <string>

#include <boost/property_tree/json_parser.hpp>

#ifndef BOOST_PATCH_H_
#define BOOST_PATCH_H_


/**
 * boost property_tree 解析Unicode Patch
 * 详见： http://stackoverflow.com/questions/10260688/boostproperty-treejson-parser-and-two-byte-wide-characters
 **/
namespace boost { 
namespace property_tree {
namespace json_parser {

// Create necessary escape sequences from illegal characters
template<>
std::basic_string<char> create_escapes(const std::basic_string<char> &s);

}
}
}
#endif
