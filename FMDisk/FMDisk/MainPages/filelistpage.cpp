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

    // ��ʱ����������
    checkTaskList();
}

FileListPage::~FileListPage()
{
    delete ui;
}

void FileListPage::init()
{
    // ��ʼ��listWidget�ļ��б�
    initListWidget();
    // ����Ҽ��˵�
    addActionMenu();
}

void FileListPage::initListWidget()
{
    ui->listWidget->setViewMode(QListView::IconMode);   //������ʾͼ��ģʽ
    ui->listWidget->setIconSize(QSize(80, 80));         //����ͼ���С
    ui->listWidget->setGridSize(QSize(100, 120));       //����item��С

    // ����QLisView��С�ı�ʱ��ͼ��ĵ���ģʽ��Ĭ���ǹ̶��ģ����Ըĳ��Զ�����
    ui->listWidget->setResizeMode(QListView::Adjust);   //�Զ���Ӧ����

    // �����б�����϶��������̶������϶���ʹ��QListView::Static
    ui->listWidget->setMovement(QListView::Static);
    // ����ͼ��֮��ļ��, ��setGridSize()ʱ����ѡ����Ч
    ui->listWidget->setSpacing(30);

    // listWidget �Ҽ��˵�
    // ���� customContextMenuRequested �ź�
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, &QListWidget::customContextMenuRequested, this, &FileListPage::rightMenu);
    // �����б��е��ϴ��ļ�ͼ��
    connect(ui->listWidget, &QListWidget::itemPressed, this, [=](QListWidgetItem* item)
    {
        QString str = item->text();
        if(str == "�ϴ��ļ�")
        {
            //�����Ҫ�ϴ����ļ����ϴ������б�
            addUploadFiles();
        }
    });
}

