
#include <QHBoxLayout>
#include <QLineEdit>
#include "Select.h"
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include <QScrollBar>
#include "ThemeConfig.h"
#include "Icon.h"
#include <QMouseEvent>
#include <QLabel>
#include "algorithm"

namespace wl {

    SelectArea::SelectArea(QWidget *parent) : QScrollArea(parent) {
        this->verticalScrollBar()->setStyleSheet(R"(
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

        this->setStyleQss("border", "none");
        this->setContentsMargins(2, 2, 2, 2);
        this->setStyleSheet(this->getJoinStyles());
    }

    void SelectArea::mousePressEvent(QMouseEvent *event) {
        QScrollArea::mousePressEvent(event);
    }

    void SelectArea::mouseReleaseEvent(QMouseEvent *event) {
        QScrollArea::mouseReleaseEvent(event);
    }


    bool SelectArea::event(QEvent *e) {
        if (e->type() == QEvent::MouseButtonPress) {
            auto event = (QMouseEvent *) e;
            if (event->button() == Qt::LeftButton) {
                // 判断点击坐标是否在窗口内容区之外
                if (!geometry().contains(event->pos())) {
                    auto gP = this->mapToGlobal(event->pos());
                    LOG_INFO("gp:" << gP.x() << "," << gP.y())
                    emit blankSpaceClicked(gP);
                    // 处理空白位置的点击事件
                }
            }
        }
        return QScrollArea::event(e);
    }

    void SelectArea::renderOptions(const SelectActionOptions &options1, bool update) {
        auto options = options1;
        // TODO 排序
        std::sort(options.begin(), options.end(), [](SelectActionOption &t1, SelectActionOption &t2) {
            return t1.label < t2.label;
//            return false;
        });
//      auto last  this->verticalScrollBar()->sliderPosition();
        if (!update) {
            auto *oldWidget = this->widget();
            if (oldWidget != nullptr) {
                oldWidget->setParent(nullptr);
                delete oldWidget;
            }
            auto *widget = new QWidget();
            widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            widget->setLayout(new QVBoxLayout());
            this->setWidget(widget);
        }

        auto layout = this->widget()->layout();

        auto themeConfig = ThemeConfig::Instance();

        for (int index = 0; index < options.size(); index++) {
            auto it = options[index];

            QPushButton *label;
            if (update) {
                label = dynamic_cast<QPushButton *>(this->widget()->layout()->itemAt(index)->widget());
            } else {
                label = new QPushButton(QString::fromStdWString(it.label));
                label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                connect(label, SIGNAL(clicked()), this, SLOT(onSelectItemClicked()));
                layout->addWidget(label);
            }
            label->setText(QString::fromStdWString(it.label));
            label->setVisible(!it.isHide);
            auto aWidget = AWidget();
            aWidget.setStyleQss("border", "none");
            aWidget.setStyleQss("font-size", "24px");
            aWidget.setStyleQss("height", "32px");

            aWidget.setStyleQss("border-top-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            aWidget.setStyleQss("border-top-right-radius", std::to_string(themeConfig.borderRadius) + "px");
            aWidget.setStyleQss("border-bottom-left-radius", std::to_string(themeConfig.borderRadius) + "px");
            aWidget.setStyleQss("border-bottom-right-radius", std::to_string(themeConfig.borderRadius) + "px");


            aWidget.setStyleQss("background-color", "rgb(255,255,255)");
            aWidget.setStyleQss("hover", "background-color", "rgb(245,245,245)");
            aWidget.setStyleQss("text-align", "left");
            aWidget.setStyleQss("padding-left", "4px");
            aWidget.setStyleQss("padding-right", "4px");
            aWidget.setStyleQss("margin-right", "4px");

            if (it.selected) {
                {
                    auto beforeIndex = index - 1;
                    if (beforeIndex >= 0 && options[beforeIndex].selected) {
                        aWidget.setStyleQssFource("border-top-left-radius", "0px");
                        aWidget.setStyleQssFource("border-top-right-radius", "0px");
                    }
                }
                {
                    auto nextIndex = index + 1;
                    if (nextIndex < options.size() && options[nextIndex].selected) {
                        aWidget.setStyleQssFource("border-bottom-left-radius", "0px");
                        aWidget.setStyleQssFource("border-bottom-right-radius", "0px");
                    }
                }

                aWidget.setStyleQssFource("background-color", themeConfig.colorPrimaryBg);
            }
            label->setStyleSheet(aWidget.getJoinStyles());
            label->setProperty("option_label", QString::fromStdWString(it.label));
            label->setProperty("option_value", QString::fromStdWString(it.value));
        }

//        auto *verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
//        layout->addItem(verticalSpacer);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        this->setWidgetResizable(true);
    }

    void SelectArea::onSelectItemClicked() {
        auto btn = dynamic_cast<QPushButton *>(sender());
        if (btn) {
            QString val = btn->property("option_value").toString();
//            LOG_INFO(val.toStdString())
            emit selectItemClicked(val);
        }
    }

    void SelectArea::updateRenderOptions(const SelectActionOptions &options) {
        this->renderOptions(options, true);
    }

    SelectWidget::SelectWidget(QWidget *parent) : HWidget(parent) {
        selectArea_ = new SelectArea();
        selectArea_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(selectArea_, &SelectArea::selectItemClicked, this, [this](const QString &val) {
            emit selectItemClicked(val);
        });
        this->addWidget(selectArea_);
        auto themeConfig = ThemeConfig::Instance();
        this->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
        this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadiusLG) + "px");
        this->setStyleQss("background-color", "white");
        this->setStyleSheet(this->getJoinStyles());
        int margin = (int) themeConfig.borderRadiusLG / 2;
        this->setContentsMargins(margin, margin, margin, margin);
    }

