FROM ubuntu:latest

# https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
RUN apt-get update && apt-get -y --no-install-recommends install \
    git doxygen graphviz \
    wget \
    && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
