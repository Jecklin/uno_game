#include "MainWindow.h"
#include <QApplication>

#include "CGameLoop.h"

int main(int argc, char *argv[])
{
    //
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CGameLoop mainloop;
    mainloop.GameStart();

    return a.exec();
}
