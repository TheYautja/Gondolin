KERNELFOLDER=kernel
BOOTFOLDER=boot
LDFOLDER=linker
FINALDIR=bin
OUTDIR=obj


CC=/home/augusto/opt/cross/bin/i686-elf-gcc
AS=/home/augusto/opt/cross/bin/i686-elf-as

.PHONY: all clean iso run

$(OUTDIR)/boot.o: $(BOOTFOLDER)/boot.s | $(OUTDIR)
	@echo "assembling boot.s"
	$(AS) $< -o $@
	@echo "done"
	
	
$(OUTDIR)/kernel.o: $(KERNELFOLDER)/kernel.c | $(OUTDIR)
	@echo "building kernel"
	$(CC) -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	@echo "done"

all: $(OUTDIR)/kernel.o $(OUTDIR)/boot.o
	@echo "linking object files"
	$(CC) -T $(LDFOLDER)/linker.ld -o gondolin \
	      -ffreestanding -O2 -nostdlib \
	      $(OUTDIR)/boot.o $(OUTDIR)/kernel.o -lgcc
	


iso:
	@echo "=================="
	@echo "building gondolin.iso"
	grub-mkrescue -o $(FINALDIR)/gondolin.iso isodir
	@echo "done"
	@echo "=================="
	
	
run:
	qemu-system-i386 -cdrom $(FINALDIR)/gondolin.iso


clean:
	@rm -rf $(OUTDIR)/boot.o $(OUTDIR)/kernel.o
	
	
