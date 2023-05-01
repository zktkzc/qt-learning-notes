
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QItemSelection>
#include <QAction>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getCurrentItem();
    void toggleSelection();
    void updateSelection(QItemSelection selected, QItemSelection deselected);
    void changeCurrent(QModelIndex current, QModelIndex previous);

private:
    Ui::MainWindow *ui;
    QTableView* table_view;
};

#endif // MAINWINDOW_H
