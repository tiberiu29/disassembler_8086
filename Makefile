.PHONY: test clean

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -g
INCLUDES= -Isrc -I/workspace/unity

test:
	$(CC) $(CFLAGS) $(INCLUDES) \
		src/disassembler.c \
		./unity/unity.c \
		test/test_disassembler.c \
		-o test_disassembler
	./test_disassembler

clean:
	rm -f test_disassembler
