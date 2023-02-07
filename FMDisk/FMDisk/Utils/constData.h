#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>

//// ������Ӧ�쳣
const QString c_sNetError = QStringLiteral("network connect error ");
//const QString c_sServerJsonError = QStringLiteral("�����������쳣 ");

////����У�鷵�ش�����ʾ
//const QString c_sBookingExpiredErr = QStringLiteral("����ʧЧ ");
//const QString c_sBookingCodeErr = QStringLiteral("��֤����� ");
//const QString c_sBookingUnlockedErr = QStringLiteral("�õ����ѱ����� ");

//�������͵�ַ
const QString c_sFormalServerUrl = "https://192.168.0.188:80";
const QString c_sTestServerUrl = "http://192.168.0.188:80";
const QString c_sLocalServerUrl = "http://192.168.0.188:80";


//��¼�ӿ�
const QString c_sHttpOrderLoginAction = "/login";
const QString c_sHttpOrderRegisterAction = "/reg";
const QString c_sHttpOrderMd5CheckAction = "/md5";
const QString c_sHttpOrderUploadAction = "/upload";
const QString c_sHttpOrderRefreshFilesAction = "/myfiles?cmd=count";

const QString c_sHttpOrderGetUserFilesListInNormal = "/myfiles?cmd=normal";
const QString c_sHttpOrderGetUserFilesListInPvasc = "/myfiles?cmd=pvasc";
const QString c_sHttpOrderGetUserFilesListInPvdesc = "/myfiles?cmd=pvdesc";

#endif