    bool SelectWidget::event(QEvent *e) {
        if (e->type() == QEvent::MouseButtonPress) {
            auto event = (QMouseEvent *) e;
            if (event->button() == Qt::LeftButton) {
                if (!geometry().contains(event->pos())) {
                    auto gP = this->mapToGlobal(event->pos());
                    if (this->shouldHide) {
                        if (!this->shouldHide(gP)) {
                            this->shouldClose_ = false;
                            return false;
                        } else {
                            this->shouldClose_ = true;
                        }
                    } else {
                        this->shouldClose_ = true;
                    }
                }
            }
        }
        return HWidget::event(e);
    }

    void SelectWidget::renderOptions(const SelectActionOptions &options) {
        this->selectArea_->renderOptions(options);
    }

    void SelectWidget::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
        this->selectArea_->update();
    }

    void SelectWidget::updateRenderOptions(const SelectActionOptions &options) {
        this->selectArea_->updateRenderOptions(options);
    }

    Select::Select(QWidget *parent) : HWidget(parent) {
        this->init();
    }


    void Select::mousePressEvent(QMouseEvent *event) {
        wl::HWidget::mousePressEvent(event);
        if (this->selectHandleClick) {
            this->selectHandleClick = false;
            input_->setFocus();
            input_->grabKeyboard();
            return;
        }
        if (!this->geometry().contains(this->mapToParent(event->pos()))) {
            LOG_INFO("not in")
            return;
        }
        this->updateSelectWidgetPos();
        this->setFocus();
        if (selectWidget_->isHidden()) {
            selectWidget_->show();
            selectWidget_->clearFocus();
            this->focus_ = true;
            input_->setFocus();
            input_->grabKeyboard();
        } else {
            // 没用。当前处于显示的情况下，事件正常情况到不了这里，已经单独处理这种情况
//            selectWidget_->hide();
            this->focus_ = false;
            input_->releaseKeyboard();
        }
    }


    void Select::setAttrSize(GeneralAttrSize generalAttrSize) {
        Select::attrSize = generalAttrSize;
    }

    void Select::updateAttr() {
        if (!isFirstShow_) {
            return;
        }
        this->updateGeometry();
        auto themeConfig = ThemeConfig::Instance();
        if (this->focus_) {
            this->setStyleQss("border", "1px solid " + themeConfig.hoverBorderColor);
        } else {
            this->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
        }
        auto fixedHeight = themeConfig.controlHeight;
        text_->setContentsMargins(8, 0, 8, 0);
        tags_->setContentsMargins(8, 4, 8, 4);
        rightIcon_->setContentsMargins(8, 4, 8, 4);
        text_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        if (this->attrMode == SelectAttrMode::tags || this->attrMode == SelectAttrMode::multiple) {
            text_->hide();
            tags_->show();
        } else {
            text_->show();
            tags_->hide();
        }
        input_->setVisible(this->attrMode == SelectAttrMode::tags);
        selectWidget_->setFixedWidth(this->width());
        auto fontSize = themeConfig.fontSize;
        this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadius) + "px");
        if (this->attrSize == GeneralAttrSize::small) {
            fixedHeight = themeConfig.controlHeightSM;
            fontSize = themeConfig.fontSizeSM;
            this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadiusSM) + "px");
        } else if (this->attrSize == GeneralAttrSize::large) {
            fixedHeight = themeConfig.controlHeightLG;
            fontSize = themeConfig.fontSizeLG;
            this->setStyleQss("border-radius", std::to_string(themeConfig.borderRadiusLG) + "px");
        }
        this->setMinimumHeight((int) fixedHeight);
        for (auto it: this->tagList_) {
            it->setContentsMargins(1, 1, 1, 1);
            //    it->setFixedHeight((int) fixedHeight - 8);
        }
        auto font = QFont();
        font.setPixelSize((int) fontSize);
        input_->setFont(font);
        input_->setFixedHeight((int) fixedHeight);
        input_->setStyleSheet("border:none;");
        this->setContentsMargins(1, 1, 1, 1);
        this->setStyleSheet(this->getJoinStyles());
    }

    void Select::paintEvent(QPaintEvent *event) {
        HWidget::paintEvent(event);
    }

    void Select::setAttrOptions(const SelectAttrOptions &selectAttrOptions) {
        this->attrOptions = selectAttrOptions;
        this->selectActionOptions.clear();
        for (const auto &it: selectAttrOptions) {
            this->selectActionOptions.emplace_back(it);
        }
        auto op = SelectActionOption();
        op.isEditing = true;
        op.isHide = true;
        this->selectActionOptions.emplace_back(op);

        if (this->selectWidget_ != nullptr) {
            this->selectWidget_->renderOptions(selectActionOptions);
        }
    }

    void Select::resizeEvent(QResizeEvent *event) {
        HWidget::resizeEvent(event);
        // TODO 判断如果下部区域显示不下，显示在上部区域
        //  auto oldPos = QPoint(selectWidget_->geometry().x(), selectWidget_->geometry().y());
        this->updateSelectWidgetPos();
        //        selectWidget_->move(newPos - oldPos);
        LOG_INFO("size:" << event->size().width() << "," << event->size().height())
        //  LOG_INFO("oldPos:" << oldPos.x() << "," << oldPos.y())
//        selectWidget_->move()
        selectWidget_->renderOptions(this->selectActionOptions);
        this->updateAttr();
        LOG_INFO("resize")
    }

    void Select::setAttrMode(SelectAttrMode mode) {
        Select::attrMode = mode;
    }

    void Select::onSelectItemClicked(const QString &val) {
        QString editingText = "";
        for (auto &it: this->selectActionOptions) {
            if (val != it.value) {
                continue;
            }
            it.selected = !it.selected;
            // 编辑的选项
            if (it.isEditing) {
                it.isHide = false;
                // 转为正式的
                it.isEditing = false;
                it.isTmp = true;
                it.selected = true;
                editingText = val;
                input_->setText("");
            }
            if (it.selected) {
                this->text_->setText(QString::fromStdWString(it.label));
                auto find = false;
                for (const auto &it2: this->selectedValues) {
                    if (val == it2.value) {
                        find = true;
                        break;
                    }
                }
                if (!find) {
                    this->selectedValues.emplace_back(it);
                }
                emit onSelect(val);
                {
                    auto tag = new Tag(val);
                    tag->setAttrCloseIcon(new Icon("CloseOutlined", tag->getPrimaryColor()));
                    tag->setFixedHeight(this->input_->height());
                    LOG_INFO(this->input_->height())
                    connect(tag, &wl::Tag::closed, this, [this, val]() {
                        LOG_ERROR("onclose clicked")
                        this->selectChildrenHandleClick = true;
//                        this->selectHandleClick = true;
                        this->deleteSelected(val);
                        selectWidget_->updateRenderOptions(this->selectActionOptions);
                        emit onDeselect(val);
                    });
                    tag->setProperty("value", val);
                    tagList_.push_back(tag);
                    this->tags_->insertWidget(tagList_.size() - 1, tag);
                }
            } else {
                emit onDeselect(val);
                this->deleteSelected(val);
                selectWidget_->renderOptions(this->selectActionOptions);
                return;

            }
        }
        if (!editingText.isEmpty()) {
            auto op = SelectActionOption();
            op.isEditing = true;
            op.isHide = true;
            this->selectActionOptions.push_back(op);
            for (auto &it: this->selectActionOptions) {
                if (!it.isEditing) { it.isHide = false; }
            }
            selectWidget_->renderOptions(this->selectActionOptions);
        } else {
            selectWidget_->updateRenderOptions(this->selectActionOptions);
        }
    }

    SelectAttrMode Select::getAttrMode() const {
        return attrMode;
    }

    void Select::deleteSelected(const QString &val) {
        LOG_ERROR("delete:" << val.toStdString())
        this->text_->setText("");
        for (auto it2 = selectedValues.begin(); it2 != selectedValues.end();) {
            if (val == it2->value) {
                it2 = selectedValues.erase(it2);
            } else {
                ++it2;
            }
        }
        if (this->attrMode == SelectAttrMode::multiple || this->attrMode == SelectAttrMode::tags) {
            for (auto it2 = tagList_.begin(); it2 != tagList_.end();) {
                auto valTmp = (*it2)->property("value").toString();
                if (valTmp == val) {
                    (*it2)->setParent(nullptr);
                    this->tags_->removeWidget(*it2, false);
                    it2 = tagList_.erase(it2);
                } else {
                    ++it2;
                }
            }
        }
        for (auto it = selectActionOptions.begin(); it != selectActionOptions.end();) {
//        for (auto &it: this->selectActionOptions) {
            if (it->value == val) {
                it->selected = false;
            }
            if (it->isTmp) {
                it = selectActionOptions.erase(it);
            } else {
                ++it;
            }
        }
    }

    void Select::init() {
        selectWidget_ = new SelectWidget();
        selectWidget_->setWindowFlags(Qt::Popup);
        selectWidget_->hide();
        selectWidget_->shouldHide = [this](QPoint p) {
            if (geometry().contains(this->mapToParent(this->mapFromGlobal(p)))) {
                this->focus_ = true;
                selectChildrenHandleClick = false;
                this->mouseClick(p);
                this->selectHandleClick = true;
                if (!this->selectChildrenHandleClick) {
                    this->focus_ = false;
                    return true;
                }
                return false;
            } else {
                this->focus_ = false;
                input_->releaseKeyboard();
                return true;
            }
        };
        connect(selectWidget_, &SelectWidget::blankSpaceClicked, this, [this](QPoint p) {
            if (geometry().contains(this->mapFromGlobal(p))) {
                LOG_INFO("in select base")
            } else {
                this->focus_ = false;
            }
        });
        selectWidget_->renderOptions(this->selectActionOptions);
        connect(selectWidget_, &SelectWidget::selectItemClicked, this, &Select::onSelectItemClicked);

        auto themeConfig = ThemeConfig::Instance();
        this->setStyleQss("border", "1px solid " + themeConfig.colorBorder);
        this->setStyleQss("hover", "border", "1px solid " + themeConfig.hoverBorderColor);
        InputAttr inputAttr;
        input_ = new WLQLineEdit();
        connect(input_, &WLQLineEdit::textChanged, this, [this](const QString &text) {
            if (text.isEmpty()) {
                return;
            }
            for (auto &it: this->selectActionOptions) {
                if (it.isEditing) {
                    it.isHide = false;
                    it.value = text.toStdWString();
                    it.label = text.toStdWString();
                }
                if (it.value.find(text.toStdWString()) == std::wstring::npos) {
                    it.isHide = true;
                } else {
                    it.isHide = false;
                }
            }
            selectWidget_->updateRenderOptions(this->selectActionOptions);
            selectWidget_->show();
            // TODO 改变位置

        });
        text_ = new Text("");
        tags_ = new Flex();
        tags_->setStyleQss("border", "none");

        tags_->addWidget(input_);
        tags_->setStyleSheet(tags_->getJoinStyles());
        rightIcon_ = new HWidget();
        rightIcon_->setFixedSize(12, 12);
        rightIcon_->setStyleQss("border", "none");
        rightIcon_->setStyleSheet(rightIcon_->getJoinStyles());

        text_->setFixed();
        this->addWidget(text_);
        this->addWidget(tags_);
        this->addWidget(rightIcon_);
        this->setVisible(true);
        isFirstShow_ = true;
        this->updateAttr();
    }

    void Select::updateSelectWidgetPos() {
        auto newPos = QPoint(this->mapToGlobal(QPoint(0, 0)).x(),
                             this->mapToGlobal(QPoint(0, 0)).y() + this->height() + 2);
        selectWidget_->setGeometry(QRect(newPos.x(), newPos.y(), this->width(), this->selectHeight));
    }
}
