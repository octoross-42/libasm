section .text
	global ft_strcmp

ft_strcmp:
	xor rax, rax
	xor r10d, r10d
	.loop:
		mov r10b, [rdi + rax]
		cmp r10b, [rsi + rax]
		jne .return
		test r10b, r10b
		jz .return
		inc rax
		jmp .loop
	.return:
		movzx eax, byte [rsi + rax]
		sub eax, r10d
		ret


section .note.GNU-stack noexec