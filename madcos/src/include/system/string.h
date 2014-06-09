/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file string.h
*\brief Stellt String und Speicherfunktionen zur verfuegung
*
*/
#ifndef _STRING_H_
#define _STRING_H_

/**
*\brief Setzt eine bestimmte Speicherzelle, auf einen bestimmten Wert
*
*@param dst Zieladresse, vohin geschrieben werden soll
*@param value Werte, auf den die Speicheradresse gesetzt wird
*@param num Anzahl der Zeichen/Bytes die geschrieben werden
*@return Zieladresse
*/
unsigned char* memset(unsigned char *dst, unsigned char value, int num);

/**
*\brief Setzt eine bestimmte Speicherzelle, auf einen bestimmten Wert
*
*@param dst Zieladresse, vohin geschrieben werden soll
*@param value Werte, auf den die Speicheradresse gesetzt wird
*@param num Anzahl der Zeichen/Bytes die geschrieben werden
*@return Zieladresse
*/
unsigned char* memsetw(unsigned short *dst, unsigned short value, int num);

/**
*\brief Kopierte den Wert einer Speicherzelle auf die andere
*
*@param dst Zieladresse, vohin geschrieben werden soll
*@param src Quelladresse, von wo kopiert werden soll
*@param num Anzahl der Zeichen/Bytes die kopiert werden
*@return Zieladresse
*/
unsigned short* memcpyw(unsigned short *dst, unsigned short *src, int num);
/**
*\brief Vergleicht zwei string
*
*@param str1 String 1
*@param str2 String 2
*@return 0 wenn strings gleich sind
*/
int strcmp(char *str1, char *str2);
/**
*\brief Entfernt alle Leerzeichen im String
*
*@param str Eingabestring mit Leerzeichen
*@param str2 Ausgabestring ohne leerzeichen
*/
void unspace(char *str, char *str2);
/**
*\brief Entfernt alle Leerzeichen am Stringanfang und Stringende
*
*@param input Eingabestring mit Leerzeichen
*@param output Ausgabestring ohne leerzeichen
*/
void trim(char *input, char *output);
/**
*\brief Berechne Anzahl der Zeichen im String
*
*@param str Eingabestring
*@return Anzahl der Zeichen im String
*/
int strlen(char *str);

/**
*\brief Zerlege String in zwei Teilstring
*
*@param input Eingabestring
*@param output 2 Ausgabestring
*@param token zeichen, der als Zerlegunszeichen gilt
*/
void tokanize(char *input, char output[2][256], char token);

/**
*\brief Wandele String in Zahl um(Diese Funktion ist noch nicht vollständig implementiert)
*
*@param input Zahl als String
*@return Zahl als Integer
*/
int atoi(char *input);

#endif
