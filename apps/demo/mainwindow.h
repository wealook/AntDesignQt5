#include "QComboBox"
#include "Layout.h"
#include <QDateTime>
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QStandardItem>
#include <iostream>
#include <mutex>
#include <thread>
#include "Content.h"

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    //    ~MainWindow();
    void resizeEvent(QResizeEvent *event) override;

protected slots:

    void onMenuClicked(QString k);

private:
    wl::Content* content_;

    Ui::MainWindow *ui;
    std::shared_ptr<std::thread> thread_;
    wl::Layout *baseLayout_;
    std::unordered_map<std::string, QWidget *> widgetsMap;
public:

public:
    //    void resizeEvent(QResizeEvent* event) override;

};
