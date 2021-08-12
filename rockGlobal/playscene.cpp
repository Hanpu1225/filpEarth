#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include"QTimer"
#include<QLabel>
#include<QFont>
#include"mycoin.h"
#include"dataconfig.h"
#include"QPropertyAnimation"
#include<QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第 %i 关 ").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;


    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻转地球场景");

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

   //添加音效资源
     //翻金币音效
     QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
     //胜利按钮音效
     QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);
     //返回按钮音效
     QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

   //返回按钮
   MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
   backBtn->setParent(this);
   backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

   connect(backBtn,&MyPushButton::clicked,[=](){
       qDebug()<<"游戏翻金币点击了返回按钮";
       //告诉返回按钮， 我返回了 主场景监听
       //做延时返回

      backSound->play();
      QTimer::singleShot(500,this,[=](){
           emit this->chooseSceneBack();
       });

   });
   //显示关卡数
   QLabel *label = new QLabel;
   label->setParent(this);
   QFont font;
   font.setPointSize(20);
   QString str1 = QString("Level:%1").arg(this->levelIndex);
   //将字体设置到标签控件中
   font.setFamily("华文新魏");
   label->setFont(font);
   label->setText(str1);
   label->setGeometry(30,this->height()-50,120,50);


   //初始化每个关卡的二维数组
   dataConfig config;
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
       }
   }

   //显示胜利图片
   QLabel* winLabel = new QLabel;
   QPixmap tmpPix;
   tmpPix.load(":/res/LevelCompletedDialogBg.png");
   winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
   winLabel->setPixmap(tmpPix);
   winLabel->setParent(this);
   winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());



   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           QPixmap pix = QPixmap(":/res/BoardNode.png");
           QLabel *label = new QLabel;
           label->setGeometry(0,0,pix.width(),pix.height());
           label->setPixmap(pix);
           label->setParent(this);
           label->move(57+i*50,200+j*50);

           QString str;
           if(this->gameArray[i][j]==1)
           {
               str = ":/res/Coin0001.png";
           }
           else
           {
                str = ":/res/Coin0008.png";
           }

           MyCoin *coin = new MyCoin(str);
           coin->setParent(this);
           coin->move(59+i*50,204+j*50);

           coin->posX = i;
           coin->posY = j;
           coin->flag = this->gameArray[i][j];//正面 反面


           //将金币放在金币的二维数组中
           coinBtn[i][j] = coin;


           //点击金币进行翻转
           connect(coin,&MyCoin::clicked,[=](){

               flipSound->play();

               //点击按钮，将所有的按钮都禁用
               for(int i=0;i<4;i++)
               {
                   for(int j=0;j<4;j++)
                   {
                       this->coinBtn[i][j]->isWin = true;
                   }
               }

               coin->changeFlag();
               this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

               //延时翻转
               QTimer::singleShot(300,this,[=](){
                   if(coin->posX+1<=3)//周围右侧翻转金币
                   {
                       coinBtn[coin->posX+1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                   }
                   if(coin->posX-1>=0)//周围左侧翻转金币
                   {
                       coinBtn[coin->posX-1][coin->posY]->changeFlag();
                       this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                   }

                   if(coin->posY+1<=3)//周围上侧翻转金币
                   {
                       coinBtn[coin->posX][coin->posY+1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                   }
                   if(coin->posY-1>=0)//周围下侧翻转金币
                   {
                       coinBtn[coin->posX][coin->posY-1]->changeFlag();
                       this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                   }

                   //点击按钮，将所有的按钮都解除禁用
                   for(int i=0;i<4;i++)
                   {
                       for(int j=0;j<4;j++)
                       {
                           this->coinBtn[i][j]->isWin = false;
                       }
                   }

                   //判断是否胜利
                   this->isWin = true;
                   for(int i=0;i< 4;i++)
                   {
                       for(int j=0;j<4;j++)
                       {
                           if(coinBtn[i][j]->flag==false)
                           {
                               this->isWin = false;
                           }

                       }
                   }

                   if(this->isWin)
                   {
                       winSound->play();

                       qDebug()<<"游戏胜利";
                       //将所有胜利的标志改为true 若再次点击就直接return
                       for(int i=0;i< 4;i++)
                       {
                           for(int j=0;j<4;j++)
                           {
                               coinBtn[i][j]->isWin=true;
                           }
                       }
                       //将胜利的图片一下来
                       QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                       //设置时间间隔
                       animation->setDuration(1000);

                       animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));

                       animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));

                       animation->setEasingCurve(QEasingCurve::OutBounce);

                       animation->start();
                   }
               });


           });



       }
   }

}


void PlayScene::paintEvent(QPaintEvent *)
{
      //画背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load((":/res/Title.png"));
    //pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//将照片进行缩放
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}


