# 添加源文件
list(APPEND SRC_DIRS ${CMAKE_CURRENT_LIST_DIR}/src)

# 添加PUBLIC头文件
# list(APPEND PUBLIC_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加INTERFACE头文件
# list(APPEND INTERFACE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加PRIVATE头文件
list(APPEND PRIVATE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加库依赖
# list(APPEND DEPEND_COMPONENTS
# cJSON
# )

# 添加成果库依赖
# list(APPEND DEPEND_LIBS
# gcov
# )

# 添加C编译选项
set(CUSTOM_CMAKE_C_FLAGS "")

# 添加C++编译选项
set(CUSTOM_CMAKE_CXX_FLAGS "")

# 添加链接选项
if(CONFIG_LIBC_SUBSTITUTE_WRAP)
    set(CUSTOM_CMAKE_EXE_LINKER_FLAGS "-Wl,--wrap=malloc -Wl,--wrap=free")
endif()

# 添加自定义defines
set(CUSTOM_DEFINES "")

RibbonBuildApplication()
