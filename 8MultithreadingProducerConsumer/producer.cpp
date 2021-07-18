#include "producer.h"
#include <QThread>
#include <QTimer>
#include <QDebug>

Producer::Producer(QObject *parent) : QObject(parent)
{
    qInfo() << "Producer constructed! on thread:" << QThread::currentThread();
}

Producer::~Producer()
{
    m_timer->stop();
    delete m_timer;
    qInfo() << "Producer destructed! on thread:" << QThread::currentThread();
}

void Producer::startProduction()
{
    m_timer = new QTimer();
    m_timer->setInterval(1000);
    connect(m_timer,&QTimer::timeout,this,&Producer::produce);
    m_timer->start();
}

void Producer::produce()
{
    m_value++;
    qInfo() << "Produced " << m_value << " thread:" << QThread::currentThread();
    emit produced(m_value);
}
