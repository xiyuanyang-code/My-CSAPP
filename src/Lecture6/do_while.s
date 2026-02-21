	.file	"do_while.c"
	.text
	.globl	pcount_do
	.type	pcount_do, @function
pcount_do:
.LFB0:
	.cfi_startproc
	movl	$0, %edx
	.p2align 5
.L2:
	movq	%rdi, %rax
	andl	$1, %eax
	addq	%rdx, %rax
	movq	%rax, %rdx
	shrq	%rdi
	jne	.L2
	ret
	.cfi_endproc
.LFE0:
	.size	pcount_do, .-pcount_do
	.globl	pcount_goto
	.type	pcount_goto, @function
pcount_goto:
.LFB1:
	.cfi_startproc
	movl	$0, %edx
	.p2align 5
.L4:
	movq	%rdi, %rax
	andl	$1, %eax
	addq	%rdx, %rax
	movq	%rax, %rdx
	shrq	%rdi
	jne	.L4
	ret
	.cfi_endproc
.LFE1:
	.size	pcount_goto, .-pcount_goto
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
