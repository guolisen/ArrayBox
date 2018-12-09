#include <QComboBox>
#include <QApplication>
#include <QStandardItemModel>
#include "detailrelationaldelegate.h"

DetailRelationalDelegate::DetailRelationalDelegate(QObject *parent, QSqlRelationalTableModel *model):
    QItemDelegate(parent), model_(model), listViewModel_(new QStandardItemModel)
{

}

void DetailRelationalDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //if (index.column() != model_->fieldIndex("ioips"))
    {
        QItemDelegate::paint(painter, option, index);
        return;
    }

    QStyleOptionComboBox comboBoxOption;
    comboBoxOption.rect = option.rect;
    comboBoxOption.state = option.state;
    comboBoxOption.state |= QStyle::State_Enabled;
    comboBoxOption.editable = false;
    //comboBoxOption.currentText = "testcombobox";

    QComboBox* comboBox = new QComboBox;
    QString srcStr = index.data().toString();
    QStringList ioipList = srcStr.split(',', QString::SkipEmptyParts);
    comboBox->addItems(ioipList);

    //QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &comboBoxOption, painter);

    return;
}

QWidget *DetailRelationalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return nullptr;
}

void DetailRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() != model_->fieldIndex("ioips"))
    {
        QItemDelegate::setEditorData(editor, index);
        return;
    }

    listViewModel_->clear();
    QString srcStr = index.data().toString();
    QStringList ioipList = srcStr.split(',', QString::SkipEmptyParts);
    foreach(QString ioip, ioipList)
    {
        QStandardItem *item = new QStandardItem(ioip);
        listViewModel_->appendRow(item);
    }

    QListView* listView = qobject_cast<QListView*>(editor);
    listView->setModel(listViewModel_);
}

