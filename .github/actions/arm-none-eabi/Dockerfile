FROM ubuntu:xenial

LABEL "com.github.actions.name"="Include What You Use"
LABEL "com.github.actions.description"="Write arguments to the cmake options"
LABEL "com.github.actions.icon"="check"
LABEL "com.github.actions.color"="blue"

LABEL "repository"="https://github.com/srz-zumix/iutest"
LABEL "homepage"="https://github.com/srz-zumix/iutest"
LABEL "maintainer"="https://github.com/srz-zumix"


# https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
RUN dpkg --add-architecture i386 && \
  apt-get update && apt-get -y --no-install-recommends install \
    ca-certificates \
    build-essential clang libc6:i386 \
    bzip2 \
    git \
    cmake make \
    python \
    vim-common astyle \
    wget \
    && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/* && \
  mkdir -p /usr/local/bin/ && \
#   wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q2-update/+download/gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2 && \
#   tar -xf gcc-arm-none-eabi-5_4-2016q2-20160622-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
#   wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 && \
#   tar -xf gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
#   wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2016q4/gcc-arm-none-eabi-6_2-2016q4-20161216-linux.tar.bz2 && \
#   tar -xf gcc-arm-none-eabi-6_2-2016q4-20161216-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
#   wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/6_1-2017q1/gcc-arm-none-eabi-6-2017-q1-update-linux.tar.bz2 && \
#   tar -xf gcc-arm-none-eabi-6-2017-q1-update-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
#   wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2 && \
#   tar -xf gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
  wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2018q2/gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2 && \
  tar -xf gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
  wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2018q4/gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 && \
  tar -xf gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 -C /usr/local/bin/ && rm *.tar.bz2 && \
  apt-get clean

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]
