	.file	"for.c"
	.text
	.globl	pcount_for
	.type	pcount_for, @function
pcount_for:
.LFB11:
	.cfi_startproc
	movl	$0, %edx
	movl	$0, %ecx
	jmp	.L2
	.p2align 5
.L3:
	movq	%rdi, %rax
	shrq	%cl, %rax
	andl	$1, %eax
	addq	%rax, %rdx
	addq	$1, %rcx
.L2:
	cmpq	$31, %rcx
	jbe	.L3
	movq	%rdx, %rax
	ret
	.cfi_endproc
.LFE11:
	.size	pcount_for, .-pcount_for
	.globl	pcount_while
	.type	pcount_while, @function
pcount_while:
.LFB12:
	.cfi_startproc
	movl	$0, %edx
	movl	$0, %ecx
	jmp	.L5
	.p2align 5
.L6:
	movq	%rdi, %rax
	shrq	%cl, %rax
	andl	$1, %eax
	addq	%rax, %rdx
	addq	$1, %rcx
.L5:
	cmpq	$31, %rcx
	jbe	.L6
	movq	%rdx, %rax
	ret
	.cfi_endproc
.LFE12:
	.size	pcount_while, .-pcount_while
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
