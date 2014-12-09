#!/usr/bin/env python
#
# pypaiza.py
#

import requests
import json;

#
#
#
class PaizaIO:
	"""wandbox api class"""
	api_url = 'http://api.paiza.io/'
	parameter = { 'source_code':'', 'language':'cpp', 'api_key':'guest' }
	session_id = ''

	def create(self):
		headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
		payload = json.dumps(self.parameter)
		r = requests.post(self.api_url + 'runners/create/', data=payload, headers=headers)
		r.raise_for_status()
		result = r.json()
		if 'error' in result:
			print result['error']
			print result
			raise
		elif 'id' in result:
			self.session_id = result['id']
		else:
			print result
			raise
		return result
	
	def get_status(self):
		headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
		parameter = { 'id': self.session_id, 'api_key':self.parameter['api_key'] }
		payload = json.dumps(parameter)
		r = requests.get(self.api_url + 'runners/get_status/', data=payload, headers=headers)
		r.raise_for_status()
		return r.json()

	def get_details(self):
		headers = {'Content-type': 'application/json', 'Accept': 'text/plain'}
		parameter = { 'id': self.session_id, 'api_key':self.parameter['api_key'] }
		payload = json.dumps(parameter)
		r = requests.get(self.api_url + 'runners/get_details/', data=payload, headers=headers)
		r.raise_for_status()
		return r.json()
	
	def is_completed(self, r):
		if 'status' in r:
			return r['status'] == 'completed'
		return False

	def wait_complete(self):
		r = self.get_status()
		while not self.is_completed(r):
			r = self.get_status()

	def run(self):
		self.create()
		self.wait_complete();
		return self.get_details()

	def language(language, str):
		self.parameter.update({'language':str})
	def source_code(source_code, str):
		self.parameter.update({'source_code':str})
	def code(self, str):
		self.parameter.update({'source_code':str})
	def input(self, str):
		self.parameter.update({'input':str})
	def stdin(self, str):
		self.parameter.update({'input':str})
		
	def dump(self):
		print self.parameter

if __name__ == '__main__':
	paiza = PaizaIO()
	paiza.code('#include <iostream>\nint main() { int x = 0; std::cout << "hoge" << std::endl; }')
	print paiza.run()

