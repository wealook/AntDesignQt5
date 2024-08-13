#pragma once

#include "GeneralAttr.h"

namespace wl {

    class TextAttr {

    public:
        TextAttr() = default;

        explicit TextAttr(GeneralAttrColorType type) : type(type) {
        }

        GeneralAttrColorType type = GeneralAttrColorType::none;

        bool mark = false;
        bool code = false;
        bool keyboard = false;
        bool underline = false;
        bool destroy = false;
        bool strong = false;
        bool italic = false;
        bool link = false;

        int fontSize = 16;
    };
}