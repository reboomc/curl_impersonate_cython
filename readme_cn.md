# 目标

基于[curl-impersonate](https://github.com/lwthiker/curl-impersonate)提供python扩展<br><br>
既然已经存在[cffi版本](https://github.com/yifeikong/curl_cffi)的轮子,为什么重新发明一次?<br>
cffi版本的问题在于pyd文件之外, 还存在大量明文的python代码文件<br>
这一定程度上是cffi的限制导致<br>
因此该工程使用cython提供另一个选择

# 如何编译

## 本项目依赖申明

|文件组成|来源|
|-|-|
|cacert.pem|[certifi](https://pypi.org/project/certifi/)|
|include|[curl头文件](https://pypi.org/project/curl-cffi/#files)|
|libcurl|[已编译的libcurl-impersonate win版本](https://github.com/yifeikong/curl_cffi)|

## 安装依赖&编译-windows

1. Python3.8.10 或更高版本(Python3.8.10为支持Windows7的最高版本)
1. 匹配Python的对应Visual Studio IDE或者 BuildTools(IDE非必要); 见[微软官网](https://my.visualstudio.com/Downloads?q=Visual%20Studio%202019);对应python3.8.10的vs版本为vs2019 16.9
1. pip install -i https://pypi.tuna.tsinghua.edu.cn/simple pymsvc cython

```bat
rem 安装依赖
rem 可能需修改build.bat第三行python.exe路径
rem d:\Python38-32\python.exe setup.py build_ext -i
build.bat
```

## 安装依赖&编译-linux

1. 按照[curl-impersonate](https://github.com/lwthiker/curl-impersonate)要求编译impersonate版本
1. 修改本项目setup.py第17行相应目录为curl源码路径
```python
    curl_root = path.expanduser('~/codes/curl-8.1.1')
```
3. 安装python3-dev和cython
```bash
sudo apt install python3-dev && pip install -i https://pypi.tuna.tsinghua.edu.cn/simple cython
sh linux.sh
```

# 用法

```bash
# 具体见test.py
# 拷贝libcurl/libcurl.dll到test.py同目录;仅限win版本
python3 test.py
```

# todo

- [ ] 增加cookie输出