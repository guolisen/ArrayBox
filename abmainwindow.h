#ifndef ABMAINWINDOW_H
#define ABMAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "swarm/iswarm.h"

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
    ABMainWindow(QWidget *parent, swarm::SwarmPtr swarm);
    ~ABMainWindow();

    bool init();
    void findStringProcess(const QString& s);
    void currentRowChangedProcess(const QModelIndex &current, const QModelIndex &previous);

private slots:
    void about();
    void insterFromSwarm();
private:
    void createMenu();
    void createToolbar();
    void createDataMap();
    void createFindDelegate();
    void tableViewInit();
    QSqlError databaseInit();
    void showError(const QSqlError &err);

    Ui::ABMainWindow *ui;
    SortFilterProxyModel* proxyModel_;
    std::shared_ptr<ArrayDatabaseModel> databaseModel_;
    QDataWidgetMapper* mapper_;
    swarm::SwarmPtr swarm_;
};

#endif // ABMAINWINDOW_H
