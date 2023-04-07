#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCursor>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextFrameFormat>
#include <QAction>
#include <QDebug>
#include <QTextBlockFormat>
#include <QTextTableFormat>
#include <QTextListFormat>
#include <QTextImageFormat>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 获取文档
    QTextDocument* doc = ui->textEdit->document();
    // 获取框架
    QTextFrame* root_frame = doc->rootFrame();
    // 创建框架样式
    QTextFrameFormat format;
    // 设置样式
    format.setBorderBrush(Qt::blue);
    format.setBorder(3);
    root_frame->setFrameFormat(format);

    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray); // 设置背景颜色
    frameFormat.setMargin(10); // 设置外边距
    frameFormat.setPadding(5); // 设置内边距
    frameFormat.setBorder(2); // 设置边框宽度
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Dashed); // 设置边框为虚线
    QTextCursor cursor = ui->textEdit->textCursor(); // 获取光标位置
    cursor.insertFrame(frameFormat); // 在光标位置插入样式
    ui->textEdit->insertPlainText("inner text!\n");
    ui->textEdit->insertPlainText("Hello inner text!\n");

    QAction* action_frame = new QAction("Frame", this);
    connect(action_frame, &QAction::triggered, this, &MainWindow::showTextFrame);
    ui->toolBar->addAction(action_frame);

    QAction* action_textBlock = new QAction(tr("文本块"), this);
    connect(action_textBlock, &QAction::triggered, this, &MainWindow::showTextBlock);
    ui->toolBar->addAction(action_textBlock);

    QAction* action_font = new QAction(tr("字体"), this);
    action_font->setCheckable(true);
    connect(action_font, &QAction::toggled, this, &MainWindow::setTextFont);
    ui->toolBar->addAction(action_font);

    QAction* action_textTable = new QAction(tr("表格"), this);
    QAction* action_textList = new QAction(tr("列表"), this);
    QAction* action_textImage = new QAction(tr("图片"), this);
    connect(action_textTable, &QAction::triggered, this, &MainWindow::insertTable);
    connect(action_textList, &QAction::triggered, this, &MainWindow::insertList);
    connect(action_textImage, &QAction::triggered, this, &MainWindow::insertImage);
    ui->toolBar->addAction(action_textTable);
    ui->toolBar->addAction(action_textList);
    ui->toolBar->addAction(action_textImage);

    QAction* action_textFind = new QAction(tr("查找"), this);
    connect(action_textFind, &QAction::triggered, this, &MainWindow::textFind);
    ui->toolBar->addAction(action_textFind);

    findDialog = new QDialog(this);
    lineEdit = new QLineEdit(findDialog);
    QPushButton* btn = new QPushButton(findDialog);
    btn->setText(tr("查找下一个"));
    connect(btn, &QPushButton::clicked, this, &MainWindow::findNext);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    findDialog->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{
    auto doc = ui->textEdit->document();
    auto rootFrame = doc->rootFrame();
    for (auto iter = rootFrame->begin(); iter != rootFrame->end(); iter++)
    {
        auto cur_frame = iter.currentFrame();
        auto cur_block = iter.currentBlock();
        if(cur_frame)
        {
            qDebug() << "cur node is frame.";
        }
        else if (cur_block.isValid())
        {
            qDebug() << "cur node is text block, text is " << cur_block.text();
        }
    }
}

void MainWindow::showTextBlock()
{
    QTextDocument* document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();
    for (int i = 0; i < document->blockCount(); i++)
    {
        qDebug() << tr("文本块%1，文本块首行行号%2，长度%3，内容%4")
                    .arg(i)
                    .arg(block.firstLineNumber())
                    .arg(block.length())
                    .arg(block.text());
        block = block.next();
    }
}

void MainWindow::setTextFont(bool checked)
{
    if (checked)
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter);
        cursor.insertBlock(blockFormat);
        QTextCharFormat charFormat;
        charFormat.setBackground(Qt::lightGray);
        charFormat.setForeground(Qt::blue);
        charFormat.setFont(QFont(tr("宋体"), 12, QFont::Bold, true));
        charFormat.setFontUnderline(true);
        cursor.setCharFormat(charFormat);
        cursor.insertText(tr("插入字体"));
    }
    else
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignLeft);
        cursor.insertBlock(blockFormat);
        QTextCharFormat charFormat;
        cursor.setCharFormat(charFormat);
        cursor.insertText(tr("微软雅黑字体"));
    }
}

void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setCellSpacing(2); // 表格与表格之间的间距
    format.setCellPadding(10); // 表格内容与边框的间距
    cursor.insertTable(2, 2, format);
}

void MainWindow::insertList()
{
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal);
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertImage()
{
    QTextImageFormat format;
    format.setName(":/res/dock.png");
    ui->textEdit->textCursor().insertImage(format);
}

void MainWindow::textFind()
{
    findDialog->show();
}

void MainWindow::findNext()
{
    QString s = lineEdit->text();
    bool isFind = ui->textEdit->find(s, QTextDocument::FindBackward);
    if (isFind)
    {
        qDebug() << tr("行号：%1，列号：%2")
            .arg(ui->textEdit->textCursor().blockNumber())
            .arg(ui->textEdit->textCursor().columnNumber());
    }
}

