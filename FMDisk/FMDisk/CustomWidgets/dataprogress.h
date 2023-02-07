#ifndef DATAPROGRESS_H
#define DATAPROGRESS_H

#include <QWidget>

namespace Ui {
class DataProgress;
}

//�ϴ������ؽ��ȿؼ�
class DataProgress : public QWidget
{
    Q_OBJECT

public:
    explicit DataProgress(QWidget *parent = 0);
    ~DataProgress();

    void setFileName(QString name = "����"); //�����ļ�����
    void setProgress(int value = 0, int max = 100); //���ý������ĵ�ǰֵvalue, ���ֵmax

private:
    Ui::DataProgress *ui;
};

#endif // DATAPROGRESS_H
