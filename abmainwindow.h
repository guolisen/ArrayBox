#ifndef ABMAINWINDOW_H
#define ABMAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "swarm/iswarm.h"
#include "swarm/iswarmreply.h"

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
    void swarmResult(bool result, swarm::SwarmReplyPtr reply);
private slots:
    void about();
    void insterFromSwarm();
    void copyToCilpboard(const QModelIndex &index);
private:
    void createMenu();
    void createToolbar();
    void createDataMap();
    void createFindDelegate();
    void tableViewInit();
    QSqlError databaseInit();
    void showError(const QSqlError &err);
    void copyToClipboardTool(const QString& ipStr);

    Ui::ABMainWindow *ui;
    SortFilterProxyModel* proxyModel_;
    std::shared_ptr<ArrayDatabaseModel> databaseModel_;
    QDataWidgetMapper* mapper_;
    swarm::SwarmPtr swarm_;

};

#endif // ABMAINWINDOW_H
