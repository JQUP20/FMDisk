/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "CustomWidgets/buttongroup.h"
#include "MainPages/filelistpage.h"
#include "MainPages/rankinglistpage.h"
#include "MainPages/sharelistpage.h"
#include "MainPages/transferpage.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    ButtonGroup *btn_group;
    QStackedWidget *stackedWidget;
    FileListPage *myfiles_page;
    ShareListPage *sharefile_page;
    RankingListPage *ranking_page;
    TransferPage *transfer_page;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(755, 621);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_group = new ButtonGroup(centralwidget);
        btn_group->setObjectName(QString::fromUtf8("btn_group"));
        btn_group->setGeometry(QRect(0, 0, 755, 91));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_group->sizePolicy().hasHeightForWidth());
        btn_group->setSizePolicy(sizePolicy);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 90, 755, 531));
        myfiles_page = new FileListPage();
        myfiles_page->setObjectName(QString::fromUtf8("myfiles_page"));
        stackedWidget->addWidget(myfiles_page);
        sharefile_page = new ShareListPage();
        sharefile_page->setObjectName(QString::fromUtf8("sharefile_page"));
        stackedWidget->addWidget(sharefile_page);
        ranking_page = new RankingListPage();
        ranking_page->setObjectName(QString::fromUtf8("ranking_page"));
        stackedWidget->addWidget(ranking_page);
        transfer_page = new TransferPage();
        transfer_page->setObjectName(QString::fromUtf8("transfer_page"));
        stackedWidget->addWidget(transfer_page);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
