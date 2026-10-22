#!/bin/bash
set -e

if [ $# -ne 1 ]; then
    echo "Usage: $0 <assembly-file.asm>"
    exit 1
fi

SOURCE="$1"

nasm -f elf64 "$SOURCE" -o test_asm.o
gcc test_asm.o -o test_asm
./test_asm

