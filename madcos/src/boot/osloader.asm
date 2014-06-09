;===================================
;(c)2008 by MADCrew all rights reserved
;Marcel S., Dmitrij M.
;===================================
	
bits 16

jmp loader2

%include "bootloader.inc"
	

;gdt tabellen
gdt_table1:
	dd 0
	dd 0  ;sollen 0 sein
	
gdt_code_desc:	
	;codesegment
	dw 0xffffffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0
	
gdt_data_desc:	
	;datensegment
	dw 0xffffffff ;segment grenze
	dw 0x0    ; base adresse
	db 0x0
	db 10010010b ; zugriff rechte
	db 11001111b ; 
	db 0
	
gdt_table1_end:
gdt1: ; zeiger auf gdt structur
	dw gdt_table1_end - gdt_table1 - 1 ; größe der tabelle
	dd gdt_table1 ;adresse
	
loader2:
	org 0x7e00
	
	cli 
		;mov eax, cs
		xor ax, ax
		mov ds, ax
		;erstelle stack
		mov ss, ax
		mov sp, 0xffff	
	sti
	
	mov ax, newline
	call writeStr
	
	mov ax, loadmsg
	mov bx, TXT_GREEN
	call writeStr
	
	
	fatLoadRoot:
		xor cx, cx
		xor dx, dx
		;berechne die anzahl der rootsektoren (=32*Anzahl der Rooteinträge/Sektorgröße)
		mov ax, 0x0020
		mul WORD[RootEntryCount]
		div WORD[BytesPerSector]
		xchg ax, cx
		;cx hat jetzt die anzahl der root sektoren
	
		;berechne die adresse
		;anzahl der fat tabellen * fat tabellengröße + reservierte sektoren
		mov al, BYTE[NumFATs]
		mul WORD[FATSize]
		add ax, WORD[ReservedSectors]
	
		mov WORD[datasector], ax
		add WORD[datasector], cx
	
		;lade die root tabelle
		mov bx, fatRootAddr
		call readSectors
		
		mov cx, WORD[RootEntryCount]
		mov di, fatRootAddr
		
	fatFindKernel_find_loop:
		push cx ;
		mov cx, 11 ;vergleiche 11 bytes(dateinamegörße)
		mov si, kernelFile ;name von dem osloader
		push di
		rep cmpsb
		pop di
		je fatLoadFAT ;gefunden
		pop cx
		add di, 0x0020 ;sonst suche den nöchsten eintrag
		loop fatFindKernel_find_loop
		mov ax, kernelNotFound
		mov bx, TXT_RED
		call writeStr
	
	fatLoadFAT:
		mov ax, kernelFound
		mov bx, TXT_WHITE
		call writeStr
		mov dx, WORD[di+0x001A]
		mov WORD[kernel], dx
		xor ax, ax
		mov al, BYTE[NumFATs]
		mul WORD[FATSize]
		mov cx, ax
		mov ax, WORD[ReservedSectors]
		mov bx, fatFatAddr
		call readSectors	
	
	fatLoadKernel_load:	
		xor ax, ax
		pop es
		mov bx, 0xA000
		push bx	
		fatLoadKernel_load_load:
		mov ax, WORD[kernel]
		pop bx
		call CHSToLBA
		xor cx, cx
		mov cl, BYTE[SectorPerCluster]
		call readSectors
		push bx
		mov ax, WORD[kernel]
		mov cx, ax
		mov dx, ax
		shr dx, 0x0001
		add cx, dx
		mov bx, fatFatAddr
		add bx, cx
		mov dx, WORD[bx]
		test ax, 0x0001
		jnz  fatLoadKernel_load_odd     
		fatLoadKernel_load_even:
			and     dx, 0000111111111111b               
			jmp     fatLoadKernel_load_done
		fatLoadKernel_load_odd:
			shr     dx, 0x0004                          
		fatLoadKernel_load_done:
			mov     WORD [osLoader], dx                  
			cmp     dx, 0x0FF0                          
			jb      fatLoadKernel_load_load
          	
	mov ax, newline
	call writeStr
	
	mov ax, pressKeyMsg
	mov bx, TXT_WHITE
	call writeStr
	
	xor ah, ah
	int 0x16
	
	;schalte wieder in textmodus
	mov ah, 0
	mov al, 0x03
	int 0x10
	
	;A20 gate aktivieren
	mov ax, 0x2401
	int 0x15
	
	cli
	lgdt [gdt1]

	;cpu in den protected mode umschalten
	mov eax, cr0
	or  eax, 1
	mov cr0, eax
	;sti
	
	jmp 0x8:loader2_32
	
	;cli
	;hlt
	
bits 32	
loader2_32:
		
	mov ax, 0x10
	
	mov ds, ax
	mov es, ax
	mov ss, ax
	
	xor ax, ax
	mov fs, ax
	mov gs, ax
	mov esp, 0x1FFFF
	
	
	jmp 0x8:0xA000
	
	cli
	hlt
		
newline db 13,10,0
loadmsg db "[OSLoader geladen]",13,10,0
kernelFound	  db  "[madkr.bin gefunden]",13,10,0	
kernelNotFound db "[Datei madkr.bin nicht gefunden]",13,10,0	
pressKeyMsg    db "[Bitte eine Taste druecken]",13,10,13,10,0	
