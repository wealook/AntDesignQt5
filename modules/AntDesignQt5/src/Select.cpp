
#include <QHBoxLayout>
#include <QLineEdit>
#include "Select.h"
#include <QPushButton>
#include <QComboBox>
#include <QApplication>
#include <QScrollBar>
#include "ThemeConfig.h"
#include <QMouseEvent>
#include <QLabel>

#include <QPushButton>

namespace wl {
    QWidget *getTopLevelWidget(QWidget * widget) {
        while (widget && widget->parentWidget()) {
            widget = widget->parentWidget();
        }
        return widget;
    }

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

    }

    void SelectArea::mousePressEvent(QMouseEvent *event) {
//        emit areaClicked();
        LOG_INFO("SelectArea::mousePressEvent")
        QScrollArea::mousePressEvent(event);
    }

    void SelectArea::mouseReleaseEvent(QMouseEvent *event) {
        LOG_INFO("SelectArea::mouseReleaseEvent")
        QScrollArea::mouseReleaseEvent(event);
    }

    bool SelectArea::eventFilter(QObject *watched, QEvent *event) {
//        emit areaClicked();
        //   LOG_INFO("SelectArea::eventFilter:" << event->type())
//        return QAbstractItemView::eventFilter(watched, event);
        return false;
    }

    bool SelectArea::event(QEvent *e) {
        if (e->type() == QEvent::MouseButtonPress) {
            auto event = (QMouseEvent *) e;
            if (event->button() == Qt::LeftButton) {
                // 判断点击坐标是否在窗口内容区之外
                if (!geometry().contains(event->pos())) {
                    auto gP = this->mapToGlobal(event->pos());
                    LOG_INFO("gp:" << gP.x() << "," << gP.y())
//                    this->hide();
//                    return false;
                    emit blankSpaceClicked(gP);
                    // 处理空白位置的点击事件
                }
            }
        }
        return QScrollArea::event(e);
    };

    Select::Select(QWidget *parent) : QWidget(parent) {
        setFocusPolicy(Qt::ClickFocus);
        base_ = new QWidget(this);
//        selectWidget_ = new SelectArea(getTopLevelWidget(base_));
        selectWidget_ = new SelectArea(base_);
        selectWidget_->setWindowFlags(Qt::Popup);
//        selectWidget_->setAttribute(Qt::WA_TranslucentBackground);
        selectWidget_->show();
        auto themeConfig = ThemeConfig::Instance();
        auto str = ":!hover{border: 1px solid " + themeConfig.colorBorder + ";}:hover{border: 1px solid  " + themeConfig.colorBorder + ";}        ";
        selectWidget_->setStyleSheet(QString::fromStdString(str));
        connect(selectWidget_, SIGNAL(areaClicked()), this, SLOT(areaClicked()));
        connect(selectWidget_, SIGNAL(blankSpaceClicked(QPoint)), this, SLOT(OnBlankSpaceClicked(QPoint)));
        this->installEventFilter(selectWidget_);
        this->setVisible(true);
    }

    const SelectAttr &Select::getAttr() const {
        return attr;
    }

    void Select::setAttr(const SelectAttr &selectAttr) {
        auto themeConfig = ThemeConfig::Instance();
        this->attr = selectAttr;

        this->setFixedWidth(this->attr.fixedWidth);
        this->setFixedHeight(30);

        base_->setFixedWidth(this->attr.fixedWidth);
        base_->setFixedHeight(30);
        base_->setGeometry(QRect(0, 0, base_->width(), base_->height()));

        auto str =
                ":!hover{border: 1px solid " + themeConfig.colorBorder + ";background-color:" + themeConfig.colorBgBase + ";}:hover{border: 1px solid  " +
                themeConfig.colorPrimary +
                ";}";
        base_->setStyleSheet(QString::fromStdString(str));
        base_->setVisible(true);


        this->initFixedShowArea();
        this->initSelectOptionsArea();
    }

    void Select::focusInEvent(QFocusEvent *event) {
        QWidget::focusInEvent(event);
    }

    void Select::focusOutEvent(QFocusEvent *event) {
        QWidget::focusOutEvent(event);
    }

    void Select::areaClicked() {
    }


    void Select::mousePressEvent(QMouseEvent *event) {
        LOG_INFO("mousePressEvent")
//        LOG_INFO(this->pos().x());
//        LOG_INFO(this->pos().y());
//        LOG_INFO(this->mapToGlobal(QPoint(0, 0)).x())
//        LOG_INFO(this->mapToGlobal(QPoint(0, 0)).y())
        selectWidget_->setGeometry(QRect(this->mapToGlobal(QPoint(0, 0)).x(), this->mapToGlobal(QPoint(0, 0)).y() + this->height() + 2,
                                         this->attr.fixedWidth, this->attr.selectHeight));

        if (selectWidget_->isHidden()) {
            if (!lastHiddenInFixedArea) {
                selectWidget_->show();
            }
        } else {
            selectWidget_->hide();
        }
        lastHiddenInFixedArea = false;
//        selectWidget_->show();
//        if (selectWidget_->isHidden()) {
//            selectWidget_->show();
//        } else {
//            selectWidget_->hide();
//        }
        QWidget::mousePressEvent(event);
    }

    void Select::mouseReleaseEvent(QMouseEvent *event) {
        LOG_INFO("mouseReleaseEvent")
        QWidget::mouseReleaseEvent(event);
    }

    bool Select::eventFilter(QObject *watched, QEvent *event) {
        return QObject::eventFilter(watched, event);
    }

    void Select::initFixedShowArea() {
        QLayout *layout;
        auto *oldLayout = base_->layout();
        if (oldLayout != nullptr) {
            QLayoutItem *child;
            while ((child = oldLayout->takeAt(0)) != nullptr) {
                if (child->widget()) {
                    child->widget()->setParent(nullptr);//setParent(nullptr),防止删除之后界面不消失
                    delete child->widget();  //释放
                }
                delete child;
            }
            layout = oldLayout;
        } else {
            layout = new QHBoxLayout(base_);

        }
        base_->setLayout(layout);
        auto *spacerItem = new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Minimum);

        layout->setMargin(0);
        layout->setSpacing(0);
        if (!this->selectedValues.empty()) {
            auto *label = new QLabel(base_);
            label->setText(QString::fromStdWString(this->selectedValues[0].label));
            label->setStyleSheet(":!hover{color:rgba(0,0,0,0.88);font-size:22px;}");

            layout->addWidget(label);
        }

