#pragma  once

#include "QWidget"
#include "TextAttr.h"
#include "QLabel"

namespace wl {

    class Text : public QWidget {
    Q_OBJECT
    public:
        explicit Text(const QString &text, QWidget *parent = nullptr);

        explicit Text(const QString &text, const TextAttr &textAttr, QWidget *parent = nullptr);

        void setAttr(const TextAttr &textAttr);

        void mousePressEvent(QMouseEvent *event) override;

    signals:

        void clicked();

    private:
        QLabel *label_;
        TextAttr attr_;
    };

}



