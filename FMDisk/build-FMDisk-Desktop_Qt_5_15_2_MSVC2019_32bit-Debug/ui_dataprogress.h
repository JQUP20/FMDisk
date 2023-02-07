/********************************************************************************
** Form generated from reading UI file 'dataprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAPROGRESS_H
#define UI_DATAPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataProgress
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *DataProgress)
    {
        if (DataProgress->objectName().isEmpty())
            DataProgress->setObjectName(QString::fromUtf8("DataProgress"));
        DataProgress->resize(773, 41);
        progressBar = new QProgressBar(DataProgress);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(60, 10, 708, 23));
        progressBar->setValue(0);
        label = new QLabel(DataProgress);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 10, 43, 23));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(16777215, 16777215));

        retranslateUi(DataProgress);

        QMetaObject::connectSlotsByName(DataProgress);
    } // setupUi

    void retranslateUi(QWidget *DataProgress)
    {
        DataProgress->setWindowTitle(QCoreApplication::translate("DataProgress", "Form", nullptr));
        label->setText(QCoreApplication::translate("DataProgress", "\346\226\207\344\273\2661\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataProgress: public Ui_DataProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAPROGRESS_H
