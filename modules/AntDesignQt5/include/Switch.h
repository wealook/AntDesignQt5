#pragma once

#include "AWidget.h"
#include "HWidget.h"
#include "QWidget"
#include "QPushButton"
#include "GeneralAttr.h"

namespace wl {

    class SwitchAttr {
    public:
        bool checked = false;
        QWidget *checkedChildren = nullptr;
        QWidget *unCheckedChildren = nullptr;
        bool disabled = false;
        GeneralAttrSize size = GeneralAttrSize::middle;
    };

    class Switch : public HWidget {
    Q_OBJECT
    public:
        explicit Switch(SwitchAttr attr, QWidget *parent = nullptr);

        void paintEvent(QPaintEvent *event) override;

        void updateAttr(SwitchAttr attr);

    public slots:

        void onClicked();

    signals:

        void changed(bool);

    private:

        SwitchAttr attr;
        HWidget *left = nullptr;
        HWidget *right = nullptr;
        HWidget *center = nullptr;
    };
}
