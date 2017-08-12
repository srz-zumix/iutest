[![Travis-CI Build Status](https://travis-ci.org/srz-zumix/iutest.svg?branch=master)](https://travis-ci.org/srz-zumix/iutest)
[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/2gdmgo8ce8m0iy0e/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest/branch/master)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/1316/badge.svg)](https://scan.coverity.com/projects/srz-zumix-iutest)
[![Codeship Status for srz-zumix/iutest](https://codeship.com/projects/5bc87030-5b41-0133-6000-4242aa07dce3/status?branch=master)](https://codeship.com/projects/110695)  
[![wercker status](https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/s/master "wercker status")](https://app.wercker.com/project/bykey/d385156052aa4118a7f24affe4a8f851)
[![Shippable Run Status](https://api.shippable.com/projects/541904d2ac22859af743f867/badge?branch=master)](https://app.shippable.com/github/srz-zumix/iutest)
[![Semaphore Build Status](https://semaphoreci.com/api/v1/srz_zumix/iutest/branches/master/badge.svg)](https://semaphoreci.com/srz_zumix/iutest)
[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=master&pipelineName=iutest&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:master;service:58a933be9d1bd40100495882~iutest)
[![Bitrise Build Status](https://www.bitrise.io/app/a1525fe176d85f53/status.svg?token=C67enKOhen9rjw_Cl37ihA&branch=master)](https://www.bitrise.io/app/a1525fe176d85f53)
[![CircleCI](https://circleci.com/gh/srz-zumix/iutest/tree/master.svg?style=svg)](https://circleci.com/gh/srz-zumix/iutest/tree/master)
[![Scrutinizer Build Status](https://scrutinizer-ci.com/g/srz-zumix/iutest/badges/build.png?b=master)](https://scrutinizer-ci.com/g/srz-zumix/iutest/build-status/master)  
[![Coverage Status](https://coveralls.io/repos/github/srz-zumix/iutest/badge.svg?branch=master)](https://coveralls.io/github/srz-zumix/iutest?branch=master)
[![codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graph/badge.svg)](https://codecov.io/gh/srz-zumix/iutest)  
[![New(3-clause) BSD License](https://img.shields.io/badge/license-New_BSD-blue.svg)](http://opensource.org/licenses/BSD-3-Clause)
[![NuGet version](https://badge.fury.io/nu/iutest.svg)](https://badge.fury.io/nu/iutest)  

iutest
==========
iutest - iris unit test framework

Welcome to the iutest
--------------------------------------------------
iutest is framework for writing C++ tests.

Features
--------------------------------------------------

* An [XUnit](https://en.wikipedia.org/wiki/XUnit) test framework.
* Include only.
* Test discovery.
* XML/JUnit test report generation.
* Assertions.
   + A rich set of assertions.
   + User-defined assertions.
   + Power-assert (expression-assert).
   + Matchers.
   + Fatal and non-fatal, warning, assume failures.
* Value-parameterized tests.
* Type-parameterized tests.
* Advanced parameter generation.
   + Pairwise parameter.
   + CSV parameter.
   + Any parameter.
   + Random parameter.
   + Multiple parameters can be concatenated. 
* Test packages (grouping).
* Skip test.
* Private member test.
* Janaese test name (C++03). 
* Various options for running the tests.
* Compatible with Google Test.

Platforms
--------------------------------------------------

* Windows
* Linux
* Mac OS X
* Cygwin
* MinGW

Documentation
--------------------------------------------------

* in repository  
doc/index.html  
* online document  
[least released version(OSDN)](http://iutest.osdn.jp/doc/index.html)  
[github master branch (gh-pages)](http://srz-zumix.github.io/iutest/)  

Project page
--------------------------------------------------

* [OSDN Project page](http://iutest.osdn.jp/)  
* [Github](https://github.com/srz-zumix/iutest)  

Support
--------------------------------------------------

* Use [Github issues](https://github.com/srz-zumix/iutest/issues) to report bugs and feature requests.
* Ask questions at the twitter ([@srz_zumix](https://twitter.com/srz_zumix))

Tools
--------------------------------------------------

* fused  
make fused-src.
* twilio  
notifies the test results using twilio
* wandbox  
tools to make use of the iutest in [wandbox](https://wandbox.org/)

Tests
--------------------------------------------------

|CI|master|develop|Tests|
|:--|:--|:--|:--|
|Travis CI|[![Travis-CI Build Status](https://travis-ci.org/srz-zumix/iutest.svg?branch=master)](https://travis-ci.org/srz-zumix/iutest)|[![Travis-CI Build Status](https://travis-ci.org/srz-zumix/iutest.svg?branch=develop)](https://travis-ci.org/srz-zumix/iutest)|Basic tests, Google test compatibility, Coverage, Coverity-scan, Wine + MinGW|
|AppVeyor|[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/2gdmgo8ce8m0iy0e/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest/branch/master)|[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/2gdmgo8ce8m0iy0e/branch/develop?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest/branch/develop)|Windows, NuGet|
||[![AppVeyor Build sample status](https://ci.appveyor.com/api/projects/status/906w23swuocl9fex/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-8dhoe/branch/master)|[![AppVeyor Build sample status](https://ci.appveyor.com/api/projects/status/906w23swuocl9fex/branch/develop?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-8dhoe/branch/develop)|Sample build|
||[![AppVeyor Build PREFAST status](https://ci.appveyor.com/api/projects/status/0w0wuhc58kre178q/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-xsqun/branch/master)|[![AppVeyor Build PREFAST status](https://ci.appveyor.com/api/projects/status/0w0wuhc58kre178q/branch/develop?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-xsqun/branch/develop)|Visual Studio PREFAST (Code Analysis)|
||[![AppVeyor Build cygwin status](https://ci.appveyor.com/api/projects/status/erhkn5rer20jmdbq/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-xlae4/branch/master)|[![AppVeyor Build cygwin status](https://ci.appveyor.com/api/projects/status/erhkn5rer20jmdbq/branch/develop?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-xlae4/branch/develop)|Cygwin|
||[![AooVeyor Build mingw status](https://ci.appveyor.com/api/projects/status/xr7yvj6swxutluu4/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-rbhes/branch/master)|[![AppVeyor Build mingw status](https://ci.appveyor.com/api/projects/status/xr7yvj6swxutluu4/branch/develop?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-rbhes/branch/develop)|MinGW|
|Wercker|[![wercker status](https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/s/master "wercker status")](https://app.wercker.com/project/byKey/d385156052aa4118a7f24affe4a8f851)|[![wercker status](https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/s/develop "wercker status")](https://app.wercker.com/project/byKey/d385156052aa4118a7f24affe4a8f851)|Syntax tests for compiler each version|
|Shippable|[![Shippable Run Status](https://api.shippable.com/projects/541904d2ac22859af743f867/badge?branch=master)](https://app.shippable.com/github/srz-zumix/iutest)|[![Run Status](https://api.shippable.com/projects/541904d2ac22859af743f867/badge?branch=develop)](https://app.shippable.com/github/srz-zumix/iutest)|Syntax tests for compiler each version (c++98)|
|Codeship|[ ![Codeship Status for srz-zumix/iutest](https://app.codeship.com/projects/5bc87030-5b41-0133-6000-4242aa07dce3/status?branch=master)](https://app.codeship.com/projects/110695)|[ ![Codeship Status for srz-zumix/iutest](https://app.codeship.com/projects/5bc87030-5b41-0133-6000-4242aa07dce3/status?branch=develop)](https://app.codeship.com/projects/110695)|Cpplint, Update documents|
|Semaphore|[![Semaphore Build Status](https://semaphoreci.com/api/v1/srz_zumix/iutest/branches/master/badge.svg)](https://semaphoreci.com/srz_zumix/iutest)|[![Semaphore Build Status](https://semaphoreci.com/api/v1/srz_zumix/iutest/branches/develop/badge.svg)](https://semaphoreci.com/srz_zumix/iutest)|Scan-build|
|Codefresh|[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=master&pipelineName=iutest&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:master;service:58a933be9d1bd40100495882~iutest)|[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=develop&pipelineName=iutest&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:develop;service:58a933be9d1bd40100495882~iutest)|Google Test compatibility|
||[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=master&pipelineName=iutest_gmock&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:master;service:5988fd7df61a9b000176f0a3~iutest_gmock)|[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=develop&pipelineName=iutest_gmock&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:develop;service:5988fd7df61a9b000176f0a3~iutest_gmock)|Google Mock compatibility|
|Bitrise|[![Bitrise Build Status](https://www.bitrise.io/app/a1525fe176d85f53/status.svg?token=C67enKOhen9rjw_Cl37ihA&branch=master)](https://www.bitrise.io/app/a1525fe176d85f53)|[![Bitrise Build Status](https://www.bitrise.io/app/a1525fe176d85f53/status.svg?token=C67enKOhen9rjw_Cl37ihA&branch=develop)](https://www.bitrise.io/app/a1525fe176d85f53)|iOS|
||[![Build Status](https://www.bitrise.io/app/aefa67ee488094b1/status.svg?token=aDrRgkZEmNFmsDjBM9fWTw&branch=master)](https://www.bitrise.io/app/aefa67ee488094b1)|[![Build Status](https://www.bitrise.io/app/aefa67ee488094b1/status.svg?token=aDrRgkZEmNFmsDjBM9fWTw&branch=develop)](https://www.bitrise.io/app/aefa67ee488094b1)|Android|
|CircleCI|[![CircleCI](https://circleci.com/gh/srz-zumix/iutest/tree/master.svg?style=svg)](https://circleci.com/gh/srz-zumix/iutest/tree/master)|[![CircleCI](https://circleci.com/gh/srz-zumix/iutest/tree/develop.svg?style=svg)](https://circleci.com/gh/srz-zumix/iutest/tree/develop)|Optimize options test|
|Scrutinizer|[![Scrutinizer Build Status](https://scrutinizer-ci.com/g/srz-zumix/iutest/badges/build.png?b=master)](https://scrutinizer-ci.com/g/srz-zumix/iutest/build-status/master)|[![Scrutinizer Build Status](https://scrutinizer-ci.com/g/srz-zumix/iutest/badges/build.png?b=develop)](https://scrutinizer-ci.com/g/srz-zumix/iutest/build-status/develop)|iuwandbox tests|

Coverage
--------------------------------------------------

[![Coverage Status](https://coveralls.io/repos/github/srz-zumix/iutest/badge.svg?branch=master)](https://coveralls.io/github/srz-zumix/iutest?branch=master)  


[![codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graph/badge.svg)](https://codecov.io/gh/srz-zumix/iutest)  
[![codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graphs/icicle.svg)](https://codecov.io/gh/srz-zumix/iutest)  


License
--------------------------------------------------

    Copyright (c) 2011-2017, Takazumi Shirayanagi,
    All rights reserved.

    This software is released under the New(3-clause) BSD License, see LICENSE
