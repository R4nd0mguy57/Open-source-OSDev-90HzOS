CFLAGS= -Wall -Wextra -Iinclude

all:
	mkdir -p ~/OSDev/90HzOS/kernel/src ~/OSDev/90HzOS/kernel/bin ~/OSDev/90HzOS/OS ~/OSDev/90HzOS/img ~/OSDev/90HzOS/boot/bin ~/OSDev/90HzOS/boot/src ~/OSDev/90HzOS/kernel/bin/full
	nasm -f bin ~/OSDev/90HzOS/boot/src/boot.asm -o ~/OSDev/90HzOS/boot/bin/bootloader
	nasm -f elf ~/OSDev/90HzOS/kernel/src/entry.asm -o ~/OSDev/90HzOS/kernel/bin/entry.o
	nasm -f elf ~/OSDev/90HzOS/kernel/src/ports.asm -o ~/OSDev/90HzOS/kernel/bin/ports.o
	i386-elf-gcc $(CFLAGS) -ffreestanding -m32 -g -c ~/OSDev/90HzOS/kernel/src/kernel.c -o ~/OSDev/90HzOS/kernel/bin/kernel.o
	i386-elf-gcc $(CFLAGS) -ffreestanding -m32 -g -c ~/OSDev/90HzOS/kernel/src/keyboard/ps2.c -o ~/OSDev/90HzOS/kernel/bin/ps2.o
	i386-elf-gcc $(CFLAGS) -ffreestanding -m32 -g -c ~/OSDev/90HzOS/prog/src/terminal.c -o ~/OSDev/90HzOS/prog/bin/terminal.o
	i386-elf-ld -o ~/OSDev/90HzOS/kernel/bin/full/kernel.bin -Ttext 0x100000 ~/OSDev/90HzOS/kernel/bin/entry.o ~/OSDev/90HzOS/kernel/bin/ports.o ~/OSDev/90HzOS/kernel/bin/kernel.o ~/OSDev/90HzOS/kernel/bin/ps2.o ~/OSDev/90HzOS/prog/bin/terminal.o --oformat binary
	rm -f ~/OSDev/90HzOS/OS/90HzOS.bin
	cat ~/OSDev/90HzOS/boot/bin/bootloader ~/OSDev/90HzOS/kernel/bin/full/kernel.bin > ~/OSDev/90HzOS/OS/90HzOS.bin
	dd if=/dev/zero >> ~/OSDev/90HzOS/OS/90HzOS.bin count=32 bs=512
