	.file	"incr.c"
	.intel_syntax noprefix
	.text
	.globl	incr
	.type	incr, @function
incr:
	push	rbp
	mov	rbp, rsp
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-8], rax
	mov	rdx, QWORD PTR [rbp-8]
	mov	rax, QWORD PTR [rbp-32]
	add	rax, rdx
	mov	QWORD PTR [rbp-16], rax
	mov	rax, QWORD PTR [rbp-24]
	mov	rdx, QWORD PTR [rbp-16]
	mov	QWORD PTR [rax], rdx
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	ret
	.size	incr, .-incr
	.globl	call_incr
	.type	call_incr, @function
call_incr:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 16
	mov	QWORD PTR [rbp-16], 15213
	lea	rax, [rbp-16]
	mov	esi, 3000
	mov	rdi, rax
	call	incr
	mov	QWORD PTR [rbp-8], rax
	mov	rdx, QWORD PTR [rbp-16]
	mov	rax, QWORD PTR [rbp-8]
	add	rax, rdx
	leave
	ret
	.size	call_incr, .-call_incr
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
