#!/bin/bash

# 获取当前脚本文件的绝对路径
SCRIPT_DIR=$(dirname $(realpath "$0"))

# 输出当前脚本文件所在的目录
echo "Script directory: $SCRIPT_DIR"

#输入的第一个参数为Project name
Project_name=$1
#如何没有输入参数，则报错退出
if [ -z "$Project_name" ]; then
    echo "Please input Project name"
    exit 1
fi
echo "Project_name: $Project_name"


RibbonDF_dir=$(realpath "$SCRIPT_DIR/../..")
echo "RibbonDF_dir: $RibbonDF_dir"

BuildPath=$RibbonDF_dir/project/$Project_name/build

# lcov --directory $BuildPath --zerocounters

# 使用 lcov 工具生成代码覆盖率报告
# 参数说明：
# -c: 捕获覆盖率数据
# -d $BuildPath: 指定构建目录
# -o $BuildPath/code_coverage.info: 指定输出文件路径
# --rc lcov_branch_coverage=1: 启用分支覆盖率统计
lcov -c -d $BuildPath  -o $BuildPath/code_coverage.info --rc lcov_branch_coverage=1
lcov --extract $BuildPath/code_coverage.info "*/RibbonDF/*" -o $BuildPath/extracted_code_coverage.info
genhtml $BuildPath/extracted_code_coverage.info -o $BuildPath/code_coverage_report
