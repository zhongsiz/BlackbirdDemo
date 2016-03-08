/**
*Author: Steve Zhong
*Creation Date: 2015年09月22日 星期二 10时22分47秒
*Last Modified: 2015年09月22日 星期二 10时27分55秒
*Purpose: Boost ygwin patch
**/

#include "boost_patch.h"

/**
 * boost property_tree 解析Unicode Patch
 * 详见： http://stackoverflow.com/questions/10260688/boostproperty-treejson-parser-and-two-byte-wide-characters
 **/
namespace boost { 
namespace property_tree {
namespace json_parser {

// Create necessary escape sequences from illegal characters
template<>
std::basic_string<char> create_escapes(const std::basic_string<char> &s)
{
    std::basic_string<char> result;
    std::basic_string<char>::const_iterator b = s.begin();
    std::basic_string<char>::const_iterator e = s.end();
    while (b != e)
    {
        // This assumes an ASCII superset. But so does everything in PTree.
        // We escape everything outside ASCII, because this code can't
        // handle high unicode characters.
        if (*b == 0x20 || *b == 0x21 || (*b >= 0x23 && *b <= 0x2E) ||
            (*b >= 0x30 && *b <= 0x5B) || (*b >= 0x5D && *b <= 0xFF)  //it fails here because char are signed
            || (*b >= -0x80 && *b < 0 ) ) // this will pass UTF-8 signed chars
            result += *b;
        else if (*b == char('\b')) result += char('\\'), result += char('b');
        else if (*b == char('\f')) result += char('\\'), result += char('f');
        else if (*b == char('\n')) result += char('\\'), result += char('n');
        else if (*b == char('\r')) result += char('\\'), result += char('r');
        else if (*b == char('/')) result += char('\\'), result += char('/');
        else if (*b == char('"'))  result += char('\\'), result += char('"');
        else if (*b == char('\\')) result += char('\\'), result += char('\\');
        else
        {
            const char *hexdigits = "0123456789ABCDEF";
            typedef make_unsigned<char>::type UCh;
            unsigned long u = (std::min)(static_cast<unsigned long>(
                                             static_cast<UCh>(*b)),
                                         0xFFFFul);
            int d1 = u / 4096; u -= d1 * 4096;
            int d2 = u / 256; u -= d2 * 256;
            int d3 = u / 16; u -= d3 * 16;
            int d4 = u;
            result += char('\\'); result += char('u');
            result += char(hexdigits[d1]); result += char(hexdigits[d2]);
            result += char(hexdigits[d3]); result += char(hexdigits[d4]);
        }
        ++b;
    }
    return result;
}

}
}
}
