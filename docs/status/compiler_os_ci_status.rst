====================================
Compiler and OS tests status
====================================

Basic Tests
###########

Compiler
--------

+--------------+----+----------+-----------------------------------------+
|Compiler           | -std     | Status                                  |
+==============+====+==========+=========================================+
| clang        | 8  |    c++20 |                                         |
+              +    +----------+-----------------------------------------+
|              |    |    c++17 | |LinuxTests| |GitHubActions|            |
+              +    +----------+-----------------------------------------+
|              |    |    c++14 |                                         |
+              +    +----------+-----------------------------------------+
|              |    |    c++11 | |CompilerMatrix|                        |
+              +    +----------+-----------------------------------------+
|              |    |    c++98 | |CompilerMatrix|                        |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 |                                         |
+              +----+----------+-----------------------------------------+
|              | 7  |    c++17 | |CompilerMatrix|                        |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 | |CompilerMatrix|                        |
+--------------+----+----------+-----------------------------------------+
| gcc          | 9  |    c++20 | |LinuxTests|                            |
+              +    +----------+-----------------------------------------+
|              |    |    c++17 | |LinuxTests| |CompilerMatrix|           |
+              +    +----------+-----------------------------------------+
|              |    |    c++14 | |LinuxTests|                            |
+              +    +----------+-----------------------------------------+
|              |    |    c++11 | |CompilerMatrix|                        |
+              +    +----------+-----------------------------------------+
|              |    |    c++98 | |CompilerMatrix|                        |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 |                                         |
+              +----+----------+-----------------------------------------+
|              | 8  |    c++17 | |CompilerMatrix| |Benchmark|            |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 | |CompilerMatrix|                        |
+              +----+----------+-----------------------------------------+
|              | 7  |    c++17 | |CompilerMatrix|                        |
+--------------+----+----------+-----------------------------------------+


OS
--

+--------------+-----------+------------------+
|OS                        | Status           |
+==============+===========+==================+
| Windows      |           | |WindowsTests|   |
+              +-----------+------------------+
|              | Cygwin    | |WindowsTests|   |
+              +-----------+------------------+
|              | MinGW     | |WindowsTests|   |
+--------------+-----------+------------------+
| Mac OS       |           | |AppleTests|     |
+--------------+-----------+------------------+
| Linux        | Ubuntu    | |LinuxTests|     |
+--------------+-----------+------------------+
| FreeBSD      |           | |FreeBSDTests|   |
+--------------+-----------+------------------+


.. |GitHubActions| image:: https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions/badge.svg
  :target: https://github.com/srz-zumix/iutest/actions

.. |LinuxTests| image:: https://github.com/srz-zumix/iutest/actions/workflows/linux.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/linux.yml

.. |WindowsTests| image:: https://github.com/srz-zumix/iutest/actions/workflows/windows.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/windows.yml

.. |AppleTests| image:: https://github.com/srz-zumix/iutest/actions/workflows/apple.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/apple.yml

.. |AndroidBuild| image:: https://github.com/srz-zumix/iutest/actions/workflows/android.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/android.yml

.. |FreeBSDTests| image:: https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml

.. |CompilerMatrix| image:: https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml

.. |ConfigTests| image:: https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml

.. |Benchmark| image:: https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml/badge.svg?branch=master
  :target: https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml

.. |GitLabCI| image:: https://gitlab.com/srz-zumix/iutest-test/badges/master/pipeline.svg
  :target: https://gitlab.com/srz-zumix/iutest-test/commits/master


.. |Codacy| image:: https://api.codacy.com/project/badge/Grade/e6407b63c9c844d080ed71c7707bded9?branch=master&.svg
  :target: https://www.codacy.com/app/srz-zumix/iutest?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=srz-zumix/iutest&amp;utm_campaign=Badge_Grade

.. |CoverityScan| image:: https://scan.coverity.com/projects/1316/badge.svg
  :target: https://scan.coverity.com/projects/srz-zumix-iutest

.. |GuardRails| image:: https://badges.guardrails.io/srz-zumix/iutest.svg?token=fe1bb5ca5f743800d26e4d2b7282c5b316df83c0b228048f4192510bdd7280f0&.svg
  :target: https://dashboard.guardrails.io/default/gh/srz-zumix/iutest

.. |INSPECODEScore| image:: https://inspecode.rocro.com/badges/github.com/srz-zumix/iutest/report?token=wt0KUnRUG1-Ul2mLrg8ComR1RznZV3VoXecBJHW0EIk&branch=master&.svg
  :target: https://inspecode.rocro.com/reports/github.com/srz-zumix/iutest/branch/master/summary

.. |ScrutinizerScore| image:: https://scrutinizer-ci.com/g/srz-zumix/iutest/badges/quality-score.png?b=master&.svg
  :target: https://scrutinizer-ci.com/g/srz-zumix/iutest/build-status/master



.. |Codecov| image:: https://codecov.io/gh/srz-zumix/iutest/branch/master/graph/badge.svg?height=50&.svg
  :target: https://codecov.io/gh/srz-zumix/iutest

.. |CodecovGraph| image:: https://codecov.io/gh/srz-zumix/iutest/branch/master/graphs/icicle.svg
  :target: https://codecov.io/gh/srz-zumix/iutest
  :height: 300px

.. |CodecovGraphSunburst| image:: https://codecov.io/gh/srz-zumix/iutest/branch/master/graphs/sunburst.svg
  :target: https://codecov.io/gh/srz-zumix/iutest
  :height: 800px

.. |Coveralls| image:: https://coveralls.io/repos/github/srz-zumix/iutest/badge.svg?branch=master&.svg
  :target: https://coveralls.io/github/srz-zumix/iutest?branch=master
