# RibbonDF
[English](README_EN.md)

## 简介
**RibbonDF** 是一款**嵌入式应用**开发框架，基于 [RibbonBuild](https://github.com/RibbonDFTeam/RibbonBuild)实现。`RibbonBuild`是一个组件化编译框架，`RibbonDF`在此基础上实现内部组件，引入三方开源组件，集成调试、单元测试、代码覆盖率统计、内存泄漏检测、系统性能验证等工具，搭建一站式**嵌入式应用**开发框架。

## 目标
**RibbonDF**的目标是解决嵌入式开发过程中的以下问题：
1. 不同产品、不同项目代码重复开发，代码复用率低。
   - 频繁造轮子，造成人力资源浪费。
   - 代码缺少覆盖验证，代码质量差。
   - 公共组件缺少仓库化、版本化管理。
2. 缺少开源组件引入框架
   - 无法快速引入开源组件，或进行组件升级
3. 缺少工具沉淀，缺少提升开发效率手段。
   - 缺少单元测试、代码覆盖率统计，缺少代码质量提升手段。
   - 缺少内存泄漏检测、系统性能验证工具，缺少软件验证手段。

## 实现
1.  适配`git` submodule，引入三方开源组件，通过`Kconfig`配置，实现开源组件灵活配置、编译。
2.  支持`clang-format`、`clang-tidy`，实现代码格式化、代码检查、代码静态分析等。
3. 集成`valgrind`工具进行内存泄漏、系统性能验证。
4.搭建单元测试框架，集成单元测试工具`gtest`，简化系统级单元测试开发难度。
5. 集成`gcov`, `lcov`工具，实现代码覆盖率统计。

## 快速上手
- 下载源码：
  ```
  git clone https://github.com/RibbonDFTeam/RibbonDF.git
  ```
- 更新子模块：
   ```
   git submodule update --init
   ```
> `RibbonBuild`模块为必选模块。`--recursive`可视情况添加。

- 编译
    依赖`python3.8`以上版本
    ```
    sh build.sh ${project_name}
    ```
    具体编译过程可查看build.sh脚本内容。
- 配置
    ```
    sh build.sh ${project_name} menuconfig
    ```

   ## 架构说明

   ### 目录结构
```
RibbonDF
├── components
│   ├── rblog
│   ├── uint_test
│   └──...
├── project
│   ├── test
│   │   ├── src
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   └──...
│   └──...
├── third_lib
│   ├── cJSON
│   │   ├── cJSON(git repo)
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   └──...
│   └──...
├── tools
│   ├── protoc
│   ├── lcov
│   └── ...
├── build.sh
├── LICENSE
├── README.md
├── README_EN.md
```

RibbonDF的目录按功能划分如下：
- 组件目录：存放`RibbonDF`组件。包括`components`，`third_lib`，`project/${project_name}/src`三类，具体说明见组件一节。
- 项目目录：`project/${project_name}`：存放RibbonDF项目。
- 工具目录：`tools`：存放工具工具。
- 文档目录：`docs`，存放系统相关文档。
   ### 项目
   **项目目录结构如下:**
   ```
   project
   ├── projectA_name
   │   ├── src
   │   │   ├── project_componentA
   │   │   ├── project_componentB
   │   │   └──...
   │   ├── build
   │   ├── install
   │   ├── config
   │   ├── CMakeLists.txt
   │   └──...
   ├── projectB_name
   │   ├── src
   │   │   ├── project_componentC
   │   │   ├── project_componentD
   │   │   └──...
   │   ├── build
   │   ├── install
   │   ├── config
   │   ├── CMakeLists.txt
   │   └──...  ```
   - `src`目录存放项目组件。
   - `build`目录存放cmake编译生成的中间文件。
   - `install`目录存放make install生成的成果物文件。
   - `config`目录存放生成的配置文件。
   - `CMakeLists.txt`, 项目编译入口文件。
   - `Kconfig`项目全局配置文件，配置项对所有组件生效。

### 组件
 1. `RibbonDF`的组件分为三类：
   - 三方组件：三方组件是指`RibbonDF`框架体系外的公共组件，如`cJSON`组件。此类组件通常拥有独立的仓库，可通过子仓库方式引入。
   - 标准组件：标准组件是在`RibbonDF`框架中供不同项目公用的组件。如`rblog`组件，为`RibbonDF`提供统一的日志接口。
   - 项目组件：项目组件是指项目内使用的组件，在组件功能不能抽象成标准组件时使用。项目组件存放于项目`src`目录下。

   #### 标准组件
   标准组件存放在`components`目录下，每个组件都有自己的目录，目录名即为组件名。

   **目录结构如下:**
   ```
   componentA
   ├── src
   │   ├── component_code.c
   │   └──...
   │   ├── CMakeLists.txt
   │   ├── Kconfig
   │   └──...
   ```
   - `src`目录存放组件的源码。
   - `CMakeLists.txt`文件存放构建信息，用于描述组件的编译依赖关系。
   - `Kconfig`文件用于组件配置，通过menuconfig命令进行配置。在RibbonDFConfig.cmake文件中生成配置信息，可影响cmake构建过程。

   #### 项目组件
   项目组件存放在项目`src`目录下，其构成与一般组件基本一致。

   #### 三方组件
   三方组件存放在`third_lib`目录下，每个组件都有自己的目录，目录名即为组件名。

   **目录结构如下:**
   ```
   third_lib
   ├── componentB
   │   ├── componentB(git repo)
   │   ├── CMakeLists.txt
   │   ├── Kconfig
   │   └──...
   ```
   - `componentB(git repo)`目录存放组件的源码,对于三方组件，一般为git submodule，其地址存放在.gitmodules中。
   - `CMakeLists.txt`文件存放构建信息，用于描述组件的编译依赖关系。
   - 三方组件的编译方式需要根据三方组件的情况决定。建议详细了解其编译方式后，编写`CMakeLists.txt`文件。

   #### tools目录
   存放工具工具，如`protoc`、`lcov`等。

---
请开启你的`RibbonDF`之旅吧！