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

// cmake_build_dir は mounts して cache する
// テスト結果を client に書き出したいので mounts path 以外にテスト結果を出力する
// mounts 配下の path を client に write する方法は不明
iutest_root_dir: "/iutest"
test_result_dir: "/iutest/TestResults"
cmake_build_dir: "/dagger-cmake-build"

// パイプラインは Plan に書く
dagger.#Plan & {
    // 共通設定をまとめておく
    _cmakeBuildDirConfig: {    
        // cmake での out-of-source build のパスをマウント
        mounts: (cmake_build_dir): {
            dest: (cmake_build_dir)
            type: "cache"
            contents: core.#CacheDir & {
                id: "iutest-cmake-builddir-cache"
            }
        }
        // 作業ディレクトリを out-of-source build のパスにセット
        workdir: mounts[(cmake_build_dir)].dest
        // 必要な環境変数をセット
        env: {
            // string は () で囲んで展開する
            IUTEST_ROOT_DIR: (iutest_root_dir)
            // 文字列の中で変数展開する場合は ( をエスケープする
            IUTEST_OUTPUT_DIR: "\(test_result_dir)"
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
                    "dagger-out",
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
            // ctest の結果を client に書き出し
            "./dagger-out/TestResults": write: contents: actions.ctest.contents.output
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
                // client から container に copy
                docker.#Copy & {
                    contents: client.filesystem."./".read.contents
                    dest:     (iutest_root_dir)
                },
            ]
        }

        // cmake generate project
        cmake: bash.#Run & {
            _cmakeBuildDirConfig

            input:  deps.output
            script: contents: """
                cmake "${IUTEST_ROOT_DIR}/projects/cmake" -DTEST_OUTPUT_DIR=${IUTEST_OUTPUT_DIR}
            """
        }

        // cmake build
        cmake_build: bash.#Run & {
            _cmakeBuildDirConfig

            input:  cmake.output
            script: contents: """
                cmake --build . -j 4
            """
        }

        // ctest
        ctest: {
            run: bash.#Run & {
                _cmakeBuildDirConfig

                input: cmake_build.output
                script: contents: """
                    rm -rf "${IUTEST_OUTPUT_DIR}"
                    mkdir -p "${IUTEST_OUTPUT_DIR}"
                    ctest -C Debug --output-on-failure || :
                """
                exit: 0
            }

            test_result: bash.#Run & {
                input:   run.output
                workdir: (test_result_dir)
                script: contents: """
                    ls
                """
            }

            contents: core.#Subdir & {
                input: test_result.output.rootfs
                path: (test_result_dir)
            }
        }
    }
}
