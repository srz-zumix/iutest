package iutest

// 必要なパッケージをインポートする
// docker alpine image でビルドするのでそれらをインポート
import (
    "dagger.io/dagger"
    "dagger.io/dagger/core"
    "universe.dagger.io/alpine"
    "universe.dagger.io/bash"
    "universe.dagger.io/docker"
)

// 定数化
cmake_build_path: "/src/dagger-cmake-build"  

// パイプラインは Plan に書く
dagger.#Plan & {
    // cmake での out-of-source build のパスをキャッシュ
    _cmakeBuildDirMount: cmake_build_path: {
        dest:     "/src/dagger-cmake-build"
        type:     "cache"
        contents: core.#CacheDir & {
            id: "iutest-cmake-builddir-cache"
        }
    }

    // dagger の実行環境定義
    client: {
        filesystem: {
            "./": read: {
                contents: dagger.#FS
                exclude: [
                    "README.md",
                    "build",
                    "cmake-build",
                    "dagger-cmake-build",
                    ".ci",
                    ".circleci",
                    ".github",
                    ".idea",
                    ".semaphore",
                    ".vscode",
                ]
            }
            "./dagger-cmake-build": write: contents: actions.cmake.contents.output
            "./dagger-cmake-build/TestResults": write: contents: actions.ctest.contents.output
        }
    }
    actions: {
        // build alpine image
        deps: docker.#Build & {
            steps: [
                alpine.#Build & {
                    // iutest のビルドに必要な追加パッケージ
                    packages: {
                        bash: {}
                        make: {}
                        cmake: {}
                        "g++": {}
                        clang: {}
                    }
                },

                docker.#Copy & {
                    contents: client.filesystem."./".read.contents
                    dest:     "/src"
                },
            ]
        }

        // cmake generate project
        cmake: {
            run: bash.#Run & {
                input:   deps.output
                workdir: cmake_build_path
                mounts: _cmakeBuildDirMount
                script: contents: #"""
                    ls
                    cmake ../projects/cmake 
                """#
            }
            contents: core.#Subdir & {
                input: run.output.rootfs
                path: cmake_build_path
            }
        }

        cmake_build: {
            run: bash.#Run & {
                input:   cmake.run.output
                workdir: cmake_build_path
                mounts: _cmakeBuildDirMount
                script: contents: #"""
                    ls
                    cmake --build .
                """#
            }
            contents: core.#Subdir & {
                input: run.output.rootfs
                path: cmake_build_path
            }
        }

        ctest: {
            run: bash.#Run & {
                input:   cmake_build.run.output
                workdir: cmake_build_path
                mounts: _cmakeBuildDirMount
                env: {
                    IUTEST_OUTPUT: "xml:TestResults"
                }
                script: contents: #"""
                    ctest -C Debug --output-on-failure
                """#
            }
            contents: core.#Subdir & {
                input: run.output.rootfs
                path: cmake_build_path + "TestResults"
            }
        }
    }
}
