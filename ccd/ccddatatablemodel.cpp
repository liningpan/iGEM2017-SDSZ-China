#include "ccddatatablemodel.h"
#include <QDebug>
#include <QFlags>
CcdDataTableModel::CcdDataTableModel(QObject* parent) :
    QAbstractTableModel(parent)
{
    m_column = 0;
    m_row = 0;
}

CcdDataTableModel::~CcdDataTableModel(){
    qDeleteAll(m_data);
}

int CcdDataTableModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return m_row;
}

int CcdDataTableModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return m_column;
}

QVariant CcdDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "x";
        else
            return "y";
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant CcdDataTableModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole) {
        return m_data[index.column()]->at(index.row());
    } else if (role == Qt::BackgroundRole) {
        if(index.row() % 2 == 0){
            return QColor("#FEFEFE");
        }
        else{
            return QColor(Qt::white);
        }
    }
    return QVariant();
}

bool CcdDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid()){
        m_data[index.column()]->replace(index.row(),value.toDouble());
        emit(dataChanged(index,index));
    }
}

Qt::ItemFlags CcdDataTableModel::flags(const QModelIndex &index) const{
    return Qt::NoItemFlags;
}

bool CcdDataTableModel::insertRows(int row, int count, const QModelIndex &parent){
    if(row <= m_row){
        emit(beginInsertRows(parent, row ,row + count - 1));
        for(int i = 0; i < m_column; i ++){
            m_data[i]->insert(row,count,0);
            //qDebug()<<(m_data[i]->size() == m_row + count);
        }
        m_row += count;
        emit(endInsertRows());
        return true;
    }
    return false;
}

bool CcdDataTableModel::insertColumns(int column, int count, const QModelIndex &parent){
    if(column <= m_column){
        emit(beginInsertColumns(parent,column,column + count - 1));
        for(int i = 0; i < count; i ++){
            QVector<qreal>* da = new QVector<qreal>(m_row,0);
            m_data.insert(column + i,da);
        }
        m_column += count;
        emit(endInsertColumns());
        return true;
    }
    return false;
}

bool CcdDataTableModel::removeRows(int row, int count, const QModelIndex &parent){
    if(row + count - 1 <= m_row){
        emit(beginRemoveRows(parent,row,row + count - 1));
        for(int i = 0; i < m_column; i ++){
            m_data[i]->remove(row,count);
        }
        m_row -= count;
        emit(endRemoveRows());
        return true;
    }
    return false;
}

bool CcdDataTableModel::removeColumns(int column, int count, const QModelIndex &parent){
    if(column + count - 1 <= m_column){
        emit(beginRemoveColumns(parent,column,column + count + 1));
        for(int i = count - 1; i >= 0; i --){
            QVector<qreal>* da = m_data.at(column + i);
            m_data.removeAt(column + i);
            delete da;
        }
        emit(endRemoveColumns());
        return true;
    }
    return false;
}
