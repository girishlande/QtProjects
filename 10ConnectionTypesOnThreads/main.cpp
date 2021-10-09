#include <QCoreApplication>

/*

  What
  Signal & Slot Connection Types

  Description
  Connections between signals and slots can have differnt connection types

  Why
    We are about to find out!

  Example

  https://doc.qt.io/qt-5/signalsandslots.html
  https://doc.qt.io/qt-5/qt.html#ConnectionType-enum

 */

#include <QDebug>
#include <QThread>
#include "myclass.h"

void test(MyClass *source, MyClass *destination, Qt::ConnectionType type = Qt::ConnectionType::AutoConnection, QThread *thread = nullptr)
{
    QObject::connect(source,&MyClass::test, destination,&MyClass::onTest, type);
    if(thread)
    {
        qInfo() << destination->objectName() << " moving to " << thread->objectName();
        destination->moveToThread(thread);
    }
    source->perform();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread::currentThread()->setObjectName("Main Thread");

    MyClass source(nullptr,"source");
    MyClass destination(nullptr,"destination");

    QThread thread;
    thread.start();
    thread.setObjectName("Seperate Thread");

    //---Non-Threaded---

    //Auto
    //test(&source,&destination);

    //DirectConnection
    //test(&source,&destination,Qt::DirectConnection);

    //QueuedConnection
    //test(&source,&destination,Qt::QueuedConnection);

    //BlockingQueuedConnection - will deadlock
    //test(&source,&destination,Qt::BlockingQueuedConnection);

    //UniqueConnection
    //test(&source,&destination,Qt::UniqueConnection);

    //---Threaded---

    //Auto threaded - works across thread - sometimes
    //test(&source,&destination,Qt::AutoConnection, &thread);

    //DirectConnection threaded - signal triggers slot but sender is 0x0
    //test(&source,&destination,Qt::DirectConnection, &thread);

    //QueuedConnection threaded -  works as expected (perfered for cross thread)
    //test(&source,&destination,Qt::QueuedConnection, &thread);

    //BlockingQueuedConnection threaded - a bit dangerous, can lock the signaling thread
    //test(&source,&destination,Qt::BlockingQueuedConnection, &thread);

    //UniqueConnection threaded - works as expected
    //test(&source,&destination,Qt::UniqueConnection,&thread);



    return a.exec();
}
