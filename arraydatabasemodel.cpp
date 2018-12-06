#include <memory>
#include <QtSql>
#include "arraydatabasemodel.h"
#include "ui_abmainwindow.h"

static const QString dbPath("C:/Code/qt/ab/ArrayBox/Arrays.db");
static const QLatin1String createArraysTableSql("CREATE TABLE arrays (id integer primary key, \
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

ArrayDatabaseModel::ArrayDatabaseModel()
{

}

QSqlError ArrayDatabaseModel::init(QTableView* tableView)
{
    QSqlError err = initDatabase();
    if (err.type() != QSqlError::NoError) {
        return err;
    }

    // Create the data model:
    model_ = std::make_shared<QSqlRelationalTableModel>(tableView);
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
        QSqlError err1 = model_->lastError();
        return err1;
    }

    return QSqlError();
}

QSqlError ArrayDatabaseModel::initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open())
        return db.lastError();

    QSqlQuery q;
#if 0
    if (!q.prepare(QLatin1String("insert into arrays(id, name, mgmtip, spaip, spbip, terminalspaip, terminalspbip, model, \
                                  ioips, reservedby, serial, lablocation, type, url, state, statereason, pools) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")))
        return q.lastError();
    q.addBindValue(3);
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.addBindValue("TestArray3");
    q.exec();
#endif
    QStringList tables = db.tables();
    if (tables.contains("arrays", Qt::CaseInsensitive))
        return QSqlError();

    if (!q.exec(createArraysTableSql))
        return q.lastError();

    return QSqlError();
}
