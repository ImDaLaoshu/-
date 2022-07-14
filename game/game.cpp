#include "game.h"
#include "ui_game.h"




game::game(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}
//设置迷宫长宽
void game::setLengthAndWidth() {
    row = ui.lineEdit->text().toInt();
    col = ui.lineEdit_2->text().toInt();
}

//从文本读取迷宫数组
void game::getFromFile() {
    int irow=0,icol=0;
    char c;
    fstream in;
    in.open("testfile.txt",ios::in);

    while (in.peek() != EOF) {
        c = in.get();
        int n;
        if(c>='0'&&c<='9'){
            n = c - '0';
            if (n == 2) {
                inPointX = irow; inPointY = icol;
            }
            if (n == 3) {
                outPointX = irow; outPointY = icol;
            }
         a[irow][icol++] = n;

        if (icol >= col) {
            icol = 0;
            irow++;
        }
        }
    }   
}

//创建给定迷宫  1:墙 0：路 2：起点 3：终点
void game::create1() {
    setLengthAndWidth();
    int x, y,centa;

    getFromFile();
    

    for (int i = 0; i < row * col; i++) {
        //对应二维数组位置
        centa = a[i / col][i % col];
        //坐标设置
        x = 150 + 20 * (i % col);
        y = 50 + 20 * (i / col);
        input[i] = new QPushButton(QString::asprintf("0"), this);
        input[i]->setGeometry(x, y, 20, 20);
        //各块图块设置
        if (centa==2)      input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/startPoint.png);"));
       
        else if (centa == 1) input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/1.png);"));
        else if(centa==0)    input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/0.png);"));
        else                 input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/outPoint.png);"));
   
    input[i]->hide();
    input[i]->show();
 }
    ui.pushButton->setEnabled(false);//一旦生成迷宫之后就不能再点击了
    ui.pushButton_2->setEnabled(false);
    }


//随机生成迷宫算法
void CreateMaze(int maze[MAXSIZE][MAXSIZE], int x1, int y1, int x2, int y2) {
    //判断是否还能继续分割
    if (x2 - x1 < 2 || y2 - y1 < 2) {
        return;
    }

    //随机取点
    int x = x1 + 1 + rand() % (x2 - x1 - 1);
    int y = y1 + 1 + rand() % (y2 - y1 - 1);

    //画墙
    for (int i = x1; i <= x2; i++) maze[i][y] = WALL;
    for (int i = y1; i <= y2; i++) maze[x][i] = WALL;

    //递归分割，继续划分区域
    CreateMaze(maze, x1, y1, x - 1, y - 1);
    CreateMaze(maze, x + 1, y + 1, x2, y2);
    CreateMaze(maze, x + 1, y1, x2, y - 1);
    CreateMaze(maze, x1, y + 1, x - 1, y2);

    //随机取其中的三面墙
    int r[4] = { 0 };
    r[rand() % 4] = 1;

    //在墙上随机取点开孔
    for (int i = 0; i < 4; i++) {
        if (r[i] == 0) {
            int rx = x;
            int ry = y;
            switch (i) {
            case 0:
                //判断该位置是否能确保打通相邻两块区域，判断依据，上下左右位置最多只有两面墙，下面一样
                do {
                    rx = x1 + rand() % (x - x1);
                } while (maze[rx - 1][ry] + maze[rx + 1][ry] + maze[rx][ry - 1] + maze[rx][ry + 1] > 2 * WALL);
                break;
            case 1:
                do {
                    ry = y + 1 + rand() % (y2 - y);
                } while (maze[rx - 1][ry] + maze[rx + 1][ry] + maze[rx][ry - 1] + maze[rx][ry + 1] > 2 * WALL);
                break;
            case 2:
                do {
                    rx = x + 1 + rand() % (x2 - x);
                } while (maze[rx - 1][ry] + maze[rx + 1][ry] + maze[rx][ry - 1] + maze[rx][ry + 1] > 2 * WALL);
                break;
            case 3:
                do {
                    ry = y1 + rand() % (y - y1);
                } while (maze[rx - 1][ry] + maze[rx + 1][ry] + maze[rx][ry - 1] + maze[rx][ry + 1] > 2 * WALL);
                break;
            default:
                break;
            }
            maze[rx][ry] = ROUTE;
        }
    }
}


