package main

import (
    "dagger.io/dagger"
    "dagger.io/dagger/core"
    "universe.dagger.io/alpine"
    "universe.dagger.io/bash"
    "universe.dagger.io/docker"
)

dagger.#Plan & {
    _cmakeBuildDirMount: "/src/dagger-cmake-build": {
        dest:     "/src/dagger-cmake-build"
        type:     "cache"
        contents: core.#CacheDir & {
            id: "iutest-cmake-builddir-cache"
        }
    }

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
        }
    }
    actions: {
        deps: docker.#Build & {
            steps: [
                alpine.#Build & {
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

        cmake: {
            run: bash.#Run & {
                input:   deps.output
                workdir: "/src/dagger-cmake-build"
                mounts: _cmakeBuildDirMount
                script: contents: #"""
                    cmake ../projects/cmake 
                """#
            }
			contents: core.#Subdir & {
				input: run.output.rootfs
				path:  "/src/dagger-cmake-build"
			}
        }

        cmake_build: bash.#Run & {
            input:   cmake.run.output
            workdir: "/src/dagger-cmake-build"
            mounts: _cmakeBuildDirMount
            script: contents: #"""
                cmake --build .
            """#
        }

        ctest: bash.#Run & {
            input:   cmake_build.output
            workdir: "/src/dagger-cmake-build"
            mounts: _cmakeBuildDirMount
            script: contents: #"""
                ctest -C Debug --output-on-failure
            """#
        }
    }
}
