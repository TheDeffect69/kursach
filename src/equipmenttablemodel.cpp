#include "equipmenttablemodel.h"

EquipmentTableModel::EquipmentTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    headers << "Name" << "Type" << "Maintenance Info" << "Last Service Date";
}

int EquipmentTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return equipmentList.size();
}

int EquipmentTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.size();
}

QVariant EquipmentTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        int row = index.row();
        int col = index.column();

        auto it = equipmentList.begin();
        std::advance(it, row);

        switch (col) {
            case 0: return it->name;
            case 1: return it->type;
            case 2: return it->maintenanceInfo;
            case 3: return it->lastServiceDate;
            default: return QVariant();
        }
    }

    return QVariant();
}

QVariant EquipmentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section >= 0 && section < headers.size()) {
            return headers.at(section);
        }
    }
    return QVariant();
}

void EquipmentTableModel::addEquipment(const Equipment &eq)
{
    beginInsertRows(QModelIndex(), equipmentList.size(), equipmentList.size());
    equipmentList.append(eq);
    endInsertRows();
}

void EquipmentTableModel::updateEquipment(int row, const Equipment &eq)
{
    if (row < 0 || row >= equipmentList.size()) return;

    auto it = equipmentList.begin();
    std::advance(it, row);
    *it = eq;

    // Notify the view that data changed for this specific row across all columns
    QModelIndex topLeft = index(row, 0);
    QModelIndex bottomRight = index(row, columnCount() - 1);
    emit dataChanged(topLeft, bottomRight);
}

void EquipmentTableModel::removeEquipment(int row)
{
    if (row < 0 || row >= equipmentList.size()) return;

    beginRemoveRows(QModelIndex(), row, row);
    auto it = equipmentList.begin();
    std::advance(it, row);
    equipmentList.erase(it);
    endRemoveRows();
}

Equipment EquipmentTableModel::getEquipment(int row) const
{
    if (row < 0 || row >= equipmentList.size()) return Equipment();

    auto it = equipmentList.begin();
    std::advance(it, row);
    return *it;
}

const QLinkedList<Equipment>& EquipmentTableModel::getList() const
{
    return equipmentList;
}

void EquipmentTableModel::setList(const QLinkedList<Equipment>& newList)
{
    beginResetModel();
    equipmentList = newList;
    endResetModel();
}
