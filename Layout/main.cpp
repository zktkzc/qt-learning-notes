#include "login.h"
#include "register.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<Login> w = std::make_shared<Login>();
    w->InitSignals();
    w->show();
    return a.exec();
}
