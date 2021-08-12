#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>


class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);//参数代表传入的路径

    int posX;//x的坐标位置
    int posY;//y的坐标位置
    bool flag;//正反面标志


    //改变标志的方法
    void changeFlag();
    QTimer *timer1;//正面——>反面的定时器
    QTimer *timer2;//反面->正面的定时器
    int min = 1;
    int max = 8;

    bool isAnimation = false;//执行动画的标志

    //重写 按下
    void mousePressEvent(QMouseEvent *e);

   //是否胜利的标志
   bool isWin = false;
signals:

public slots:
};

#endif // MYCOIN_H
