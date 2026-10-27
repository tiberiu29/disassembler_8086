#!/bin/bash

rm -rf elf_output
rm -rf main.o
rm -rf main

SOURCE="$1"

nasm -f elf64 -g -F dwarf "$SOURCE" -o main.o
gcc -g main.o -o main
./main

mkdir -p elf_output/main.o elf_output/main

for elf in main.o main; do
    out="elf_output/$elf"

    readelf -Wh "$elf" > "$out/elf_header.txt"

    #-d.dynamic -> dynamic linker entry point
    #-r -> .rela.dyn +.rela.plt. 
    #-p .dynstr -> string dump .dynstr (needed by #NEEDED section of .dynamic)
    readelf -Wrd -p .dynstr "$elf" > "$out/elf_relocations.txt" 2>&1

    readelf -Ws "$elf" > "$out/elf_symbols.txt"
    readelf -WS "$elf" > "$out/elf_sections.txt"
    readelf -Wl  "$elf" > "$out/elf_program_headers.txt" 2>&1

    objdump -dr -M intel "$elf" > "$out/disassembled.txt"
    objdump -d -M intel -j .plt "$elf" > "$out/plt.txt" 2>&1

    # for .got/.got.plt we could use readelf -Wx .got/.got.plt
    # but using objdump with -s (raw-bytes) on section (-j)
    # display the GOT sections as hexadecimal dumps.
    # each address identifies a byte; bytes are shown in increasing address order.    
    objdump -s -j .got "$elf" > "$out/got.txt" 2>&1
    objdump -s -j .got.plt "$elf" > "$out/got_plt.txt" 2>&1
done
