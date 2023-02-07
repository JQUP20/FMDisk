#include "downloadlayout.h"

//��̬���ݳ�Ա������������������붨��
DownloadLayout * DownloadLayout::instance = new DownloadLayout;

//static�������������main()�˳������
DownloadLayout::Garbo DownloadLayout::temp; //��̬���ݳ�Ա���������������ⶨ��

DownloadLayout * DownloadLayout::getInstance()
{
    return instance;
}

//���ò���
void DownloadLayout::setDownloadLayout(QWidget *p)
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

    vlayout->addStretch();
}

//��ȡ����
QLayout *DownloadLayout::getDownloadLayout()
{
    return m_layout;
}

