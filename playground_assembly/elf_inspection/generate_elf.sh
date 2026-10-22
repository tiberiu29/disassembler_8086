#!/usr/bin/env bash
rm -rf main.o
rm -rf main

rm -rf elf_output

rm -rf main.o main elf_output

gcc -c main.c -o main.o
gcc main.o -o main

mkdir -p elf_output/main.o elf_output/main

for elf in main.o main; do
    out="elf_output/$elf"

    objdump -dr -M intel "$elf" > "$out/disassembled.txt"
    readelf -Wr "$elf" > "$out/relocations.txt"
    readelf -Ws "$elf" > "$out/symbols.txt"
    readelf -WS "$elf" > "$out/sections.txt"

    objdump -d -M intel -j .plt "$elf" > "$out/plt.txt"
    objdump -s -j .got "$elf" > "$out/got.txt"
    objdump -s -j .got.plt "$elf" > "$out/got_plt.txt"
done
