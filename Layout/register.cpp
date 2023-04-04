#include "login.h"
#include "register.h"
#include "ui_register.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setMaximumSize(QSize(400, 550));
    this->setMinimumSize(QSize(400, 550));
    auto vbox_layout = new QVBoxLayout();
    auto verticalSpacer1 = new QSpacerItem(40, 20,QSizePolicy::Minimum,QSizePolicy::Expanding);
    vbox_layout->addItem(verticalSpacer1);

    QLabel* name_label = new QLabel();
    name_label->setText(tr("邮箱："));
    QSpacerItem* name_item1 = new QSpacerItem(80,20,QSizePolicy::Fixed,QSizePolicy::Minimum);
    QSpacerItem* name_item2 = new QSpacerItem(80,20,QSizePolicy::Fixed,QSizePolicy::Minimum);
    QLineEdit* name_edit = new QLineEdit();
    auto name_layout = new QHBoxLayout();
    name_layout->addItem(name_item1);
    name_layout->addWidget(name_label);
    name_layout->addWidget(name_edit);
    name_layout->addItem(name_item2);
    vbox_layout->addLayout(name_layout);

    this->setLayout(vbox_layout);

    auto verticalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Maximum,QSizePolicy::Maximum);
    vbox_layout->addItem(verticalSpacer2);

    QSpacerItem* pwd_item1 = new QSpacerItem(80,20,QSizePolicy::Fixed,QSizePolicy::Minimum);
    QSpacerItem* pwd_item2 = new QSpacerItem(80,20,QSizePolicy::Fixed,QSizePolicy::Minimum);

    auto pwd_layout = new QHBoxLayout();
    QLabel* pwd_label = new QLabel();
    pwd_label->setText(tr("密码："));
    QLineEdit* pwd_edit = new QLineEdit();
    pwd_layout->addItem(pwd_item1);
    pwd_layout->addWidget(pwd_label);
    pwd_layout->addWidget(pwd_edit);
    pwd_layout->addItem(pwd_item2);
    vbox_layout->addLayout(pwd_layout);

    auto verticalSpacer3 = new QSpacerItem(40, 20, QSizePolicy::Fixed,QSizePolicy::Maximum);
    vbox_layout->addItem(verticalSpacer3);

    QSpacerItem* reg_btn_item1 = new QSpacerItem(150,20,QSizePolicy::Fixed,QSizePolicy::Minimum);
    QSpacerItem* reg_btn_item2 = new QSpacerItem(150,20,QSizePolicy::Fixed,QSizePolicy::Minimum);

    auto _reg_btn = new QPushButton();
    _reg_btn->setText(tr("注册"));
    auto regbtn_layout = new QHBoxLayout();
    regbtn_layout->addItem(reg_btn_item1);
    regbtn_layout->addWidget(_reg_btn,5);
    regbtn_layout->addItem(reg_btn_item2);
    vbox_layout->addLayout(regbtn_layout);

    auto verticalSpacer4 = new QSpacerItem(40, 20, QSizePolicy::Fixed,QSizePolicy::Expanding);
    vbox_layout->addItem(verticalSpacer4);

    connect(_reg_btn, &QPushButton::clicked, this, &Register::Slot_register);
}
Register::~Register()
{
    delete ui;
}

void Register::Set_login(const std::weak_ptr<Login> &login)
{
    _login = login;
}

void Register::Slot_register()
{
    this->close();
    auto shared_login = _login.lock(); // lock方法不会增加引用计数
    shared_login->show();
}
