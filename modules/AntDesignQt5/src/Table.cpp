
#include "Table.h"

#include <utility>
#include "QHeaderView"
#include "ThemeConfig.h"
#include "qevent.h"
#include "QVBoxLayout"
#include "QLabel"

namespace wl {

    Table::Table(QWidget *parent) : QWidget(parent) {
//        this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        tableModel_ = new QStandardItemModel();
        this->tableView_ = new QTableView(this);
        this->tableView_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        this->tableView_->setModel(tableModel_);

        auto ly = new QVBoxLayout();
        ly->setAlignment(Qt::AlignTop);
        this->setLayout(ly);
        ly->addWidget(this->tableView_);
        ly->addSpacerItem(new QSpacerItem(QSizePolicy::Preferred, QSizePolicy::Expanding));
        this->tableView_->verticalHeader()->setVisible(false);
        this->tableView_->setSelectionBehavior(QAbstractItemView::SelectItems);
        this->tableView_->setShowGrid(false);
        this->tableView_->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        this->tableView_->horizontalHeader()->setStyleSheet("color:black;font-size:14px;font-weight:600;");
        this->tableView_->verticalHeader()->setMinimumSectionSize(60);//设置垂直单元格最小高度
    }

    void Table::renderData() {
        tableModel_->clear();
        QStringList headers;
        for (const auto &it: this->attrColumns) {
            headers << it.title;
        }
        this->tableModel_->setHorizontalHeaderLabels(headers);
        int rowIndex = 0;
        for (auto &record: this->attrDataSources) {
            QList<QStandardItem *> listItem;
            for (const auto &column: this->attrColumns) {
                QStandardItem *item = nullptr;
                if (record.contains(column.dataIndex)) {
                    item = new QStandardItem(record[column.dataIndex].toString());
                } else {
                    item = new QStandardItem("");
                }
//                item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
                item->setEditable(false);
                item->setSelectable(false);
                item->setCheckable(false);
                listItem << item;
            }
            this->tableModel_->appendRow(listItem);
//            this->tableView_->setRowHeight(rowIndex, 60);
            rowIndex++;
        }
        this->updateAttr();
    }

    void Table::updateAttr() {
        auto theme = ThemeConfig::Instance();
        auto sizeRowHeight = 47;
        if (this->attrSize == GeneralAttrSize::small) {
            sizeRowHeight = 39;
        } else if (this->attrSize == GeneralAttrSize::large) {
            sizeRowHeight = 55;
        }
        this->setStyleQss("QTableView::item", "padding-top", "12px");
        this->setStyleQss("QTableView::item", "padding-left", "12px");
        this->setStyleQss("QTableView::item", "padding-right", "12px");
        this->setStyleQss("QTableView::item", "padding-bottom", "12px");
        this->setStyleQss("QTableView::item:selected", "border", "none");
        this->setStyleQss("QTableView", "padding", "4px");
        this->setStyleQss("QTableView", "outline", "none");
        this->setStyleQss("color", "black");
        this->setStyleQss("font-size", "14px");
        this->setStyleQss("color", "black");

        auto borderStyle = "1px solid " + theme.colorBorder;
        // 必须有border 不然padding设置没用。可能是bug;
        headerStyles.setStyleQss("border", "0px");
        headerStyles.setStyleQss("border-bottom", borderStyle);
        headerStyles.setStyleQss("border-bottom-left-radius", "none");
        headerStyles.setStyleQss("border-bottom-right-radius", "none");
        headerStyles.setStyleQss("background-color", "gray");
        headerStyles.setStyleQss("font-weight", "600");
        headerStyles.setStyleQss("font-size", "14px");

        if (this->attrBordered) {
            this->setStyleQss("QTableView", "border", borderStyle);
            this->setStyleQss("QTableView::item", "border", "0px");
        } else {
            this->setStyleQss("QTableView", "border", "none");
            this->setStyleQss("QTableView::item", "border-bottom", borderStyle);
        }
        this->tableView_->setShowGrid(this->attrBordered);
        this->tableView_->setStyleSheet(this->getJoinStyles());
        this->tableView_->horizontalHeader()->setStyleSheet(headerStyles.getJoinStyles());
        this->tableView_->horizontalHeader()->hide();

    }

    void Table::setAttrColumns(const std::vector<Column> &attrColumns) {
        Table::attrColumns = attrColumns;
    }

    void Table::setAttrDataSources(const std::vector<TableRecord> &attrDataSources) {
        Table::attrDataSources = attrDataSources;
    }

    void Table::setAttrSize(GeneralAttrSize attrSize) {
        Table::attrSize = attrSize;
    }

    QSize Table::getSizePadding() {
        if (this->attrSize == GeneralAttrSize::small) {
            return {8, 8};
        } else if (this->attrSize == GeneralAttrSize::large) {
            return {16, 16};
        }
        return {8, 12};
    }

    void Table::resizeEvent(QResizeEvent *event) {
        LOG_INFO("resize:" << event->size().height())
        auto rows = this->tableModel_->rowCount();
        int rowsHeight = 0;
        for (int row = 0; row < rows; row++) {
            rowsHeight += this->tableView_->rowHeight(row);

        }
        LOG_INFO(rowsHeight)
        this->tableView_->setFixedHeight(rowsHeight + this->tableView_->horizontalHeader()->height() + 30);
        QWidget::resizeEvent(event);
        this->renderData();
    }

    void Table::setAttrBordered(bool attrBordered) {
        Table::attrBordered = attrBordered;
    }


    Column::Column(QString title, QString dataIndex, QString key, const ColumnRender &render) : title(std::move(title)), dataIndex(std::move(dataIndex)), key(std::move(key)),
                                                                                                render(render) {}
}