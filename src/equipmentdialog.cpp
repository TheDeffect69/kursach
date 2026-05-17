#include "equipmentdialog.h"
#include <QMessageBox>
#include <QVBoxLayout>

EquipmentDialog::EquipmentDialog(QWidget *parent)
    : QDialog(parent)
{
    nameEdit = new QLineEdit(this);
    typeEdit = new QLineEdit(this);
    maintenanceInfoEdit = new QLineEdit(this);
    lastServiceDateEdit = new QLineEdit(this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Name:", nameEdit);
    formLayout->addRow("Type:", typeEdit);
    formLayout->addRow("Maintenance Info:", maintenanceInfoEdit);
    formLayout->addRow("Last Service Date:", lastServiceDateEdit);

    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &EquipmentDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &EquipmentDialog::reject);

    setWindowTitle("Equipment Details");
}

void EquipmentDialog::setEquipment(const Equipment& eq)
{
    nameEdit->setText(eq.name);
    typeEdit->setText(eq.type);
    maintenanceInfoEdit->setText(eq.maintenanceInfo);
    lastServiceDateEdit->setText(eq.lastServiceDate);
}

Equipment EquipmentDialog::getEquipment() const
{
    Equipment eq;
    eq.name = nameEdit->text();
    eq.type = typeEdit->text();
    eq.maintenanceInfo = maintenanceInfoEdit->text();
    eq.lastServiceDate = lastServiceDateEdit->text();
    return eq;
}

void EquipmentDialog::accept()
{
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Name cannot be empty.");
        return;
    }
    QDialog::accept();
}
