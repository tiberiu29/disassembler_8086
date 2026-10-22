elf="$1"

name="$(basename "$elf")"
out_dir="elf_output"
mkdir -p "$out_dir"

objdump -dr -M intel "$elf" > "$out_dir/$name.disassembled.txt"

# use -W to prevent truncated text
readelf -W -r "$elf" > "$out_dir/$name.relocations.txt"
readelf -W -s "$elf" > "$out_dir/$name.symbols.txt"
readelf -W -S "$elf" > "$out_dir/$name.sections.txt"

# optionals: main.o has no plt/got sections yet
objdump -d -M intel -j .plt "$elf" > "$out_dir/$name.plt.txt" 2>&1 || true
objdump -s -j .got "$elf" > "$out_dir/$name.got.txt" 2>&1 || true
objdump -s -j .got.plt "$elf" > "$out_dir/$name.got_plt.txt" 2>&1 || true

echo "ELF inspection saved in: $out_dir/"
