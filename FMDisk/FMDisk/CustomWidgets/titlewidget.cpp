#include "titlewidget.h"
#include "ui_titlewidget.h"
#include <QMouseEvent>
#include <QDebug>

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);

    m_parent = parent;
    // logo
    ui->logo->setPixmap(QPixmap(":/images/logo.ico").scaled(40, 40));

    // ��ť
    // ��С��
    connect(ui->min_btn, &QToolButton::clicked, [=]()
    {
        m_parent->showMinimized();
    });

    // �ر�
    connect(ui->close_btn, &QToolButton::clicked, [=]()
    {
        emit closeWindow();
    });

    // ����
    connect(ui->set_btn, &QToolButton::clicked, [=]()
    {
        // �л������ô���
        // ���źŸ�������
        emit showSetWidget();
    });
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::mousePressEvent(QMouseEvent *ev)
{
    // ��������, ���㴰�����Ͻ�, �͵�ǰ��ťλ�õľ���
    if(ev->button() == Qt::LeftButton)
    {
        // ����ʹ������Ͻǵ����λ��
        m_pos = ev->globalPos() - m_parent->geometry().topLeft();
    }
}

void TitleWidget::mouseMoveEvent(QMouseEvent *ev)
{
    // �ƶ��ǳ�����״̬, ��Ҫʹ��buttons
    if(ev->buttons() & Qt::LeftButton)
    {
        QPoint pos = ev->globalPos() - m_pos;
        m_parent->move(pos);
    }
}
