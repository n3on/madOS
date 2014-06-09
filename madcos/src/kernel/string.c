/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file string.c
*\brief Stellt String und Speicherfunktionen zur verfuegung
*
*/

#include <system\string.h>

//speicherbereich mit einem wert setzen
unsigned char* memset(unsigned char *dst, unsigned char value, int num)
{
	//solange die anzahl nicht null ist -> setzen
	while(num)
	{
		*dst = value;
		dst++;
		num--;
	}
	
	//zieladresse ausgeben
	return dst;
}

//wie memset nur für größeren datentyp
unsigned char* memsetw(unsigned short *dst, unsigned short value, int num)
{
	while(num)
	{
		*dst = value;
		dst++;
		num--;
	}
	return dst;
}

//speicherebereich kopieren
unsigned char* memcpy(unsigned char *dst, unsigned char *src, int num)
{
	while(num)
	{
		*dst = *src;
		dst++;
		src++;
		num--;
	}
	
	return dst;
}

//wie memcpy nur für gößeren datentyp
unsigned short* memcpyw(unsigned short *dst, unsigned short *src, int num)
{
	while(num)
	{
		*dst = *src;
		dst++;
		src++;
		num--;
	}
	
	return dst;
}

//zwei strings vergleichen
int strcmp(char *str1, char *str2)
{
	//solange sie gleich sind und das erste nicht beendet ist
	while(*str1==*str2)
	{
		if(*str1=='\0')
			return 0;
			
		*str1++;
		*str2++;
	}
	
	return 1;
}

//größe von einem string berechnen
int strlen(char *str)
{
	int numChars=0;
	
	//solange kein stringende vorkommt, den zähler erhöhen
	while(*str != '\0')
	{
		++numChars;
		++str;
	}
	
	return numChars;
}

//alle leerzeichen entfernen
void unspace(char *str, char *str2)
{
	int i;
	int j;
	
	str2[0]='\0';
	
	//string durchgehen und auf leerzeichen prüfen, wenn leerzeichen dann entfernen
	//(in str2 alle zeichen ausser leerzeichen speichern)
	for(i=0; *str!='\0'; ++i)
	{
		if(*str!=' ')
		{
			*str2=*str;
			str2++;
			j++;
		}
		str++;
	}
	
	str2[i]='\0';
	i=0;
	
}

//leerzeichen am stringanfang und stringende entfernen
void trim(char *input, char *output)
{
	int firstSpace = 0; //leerzeichen stringanfang
	int lastSpace  = strlen(input); //leerzeichen stringende
	int size=0; 
	int i;
	
	//letzen leerzeichen am stringanfang suchen
	for(i=0; i<strlen(input); ++i)
	{
		if(input[i]==' ')
			firstSpace++;
		else
			break;
	}
	
	//erstes leerzeichen am stringende suchen
	for(i=strlen(input)-1; i>0 && lastSpace>0; --i)
	{
		if(input[i]==' ')
			lastSpace--;
		else
			break;
	}
	
	//speicher zwischen den leerzeichen in ausgabestring kopieren
	memcpy(output, input+firstSpace, lastSpace-firstSpace);
	
	//mit nullbyte string terminieren
	if((lastSpace>0) && (firstSpace>0))
		output[lastSpace-firstSpace]='\0';
	else
		output[strlen(input)]='\0';
	
}

//zeistrings, die mit durch token getrennt sind in einzelne buffer speichern
void tokanize(char *input, char output[2][256], char token)
{
	int tokenStart= 0;
	int tokenEnd  = 0;
	int i, tokenNum=0;
	
	for(i=0; i<strlen(input); ++i)
	{
		if(input[i]==token)
		{
			tokenStart=i;
			tokenNum++;
			break;
		}
	}
	
	if(tokenStart>0)
	{
		memcpy(output[0], input, tokenStart);
		output[0][tokenStart]='\0';
		memcpy(output[1], input+tokenStart+1, strlen(input));
		output[1][strlen(input)]='\0';
	}
	else
	{
	   memcpy(output[0],input, strlen(input));
	}
	return 0;
}

//string in zahl konvetieren
//TODO: wird noch entwickelt
int atoi(char *input)
{
	int number=0;
	int i=0;
	
	for(i=0; i<strlen(input); ++i)
	{
		//number+=(48-input[i])*10*(i);
	}
	
	return number;
}

