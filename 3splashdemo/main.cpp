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
    QFont splashFont;
    splashFont.setFamily("Arial");
    splashFont.setBold(true);
    splashFont.setPixelSize(39);
    splashFont.setStretch(125);

    splash->setFont(splashFont);
    splash->showMessage("Loaded modules",Qt::AlignRight | Qt::AlignBottom | Qt::AlignJustify);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    app.processEvents();

    splash->showMessage("Established connections",Qt::AlignRight | Qt::AlignBottom );
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    app.processEvents();

    splash->hide();
    QMainWindow window;
    window.showMaximized();

    return app.exec();
}
