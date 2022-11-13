FROM ubuntu:20.04

RUN apt update -y
RUN apt install -y gcc
RUN apt install -y g++
RUN apt install -y gcc-10 g++-10 cpp-10
RUN apt install -y cmake
RUN apt install -y git
RUN apt install -y libssl-dev
RUN apt install -y libgtest-dev
WORKDIR "/usr/src/googletest/googletest"
RUN mkdir build
WORKDIR "/usr/src/googletest/googletest/build"
RUN cmake ..
RUN make
RUN cp ./lib/libgtest* /usr/lib/
RUN mkdir /usr/local/lib/googletest
RUN ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
RUN ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a

WORKDIR "/home"
RUN git clone https://github.com/jbeder/yaml-cpp.git
RUN mkdir yaml-cpp/build
WORKDIR "/home/yaml-cpp/build"
RUN cmake ..
RUN make
RUN make install

WORKDIR "/home"
RUN apt install -y libpqxx-dev

RUN apt install -y libboost-all-dev

RUN apt install -y libjsoncpp-dev

RUN git clone https://github.com/arun11299/cpp-jwt.git
WORKDIR "/home/cpp-jwt"
RUN mkdir build
WORKDIR "/home/cpp-jwt/build"
RUN cmake ..
RUN make install

