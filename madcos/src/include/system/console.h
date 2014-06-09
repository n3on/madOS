/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file console.h
*\brief Implementiert die Kernelkonsole
*
*/

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "sys.h"
#include "..\drivers\keyboard\keyboard.h"
#include "..\drivers\floppy\floppy.h"
#include "..\drivers\timer\timer.h"

/**
*\enum TEXT_COLOR
*\brief Farbaufzaehlung fuer Textausgabe
*
*Enthaelt Farbkonstanten, die von Ausgabefunktion verwendet werden.
*/
enum TEXT_COLOR
{
   CL_BLACK = 0,  /**Schwarz*/ 
   CL_BLUE,			/**Blau*/ 
   CL_GREEN ,       /**Gruen*/ 
   CL_CYAN,         /**Tuerkis*/ 
   CL_RED,          /**Rot*/ 
   CL_MAGENTA,      /**Magenta*/ 
   CL_BROWN,        /**Braun*/ 
   CL_LIGHT_GRAY,   /**Hellgrau*/ 
   CL_DARK_GRAY,    /**Dunkelgrau*/ 
   CL_LIGHT_BLUE,   /**Hellblau*/ 
   CL_LIGHT_GREEN,  /**Hellgruen*/ 
   CL_LIGHT_CYAN,   /**Helltuerkis*/ 
   CL_LIGHT_RED,    /**Hellrot*/ 
   CL_LIGHT_MAGENTA,/**Hellmagenta*/ 
   CL_LIGHT_BROWN,  /**Hellbraun*/  
   CL_WHITE         /**Weiss*/ 
};

/**
*\struct Console
*\brief Struktur, die die gesamte Kernel Konsole repraesentiert
*
*Diese Struktur enthaelt Elemente, die die Kernel Konsole repaersentieren
*/
struct Console
{
	enum TEXT_COLOR fgColor; /**Fordergrundfarbe */ 
	enum TEXT_COLOR bgColor; /**Hintergrundfarbe */ 
	enum TEXT_COLOR clColor; /**Konsolenfarbe */ 
	unsigned char numX;      /**Textbreite der Konsole */ 
	unsigned char numY;      /**Texthoehe der Konsole */
	unsigned char cursor_x;  /**Cursor x Position */ 
	unsigned char cursor_y;  /**Cursor y Position */ 
	unsigned char tabWidth;  /**Breite von dem Tabzeichen */
	unsigned short *video;   /**Zeiger auf den Textausgabespeicher */ 	
	int blink;
};

/**
*\brief Initialisiert die Kernel Konsole
*
*Diese Funktion fuellt die Struktur Console mit Werten aus und initialisiert somit die Kernel Konsole
*/
void initConsole();
/**
*\brief Gibt ein C String aus.
*
*@param str Zeichenkette, die ausgegeben wird
*/
void kprint(char *str);
/**
*\brief Gibt einen Buchstaben aus
*
*@param c Buchstabe, der ausgegeben wird
*/
void kputchar(char c);
/**
*\brief Loescht den Bildschirminhalt auf die aktuelle Farbe
*
*/
void clearScreen();
/**
*\brief Setzt die Farbe für die clearScreen Funktion
*
*@param color Farbe für die clearScreen Funktion
*/
void setClearColor(enum TEXT_COLOR color);
/**
*\brief Setzt die Schrift Hintergrundfarbe
*
*@param color Schrift Hintergrundfarbe
*/
void setBgColor(enum TEXT_COLOR color);
/**
*\brief gibt die aktuelle Hintergrundfarbe zurueck
*
*/
enum TEXT_COLOR getBgColor();
/**
*\brief Setzt die Schrift Fordergrundgrundfarbe
*
*@param color Schrift Fordergrundfarbe
*/
void setFgColor(enum TEXT_COLOR color);
/**
*\brief gibt die aktuelle Vordergrundfarbe zurueck
*
*/
enum TEXT_COLOR getFgColor();

/**
*\brief aktiviere schriftblinker
*
*@param blinker blinker aktivieren
*/
void setBlink(int blinker);

/**
*\brief Minimale Position in der Konsole fessetzen
*
*@param x minimale X Position
*@param y minimale Y Position
*/
void setMinPosition(unsigned char x, unsigned char y);

/**
*\brief Die Aktuelle Buchstabenposition wird auf den Console X, Y Wert gesetzt
*
*/
void updateCursor();
/**
*\brief Setzt den  aktuellen Cursor X, Y Wert
*
*@param x X-Position
*@param y Y-Position
*/
void setCursor(int x, int y);
/**
*\brief Aktuallisiere den binkenden Hardwarecursor
*
*/
void updateHrdCursor();

/**
*\brief Startet Befehl Ein/Ausgabe für die Konsole
*
*/
void startConsole();

/**
*\brief Führt die Eingegebene Befehle aus
*
*@param command Befehl
*/
int processCommand(char *command);

/**
*\brief Runterscrollen, wenn die Konsole zu voll wird
*
*/
void scrollDown();

#endif
