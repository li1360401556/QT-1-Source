#ifndef ICON_H
#define ICON_H

#include <QWidget>
#include<qpixmap.h>
#include<QTimer>
#include<QMouseEvent>
#include<QMenu>

class icon : public QWidget
{
    Q_OBJECT
public:
    explicit icon(QWidget *parent = nullptr);
    //显示图片
    QPixmap m_icon_pix;
    //最小值下标
    int min=1;
    //最大值下标
    int max=11;
    //定时器
    QTimer*timer;
    //启动定时器
    void running();
    //记录分量坐标
    QPoint m_pos;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent*);
    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent*);
    //设置鼠标按下状态
    bool mousedown=false;
    //重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent*);
    //右键退出菜单
    QMenu*m_menu;





signals:
    //自定义信号 代表正在切换图片
    void changePixmap();
    //自定义信号 代表正在移动图片
    void moving(QPoint point);


};

#endif // ICON_H
