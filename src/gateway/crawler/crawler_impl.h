/**
*Author: Steve Zhong
*Creation Date: 2015年09月02日 星期三 01时05分10秒
*Last Modified: 2015年11月17日 星期二 00时53分21秒
*Purpose: libcurl wrapper
**/
#ifndef CRAWLER_IMPL_H_
#define CRAWLER_IMPL_H_

#include <string>
#include <cstdio>
#include <cstdlib>

#include <curl/curl.h>

#include <common/logger.h>

namespace gateway {
namespace crawler {

class crawler_impl {
    using logger = common::logger;
public:
    // 构造函数
    crawler_impl():
        curl_handler(curl_easy_init())
    {
        // 判断是否初始化成功
        if (curl_handler == nullptr) {
            logger::log_info("初始化libcurl失败！");
            exit(-1);
        }
    }
    // 析构函数
    ~crawler_impl()
    {
        curl_easy_cleanup(curl_handler);
    }
    // 获取文本字符串
    std::string get_string_content(const std::string& url)
    {
        // 检查URL
        if (check_url(url)) {
            // 返回数据
            std::string return_data;
            // 设置libcurl选项
            if (set_option_variadic(make_pair(CURLOPT_URL, url.c_str()),
                    make_pair(CURLOPT_WRITEDATA, (void *) &return_data),
                    make_pair(CURLOPT_WRITEFUNCTION, write_cb)))
            {
                // 获取数据
                if (run()) {
                    // 返回获得的数据
                    return return_data;
                }
            }
        }
        return "";
    }
private:
    // 写文本回调函数
    static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata) {
        std::string* str = (std::string *) userdata;
        if (str == NULL || ptr == NULL) {
            logger::log_error("Error while crawl data");
        }
        size_t len = size * nmemb;
        str->append(ptr, len);
        return len;
    }
private:
    // 检查请求URL长度
    bool check_url(const std::string& url)
    {
        // need to change
        if (url.length() > 0 && url.length() < 10000000)
            return true;
        else {
            logger::log_info("请求URL[" + url + "]不合法，请检查！");
            return false;
        }
    }
    // 设置libcurl选项
    template <typename T>
    bool set_option_variadic(const T& one_option)
    {
        return set_option(one_option.first, one_option.second);
    }
    // 设置libcurl选项
    template <typename T, typename... Args>
    bool set_option_variadic(const T& one_option, Args... other_options)
    {
        return set_option(one_option.first, one_option.second)
            && set_option_variadic(other_options...);
    }
    // 开始数据传输
    bool run()
    {
        CURLcode curl_code = curl_easy_perform(curl_handler);
        if (curl_code == CURLE_OK)
            return true;
        else {
            common::logger::log_info("数据传输失败(curl_easy_perform)。");
            return false;
        }
    }
private:
    // 设置libcurl选项
    template <typename Option, typename Value>
    bool set_option(Option opt, Value val)
    {
        // 设置选项
        CURLcode curl_code = curl_easy_setopt(curl_handler, opt, val);
        // 判断是否设置成功
        switch (curl_code) {
            case CURLE_OK: return true;
            case CURLE_UNKNOWN_OPTION: {
                    logger::log_info("设置选项错误：当前libcurl版本不支持选项");
                    return false;
                }
            case CURLE_NOT_BUILT_IN: {
                    logger::log_info("设置选项错误：编译时间不支持选项");
                    return false;
                }
            default: {
                    logger::log_info("设置选项错误：其它错误");
                    return false;
                }
        }
    }
private:
    // libcurl句柄
    CURL *curl_handler;
};

}
}

#endif
