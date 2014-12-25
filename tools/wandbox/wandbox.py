#!/usr/bin/env python
#
# wandbox.py
#

import requests
import json

#
#
#
class Wandbox:
	"""wandbox api class"""
	api_url = 'http://melpon.org/wandbox/api'
	parameter = { 'code':'' }
	def get_compiler_list(self):
		r = requests.get(self.api_url + '/list.json')
		r.raise_for_status()
		return r.json()
	def run(self):
		headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
		payload = json.dumps(self.parameter)
		r = requests.post(self.api_url + '/compile.json', data=payload, headers=headers)
		r.raise_for_status()
		return r.json()
	def get_permlink(self, link):
		r = requests.get(self.api_url + '/permlink/' + link )
		r.raise_for_status()
		return r.json()

	def code(self, str):
		self.parameter.update({'code':str})
	def compiler(self, str):
		self.parameter.update({'compiler':str})
	def options(self, str):
		self.parameter.update({'options':str})
	def stdin(self, str):
		self.parameter.update({'stdin':str})
	def compiler_options(self, str):
		self.parameter.update({'compiler-option-raw':str})
	def runtime_options(self, str):
		self.parameter.update({'runtime-option-raw':str})
	def permanent_link(self, b):
		self.parameter.update({'save':b})
	def dump(self):
		print self.parameter

if __name__ == '__main__':
	w = Wandbox()
	w.compiler('gcc-head')
	w.options('warning,gnu++1y')
	w.compiler_options('-Dx=hogefuga\n-O3')
	w.code('#include <iostream>\nint main() { int x = 0; std::cout << "hoge" << std::endl; }')
	print w.run()

