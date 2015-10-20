/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年07月06日 星期一 23时53分08秒
*Purpose:
**/

#ifndef IO_WRAPPER_H_
#define IO_WRAPPER_H_

#include <string>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <fstream>
#include <initializer_list>

#include <boost/filesystem.hpp>

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

    template <typename T>
    static void list_out(const std::vector<int>width, const char* endctl, std::initializer_list<T> list)
    {
        size_t idx = 0;
        for (auto elem : list) {
            cout << std::setw(width[idx++]) << std::left << elem;
        }
        cout << endctl;
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
    static void out_variadic(ostream& out, T& t)
    {
        out << t << endl;
    }

    template <typename T, typename... Args>
    static void out_variadic(ostream& out, T& t, Args... args)
    {
        out << t;
        out_variadic(out, args...);
    }
};

}
}

#endif
