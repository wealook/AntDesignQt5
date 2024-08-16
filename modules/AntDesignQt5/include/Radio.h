#pragma  once

#include "AWidget.h"
#include "GeneralAttr.h"


namespace wl {

    class RoundRadio : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit RoundRadio(QWidget *parent = nullptr);

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
        // 0 默认未选择状态  1 选择
        int state = 0;
        bool mousePress = false;
    };


    class RadioAttr {

    public:
        explicit RadioAttr(QString text, bool defaultChecked = false, bool disabled = false)
                : text(text), defaultChecked(defaultChecked), disabled(disabled) {

        }

        bool checked = false;
        bool defaultChecked = false;
        bool disabled = false;
        QString text;
    };

    class RadioGroupAttr {
    public:
        std::vector<GeneralAttrOption> options;
        std::vector<QString> value;
    };

    class Radio : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit Radio(const RadioAttr &attr, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;


    protected slots:

        void onClicked();

    private:
        RadioAttr attr;


    };

    class RadioGroup : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit RadioGroup(const RadioGroupAttr &attr, QWidget *parent = nullptr);

    private:
        RadioGroupAttr attr;
    };


}

