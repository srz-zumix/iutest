#
# Makefile

.PHONY: setup sample dryrun run

help: iutwilio.py
	python ./iutwilio.py -h

sample: sample.cpp Makefile
	${CXX} sample.cpp -o sample

exec_sample: sample
	- ./sample --iutest_output=xml:result.xml

dryrun: exec_sample iutwilio.py
ifdef SMS
	python ./iutwilio.py result.xml --dryrun --sms ${CALL_NUMBER}
else
	python ./iutwilio.py result.xml --dryrun --call ${CALL_NUMBER}
endif

run: exec_sample iutwilio.py
ifdef SMS
	python ./iutwilio.py result.xml --sms ${CALL_NUMBER}
else
	python ./iutwilio.py result.xml --call ${CALL_NUMBER}
endif

test: iutwilio.py
	python ./iutwilio.py -h
	- python ./iutwilio.py result.xml --dryrun --sms ${CALL_NUMBER}
	- python ./iutwilio.py result.xml --dryrun --call ${CALL_NUMBER}

setup:
	#pip install twilio
	easy_install twilio
