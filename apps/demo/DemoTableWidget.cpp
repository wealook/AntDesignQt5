
#include "DemoTableWidget.h"
#include "Table.h"
#include "Card.h"

DemoTableWidget::DemoTableWidget(QWidget *parent) : DemoContentWidget(parent) {
    {
        auto *wi = new wl::VWidget();
        auto *card = new wl::Card();
        card->setContentWidget(wi);
        this->layoutLeft_->addWidget(card);

        std::vector<wl::Column> columns;
        for (int index = 0; index < 10; index++) {
            auto tmp = QString::fromStdString("column-" + std::to_string(index));
            columns.emplace_back(tmp, tmp, tmp);
        }
        std::vector<wl::TableRecord> dataSource;
        for (int index = 0; index < 15; index++) {
            wl::TableRecord record;
            for (int col = 0; col < columns.size(); col++) {
                auto column = columns[col];
                record.insert(column.dataIndex, QString::fromStdString("中文-" + std::to_string(col) + "-" + std::to_string(index)));
            }
            dataSource.push_back(record);
        }
        auto *table = new wl::Table();
        table->setAttrColumns(columns);
        table->setAttrDataSources(dataSource);
        table->setAttrBordered(true);
        wi->addWidget(table);
    }
}
