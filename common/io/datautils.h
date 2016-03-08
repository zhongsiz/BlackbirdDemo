/*
 * Author: Steve Zhong
 * Creation Date: 2015年08月26日 星期三 23时49分23秒
 * Last Modified: 2016年03月06日 星期日 23时52分43秒
 * Purpose: 代码/数据文件读写类
 */

#ifndef DATA_UTILS_H_
#define DATA_UTILS_H_

#include <string>
#include <vector>
#include <fstream>

#include "../utility.h"
#include "../instrument/stock.h"
#include "../instrument/basic_term_def.h"
#include "../instrument/category/ths.h"
#include "fileutils.h"
#include "io_wrapper.h"

namespace common {
namespace io {

class datautils {
	using self_type   = datautils;
	using stock       = common::instrument::stock;
    using stock_basic = common::instrument::stock_basic;
    // 同花顺行业信息
    using ths_hy_category = common::instrument::ths_hy_category;
    // 同花顺概念板块信息
    using ths_gn_category = common::instrument::ths_gn_category;
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
        std::string bk_term_name;
        if (bk == "all") bk_term_name = MARKET_BK_NAME[0];
        else if (bk == "cyb") bk_term_name = MARKET_BK_NAME[1];
        else if (bk == "zxb") bk_term_name = MARKET_BK_NAME[2];
        else if (bk == "sz") bk_term_name = MARKET_BK_NAME[3];
        else if (bk == "sh") bk_term_name = MARKET_BK_NAME[4];
        bk_term_name += "股票代码列表.ds";
        ifstream ifs(path + bk_term_name);
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
    /*
     * 读取同花顺分类信息
     */
    static void read_ths_hy_category(const string& path,
            std::vector<ths_hy_category>& hy_vec,
            std::vector<std::vector<std::string>>& hy_code_vec)
    {
        // 行业分类总数量
        std::ifstream ifs(path + "ths_category.ds");
        std::string hy_id, hy_code, hy_name;
        while (ifs >> hy_id >> hy_code >> hy_name) {
            hy_vec.push_back(ths_hy_category(hy_code, hy_name));
        }
        ifs.close();
        // 每个行业的股票代码
        std::string code;
        std::vector<std::string> code_vec;
        for(const auto& hy_category : hy_vec) {
            ifs.open(path + "category_code_" + hy_category.hy_name + ".ds");
            while (ifs >> code) {
                code_vec.push_back(code);
            }
            ifs.close();
            hy_code_vec.push_back(code_vec);
            code_vec.clear();
        }
    }
    /*
     * 读取同花顺概念板块信息
     */
    static void read_ths_gn_category(const string& path,
            std::vector<ths_gn_category>& gn_vec,
            std::vector<std::vector<std::string>>& gn_code_vec)
    {
        // 行业概念板块总数量
        std::ifstream ifs(path + "gn.ds");
        std::string gn_code, gn_name;
        while (ifs >> gn_code >> gn_name) {
            gn_vec.push_back(ths_gn_category(gn_code, gn_name));
        }
        ifs.close();
        // 每个概念板块的股票代码
        std::string code;
        std::vector<std::string> code_vec;
        for(const auto& gn_category : gn_vec) {
            ifs.open(path + gn_category.gn_name + ".ds");
            while (ifs >> code) {
                code_vec.push_back(code);
            }
            ifs.close();
            gn_code_vec.push_back(code_vec);
            code_vec.clear();
        }
    }
};

}
}

#endif
