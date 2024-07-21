#pragma  once

#include <QWidget>
#include "AWidget.h"
#include "SelectAttr.h"
#include <QListWidget>
#include <QScrollArea>

namespace wl {


    class SelectArea : public QScrollArea, public AWidget {
    Q_OBJECT

    public:

        explicit SelectArea(QWidget *parent = nullptr);

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

        bool eventFilter(QObject *watched, QEvent *event) override;

        bool event(QEvent *) override;

    signals:

        void areaClicked();

        void blankSpaceClicked(QPoint);
    };

    class Select : public QWidget, public AWidget {
    Q_OBJECT

    public:

        explicit Select(QWidget *parent = nullptr);

        [[nodiscard]] const SelectAttr &getAttr() const;

        void setAttr(const SelectAttr &selectAttr);

        void focusInEvent(QFocusEvent *event) override;

        void focusOutEvent(QFocusEvent *event) override;

        void mousePressEvent(QMouseEvent *event) override;

        void mouseReleaseEvent(QMouseEvent *event) override;

        bool eventFilter(QObject *watched, QEvent *event) override;

    signals:

        void onSelect(QString val);

    public slots:


        void areaClicked();

        void selectItemClicked();

        void OnBlankSpaceClicked(QPoint);


    private:
        void initSelectOptionsArea();

        void initFixedShowArea();

    private:
        SelectAttr attr;
        SelectArea *selectWidget_ = nullptr;
        QWidget *base_ = nullptr;
        std::vector<SelectAttrOption> selectedValues;

        bool lastHiddenInFixedArea = false;

    };


}
