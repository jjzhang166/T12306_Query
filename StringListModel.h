#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QVector>
#include <QAbstractTableModel>

class QVariant;
class QModelIndex;
class QStringList;
class QObject;

class StringListModel : public QAbstractTableModel
{
public:
    StringListModel(const QVector<QStringList> &tableData, QObject *parent = 0);
    StringListModel(QObject *parent = 0);

    int setHead(QStringList& headData);

    // rowCount()返回model中的行数
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    // columnCount()返回model中的列数
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    //data()返回与特定model index对应的数据项
    QVariant data(const QModelIndex &index, int role) const;

    //具有良好行为的model也会实现headerData()，它返回tree和table views需要的，在标题中显示的数据。
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    // 因为这是一个非层次结构的model,我们不必考虑父子关系。假如model具有层次结构，我们也应该实现index()与parent()函数。
    //清除数据
    void clear();

private:
    QVector<QStringList> table;
    QStringList head;
};

#endif // STRINGLISTMODEL_H