void FileListPage::addActionMenu()
{
    //===================�˵�1==================
    m_menu = new CustomMenu( this );

    // ��ʼ���˵���
    m_downloadAction = new QAction("����", this);
    m_shareAction = new QAction("����", this);
    m_delAction = new QAction("ɾ��", this);
    m_propertyAction = new QAction("����", this);

    // ����1��ӵ��˵�1
    m_menu->addAction(m_downloadAction);
    m_menu->addAction(m_shareAction);
    m_menu->addAction(m_delAction);
    m_menu->addAction(m_propertyAction);

    //===================�˵�2===================
    m_menuEmpty = new CustomMenu( this );
    // ����2
    m_pvAscendingAction = new QAction("������������", this);
    m_pvDescendingAction = new QAction("������������", this);
    m_refreshAction = new QAction("ˢ��", this);
    m_uploadAction = new QAction("�ϴ�", this);

    // ����2��ӵ��˵�2
    m_menuEmpty->addAction(m_pvAscendingAction);
    m_menuEmpty->addAction(m_pvDescendingAction);
    m_menuEmpty->addAction(m_refreshAction);
    m_menuEmpty->addAction(m_uploadAction);

    //=====================�ź����===================
    // ����
    connect(m_downloadAction, &QAction::triggered, [=]()
    {
        cout << "���ض���";
        //�����Ҫ���ص��ļ������������б�
       // addDownloadFiles();
    });

    // ����
    connect(m_shareAction, &QAction::triggered, [=]()
    {
        cout << "������";
//        dealSelectdFile("����"); //����ѡ�е��ļ�
    });

    // ɾ��
    connect(m_delAction, &QAction::triggered, [=]()
    {
        cout << "ɾ������";
//        dealSelectdFile("ɾ��"); //����ѡ�е��ļ�
    });

    // ����
    connect(m_propertyAction, &QAction::triggered, [=]()
    {
        cout << "���Զ���";
//        dealSelectdFile("����"); //����ѡ�е��ļ�
    });

    // ������������
    connect(m_pvAscendingAction, &QAction::triggered, [=]()
    {
        cout << "������������";
//        refreshFiles(PvAsc);
        emit RequestOnRefreshFiles(PvAsc);
    });

    // ������������
    connect(m_pvDescendingAction, &QAction::triggered, [=]()
    {
        cout << "������������";
//        refreshFiles(PvDesc);
        emit RequestOnRefreshFiles(PvDesc);
    });

    //ˢ��
    connect(m_refreshAction, &QAction::triggered, [=]()
    {
        cout << "ˢ�¶���";
        //��ʾ�û����ļ��б�
        emit RequestOnRefreshFiles(Normal);
    });

    //�ϴ�
    connect(m_uploadAction, &QAction::triggered, [=]()
    {
        cout << "�ϴ�����";
        //�����Ҫ�ϴ����ļ����ϴ������б�
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

    //����Դ����jsonת��ΪJsonDocument
    //��QByteArray������һ��QJsonDocument�����������ǵĶ�д����
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) //û�г���
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return list;
        }

        if( doc.isObject() )
        {
            QJsonObject obj = doc.object();//ȡ���������������
            list.append( obj.value( "token" ).toString() ); //��½token
            list.append( obj.value( "num" ).toString() ); //�ļ�����
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

    /*json��������
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
    //������Ŀ��������������
    if(m_userFilesCount <= 0) //���������������������Ҫ�������ݹ�Ľ�������
    {
        cout << "��ȡ�û��ļ��б���������";
        refreshFileItems(); //����item
        return; //�жϺ���
    }
    else if(m_count > m_userFilesCount) //��������ļ����������û����ļ���Ŀ
    {
        m_count = m_userFilesCount;
    }


    QNetworkRequest request; //�������

    // ��ȡ��½��Ϣʵ��
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //��ȡ����

    // ��ȡ�û��ļ���Ϣ 127.0.0.1:80/myfiles&cmd=normal
    // ������������ 127.0.0.1:80/myfiles?cmd=pvasc
    // ������������127.0.0.1:80/myfiles?cmd=pvdesc
    QString url;

    QString tmp;
    //cmdȡֵ��Normal����ͨ�û��б�PvAsc�������������� PvDesc��������������
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
    request.setUrl(QUrl( url )); //����url
    cout << "myfiles url: " << url;

    //qtĬ�ϵ�����ͷ
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

    //�ı��ļ����λ��
    m_start += m_count;
    m_userFilesCount -= m_count;

    //����post����
    QNetworkReply * reply = m_manager->post( request, data );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    //��ȡ������������ʱ���ͻᷢ���ź�SIGNAL(finished())
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //�д���
        {
            cout << reply->errorString();
            reply->deleteLater(); //�ͷ���Դ
            return;
        }

        //�����������û�������
        QByteArray array = reply->readAll();
        cout << "file info:" << array;

        reply->deleteLater();

        //token��֤ʧ��
        if("111" == m_cm.getCode(array) ) //common.h
        {
            QMessageBox::warning(this, "�˻��쳣", "�����µ�½������");
            emit loginAgainSignal(); //�������µ�½�ź�

            return; //�ж�
        }

        //���Ǵ�����ʹ����ļ��б�json��Ϣ
        if("015" != m_cm.getCode(array) ) //common.h
        {
            //cout << array.data();
            getFileJsonInfo(array);//�����ļ��б�json��Ϣ��������ļ��б���

            //������ȡ�û��ļ��б�
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
    //-- user	�ļ������û�
    //-- md5 �ļ�md5
    //-- createtime �ļ�����ʱ��
    //-- filename �ļ�����
    //-- shared_status ����״̬, 0Ϊû�й��� 1Ϊ����
    //-- pv �ļ���������Ĭ��ֵΪ0������һ�μ�1
    //-- url �ļ�url
    //-- size �ļ���С, ���ֽ�Ϊ��λ
    //-- type �ļ����ͣ� png, zip, mp4����

    //����Դ����jsonת��ΪJsonDocument
    //��QByteArray������һ��QJsonDocument�����������ǵĶ�д����
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    if (error.error == QJsonParseError::NoError) //û�г���
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if( doc.isObject())
        {
            //QJsonObject json��������json������{}����������
            QJsonObject obj = doc.object();//ȡ���������������

            //��ȡgames����Ӧ������
            //QJsonArray json���飬����json������[]����������
            QJsonArray array = obj.value("files").toArray();

            int size = array.size();   //�������
            cout << "size = " << size;

            for(int i = 0; i < size; ++i)
            {
                QJsonObject tmp = array[i].toObject(); //ȡ��i������
                /*
                    //�ļ���Ϣ
                    struct FileInfo
                    {
                        QString md5;        //�ļ�md5��
                        QString filename;   //�ļ�����
                        QString user;       //�û�
                        QString time;       //�ϴ�ʱ��
                        QString url;        //url
                        QString type;       //�ļ�����
                        qint64 size;        //�ļ���С
                        int shareStatus;    //�Ƿ���, 1���� 0������
                        int pv;             //������
                        QListWidgetItem *item; //list widget ��item
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
                info->user = tmp.value("user").toString(); //�û�
                info->md5 = tmp.value("md5").toString(); //�ļ�md5
                info->time = tmp.value("time").toString(); //�ϴ�ʱ��
                info->filename = tmp.value("filename").toString(); //�ļ�����
                info->shareStatus = tmp.value("share_status").toInt(); //����״̬
                info->pv = tmp.value("pv").toInt(); //������
                info->url = tmp.value("url").toString(); //url
                info->size = tmp.value("size").toInt(); //�ļ���С�����ֽ�Ϊ��λ
                info->type = tmp.value("type").toString();//�ļ���׺
                QString type = info->type + ".png";
                info->item = new QListWidgetItem(QIcon( m_cm.getFileType(type) ), info->filename);

                //list��ӽڵ�
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
//    // �л��������б��, �ϴ�����
//    emit gotoTransfer(TransferStatus::Uplaod);
//    //��ȡ�ϴ��б�ʵ��
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
//        qDebug() << "��ѡ�ļ�Ϊ��"<<list.at(i);
//        //  -1: �ļ�����30m
//        //  -2���ϴ����ļ��Ƿ��Ѿ����ϴ�������
//        //  -3: ���ļ�ʧ��
//        //  -4: ��ȡ����ʧ��
//        int res = m_uploadTask->appendUploadList(list.at(i));
//        if(res == -1)
//        {
//            QMessageBox::warning(this, "�ļ�̫��", "�ļ���С���ܳ���30M������");
//        }
//        else if(res == -2)
//        {
//            QMessageBox::warning(this, "���ʧ��", "�ϴ����ļ��Ƿ��Ѿ����ϴ������У�����");
//        }
//        else if(res == -3)
//        {
//            cout << "���ļ�ʧ��";
//        }
//        else if(res == -4)
//        {
//            cout << "��ȡ����ʧ��";
//        }
//    }

    // �л��������б��, �ϴ�����
    emit gotoTransfer(TransferStatus::Uplaod);
    //��ȡ�ϴ��б�ʵ��
    UploadTask *uploadList = UploadTask::getInstance();
    if(uploadList == NULL)
    {
        cout << "UploadTask::getInstance() == NULL";
        return;
    }

    QStringList list = QFileDialog::getOpenFileNames();
    for(int i = 0; i < list.size(); ++i)
    {
        //cout << "��ѡ�ļ�Ϊ��"<<list.at(i);
        //  -1: �ļ�����30m
        //  -2���ϴ����ļ��Ƿ��Ѿ����ϴ�������
        //  -3: ���ļ�ʧ��
        //  -4: ��ȡ����ʧ��
        int res = uploadList->appendUploadList(list.at(i));
        if(res == -1)
        {
            QMessageBox::warning(this, "�ļ�̫��", "�ļ���С���ܳ���30M������");
        }
        else if(res == -2)
        {
            QMessageBox::warning(this, "���ʧ��", "�ϴ����ļ��Ƿ��Ѿ����ϴ������У�����");
        }
        else if(res == -3)
        {
            cout << "���ļ�ʧ��";
        }
        else if(res == -4)
        {
            cout << "��ȡ����ʧ��";
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
    //ʹ��QListWidget::count()��ͳ��ListWidget���ܹ���item��Ŀ
    int n = ui->listWidget->count();
    qDebug() << "n = " << n;
    for(int i = 0; i < n; ++i)
    {
        QListWidgetItem *item = ui->listWidget->takeItem(0); //������0������i
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

    //����ļ��б�Ϊ�գ���ʾ�ļ��б�
    if(m_fileList.isEmpty() == false)
    {
        int n = m_fileList.size(); //Ԫ�ظ���
        qDebug() << "files count = " << n;
        for(int i = 0; i < n; ++i)
        {
            FileInfo *tmp = m_fileList.at(i);
            QListWidgetItem *item = tmp->item;
            //list widget add item
            ui->listWidget->addItem(item);
        }
    }

    //����ϴ��ļ�item
    this->addUploadItem();
}

void FileListPage::slotOnUploadFile()
{
   // qDebug() << "begin upoload";
    // ��ȡ�ϴ��б�ʵ��
//    UploadTask *m_uploadTask = UploadTask::getInstance();
//    m_uploadTask = UploadTask::getInstance();
//    if(m_uploadTask == NULL)
//    {
//        cout << "UploadTask::getInstance() == NULL";
//        return;
//    }

//    // �������Ϊ�գ����ϴ�������ֹ����
//    if( m_uploadTask->isEmpty() )
//    {
//        return;
//    }

//    // �鿴�Ƿ����ϴ����񣬵������ϴ�����ǰ�����񣬲����ϴ�
//    if( m_uploadTask->isUpload() )
//    {
//        return;
//    }

//    // ��ȡ��½��Ϣʵ��
//    m_loginInfoInstance = LoginInfoInstance::getInstance(); //��ȡ����

//    //
//    m_uploadFileInfo = m_uploadTask->takeTask();

//    //�˴��ɳ��������߳�

//    HttpAgent::instance()->RequestOnUpload( m_uploadFileInfo, m_loginInfoInstance);

   // qDebug() << "MyFileWg::uploadFilesAction()";
    // ��ȡ�ϴ��б�ʵ��
    UploadTask *uploadList = UploadTask::getInstance();
    if(uploadList == NULL)
    {
        cout << "UploadTask::getInstance() == NULL";
        return;
    }

    // �������Ϊ�գ����ϴ�������ֹ����
    if( uploadList->isEmpty() )
    {
        return;
    }

    // �鿴�Ƿ����ϴ����񣬵������ϴ�����ǰ�����񣬲����ϴ�
    if( uploadList->isUpload() )
    {
        return;
    }

    // ��ȡ��½��Ϣʵ��
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //��ȡ����

    // url
    QNetworkRequest request;
//    QString url = QString("http://%1:%2/md5").arg( login->getIp() ).arg( login->getPort() );
    QString url = "http://192.168.0.188:80/md5";
    request.setUrl( QUrl( url )); //����url
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // ȡ����0���ϴ���������������û���������ϴ������õ�0�������ϴ�
    UploadFileInfo *info = uploadList->takeTask();

    // post���ݰ�
    QByteArray array = setMd5Json(login->getUser(), login->getToken(), info->md5, info->fileName);
    qDebug() << "post array : " << array;

    // ����post����
    QNetworkReply *reply = m_manager->post(request, array);
    if(reply == NULL)
    {
        cout << "reply is NULL";
        return;
    }

    // �źźͲ�����
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //�д���
        {
            cout << reply->errorString();
            reply->deleteLater(); //�ͷ���Դ
            return;
        }

        QByteArray array = reply->readAll();
        qDebug() << "response array : " << array;
        //cout << array.data();
        reply->deleteLater(); //�ͷ���Դ

        /*
        �봫�ļ���
            �ļ��Ѵ��ڣ�{"code":"005"}
            �봫�ɹ���  {"code":"006"}
            �봫ʧ�ܣ�  {"code":"007"}
        token��֤ʧ�ܣ�{"code":"111"}

        */
        if("006" == m_cm.getCode(array) ) //common.h
        {
            //�봫�ļ��ɹ�
            //cout << info->fileName.toUtf8().data() << "-->�봫�ɹ�";
            m_cm.writeRecord(login->getUser(), info->fileName, "006");

            //ɾ���Ѿ���ɵ��ϴ�����
            uploadList->dealUploadTask();
        }
        else if("007" == m_cm.getCode(array) )
        {
            // ˵����̨������û�д��ļ�����Ҫ�������ļ��ϴ�
            slotOnUploadFileInReal(info);
        }
        else if("005" == m_cm.getCode(array) )// "005", �ϴ����ļ��Ѵ���
        {
            //QMessageBox::information(this, "�ļ��Ѵ���", QString("%1 �Ѵ���").arg(info->fileName))
            //cout << QString("%1 �Ѵ���").arg(info->fileName).toUtf8().data();
            m_cm.writeRecord(login->getUser(), info->fileName, "005");

            //ɾ���Ѿ���ɵ��ϴ�����
            uploadList->dealUploadTask();
        }
        else if("111" == m_cm.getCode(array)) //token��֤ʧ��
        {
            QMessageBox::warning(this, "�˻��쳣", "�����µ�½������");
            emit loginAgainSignal(); //�������µ�½�ź�
            return;
        }
    });
}

