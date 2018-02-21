FROM ubuntu

RUN apt-get -qq update && apt-get -qq install -y \
  git \
  cmake \
  autoconf \
  automake \
  make \
  wget \
  g++-arm-linux-gnueabihf \
  gcc-arm-linux-gnueabihf \
  python \
  python-pip && \
  pip install --upgrade pip && \
  pip install pyaml && \
  rm -rf /var/lib/apt/lists/*

RUN mkdir /root/raspberry && \
  cd /root && \ 
  echo 'using gcc : arm : arm-linux-gnueabihf-g++ ;' > ~/user-config.jam && \
  wget -q https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz && \
  tar -zxf /root/boost_1_66_0.tar.gz && \
  cd /root/boost_1_66_0 && \
  ./bootstrap.sh && \
  ./b2 --prefix=/root/raspberry/ --with-atomic --with-chrono --with-date_time --with-filesystem --with-regex --with-serialization --with-thread --with-system --no-samples --no-tests toolset=gcc-arm cxxflags=-fPIC -j`nproc` && \
  ./b2 --prefix=/root/raspberry/ --with-atomic --with-chrono --with-date_time --with-filesystem --with-regex --with-serialization --with-thread --with-system --no-samples --no-tests toolset=gcc-arm cxxflags=-fPIC -j`nproc` install && \
  rm -fR /root/boost_1_66_0 && \
  rm /root/boost_1_66_0.tar.gz

RUN cd /root && \
  wget -q https://www.openssl.org/source/openssl-1.0.2l.tar.gz && \
  tar -zxf /root/openssl-1.0.2l.tar.gz && \
  rm /root/openssl-1.0.2l.tar.gz && \
  cd /root/openssl-1.0.2l && \
  ./Configure --prefix=/root/raspberry/ os/compiler:arm-linux-gnueabihf && \
  make CC="arm-linux-gnueabihf-gcc" AR="arm-linux-gnueabihf-ar r" RANLIB="arm-linux-gnueabihf-ranlib" -j`nproc` && \
  make install && \
  rm -fR /root/openssl-1.0.2l

RUN cd /root && \
  wget -q https://github.com/nghttp2/nghttp2/releases/download/v1.30.0/nghttp2-1.30.0.tar.gz && \
  tar -zxf nghttp2-1.30.0.tar.gz && \
  cd /root/nghttp2-1.30.0 && \
  ./configure --prefix=/root/raspberry/ --host=armv7l-unknown-linux-gnueabihf --enable-asio-lib CPPFLAGS=-I/root/raspberry/include --with-boost-libdir=/root/raspberry/lib/ CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ && \
  make -j`nproc` && \
  make install && \
  cp /root/nghttp2-1.30.0/./third-party/.libs/libhttp-parser.a /root/raspberry/lib && \
  rm -fR /root/nghttp2-1.30.0 && \
  rm -f /root/nghttp2-1.30.0.tar.gz && \
  mkdir /root/raspberry/PiHttp2Server

RUN cd /root && \
  wget https://github.com/mongodb/libbson/releases/download/1.9.2/libbson-1.9.2.tar.gz && \
  tar -zxf libbson-1.9.2.tar.gz && \
  cd /root/libbson-1.9.2 && \
  ./configure --prefix=/root/raspberry/ --host=armv7l-unknown-linux-gnueabihf CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ && \
  make -j`nproc` && \
  make install && \
  rm -fR /root/libbson-1.9.2 && \
  rm -f /root/libbson-1.9.2.tar.gz && \
  cd /root && \
  wget https://github.com/mongodb/mongo-c-driver/releases/download/1.9.2/mongo-c-driver-1.9.2.tar.gz && \
  tar -zxf mongo-c-driver-1.9.2.tar.gz && \
  cd mongo-c-driver-1.9.2 && \
  ./configure --prefix=/root/raspberry/ --host=armv7l-unknown-linux-gnueabihf CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ && \
  make -j`nproc` && \
  make install && \
  rm -fR /root/mongo-c-driver-1.9.2 && \
  rm -f /root/mongo-c-driver-1.9.2.tar.gz && \
  cd /root && \
  git clone https://github.com/mongodb/mongo-cxx-driver.git && \
  cd /root/mongo-cxx-driver/build && \
  cmake -DCMAKE_SYSTEM_PROCESSOR=armv7l -DCMAKE_C_COMPILER=arm-linux-gnueabihf-gcc -DCMAKE_CXX_COMPILER=arm-linux-gnueabihf-g++ -DCMAKE_INSTALL_PREFIX=/root/raspberry/ -DCMAKE_PREFIX_PATH=/root/raspberry/ .. && \
  make -j`nproc` && \
  make install && \
  rm -fR /root/mongo-cxx-driver

COPY PiHttp2Server /root/raspberry/PiHttp2Server

RUN cd /root/raspberry/PiHttp2Server && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make -j`nproc` && \
  cp Http2Server /root/raspberry/bin && \
  rm -fR /root/raspberry/PiHttp2Server
