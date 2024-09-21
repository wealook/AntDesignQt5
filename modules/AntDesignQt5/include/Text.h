#pragma  once

#include "QWidget"
#include "HWidget.h"
#include "QLabel"
#include "GeneralAttr.h"
namespace wl {

    class Text : public HWidget {
    Q_OBJECT
    public:
        explicit Text(const QString &text, QWidget *parent = nullptr);


        void updateAttr();

        void mousePressEvent(QMouseEvent *event) override;

        void paintEvent(QPaintEvent *event) override;

        void setText(const QString &text);

        QString getText();

    signals:

        void clicked();

    private:
        QLabel *label_;

    private:
        bool attrMark = false;
        bool attrCode = false;
        bool attrKeyboard = false;
        bool attrUnderline = false;
        bool attrDestroy = false;
        bool attrStrong = false;
        bool attrItalic = false;
        bool attrLink = false;
        int attrFontSize = 14;
        GeneralAttrColorType attrType = GeneralAttrColorType::none;

    public:

        void setAttrMark(bool mark);

        void setAttrCode(bool code);

        void setAttrKeyboard(bool keyboard);

        void setAttrUnderline(bool underline);

        void setAttrDestroy(bool destroy);

        void setAttrStrong(bool strong);

        void setAttrItalic(bool italic);

        void setAttrLink(bool link);

        void setAttrFontSize(int fontSize);

        void setAttrType(GeneralAttrColorType colorType);
    };

}



