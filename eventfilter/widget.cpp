
#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QWheelEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    line_edit = new MyEdit(this);
    line_edit->move(100,100);
    line_edit->installEventFilter(this); // 安装父节点的事件过滤器
    ui->textEdit->installEventFilter(this);
    ui->spinBox->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressDown(QKeyEvent *event)
{
    qDebug() << "Widget key press down";
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == line_edit) {
        if (event->type() == QEvent::KeyPress) {
            qDebug() << "widget eventFilter catch line_edit";
            return false;
        }
    }

    if (watched == ui->textEdit) {
        if (event->type() == QEvent::Wheel) {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
            if (wheelEvent->delta() > 0) {
                qDebug() << "catch wheel event delta > 0";
                ui->textEdit->zoomIn(); // 缩小
            } else {
                qDebug() << "catch wheel event delta < 0";
                ui->textEdit->zoomOut(); // 放大
            }
            return true;
        }
        return false;
    }

    return QWidget::eventFilter(watched, event);
}


