global x86_outb
global x86_inb
global x86_enable_interrupts
global x86_disable_interrupts

x86_outb:
    mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

x86_inb:
    mov dx, [esp + 4]
    xor eax, eax
    in al, dx
    ret

x86_enable_interrupts:
	sti
	ret

x86_disable_interrupts:
	cli
	ret