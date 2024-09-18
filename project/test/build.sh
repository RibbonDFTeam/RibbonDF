#~/bin/bash

mkdir -p build
cd build
cmake ..
make menuconfig
make -j4 install
cd - > /dev/null