// ����md5��Ϣ��json��
QByteArray FileListPage::setMd5Json(QString user, QString token, QString md5, QString fileName)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);
    tmp.insert("md5", md5);
    tmp.insert("fileName", fileName);

    /*json��������
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
    // ȡ���ϴ�����
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

    //ȡ���ϴ�����
    QFile *file = uploadFileInfo->file;           //�ļ�ָ��
    QString fileName = uploadFileInfo->fileName;  //�ļ�����
    QString md5 = uploadFileInfo->md5;            //�ļ�md5��
    qint64 size = uploadFileInfo->size;           //�ļ���С
    DataProgress *dp = uploadFileInfo->dp;        //�������ؼ�
    QString boundary = m_cm.getBoundary();   //�����ָ���

    //��ȡ��½��Ϣʵ��
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //��ȡ����
#if 0
    QByteArray data;

    /*
    ------WebKitFormBoundary88asdgewtgewx\r\n
    Content-Disposition: form-data; user="mike"; filename="xxx.jpg"; md5="xxxx"; size=10240\r\n
    Content-Type: application/octet-stream\r\n
    \r\n
    �������ļ�����\r\n
    ------WebKitFormBoundary88asdgewtgewx
    */

    //��1�У��ָ���
    data.append(boundary);
    data.append("\r\n");

    //�ϴ��ļ���Ϣ
    data.append("Content-Disposition: form-data; ");
    data.append( QString("user=\"%1\" ").arg( login->getUser() ) ); //�ϴ��û�
    data.append( QString("filename=\"%1\" ").arg(fileName) ); //�ļ�����
    data.append( QString("md5=\"%1\" ").arg(md5) ); //�ļ�md5��
    data.append( QString("size=%1").arg(size)  );   //�ļ���С
    data.append("\r\n");

    data.append("Content-Type: application/octet-stream");
    data.append("\r\n");
    data.append("\r\n");

    // �ϴ��ļ�����
    data.append( file->readAll() ); //�ļ�����
    data.append("\r\n");

    // �����ָ���
    data.append(boundary);
