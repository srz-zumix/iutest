#!/usr/bin/env python
#
# wandbox.py
#

"""
Wandbox API for Python
"""

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

    """
    get compiler list
    """
    @staticmethod
    def GetCompilerList():
        response = requests.get(Wandbox.api_url + '/list.json')
        response.raise_for_status()
        return response.json()

    """
    get compiler list
    .. deprecated:: 0.3.4
    """
    def get_compiler_list(self):
        return Wandbox.GetCompilerList()

    """
    get wandbox permanet link
    """
    @staticmethod
    def GetPermlink(link):
        response = requests.get(Wandbox.api_url + '/permlink/' + link)
        response.raise_for_status()
        return response.json()

    """
    get wandbox permanet link
    .. deprecated:: 0.3.4
    """
    def get_permlink(self, link):
        return Wandbox.GetPermlink(link)

    """
    excute on wandbox
    """
    def run(self):
        headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
        payload = json.dumps(self.parameter)
        response = requests.post(self.api_url + '/compile.json', data=payload, headers=headers)
        response.raise_for_status()
        return response.json()

    """
    set main source code
    """
    def code(self, code):
        self.parameter.update({'code': code})

    """
    append file
    """
    def add_file(self, filename, code):
        if 'codes' in self.parameter:
            self.parameter['codes'].append({'file': filename, 'code': code})
        else:
            self.parameter.update({'codes': [{'file': filename, 'code': code}]})

    """
    set compiler name
    """
    def compiler(self, name):
        self.parameter.update({'compiler': name})

    """
    set wandbox options
    """
    def options(self, options_str):
        self.parameter.update({'options': options_str})

    """
    set stdin buffer
    """
    def stdin(self, input):
        self.parameter.update({'stdin': input})

    """
    set wandbox defined compiler options
    """
    def compiler_options(self, options_str):
        self.parameter.update({'compiler-option-raw': options_str})

    """
    set compiler options
    """
    def add_compiler_options(self, options_str):
        if 'compiler-option-raw' not in self.parameter:
            self.compiler_options(options_str)
        else:
            option = self.parameter['compiler-option-raw']
            option += '\n'
            option += options_str
            self.parameter.update({'compiler-option-raw': option})

    """
    set runtime options
    """
    def runtime_options(self, options_str):
        self.parameter.update({'runtime-option-raw': options_str})

    """
    wandbox permanet link to enable
    """
    def permanent_link(self, enable):
        self.parameter.update({'save': enable})

    """
    dump parameters
    """
    def dump(self):
        print(self.parameter)

    """
    reset parametes
    """
    def reset(self):
        self.parameter = {'code': ''}


if __name__ == '__main__':
    with Wandbox() as w:
        w.compiler('gcc-head')
        w.options('warning,gnu++1y')
        w.compiler_options('-Dx=hogefuga\n-O3')
        w.code('#include <iostream>\nint main() { int x = 0; std::cout << "hoge" << std::endl; }')
        print(w.run())
