	.file	"while.c"
	.text
	.globl	pcount_while
	.type	pcount_while, @function
pcount_while:
.LFB0:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L4
	movl	$0, %eax
	.p2align 4
.L3:
	movq	%rdi, %rdx
	andl	$1, %edx
	addq	%rdx, %rax
	shrq	%rdi
	jne	.L3
	ret
.L4:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	pcount_while, .-pcount_while
	.globl	pcount_goto_jtm
	.type	pcount_goto_jtm, @function
pcount_goto_jtm:
.LFB1:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L9
	movl	$0, %eax
	.p2align 4
.L8:
	movq	%rdi, %rdx
	andl	$1, %edx
	addq	%rdx, %rax
	shrq	%rdi
	jne	.L8
	ret
.L9:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	pcount_goto_jtm, .-pcount_goto_jtm
	.globl	pcount_goto_dw
	.type	pcount_goto_dw, @function
pcount_goto_dw:
.LFB2:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L14
	movl	$0, %eax
	.p2align 4
.L13:
	movq	%rdi, %rdx
	andl	$1, %edx
	addq	%rdx, %rax
	shrq	%rdi
	jne	.L13
	ret
.L14:
	movl	$0, %eax
.L12:
	ret
	.cfi_endproc
.LFE2:
	.size	pcount_goto_dw, .-pcount_goto_dw
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
