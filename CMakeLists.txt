cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(wxPad LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ExternalProject base
# this is a directory where we will be downloading external projects and placing their sources and build artefacts
set_property(DIRECTORY PROPERTY EP_BASE ${CMAKE_BINARY_DIR}/subprojects)

# this is a directory where we will be installing the downloaded libraries
set(STAGED_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/stage)

# make sure CMake system reads txt files from thirdparty directory
add_subdirectory(thirdparty)

# "src" and "thirdparty" directories are each external projects
include(ExternalProject)
ExternalProject_Add(${PROJECT_NAME}_core
  # make sure the main project depends on the wxWidgets project
  DEPENDS
    wxWidgets_external
  SOURCE_DIR
  # set the source directory for the main project
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    -DCMAKE_CXX_EXTENSIONS=${CMAKE_CXX_EXTENSIONS}
    -DCMAKE_CXX_STANDARD_REQUIRED=${CMAKE_CXX_STANDARD_REQUIRED}
    -DwxWidgets_ROOT_DIR=${wxWidgets_ROOT_DIR}
    -DENV_WX_CONFIG=${ENV_WX_CONFIG}
  CMAKE_CACHE_ARGS
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_PREFIX_PATH:PATH=${CMAKE_PREFIX_PATH}
  BUILD_ALWAYS
    1
  INSTALL_COMMAND
    ""
  )