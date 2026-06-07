section .text
	global ft_strcpy

ft_strcpy:
	xor rax, rax
	.loop:
		mov r10b, [rsi + rax]
		mov [rdi + rax], r10b
		cmp byte [rsi + rax], 0
		je .return
		inc rax
		jmp .loop
	.return:
		mov rax, rdi
		ret

section .note.GNU-stack noexec