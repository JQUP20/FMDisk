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

    //==========>显示共享文件列表<==============
    void refreshFiles();//显示共享的文件列表

private:
    Ui::ShareListPage *ui;
};

#endif // SHARELISTPAGE_H
