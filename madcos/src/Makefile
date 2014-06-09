#====================================
#(c)2008 by MADCrew all rights reserved
#Marcel S., Dmitrij M.
#====================================

ASM = nasm
GCC = i686-elf-gcc
LD  = i686-elf-ld

OBJ_FILES = bldr.bin osldr.bin kernelEnt.obj interruptsAsm.obj \
			madkr.obj console.obj string.obj sys.obj interrupts.obj \
			keyboard.obj timer.obj init.obj floppy.obj dma.obj
			
BOOT_DIR   = boot
KERNEL_DIR = kernel
DRIVER_DIR = drivers
OUTPUT_DIR = ..\devTest
INCLUDE_DIR = include

madcos: $(OBJ_FILES)
		$(LD)  -T $(KERNEL_DIR)\linker.ld -o $(OUTPUT_DIR)\madkr.bin

bldr.bin: $(BOOT_DIR)\bootloader.asm 
				$(ASM) -I$(BOOT_DIR)\\ -f bin -o $(OUTPUT_DIR)\bldr.bin $(BOOT_DIR)\bootloader.asm
				
osldr.bin: $(BOOT_DIR)\osloader.asm 
				 $(ASM) -I$(BOOT_DIR)\\ -f bin -o $(OUTPUT_DIR)\osldr.bin $(BOOT_DIR)\osloader.asm

kernelEnt.obj: $(KERNEL_DIR)\kernelEntry.asm
				$(ASM) -f elf -o $(OUTPUT_DIR)\kernelEnt.obj $(KERNEL_DIR)\kernelEntry.asm

init.obj: $(KERNEL_DIR)\init.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -o $(OUTPUT_DIR)\init.obj $(KERNEL_DIR)\init.c -nostdlib -nostartfiles -nodefaultlibs
				
interruptsAsm.obj: $(KERNEL_DIR)\interrupts.asm
				$(ASM) -f elf -o $(OUTPUT_DIR)\interruptsAsm.obj $(KERNEL_DIR)\interrupts.asm				
				
madkr.obj: $(KERNEL_DIR)\kernel.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -o $(OUTPUT_DIR)\madkr.obj $(KERNEL_DIR)\kernel.c -nostdlib -nostartfiles -nodefaultlibs
				 
console.obj: $(KERNEL_DIR)\console.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -o $(OUTPUT_DIR)\console.obj $(KERNEL_DIR)\console.c -nostdlib -nostartfiles -nodefaultlibs	

string.obj: $(KERNEL_DIR)\string.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -o $(OUTPUT_DIR)\string.obj $(KERNEL_DIR)\string.c -nostdlib -nostartfiles -nodefaultlibs				 
				 
sys.obj: $(KERNEL_DIR)\sys.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -o $(OUTPUT_DIR)\sys.obj $(KERNEL_DIR)\sys.c -nostdlib -nostartfiles -nodefaultlibs	
				 
interrupts.obj: $(KERNEL_DIR)\interrupts.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -o $(OUTPUT_DIR)\interrupts.obj $(KERNEL_DIR)\interrupts.c -nostdlib -nostartfiles -nodefaultlibs
				 
keyboard.obj: $(DRIVER_DIR)\keyboard\keyboard.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -I$(DRIVER_DIR)\keyboard -o $(OUTPUT_DIR)\keyboard.obj $(DRIVER_DIR)\keyboard\keyboard.c -nostdlib -nostartfiles -nodefaultlibs
	
timer.obj: $(DRIVER_DIR)\timer\timer.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -I$(DRIVER_DIR)\timer -o $(OUTPUT_DIR)\timer.obj $(DRIVER_DIR)\timer\timer.c -nostdlib -nostartfiles -nodefaultlibs

floppy.obj: $(DRIVER_DIR)\floppy\floppy.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -I$(DRIVER_DIR)\floppy -o $(OUTPUT_DIR)\floppy.obj $(DRIVER_DIR)\floppy\floppy.c -nostdlib -nostartfiles -nodefaultlibs

dma.obj: $(DRIVER_DIR)\dma\dma.c
				 $(GCC) -ffreestanding -c -I$(INCLUDE_DIR) -I$(DRIVER_DIR)\dma -o $(OUTPUT_DIR)\dma.obj $(DRIVER_DIR)\dma\dma.c -nostdlib -nostartfiles -nodefaultlibs
				 
clean:
		rm $(OUTPUT_DIR)\*.obj
		