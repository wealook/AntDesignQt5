#pragma  once

#include "QCheckBox"
#include "AWidget.h"
#include "GeneralAttr.h"

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


    class CheckBoxAttr {

    public:
        explicit CheckBoxAttr(QString text, bool defaultChecked = false, bool indeterminate = false, bool disabled = false)
                : text(text), defaultChecked(defaultChecked), indeterminate(indeterminate), disabled(disabled) {

        }

        bool checked = false;
        bool defaultChecked = false;
        bool disabled = false;
        bool indeterminate = false;
        QString text;
    };

    class CheckBoxGroupAttr {
    public:
        std::vector<GeneralAttrOption> options;
        std::vector<QString> value;
    };

    class CheckBox : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit CheckBox(const CheckBoxAttr &attr, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;


    protected slots:

        void onClicked();

    private:
        CheckBoxAttr attr;


    };

    class CheckBoxGroup : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit CheckBoxGroup(const CheckBoxGroupAttr &attr, QWidget *parent = nullptr);

    private:
        CheckBoxGroupAttr attr;
    };


}



