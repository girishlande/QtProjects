#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBarJob1->setValue(0);
    ui->progressBarJob2->setValue(0);

    t1 = new Task();
    connect(t1,&Task::updateProgress,this,&MainWindow::progressUpdated);

    t2 = new Task();
    connect(t2,&Task::updateProgress,this,&MainWindow::progressUpdated2);

}

MainWindow::~MainWindow()
{
    t1->wait();
    delete t1;

    t2->wait();
    delete t2;

    delete ui;
}

void MainWindow::on_pushButtonJob1_clicked()
{
    qDebug() << "start job1";
    t1->start();
}

void MainWindow::progressUpdated(int progress)
{
    ui->progressBarJob1->setValue(progress);
}

void MainWindow::progressUpdated2(int progress)
{
    ui->progressBarJob2->setValue(progress);
}

void MainWindow::on_pushButtonJob2_clicked()
{
    qDebug() << "start job2";
    t2->start();
}

void MainWindow::on_pushButtonRed_clicked()
{
    ui->label->setText("clicked: RED");
}

void MainWindow::on_pushButtonGreen_clicked()
{
    ui->label->setText("clicked: GREEN");
}

void MainWindow::on_pushButtonBlue_clicked()
{
    ui->label->setText("clicked: BLUE");
}
