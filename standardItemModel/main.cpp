
#include "mainwindow.h"

#include <QApplication>
#include <QStandardItemModel>
#include <QPixmap>
#include <QTreeView>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QStandardItemModel model;
    auto *parent_item = model.invisibleRootItem();
    QStandardItem *item0 = new QStandardItem();
    item0->setText("item0");
    QPixmap pixmap0(50,50);
    pixmap0.fill(Qt::red);
    item0->setIcon(pixmap0);
    item0->setToolTip("indexA");
    parent_item->appendRow(item0);

    parent_item = item0;

    QStandardItem *item1 = new QStandardItem();
    item1->setText("item1");
    QPixmap pixmap1(50,50);
    pixmap1.fill(Qt::blue);
    item1->setIcon(pixmap1);
    item1->setToolTip("indexB");
    parent_item->appendRow(item1);

    QStandardItem *item2 = new QStandardItem();
    item2->setText("item2");
    QPixmap pixmap2(50,50);
    pixmap2.fill(Qt::green);
    item2->setIcon(pixmap2);
    item2->setToolTip("indexC");
    parent_item->appendRow(item2);

    QStandardItem *item3 = new QStandardItem();
    item3->setData("item3",Qt::EditRole);
    item3->setData("indexD",Qt::ToolTipRole);
    QPixmap pixmap3(50,50);
    pixmap3.fill(Qt::yellow);
    item3->setData(QIcon(pixmap3), Qt::DecorationRole);
    parent_item->appendRow(item3);

    // 去除根节点下第0行第0列的item的模型索引
    QModelIndex indexA = model.index(0,0,QModelIndex()); // QModelIndex()表示根节点的index
    qDebug() << "model indexA row count is " << model.rowCount(indexA);

    // 获取indexA下的0行0列
    QModelIndex indexB = model.index(0,0,indexA);
    qDebug() << "indexB text is " << model.data(indexB, Qt::EditRole).toString();
    qDebug() << "indexB icon is " << model.data(indexB, Qt::DecorationRole);
    qDebug() << "indexB tool tip is " << model.data(indexB, Qt::ToolTipRole).toString();

    QTreeView view;
    view.setModel(&model);
    view.show();

    return a.exec();
}
