#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qprocess.h>
#include <qmessagebox.h>
#include <qtimer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    startProcess();
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "Button 1 is clicked";
}

void MainWindow::OnStarted()
{
}

void MainWindow::OnStopped()
{
    msgBox->setText("Timer process finished....");
    QTimer::singleShot(1000, this, SLOT(HideMessageBox()));
}

void MainWindow::ShowMessageBox()
{
    msgBox = new QMessageBox;
    msgBox->setWindowFlags(Qt::FramelessWindowHint);  //removes titlebar
    msgBox->setStandardButtons(0); //removes button
    msgBox->setText("Timer process started....");
    msgBox->setFixedSize(800,300); //has no effect
    msgBox->show();
}

void MainWindow::HideMessageBox()
{
    delete msgBox;
}

void MainWindow::startProcess()
{
    ShowMessageBox();
    QString processPath = "D:\\test\\build-TimerProcess-Desktop_Qt_5_13_0_MinGW_64_bit-Debug\\debug\\TimerProcess.exe";
    QProcess *process = new QProcess(this);
    connect(process,SIGNAL(started()),this,SLOT(OnStarted()));
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus exitStatus){
        OnStopped();
    });

    process->start(processPath);
}
