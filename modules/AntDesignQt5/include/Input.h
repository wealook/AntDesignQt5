#pragma  once

#include <QWidget>
#include <vector>
#include "AWidget.h"
#include "InputAttr.h"
#include "HWidget.h"
#include "WLQLineEdit.h"

namespace wl {

    class Input : public QWidget, public AWidget {

    public:
    Q_OBJECT
    public:
        explicit Input(QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        void updateAttr();

        QSize sizeHint() const override;

    protected slots:


        void editFocusChange(QFocusEvent *e);

    signals:

        void textChanged(const QString &);

    private:

        bool editFocus = false;

        HWidget *editWidget_ = nullptr;
        WLQLineEdit *edit_ = nullptr;
        HWidget *beforeWidget_ = nullptr;
        HWidget *afterWidget_ = nullptr;

        HWidget *prefixWidget_ = nullptr;
        HWidget *suffixWidget_ = nullptr;
    private:
        GeneralAttrSize attrSize = GeneralAttrSize::middle;
        QWidget *attrAddonBefore = nullptr;
        QWidget *attrAddonAfter = nullptr;

        InputAttrStatus attrStatus = InputAttrStatus::none;
        bool attrDisabled = false;
        QWidget *attrPrefix = nullptr;
        QWidget *attrSuffix = nullptr;

        QString attrPlaceholder;
        InputAttrVariant attrVariant = InputAttrVariant::outlined;

    public:
        void setAttrSize(GeneralAttrSize generalAttrSize);

        void setAttrAddonBefore(QWidget *addonBefore);

        void setAttrAddonAfter(QWidget *addonAfter);

        void setAttrStatus(InputAttrStatus status);

        void setAttrDisabled(bool disabled);

        void setAttrPrefix(QWidget *prefix);

        void setAttrSuffix(QWidget *suffix);

        void setAttrPlaceholder(const QString &placeholder);

        void setAttrVariant(InputAttrVariant variant);
    };

}

