#ifndef EQUIPMENTTABLEMODEL_H
#define EQUIPMENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QLinkedList>
#include "equipment.h"

class EquipmentTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit EquipmentTableModel(QObject *parent = nullptr);

    // Basic functionality required by QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Methods to interact with the underlying data
    void addEquipment(const Equipment &eq);
    void updateEquipment(int row, const Equipment &eq);
    void removeEquipment(int row);

    // Retrieve equipment at specific row
    Equipment getEquipment(int row) const;

    // File operations
    const QLinkedList<Equipment>& getList() const;
    void setList(const QLinkedList<Equipment>& newList);

private:
    QLinkedList<Equipment> equipmentList;
    QStringList headers;
};

#endif // EQUIPMENTTABLEMODEL_H
