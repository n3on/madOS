/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file console.c
*\brief Implementiert die Kernelkonsole
*
*/

#include <system\console.h>

struct Console console;

//initialisiere konsole, belege mit standartwertten
void initConsole()
{
	//videobuffer adresse
	console.video    = (unsigned short*)0xB8000;
	console.numX     = 80; //breite in zeichen
	console.numY     = 25; //höhe in zeichen
	console.fgColor  = CL_WHITE; //schriftvordergrund
	console.bgColor  = CL_BLACK; //schrifthintergrund
	console.clColor  = CL_BLACK; //konsolenhintergrund
	console.cursor_x = 0; //cursorposiition
	console.cursor_y = 0;
	console.tabWidth = 4; //breite von dem tab zeichen
	console.blink    = 0; //status ob text blinkt
	
}

//ausgabe von einem zeichen
void kputchar(char c)
{
	//newline
	if(c=='\n')
	{
		//gehe eine zeile nach unten
		setCursor(0, ++console.cursor_y);
	}
	//tabulator
	else if(c=='\t')
	{
		//verschiebe x cursor position um tabbreite 
		setCursor(console.cursor_x+console.tabWidth, console.cursor_y);
	}
	//zeichen löschen
	else if(c=='\b')
	{
		//nicht anfang der zeile
		if(console.cursor_x>0)
		{
			//zeichen löschen und x cursor position verringern
			setCursor(--console.cursor_x, console.cursor_y);
			kputchar(' ');
			setCursor(--console.cursor_x, console.cursor_y);
		}
		//anfang der zeile
		else
		{
			//zeichen löschen und y position verringen, um in die obere zeile zu kommen
			setCursor(console.numX, --console.cursor_y);
			kputchar(' ');
			setCursor(console.numX, --console.cursor_y);		
		}
	}
	//alle andere zeichen einfach in den  textbuffer ausgeben
	else
	{	
		//fülle textbuffer mit zeichen und parametern
		console.video[console.cursor_x+console.cursor_y*console.numX] = \
							c |(console.fgColor<<8) | (console.bgColor<<12);
		//verschiebe richtig den cursor
		updateCursor();
	}

}

//string ausgeben
void kprint(char *str)
{	
	int i;
	//jedes zeichen einzeln ausgeben
	for(i=0; str[i]; i++)
	{	
		kputchar(str[i]);
	}
}

//konsolenbildschirm löschen
void clearScreen()
{
	//textbuffer mit leerzeichen füllen und entsprechende farbe als parameter setzen
    int numChars = console.numX*console.numY;
    int i;
	for(i=0; i<numChars; i++)
	{
		console.video[i] = '\0' | (console.clColor<<12);
	}
	
	//cursorposition ist wieder oben links(startposition)
	setCursor(0,0);
}

//konsolenhintergrundfarbe setzen
void setClearColor(enum TEXT_COLOR color)
{
  console.clColor = color;
  console.bgColor = color;
}

//text hintergrundfarbe setzen
void setBgColor(enum TEXT_COLOR color)
{
  console.bgColor = color;
}

enum TEXT_COLOR getBgColor()
{
  return console.bgColor;
}

//text vordergrundfarbe setzen
void setFgColor(enum TEXT_COLOR color)
{
  console.fgColor = color;
}

//schrift blinkt oder nicht?
void setBlink(int blinker)
{
	if(blinker)
		console.blink = 1;
	else
		console.blink = 0;
}

enum TEXT_COLOR getFgColor()
{
  return console.fgColor;
}

//cursorposition setzen
void setCursor(int x, int y)
{
	
	if((x<=console.numX) && (x>=0))
		console.cursor_x=x;	
	else if((x>console.numX) && (x>=0))
	{
		console.cursor_x=0;
		++y;
	}
	else if(x<0)
	{
		console.cursor_x=console.numX-1;
		--console.cursor_y;
	}
		
	console.cursor_y=y;
	if(y>=console.numY)
	{
		console.cursor_y=console.numY-3;
		scrollDown();
	}

	//hardware cursor aktualisieren
	updateHrdCursor();
}

