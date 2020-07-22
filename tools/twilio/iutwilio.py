#!/usr/bin/env python
#
# iutwilio.py
#
# Copyright (C) 2015-2016, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

import os
import sys
import xml.etree.ElementTree as ET

from argparse import ArgumentParser
from twilio.rest import TwilioRestClient

try:
    import configparser
except ImportError:
    import ConfigParser as configparser

account_sid = ''
auth_token = ''
my_number = ''
sms_number = ''


# command line option
def parse_command_line():
    parser = ArgumentParser()
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        version=u'%(prog)s version 0.4'
    )
    parser.add_argument(
        '--ini',
        default='config.ini',
        help='ini file path. (inifile section [Twilio] account_sid,auth_token,number,sms_number)'
    )
    parser.add_argument(
        '--call',
        metavar='NUMBER',
        help='call to number.'
    )
    parser.add_argument(
        '--sms',
        metavar='NUMBER',
        help='send message number.'
    )
    parser.add_argument(
        '--account_sid',
        metavar='SID',
        help='account sid.'
    )
    parser.add_argument(
        '--auth_token',
        metavar='TOKEN',
        help='auth token.'
    )
    parser.add_argument(
        '--number',
        help='twilio phone number.'
    )
    parser.add_argument(
        '--dump',
        action='store_true',
        help='dump setting.'
    )
    parser.add_argument(
        '--dryrun',
        action='store_true',
        help='dryrun.'
    )
    parser.add_argument(
        '--url',
        default='http://twimlbin.com/2e6ad348',
        help='TwiML url.'
    )
    parser.add_argument(
        'xml',
        metavar='XML',
        nargs='?',
        help='test result xml file'
    )
    options = parser.parse_args()

    if not options.dump:
        if not options.xml:
            if not options.call:
                parser.print_help()

    return options


# setup
def setup(options):
    global account_sid
    global auth_token
    global my_number
    global sms_number
    if options.account_sid:
        account_sid = options.account_sid
    if options.auth_token:
        auth_token = options.auth_token
    if options.number:
        my_number = options.number
        sms_number = options.number


def get_ini(ini, s, n):
    try:
        return ini.get(s, n)
    except Exception as e:
        print(e)
        return None


def parse_ini(path):
    global account_sid
    global auth_token
    global my_number
    global sms_number
    if account_sid and auth_token and my_number:
        return
    ini = configparser.SafeConfigParser()
    if not os.path.exists(path):
        sys.stderr.write('%s not found...' % path)
        sys.exit(2)
    ini.read(path)

    account_sid = get_ini(ini, 'Twilio', 'account_sid')
    auth_token = get_ini(ini, 'Twilio', 'auth_token')
    my_number = get_ini(ini, 'Twilio', 'number')
    sms_number = get_ini(ini, 'Twilio', 'sms_number')

#   for section in ini.sections():
#       print('[%s]' % (section))
#       for key in ini.options(section):
#           print('%s.%s =%s' % (section, key, ini.get(section, key)))


def parse_xml(path):
    tree = ET.parse(path)
    root = tree.getroot()
    testsuites = root.find('[@failures]')
    return testsuites.attrib['failures']


# make twilio client
def make_twilio():
    client = TwilioRestClient(account_sid, auth_token)
    return client


# call twilio
def call(client, options):
    if options.dryrun:
        print('twilio call to ' + options.call)
    else:
        call = client.calls.create(
            url=options.url,
            to=options.call,
            from_=my_number)
        print(call.sid)


# make_message
def make_message(options):
    body = ""
    filepath = options.xml
    if filepath and os.path.exists(filepath):
        tree = ET.parse(filepath)
        root = tree.getroot()
        tests = int(root.get('tests'))
        testcases = len(root.findall('testsuite'))
        failures = int(root.get('failures'))
        disabled = int(root.get('disabled'))
        skipped = int(root.get('skip'))
        passed = tests - failures - skipped
        time = root.get('time')
        timestamp = root.get('timestamp')

        if timestamp:
            body += "%s\n" % (timestamp)
        first_failure = None

        body += "%d tests from %s testcase ran. (%sms total)\n" % (tests, testcases, time)
        if passed:
            body += "PASSED  : %d\n" % (passed)
        if disabled:
            body += "DISABLED: %d\n" % (disabled)
        if skipped:
            body += "SKIPPED : %d\n" % (skipped)
        if failures:
            body += "FAILED  : %d\n" % (failures)
        failure_testsuites = root.findall('testsuite')
        for suite in failure_testsuites:
            if int(suite.get('failures')):
                for test in suite:
                    failure_node = test.find('.//failure')
                    if failure_node:
                        if not first_failure:
                            first_failure = failure_node
                        name = "%s.%s\n" % (suite.get('name'), test.get('name'))
                        if len(body) + len(name) < 155:
                            body += name
                        else:
                            body += "..."
                            return body
        if first_failure:
            for s in first_failure.text.split('\n'):
                if len(body) + len(s) < 155:
                    body += "%s\n" % s
                else:
                    body += "..."
                    return body
    return body


# message
def message(client, options):
    m = make_message(options)
    if options.dryrun:
        print('twilio call to ' + options.sms)
        print(m)
    else:
        call = client.messages.create(
            body=m,
            to=options.sms,
            from_=sms_number)
        print(call.sid)


# run
def run(options):
    filepath = options.xml
    if filepath:
        if not os.path.exists(filepath):
            sys.exit(1)
        else:
            if int(parse_xml(filepath)) > 0:
                if options.sms:
                    message(make_twilio(), options)
                elif options.call:
                    call(make_twilio(), options)
                else:
                    print('was failed ' + filepath)
    else:
        if options.call:
            call(make_twilio(), options)

    sys.exit(0)


# dump
def dump(options):
    print('account_sid: %s' % (account_sid))
    print('auth_token : %s' % (auth_token))
    print('my_number  : %s' % (my_number))
    if options.call:
        print('call       : %s' % (options.call))
    if options.sms:
        print('sms        : %s' % (options.sms))


def main():
    options = parse_command_line()
    setup(options)
    parse_ini(options.ini)
    if options.dump:
        dump(options)
    else:
        run(options)


if __name__ == '__main__':
    main()
