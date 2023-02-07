#include <QFile>
#include <QMap>
#include <QDir>
#include <QTime>
#include <QFileInfo>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>
#include <QJsonDocument>
#include <QFileInfoList>
#include <QDesktopWidget>
#include <QCryptographicHash>
#include "des.h"
#include "common.h"

// ��ʼ������
QString Common::m_typePath = FILETYPEDIR;
QStringList Common::m_typeList = QStringList();
QNetworkAccessManager* Common::m_netManager = new QNetworkAccessManager;

Common* Common::instance = new Common;


Common *Common::getInstance()
{
    return instance;
}

Common::Common(QObject *parent)
{
    Q_UNUSED(parent)
}

// ��������Ļ������ʾ
void Common::moveToCenter(QWidget *tmp)
{
     // ��ʾ����
     tmp->show();
     // ��Ļ�м���ʾ
     // ʹ��qApp->desktop();Ҳ����
     QDesktopWidget* desktop = QApplication::desktop();
     // �ƶ�����
     tmp->move((desktop->width() - tmp->width())/2, (desktop->height() - tmp->height())/2);
}

/* -------------------------------------------*/
/**
 * @brief           �������ļ��еõ����Ӧ�Ĳ���
 *
 * @param title     �����ļ�title����[title]
 * @param key       key
 * @param path      �����ļ�·��
 *
 * @returns
 *                  success: �õ���value
 *                  fail:    �մ�
 */
/* -------------------------------------------*/
QString Common::getCfgValue(QString title, QString key, QString path)
{
    QFile file(path);

    // ֻ����ʽ��
    if( false == file.open(QIODevice::ReadOnly) )
    {
        // ��ʧ��
        cout << "file open err";
        return "";
    }

    QByteArray json = file.readAll(); // ��ȡ��������
    file.close(); // �ر��ļ�

    QJsonParseError error;

    // ����Դ����jsonת��ΪJsonDocument
    // ��QByteArray������һ��QJsonDocument�����������ǵĶ�д����
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) // û�г���
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return "";
        }

        if( doc.isObject()) // �������Ϊ��
        {
            // QJsonObject json��������json������{}����������
            QJsonObject obj = doc.object();// ȡ���������������

            QJsonObject tmp = obj.value( title ).toObject();
            QStringList list = tmp.keys(); // ȡ��key�б�
            for(int i = 0; i < list.size(); ++i)
            {
                if( list.at(i) == key )
                {
                    return tmp.value( list.at(i) ).toString();
                }
            }

        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }

    return "";
}

// ͨ����ȡ�ļ�, �õ��ļ�����, �����typeList
void Common::getFileTypeList()
{
    // QDir��ʹ����Ի�����ļ�·����ָ��һ���ļ�/Ŀ¼��
    QDir dir(m_typePath);
    if(!dir.exists())
    {
        dir.mkpath(m_typePath);
        cout << m_typePath << "�����ɹ�������";
    }

    /*
        QDir::Dirs      �г�Ŀ¼��
        QDir::AllDirs   �г�����Ŀ¼������Ŀ¼�����й��ˣ�
        QDir::Files     �г��ļ���
        QDir::Drives    �г��߼����������ƣ���ö�ٱ�����Linux/Unix�н������ԣ�
        QDir::NoSymLinks        ���г��������ӣ�
        QDir::NoDotAndDotDot    ���г��ļ�ϵͳ�е������ļ�.��..��
        QDir::NoDot             ���г�.�ļ�����ָ��ǰĿ¼��������
        QDir::NoDotDot          ���г�..�ļ���
        QDir::AllEntries        ��ֵΪDirs | Files | Drives���г�Ŀ¼���ļ����������������ӵ������ļ���
        QDir::Readable      �г���ǰӦ���ж�Ȩ�޵��ļ���Ŀ¼��
        QDir::Writable      �г���ǰӦ����дȨ�޵��ļ���Ŀ¼��
        QDir::Executable    �г���ǰӦ����ִ��Ȩ�޵��ļ���Ŀ¼��
        Readable��Writable��Executable����Ҫ��Dirs��Filesö��ֵ����ʹ�ã�
        QDir::Modified      �г��ѱ��޸ĵ��ļ�����ֵ��Linux/Unixϵͳ�н������ԣ�
        QDir::Hidden        �г������ļ���
        QDir::System        �г�ϵͳ�ļ���
        QDir::CaseSensitive �趨������Ϊ��Сд���С�
    */
    dir.setFilter(QDir::Files | QDir::NoDot |  QDir::NoDotDot | QDir::NoSymLinks); // �����ļ�
    dir.setSorting(QDir::Size | QDir::Reversed);   // ����

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        m_typeList.append( fileInfo.fileName() );
    }
}

// �õ��ļ���׺������Ϊ�ļ����ͣ������ڲ��ж��Ƿ��д����ͣ�����У�ʹ�ô����ͣ�û�У�ʹ��other.png
QString Common::getFileType(QString type)
{
    if(true == m_typeList.contains(type))
    {
        return m_typePath + "/" + type;
    }

    return m_typePath + "/other.png";
}

