/********************************************************************************
** Form generated from reading UI file 'filelistpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILELISTPAGE_H
#define UI_FILELISTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileListPage
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *FileListPage)
    {
        if (FileListPage->objectName().isEmpty())
            FileListPage->setObjectName(QString::fromUtf8("FileListPage"));
        FileListPage->resize(739, 541);
        listWidget = new QListWidget(FileListPage);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 721, 521));

        retranslateUi(FileListPage);

        QMetaObject::connectSlotsByName(FileListPage);
    } // setupUi

    void retranslateUi(QWidget *FileListPage)
    {
        FileListPage->setWindowTitle(QCoreApplication::translate("FileListPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileListPage: public Ui_FileListPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILELISTPAGE_H
