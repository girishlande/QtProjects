#include "mytimer.h"
#include "qdebug.h"

MyTimer::MyTimer(QObject *parent) : QObject(parent)
{

    // create a timer
    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, SIGNAL(timeout()),
            this, SLOT(MyTimerSlot()));

    // msec
    timer->start(1000);
}

void MyTimer::MyTimerSlot()
{
    qDebug() << "Timer..." << m_timer;
    if(m_timer==0) {
        timer->stop();
        exit(0);
    }
    m_timer--;
}
