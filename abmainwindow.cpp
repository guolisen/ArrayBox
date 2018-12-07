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

void ABMainWindow::tableViewInit()
{
    ui->tableView->setModel(proxyModel_);
    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->horizontalHeader()->resizeSection(0,150);  //修改表头第一列的宽度为150
    ui->tableView->horizontalHeader()->setFixedHeight(25);  //修改表头合适的高度
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color:lightblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");    //设置表头字体，颜色，模式
    ui->tableView->verticalHeader()->setStyleSheet("QHeaderView::section {  background-color:skyblue;color: black;padding-left: 4px;border: 1px solid #6c6c6c}");   //设置纵列的边框项的字体颜色模式等
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

bool ABMainWindow::init()
{
    //ui->splitter->setSizes(QList<int>({INT_MAX, INT_MAX}));
    createMenu();
    createToolbar();

    QSqlError err = databaseInit();
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return false;
    }

    tableViewInit();

    mapper_ = new QDataWidgetMapper(this);
    mapper_->setModel(databaseModel_->getDatabaseModel());
    //mapper->setItemDelegate(new BookDelegate(this));
    mapper_->addMapping(ui->nameLineEdit, databaseModel_->getDatabaseModel()->fieldIndex("name"));
   //mapper->addMapping(ui.yearEdit, proxyModel_->fieldIndex("year"));

#if 0
    connect(ui->tableView,
            &QTableView::selectRow,
            this,
            &ABMainWindow::currentRowChangedProcess);
#endif

    connect(ui->tableView->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            mapper_,
            &QDataWidgetMapper::setCurrentModelIndex
            );

    //ui->tableView->setCurrentIndex(databaseModel_->getDatabaseModel()->index(1, 0));
    statusBar()->showMessage(tr("Ready"));
    return true;
}

void ABMainWindow::findStringProcess(const QString& s)
{
    QString str = "*" + s + "*";
    proxyModel_->addFilterFixedString(str);
    proxyModel_->setFilterRegExp(QRegExp(str, proxyModel_->filterCaseSensitivity(), QRegExp::Wildcard));
}

void ABMainWindow::currentRowChangedProcess(int row)
{
    mapper_->setCurrentIndex(row);
}

void ABMainWindow::createMenu()
{

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
