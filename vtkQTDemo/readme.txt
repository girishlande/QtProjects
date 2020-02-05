This project shows how to use vtk along with QT widgets to create visualization application. 

PRECONDITION
===================
It makes use of cmake. You should have that installed. 
Using cmake you can build vtk and qt so their dlls are compatible with common generator. 
It assumes that you already have vtk and qt installed in your system. 
You can download and build qt using your compiler(generator).

Now try to build this project.

1. Open cmakeLists.txt and make sure that 
VTK_DIR is set to correct path 

2.run buildProject.cmd
In ideal env this script should do everything. that is 
> create build folder
> use cmake to populate build folder with correct project file. 
> build project file based on the debug / release setting inside script. 

Please check paths inside copydlls.cmd whether they are pointing to correct paths. 

This project has capability to open dicom file for viewing
also it can render stl/obj files 
