#include "CWidget.h"
#include <QApplication>
#include <qdesktopwidget.h>  

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWidget w;
    
    QDesktopWidget *desktop = QApplication::desktop();  
    w.move((desktop->width() - w.width())/ 2, (desktop->height() - w.height()) /2 - 50); 
    
    w.show();

    return a.exec();
}
