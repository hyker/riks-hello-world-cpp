@echo off
setlocal enableextensions enabledelayedexpansion

if exist build rd /s /q build
md build
cd build

call cl^
    -I..\..\riks-cpp\build\include^
    ..\main.cpp^
    ..\..\riks-cpp\build\lib\riks.lib^
    /W4 /O1 /EHsc^
    /std:c++latest

copy ..\res\default.config
copy ..\res\root_certificate.pem

copy ..\..\riks-cpp\build\bin\riks.dll

echo.
echo "Build complete. Running hello world..."
echo.

call main

endlocal
