#include <memory>
#include <map>
#include <QObject>
#include <QtSql>
#include "arraydatabasemodel.h"
#include "ui_abmainwindow.h"

static const QString dbPath("../ab/ArrayBox/Arrays.db");
static const QLatin1String createArraysTableSql("CREATE TABLE arrays ("
                                                "id    varchar primary key,"
                                                "name    varchar ,"
                                                "type    varchar,"
                                                "model    varchar,"
                                                "spaip    varchar,"
                                                "spbip    varchar,"
                                                "csip    varchar ,"
                                                "csipv6    varchar,"
                                                "bmcaip    varchar,"
                                                "bmcbip    varchar,"
                                                "terminalip   varchar,"
                                                "terminalaport    varchar,"
                                                "terminalbport    varchar,"
                                                "consoleip    varchar,"
                                                "series    varchar ,"
                                                "owner    varchar,"
                                                "reserved_by    varchar,"
                                                "diskcount    varchar,"
                                                "username    varchar,"
                                                "password    varchar,"
                                                "rempowsupip    varchar,"
                                                "rempowsupoutb     varchar,"
                                                "hypervisor    varchar,"
                                                "program    varchar,"
                                                "location    varchar,"
                                                "post    varchar,"
                                                "memory_configuration   varchar,"
                                                "productserialno    varchar ,"
                                                "bounddiskcount    varchar,"
                                                "crawledmodel    varchar,"
                                                "totalcapacity    varchar,"
                                                "responsiblemanager    varchar,"
                                                "bios    varchar,"
                                                "rempowsupouta     varchar,"
                                                "racklocation    varchar,"
                                                "pduname    varchar,"
                                                "lastcrawltime    varchar ,"
                                                "frequent_crawl    varchar,"
                                                "cs1ip    varchar,"
                                                "imagefile    varchar,"
                                                "lastcrawlresult    varchar,"
                                                "version    varchar,"
                                                "blockfilestate    varchar,"
                                                "image    varchar,"
                                                "virtualmanagementserver   varchar,"
                                                "lab   varchar"
                                                ");");
static const QLatin1String createIoIpSql("CREATE TABLE ioip (id integer primary key, \
                                                            name varchar, \
                                                            ip varchar\
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

    QSqlQuery viewQuery("select arrays.id, arrays.model, TestTable.A2 from arrays, TestTable where arrays.id = TestTable.id");
    //QSqlQuery viewQuery("select * from arrays a left join TestTable b on a.id = b.id");
    std::shared_ptr<QSqlQueryModel> queryModel = std::static_pointer_cast<QSqlQueryModel>(model_);
    queryModel->setQuery(viewQuery);

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

QSqlError ArrayDatabaseModel::insertRow(const QString &table, const ColMap row)
{
    QSqlQuery query;
    QString str = "PRAGMA table_info(" + table + ")";
    std::map<QString, QString> insertColMap;

    query.prepare(str);
    if (query.exec())
    {
       while (query.next())
       {
           qDebug() << QString(QString::fromLocal8Bit("%1      %2      %3")).arg(query.value(0).toString()).arg(query.value(1).toString()).arg(query.value(2).toString());
           QString colName = query.value(1).toString();
           QString pattenCol = QString(":") + colName;
           auto iter = row.find(colName);
           if (iter != row.end())
           {
               insertColMap.insert(std::make_pair(pattenCol,  iter->second));
               continue;
           }
           insertColMap.insert(std::make_pair(pattenCol, ""));
       }
    }

    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into arrays(id,name,type,model,spaip,spbip,csip,csipv6,bmcaip,bmcbip,terminalip,terminalaport ,terminalbport,consoleip,series,"
                                 "owner,reserved_by,diskcount,username,password,rempowsupip,rempowsupoutb ,hypervisor,program,location,post,memory_configuration,"
                                 "productserialno ,bounddiskcount,crawledmodel,totalcapacity,responsiblemanager,bios,rempowsupouta ,racklocation,pduname,"
                                 "lastcrawltime ,frequent_crawl,cs1ip,imagefile,lastcrawlresult,version,blockfilestate,image,virtualmanagementserver,lab)"
                                 "values(:id, :name, :type, :model, :spaip, :spbip, :csip, :csipv6, :bmcaip, :bmcbip, :terminalip, :terminalaport , :terminalbport, :consoleip, :series, :"
                                 "owner, :reserved_by, :diskcount, :username, :password, :rempowsupip, :rempowsupoutb , :hypervisor, :program, :location, :post, :memory_configuration, :"
                                 "productserialno , :bounddiskcount, :crawledmodel, :totalcapacity, :responsiblemanager, :bios, :rempowsupouta , :racklocation, :pduname, :"
                                 "lastcrawltime , :frequent_crawl, :cs1ip, :imagefile, :lastcrawlresult, :version, :blockfilestate, :image, :virtualmanagementserver, :lab)")))
        return q.lastError();

    for (auto val: insertColMap)
    {
        q.bindValue(val.first, val.second);
    }

    if(!q.exec())
        return q.lastError();

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
    //if (!q.exec(createIoIpSql))
    //    return q.lastError();

    return QSqlError();
}
