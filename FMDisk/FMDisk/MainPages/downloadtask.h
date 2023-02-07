#ifndef DOWNLOADTASK_H
#define DOWNLOADTASK_H

#include "Utils/Common.h"
#include "Utils/HttpStructData.h"

#include <QVBoxLayout>
#include <QUrl>
#include <QFile>
#include "CustomWidgets/dataprogress.h"
#include <QList>


//���������б��࣬����ģʽ��һ������ֻ����һ�����������б�
class DownloadTask
{
public:
    static DownloadTask *getInstance(); //��֤Ψһһ��ʵ��

    void clearList(); //����ϴ��б�
    bool isEmpty();   //�ж��ϴ������Ƿ�Ϊ��
    bool isDownload(); //�Ƿ����ļ���������
    bool isShareTask();//��һ�������Ƿ�Ϊ�����ļ�������
    DownloadFileInfo *takeTask();//ȡ����0��������������������û�����������أ����õ�0����������
    void dealDownloadTask(); //ɾ��������ɵ�����


    //׷���������ض���
    //������info�������ļ���Ϣ�� filePathName���ļ�����·��, isShare: �Ƿ�Ϊ�����ļ�����, Ĭ��Ϊfalse
    //�ɹ���0
    //ʧ�ܣ�
    //  -1: ���ص��ļ��Ƿ��Ѿ������ض�����
    //  -2: ���ļ�ʧ��
    int appendDownloadList( FileInfo *info, QString filePathName, bool isShare = false);


private:
    DownloadTask()    //���캯��Ϊ˽��
    {
    }

    ~DownloadTask()    //��������Ϊ˽��
    {
    }

    //��̬���ݳ�Ա������������������붨��
    static DownloadTask *instance;

    //����Ψһ��������������������ɾ��Singleton��ʵ��
    class Garbo
    {
    public:
        ~Garbo()
        {
          if(NULL != DownloadTask::instance)
          {
            DownloadTask::instance->clearList();//����ϴ��б�

            delete DownloadTask::instance;
            DownloadTask::instance = NULL;
            cout << "instance is detele";
          }
        }
    };

    //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
    //static�������������main()�˳������
    static Garbo temp; //��̬���ݳ�Ա���������������ⶨ��

    // ���ص��������
    QList <DownloadFileInfo *> list;
};

#endif // DOWNLOADTASK_H
