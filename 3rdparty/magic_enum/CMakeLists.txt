project(magic_enum LANGUAGES CXX)

LIST(APPEND _SRC_FILES
        magic_enum.hpp
)

# github https://github.com/Neargye/magic_enum/tree/v0.9.5
# 注意枚举范围变大后会影响编译速度，运行速度不受影响
add_library(magic_enum STATIC ${_SRC_FILES})
SET_TARGET_PROPERTIES(magic_enum PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(magic_enum PROPERTIES FOLDER "vendor")
