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

        SelectAttrOption(std::wstring label, std::wstring value) : label(std::move(label)), value(std::move(value)) {

        };

        std::wstring label;
        std::wstring value;
    };


    using SelectAttrOptions = std::vector<SelectAttrOption>;

    class SelectAttr {
    public:
        SelectAttrMode mode = SelectAttrMode::none;
        SelectAttrOptions options;
        uint16_t fixedWidth = 100;
        uint16_t selectHeight = 100;
    };
}