FROM srzzumix/codecrumbs:latest

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

COPY . /iutest
WORKDIR /iutest

COPY .ci/codefresh/entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
