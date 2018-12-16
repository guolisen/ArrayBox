#ifndef ARRAYDATABASEMODEL_H
#define ARRAYDATABASEMODEL_H

#include <memory>
#include <QtWidgets>
#include <QtSql>
#include <QSqlRelationalDelegate>

typedef std::map<QString, QString> ColMap;

class ArrayDatabaseModel
{
public:
    ArrayDatabaseModel();

    QSqlError init(QTableView* tableView);
    QSqlRelationalTableModel* getDatabaseModel() const
    {
        return model_.get();
    }

    QSqlError insertRow(const QString& table, const ColMap row);
private:
    QSqlError initDatabase();
    std::shared_ptr<QSqlRelationalTableModel> model_;
};

#endif // ARRAYDATABASEMODEL_H
