#include "filelistpage.h"
#include "ui_filelistpage.h"

#include "Network/HttpAgent.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QListWidgetItem>
#include <QHttpMultiPart>
#include <QHttpPart>

FileListPage::FileListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileListPage)
{
    ui->setupUi(this);

    m_manager = Common::getNetManager();

    init();

    initConnect();

    // 定时检查任务队列
    checkTaskList();
}

FileListPage::~FileListPage()
{
    delete ui;
}

void FileListPage::init()
{
    // 初始化listWidget文件列表
    initListWidget();
    // 添加右键菜单
    addActionMenu();
}

void FileListPage::initListWidget()
{
    ui->listWidget->setViewMode(QListView::IconMode);   //设置显示图标模式
    ui->listWidget->setIconSize(QSize(80, 80));         //设置图标大小
    ui->listWidget->setGridSize(QSize(100, 120));       //设置item大小

    // 设置QLisView大小改变时，图标的调整模式，默认是固定的，可以改成自动调整
    ui->listWidget->setResizeMode(QListView::Adjust);   //自动适应布局

    // 设置列表可以拖动，如果想固定不能拖动，使用QListView::Static
    ui->listWidget->setMovement(QListView::Static);
    // 设置图标之间的间距, 当setGridSize()时，此选项无效
    ui->listWidget->setSpacing(30);

    // listWidget 右键菜单
    // 发出 customContextMenuRequested 信号
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, &FileListPage::rightMenu);
    // 点中列表中的上传文件图标
    connect(ui->listWidget, &QListWidget::itemPressed, this, [=](QListWidgetItem* item)
    {
        QString str = item->text();
        if(str == "上传文件")
        {
            //添加需要上传的文件到上传任务列表
            addUploadFiles();
        }
    });
}

void FileListPage::addActionMenu()
{
    //===================菜单1==================
    m_menu = new CustomMenu( this );

    // 初始化菜单项
    m_downloadAction = new QAction("下载", this);
    m_shareAction = new QAction("分享", this);
    m_delAction = new QAction("删除", this);
    m_propertyAction = new QAction("属性", this);

    // 动作1添加到菜单1
    m_menu->addAction(m_downloadAction);
    m_menu->addAction(m_shareAction);
    m_menu->addAction(m_delAction);
    m_menu->addAction(m_propertyAction);

    //===================菜单2===================
    m_menuEmpty = new CustomMenu( this );
    // 动作2
    m_pvAscendingAction = new QAction("按下载量升序", this);
    m_pvDescendingAction = new QAction("按下载量降序", this);
    m_refreshAction = new QAction("刷新", this);
    m_uploadAction = new QAction("上传", this);

    // 动作2添加到菜单2
    m_menuEmpty->addAction(m_pvAscendingAction);
    m_menuEmpty->addAction(m_pvDescendingAction);
    m_menuEmpty->addAction(m_refreshAction);
    m_menuEmpty->addAction(m_uploadAction);

    //=====================信号与槽===================
    // 下载
    connect(m_downloadAction, &QAction::triggered, [=]()
    {
        cout << "下载动作";
        //添加需要下载的文件到下载任务列表
       // addDownloadFiles();
    });

    // 分享
    connect(m_shareAction, &QAction::triggered, [=]()
    {
        cout << "分享动作";
//        dealSelectdFile("分享"); //处理选中的文件
    });

    // 删除
    connect(m_delAction, &QAction::triggered, [=]()
    {
        cout << "删除动作";
//        dealSelectdFile("删除"); //处理选中的文件
    });

    // 属性
    connect(m_propertyAction, &QAction::triggered, [=]()
    {
        cout << "属性动作";
//        dealSelectdFile("属性"); //处理选中的文件
    });

    // 按下载量升序
    connect(m_pvAscendingAction, &QAction::triggered, [=]()
    {
        cout << "按下载量升序";
//        refreshFiles(PvAsc);
        emit RequestOnRefreshFiles(PvAsc);
    });

    // 按下载量降序
    connect(m_pvDescendingAction, &QAction::triggered, [=]()
    {
        cout << "按下载量降序";
//        refreshFiles(PvDesc);
        emit RequestOnRefreshFiles(PvDesc);
    });

    //刷新
    connect(m_refreshAction, &QAction::triggered, [=]()
    {
        cout << "刷新动作";
        //显示用户的文件列表
        emit RequestOnRefreshFiles(Normal);
    });

    //上传
    connect(m_uploadAction, &QAction::triggered, [=]()
    {
        cout << "上传动作";
        //添加需要上传的文件到上传任务列表
        addUploadFiles();
    });
}

