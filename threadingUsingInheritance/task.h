#ifndef TASK_H
#define TASK_H

#include "qthread.h"

class Task : public QThread
{
    Q_OBJECT
public:
    Task();
    void run();

signals:
    void updateProgress(int progress);

};

#endif // TASK_H
