#
#	---------------------------------------------------------------------
# 	Makefile for the Moelex kernel 
# 	we use GCC as the default compiler  
# 	we compile assembly code with nasm ,and link with ld
#	---------------------------------------------------------------------
#
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -nostdlib -nostdinc -fno-builtin -fno-stack-protector -I include -m32
LD_FLAGS = -T scripts/link.ld -melf_i386
ASM_FLAGS = -f elf

all: $(S_OBJECTS) $(C_OBJECTS) link

.c.o:
	@echo complile code file $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo complile asm code $< ...
	nasm $(ASM_FLAGS) $<

link:
	@echo complile kernel file $<...
	ld $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o Moelex

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) Moelex

.PHONY:flush_img
flush_img:
	sudo mount floppy.img /mnt/kernel
	sudo cp Moelex /mnt/kernel/Moelex
	sleep 1
	sudo umount /mnt/kernel
.PHONY: start
start:
	bochs -f bochsrc.txt
.PHONY:git
git:
	git push -u origin master
