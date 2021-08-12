#include "maininterface.h"
#include "ui_maininterface.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>


MainInterface::MainInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    //配置主要场景

    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻转地球主场景");

    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);
    //startSound->setLoops(-1);//音效无效循环
    startSound->play();


    //开始按钮
    MyPushButton *startButton = new MyPushButton(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-startButton->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){

        this->setGeometry(chooseScene->geometry());

        chooseScene->hide();
        this->show();//重新显示主场景
    });

    connect(startButton,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了开始";
        //弹起的特效

        //播放音效
        startSound->play();

        startButton->zoom1();
        startButton->zoom2();

        //延时0.5s以后进入选择关卡场景
        QTimer::singleShot(500,this,[=](){

            //设置chooseScene场景的位置
            chooseScene->setGeometry(this->geometry());

            this->hide();
            //进入选择场景
            chooseScene->show();   
        });


    });

}

void MainInterface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //加载背景照片
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load((":/res/Title.png"));
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);//将照片进行缩放
    painter.drawPixmap(10,30,pix);

}

MainInterface::~MainInterface()
{
    delete ui;
}


