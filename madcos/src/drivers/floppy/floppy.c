/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

#include "floppy.h"

void floppy_init()
{
	floppy_irq      = 0;
	floppy_motor_on = 0;
	
	floppy_motorOn();
	floppy_reset();
	
	//dma initialisieren
	outb(0x0a, 0x06);
	outb(0x0c, 0xff);
	//outb(0x04, );
}

void floppy_motorOn()
{
	if(!floppy_motor_on)
	{
		outb(FP_DIGITAL_OUTPUT_REGISTER,0x1c);
		timerSleep(100);
		floppy_motor_on=1;
	}
}

void floppy_motorOff()
{
	if(floppy_motor_on)
	{
		outb(FP_DIGITAL_OUTPUT_REGISTER,0x0c);
		timerSleep(100);
	}
}

void floppy_waitIrq()
{
	while(floppy_irq==0);
	
	floppy_irq=0;
}

void floppy_calibrate()
{
	floppy_out(FC_RECALIBRATE);
	floppy_out(0x0); //driver
		
	floppy_waitIrq();
		
	floppy_out(FC_SENSE_INTERRUPT);
	floppy_read(FP_STATUS_REGISTER_A);
	floppy_read(FP_STATUS_REGISTER_A);
	
}

void floppy_reset()
{
	outb(FP_DIGITAL_OUTPUT_REGISTER,0x00);
	outb(FP_DIGITAL_OUTPUT_REGISTER,0x0C);	
	floppy_waitIrq();
	floppy_out(FC_SENSE_INTERRUPT);
	floppy_read(FP_STATUS_REGISTER_A);
	floppy_read(FP_STATUS_REGISTER_A); 
	
	//geschwindigkeit auf 500 kb/s setzen
	outb(FP_CONFIGURATION_CONTROL_REGISTER, 0x00);
	
	floppy_out(FC_SPECIFY);
	floppy_out(0xdf);
	floppy_out(0x02);
	
	floppy_calibrate();
	
	kprint("\nFloppy zurueckgesetzt\n");
}

void floppy_out(char cmd)
{
	int counter=0;
	
	while(((inb(FP_MAIN_STATUS_REGISTER) & 0x80)==0))
	{
		if(counter>=90)
		{
			kprint("\nFloppy Schreibzugriff Zeitueberschreitung\n");
			break;
		}
		
		counter++;
		timerSleep(10);
	}
	
	//kprint("\nFloppy Daten geschrieben\n");
	outb(FP_DATA_FIFO, cmd);
	waitIO();
}

unsigned char floppy_read(unsigned short port)
{
	int counter=0;
	unsigned char in=0;
	
	while(((inb(FP_MAIN_STATUS_REGISTER) & 0x80)==0))
	{
		if(counter>=90)
		{
			kprint("\nFloppy Lesezugriff Zeitueberschreitung\n");
			break;
		}
		
		counter++;
		timerSleep(10);
	}
	
	//kprint("\nFloppy Daten gelesen\n");
	timerSleep(1);
	waitIO();
	in=inb(FP_DATA_FIFO);
	waitIO();
	
	return in;
}

void floppy_set(int head, int cylinder)
{
	int i;
	
	while(i<10)
	{
		floppy_out(FC_SEEK);
		floppy_out(head<<2);
		floppy_out(cylinder);
		
		floppy_waitIrq();
		
		floppy_out(FC_SENSE_INTERRUPT);
		floppy_read(FP_STATUS_REGISTER_A);
		floppy_read(FP_STATUS_REGISTER_A);

 		
	}
	
}


