cmake_minimum_required(VERSION 3.8)

project(third_party)

add_subdirectory(dxflib)

set(CXXOPTS_BUILD_EXAMPLES OFF CACHE BOOL "CXX Build Examples" FORCE)
set(CXXOPTS_BUILD_TESTS OFF CACHE BOOL "CXX Build Tests" FORCE)
add_subdirectory(cxxopts)

