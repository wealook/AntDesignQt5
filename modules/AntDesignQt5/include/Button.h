#pragma  once

#include "ButtonAttr.h"
#include <QPushButton>
#include "AWidget.h"
#include "QWidget"
#include "Icon.h"
#include "QLabel"

namespace wl {
    class Button : public HWidget {
    public:


        explicit Button(const QString &text, QWidget *parent = nullptr);

        void paintEvent(QPaintEvent *event) override;

        void enterEvent(QEvent *event) override;

        void leaveEvent(QEvent *event) override;

        void updateAttr();

        void mouseMoveEvent(QMouseEvent *e) override;

    private:
        QLabel *label_ = nullptr;
        wl::Icon *icon_ = nullptr;
        wl::HWidget *iconWidget_ = nullptr;

    private:
        ButtonAttrType attrType = ButtonAttrType::primary;
        bool attrLoading = false;
        bool attrBlock = false;
        bool attrDisabled = false;
        bool attrDanger = false;
        GeneralAttrSize attrSize = GeneralAttrSize::middle;
        GeneralAttrShape attrShape = GeneralAttrShape::none;
        std::optional<IconSvg> attrIcon;
        ButtonAttrIconPosition attrIconPosition = ButtonAttrIconPosition::prefix;

    public:
        void setAttrType(ButtonAttrType buttonAttrType);

        void setAttrLoading(bool loading);

        void setAttrBlock(bool blck);

        void setAttrDisabled(bool disabled);

        void setAttrDanger(bool danger);

        void setAttrSize(GeneralAttrSize size);

        void setAttrShape(GeneralAttrShape generalAttrShape);

        void setAttrIcon(const std::optional<IconSvg> &icon);

        void setAttrIconPosition(ButtonAttrIconPosition position);
    };
}


