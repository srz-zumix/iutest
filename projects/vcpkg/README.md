# vcpkg port for iutest

`ports/iutest` is a vcpkg port for iutest.
Tests and samples are not built, and a static library (`iutest::iutest`, `iutest::iutest_main`) is built for both debug and release.

## Use as an overlay port

```sh
vcpkg install iutest --overlay-ports=<iutest>/projects/vcpkg/ports
```

When used as an overlay port inside this repository, the port builds the local source tree.
vcpkg does not track changes of the local source tree, so use `--no-binarycaching` (or `-DVCPKG_INSTALL_OPTIONS=--no-binarycaching`) to rebuild it after modifying the sources.

```cmake
find_package(iutest CONFIG REQUIRED)
target_link_libraries(main PRIVATE iutest::iutest)
# or, to use the main() provided by iutest
target_link_libraries(main PRIVATE iutest::iutest_main)
```

`test` is a manifest-mode project that uses this port:

```sh
cmake -S projects/vcpkg/test -B build -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake --build build
ctest --test-dir build
```

## Submit to microsoft/vcpkg

After a release tag is created:

1. Update `version` in `ports/iutest/vcpkg.json`.
2. Remove the local source tree branch from `ports/iutest/portfile.cmake` and set `SHA512` of `vcpkg_from_github` to the hash of the release tarball.
3. Copy `ports/iutest` to `ports/iutest` of microsoft/vcpkg, then run `vcpkg x-add-version iutest`.
