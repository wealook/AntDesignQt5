cmake_minimum_required(VERSION 3.5)
project(AntDesignQt5)
include(cmake/predefines.cmake)

option(BUILD_APP "" OFF)
# 修改为本机QT5路径
set(Qt5_DIR "D:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5")
if (MSVC)
    set(CMAKE_CXX_FLAGS "/utf-8")
    set(CMAKE_C_FLAGS "/utf-8")
endif ()
add_subdirectory(3rdparty)
add_subdirectory(modules)

if (BUILD_APP)
    add_subdirectory(apps)
endif ()
