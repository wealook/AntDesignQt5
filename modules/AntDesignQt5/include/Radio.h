#pragma  once

#include "AWidget.h"
#include "GeneralAttr.h"
#include "HWidget.h"
#include "Text.h"

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


    class Radio : public QWidget, public AWidget {
    Q_OBJECT
    public:

        explicit Radio(const QString &text, QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;


        void updateAttr();

    protected slots:

        void onClicked();

    signals:

        void onChange(bool val);

    private:
        RoundRadio *roundRadio_ = nullptr;
        HWidget *textWidget_ = nullptr;
        Text *text_ = nullptr;
    private:
//        RadioAttr attr;
        std::optional<bool> attrChecked;
        bool attrDefaultChecked = false;
        bool attrDisabled = false;
        QString attrText;
    public:
        const QString &getAttrText() const;

        void setAttrChecked(bool checked);

        void setAttrDefaultChecked(bool defaultChecked);

        void setAttrDisabled(bool disabled);

        void setAttrText(const QString &text);

    };

    class RadioGroup : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit RadioGroup(const std::vector<GeneralAttrOption> &attrOptions, QString attrValue, QWidget *parent = nullptr);

    signals:

        void onChange(QString val);

    private:
        std::vector<GeneralAttrOption> attrOptions;
        QString attrValue;
        std::vector<Radio *> radioList_;
    };


}

