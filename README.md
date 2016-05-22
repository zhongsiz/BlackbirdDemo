## Blackbird-A股神器(A Niubility China Stock Tools)
Blackbird是一款茁壮成长的A股神器, 有任何建议或意见，欢迎联系[Steve](mailto:zhongsizhi@foxmail.com)。

### Demo -- 行情模拟器(mdsim)
![Blackbird.gif](demo/mdsim.gif)

### 更新

* 2016-05-22: [A股上市公司简介](https://allall01.baidupcs.com/file/264458661b0648360dc20c082a031219?bkt=p3-1400264458661b0648360dc20c082a0312197dccbef90000004a1000&fid=2451167519-250528-707399430314362&time=1463910935&sign=FDTAXGERLBH-DCb740ccc5511e5e8fedcff06b081203-kYF4rh4eNg86oHhwcc%2Bi%2BbW7FZg%3D&to=wb&fm=Yan,B,M,mn&sta_dx=5&sta_cs=0&sta_ft=tar&sta_ct=0&fm2=Yangquan,B,M,mn&newver=1&newfm=1&secfm=1&flow_ver=3&pkey=1400264458661b0648360dc20c082a0312197dccbef90000004a1000&sl=76480590&expires=8h&rt=sh&r=224789053&mlogid=3310704560960432128&vuk=2451167519&vbdid=2278995082&fin=company_basic.tar&fn=company_basic.tar&slt=pm&uta=0&rtype=1&iv=0&isw=0&dp-logid=3310704560960432128&dp-callid=0.1.1)

### Build && Usage

1. Linux下编译参考[wiki](https://github.com/subler/Blackbird/wiki/Blackbird%E7%BC%96%E8%AF%91%E6%8C%87%E5%8D%97(Linux))
2. 拷贝基础数据

        cp -r data/ build/bin/
3. 拷贝配置文件

        cp config/*.xml build/bin/
4. 运行程序

        ./mdsim -c mdsim.xml
5. 输入命令和参数

        # 沪市现价前10股票
        --bk sh -T 10 -O xj
    查看实时行情，可按`q`退出。

**mdsim**用于查看实时行情，提供功能如下：

        -H [ --help ]         显示帮助信息
        -Q [ --quit ]         退出程序
        --code arg            查看个股信息，代码用','分开
        -c [ --config ] arg   设置配置文件
        --bk arg              批量显示行情
            可能值(沪|深|创|中小|全部): sz|sh|cyb|zxb|all
        -M [ --market ]       显示大盘行情
            沪市|深市|创业板
        -T [ --top ] arg      筛选前几个信息
        -O [ --order ] arg    排序规则
            可能值:
                正序： zdf(涨跌幅)|xj(现价)|cjl()|cje(成交额)
                逆序： zdfi|xji|cjli|cjei
        --add-option arg      追加自选股,股票代码用','分开
        --del-option arg      删除自选股,股票代码用','分开
        --show-option         查看自选股
