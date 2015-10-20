/**
*Author: Steve Zhong
*Creation Date: 2015年08月24日 星期一 22时56分10秒
*Last Modified: 2015年08月24日 星期一 23时01分53秒
*Purpose: 禁止拷贝类基类
**/

#ifndef UNCOPYABLE_H_
#define UNCOPYABLE_H_

namespace common {

class uncopyable {
protected:
    uncopyable() { }
    ~uncopyable() { }
private:
    // 禁止拷贝构造函数
    uncopyable(const uncopyable&);
    // 禁止赋值操作符
    uncopyable& operator=(const uncopyable&);
};

}

#endif
