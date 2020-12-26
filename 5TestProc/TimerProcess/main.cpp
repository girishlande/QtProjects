#include <QCoreApplication>
#include <qtimer.h>
#include <qdebug.h>
#include <qobject.h>
#include "mytimer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyTimer timer;
    return a.exec();
}
