#include "Menu.h"
#include "QLayout"
#include "QPushButton"
#include "QScrollBar"
#include "qevent.h"
#include "logger.h"
#include "ThemeConfig.h"
#include "QTreeWidget"
#include "QVariant"

namespace wl {

    void MenuItem::treeToListKeys(const std::vector<MenuItem> &items, std::vector<QString> &keys) {
        auto tmpList = std::vector<MenuItem>();
        tmpList.insert(tmpList.begin(), items.begin(), items.end());
        while (!tmpList.empty()) {
            auto it = tmpList[0];
            keys.push_back(it.key);
            tmpList.erase(tmpList.begin());

            if (!it.children.empty()) {
                for (const auto &it2: it.children) {
                    tmpList.push_back(it2);
                }
            }
        }

    }

    Menu::Menu(QWidget *parent) : QScrollArea(parent) {
//        this->setStyleSheet("border: 1px solid rgb(230,100,23);");
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        this->setMinimumHeight(200);
        this->setMinimumWidth(100);


        tree = new QTreeWidget(this);
        tree->clear();
        this->setWidget(tree);
        tree->verticalScrollBar()->setStyleSheet(
                R"(
            QScrollBar {
                    width: 8px;
                    background-color: #f0f0f0;
                    border: none;
            }
            QScrollBar::handle {
                    background-color: #c8c8c8;
                    border-radius: 4px;
            }
            QScrollBar::handle:hover {
                    background-color: #c8c8c8;
                    color:rgba(0,0,0,0.5);
                    height:50%;
            }
            QScrollBar::corner {
                    background: transparent;
            }
        )"
        );
        connect(tree, SIGNAL(itemClicked(QTreeWidgetItem * , int)), this, SLOT(onTreeItemClicked(QTreeWidgetItem * , int)));
    }

    void Menu::initWidget() {
        auto themeConfig = ThemeConfig::Instance();
        tree->clear();
        for (const auto &it: this->menuItems) {
            auto *btn = new QPushButton(it.label);
            btn->setStyleSheet(":!hover{color:rgba(0,0,0,0.88);font-size:16px;border:none;text-align:left;padding:5 10 5 10;}"
                               ":hover{color:rgba(0,0,0,0.88); font-size:16px;border:none;text-align:left;padding:5 10 5 10;background-color:rgb(237,237,237);}");
            btn->setFixedHeight(28);
            btn->setProperty("menu_item_key", it.key);
            connect(btn, SIGNAL(clicked()), this, SLOT(onItemClicked()));
            auto *item1 = new QTreeWidgetItem(0);
//            item1->setText(0, it.label);
            tree->addTopLevelItem(item1);
            this->btn2Item_[btn] = item1;
            tree->setItemWidget(item1, 0, btn);
            if (!it.children.empty()) {
                for (const auto &it2: it.children) {
                    auto *btnSecond = new QPushButton(it2.label);
                    std::string str;
                    str += ":!hover{color:rgba(0,0,0,0.88);font-size:16px;border:none;text-align:left;padding:5 10 5 20;}";
                    str += ":hover{color:rgba(0,0,0,0.88); font-size:16px;border:none;text-align:left;padding:5 10 5 20;background-color:";
                    str += themeConfig.colorInfoBg + ";}";
                    btnSecond->setStyleSheet(QString::fromStdString(str));
                    btnSecond->setProperty("menu_item_key", it2.key);
                    connect(btnSecond, SIGNAL(clicked()), this, SLOT(onItemClicked()));
                    btnSecond->setFixedHeight(28);

                    auto *item2 = new QTreeWidgetItem(0);

                    this->btn2Item_[btnSecond] = item2;
                    item1->addChild(item2);
                    tree->setItemWidget(item2, 0, btnSecond);

                    if (!it2.children.empty()) {
                        for (const auto &it3: it2.children) {
                            auto *btnThird = new QPushButton(it3.label);
                            std::string str;
                            str += ":!hover{color:rgba(0,0,0,0.88);font-size:16px;border:none;text-align:left;padding:5 10 5 30;}";
                            str += ":hover{color:rgba(0,0,0,0.88); font-size:16px;border:none;text-align:left;padding:5 10 5 30;background-color:";
                            str += themeConfig.colorInfoBg + ";}";
                            btnThird->setStyleSheet(QString::fromStdString(str));
                            btnThird->setProperty("menu_item_key", it3.key);
                            connect(btnThird, SIGNAL(clicked()), this, SLOT(onItemClicked()));
                            btnThird->setFixedHeight(28);

                            auto *item3 = new QTreeWidgetItem(0);
                            item2->addChild(item3);
                            tree->setItemWidget(item3, 0, btnThird);
                            this->btn2Item_[btnThird] = item3;

                        }
                    }
                }
            }
        }


//        tree->setStyleSheet(R"(
//            QTreeWidget::item {
//height:30px;
//                margin-top:1px;
//                margin-bottom:1px;
//                font-size:22px;
//                border-top-right-radius: 8px;
//                border-bottom-right-radius: 8px;
//border:1px solid red;
//            }
//        )");
        tree->setAnimated(true);
        tree->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        tree->setHeaderHidden(true);

        tree->expandAll();
        tree->setItemsExpandable(true);
        tree->setIndentation(0);
        tree->setFixedWidth(this->geometry().width());
        tree->setFixedHeight(this->geometry().height());
    }

    void Menu::resizeEvent(QResizeEvent *event) {
//        this->widget()->resize(event->size());
        QScrollArea::resizeEvent(event);
//        LOG_INFO(event->size().width());
        this->initWidget();
    }

    void Menu::onItemClicked() {
        auto *btn = (QPushButton *) (sender());
        auto k = btn->property("menu_item_key").toString();
        std::vector<QString> keys;
        std::vector<QString> childrenKeys;
        for (const auto &it: this->menuItems) {
            if (k == it.key) {
                keys.push_back(it.key);
                MenuItem::treeToListKeys(it.children, childrenKeys);
                break;
            }
            if (it.children.empty()) {
                continue;
            }
            for (const auto &it2: it.children) {
                if (k == it2.key) {
                    keys.push_back(it.key);
                    keys.push_back(it2.key);
                    MenuItem::treeToListKeys(it2.children, childrenKeys);
                    break;
                }
                if (it2.children.empty()) {
                    continue;
                }
                for (const auto &it3: it2.children) {
                    if (k == it3.key) {
                        keys.push_back(it.key);
                        keys.push_back(it2.key);
                        keys.push_back(it3.key);
                        MenuItem::treeToListKeys(it3.children, childrenKeys);
                        break;
                    }
                }
            }
        }
        for (const auto &it: keys) {
//            LOG_INFO(it.toStdString());
        }
        std::stringstream ss;
        for (const auto &it: childrenKeys) {
            ss << it.toStdString() << ",";
        }
//        LOG_INFO(ss.str())
//        LOG_INFO("count:" << this->widget()->layout()->count())
        if (this->btn2Item_.find(btn) != this->btn2Item_.end()) {
            auto *item = dynamic_cast<QTreeWidgetItem *>((QTreeWidgetItem *) this->btn2Item_[btn]);
            if (item && item->childCount() > 0) {
                item->setExpanded(!item->isExpanded());
                return;
            }
        }
        emit menuClicked(k);

    }

    void Menu::onTreeItemClicked(QTreeWidgetItem *item, int index) {
        LOG_INFO("index:" << index)
    }
}