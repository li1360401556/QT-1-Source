#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QTimer>
#include<QApplication>
#include<QScreen>
#include<QRandomGenerator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/res/icon.png"));
    setWindowTitle(" ");
    //创建对象
    this->m_icon=new icon;
    //将对象显示到窗口
    this->m_icon->setParent(this);
    //设置窗口大小
    this->setFixedHeight(m_icon->m_icon_pix.height());
    this->setFixedWidth(m_icon->m_icon_pix.width());
    //启动定时器
    this->m_icon->running();

    //监听自定义信号
    connect(this->m_icon,&icon::changePixmap,[=](){
        //手动调用绘图事件
        update();

    });
    //监听鼠标移动信号
    connect(this->m_icon,&icon::moving,[=](QPoint point){
        this->move(point);
        m_auto_pos=point;//鼠标拖拽更新位置信息
    });
    //创建自动移动定时器对象
    this->timer=new QTimer(this);
    //启动定时器
    this->timer->start(30);
    //监听定时器
    connect(this->timer,&QTimer::timeout,[=](){
        //如果鼠标按下状态为假,才自动移动
        if(this->m_icon->mousedown!=true)
        {  m_auto_pos.setX(this->m_auto_pos.x()+5);}


        //QGuiApplication::primaryScreen()->size().width()获取屏幕信息
        if(this->m_auto_pos.x()> QGuiApplication::primaryScreen()->size().width())
        {
            m_auto_pos.setX(-this->m_icon->width());
            m_auto_pos.setY(QRandomGenerator::global()->bounded(1,QGuiApplication::primaryScreen()->size().height()));

        }

        //重新同步
        this->move(this->m_auto_pos);
    });
    //去掉标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置透明窗体 120属性
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口顶层
    this->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint);
    //设置起始Y坐标           随机数生成位置QRandomGenerator::global()->bounded
    this->m_auto_pos.setY(QRandomGenerator::global()->bounded(1,QGuiApplication::primaryScreen()->size().height()));




}





Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->m_icon->m_icon_pix);
}

