
#include "myedit.h"
#include <QDebug>

MyEdit::MyEdit(QWidget *parent) : QLineEdit(parent)
{

}

void MyEdit::keyPressEvent(QKeyEvent * event)
{
    qDebug() << "MyEdit key press event";
    QLineEdit::keyPressEvent(event);
    event->ignore(); // 将事件传递给父节点
}

bool MyEdit::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        qDebug()<<"my edit event";
        return false; // 返回false时还会调用父节点的处理，返回true则不会调用
    }
    // 如果不是按键事件就调用基类的event来处理
    return QLineEdit::event(event);
}
