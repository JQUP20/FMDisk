#ifndef FILELISTPAGE_H
#define FILELISTPAGE_H

#include <QWidget>
#include <QTimer>

#include "Utils/Common.h"
#include "CustomWidgets/custommenu.h"

#include "Utils/HttpStructData.h"
#include "Utils/EnumData.h"
#include "uploadtask.h"
#include "downloadtask.h"
#include "LoginWindow//logininfoinstance.h"
#include "CustomWidgets/filepropertyinfo.h"
#include "MainPages/downloadtask.h"

namespace Ui {
class FileListPage;
}

//==========>��ʾ�û����ļ��б�<==============
// desc��descend ������˼
// asc ��ascend ������˼
// Normal����ͨ�û��б�PvAsc�������������� PvDesc��������������
//enum Display{Normal, PvAsc, PvDesc};

class FileListPage : public QWidget
{
    Q_OBJECT

public:
    explicit FileListPage(QWidget *parent = nullptr);
    ~FileListPage();

    //
    void init();
    // ��ʼ��listWidget�ļ��б�
    void initListWidget();
    // ����Ҽ��˵�
    void addActionMenu();

    void initConnect();

    //==========>��ʾ�û����ļ��б�<==============
    // �õ�������json�ļ�
    QStringList getCountStatus(QByteArray json);
    // ��ʾ�û����ļ��б�
//    void refreshFiles(Display cmd=Normal);

    // ����json��
    QByteArray setGetCountJson(QString user, QString token);
    // ����json��
    QByteArray setFilesListJson(QString user, QString token, int start, int count);
    // ��ȡ�û��ļ��б�
    void getUserFilesList(Display cmd=Normal);
    // �����ļ��б�json��Ϣ��������ļ��б���
    void getFileJsonInfo(QByteArray data);


    //==========>�ϴ��ļ�����<==============
    // �����Ҫ�ϴ����ļ����ϴ������б�
    void addUploadFiles();
    // ����md5��Ϣ��json��
    QByteArray setMd5Json(QString user, QString token, QString md5, QString fileName);
    // �ϴ��ļ�����ȡ���ϴ������б�Ķ��������ϴ������ȡ��һ������
//    void uploadFilesAction();

    //==========>�ļ�itemչʾ<==============
    // ����ļ��б�
    void clearFileList();
    // �������item��Ŀ
    void clearItems();
    // ����ϴ��ļ���Ŀitem
    void addUploadItem(QString iconPath=":/images/upload.png", QString name="�ϴ��ļ�");
    // �ļ�itemչʾ
    void refreshFileItems();




signals:
    void loginAgainSignal();
    void gotoTransfer(TransferStatus status);
    void RequestOnUpload();
    void RequestOnUploadInReal(UploadFileInfo* uploadFileInfo);
    void RequestOnDownload(DownloadFileInfo* downloadFileInfo);
    void RequestOnRefreshFiles(Display cmd);
    void RequestOnGetUserFilesList(Display cmd);

private slots:
    // �ϴ��������ļ����ݣ������봫��ǰ����
    void slotOnUploadFile();
    void slotOnUploadFileInReal(UploadFileInfo* uploadFileInfo);
    void slotOnDownloadFile(DownloadFileInfo* downloadFileInfo);
    void slotOnRefreshFiles(Display cmd);
    void slotOnGetUserFilesList(Display cmd);

    //
    void RespondOnUpload(QString nCode);
    //
    void RespondOnUploadInReal(QString nCode);
    //
    void RespondOnRefreshFiles(QString nCode, long nCount);
    //
    void RespondOnGetUserFilesList(QString nCode, QByteArray responseResult);

private:
    void rightMenu(const QPoint &pos);

    //����ϴ���������
    void clearAllTask();
    // ��ʱ��鴦����������е�����
    void checkTaskList();

private:
    Ui::FileListPage *ui;

    Common m_cm;
  //  QNetworkAccessManager* m_
    CustomMenu      *m_menu;
    QAction *m_downloadAction; // ����
    QAction *m_shareAction;    // ����
    QAction *m_delAction;      // ɾ��
    QAction *m_propertyAction; // ����

    CustomMenu      *m_menuEmpty;
    QAction *m_pvAscendingAction;  // ������������
    QAction *m_pvDescendingAction; // ������������
    QAction *m_refreshAction;      // ˢ��
    QAction *m_uploadAction;       // �ϴ�


    long m_userFilesCount;        //�û��ļ���Ŀ
    int m_start;                  //�ļ�λ�����
    int m_count;                  //ÿ�������ļ�����
    Display m_cmd;

    //��ʱ��
    QTimer m_uploadFileTimer;       //��ʱ����ϴ������Ƿ���������Ҫ�ϴ�
    QTimer m_downloadTimer;         //��ʱ������ض����Ƿ���������Ҫ����

    LoginInfoInstance *m_loginInfoInstance;
    UploadFileInfo    *m_uploadFileInfo;
    DownloadFileInfo  *m_downloadFileInfo;
    UploadTask        *m_uploadTask;
    DownloadTask      *m_downlaodTask;

    QNetworkAccessManager* m_manager;

    QList<FileInfo *> m_fileList;    //�ļ��б�
};

#endif // FILELISTPAGE_H
