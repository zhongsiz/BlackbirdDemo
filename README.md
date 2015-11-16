## Blackbird-A股神器(A Niubility China Stock Tools)
Blackbird是一款茁壮成长的A股神器，目前支持Linux, 有任何建议或意见，欢迎联系[Steve](mailto:zhongsizhi@foxmail.com)。

### Demo -- 行情模拟器(mdsim)
![Blackbird.gif](demo/mdsim.gif)

### Build && Usage

1. Linux下编译参考[wiki](https://github.com/subler/Blackbird/wiki/Blackbird%E7%BC%96%E8%AF%91%E6%8C%87%E5%8D%97(Linux))
2. 拷贝基础数据

        `cp -r data/ build/bin/`
3. 拷贝配置文件

        `cp config/*.xml build/bin/`
4. 运行程序

        `./mdsim -c mdsim.xml`

**mdsim**用于查看实时行情，提供功能如下：

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
