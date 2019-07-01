cmake_minimum_required(VERSION 2.8)

project(ssas CXX)

# Define options
option(SSAS_BUILD_SHARED "Set to ON to build as a shared library" ON)

# Set policies
cmake_policy(SET CMP0020 NEW)

# Set target name
set(TARGET_NAME ssas)

# Set build type
set(BUILD_TYPE STATIC)
if (SSAS_BUILD_SHARED)
  set(BUILD_TYPE SHARED)
endif()

# Find Qtep
set(QTEP_LIBS qtep)

# Find Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Source files
set(SRC_FILES
  core/edge.cpp
  core/element.cpp
  core/model.cpp
  core/node.cpp
  core/surface.cpp
  core/treatment.cpp
  core/triangle.cpp
)

# Header files
set(HDR_FILES
  ssas.h
  core/edge.h
  core/element.h
  core/model.h
  core/node.h
  core/surface.h
  core/treatment.h
  core/triangle.h
)

# Create target
add_library(${TARGET_NAME} ${BUILD_TYPE} ${SRC_FILES} ${HDR_FILES})

# Set target compile options and definitions
if (SSAS_BUILD_SHARED)
  target_compile_definitions(${TARGET_NAME} PRIVATE -DSSAS_COMPILE_LIBRARY)
endif()

target_compile_definitions(${TARGET_NAME} PUBLIC -DQTEP_USE_LIBRARY)

# Specify target include directories
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)

# Specify target link libraries
target_link_libraries(${TARGET_NAME} ${QTEP_LIBS})
#target_link_libraries(${TARGET_NAME} Qt5::Core)
#target_link_libraries(${TARGET_NAME} Qt5::Gui)
#target_link_libraries(${TARGET_NAME} Qt5::Widgets)
