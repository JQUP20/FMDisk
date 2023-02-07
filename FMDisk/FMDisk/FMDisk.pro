QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += PLATFORM_TYPE

#CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomControls/ipaddredit.cpp \
    CustomWidgets/buttongroup.cpp \
    CustomWidgets/custommenu.cpp \
    CustomWidgets/dataprogress.cpp \
    CustomWidgets/filepropertyinfo.cpp \
    CustomWidgets/titlewidget.cpp \
    CustomWidgets/topbarwidget.cpp \
    Log/logging.cpp \
    LoginWindow/login.cpp \
    LoginWindow/logininfoinstance.cpp \
    LoginWindow/register.cpp \
    MainPages/downloadlayout.cpp \
    MainPages/downloadtask.cpp \
    MainPages/filelistpage.cpp \
    MainPages/rankinglistpage.cpp \
    MainPages/sharelistpage.cpp \
    MainPages/transferpage.cpp \
    MainPages/uploadlayout.cpp \
    MainPages/uploadtask.cpp \
    Network/httpagent.cpp \
    Network/httpclient.cpp \
    Network/httpgetuserfileslist.cpp \
    Network/httplogin.cpp \
    Network/httprefreshfiles.cpp \
    Network/httpregister.cpp \
    Network/httpsignal.cpp \
    Network/httpupload.cpp \
    Network/httpuploadinreal.cpp \
    Network/ihttpreqres.cpp \
    Utils/appconfig.cpp \
    Utils/appconfigini.cpp \
    Utils/common.cpp \
    Utils/commonfun.cpp \
    Utils/datapathmanager.cpp \
    Utils/des.cpp \
    Utils/threadmanager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomControls/ipaddredit.h \
    CustomWidgets/buttongroup.h \
    CustomWidgets/custommenu.h \
    CustomWidgets/dataprogress.h \
    CustomWidgets/filepropertyinfo.h \
    CustomWidgets/titlewidget.h \
    CustomWidgets/topbarwidget.h \
    Log/logging.h \
    LoginWindow/login.h \
    LoginWindow/logininfoinstance.h \
    LoginWindow/register.h \
    MainPages/downloadlayout.h \
    MainPages/downloadtask.h \
    MainPages/filelistpage.h \
    MainPages/rankinglistpage.h \
    MainPages/sharelistpage.h \
    MainPages/transferpage.h \
    MainPages/uploadlayout.h \
    MainPages/uploadtask.h \
    Network/httpagent.h \
    Network/httpclient.h \
    Network/httpgetuserfileslist.h \
    Network/httplogin.h \
    Network/httprefreshfiles.h \
    Network/httpregister.h \
    Network/httpsignal.h \
    Network/httpupload.h \
    Network/httpuploadinreal.h \
    Network/ihttpreqres.h \
    Utils/Common.h \
    Utils/EnumData.h \
    Utils/HttpStructData.h \
    Utils/appconfig.h \
    Utils/appconfigini.h \
    Utils/commonfun.h \
    Utils/constData.h \
    Utils/datapathmanager.h \
    Utils/des.h \
    Utils/dump.h \
    Utils/threadmanager.h \
    mainwindow.h

FORMS += \
    CustomWidgets/buttongroup.ui \
    CustomWidgets/dataprogress.ui \
    CustomWidgets/filepropertyinfo.ui \
    CustomWidgets/titlewidget.ui \
    LoginWindow/login.ui \
    MainPages/filelistpage.ui \
    MainPages/rankinglistpage.ui \
    MainPages/sharelistpage.ui \
    MainPages/transferpage.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

INCLUDEPATH += $$PWD\include\
