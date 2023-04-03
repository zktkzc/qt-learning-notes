#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QStringList>
#include <QMessageBox>
#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _counter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 颜色选择对话框
void MainWindow::on_colorBtn_clicked()
{
    QColorDialog colorDialog(Qt::blue, this);
    colorDialog.setOption(QColorDialog::ShowAlphaChannel);
    colorDialog.exec();
    QColor color = colorDialog.currentColor();
    qDebug() << "color is " << color;
}

// 文件对话框
void MainWindow::on_textBtn_clicked()
{
    QString path = QDir::currentPath();
    QString title = tr("文件对话框");
    QString filter = tr("文本文件(*.txt);;图片文件(*.jpg *.gif *.png);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this, title, path, filter);
    qDebug() << aFileName << Qt::endl;
}

// 整型输入对话框
void MainWindow::on_intDlgBtn_clicked()
{
    bool ok = false;
    auto intdata = QInputDialog::getInt(this, tr("数字输入对话框"), tr("请输入数字："), 200, -200, 400, 10, &ok);
    if (ok)
    {
        qDebug() << intdata << Qt::endl;
    }
}

// 浮点输入对话框
void MainWindow::on_floatBtn_clicked()
{
    bool ok = false;
    auto floatdata = QInputDialog::getDouble(this, tr("浮点输入对话框"), tr("请输入浮点数："), 0.1, -2, 4, 2, &ok);
    if (ok)
    {
        qDebug() << floatdata << Qt::endl;
    }
}

// 条目对话框
void MainWindow::on_itemBtn_clicked()
{
    QStringList items;
    items << tr("条目1") << tr("条目2");
    bool ok = false;
    auto itemData = QInputDialog::getItem(this, tr("条目对话框"), tr("请输入或选择条目："), items, 0, true, &ok);
    if (ok)
    {
        qDebug() << "item is " << itemData << Qt::endl;
    }
}

// 提示对话框
void MainWindow::on_tipBtn_clicked()
{
    auto ret = QMessageBox::question(this, tr("提问对话框"), tr("你是单身吗？"));
    if(ret == QMessageBox::Yes)
    {
        qDebug() << "ret is " << ret << Qt::endl;
        qDebug() << tr("你好，单身狗") << Qt::endl;
    }
    else
    {
        return;
    }

    auto ret2 = QMessageBox::information(this, tr("通知对话框"), tr("你好，单身狗"), QMessageBox::Yes);
    if (ret2 == QMessageBox::Yes)
        qDebug() << "ret2 is " << ret2 << Qt::endl;
    else
        return;

    auto ret3 = QMessageBox::warning(this, tr("警告对话框"), tr("你最好找个地方发泄一下"), QMessageBox::Yes);
    if (ret3 == QMessageBox::Yes)
        qDebug() << "ret3 is " << ret3 << Qt::endl;
    else
        return;

    auto ret4 = QMessageBox::critical(this, tr("关键提示对话框"), tr("我梦寐以求， 是真爱和自由"), QMessageBox::Ok);
    if (ret4 == QMessageBox::Ok)
        qDebug() << "ret4 is " << ret4 << Qt::endl;
}

// 进度对话框
void MainWindow::on_pushButton_clicked()
{
    _progressDialog = new QProgressDialog(tr("正在复制"), tr("取消复制"), 0, 5000, this);
    _progressDialog->setWindowTitle(tr("文件复制进度对话框"));
    _progressDialog->setWindowModality(Qt::ApplicationModal);
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::on_updateProgressDialog);
    connect(_progressDialog, &QProgressDialog::canceled, this, &MainWindow::on_cancleProgressDialog);
    _timer->start(2); // 启动定时器，每2毫秒更新一次
}

void MainWindow::on_updateProgressDialog()
{
    _counter++;
    if (_counter > 5000)
    {
        _timer->stop();
        delete _timer;
        _timer = nullptr;
        delete _progressDialog;
        _progressDialog = nullptr;
        _counter = 0;
        return;
    }

    _progressDialog->setValue(_counter);

}

void MainWindow::on_cancleProgressDialog()
{
    _timer->stop();
    delete _timer;
    _timer = nullptr;
    delete _progressDialog;
    _progressDialog = nullptr;
    _counter = 0;
    return;
}

// 向导对话框
void MainWindow::on_pushButton_2_clicked()
{
    QWizard wizard(this);
    wizard.setWindowTitle(tr("全城热恋"));
    auto page1 = new QWizardPage();
    page1->setTitle(tr("婚恋介绍引导程序"));
    auto label1 = new QLabel();
    label1->setText(tr("该程序将会帮助您找到人生伴侣"));
    auto layout = new QVBoxLayout();
    layout->addWidget(label1);
    page1->setLayout(layout);
    wizard.addPage(page1);

    QWizardPage* page2 = new QWizardPage();
    page2->setTitle(tr("选择心动类型"));
    auto group = new QButtonGroup(page2);
    auto btn1 = new QRadioButton();
    btn1->setText(tr("白富美"));
    group->addButton(btn1);

    auto btn2 = new QRadioButton();
    btn2->setText(tr("萝莉"));
    group->addButton(btn2);

    auto btn3 = new QRadioButton();
    btn3->setText(tr("御姐"));
    group->addButton(btn3);

    auto btn4 = new QRadioButton();
    btn4->setText(tr("小家碧玉"));
    group->addButton(btn4);

    auto btn5 = new QRadioButton();
    btn5->setText(tr("女汉子"));
    group->addButton(btn5);

    auto btn6 = new QRadioButton();
    btn6->setText(tr("成年人不做选择，我都要！"));
    group->addButton(btn6);

    auto layout2 = new QVBoxLayout();
    for (int i = 0; i < group->buttons().size(); ++i) {
        layout2->addWidget(group->buttons()[i]);
    }

    page2->setLayout(layout2);
    wizard.addPage(page2);

    auto page3 = new QWizardPage();
    page3->setTitle(tr("你的缘分即将到来！"));

    auto label3 = new QLabel();
    label3->setText(tr("感谢您的参与，接下来的一个月您会遇到对的人！"));

    auto layout3 = new QVBoxLayout();
    layout3->addWidget(label3);

    page3->setLayout(layout3);
    wizard.addPage(page3);

    wizard.show();
    wizard.exec();
}

