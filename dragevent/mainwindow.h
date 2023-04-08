
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>
#include <QDropEvent>
#include <QList>
#include <QString>
#include <QUrl>
#include <QTextCodec>
#include <QTextStream>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void dragEnterEvent(QDragEnterEvent* event);
    virtual void dropEvent(QDropEvent* event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
