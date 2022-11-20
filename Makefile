lib=allocator.so

# Set the following to '0' to disable log messages:
LOGGER ?= 1

# Compiler/linker flags
CFLAGS += -g -Wall -fPIC -DLOGGER=$(LOGGER) -pthread -shared
LDLIBS +=
LDFLAGS +=

$(lib): allocator.c allocator_overrides.c allocator.h logger.h
	$(CC) $(CFLAGS) -DLOGGER=$(LOGGER) allocator.c allocator_overrides.c -o $@

docs: Doxyfile
	doxygen

clean:
	rm -f $(lib)
	rm -rf docs


# Tests --

test: $(lib) ./tests/run_tests
	@DEBUG="$(debug)" ./tests/run_tests $(run)

testupdate: testclean test

./tests/run_tests:
	rm -rf tests
	git clone https://github.com/usf-cs326-fa21/P3-Tests.git tests

testclean:
	rm -rf tests