void FileListPage::initConnect()
{
    connect(this, SIGNAL(RequestOnUpload()), this, SLOT(slotOnUploadFile()));
//    connect(this, SIGNAL(RequestOnUploadInReal(UploadFileInfo*)), this, SLOT(slotOnUploadFileInReal(UploadFileInfo*)));
    connect(this, SIGNAL(RequestOnRefreshFiles(Display)), this, SLOT(slotOnRefreshFiles(Display)));
    connect(this, SIGNAL(RequestOnGetUserFilesList(Display)), this, SLOT(slotOnGetUserFilesList(Display)));

//    connect(HttpAgent::instance(), SIGNAL(RespondOnUpload(QString)), this, SLOT(RespondOnUpload(QString)));
//    connect(HttpAgent::instance(), SIGNAL(RespondOnUploadInReal(QString)), this, SLOT(RespondOnUploadInReal(QString)));
//    connect(HttpAgent::instance(), SIGNAL(RespondOnRefreshFiles(QString,long)), this, SLOT(RespondOnRefreshFiles(QString,long)));
    //    connect(HttpAgent::instance(), SIGNAL(RespondOnGetUserFilesList(QString,QByteArray)), this, SLOT(RespondOnGetUserFilesList(QString,QByteArray)));
}

QStringList FileListPage::getCountStatus(QByteArray json)
{
    QJsonParseError error;
    QStringList list;

    //cout << "json = " << json.data();

    //将来源数据json转化为JsonDocument
    //由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) //没有出错
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return list;
        }

        if( doc.isObject() )
        {
            QJsonObject obj = doc.object();//取得最外层这个大对象
            list.append( obj.value( "token" ).toString() ); //登陆token
            list.append( obj.value( "num" ).toString() ); //文件个数
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }

    return list;
}

QByteArray FileListPage::setGetCountJson(QString user, QString token)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);

    /*json数据如下
    {
        user:xxxx
        token: xxxx
    }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(tmp);
    if ( jsonDocument.isNull() )
    {
        cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();
    return jsonDocument.toJson();
}

QByteArray FileListPage::setFilesListJson(QString user, QString token, int start, int count)
{
    /*{
        "user": "yoyo"
        "token": "xxx"
        "start": 0
        "count": 10
    }*/
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);
    tmp.insert("start", start);
    tmp.insert("count", count);

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(tmp);
    if ( jsonDocument.isNull() )
    {
        cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();

    return jsonDocument.toJson();
}

void FileListPage::getUserFilesList(Display cmd)
{
    //遍历数目，结束条件处理
    if(m_userFilesCount <= 0) //结束条件，这个条件很重要，函数递归的结束条件
    {
        cout << "获取用户文件列表条件结束";
        refreshFileItems(); //更新item
        return; //中断函数
    }
    else if(m_count > m_userFilesCount) //如果请求文件数量大于用户的文件数目
    {
        m_count = m_userFilesCount;
    }


    QNetworkRequest request; //请求对象

    // 获取登陆信息实例
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //获取单例

    // 获取用户文件信息 127.0.0.1:80/myfiles&cmd=normal
    // 按下载量升序 127.0.0.1:80/myfiles?cmd=pvasc
    // 按下载量降序127.0.0.1:80/myfiles?cmd=pvdesc
    QString url;

    QString tmp;
    //cmd取值，Normal：普通用户列表，PvAsc：按下载量升序， PvDesc：按下载量降序
    if(cmd == Normal)
    {
        tmp = "normal";
    }
    else if(cmd == PvAsc)
    {
        tmp = "pvasc";
    }
    else if(cmd == PvDesc)
    {
        tmp = "pvdesc";
    }

   // url = QString("http://%1:%2/myfiles?cmd=%3").arg(login->getIp()).arg(login->getPort()).arg(tmp);
    url = "http://192.168.0.188:80/myfiles?cmd=normal";
    request.setUrl(QUrl( url )); //设置url
    cout << "myfiles url: " << url;

    //qt默认的请求头
    //request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    /*
    {
        "user": "yoyo"
        "token": "xxxx"
        "start": 0
        "count": 10
    }
    */
    QByteArray data = setFilesListJson( login->getUser(), login->getToken(), m_start, m_count);

    cout << "data : " << data;

    //改变文件起点位置
    m_start += m_count;
    m_userFilesCount -= m_count;

    //发送post请求
    QNetworkReply * reply = m_manager->post( request, data );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    //获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //有错误
        {
            cout << reply->errorString();
            reply->deleteLater(); //释放资源
            return;
        }

        //服务器返回用户的数据
        QByteArray array = reply->readAll();
        cout << "file info:" << array;

        reply->deleteLater();

        //token验证失败
        if("111" == m_cm.getCode(array) ) //common.h
        {
            QMessageBox::warning(this, "账户异常", "请重新登陆！！！");
            emit loginAgainSignal(); //发送重新登陆信号

            return; //中断
        }

        //不是错误码就处理文件列表json信息
        if("015" != m_cm.getCode(array) ) //common.h
        {
            //cout << array.data();
            getFileJsonInfo(array);//解析文件列表json信息，存放在文件列表中

            //继续获取用户文件列表
            getUserFilesList(cmd);
        }
    });
}

