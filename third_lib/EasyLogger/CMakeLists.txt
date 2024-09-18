
set(CUSTOM_CMAKE_C_FLAGS "")
set(CUSTOM_CMAKE_CXX_FLAGS "")

# 添加源文件
list(APPEND SRC_DIRS
    ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/easylogger/src
)

# 添加PUBLIC头文件
list(APPEND PUBLIC_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/easylogger/inc
)

# 添加INTERFACE头文件
# list(APPEND INTERFACE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)

# 添加PRIVATE头文件
# list(APPEND PRIVATE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include)
if(CONFIG_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND SRC_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/demo/os/linux/easylogger/port
    )
    list(APPEND PUBLIC_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/demo/os/linux/easylogger/inc
    )
endif()

if(CONFIG_MODULE_EASYLOG_PLUGIN_FILE_ENABLE)
    list(APPEND SRC_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/easylogger/plugins/file)
    list(APPEND PUBLIC_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/easylogger/plugins/file)
endif()

if(CONFIG_MODULE_EASYLOG_PLUGIN_FLASH_ENABLE)
    list(APPEND SRC_DIRS
        ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/easylogger/plugins/flash)
    list(APPEND PUBLIC_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/EasyLogger/easylogger/plugins/flash)
endif()

# 添加库依赖
# list(APPEND DEPEND_COMPONENTS cJSON)

# 添加成果库依赖
list(APPEND DEPEND_LIBS
    pthread)

# 添加C编译选项
set(CUSTOM_CMAKE_C_FLAGS "")

# 添加C++编译选项
set(CUSTOM_CMAKE_CXX_FLAGS "")

# 添加链接选项
set(CUSTOM_CMAKE_EXE_LINKER_FLAGS "")

# 添加自定义defines
set(CUSTOM_DEFINES "")

RibbonBuildComponent()
