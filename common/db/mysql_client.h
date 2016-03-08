/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月02日 星期六 21时45分36秒
 * Last Modified: 2016年01月03日 星期日 22时09分51秒
 * Purpose: MySQL客户端
 */

#ifndef MYSQL_CLIENT_H_
#define MYSQL_CLIENT_H_

#include <string>
#include <mysql/mysql.h>

namespace common {
namespace db {

class mysql_client {
public:
    // 初始化数据库连接
    bool init_db();
    // 执行SQL语句
    bool exec_sql(const std::string& sql_stmt);
    // 执行SELECT语句
    bool select_query(const std::string& sql_stmt);
    // 关闭数据库连接
    bool close_db();
private:
    MYSQL *connection;
    MYSQL_RES *mysql_res;
};

}
}

#endif
