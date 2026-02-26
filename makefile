KERNELDIR=kernel
BOOTDIR=boot
LDDIR=linker
ISODIR=isodir
OBJDIR=obj
BINDIR=bin

KERNEL=kernel.bin
ISO=$(BINDIR)/gondolin.iso

CC=/home/augusto/opt/cross/bin/i686-elf-gcc
AS=/home/augusto/opt/cross/bin/i686-elf-as

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
CFLAGS+=$(shell find $(KERNELDIR) -type d -exec echo -I{} \;)
LDFLAGS=-T $(LDDIR)/linker.ld -ffreestanding -O2 -nostdlib

KERNEL_C=$(shell find $(KERNELDIR) -name "*.c")
KERNEL_O=$(patsubst %.c,$(OBJDIR)/%.o,$(KERNEL_C))
BOOT_O=$(OBJDIR)/boot.o

.PHONY: all clean iso run dirs

dirs:
	mkdir -p $(OBJDIR) $(BINDIR) $(ISODIR)/boot
	mkdir -p $(sort $(dir $(KERNEL_O)))

$(BOOT_O): $(BOOTDIR)/boot.s | dirs
	$(AS) $< -o $@

$(OBJDIR)/%.o: %.c | dirs
	$(CC) -c $< -o $@ $(CFLAGS)

$(KERNEL): $(BOOT_O) $(KERNEL_O)
	$(CC) $(LDFLAGS) -o $@ $^ -lgcc

$(ISODIR)/boot/kernel.bin: $(KERNEL)
	cp $< $@

all: $(KERNEL)

iso: $(ISODIR)/boot/kernel.bin
	grub-mkrescue -o $(ISO) $(ISODIR)

run: iso
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf $(OBJDIR) $(KERNEL) $(ISO)
