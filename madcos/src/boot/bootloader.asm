;===================================
;(c)2008 by MADCrew all rights reserved
;Marcel S., Dmitrij M.
;===================================

;Bootloader
;BIOS lädt den B ootloader an die Adresse 0x0000:0x7c00
;vom ersten Sektor. Der Bootloader liest das FAT Format und 
;sucht nach dem OSLoader auf der Diskette.
;Dannach wird der OSLoader geladen und ausgeführt

org 0x0

;16 bits reals mode
bits 16

;variablen und funktiondefinitionen überspringen
jmp bootMain		


;include
%include "bootloader.inc"

;====Hauptprogramm
bootMain:

	cli
		;datensegment auf 0 setzen
		mov ax,origin		
		mov ds, ax
		mov es, ax
	
		;erstelle stack
		mov ax, bootL1Stack
		mov sp, ax
		xor ax, ax
		mov ss, ax
	sti
	
	; schalte in den grafikmodus um 
	;80x30  Text und  640x480 Grafik 
	mov ah, 0
	mov al, 0x012
	int 0x10
	
	;laufwerk für eventuelle weitere benutzung speichern
	mov [DriverNum], dl
	
	;statusmeldungen
	mov ax, startstr
	mov bx, TXT_GREEN
	call writeStr
	
	;initialisiere fat 12 dateisystem
	call initializeFAT
	;lade osloader
	call loadFile
		
	;wenn der code bisher kommt, dann gabs fehler -> schalte interrupts aus und halte cpu an	
	cli
	hlt
	
;======================funktionen==========================================
	
initializeFAT:
	;fat root directory laden
	call fatLoadRoot
	ret
	
loadFile:
	;osloader auf diskette suchen und ausführen
	call fatFindOSLoader_find
	ret
	
fatLoadRoot:
	;berechne die anzahl der rootsektoren (=32*Anzahl der Rooteinträge/Sektorgröße)
	xor dx, dx
	mov ax, 0x0020 ; rootsektor=32 byte
	mul WORD[RootEntryCount] ; anzahl der einträge
	div WORD[BytesPerSector] ; anzahl der bytes pro sektor(standart 512)
	xchg ax, cx
	;cx hat jetzt die anzahl der root sektoren
	
	;berechne die adresse
	;anzahl der fat tabellen * fat tabellengröße + reservierte sektoren
	mov al, BYTE[NumFATs] ; anzahl der fat tabellen(2 für redundanz)
	mul WORD[FATSize] ;größe der root tabelle
	add ax, WORD[ReservedSectors] ;mögliche reservierte sektoren
	
	mov WORD[datasector], ax
	add WORD[datasector], cx
	
	;lade die root tabelle nach es:0x0300
	mov bx, fatRootAddr
	call readSectors
		
	ret
		
;finde osloader datei		
fatFindOSLoader_find:
	mov cx, WORD[RootEntryCount]
	mov di, fatRootAddr
	fatFindOSLoader_find_loop:
	push cx ;
	mov cx, 11 ;vergleiche 11 bytes(dateinamegörße)
	mov si, osldrFile ;name von dem osloader
	push di
	rep cmpsb
	pop di
	je fatLoadFAT ;gefunden
	pop cx
	add di, 0x0020 ;sonst suche den nöchsten eintrag
	loop fatFindOSLoader_find_loop
	mov ax, osldrNotFound ;osloader konnte nicht gefunden werden
	mov bx, TXT_RED
	call writeStr
	ret
	
;fat tabelle in den speicher laden	
fatLoadFAT:
	;statusmeldung: osloader gefunden
	mov ax, osldrFound
	mov bx, TXT_WHITE
	call writeStr
	mov dx, WORD[di+0x001A]
	mov WORD[osLoader], dx ; speichere osloader adresse
	xor ax, ax
	;lade fat tabelle
	mov al, BYTE[NumFATs]
	mul WORD[FATSize] ; groesse berechnen und nach cx speichern
	mov cx, ax
	mov ax, WORD[ReservedSectors] ;reservierte sektoren dazuaddieren
	mov bx, fatFatAddr ;adresse von dem buffer(wohin die fat tabelle speichern)
	call readSectors ;sektoren lesen, die fat tabelle enthalten
	call fatLoadOSLoader_load ; lade osloader
	ret	
	
fatLoadOSLoader_load:
	push WORD 0x0
	pop es ;adressierung erfolgt mit es:bs, für vereinfachung es=0
	mov bx, osLoaderAddr         
	push bx	
	fatLoadOSLoader_load_load:
	mov ax, WORD[osLoader] ;osLoader sektor
	pop bx
	call CHSToLBA ; wandele cluster, head, sektor diskettennummerierung in logische nummerierung
	xor cx, cx
	mov cl, BYTE[SectorPerCluster]
	call readSectors
	push bx
	mov ax, WORD[osLoader] ;osloader cluster
	;teste ob cluster gerade oder ungerade is
	mov cx, ax 
	mov dx, ax
	shr dx, 0x0001
	add cx, dx
	mov bx, fatFatAddr
	add bx, cx
	mov dx, WORD[bx]
    test ax, 0x0001
	jnz  fatLoadOSLoader_load_odd     
    fatLoadOSLoader_load_even:
      and     dx, 0000111111111111b        ;12 unteren bits nehmen       
      jmp     fatLoadOSLoader_load_done
    fatLoadOSLoader_load_odd:
      shr     dx, 0x0004                   ;12 oberen bits nehmen       
    fatLoadOSLoader_load_done:
      mov     WORD [osLoader], dx                  
      cmp     dx, 0x0FF0   ;ende der datei erreicht?                
      jb      fatLoadOSLoader_load_load
	
	call jump_osloader ;osloader ausführen
	ret
	
jump_osloader:
	jmp 0x0000:osLoaderAddr ;osloader ausführen
	ret
	
	
;=========================================Variablen======================================	
	
startstr db 		 "[Bootloader geladen]",13,10,0
osldrNotFound db	 "[Datei osldr.bin nicht gefunden]",13,10,0
osldrFound	  db     "[osldr.bin gefunden]",13,10,0
	
	
;binary größe muss 512 bytes sein
;2 bytes sind für signatur reserviert 
times 510-($-$$) db 0
dw bootSignature
