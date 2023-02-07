#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QNetworkAccessManager>
#include "Utils/Common.h"

namespace Ui {
class Login;
}

class Register : public QDialog
{
public:
    explicit Register(QWidget *parent = 0);
    ~Register();

    void init();
    void initConnect();


protected:
    void paintEvent(QPaintEvent *);

private slots:
    void slotOnRegister();

private:
    Ui::Login *ui;

    // 处理网络请求类对象
    QNetworkAccessManager* m_manager;

    Common m_cm;
};

#endif // REGISTER_H
