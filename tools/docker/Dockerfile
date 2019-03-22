# Usage
# docker build tools/docker -t iutest
# docker run -it -v $(pwd):/iutest iutest bash

FROM ubuntu:xenial

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN apt-get update -q -y && \
    apt-get install -y --no-install-recommends software-properties-common && \
    apt-get update -q -y && \
    apt-get install -y \
        wget vim iputils-ping curl \
        libsqlite3-dev libssl-dev \
        python2.7 python2.7-dev python-virtualenv \
        git subversion \
        build-essential gdb && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# pyenv
ENV PYENV_ROOT $HOME/.pyenv
ENV PATH $HOME/.pyenv/shims:$HOME/.pyenv/bin:$PATH
RUN wget https://raw.githubusercontent.com/yyuu/pyenv-installer/master/bin/pyenv-installer -O - | bash
RUN pyenv --version && \
    pyenv install 2.7.13 && \
    pyenv install 3.5.2 && \
    pyenv install 3.6.0
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
    apt-get install -y --no-install-recommends g++-8 gcc-8 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
RUN update-alternatives --install /usr/bin/gcc  gcc  /usr/bin/gcc-8 1000 \
                        --slave   /usr/bin/g++  g++  /usr/bin/g++-8 \
                        --slave   /usr/bin/gcov gcov /usr/bin/gcov-8

# clang
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
    apt-add-repository "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-7 main" && \
    apt-get update && \
    apt-get install -y --no-install-recommends clang-7 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
RUN update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-7 1000 \
                        --slave   /usr/bin/clang clang /usr/bin/clang-7

RUN mkdir /iutest
VOLUME [ "/iutest" ]
WORKDIR /iutest
