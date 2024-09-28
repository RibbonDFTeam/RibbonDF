cmake_minimum_required(VERSION 3.10.0)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RibbonBuildPath "${PROJECT_SOURCE_DIR}/../../RibbonBuild")
set(RibbonComponentsPath
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/../../components"
    "${PROJECT_SOURCE_DIR}/../../third_lib")

include(${RibbonBuildPath}/RibbonBuild.cmake)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX)

RibbonBuild()
