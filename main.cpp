#include "mainwindow.h"
#include<qtextcodec.h>
#include <QApplication>
#include<diag.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w->show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    int result = a.exec();
    delete w;
    return result;
}
