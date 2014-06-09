/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

#ifndef _KEYBOARD_H
#define _KEYBOARD_H

/**
*\file keyboard.h
*\brief Implementiert Tastaturtreiber
*
*/

#include "..\drivers\timer\timer.h"

#define KB_BUFFER_MAX 1024

/**
*\enum KB_PORTS
*\brief Tastatur I/O Ports
*
*/
enum KB_PORTS
{
	KB_PORT1_DATA = 0x60,
	KB_PORT1_COMM = 0x61,
	KB_PORT2_DATA = 0x64,
	KB_PORT2_COMM = 0x64
};

/**
*\struct KBBuffer
*\brief Interner Tastaturpuffer, für Speicherung von eingebenen Tasten
*
*/
struct KBBuffer
{
	int index;
	char buffer[KB_BUFFER_MAX];
};

//unsigned char deKeymap[128];

//unsigned char buffer[256];

/**
*\brief Liest ein Zeichen von der Tastatur
*
*@return Zeichen/Tastenschlag
*/
unsigned char _kbGetChar();

/**
*\brief Liest ein String von der Tastatur
*
*@param str String, der eingelesen werden soll
*@return Anzahl der gelesenen Zeichen
*/
int _kbGetStr(char *str);
	

#endif
