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

        explicit Button(QWidget *parent = nullptr);


        explicit Button(const QString &text, const ButtonAttr &aButtonAttr, QWidget *parent = nullptr);


        const ButtonAttr &getButtonAttr() const;

        bool eventFilter(QObject *watched, QEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

        void mouseDoubleClickEvent(QMouseEvent *event) override;

        void enterEvent(QEvent *event) override;

        void leaveEvent(QEvent *event) override;

    protected:
        void setButtonAttr(const ButtonAttr &aButtonAttr);

        void mouseMoveEvent(QMouseEvent *e) override;
    private:
        ButtonAttr buttonAttr;
        QLabel *label_ = nullptr;
        wl::Icon *icon_ = nullptr;
        wl::Icon *iconHover_ = nullptr;
    };
}


