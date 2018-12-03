#include <memory>
#include <QtSql>
#include "arraydatabasemodel.h"
#include "ui_abmainwindow.h"

static const QString dbPath("C:/Code/qt/ArrayBox/Arrays.db");
static const QLatin1String createArraysTableSql("CREATE TABLE arraysTest (id integer primary key, \
        name	varchar, \
        mgmtip	varchar, \
        spaip	varchar, \
        spbip	varchar, \
        terminalspaip	varchar, \
        terminalspbip	varchar, \
        model	varchar, \
        ioips	varchar, \
        reservedby	varchar, \
        serial	varchar, \
        lablocation	varchar, \
        type	varchar, \
        url	varchar, \
        state	varchar, \
        statereason	varchar, \
        pools	varchar \
    );");

ArrayDatabaseModel::ArrayDatabaseModel(QTableView* tableView):
    model_(std::make_shared<QSqlRelationalTableModel>(tableView))
{

}

QSqlError ArrayDatabaseModel::init()
{
    QSqlError err = initDatabase();
    if (err.type() != QSqlError::NoError) {
        return err;
    }

    // Create the data model:
    model_->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_->setTable("arrays");

    // Set the localized header captions:
    model_->setHeaderData(model_->fieldIndex("name"),
                         Qt::Horizontal, "Array Name");
    model_->setHeaderData(model_->fieldIndex("spaip"),
                         Qt::Horizontal, "SPA IP");
    model_->setHeaderData(model_->fieldIndex("spbip"),
                         Qt::Horizontal, "SPB IP");
    model_->setHeaderData(model_->fieldIndex("mgmtip"),
                         Qt::Horizontal, "Mgmt IP");

    // Populate the model:
    if (!model_->select()) {
        return model_->lastError();
    }

    return QSqlError();
}

QSqlError ArrayDatabaseModel::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("arrays", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(createArraysTableSql))
        return q.lastError();

    return QSqlError();
}
