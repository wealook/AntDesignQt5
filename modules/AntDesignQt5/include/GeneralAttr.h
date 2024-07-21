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

    class GeneralAttr {
    public:
        GeneralAttrSize size = GeneralAttrSize::middle;
        GeneralAttrShape shape = GeneralAttrShape::none;
    };


}


