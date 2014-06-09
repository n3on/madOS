/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

#include <system\sys.h>
#include "keyboard.h"

unsigned char deKeyboard[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8','9', '0', 
	'-', '=', 
	'\b',
    '\t',
     'q', 'w', 'e', 'r','t', 'z', 'u', 'i', 'o', 'p', 
	 '[', ']', '\n',
    0,			//Crt
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 
	';',
    '\'', '`',   0,		//shift(links) 
	'\\', 
	'y', 'x', 'c', 'v', 'b', 'n','m', 
	',', '.', '/',   0,	//shift(rechts)
    '*',
    0,	//Alt 
    ' ', // Space
    0,	// Caps lock 
    0, 0,   0,   0,   0,   0,   0,   0,   0, 0,	//F0-F10
    0,	//Num lock
    0,	// Scroll Lock
    0,	// Home
    0,	// Pfeil auf
    0,	// Page Up
    '-',
    0,	// Pfeil links
    0,
    0,	// Pfeil recht
    '+',
    0,	//End key
    0,	//Pfeil unten
    0,	// Page Down
    0,	//Einfügen
    0,	//Entfernen
    0,   0,   0,
    0,	// F11
    0,	// F12 
    0,	// undefiniert
};

struct KBBuffer _kbBuffer = {0,0};
 
unsigned char _kbGetChar()
{
	
	unsigned char scancode;
	scancode = inb(KB_PORT1_DATA);
	
	if(scancode & 0x80)
	{
		return 254;
	}
	else
	{
		if(_kbBuffer.index>=KB_BUFFER_MAX)
			_kbBuffer.index=0;
		else
			++_kbBuffer.index;
		
		_kbBuffer.buffer[_kbBuffer.index] = deKeyboard[scancode];
		return _kbBuffer.buffer[_kbBuffer.index];
	}
	
	return 255;
}

int _kbGetStr(char *str)
{
	int index=0;
	unsigned char key='\0';
	int numChars;
	
	str[0]='\0';
	key = _kbGetChar();
			
	while(key != '\n')
	{
			
		if(key<254)
		{
			if(index>=KB_BUFFER_MAX)
				index=0;
				
			if(key=='\b')
			{
				if((index>0) && (_kbBuffer.index>0))
				{
					--index;
					--_kbBuffer.index;
					kputchar(key);
				}
				
			}
			else
			{
				str[index] = key;
				++index;
				kputchar(key);
				
			}	
						
		}
		
		key = _kbGetChar();
		timerSleep(50);
	}
	
	str[index] = '\0';
	
	return index;
}

int _kbIsReadable()
{

}
