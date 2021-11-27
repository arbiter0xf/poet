SRC := $(wildcard src/*.c)
SRC_TEST := $(wildcard test/*.c)
OBJ := $(SRC:.c=.o)
OBJ_TEST := $(SRC_TEST:.c=.o)
DEP := $(SRC:.c=.d)
HEADERS := $(wildcard *.h) $(wildcard *.const)

SRC_WITHOUT_MAIN := $(filter-out src/main.c,$(SRC))

# Produce header dependency files to be included below
CFLAGS := -MMD

EXECUTABLE := poet
EXECUTABLE_TEST := current_test

#COMPILER := clang
COMPILER := gcc
COMPILER_TEST := $(COMPILER)

LDFLAGS := -lncurses
LDFLAGS_TEST := $(LDFLAGS) -lcriterion

.PHONY: clean run slow test test_run distcheck

$(EXECUTABLE): $(OBJ)
	$(COMPILER) -Wall -o $@ $^ $(LDFLAGS)

-include $(DEP)

slow: $(SRC) $(HEADERS)
	$(COMPILER) -Wall -o $(EXECUTABLE) $(SRC) $(LDFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

test: $(SRC_TEST) $(SRC_WITHOUT_MAIN)
	$(COMPILER_TEST) -DLOGGING_DISABLED=1 -Wall -o $(EXECUTABLE_TEST) $^ $(LDFLAGS_TEST)

test_run: test
	LD_LIBRARY_PATH=/usr/lib64 ./$(EXECUTABLE_TEST)

test_slow:
	./run_tests.sh

distcheck:
	true

clean:
	$(RM) $(OBJ) $(DEP) $(EXECUTABLE)
