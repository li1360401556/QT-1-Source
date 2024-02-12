#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"icon.h"
#include<QPainter>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    //图片移动的指针
    icon*m_icon;

    Widget(QWidget *parent = nullptr);
    ~Widget();
    //重写绘图事件
    void paintEvent(QPaintEvent*);
    //记录自动移动的位置
    QPoint m_auto_pos;
    //自动移动定时器
    QTimer *timer;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
