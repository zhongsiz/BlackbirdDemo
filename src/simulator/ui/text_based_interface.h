/**
*Author: Steve Zhong
*Creation Date: 2015年07月11日 星期六 17时16分48秒
*Last Modified: 2015年09月12日 星期六 21时52分10秒
*Purpose:
**/
#ifndef TEXT_BASED_INTERFACE_H
#define TEXT_BASED_INTERFACE_H

#include <vector>
#include <cstring>
#include <cstdlib>
#include <clocale>

#include <cstdio>

#include <ncurses.h>

#include <common/system/cctime.h>
#include <common/instrument/stock.h>
#include <common/instrument/stockterm.h>
#include <common/ui/val_convert.h>

namespace simulator {
namespace ui {

class text_based_interface {
    using val_convert        = common::ui::val_convert;
    using process_double_t = common::ui::process_double_t;
    using stock            = common::instrument::stock;
    using stock_basic      = common::instrument::stock_basic;
    using market           = common::instrument::market;
public:
    text_based_interface()
    {
    }
    ~text_based_interface()
    {
        endwin();
    }
    // 显示大盘行情
    int print_market(const std::vector<market>& market_vec)
    {
        initialize();
        print_header("大盘行情");
        int row = 1, col = 0;
        for (auto one : market_vec) {
            int flag = one.inc_qty > 0 ? 1 : (one.inc_qty == 0 ? 0 : -1);
            col = 0;
            mvaddstr(row, col, one.name.c_str());
            col += 15;
            print_double_flag(row, col, one.index, flag);
            col += 15;
            print_double_flag(row, col, one.inc_qty, flag);
            col += 15;
            print_string_flag(row, col, (val_convert::to_string_pcs(one.inc_per, 2) + "%").c_str(), flag);
            col += 15;
            mvaddstr(row, col, val_convert::process_volumn_market(one.volumn).c_str());
            col += 15;
            mvaddstr(row, col, val_convert::process_to_market(one.turnover).c_str());
            ++row;
        }
        refresh();
        nodelay(win_handle, TRUE);
        if (kbhit('q')) {
            clear();
            endwin();
            return -1;
        }
        return 0;
    }
    int print_stock(const std::vector<stock>& stock_vec, const char* header_name)
    {
        initialize();
        print_header(header_name);
        stock_info(stock_vec);
        nodelay(win_handle, TRUE);
        if (kbhit('q')) {
            endwin();
            return -1;
        }
        return 0;
    }
    int print_options(const std::vector<stock>& stock_vec)
    {
        initialize();
        print_header("自选股行情");
        stock_info(stock_vec);
        nodelay(win_handle, TRUE);
        if (kbhit('q')) {
            endwin();
            return -1;
        }
        return 0;
    }
private:
    void initialize()
    {
        setlocale(LC_ALL, "zh_CN.UTF-8"); // 支持中文

        initscr(); // start curses mode
        win_handle = stdscr;
        getmaxyx(win_handle, row_, col_);
    }
    void print_header(const char* header_name)
    {
        mvprintw(0, 0, "%s    %s", header_name, common::timewrapper::get_curr_date_time().c_str());
    }
    void stock_info(const std::vector<stock>& stock_vec)
    {
        std::vector<const char*> strvec = {common::CODE_CH,
            common::NAME_CH,
            common::CURR_P,
            common::INC,
            common::INC_V,
            common::OPEN_P,
            common::CLOSE_P,
            common::HIGH_P,
            common::LOW_P,
            common::VOL,
            common::TO};
        int row = 1, col = 0;

        attron(A_BOLD);
        for (auto str : strvec) {
            mvaddstr(row, col, str);
            col += 10;
        }
        attroff(A_BOLD);

        row++;
        for (auto one : stock_vec) {
            col = 0;
            mvprintw(row, col, "%s", one.code.c_str()); // 股票代码
            col += 10;
            mvprintw(row, col, "%s", one.name.c_str()); // 股票名称
            col += 10;
            print_double(row, col, one.curr_price, one.curr_price - one.close_price);
            col += 10;
            print_string(row, col, one.inc, &val_convert::get_inc);
            col += 10;
            print_double(row, col, one.inc_v, one.inc_v);
            col += 10;
            print_double(row, col, one.open_price, one.open_price - one.close_price);
            col += 10;
            mvprintw(row, col, "%.2lf", one.close_price);
            col += 10;
            print_double(row, col, one.high_price, one.high_price - one.close_price);
            col += 10;
            print_double(row, col, one.low_price, one.low_price - one.close_price);
            col += 10;
            print_string(row, col, one.volumn, &val_convert::process_volumn, true);
            col += 10;
            print_string(row, col, one.turnover, &val_convert::process_to, true);
            ++row;
        }
        refresh();
    }
    void print_string(int row, int col, const double& val, process_double_t proc_double_func, bool flag = false) const
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        if (flag || (val > -0.001 && val < 0.001)) {
            attron(COLOR_PAIR(3));
            mvaddstr(row, col, proc_double_func(val).c_str());
            attroff(COLOR_PAIR(3));
        }
        else if (val >= 0.001) {
            attron(COLOR_PAIR(1));
            mvaddstr(row, col, proc_double_func(val).c_str());
            attroff(COLOR_PAIR(1));
        }
        else if (val <= -0.001) {
            attron(COLOR_PAIR(2));
            mvaddstr(row, col, proc_double_func(val).c_str());
            attroff(COLOR_PAIR(2));
        }
    }
    void print_double(int row, int col, const double& val, double const& flag) const
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        if ((val > -0.001 && val < 0.001) || (flag > -0.001 && flag < 0.001)) {
            attron(COLOR_PAIR(3));
            mvprintw(row, col, "%.2lf", val);
            attroff(COLOR_PAIR(3));
        }
        else if (flag >= 0.001) {
            attron(COLOR_PAIR(1));
            mvprintw(row, col, "%.2lf", val);
            attroff(COLOR_PAIR(1));
        }
        else if (flag <= -0.001) {
            attron(COLOR_PAIR(2));
            mvprintw(row, col, "%.2lf", val);
            attroff(COLOR_PAIR(2));
        }
    }

    void print_double_flag(int row, int col, const double& val, int flag) const
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        if (flag == 0) {
            attron(COLOR_PAIR(3));
            mvprintw(row, col, "%.2lf", val);
            attroff(COLOR_PAIR(3));
        }
        else if (flag  == 1) {
            attron(COLOR_PAIR(1));
            mvprintw(row, col, "%.2lf", val);
            attroff(COLOR_PAIR(1));
        }
        else if (flag <= -0.001) {
            attron(COLOR_PAIR(2));
            mvprintw(row, col, "%.2lf", val);
            attroff(COLOR_PAIR(2));
        }
    }
    void print_string_flag(int row, int col, const std::string& val, int flag) const
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        if (flag == 0) {
            attron(COLOR_PAIR(3));
            mvaddstr(row, col, val.c_str());
            attroff(COLOR_PAIR(3));
        }
        else if (flag  == 1) {
            attron(COLOR_PAIR(1));
            mvaddstr(row, col, val.c_str());
            attroff(COLOR_PAIR(1));
        }
        else if (flag <= -0.001) {
            attron(COLOR_PAIR(2));
            mvaddstr(row, col, val.c_str());
            attroff(COLOR_PAIR(2));
        }
    }
private:
    int kbhit(char target_ch)
    {
        int ch = getch();
        if (ch != ERR) { return ch == target_ch; }
        else { return 0; }
    }
private:
    int row_, col_;
    WINDOW* win_handle;
};

}
}

#endif