void FileListPage::getFileJsonInfo(QByteArray data)
{
    QJsonParseError error;

    /*
    {
    "user": "yoyo",
    "md5": "e8ea6031b779ac26c319ddf949ad9d8d",
    "time": "2017-02-26 21:35:25",
    "filename": "test.mp4",
    "share_status": 0,
    "pv": 0,
    "url": "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z0782.mp4",
    "size": 27473666,
     "type": "mp4"
    }
    */
    //-- user	文件所属用户
    //-- md5 文件md5
    //-- createtime 文件创建时间
    //-- filename 文件名字
    //-- shared_status 共享状态, 0为没有共享， 1为共享
    //-- pv 文件下载量，默认值为0，下载一次加1
    //-- url 文件url
    //-- size 文件大小, 以字节为单位
    //-- type 文件类型： png, zip, mp4……

    //将来源数据json转化为JsonDocument
    //由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error == QJsonParseError::NoError) //没有出错
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if( doc.isObject())
        {
            //QJsonObject json对象，描述json数据中{}括起来部分
            QJsonObject obj = doc.object();//取得最外层这个大对象

            //获取games所对应的数组
            //QJsonArray json数组，描述json数据中[]括起来部分
            QJsonArray array = obj.value("files").toArray();

            int size = array.size();   //数组个数
            cout << "size = " << size;

            for(int i = 0; i < size; ++i)
            {
                QJsonObject tmp = array[i].toObject(); //取第i个对象
                /*
                    //文件信息
                    struct FileInfo
                    {
                        QString md5;        //文件md5码
                        QString filename;   //文件名字
                        QString user;       //用户
                        QString time;       //上传时间
                        QString url;        //url
                        QString type;       //文件类型
                        qint64 size;        //文件大小
                        int shareStatus;    //是否共享, 1共享， 0不共享
                        int pv;             //下载量
                        QListWidgetItem *item; //list widget 的item
                    };

                    {
                    "user": "yoyo",
                    "md5": "e8ea6031b779ac26c319ddf949ad9d8d",
                    "time": "2017-02-26 21:35:25",
                    "filename": "test.mp4",
                    "share_status": 0,
                    "pv": 0,
                    "url": "http://192.168.31.109:80/group1/M00/00/00/wKgfbViy2Z2AJ-FTAaM3As-g3Z0782.mp4",
                    "size": 27473666,
                     "type": "mp4"
                    }
                */
                FileInfo *info = new FileInfo;
                info->user = tmp.value("user").toString(); //用户
                info->md5 = tmp.value("md5").toString(); //文件md5
                info->time = tmp.value("time").toString(); //上传时间
                info->filename = tmp.value("filename").toString(); //文件名字
                info->shareStatus = tmp.value("share_status").toInt(); //共享状态
                info->pv = tmp.value("pv").toInt(); //下载量
                info->url = tmp.value("url").toString(); //url
                info->size = tmp.value("size").toInt(); //文件大小，以字节为单位
                info->type = tmp.value("type").toString();//文件后缀
                QString type = info->type + ".png";
                info->item = new QListWidgetItem(QIcon( m_cm.getFileType(type) ), info->filename);

                //list添加节点
                m_fileList.append(info);
            }
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }
}

