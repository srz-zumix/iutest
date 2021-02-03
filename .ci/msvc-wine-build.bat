cmake --version
rem cl.exe /?

mkdir build
cd build

cmake %~dp0/../projects/cmake
echo ==== finish cmake generate ====
cmake --build .
echo ==== finish cmake build ====
ctest -V --output-on-failure
echo ==== finish ctest ====
