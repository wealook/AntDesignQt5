#pragma  once

#include "GeneralAttr.h"

namespace wl {


    enum class InputAttrStatus {
        none,
        warning,
        error
    };

    class InputAttr {


    public:
        GeneralAttrSize size = GeneralAttrSize::middle;
        std::wstring textBefore;
        std::wstring textAfter;
        InputAttrStatus status = InputAttrStatus::none;
        bool disabled = false;
    };
}