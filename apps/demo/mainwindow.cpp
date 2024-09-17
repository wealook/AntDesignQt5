//
///1/4.
//

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSpacerItem>
#include <memory>
#include "Button.h"
#include "Space.h"
#include "Input.h"
#include "Select.h"
#include "string_helper.h"
#include "qevent.h"
#include "Slider.h"
#include "Header.h"
#include "Content.h"
#include "Footer.h"
#include "Menu.h"
#include "DemoSelectWidget.h"
#include "DemoDividerWidget.h"
#include "DemoCardWidget.h"
#include "DemoGridWidget.h"
#include "DemoButtonWidget.h"
#include "DemoIconWidget.h"
#include "DemoTypography.h"
#include "DemoInputWidget.h"
#include "DemoCheckBoxWidget.h"
#include "DemoRadioWidget.h"
#include "DemoSwitchWidget.h"
#include "DemoTagWidget.h"
#include "DemoFlexWidget.h"
#include "DemoDatePickerWidget.h"
#include "DemoTableWidget.h"
#include "DemoPaginationWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("AntDesignQt5");
    this->widgetsMap["select"] = new DemoSelectWidget();
    this->widgetsMap["divider"] = new DemoDividerWidget();
    this->widgetsMap["card"] = new DemoCardWidget();
    this->widgetsMap["grid"] = new DemoGridWidget();
    this->widgetsMap["button"] = new DemoButtonWidget();
    this->widgetsMap["typography"] = new DemoTypography();
    this->widgetsMap["input"] = new DemoInputWidget();
    this->widgetsMap["checkbox"] = new DemoCheckBoxWidget();
    this->widgetsMap["radio"] = new DemoRadioWidget();
    this->widgetsMap["switch"] = new DemoSwitchWidget();
    this->widgetsMap["tag"] = new DemoTagWidget();
    this->widgetsMap["flex"] = new DemoFlexWidget();
    this->widgetsMap["datePicker"] = new DemoDatePickerWidget();
    this->widgetsMap["table"] = new DemoTableWidget();
    this->widgetsMap["pagination"] = new DemoPaginationWidget();
    this->widgetsMap["icon"] = new DemoIconWidget();

    baseLayout_ = new wl::Layout(this);
    auto *layout2 = new wl::Layout(this);
    this->layout()->addWidget(baseLayout_);
    auto *header = new wl::Header();
    content_ = new wl::Content();
    auto *footer = new wl::Footer();
    auto *slider = new wl::Slider();
    auto sliderLayout = new QVBoxLayout(slider);
    sliderLayout->setSpacing(0);
    sliderLayout->setMargin(0);
    auto *menu = new wl::Menu();
    connect(menu, SIGNAL(menuClicked(QString)), this, SLOT(onMenuClicked(QString)));

    {
        auto tmpItems = wl::MenuItem("通用", "general");
        tmpItems.children.emplace_back("Button按钮", "button");
//        tmpItems.children.emplace_back("FloatButton悬浮按钮", "general-button");
        tmpItems.children.emplace_back("Icon图标", "icon");
        tmpItems.children.emplace_back("Typography排版", "typography");
        menu->menuItems.push_back(tmpItems);
    }
    {
        auto tmpItems = wl::MenuItem("导航", "nav");
        tmpItems.children.emplace_back("Pagination分页", "pagination");
        menu->menuItems.push_back(tmpItems);
    }
    {
        auto tmpItems = wl::MenuItem("布局", "general");
        tmpItems.children.emplace_back("Divider分割线", "divider");
        tmpItems.children.emplace_back("Flex弹性布局", "flex");
        tmpItems.children.emplace_back("Grid栅格", "grid");
        tmpItems.children.emplace_back("Layout布局", "general-button");
        tmpItems.children.emplace_back("Space间距", "general-button");
        menu->menuItems.push_back(tmpItems);
    }
    {
        auto tmpItems = wl::MenuItem("数据录入", "data-input");
        tmpItems.children.emplace_back("Checkbox多选框", "checkbox");
        tmpItems.children.emplace_back("DatePicker日期选择", "datePicker");
        tmpItems.children.emplace_back("Input输入框", "input");
        tmpItems.children.emplace_back("Radio 单选框", "radio");
        tmpItems.children.emplace_back("Select 选择器", "select");
        tmpItems.children.emplace_back("Switch 开关", "switch");
        menu->menuItems.push_back(tmpItems);
    }
    {
        auto tmpItems = wl::MenuItem("数据展示", "data-show");
        tmpItems.children.emplace_back("Card卡片", "card");
        tmpItems.children.emplace_back("Tag 标签", "tag");
        tmpItems.children.emplace_back("Table 表格", "table");
        menu->menuItems.push_back(tmpItems);

    }

    for (int index = 0; index < 0; index++) {
        auto firstItems = wl::MenuItem("Test " + QString::fromStdString(std::to_string(index)),
                                       "select-" + QString::fromStdString(std::to_string(index)));

        if (index % 2 == 0) {
            menu->menuItems.push_back(firstItems);
            continue;
        }
        for (int i = 0; i < 3; ++i) {
            auto secondItems = wl::MenuItem(
                    "second " + QString::fromStdString(std::to_string(index) + "_" + std::to_string(i)),
                    "select-" + QString::fromStdString(std::to_string(index) + "_" + std::to_string(i)));
            if (i % 2 == 0) {
                firstItems.children.push_back(secondItems);
                continue;
            }
            for (int j = 0; j < 3; ++j) {
                secondItems.children.emplace_back("third " + QString::fromStdString(
                                                          std::to_string(index) + "_" + std::to_string(i) + "_" + std::to_string(j)),
                                                  "select-" + QString::fromStdString(
                                                          std::to_string(index) + "_" + std::to_string(i) + "_" +
                                                          std::to_string(j)));
            }
            firstItems.children.push_back(secondItems);
        }
        menu->menuItems.push_back(firstItems);
    }
    menu->initWidget();
    sliderLayout->addWidget(menu);

