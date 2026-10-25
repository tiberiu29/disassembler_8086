.DEFAULT_GOAL := test

CC := gcc
CPPFLAGS := -Isrc -Isrc/model -Isrc/helper -Isrc/instructions -Iunity
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic -g
BUILD_DIR := build
TEST_PATTERN := test/test_*.c

# Production sources only.
SRC := $(wildcard src/*.c src/model/*.c src/helper/*.c src/instructions/*.c)
OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
UNITY_OBJ := $(BUILD_DIR)/unity/unity.o

# Discover test files in the root test/ and module test/ folders.
TEST_SRC := $(wildcard $(TEST_PATTERN) src/*/$(TEST_PATTERN))
TEST_BIN := $(patsubst %.c,$(BUILD_DIR)/%,$(TEST_SRC))
TEST_OBJ := $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRC))

.PHONY: all test clean list-tests

all: $(TEST_BIN)

test: $(TEST_BIN)
	@set -e; for test_bin in $(TEST_BIN); do \
		printf '\n== Running %s ==\n' "$$test_bin"; \
		"./$$test_bin"; \
	done

list-tests:
	@printf '%s\n' $(TEST_BIN)

# Each test source produces a separate executable.
# NOTE: this is a bit problematic because I link all $(OBJ) files
# but I will keep it like this for now
$(TEST_BIN): %: %.o $(OBJ) $(UNITY_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

# Compile .c files into .o files.
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

# Automatically track header dependencies.
-include $(OBJ:.o=.d) $(TEST_OBJ:.o=.d) $(UNITY_OBJ:.o=.d)

clean:
	rm -rf $(BUILD_DIR)

