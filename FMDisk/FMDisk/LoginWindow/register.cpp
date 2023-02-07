#include "register.h"
#include "ui_login.h"

Register::Register(QWidget *parent)
{

}

Register::~Register()
{

}

void Register::init()
{
    ui->reg_pwd->setEchoMode(QLineEdit::Password);
    ui->reg_surepwd->setEchoMode(QLineEdit::Password);
    ui->reg_usr->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->reg_nickname->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->reg_pwd->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");
    ui->reg_surepwd->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");

#if 1
    // 测试数据
    ui->reg_usr->setText("kevin_666");
    ui->reg_nickname->setText("kevin@666");
    ui->reg_pwd->setText("123456");
    ui->reg_surepwd->setText("123456");
    ui->reg_phone->setText("11111111111");
    ui->reg_mail->setText("abc@qq.com");

#endif
}

void Register::initConnect()
{
    connect(ui->register_btn, SIGNAL(clicked()), this, SLOT(slotOnRegister()));
}

void Register::paintEvent(QPaintEvent *)
{

}

void Register::slotOnRegister()
{
    //showLoadingProgress();
}

