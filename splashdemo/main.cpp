#include "mainwindow.h"
#include <QApplication>
#include <qsplashscreen.h>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap(":/splashscreen.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    splash->showMessage("Loaded modules");

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    app.processEvents();

    splash->showMessage("Established connections");
    app.processEvents();

    splash->hide();
    QMainWindow window;
    window.showMaximized();

    return app.exec();
}
