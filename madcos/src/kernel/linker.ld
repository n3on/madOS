OUTPUT_FORMAT("binary")
INPUT(..\devTest\kernelEnt.obj ..\devTest\interruptsAsm.obj
	  ..\devTest\keyboard.obj	..\devTest\timer.obj
	  ..\devTest\console.obj ..\devTest\string.obj
	  ..\devTest\sys.obj ..\devTest\interrupts.obj
	  ..\devTest\madkr.obj ..\devTest\init.obj 
	  ..\devTest\floppy.obj ..\devTest\dma.obj)
	  
ENTRY(_kernelEntry)
SECTIONS
{
  .text  0xAdf0 : {
    code = .; _code = .; __code = .;
    *(.text)
    . = ALIGN(1);
  }
  .data  : {
    data = .; _data = .; __data = .;
    *(.data)
    . = ALIGN(1);
  }
  .bss  :
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
    . = ALIGN(1);
  }
  end = .; _end = .; __end = .;
}
