# 添加源文件
list(APPEND SRC_DIRS ${CMAKE_CURRENT_LIST_DIR}/src)

# 添加PUBLIC头文件
# list(APPEND PUBLIC_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加INTERFACE头文件
# list(APPEND INTERFACE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加PRIVATE头文件
list(APPEND PRIVATE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加库依赖
if(CONFIG_MODULE_GTEST_ENABLE)
    list(APPEND DEPEND_COMPONENTS
        gtest
        )
endif()

# 添加成果库依赖
# list(APPEND DEPEND_LIBS
# pthread)

# 添加C编译选项
set(CUSTOM_CMAKE_C_FLAGS "")

# 添加C++编译选项
set(CUSTOM_CMAKE_CXX_FLAGS "")

# 添加链接选项
set(CUSTOM_CMAKE_EXE_LINKER_FLAGS "")

# 添加自定义defines
list(APPEND CUSTOM_DEFINES "")

if(CONFIG_MODULE_RBLOG_ENABLE)
list(APPEND SRC_DIRS ${CMAKE_CURRENT_LIST_DIR}/src/rblog)
list(APPEND PRIVATE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/rblog)
list(APPEND DEPEND_COMPONENTS rblog)
endif()

RibbonDF_build_application()
add_test(NAME UnitTest COMMAND ${target_name})
