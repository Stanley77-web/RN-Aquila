compile:
	nasm -f win32 guest-number.asm -o guest-number.o

link:
	ld -m elf_i386 -s guest-number.o -o guest-number.exe

exec:
	./guest-number.exe

run: compile link exec