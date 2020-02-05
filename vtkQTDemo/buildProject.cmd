:: set default configuration 
@echo off
SET APP=%1
setlocal ENABLEEXTENSIONS
Setlocal EnableDelayedExpansion

:: create build folder , goinside build folder and fire cmake command with appropriate generator
mkdir build
pushd build
cmake .. -G "Visual Studio 16 2019"

:: Initialise visual studio environment 
set BUILD_PLATFORM=/p:Platform="x64"
set BUILD_ARCH=x64
set BUILD_SOLUTION="vtkQTDemo.sln"
echo Set VS Env
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

echo ========================================================================================
set buildDebug=0
set buildRelease=1

if %buildDebug% NEQ 0 (
    echo [33m
    call :buildConfiguration debug
)

if %buildRelease% NEQ 0 (
    echo [36m
    call :buildConfiguration release
)

:buildConfiguration
set BUILD_CONFIGURATION=%1
echo Running %BUILD_CONFIGURATION% build...
msbuild /t:build /p:Configuration=%BUILD_CONFIGURATION% %BUILD_PLATFORM% %BUILD_SOLUTION%

popd
call copydlls.cmd %BUILD_CONFIGURATION%