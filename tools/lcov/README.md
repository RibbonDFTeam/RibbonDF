# 代码覆盖率统计方法

1. 工程开启gcov选项，编译生成.gcno文件
2. 运行测试用例或可执行程序，生成.gcda文件
3. 执行sh code_coverity_summury.sh命令，生成覆盖率HTML报告
4. 打开HTML报告，查看覆盖率统计结果