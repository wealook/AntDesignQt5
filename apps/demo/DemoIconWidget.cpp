
#include "DemoIconWidget.h"
#include "magic_enum.hpp"
#include "Icon.h"
#include "logger.h"
#include "Row.h"
#include "Col.h"
#include "QLayout"
#include "QPushButton"
#include "ThemeConfig.h"

DemoIconWidget::DemoIconWidget(QWidget *parent) : QWidget(parent) {

    auto *ly = new QVBoxLayout(this);
    auto *row = new wl::Row();

    int sum = 0;

    auto themeConfig = wl::ThemeConfig::Instance();
    for (const auto &entry: magic_enum::enum_values<wl::IconSvg>()) {
        auto *col = new wl::Col();
        auto attr = col->getAttr();
        attr.span = 3;
        col->setAttr(attr);
        auto *icon = new wl::Icon(QString::fromStdString(std::string(magic_enum::enum_name(entry))), Qt::blue);
        icon->setFixedHeight(100);
        col->setContentWidget(icon);
//        col->setContentWidget(new QPushButton("aaaaaaa"));
        row->addCol(col);
        sum++;

    }
    LOG_INFO("sum:" << sum)
    row->flushContent();
    ly->addWidget(row);
}
