/****************************************
 (c)2008-2009 by MADCrew all rights reserved
 Marcel S., Dmitrij M.
****************************************/

/**
*\file kernel.c
*\brief Haupteintritt fuer den Kernel
*
*/

#include <system\init.h>
#include <system\console.h>
#include <system\interrupts.h>

//hautpkernelfunktion
int _main()
{
  //initialisieren kernelumgebung
  init();

  //konsole starten
  startConsole();
  
  //while(1);
  
  return 0;
}
