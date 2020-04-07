#include "mainwindow.h"
#include "set.h"
#include <QString>
#include <assert.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
