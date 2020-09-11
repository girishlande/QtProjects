#include "mainwindow.h"

#include <QBoxLayout.h>
#include <QComboBox.h>
#include <QDir.h>
#include <QFileDialog.h>
#include <QGridLayout.h>
#include <QSplitter.h>
#include <qdebug.h>
#include <qscrollbar.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkOBJReader.h>
#include <vtkObjectFactory.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>

#include <QPushButton>
#include <QStringList>
#include <QTimer>

#include "QVTKWidget.h"
#include "dicominteractionstyle.h"
#include "modelinteractionstyle.h"

// headers needed for this example
#include <QStackedWidget.h>
#include <vtkActor2D.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

// needed to easily convert int to std::string
#include <sstream>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_vtkImageViewer(nullptr) {

  // Setup window and resize it
  ui->setupUi(this);
  this->resize(1002, 666);
  this->showMaximized();

  // Apply style sheet on it for Black theme appearance
  QFile file(":/stylesheets/style2.qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());
  this->setStyleSheet(styleSheet);

  // Create central widget
  centralwidget = new QWidget(this);
  centralwidget->setObjectName(QStringLiteral("centralwidget"));

  // Create layout for central widget
  vboxLayout = new QVBoxLayout(centralwidget);
  vboxLayout->setSpacing(1);
  vboxLayout->setObjectName(QStringLiteral("vboxLayout"));

  // ----------------------------------
  // Create VTK Widgets for each View
  // ----------------------------------
  m_vtkView = new QVTKWidget(this);

  QVBoxLayout* tablayout = new QVBoxLayout();
  QPushButton* b1 = new QPushButton("Test Button", this);
  connect(b1, SIGNAL(clicked(bool)), this, SLOT(test()));
  tablayout->addWidget(b1);

  m_slider = new QScrollBar(this);
  m_slider->setFixedWidth(20);
  connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged1(int)));

  QWidget* controls_widget = new QWidget;
  controls_widget->setLayout(tablayout);

  m_container_layout = new QGridLayout;
  m_container_layout->addWidget(m_vtkView, 0, 0, 1, 1);
  m_container_layout->addWidget(m_slider, 0, 1, 1, 1);
  QWidget* container = new QWidget;
  container->setLayout(m_container_layout);

  // -------------------------------------------------
  // Add splitter between VTK Views and field editor
  // -------------------------------------------------
  QSplitter* split2 = new QSplitter;
  split2->setOrientation(Qt::Horizontal);
  split2->addWidget(container);
  split2->addWidget(controls_widget);

  QList<int> sizes;
  sizes << 1600 << 400;
  split2->setSizes(sizes);

  vboxLayout->addWidget(split2);

  this->setCentralWidget(centralwidget);

  InitialiseView();
}

