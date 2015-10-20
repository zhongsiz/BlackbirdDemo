/**
*Author: Steve Zhong
*Creation Date: 2015年08月26日 星期三 23时49分23秒
*Last Modified: 2015年09月12日 星期六 17时36分26秒
*Purpose: 代码/数据文件读写类
**/

#ifndef DATA_UTILS_H_
#define DATA_UTILS_H_

#include <string>
#include <vector>
#include <fstream>

#include "../utility.h"
#include "../instrument/stock.h"
#include "fileutils.h"
#include "io_wrapper.h"

namespace common {
namespace io {

class datautils {
	using self_type   = datautils;
	using stock       = common::instrument::stock;
    using stock_basic = common::instrument::stock_basic;
public:
	static bool save_code(std::vector<std::string>& code_vec, const std::string& dir_path, const std::string& fname)
    {
        fileutils::create_folder(dir_path.c_str());
        ofstream ofs(dir_path + fname, ios::out);
        for (auto code : code_vec) {
            iowrapper::out_variadic(ofs, code);
        }
        ofs.close();
        return true;
    }
    static bool save_code_jp_name(std::vector<stock_basic>& stock_basic_vec, const string& dir_path)
    {
        fileutils::create_folder(dir_path.c_str());
        ofstream ofs(dir_path + "code_jp_name.ds", ios::out);
        std::string data;
        for (auto stock_basic : stock_basic_vec) {
            iowrapper::out_variadic(ofs,
                    stock_basic.code, " ",
                    stock_basic.jp, " ",
                    stock_basic.name, " ",
                    stock_basic.market_code);
        }
        ofs.close();
        return true;
    }
    // 读股票代码数据
    static bool read_code_jp_name(std::vector<stock_basic>& stock_basic_vec, const string& dir_path)
    {
        FILE *ifp = fopen((dir_path + "code_jp_name.ds").c_str(), "r");
        char code[7], jp[7], name[20], market_code[10];
        while (fscanf(ifp, "%s %s %s %s", code, jp, name, market_code) != EOF) {
            stock_basic_vec.push_back(stock_basic(code, jp, name, market_code));
        }
        fclose(ifp);
        return true;
    }
    // read bk code
    static bool read_code(std::vector<std::string>& code_vec, const string& path, const string& bk, bool clear = false)
    {
        // whether clear the origin code vector
        if (clear) code_vec.clear();
        ifstream ifs(path + bk + "_code.ds");
        string code_name;
        while (getline(ifs, code_name)) {
            code_vec.push_back(code_name.substr(0, 6));
        }
        ifs.close();
        return true;
    }
    // 增加自选股
    static bool add_option(const std::vector<std::string>& code_vec, const string& path)
    {
        std::vector<std::string> option_vec;
        self_type::read_option(option_vec, path);
        ofstream ofs(path + "option_code.ds", std::ios::app);
        for (auto code : code_vec) {
            if (std::binary_search(option_vec.begin(), option_vec.end(), code) == false) {
                ofs << code << endl;
            }
        }
        ofs.close();
        return true;
    }
    static bool del_option(std::vector<std::string>& code_vec, const string& path)
    {
        std::vector<std::string> option_vec;
        self_type::read_option(option_vec, path);
        utility::remove_common_vector(option_vec, code_vec);
        ofstream ofs(path + "option_code.ds");
        for (auto code : option_vec) {
            ofs << code << endl;
        }
        ofs.close();
        return true;
    }
    static bool read_option(std::vector<std::string>& code_vec, const string& path, bool clear = false)
    {
        // clear code_vec
        if (clear)
            code_vec.clear();
        ifstream ifs(path + "option_code.ds");
        string code;
        while (ifs >> code) {
            code_vec.push_back(code);
        }
        utility::unique_vector(code_vec);
        ifs.close();
        return true;
    }
};

}
}

#endif
