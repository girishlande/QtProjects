#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:
    void updatedTimer(int timer);

public slots:
    void startWork();
    void stopWork();

private:
    bool m_running = false;
};

#endif // WORKER_H
