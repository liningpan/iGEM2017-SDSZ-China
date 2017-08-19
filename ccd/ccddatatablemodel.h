#ifndef CCDDATATABLEMODEL_H
#define CCDDATATABLEMODEL_H
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QVector>
#include <QColor>
#include <QModelIndex>

class CcdDataTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CcdDataTableModel(QObject* parent=0);
    virtual ~CcdDataTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool insertColumns(int column, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    bool removeColumns(int column, int count, const QModelIndex &parent);

private:
    QList<QVector<qreal>*> m_data;
    int m_row;
    int m_column;
};

#endif // CCDDATATABLEMODEL_H
