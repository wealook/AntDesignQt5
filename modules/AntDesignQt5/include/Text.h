#pragma  once

#include "QWidget"
#include "TextAttr.h"
#include "HWidget.h"
#include "QLabel"

namespace wl {

    class Text : public HWidget {
    Q_OBJECT
    public:
        explicit Text(const QString &text, QWidget *parent = nullptr);

        explicit Text(const QString &text, const TextAttr &textAttr, QWidget *parent = nullptr);

        void setAttr(const TextAttr &textAttr);
        void updateAttr();

        void mousePressEvent(QMouseEvent *event) override;

        void paintEvent(QPaintEvent *event) override;

        void setText(const QString &text);

        QString getText();

    signals:

        void clicked();

    private:
        QLabel *label_;
        TextAttr attr_;


    };

}



