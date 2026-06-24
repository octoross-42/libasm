extern malloc
extern ft_strlen

section .text
	global ft_strdup

ft_strdup:
	push rbx
	mov rbx, rdi
	call ft_strlen
	mov rdi, rax
	inc rdi
	call malloc wrt ..plt
	test rax, rax
	jz .return
	xor rdi, rdi
	.loop:
		mov r10b, [rbx + rdi]
		mov [rax + rdi], r10b
		test r10b, r10b
		jz .return
		inc rdi
		jmp .loop
.return:
	pop rbx
	ret

section .note.GNU-stack noexec