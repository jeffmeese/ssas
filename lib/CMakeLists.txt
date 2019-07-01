cmake_minimum_required(VERSION 2.8)

project(ssas CXX)

# Just build qtep as a static library
set(QTEP_BUILD_SHARED OFF CACHE BOOL "")

add_subdirectory(qtep)


