#include "abmainwindow.h"
#include "ui_abmainwindow.h"
#include "arraydatabasemodel.h"
#include "sortfilterproxymodel.h"

ABMainWindow::ABMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ABMainWindow),
    databaseModel_(std::make_shared<ArrayDatabaseModel>())
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &ABMainWindow::findStringProcess);

}

void ABMainWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Find some Error: ", err.text());
}

ABMainWindow::~ABMainWindow()
{

    delete ui;
}

bool ABMainWindow::init()
{
    ui->splitter->setSizes(QList<int>({INT_MAX, INT_MAX}));

    QSqlError err = databaseModel_->init(ui->tableView);
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return false;
    }

    proxyModel_ = new SortFilterProxyModel(this);
    proxyModel_->setSourceModel(databaseModel_->getDatabaseModel());
    proxyModel_->setFilterCaseSensitivity(Qt::CaseInsensitive);

    proxyModel_->setFilterKeyColumns(10);
    proxyModel_->addFilterFixedString("*");

    ui->tableView->setModel(proxyModel_);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader();

    //获取表头列数
    for(int i = 0; i < ui->tableView->horizontalHeader()->count(); i++)
    {
        ui->tableView->setColumnWidth(i, ui->tableView->columnWidth(i) + 10);  //多一些空余控件，不然每列内容很挤
    }

    return true;
}

void ABMainWindow::findStringProcess(const QString& s)
{
    QString str = "*" + s + "*";
    proxyModel_->addFilterFixedString(str);
    proxyModel_->setFilterRegExp(QRegExp(str, proxyModel_->filterCaseSensitivity(), QRegExp::Wildcard));
    //proxyModel_->setFilterWildcard(str);
}
