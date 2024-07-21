#pragma  once

#include "QWidget"

class DemoGridWidget : public QWidget {

public:
    DemoGridWidget(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;

};

