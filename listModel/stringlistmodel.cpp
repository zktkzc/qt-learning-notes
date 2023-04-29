
#include "stringlistmodel.h"

StringListModel::StringListModel(const QStringList &strings, QObject *parent)
    :QAbstractListModel(parent), stringList(strings)
{

}

// 根据索引获取数据
QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if(index.row() >= stringList.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return stringList.at(index.row());
    } else {
        return QVariant();
    }
}

// 编辑时自动调用该函数
bool StringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index); // 发送信号，同时view渲染，两个index分别是左上角索引和右下角索引
        return true;
    }
    return false;
}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    return stringList.count();
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return QString("Column %1").arg(section);
    } else {
        return QString("Row %1").arg(section);
    }
}

bool StringListModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    // 通知view，这个model有修改
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        stringList.insert(position + row, QString::number(row));
    }
    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // index有效，返回基本的标记，并且添加可编辑的标记
}
