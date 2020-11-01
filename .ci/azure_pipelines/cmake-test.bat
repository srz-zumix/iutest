@echo off

C:\x64.bat

dir

mkdir build
cd build

cmake ../project/cmake
cmake --build .
ctest -V --output-on-failure

exit /b 0
