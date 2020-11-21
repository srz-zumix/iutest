cmake --version
rem cl.exe /?

cmake %~dp0/../projects/cmake
cmake --build .
ctest -V --output-on-failure
