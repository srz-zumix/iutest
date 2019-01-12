FROM ubuntu:xenial

LABEL "com.github.actions.name"="Hello World"
LABEL "com.github.actions.description"="Hello World"
LABEL "com.github.actions.icon"="mic"
LABEL "com.github.actions.color"="green"
LABEL "repository"="https://github.com/srz-zumix/iutest"
LABEL "homepage"="https://github.com/srz-zumix/iutest"
LABEL "maintainer"="srz_zumix <https://github.com/srz-zumix>"

ADD entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

