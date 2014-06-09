global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global irq0
global irq1
global irq6

extern _isrException
extern _irqTimer
extern _irqKeyboard
extern _irqFloppy

isr0: 
	pushad
	push 0
	call _isrException
	popad
	iret
	
isr1: 
	pushad
	push 1
	call _isrException
	popad
	iret

isr2: 
	pushad
	push 2
	call _isrException
	popad
	iret	
	
isr3: 
	pushad
	push 3
	call _isrException
	popad
	iret

isr4: 
	pushad
	push 4
	call _isrException
	popad
	iret
	
isr5: 
	pushad
	push 5
	call _isrException
	popad
	iret

isr6: 
	pushad
	push 6
	call _isrException
	popad
	iret	
	
isr7: 
	pushad
	push 7
	call _isrException
	popad
	iret

isr8: 
	pushad
	push 8
	call _isrException
	popad
	iret
	
isr9: 
	pushad
	push 9
	call _isrException
	popad
	iret

isr10: 
	pushad
	push 10
	call _isrException
	popad
	iret	
	
isr11: 
	pushad
	push 11
	call _isrException
	popad
	iret

isr12: 
	pushad
	push 12
	call _isrException
	popad
	iret
	
isr13: 
	pushad
	push 13
	call _isrException
	popad
	iret

isr14: 
	pushad
	push 14
	call _isrException
	popad
	iret	
	
isr15: 
	pushad
	push 15
	call _isrException
	popad
	iret

isr16: 
	pushad
	push 16
	call _isrException
	popad
	iret	
	
isr17: 
	pushad
	push 17
	call _isrException
	popad
	iret	
	

isr18: 
	pushad
	push 18
	call _isrException
	popad
	iret

isr19: 
	pushad
	push 19
	call _isrException
	popad
	iret

isr20: 
	pushad
	push 20
	call _isrException
	popad
	iret
	
isr21: 
	pushad
	push 21
	call _isrException
	popad
	iret

isr22: 
	pushad
	push 22
	call _isrException
	popad
	iret	
	
isr23: 
	pushad
	push 23
	call _isrException
	popad
	iret

isr24: 
	pushad
	push 24
	call _isrException
	popad
	iret	
	
isr25: 
	pushad
	push 25
	call _isrException
	popad
	iret	
	

isr26: 
	pushad
	push 26
	call _isrException
	popad
	iret

isr27: 
	pushad
	push 27
	call _isrException
	popad
	iret

isr28: 
	pushad
	push 28
	call _isrException
	popad
	iret	
	
isr29: 
	pushad
	push 29
	call _isrException
	popad
	iret

isr30: 
	pushad
	push 30
	call _isrException
	popad
	iret	
	
isr31: 
	pushad
	push 31
	call _isrException
	popad
	iret		

irq0:
	pushad
	call _irqTimer
	popad
	iret
	
irq1:
	pushad
	call _irqKeyboard
	popad
	iret
	
irq6:
	pushad
	call _irqFloppy
	popad
	iret	
	
	