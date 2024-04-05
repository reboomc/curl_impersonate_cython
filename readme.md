# Goal

provide another python extension, based on [curl-impersonate](https://github.com/lwthiker/curl-impersonate)<br><br>
why re-invent wheel since [cffi version](https://github.com/yifeikong/curl_cffi) exists?<br>
just because plain python codes exist in curl-cffi's output; which caused by cffi's limitation<br>
so this is another choice based on cython

# How to compile

## declaration for references

|files|source|
|-|-|
|cacert.pem|[certifi](https://pypi.org/project/certifi/)|
|include|[curl header files](https://pypi.org/project/curl-cffi/#files)|
|libcurl|[compiled libcurl-impersonate for windows](https://github.com/yifeikong/curl_cffi)|

## install depends & compile-windows

1. Python3.8.10 or higher
1. Visual Studio IDE or BuildTools, which matchs for target python; see [m$](https://my.visualstudio.com/Downloads?q=Visual%20Studio%202019)
1. pip install pymsvc cython

```bat
rem install depends
rem you may need to use correct python path, for line 3 of build.bat
rem d:\Python38-32\python.exe setup.py build_ext -i
build.bat
```

## install depends & compile-linux

1. compile curl-impersonate via [curl-impersonate](https://github.com/lwthiker/curl-impersonate)
1. use your curl project's root, to replace line 17 of setup.py in this project
```python
    curl_root = path.expanduser('~/codes/curl-8.1.1')
```
3. install python3-dev & cython
```bash
sudo apt install python3-dev && pip install cython
sh linux.sh
```

# 用法

```bash
# copy libcurl/libcurl.dll to same directory as test.py's, necessary only for windows
python3 test.py
```

# todo

- [ ] output http cookies