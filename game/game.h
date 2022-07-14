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
   
    void setLengthAndWidth();        //�Թ���������
    void create1();                    //�Թ���������
    void create2();                     //�漴�Թ�����
    void getFromFile();                //���ļ��ж�ȡ�Թ�����
    void Sleep(int msec);                //��ʱ����
    void CharacterMove();               //���������ƶ�

    ~game() {
        delete inputC;

        for (int i = 0; i < row * col; i++) {
            delete input[i];
        }
    }
    

    
    
private slots:
    void on_pushButton_clicked(); //�����Թ�
    void on_pushButton_2_clicked();//����Թ� 
    void on_pushButton_3_clicked();//�������
    void on_pushButton_4_clicked();//�������
    void on_pushButton_5_clicked();  //��������
    void on_pushButton_6_clicked();  //�ֶ�Ѱ·
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
