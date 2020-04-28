#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Task;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonJob1_clicked();

    void on_pushButtonJob2_clicked();

    void on_pushButtonRed_clicked();

    void on_pushButtonGreen_clicked();

    void on_pushButtonBlue_clicked();

public slots:
    void progressUpdated(int progress);
     void progressUpdated2(int progress);

private:
    Ui::MainWindow *ui;
    Task* t1;
    Task* t2;
};

#endif // MAINWINDOW_H
