/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年09月16日 星期三 22时48分13秒
*Purpose:
**/

#include <iostream>
#include <string>
#include <memory> // shared_ptr

#include "mdsim_config.h" // some using and libev watcher wrapper

class mdsim_service : public common_service {
public:
    // configure mdsim_service using command line argument
    void configure(int argc, char **argv)
    {
        // set user's command
        config->add_plain_option("quit,Q", "退出程序");
        config->add_option("code", "查看个股信息，代码用','分开", std::string());
        config->add_option("config,c", "设置配置文件", std::string());
        config->add_option("bk", "批量显示行情", std::string());
        config->add_plain_option("market,M", "显示大盘行情");
        config->add_option("top,T", "筛选前几个信息", int());
        config->add_option("order,O", "排序规则", std::string());
        config->add_option("add-option", "追加自选股,股票代码用','分开", std::string());
        config->add_option("del-option", "删除自选股,股票代码用','分开", std::string());
        config->add_plain_option("show-option", "查看自选股");
        // parse command line options
        if (!config->parse_command_line(argc, argv)) {
            // 解析命令行参数
            common::logger::log_info("未设置配置文件！");
            return;
        }
        // 初始化行情客户端
        std::vector<std::string> market_code;
        config->get_xml_multi_value("stock.market_data.code.markets", market_code),
        md_client_.configure(market_code,
                config->get_xml_value("stock.market_data.code.code_path", std::string()));
        // 配置自选股管理器
        option_manager_.configure(config->get_xml_value("stock.market_data.code.code_path", std::string()),
                config->get_xml_value("stock.market_data.code.option_path", std::string()));
        // set libev io watcher
        ev_io_data_.config = config;
        ev_io_data_.md_client_ptr = &md_client_;
        ev_io_data_.option_manager_ptr = &option_manager_;
        // listen user input command
        ev_io_init(&ev_io_data_.watcher, parse_command_cb, 0, EV_READ);
        ev_io_start(ev_loop_, &ev_io_data_.watcher);
    }
    // start service
    void run()
    {
        logger::log_info_inline("请输入命令和参数> ");
        // invoke base::run()
        common_service::run();
    }
private:
    // execute user's command
    static void parse_command_cb(EV_P_ ev_io *w, int)
    {
        ev_io_data *io_data      = (ev_io_data*) w;
        // get user data
        auto md_client_ptr      = io_data->md_client_ptr;
        auto option_manager_ptr = io_data->option_manager_ptr;
        common_service::config_type config = io_data->config;
        // get user's input command
        std::string command;
        std::getline(std::cin, command);
        // parse user's command
        if (config->parse_string_options(command)) {
            // 查看个股行情
            if (config->is_option_set("code")) {
                // stop main io loop and will restart in md_client_ptr
                ev_io_stop(loop, w);
                md_client_ptr->show_stock(loop,
                        &io_data->watcher,
                        config->get_string_option("code"));
            }
            // 查看大盘行情
            else if (config->is_option_set("market")) {
                // stop main io loop and will restart in md_client_ptr
                ev_io_stop(loop, w);
                md_client_ptr->show_market(loop, &io_data->watcher);
            }
            // 批量显示股票行情
            else if (config->is_option_set("bk")) {
                // select number
                int32_t top_num = config->is_option_set("top") ? config->get_int_option("top") : -1;
                // 排序规则
                std::string order = config->is_option_set("order") ? config->get_string_option("order") : "";
                // stop main io loop and will restart in md_client_ptr
                ev_io_stop(loop, w);
                md_client_ptr->show_md_bk(loop,
                        &io_data->watcher,
                        config->get_string_option("bk"),
                        config->get_xml_value("stock.market_data.request_speed", uint32_t()),
                        top_num,
                        order);
            }
            // 增加自选股
            else if (config->is_option_set("add-option")) {
                option_manager_ptr->add_option(config->get_string_option("add-option"));
            }
            // 删除自选股
            else if (config->is_option_set("del-option")) {
                option_manager_ptr->del_option(config->get_string_option("del-option"));
            }
            // 显示自选股行情
            else if (config->is_option_set("show-option")) {
                // stop main io loop and will restart in option_manager_ptr
                ev_io_stop(loop, w);
                option_manager_ptr->show_option(loop, &io_data->watcher);
            }
            // show all options
            else if (config->is_option_set("help")) {
                config->show_options();
            }
            // quit
            else if (config->is_option_set("quit")) {
                ev_break(EV_A_ EVBREAK_ALL);
                return;
            }
            // commond don't recognized
            else {
                if (command != "--")
                    logger::option_error(config->decode_string_option(command));
            }
            // delete all commands
            config->delete_option_value();
        }
        logger::log_info_inline("请输入命令和参数> ");
    }
private:
    // 行情客户端
    md_client_t md_client_;
    // 自选股管理器
    option_manager_t option_manager_;
    // libev io watcher wrapper
    ev_io_data ev_io_data_;
};

// mdsim entry
int main(int argc, char* argv[]) {
    mdsim_service *service = new mdsim_service();
    service->configure(argc, argv);
    // libev loop
    service->run();
    return 0;
}
