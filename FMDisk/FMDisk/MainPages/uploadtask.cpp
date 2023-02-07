#include "uploadtask.h"
#include <QFileInfo>
#include "uploadlayout.h"
#include "Utils/Common.h"
#include <QDebug>

//��̬���ݳ�Ա������������������붨��
UploadTask * UploadTask::instance = new UploadTask;

//static�������������main()�˳������
UploadTask::Garbo UploadTask::temp; //��̬���ݳ�Ա���������������ⶨ��

UploadTask * UploadTask::getInstance()
{
    return instance;
}

//׷���ϴ��ļ����ϴ��б���
//������path �ϴ��ļ�·��
//ʧ�ܣ�
//  -1: �ļ�����30m
//  -2���ϴ����ļ��Ƿ��Ѿ����ϴ�������
//  -3: ���ļ�ʧ��
//  -4: ��ȡ����ʧ��
int UploadTask::appendUploadList(QString path)
{
    qint64 size = QFileInfo( path ).size();
//    if(size > 30*1024*1024) //����ļ�ֻ����30M
//    {
//        cout << "file is to big\n";
//        return -1;
//    }


    //�����鿴һ�£����ص��ļ��Ƿ��Ѿ����ϴ�������
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->path == path) //list[i]->path
        {
            cout << QFileInfo( path ).fileName() << " �Ѿ����ϴ������� ";
            return -2;
        }
    }

    QFile *file = new QFile(path); //�ļ�ָ�����ռ�

    if(!file->open(QIODevice::ReadOnly))
    {
        //������ļ�ʧ�ܣ���ɾ�� file����ʹ file ָ��Ϊ 0��Ȼ�󷵻�
        cout << "file open error";

        delete file;
        file = NULL;
        return -3;
    }

    //��ȡ�ļ�������Ϣ
    QFileInfo info(path);

     //��̬�����ڵ�
    Common mc;
    UploadFileInfo *tmp = new UploadFileInfo;
    tmp->md5 = mc.getFileMd5(path); //��ȡ�ļ���md5��, common.h
    tmp->file = file; //�ļ�ָ��
    tmp->fileName = info.fileName();//�ļ�����
    tmp->size = size; //�ļ���С
    tmp->path = path; //�ļ�·��
    tmp->isUpload = false;//��ǰ�ļ�û�б��ϴ�

    DataProgress *p = new DataProgress; //����������
    p->setFileName(tmp->fileName); //�����ļ�����
    tmp->dp = p;

    //��ȡ����
    UploadLayout *pUpload = UploadLayout::getInstance();
    if(pUpload == NULL)
    {
        cout << "UploadTask::getInstance() == NULL";
        return -4;
    }

    cout << "test begin";
    QVBoxLayout *layout = (QVBoxLayout*)pUpload->getUploadLayout();
    cout << "test begin1";
    // ��ӵ�����, ���һ���ǵ���, ���뵽�����ϱ�
//    layout->insertWidget(layout->count()-1, p);
//    layout->insertWidget(p);
//    layout->addWidget(p);
    cout << "test begin2";

    cout << "test end";

    cout << tmp->fileName.toUtf8().data() << "�Ѿ������ϴ��б�";

    //����ڵ�
    list.append(tmp);

    return 0;
}

bool UploadTask::isEmpty() //�ж��ϴ������ͷ�Ϊ��
{
    return list.isEmpty();
}

bool UploadTask::isUpload() //�Ƿ����ļ������ϴ�
{
    //��������
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->isUpload == true) //˵�����ϴ����񣬲������������
        {

            return true;
        }
    }

    return false;
}

// ȡ����0���ϴ���������������û���������ϴ������õ�0�������ϴ�
UploadFileInfo *UploadTask::takeTask()
{
    //ȡ����һ������
    UploadFileInfo *tmp = list.at(0);
    list.at(0)->isUpload = true; //��־λ�����ô��ļ����ϴ�

    return tmp;
}

//ɾ���ϴ���ɵ�����
void UploadTask::dealUploadTask()
{
    //��������
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->isUpload == true) //˵������������
        {
            //�Ƴ����ļ�����Ϊ�Ѿ��ϴ������
            UploadFileInfo *tmp = list.takeAt(i);

            qDebug() << "delete the file : " << tmp->fileName;

            //��ȡ����
            UploadLayout *pUpload = UploadLayout::getInstance();
            QLayout *layout = pUpload->getUploadLayout();
            layout->removeWidget(tmp->dp); //�Ӳ������Ƴ��ؼ�

            //�رմ򿪵��ļ�ָ��
            QFile *file = tmp->file;
            file->close();
            delete file;

            delete tmp->dp;
            delete tmp; //�ͷſռ�

            return;
        }
    }
}

//����ϴ��б�
void UploadTask::clearList()
{
    int n = list.size();
    for(int i = 0; i < n; ++i)
    {
        UploadFileInfo *tmp = list.takeFirst();
        delete tmp;
    }
}
