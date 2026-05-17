#ifndef EQUIPMENTDIALOG_H
#define EQUIPMENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include "equipment.h"

class EquipmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentDialog(QWidget *parent = nullptr);
    void setEquipment(const Equipment& eq);
    Equipment getEquipment() const;

private slots:
    void accept() override;

private:
    QLineEdit *nameEdit;
    QLineEdit *typeEdit;
    QLineEdit *maintenanceInfoEdit;
    QLineEdit *lastServiceDateEdit;
};

#endif // EQUIPMENTDIALOG_H