//随机迷宫生成
void game::create2() {
    srand((unsigned)time(NULL));
    setLengthAndWidth();
    int Maze[MAXSIZE][MAXSIZE] = { ROUTE };


    //外侧一圈为墙
    for (int i = 0; i < row; i++) {
        Maze[i][0] = WALL;
        Maze[i][col - 1] = WALL;
    }
    for (int i = 0; i < col; i++) {
        Maze[0][i] = WALL;
        Maze[row - 1][i] = WALL;
    }


    //生成迷宫
    CreateMaze(Maze, 1, 1, row - 2, col - 2);

    //设置出口
    Maze[1][0] = ROUTE;
    Maze[row - 2][col - 1] = ROUTE;

    inPointX = 1;
    inPointY = 0;
    outPointX = row - 2;
    outPointY = col - 1;


    //传入迷宫二维数组
    for(int i=0;i<row;i++)
        for (int j = 0; j < col; j++) {
            a[i][j] = Maze[i][j];
        }

    a[inPointX][inPointY] = 2;
    a[outPointX][outPointY] = 3;
    int centa,x,y;

    for (int i = 0; i < row * col; i++) {
        //对应二维数组位置
        centa = a[i / col][i % col];
        //坐标设置
        x = 150 + 20 * (i % col);
        y = 50 + 20 * (i / col);
        input[i] = new QPushButton(QString::asprintf("0"), this);
        input[i]->setGeometry(x, y, 20, 20);
        //各块图块设置
        if (centa == 2)      input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/startPoint.png);"));

        else if (centa == 1) input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/1.png);"));
        else if (centa == 0)    input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/0.png);"));
        else                 input[i]->setStyleSheet(QString::fromUtf8("border-image: url(:/game/outPoint.png);"));

        input[i]->hide();
        input[i]->show();
    }
    ui.pushButton_2->setEnabled(false);//一旦生成迷宫之后就不能再点击了
    ui.pushButton->setEnabled(false);
}



//DFS

//DFS前置函数
typedef struct {
    int x;
    int y;
}node;

typedef struct {
    node data[MAXSIZES];
    int top;
}stack;

void enStack(stack& S, int x, int y) {
    S.top++;
    S.data[S.top].x = x;
    S.data[S.top].y = y;
}



void getStackTop(stack &S, int& x, int& y) {
    x = S.data[S.top].x;
    y = S.data[S.top].y;
}

bool emptyStack(stack &S) {
    return S.top == -1;
}
//检测是否舍近求远 
bool checkShort(stack S, int x, int y, int& shortX, int& shortY) {

    S.top--;
    bool a = false, b = false;
    int ix, iy;
    while (!emptyStack(S)) {

        getStackTop(S, ix, iy);


        a = (ix - 1 == x && iy == y) || (ix + 1 == x && iy == y) || (ix == x && iy - 1 == y) || (ix == x && iy + 1 == y);
        b = a;
        if (b) {

            shortX = ix;
            shortY = iy;
            break;
        }

        S.top--;

    }

    return b;

}
//回退到路口 
void shortWay(stack& S, int checkM[MAXSIZE][MAXSIZE], int& countMap, int& shortX, int& shortY, int ix, int iy) {

    int sX, sY;
    while (!emptyStack(S)) {

        getStackTop(S, sX, sY);
        if (sX == shortX && sY == shortY) {
            ix = sX;
            iy = sY;
            break;
        }

        else {
            checkM[sX][sX] = -1;
            countMap--;
            S.top--;
        }

    }

}

//DFS实现

