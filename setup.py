# coding:utf-8

from setuptools import setup, Extension
from Cython.Build import cythonize
from sys import platform
from os import path

if "win32" == platform:
    import pyMSVC

    pyMSVC.setup_environment()
    include_dirs = ["./include"]
    libraries = ["libcurl"]
    library_dirs = [r'./libcurl']
    extra_link_args = None
else:
    curl_root = path.expanduser('~/codes/curl-8.1.1')
    include_dirs = [path.join(curl_root, './include')]
    libraries = ["curl"]
    library_dirs = [path.join(curl_root, './lib/.libs')]
    extra_link_args = ['-Wl,-rpath,%s' % path.join(curl_root, './lib/.libs')]

include_dirs.append('./shim')

ext = [
    Extension(
        "cwrap",
        ["ccurl.pyx", "./shim/shim.c"],
        include_dirs=include_dirs,
        libraries=libraries,
        library_dirs=library_dirs,
        extra_link_args=extra_link_args,
    ),
]

setup(
    name="test_cy",
    author="reboomc",
    ext_modules=cythonize(ext, language_level=3),
)
