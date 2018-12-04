#ifndef ARRAYDATABASEMODEL_H
#define ARRAYDATABASEMODEL_H

#include <memory>
#include <QtWidgets>
#include <QtSql>
#include <QSqlRelationalDelegate>

class ArrayDatabaseModel
{
public:
    ArrayDatabaseModel();

    QSqlError init(QTableView* tableView);
    QSqlTableModel* getDatabaseModel() const
    {
        return model_.get();
    }

private:
    QSqlError initDatabase();
    std::shared_ptr<QSqlRelationalTableModel> model_;
};

#endif // ARRAYDATABASEMODEL_H
