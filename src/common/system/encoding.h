/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年09月22日 星期二 00时04分06秒
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
    static std::string utf8_to_gbk(std::string str);
    static std::string unicode_to_utf8(std::string str);
    // \u56ed\u533a --> 园区
    static std::string ucs_literal_to_utf8(const std::string& ucs_literal);
private:
    // iconv core
    static int charset_convert(const char *from_charset,
                        const char *to_charset,
                        char *in_buf,
                        size_t in_left,
                        char *out_buf,
                        size_t out_left);
    /** unic     字符的Unicode编码值
      * pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
      * outsize  pOutput缓冲的大小
      */
    static int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput, int outSize);
};

}

#endif

