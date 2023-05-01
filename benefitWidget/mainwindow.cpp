
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto *listWidget = new QListWidget(this);
    auto *listWidgetItem = new QListWidgetItem();
    listWidgetItem->setText("listItem");
    QPixmap pixmap(50,50);
    pixmap.fill(Qt::blue);
    listWidgetItem->setIcon(pixmap);
    listWidgetItem->setToolTip("this is list item");
    listWidget->insertItem(0, listWidgetItem);

    auto *listWidgetItem2 = new QListWidgetItem();
    listWidgetItem2->setText("listItem2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    listWidgetItem2->setIcon(pixmap2);
    listWidgetItem2->setToolTip("this is list item2");
    listWidget->insertItem(1, listWidgetItem2);

    listWidget->setSortingEnabled(true);
    listWidget->sortItems(Qt::DescendingOrder);
    listWidget->show();
    this->setCentralWidget(listWidget);

    // 设置拖放
    listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    listWidget->setDragEnabled(true);
    listWidget->viewport()->setAcceptDrops(true);
    listWidget->setDropIndicatorShown(true);
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(2);
    QStringList headers;
    headers << "name" << "year";
    treeWidget->setHeaderLabels(headers);

    auto *grade1 = new QTreeWidgetItem(treeWidget);
    grade1->setText(0, "Grade1");

    QTreeWidgetItem *student = new QTreeWidgetItem(grade1);
    student->setText(0, "Tom");
    student->setText(1, "1996");

    QTreeWidgetItem *student2 = new QTreeWidgetItem(grade1, student);
    student2->setText(0, "Zack");
    student2->setText(1, "1988");

    auto *grade2 = new QTreeWidgetItem(treeWidget, grade1);
    grade2->setText(0, "Grade2");
    QTreeWidgetItem *student3 = new QTreeWidgetItem(grade1, student2);
    student3->setText(0, "Will");
    student3->setText(1, "1989");

    // 删除student3节点
    auto *parent_student3 = student3->parent();
    auto index_student3 = parent_student3->indexOfChild(student3);
    delete parent_student3->takeChild(index_student3);

    // 删除grade2节点
    auto *parent_grade2 = grade2->parent();
    assert(parent_grade2 == nullptr);
    auto index_grade2 = treeWidget->indexOfTopLevelItem(grade2);
    delete treeWidget->takeTopLevelItem(index_grade2);

    treeWidget->show();

    tableWidget = new QTableWidget(3,2);
    QTableWidgetItem *tableWidgetItem = new QTableWidgetItem("qt");
    tableWidget->setItem(1,1,tableWidgetItem);
    QTableWidgetItem *headerV = new QTableWidgetItem("first");
    tableWidget->setVerticalHeaderItem(0,headerV);
    QTableWidgetItem *headerH = new QTableWidgetItem("ID");
    tableWidget->setHorizontalHeaderItem(0, headerH);
    tableWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete treeWidget;
    delete tableWidget;
}


