#pragma  once

#include <QString>
#include <utility>
#include "QWidget"
#include "GeneralAttr.h"

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

    class DividerAttr {


    public:
        DividerAttr() = default;

        explicit DividerAttr(GeneralAttrTypeDirection type) : type(type) {

        }

        explicit DividerAttr(QString text) : childrenText(std::move(text)) {

        }

        explicit DividerAttr(QString text, DividerAttrOrientation orientation) :
                childrenText(std::move(text)),
                orientation(orientation) {

        }

        explicit DividerAttr(QWidget *wid) : children(wid) {

        }

        explicit DividerAttr(QWidget *wid, DividerAttrOrientation orientation) :
                children(wid),
                orientation(orientation) {

        }

        QString childrenText = "";
        QWidget *children = nullptr;

        bool dashed = false;
        DividerAttrOrientation orientation = DividerAttrOrientation::center;
        GeneralAttrTypeDirection type = GeneralAttrTypeDirection::horizontal;
    };
}