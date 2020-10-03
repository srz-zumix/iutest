# Usage
# docker build .ci/osdn -t osdn
# docker run -it -v $(pwd):/iutest -e VERSION=v1.17.0 osd

FROM ruby:2.5

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

RUN gem install osdn-cli
VOLUME $HOME/.config/osdn

ENV LANG C
ENV LC_CTYPE=en_US.UTF-8

VOLUME /iutest
WORKDIR /iutest

COPY entrypoint.sh /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
