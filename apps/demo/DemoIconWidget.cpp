
#include "DemoIconWidget.h"

#include <memory>
#include "magic_enum.hpp"
#include "Row.h"
#include "QLayout"
#include "QPushButton"
#include "VWidget.h"
#include "Text.h"
#include "Flex.h"
#include "Util.h"
#include "omp.h"
#include "regex"

DemoIconWidget::DemoIconWidget(QWidget *parent) : QWidget(parent) {

    auto *ly = new QVBoxLayout(this);
    this->setLayout(ly);
    auto themeConfig = wl::ThemeConfig::Instance();
    for (const auto &entry: magic_enum::enum_values<wl::IconSvg>()) {
        files_.emplace_back(magic_enum::enum_name(entry));
    }
    auto counter = files_.size();
    auto *flex = new wl::Flex();
    for (int index = 0; index < counter; index++) {
        auto name = files_[index];
        auto *icon = new wl::Icon();
        this->icons_.push_back(icon);
        icon->setFixedSize(60, 60);
        auto *h0 = new wl::HWidget();
        auto *wid = new wl::HWidget(true);
        h0->addWidget(wid);
        h0->setContentsMargins(1, 1, 1, 1);
        h0->setFixedSize(200, 120);
        wid->setContentsMargins(1, 1, 1, 1);
//        wid->layout()->setAlignment(Qt::AlignCenter);
        {
            auto h1 = new wl::HWidget();
            h1->addWidget(icon);
//            h1->setGlobalHover(false);
            wid->addWidget(h1);
        }
        auto *text = new wl::Text(QString::fromStdString(name));
        text->setStyleQss("text-align", "center");
        text->updateAttr();
        {

            auto h1 = new wl::HWidget();
//            h1->setGlobalHover(false);
            h1->addWidget(text);
            wid->addWidget(h1);
        }
        h0->setStyleQss("background-color", themeConfig.colorPrimary);
        h0->setStyleQss("!hover", "background-color", "white");
//        h0->setStyleQss("!hover", "color", "rgb(85,85,85)");
//        h0->setStyleQss("hover", "color", themeConfig.colorPrimary);
//        h0->getGlobalHoverAttributes().emplace_back("color");
        wid->layout()->setAlignment(Qt::AlignCenter);

        connect(h0, &wl::HWidget::mouseEnter, this, [text, icon]() {
            auto themeConfig = wl::ThemeConfig::Instance();
            text->setStyleQssFource("color", "white");
            icon->changeColor(wl::Util::fromCssColor("rgb(255,255,255)"));
            //     wid->setStyleSheet("HWidget:{background-color:blue}");
        });
        connect(h0, &wl::HWidget::mouseLeave, this, [text, icon]() {
            auto themeConfig = wl::ThemeConfig::Instance();
            text->setStyleQssFource("color", "rgb(85,85,85)");
            icon->changeColor(wl::Util::fromCssColor("rgb(85,85,85)"));
            // wid->setStyleSheet("HWidget:{background-color:white}");
        });

        flex->addWidget(h0);
    }

    this->layout()->addWidget(flex);
    this->thread_ = std::make_shared<std::thread>([this]() {
        auto theme = wl::ThemeConfig::Instance();
        auto counter = files_.size();
        omp_set_num_threads(6);
#pragma omp parallel   for
        for (auto index = 0; index < counter; index++) {
            std::regex r(".*?Twotone$");
            std::regex r2(".*?TwoTone$");
            if (std::regex_match(files_[index], r) || std::regex_match(files_[index], r2)) {
                this->icons_[index]->loadBaseSvg(QString::fromStdString(files_[index]));
            } else {
                this->icons_[index]->loadBaseSvg(QString::fromStdString(files_[index]), wl::Util::fromCssColor("rgb(85,85,85)"));
            }

        }
    });

}

DemoIconWidget::~DemoIconWidget() {
    this->working_ = false;
    if (this->thread_ && this->thread_->joinable()) {
        this->thread_->join();
    }
}
