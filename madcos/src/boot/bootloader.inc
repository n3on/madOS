;====================================
;(c)2008 by MADCrew all rights reserved
;Marcel S., Dmitrij M.
;===================================
%ifndef _MADCOS_BOOTLOADER_INC_
%define _MADCOS_BOOTLOADER_INC_

; BIOS Parameter Block für FAT
OEMName 			db 'MADCOS  '
BytesPerSector 		dw 512
SectorPerCluster 	db 1
ReservedSectors 	dw 1
NumFATs				db 2
RootEntryCount		dw 224
NumSectors			dw 2880
MediaType			db 248
FATSize				dw 9
SectorsPerTrack		dw 18
HeadsNum			dw 2
HiddenSectors		dd 0
TotSec32			dd 0
DriverNum			db 0
NTReserved			db 0
ExtBootSignature: 	db 0x29
SerialNumber		dd 0
VolumeLabel			db 'MADCOS     '
FyleSystemType		db 'FAT12   '

;===configuration defines
;bootloader start adresse
origin equ 0x07c0
;bootsignature
bootSignature equ 0xAA55
;Stack für bootloader
bootL1Stack   equ 0xffff
;OSLoader adresse
osLoaderAddr equ 0x7e00
;name von level 2 bootloader
osldrFile db "OSLDR   BIN"
;kerneldatei
kernelFile db "MADKR   BIN"

datasector dw 0
%define osLoader 0x9999
%define kernel   0x9999
;osLoader dw 0
;kernel   dw 0

;adresse vom FAT12 Rooteintrag
fatRootAddr equ 0x1000
fatFatAddr  equ 0x1000


;argumente für funktionen
%define arg1 [ebp+0x4]
%define arg2 [ebp+0x6]
%define arg3 [ebp+0x8]

;farbwerte für text
TXT_WHITE equ 0x0007
TXT_RED	  equ 0x0004
TXT_GREEN equ 0x0002
TXT_BLUE  equ 0x0001


;===Funktionen

;string ausgabe
;ax: ausgabestring
;bx: textfarbe(falls im videomodus)
writeStr:
	;popa
;;	push ax
;;	push si
	mov si, ax ;zeichenkette laden
	writeChar:
		lodsb
		cmp al, 0 ;stringende erreicht?
		je short writeStrEnd
		mov ah, 0x0E
		int 0x10
		jmp writeChar
	writeStrEnd:
;;		pop si
;;		pop ax
		;pusha
		ret
		
;wandelt die cluster-head-sector adresse in logische adresse um		
;(cluster-2 ) * sektoren pro cluster
CHSToLBA:
	sub ax, 0x0002
	xor cx, cx
	mov cl, BYTE[SectorPerCluster]
	mul cx
	add ax, WORD[datasector]
	ret
	
;wandelt die Logische Sectornummer in die CHS(Cluster, Head, Sector) form
;(Sector)cl=logical sector MOD sectors per track) + 1
;(Head)dh=logical sector / sectors per track) MOD number of heads
;(Track)ch=logical sector / (sectors per track * number of heads)	
LBAToCHS:
	xor dx, dx
	div WORD[SectorsPerTrack]
	inc dl
	;mov BYTE[absSector], dl
	mov cl, dl
	xor dx, dx
	div WORD[HeadsNum]
	;mov BYTE[absHead], dl
	mov dh, dl
	;mov BYTE[absTrack], al
	mov ch, al
	ret

;list sectoren an die adresse es:bx
;ax enthält die logische adresse
;cx die anzahl der sectoren
readSectors:
	read_sectors_start:
		pusha
		xor ax, ax
		mov dl, BYTE[DriverNum]
		int 0x13 ; resete den floppy driver
		popa
		jc read_sectors_start
	read_sectors_read:
		pusha
		call LBAToCHS ;wandele um
		mov ah, 0x2
		mov al, 0x1 ;anzahl der sektoren
		mov dl, BYTE[DriverNum] ;laufwerk
		int 0x13 ;lese den sector
		popa
		jc read_sectors_read
	read_sectors_end:
		add bx, WORD[BytesPerSector]
		inc ax
		loop read_sectors_start
		ret	

%endif 
		