//        auto *edit = new QLineEdit(base_);
//        edit->setFixedWidth(60);
//        edit->installEventFilter(this);
//        layout->addWidget(edit);

        layout->addItem(spacerItem);
    }

    void Select::initSelectOptionsArea() {
        auto *oldWidget = this->selectWidget_->widget();
        if (oldWidget != nullptr) {
            oldWidget->setParent(nullptr);
            delete oldWidget;
        }
        auto *widget = new QWidget();
        auto *layout = new QVBoxLayout(widget);

        auto themeConfig = ThemeConfig::Instance();
        for (auto &it: this->attr.options) {
            auto *label = new QPushButton(QString::fromStdWString(it.label));

            bool select = false;
            for (const auto &it2: this->selectedValues) {
                if (it2.value == it.value) {
                    select = true;
                    break;
                }
            }
            if (select) {
                label->setStyleSheet(
                        QString::fromStdString(
                                " :!hover{border:none; background-color:" + themeConfig.colorPrimaryBg + "; font-size:24px; line-height:28px;}"  \
                        "  :hover{border:none; background-color:" + themeConfig.colorPrimaryBg + ";}"
                        ));
            } else {
                label->setStyleSheet(R"(
    :!hover{border:none; background-color:rgb(255,255,255); font-size:24px; line-height:28px;}
    :hover{border:none; background-color:rgb(245,245,245);}
)");
            }

            label->setProperty("option_label", QString::fromStdWString(it.label));
            label->setProperty("option_value", QString::fromStdWString(it.value));
            connect(label, SIGNAL(clicked()), this, SLOT(selectItemClicked()));
            layout->addWidget(label);
        }
        widget->setFixedWidth(this->attr.fixedWidth - 10);
        auto *verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);
        layout->addItem(verticalSpacer);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
//        layout->addStretch();
        this->selectWidget_->setWidget(widget);

    }

    void Select::selectItemClicked() {
        auto *btn = (QPushButton *) sender();
        if (btn == nullptr) {
            return;
        }
        auto val = btn->property("option_value").toString().toStdWString();
        LOG_INFO("aaa << " << btn->property("option_value").toString().toStdString());
        this->selectedValues.clear();
        this->selectedValues.emplace_back(btn->property("option_label").toString().toStdWString(), btn->property("option_value").toString().toStdWString());
        this->initFixedShowArea();
        emit onSelect(btn->property("option_value").toString());
        selectWidget_->hide();
        // 改为手动选择然后改变css
        this->initSelectOptionsArea();
    }

    void Select::OnBlankSpaceClicked(QPoint p) {
        auto gp = this->mapToGlobal(QPoint(0, 0));
        auto p2 = p - gp;
        LOG_INFO("p2:" << p2.x() << "," << p2.y())
        if (!this->geometry().contains(p2) && !base_->geometry().contains(p2)) {
            LOG_INFO("not contain")
            selectWidget_->hide();
            lastHiddenInFixedArea = false;
        } else {
            lastHiddenInFixedArea = true;
            selectWidget_->hide();
            LOG_INFO(" contain")
        }
    }
}