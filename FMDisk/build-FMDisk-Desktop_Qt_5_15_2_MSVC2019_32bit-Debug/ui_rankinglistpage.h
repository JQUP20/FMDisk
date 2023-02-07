/********************************************************************************
** Form generated from reading UI file 'rankinglistpage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANKINGLISTPAGE_H
#define UI_RANKINGLISTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RankingListPage
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *RankingListPage)
    {
        if (RankingListPage->objectName().isEmpty())
            RankingListPage->setObjectName(QString::fromUtf8("RankingListPage"));
        RankingListPage->resize(511, 424);
        tableWidget = new QTableWidget(RankingListPage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 493, 402));
        tableWidget->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\226\260\345\256\213\344\275\223\";"));

        retranslateUi(RankingListPage);

        QMetaObject::connectSlotsByName(RankingListPage);
    } // setupUi

    void retranslateUi(QWidget *RankingListPage)
    {
        RankingListPage->setWindowTitle(QCoreApplication::translate("RankingListPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RankingListPage: public Ui_RankingListPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANKINGLISTPAGE_H
