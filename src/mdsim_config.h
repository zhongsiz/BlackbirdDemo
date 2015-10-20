/**
*Author: Steve Zhong
*Creation Date: 2015年06月22日 星期一 00时13分41秒
*Last Modified: 2015年09月12日 星期六 14时17分23秒
*Purpose: 行情模拟器
**/

#ifndef MDSIM_CONFIG_H_
#define MDSIM_CONFIG_H_

#include <gateway/crawler/include/sina_crawler.h>

#include <common/logger.h>
#include <common/instrument/code_db.h>
#include <common/infrastucture/common_service.h>

#include <simulator/market_data_client.h>
#include <simulator/option_manager.h>
#include <simulator/ui/text_based_interface.h>

#include <common/configurator.h>

#include <ev.h>

using code_db                   = common::instrument::code_db;

using sina_crawler              = gateway::crawler::sina_crawler;
using tb_displayer              = simulator::ui::text_based_interface;

using md_client_t               = simulator::market_data_client<code_db, sina_crawler, tb_displayer>;
using option_manager_t          = simulator::option_manager<code_db, sina_crawler, tb_displayer>;

using logger                    = common::logger;
using configurator              = common::configurator;
using common_service            = common::infrastucture::service;

// libev timer watch wrapper
struct ev_io_data {
    ev_io watcher;
    md_client_t *md_client_ptr;
    option_manager_t *option_manager_ptr;
    typename common_service::config_type config;
};

#endif