void DFS(int a[MAXSIZE][MAXSIZE],int irow,int icol,int inPX,int inPY,int outPX,int outPY,node *printMap,int &countMap){
    
     countMap = 0;
    //输出表  
    
    for (int i = 0; i < MAXSIZE*MAXSIZE; i++) {
        printMap[i].x = -1;
        printMap[i].y = -1;
    }


    a[inPX][inPY] = 0;
    a[outPX][outPY] = 0;




   int ix = 0,iy = 0,count = 0,shortX = 0,shortY = 0;

   //创建栈及其初始化； 
   stack S;
   S.top = -1;
   //数组元素权值表 墙权值为-1 ，起点权值为1 未访问权值为0 
   int checkM[MAXSIZE][MAXSIZE];
   for (int i = 0; i < irow; i++)
   for (int j = 0; j < icol; j++) {

       if (a[i][j] == 1) checkM[i][j] = -1;
       else checkM[i][j] = 0;
   }
   //起点入栈
   enStack(S,inPX,inPY);
   
   checkM[inPX][inPY] = 1;



   while (!emptyStack(S) && (ix != outPX || iy != outPY)) {

       getStackTop(S,ix,iy);

       //


       //判断是否为未被访问的无障碍结点 
       //上 
       if (ix - 1 >= 0)
       if (checkM[ix - 1][iy] > checkM[ix][iy] + 1 || checkM[ix - 1][iy] == 0)
       if (a[ix - 1][iy] == 0) {

          

           checkM[ix - 1][iy]++;
           enStack(S,ix - 1,iy);

           printMap[countMap].x = ix - 1;
           printMap[countMap++].y = iy;
           
           count++;
       }

       //下
       if (count == 0)
       if (ix + 1 < irow)
       if (checkM[ix + 1][iy] > checkM[ix][iy] + 1 || checkM[ix + 1][iy] == 0)
       if (a[ix + 1][iy] == 0) {

           

           checkM[ix + 1][iy]++;
           enStack(S,ix + 1,iy);
           printMap[countMap].x = ix + 1;
           printMap[countMap++].y = iy;
           
           count++;
       }

       //左
       if (count == 0)
       if (iy - 1 >= 0)
       if (checkM[ix][iy - 1] > checkM[ix][iy] + 1 || checkM[ix][iy - 1] == 0)
       if (a[ix][iy - 1] == 0) {
           

           checkM[ix][iy - 1]++;
           enStack(S,ix,iy - 1);
           printMap[countMap].x = ix;
           printMap[countMap++].y = iy - 1;
           
           count++;
       }

       //右
       if (count == 0)
       if (iy + 1 < icol)
       if (checkM[ix][iy + 1] > checkM[ix][iy] + 1 || checkM[ix][iy + 1] == 0)
       if (a[ix][iy + 1] == 0) {

           

           checkM[ix][iy + 1]++;
           enStack(S,ix,iy + 1);
           printMap[countMap].x = ix;
           printMap[countMap++].y = iy + 1;
           
           count++;
       }




       //回溯
       if (count == 0) {

           countMap--;
           S.top--;
       }

   count = 0;
   getStackTop(S,ix,iy);
   }

   //将出迷宫点输出 
       printMap[countMap].x = outPX;
       printMap[countMap].y = outPY;
           S.top--;


           
}

 void game::Sleep(int msec)
{
      QTime dieTime = QTime::currentTime().addMSecs(msec);
         while (QTime::currentTime() < dieTime)
               QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     }




void game::on_pushButton_clicked() {
    create1();//出现迷宫
    for (int i = 0; i < row * col; i++)
        input[i]->show();

   
}

void game::on_pushButton_2_clicked() {
    create2();
    for (int i = 0; i < row * col; i++)
        input[i]->show();

    

}

node printMap[MAXSIZE * MAXSIZE];

void game::on_pushButton_3_clicked() {
    ui.pushButton_4->setEnabled(false);
    
    int countMap;
    DFS(a, row, col, inPointX, inPointY, outPointX, outPointY, printMap, countMap);
    
    
   
    if(inputC==NULL)
    inputC = new QPushButton(QString::asprintf("0"), this);
       
    for(int i=0;i<= countMap;i++){
       characterx = 150 + 20 * printMap[i].y;
       charactery = 50 + 20 * printMap[i].x;
    inputC->setGeometry(characterx, charactery, 20, 20);
    inputC->setStyleSheet(QString::fromUtf8("border-image: url(:/game/character.png);"));

    inputC->show();
    Sleep(1000);
    inputC->hide();
}
    //delete inputC;

    ui.pushButton_4->setEnabled(true);
}

void game::on_pushButton_5_clicked() {
    delete inputC;

    for (int i = 0; i < row * col; i++) {
        delete input[i];
    }
    
    exit(0);

}


typedef struct {
    int x;
    int y;
}nodeQ;

typedef struct {
    int fx;
    int fy;
}box;


typedef struct {
    nodeQ data[MAXSIZES];
    int front, rear;
}queue;

void enQueue(queue& q, int ix, int iy) {
    q.rear++;
    q.data[q.rear].x = ix;
    q.data[q.rear].y = iy;

}



bool emptyQueue(queue &q) {

    return (q.front == q.rear);
}

void getQueueTop(queue &q, int& x, int& y) {
    x = q.data[q.front + 1].x;
    y = q.data[q.front + 1].y;

}

