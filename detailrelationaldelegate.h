#ifndef DETAILRELATIONALDELEGATE_H
#define DETAILRELATIONALDELEGATE_H

#include <QModelIndex>
#include <QSqlRelationalDelegate>

class DetailRelationalDelegate : public QSqlRelationalDelegate
{
public:
    DetailRelationalDelegate(QObject *parent, QSqlRelationalTableModel* model);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    QSqlRelationalTableModel* model_;
};

#endif // DETAILRELATIONALDELEGATE_H
