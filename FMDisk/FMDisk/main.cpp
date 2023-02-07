#include "Log/logging.h"
#include "Utils/dump.h"

#include "LoginWindow/login.h""

#include <QApplication>
#include <QDateTime>
#include <QTextCodec>
#include <QFont>
#include <windows.h>

int main(int argc, char *argv[])
{

    EnableAutoDump();

    QApplication a(argc, argv);

    //…Ë÷√◊÷ÃÂ
    QFont font;
    font.setFamily(QString::fromLocal8Bit("Œ¢»Ì—≈∫⁄"));
    a.setFont(font);

    //…Ë÷√±‡¬Î∏Ò Ω
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);


    QDir dir;
    QString initFilePath = QDir::cleanPath(QDir::homePath() + "/AppData/Local/FMDisk/");
    if (!dir.exists(initFilePath + "/log"))
    {
        if (!dir.mkpath(initFilePath + "/log"))
        {
            return -1;
        }
    }

    QString log_name = QString("/log_%1.txt").arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QString log_path = initFilePath + "/log" + log_name;
    std::string logpath = log_path.toLocal8Bit().data();
    Log::Initialise(logpath);
    Log::SetThreshold(Log::LOG_TYPE_DEBUG);

    dir.mkdir(initFilePath + "/Dump");

    Login w;
    w.show();
    return a.exec();
}
