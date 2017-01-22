#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR

if [[ -e $DIR/../app/externals/wxWidgets-3.1.0/install_dir/bin/wx-config ]]
then
    echo '-- wxWidgets are installed'
    exit 0
fi

echo '-- Installing wxWidgets 3.1.0'
cd ../app/externals && tar -xvf wxWidgets-3.1.0.tar.bz2 && cd wxWidgets-3.1.0 && \
mkdir -p build_dir && mkdir -p install_dir && cd build_dir && \
../configure --prefix=$DIR/../app/externals/wxWidgets-3.1.0/install_dir \
--enable-stl --enable-cxx11 --disable-sys-libs --disable-shared && \
make && make install

