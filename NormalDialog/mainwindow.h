#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QTimer>

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
    void on_colorBtn_clicked();

    void on_colorBtn_2_clicked();

    void on_textBtn_clicked();

    void on_intDlgBtn_clicked();

    void on_floatBtn_clicked();

    void on_itemBtn_clicked();

    void on_tipBtn_clicked();

    void on_pushButton_clicked();

    void on_updateProgressDialog();

    void on_cancleProgressDialog();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QProgressDialog* _progressDialog;
    QTimer* _timer;
    int _counter;
};
#endif // MAINWINDOW_H
