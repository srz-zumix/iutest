#
# Makefile

.PHONY: setup sample dryrun run

sample: sample.cpp Makefile
	${CXX} sample.cpp -o sample

exec_sample: sample
	- ./sample --iutest_output=xml:result.xml
	
dryrun: exec_sample
ifdef SMS
	./iutwilio.py result.xml --dryrun --sms ${CALL_NUMBER}
else
	./iutwilio.py result.xml --dryrun --call ${CALL_NUMBER}
endif

run: exec_sample
ifdef SMS
	./iutwilio.py result.xml --sms ${CALL_NUMBER}
else
	./iutwilio.py result.xml --call ${CALL_NUMBER}
endif

setup:
	#pip install twilio
	easy_install twilio
	