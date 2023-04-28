
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QObject>
#include <QEvent>
#include "myedit.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void keyPressDown(QKeyEvent* event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Widget *ui;
    MyEdit* line_edit;
};

#endif // WIDGET_H
