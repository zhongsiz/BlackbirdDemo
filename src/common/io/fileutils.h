/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 21时15分57秒
*Last Modified: 2015年10月14日 星期三 22时56分59秒
*Purpose:
**/

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <initializer_list>

#include <boost/filesystem.hpp>

#include "../logger.h"

namespace fs          = boost::filesystem;

namespace common {
namespace io {

// 写文件模式
enum class FILEMODE { OVERWRITE, APPEND };

class fileutils {
    using self_type   = fileutils;
public:
    // 写文件
    template <typename T>
    static bool save_file(const std::string& filename, const T& content, FILEMODE file_mode = FILEMODE::OVERWRITE)
    {
        ofstream ofs;
        if (file_mode == FILEMODE::OVERWRITE) {
            ofs.open(filename);
        }
        else if (file_mode == FILEMODE::APPEND) {
            ofs.open(filename, ios::app);
        }
        ofs << content;
        ofs.close();
        return true;
    }
    // 删除文件
    static bool remove_file(const std::string& filename)
    {
        return remove(filename.c_str()) == 0;
    }
    // 删除目录中所有文件
    static int remove_all_file(const std::string& path)
    {
        // 调用bash命令
        std::string command("exec rm -r " + path + "*");
        return system(command.c_str());
    }
    // 删除目录中特定模式(目录+模式)文件
    static int remove_pattern_file(const std::string& pattern)
    {
        // 调用bash命令
        std::string command("exec rm " + pattern);
        return system(command.c_str());
    }
    // 重命名文件
    static bool rename_file(const string& oldname, const string& newname)
    {
        return rename(oldname.c_str(), newname.c_str()) == 0;
    }
    // 合并文件(file1->file2)
    static void merge_file(const string& filename1, const string& filename2, const string& new_filename = "", bool delete_file1 = false)
    {
        std::ifstream ifs(filename1);
        std::ofstream ofs(filename2);
        ofs << ifs.rdbuf();
        ofs.close();
        // 删除文件1
        if (delete_file1) {
            self_type::remove_file(filename1);
        }
        // 重命名文件
        if (new_filename != "") {
            self_type::rename_file(filename1, new_filename);
        }
    }
    // 获取得到文件列表
    static void get_file_list(std::vector<std::string>& file_list, const std::string& path)
    {
        if (fs::exists(path.c_str())) {
            fs::directory_iterator end_iter;
            for (fs::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter) {
                if (fs::is_regular_file(*dir_iter) && dir_iter->path().extension() == ".csv") {
                    file_list.push_back(dir_iter->path().filename().string());
                }
            }
        }
        else {
            common::logger::dir_not_exist(path);
        }
    }
    template <typename T>
    static bool check_files_exist(initializer_list<T> file_names)
    {
        for (auto beg = begin(file_names); beg != end(file_names); ++beg) {
            if (!fs::exists(*beg)) {
                return false;
            }
        }
        return true;
    }
    static bool create_folder(const char* dir_path, bool show_logger = false)
    {
        fs::path path(dir_path);
        if (!fs::exists(path)) {
            if (show_logger)
                logger::log_info("创建文件夹 " + std::string(dir_path));
            return fs::create_directories(path);
        }
        return true;
    }
};

}
}
#endif
