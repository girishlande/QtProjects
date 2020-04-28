#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "qfiledialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setFontPointSize(20);
    setWindowTitle("Girish's Notepad");
    d1 = new Dialog();
    d1->setWindowTitle("About Girish Notepad");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    qDebug() << "Create new file";
    ui->textEdit->setText(QString());
    currentFile="";

}

void MainWindow::on_actionOpen_triggered()
{
    qDebug() << "Open an existing file";
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Text File"), "D://", tr("Text Files (*.txt)"));
    qDebug () << "Open file:" << fileName;
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        currentFile = fileName;
       QTextStream in(&inputFile);
       ui->textEdit->setText(in.readAll());
       inputFile.close();
    }

}

void MainWindow::on_actionSave_triggered()
{
    if (currentFile.size()==0) {
        on_actionSave_A_triggered();
    }

    qDebug() << "save file";
    QFile inputFile(currentFile);
    if (inputFile.open(QIODevice::WriteOnly))
    {
       QTextStream in(&inputFile);
       in << ui->textEdit->toPlainText();
       inputFile.close();
    }
}

void MainWindow::on_actionSave_A_triggered()
{
    qDebug() << "Save as file";
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Text File"), "D://", tr("Text Files (*.txt)"));
    qDebug () << "Open file:" << fileName;
    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::WriteOnly))
    {
       QTextStream in(&inputFile);
       in << ui->textEdit->toPlainText();
       inputFile.close();
    }

}

void MainWindow::on_actionExit_triggered()
{
    qDebug() << "Exit application";
    QApplication::quit();

}

void MainWindow::on_actionCut_triggered()
{
    qDebug() << "Cut selection";
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    qDebug() << "Create new file";
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    qDebug() << "Paste selection";
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    qDebug() << "Undo selection";
    ui->textEdit->undo();

}

void MainWindow::on_actionRedo_triggered()
{
    qDebug() << "Redo selection";
    ui->textEdit->redo();
}

void MainWindow::on_actionGirish_s_Notepad_triggered()
{
    qDebug() << "about Girish notepad ";

    d1->open();
}
