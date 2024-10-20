cmake_minimum_required(VERSION 3.10.0)

set(RibbonBuildPath "${CMAKE_CURRENT_SOURCE_DIR}/../../RibbonBuild")
set(RibbonComponentsPath
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../components"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../third_lib")

include(${RibbonBuildPath}/RibbonBuild.cmake)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C CXX)

RibbonBuild()
