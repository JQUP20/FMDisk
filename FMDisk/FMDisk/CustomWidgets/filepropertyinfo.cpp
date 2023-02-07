#include "filepropertyinfo.h"
#include "ui_filepropertyinfo.h"

FilePropertyInfo::FilePropertyInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilePropertyInfo)
{
    ui->setupUi(this);

    ui->url->setOpenExternalLinks(true); //label������Ϊ����������
}

FilePropertyInfo::~FilePropertyInfo()
{
    delete ui;
}

//��������
void FilePropertyInfo::setInfo(FileInfo *info)
{
    ui->filename->setText(info->filename);
    ui->user->setText(info->user);
    ui->time->setText(info->time);

    int size = info->size;
    if(size >= 1024 && size < 1024*1024)
    {
         ui->size->setText( QString("%1 KB").arg( size/1024.0 ) );
    }
    //else if(size >= 1024*1024 < size < 1024*1024*1024)
    else
    {
         ui->size->setText( QString("%1 MB").arg( size/1024.0/1024.0 ) );
    }

    ui->pv->setText(QString("������ %1 ��").arg(info->pv));
    if(info->shareStatus == 0)
    {
        ui->share->setText("û�з���");
    }
    else
    {
        ui->share->setText("�Ѿ�����");
    }

    //"<a href="http://www.baidu.com">baidu</a>"
    QString tmp = QString("<a href=\"%1\">%2</a>").arg( info->url ).arg( info->url );
    ui->url->setText(tmp);
}