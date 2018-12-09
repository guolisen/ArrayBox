#ifndef ABMAINWINDOW_H
#define ABMAINWINDOW_H

#include <memory>
#include <QMainWindow>

namespace Ui {
class ABMainWindow;
}

class ArrayDatabaseModel;
class QSqlError;
class SortFilterProxyModel;
class QDataWidgetMapper;
class DetailRelationalDelegate;

class ABMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ABMainWindow(QWidget *parent = nullptr);
    ~ABMainWindow();

    bool init();
    void findStringProcess(const QString& s);
    void currentRowChangedProcess(const QModelIndex &current, const QModelIndex &previous);
private:
    void createMenu();
    void createToolbar();
    void tableViewInit();
    QSqlError databaseInit();
    void showError(const QSqlError &err);

    Ui::ABMainWindow *ui;
    SortFilterProxyModel* proxyModel_;
    std::shared_ptr<ArrayDatabaseModel> databaseModel_;
    QDataWidgetMapper* mapper_;
};

#endif // ABMAINWINDOW_H