#endif
    QHttpPart part;
    QString disp = QString("form-data; user=\"%1\"; filename=\"%2\"; md5=\"%3\"; size=%4")
            .arg(login->getUser()).arg(uploadFileInfo->fileName).arg(uploadFileInfo->md5).arg(uploadFileInfo->size);
    part.setHeader(QNetworkRequest::ContentDispositionHeader, disp);
    part.setHeader(QNetworkRequest::ContentTypeHeader, "image/png"); // ������ļ���Ӧ��content-type
    part.setBodyDevice(uploadFileInfo->file);
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    multiPart->append(part);


    QNetworkRequest request; //�������
    //http://127.0.0.1:80/upload
//    QString url = QString("http://%1:%2/upload").arg(login->getIp()).arg(login->getPort());
    QString url = "http://192.168.0.188:80/upload";
    request.setUrl(QUrl( url )); //����url

    // qtĬ�ϵ�����ͷ
    //request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");

    // ����post����
    QNetworkReply * reply = m_manager->post( request, multiPart );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    // �п������ݸ���ʱ
    connect(reply, &QNetworkReply::uploadProgress, [=](qint64 bytesRead, qint64 totalBytes)
    {
        if(totalBytes != 0) //�����������Ҫ
        {
            //cout << bytesRead/1024 << ", " << totalBytes/1024;
            dp->setProgress(bytesRead/1024, totalBytes/1024); //���ý�����
        }
    });

    // ��ȡ������������ʱ���ͻᷢ���ź�SIGNAL(finished())
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //�д���
        {
            cout << reply->errorString();
            reply->deleteLater(); //�ͷ���Դ
            m_cm.writeRecord(login->getUser(), uploadFileInfo->fileName, "009");
            UploadTask *uploadList = UploadTask::getInstance();
            uploadList->dealUploadTask(); //ɾ���Ѿ���ɵ��ϴ�����
            return;
        }

        QByteArray array = reply->readAll();

        qDebug() << "response array : " << array;

        reply->deleteLater();
        // ��������
        multiPart->deleteLater();

        /*
            �ϴ��ļ���
                �ɹ���{"code":"008"}
                ʧ�ܣ�{"code":"009"}
            */
        if("008" == m_cm.getCode(array) ) //common.h
        {
            cout << fileName.toUtf8().data() <<" ---> �ϴ����";
            m_cm.writeRecord(login->getUser(), uploadFileInfo->fileName, "008");
        }
        else if("009" == m_cm.getCode(array) )
        {
            cout << fileName.toUtf8().data() << " ---> �ϴ�ʧ��";
            m_cm.writeRecord(login->getUser(), uploadFileInfo->fileName, "009");
        }


        //��ȡ�ϴ��б�ʵ��
        UploadTask *uploadList = UploadTask::getInstance();
        if(uploadList == NULL)
        {
            cout << "UploadTask::getInstance() == NULL";
            return;
        }

        uploadList->dealUploadTask(); //ɾ���Ѿ���ɵ��ϴ�����
    }
    );
}

