/**
*Author: Steve Zhong
*Creation Date: 2015年08月25日 星期二 22时07分14秒
*Last Modified: 2015年12月10日 星期四 01时07分16秒
*Purpose: 终端相关工具
**/

#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <iostream>
#include <iomanip>

namespace common {
namespace ui {

class terminal {
public:
    // 生成进度条, x当前位置, n总数, w进度条宽度, x从1开始
    static inline void loadbar(unsigned x, unsigned n, unsigned w = 50)
    {
        if ((x != n) && (x % (n / w + 1) != 0)) return;
        float ratio = x / (float) n;
        unsigned c  = ratio * w;

        std::cout << std::setw(3) << (int) (ratio * 100) << "% [";
        for (unsigned x = 0; x < c; ++x) std::cout << "=";
        for (unsigned x = c; x < w; ++x) std::cout << " ";
        if (x != n)
            std::cout << "]\r" << std::flush;
        else
            std::cout << "]\n" << std::flush;
    }
};

}
}

#endif
