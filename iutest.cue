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

iutest_root_dir: "/iutest"
test_result_dir: "/iutest/TestResults"
cmake_build_path_name: "dagger-cmake-build"

// パイプラインは Plan に書く
dagger.#Plan & {
    // cmake での out-of-source build のパスをマウント
    _cmakeBuildDirMount: {
        mounts: (cmake_build_path_name): {
            dest: "/\(cmake_build_path_name)"
            type: "cache"
            contents: core.#CacheDir & {
                id: "iutest-cmake-builddir-cache"
            }
        }
        workdir: mounts[(cmake_build_path_name)].dest
        env: {
            IUTEST_ROOT_DIR: (iutest_root_dir)
            IUTEST_OUTPUT_DIR: (test_result_dir)
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
                    (cmake_build_path_name),
                    ".ci",
                    ".circleci",
                    ".git",
                    ".github",
                    ".idea",
                    ".semaphore",
                    ".vscode",
                    "cue.mod",
                ]
            }
            "./\(cmake_build_path_name)/cmake-build": write: contents: actions.cmake.contents.output
            "./\(cmake_build_path_name)/TestResults": write: contents: actions.ctest.contents.output
        }
    }
    actions: {
        // build alpine image
        deps: docker.#Build & {
            steps: [
                alpine.#Build & {
                    // iutest のビルドに必要な追加パッケージ
                    packages: {
                        bash: _
                        make: _
                        cmake: _
                        "g++": _
                        clang: _
                    }
                },
                docker.#Copy & {
                    contents: client.filesystem."./".read.contents
                    dest:     (iutest_root_dir)
                },
            ]
        }

        // cmake generate project
        cmake: {
            run: bash.#Run & {
                _cmakeBuildDirMount

                input:  deps.output
                script: contents: #"""
                    cmake "${IUTEST_ROOT_DIR}/projects/cmake" -DTEST_OUTPUT_DIR=${IUTEST_OUTPUT_DIR}
                """#
            }
            contents: core.#Subdir & {
                input: run.output.rootfs
                path: _cmakeBuildDirMount.workdir
            }
        }

        // cmake build
        cmake_build: {
            run: bash.#Run & {
                _cmakeBuildDirMount

                input:  cmake.run.output
                script: contents: #"""
                    cmake --build .
                """#
            }
            contents: core.#Subdir & {
                input: run.output.rootfs
                path: _cmakeBuildDirMount.workdir
            }
        }

        // ctest
        ctest: {
            run: bash.#Run & {
                _cmakeBuildDirMount

                input: cmake_build.run.output
                script: contents: #"""
                    rm -rf "${IUTEST_OUTPUT_DIR}"
                    mkdir -p "${IUTEST_OUTPUT_DIR}"
                    ctest -C Debug --output-on-failure || :
                """#
                exit: 0
            }

            test_result: bash.#Run & {
                input:   run.output
                workdir: (test_result_dir)
                script: contents: #"""
                    ls
                """#
            }

            contents: core.#Subdir & {
                input: test_result.output.rootfs
                path: (test_result_dir)
            }
        }
    }
}
