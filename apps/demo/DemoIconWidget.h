#pragma once

#include "QWidget"
#include "thread"
#include "Icon.h"

class DemoIconWidget : public QWidget {

Q_OBJECT
public:
    DemoIconWidget(QWidget *parent = nullptr);

    ~DemoIconWidget();


private:
    std::shared_ptr<std::thread> thread_;
    bool working_ = false;
    std::vector<QWidget *> widgets_;
    std::vector<wl::Icon *> icons_;
    std::vector<std::string> files_;

};


