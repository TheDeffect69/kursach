#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "equipmenttablemodel.h"

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
    EquipmentTableModel *tableModel;
    QTableView *tableView;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
};

#endif // MAINWINDOW_H
