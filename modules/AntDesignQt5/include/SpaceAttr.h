#pragma once

#include "GeneralAttr.h"
#include <variant>

namespace wl {

    enum class SpaceAttrDirection {
        vertical,
        horizontal
    };

    class SpaceAttr {
    public:
        std::variant<GeneralAttrSize, uint16_t> size = GeneralAttrSize::middle;
        SpaceAttrDirection direction = SpaceAttrDirection::horizontal;
    };
}