/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年11月17日 星期二 01时29分05秒
*Purpose: 字符编码转换
**/

#ifndef ENCODING_H_
#define ENCODING_H_

#include <string>

#include <iconv.h>

namespace common {

class encoding {
public:
    static std::string gbk_to_utf8(std::string str);
private:
    // iconv core
    static int charset_convert(const char *from_charset,
                        const char *to_charset,
                        char *in_buf,
                        size_t in_left,
                        char *out_buf,
                        size_t out_left);
};

}

#endif

