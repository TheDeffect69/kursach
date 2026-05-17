#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLinkedList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "equipment.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addRecord();
    void editRecord();
    void deleteRecord();
    void saveToFile();
    void loadFromFile();

private:
    void refreshTable();

    QLinkedList<Equipment> equipmentList;

    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
};

#endif // MAINWINDOW_H
