#include "myclass.h"

MyClass::MyClass(QObject *parent, QString name) : QObject(parent)
{
    setObjectName(name);
    qInfo() << this->objectName() << "Created on " << QThread::currentThread()->objectName();
}

MyClass::~MyClass()
{
    qInfo() << this->objectName() << "Destroyed on " << QThread::currentThread()->objectName();
}

void MyClass::perform()
{
    qInfo() << this->objectName() << "Emitting signal on " << QThread::currentThread()->objectName();
    emit test();
}

void MyClass::onTest()
{
    qInfo() << this->objectName() << " receiving signal on "<< QThread::currentThread()->objectName() << " sender:" << (sender() ? sender()->objectName() : "NA");
}