void FileListPage::addUploadFiles()
{
//    // 切换到传输列表的, 上传界面
//    emit gotoTransfer(TransferStatus::Uplaod);
//    //获取上传列表实例
//   // UploadTask *m_uploadTask = UploadTask::getInstance();
//    m_uploadTask = UploadTask::getInstance();

//    if(m_uploadTask == NULL)
//    {
//        cout << "UploadTask::getInstance() == NULL";
//        return;
//    }

//    QStringList list = QFileDialog::getOpenFileNames();
//    for(int i = 0; i < list.size(); ++i)
//    {
//        qDebug() << "所选文件为："<<list.at(i);
//        //  -1: 文件大于30m
//        //  -2：上传的文件是否已经在上传队列中
//        //  -3: 打开文件失败
//        //  -4: 获取布局失败
//        int res = m_uploadTask->appendUploadList(list.at(i));
//        if(res == -1)
//        {
//            QMessageBox::warning(this, "文件太大", "文件大小不能超过30M！！！");
//        }
//        else if(res == -2)
//        {
//            QMessageBox::warning(this, "添加失败", "上传的文件是否已经在上传队列中！！！");
//        }
//        else if(res == -3)
//        {
//            cout << "打开文件失败";
//        }
//        else if(res == -4)
//        {
//            cout << "获取布局失败";
//        }
//    }

    // 切换到传输列表的, 上传界面
    emit gotoTransfer(TransferStatus::Uplaod);
    //获取上传列表实例
    UploadTask *uploadList = UploadTask::getInstance();
    if(uploadList == NULL)
    {
        cout << "UploadTask::getInstance() == NULL";
        return;
    }

    QStringList list = QFileDialog::getOpenFileNames();
    for(int i = 0; i < list.size(); ++i)
    {
        //cout << "所选文件为："<<list.at(i);
        //  -1: 文件大于30m
        //  -2：上传的文件是否已经在上传队列中
        //  -3: 打开文件失败
        //  -4: 获取布局失败
        int res = uploadList->appendUploadList(list.at(i));
        if(res == -1)
        {
            QMessageBox::warning(this, "文件太大", "文件大小不能超过30M！！！");
        }
        else if(res == -2)
        {
            QMessageBox::warning(this, "添加失败", "上传的文件是否已经在上传队列中！！！");
        }
        else if(res == -3)
        {
            cout << "打开文件失败";
        }
        else if(res == -4)
        {
            cout << "获取布局失败";
        }
    }

}

void FileListPage::clearFileList()
{
    int n = m_fileList.size();
    for(int i = 0; i < n; ++i)
    {
        FileInfo *tmp = m_fileList.takeFirst();
        delete tmp;
    }
}

void FileListPage::clearItems()
{
    qDebug() << "clearitems";
    //使用QListWidget::count()来统计ListWidget中总共的item数目
    int n = ui->listWidget->count();
    qDebug() << "n = " << n;
    for(int i = 0; i < n; ++i)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0); //这里是0，不是i
        delete item;
    }
}

void FileListPage::addUploadItem(QString iconPath, QString name)
{
    qDebug() << "addUploadItem";
    ui->listWidget->addItem(new QListWidgetItem(QIcon(iconPath), name));
}

void FileListPage::refreshFileItems()
{
    qDebug() << "FileListPage::refreshFileItems()";
    clearItems();

    //如果文件列表不为空，显示文件列表
    if(m_fileList.isEmpty() == false)
    {
        int n = m_fileList.size(); //元素个数
        qDebug() << "files count = " << n;
        for(int i = 0; i < n; ++i)
        {
            FileInfo *tmp = m_fileList.at(i);
            QListWidgetItem *item = tmp->item;
            //list widget add item
            ui->listWidget->addItem(item);
        }
    }

    //添加上传文件item
    this->addUploadItem();
}

