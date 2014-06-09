/***********************************
 (c)2008 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
***********************************/

/**
*\file sys.h
*\brief Stellt Systemfunktionen zur verfuegung
*
*/
#ifndef _SYS_H_
#define _SYS_H_

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

#endif
