#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QScreen"
#include "QApplication"
#include <qdebug.h>
#include <qnetworkaccessmanager.h>
#include <QNetworkReply>
#include <qnetworkrequest.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    determineScreenSize();

    checkInternetConnection();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::determineScreenSize()
{
    QScreen *screen = QApplication::screens().at(0);
    QSize size = screen->size();
    int screenWidth = size.width();
    int screenHeight = size.height();
    qDebug() << "Screen width:" << screenWidth;
    qDebug() << "Screen Height:" << screenHeight;
    if (screenHeight>screenWidth) {
        qDebug() << "This is portrait screen";
    } else {
        qDebug() << "This is landscape screen";
    }

    if (screenHeight>screenWidth) {
        ui->screenTypeLabel->setText("Screen Type: Portrait screen");
    } else {
        ui->screenTypeLabel->setText("Screen Type: Landscape screen");
    }
}

void MainWindow::checkInternetConnection()
{
    // following are 2 ways to listen to the output from network access manager
    // one is to write member function and second is to write lamvda function
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://google.com")));
    connect(reply, &QNetworkReply::finished,[=]() {

        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray response = reply->readAll();
            // do something with the data...
            qDebug() << "Reply is fine";
        }
        else // handle error
        {
            qDebug() << "didnt get reply. Error:" <<  reply->errorString();
        }
    });
}


void MainWindow::replyFinished(QNetworkReply* reply)
{
    //some other code here
    qDebug() << "received reply";
    if(reply->error() == QNetworkReply::NoError)
    {
        ui->internetLabel->setText("Internet Status: Internet is available");
    } else {
        ui->internetLabel->setText("Internet Status: Internet is NOT available");
    }
}
