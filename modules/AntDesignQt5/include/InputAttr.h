#pragma  once

#include <utility>

#include "GeneralAttr.h"

namespace wl {


    enum class InputAttrStatus {
        none,
        warning,
        error
    };

    class InputAttr {


    public:
        InputAttr() = default;

        explicit InputAttr(QString textBefore, const QString &textAfter) :
                addonBefore(std::move(textBefore)), addonAfter(textAfter) {
        }

        GeneralAttrSize size = GeneralAttrSize::middle;
        QString addonBefore;
        QString addonAfter;
        InputAttrStatus status = InputAttrStatus::none;
        bool disabled = false;
        QWidget *prefix = nullptr;
        QWidget *suffix = nullptr;
    };
}