// ��¼��Ϣ��д�������ļ�
void Common::writeLoginInfo(QString user, QString pwd, bool isRemeber, QString path)
{
    // web_server��Ϣ
    QString ip = getCfgValue("web_server", "ip");
    QString port = getCfgValue("web_server", "port");

    QMap<QString, QVariant> web_server;
    web_server.insert("ip", ip);
    web_server.insert("port", port);

    // type_path��Ϣ
    QMap<QString, QVariant> type_path;
    type_path.insert("path", m_typePath);

    // login��Ϣ
    QMap<QString, QVariant> login;

    // ��½��Ϣ����
    int ret = 0;

    // ��½�û�����
    unsigned char encUsr[1024] = {0};
    int encUsrLen;
    // QString -> const char*
    // QString toutf8(QByteArray)->char*  (.data())
    // toLocal8Bit(), ת��Ϊ�����ַ��������windows��Ϊgbk���룬���linux��Ϊutf-8����
    ret = DesEnc((unsigned char *)user.toLocal8Bit().data(), user.toLocal8Bit().size(), encUsr, &encUsrLen);
    if(ret != 0)//����ʧ��
    {
        cout << "DesEnc err";
        return;
    }

    // �û��������
    unsigned char encPwd[512] = {0};
    int encPwdLen;
    // toLocal8Bit(), ת��Ϊ�����ַ��������windows��Ϊgbk���룬���linux��Ϊutf-8����
    ret = DesEnc((unsigned char *)pwd.toLocal8Bit().data(), pwd.toLocal8Bit().size(), encPwd, &encPwdLen);
    if(ret != 0)
    {
        cout << "DesEnc err";
        return;
    }

    // �ٴμ���
    // base64ת����ܣ�Ŀ�Ľ����ܺ�Ķ�����ת��Ϊbase64�ַ���
    login.insert("user",  QByteArray((char *)encUsr, encUsrLen).toBase64());
    login.insert("pwd", QByteArray((char *)encPwd, encPwdLen).toBase64() );
    if(isRemeber == true)
    {
         login.insert("remember", "yes");
    }
    else
    {
        login.insert("remember", "no");
    }

    // QVariant����Ϊһ����Ϊ�ձ��Qt�������͵�����
    // QVariantΪһ�����ܵ���������--������Ϊ������ͻ���֮������Զ�ת����
    QMap<QString, QVariant> json;
    json.insert("web_server", web_server);
    json.insert("type_path", type_path);
    json.insert("login", login);


    QJsonDocument jsonDocument = QJsonDocument::fromVariant(json);
    if ( jsonDocument.isNull() == true)
    {
        cout << " QJsonDocument::fromVariant(json) err";
        return;
    }

    QFile file(path);

    if( false == file.open(QIODevice::WriteOnly) )
    {
        cout << "file open err";
        return;
    }

    //json����д���ļ�
    file.write(jsonDocument.toJson());
    file.close();
}

// ��������Ϣ��д�������ļ�
void Common::writeWebInfo(QString ip, QString port, QString path)
{
    // web_server��Ϣ
    QMap<QString, QVariant> web_server;
    web_server.insert("ip", ip);
    web_server.insert("port", port);

    // type_path��Ϣ
    QMap<QString, QVariant> type_path;
    type_path.insert("path", m_typePath);

    // login��Ϣ
    QString user = getCfgValue("login", "user");
    QString pwd = getCfgValue("login", "pwd");
    QString remember = getCfgValue("login", "remember");


    QMap<QString, QVariant> login;
    login.insert("user", user);
    login.insert("pwd", pwd);
    login.insert("remember", remember);


    // QVariant����Ϊһ����Ϊ�ձ��Qt�������͵�����
    // QVariantΪһ�����ܵ���������--������Ϊ������ͻ���֮������Զ�ת����
    QMap<QString, QVariant> json;
    json.insert("web_server", web_server);
    json.insert("type_path", type_path);
    json.insert("login", login);


    QJsonDocument jsonDocument = QJsonDocument::fromVariant(json);
    if ( jsonDocument.isNull() == true)
    {
        cout << " QJsonDocument::fromVariant(json) err";
        return;
    }

    QFile file(path);

    if( false == file.open(QIODevice::WriteOnly) )
    {
        cout << "file open err";
        return;
    }

    file.write(jsonDocument.toJson());
    file.close();
}

// ��ȡĳ���ļ���md5��
QString Common::getFileMd5(QString filePath)
{
    QFile localFile(filePath);

    if (!localFile.open(QFile::ReadOnly))
    {
        qDebug() << "file open error.";
        return 0;
    }

    QCryptographicHash ch(QCryptographicHash::Md5);

    quint64 totalBytes = 0;
    quint64 bytesWritten = 0;
    quint64 bytesToWrite = 0;
    quint64 loadSize = 1024 * 4;
    QByteArray buf;

    totalBytes = localFile.size();
    bytesToWrite = totalBytes;

    while (1)
    {
        if(bytesToWrite > 0)
        {
            buf = localFile.read(qMin(bytesToWrite, loadSize));
            ch.addData(buf);
            bytesWritten += buf.length();
            bytesToWrite -= buf.length();
            buf.resize(0);
        }
        else
        {
            break;
        }

        if(bytesWritten == totalBytes)
        {
            break;
        }
    }

    localFile.close();
    QByteArray md5 = ch.result();
    return md5.toHex();
}

