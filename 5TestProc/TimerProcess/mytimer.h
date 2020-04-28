#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <qtimer.h>


class MyTimer : public QObject
{
    Q_OBJECT
public:
    explicit MyTimer(QObject *parent = nullptr);

    QTimer *timer;
public slots:
    void MyTimerSlot();

signals:

private:
    int m_timer = 5;
};

#endif // MYTIMER_H
