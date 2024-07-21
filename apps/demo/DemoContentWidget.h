#pragma  once

#include "QWidget"
#include "QLayout"
#include "QScrollArea"

//class DemoContentWidget : public QScrollArea {
class DemoContentWidget : public QWidget {

public:
    explicit DemoContentWidget(QWidget *parent = nullptr);

    virtual  ~DemoContentWidget();
    void resizeEvent(QResizeEvent *) override;

protected:

    QLayout *layoutLeft_;
    QLayout *layoutRight_;
};


