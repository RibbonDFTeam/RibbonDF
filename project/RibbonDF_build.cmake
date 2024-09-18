set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(RibbonDF_get_component_config component_name config value)
    string(TOUPPER "CONFIG_MODULE_${component_name}_${config}" component_config)
    set(${value} "${${component_config}}" PARENT_SCOPE)

    # message(STATUS "${component_config}=${${component_config}}")
endfunction()

function(RibbonDF_build_targets targets_path_list)
    foreach(target_path ${targets_path_list})
        get_filename_component(target_name ${target_path} NAME_WE)
        RibbonDF_get_component_config(${target_name} ENABLE target_enable)

        if(${target_enable})
            message("Target [${target_name}] enable")
            add_subdirectory(${target_path} "${PROJECT_SOURCE_DIR}/build/${target_name}")
        else()
            message("Target [${target_name}] disabled")
        endif()
    endforeach()
endfunction()

# @brief 在指定路径下查找库
# @param target_path 查找库的路径
# @return
function(RibbonDF_scan_target target_path)
    message("Scan Targets in PATH: ${target_path}")

    # Execute the Python script
    execute_process(
        COMMAND python "${RibbonDF_PATH}/project/RibbonDF_build.py" --search-module ${target_path}
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE python_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    # 将逗号分隔的字符串解析为CMake的列表
    string(REPLACE " " ";" targets_list "${python_output}")

    foreach(target ${targets_list})
        message(STATUS "find target ${target}")
    endforeach(target ${targets_list})

    set(tmp_targets ${targets})
    list(APPEND tmp_targets ${targets_list})
    set(targets ${tmp_targets} PARENT_SCOPE)
endfunction()

function(RibbonDF_python_check)
    find_package(Python 3.8 REQUIRED)

    if(NOT Python_FOUND)
        message(FATAL_ERROR "Python 3.8 or higher is required")
    endif()
endfunction()

function(RibbonDF_dependents_check)
    message("Dependents Check")
    RibbonDF_python_check()
endfunction()

function(RibbonDF_kconfig_generate targets)
    message("Kconfig Generate")
    execute_process(
        COMMAND python "${RibbonDF_PATH}/project/RibbonDF_build.py" --kconfig-reg ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE python_output
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    add_custom_target(menuconfig
        COMMAND python "${RibbonDF_PATH}/project/RibbonDF_build.py" --kconfig-menuconfig ${PROJECT_SOURCE_DIR}
        COMMAND cd "${PROJECT_SOURCE_DIR}/build"
        COMMAND cmake ".."
        COMMENT "execute menuconfig"
    )

    add_custom_target(distclean
        COMMAND python "${RibbonDF_PATH}/project/RibbonDF_build.py" --distclean ${PROJECT_SOURCE_DIR}
        COMMENT "clean kconfig files"
    )
endfunction()

macro(RibbonDF_config_project)
    include(${PROJECT_SOURCE_DIR}/config/RibbonDFConfig.cmake)
    include_directories(${PROJECT_SOURCE_DIR}/config)

    if(${CONFIG_PROJECT_DEBUG})
        set(CMAKE_BUILD_TYPE Debug)
    else()
        set(CMAKE_BUILD_TYPE Release)
    endif()

    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "Install path" FORCE)

    find_program(CMAKE_C_COMPILER "${CONFIG_TOOL_CHAIN_PREFIX}${CONFIG_C_COMPILER}")
    find_program(CMAKE_CXX_COMPILER "${CONFIG_TOOL_CHAIN_PREFIX}${CONFIG_CXX_COMPILER}")

    set(CMAKE_C_FLAGS "${CONFIG_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CONFIG_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CONFIG_LD_FLAGS}")
    add_definitions("${CONFIG_PROJECT_DEFINES}")
    message("Project Config")
    message(STATUS "Project Install Path: ${CMAKE_INSTALL_PREFIX}")
    message(STATUS "Project Build Type: ${CMAKE_BUILD_TYPE}")
    message(STATUS "Project C_COMPILER: ${CMAKE_C_COMPILER}")
    message(STATUS "Project CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
    message(STATUS "Project CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
    message(STATUS "Project CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    message(STATUS "Project CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
    message(STATUS "Project Defines: ${CONFIG_PROJECT_DEFINES}")
    message(STATUS "Project gcov enable: ${CONFIG_PROJECT_GCOV_ENABLE}")
    message(STATUS "Project unit test enable: ${CONFIG_PROJECT_UNIT_TEST_ENABLE}")
endmacro()

function(RibbonDF_do_build)
    # 扫描目标
    set(targets "")

    foreach(target_path ${RibbonDF_TARGETS_PATHS})
        RibbonDF_scan_target(${target_path})
    endforeach(target_path ${RibbonDF_TARGETS_PATHS})

    if(NOT targets)
        message(WARNING "Not find any module in ${target_path}, exit build")
        return()
    endif()

    # kconfig生成
    RibbonDF_kconfig_generate("${targets}")

    # 配置项目
    RibbonDF_config_project()

    # 注册目标
    RibbonDF_build_targets("${targets}")
endfunction()

# @brief 项目构建函数
# @return
function(RibbonDF_build)
    get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

    message("Project: ${PROJECT_NAME} Build Start")

    # 获取当前项目的根目录的绝对路径
    get_filename_component(RibbonDF_PATH "${PROJECT_SOURCE_DIR}/../.." ABSOLUTE)
    message("RibbonDF_PATH: ${RibbonDF_PATH}")

    # 引入TargetBuild.cmake库
    include(${RibbonDF_PATH}/project/TargetBuild.cmake)

    # 设置项目的目标库路径列表
    set(RibbonDF_TARGETS_PATHS "${RibbonDF_PATH}/third_lib" "${RibbonDF_PATH}/components" "${PROJECT_SOURCE_DIR}/src")

    # 依赖检查
    RibbonDF_dependents_check()

    # 构建项目
    RibbonDF_do_build()

    message(STATUS "Project Config done")
endfunction()

RibbonDF_build()
