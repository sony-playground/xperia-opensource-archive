#!/bin/bash
DEPENDENCY_PATH=$1    #/home/jimbo/sample/dependency/
DOWNLOAD_PATH=$2      #/home/jimbo/sample/download/
mkdir -p ${DEPENDENCY_PATH}
mkdir -p ${DOWNLOAD_PATH}
wget -P ${DOWNLOAD_PATH} https://github.com/google/protobuf/archive/v3.1.0.tar.gz
tar xvf ${DOWNLOAD_PATH}v3.1.0.tar.gz -C ${DOWNLOAD_PATH}

cd ${DOWNLOAD_PATH}protobuf-3.1.0
mkdir build && cd build
cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON -Dprotobuf_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_PATH} ../cmake
make
make install