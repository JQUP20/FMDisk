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

//==========>显示用户的文件列表<==============
// desc是descend 降序意思
// asc 是ascend 升序意思
// Normal：普通用户列表，PvAsc：按下载量升序， PvDesc：按下载量降序
//enum Display{Normal, PvAsc, PvDesc};

class FileListPage : public QWidget
{
    Q_OBJECT

public:
    explicit FileListPage(QWidget *parent = nullptr);
    ~FileListPage();

    //
    void init();
    // 初始化listWidget文件列表
    void initListWidget();
    // 添加右键菜单
    void addActionMenu();

    void initConnect();

    //==========>显示用户的文件列表<==============
    // 得到服务器json文件
    QStringList getCountStatus(QByteArray json);
    // 显示用户的文件列表
//    void refreshFiles(Display cmd=Normal);

    // 设置json包
    QByteArray setGetCountJson(QString user, QString token);
    // 设置json包
    QByteArray setFilesListJson(QString user, QString token, int start, int count);
    // 获取用户文件列表
    void getUserFilesList(Display cmd=Normal);
    // 解析文件列表json信息，存放在文件列表中
    void getFileJsonInfo(QByteArray data);


    //==========>上传文件处理<==============
    // 添加需要上传的文件到上传任务列表
    void addUploadFiles();
    // 设置md5信息的json包
    QByteArray setMd5Json(QString user, QString token, QString md5, QString fileName);
    // 上传文件处理，取出上传任务列表的队首任务，上传完后，再取下一个任务
//    void uploadFilesAction();

    //==========>文件item展示<==============
    // 清空文件列表
    void clearFileList();
    // 清空所有item项目
    void clearItems();
    // 添加上传文件项目item
    void addUploadItem(QString iconPath=":/images/upload.png", QString name="上传文件");
    // 文件item展示
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
    // 上传真正的文件内容，不能秒传的前提下
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

    //清除上传下载任务
    void clearAllTask();
    // 定时检查处理任务队列中的任务
    void checkTaskList();

private:
    Ui::FileListPage *ui;

    Common m_cm;
  //  QNetworkAccessManager* m_
    CustomMenu      *m_menu;
    QAction *m_downloadAction; // 下载
    QAction *m_shareAction;    // 分享
    QAction *m_delAction;      // 删除
    QAction *m_propertyAction; // 属性

    CustomMenu      *m_menuEmpty;
    QAction *m_pvAscendingAction;  // 按下载量升序
    QAction *m_pvDescendingAction; // 按下载量降序
    QAction *m_refreshAction;      // 刷新
    QAction *m_uploadAction;       // 上传


    long m_userFilesCount;        //用户文件数目
    int m_start;                  //文件位置起点
    int m_count;                  //每次请求文件个数
    Display m_cmd;

    //定时器
    QTimer m_uploadFileTimer;       //定时检查上传队列是否有任务需要上传
    QTimer m_downloadTimer;         //定时检查下载队列是否有任务需要下载

    LoginInfoInstance *m_loginInfoInstance;
    UploadFileInfo    *m_uploadFileInfo;
    DownloadFileInfo  *m_downloadFileInfo;
    UploadTask        *m_uploadTask;
    DownloadTask      *m_downlaodTask;

    QNetworkAccessManager* m_manager;

    QList<FileInfo *> m_fileList;    //文件列表
};

#endif // FILELISTPAGE_H
