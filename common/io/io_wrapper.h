/*
 * Author: Steve Zhong
 * Creation Date: 2015年06月22日 星期一 00时13分41秒
 * Last Modified: 2016年03月08日 星期二 00时24分30秒
 * Purpose:
 */
#ifndef IO_WRAPPER_H_
#define IO_WRAPPER_H_

#include <algorithm>
#include <iterator>
#include <string>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <fstream>
#include <initializer_list>

#include <boost/filesystem.hpp>

#include "fileutils.h"

using namespace std;

namespace common {
namespace io {

class iowrapper {
public:
    static bool sd_pair(const char* midctl, const char* endctl, int count, ...)
    {
        std::va_list args;
        va_start(args, count);
        while (count--) {
            cout << va_arg(args, char*) << ": "
                << fixed << setprecision(2)
                << va_arg(args, double) << midctl;
        }
        va_end(args);

        std::cout << endctl;
        return true;
    }

    /*
     * function: 输出表格(中文字符可能无法列队齐)
     * arg1: 每列宽度集合
     * arg3: 数据集合
     * arg2: 一行结束符, 默认换行符
     * arg4: 输出流，默认控制台输出
     */
    template <typename T>
    static void list_out(const std::vector<int> width,
            std::initializer_list<T> list,
            const char* endctl = "\n",
            std::ostream& out = std::cout)
    {
        size_t idx = 0;
        for (auto elem : list)
            out << std::setw(width[idx++]) << std::left << elem;
        out << endctl;
    }

    template <typename T>
    static void list_out(const char* midctl, const char* endctl, std::initializer_list<T> list)
    {
        size_t idx = 0;
        for (auto elem : list) {
            if (idx++ != 0)
                cout << midctl;
            cout << elem;
        }
        cout << endctl;
    }

    template <typename Name, typename Value>
    static bool list_pair_out(const char* midctl, const char* endctl,
            initializer_list<Name> nlist,
            initializer_list<Value> vlist)
    {
        const Name* nit = begin(nlist);
        const Value* vit = begin(vlist);
        while (nit != end(nlist)) {
            cout << (nit == begin(nlist) ? "" : midctl) <<
                *nit << ": " << fixed << setprecision(2) << *vit;
            ++nit, ++vit;
        }
        cout << endctl;

        return true;
    }

    static void sd_pair_one(const string& name, const double& val) { printf("%s: %.2lf\t", name.c_str(), val); }

    template <typename T, typename S>
    static void sd_pair_t(T& first, T& second, bool end = false)
    {
        std::cout << first << "\t" << second;
        if (end) { std::cout << endl; }
    }

    template <typename T>
    static void out_variadic(ostream& out, const T& t)
    {
        out << t << endl;
    }

    template <typename T, typename... Args>
    static void out_variadic(ostream& out, const T& t, Args... args)
    {
        out << t;
        out_variadic(out, args...);
    }
    /*
     * 打印一行
     */
    template <typename Content>
    static void out_oneline(ostream& out, const Content& content)
    {
        out << content << std::endl;
    }
    // 将文件数据读入到向量中
    template <typename Type>
    static void vector_from_file(const std::string& filename, std::vector<Type>& type_vec)
    {
        if (fileutils::check_files_exist({filename})) {
            ifstream ifs(filename, ios::in);
            std::copy(std::istream_iterator<Type>(ifs),
                    std::istream_iterator<Type>(),
                    std::back_inserter(type_vec));
        }
    }
    const static int ITEM_SIZE = 1024;
};

}
}

#endif
