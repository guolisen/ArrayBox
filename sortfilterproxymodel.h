#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QtCore/qsortfilterproxymodel.h>

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SortFilterProxyModel(QObject *parent);
    void setFilterKeyColumns(const QList<qint32> &filterColumns);
    void addFilterFixedString(qint32 column, const QString &pattern);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    QMap<qint32, QString> columnPatterns_;
};

#endif // SORTFILTERPROXYMODEL_H
