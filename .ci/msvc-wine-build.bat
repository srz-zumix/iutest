cmake --version
rem cl.exe /?

mkdir build
cd build

cmake ../projects/cmake
cmake --build .
ctest -V --output-on-failure
