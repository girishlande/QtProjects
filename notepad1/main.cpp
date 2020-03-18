#include "mainwindow.h"
#include <QApplication>
#include <qsplashscreen.h>
#include <thread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/splashscreen.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    QFont splashFont;
    splashFont.setFamily("Arial");
    splashFont.setBold(true);
    splashFont.setPixelSize(24);
    splashFont.setStretch(125);

    splash->setFont(splashFont);
    splash->showMessage("launching notepad",Qt::AlignRight | Qt::AlignBottom | Qt::AlignJustify);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    a.processEvents();

    splash->hide();

    MainWindow w;
    w.show();

    return a.exec();
}
