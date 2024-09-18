
set(CMAKE_CXX_FLAGS "-std=c++14")
message(STATUS "CMAKE_CXX_FLAGS:${CMAKE_CXX_FLAGS}")

function(RibbonDF_build_component)
    set(component_dynamic "STATIC")

    if(ARGN)
        list(GET ARGN 0 component_dynamic)
    endif()

    if(${component_dynamic} STREQUAL "DYNAMIC")
        set(LIBRARY_TYPE SHARED)
    else()
        set(LIBRARY_TYPE STATIC)
    endif()

    message(STATUS "LIBRARY_TYPE:${LIBRARY_TYPE}")
endfunction()

RibbonDF_build_component(DYNAMIC)

# RibbonDF_build_component()
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(test_lib ${SRC})
target_include_directories(test_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 测试目标

# 2. 头文件包含