void FileListPage::slotOnDownloadFile(DownloadFileInfo* downloadFileInfo)
{

}

void FileListPage::slotOnRefreshFiles(Display cmd)
{
    //=========================>�Ȼ�ȡ�û��ļ���Ŀ<=========================
//    m_userFilesCount = 0;

//    m_cmd = cmd;

//    qDebug() << "request refresh.";

//    m_loginInfoInstance = LoginInfoInstance::getInstance(); //��ȡ����

//    HttpAgent::instance()->RequestOnRefreshFiles(m_loginInfoInstance);

    //=========================>�Ȼ�ȡ�û��ļ���Ŀ<=========================
    m_userFilesCount = 0;

    QNetworkRequest request; //�������

    // ��ȡ��½��Ϣʵ��
    LoginInfoInstance *login = LoginInfoInstance::getInstance(); //��ȡ����

    // 127.0.0.1:80/myfiles&cmd=count		//��ȡ�û��ļ�����
   // QString url = QString("http://%1:%2/myfiles?cmd=count").arg(login->getIp()).arg(login->getPort());
    QString url = "http://192.168.0.188:80/myfiles?cmd=count";
    request.setUrl(QUrl( url )); //����url

    // qtĬ�ϵ�����ͷ
    // request.setRawHeader("Content-Type","text/html");
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

    QByteArray data = setGetCountJson( login->getUser(), login->getToken());

    // ����post����
    QNetworkReply * reply = m_manager->post( request, data );
    if(reply == NULL)
    {
        cout << "reply == NULL";
        return;
    }

    // ��ȡ������������ʱ���ͻᷢ���ź�SIGNAL(finished())
    connect(reply, &QNetworkReply::finished, [=]()
    {
        if (reply->error() != QNetworkReply::NoError) //�д���
        {
            cout << reply->errorString();
            reply->deleteLater(); //�ͷ���Դ
            return;
        }

        // ��������������
        QByteArray array = reply->readAll();
        cout << "server return file ...: " << array;

        reply->deleteLater(); //�ͷ�

        // �õ�������json�ļ�
        QStringList list = getCountStatus(array);

        // token��֤ʧ��
        if( list.at(0) == "111" )
        {
            QMessageBox::warning(this, "�˻��쳣", "�����µ�½������");

            emit loginAgainSignal(); //�������µ�½�ź�

            return; //�ж�
        }

        // ת��Ϊlong
        m_userFilesCount = list.at(1).toLong();
        cout << "userFilesCount = " << m_userFilesCount;

        // ����ļ��б���Ϣ
        clearFileList();

        if(m_userFilesCount > 0)
        {
            // ˵���û����ļ�����ȡ�û��ļ��б�
            m_start = 0;  //��0��ʼ
            m_count = 10; //ÿ������10��

            // ��ȡ�µ��ļ��б���Ϣ
            getUserFilesList(cmd);
        }
        else //û���ļ�
        {
            refreshFileItems(); //����item
        }
    });
}

