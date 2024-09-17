#pragma  once

#include "QWidget"
#include "functional"
#include "AWidget.h"
#include "QSpacerItem"

namespace wl {
/**
 *  自带水平布局的widget
 */
    class HWidget : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit HWidget(QWidget *parent = nullptr, bool spacer = false);

        explicit HWidget(bool vertical, QWidget *parent = nullptr);

        ~HWidget() override = default;

        void paintEvent(QPaintEvent *event) override;

        virtual void addWidget(QWidget *wid);

        virtual void insertWidget(int index, QWidget *wid);

        virtual void addWidget(QSpacerItem *item);

        void replaceWidget(QWidget *newWidget, QWidget *old = nullptr, bool isDelete = false);

        void removeWidget(QWidget *wid, bool isDelete = false);

        void enterEvent(QEvent *event) override;

        void leaveEvent(QEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

        void setFixed();

        void setStyleSheet(const QString &styleSheet);

        void mouseClick(QPoint globalPos);

        std::function<void(QEvent *event)> enterEventCB = nullptr;
        std::function<void(QEvent *event)> leaveEventCB = nullptr;
    protected:
        bool globalHover = true;
        bool vertical = false;
    protected:
        std::vector<std::string> globalHoverAttributes;
    public:
        bool isGlobalHover() const;

        void setGlobalHover(bool globalHover);

        std::vector<std::string> &getGlobalHoverAttributes();

    signals:

        void clicked();

        void mouseEnter();

        void mouseLeave();
    };
}


