#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QMenu>

class CustomMenu : public QMenu
{
    Q_OBJECT
public:
    explicit CustomMenu(QWidget *parent = 0);
};

#endif // CUSTOMMENU_H
