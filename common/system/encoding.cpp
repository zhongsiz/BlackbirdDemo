/*
 * Author: Steve Zhong
 * Creation Date: 2015年08月16日 星期日 21时33分19秒
 * Last Modified: 2016年01月16日 星期六 23时31分22秒
 * Purpose:
 */
#include <cstring>
#include <cstdlib>
#include <cassert>

#include <boost/locale/encoding.hpp>
#ifdef __POSIX__
  #include <iconv.h>
#endif

#include "../utility.h"
#include "../logger.h"

#include "encoding.h"

namespace common {

// boost编码转换
namespace BCONV = boost::locale::conv;

std::string encoding::gbk_to_utf8(std::string str) {
#ifdef __POSIX__
    size_t len  = str.length();
    char *src   = (char*) malloc(len);
    char *dest  = (char*) calloc(1, len * 2);

    strcpy(src, str.c_str());
    charset_convert("GBK", "UTF-8", src, len, dest, len * 2);
    return std::string(dest);
#endif
    return conv_charaset_between(str, "GBK", "UTF-8");
}

std::string encoding::utf8_to_gbk(std::string str) {
#ifdef __POSIX__
    size_t len  = str.length();
    char *src   = (char*) malloc(len);
    char *dest  = (char*) calloc(1, len);

    strcpy(src, str.c_str());
    charset_convert("UTF-8", "GBK", src, len, dest, len * 2);
    return std::string(dest);
#endif
    return conv_charaset_between(str, "UTF-8", "GBK");
}

std::string encoding::unicode_to_utf8(std::string str) {
#ifdef __POSIX__
    size_t len  = str.length();
    char *src   = (char*) malloc(len);
    char *dest  = (char*) calloc(1, len * 2);

    strcpy(src, str.c_str());
    charset_convert("UCS-2LE", "UTF-8", src, len, dest, len * 2);
    return std::string(dest);
#endif
    return conv_charaset_between(str, "UCS-2LE", "UTF-8");
} 
std::string encoding::conv_charaset_between(std::string const text,
        std::string const& from_encoding,
        std::string const& to_encoding)
{
    return BCONV::between(text, from_encoding, to_encoding);
}

#ifdef __POSIX__
    int encoding::charset_convert(const char *from_charset, 
            const char *to_charset,
            char *in_buf,
            size_t in_left,
            char *out_buf,
            size_t out_left)
    {
        iconv_t icd;
        char *pin = in_buf;
        char *pout = out_buf;
        size_t out_len = out_left;
        if ((iconv_t)-1 == (icd = iconv_open(to_charset,from_charset))) {
            return -1;
        }
        if ((size_t)-1 == iconv(icd, &pin, &in_left, &pout, &out_left)) {
            iconv_close(icd);
            return -1;
        }
        out_buf[out_len - out_left] = 0;
        iconv_close(icd);
        return (int)out_len - out_left;
    }
#endif

std::string encoding::ucs_literal_to_utf8(const std::string& ucs_literal)
{
    std::vector<std::string> hex_str_vec;
    // ["56ed", "533a"]
    utility::split_string(ucs_literal, "\\u", hex_str_vec);
    std::string utf8_result = "";
    unsigned char output[13];
    int byte_num;
    for (auto hex_str : hex_str_vec) {
        // "0x56ed" -> 0x56ed 
#ifdef __CYGWIN__
        byte_num = enc_unicode_to_utf8_one(strtol(("0x" + hex_str).c_str(), 0, 16), output, 13);
#else
        byte_num = enc_unicode_to_utf8_one(std::stoul("0x" + hex_str, nullptr, 16), output, 13);
#endif
        output[byte_num] = '\0';
        utf8_result += std::string(output, output + byte_num);
    }
    return utf8_result;
}

/**
  * unic     字符的Unicode编码值
  * pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
  * outsize  pOutput缓冲的大小
  */
int encoding::enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput, int outSize)
{
    assert(pOutput != NULL);
    assert(outSize >= 6);
    
    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {                                                                                                     
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+5) = (unic & 0x3F) | 0x80;
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }
    return 0;
}

}
