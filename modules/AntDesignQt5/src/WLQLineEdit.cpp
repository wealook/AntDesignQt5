
#include "WLQLineEdit.h"
#include "logger.h"

namespace wl {

    WLQLineEdit::WLQLineEdit(QWidget *parent) : QLineEdit(parent) {

        connect(this, &WLQLineEdit::textChanged, this, [this](const QString &text) {
            this->updateGeometry();
        });
    }

    void WLQLineEdit::focusInEvent(QFocusEvent *e) {
        QLineEdit::focusInEvent(e);
        emit focusChange(e);
    }

    void WLQLineEdit::focusOutEvent(QFocusEvent *e) {
        QLineEdit::focusOutEvent(e);
        emit focusChange(e);
    }

    QSize WLQLineEdit::sizeHint() const {
        auto si = QLineEdit::sizeHint();
        QFontMetrics fontMetrics(this->font());
        int charWidth = fontMetrics.horizontalAdvance(this->text());
        return {charWidth + 5, si.height()};
    }

    void WLQLineEdit::resizeEvent(QResizeEvent *event) {
        QWidget::resizeEvent(event);
    }
}