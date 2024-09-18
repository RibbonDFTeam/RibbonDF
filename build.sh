#!/bin/bash

ProjectName=$1

if [ -z "$ProjectName" ]; then
    echo "Please input ProjectName"
    echo "Usage:sh build.sh ProjectName"
    exit 1
fi

if [ ! -d "project/$ProjectName" ]; then
    echo "Project $ProjectName not exists"
    exit 1
fi

cd project/$ProjectName
sh build.sh