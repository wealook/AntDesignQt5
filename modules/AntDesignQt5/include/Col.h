#pragma  once

#include "QWidget"
#include "AWidget.h"
#include "vector"
#include "ColAttr.h"

namespace wl {
    class Col : public QWidget, public AWidget {

    public:
        explicit Col(QWidget *parent = nullptr);

        explicit Col(const QString &txt, QWidget *parent = nullptr);

        void setContentWidget(QWidget *wid);

        void resizeEvent(QResizeEvent *event) override;

    private:

//        std::vector<QWidget *> contentWidgets_;
        QWidget *contentWidget_ = nullptr;
        ColAttr attr;
    public:
        const ColAttr &getAttr() const;

        void setAttr(const ColAttr &colAttr);
    };
}



