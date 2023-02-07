#include "uploadlayout.h"

//��̬���ݳ�Ա������������������붨��
UploadLayout * UploadLayout::instance = new UploadLayout;

//static�������������main()�˳������
UploadLayout::Garbo UploadLayout::temp; //��̬���ݳ�Ա���������������ⶨ��

UploadLayout * UploadLayout::getInstance()
{
    return instance;
}

// ���ò���
// ����ǰ������Ӵ���
void UploadLayout::setUploadLayout(QWidget *p)
{
    m_wg = new QWidget(p);
    QLayout* layout = p->layout();
    layout->addWidget(m_wg);
    layout->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout* vlayout = new QVBoxLayout;
    // �������ø�����
    m_wg->setLayout(vlayout);
    // �߽���
    vlayout->setContentsMargins(0, 0, 0, 0);
    m_layout = vlayout;

    // ��ӵ���
    vlayout->addStretch();  //���һ����
}

//��ȡ����
QLayout *UploadLayout::getUploadLayout()
{
    return m_layout; // ��ֱ����
}
