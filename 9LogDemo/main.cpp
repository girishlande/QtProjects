#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>
#include "logger.h"
#include "test.h"

// Demo of how to use custom class for logging
// How to redirect logs in file on the disk
void LoggerDemo() {
    qInfo() << "File:" << Logger::filename;
    Logger::attach();

    qInfo() << "test";

    Logger::logging = false;
    qInfo() << "This will not get logged";
    Logger::logging = true;

    Test t;
    t.testing();

    qInfo() << "Finished";
}

// Demo of how to use log category so that you can disable and enable these logs whenever required
void CategoryDemo() {
    QLoggingCategory logtest("testing");
    logtest.setEnabled(QtMsgType::QtDebugMsg,false);
    logtest.setEnabled(QtMsgType::QtWarningMsg,false);

    qDebug() << "Debug = " << logtest.isDebugEnabled();
    qInfo() << "Info = " << logtest.isInfoEnabled();
    qWarning() << "Warning = " << logtest.isWarningEnabled();
    qCritical() << "Critical = " << logtest.isCriticalEnabled();

    qDebug(logtest) << "This is a debug";
    qInfo(logtest) << "This is a info";
    qWarning(logtest) << "This is a warning";
    qCritical(logtest) << "This is a critical";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LoggerDemo();
    CategoryDemo();

    return a.exec();
}
