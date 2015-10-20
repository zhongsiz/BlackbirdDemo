/**
*Author: Steve Zhong
*Creation Date: 2015年08月27日 星期四 00时25分18秒
*Last Modified: 2015年08月27日 星期四 00时26分14秒
*Purpose:
**/

#ifndef PRINT_HELPER_H_
#define PRINT_HELPER_H_

#include <cstdio>

namespace common {
namespace io {

class print_helper {
	static void cmd2f(const double& val) { printf("%.2lf", val); }
    static void divider() { printf("--------------------------------------------------------------------------------\n"); };
};

}
}

#endif
