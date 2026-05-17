#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QJsonObject>

struct Equipment {
    QString name;
    QString type;
    QString maintenanceInfo;
    QString lastServiceDate;

    // Serialize to JSON
    QJsonObject toJson() const {
        QJsonObject json;
        json["name"] = name;
        json["type"] = type;
        json["maintenanceInfo"] = maintenanceInfo;
        json["lastServiceDate"] = lastServiceDate;
        return json;
    }

    // Deserialize from JSON
    static Equipment fromJson(const QJsonObject& json) {
        Equipment eq;
        eq.name = json["name"].toString();
        eq.type = json["type"].toString();
        eq.maintenanceInfo = json["maintenanceInfo"].toString();
        eq.lastServiceDate = json["lastServiceDate"].toString();
        return eq;
    }
};

#endif // EQUIPMENT_H
