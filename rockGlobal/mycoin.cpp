#include "mycoin.h"
#include<QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
   QPixmap pix;
   bool ret = pix.load(btnImg);
   if(!ret)
   {
       QString str = QString("图片 %1 加载失败").arg(btnImg);
       qDebug()<<"str";
       return;
   }
   this->setFixedSize(pix.width(),pix.height());
   this->setStyleSheet("QPushButton{border:0px;}");
   this->setIcon(pix);
   this->setIconSize(QSize(pix.width(),pix.height()));

   //初始化定时器对象
   timer1 = new QTimer(this);
   timer2 = new QTimer(this);

   //监听正面->反面(金币到银币)的信号，并且翻转金币
   connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1").arg(this->min++);
       pix.load(str);

       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       //若翻完了，将min重置
       if(this->min>this->max)
       {
           this->min = 1;
           isAnimation = false;
           timer1->stop();
       }
   });

   //监听正面->反面(银币到金币)的信号
   connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1").arg(this->max--);
       pix.load(str);

       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       //若翻完了，将min重置
       if(this->max < this->min)
       {
           this->max = 8;
           isAnimation = false;
           timer2->stop();
       }
   });
}
//改变正反面标志的方法
void MyCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);//金币到银币
        isAnimation = true;//开始做动画
        this->flag = false;
    }
    else
    {

        timer2->start(30);//银币到金币
        isAnimation = false;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin==true)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

