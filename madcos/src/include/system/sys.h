/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file sys.h
*\brief Stellt Systemfunktionen zur verfuegung
*
*/
#ifndef _SYS_H_
#define _SYS_H_

#include <system\interrupts.h>

#define MASTER_PIC_COM 0x20
#define MASTER_PIC_DAT 0x21
#define SLAVE_PIC_COM 0xA0
#define SLAVE_PIC_DAT 0xA1
#define PIC_INIT 0x11
#define PIC_EOI 0x20


/**
*\brief Liest ein Byte aus dem angegebenen Port
*
*@param port Port vom dem gelesen werden soll
*@return Gelesene Byte
*/
unsigned char inb(unsigned short port);
/**
*\brief Schreibt ein Wert/Byte auf den angegebenen Port
*
*@param port Port vohin geschrieben werden soll
*@param value Wert/Byte, der geschrieben wird
*/
void outb(unsigned short port, unsigned char value);

void waitIO();

/**
*\struct GDT
*\brief Diese Struktur enthält die Adresse und Groesse von gdt Tabelle
*
*/
struct GDT
{
   unsigned short limit; /**die groesse der GDT Tabelle*/
   unsigned int   base;  /**Die Adresse der GDT Tabelle*/
} __attribute__((packed));

/**
*\struct GDTDescriptor
*\brief Desktriptoren Beschreiben die einzelne Speichersegmente
*
*/
struct GDTDescriptor
{
	unsigned short size_0_15;  /**Segmentgroesse bits 0-15*/ 
	unsigned short base_0_15;  /**Segmentbasisadresse bits 0-15 */
    unsigned char  base_16_23; /**Segmentbasisadresse bits 16-23 */
    unsigned char  typ;        /** Zugriff und Deskriptortyp */
    unsigned char  annex; /**Zusatz enthält Granualitaet und Segmentgroesse bits 16-19*/		
    unsigned char  base_24_32; /**Segmentbasisadresse bits 24-32*/
} __attribute__((packed)); 

/**
*\struct IDTDescriptor
*\brief IDT Descriptor beschreiben die Interrupts
*
*/
struct  IDTDescriptor
{
   unsigned short base_0_15; /**Basisadresse innerhalb Segments bits 0-15 */
   unsigned short selector; /***/
   unsigned char  zero; /** Muss immer NULL sein*/
   unsigned char  options; /**Beschreiben Deskriptor*/
   unsigned short base_16_31; /**Basisadresse innerhalb Segments bits 16-31*/
} __attribute__((packed));

/**
*\struct IDT
*\brief Diese Struktur enhaelt Adresse und Groesse von IDT
*
*/
struct IDT
{
	unsigned short limit; /**groesse von IDT*/
	unsigned int   base;  /**Adresse von IDT*/
} __attribute__((packed));

/**
*\brief Setzt die GDT Descriptor
*
*@param desc Deskriptor, der ausgefuellt werden soll
*@param start Startadresse
*@param end    Endadresse
*@param type Typ von dem Segment
*/
void setGDTDescriptor(struct GDTDescriptor *desc, unsigned long start, unsigned long end, 
						unsigned char type);

/**
*\brief richte die GDT ein
*
*/
void createGDT();

/**
*\brief Lade die Segmentregister mit neuen GDT Werten
*
*/
void loadGDTTable();

void setIDTGate(struct IDTDescriptor *desc, unsigned int start, unsigned short selector, 
					unsigned char options);
					
/**
*\brief Laed IDT in den Processor
*
*/
void loadIDT();

/**
*\brief Erstellt IDT
*
*/
void createIDT();

/**
*\brief Mappt IRQ auf neue Iterrupt Adressen
*
*/
void remapIRQ();

/**
*\brief Started Computer neu.(Diese Funktion ist noch in entwicklung)
*
*/
void reboot();


#endif
