#include "icon.h"
#include<qDebug>
icon::icon(QWidget *parent)
    : QWidget{parent}
{
//加载所有图片
    for(int i=1;i<12;i++)
{
    QString str=QString(":/res/F_%1").arg(i);
        this->m_icon_pix.load(str);

    //设置图片尺寸
        this->setFixedSize(this->m_icon_pix.width(),this->m_icon_pix.height());
    }
    //new一个timer
    this->timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        QString str=QString(":/res/F_%1").arg(min++);
        if(this->min>this->max)
        {
            min=1;
        }
        this->m_icon_pix.load(str);
        //抛出自定义信号
        emit changePixmap();

    });
    //new一个菜单
    this->m_menu=new QMenu(this);
    //连接菜单项
    connect(this->m_menu->addAction("退出"),&QAction::triggered,[=](){
        exit(0);
    });

}

void icon::running()
{
    //启动定时器
    this->timer->start(50);

}

void icon::mousePressEvent(QMouseEvent *e)
{

    //鼠标按下记录分量
    //((QWidget*)this->parent())->frameGeometry().topLeft()获取当前窗口左上角到屏幕左上角的坐标
    this->m_pos =( e->globalPosition()-((QWidget*)this->parent())->frameGeometry().topLeft()).toPoint();
    //point=pointf.toPoint(); 将浮点型pointf转换为整数型point
    //鼠标按下状态为真
    this->mousedown=true;

    //如果鼠标右键弹出菜单
    if(e->button()==Qt::RightButton)
    {
        //弹出菜单 QCursor::pos()鼠标当前位置
        this->m_menu->popup(QCursor::pos());
    }
    //如果退出菜单通过别的方式消失的，图片应该继续向前飞
    //QMenu::aboutToHide菜单消失发送的信号
    connect(this->m_menu,&QMenu::aboutToHide,[=](){
        this->mousedown=false;
    });
}

void icon::mouseMoveEvent(QMouseEvent *e)
{
    //在移动过程中反向获取到窗口最终移动位置
    emit moving((e->globalPosition()-this->m_pos).toPoint());
}

void icon::mouseReleaseEvent(QMouseEvent *)
{
    //设置鼠标按下状态
    this->mousedown=false;
}

