cmake --version
rem cl.exe /?

mkdir build
cd build

cmake %~dp0/../projects/cmake
echo ==== finish cmake generate ====
ls
echo ==== start cmake build ====
cmake --build . -j 8
echo ==== finish cmake build ====
ctest -V --output-on-failure
echo ==== finish ctest ====
