
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus); // 点击窗口就自动聚焦

    // 定时器
    // 第一种方式
    id1 = startTimer(1000);
    id2 = startTimer(1500);
    id3 = startTimer(2000);

    // 第二种方式
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::slot_update_led);
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
    // 回收资源
    killTimer(id1);
    killTimer(id2);
    killTimer(id3);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_M && windowState() != Qt::WindowFullScreen) {
            setWindowState(Qt::WindowFullScreen);
            return;
        }
        return;
    }

    if (event->key() == Qt::Key_Escape && windowState() == Qt::WindowFullScreen) {
        setWindowState(Qt::WindowNoState);
        return;
    }

    bool b_upflag = false;
    bool b_downflag = false;
    bool b_leftflag = false;
    bool b_rightflag = false;

    if (event->key() == Qt::Key_Up) {
        if (event->isAutoRepeat()) {
            auto cur_pos = ui->pushButton->pos();
            cur_pos.setY(cur_pos.y() - 5);
            ui->pushButton->move(cur_pos);
            return;
        } else {
            b_upflag = true;
        }
    }

    if (event->key() == Qt::Key_Left) {
        if (event->isAutoRepeat()) {
            auto cur_pos = ui->pushButton->pos();
            cur_pos.setX(cur_pos.x() - 5);
            ui->pushButton->move(cur_pos);
            return;
        } else {
            b_leftflag = true;
        }
    }

    if (event->key() == Qt::Key_Down) {
        if (event->isAutoRepeat()) {
            auto cur_pos = ui->pushButton->pos();
            cur_pos.setY(cur_pos.y() + 5);
            ui->pushButton->move(cur_pos);
            return;
        } else {
            b_downflag = true;
        }
    }

    if (event->key() == Qt::Key_Right) {
        if (event->isAutoRepeat()) {
            auto cur_pos = ui->pushButton->pos();
            cur_pos.setX(cur_pos.x() + 5);
            ui->pushButton->move(cur_pos);
            return;
        } else {
            b_rightflag = true;
        }
    }

    auto cur_pos = ui->pushButton->pos();
    if (b_upflag) {
        cur_pos.setY(cur_pos.y() - 5);
    }
    if (b_downflag) {
        cur_pos.setY(cur_pos.y() + 5);
    }
    if (b_leftflag) {
        cur_pos.setX(cur_pos.x() - 5);
    }
    if (b_rightflag) {
        cur_pos.setX(cur_pos.x() + 5);
    }
    ui->pushButton->move(cur_pos);
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1) {
        qDebug() << "id1 timer triggered";
    }

    if (event->timerId() == id2) {
        qDebug() << "id2 timer triggered";
    }

    if (event->timerId() == id3) {
        qDebug() << "id3 timer triggered";
    }
}

void Widget::slot_update_led()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    // qDebug() << "current time is " << text;
    if (time.second()%2 == 0) {
        text[5] = ' ';
        text[2] = ' ';
    }
    ui->lcdNumber->setDigitCount(text.length());
    ui->lcdNumber->display(text);
}


