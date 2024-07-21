#pragma  once

#include <QWidget>
#include <vector>
#include "AWidget.h"
#include "InputAttr.h"

namespace wl {

    class Input : public QWidget, public AWidget {

    public:

        explicit Input(QWidget *parent = nullptr);

        const InputAttr &getAttr() const;

        void setAttr(const InputAttr &inputAttr);

    protected :

    private:
        InputAttr attr;
    };

}

