#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>

//// 网络响应异常
const QString c_sNetError = QStringLiteral("network connect error ");
//const QString c_sServerJsonError = QStringLiteral("服务器数据异常 ");

////订座校验返回错误提示
//const QString c_sBookingExpiredErr = QStringLiteral("订座失效 ");
//const QString c_sBookingCodeErr = QStringLiteral("验证码错误 ");
//const QString c_sBookingUnlockedErr = QStringLiteral("该电脑已被解锁 ");

//服务类型地址
const QString c_sFormalServerUrl = "https://192.168.0.188:80";
const QString c_sTestServerUrl = "http://192.168.0.188:80";
const QString c_sLocalServerUrl = "http://192.168.0.188:80";


//登录接口
const QString c_sHttpOrderLoginAction = "/login";
const QString c_sHttpOrderRegisterAction = "/reg";
const QString c_sHttpOrderMd5CheckAction = "/md5";
const QString c_sHttpOrderUploadAction = "/upload";
const QString c_sHttpOrderRefreshFilesAction = "/myfiles?cmd=count";

const QString c_sHttpOrderGetUserFilesListInNormal = "/myfiles?cmd=normal";
const QString c_sHttpOrderGetUserFilesListInPvasc = "/myfiles?cmd=pvasc";
const QString c_sHttpOrderGetUserFilesListInPvdesc = "/myfiles?cmd=pvdesc";

#endif
