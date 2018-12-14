#include <memory>
#include <QComboBox>
#include "abmainwindow.h"
#include "ui_abmainwindow.h"
#include "ui_swarmfinddialog.h"
#include "arraydatabasemodel.h"
#include "sortfilterproxymodel.h"
#include "detailrelationaldelegate.h"

ABMainWindow::ABMainWindow(QWidget *parent, swarm::SwarmPtr swarm) :
    QMainWindow(parent),
    ui(new Ui::ABMainWindow),
    databaseModel_(std::make_shared<ArrayDatabaseModel>()),
    swarm_(swarm)
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

void ABMainWindow::tableViewInit()
{
    ui->tableView->setModel(proxyModel_);
    ui->tableView->setItemDelegate(new DetailRelationalDelegate(this, databaseModel_->getDatabaseModel()));

    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->horizontalHeader()->resizeSection(0,150);  //修改表头第一列的宽度为150
    ui->tableView->horizontalHeader()->setFixedHeight(25);  //修改表头合适的高度
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;padding-left: 4px;border: 0.5px solid #FFFFFF;}");    //设置表头字体，颜色，模式
    ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section {  background-color:skyblue;color: black;padding-left: 4px;border: 0.5px solid #FFFFFF}");   //设置纵列的边框项的字体颜色模式等
    ui->tableView->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"        //垂直滑块整体
                                                      "background:#FFFFFF;"  //背景色
                                                      "padding-top:20px;"    //上预留位置（放置向上箭头）
                                                      "padding-bottom:20px;" //下预留位置（放置向下箭头）
                                                      "padding-left:3px;"    //左预留位置（美观）
                                                      "padding-right:3px;"   //右预留位置（美观）
                                                      "border-left:1px solid #d7d7d7;}"//左分割线
                                                      "QScrollBar::handle:vertical{"//滑块样式
                                                      "background:#dbdbdb;"  //滑块颜色
                                                      "border-radius:6px;"   //边角圆润
                                                      "min-height:80px;}"    //滑块最小高度
                                                      "QScrollBar::handle:vertical:hover{"//鼠标触及滑块样式
                                                      "background:#d0d0d0;}" //滑块颜色
                                                      "QScrollBar::add-line:vertical{"//向下箭头样式
                                                      "background:url(:/images/resource/images/checkout/down.png) center no-repeat;}"
                                                      "QScrollBar::sub-line:vertical{"//向上箭头样式
                                                      "background:url(:/images/resource/images/checkout/up.png) center no-repeat;}");

    ui->tableView->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal{"
                                                        "background:#FFFFFF;"
                                                        "padding-top:15px;"
                                                        "padding-bottom:2px;"
                                                        "padding-left:20px;"
                                                        "padding-right:20px;}"
                                                        "QScrollBar::handle:horizontal{"
                                                        "background:#dbdbdb;"
                                                        "border-radius:6px;"
                                                        "min-width:40px;}"
                                                        "QScrollBar::handle:horizontal:hover{"
                                                        "background:#d0d0d0;}"
                                                        "QScrollBar::add-line:horizontal{"
                                                        "background:url(:/images/resource/images/checkout/right.png) center no-repeat;}"
                                                        "QScrollBar::sub-line:horizontal{"
                                                        "background:url(:/images/resource/images/checkout/left.png) center no-repeat;}"
                                                        );
    //获取表头列数
    for(int i = 0; i < ui->tableView->horizontalHeader()->count(); i++)
    {
        ui->tableView->setColumnWidth(i, ui->tableView->columnWidth(i) + 10);  //多一些空余控件，不然每列内容很挤
    }

    //ui->tableView->setCurrentIndex(databaseModel_->getDatabaseModel()->index(0, 0));
}

QSqlError ABMainWindow::databaseInit()
{
    QSqlError err = databaseModel_->init(ui->tableView);
    if (err.type() != QSqlError::NoError) {
        return err;
    }
    proxyModel_ = new SortFilterProxyModel(this);
    proxyModel_->setSourceModel(databaseModel_->getDatabaseModel());
    proxyModel_->setFilterCaseSensitivity(Qt::CaseInsensitive);

    proxyModel_->setFilterKeyColumns(10);
    proxyModel_->addFilterFixedString("*");

    return QSqlError();
}

