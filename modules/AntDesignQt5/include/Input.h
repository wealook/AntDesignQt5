#pragma  once

#include <QWidget>
#include <vector>
#include "AWidget.h"
#include "InputAttr.h"
#include "HWidget.h"

namespace wl {

    class Input : public QWidget, public AWidget {

    public:
    Q_OBJECT
    public:

        explicit Input(QWidget *parent = nullptr);

        explicit Input(const InputAttr &inputAttr, QWidget *parent = nullptr);

        const InputAttr &getAttr() const;

        void setAttr(const InputAttr &inputAttr);

    protected       slots:


        void editFocusChange(QFocusEvent *e);


    private:
        InputAttr attr;

        bool editFocus = false;

        HWidget* editWidget;
    };

}

