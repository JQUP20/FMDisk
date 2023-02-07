#ifndef UPLOADTASK_H
#define UPLOADTASK_H

#include "Utils/Common.h"
#include <QVBoxLayout>
#include <QFile>
#include "CustomWidgets/dataprogress.h"
#include "Utils/HttpStructData.h"

//�ϴ��ļ���Ϣ
//struct UploadFileInfo
//{
//    QString md5;        //�ļ�md5��
//    QFile *file;        //�ļ�ָ��
//    QString fileName;   //�ļ�����
//    qint64 size;        //�ļ���С
//    QString path;       //�ļ�·��
//    bool isUpload;      //�Ƿ��Ѿ����ϴ�
//    DataProgress *dp;   //�ϴ����ȿؼ�
//};

//�ϴ������б��࣬����ģʽ��һ������ֻ����һ���ϴ������б�
class UploadTask
{
public:
    static UploadTask *getInstance(); //��֤Ψһһ��ʵ��


    //׷���ϴ��ļ����ϴ��б���
    //������path �ϴ��ļ�·��
    //����ֵ���ɹ�Ϊ0
    //ʧ�ܣ�
    //  -1: �ļ�����30m
    //  -2���ϴ����ļ��Ƿ��Ѿ����ϴ�������
    //  -3: ���ļ�ʧ��
    //  -4: ��ȡ����ʧ��
    int appendUploadList(QString path);

    bool isEmpty(); //�ж��ϴ������ͷ�Ϊ��
    bool isUpload(); //�Ƿ����ļ������ϴ�

    //ȡ����0���ϴ���������������û���������ϴ������õ�0�������ϴ�
    UploadFileInfo * takeTask();
    //ɾ���ϴ���ɵ�����
    void dealUploadTask();

    void clearList(); //����ϴ��б�

private:
    UploadTask()    //���캯��Ϊ˽��
    {
    }

    ~UploadTask()    //��������Ϊ˽��
    {
    }

    //��̬���ݳ�Ա������������������붨��
    static UploadTask *instance;

    //����Ψһ��������������������ɾ��Singleton��ʵ��
    class Garbo
    {
    public:
        ~Garbo()
        {
          if(NULL != UploadTask::instance)
          {
            UploadTask::instance->clearList();

            delete UploadTask::instance;
            UploadTask::instance = NULL;
            cout << "instance is detele";
          }
        }
    };

    //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
    //static�������������main()�˳������
    static Garbo temp; //��̬���ݳ�Ա���������������ⶨ��

    QList<UploadFileInfo *> list; //�ϴ������б�(�������)
    // QQueue<UploadFileInfo *> list1;
};

#endif // UPLOADTASK_H
