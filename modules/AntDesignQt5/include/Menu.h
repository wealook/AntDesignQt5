#pragma once

#include <QScrollArea>
#include "QWidget"
#include "QTreeWidget"
#include <unordered_map>

namespace wl {

    class MenuItem {

    public:
        explicit MenuItem(QString label, QString key) : label(label), key(key) {

        }

        QString label;
        QString key;
        std::vector<MenuItem> children;

        static void treeToListKeys(const std::vector<MenuItem> &items, std::vector<QString> &keys);
    };

    class Menu : public QScrollArea {
    Q_OBJECT
    public:
        explicit Menu(QWidget *parent = nullptr);

        void resizeEvent(QResizeEvent *event) override;

        std::vector<MenuItem> menuItems;

        void initWidget();

    signals:

        void menuClicked(QString key);

    protected slots:

        void onItemClicked();

        void onTreeItemClicked(QTreeWidgetItem *, int);

    private:
        QTreeWidget *tree = nullptr;
        std::unordered_map<void *, void *> btn2Item_;
    };
}