void FileListPage::slotOnGetUserFilesList(Display cmd)
{
    //������Ŀ��������������
    if(m_userFilesCount <= 0) //���������������������Ҫ�������ݹ�Ľ�������
    {
        cout << "��ȡ�û��ļ��б���������";
        refreshFileItems(); //����item
        return; //�жϺ���
    }
    else if(m_count > m_userFilesCount) //��������ļ����������û����ļ���Ŀ
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
    �봫�ļ���
        �ļ��Ѵ��ڣ�{"code":"005"}
        �봫�ɹ���  {"code":"006"}
        �봫ʧ�ܣ�  {"code":"007"}
    token��֤ʧ�ܣ�{"code":"111"}

    */
    if("006" == nCode ) //common.h
    {
        //�봫�ļ��ɹ�
        //cout << info->fileName.toUtf8().data() << "-->�봫�ɹ�";
     //   m_cm.writeRecord(login->getUser(), info->fileName, "006");

        //ɾ���Ѿ���ɵ��ϴ�����
        //m_uploadTask->dealUploadTask();
    }
    else if("007" == nCode )
    {
        // ˵����̨������û�д��ļ�����Ҫ�������ļ��ϴ�
//        uploadFile(m_uploadFileInfo);
        //emit RequestOnUploadInReal(m_uploadFileInfo);
        slotOnUploadFileInReal(m_uploadFileInfo);
    }
    else if("005" == nCode)// "005", �ϴ����ļ��Ѵ���
    {
        //QMessageBox::information(this, "�ļ��Ѵ���", QString("%1 �Ѵ���").arg(info->fileName))
        //cout << QString("%1 �Ѵ���").arg(info->fileName).toUtf8().data();
       // m_cm.writeRecord(login->getUser(), info->fileName, "005");

        //ɾ���Ѿ���ɵ��ϴ�����
       // m_uploadTask->dealUploadTask();
    }
    else if("111" == nCode) //token��֤ʧ��
    {
        QMessageBox::warning(this, "�˻��쳣", "�����µ�½������");
        emit loginAgainSignal(); //�������µ�½�ź�
        return;
    }
}

