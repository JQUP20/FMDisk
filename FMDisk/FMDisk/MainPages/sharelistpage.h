#ifndef SHARELISTPAGE_H
#define SHARELISTPAGE_H

#include <QWidget>

namespace Ui {
class ShareListPage;
}

class ShareListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ShareListPage(QWidget *parent = nullptr);
    ~ShareListPage();

    //==========>��ʾ�����ļ��б�<==============
    void refreshFiles();//��ʾ������ļ��б�

private:
    Ui::ShareListPage *ui;
};

#endif // SHARELISTPAGE_H
