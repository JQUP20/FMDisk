#ifndef TRANSFERPAGE_H
#define TRANSFERPAGE_H

#include <QWidget>

namespace Ui {
class TransferPage;
}

class TransferPage : public QWidget
{
    Q_OBJECT

public:
    explicit TransferPage(QWidget *parent = nullptr);
    ~TransferPage();

private:
    Ui::TransferPage *ui;
};

#endif // TRANSFERPAGE_H