void BFS(int Maze[MAXSIZE][MAXSIZE], int irow, int icol, int inPX, int inPY, int outPX, int outPY, box head[MAXSIZE][MAXSIZE]) {
    int ix = 0, iy = 0;
    //创建队列 
    queue Q;
    Q.front = Q.rear = -1;//初始化 

    //前驱元素表
    for (int i = 0; i < irow; i++)
        for (int j = 0; j < icol; j++) {
            head[i][j].fx = i;
            head[i][j].fy = j;
            head[i][j].fx = head[i][j].fy = -1;
        }





    //入口入队列 
    enQueue(Q, inPX, inPY);
    head[inPX][inPY].fx = inPX;
    head[inPX][inPY].fy = inPY;



    while (!emptyQueue(Q) && (ix != outPX || iy != outPY)) {
        getQueueTop(Q, ix, iy);
        Q.front++;
        //判断是否为未被访问的无障碍结点 
        //上 
        if (ix - 1 >= 0)
            if (head[ix - 1][iy].fx == -1 && head[ix - 1][iy].fy == -1)
                if (Maze[ix - 1][iy] == 0) {

                    enQueue(Q, ix - 1, iy);
                    head[ix - 1][iy].fx = ix;
                    head[ix - 1][iy].fy = iy;


                }

        //下

        if (ix + 1 < irow)
            if (head[ix + 1][iy].fx == -1 && head[ix + 1][iy].fy == -1)
                if (Maze[ix + 1][iy] == 0) {

                    enQueue(Q, ix + 1, iy);
                    head[ix + 1][iy].fx = ix;
                    head[ix + 1][iy].fy = iy;

                }

        //左

        if (iy - 1 >= 0)
            if (head[ix][iy - 1].fx == -1 && head[ix][iy - 1].fy == -1)
                if (Maze[ix][iy - 1] == 0) {

                    enQueue(Q, ix, iy - 1);
                    head[ix][iy - 1].fx = ix;
                    head[ix][iy - 1].fy = iy;

                }

        //右

        if (iy + 1 < icol)
            if (head[ix][iy + 1].fx == -1 && head[ix][iy + 1].fy == -1)
                if (Maze[ix][iy + 1] == 0) {

                    enQueue(Q, ix, iy + 1);
                    head[ix][iy + 1].fx = ix;
                    head[ix][iy + 1].fy = iy;

                }


        getQueueTop(Q, ix, iy);

    }

}

box head[MAXSIZE][MAXSIZE];

void game::on_pushButton_4_clicked() {
    ui.pushButton_3->setEnabled(false);
    int countMap;
    a[inPointX][inPointY] = 0;
    a[outPointX][outPointY] = 0;
    BFS(a, row, col, inPointX, inPointY, outPointX, outPointY, head);
    int centx=outPointX, centy=outPointY,cent;
    if (inputC == NULL)
        inputC = new QPushButton(QString::asprintf("0"), this);

    while(centx != inPointX || centy != inPointY) {
        characterx = 150 + 20 * centy;
        charactery = 50 + 20 * centx;
        cent = centx;
        centx = head[centx][centy].fx;
        centy = head[cent][centy].fy;

        inputC->setGeometry(characterx, charactery, 20, 20);
        inputC->setStyleSheet(QString::fromUtf8("border-image: url(:/game/character.png);"));

        inputC->show();
        Sleep(100);
        inputC->hide();
    }


    while(centx != inPointX || centy != inPointY) {
        characterx = 150 + 20 * centy;
        charactery = 50 + 20 * centx;
        cent = centx;
        centx = head[centx][centy].fx;
        centy = head[cent][centy].fy;

        inputC->setGeometry(characterx, charactery, 20, 20);
        inputC->setStyleSheet(QString::fromUtf8("border-image: url(:/game/character.png);"));

        inputC->show();
        Sleep(500);
        inputC->hide();
    }

    ui.pushButton_3->setEnabled(true);

}



//控制人物移动
void game::CharacterMove() {

    //创建人物块
    if (inputC == NULL)
        inputC = new QPushButton(QString::asprintf("0"), this);
        inputC->setStyleSheet(QString::fromUtf8("border-image: url(:/game/character.png);"));
        inputC->setGeometry(characterx, charactery, 20, 20);
        inputC->show();
        Sleep(100);
        inputC->hide();


    //读取键盘方向键
    int c1 = _getch(), c2 = _getch();
    while (c2 != 13) {
        //上
        if (c2 == 72)  charactery -= 20;
        //下
        if (c2 == 80) charactery += 20;
        //左
        if (c2 == 75) characterx -= 20;
        //右
        if (c2 == 77) characterx+=20;

        inputC->setGeometry(characterx, charactery, 20, 20);
        inputC->show();
        Sleep(100);
        inputC->hide();

        c1 = _getch(), c2 = _getch();
    }


}

void game::on_pushButton_6_clicked() {
    CharacterMove();
}