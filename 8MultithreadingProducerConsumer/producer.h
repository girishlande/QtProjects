#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QTimer>

class Producer : public QObject
{
    Q_OBJECT
public:
    explicit Producer(QObject *parent = nullptr);
    ~Producer();

public slots:
    void startProduction();
    void produce();

signals:
    void produced(int value);

private:
    QTimer* m_timer = nullptr;
    int m_value = 0;
};

#endif // PRODUCER_H
