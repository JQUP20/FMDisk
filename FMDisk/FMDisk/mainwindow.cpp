#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "LoginWindow/logininfoinstance.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fileListPage = new FileListPage;

    // ȥ���߿�
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    // ���˵����ڴ���
    ui->btn_group->setParent(this);
    // ���������ź�
    managerSignals();
    // Ĭ����ʾ�ҵ��ļ�����
    ui->stackedWidget->setCurrentWidget(ui->myfiles_page);

    connect(this, &MainWindow::setUser, ui->btn_group, &ButtonGroup::changeCurrUser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainWindow()
{
    qDebug() << "showMainWindow()";
    m_common.moveToCenter(this); //������ʾ
    // �л����ҵ��ļ�ҳ��
    ui->stackedWidget->setCurrentWidget(ui->myfiles_page);
    // ˢ���û��ļ��б�
//    ui->myfiles_page->refreshFiles();
    //emit ui->myfiles_page->RequestOnRefreshFiles(Normal);

    emit m_fileListPage->RequestOnRefreshFiles(Normal);
    // �����źţ����ߵ�½���ڣ���ʼ����ǰ��¼�û�
    LoginInfoInstance* login = LoginInfoInstance::getInstance();
    emit setUser(login->getUser());
}

void MainWindow::managerSignals()
{
    // �ر�
    connect(ui->btn_group, &ButtonGroup::closeWindow, this, &MainWindow::close);
    // ���
    connect(ui->btn_group, &ButtonGroup::maxWindow, [=]()
    {
        static bool flag = false;
        if(!flag)
        {
            this->showMaximized();
            flag = true;
        }
        else
        {
            this->showNormal();
            flag = false;
        }
    });
    // ��С��
    connect(ui->btn_group, &ButtonGroup::minWindow, this, &MainWindow::showMinimized);
    // ջ�����л�
    // �ҵ��ļ�
    connect(ui->btn_group, &ButtonGroup::sigMyFile, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->myfiles_page);
        // ˢ���ļ��б�
//        ui->myfiles_page->refreshFiles();
        emit ui->myfiles_page->RequestOnRefreshFiles(Normal);
    });
    // �����б�
    connect(ui->btn_group, &ButtonGroup::sigShareList, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->sharefile_page);
        // ˢ�·����б�
        ui->sharefile_page->refreshFiles();
    });
    // ���ذ�
    connect(ui->btn_group, &ButtonGroup::sigDownload, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->ranking_page);
        // ˢ�����ذ��б�
        ui->ranking_page->refreshFiles();
    });
    // �����б�
    connect(ui->btn_group, &ButtonGroup::sigTransform, [=]()
    {
        ui->stackedWidget->setCurrentWidget(ui->transfer_page);
    });
    // �л��û�
    connect(ui->btn_group, &ButtonGroup::sigSwitchUser, [=]()
    {
        qDebug() << "bye bye...";
        loginAgain();
    });
    // stack�����л�
//    connect(ui->myfiles_page, &MyFileWg::gotoTransfer, [=](TransferStatus status)
//    {
//        ui->btn_group->slotButtonClick(Page::TRANSFER);
//        if(status == TransferStatus::Uplaod)
//        {
//            ui->transfer_page->showUpload();
//        }
//        else if(status == TransferStatus::Download)
//        {
//            ui->transfer_page->showDownload();
//        }
//    });
    // �źŴ���
//    connect(ui->sharefile_page, &ShareList::gotoTransfer, ui->myfiles_page, &MyFileWg::gotoTransfer);
}

void MainWindow::loginAgain()
{
    // �����źţ����ߵ�½���ڣ��л��û�
    emit changeUser();
    // �����һ���û����ϴ�����������
//    ui->myfiles_page->clearAllTask();

    // �����һ���û���һЩ�ļ���ʾ��Ϣ
//    ui->myfiles_page->clearFileList();
//    ui->myfiles_page->clearItems();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bk(":/images/title_bk3.jpg");
    painter.drawPixmap(0, 0, width(), height(), bk);
}

