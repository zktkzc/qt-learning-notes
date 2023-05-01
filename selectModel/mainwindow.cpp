
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel(7,4,this);
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 4; column++) {
            QStandardItem *item = new QStandardItem(QString("%1").arg(row * 4 + column));
            model->setItem(row, column,item);
        }
    }

    table_view = new QTableView();
    table_view->setModel(model);
    setCentralWidget(table_view); // 将table_view设置成mainwindow的中心构件
    this->resize(800,800);

    QItemSelectionModel *selection_model = table_view->selectionModel();
    // 定义左上角和右下角的索引
    QModelIndex topLeft;
    QModelIndex bottomRight;
    topLeft = model->index(1,1,QModelIndex());
    bottomRight = model->index(5,2,QModelIndex());

    // 设置选择区域
    QItemSelection selection(topLeft, bottomRight);
    selection_model->select(selection, QItemSelectionModel::Select);

    QTableView *table_view2;
    table_view2 = new QTableView();
    table_view2->setWindowTitle("tableView2");
    table_view2->resize(400,300);
    table_view2->setModel(model);
    table_view2->setSelectionModel(selection_model);
    table_view2->show();

    ui->mainToolBar->addAction(tr("当前项目"), this, &MainWindow::getCurrentItem);
    ui->mainToolBar->addAction(tr("切换选中"), this, &MainWindow::toggleSelection);

    // 选择模型的选择条目更改后触发updateSelection函数
    connect(selection_model, &QItemSelectionModel::selectionChanged, this, &MainWindow::updateSelection);
    // 选择模型改变后，当前项目也会改变，会触发changeCurrent函数
    connect(selection_model, &QItemSelectionModel::currentChanged, this, &MainWindow::changeCurrent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCurrentItem()
{
    auto currentData = table_view->selectionModel()->currentIndex().data().toString();
    qDebug() << tr("当前项目的内容：") << currentData;
}

void MainWindow::toggleSelection()
{
    // 找到根节点下第1行第1列的索引
    QModelIndex topLeft = table_view->model()->index(0,0,QModelIndex());
    auto max_row = table_view->model()->rowCount(QModelIndex());
    auto max_column = table_view->model()->columnCount(QModelIndex());
    // 根据行号和列号获取右下角item的索引
    QModelIndex bottomRight = table_view->model()->index(max_row-1,max_column-1,QModelIndex());
    // 设置选择区域
    QItemSelection curSelection(topLeft,bottomRight);
    table_view->selectionModel()->select(curSelection, QItemSelectionModel::Toggle);
}

void MainWindow::updateSelection(QItemSelection selected, QItemSelection deselected)
{
    QModelIndex index;
    QModelIndexList list = selected.indexes();
    for (int i = 0; i < list.size(); i++) {
        QString text = QString("(%1, %2)").arg(list[i].row()).arg(list[i].column());
        table_view->model()->setData(list[i], text);
    }

    list = deselected.indexes();
    foreach (index, list) {
        table_view->model()->setData(index, "");
    }
}

void MainWindow::changeCurrent(QModelIndex current, QModelIndex previous)
{
    qDebug() << tr("move(%1, %2) to (%3, %4)").arg(previous.row()).arg(previous.column()).arg(current.row()).arg(current.column());
}


