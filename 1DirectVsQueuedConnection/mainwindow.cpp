#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"
#include <qthread.h>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QThread* thread1 = new QThread();
    Worker* worker = new Worker();
    worker->moveToThread(thread1);
    thread1->start();

    connect(ui->pushButton,SIGNAL(clicked()),worker,SLOT(startWork()),Qt::QueuedConnection);
    connect(ui->pushButton_2,SIGNAL(clicked()),worker,SLOT(stopWork()),Qt::DirectConnection);
    connect(worker,SIGNAL(updatedTimer(int)),this,SLOT(updateUI(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI(int timer)
{
    qDebug() << "Main UI update" << timer;
    ui->progressBar->setValue(timer);
}

