#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QWidget>
#include <QString>
#include <QListWidgetItem>
#include <QNetworkAccessManager>

#define cout qDebug() << "[ " << __FILE__ << ":"  << __LINE__ << " ] "

// �ļ�·��
const QString CONFFILE      = "conf/cfg.json";     // �����ļ�
const QString  RECORDDIR    = "conf/record/";      // �û��ļ��ϴ����ؼ�¼
const QString  FILETYPEDIR  = "conf/fileType";     // ����ļ�����ͼƬĿ¼

// ������ʽ
const QString USER_REG      = "^[a-zA-Z\\d_@#-\\*]\\{3,16\\}$";
const QString PASSWD_REG    = "^[a-zA-Z\\d_@#-\\*]\\{6,18\\}$";
const QString PHONE_REG     = "1\\d\\{10\\}";
const QString EMAIL_REG     = "^[a-zA-Z\\d\\._-]\\+@[a-zA-Z\\d_\\.-]\\+(\\.[a-zA-Z0-9_-]\\+)+$";
const QString IP_REG        = "((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)";
const QString PORT_REG      = "^[1-9]$|(^[1-9][0-9]$)|(^[1-9][0-9][0-9]$)|(^[1-9][0-9][0-9][0-9]$)|(^[1-6][0-5][0-5][0-3][0-5]$)";

// �ļ���Ϣ
struct FileInfo
{
    QString md5;            // �ļ�md5��
    QString filename;       // �ļ�����
    QString user;           // �û�
    QString time;           // �ϴ�ʱ��
    QString url;            // url
    QString type;           // �ļ�����
    qint64 size;            // �ļ���С
    int shareStatus;        // �Ƿ���, 1���� 0������
    int pv;                 // ������
    QListWidgetItem *item;  // list widget ��item
};
// ����״̬
enum TransferStatus{Download, Uplaod, Recod};


class Common : public QObject
{
    Q_OBJECT

public:
    static Common* getInstance(void);

    Common(QObject* parent = 0);
    ~Common();

    // ��������Ļ������ʾ
    void moveToCenter(QWidget *tmp);

    // �������ļ��еõ����Ӧ�Ĳ���
    QString getCfgValue(QString title, QString key, QString path = CONFFILE);

    // ͨ����ȡ�ļ�, �õ��ļ�����, �����typeList
    void getFileTypeList();

    // �õ��ļ���׺������Ϊ�ļ����ͣ������ڲ��ж��Ƿ��д����ͣ�����У�ʹ�ô����ͣ�û�У�ʹ��other.png
    QString getFileType(QString type);

    // ��¼��Ϣ��д�������ļ�
    void writeLoginInfo(QString user, QString pwd, bool isRemeber, QString path = CONFFILE);

    // ��������Ϣ��д�������ļ�
    void writeWebInfo(QString ip, QString port, QString path=CONFFILE);

    // ��ȡĳ���ļ���md5��
    QString getFileMd5(QString filePath);

    // ��ĳ���ַ������ܳ�md5��
    QString getStrMd5(QString str = "");

    // �����ָ���
    QString getBoundary();

    // �õ��������ظ���״̬�룬 ����ֵΪ "000", �� "001"
    QString getCode(QByteArray json);

    // �������ݼ�¼�������ļ���user�������û���name���������ļ�, code: �����룬 path: �ļ������·��
    void writeRecord(QString user, QString name, QString code, QString path = RECORDDIR);

    // �õ�httpͨ�������
    static QNetworkAccessManager* getNetManager();
public:
    static QStringList  m_typeList;

private:
    // �ļ�����·��
    static QString      m_typePath;
    // ��Ҫ�����ļ����͵ĺ�׺
    // http��
    static QNetworkAccessManager *m_netManager;
    static Common *instance;

};

#endif // COMMON_H

