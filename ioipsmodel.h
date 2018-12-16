#ifndef IOIPSMODEL_H
#define IOIPSMODEL_H

#include <QAbstractListModel>

class IoipsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    IoipsModel(const QStringList &strings, QObject *parent = 0):
        QAbstractListModel(parent), stringList(strings) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        return stringList.count();
    }
    QVariant data(const QModelIndex &index, int role) const
    {
        if (!index.isValid())
            return QVariant();
        if (index.row() >= stringList.size())
            return QVariant();
        if (role == Qt::DisplayRole)
            return stringList.at(index.row());
        else
            return QVariant();
    }

private:
    QStringList stringList;

};

#endif // IOIPSMODEL_H
