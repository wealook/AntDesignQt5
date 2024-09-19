#pragma  once

#include "QCheckBox"
#include "AWidget.h"
#include "GeneralAttr.h"
#include "HWidget.h"
#include "Text.h"

namespace wl {

    class RectCheck : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit RectCheck(QWidget *parent = nullptr);

        void paintEvent(QPaintEvent *event) override;

        void setState(int state) {
            this->state = state;
        }

        int getState() const;

        void leaveEvent(QEvent *event) override {
            this->mousePress = false;
        }

        void mousePressEvent(QMouseEvent *event) override {
            this->mousePress = true;
        }

        void mouseReleaseEvent(QMouseEvent *event) override {
            if (this->mousePress) {
//                if (this->clickCB) {
//                    this->clickCB();
//                }
                emit clicked();
            }
            this->mousePress = false;
        }

    signals:

        void clicked();

    private:
        // 0 默认未选择状态  1 选择  2 半选状态
        int state = 0;
        bool mousePress = false;
    };


    class CheckBox : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit CheckBox(QWidget *parent = nullptr);

        explicit CheckBox(const QString &text, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        void updateAttr();

    protected slots:

        void onClicked();

    signals:

        void onChange(bool val);

    private:
        HWidget *textWidget_ = nullptr;
        Text *text_ = nullptr;
        RectCheck *rectCheck_ = nullptr;
    private:
        bool attrChecked = false;
        bool attrDefaultChecked = false;
        bool attrDisabled = false;
        bool attrIndeterminate = false;
        QString attrText;

    public:

        const QString &getAttrText() const;

        void setAttrChecked(bool checked);

        void setAttrDefaultChecked(bool defaultChecked);

        void setAttrDisabled(bool disabled);

        void setAttrIndeterminate(bool attrIndeterminate);

        void setAttrText(const QString &attrText);

    };

    class CheckBoxGroup : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit CheckBoxGroup(const std::vector<GeneralAttrOption> &options, const std::vector<QString> &value, QWidget *parent = nullptr);


    private:
        std::vector<GeneralAttrOption> attrOptions;
        std::vector<QString> attrValue;
    public:
        void setAttrOptions(const std::vector<GeneralAttrOption> &attrOptions);

        void setAttrValue(const std::vector<QString> &attrValue);

    signals:

        void onChange(const std::vector<QString> &attrValue);
    };


}



