#ifndef RANKINGLISTPAGE_H
#define RANKINGLISTPAGE_H

#include <QWidget>

namespace Ui {
class RankingListPage;
}

class RankingListPage : public QWidget
{
    Q_OBJECT

public:
    explicit RankingListPage(QWidget *parent = nullptr);
    ~RankingListPage();

    // ==========>显示共享文件列表<==============
    void refreshFiles();                                // 显示共享的文件列表

private:
    Ui::RankingListPage *ui;
};

#endif // RANKINGLISTPAGE_H