//nach unten scrollen, wenn konsole zu voll ist
void scrollDown()
{
	int i;
	
	//konsolenspeicher um eine zeile nach oben verschieben und die untere zeile löschen
	memcpyw(console.video, console.video+console.numX*3, console.numX*(console.numY-3));
	memsetw(console.video+(console.numX*(console.numY-3)), 
			' ' |(console.clColor<<8) | (console.clColor<<12),
			console.numX*3);
}

//cursor aktualisieren
void updateCursor()
{
	setCursor(++console.cursor_x, console.cursor_y);
}

//hardware cursor aktualisieren
void updateHrdCursor()
{
	unsigned int cursorIndex;
	
	cursorIndex = (console.cursor_x)+console.cursor_y*console.numX;
	
	//vga ports für cursor
	outb(0x3D4, 0xE);
	outb(0x3D5, cursorIndex>>8);
	outb(0x3D4, 0xF);
	outb(0x3D5, cursorIndex);
	
	cursorIndex = 0;
}

//starte befehl ein/ausgabe für die konsole
void startConsole()
{	
	//solange kein abbruch, befehl einlesen und verarbeiten
	int runConsole = 1;
	while(runConsole)
	{
	   char command[256] = {'\0'};
	   kprint("\nsympos > ");
	   _kbGetStr(command);
	   
	   if(processCommand(command)!=0)
			runConsole = 0;
	  	   
		/*unsigned char key = _kbGetChar();
		if(key<255)
			kputchar(key);*/
		
		//zu schnelle bearbeitung verhindern
		timerSleep(50);
	}
	
}

//befehl bearbeiten
int processCommand(char* command)
{
	//speicher für das angegebene befehl
	//char com[256]={'\0'};
	char com[2][256]={'\0','\0'};
	//leerzeichen am anfang und ende löschen
	trim(command, command);
	//befehl - argument trennen(leerzeichen ist trennzeichen)
	tokanize(command, com, ' ');
	
	//debug ausgaben
	/*kprint("\n");
	kprint(com[0]);
	kprint("\n");
	kprint(com[1]);	
	kprint("\n");
	kprint(command);
	kprint('\n');*/
	
	//textfarbe setzen
	setFgColor(CL_LIGHT_GRAY);
	
	//befehle abarbeiten
	if(!strcmp(com[0], "help"))
	{
		kprint("\n\n   =Sympos, Symplatonix Operating System\n");
		kprint("   =(c)2008-2009 Symplatonix Software\n\n");
		setFgColor(CL_RED);
		kprint("   ==Befehle:\n");
		setFgColor(CL_LIGHT_GRAY);
		kprint("   ==help                - Befehlsuerbersicht\n");
		kprint("   ==shutdown            - Computer herunterfahren\n");
		kprint("   ==reboot              - Computer neustarten\n");
		kprint("   ==cls                 - Bildschirm loeschen\n");
		kprint("   ==int interruptNummer - interrupt ausloesen\n\n");
	}
	else if(!strcmp(com[0], "shutdown"))
	{
		kprint("\n\nDer Computer wird heruntergefahren!\n\n");
		return 1;
	}
	else if(!strcmp(com[0], "reboot"))
	{

		kprint("\n\nDer Computer wird neugestarted!\n\n");
		reboot();
	}
	else if(!strcmp(com[0], "cls"))
	{
		clearScreen();
	}
	else if(!strcmp(com[0], "int"))
	{
		unsigned char intNum = atoi(com[1]);
		
		unsigned char intN = 10;
		//asm("int %0;"::"g" (intN));
	}
	//für interne testzwecke
	else if(!strcmp(com[0], "test"))
	{
		floppy_init();
	}
	else
	{
	    kprint("\n\nBefehl [");
		setFgColor(CL_RED);
	    kprint(com[0]);
	    setFgColor(CL_LIGHT_GRAY);
	    kprint("] nicht gefunden!...\n");	
	}
	
	command[0]='\0';
	
	setFgColor(CL_WHITE);

	return 0;
}


