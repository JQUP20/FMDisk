#include "rankinglistpage.h"
#include "ui_rankinglistpage.h"

RankingListPage::RankingListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankingListPage)
{
    ui->setupUi(this);
}

RankingListPage::~RankingListPage()
{
    delete ui;
}

void RankingListPage::refreshFiles()
{

}
