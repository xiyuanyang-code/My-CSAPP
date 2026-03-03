	.file	"multstore.c"
	.intel_syntax noprefix
	.text
	.globl	mult2
	.type	mult2, @function
mult2:
	push	rbp
	mov	rbp, rsp
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	rax, QWORD PTR [rbp-24]
	imul	rax, QWORD PTR [rbp-32]
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-8]
	pop	rbp
	ret
	.size	mult2, .-mult2
	.globl	multstore
	.type	multstore, @function
multstore:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	QWORD PTR [rbp-24], rdi
	mov	QWORD PTR [rbp-32], rsi
	mov	QWORD PTR [rbp-40], rdx
	mov	rdx, QWORD PTR [rbp-32]
	mov	rax, QWORD PTR [rbp-24]
	mov	rsi, rdx
	mov	rdi, rax
	call	mult2
	mov	QWORD PTR [rbp-8], rax
	mov	rax, QWORD PTR [rbp-40]
	mov	rdx, QWORD PTR [rbp-8]
	mov	QWORD PTR [rax], rdx
	nop
	leave
	ret
	.size	multstore, .-multstore
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
