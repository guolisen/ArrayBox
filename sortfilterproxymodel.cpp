#include "sortfilterproxymodel.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

void SortFilterProxyModel::setFilterKeyColumns(const QList<qint32> &filterColumns)
{
    columnPatterns_.clear();

    foreach(qint32 column, filterColumns)
        columnPatterns_.insert(column, QString());
}

void SortFilterProxyModel::addFilterFixedString(qint32 column, const QString &pattern)
{
    if(!columnPatterns_.contains(column))
        return;

    columnPatterns_[column] = pattern;
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(columnPatterns_.isEmpty())
        return true;

    bool ret = false;

    for(QMap<qint32, QString>::const_iterator iter = columnPatterns_.constBegin();
    iter != columnPatterns_.constEnd();
    ++iter)
    {
        QModelIndex index = sourceModel()->index(sourceRow, iter.key(), sourceParent);
        QRegExp rx(iter.value());
        rx.setPatternSyntax(QRegExp::Wildcard);
        QString f = index.data().toString();
        ret = rx.exactMatch(index.data().toString());

        if(ret)
            return ret;
    }

    return ret;
}
