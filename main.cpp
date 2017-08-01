#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setWindowState(Qt::WindowMaximized);
    w.setGeometry(110,110,666,666);
    w.show();

    return a.exec();
}
