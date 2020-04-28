#include "mainwindow.h"
#include <QApplication>
#include "qsqldatabase.h"
#include "qdebug.h"
#include "iostream"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("D:\\imagedata.db");

    bool ok = database.open();
    if(ok) {
        qDebug("database opened");
        QStringList list = database.tables();
        qDebug() << "Number of tables:" << list.count();

        for(auto x: list) {
            qDebug() << x;
        }

    } else {
        qDebug("database did not open");
    }
    return a.exec();
}
