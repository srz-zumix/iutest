
# Usage
# docker build .ci/docker/googletest -t iutest-gtest --build-arg VERSION=release-1.8.0
# docker run -it -v $(pwd):/iutest iutest-gtest bash

ARG VERSION=latest
FROM srzzumix/googletest:${VERSION}

LABEL maintainer "srz_zumix <https://github.com/srz-zumix>"

ARG VERSION
RUN echo ${VERSION} | tee image_version
VOLUME /iutest
WORKDIR /iutest

