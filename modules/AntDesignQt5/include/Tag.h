#pragma  once

#include "AWidget.h"
#include "HWidget.h"
#include "GeneralAttr.h"
#include "Text.h"

namespace wl {

//    class TagAttr {
//    public:
//        QWidget *icon = nullptr;
//        QWidget *closeIcon = nullptr;
//        bool bordered = true;
//        std::function<bool()> onClose;
//        GeneralAttrColorType color;
//        QString text;
//    };

    class Tag : public HWidget {

    Q_OBJECT
    public:
        explicit Tag(QString text, QWidget *parent = nullptr);

        void updateAttr();

    signals:

        void closed();

    private:
//        TagAttr attr;

        HWidget *icon_;
        Text *text_;
        HWidget *iconClose_;


        std::string mainColor_;
    private:
        QWidget *attrIcon = nullptr;
        QWidget *attrCloseIcon = nullptr;
        bool attrBordered = true;
        std::function<bool()> onClose;
        GeneralAttrColorType attrColor = GeneralAttrColorType::none;
        QString attrText;
    public:
        void setAttrIcon(QWidget *icon);

        void setAttrBordered(bool attrBordered);

        void setAttrColor(GeneralAttrColorType attrColor);

        GeneralAttrColorType getAttrColor() const;

        void setAttrText(const QString &attrText);

        void setAttrCloseIcon(QWidget *icon);

        void setOnClose(const std::function<bool()> &close);

        QColor getPrimaryColor();

    };

}
