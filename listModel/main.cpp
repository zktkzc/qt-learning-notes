
#include "mainwindow.h"
#include "stringlistmodel.h"
#include <QStringList>
#include <QListView>
#include <QTableView>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QStringList list;
    list << "a" << "b" << "c";
    StringListModel model(list);
    model.insertRows(3,2);
    model.removeRows(1,1);

    QTableView tableView;
    tableView.setModel(&model);
    tableView.show();

    QListView listView;
    listView.setModel(&model);
    listView.show();

    return a.exec();
}
