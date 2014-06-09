/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file sys.c
*\brief Stellt Systemfunktionen zur verfuegung
*
*/
#include <system\sys.h>

//instanziere gdt und gdt zeiger
struct GDT pGdt;
//3 deskriptoren für NULL, Code und Data Segmente
struct GDTDescriptor gdtDesc[3];

//instanziere  idt zeiger
struct IDT pIdt;
//256 Interrupts
struct IDTDescriptor idtDesc[256];

//aus einem i/o port lesen
unsigned char inb(unsigned short port)
{
	unsigned char value;
	__asm__ volatile ("inb %1, %0" : "=a"(value) : "dN"(port));
	
	return value;
}

//wert in ein i/o port schreiben
void outb(unsigned short port, unsigned char value)
{
	__asm__ volatile ("outb %1, %0" : : "dN"(port), "a"(value));
	
}

//warte bis i/o ausgabe fertig ist
void waitIO()
{
	__asm__ volatile ("outb %%al, $0x80" : : "a"(0));
}

//GDT setzen
void setGDTDescriptor(struct GDTDescriptor *desc, unsigned long start, unsigned long end, 
						unsigned char type)
{
	desc->size_0_15 = end & 0xFFFF;
	desc->base_0_15 = start & 0xFFFF;
	desc->base_16_23 = (start>>16) & 0xFF;
	desc->typ = type;
	desc->annex = (end >> 16) & 0xF;
	desc->annex = desc->annex | (0xCF & 0xF0); 
	desc->base_24_32 = (start>>24) & 0xFF;
	
}

//erstelle GDT
void createGDT()
{
	//erstelle 3 Tabellen
	setGDTDescriptor(&gdtDesc[0], 0, 0, 0);
	kprint("- GDT NULL Deskriptor erstellt\n");	
	setGDTDescriptor(&gdtDesc[1], 0, 0xffffffff, 0x9A);
	kprint("- GDT Code Deskriptor erstellt\n");
	setGDTDescriptor(&gdtDesc[2], 0, 0xffffffff, 0x92);
	kprint("- GDT Data Deskriptor erstellt\n");

	pGdt.limit = 23;
	pGdt.base  = (unsigned int)&gdtDesc;
	
	//register mit gdt laden
	loadGDTTable();
	
	kprint("- GDT Erstellt\n");
}

//register mit neuen gdt werten laden
void loadGDTTable()
{
	__asm__ volatile ("lgdtl %0;"
					  "ljmp $(0x8), $farJump;"
					  "farJump:"
					  "movl $0x10, %%eax;"
					  "movl %%eax, %%ds;"
					  "movl %%eax, %%es;"
					  "movl %%eax, %%fs;"
					  "movl %%eax, %%gs;"
					  "movl %%eax, %%ss;" : : "m"(pGdt));
					  
	kprint("- GDT in Prozessor geladen\n");					  
}

//idt erstellen
void setIDTGate(struct IDTDescriptor *desc, unsigned int start, unsigned short selector, 
					unsigned char options)
{
	desc->base_0_15 = start & 0xFFFF;
	desc->selector = selector;
	desc->zero = 0;
	desc->options = options;
	desc->base_16_31 = (start>>16) & 0xFFFF;

}

//register mit idt werten laden
void loadIDT()
{
	__asm__ volatile("lidtl %0;" : : "m"(pIdt));
}

