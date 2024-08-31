#pragma  once

#include <QWidget>
#include <vector>
#include "AWidget.h"
#include "InputAttr.h"
#include "HWidget.h"
#include "WLQLineEdit.h"

namespace wl {

    class Input : public QWidget, public AWidget {

    public:
    Q_OBJECT
    public:
        explicit Input(const InputAttr &inputAttr, QWidget *parent = nullptr);

        const InputAttr &getAttr() const;

        void setAttr(const InputAttr &inputAttr);

        QSize sizeHint() const override;

    protected       slots:


        void editFocusChange(QFocusEvent *e);

    signals:

        void textChanged(const QString &);

    private:
        InputAttr attr;

        bool editFocus = false;

        HWidget *editWidget;
        WLQLineEdit *edit;
    };

}