void FileListPage::slotOnUploadFile()
{
   // qDebug() << "begin upoload";
    // 获取上传列表实例
//    UploadTask *m_uploadTask = UploadTask::getInstance();
//    m_uploadTask = UploadTask::getInstance();
//    if(m_uploadTask == NULL)
//    {
//        cout << "UploadTask::getInstance() == NULL";
//        return;
//    }

//    // 如果队列为空，无上传任务，终止程序
//    if( m_uploadTask->isEmpty() )
//    {
//        return;
//    }

//    // 查看是否有上传任务，单任务上传，当前有任务，不能上传
//    if( m_uploadTask->isUpload() )
//    {
//        return;
//    }

//    // 获取登陆信息实例
//    m_loginInfoInstance = LoginInfoInstance::getInstance(); //获取单例

//    //
//    m_uploadFileInfo = m_uploadTask->takeTask();

//    //此处可尝试启用线程

//    HttpAgent::instance()->RequestOnUpload( m_uploadFileInfo, m_loginInfoInstance);

   // qDebug() << "MyFileWg::uploadFilesAction()";
    // 获取上传列表实例
    UploadTask *uploadList = UploadTask::getInstance();
    if(uploadList == NULL)
    {
        cout << "UploadTask::getInstance() == NULL";
        return;
    }

    // 如果队列为空，无上传任务，终止程序
    if( uploadList->isEmpty() )
    {
        return;
    }

    // 查看是否有上传任务，单任务上传，当前有任务，不能上传
    if( uploadList->isUpload() )
    {
        return;
    }

    // 获取登陆信息实例
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //获取单例

    // url
    QNetworkRequest request;
//    QString url = QString("http://%1:%2/md5").arg( login->getIp() ).arg( login->getPort() );
    QString url = "http://192.168.0.188:80/md5";
    request.setUrl( QUrl( url )); //设置url
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 取出第0个上传任务，如果任务队列没有任务在上传，设置第0个任务上传
    UploadFileInfo *info = uploadList->takeTask();

    // post数据包
    QByteArray array = setMd5Json(login->getUser(), login->getToken(), info->md5, info->fileName);
    qDebug() << "post array : " << array;

    // 发送post请求
    QNetworkReply *reply = m_manager->post(request, array);
    if(reply == NULL)
    {
        cout << "reply is NULL";
        return;
    }

    // 信号和槽连接
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //有错误
        {
            cout << reply->errorString();
            reply->deleteLater(); //释放资源
            return;
        }

        QByteArray array = reply->readAll();
        qDebug() << "response array : " << array;
        //cout << array.data();
        reply->deleteLater(); //释放资源

        /*
        秒传文件：
            文件已存在：{"code":"005"}
            秒传成功：  {"code":"006"}
            秒传失败：  {"code":"007"}
        token验证失败：{"code":"111"}

        */
        if("006" == m_cm.getCode(array) ) //common.h
        {
            //秒传文件成功
            //cout << info->fileName.toUtf8().data() << "-->秒传成功";
            m_cm.writeRecord(login->getUser(), info->fileName, "006");

            //删除已经完成的上传任务
            uploadList->dealUploadTask();
        }
        else if("007" == m_cm.getCode(array) )
        {
            // 说明后台服务器没有此文件，需要真正的文件上传
            slotOnUploadFileInReal(info);
        }
        else if("005" == m_cm.getCode(array) )// "005", 上传的文件已存在
        {
            //QMessageBox::information(this, "文件已存在", QString("%1 已存在").arg(info->fileName))
            //cout << QString("%1 已存在").arg(info->fileName).toUtf8().data();
            m_cm.writeRecord(login->getUser(), info->fileName, "005");

            //删除已经完成的上传任务
            uploadList->dealUploadTask();
        }
        else if("111" == m_cm.getCode(array)) //token验证失败
        {
            QMessageBox::warning(this, "账户异常", "请重新登陆！！！");
            emit loginAgainSignal(); //发送重新登陆信号
            return;
        }
    });
}

