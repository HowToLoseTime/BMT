#include "mainwindow.h"

#include <QApplication>
#include <database.cpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int i;
    return a.exec();
}
