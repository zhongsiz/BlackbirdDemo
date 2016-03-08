/**
*Author: Steve Zhong
*Creation Date: 2015年10月14日 星期三 22时09分39秒
*Last Modified: 2015年10月14日 星期三 22时12分10秒
*Purpose: leveldb客户端
**/

#ifndef LEVELDB_CLIENT_H_
#define LEVELDB_CLIENT_H_

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <cctype>

#include <leveldb/db.h>
#include "../logger.h"

namespace common {
namespace db {

using db_handler    = leveldb::DB;
using db_status     = leveldb::Status;
using db_options    = leveldb::Options;

class leveldb_client {
public:
    ~leveldb_client()
    {
        close();
    }
    // 配置数据库位置
    void configure(const std::string& db_path_)
    {
        db_path = db_path_;
        // 不存在则创建
        options.create_if_missing = true;
    }
    // 打开数据库
    bool open()
    {
        db_status status = db_handler::Open(options, db_path, &handler); 
        if (status.ok()) {
            return true;
        }
        else {
            common::logger::log_info("数据库打开失败: " + status.ToString());
            return false;
        }
    }
    // 插入数据
    template <typename Key, typename Value>
    bool insert(Key& key, const Value& value)
    {
        db_status status = handler->Put(leveldb::WriteOptions(), key, value);
        return status.ok();
    }
    // 读取数据
    template <typename Key, typename Value>
    db_status select(Key& key, Value& value)
    {
        return  handler->Get(leveldb::ReadOptions(), key, &value);
    }
    // 删除数据
    template <typename Key>
    bool del(const Key& key)
    {
        db_status status = handler->Delete(leveldb::WriteOptions(), key);
        return status.ok();
    }
    // 关闭数据库
    void close()
    {
        delete handler;
    }
private:
    // 数据库位置
    std::string db_path;
    // 数据库选项
    db_options options;
    // 数据库句柄
    db_handler *handler;
};

}
}

#endif
