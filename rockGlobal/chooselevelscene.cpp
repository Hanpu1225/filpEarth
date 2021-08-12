#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include<QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{

    //配置选择关卡的场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单栏
   QMenu * startMenu = bar->addMenu("开始");
   //创建退出菜单项
   QAction * quitAction = startMenu->addAction("退出");

   //点击退出 实现退出游戏
   connect(quitAction,&QAction::triggered,[=](){
       this->close();
   });

   //选择关卡音效 返回音效
   QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",this);
   QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);

   //返回按钮
   MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
   backBtn->setParent(this);
   backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

   connect(backBtn,&MyPushButton::clicked,[=](){
       //qDebug()<<"点击了返回按钮";
       //告诉返回按钮， 我返回了 主场景监听
       backSound->play();

       //做延时返回
       QTimer::singleShot(500,this,[=](){
           emit this->chooseSceneBack();
       });

   });


   //创建选择关卡的按钮
   for(int i=0;i<20;i++)
   {
       MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
       menuBtn->setParent(this);
       menuBtn->move(25 + (i%4)*70 , 130+ (i/4)*70);

       //监听每个按钮的点击事件
       connect(menuBtn,&MyPushButton::clicked,[=](){

           chooseSound->play();

           QString str = QString("您选择的是第 %1 关 ").arg(i+1);
           qDebug()<<str;

           //进入游戏场景对象指针
           this->hide();//将游戏选关隐藏掉
           play = new PlayScene(i+1);

           //设置游戏场景的初始位置
           play->setGeometry(this->geometry());


           play->show();//显示游戏场景



           connect(play,&PlayScene::chooseSceneBack,[=](){
               this->setGeometry(play->geometry());
               this->show();
               delete play;
               play = NULL;
           });

       });

       //在按钮上 设置一个QLabel来显示关卡数
       QLabel * label = new QLabel;
       label->setParent(this);

       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i+1));
       label->move(25 + (i%4)*70 , 130+ (i/4)*70);

       //设置label上的对其齐方式
       label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
       //鼠标穿透事件
       label->setAttribute(Qt::WA_TransparentForMouseEvents);
   }


}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画背景图片
    pix.load((":/res/Title.png"));
    //pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//将照片进行缩放
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
