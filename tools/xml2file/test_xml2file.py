import json
import os
import subprocess
import sys
import tempfile
import unittest


SCRIPT = os.path.join(os.path.dirname(__file__), 'xml2file.py')


class Xml2FileTests(unittest.TestCase):
    def convert(self, xml, *options):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        source = os.path.join(directory.name, 'results.xml')
        output = os.path.join(directory.name, 'output')
        with open(source, 'wb') as f:
            f.write(xml)
        subprocess.run([sys.executable, SCRIPT, '-o', output, *options, source],
                       check=True, capture_output=True)
        return os.path.join(output, 'results')

    def test_iutest_properties_and_non_test_suite_failure(self):
        root = self.convert(b'''<?xml version="1.0" encoding="UTF-8"?>
<testsuites name="AllTests" tests="2" skipped="0" time="1">
  <testsuite name="Suite" tests="1" skipped="0" custom="suite attribute">
    <testcase name="Case" time="0.1" custom="case attribute">
      <failure message="failed">details</failure>
      <skipped message="skipped"/>
    </testcase>
    <properties><property name="suite record" value="suite value"/></properties>
  </testsuite>
  <testsuite name="NonTestSuiteFailure" tests="1">
    <testcase name="" status="run"><failure message="global">setup</failure></testcase>
  </testsuite>
  <properties><property name="root record" value="root value"/></properties>
</testsuites>''', '--no-time')
        with open(os.path.join(root, 'Suite', 'Case.json'), encoding='utf-8') as f:
            case = json.load(f)
        self.assertNotIn('time', case)
        self.assertEqual(case['custom'], 'case attribute')
        self.assertEqual(case['testsuites_attrib'], {'root record': 'root value'})
        self.assertEqual(case['testsuite_attrib'],
                         {'custom': 'suite attribute', 'suite record': 'suite value'})
        self.assertEqual(case['failure'], [{'message': 'failed', 'text': 'details'}])
        self.assertEqual(case['skipped'], [{'message': 'skipped', 'text': None}])
        with open(os.path.join(root, 'NonTestSuiteFailure', '.json'), encoding='utf-8') as f:
            failure = json.load(f)
        self.assertEqual(failure['failure'][0]['text'], 'setup')

    def test_junit_and_xml_declared_encoding(self):
        xml = '''<?xml version="1.0" encoding="UTF-16"?>
<testsuites><testsuite name="JUnit">
  <properties><property name="suite" value="日本語"/></properties>
  <testcase name="ok" time="0.2"><failure message="failed">失敗</failure></testcase>
</testsuite></testsuites>'''
        root = self.convert(xml.encode('utf-16'))
        with open(os.path.join(root, 'JUnit', 'ok.json'), encoding='utf-8') as f:
            case = json.load(f)
        self.assertEqual(case['time'], '0.2')
        self.assertEqual(case['testsuite_attrib']['suite'], '日本語')
        self.assertEqual(case['failure'][0]['text'], '失敗')

    def test_names_cannot_escape_output_directory(self):
        root = self.convert(b'''<testsuites><testsuite name="../outside">
<testcase name="../../escape"/><testcase name=".."/>
</testsuite></testsuites>''')
        with open(os.path.join(root, '..%2Foutside', '..%2F..%2Fescape.json'),
                  encoding='utf-8') as f:
            self.assertEqual(json.load(f)['name'], '../../escape')
        self.assertTrue(os.path.isfile(os.path.join(root, '..%2Foutside', '%2E%2E.json')))


if __name__ == '__main__':
    unittest.main()
