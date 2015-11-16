/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年11月17日 星期二 01时51分47秒
*Purpose:
**/

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>

using namespace std;

namespace common {

class logger {
public:
    static void log_error(const string& error_info) { cerr << error_info << endl; }
    template <typename T> static void log_info(const T& info) { cout << info << endl; }
    template <typename T> static void log_info_inline(const T& info) { cout << info << flush; } // 不加换行
    static void code_error(const string& code) { cerr << "股票代码(简拼)[" << code << "]不存在，请检查！" << endl; }
    static void option_error(const string& option) { cerr << "未知选项[" << option << "]: 格式错误" << endl; }
    static void parse_config_error(const char *error_info) { cerr << "解析配置xml文件错误: " << error_info << endl; }
    static void parse_option_error(const char *error_info) { cerr << "解析程序选项错误: " << error_info << endl; }
};

}

#endif
