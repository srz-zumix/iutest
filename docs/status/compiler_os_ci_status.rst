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
| clang        | 8  |    c++2a |                                         |
+              +    +----------+-----------------------------------------+
|              |    |    c++17 | |TravisCI| |GitHubActions|              |
+              +    +----------+-----------------------------------------+
|              |    |    c++14 |                                         |
+              +    +----------+-----------------------------------------+
|              |    |    c++11 | |TravisCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |    c++98 | |TravisCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 |                                         |
+              +----+----------+-----------------------------------------+
|              | 7  |    c++17 | |CircleCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 | |CircleCI|                              |
+--------------+----+----------+-----------------------------------------+
| gcc          | 9  |    c++2a | |CirrusCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |    c++17 | |CirrusCI| |TravisCI|                   |
+              +    +----------+-----------------------------------------+
|              |    |    c++14 | |CirrusCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |    c++11 | |TravisCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |    c++98 | |TravisCI|                              |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 |                                         |
+              +----+----------+-----------------------------------------+
|              | 8  |    c++17 | |CircleCI| |Codefresh|                  |
+              +    +----------+-----------------------------------------+
|              |    |  gnu++17 | |CircleCI|                              |
+              +----+----------+-----------------------------------------+
|              | 7  |    c++17 | |Codefresh|                             |
+--------------+----+----------+-----------------------------------------+


OS
--

+--------------+-----------+------------------+
|OS                        | Status           |
+==============+===========+==================+
| Windows      |           | |AppVeyor|       |
+              +-----------+------------------+
|              | Cygwin    | |AppVeyor|       |
+              +-----------+------------------+
|              | MinGW     | |AppVeyor|       |
+--------------+-----------+------------------+
| Mac OS       |           | |CirrusCI|       |
+--------------+-----------+------------------+
| Linux        | Ubuntu    | |TravisCI|       |
+--------------+-----------+------------------+
| FreeBSD      |           | |CirrusCI|       |
+--------------+-----------+------------------+


.. |AppVeyor| image:: https://ci.appveyor.com/api/projects/status/2gdmgo8ce8m0iy0e/branch/master?svg=true&.svg
  :target: https://ci.appveyor.com/project/srz-zumix/iutest/branch/master

.. |AzurePipelines| image:: https://dev.azure.com/srz-zumix/iutest/_apis/build/status/srz-zumix.iutest?branchName=master&.svg
  :target: https://dev.azure.com/srz-zumix/iutest/_build/latest?definitionId=4

.. |Bitrise| image:: https://app.bitrise.io/app/6903498632e89465/status.svg?token=siumhVNY6p6lklSZF6xGNA&branch=master&.svg
  :target: https://app.bitrise.io/app/6903498632e89465

.. |Buddy| image:: https://app.buddy.works/zumixcpp/iutest/repository/branch/master/badge.svg?token=5e58135ab4831252209e7b1fe75bfe9de669b0dc7e95ed4316eebad2187d59a0&.svg
  :target: https://app.buddy.works/zumixcpp/iutest/repository/branch/master

.. |CircleCI| image:: https://circleci.com/gh/srz-zumix/iutest/tree/master.svg?style=svg&.svg
  :target: https://circleci.com/gh/srz-zumix/iutest/tree/master

.. |CirrusCI| image:: https://api.cirrus-ci.com/github/srz-zumix/iutest.svg?branch=master&.svg
  :target: https://cirrus-ci.com/github/srz-zumix/iutest/master

.. |Codefresh| image:: https://g.codefresh.io/api/badges/pipeline/srz-zumix/srz-zumix%2Fiutest%2Fiutest_unittest?branch=master&type=cf-1&.svg
  :target: https://g.codefresh.io/pipelines/iutest_unittest/builds?repoOwner=srz-zumix&repoName=iutest&serviceName=srz-zumix%2Fiutest&filter=trigger:build~Build;branch:master;pipeline:58a933be9d1bd40100495882~iutest_unittest

.. |Codeship| image:: https://codeship.com/projects/5bc87030-5b41-0133-6000-4242aa07dce3/status?branch=master&.svg
  :target: https://codeship.com/projects/110695

.. |GitHubActions| image:: https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions/badge.svg
  :target: https://github.com/srz-zumix/iutest/actions

.. |GitLabCI| image:: https://gitlab.com/srz-zumix/iutest-test/badges/master/pipeline.svg
  :target: https://gitlab.com/srz-zumix/iutest-test/commits/master

.. |INSPECODE| image:: https://inspecode.rocro.com/badges/github.com/srz-zumix/iutest/status?token=wt0KUnRUG1-Ul2mLrg8ComR1RznZV3VoXecBJHW0EIk&branch=master&.svg
  :target: https://inspecode.rocro.com/jobs/github.com/srz-zumix/iutest/latest?completed=true&branch=master

.. |Scrutinizer| image:: https://scrutinizer-ci.com/g/srz-zumix/iutest/badges/build.png?b=master&.svg
  :target: https://scrutinizer-ci.com/g/srz-zumix/iutest/build-status/master

.. |Semaphore| image:: https://semaphoreci.com/api/v1/srz_zumix/iutest/branches/master/badge.svg
  :target: https://semaphoreci.com/srz_zumix/iutest

.. |Shippable| image:: https://api.shippable.com/projects/541904d2ac22859af743f867/badge?branch=master&.svg
  :target: https://app.shippable.com/github/srz-zumix/iutest

.. |TravisCI| image:: https://travis-ci.com/srz-zumix/iutest.svg?branch=master&.svg
  :target: https://travis-ci.com/srz-zumix/iutest

.. |Wercker| image:: https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/s/master?.svg
  :target: https://app.wercker.com/project/bykey/d385156052aa4118a7f24affe4a8f851

.. |WerckerLarge| image:: https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/m/master?.svg
  :target: https://app.wercker.com/project/bykey/d385156052aa4118a7f24affe4a8f851


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
