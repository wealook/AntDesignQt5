#pragma  once

#include <functional>
#include <utility>
#include <vector>
#include <string>
#include <optional>

namespace wl {

    enum class SelectAttrMode {
        none,
        multiple,
        tags,
    };

    class SelectAttrOption {

    public:
        SelectAttrOption() = default;

        SelectAttrOption(const SelectAttrOption &option) {
            this->label = option.label;
            this->value = option.value;
            this->selected = option.selected;
        };

        SelectAttrOption(std::wstring label, std::wstring value) : label(std::move(label)), value(std::move(value)) {

        };

        std::wstring label;

        std::wstring value;
        bool selected = false;
    };


    using SelectAttrOptions = std::vector<SelectAttrOption>;

    class SelectAttr {
    public:
        SelectAttrMode mode = SelectAttrMode::none;
        SelectAttrOptions options;
        uint16_t fixedWidth = 100;
        uint16_t selectHeight = 200;
    };
}