#!/usr/bin/env python
#
# iutwilio.py
#

import os
import sys
import argparse
import ConfigParser
import twilio
import xml.etree.ElementTree as ET

from argparse import ArgumentParser
from twilio.rest import TwilioRestClient

account_sid= ''
auth_token = ''
my_number  = ''


#
# command line option
def parse_command_line():
	parser = ArgumentParser()
	parser.add_argument(
		'-v'
		, '--version'
		, action='version'
		, version=u'%(prog)s version 0.1'
	)
	parser.add_argument(
		'--ini'
		, help = 'ini file path.'
		, default = 'config.ini'
	)
	parser.add_argument(
		'--call'
		, help = 'call to number.'
	)
	parser.add_argument(
		'--account_sid'
		, help = 'account sid.'
	)
	parser.add_argument(
		'--auth_token'
		, help = 'auth token.'
	)
	parser.add_argument(
		'--number'
		, help = 'twilio phone number.'
	)
	parser.add_argument(
		'--dump'
		, action = 'store_true'
		, help = 'dump setting.'
	)
	parser.add_argument(
		'--dryrun'
		, action = 'store_true'
		, help = 'dryrun.'
	)
	parser.add_argument(
		'--url'
		, help = 'TwiML url.'
		, default = 'http://twimlbin.com/2e6ad348'
	)
	parser.add_argument(
		'xml'
		, metavar='XML'
		, help = 'test result xml file'
		, nargs='?'
	)
	del sys.argv[0]
	options = parser.parse_args(sys.argv)
	
	if not options.dump:
		if not options.xml:
			if not options.call:
				parser.print_help()
	
	return options

#
# setup
def setup(options):
	global account_sid
	global auth_token
	global my_number
	if options.account_sid:
		account_sid = options.account_sid
	if options.auth_token:
		auth_token = options.auth_token
	if options.number:
		my_number = options.number

#
# parse ini
def parse_ini(path):
	ini = ConfigParser.SafeConfigParser()
	if not os.path.exists(path):
		sys.stderr.write('%s not found...' % path)
		sys.exit(2)
	ini.read(path)
	
	global account_sid
	global auth_token
	global my_number
	try:
		account_sid = ini.get('Twilio', 'account_sid')
		auth_token = ini.get('Twilio', 'auth_token')
		my_number = ini.get('Twilio', 'my_number')
	except:
		pass
		
#	for section in ini.sections():
#		print '[%s]' % (section)
#		for key in ini.options(section):
#			print '%s.%s =%s' % (section, key, ini.get(section, key))

#
# parse xml
def parse_xml(path):
	tree = ET.parse(path)
	root = tree.getroot()
	testsuites = root.find('[@failures]')
	return testsuites.attrib['failures']

#
# make twilio client
def make_twilio():
	client = TwilioRestClient(account_sid, auth_token)
	return client

#
# call twilio
def call(client, options):
	if options.dryrun:
		print 'twilio call to ' + options.call + ' from ' + my_number
	else:
		call = client.calls.create(url=options.url,
			to=options.call,
			from_=my_number)
		print call.sid


#
# run
def run(options):
	filepath = options.xml
	if filepath:
		if not os.path.exists(filepath):
			sys.exit(1)
		else:
			if parse_xml(filepath) > 0:
				if options.call:
					call(make_twilio(), options)
				else:
					print 'was failed ' + filepath
	else:
		if options.call:
			call(make_twilio(), options)

	sys.exit(0)

#
# dump
def dump():
	print 'account_sid: %s' % (account_sid)
	print 'auth_token : %s' % (auth_token)
	print 'my_number  : %s' % (my_number)

#
#
def main():
	options = parse_command_line()
	parse_ini(options.ini)
	setup(options)
	if options.dump:
		dump()
	else:
		run(options)

if __name__ == '__main__':
	main()
