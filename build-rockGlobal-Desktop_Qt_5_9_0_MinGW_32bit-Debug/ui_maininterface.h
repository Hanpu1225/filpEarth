/********************************************************************************
** Form generated from reading UI file 'maininterface.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAININTERFACE_H
#define UI_MAININTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainInterface
{
public:
    QAction *actionquit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menukais;

    void setupUi(QMainWindow *MainInterface)
    {
        if (MainInterface->objectName().isEmpty())
            MainInterface->setObjectName(QStringLiteral("MainInterface"));
        MainInterface->resize(400, 300);
        actionquit = new QAction(MainInterface);
        actionquit->setObjectName(QStringLiteral("actionquit"));
        centralWidget = new QWidget(MainInterface);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainInterface->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainInterface);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menukais = new QMenu(menuBar);
        menukais->setObjectName(QStringLiteral("menukais"));
        MainInterface->setMenuBar(menuBar);

        menuBar->addAction(menukais->menuAction());
        menukais->addAction(actionquit);

        retranslateUi(MainInterface);

        QMetaObject::connectSlotsByName(MainInterface);
    } // setupUi

    void retranslateUi(QMainWindow *MainInterface)
    {
        MainInterface->setWindowTitle(QApplication::translate("MainInterface", "MainInterface", Q_NULLPTR));
        actionquit->setText(QApplication::translate("MainInterface", "\351\200\200\345\207\272", Q_NULLPTR));
        menukais->setTitle(QApplication::translate("MainInterface", "\345\274\200\345\247\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainInterface: public Ui_MainInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAININTERFACE_H
