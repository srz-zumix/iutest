cmake --version
rem cl.exe /?

mkdir build
cd build

cmake %~dp0/../projects/cmake
cmake --build .
ctest -V --output-on-failure
