# earthly version
VERSION 0.6

# Earthfile
FROM ubuntu:22.04

# configure apt to be noninteractive
ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN true

# install dependencies
RUN apt-get update && apt-get install -y \
      build-essential cmake \
      git \
      python3 python-is-python3

# iutest test env
ENV IUTEST_OUTPUT_DIR=TestResults

WORKDIR /code

all:
  BUILD +lint
  BUILD +build
  BUILD +test

full:
  BUILD +all
  BUILD +cppcheck

code:
  COPY . src

build:
  FROM +code
  RUN mkdir -p ${IUTEST_OUTPUT_DIR}
  RUN cmake src/projects/cmake -DTEST_OUTPUT_DIR=${IUTEST_OUTPUT_DIR}
  # cache cmake temp files to prevent rebuilding .o files
  # when the .cpp files don't change
  RUN --mount=type=cache,target=/code/CMakeFiles make

test:
  FROM +build
  RUN --mount=type=cache,target=/code/CMakeFiles ctest .
  SAVE ARTIFACT ${IUTEST_OUTPUT_DIR} AS LOCAL earthly-out/

lint:
  FROM +code
  RUN make -C src/test/cpplint

cppcheck:
  FROM +code
  RUN apt-get update && apt-get install -y cppcheck
  RUN make -C src/test/cppcheck
  RUN make -C src/test/cppcheck html HTML_REPORT_DIR=./cppcheck-result
  SAVE ARTIFACT src/test/cppcheck/cppcheck-result AS LOCAL earthly-out/
