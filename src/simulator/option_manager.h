/**
*Author: Steve Zhong
*Creation Date: 2015年07月04日 星期六 23时57分03秒
*Last Modified: 2015年11月17日 星期二 01时19分06秒
*Purpose: 自选股管理器
**/

#ifndef OPTION_MANAGER_H
#define OPTION_MANAGER_H

#include <string>
#include <memory>

#include <ev.h>

#include <common/utility.h>
#include <common/io/datautils.h>
#include <common/instrument/stock.h>

namespace simulator {

template <typename code_db, typename md_crawler, typename displayer>
class option_manager {
    using self_type    = option_manager<code_db, md_crawler, displayer>;
    using utility      = common::utility;
    using datautils    = common::io::datautils;
    using stock        = common::instrument::stock;
private:
    // timer
    struct ev_timer_wrapper {
        ev_timer timeout_watcher;
        ev_io *main_io_watcher;
        self_type *opt_manger_ptr;
    };
public:
    // configure option manager
    void configure(const std::string& code_path_, const std::string& option_path_)
    {
        option_path = option_path_;
        db->configure(code_path_);
    }
    // add option stock
    void add_option(const std::string& options)
    {
        std::vector<std::string> code_vec;
        utility::split(options, ',', code_vec);
        if (db->from_jp_to_code(code_vec)) {
            datautils::add_option(code_vec, option_path);
        }
    }
    // delete option stock
    void del_option(const std::string& options)
    {
        std::vector<std::string> code_vec;
        utility::split(options, ',', code_vec);
        if (db->from_jp_to_code(code_vec)) {
            datautils::del_option(code_vec, option_path);
        }
    }
    // show option stock data
    bool show_option(struct ev_loop*& ev_loop_, ev_io *main_io_watcher)
    {
        // get option stock code
        datautils::read_option(opt_code_vec, option_path, true);
        // set timer
        timer_wrapper.opt_manger_ptr  = this;
        timer_wrapper.main_io_watcher = main_io_watcher;
        ev_timer_init(&timer_wrapper.timeout_watcher, opt_timeout_cb, 0, 1);
        ev_timer_start(ev_loop_, &timer_wrapper.timeout_watcher);
        return true;
    }
private:
    static void opt_timeout_cb(struct ev_loop *ev_loop_, ev_timer *w, int)
    {
        ev_timer_wrapper *timer_wrapper = (ev_timer_wrapper*) w;
        auto opt_manager_ptr = timer_wrapper->opt_manger_ptr;
        // clear stock vector
        opt_manager_ptr->opt_stock_vec.clear();
        opt_manager_ptr->crawler_.get_stock_data(opt_manager_ptr->opt_code_vec,
                opt_manager_ptr->opt_stock_vec);
        // display option stock data
        if (opt_manager_ptr->displayer_.print_options(opt_manager_ptr->opt_stock_vec) == -1) {
            // stop timer-watcher
            ev_timer_stop(ev_loop_, w);
            // start main io-watcher
            ev_io_start(ev_loop_, timer_wrapper->main_io_watcher);
        }
    }
private:
    std::string option_path;
    std::shared_ptr<code_db> db;
    std::vector<std::string> opt_code_vec;
    std::vector<stock> opt_stock_vec;
    md_crawler crawler_;
    displayer displayer_;
private:
    ev_timer_wrapper timer_wrapper;
};

}

#endif