//erstelle alle idts
void createIDT()
{
	//irqs umprogrammieren, so dass keine konflikte mit interrupts entstehen
	remapIRQ();
	
	//interrupt laden
	setIDTGate(&idtDesc[0], (unsigned long)isr0, 0x08, 0x8E);
	kprint("- Interrupt 0: Exception Division durch 0 erstellt\n");
	
	setIDTGate(&idtDesc[1], (unsigned long)isr1, 0x08, 0x8E);
	kprint("- Interrupt 1: Debug exception erstellt\n");

	setIDTGate(&idtDesc[2], (unsigned long)isr2, 0x08, 0x8E);
	kprint("- Interrupt 2: Non Maskable Interrupt Exception erstellt\n");	
	
	setIDTGate(&idtDesc[3], (unsigned long)isr3, 0x08, 0x8E);
	kprint("- Interrupt 3: Breakpoint Exception erstellt\n");

	setIDTGate(&idtDesc[4], (unsigned long)isr4, 0x08, 0x8E);
	kprint("- Interrupt 4: Breakpoint Exception erstellt\n");

	setIDTGate(&idtDesc[5], (unsigned long)isr5, 0x08, 0x8E);
	kprint("- Interrupt 5:  Into Detected Overflow Exception erstellt\n");
	
    setIDTGate(&idtDesc[6], (unsigned long)isr6, 0x08, 0x8E);
	kprint("- Interrupt 6:  Invalid Opcode Exception erstellt\n");
	
	setIDTGate(&idtDesc[7], (unsigned long)isr7, 0x08, 0x8E);
	kprint("- Interrupt 7: No Coprocessor Exception erstellt\n");

	setIDTGate(&idtDesc[8], (unsigned long)isr8, 0x08, 0x8E);
	kprint("- Interrupt 8: Double Fault Exception erstellt\n");	
	
	setIDTGate(&idtDesc[9], (unsigned long)isr9, 0x08, 0x8E);
	kprint("- Interrupt 9: Coprocessor Segment Overrun Exception erstellt\n");

	setIDTGate(&idtDesc[10], (unsigned long)isr10, 0x08, 0x8E);
	kprint("- Interrupt 10:  Bad TSS Exception erstellt\n");
	
	setIDTGate(&idtDesc[11], (unsigned long)isr11, 0x08, 0x8E);
	kprint("- Interrupt 11: Segment Not Present Exception erstellt\n");

	setIDTGate(&idtDesc[12], (unsigned long)isr12, 0x08, 0x8E);
	kprint("- Interrupt 12: Stack Fault Exception erstellt\n");
	
    setIDTGate(&idtDesc[13], (unsigned long)isr13, 0x08, 0x8E);
	kprint("- Interrupt 13: General Protection Fault Exception erstellt\n");
	
	setIDTGate(&idtDesc[14], (unsigned long)isr14, 0x08, 0x8E);
	kprint("- Interrupt 14: Page Fault Exception erstellt\n");

	setIDTGate(&idtDesc[15], (unsigned long)isr15, 0x08, 0x8E);
	kprint("- Interrupt 15: Unknown Interrupt Exception erstellt\n");	
	
	setIDTGate(&idtDesc[16], (unsigned long)isr16, 0x08, 0x8E);
	kprint("- Interrupt 16: Coprocessor Fault Exception erstellt\n");

	setIDTGate(&idtDesc[17], (unsigned long)isr17, 0x08, 0x8E);
	kprint("- Interrupt 17: Alignment Check Exception erstellt\n");	
	
	setIDTGate(&idtDesc[18], (unsigned long)isr18, 0x08, 0x8E);
	kprint("- Interrupt 18: Machine Check Exception  erstellt\n");	

	setIDTGate(&idtDesc[19], (unsigned long)isr19, 0x08, 0x8E);
	setIDTGate(&idtDesc[20], (unsigned long)isr20, 0x08, 0x8E);	
	setIDTGate(&idtDesc[21], (unsigned long)isr21, 0x08, 0x8E);
	setIDTGate(&idtDesc[22], (unsigned long)isr22, 0x08, 0x8E);	
	setIDTGate(&idtDesc[23], (unsigned long)isr23, 0x08, 0x8E);
	setIDTGate(&idtDesc[24], (unsigned long)isr24, 0x08, 0x8E);	
	setIDTGate(&idtDesc[25], (unsigned long)isr25, 0x08, 0x8E);
	setIDTGate(&idtDesc[26], (unsigned long)isr26, 0x08, 0x8E);	
	setIDTGate(&idtDesc[27], (unsigned long)isr27, 0x08, 0x8E);	
	setIDTGate(&idtDesc[28], (unsigned long)isr28, 0x08, 0x8E);
	setIDTGate(&idtDesc[29], (unsigned long)isr29, 0x08, 0x8E);	
	setIDTGate(&idtDesc[30], (unsigned long)isr30, 0x08, 0x8E);
	setIDTGate(&idtDesc[31], (unsigned long)isr31, 0x08, 0x8E);		
	kprint("- Interrupts: Intel reservierte Exceptions erstellt\n");
	
	setIDTGate(&idtDesc[32], (unsigned long)irq0, 0x08, 0x8E);
	kprint("- Interrupts 32: IRQ: Timer\n");	
	setIDTGate(&idtDesc[33], (unsigned long)irq1, 0x08, 0x8E);
	kprint("- Interrupts 33: IRQ: Keyboard\n");	
	setIDTGate(&idtDesc[38], (unsigned long)irq6, 0x08, 0x8E);
	kprint("- Interrupts 33: IRQ: Floppy\n");		
	
	
	
	pIdt.limit = 2047;
	pIdt.base  = (unsigned int)&idtDesc;
	
	loadIDT();	
	kprint("- IDT Erstellt\n");

	
}

void remapIRQ()
{
	//PIC umprogrammierung
	outb(MASTER_PIC_COM, PIC_INIT);
	waitIO();
	outb(SLAVE_PIC_COM, PIC_INIT);
	waitIO();
	outb(MASTER_PIC_DAT, 0x20);
	waitIO();	
	outb(SLAVE_PIC_DAT,  0x28);
	waitIO();	
	outb(MASTER_PIC_DAT, 0x4);
	waitIO();	
	outb(SLAVE_PIC_DAT, 0x2);
	waitIO();	
	outb(MASTER_PIC_DAT, 0x1);
	waitIO();	
	outb(SLAVE_PIC_DAT, 0x1);
	waitIO();	
	outb(MASTER_PIC_DAT, 0x0);
	waitIO();
	outb(SLAVE_PIC_DAT, 0x0);
	waitIO();
		
	kprint("- IRQ's umgestellt. Interrupts 50-66\n");
}

//rechner neustarten
//TODO: macht probleme
void reboot()
{
	outb(0x64, 0xFE);
}

