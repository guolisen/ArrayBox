#ifndef DETAILRELATIONALDELEGATE_H
#define DETAILRELATIONALDELEGATE_H
#include <map>
#include <QModelIndex>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QStyledItemDelegate>
#include <QItemDelegate>

typedef std::map<QString, QStringList> IoipsModelMap;

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
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

private:
    QSqlRelationalTableModel* model_;

};

#endif // DETAILRELATIONALDELEGATE_H
