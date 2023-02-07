#include "TransferPage.h"
#include "ui_TransferPage.h"

TransferPage::TransferPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransferPage)
{
    ui->setupUi(this);
}

TransferPage::~TransferPage()
{
    delete ui;
}
