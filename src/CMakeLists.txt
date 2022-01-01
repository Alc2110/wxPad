cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(wxPad_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (DEFINED ENV_WX_CONFIG)
    set (ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

# using static linking with wxWidgets
set(wxWidgets_USE_STATIC 1)

find_package(wxWidgets REQUIRED)

set(SRC_MAIN main.cpp)

# make sure compiler knows where to look for wxWidgets include directories
# this variable is set by find_package script
include(${wxWidgets_USE_FILE})

file(GLOB MAIN_SOURCES "*.cpp")

if (APPLE)
    # create bundle on apple compiles
    add_executable(main MACOSX_BUNDLE ${SRC_MAIN} ${MAIN_SOURCES})
    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties(main PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # set WIN32 to ensure it finds WinMain
    add_executable(main WIN32 ${SRC_MAIN} ${MAIN_SOURCES})
endif()

# make sure linker knows where to look for wxWidgets libraries
# this variable is set by find_package script
target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})