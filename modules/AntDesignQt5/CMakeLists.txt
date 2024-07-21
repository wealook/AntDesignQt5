set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SVG_LIST "icon-svg/*.svg")
foreach (svg_file ${SVG_LIST})
    get_filename_component(var_path ${svg_file} NAME_WLE)
    list(APPEND ICON_SVG_LIST_ "${var_path}" )
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

add_library(AntDesignQt5 STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(AntDesignQt5 PRIVATE
        CommonUtils
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Xml
        Qt5::Svg
        ${SYSTEM_LIBS}
)