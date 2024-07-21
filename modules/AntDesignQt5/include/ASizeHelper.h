#pragma  once


#include "GeneralAttr.h"

namespace wl {


    uint16_t getSizeHeight(GeneralAttrSize size) {
        if (size == GeneralAttrSize::small) {
            return 14;
        }
        if (size == GeneralAttrSize::middle) {
            return 20;
        }
        if (size == GeneralAttrSize::large) {
            return 24;
        }
        return 14;
    }
}