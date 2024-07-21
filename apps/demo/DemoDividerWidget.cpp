//
 ///7/10.
//

#include "DemoDividerWidget.h"
#include "QPushButton"
#include "QDateTimeEdit"

DemoDividerWidget::DemoDividerWidget(QWidget *parent) : DemoContentWidget(parent) {

    this->layoutLeft_->addWidget(new QPushButton("测试1"));
    this->layoutLeft_->addWidget(new QPushButton("测试1"));
    this->layoutLeft_->addWidget(new QPushButton("测试1"));
    this->layoutLeft_->addWidget(new QPushButton("测试1"));
    this->layoutRight_->addWidget(new QPushButton("测试2"));
    this->layoutRight_->addWidget(new QPushButton("测试2"));
    this->layoutRight_->addWidget(new QPushButton("测试2"));
    this->layoutRight_->addWidget(new QPushButton("测试2"));
    auto dateTimeEdit = new QDateTimeEdit();
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

    // 设置日期时间选择模式为日期和时间
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    dateTimeEdit->setCalendarPopup(true); // 设置为弹出日历选择日期
    dateTimeEdit->setTimeSpec(Qt::UTC); // 设置时间标准，例如UTC或本地时间
    dateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365)); // 设置最小日期
    dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365)); // 设置最大日期
    this->layoutRight_->addWidget(dateTimeEdit);
}
