# YOU DO NOT NEED TO RUN THIS TO USE QUNIT!
# These are simply for the tests

.PHONY: all
all: simple simple-tap failing failing-tap

simple: example/simple.c qunit.h
	$(CC) $< -o $@

simple-tap: example/simple.c qunit.h
	$(CC) $< -o $@ -DQUNIT_TAP

failing: example/failing.c qunit.h
	$(CC) $< -o $@

failing-tap: example/failing.c qunit.h
	$(CC) $< -o $@ -DQUNIT_TAP
