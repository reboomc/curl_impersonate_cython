# coding:utf-8

from cwrap import CurlPy

def run():
    bsl = b"https://tls.browserleaks.com/json"
    baidu = b"https://www.baidu.com"

    c = CurlPy()
    resp = c.request(baidu, None, b"Content-Type: application/json", 0, 180)
    print(resp.decode('utf-8'))

run()