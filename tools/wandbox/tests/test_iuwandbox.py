#!/usr/bin/env python
#
# test_iuwandbox.py
#

from __future__ import print_function

import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/../../fused')
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/../../wandbox')

try:
    import unittest2 as unittest
except:
    import unittest
import iuwandbox
import fused_iutest_files
import shutil

try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO

root = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../../../')
fused_src = root + '/fused-src'
test_src = root + '/test/syntax_tests.cpp'
test_opt_default = ['--encoding', 'utf-8-sig']
test_opt_nomain = test_opt_default
test_opt = ['-f"-DIUTEST_USE_MAIN"']
test_opt.extend(test_opt_default)


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


class iuwandbox_test_base(unittest.TestCase):
    dir = None

    def setUp(self):
        self.capture = StringIO()
        sys.stdout = self.capture
        self.dir = os.getcwd()
        os.chdir(os.path.dirname(os.path.abspath(__file__)))
        return super(iuwandbox_test_base, self).setUp()

    def tearDown(self):
        sys.stdout = sys.__stdout__
        os.chdir(self.dir)
        self.capture.close()
        return super(iuwandbox_test_base, self).tearDown()

    def dump(self):
        value = self.capture.getvalue()
        eprint(value)


class nofused_iuwandbox_test(iuwandbox_test_base):
    def setUp(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        if os.path.exists(fused_src):
            try:
                shutil.rmtree(fused_src)
            except:
                pass
        if os.path.exists(os.path.join(fused_src, 'iutest.min.hpp')):
            self.skipTest('fused-src is exists')
        return super(nofused_iuwandbox_test, self).setUp()

    def test_nofused(self):
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.dump()
        self.assertEqual(cm.exception.code, 1, self.capture.getvalue())
        self.assertRegex(self.capture.getvalue(), '.*please try \"make fused\".*')


class iuwandbox_test(iuwandbox_test_base):
    def setUp(self):
        if not os.path.exists(fused_src):
            try:
                fused_iutest_files.FusedAll(fused_iutest_files.IUTEST_INCLUDE_DIR, fused_src)
#              os.system('python ' + root + '/tools/fused/fused_iutest_files.py ' + fused_src)
            except:
                pass
        if not os.path.exists(os.path.join(fused_src, 'iutest.min.hpp')):
            self.skipTest('fused-src is not exists')
        return super(iuwandbox_test, self).setUp()

    def test_nomain(self):
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt_nomain)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.dump()
        self.assertEqual(cm.exception.code, 1, self.capture.getvalue())
        self.assertRegex(self.capture.getvalue(), '.*hint:.*')
        self.assertRegex(self.capture.getvalue(), '.*If you do not use boost test, please specify the file with the main function first..*')

    def test_run(self):
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt)
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.dump()
        self.assertEqual(cm.exception.code, 0, self.capture.getvalue())
        self.assertRegex(self.capture.getvalue(), '.*OK.*')

    def test_same_filename(self):
        sys.argv[1:] = ['src/main.cpp', 'src/A/sample.cpp', 'src/B/sample.cpp']
        sys.argv.extend(test_opt_nomain)
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.dump()
        self.assertEqual(cm.exception.code, 0, self.capture.getvalue())
        self.assertRegex(self.capture.getvalue(), '.*OK.*')


if __name__ == "__main__":
    unittest.main()
