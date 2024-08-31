#pragma  once

#include <utility>

#include "GeneralAttr.h"

namespace wl {


    enum class InputAttrStatus {
        none,
        warning,
        error
    };
    enum class InputAttrVariant {
        outlined,
        borderless,
        filled
    };

    class InputAttr {


    public:
        InputAttr() = default;

        explicit InputAttr(QWidget *textBefore, QWidget *textAfter = nullptr) :
                addonBefore(textBefore), addonAfter(textAfter) {
        }

        GeneralAttrSize size = GeneralAttrSize::middle;
        QWidget *addonBefore = nullptr;
        QWidget *addonAfter = nullptr;

        InputAttrStatus status = InputAttrStatus::none;
        bool disabled = false;
        QWidget *prefix = nullptr;
        QWidget *suffix = nullptr;

        QString placeholder;
        InputAttrVariant variant = InputAttrVariant::outlined;
    };
}