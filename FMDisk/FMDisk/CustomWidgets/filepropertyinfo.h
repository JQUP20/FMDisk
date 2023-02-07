#ifndef FILEPROPERTYINFO_H
#define FILEPROPERTYINFO_H

#include <QDialog>
#include "Utils/Common.h" //FileInfo

namespace Ui {
class FilePropertyInfo;
}

class FilePropertyInfo : public QDialog
{
    Q_OBJECT

public:
    explicit FilePropertyInfo(QWidget *parent = 0);
    ~FilePropertyInfo();

    //…Ë÷√ƒ⁄»›
    void setInfo(FileInfo *info);

private:
    Ui::FilePropertyInfo *ui;
};

#endif // FILEPROPERTYINFO_H
