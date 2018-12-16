#include <map>
#include <QComboBox>
#include <QApplication>
#include "detailrelationaldelegate.h"

static IoipsModelMap ioipsMap_;
DetailRelationalDelegate::DetailRelationalDelegate(QObject *parent, QSqlRelationalTableModel *model):
    QItemDelegate(parent), model_(model)
{

}

void DetailRelationalDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
    //if (index.column() != model_->fieldIndex("ioips"))
    //{
    //    QItemDelegate::paint(painter, option, index);
    //    return;
    //}

    //index.model();
#if 0
    if (index.column() != model_->fieldIndex("ioips"))
    {
        QItemDelegate::paint(painter, option, index);
        return;
    }

    QStyleOptionComboBox comboBoxOption;
    comboBoxOption.rect = option.rect;
    comboBoxOption.state = option.state;
    comboBoxOption.state |= QStyle::State_Enabled;
    comboBoxOption.editable = false;

    QComboBox* comboBox = new QComboBox;
    QString srcStr = index.data().toString();
    QStringList ioipList = srcStr.split(',', QString::SkipEmptyParts);
    comboBox->addItems(ioipList);

    QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &comboBoxOption, painter);
#endif
    return;
}

QWidget *DetailRelationalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() != model_->fieldIndex("ioips"))
    {
        //return QItemDelegate::createEditor(parent, option, index);
        return nullptr;
    }

    QComboBox *editor = new QComboBox(parent);
    QString srcStr = index.data().toString();
    QStringList ioipList = srcStr.split(',', QString::SkipEmptyParts);
    editor->addItems(ioipList);

    return editor;
}

void DetailRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() != model_->fieldIndex("ioips"))
    {
        QItemDelegate::setEditorData(editor, index);
        return;
    }

    QModelIndex nameIndex = index.model()->index(index.row(), 0);
    QString nameStr = nameIndex.data().toString();
    QStringList ioipsList;
    ioipsList.clear();
    auto iter = ioipsMap_.find(nameStr);
    if (iter == ioipsMap_.end())
    {
        QString srcStr = index.data().toString();
        ioipsList = srcStr.split(',', QString::SkipEmptyParts);
        ioipsMap_.insert(std::make_pair(nameStr, ioipsList));
    }
    else
    {
        ioipsList = iter->second;
    }
    QComboBox* cb = qobject_cast<QComboBox*>(editor);
    cb->clear();
    cb->addItems(ioipsList);
}

void DetailRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                            const QModelIndex &index) const
{
    QItemDelegate::setModelData(editor, model, index);
    return;
}

