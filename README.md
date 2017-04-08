[![Travis-CI Build Status](https://travis-ci.org/srz-zumix/iutest.png?branch=master)](https://travis-ci.org/srz-zumix/iutest)
[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/2gdmgo8ce8m0iy0e/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest/branch/master)
[![Coverage Status](https://coveralls.io/repos/srz-zumix/iutest/badge.png?branch=master)](https://coveralls.io/r/srz-zumix/iutest?branch=master)
[![codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graph/badge.svg)](https://codecov.io/gh/srz-zumix/iutest)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/1316/badge.svg)](https://scan.coverity.com/projects/srz-zumix-iutest)
[ ![Codeship Status for srz-zumix/iutest](https://codeship.com/projects/5bc87030-5b41-0133-6000-4242aa07dce3/status?branch=master)](https://codeship.com/projects/110695)  
[![Snap-CI Build Status](https://snap-ci.com/srz-zumix/iutest/branch/master/build_image)](https://snap-ci.com/srz-zumix/iutest/branch/master)
[![wercker status](https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/s/master "wercker status")](https://app.wercker.com/project/bykey/d385156052aa4118a7f24affe4a8f851)
[![Shippable Build Status](https://api.shippable.com/projects/541904d2ac22859af743f867/badge?branchName=master)](https://app.shippable.com/projects/541904d2ac22859af743f867/builds/latest)
[![Semaphore Build Status](https://semaphoreci.com/api/v1/srz_zumix/iutest/branches/master/badge.svg)](https://semaphoreci.com/srz_zumix/iutest)
[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=master&pipelineName=iutest&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:master;service:58a933be9d1bd40100495882~iutest)
[![Build Status](https://www.bitrise.io/app/a1525fe176d85f53.svg?token=C67enKOhen9rjw_Cl37ihA&branch=master)](https://www.bitrise.io/app/a1525fe176d85f53)
[![Circle CI](https://circleci.com/gh/srz-zumix/iutest.svg?style=svg)](https://circleci.com/gh/srz-zumix/iutest)
[![Magnum CI](https://magnum-ci.com/status/9175310cbf4594b8755634347186515a.png)](https://magnum-ci.com/public/ad50f16d4e6b5c8a578a/builds)  
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
* Google Native Client

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
* Ask questions at the twitter ([]@srz_zumix](https://twitter.com/srz_zumix))

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

|CI|Tests|
|:--|:--|
|[![Travis-CI Build Status](https://travis-ci.org/srz-zumix/iutest.png?branch=master)](https://travis-ci.org/srz-zumix)|Basic tests, Google test compatibility, Coverage, Coverity-scan, Wine + MinGW|
|[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/2gdmgo8ce8m0iy0e/branch/master?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest/branch/master)|Windows, NuGet|
|[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/906w23swuocl9fex?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-8dhoe)|Sample build|
|[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/0w0wuhc58kre178q?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-xsqun)|Visual Studio PREFAST (Code Analysis)|
|[![Build status](https://ci.appveyor.com/api/projects/status/erhkn5rer20jmdbq?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-xlae4)|Cygwin|
|[![AppVeyor Build status](https://ci.appveyor.com/api/projects/status/xr7yvj6swxutluu4?svg=true)](https://ci.appveyor.com/project/srz-zumix/iutest-rbhes)|MinGW|
|[![Snap-CI Build Status](https://snap-ci.com/srz-zumix/iutest/branch/master/build_image)](https://snap-ci.com/srz-zumix/iutest/branch/master)|Configurations tests, CentOS, Android|
|[![wercker status](https://app.wercker.com/status/d385156052aa4118a7f24affe4a8f851/s/master "wercker status")](https://app.wercker.com/project/bykey/d385156052aa4118a7f24affe4a8f851)|Syntax tests for compiler each version|
|[![Shippable Build Status](https://api.shippable.com/projects/541904d2ac22859af743f867/badge?branchName=master)](https://app.shippable.com/projects/541904d2ac22859af743f867/builds/latest)|Syntax tests for compiler each version (c++98)|
|[![Codeship Status for srz-zumix/iutest](https://codeship.com/projects/5bc87030-5b41-0133-6000-4242aa07dce3/status?branch=master)](https://codeship.com/projects/110695)|Cpplint, Update documents|
|[![Semaphore Build Status](https://semaphoreci.com/api/v1/srz_zumix/iutest/branches/master/badge.svg)](https://semaphoreci.com/srz_zumix/iutest)|Scan-build|
|[![Codefresh build status]( https://g.codefresh.io/api/badges/build?repoOwner=srz-zumix&repoName=iutest&branch=master&pipelineName=iutest&accountName=srz-zumix&type=cf-1)]( https://g.codefresh.io/repositories/srz-zumix/iutest/builds?filter=trigger:build;branch:master;service:58a933be9d1bd40100495882~iutest)|Google Test/Google Mock compatibility|
|[![Build Status](https://www.bitrise.io/app/a1525fe176d85f53.svg?token=C67enKOhen9rjw_Cl37ihA&branch=master)](https://www.bitrise.io/app/a1525fe176d85f53)|iOS|
|[![Circle CI](https://circleci.com/gh/srz-zumix/iutest.svg?style=svg)](https://circleci.com/gh/srz-zumix/iutest)|Optimize options test|
|[![Magnum CI](https://magnum-ci.com/status/9175310cbf4594b8755634347186515a.png)](https://magnum-ci.com/public/ad50f16d4e6b5c8a578a/builds)|Google Native Client|

License
--------------------------------------------------

    Copyright (c) 2011-2017, Takazumi Shirayanagi,
    All rights reserved.

    This software is released under the New(3-clause) BSD License, see LICENSE
