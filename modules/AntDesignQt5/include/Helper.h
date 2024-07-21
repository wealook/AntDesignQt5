#pragma once

#include <string>
#include <unordered_map>

namespace wl {


    void styles2String(const std::unordered_map<std::string, std::string> &styles, std::string &res) {
        for (const auto& it: styles) {
            res += it.first + ":" + it.second + ";";
        }
    }
};