	.file	"licm.c"
	.text
	.globl	set_row
	.type	set_row, @function
set_row:
.LFB0:
	.cfi_startproc
	testq	%rcx, %rcx
	jle	.L1
	imulq	%rcx, %rdx
	leaq	(%rdi,%rdx,8), %rdx
	movl	$0, %eax
	.p2align 5
.L3:
	movsd	(%rsi,%rax,8), %xmm0
	movsd	%xmm0, (%rdx,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %rcx
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	set_row, .-set_row
	.globl	set_row_licm
	.type	set_row_licm, @function
set_row_licm:
.LFB1:
	.cfi_startproc
	testq	%rcx, %rcx
	jle	.L5
	imulq	%rcx, %rdx
	leaq	(%rdi,%rdx,8), %rdx
	movl	$0, %eax
	.p2align 5
.L7:
	movsd	(%rsi,%rax,8), %xmm0
	movsd	%xmm0, (%rdx,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %rcx
	jne	.L7
.L5:
	ret
	.cfi_endproc
.LFE1:
	.size	set_row_licm, .-set_row_licm
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
