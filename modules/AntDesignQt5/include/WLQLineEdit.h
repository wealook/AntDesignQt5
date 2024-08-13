#pragma  once

#include "QLineEdit"
#include "QFocusEvent"

namespace wl {

    class WLQLineEdit : public QLineEdit {


    public:
    Q_OBJECT
    public:
        WLQLineEdit(QWidget *parent = nullptr);

        void focusInEvent(QFocusEvent * e) override;

        void focusOutEvent(QFocusEvent * e) override;


    Q_SIGNALS:

        void focusChange(QFocusEvent *);
    };

}



