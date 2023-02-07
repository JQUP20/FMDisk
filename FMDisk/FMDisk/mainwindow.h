#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Utils/Common.h"
#include "MainPages/filelistpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // ��ʾ������
    void showMainWindow();
    // �����ź�
    void managerSignals();
    // ���µ�½
    void loginAgain();

signals:
    // �л��û���ť�ź�
    void changeUser();
    void setUser(QString user);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;

    FileListPage *m_fileListPage;


    Common m_common;
};
#endif // MAINWINDOW_H
