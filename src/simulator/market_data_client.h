/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年11月17日 星期二 01时22分22秒
*Purpose:
**/

#ifndef MARKET_DATA_CLIENT_H_
#define MARKET_DATA_CLIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <memory>
#include <cstdint> // int32_t, uint32_t

#include <ev.h>

#include <common/logger.h>
#include <common/utility.h>
#include <common/configurator.h>
#include <common/io/datautils.h>
#include <common/instrument/stock.h>

namespace simulator {

template <typename code_db, typename md_crawler, typename displayer>
class market_data_client {
private:
    using self_type     = market_data_client<code_db, md_crawler, displayer>;
    using datautils     = common::io::datautils;
    using utility       = common::utility;
    using logger        = common::logger;
    using stock         = common::instrument::stock;
    using stock_basic   = common::instrument::stock_basic;
    using market        = common::instrument::market;
private:
    // libev timer watcher wrapper
    struct ev_timer_wrapper {
        ev_timer timeout_watcher;
        ev_io *main_io_watcher;
        self_type *md_client_ptr;
    };
    struct ev_timer_wrapper_bk : ev_timer_wrapper {
        uint32_t speed;
        uint32_t top_num;
        std::string order;
        const std::vector<std::string>* code_vec;
        std::string bk;
    };
public:
    void configure(std::vector<std::string>& market_codes_, const std::string code_path_)
    {
        // 沪市/深市/各大板块代码
        market_codes = market_codes_;
        code_path = code_path_;
        db->configure(code_path);
    }
    // 查看个股信息
    void show_stock(struct ev_loop*& ev_loop_, ev_io *main_io_watcher, const std::string& code_str)
    {
        code_vec.clear();
        utility::split(code_str, ',', code_vec);
        if (db->from_jp_to_code(code_vec)) {
            // set timer watcher wrapper
            timer_wrapper.main_io_watcher = main_io_watcher;
            timer_wrapper.md_client_ptr = this;
            ev_timer_init(&timer_wrapper.timeout_watcher, stock_timeout_cb, 0, 1);
            ev_timer_start(ev_loop_, &timer_wrapper.timeout_watcher);
        }
    }
    // 查看大盘行情
    void show_market(struct ev_loop*& ev_loop_, ev_io *main_io_watcher)
    {
        // set timer watcher wrapper
        timer_wrapper.main_io_watcher = main_io_watcher;
        timer_wrapper.md_client_ptr = this;
        ev_timer_init(&timer_wrapper.timeout_watcher, market_timeout_cb, 0, 1);
        ev_timer_start(ev_loop_, &timer_wrapper.timeout_watcher);
    }
    // 查看板块行情
    void show_md_bk(struct ev_loop*& ev_loop_, ev_io *main_io_watcher,
        const std::string& bk, uint32_t speed, int32_t top_num, std::string& order)
    {
        code_vec.clear();
        datautils::read_code(code_vec, code_path, bk);
        timer_wrapper_bk.main_io_watcher = main_io_watcher;
        timer_wrapper_bk.md_client_ptr = this;
        timer_wrapper_bk.speed = speed;
        timer_wrapper_bk.top_num = top_num;
        timer_wrapper_bk.order = order;
        timer_wrapper_bk.code_vec = &code_vec;
        timer_wrapper_bk.bk = bk;
        ev_timer_init(&timer_wrapper_bk.timeout_watcher, bk_timeout_cb, 0, 1);
        ev_timer_start(ev_loop_, &timer_wrapper_bk.timeout_watcher);
    }
private:
    static void stock_timeout_cb(struct ev_loop *ev_loop_, ev_timer *w, int)
    {
        ev_timer_wrapper *timer_wrapper = (ev_timer_wrapper*) w;
        auto md_client_ptr = timer_wrapper->md_client_ptr;
        // clear stock vector
        md_client_ptr->stock_vec.clear();
        // get stock data
        md_client_ptr->crawler_.get_stock_data(md_client_ptr->code_vec, md_client_ptr->stock_vec);
        // display stock data
        if (md_client_ptr->displayer_.print_stock(md_client_ptr->stock_vec, "A股个股行情") == -1) {
            // change listener to io watcher
            ev_timer_stop(ev_loop_, w);
            ev_io_start(ev_loop_, timer_wrapper->main_io_watcher);
        }
    }
    static void market_timeout_cb(struct ev_loop *ev_loop_, ev_timer *w, int)
    {
        ev_timer_wrapper *timer_wrapper = (ev_timer_wrapper*) w;
        auto md_client_ptr = timer_wrapper->md_client_ptr;
        // clear stock vector
        md_client_ptr->market_vec.clear();
        // get stock data
        md_client_ptr->crawler_.get_market_data(md_client_ptr->market_codes, md_client_ptr->market_vec);
        // display stock data
        if (md_client_ptr->displayer_.print_market(md_client_ptr->market_vec) == -1) {
            // change listener to io watcher
            ev_timer_stop(ev_loop_, w);
            ev_io_start(ev_loop_, timer_wrapper->main_io_watcher);
        }
    }
    static void bk_timeout_cb(struct ev_loop *ev_loop_, ev_timer *w, int)
    {
        ev_timer_wrapper_bk *timer_wrapper_bk = (ev_timer_wrapper_bk*) w;
        auto md_client_ptr = timer_wrapper_bk->md_client_ptr;
        uint32_t speed = timer_wrapper_bk->speed;
        uint32_t idx = 0;
        std::vector<stock> stock_vec;
        string bk_data;
        // clear stock vector
        md_client_ptr->stock_vec.clear();
        std::vector<std::string> subvec;
        while (utility::get_vec_by_step(*(timer_wrapper_bk->code_vec), idx, speed, subvec)) {
            std::vector<stock> sub_stock_vec;
            // get stock data
            md_client_ptr->crawler_.get_stock_data(subvec, sub_stock_vec);
            md_client_ptr->stock_vec.insert(md_client_ptr->stock_vec.end(),
                sub_stock_vec.begin(),
                sub_stock_vec.end());
        }
        if (!subvec.empty()) {
            std::vector<stock> sub_stock_vec;
            // get stock data
            md_client_ptr->crawler_.get_stock_data(subvec, md_client_ptr->stock_vec);
            md_client_ptr->stock_vec.insert(md_client_ptr->stock_vec.end(),
                sub_stock_vec.begin(),
                sub_stock_vec.end());
        }
        md_client_ptr->select_stock(timer_wrapper_bk->top_num, timer_wrapper_bk->order, md_client_ptr->stock_vec);
        // display stock data
        if (md_client_ptr->displayer_.print_stock(md_client_ptr->stock_vec, "个股行情") == -1) {
            // change listener to io watcher
            ev_timer_stop(ev_loop_, w);
            ev_io_start(ev_loop_, timer_wrapper_bk->main_io_watcher);
        }
    }
private:
    bool select_stock(int32_t top_num, std::string& order, std::vector<stock>& stock_vec)
    {
        if (top_num == -1) top_num = stock_vec.size();

        if (order == "") { }
        else if (order == "zdf") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.inc > rsh.inc; });
        }
        else if (order == "xj") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.curr_price > rsh.curr_price; });
        }
        else if (order == "cjl") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.volumn > rsh.volumn; });
        }
        else if (order == "cje") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.turnover > rsh.turnover; });
        }
        else if (order == "zdfi") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.inc < rsh.inc; });
        }
        else if (order == "xji") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.curr_price < rsh.curr_price; });
        }
        else if (order == "cjli") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.volumn < rsh.volumn; });
        }
        else if (order == "cjei") {
            std::partial_sort(stock_vec.begin(),
                    stock_vec.begin() + top_num,
                    stock_vec.end(),
                    [](const stock& lsh, const stock& rsh) { return lsh.turnover < rsh.turnover; });
        }
        else {
            logger::log_error("排序标准有问题!");
            return false;
        }
        stock_vec = std::vector<stock>(stock_vec.begin(), stock_vec.begin() + top_num);
        return true;
    }
private:
    std::string code_path; // 股票代码文件存放

    std::vector<std::string> code_vec;
    std::vector<stock> stock_vec;
    std::vector<std::string> market_codes;
    std::vector<market> market_vec;
private:
    code_db* db;
    displayer displayer_;
    md_crawler crawler_;
private:
    ev_timer_wrapper timer_wrapper;
    ev_timer_wrapper_bk timer_wrapper_bk;
};

}
#endif
