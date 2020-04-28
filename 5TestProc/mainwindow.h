#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qmessagebox.h>

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
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

public slots:
    void OnStarted();
    void OnStopped();

protected slots:
    void ShowMessageBox();
    void HideMessageBox();

protected:
    void startProcess();

private:
    Ui::MainWindow *ui;
    QMessageBox* msgBox;
};

#endif // MAINWINDOW_H
