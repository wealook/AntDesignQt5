#pragma once

#include <optional>

namespace wl {


    enum class GeneralAttrSize {
        small,
        middle,
        large,
    };
    enum class GeneralAttrShape {
        none,
        circle,
        round
    };
    enum class GeneralAttrColorType {
        none,
        secondary,
        success,
        warning,
        danger,
    };

    class GeneralAttr {
    public:
        GeneralAttrSize size = GeneralAttrSize::middle;
        GeneralAttrShape shape = GeneralAttrShape::none;
    };


}


