cmake --version
cl.exe /?

mkdir -p tmp/build
cd tmp/build

cmake ../../projects/cmake
cmake --build .
ctest -V --output-on-failure
