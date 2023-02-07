#include "dataprogress.h"
#include "ui_dataprogress.h"

DataProgress::DataProgress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataProgress)
{
    ui->setupUi(this);
}

DataProgress::~DataProgress()
{
    delete ui;
}

//�����ļ�����
void DataProgress::setFileName(QString name)
{
    ui->label->setText(name + " : ");
    ui->progressBar->setMinimum(0); //��Сֵ
    ui->progressBar->setValue(0);
}

//���ý������ĵ�ǰֵvalue, ���ֵmax
void DataProgress::setProgress(int value, int max)
{
    ui->progressBar->setValue(value);
    ui->progressBar->setMaximum(max);
}
