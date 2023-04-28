
#ifndef MYEDIT_H
#define MYEDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QKeyEvent>

class MyEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyEdit(QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent* event);
    bool event(QEvent *event);
};

#endif // MYEDIT_H
