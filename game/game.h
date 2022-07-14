#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_game.h"
#include <QLineEdit>
#include <QMainWindow>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <typeinfo>
#include <iostream>
#include <sstream>
#include <vector>
#include <QDebug>
#include "QFileDialog"
#include <QtMath>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QTimer>
#include<QEventLoop>
#include<QTime>
#include<conio.h>


#define MAXSIZE 50
#define MAXSIZES 2500
static const int ROUTE = 0;
static const int WALL = 1;
using namespace std;




class game : public QMainWindow
{
    Q_OBJECT

public:
    
    QPushButton *inputC = NULL;
    game(QWidget *parent = Q_NULLPTR);
   
    void setLengthAndWidth();        //迷宫长宽设置
    void create1();                    //迷宫给定生成
    void create2();                     //随即迷宫生成
    void getFromFile();                //从文件中读取迷宫数组
    void Sleep(int msec);                //延时函数
    void CharacterMove();               //控制人物移动

    ~game() {
        delete inputC;

        for (int i = 0; i < row * col; i++) {
            delete input[i];
        }
    }
    

    
    
private slots:
    void on_pushButton_clicked(); //给定迷宫
    void on_pushButton_2_clicked();//随机迷宫 
    void on_pushButton_3_clicked();//深度优先
    void on_pushButton_4_clicked();//广度优先
    void on_pushButton_5_clicked();  //结束程序
    void on_pushButton_6_clicked();  //手动寻路
private:
    Ui::gameClass ui;
    int row;
    int col;
    int a[MAXSIZE][MAXSIZE] = {1};
    int inPointX;
    int inPointY;
    int outPointX;
    int outPointY;
    int characterx=150;
    int charactery=70;
    
    
    QPushButton* input[MAXSIZE * MAXSIZE];
    
    

};
