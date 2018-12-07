#include "sortfilterproxymodel.h"

SortFilterProxyModel::SortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
}

void SortFilterProxyModel::setFilterKeyColumns(qint32 colNum)
{
    columnPatterns_.clear();

    for (qint32 i= 0; i < colNum; ++i)
        columnPatterns_.insert(i, QString());
}

void SortFilterProxyModel::addFilterFixedString(const QString &pattern)
{
    //if(!columnPatterns_.contains(column))
    //    return;
    qint32 count = columnPatterns_.size();
    for (qint32 i= 0; i < count; ++i)
        columnPatterns_[i] = pattern;
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
        rx.setCaseSensitivity(Qt::CaseInsensitive);
        rx.setPatternSyntax(QRegExp::Wildcard);
        QString f = index.data().toString();
        ret = rx.exactMatch(index.data().toString());

        if(ret)
            return ret;
    }

    return ret;
}
