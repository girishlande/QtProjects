#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QNetworkReply;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void determineScreenSize();
    void checkInternetConnection();

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
