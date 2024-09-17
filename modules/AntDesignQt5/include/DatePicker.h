#pragma once

#include "QDateTime"
#include "HWidget.h"
#include "VWidget.h"
#include "Icon.h"
#include "Text.h"

namespace wl {


    enum class DatePickerPicker {
        date, week, month, quarter, year
    };

    class DateSelectPanelHeader : public HWidget {

    public:
        explicit DateSelectPanelHeader(QWidget *parent = nullptr);

    private:
        Icon *iconLeft_;
        Icon *iconDoubleLeft_;
        Icon *iconRight_;
        Icon *iconDoubleRight_;
        Text *text_;
    };

    class DateSelectPanelContent : public HWidget {

    public:
        explicit DateSelectPanelContent(QWidget *parent = nullptr);

        void updateAttr();

    private:
        QDateTime currentDateTime_;
    };

    class DateSelectPanel : public VWidget {

    public:
        explicit DateSelectPanel(QWidget *parent = nullptr);

    private:

        DateSelectPanelHeader *header_;
        DateSelectPanelContent *content_;
    };

    class DatePicker : public HWidget {

    public:
        explicit DatePicker(QWidget *parent = nullptr);
    };


}
