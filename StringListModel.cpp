#include "StringListModel.h"
#include <QVariant>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>

#include <QDebug>


StringListModel::StringListModel(const QVector<QStringList> &tableData, QObject *parent)
    :table(tableData),QAbstractTableModel(parent)
{}

StringListModel::StringListModel(QObject *parent)
    :QAbstractTableModel(parent)
{}

int StringListModel::setHead(QStringList &headData)
{
    head=headData;
    return head.count();
}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    return table.count();   //每一个QStringList是一行,Vector中的行数
}

int StringListModel::columnCount(const QModelIndex &parent) const
{
    return table.isEmpty()?0:table.first().count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole) {
        //获取值
        if(index.row()<table.count() && index.column() < this->columnCount()){
            return table[index.row()].at(index.column());
        }
    }
    return QVariant();
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal && section < head.count())
        return head[section];
    else
        return QString("Row %1").arg(section);
}

void StringListModel::clear()
{
    table.clear();
}
