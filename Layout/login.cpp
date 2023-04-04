#include "login.h"
#include "register.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

// 初始化信号
void Login::InitSignals()
{
    _register = std::make_shared<Register>();
    _register->Set_login(shared_from_this()); // shared_from_this会返回一个Login的智能指针，与引用Login类的只能指针共享引用计数
}


void Login::on_pushButton_2_clicked()
{
    this->close();
    _register->show();
}

