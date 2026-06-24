; strlen, segfault when the first argument isnt a valid pointer, and potentianlly segfault if the pointer doesnt end in a '\0' and memory goes forbidden access 

section .text
    global ft_strlen


ft_strlen:
	xor rax, rax
	.loop:
		mov r10b, [rdi + rax]
		test r10b, r10b
		jz .return
		inc rax
		jmp .loop
	.return:
		ret

section .note.GNU-stack noexec