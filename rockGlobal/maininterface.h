#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QMainWindow>
#include"chooselevelscene.h"


namespace Ui {
class MainInterface;
}

class MainInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainInterface(QWidget *parent = 0);
    ~MainInterface();

    //重写paintEvent事件
    void paintEvent(QPaintEvent*);

    ChooseLevelScene* chooseScene = NULL;

private:
    Ui::MainInterface *ui;
};

#endif // MAININTERFACE_H
