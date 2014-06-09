/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file interrupts.h
*\brief Stellt Interrupts zur verfuegung
*
*/

#ifndef _INTERRUPTS_H_
#define _INTERRUPTS_H_

#include <system\console.h>
#include <system\sys.h>
#include "..\drivers\keyboard\keyboard.h"
#include "..\drivers\floppy\floppy.h"
#include "..\drivers\timer\timer.h"

//exceptions
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

//hardware interrupts
extern void irq0(); //timer
extern void irq1(); //tastatur
extern void irq6(); //floppy disk

void _isrException(unsigned int intNum);
void _irqTimer();
void _irqKeyboard();
void _irqFloppy();

#endif

