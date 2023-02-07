#ifndef DOWNLOADLAYOUT_H
#define DOWNLOADLAYOUT_H

#include "Utils/Common.h"
#include <QVBoxLayout>

//���ؽ��Ȳ����࣬����ģʽ
class DownloadLayout
{
public:
    static DownloadLayout *getInstance(); //��֤Ψһһ��ʵ��
    void setDownloadLayout(QWidget *p); //���ò���
    QLayout *getDownloadLayout(); //��ȡ����

private:
    DownloadLayout()
    {

    }

    ~DownloadLayout()    //��������Ϊ˽��
    {
    }

    //��̬���ݳ�Ա������������������붨��
    static DownloadLayout *instance;
    QLayout *m_layout;
    QWidget* m_wg;

    //����Ψһ��������������������ɾ��Singleton��ʵ��
    class Garbo
    {
    public:
        ~Garbo()
        {
          if(NULL != DownloadLayout::instance)
          {
            delete DownloadLayout::instance;
            DownloadLayout::instance = NULL;
            cout << "instance is detele";
          }
        }
    };

    //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
    //static�������������main()�˳������
    static Garbo temp; //��̬���ݳ�Ա���������������ⶨ��
};


#endif // DOWNLOADLAYOUT_H
