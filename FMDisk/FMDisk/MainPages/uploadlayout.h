#ifndef UPLOADLAYOUT_H
#define UPLOADLAYOUT_H
#include "Utils/Common.h"
#include <QVBoxLayout>

//�ϴ����Ȳ����࣬����ģʽ
class UploadLayout
{
public:
    static UploadLayout *getInstance(); //��֤Ψһһ��ʵ��
    void setUploadLayout(QWidget *p); //���ò���
    QLayout *getUploadLayout(); //��ȡ���� - ��ӿؼ�

private:
    UploadLayout()
    {

    }

    ~UploadLayout()    //��������Ϊ˽��
    {
    }

    //��̬���ݳ�Ա������������������붨��
    static UploadLayout *instance;
    QLayout *m_layout;
    QWidget *m_wg;

    //����Ψһ��������������������ɾ��Singleton��ʵ��
    class Garbo
    {
    public:
        ~Garbo()
        {
          if(NULL != UploadLayout::instance)
          {
            delete UploadLayout::instance;
            UploadLayout::instance = NULL;
            cout << "instance is detele";
          }
        }
    };

    //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
    //static�������������main()�˳������
    static Garbo temp; //��̬���ݳ�Ա���������������ⶨ��
};

#endif // UPLOADLAYOUT_H