//    auto *slider2 = new wl::Slider();

    layout2->addWidget(slider);
    layout2->addWidget(content_);
//    layout2->addWidget(slider2);
    layout2->initLayout();
//    baseLayout_->addWidget(header);
    baseLayout_->addWidget(layout2);
    baseLayout_->addWidget(footer);
    baseLayout_->initLayout();
    /*

          auto attr = btn->getAttr();
  //        attr.size = 100;
          attr.size = wl::GeneralAttrSize::small;
          btn->setAttr(attr);
          ui->h1->addWidget(btn);
          {
              auto *input = new wl::Input(this);
              auto attr = input->getAttr();
              attr.textBefore = wl::StringHelper::s2ws("aaaaaaaaa");
              input->setAttr(attr);
              ui->h1->addWidget(input);
          }
          {
              auto *pSelect = new wl::Select(this);
              auto attrSelect = pSelect->getAttr();
              attrSelect.fixedWidth = 150;
              attrSelect.selectHeight = 200;

              attrSelect.options.clear();
              for (int index = 0; index <= 10; index++) {
                  attrSelect.options.emplace_back(
                          QString("item" + QString::fromStdString(std::to_string(index))).toStdWString(),
                          QString("item" + QString::fromStdString(std::to_string(index))).toStdWString()
                  );
              }
              pSelect->setAttr(attrSelect);
              ui->h1->addWidget(pSelect);

          }
      }*/
    /*
      for (int index = 0; index < 2; index++) {
          PaperThumbnailWidget* btn = new PaperThumbnailWidget();
          btn->setFixedHeight(200);
          connect(btn, SIGNAL(imageClicked(int, int)), this, SLOT(onImageThumbnailClicked(int, int)));
          ly->addWidget(btn);
      }
      QSpacerItem* spacer = new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
      ly->addItem(spacer);*/
}

void MainWindow::resizeEvent(QResizeEvent *event) {
//    LOG_INFO(this->size().height())
//    LOG_INFO(this->size().width())
    baseLayout_->resize(event->size());
    QWidget::resizeEvent(event);
}

void MainWindow::onMenuClicked(QString k) {
    auto str = k.toStdString();
    LOG_INFO(str)
    if (this->widgetsMap.find(str) != this->widgetsMap.end()) {
        content_->setContentWidget(this->widgetsMap[str]);
    } else {
//        content_->setContentWidget(nullptr);
    }
}
