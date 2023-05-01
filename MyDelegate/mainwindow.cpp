
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto *model = new QStandardItemModel(7,4,this);
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 4; column++) {
            QStandardItem *item = new QStandardItem(QString("%1").arg(row*4+column));
            model->setItem(row, column, item);
        }
    }

    QTableView *table_view = new QTableView();
    table_view->setModel(model);
    setCentralWidget(table_view);
    this->resize(800,800);

    auto *model2 = new QStandardItemModel(7,4,this);
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 4; column++) {
            QStandardItem *item = new QStandardItem(QString("%1").arg(row*4+column));
            model2->setItem(row, column, item);
        }
    }

    auto *delegate = new SpinBoxDelegate(this);

    table_view2 = new QTableView();
    table_view2->setModel(model2);
    table_view2->setItemDelegate(delegate); // 设置代理
    table_view2->show();
    table_view2->resize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete table_view2;
}


