FROM ubuntu:trusty

MAINTAINER srz_zumix <zumix.cpp@gmail.com>

RUN apt-get update -q -y
RUN apt-get install -y wget vim iputils-ping sudo curl
RUN apt-get install -y libsqlite3-dev libssl-dev
RUN apt-get install -y python2.7 python2.7-dev python-virtualenv
RUN apt-get install -y git subversion
RUN apt-get install -y build-essential
RUN mkdir /iutest

# pyenv
ENV PYENV_ROOT $HOME/.pyenv
ENV PATH $HOME/.pyenv/shims:$HOME/.pyenv/bin:$PATH
RUN curl -L https://raw.githubusercontent.com/yyuu/pyenv-installer/master/bin/pyenv-installer | bash
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

ADD Dockerfile /data
RUN git clone https://github.com/srz-zumix/iutest.git /iutest


