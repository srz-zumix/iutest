#!/usr/bin/env python
#
# test_iuwandbox.py
#

import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/../../fused')
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + '/../../wandbox')

import unittest
import iuwandbox
import shutil

try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO

root = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../../../')
fused_src = root + '/fused-src'
test_src = root + '/test/syntax_tests.cpp'
test_opt_nomain = [ '--encoding', 'utf-8-sig' ]
test_opt = [ '--encoding', 'utf-8-sig', '-f"-DIUTEST_USE_MAIN"' ]

class iuwandbox_test_base(unittest.TestCase):
    def setUp(self):
        self.capture = StringIO()
        sys.stdout = self.capture
        return super().setUp()

    def tearDown(self):
        sys.stdout = sys.__stdout__
        return super().tearDown()


class nofused_iuwandbox_test(iuwandbox_test_base):
    def setUp(self):
        if os.path.exists(fused_src):
            shutil.rmtree(fused_src)
        return super().setUp()

    def test_nofused(self):
        sys.argv[1:] = [ test_src ]
        sys.argv.extend(test_opt)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.assertEqual(cm.exception.code, 1)
        self.assertRegex(self.capture.getvalue(), '.*please try \"make fused\".*')


class iuwandbox_test(iuwandbox_test_base):
    def setUp(self):
        if not os.path.exists(fused_src):
            os.system('python ' + root + '/tools/fused/fused_iutest_files.py ' + fused_src)
        return super().setUp()

    def test_nomain(self):
        sys.argv[1:] = [ test_src ]
        sys.argv.extend(test_opt_nomain)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.assertEqual(cm.exception.code, 1)
        self.assertRegex(self.capture.getvalue(), '.*hint:.*')
        self.assertRegex(self.capture.getvalue(), '.*If you do not use boost test, please specify the file with the main function first..*')

    def test_run(self):
        sys.argv[1:] = [ test_src ]
        sys.argv.extend(test_opt)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.assertEqual(cm.exception.code, 0)
        self.assertRegex(self.capture.getvalue(), '.*OK.*')

if __name__ == "__main__":
    unittest.main()