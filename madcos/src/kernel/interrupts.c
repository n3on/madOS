/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file interrupts.c
*\brief Stellt Interrupts zur verfuegung
*
*/

#include <system\interrupts.h>

//behandelt exception interrupts
void _isrException(unsigned int intNum)
{
	setClearColor(CL_BLUE);
	clearScreen();
	
	enum TEXT_COLOR color;
	color = getFgColor();
	setFgColor(CL_WHITE);
	
	setCursor(40,10);
	
	switch(intNum)
	{
		case 0:
		{
		   kprint("\nException: Division durch 0 ...\n");
		}break;
		case 1:
		{
		   kprint("\nException: Debuger ...\n");
		}break;
		case 2:
		{
		   kprint("\nException: Non Maskable Interrupt ...\n");
		}break;
		case 3:
		{
		   kprint("\nException: Breakpoint ...\n");
		}break;
		case 4:
		{
		   kprint("\nException: Into Detected Overflow ...\n");
		}break;
		case 5:
		{
			kprint("\nException: Out of Bounds ...\n");
		}break;
		case 6:
		{
		   kprint("\nException: Invalid Opcode ...\n");
		}break;
		case 7:
		{
		   kprint("\nException: No Coprocessor ...\n");
		}break;
		case 8:
		{
		   kprint("\nException: Double Fault ...\n");
		}break;
		case 9:
		{
		   kprint("\nException: Coprocessor Segment Overrun ...\n");
		}break;
		case 10:
		{
		   kprint("\nException: Bad TSS ...\n");
		}break;
		case 11:
		{
		   kprint("\nException: Segment Not Present ...\n");
		}break;
		case 12:
		{
		   kprint("\nException: Stack Fault ...\n");
		}break;
		case 13:
		{
		   kprint("\nException: General Protection Fault ...\n");
		}break;
		case 14:
		{
			kprint("\nException: Page Fault ...\n");
		}break;
		case 15:
		{
		   kprint("\nException: Unknown Interrupt ...\n");
		}break;
		case 16:
		{
		   kprint("\nException: Coprocessor Fault ...\n");
		}break;
		case 17:
		{
		   kprint("\nException: Alignment Check ...\n");
		}break;
		case 18:
		{
		   kprint("\nException: Machine Check ...\n");
		}break;		
		default:
		{
		   kprint("\nException: Von Intel reserviert ...\n");
		}break;
	};
	
	kprint("System angehalten. Bitte neustarten!\n");
	setFgColor(color);
	for (;;);
}

void _irqTimer()
{
	//kprint("Timer!!!!!!!!\n");
	pitTickCount++;
	outb(MASTER_PIC_COM, PIC_EOI);
}

void _irqKeyboard()
{
	//kprint("Key pressed. Wh0oho it works!!!!!!!!\n");
	
	//unsigned char key = _kbGetChar();
	//if(key<255)
	//	kputchar(key);
	outb(MASTER_PIC_COM, PIC_EOI);
}

void _irqFloppy()
{
	//kprint("\nFloppy IRQ!!!!!!!!\n");
	outb(MASTER_PIC_COM, PIC_EOI);
	floppy_irq = 1;
}



