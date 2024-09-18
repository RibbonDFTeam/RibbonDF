macro(TargetInit)
    set(SRC_DIRS "")
    set(PUBLIC_HEADERS "")
    set(INTERFACE_HEADERS "")
    set(PRIVATE_HEADERS "")

    set(DEPEND_COMPONENTS "")
    set(DEPEND_LIBS "")
    set(CUSTOM_CMAKE_C_FLAGS "")
    set(CUSTOM_CMAKE_CXX_FLAGS "")
    set(CUSTOM_CMAKE_EXE_LINKER_FLAGS "")
    set(CUSTOM_DEFINES "")
endmacro()

macro(enable_gcov)
    # list(APPEND CUSTOM_CMAKE_C_FLAGS "--coverage -fprofile-dir=${RibbonDF_PATH}/project/${PROJECT_NAME}/build/gcov_output")
    list(APPEND CUSTOM_CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage")
    list(APPEND CUSTOM_CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
    list(APPEND DEPEND_LIBS
        gcov
    )
endmacro()

macro(RibbonDF_target_config)
    if(CONFIG_PROJECT_GCOV_ENABLE)
        enable_gcov()
    endif()

    string(REPLACE " " ";" TARGET_CMAKE_C_FLAGS "${CMAKE_C_FLAGS};${CUSTOM_CMAKE_C_FLAGS}")
    string(REPLACE " " ";" TARGET_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS};${CUSTOM_CMAKE_CXX_FLAGS}")
    string(REPLACE " " ";" TARGET_CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS};${CUSTOM_CMAKE_EXE_LINKER_FLAGS}")
    string(REPLACE " " ";" TARGET_DEFINES "${CUSTOM_DEFINES}")

    message(STATUS "TARGET_CMAKE_EXE_LINKER_FLAGS: ${TARGET_CMAKE_EXE_LINKER_FLAGS}")
    message(STATUS "TARGET_CMAKE_C_FLAGS: ${TARGET_CMAKE_C_FLAGS}")
    message(STATUS "TARGET_CMAKE_CXX_FLAGS: ${TARGET_CMAKE_CXX_FLAGS}")
    message(STATUS "TARGET_DEFINES: ${TARGET_DEFINES}")

    foreach(PUBLIC_HEADER ${PUBLIC_HEADERS})
        target_include_directories(${target_name} PUBLIC ${PUBLIC_HEADER})
    endforeach(PUBLIC_HEADER ${PUBLIC_HEADERS})

    message(STATUS "Public Headers: ${PUBLIC_HEADERS}")

    foreach(INTERFACE_HEADER ${INTERFACE_HEADERS})
        target_include_directories(${target_name} INTERFACE ${INTERFACE_HEADER})
    endforeach(INTERFACE_HEADER ${INTERFACE_HEADERS})

    message(STATUS "Interface Headers: ${INTERFACE_HEADERS}")

    foreach(PRIVATE_HEADER ${PRIVATE_HEADERS})
        target_include_directories(${target_name} PRIVATE ${PRIVATE_HEADER})
    endforeach(PRIVATE_HEADER ${PRIVATE_HEADERS})

    message(STATUS "Private Headers: ${PRIVATE_HEADERS}")

    message(STATUS "Sources: ${SRC}")

    foreach(depend_component ${DEPEND_COMPONENTS})
        add_dependencies(${target_name} ${depend_component})
        target_link_libraries(${target_name} PRIVATE ${depend_component})
    endforeach()

    message(STATUS "Depend components: ${DEPEND_COMPONENTS}")

    foreach(depend_lib ${DEPEND_LIBS})
        target_link_libraries(${target_name} PRIVATE ${depend_lib})
    endforeach()

    message(STATUS "Depend librarys: ${DEPEND_LIBS}")

    target_compile_options(${target_name} PRIVATE "${TARGET_CMAKE_C_FLAGS}")
    target_compile_options(${target_name} PRIVATE "${TARGET_CMAKE_CXX_FLAGS}")
    target_link_options(${target_name} PRIVATE "${TARGET_CMAKE_EXE_LINKER_FLAGS}")
    target_compile_definitions(${target_name} PRIVATE ${TARGET_DEFINES})

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set_target_properties(${target_name} PROPERTIES
            OUTPUT_NAME ${target_name}
            DEBUG_POSTFIX "_debug"
        )
    endif()

    install(TARGETS ${target_name}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

    install(DIRECTORY ${PUBLIC_HEADERS} DESTINATION include/${target_name})
    install(DIRECTORY ${INTERFACE_HEADERS} DESTINATION include/${target_name})
endmacro()

function(RibbonDF_build_application)
    get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

    message("Register Application: [${target_name}]")

    set(SRC "")

    foreach(SRC_DIR ${SRC_DIRS})
        aux_source_directory(${SRC_DIR} SRC)
    endforeach(SRC_DIR ${SRC_DIRS})

    add_executable(${target_name} ${SRC})

    set_target_properties(${target_name} PROPERTIES INSTALL_RPATH "../lib")
    set_target_properties(${target_name} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

    RibbonDF_target_config()
endfunction()

function(RibbonDF_build_component)
    get_filename_component(target_name ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)

    message("Register Component: [${target_name}]")

    set(component_dynamic "STATIC")

    if(ARGN)
        list(GET ARGN 0 component_dynamic)
    endif()

    if(${component_dynamic} STREQUAL "DYNAMIC")
        set(LIBRARY_TYPE SHARED)
    else()
        set(LIBRARY_TYPE STATIC)
    endif()

    message(STATUS "LIBRARY_TYPE: ${LIBRARY_TYPE}")

    foreach(SRC_DIR ${SRC_DIRS})
        aux_source_directory(${SRC_DIR} SRC)
    endforeach(SRC_DIR ${SRC_DIRS})

    add_library(${target_name} ${LIBRARY_TYPE} ${SRC})

    RibbonDF_target_config()
endfunction()