// 设置md5信息的json包
QByteArray FileListPage::setMd5Json(QString user, QString token, QString md5, QString fileName)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);
    tmp.insert("md5", md5);
    tmp.insert("fileName", fileName);

    /*json数据如下
    {
        user:xxxx,
        token:xxxx,
        md5:xxx,
        fileName: xxx
    }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(tmp);
    if ( jsonDocument.isNull() )
    {
        cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();

    return jsonDocument.toJson();
}


void FileListPage::slotOnUploadFileInReal(UploadFileInfo *uploadFileInfo)
{
    qDebug() << "FileListPage::slotOnUploadFileInReal ... " ;
    // 取出上传任务
//    QFile *file = uploadFileInfo->file;
//    QString fileName = uploadFileInfo->fileName;
//    QString md5 = uploadFileInfo->md5;
//    qint64 size = uploadFileInfo->size;
//    DataProgress *dp = uploadFileInfo->dp;
//    QString boundary = m_cm.getBoundary();

//    qDebug() << "Test : " << "uploadFileInfoInReal -- " << fileName << "  " << md5 << "  " << size;
//    m_loginInfoInstance = LoginInfoInstance::getInstance();
////    m_uploadTask =
//   // m_uploadFileInfo = m_uploadTask->takeTask();

//    HttpAgent::instance()->RequestOnUploadInReal(uploadFileInfo, m_loginInfoInstance);

    //取出上传任务
    QFile *file = uploadFileInfo->file;           //文件指针
    QString fileName = uploadFileInfo->fileName;  //文件名字
    QString md5 = uploadFileInfo->md5;            //文件md5码
    qint64 size = uploadFileInfo->size;           //文件大小
    DataProgress *dp = uploadFileInfo->dp;        //进度条控件
    QString boundary = m_cm.getBoundary();   //产生分隔线

    //获取登陆信息实例
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //获取单例
#if 0
    QByteArray data;

    /*
    ------WebKitFormBoundary88asdgewtgewx\r\n
    Content-Disposition: form-data; user="mike"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
    Content-Type: application/octet-stream\r\n
    \r\n
    真正的文件内容\r\n
    ------WebKitFormBoundary88asdgewtgewx
    */

    //第1行，分隔线
    data.append(boundary);
    data.append("\r\n");

    //上传文件信息
    data.append("Content-Disposition: form-data; ");
    data.append( QString("user=\"%1\" ").arg( login->getUser() ) ); //上传用户
    data.append( QString("filename=\"%1\" ").arg(fileName) ); //文件名字
    data.append( QString("md5=\"%1\" ").arg(md5) ); //文件md5码
    data.append( QString("size=%1").arg(size)  );   //文件大小
    data.append("\r\n");

    data.append("Content-Type: application/octet-stream");
    data.append("\r\n");
    data.append("\r\n");

    // 上传文件内容
    data.append( file->readAll() ); //文件内容
    data.append("\r\n");

    // 结束分隔线
    data.append(boundary);
#endif
    QHttpPart part;
    QString disp = QString("form-data; user=\"%1\"; filename=\"%2\"; md5=\"%3\"; size=%4")
            .arg(login->getUser()).arg(uploadFileInfo->fileName).arg(uploadFileInfo->md5).arg(uploadFileInfo->size);
    part.setHeader(QNetworkRequest::ContentDispositionHeader, disp);
    part.setHeader(QNetworkRequest::ContentTypeHeader, "image/png"); // 传输的文件对应的content-type
    part.setBodyDevice(uploadFileInfo->file);
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    multiPart->append(part);


    QNetworkRequest request; //请求对象
    //http://127.0.0.1:80/upload
//    QString url = QString("http://%1:%2/upload").arg(login->getIp()).arg(login->getPort());
    QString url = "http://192.168.0.188:80/upload";
    request.setUrl(QUrl( url )); //设置url

    // qt默认的请求头
    //request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");

    // 发送post请求
    QNetworkReply * reply = m_manager->post( request, multiPart );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    // 有可用数据更新时
    connect(reply, &QNetworkReply::uploadProgress, [=](qint64 bytesRead, qint64 totalBytes)
    {
        if(totalBytes != 0) //这个条件很重要
        {
            //cout << bytesRead/1024 << ", " << totalBytes/1024;
            dp->setProgress(bytesRead/1024, totalBytes/1024); //设置进度条
        }
    });

    // 获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //有错误
        {
            cout << reply->errorString();
            reply->deleteLater(); //释放资源
            m_cm.writeRecord(login->getUser(), uploadFileInfo->fileName, "009");
            UploadTask *uploadList = UploadTask::getInstance();
            uploadList->dealUploadTask(); //删除已经完成的上传任务
            return;
        }

        QByteArray array = reply->readAll();

        qDebug() << "response array : " << array;

        reply->deleteLater();
        // 析构对象
        multiPart->deleteLater();

        /*
            上传文件：
                成功：{"code":"008"}
                失败：{"code":"009"}
            */
        if("008" == m_cm.getCode(array) ) //common.h
        {
            cout << fileName.toUtf8().data() <<" ---> 上传完成";
            m_cm.writeRecord(login->getUser(), uploadFileInfo->fileName, "008");
        }
        else if("009" == m_cm.getCode(array) )
        {
            cout << fileName.toUtf8().data() << " ---> 上传失败";
            m_cm.writeRecord(login->getUser(), uploadFileInfo->fileName, "009");
        }


        //获取上传列表实例
        UploadTask *uploadList = UploadTask::getInstance();
        if(uploadList == NULL)
        {
            cout << "UploadTask::getInstance() == NULL";
            return;
        }

        uploadList->dealUploadTask(); //删除已经完成的上传任务
    }
    );
}

