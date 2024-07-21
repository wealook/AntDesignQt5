#pragma  once

#include "GeneralAttr.h"
#include "IconSvg.h"

namespace wl {

    enum class ButtonAttrType {
        primary,
        dashed,
        link,
        text,
        none
    };

    enum class ButtonAttrIconPosition {
        prefix,
        postfix,
    };

    class ButtonAttr {
    public:
        ButtonAttr() = default;

        explicit ButtonAttr(ButtonAttrType type, GeneralAttrSize size, GeneralAttrShape shape) :
                type(type), size(size), shape(shape) {
//            this->iconSvg = IconSvg::SearchOutlined;
        }

        explicit ButtonAttr(ButtonAttrType type, GeneralAttrSize size, GeneralAttrShape shape, IconSvg iconSvg) :
                type(type), size(size), shape(shape), icon(iconSvg) {
        }

        ButtonAttrType type = ButtonAttrType::primary;
        bool loading = false;
        bool blck = false;
        bool disabled = false;
        bool danger = false;
        GeneralAttrSize size = GeneralAttrSize::middle;
        GeneralAttrShape shape = GeneralAttrShape::none;
        std::optional<IconSvg> icon;
        ButtonAttrIconPosition iconPosition = ButtonAttrIconPosition::prefix;
    };
}