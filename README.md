##Blackbird-A股神器(A Niubility China Stock Tools)
Blackbird是一款A股神器，目前支持Linux和Windows(Cygwin)平台。Blackbird目标如下

1. 短期目标：辅助个人炒股
2. 长期目标
    1. 量化分析
    2. 自动交易

**Blackbird目前正处于起步阶段，欢迎有兴趣小伙伴加入**

###Demo
![Blackbird.gif](demo/demo.gif)

###Usage
Blackbird目前由以下工具构成

####行情模拟器mdsim
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

###版本更新

####2015-10-20. 闭源

####2015-09-01. Verion 0.4
1. 增加`AS(Action Support)`模块，操盘助手
    1. 实时行情监控
    2. 智能选股

####2015-08-01. Verion 0.3
1. 增加`DataCenter`模块，获取数据(历史数据)

####2015-07-13. Verion 0.2
1. 增加通过简拼查询功能
2. 实时行情刷新功能

####2015-07-01. Verion 0.1
1. 实现基本行情查看

####2015-06-22. Blackbird启动
1. 短期目标：辅助个人炒股
2. 长期目标
    1. 量化分析
    2. 自动交易

###Q&A
#####1. 股票能用程序预测吗？
坚信技术的力量，有利于炒股，当然神器是终极目标。

#####2. 为什么用C++开发？
C++大家都会&&比较熟悉，目前工作也主用C++，由于Blackbird是副业且水平不够，所以进度比较慢。

#####3. 还需要小伙伴吗？
欢迎有兴趣，业余有时间且满足任意条件的小伙伴加入。请联系[Steve Zhong](mailto:zhongsizhi@foxmail.com)。

1. 会C++
2. 热爱前端技术(HTML/CSS/Javascript）
3. 会量化分析的(金融数学统计/数据挖掘等)
4. 认为Blackbird有前途的