extern __errno_location

section .text
	global ft_write

ft_write:
	mov rax, 1
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

; pie -> alsr (address space layout randomization) -> de base adresses absolues hardcodées, maintenant relatives, donc on doit les chercher avec plt