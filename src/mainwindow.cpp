#include "mainwindow.h"
#include "equipmentdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    tableWidget = new QTableWidget(0, 4, this);
    tableWidget->setHorizontalHeaderLabels({"Name", "Type", "Maintenance Info", "Last Service Date"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add", this);
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);
    saveButton = new QPushButton("Save to File", this);
    loadButton = new QPushButton("Load from File", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);

    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
    resize(800, 600);
    setWindowTitle("Equipment Manager");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editRecord);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRecord);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);

    refreshTable();
}

MainWindow::~MainWindow()
{
}

void MainWindow::refreshTable()
{
    qDebug() << "Refreshing table...";
    tableWidget->setRowCount(0);
    tableWidget->setRowCount(equipmentList.size());
    int row = 0;
    for (const Equipment &eq : equipmentList) {
        tableWidget->setItem(row, 0, new QTableWidgetItem(eq.name));
        tableWidget->setItem(row, 1, new QTableWidgetItem(eq.type));
        tableWidget->setItem(row, 2, new QTableWidgetItem(eq.maintenanceInfo));
        tableWidget->setItem(row, 3, new QTableWidgetItem(eq.lastServiceDate));
        row++;
    }
    qDebug() << "Table refreshed, total rows:" << equipmentList.size();
}

void MainWindow::addRecord()
{
    qDebug() << "Add Record clicked. Opening dialog...";
    EquipmentDialog *dialog = new EquipmentDialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        qDebug() << "Dialog accepted. Appending data to QLinkedList...";
        Equipment eq = dialog->getEquipment();
        equipmentList.append(eq);
        qDebug() << "Data appended. Calling refreshTable...";
        refreshTable();
        qDebug() << "Add Record complete.";
    } else {
        qDebug() << "Dialog cancelled.";
    }
    dialog->deleteLater();
}

void MainWindow::editRecord()
{
    int row = tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Edit Record", "Please select a record to edit.");
        return;
    }

    auto it = equipmentList.begin();
    std::advance(it, row);

    EquipmentDialog dialog(this);
    dialog.setEquipment(*it);
    if (dialog.exec() == QDialog::Accepted) {
        *it = dialog.getEquipment();
        refreshTable();
    }
}

void MainWindow::deleteRecord()
{
    int row = tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Delete Record", "Please select a record to delete.");
        return;
    }

    auto it = equipmentList.begin();
    std::advance(it, row);
    equipmentList.erase(it);

    refreshTable();
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QJsonArray jsonArray;
    for (const Equipment &eq : equipmentList) {
        jsonArray.append(eq.toJson());
    }

    QJsonDocument doc(jsonArray);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file for writing.");
        return;
    }

    file.write(doc.toJson());
    file.close();
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Could not open file for reading.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        QMessageBox::critical(this, "Error", "Invalid JSON format.");
        return;
    }

    equipmentList.clear();
    QJsonArray jsonArray = doc.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject jsonObj = jsonArray[i].toObject();
        equipmentList.append(Equipment::fromJson(jsonObj));
    }

    refreshTable();
}