// ��ĳ���ַ������ܳ�md5��
QString Common::getStrMd5(QString str)
{
    QByteArray array;
    //md5����
    array = QCryptographicHash::hash ( str.toLocal8Bit(), QCryptographicHash::Md5 );

    return array.toHex();
}

// �����ָ���
QString Common::getBoundary()
{
    // �������
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QString tmp;

    // 48~122, '0'~'A'~'z'
    for(int i = 0; i < 16; i++)
    {
        tmp[i] = qrand() % (122-48) + 48;
    }

    return QString("------WebKitFormBoundary%1").arg(tmp);
}

// �õ��������ظ���״̬�룬 ����ֵΪ "000", �� "001"
QString Common::getCode(QByteArray json)
{
    QJsonParseError error;

    // ����Դ����jsonת��ΪJsonDocument
    // ��QByteArray������һ��QJsonDocument�����������ǵĶ�д����
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return "";
        }

        if( doc.isObject() )
        {
            // ȡ���������������
            QJsonObject obj = doc.object();
            return obj.value( "code" ).toString();
        }

    }
    else
    {
        cout << "err = " << error.errorString();
    }

    return "";
}

// �������ݼ�¼�������ļ���user�������û���name���������ļ�, code: �����룬 path: �ļ������·��
void Common::writeRecord(QString user, QString name, QString code, QString path)
{
    qDebug() << "writeRecord";
    // �ļ����֣���½�û�����Ϊ�ļ���
    QString fileName = path + user;
    // ���Ŀ¼�Ƿ���ڣ���������ڣ��򴴽�Ŀ¼
    QDir dir(path);
    cout << "path" << path;
    if(!dir.exists())
    {
        // Ŀ¼������, ����
        if(dir.mkpath(path))
        {
            cout << path << "Ŀ¼�����ɹ�������";
        }
        else
        {
            cout << path << "Ŀ¼����ʧ�ܡ�����";
        }
    }
    cout << "fileName = " << fileName.toUtf8().data();
    QByteArray array;

    QFile file(fileName);

    // ����ļ����ڣ� �ȶ�ȡ�ļ�ԭ��������
    if( true == file.exists() )
    {
        if( false == file.open(QIODevice::ReadOnly) )
        {
            cout << "file.open(QIODevice::ReadOnly) err";
            return;
        }
        //��ȡ�ļ�ԭ��������
        array = file.readAll();
        file.close();
    }

    if( false == file.open(QIODevice::WriteOnly) )
    {
        cout << "file.open(QIODevice::WriteOnly) err";
        return;
    }

    // ��¼������
    // xxx.jpg       2017��2��27��12:04:49       �봫�ɹ�
    // ��ȡ��ǰʱ��
    QDateTime time = QDateTime::currentDateTime();//��ȡϵͳ���ڵ�ʱ��
    QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //������ʾ��ʽ

    /*
       �봫�ļ���
            �ļ��Ѵ��ڣ�{"code":"005"}
            �봫�ɹ���  {"code":"006"}
            �봫ʧ�ܣ�  {"code":"007"}
        �ϴ��ļ���
            �ɹ���{"code":"008"}
            ʧ�ܣ�{"code":"009"}
        �����ļ���
            �ɹ���{"code":"010"}
            ʧ�ܣ�{"code":"011"}
    */
    QString actionStr;
    if(code == "005")
    {
        actionStr = "�ϴ�ʧ�ܣ��ļ��Ѵ���";
    }
    else if(code == "006")
    {
        actionStr = "�봫�ɹ�";
    }
    else if(code == "008")
    {
        actionStr = "�ϴ��ɹ�";
    }
    else if(code == "009")
    {
        actionStr = "�ϴ�ʧ��";
    }
    else if(code == "010")
    {
        actionStr = "���سɹ�";
    }
    else if(code == "011")
    {
        actionStr = "����ʧ��";
    }

    QString str = QString("[%1]\t%2\t[%3]\r\n").arg(name).arg(timeStr).arg(actionStr);
    cout << str.toUtf8().data();

    // toLocal8Bit(), ת��Ϊ�����ַ���
    // ��д������
    file.write( str.toLocal8Bit() );

    if(array.isEmpty() == false)
    {
        // ��дԭ��������
        file.write(array);
    }

    file.close();

}

QNetworkAccessManager *Common::getNetManager()
{
    // �ö���һ��һ��Ӧ�ó�������һ���͹��ˣ�����new���
    return  m_netManager;
}

Common::~Common()
{
}
