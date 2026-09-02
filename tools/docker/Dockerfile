# Usage
# docker build tools/docker --build-arg VERSION=24.04 -t iutest
# docker run -it -v $(pwd):/iutest iutest bash

ARG VERSION=24.04
FROM ubuntu:$VERSION
ARG VERSION
RUN echo ${VERSION} > image_version

LABEL maintainer="srz_zumix <https://github.com/srz-zumix>"

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN apt-get update -q -y && \
    apt-get install -y --no-install-recommends software-properties-common apt-transport-https && \
    apt-get update -q -y && \
    apt-get install -y \
        make cmake build-essential libssl-dev zlib1g-dev libbz2-dev \
        libreadline-dev libsqlite3-dev wget curl llvm libncurses5-dev libncursesw5-dev \
        xz-utils tk-dev libffi-dev liblzma-dev python3-openssl git \
        language-pack-ja-base language-pack-ja ibus-mozc \
        linux-tools-common linux-tools-generic \
        vim gdb iputils-ping \
        cppcheck \
        subversion \
        python3 python3-pip \
        python3-virtualenv virtualenvwrapper \
        doxygen graphviz && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# pyenv
RUN update-alternatives --install /usr/bin/python  python  /usr/bin/python3 1000 \
                        --slave   /usr/bin/pip  pip  /usr/bin/pip3
ENV PYENV_ROOT=/root/.pyenv
ENV PATH=${PYENV_ROOT}/shims:${PYENV_ROOT}/bin:$PATH
RUN wget https://raw.githubusercontent.com/yyuu/pyenv-installer/master/bin/pyenv-installer -O - | bash && \
    pyenv --version && \
    pyenv install 3.13 && \
    pyenv install 3.12
RUN pyenv local "$(pyenv latest 3.13)" && \
    pip install --upgrade pip && \
    pip install --upgrade setuptools tox requests && \
    pyenv local --unset
RUN pyenv local "$(pyenv latest 3.12)" && \
    pip install --upgrade pip && \
    pip install --upgrade setuptools tox requests && \
    pyenv local --unset
RUN pyenv local "$(pyenv latest 3.13)" "$(pyenv latest 3.12)" && \
    pip install virtualenv

# gcc
ENV GCC_VERSION=14
RUN apt-get update && \
    apt-get install -y --no-install-recommends g++-${GCC_VERSION} gcc-${GCC_VERSION} && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/gcc  gcc  /usr/bin/gcc-${GCC_VERSION} 1000 \
                        --slave   /usr/bin/g++  g++  /usr/bin/g++-${GCC_VERSION} \
                        --slave   /usr/bin/gcov gcov /usr/bin/gcov-${GCC_VERSION}

# clang
ARG CLANG_VERSION=18
RUN apt-get update && \
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
