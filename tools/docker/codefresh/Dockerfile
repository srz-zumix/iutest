FROM ubuntu:latest

MAINTAINER srz_zumix <zumix.cpp@gmail.com>

RUN apt-get update; \
    apt-get -y upgrade

RUN apt-get update
RUN apt-get -y install git g++ cmake wget

# Google Test/Mock
RUN git clone https://github.com/google/googletest.git ./googletest
WORKDIR googletest/googletest
RUN cp -r include/gtest /usr/local/include/
RUN ls -la /usr/local/include/*
RUN cmake . && cmake --build . && mv libg* /usr/local/lib/
WORKDIR ../
WORKDIR googlemock
RUN cmake . && cmake --build . && mv libg* /usr/local/lib/;
RUN cp -r include/gmock /usr/local/include/

# Google Native Client
#WORKDIR /usr/local
#RUN apt-get -y install libc6-i386 lib32gcc1 lib32stdc++6 unzip lbzip2
#RUN apt-get -y install python
#RUN python --version
#RUN wget http://storage.googleapis.com/nativeclient-mirror/nacl/nacl_sdk/nacl_sdk.zip
#RUN unzip nacl_sdk.zip
#RUN ./nacl_sdk/naclsdk list
#RUN ./nacl_sdk/naclsdk update > /dev/null
#RUN find ./nacl_sdk -maxdepth 1 -type d -name 'pepper_*'
##ENV NACL_SDK_ROOT $(find ./nacl_sdk -maxdepth 1 -type d -name 'pepper_*')
#RUN echo 'export NACL_SDK_ROOT="$(find /usr/local/nacl_sdk -maxdepth 1 -type d -name 'pepper_*')"' >> ~/.bashrc
##RUN echo 'export NACL_SDK_ROOT="$(find /usr/local/nacl_sdk -maxdepth 1 -type d -name 'pepper_*')"' >> ~/.profile

COPY . /usr/src/iutest
WORKDIR /usr/src/iutest
