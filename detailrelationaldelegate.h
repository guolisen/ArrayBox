#ifndef DETAILRELATIONALDELEGATE_H
#define DETAILRELATIONALDELEGATE_H

#include <QModelIndex>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

class QStandardItemModel;
class DetailRelationalDelegate : public QItemDelegate
{
    //Q_OBJECT
public:
    DetailRelationalDelegate(QObject *parent, QSqlRelationalTableModel* model);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
private:
    QSqlRelationalTableModel* model_;
    QStandardItemModel* listViewModel_;
};

#endif // DETAILRELATIONALDELEGATE_H
