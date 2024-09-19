#pragma  once

#include "QWidget"
#include "HWidget.h"
#include "Text.h"

namespace wl {
    enum class DividerAttrOrientation {
        left,
        right,
        center
    };
    enum class DividerAttrType {
        horizontal,
        vertical,
    };
    class Divider : public QWidget {

    public:
        static Divider *createLeft(const QString &text);

        explicit Divider(bool vertical = false, QWidget *parent = nullptr);

        explicit Divider(const QString &text, QWidget *parent = nullptr);

        explicit Divider(const QString &text, DividerAttrOrientation orientation, QWidget *parent = nullptr);

        explicit Divider(QWidget *children, DividerAttrOrientation orientation, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        void updateAttr();

    protected:
        HWidget *childrenWidget_ = nullptr;
        Text *text_ = nullptr;
        QWidget *left_ = nullptr;
        QWidget *right_ = nullptr;
    private:

        QString attrChildrenText = "";
        QWidget *attrChildren = nullptr;
        bool attrDashed = false;
        DividerAttrOrientation attrOrientation = DividerAttrOrientation::center;
        GeneralAttrTypeDirection attrType = GeneralAttrTypeDirection::horizontal;

    public:

        void setAttrChildrenText(const QString &childrenText);

        void setAttrChildren(QWidget *children);

        void setAttrDashed(bool dashed);

        void setAttrOrientation(DividerAttrOrientation orientation);

    };


}


