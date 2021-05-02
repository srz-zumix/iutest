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
import iuwandbox_pp

try:
    from StringIO import StringIO
except ImportError:
    from io import StringIO

root = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../../../')
fused_src = root + '/fused-src'
test_src = root + '/test/syntax_tests.cpp'
test_opt_default = ['--encoding', 'utf-8-sig', '--compiler', 'gcc-10.1.0']
test_opt_nomain = test_opt_default
test_opt = ['-f"-DIUTEST_USE_MAIN"']
test_opt.extend(test_opt_default)
test_opt_verbose = ['--verbose']
test_opt_dryrun = ['--dryrun']
test_opt_no_min = ['--no-iutest-use-wandbox-min']


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
        return value


class nofused_iuwandbox_test(iuwandbox_test_base):
    def setUp(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        for f in ['iutest.hpp', 'iutest.min.hpp', 'iutest.wandbox.min.hpp']:
            if os.path.exists(os.path.join(fused_src, f)):
                try:
                    os.remove(os.path.join(fused_src, f))
                except Exception as e:
                    self.skipTest('fused-src/' + f + ' remove failed... : ' + str(e))
            if os.path.exists(os.path.join(fused_src, f)):
                self.skipTest('fused-src/' + f + ' is exists')
        return super(nofused_iuwandbox_test, self).setUp()

    def test_nofused(self):
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        self.dump()
        output = self.capture.getvalue()
        self.assertEqual(cm.exception.code, 1, output)
        self.assertRegex(output, '.*please try \"make fused\".*')


class iuwandbox_test(iuwandbox_test_base):
    def setUp(self):
        need_make_fused = False
        for f in ['iutest.hpp', 'iutest.min.hpp', 'iutest.wandbox.min.hpp']:
            if not os.path.exists(os.path.join(fused_src, f)):
                need_make_fused = True
        if need_make_fused:
            try:
                fused_iutest_files.FusedAll(fused_iutest_files.IUTEST_INCLUDE_DIR, fused_src)
                iuwandbox_pp.default_pp()
#              os.system('python ' + root + '/tools/fused/fused_iutest_files.py ' + fused_src)
            except:
                pass
        if not os.path.exists(os.path.join(fused_src, 'iutest.min.hpp')):
            self.skipTest('fused-src is not exists')
        if not os.path.exists(os.path.join(fused_src, 'iutest.wandbox.min.hpp')):
            self.skipTest('fused-src (wandbox) is not exists')
        return super(iuwandbox_test, self).setUp()

    def test_nomain(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt_nomain)
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 1, output)
        self.assertRegex(output, '.*hint:.*')
        self.assertRegex(output, '.*In "iutest" you can omit the definition of the main function, please define IUTEST_USE_MAIN. (--iutest-use-main or -f"-DIUTEST_USE_MAIN")*')

    def test_use_main(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt_nomain)
        sys.argv.append('--iutest-use-main')
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 0, output)
        self.assertRegex(output, '.*OK.*')

    def test_define_wandbox(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt)
        sys.argv.extend(test_opt_dryrun)
        sys.argv.extend(test_opt_verbose)
        sys.argv.append('-f"-DTEST"')
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 0, output)
        self.assertRegex(output, '.*-D__WANDBOX__.*')
        self.assertRegex(output, '.*-DTEST.*')

    def test_boosttest_workarround(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt_nomain)
        sys.argv.extend(['--boost', '1.65.0'])
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 1, output)
        self.assertRegex(output, '.*hint:.*')
        self.assertRegex(output, '.*If you do not use boost test, please specify the file with the main function first..*')

    def test_run(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt)
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 0, output)
        self.assertRegex(output, r'\[ \s+OK \]')
        self.assertFalse('-Wmisleading-indentation' in output)

    def test_same_filename(self):
        sys.argv[1:] = ['src/main.cpp', 'src/A/sample.cpp', 'src/B/sample.cpp']
        sys.argv.extend(test_opt_nomain)
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 0, output)
        self.assertRegex(output, '.*OK.*')
        self.assertFalse('-Wmisleading-indentation' in output)

    # def test_no_min_run(self):
    #     if 'SCRUTINIZER' in os.environ:
    #         self.skipTest('this test is not run on SCRUTINIZER.')
    #     sys.argv[1:] = [test_src]
    #     sys.argv.extend(test_opt)
    #     sys.argv.extend(test_opt_no_min)
    #     print(sys.argv)
    #     with self.assertRaises(SystemExit) as cm:
    #         iuwandbox.main()
    #     output = self.dump()
    #     self.assertEqual(cm.exception.code, 0, output)
    #     self.assertRegex(output, r'\[ \s+OK \]')
    #     # false positive : IUTEST_COND_LIKELY/IUTEST_COND_UNLIKELY
    #     # self.assertFalse('-Wmisleading-indentation' in output)

    def test_make_run(self):
        if 'SCRUTINIZER' in os.environ:
            self.skipTest('this test is not run on SCRUTINIZER.')
        sys.argv[1:] = [test_src]
        sys.argv.extend(test_opt)
        sys.argv.extend(['--make'])
        print(sys.argv)
        with self.assertRaises(SystemExit) as cm:
            iuwandbox.main()
        output = self.dump()
        self.assertEqual(cm.exception.code, 0, output)
        self.assertRegex(output, r'\[ \s+OK \]')


if __name__ == "__main__":
    unittest.main()
