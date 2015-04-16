#
# Makefile

.PHONY: setup sample dryrun run

sample: sample.cpp Makefile
	${CXX} sample.cpp -o sample

exec_sample: sample
	- ./sample --iutest_output=xml:result.xml
	
dryrun: exec_sample
	./iutwilio.py result.xml --dryrun --call ${CALL_NUMBER}

run: exec_sample
	./iutwilio.py result.xml --call ${CALL_NUMBER}

setup:
	#pip install twilio
	easy_install twilio
	