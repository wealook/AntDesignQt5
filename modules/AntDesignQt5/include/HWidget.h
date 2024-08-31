#pragma  once

#include "QWidget"
#include "functional"
#include "AWidget.h"

namespace wl {
/**
 *  自带水平布局的widget
 */
    class HWidget : public QWidget, public AWidget {
    Q_OBJECT
    public:
        explicit HWidget(QWidget *parent = nullptr, bool spacer = false);

        ~HWidget() override = default;

        void paintEvent(QPaintEvent *event) override;

        virtual void addWidget(QWidget *wid);

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
    private:
        bool globalHover = true;
    protected:
        std::vector<std::string> globalHoverAttributes;
    public:
        bool isGlobalHover() const;

        void setGlobalHover(bool globalHover);

    signals:

        void clicked();
    };
}


