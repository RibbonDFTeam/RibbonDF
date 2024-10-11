set(CUSTOM_CMAKE_C_FLAGS "")
set(CUSTOM_CMAKE_CXX_FLAGS "")

set(JSONCPP_WITH_TESTS CACHE BOOL "Build the JsonCpp tests" OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST CACHE BOOL "Run the JsonCpp unit tests after building" OFF)

add_subdirectory(jsoncpp)
