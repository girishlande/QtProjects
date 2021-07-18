#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);
    ~Consumer();

public slots:
    void consume(int value);

signals:

};

#endif // CONSUMER_H
