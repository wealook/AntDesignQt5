#pragma once

#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <bitset>

namespace wl {

    class StringHelper {
    public:
        static std::string &trim(std::string &s) {
            if (s.empty()) {
                return s;
            }

            std::string::iterator c;
            for (c = s.begin(); c != s.end() && iswspace(*c++););
            s.erase(s.begin(), --c);

            for (c = s.end(); c != s.begin() && iswspace(*--c););
            s.erase(++c, s.end());

            return s;
        }

        // unicode to utf8
        static std::string ws2s(const std::wstring &src);

        // utf8 to unicode
        static std::wstring s2ws(const std::string &str);

        //GBK 2 unicode
        static std::wstring ls2ws(const std::string &input);

        //unicode to GBK
        static std::string ws2ls(const std::wstring &unicodeStr);

        //utf8 to GBK
        static std::string s2ls(const std::string &input) {
            std::wstring unicodeStr = s2ws(input);
            return ws2ls(unicodeStr);
        }

        //gbk to utf8
        static std::string ls2s(const std::string &input) {
            std::wstring unicodeStr = ls2ws(input);
            return ws2s(unicodeStr);
        }

        static std::string toLower(const std::string &in) {
            std::string s = in;
            std::for_each(s.begin(), s.end(), [](char &c) {
                c = ::tolower(c);
            });
            return s;
        }

        static void split(const std::string &s, std::vector<std::string> &v, const std::string &c) {
            std::string::size_type pos1, pos2;
            size_t len = s.length();
            pos2 = s.find(c);
            pos1 = 0;
            while (std::string::npos != pos2) {
                v.emplace_back(s.substr(pos1, pos2 - pos1));

                pos1 = pos2 + c.size();
                pos2 = s.find(c, pos1);
            }
            if (pos1 != len)
                v.emplace_back(s.substr(pos1));
        }

        static std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
            std::vector<std::string> results;
            split(s, results, delimiter);
            return results;
        }

        static std::string &replaceAll(std::string &source, const std::string &from, const std::string &to) {
            std::string newString;
            newString.reserve(source.length());  // avoids a few memory allocations

            std::string::size_type lastPos = 0;
            std::string::size_type findPos;

            while (std::string::npos != (findPos = source.find(from, lastPos))) {
                newString.append(source, lastPos, findPos - lastPos);
                newString += to;
                lastPos = findPos + from.length();
            }

            // Care for the rest after last occurrence
            newString += source.substr(lastPos);
            source.swap(newString);

            return source;
        }

        static std::map<std::string, std::string> parseYoloCfg(std::string cfgFile) {
            std::map<std::string, std::string> results;
            std::ifstream ifs(cfgFile.c_str());
            std::string line;
            std::string section = "::";
            while (std::getline(ifs, line)) {
                auto commentPos = line.find("#");
                if (commentPos != line.npos)
                    line = line.substr(0, commentPos);

                trim(line);
                if (line[0] == '[' && line[line.length() - 1] == ']') {
                    section = line.substr(1, line.length() - 2);
                    section += "::";
                    continue;
                }

                auto sepPos = line.find("=");
                if (sepPos == line.npos)
                    continue;

                std::string key = line.substr(0, sepPos);
                std::string val = line.substr(sepPos + 1);

                trim(key);
                trim(val);

                key = section + key;
                results[key] = val;
            }

            return results;
        }


        static std::string getMicroTimestampStr() {
            return std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        }

        static std::string getTimestampStr(const char *formater = "%y%m%d%H%M%S") {
            const size_t buffer_size = 1024;
            char fname[buffer_size];
            time_t t = time(0);

            struct tm *now = nullptr;
#if defined(_WINDOWS)
            struct tm nowAlloc;
            localtime_s(&nowAlloc, &t);
            now = &nowAlloc;
#else
            now = localtime(&t);
#endif

            strftime(fname, buffer_size, formater, now);

            return fname;
        }

        static std::pair<std::string, std::string> splitFilePath(const std::string &filePath) {
            auto lnpos = filePath.rfind('\\');
            auto rnpos = filePath.rfind('/');

            if (lnpos != filePath.npos && rnpos != filePath.npos) {
                if (rnpos > lnpos) lnpos = rnpos;
            } else if (rnpos != filePath.npos) {
                lnpos = rnpos;
            } else if (rnpos == filePath.npos && lnpos == filePath.npos) {
                return std::make_pair("", filePath);
            }
            std::string basePath = filePath.substr(0, lnpos);
            std::string fileName = filePath.substr(lnpos + 1);

            return std::make_pair(basePath, fileName);
        }

        static std::string toHexString(const unsigned char *data, int len, const std::string &delimiter = " ") {
            std::stringstream ss;
            for (int index = 0; index < len; index++) {
                ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (int) data[0 + index];
                if (index < len - 1) {
                    ss << delimiter;
                }
            }
            return ss.str();
        }

        static std::string toHexString(uint32_t *data, int len, const std::string &delimiter = " ") {
            std::stringstream ss;
            for (int index = 0; index < len; index++) {
                auto v0 = *(uint32_t *) (data + index);
                auto v1 = (v0 & 0xFF000000) >> 24;
                auto v2 = (v0 & 0xFF0000) >> 16;
                auto v3 = (v0 & 0xFF00) >> 8;
                auto v4 = v0 & 0xFF;
                ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (int) v1 << delimiter;
                ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (int) v2 << delimiter;
                ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (int) v3 << delimiter;
                ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (int) v4;
                if (index < len - 1) {
                    ss << delimiter;
                }
            }
            return ss.str();
        }

        static std::string toHexString(uint32_t val, const std::string &delimiter = " ") {
            std::stringstream ss;
            ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << val;
            std::string str = ss.str();
            std::stringstream ss2;
            ss2 << str[0] << str[1];
            for (int index = 2; index < str.length(); index += 2) {
                ss2 << delimiter << str[index] << str[index + 1];
            }
            return ss2.str();
        }

        static std::string toHexString(unsigned char val) {
            std::stringstream ss;
            ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (uint32_t) val;
            return ss.str();
        }

        static std::string toHexString(const std::vector<unsigned char> &li) {
            std::stringstream ss;
            for (auto &it: li) {
                ss << std::hex << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::uppercase) << (uint16_t) it;
            }
            return ss.str();
        }
    };

}
