/**
*Author: Steve Zhong
*Creation Date: 2015年08月16日 星期日 21时33分19秒
*Last Modified: 2015年11月17日 星期二 01时29分52秒
*Purpose:
**/

#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

#include "../utility.h"
#include "../logger.h"

#include "encoding.h"

namespace common {

std::string encoding::gbk_to_utf8(std::string str) {
    size_t len = str.length();
    char *src = (char*) malloc(len);
    char *dest = (char*) calloc(1, len * 2);

    strcpy(src, str.c_str());
    charset_convert("GBK", "UTF-8", src, len, dest, len * 2);

    return std::string(dest);
}

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

}
