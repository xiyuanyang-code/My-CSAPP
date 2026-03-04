	.file	"p_countr.c"
	.intel_syntax noprefix
	.text
	.globl	pcount_r
	.type	pcount_r, @function
pcount_r:
	push	rbp
	mov	rbp, rsp
	push	rbx
	sub	rsp, 24
	mov	QWORD PTR [rbp-24], rdi
	cmp	QWORD PTR [rbp-24], 0
	jne	.L2
	mov	eax, 0
	jmp	.L3
.L2:
	mov	rax, QWORD PTR [rbp-24]
	and	eax, 1
	mov	rbx, rax
	mov	rax, QWORD PTR [rbp-24]
	shr	rax
	mov	rdi, rax
	call	pcount_r
	add	rax, rbx
.L3:
	mov	rbx, QWORD PTR [rbp-8]
	leave
	ret
	.size	pcount_r, .-pcount_r
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
