KERNELFOLDER=kernel
BOOTFOLDER=boot
LDFOLDER=linker
FINALDIR=bin
OUTDIR=obj
ISODIR=isodir
KERNEL=kernel.bin

CC=/home/augusto/opt/cross/bin/i686-elf-gcc
AS=/home/augusto/opt/cross/bin/i686-elf-as


.PHONY: all clean iso run


$(OUTDIR):
	mkdir -p $(OUTDIR)


$(OUTDIR)/boot.o: $(BOOTFOLDER)/boot.s | $(OUTDIR)
	@echo "assembling boot.s"
	$(AS) $< -o $@
	@echo "done"


$(OUTDIR)/kernel.o: $(KERNELFOLDER)/kernel.c | $(OUTDIR)
	@echo "building kernel"
	$(CC) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	@echo "done"


$(KERNEL): $(OUTDIR)/boot.o $(OUTDIR)/kernel.o
	@echo "linking kernel"
	$(CC) -T $(LDFOLDER)/linker.ld -o $@ \
	      -ffreestanding -O2 -nostdlib \
	      $^ -lgcc


$(ISODIR)/boot/kernel.bin: $(KERNEL)
	cp $(KERNEL) $(ISODIR)/boot/kernel.bin


all: $(KERNEL)

iso: $(ISODIR)/boot/kernel.bin
	@echo "=================="
	@echo "building gondolin.iso"
	grub-mkrescue -o $(FINALDIR)/gondolin.iso $(ISODIR)
	@echo "done"
	@echo "=================="

run: iso
	qemu-system-i386 -cdrom $(FINALDIR)/gondolin.iso

clean:
	rm -f $(OUTDIR)/*.o $(KERNEL)
