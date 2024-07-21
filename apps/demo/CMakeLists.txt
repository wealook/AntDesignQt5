
project(demo LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 COMPONENTS Core Gui Widgets Xml Svg REQUIRED)
include_directories(
        ../../modules/CommonUtils
        ../../modules/AntDesignQt5/include
        ../../3rdparty/magic_enum
        ${CMAKE_BINARY_DIR}/modules/AntDesignQt5
)
file(GLOB_RECURSE DEMO_HEADER_FILES "Demo*.h*")
file(GLOB_RECURSE DEMO_SOURCE_FILES "Demo*.c*")
add_executable(${PROJECT_NAME}
        main.cpp
        mainwindow.ui
        mainwindow.h
        mainwindow.cpp
        ${DEMO_HEADER_FILES}
        ${DEMO_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        CommonUtils
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Svg
        spdlog::spdlog
        AntDesignQt5
        ${SYSTEM_LIBS}
)

if (MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "demo")
    target_link_options(${PROJECT_NAME} PUBLIC /DEBUG)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
endif ()

if (MSVC)
    set(CMAKE_CXX_FLAGS "/utf-8")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
endif ()