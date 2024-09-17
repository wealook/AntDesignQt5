#pragma  once

#include "QWidget"
#include <QString>
#include <QTableView>
#include <QStandardItemModel>
#include "functional"
#include "QJsonObject"
#include "GeneralAttr.h"
#include "VWidget.h"
#include "AWidget.h"

namespace wl {
    using TableRecord = QJsonObject;
    using ColumnRender = std::function<QWidget *(QVariant text, TableRecord record, int index)>;

    class Column {
    public:

        Column(QString title, QString dataIndex, QString key, const ColumnRender &render = nullptr);

        QString title;
        QString dataIndex;
        QString key;
        ColumnRender render = nullptr;
    };

    class Table : public QWidget, public AWidget {
    public:
        explicit Table(QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        void updateAttr();

        void renderData();

    private:
        QSize getSizePadding();

    private:
        QTableView *tableView_ = nullptr;
        QStandardItemModel *tableModel_ = nullptr;

        AWidget headerStyles;
    public:
        void setAttrColumns(const std::vector<Column> &attrColumns);

        void setAttrDataSources(const std::vector<TableRecord> &attrDataSources);

        void setAttrSize(GeneralAttrSize attrSize);

        void setAttrBordered(bool attrBordered);

    private:
        std::vector<Column> attrColumns;
        std::vector<TableRecord> attrDataSources;
        GeneralAttrSize attrSize;
        bool attrBordered = false;
    };
}
