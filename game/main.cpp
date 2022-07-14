#include "game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game w;
    w.setWindowTitle("maze");
    w.setFixedSize(1920, 1080);
    w.show();
    
    return a.exec();
}