void MainWindow::InitialiseView() {
  vtkSmartPointer<vtkSphereSource> s1 = vtkSmartPointer<vtkSphereSource>::New();
  s1->Update();

  vtkSmartPointer<vtkPolyDataMapper> sm1 =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sm1->SetInputConnection(s1->GetOutputPort());
  vtkSmartPointer<vtkActor> sa1 = vtkSmartPointer<vtkActor>::New();
  sa1->SetMapper(sm1);
  vtkSmartPointer<vtkRenderer> r1 = vtkSmartPointer<vtkRenderer>::New();
  r1->AddActor(sa1);
  this->m_vtkView->GetRenderWindow()->AddRenderer(r1);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_DICOM_file_triggered() {
  // Browse for and open the file
  QDir dir;

  // Open the text data file
  QString fileName =
      QFileDialog::getOpenFileName(this, "Select DICOM file", "../models",
                                   "DICOM Files (*.dcm);;All Files (*.*)");

  if (fileName.isNull()) {
    cerr << "Could not open file" << endl;
    return;
  }

  QFileInfo fileinfo(fileName);
  QDir dirname = fileinfo.absoluteDir();
  QString dirpath = dirname.absolutePath();
  dicom_dir_path = dirpath;

  QTimer::singleShot(100, this, SLOT(updateview_1()));
  QTimer::singleShot(200, this, SLOT(updateview_2()));
  QTimer::singleShot(300, this, SLOT(updateview_3()));
  QTimer::singleShot(400, this, SLOT(updateview_4()));
}

void MainWindow::updateview_1() {
  current_view_index = 1;
  UpdateViewForDICOM();
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::UpdateViewForDICOM() {
  // Read all the DICOM files in the specified dir    ectory.
  vtkSmartPointer<vtkDICOMImageReader> reader =
      vtkSmartPointer<vtkDICOMImageReader>::New();
  reader->SetDirectoryName(dicom_dir_path.toLatin1());
  reader->Update();

  // Visualize
  vtkSmartPointer<vtkImageViewer2> imageViewer =
      vtkSmartPointer<vtkImageViewer2>::New();
  imageViewer->SetInputConnection(reader->GetOutputPort());
  imageViewer->SetSliceOrientationToXY();
  m_vtkImageViewer = imageViewer.Get();
  m_slider->setMinimum(imageViewer->GetSliceMin());
  m_slider->setMaximum(imageViewer->GetSliceMax());
  m_slider->setValue(imageViewer->GetSlice());

  // slice status message
  vtkSmartPointer<vtkTextProperty> sliceTextProp =
      vtkSmartPointer<vtkTextProperty>::New();
  sliceTextProp->SetFontFamilyToCourier();
  sliceTextProp->SetFontSize(20);
  sliceTextProp->SetVerticalJustificationToBottom();
  sliceTextProp->SetJustificationToLeft();

  vtkSmartPointer<vtkTextMapper> sliceTextMapper =
      vtkSmartPointer<vtkTextMapper>::New();
  std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
                                          imageViewer->GetSliceMax());
  sliceTextMapper->SetInput(msg.c_str());
  sliceTextMapper->SetTextProperty(sliceTextProp);

  vtkSmartPointer<vtkActor2D> sliceTextActor =
      vtkSmartPointer<vtkActor2D>::New();
  sliceTextActor->SetMapper(sliceTextMapper);
  sliceTextActor->SetPosition(15, 10);

  // usage hint message
  vtkSmartPointer<vtkTextProperty> usageTextProp =
      vtkSmartPointer<vtkTextProperty>::New();
  usageTextProp->SetFontFamilyToCourier();
  usageTextProp->SetFontSize(14);
  usageTextProp->SetVerticalJustificationToTop();
  usageTextProp->SetJustificationToLeft();

  vtkSmartPointer<vtkTextMapper> usageTextMapper =
      vtkSmartPointer<vtkTextMapper>::New();
  usageTextMapper->SetInput(
      "- Slice with mouse wheel\n  \n- Zoom with pressed right\n  mouse button "
      "while dragging");
  usageTextMapper->SetTextProperty(usageTextProp);

  vtkSmartPointer<vtkActor2D> usageTextActor =
      vtkSmartPointer<vtkActor2D>::New();
  usageTextActor->SetMapper(usageTextMapper);
  usageTextActor->GetPositionCoordinate()
      ->SetCoordinateSystemToNormalizedDisplay();
  usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

  // create an interactor with our own style (inherit from
  // vtkInteractorStyleImage) in order to catch mousewheel and key events
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();

  vtkSmartPointer<myVtkInteractorStyleImage> myInteractorStyle =
      vtkSmartPointer<myVtkInteractorStyleImage>::New();
  myInteractorStyle->setWindow(this);
  // make imageviewer2 and sliceTextMapper visible to our interactorstyle
  // to enable slice status message updates when scrolling through the slices
  myInteractorStyle->SetImageViewer(imageViewer);
  myInteractorStyle->SetStatusMapper(sliceTextMapper);

  // make the interactor use our own interactorstyle
  // cause SetupInteractor() is defining it's own default interatorstyle
  // this must be called after SetupInteractor()
  renderWindowInteractor->SetInteractorStyle(myInteractorStyle);

  // add slice status message and usage hint message to the renderer
  imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
  // imageViewer->GetRenderer()->AddActor2D(usageTextActor);

  imageViewer->SetRenderWindow(m_vtkView->GetRenderWindow());
  m_vtkView->GetRenderWindow()->SetInteractor(renderWindowInteractor);

  // initialize rendering and interaction
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();

  renderWindowInteractor->Start();
}

void MainWindow::test() { cout << "pelvic_plane() called" << endl; }

void MainWindow::orient_angle() { m_container_layout->removeWidget(m_vtkView); }

void MainWindow::sliderChanged1(int value) {
  if (m_vtkImageViewer) {
    m_vtkImageViewer->SetSlice(value);
    myVtkInteractorStyleImage* style =
        (myVtkInteractorStyleImage*)m_vtkView->GetRenderWindow()
            ->GetInteractor()
            ->GetInteractorStyle();
    if (style) {
      style->updateSliceMsg(value);
    }
  }
}


void MainWindow::updateSlider(int value) { m_slider->setValue(value); }