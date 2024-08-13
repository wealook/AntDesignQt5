
#include "WLQLineEdit.h"


namespace wl {

    WLQLineEdit::WLQLineEdit(QWidget *parent) : QLineEdit(parent) {

    }

    void WLQLineEdit::focusInEvent(QFocusEvent *e) {
        QLineEdit::focusInEvent(e);
        emit focusChange(e);
    }

    void WLQLineEdit::focusOutEvent(QFocusEvent *e) {
        QLineEdit::focusOutEvent(e);
        emit focusChange(e);
    }
}