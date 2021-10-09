#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>
#include <QDebug>
#include <QThread>

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr, QString name="");
    ~MyClass();

    void perform();

signals:
    void test();

public slots:
    void onTest();

};

#endif // MYCLASS_H
