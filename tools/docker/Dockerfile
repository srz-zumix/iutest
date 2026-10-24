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
    pip install --no-cache-dir --upgrade pip==26.2.1 && \
    pip install --no-cache-dir --upgrade setuptools==84.0.0 tox==4.61.2 requests==2.34.2 && \
    pyenv local --unset
RUN pyenv local "$(pyenv latest 3.12)" && \
    pip install --no-cache-dir --upgrade pip==26.2.1 && \
    pip install --no-cache-dir --upgrade setuptools==84.0.0 tox==4.61.2 requests==2.34.2 && \
    pyenv local --unset
RUN pyenv local "$(pyenv latest 3.13)" "$(pyenv latest 3.12)" && \
    pip install --no-cache-dir virtualenv==21.7.8

# gcc
ENV GCC_VERSION=15
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y --no-install-recommends g++-${GCC_VERSION} gcc-${GCC_VERSION} && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/gcc  gcc  /usr/bin/gcc-${GCC_VERSION} 1000 \
                        --slave   /usr/bin/g++  g++  /usr/bin/g++-${GCC_VERSION} \
                        --slave   /usr/bin/gcov gcov /usr/bin/gcov-${GCC_VERSION}

# clang
ARG CLANG_VERSION=22
RUN wget -qO /etc/apt/trusted.gpg.d/apt.llvm.org.asc https://apt.llvm.org/llvm-snapshot.gpg.key && \
    CODENAME="$(. /etc/os-release && echo "${VERSION_CODENAME}")" && \
    echo "deb http://apt.llvm.org/${CODENAME}/ llvm-toolchain-${CODENAME}-${CLANG_VERSION} main" > /etc/apt/sources.list.d/llvm.list && \
    apt-get update && \
    apt-get install -y --no-install-recommends clang-${CLANG_VERSION} && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VERSION} 1000 \
                        --slave   /usr/bin/clang clang /usr/bin/clang-${CLANG_VERSION}

# infer (linux x86_64 only)
ARG TARGETARCH
ARG INFER_VERSION=v1.3.0
ARG INFER_SHA256=02be62ba931cb43e2d42bbf7abf4bd9a410cf8464cce5453934e25c90a825850
RUN if [ "${TARGETARCH:-amd64}" = "amd64" ]; then \
        wget -qO /opt/infer.tar.xz "https://github.com/facebook/infer/releases/download/${INFER_VERSION}/infer-linux-x86_64-${INFER_VERSION}.tar.xz" && \
        echo "${INFER_SHA256}  /opt/infer.tar.xz" | sha256sum -c - && \
        tar xJf /opt/infer.tar.xz -C /opt && \
        rm -f /opt/infer.tar.xz && \
        ln -s "/opt/infer-linux-x86_64-${INFER_VERSION}" /opt/infer; \
    else \
        echo "infer is not available for ${TARGETARCH}; skipped"; \
    fi
ENV PATH=/opt/infer/bin:${PATH}

# perf
RUN rm -f /usr/bin/perf && \
    update-alternatives --install /usr/bin/perf perf $(find /usr/lib/linux-tools -name *generic)/perf 1000

RUN mkdir /iutest
VOLUME [ "/iutest" ]
WORKDIR /iutest
