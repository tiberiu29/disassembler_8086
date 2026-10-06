#!/bin/bash

printf 'bits 16\n%s\n' "$1" > /tmp/test.asm
nasm -f bin /tmp/test.asm -o /tmp/test.bin
xxd -g 1 /tmp/test.bin

# example usage: ./assemble.sh "mov dx, bx"