void FileListPage::RespondOnUploadInReal(QString nCode)
{
    if("008" == nCode ) //common.h
    {
        //cout << fileName.toUtf8().data() <<" ---> �ϴ����";
        m_cm.writeRecord(m_loginInfoInstance->getUser(), m_uploadFileInfo->fileName, "008");
    }
    else if("009" == nCode )
    {
        //cout << fileName.toUtf8().data() << " ---> �ϴ�ʧ��";
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
        QMessageBox::warning(this, "�˻��쳣", "�����µ�½������");

        emit loginAgainSignal(); //�������µ�½�ź�

        return; //�ж�
    }

    // ����ļ��б���Ϣ
    clearFileList();

    if(m_userFilesCount > 0)
    {
        qDebug() << "get files";
        // ˵���û����ļ�����ȡ�û��ļ��б�
        m_start = 0;  //��0��ʼ
        m_count = 10; //ÿ������10��

        // ��ȡ�µ��ļ��б���Ϣ
        //getUserFilesList(cmd);
        //emit RequestOnGetUserFilesList(m_cmd);
        slotOnGetUserFilesList(m_cmd);
    }
    else //û���ļ�
    {
        refreshFileItems(); //����item
    }
}

void FileListPage::RespondOnGetUserFilesList(QString nCode, QByteArray responseResult)
{
    //token��֤ʧ��
    if("111" == nCode) //common.h
    {
        QMessageBox::warning(this, "�˻��쳣", "�����µ�½������");
        emit loginAgainSignal(); //�������µ�½�ź�

        return; //�ж�
    }

    //���Ǵ�����ʹ����ļ��б�json��Ϣ
    if ("015" != nCode) //common.h
    {
        //cout << array.data();
        getFileJsonInfo(responseResult);//�����ļ��б�json��Ϣ��������ļ��б���

        //������ȡ�û��ļ��б�
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
        if (item->text() == "�ϴ��ļ�")
            return;
        m_menu->exec(QCursor::pos());
    }
}

void FileListPage::clearAllTask()
{

}

void FileListPage::checkTaskList()
{
    //��ʱ����ϴ������Ƿ���������Ҫ�ϴ�
    connect(&m_uploadFileTimer, &QTimer::timeout, [=]()
    {
        //�ϴ��ļ�����ȡ���ϴ������б�Ķ��������ϴ������ȡ��һ������
//        uploadFilesAction();
      //  emit RequestOnUpload();
        slotOnUploadFile();
    });

    // ������ʱ����500������
    // ÿ��500���룬����ϴ�����ÿһ��ֻ���ϴ�һ���ļ�
    m_uploadFileTimer.start(500);

    // ��ʱ������ض����Ƿ���������Ҫ����
    connect(&m_downloadTimer, &QTimer::timeout, [=]()
    {
        // �ϴ��ļ�����ȡ���ϴ������б�Ķ��������ϴ������ȡ��һ������
//        downloadFilesAction();
       // emit RequestOnDownload(DownloadFileInfo* downloadFileInfo);
    });

    // ������ʱ����500������
    // ÿ��500���룬�����������ÿһ��ֻ������һ���ļ�
    m_downloadTimer.start(500);
}































