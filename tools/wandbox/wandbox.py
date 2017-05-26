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

    @staticmethod
    def GetCompilerList():
        """
        get compiler list
        """
        response = requests.get(Wandbox.api_url + '/list.json')
        response.raise_for_status()
        return response.json()

    def get_compiler_list(self):
        """
        get compiler list
        .. deprecated:: 0.3.4
        """
        return Wandbox.GetCompilerList()

    @staticmethod
    def GetPermlink(link):
        """
        get wandbox permanet link
        """
        response = requests.get(Wandbox.api_url + '/permlink/' + link)
        response.raise_for_status()
        return response.json()

    def get_permlink(self, link):
        """
        get wandbox permanet link
        .. deprecated:: 0.3.4
        """
        return Wandbox.GetPermlink(link)

    def run(self):
        """
        excute on wandbox
        """
        headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
        payload = json.dumps(self.parameter)
        response = requests.post(self.api_url + '/compile.json', data=payload, headers=headers)
        response.raise_for_status()
        return response.json()

    def code(self, code):
        """
        set main source code
        """
        self.parameter.update({'code': code})

    def add_file(self, filename, code):
        """
        append file
        """
        if 'codes' in self.parameter:
            self.parameter['codes'].append({'file': filename, 'code': code})
        else:
            self.parameter.update({'codes': [{'file': filename, 'code': code}]})

    def compiler(self, name):
        """
        set compiler name
        """
        self.parameter.update({'compiler': name})

    def options(self, options_str):
        """
        set wandbox options
        """
        self.parameter.update({'options': options_str})

    def stdin(self, input_str):
        """
        set stdin buffer
        """
        self.parameter.update({'stdin': input_str})

    def compiler_options(self, options_str):
        """
        set wandbox defined compiler options
        """
        self.parameter.update({'compiler-option-raw': options_str})

    def add_compiler_options(self, options_str):
        """
        set compiler options
        """
        if 'compiler-option-raw' not in self.parameter:
            self.compiler_options(options_str)
        else:
            option = self.parameter['compiler-option-raw']
            option += '\n'
            option += options_str
            self.parameter.update({'compiler-option-raw': option})

    def runtime_options(self, options_str):
        """
        set runtime options
        """
        self.parameter.update({'runtime-option-raw': options_str})

    def permanent_link(self, enable):
        """
        wandbox permanet link to enable
        """
        self.parameter.update({'save': enable})

    def dump(self):
        """
        dump parameters
        """
        print(self.parameter)

    def reset(self):
        """
        reset parametes
        """
        self.parameter = {'code': ''}


if __name__ == '__main__':
    with Wandbox() as w:
        w.compiler('gcc-head')
        w.options('warning,gnu++1y')
        w.compiler_options('-Dx=hogefuga\n-O3')
        w.code('#include <iostream>\nint main() { int x = 0; std::cout << "hoge" << std::endl; }')
        print(w.run())
