#include "consumer.h"
#include<qthread.h>
#include <qdebug.h>

Consumer::Consumer(QObject *parent) : QObject(parent)
{
    qInfo() << "Consumer created! Thread:" << QThread::currentThread();
}

Consumer::~Consumer()
{
    qInfo() << "Consumer Destructor" << QThread::currentThread();
}

void Consumer::consume(int value)
{
    qInfo() << "Consumed: " << value << " Thread:" << QThread::currentThread();
}

