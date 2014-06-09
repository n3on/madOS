;jmp _kernelEntry

;zwischenstuffe weil linker ld sonst probleme macht

bits 32

extern _main
global _kernelEntry

_kernelEntry:
	call _main ;lade hauptkernelfunktion
	
	cli
	hlt
	
;times 512-($-$$) db 0
	