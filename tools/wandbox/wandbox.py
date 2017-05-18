#!/usr/bin/env python
#
# wandbox.py
#

import requests
import json


#
#
class Wandbox:
    """wandbox api class"""
    #api_url = 'http://melpon.org/wandbox/api'
    api_url = 'https://wandbox.org/api'

    def __init__(self):
        self.reset()

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        return True

    @staticmethod
    def GetCompilerList():
        r = requests.get(Wandbox.api_url + '/list.json')
        r.raise_for_status()
        return r.json()

    def get_compiler_list(self):
        return Wandbox.GetCompilerList()

    @staticmethod
    def GetPermlink(link):
        r = requests.get(Wandbox.api_url + '/permlink/' + link)
        r.raise_for_status()
        return r.json()

    def get_permlink(self, link):
        return Wandbox.GetPermlink(link)

    def run(self):
        headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
        payload = json.dumps(self.parameter)
        r = requests.post(self.api_url + '/compile.json', data=payload, headers=headers)
        r.raise_for_status()
        return r.json()

    def code(self, str):
        self.parameter.update({'code': str})

    def add_file(self, filename, str):
        if 'codes' in self.parameter:
            self.parameter['codes'].append({'file': filename, 'code': str})
        else:
            self.parameter.update({'codes': [{'file': filename, 'code': str}]})

    def compiler(self, str):
        self.parameter.update({'compiler': str})

    def options(self, str):
        self.parameter.update({'options': str})

    def stdin(self, str):
        self.parameter.update({'stdin': str})

    def compiler_options(self, str):
        self.parameter.update({'compiler-option-raw': str})

    def add_compiler_options(self, str):
        if 'compiler-option-raw' not in self.parameter:
            self.compiler_options(str)
        else:
            option = self.parameter['compiler-option-raw']
            option += '\n'
            option += str
            self.parameter.update({'compiler-option-raw': option})

    def runtime_options(self, str):
        self.parameter.update({'runtime-option-raw': str})

    def permanent_link(self, b):
        self.parameter.update({'save': b})

    def dump(self):
        print(self.parameter)

    def close(self):
        self.reset()

    def reset(self):
        self.parameter = {'code': ''}


if __name__ == '__main__':
    with Wandbox() as w:
        w.compiler('gcc-head')
        w.options('warning,gnu++1y')
        w.compiler_options('-Dx=hogefuga\n-O3')
        w.code('#include <iostream>\nint main() { int x = 0; std::cout << "hoge" << std::endl; }')
        print(w.run())
