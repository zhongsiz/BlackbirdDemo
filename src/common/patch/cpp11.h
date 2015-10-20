/**
*Author: Steve Zhong
*Creation Date: 2015年08月26日 星期三 23时37分13秒
*Last Modified: 2015年08月26日 星期三 23时37分25秒
*Purpose: C++11 Cygwin patch
**/

#ifndef CPP11_H_
#define CPP11_H_

#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>

namespace std {
    // std::to_string
    template <typename T>
    static std::string to_string(const T& n) {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
    // std::stod
    static double stod(const std::string& str) {
        return atof(str.c_str());
    }
}

#endif
