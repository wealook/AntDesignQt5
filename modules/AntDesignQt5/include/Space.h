#pragma  once

#include <QWidget>
#include "SpaceAttr.h"
#include <vector>
#include "AWidget.h"

namespace wl {
    class Space : public AWidget, public QWidget {
    public:
        Space() = default;

        explicit Space(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        [[nodiscard]] const SpaceAttr &getAttr() const;

        void setAttr(const SpaceAttr &spaceAttr);

        void addItem(QWidget *);

        void clearItems();

    private:
        SpaceAttr attr;
        std::vector<QWidget *> widgets;

    };
};