void ABMainWindow::createDataMap()
{
    QSqlRelationalTableModel* model = databaseModel_->getDatabaseModel();
    mapper_ = new QDataWidgetMapper(this);
    mapper_->setModel(model);
    mapper_->setItemDelegate(new DetailRelationalDelegate(this, model));
    mapper_->addMapping(ui->nameLineEdit, model->fieldIndex("name"));
    mapper_->addMapping(ui->mgmtIPLineEdit, model->fieldIndex("mgmtip"));
    mapper_->addMapping(ui->versionLineEdit, model->fieldIndex("version"));
    mapper_->addMapping(ui->modelLineEdit, model->fieldIndex("model"));
    mapper_->addMapping(ui->labIPSPALineEdit, model->fieldIndex("spaip"));
    mapper_->addMapping(ui->labIPSPBLineEdit, model->fieldIndex("spbip"));
    mapper_->addMapping(ui->terminalSPALineEdit, model->fieldIndex("terminalspaip"));
    mapper_->addMapping(ui->terminalSPBLineEdit, model->fieldIndex("terminalspbip"));
    mapper_->addMapping(ui->serialLineEdit, model->fieldIndex("serial"));
    mapper_->addMapping(ui->typeLineEdit, model->fieldIndex("type"));
    mapper_->addMapping(ui->iOIPsComboBox, model->fieldIndex("ioips"));

    connect(ui->tableView->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this,
            &ABMainWindow::currentRowChangedProcess
            );
}

void ABMainWindow::createFindDelegate()
{
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &ABMainWindow::findStringProcess);
    ui->lineEdit->setClearButtonEnabled(true);
}

bool ABMainWindow::init()
{
    createMenu();
    createToolbar();
    createFindDelegate();

    QSqlError err = databaseInit();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return false;
    }

    tableViewInit();
    createDataMap();

    statusBar()->showMessage(tr("Ready"));
    return true;
}

void ABMainWindow::findStringProcess(const QString& s)
{
    QString str = "*" + s + "*";
    proxyModel_->addFilterFixedString(str);
    proxyModel_->setFilterRegExp(QRegExp(str, proxyModel_->filterCaseSensitivity(), QRegExp::Wildcard));
}

void ABMainWindow::currentRowChangedProcess(const QModelIndex &current, const QModelIndex &previous)
{
    mapper_->setCurrentIndex(current.row());

    QSqlRelationalTableModel* model = databaseModel_->getDatabaseModel();
    QModelIndex ioipModel = model->index(current.row(),model->fieldIndex("ioips"));

    QString srcStr = ioipModel.data().toString();
    QStringList ioipList = srcStr.split(',', QString::SkipEmptyParts);
    ui->iOIPsComboBox->clear();
    ui->iOIPsComboBox->addItems(ioipList);
}

void ABMainWindow::createMenu()
{
    QAction *quitAction = new QAction(tr("&Quit"), this);
    QAction *aboutAction = new QAction(tr("&About"), this);
    QAction *insertFromSwarmAction = new QAction(tr("&Insert From Swarm"), this);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(insertFromSwarmAction);
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);

    connect(quitAction, &QAction::triggered, this, &ABMainWindow::close);
    connect(aboutAction, &QAction::triggered, this, &ABMainWindow::about);
    connect(insertFromSwarmAction, &QAction::triggered, this, &ABMainWindow::insterFromSwarm);
}

void ABMainWindow::createToolbar()
{
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/res/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    //connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    ui->mainToolBar->addAction(newAct);
}

void ABMainWindow::about()
{
    QMessageBox::about(this, tr("About DeviceBox"),
            tr("Just a Test!"
               "with a model/view framework."));
}

void ABMainWindow::insterFromSwarm()
{
    QDialog swarmDialog;
    Ui::Dialog ui;
    ui.setupUi(&swarmDialog);
    swarmDialog.adjustSize();

    if (swarmDialog.exec() != QDialog::Accepted)
        return;

    QString searchStr = ui.lineEdit->text();
    swarm::SwarmInfoPtr info = swarm_->search("bs-d9526");
}
