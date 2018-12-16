#include <QComboBox>
#include <QApplication>
#include "detailrelationaldelegate.h"

DetailRelationalDelegate::DetailRelationalDelegate(QObject *parent, QSqlRelationalTableModel *model):
    QItemDelegate(parent), model_(model)
{

}

void DetailRelationalDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
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

    QComboBox* cb = qobject_cast<QComboBox*>(editor);
    QString srcStr = index.data().toString();
    QStringList ioipList = srcStr.split(',', QString::SkipEmptyParts);
    cb->clear();
    cb->addItems(ioipList);
}

