cmake_minimum_required(VERSION 2.8)

project(ssas CXX)
set(TARGET_NAME ssas_gui)

# Set policies
cmake_policy(SET CMP0020 NEW)

# Find OpenGL
find_package(OpenGL COMPONENTS OpenGL REQUIRED)

# Find Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Find VTK and automatically initialize modules
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(SRC_FILES
  application.cpp
  main.cpp
  mainwindow.cpp
  surfaceitem.cpp
  surfaceviewitem.cpp
  view.cpp
  viewitem.cpp
  viewmodel.cpp
  workspacemodel.cpp
  workspacemodelitem.cpp
)

set(HDR_FILES
  application.h
  mainwindow.h
  surfaceitem.h
  surfaceviewitem.h
  view.h
  viewitem.h
  viewmodel.h
  workspacemodel.h
  workspacemodelitem.h
)

set(UI_FILES
  mainwindow.ui
)

add_executable(${TARGET_NAME} ${SRC_FILES} ${HDR_FILES} ${UI_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${VTK_INCLUDE_DIRS})

target_link_libraries(${TARGET_NAME} ssas)
target_link_libraries(${TARGET_NAME} Qt5::Core)
target_link_libraries(${TARGET_NAME} Qt5::Gui)
target_link_libraries(${TARGET_NAME} Qt5::Widgets)
target_link_libraries(${TARGET_NAME} OpenGL::GL)
target_link_libraries(${TARGET_NAME} OpenGL::GLU)
target_link_libraries(${TARGET_NAME} ${VTK_LIBRARIES})
