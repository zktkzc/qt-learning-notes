
#include "widget.h"
#include "ui_widget.h"
#include <QCursor>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下
    if (event->button() == Qt::LeftButton)
    {
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor); // 这种方式设置鼠标样式可以回退
        offset = event->globalPos() - pos(); // 鼠标在窗口的位置 = 鼠标在全局的位置 - 窗口的位置(左上角)
    } else if (event->button() == Qt::RightButton) {
        QCursor cursor(QPixmap(":/res/mouse.png"));
        QApplication::setOverrideCursor(cursor);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (windowState() == Qt::WindowFullScreen) {
            setWindowState(Qt::WindowNoState);
        } else {
            setWindowState(Qt::WindowFullScreen);
        }
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    // 在鼠标移动过程中保证窗口也移动
    if (event->buttons() & Qt::LeftButton) {
        QPoint windows = event->globalPos() - offset;
        this->move(windows);
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        ui->textEdit->zoomIn();
    } else {
        ui->textEdit->zoomOut();
    }
}


