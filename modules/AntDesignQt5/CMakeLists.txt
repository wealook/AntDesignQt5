set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
option(BUILD_DYNAMIC_LIB "" OFF)

file(GLOB_RECURSE SVG_LIST "icon-svg/*.svg")
foreach (svg_file ${SVG_LIST})
    get_filename_component(var_path ${svg_file} NAME_WLE)
    list(APPEND ICON_SVG_LIST_ "${var_path}")
endforeach ()
string(JOIN "," ICON_SVG_LIST ${ICON_SVG_LIST_})
#message(${ICON_SVG_LIST})

configure_file(./IconSvg.h.in ${CMAKE_CURRENT_BINARY_DIR}/IconSvg.h)

include_directories(
        ./include
        ../CommonUtils
        ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
find_package(Qt5 COMPONENTS Core Gui Widgets Xml Svg REQUIRED)

if (BUILD_DYNAMIC_LIB)
    add_library(AntDesignQt5 SHARED ${HEADER_FILES} ${SOURCE_FILES})
else ()
    add_library(AntDesignQt5 STATIC ${HEADER_FILES} ${SOURCE_FILES})
endif ()

target_link_libraries(AntDesignQt5 PRIVATE
        CommonUtils
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Svg
        ${SYSTEM_LIBS}
)

install(
        TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/bin
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/bin
)


file(GLOB_RECURSE _SDK_FILES "include/*")
file(GLOB_RECURSE _SVG_FILES "icon-svg/*")
install(
        FILES
        ${_SDK_FILES}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/include
)
install(
        FILES
        ${_SVG_FILES}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/icon-svg
)
install(
        FILES
        install/AntDesignQt5Config.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/lib/cmake/${PROJECT_NAME}
)
