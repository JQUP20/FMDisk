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

    // ==========>��ʾ�����ļ��б�<==============
    void refreshFiles();                                // ��ʾ������ļ��б�

private:
    Ui::RankingListPage *ui;
};

#endif // RANKINGLISTPAGE_H
