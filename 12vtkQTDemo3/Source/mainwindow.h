#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class QVTKWidget;
class QVBoxLayout;
class vtkImageViewer2;
class QScrollBar;
class QGridLayout;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVBoxLayout *vboxLayout;
    QWidget *centralwidget;
    QVTKWidget *m_vtkView;
    QGridLayout *m_container_layout;

    QString dicom_dir_path;
    int current_view_index;

    void InitialiseView();

    void UpdateViewForDICOM();
    void updateSlider(int value);

private slots:
    void on_actionOpen_DICOM_file_triggered();
    void on_actionExit_triggered();

    void updateview_1();

    void test();
    void orient_angle();

    void sliderChanged1(int value);

private:
    Ui::MainWindow *ui;
    QScrollBar* m_slider;
    vtkImageViewer2* m_vtkImageViewer;
};

#endif // MAINWINDOW_H
