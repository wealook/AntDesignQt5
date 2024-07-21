add_definitions(-DNOT_REQUIRED_OPENCV_MD)
#find_package(PaddleInferenceMKL REQUIRED)
include_directories(
        .
)

list(APPEND COMMON_UTILS_SOURCEFILES
        sys_utils.h
        sys_utils.cpp
        logger.h
        logger.cpp
        string_helper.h
        string_helper.cpp
)


if (MACOSX)
    list(APPEND COMMON_UTILS_SOURCEFILES SysUtils.mm)
else ()
    list(APPEND COMMON_UTILS_SOURCEFILES sys_utils.cpp)
endif ()

include(CheckIncludeFileCXX)
if (ARMLINUX)
    CHECK_INCLUDE_FILE_CXX(X11 HAVE_X11)
    if (HAVE_X11)
        add_definitions(-DHAVE_X11)
    endif (HAVE_X11)
endif ()
CHECK_INCLUDE_FILE_CXX(codecvt HAVE_CODECVT)
if (HAVE_CODECVT)
    add_definitions(-DHAVE_CODECVT)
endif ()

add_library(CommonUtils STATIC ${COMMON_UTILS_SOURCEFILES})
target_link_libraries(CommonUtils
        PRIVATE
        spdlog::spdlog
        ${SYSTEM_LIBS}

)
set_target_properties(CommonUtils PROPERTIES FOLDER "common")
