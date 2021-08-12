#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QPainter>
#include<mycoin.h>


class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex;//内部成员属性记录所选关卡

    void paintEvent(QPaintEvent *);


    int gameArray[4][4];//二维数组维护每个关卡的具体数据

    MyCoin *coinBtn[4][4];

    bool isWin;//是否胜利的标志
signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
