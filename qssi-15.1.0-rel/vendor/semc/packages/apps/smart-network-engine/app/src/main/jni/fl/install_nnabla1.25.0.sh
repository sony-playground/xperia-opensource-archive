#!/bin/bash
DEPENDENCY_PATH=$1    #/home/jimbo/sample/dependency/
DOWNLOAD_PATH=$2      #/home/jimbo/sample/download/
mkdir -p ${DEPENDENCY_PATH}
mkdir -p ${DOWNLOAD_PATH}
wget -P ${DOWNLOAD_PATH} https://github.com/sony/nnabla/archive/refs/tags/v1.25.0.zip
unzip ${DOWNLOAD_PATH}v1.25.0.zip -d ${DOWNLOAD_PATH}

cd ${DOWNLOAD_PATH}nnabla-1.25.0
mkdir -p build && cd build
cmake .. -DBUILD_CPP_UTILS=ON -DBUILD_PYTHON_PACKAGE=OFF -DNNABLA_UTILS_WITH_HDF5=ON -DCMAKE_PREFIX_PATH=${DEPENDENCY_PATH} -DCMAKE_INSTALL_PREFIX=${DEPENDENCY_PATH}
make
sudo make install