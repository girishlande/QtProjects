#include "worker.h"
#include <qdebug.h>
#include <unistd.h>
#include <thread>
#include <chrono>
Worker::Worker(QObject *parent) : QObject(parent)
{

}

void Worker::startWork()
{
    m_running = true;
    for(int i=0;i<100;i++) {
        if (!m_running) {
            return;
        }
        qDebug() << "working " << i;
        emit updatedTimer(i+1);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Worker::stopWork()
{
    m_running = false;
    qDebug() << "Stopped ";
}
