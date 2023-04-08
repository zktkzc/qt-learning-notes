
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        // qDebug() << "event url is " << event->mimeData()->urls()[0].toLocalFile() << Qt::endl;
        event->acceptProposedAction();
    }
    else
    {
        event->ignore(); // 忽略事件，抛给其他控件处理
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    // 判断是否包含url
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        // 将第一个匹配的文件路径获取
        QString filename = urlList[0].toLocalFile();
        // qDebug() << filename << Qt::endl;
        if (!filename.isEmpty())
        {
            QTextCodec* codec = QTextCodec::codecForName("UTF-8");
            QFile file(filename);
            if (!file.open(QIODevice::ReadOnly))
            {
                return;
            }
            QTextCodec::setCodecForLocale(codec);
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
        }
    }
    else
    {
        event->ignore();
    }
}


