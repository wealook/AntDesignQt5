#pragma once

#include "memory"
#include <variant>
#include "logger.h"
#include "ThemeConfig.h"

namespace wl {

    enum class ResponseSizeName {
        xs, sm, md, lg, xl, xxl
    };


    class ResponseSize {

    public:
        static ResponseSizeName getResponseSizeName(uint16_t width) {
            auto &config = ThemeConfig::Instance();
            if (width <= config.screenXSMax) {
                return ResponseSizeName::xs;
            } else if (width >= config.screenSMMin && width <= config.screenSMMax) {
                return ResponseSizeName::sm;
            } else if (width >= config.screenMDMin && width <= config.screenMDMax) {
                return ResponseSizeName::md;
            } else if (width >= config.screenLGMin && width <= config.screenLGMax) {
                return ResponseSizeName::lg;
            } else if (width >= config.screenXLMin && width <= config.screenXLMax) {
                return ResponseSizeName::xl;
            } else if (width >= config.screenXXLMin) {
                return ResponseSizeName::xxl;
            }
            return ResponseSizeName::md;
        }

        ResponseSize() = default;

        ResponseSize(uint16_t xs, uint16_t sm, uint16_t md, uint16_t lg, uint16_t xl, uint16_t xxl) :
                xs(xs), sm(sm), md(md), lg(lg), xl(xl), xxl(xxl) {
        };

        [[nodiscard]] uint16_t getSize(ResponseSizeName name) const {
            if (name == ResponseSizeName::xs) {
                return this->xs;
            } else if (name == ResponseSizeName::sm) {
                return this->sm;
            } else if (name == ResponseSizeName::md) {
                return this->md;
            } else if (name == ResponseSizeName::lg) {
                return this->lg;
            } else if (name == ResponseSizeName::xl) {
                return this->xl;
            } else if (name == ResponseSizeName::xxl) {
                return this->xxl;
            }
            return 0;
        }

        uint16_t xs = 0;
        uint16_t sm = 0;
        uint16_t md = 0;
        uint16_t lg = 0;
        uint16_t xl = 0;
        uint16_t xxl = 0;
    };

    class ColAttr {
    public:
        std::variant<uint16_t, ResponseSize> span = 0;
        std::variant<uint16_t, ResponseSize> offset = 0;

        uint16_t getSpan(ResponseSizeName name = ResponseSizeName::md) {
            if (std::holds_alternative<ResponseSize>(this->span)) {
//                LOG_INFO(static_cast<int>( name))
//                LOG_INFO(static_cast<ResponseSize>(std::get<ResponseSize>(this->span)).getSize(name))
                return static_cast<ResponseSize>(std::get<ResponseSize>(this->span)).getSize(name);
            } else if (std::holds_alternative<uint16_t>(this->span)) {
//                LOG_INFO(std::get<uint16_t>(this->span))
                return std::get<uint16_t>(this->span);
            }
            return 0;
        }

        uint16_t getOffset(ResponseSizeName name = ResponseSizeName::md) {
            if (std::holds_alternative<ResponseSize>(this->offset)) {
                return static_cast<ResponseSize>(std::get<ResponseSize>(this->offset)).getSize(name);
            } else if (std::holds_alternative<uint16_t>(this->offset)) {
                return std::get<uint16_t>(this->offset);
            }
            return 0;
        }

    private:

    };
}