#pragma  once

#include "QColor"
#include "regex"
#include "logger.h"

namespace wl {
    class Util {

    public:
        static unsigned char hexCharToAscii(unsigned char hex1, unsigned char hex2) {
            unsigned char data = 0;
            if (hex1 >= '0' && hex1 <= '9') {
                data = (hex1 - '0') << 4;
            } else if (hex1 >= 'a' && hex1 <= 'f') {
                data = (hex1 - 'a' + 10) << 4;
            } else if (hex1 >= 'A' && hex1 <= 'F') {
                data = (hex1 - 'A' + 10) << 4;
            }

            if (hex2 >= '0' && hex2 <= '9') {
                data += (hex2 - '0');
            } else if (hex2 >= 'a' && hex2 <= 'f') {
                data += (hex2 - 'a' + 10);
            } else if (hex2 >= 'A' && hex2 <= 'F') {
                data += (hex2 - 'A' + 10);
            }
            return data;
        }

        static QColor fromCssColor(const std::string &cssColor) {
            if (cssColor.empty()) {
                return Qt::black;
            }
            std::smatch m;
            if (std::regex_match(cssColor, m, std::regex("#([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})"))) {
                auto v1 = hexCharToAscii(m[1].str()[0], m[1].str()[1]);
                auto v2 = hexCharToAscii(m[2].str()[0], m[2].str()[1]);
                auto v3 = hexCharToAscii(m[3].str()[0], m[3].str()[1]);
//                LOG_INFO(cssColor);
//                LOG_INFO((int)v1);
//                LOG_INFO((int)v2);
//                LOG_INFO((int)v3);
                return QColor(v1, v2, v3);
            } else if (std::regex_match(cssColor, m, std::regex("rgb\\( *([0-9]{1,3}) *, *([0-9]{1,3}) *, *([0-9]{1,3}) *\\)"))) {
                return QColor(std::stoi(m[1].str()), std::stoi(m[2].str()), std::stoi(m[3].str()));
            } else if (std::regex_match(cssColor, m, std::regex("rgba\\( *([0-9]{1,3}) *, *([0-9]{1,3}) *, *([0-9]{1,3}) *, *([0-9.]{1,4}) *\\)"))) {
                auto a = std::stof(m[4].str());
                if (a < 1) {
                    a *= 255;
                }
                return QColor(std::stoi(m[1].str()), std::stoi(m[2].str()), std::stoi(m[3].str()), (int) a);
            }
            return Qt::black;
        }
    };
}
