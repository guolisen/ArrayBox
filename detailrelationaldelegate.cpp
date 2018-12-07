#include <QComboBox>
#include <QApplication>
#include "detailrelationaldelegate.h"

DetailRelationalDelegate::DetailRelationalDelegate(QObject *parent, QSqlRelationalTableModel *model):
    QSqlRelationalDelegate(parent), model_(model)
{

}

QWidget *DetailRelationalDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.column() != model_->fieldIndex("ioips"))
        return QSqlRelationalDelegate::createEditor(parent, option, index);


    QComboBox *combobox = new QComboBox(parent);


    QString ioipsStr = index.data().toString();
    //combobox->addItem()

    return nullptr;
}

void DetailRelationalDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSqlRelationalDelegate::paint(painter, option, index);
    return;
#if 0
    if (index.column() != model_->fieldIndex("ioips"))
    {
        QSqlRelationalDelegate::paint(painter, option, index);
        return;
    }


        int progress = index.data().toInt();

        QStyleOptionProgressBar progressBarOption;
        progressBarOption.rect = option.rect;
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.progress = progress;
        progressBarOption.text = QString::number(progress) + "%";
        progressBarOption.textVisible = true;


        QApplication::style()->drawControl(QStyle::CE_ProgressBar,
                                           &progressBarOption, painter);
#endif

}
