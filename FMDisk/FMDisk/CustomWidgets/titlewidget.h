#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();

    void setParent(QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void showSetWidget();
    void closeWindow();

private:
    Ui::TitleWidget *ui;

    QPoint m_pos;        // ������갴��ʱ������
    QWidget *m_parent;  // ������ָ��
};

#endif // TITLEWIDGET_H
