#include "downloadtask.h"
#include "downloadlayout.h"

//��̬���ݳ�Ա������������������붨��
DownloadTask * DownloadTask::instance;

//static�������������main()�˳������
DownloadTask::Garbo DownloadTask::temp; //��̬���ݳ�Ա���������������ⶨ��

DownloadTask * DownloadTask::getInstance()
{

    //�ж��Ƿ��һ�ε���
    if(instance == NULL)
    {
        instance = new DownloadTask();
    }

    return instance;

}

//��������б�
void DownloadTask::clearList()
{
    int n = list.size();
    for(int i = 0; i < n; ++i)
    {
        DownloadFileInfo *tmp = list.takeFirst();
        delete tmp;
    }
}

//�ж��ϴ������Ƿ�Ϊ��
bool DownloadTask::isEmpty()
{
    return list.isEmpty();
}

//�Ƿ����ļ���������
bool DownloadTask::isDownload()
{
     //��������
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->isDownload == true) //˵�����������񣬲������������
        {

            return true;
        }
    }

    return false;
}

//��һ�������Ƿ�Ϊ�����ļ�������
bool DownloadTask::isShareTask()
{
    if( isEmpty() )
    {
        return NULL;
    }

    return list.at(0)->isShare;
}

//ȡ����0��������������������û�����������أ����õ�0����������
DownloadFileInfo * DownloadTask::takeTask()
{
    if( isEmpty() )
    {
        return NULL;
    }

    list.at(0)->isDownload = true; //��־Ϊ������
    return list.at(0);
}

//ɾ��������ɵ�����
void DownloadTask::dealDownloadTask()
{
    //��������
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->isDownload == true) //˵������������
        {
            //�Ƴ����ļ�����Ϊ�Ѿ��ϴ������
            DownloadFileInfo *tmp = list.takeAt(i);

            //��ȡ����
            DownloadLayout *downloadLayout = DownloadLayout::getInstance();
            QLayout *layout = downloadLayout->getDownloadLayout();

            layout->removeWidget(tmp->dp); //�Ӳ������Ƴ��ؼ�
            delete tmp->dp;

            QFile *file = tmp->file;
            file->close();  //�ر��ļ�
            delete file;    //�ͷſռ�

            delete tmp; //�ͷſռ�
            return;
        }
    }
}

//׷���������ض���
//������info�������ļ���Ϣ�� filePathName���ļ�����·��
//�ɹ���0
//ʧ�ܣ�
//  -1: ���ص��ļ��Ƿ��Ѿ������ض�����
//  -2: ���ļ�ʧ��
int DownloadTask::appendDownloadList( FileInfo *info, QString filePathName, bool isShare)
{
    //�����鿴һ�£����ص��ļ��Ƿ��Ѿ������ض�����
    for(int i = 0; i != list.size(); ++i)
    {
        if( list.at(i)->user == info->user && list.at(i)->filename == info->filename)
        {
            cout << info->filename << " �Ѿ������ض����� ";
            return -1;
        }
    }

    QFile *file = new QFile(filePathName); //�ļ�ָ�����ռ�

    if(!file->open(QIODevice::WriteOnly))
    { //������ļ�ʧ�ܣ���ɾ�� file����ʹ file ָ��Ϊ NULL��Ȼ�󷵻�
        cout << "file open error";

        delete file;
        file = NULL;
        return -2;
    }

      //��̬�����ڵ�
    DownloadFileInfo *tmp = new DownloadFileInfo;
    tmp->user = info->user;   //�û�
    tmp->file = file;         //�ļ�ָ��
    tmp->filename = info->filename; //�ļ�����
    tmp->md5 = info->md5;           //�ļ�md5
    tmp->url = info->url;           //������ַ
    tmp->isDownload = false;        //û��������
    tmp->isShare = isShare;         //�Ƿ�Ϊ�����ļ�����

    DataProgress *p = new DataProgress; //����������
    p->setFileName(tmp->filename); //�����ļ�����

    //��ȡ����
    DownloadLayout *downloadLayout = DownloadLayout::getInstance();
    QVBoxLayout *layout = (QVBoxLayout*)downloadLayout->getDownloadLayout();

    tmp->dp = p;
    // ��ӵ�����, ���һ���ǵ���, ���뵽�����ϱ�
    layout->insertWidget(layout->count()-1, p);

    cout << info->url << "�Ѿ���ӵ������б�";

    //����ڵ�
    list.append(tmp);


    return 0;
}
