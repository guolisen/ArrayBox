#include "abmainwindow.h"
#include "ui_abmainwindow.h"
#include "arraydatabasemodel.h"

ABMainWindow::ABMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ABMainWindow),
    databaseModel_(std::make_shared<ArrayDatabaseModel>())
{
    ui->setupUi(this);
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

    ui->tableView->setModel(databaseModel_->getDatabaseModel());
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    return true;
}
