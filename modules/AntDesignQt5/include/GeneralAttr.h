#pragma once

#include <optional>
#include <utility>
#include "QString"

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
    enum class GeneralAttrTypeDirection {
        horizontal,
        vertical,
    };

    class GeneralAttr {
    public:

        GeneralAttrSize size = GeneralAttrSize::middle;
        GeneralAttrShape shape = GeneralAttrShape::none;
    };


    class GeneralAttrOption {
    public:

        explicit GeneralAttrOption(QString label, QString value, bool disabled = false) :
                label(std::move(label)), value(std::move(value)), disabled(disabled) {

        }

        QString label;
        QString value;
        bool disabled = false;
    };


}


