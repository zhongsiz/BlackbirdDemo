/*
 * Author: Steve Zhong
 * Creation Date: 2016年01月02日 星期六 21时45分36秒
 * Last Modified: 2016年01月03日 星期日 22时25分09秒
 * Purpose: MySQL客户端实现
 */
#include "../../logger.h"
#include "../../configurator.h"

#include "../mysql_client.h"

namespace common {
namespace db {

// 初始化数据库连接
bool mysql_client::init_db()
{
    connection = mysql_init(NULL);
    if (connection == nullptr) {
        logger::log_error("初始化MySQL失败，请检查!");         
        return false;
    }
    // 获取数据库地址和用户信息
    xml_config config("/ws/stock/config/dc.xml");
    std::string host = config.get_value("data.db.host", std::string());
    unsigned int port = config.get_value("data.db.port", (unsigned int)0);
    std::string user = config.get_value("data.db.user", std::string());
    std::string password = config.get_value("data.db.password", std::string());
    std::string db_name("blackbird");
    connection = mysql_real_connect(connection, host.c_str(), user.c_str(), password.c_str(),
            db_name.c_str(), port, NULL, 0);
    if (connection == nullptr) {
        logger::log_error("连接MySQL失败，请检查!");         
        return false;
    }
    return true;
}

// 执行SQL语句
bool mysql_client::exec_sql(const std::string& sql_stmt) {
    if (mysql_query(connection, sql_stmt.c_str())) {
        logger::log_error("执行SQL语句[" + sql_stmt + "]失败，请检查！");                
        return false;
    }
    return true;
}

// 查询SQL
bool mysql_client::select_query(const std::string& sql_stmt) {
    if (mysql_query(connection, sql_stmt.c_str())) {
        logger::log_error("执行SQL语句[" + sql_stmt + "]失败，请检查！");                
        return false;
    }
    mysql_res = mysql_use_result(connection);
    MYSQL_ROW mysql_row;
    size_t field_idx;
    size_t filed_num;
    while((mysql_row = mysql_fetch_row(mysql_res))) {
        field_idx = 0;
        filed_num = mysql_num_fields(mysql_res);
        while (field_idx < filed_num) {
            logger::log_info_inline(mysql_row[field_idx]);
            logger::log_info_inline("\t");
            ++field_idx;
        }
        logger::log_info("");
    }
    return true;
}

// 关闭数据库连接
bool mysql_client::close_db()
{
    mysql_free_result(mysql_res);
    mysql_close(connection);
    return true;
}

}
}

