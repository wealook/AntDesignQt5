#pragma  once

#include "QLineEdit"
#include "QFocusEvent"
#include "QEvent"

namespace wl {

    class WLQLineEdit : public QLineEdit {


    public:
    Q_OBJECT
    public:
        WLQLineEdit(QWidget *parent = nullptr);

        void focusInEvent(QFocusEvent *e) override;

        void focusOutEvent(QFocusEvent *e) override;

        QSize WLQLineEdit::sizeHint() const override;

        void resizeEvent(QResizeEvent *event) override;

    Q_SIGNALS:

        void focusChange(QFocusEvent *);
    };

}



