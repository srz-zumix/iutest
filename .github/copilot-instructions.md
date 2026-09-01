# Copilot Instructions for iutest

iutest ("iris unit test") is a **header-only C++ XUnit testing framework** compatible with
Google Test. The shipped product is the `include/` tree — there is no library to build for
consumers; users just `#include "iutest.hpp"`. Everything else in the repo (`test/`,
`samples/`, `projects/`, `tools/`) exists to validate and package those headers.

## Architecture

- **`include/`** is the deliverable. Public entry point is `include/iutest.hpp`, which pulls
  in the top-level `iutest_*.hpp` headers (core, assertions, param/typed tests, matchers, etc.).
- **Header-only implementation split**: declarations live in `include/*.hpp` and
  `include/internal/*.hpp`; definitions live in `include/impl/*.ipp`. A `.hpp` conditionally
  includes its matching `.ipp` (e.g. `iutest_core.hpp` → `impl/iutest_core.ipp`) guarded by
  `// IWYU pragma: export`. When adding implementation, respect this `.hpp`/`.ipp` pairing
  rather than inlining everything.
- **`include/internal/`** holds portability/compiler-abstraction layers
  (`iutest_compiler.hpp`, `iutest_stdlib.hpp`, `iutest_port.hpp`, `iutest_pp.hpp`, etc.).
  `include/iutest_config.hpp` is the central feature-macro configuration surface.
- **Google Test compatibility** lives in `include/gtest/`. Building a test with
  `-DIUTEST_USE_GTEST` (or the `IUTEST_USE_GTEST` macro) switches the same test source to run
  against real Google Test, which is how gtest-compat is verified. Keep public macros/APIs
  aligned with their gtest counterparts.
- **`fused-src/`** is generated: `make fused` (delegates to `tools/fused`) amalgamates the
  whole `include/` tree into a single header. Do not hand-edit `fused-src/`.

## Build / test / lint

Tests live in `test/`. There are two makefiles: **`GNUmakefile`** for GNU make (Linux/macOS/
Cygwin/MinGW) and **`Makefile`** for Windows `nmake`. GNU make is used for local dev.

- Full suite: `make -C test test` (or `make test` from repo root).
- **Single test target**: each `*_tests.cpp` is its own executable. Build + run one with
  `make -C test run_<name>` — e.g. `make -C test run_basic_tests` builds and runs
  `basic_tests.cpp`. Use `make -C test <name>_build` to build without running.
- Select the C++ standard with `STDFLAG` and optimization with `OPTIMIZE`
  (e.g. `make -C test run_basic_tests STDFLAG=-std=c++17`).
- gtest-compat run: `make -C test gtest-version`.
- Emit XML/JUnit reports by setting `OUTPUTXML=1` or `OUTPUTXML=junit`.

Linters (also enforced in CI via `.github/workflows/lint.yml`):

- **cpplint** — config in `CPPLINT.cfg` (excludes `fused-src`, dotfiles, `docs`).
- **clang-tidy** — `.clang-tidy` (note the disabled checks; don't re-enable without reason).
- **EditorConfig** — `.editorconfig` is strict and enforced. Key rules for C++ sources
  (`*.{cpp,hpp,ipp,inl}`): **UTF-8 with BOM**, 4-space indent, trailing whitespace trimmed,
  final newline. Makefiles/`*.mk`/`*.in` use **tabs** and LF. `*.{bat,cmd}` use CRLF.

## Conventions

- **File header comment**: every C++ file starts with the Doxygen banner block seen across
  `include/` and `test/` — `@file`, `@brief`, `@author t.shirayanagi`, and the BSD copyright
  `@par`. Match this format when creating new headers/tests.
- **Include guards** are long and unique (e.g. `INCG_IRIS_IUTEST_VER_HPP_D65CB7A7_...`); an
  `iutest_incg_test.py` check enforces guard style. Follow the existing pattern.
- **Feature macro naming**: `IUTEST_HAS_*` macros are always defined (`0`/`1`) and are tested
  by value (`#if IUTEST_HAS_XXX`). `IUTEST_NO_*` macros are **left undefined by default** —
  never add a `#define IUTEST_NO_XXX 0` fallback. Test them with
  `#if defined(IUTEST_NO_XXX)` / `#ifdef` / `#ifndef` so that `-Wundef` stays clean.
- **Tests** use `IUTEST(TestSuite, TestName)` (the iutest analogue of gtest's `TEST`) and
  `IUTEST_ASSERT_*` / `IUTEST_EXPECT_*` macros. Every new public macro or API change must have
  a corresponding `*_tests.cpp` added to `test/` and wired into the makefile target lists in
  `test/CommonMakefile.in`, unless the change is documentation-only.
- **Version** is defined in `include/iutest_ver.hpp` (`IUTEST_VER` plus MAJOR/MINOR/MICRO/
  REVISION). `iutest_ver.hpp` intentionally uses 2-space indent (see `.editorconfig`).
- **Deprecating/removing public API**: never delete a public macro/API outright. Keep the old
  name as an alias gated by an `IUTEST_HAS_*` toggle that defaults to `1`
  (e.g. `IUTEST_HAS_TESTCASE` for the legacy TestCase API), tag it with a Doxygen
  `@deprecated` comment naming the replacement, and mark deprecated symbols with
  `IUTEST_ATTRIBUTE_DEPRECATED_` where applicable. Keep the gtest-compatible spelling working
  as long as Google Test still provides it.
- **Compiler/std portability is a hard requirement**: code must compile from VC++6 / GCC 3.4 /
  Clang 3.1 upward and across C++03→modern standards. Guard newer features behind the macros
  in `iutest_config.hpp` / `internal/iutest_compiler.hpp` rather than assuming a modern toolchain.
- **CI signal**: per `CONTRIBUTING.md`, the authoritative CI is **GitHub Actions**; other CI
  badges can be ignored. Target `develop`/feature branches for PRs.
