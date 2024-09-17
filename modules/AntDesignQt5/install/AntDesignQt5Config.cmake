get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if (_IMPORT_PREFIX STREQUAL "/")
    set(_IMPORT_PREFIX "")
endif ()
set(target_name "AntDesignQt5:AntDesignQt5")
add_library(${target_name} SHARED IMPORTED)
if (MSVC)
    set_target_properties(${target_name} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
            IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/check_commd.lib"
            IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/check_comm.lib"
            IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/check_commd.dll"
            IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/check_comm.dll"
    )
endif ()
if (MINGW_WIN32)
    set_target_properties(${target_name} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
            IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libcheck_commd.dll.a"
            IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libcheck_comm.dll.a"
            IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libcheck_commd.dll"
            IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libcheck_comm.dll"
    )
endif ()
