##Blackbird-A股神器(A Niubility China Stock Tools)
Blackbird是一款茁壮成长的A股神器，目前支持Linux和Windows(Cygwin), 有任何建议或意见，欢迎联系[Steve](mailto:zhongsizhi@foxmail.com)。

###Demo -- 行情模拟器(mdsim)
![Blackbird.gif](demo/demo.gif)

`mdsim`用与查看实时行情，目前提供功能如下：

    -h [ --help ]         显示帮助信息
    -a [ --code ] arg     查看个股信息，代码用','分开
    -c [ --config ] arg   设置配置文件
    -d [ --data ] arg     批量显示行情
    -m [ --market ]       显示大盘行情
    -t [ --top ] arg      筛选前几个信息
    -o [ --order ] arg    排序规则
    --add-option arg      追加自选股,股票代码用','分开
    --del-option arg      删除自选股,股票代码用','分开
    -O [ --show-option ]  查看自选股

### Blackbird计划与实现
Blackbird是2015年A股大牛市和大熊市而萌生一系列炒股想法的实现(2015-06-20)，它的目标如下:

1. 短期目标：辅助个人炒股
2. 长期目标
    1. 量化分析
    2. 自动交易

开发目标和计划如下：

* 整体目标
    * [x] Linux支持
    * [ ] Windows支持
        * [x] Cygwin
        * [ ] Win Application
* 功能模块
    * 操盘助手(ActionSupport)模块
        * 监控行情
            * [x] 邮件通知
                * [ ] 优化触发条件
        * 策略选股
            * [ ] 优化策略
                * [ ] 羊驼算法
                * [x] 基于历史数据选股(nightly)
                    * [ ] 增强
            * [ ] 策略设置UI -- Qt
            * [ ] 策略分析结果 -- HTML
    * 数据中心(DataCenter)模块
        * 历史数据
            * [x] 日级别历史数据
                * [ ] 断点续传
                * [ ] 多线程
            * [ ] 时分级别历史数据
        * 实时数据
            * [x] 简单行情接口
                * [ ] 实时资金流向
                    * [ ] 大/中/小单分布
        * 公司行业信息
            * [x] 基本信息
            * [ ] 完善公司信息
            * [ ] 完善行业信息
        * 政策信息
            * [ ] 收集信息
        * 数据存储
            * [ ] 文件二进制化 
            * [x] K-V数据库
            * [ ] 关系数据库
    * 模拟器
        * 实时行情查询
            * [ ] 优化体验
        * 模拟交易
            * [x] 平台登录
            * [x] 持股查询
            * [ ] 交易操盘
