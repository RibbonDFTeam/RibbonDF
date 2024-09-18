#~/bin/bash

mkdir -p build
cd build
cmake ..
make menuconfig
cmake ..
make -j4 install
cd - > /dev/null