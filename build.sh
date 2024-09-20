#!/bin/bash

project_name=$1
menuconfig=$2

if [ -z "$project_name" ]; then
    echo "Please input project_name"
    echo "Usage:sh build.sh project_name [menuconfig]"
    exit 1
fi

if [ ! -d "project/$project_name" ]; then
    echo "Project $project_name not exists"
    exit 1
fi

do_build()
{
    cd project/$project_name

    if [ ! -d "build" ]; then
        mkdir build
    fi

    cd build
    cmake ..
    make -j4 install
    cd - > /dev/null
}

do_menuconfig()
{
    cd project/$project_name
    if [ ! -d "build" ]; then
        echo "Please build project first"
        exit 1
    fi

    cd build
    make menuconfig
    cd - > /dev/null
}


if [ -z "$menuconfig" ]; then
    do_build
    echo "Build $project_name success"
else
    echo "do Menuconfig"
    do_menuconfig
fi

