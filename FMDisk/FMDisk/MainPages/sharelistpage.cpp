#include "sharelistpage.h"
#include "ui_sharelistpage.h"

ShareListPage::ShareListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareListPage)
{
    ui->setupUi(this);
}

ShareListPage::~ShareListPage()
{
    delete ui;
}

void ShareListPage::refreshFiles()
{

}
