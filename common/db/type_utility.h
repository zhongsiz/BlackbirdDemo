/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月03日 星期日 20时19分42秒
 * Last Modified: 2016年01月03日 星期日 21时55分04秒
 * Purpose: 判断数据所属类型
 */
#include <type_traits>

namespace common {
namespace db {

class type_utility {
public:
    template <class Type> bool is_float_point(const Type&);
};

}
}
