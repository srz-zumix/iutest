FROM ubuntu:xenial

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

RUN apt-get update -q -y && \
    apt-get install -y software-properties-common
RUN apt-get update -q -y && \
    apt-get install -y wget vim iputils-ping sudo curl && \
    apt-get install -y libsqlite3-dev libssl-dev && \
    apt-get install -y python2.7 python2.7-dev python-virtualenv && \
    apt-get install -y git subversion && \
    apt-get install -y build-essential && \
    apt-get install -y gdb

# pyenv
ENV PYENV_ROOT $HOME/.pyenv
ENV PATH $HOME/.pyenv/shims:$HOME/.pyenv/bin:$PATH
RUN wget https://raw.githubusercontent.com/yyuu/pyenv-installer/master/bin/pyenv-installer -O - | bash
RUN pyenv --version
RUN pyenv install 2.7.13
RUN pyenv install 3.5.2
RUN pyenv install 3.6.0
RUN pyenv local 2.7.13 && \
     pip install --upgrade setuptools pip tox requests && \
     pyenv local --unset
RUN pyenv local 3.5.2 && \
     pip install --upgrade setuptools pip tox requests && \
     pyenv local --unset
RUN pyenv local 3.6.0 && \
     pip install --upgrade setuptools pip tox requests && \
     pyenv local --unset
RUN pyenv local 2.7.13 3.5.2 3.6.0

RUN pip install virtualenv

# gcc
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y g++-8 gcc-8
RUN update-alternatives --install /usr/bin/gcc  gcc  /usr/bin/gcc-8  1000 && \
    update-alternatives --install /usr/bin/g++  g++  /usr/bin/g++-8  1000 && \
    update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-8 1000 && \
    update-alternatives --config gcc && \
    update-alternatives --config g++

# clang
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add - && \
    apt-add-repository "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-7 main" && \
    apt-get update && \
    apt-get install -y clang-7
RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-7 1000 && \
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-7 1000 && \
    update-alternatives --config clang && \
    update-alternatives --config clang++

RUN apt-get clean

RUN mkdir /iutest
VOLUME [ "/iutest" ]
WORKDIR /iutest
