# RibbonDF
[English](README_EN.md)

**RibbonDF** 是一款**嵌入式应用**开发框架。目标是解决嵌入式开发过程中的以下问题：
1. 不同产品、不同项目代码重复开发，代码复用率低。
   - 频繁造轮子，造成人力资源浪费。
   - 代码缺少覆盖验证，代码质量差。
   - 公共组件缺少仓库化、版本化管理。
2. 缺少开源组件引入框架
   - 无法快速引入开源组件，或进行组件升级
3. 缺少工具沉淀，缺少提升开发效率手段。
   - 缺少单元测试、代码覆盖率统计，缺少代码质量提升手段。
   - 缺少内存泄漏检测、系统性能验证工具，缺少软件验证手段。

## 设计理念
1. 采用代码组件化方法，解决代码复用率低问题。
   - 采用`cmake`构建系统，提供快速构造组件，链接组件能力。使得开发者可以快速组合组件，构建自己的应用。
   - 采用`Kconfig`配置系统，解决组件配置问题。支持项目维度，组件维度配置，实现组件的通用化，以及项目的差异化配置。Kconfig语法参考：[<kconfig-language.txt>](https://www.kernel.org/doc/Documentation/kbuild/kconfig-language.txt?spm=a2c4g.11186623.2.2.65b57ecfdlKcCf&file=kconfig-language.txt)
   - 组件代码最大化复用，即保证了代码的测试性，又节省了人力资源。
2.  适配`git` submodule，支持开源组件引入，`Kconfig`配置，实现开源组件的快速导入，和灵活配置。
3.  集成常用优化工具，如代码格式化、代码检查、代码静态分析等。
   - 集成`valgrind`工具进行内存泄漏、系统性能验证。
   - 搭建单元测试框架，集成单元测试工具gtest，简化系统级单元测试开发难度。
   - 集成`gcov`, `lcov`工具，实现代码覆盖率统计。

## 快速上手
- 下载源码：
  ```
  git clone https://github.com/Ribbon-Foundation/RibbonDF.git
  ```
- 更新子模块：
  ```
  git submodule update --init
  ```
    > `--recursive`可视情况添加，默认情况可不添加。

- 编译
    依赖`python3.8`以上版本
    ```
    sh build.sh example
    ```
    具体编译过程可查看build.sh脚本内容。
- 运行
  ```
  ./project/example/install/bin/main_debug
   RibbonDF system name: Linux
   RibbonDF version: V1.0.0
  ```

   ## 架构说明

   ### 目录结构
```
RibbonDF
├── components
│   ├── example_component
│   ├── example_app
│   └──...
├── project
│   ├── example
│   │   ├── src
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   └──...
│   └──...
├── third_lib
│   ├── third_lib_component
│   │   ├── third_lib_src
│   │   ├── CMakeLists.txt
│   │   ├── Kconfig
│   │   └──...
│   └──...
├── tools
│   ├── protoc
│   ├── lcov
│   └── ...
├── build.sh
├── Kconfig
├── LICENSE
├── README.md
├── README_ZH.md
```

RibbonDF的目录按功能划分如下：
- 组件目录：存放RibbonDF组件。包括`components`，`third_lib`，`project/${project_name}/src`三类，具体说明见组件一节。
- 项目目录：`project/${project_name}`：存放RibbonDF项目。
- 工具目录：`tools`：存放工具工具。
- 文档目录：`docs`，存放系统相关文档。
   ### 项目
   **项目目录结构如下:**
   ```
   project
   ├── example
   │   ├── src
   │   │   ├── project_component1
   │   │   ├── project_component2
   │   │   └──...
   │   ├── build
   │   ├── install
   │   ├── config
   │   ├── CMakeLists.txt
   │   └──...
   ├── Kconfig
   │   └──...
   ```
   - `src`目录存放项目组件。
   - `build`目录存放cmake编译生成的中间文件。
   - `install`目录存放make install生成的成果物文件。
   - `config`目录存放生成的配置文件。
   - `CMakeLists.txt`, 项目编译入口文件。
   - `Kconfig`项目全局配置文件，配置项对所有组件生效。

   ### 组件
   #### 组件分类
 1. `RibbonDF`的组件从功能上分为两类：
      - 库组件：分为动态库组件和静态库组件，参考`example_component`。
      - 应用组件：参考`example_app`。

      组件从作用域上分外三类：

   >- 三方组件：三方组件是指`RibbonDF`框架体系外的公共组件，如`cJSON`组件。此类组件通常拥有独立的仓库，可通过子仓库方式引入。
   >- 标准组件：标准组件是在`RibbonDF`框架中，可供不同项目公用的组件。如`rblog`组件，为`RibbonDF`提供统一的日志接口。
   >- 项目组件：项目组件是指项目内使用的组件，在组件功能不能抽象成标准组件时使用。项目组件存放于项目`src`目录下。

   #### 标准组件
   标准组件存放在`components`目录下，每个组件都有自己的目录，目录名即为组件名：
   **组件目录结构如下:**
   ```
   example_component
   ├── src
   │   ├── example_component.c
   │   └──...
   │   ├── CMakeLists.txt
   │   ├── Kconfig
   │   └──...
   ```
   - `src`目录存放组件的源码。
   - `CMakeLists.txt`文件存放构建信息，用于描述组件的编译依赖关系。
   - `Kconfig`文件用于组件配置，通过menuconfig命令进行配置。在RibbonDFConfig.cmake文件中生成配置信息，可影响cmake构建过程。

   1. **CMakeLists.txt文件说明**
      - SRC_DIRS：存放组件源码的目录。
      - PUBLIC_HEADERS: 存放组件公开头文件目录。
      - INTERFACE_HEADERS: 存放组件接口头文件目录。
      - PRIVATE_HEADERS: 存放组件私有头文件目录。
      - SOURCES: 存放组件源码文件。
      - DEPEND_COMPONENTS: 组件依赖的组件。
      - DEPEND_LIBS: 组件依赖的在系统中安装的库。
      - CUSTOM_CMAKE_C_FLAGS：组件自定义的C编译选项。
      - CUSTOM_CMAKE_CXX_FLAGS：组件自定义的C++编译选项。
      - CUSTOM_CMAKE_EXE_LINKER_FLAGS：组件自定义的链接选项。
      - CUSTOM_DEFINES：组件自定义的宏定义。
      - RibbonBuildComponent
        - 库组件编译命令，参数可选`STATIC`，`DYNAMIC`。不填则默认为`STATIC`。
      - RibbonBuildApplication
        - 应用组件编译命令
   2. **Kconfig文件说明**
      - 组件使能项配置（必填项）：`MODULE_${COMPONENT_NAME}_ENABLE`
        - COMPONENT_NAME：组件名称，与组件目录名称相同，全大写
      - 组件内其他配置填写规则遵循Kconfig语法。

   #### 项目组件
   项目组件存放在项目`src`目录下，其构成与一般组件基本一致。

   #### 三方组件
   三方组件存放在`third_lib`目录下，每个组件都有自己的目录，目录名即为组件名。

   **组件目录结构如下:**
   ```
   third_lib
   ├── third_lib_component1
   │   ├── third_lib_src
   │   ├── CMakeLists.txt
   │   ├── Kconfig
   │   └──...
   ```
   - `third_lib_src`目录存放组件的源码,对于三方组件，一般为git submodule，其地址存放在.gitmodules中。
   - `CMakeLists.txt`文件存放构建信息，用于描述组件的编译依赖关系。
   - 三方组件的编译方式需要根据三方组件的情况决定。建议详细了解其编译方式后，编写`CMakeLists.txt`文件。

   #### tools目录
   存放工具工具，如`protoc`、`lcov`等。

---
请开启你的`RibbonDF`之旅吧！