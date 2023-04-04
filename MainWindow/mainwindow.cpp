#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QActionGroup>
#include <QIcon>
#include <QKeySequence>
#include <QMdiSubWindow>
#include <QMenu>
#include <QMenu>
#include <QTextEdit>
#include <QToolButton>
#include <QSpinBox>
#include <QLabel>
#include "myaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu* editMenu = ui->menubar->addMenu(tr("编辑(&E)"));
    editMenu->addSeparator();
    QAction* action_open = editMenu->addAction(QIcon(":/res/edit.png"), tr("打开文件(&O)"));
    action_open->setShortcut(QKeySequence("Ctrl+O"));
    connect(action_open, &QAction::triggered, this, &MainWindow::on_actionedit_triggered);

    auto group = new QActionGroup(this);
    auto action_L = group->addAction(tr("左对齐(&L)"));
    action_L->setCheckable(true);
    auto action_R = group->addAction(tr("右对齐(&R)"));
    action_R->setCheckable(true);
    auto action_C = group->addAction(tr("居中对齐(&C)"));
    action_C->setCheckable(true);
    editMenu->addSeparator();
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);
    editMenu->addSeparator();
    MyAction* action = new MyAction(this);
    editMenu->addAction(action);
    connect(action, &MyAction::getText, this, &MainWindow::slot_set_text);

    QToolButton* toolBtn = new QToolButton(this);
    toolBtn->setText(tr("颜色"));
    ui->toolBar->addWidget(toolBtn);
    QMenu* colorMenu = new QMenu(this);
    colorMenu->addAction(tr("红色"));
    colorMenu->addAction(tr("绿色"));
    toolBtn->setMenu(colorMenu);
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar->addSeparator();
    QSpinBox* spinBox = new QSpinBox(this);
    ui->toolBar->addWidget(spinBox);

    ui->statusbar->showMessage(tr("欢迎使用多文档编辑器"), 2000); // 显示2秒
    // 永久显示
    QLabel* permnant = new QLabel(this);
    permnant->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permnant->setText(tr("By tkzc00."));
    ui->statusbar->addPermanentWidget(permnant);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionshowdock_D_triggered()
{
    ui->dockWidget->show();
}

void MainWindow::on_actionedit_triggered()
{
    qDebug() << "点击打开文件菜单项" << Qt::endl;
}


void MainWindow::on_actionNew_N_triggered()
{
    QTextEdit* textEdit = new QTextEdit(this);
    auto childWindow = ui->mdiArea->addSubWindow(textEdit);
    childWindow->setWindowTitle(tr("文本编辑子窗口"));
    childWindow->show();
}

void MainWindow::slot_set_text(const QString &string)
{
    ui->textEdit->setText(string);
}

