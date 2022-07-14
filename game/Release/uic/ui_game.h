/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *gameClass)
    {
        if (gameClass->objectName().isEmpty())
            gameClass->setObjectName(QString::fromUtf8("gameClass"));
        gameClass->resize(600, 400);
        menuBar = new QMenuBar(gameClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        gameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(gameClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        gameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(gameClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(gameClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        gameClass->setStatusBar(statusBar);

        retranslateUi(gameClass);

        QMetaObject::connectSlotsByName(gameClass);
    } // setupUi

    void retranslateUi(QMainWindow *gameClass)
    {
        gameClass->setWindowTitle(QCoreApplication::translate("gameClass", "game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameClass: public Ui_gameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
