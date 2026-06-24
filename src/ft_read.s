extern __errno_location

section .text
	global ft_read

ft_read:
	mov rax, 0
	syscall
	test rax, rax
	js .error
	ret
.error:
	neg rax
	mov r10d, eax
	call __errno_location wrt ..plt ; wrt = with respect to, plt = procedure linkage table
	mov dword [rax], r10d
	mov rax, -1
	ret

section .note.GNU-stack noexec