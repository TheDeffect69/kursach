#include "mainwindow.h"
#include "equipmentdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    tableModel = new EquipmentTableModel(this);

    tableView = new QTableView(this);
    tableView->setModel(tableModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

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

    mainLayout->addWidget(tableView);
    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
    resize(800, 600);
    setWindowTitle("Equipment Manager");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editRecord);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteRecord);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);
}

MainWindow::~MainWindow()
{
}

void MainWindow::addRecord()
{
    EquipmentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Equipment eq = dialog.getEquipment();
        tableModel->addEquipment(eq);
    }
}

void MainWindow::editRecord()
{
    QModelIndex currentIndex = tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Edit Record", "Please select a record to edit.");
        return;
    }

    int row = currentIndex.row();
    Equipment currentEq = tableModel->getEquipment(row);

    EquipmentDialog dialog(this);
    dialog.setEquipment(currentEq);
    if (dialog.exec() == QDialog::Accepted) {
        tableModel->updateEquipment(row, dialog.getEquipment());
    }
}

void MainWindow::deleteRecord()
{
    QModelIndex currentIndex = tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "Delete Record", "Please select a record to delete.");
        return;
    }

    tableModel->removeEquipment(currentIndex.row());
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    const QLinkedList<Equipment>& currentList = tableModel->getList();
    QJsonArray jsonArray;
    for (const Equipment &eq : currentList) {
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

    QLinkedList<Equipment> newList;
    QJsonArray jsonArray = doc.array();
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject jsonObj = jsonArray[i].toObject();
        newList.append(Equipment::fromJson(jsonObj));
    }

    tableModel->setList(newList);
}
