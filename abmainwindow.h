#ifndef ABMAINWINDOW_H
#define ABMAINWINDOW_H

#include <memory>
#include <QMainWindow>

namespace Ui {
class ABMainWindow;
}

class ArrayDatabaseModel;
class QSqlError;
class QSortFilterProxyModel;

class ABMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ABMainWindow(QWidget *parent = nullptr);
    ~ABMainWindow();

    bool init();
    void findStringProcess();
private:
    void showError(const QSqlError &err);
    Ui::ABMainWindow *ui;
    QSortFilterProxyModel* proxyModel_;
    std::shared_ptr<ArrayDatabaseModel> databaseModel_;
};

#endif // ABMAINWINDOW_H