void FileListPage::slotOnDownloadFile(DownloadFileInfo* downloadFileInfo)
{

}

void FileListPage::slotOnRefreshFiles(Display cmd)
{
    //=========================>先获取用户文件数目<=========================
//    m_userFilesCount = 0;

//    m_cmd = cmd;

//    qDebug() << "request refresh.";

//    m_loginInfoInstance = LoginInfoInstance::getInstance(); //获取单例

//    HttpAgent::instance()->RequestOnRefreshFiles(m_loginInfoInstance);

    //=========================>先获取用户文件数目<=========================
    m_userFilesCount = 0;

    QNetworkRequest request; //请求对象

    // 获取登陆信息实例
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //获取单例

    // 127.0.0.1:80/myfiles&cmd=count		//获取用户文件个数
   // QString url = QString("http://%1:%2/myfiles?cmd=count").arg(login->getIp()).arg(login->getPort());
    QString url = "http://192.168.0.188:80/myfiles?cmd=count";
    request.setUrl(QUrl( url )); //设置url

    // qt默认的请求头
    // request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QByteArray data = setGetCountJson( login->getUser(), login->getToken());

    // 发送post请求
    QNetworkReply * reply = m_manager->post( request, data );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    // 获取请求的数据完成时，就会发送信号SIGNAL(finished())
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //有错误
        {
            cout << reply->errorString();
            reply->deleteLater(); //释放资源
            return;
        }

        // 服务器返回数据
        QByteArray array = reply->readAll();
        cout << "server return file ...: " << array;

        reply->deleteLater(); //释放

        // 得到服务器json文件
        QStringList list = getCountStatus(array);

        // token验证失败
        if( list.at(0) == "111" )
        {
            QMessageBox::warning(this, "账户异常", "请重新登陆！！！");

            emit loginAgainSignal(); //发送重新登陆信号

            return; //中断
        }

        // 转换为long
        m_userFilesCount = list.at(1).toLong();
        cout << "userFilesCount = " << m_userFilesCount;

        // 清空文件列表信息
        clearFileList();

        if(m_userFilesCount > 0)
        {
            // 说明用户有文件，获取用户文件列表
            m_start = 0;  //从0开始
            m_count = 10; //每次请求10个

            // 获取新的文件列表信息
            getUserFilesList(cmd);
        }
        else //没有文件
        {
            refreshFileItems(); //更新item
        }
    });
}

void FileListPage::slotOnGetUserFilesList(Display cmd)
{
    //遍历数目，结束条件处理
    if(m_userFilesCount <= 0) //结束条件，这个条件很重要，函数递归的结束条件
    {
        cout << "获取用户文件列表条件结束";
        refreshFileItems(); //更新item
        return; //中断函数
    }
    else if(m_count > m_userFilesCount) //如果请求文件数量大于用户的文件数目
    {
        m_count = m_userFilesCount;
    }

    m_loginInfoInstance = LoginInfoInstance::getInstance();
    HttpAgent::instance()->RequestOnGetUserFilesList(m_loginInfoInstance, m_start, m_count, cmd);

    m_start += m_count;
    m_userFilesCount -= m_count;
}

void FileListPage::RespondOnUpload(QString nCode)
{
    /*
    秒传文件：
        文件已存在：{"code":"005"}
        秒传成功：  {"code":"006"}
        秒传失败：  {"code":"007"}
    token验证失败：{"code":"111"}

    */
    if("006" == nCode ) //common.h
    {
        //秒传文件成功
        //cout << info->fileName.toUtf8().data() << "-->秒传成功";
     //   m_cm.writeRecord(login->getUser(), info->fileName, "006");

        //删除已经完成的上传任务
        //m_uploadTask->dealUploadTask();
    }
    else if("007" == nCode )
    {
        // 说明后台服务器没有此文件，需要真正的文件上传
//        uploadFile(m_uploadFileInfo);
        //emit RequestOnUploadInReal(m_uploadFileInfo);
        slotOnUploadFileInReal(m_uploadFileInfo);
    }
    else if("005" == nCode)// "005", 上传的文件已存在
    {
        //QMessageBox::information(this, "文件已存在", QString("%1 已存在").arg(info->fileName))
        //cout << QString("%1 已存在").arg(info->fileName).toUtf8().data();
       // m_cm.writeRecord(login->getUser(), info->fileName, "005");

        //删除已经完成的上传任务
       // m_uploadTask->dealUploadTask();
    }
    else if("111" == nCode) //token验证失败
    {
        QMessageBox::warning(this, "账户异常", "请重新登陆！！！");
        emit loginAgainSignal(); //发送重新登陆信号
        return;
    }
}

