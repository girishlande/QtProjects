#include <QCoreApplication>
#include <producer.h>
#include <consumer.h>
#include <QThread>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread::currentThread()->setObjectName("main thread");

    Producer p;
    QThread pthread;
    pthread.setObjectName("Producer Thread");
    p.connect(&pthread,&QThread::started,&p,&Producer::startProduction);
    p.moveToThread(&pthread);

    Consumer c;
    QThread cthread;
    cthread.setObjectName("Consumer thread");
    c.moveToThread(&cthread);
    c.connect(&p,&Producer::produced,&c,&Consumer::consume);

    cthread.start();
    pthread.start();

    qInfo() << "Free to do thing on Thread " << QThread::currentThread();

    return a.exec();
}
