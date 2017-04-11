import os
from setuptools import setup
from setuptools import find_packages

#f = open(os.path.join(os.path.dirname(__file__), 'README.md'))
#readme = f.read()
#f.close()

VERSION = "5.3"

setup(
    name = "iuwandbox"
    , version = VERSION
    , author = "Takazumi Shirayanagi"
    , author_email = "zumix.cpp@gmail.com"
    , url = "https://github.com/srz-zumix/iutest"
    , description = "iutest run on wandbox tool."
    , license = "BSD"
    , platforms = ["any"]
    , keywords = "iutest, Wandbox"
    , packages = find_packages()
    , install_requires=['requests']
)
