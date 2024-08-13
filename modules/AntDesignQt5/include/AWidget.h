#pragma once

#include <sstream>
#include "QWidget"
#include "unordered_map"
#include "logger.h"

namespace wl {

    class AWidget {

    public:

        AWidget();

        void setStyleQss(const std::string &group, const std::string &k, const std::string &v) {
            if (this->styles.find(group) == this->styles.end()) {
                this->styles[group] = std::unordered_map<std::string, std::string>();
            }
            this->styles[group][k] = v;
        }

        bool existStyleQss(const std::string &group, const std::string &k) {
            if (this->styles.find(group) != this->styles.end()) {
                return this->styles[group].find(k) != this->styles[group].end();
            }
            return false;

        }

        void setStyleQss(const std::string &k, const std::string &v) {
            this->setStyleQss("!hover", k, v);
            if (!this->existStyleQss("hover", k)) {
                this->setStyleQss("hover", k, v);
            }
        }

        std::unordered_map<std::string, std::string> getStyleQss(const std::string &group) {
            if (this->styles.find(group) != this->styles.end()) {
                return this->styles[group];
            }
            return {};
        }

        std::string getStyleQss(const std::string &group, const std::string &k) {
            if (this->existStyleQss(group, k)) {
                return this->styles[group][k];
            }
            return "";
        }

        void removeStyle(const std::string &group, const std::string &k) {
//            this->styles.erase(k);
        }


        QString getJoinStyles() {
            std::stringstream ss;
            for (const auto &group: this->styles) {
                if (!group.first.empty()) {
                    if (group.first[0] != ':' && (group.first == "hover" || group.first == "!hover")) {
                        ss << ":";
                    }
                }
                ss << group.first << "{";
                for (const auto &it: group.second) {
                    ss << it.first << ":" << it.second << ";";
                }
                ss << "}";
            }
            //     LOG_INFO(ss.str());
            return QString::fromStdString(ss.str());
        }

        QString getJoinStyles(const std::string &groupName, bool prefix = true) {
            std::stringstream ss;
            for (const auto &group: this->styles) {
                if (groupName != group.first) {
                    continue;
                }
                // TODO 有些不需要大括号的情况
                if (prefix) {
                    if (!group.first.empty()) {
                        if (group.first[0] != ':') {
                            ss << ":";
                        }
                    }
                    ss << group.first << "{";
                }

                for (const auto &it: group.second) {
                    ss << it.first << ":" << it.second << ";";
                }
                if (prefix) {
                    ss << "}";
                }
            }
            return QString::fromStdString(ss.str());
        }

    protected:

    private:
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> styles;
    };

}