void FileListPage::RespondOnUploadInReal(QString nCode)
{
    if("008" == nCode ) //common.h
    {
        //cout << fileName.toUtf8().data() <<" ---> 上传完成";
        m_cm.writeRecord(m_loginInfoInstance->getUser(), m_uploadFileInfo->fileName, "008");
    }
    else if("009" == nCode )
    {
        //cout << fileName.toUtf8().data() << " ---> 上传失败";
        m_cm.writeRecord(m_loginInfoInstance->getUser(), m_uploadFileInfo->fileName, "009");
    }
}

void FileListPage::RespondOnRefreshFiles(QString nCode, long nCount)
{
    qDebug() << "FileListPage::RespondOnRefreshFiles";
    m_userFilesCount = nCount;

    qDebug() << "nCount : " << nCount;

    if ("111" == nCode)
    {
        QMessageBox::warning(this, "账户异常", "请重新登陆！！！");

        emit loginAgainSignal(); //发送重新登陆信号

        return; //中断
    }

    // 清空文件列表信息
    clearFileList();

    if(m_userFilesCount > 0)
    {
        qDebug() << "get files";
        // 说明用户有文件，获取用户文件列表
        m_start = 0;  //从0开始
        m_count = 10; //每次请求10个

        // 获取新的文件列表信息
        //getUserFilesList(cmd);
        //emit RequestOnGetUserFilesList(m_cmd);
        slotOnGetUserFilesList(m_cmd);
    }
    else //没有文件
    {
        refreshFileItems(); //更新item
    }
}

void FileListPage::RespondOnGetUserFilesList(QString nCode, QByteArray responseResult)
{
    //token验证失败
    if("111" == nCode) //common.h
    {
        QMessageBox::warning(this, "账户异常", "请重新登陆！！！");
        emit loginAgainSignal(); //发送重新登陆信号

        return; //中断
    }

    //不是错误码就处理文件列表json信息
    if ("015" != nCode) //common.h
    {
        //cout << array.data();
        getFileJsonInfo(responseResult);//解析文件列表json信息，存放在文件列表中

        //继续获取用户文件列表
        emit RequestOnGetUserFilesList(m_cmd);
    }
}

void FileListPage::rightMenu(const QPoint &pos)
{
    QListWidgetItem *item = ui->listWidget->itemAt(pos);

    if (item == nullptr){
        m_menuEmpty->exec(QCursor::pos());
    } else {
        ui->listWidget->setCurrentItem(item);
        if (item->text() == "上传文件")
            return;
        m_menu->exec(QCursor::pos());
    }
}

void FileListPage::clearAllTask()
{

}

void FileListPage::checkTaskList()
{
    //定时检查上传队列是否有任务需要上传
    connect(&m_uploadFileTimer, &QTimer::timeout, [=]()
    {
        //上传文件处理，取出上传任务列表的队首任务，上传完后，再取下一个任务
//        uploadFilesAction();
      //  emit RequestOnUpload();
        slotOnUploadFile();
    });

    // 启动定时器，500毫秒间隔
    // 每个500毫秒，检测上传任务，每一次只能上传一个文件
    m_uploadFileTimer.start(500);

    // 定时检查下载队列是否有任务需要下载
    connect(&m_downloadTimer, &QTimer::timeout, [=]()
    {
        // 上传文件处理，取出上传任务列表的队首任务，上传完后，再取下一个任务
//        downloadFilesAction();
       // emit RequestOnDownload(DownloadFileInfo* downloadFileInfo);
    });

    // 启动定时器，500毫秒间隔
    // 每个500毫秒，检测下载任务，每一次只能下载一个文件
    m_downloadTimer.start(500);
}































