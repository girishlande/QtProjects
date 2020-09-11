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
    : QMainWindow(parent), ui(new Ui::MainWindow), s1_viewer(nullptr) {

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
  view1 = new QVTKWidget(this);

  QVBoxLayout* tablayout = new QVBoxLayout();
  QPushButton* b1 = new QPushButton("Pelvic Plane", this);
  connect(b1, SIGNAL(clicked(bool)), this, SLOT(pelvic_plane()));
  tablayout->addWidget(b1);

  s1 = new QScrollBar(this);
  s1->setFixedWidth(20);
  connect(s1, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged1(int)));

  QWidget* firstPageWidget = new QWidget;
  QWidget* secondPageWidget = new QWidget;
  QWidget* thirdPageWidget = new QWidget;

  // Add different pages for each button
  QStackedWidget* stackedWidget = new QStackedWidget;
  stackedWidget->addWidget(firstPageWidget);
  stackedWidget->addWidget(secondPageWidget);
  stackedWidget->addWidget(thirdPageWidget);
  tablayout->addWidget(stackedWidget);

  QWidget* controls_widget = new QWidget;
  controls_widget->setLayout(tablayout);

  m_container_layout = new QGridLayout;
  m_container_layout->addWidget(view1, 0, 0, 1, 1);
  m_container_layout->addWidget(s1, 0, 1, 1, 1);
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

  DoView_1();
}

void MainWindow::DoView_1() {
  vtkSmartPointer<vtkSphereSource> s1 = vtkSmartPointer<vtkSphereSource>::New();
  s1->Update();

  vtkSmartPointer<vtkPolyDataMapper> sm1 =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sm1->SetInputConnection(s1->GetOutputPort());
  vtkSmartPointer<vtkActor> sa1 = vtkSmartPointer<vtkActor>::New();
  sa1->SetMapper(sm1);
  vtkSmartPointer<vtkRenderer> r1 = vtkSmartPointer<vtkRenderer>::New();
  r1->AddActor(sa1);
  this->view1->GetRenderWindow()->AddRenderer(r1);
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
  s1_viewer = imageViewer.Get();
  s1->setMinimum(imageViewer->GetSliceMin());
  s1->setMaximum(imageViewer->GetSliceMax());
  s1->setValue(imageViewer->GetSlice());

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

  imageViewer->SetRenderWindow(view1->GetRenderWindow());
  view1->GetRenderWindow()->SetInteractor(renderWindowInteractor);

  // initialize rendering and interaction
  imageViewer->Render();
  imageViewer->GetRenderer()->ResetCamera();

  renderWindowInteractor->Start();
}

void MainWindow::pelvic_plane() { cout << "pelvic_plane() called" << endl; }

void MainWindow::orient_angle() { m_container_layout->removeWidget(view1); }

void MainWindow::sliderChanged1(int value) {
  if (s1_viewer) {
    s1_viewer->SetSlice(value);
    myVtkInteractorStyleImage* style =
        (myVtkInteractorStyleImage*)view1->GetRenderWindow()
            ->GetInteractor()
            ->GetInteractorStyle();
    if (style) {
      style->updateSliceMsg(value);
    }
  }
}


void MainWindow::updateSlider(int value) { s1->setValue(value); }