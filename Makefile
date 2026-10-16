.PHONY: test clean

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -g
INCLUDES= -Isrc -Isrc/helper -Isrc/instructions -I/workspace/unity

test:
	$(CC) $(CFLAGS) $(INCLUDES) \
		src/helper/*.c \
		src/instructions/*.c \
		src/*.c \
		./unity/unity.c \
		test/test_disassembler.c \
		-o test_disassembler
	./test_disassembler

clean:
	rm -f test_disassembler
