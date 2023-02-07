/********************************************************************************
** Form generated from reading UI file 'sharelistpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARELISTPAGE_H
#define UI_SHARELISTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShareListPage
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *ShareListPage)
    {
        if (ShareListPage->objectName().isEmpty())
            ShareListPage->setObjectName(QString::fromUtf8("ShareListPage"));
        ShareListPage->resize(400, 300);
        listWidget = new QListWidget(ShareListPage);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 382, 282));

        retranslateUi(ShareListPage);

        QMetaObject::connectSlotsByName(ShareListPage);
    } // setupUi

    void retranslateUi(QWidget *ShareListPage)
    {
        ShareListPage->setWindowTitle(QCoreApplication::translate("ShareListPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShareListPage: public Ui_ShareListPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARELISTPAGE_H
