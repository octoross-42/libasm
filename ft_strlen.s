; hello.asm - My first NASM program!
; This program prints "Hello, Assembly!" to the console

section .text
    global ft_strlen


ft_strlen:
	xor rax, rax
	.loop:
		mov r10b, [rdi + rax]
		
		cmp r10b, 0
		je .return
		inc rax
		jmp .loop
	.return:
		ret

section .note.GNU-stack noalloc noexec nowrite progbits