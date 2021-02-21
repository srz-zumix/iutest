# Usage
# docker build tools/docker --build-arg VERSION=latest -t iutest
# docker run -it -v $(pwd):/iutest iutest bash

ARG VERSION=latest
FROM ubuntu:$VERSION
ARG VERSION
ARG CLANG_VERSION=9
RUN echo ${VERSION} > image_version

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN apt-get update -q -y && \
    apt-get install -y --no-install-recommends software-properties-common apt-transport-https && \
    apt-get update -q -y && \
    apt-get install -y \
        make cmake build-essential libssl-dev zlib1g-dev libbz2-dev \
        libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev libncursesw5-dev \
        xz-utils tk-dev libffi-dev liblzma-dev python-openssl git \
        linux-tools-common linux-tools-generic \
        vim gdb iputils-ping \
        cppcheck \
        subversion \
        python3 python3-pip \
        doxygen graphviz && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# pyenv
RUN update-alternatives --install /usr/bin/python  python  /usr/bin/python3 1000 \
                        --slave   /usr/bin/pip  pip  /usr/bin/pip3 && \
    pip install virtualenv virtualenvwrapper
ENV PYENV_ROOT $HOME/.pyenv
ENV PATH $HOME/.pyenv/shims:$HOME/.pyenv/bin:$PATH
RUN wget https://raw.githubusercontent.com/yyuu/pyenv-installer/master/bin/pyenv-installer -O - | bash && \
    pyenv --version && \
    pyenv install 3.5.9 && \
    pyenv install 3.8.2
RUN pyenv local 3.5.9 && \
    pip install --upgrade pip && \
    pip install --upgrade setuptools tox requests && \
    pyenv local --unset
RUN pyenv local 3.8.2 && \
    pip install --upgrade pip && \
    pip install --upgrade setuptools tox requests && \
    pyenv local --unset
RUN pyenv local 3.5.9 3.8.2 && \
    pip install virtualenv

# gcc
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y --no-install-recommends g++-8 gcc-8 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/gcc  gcc  /usr/bin/gcc-8 1000 \
                        --slave   /usr/bin/g++  g++  /usr/bin/g++-8 \
                        --slave   /usr/bin/gcov gcov /usr/bin/gcov-8

# clang
RUN . /etc/os-release && \
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
    apt-add-repository "deb http://apt.llvm.org/${VERSION_CODENAME}/ llvm-toolchain-${VERSION_CODENAME}-${CLANG_VERSION} main" && \
    apt-get update && \
    apt-get install -y --no-install-recommends clang-${CLANG_VERSION} && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VERSION} 1000 \
                        --slave   /usr/bin/clang clang /usr/bin/clang-${CLANG_VERSION}

# perf
RUN rm -f /usr/bin/perf && \
    update-alternatives --install /usr/bin/perf perf $(find /usr/lib/linux-tools -name *generic)/perf 1000

RUN mkdir /iutest
VOLUME [ "/iutest" ]
WORKDIR /iutest
