	.file	"memory_addressing_modes.c"
	.text
	.globl	get_digit
	.type	get_digit, @function
get_digit:
.LFB0:
	.cfi_startproc
	movslq	%esi, %rsi
	movl	(%rdi,%rsi,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	get_digit, .-get_digit
	.globl	zincr
	.type	zincr, @function
zincr:
.LFB1:
	.cfi_startproc
	movl	$0, %eax
	jmp	.L3
	.p2align 5
.L4:
	leaq	(%rdi,%rax,4), %rcx
	movl	(%rcx), %esi
	leal	1(%rsi), %edx
	movl	%edx, (%rcx)
	addq	$1, %rax
.L3:
	cmpq	$5, %rax
	jbe	.L4
	ret
	.cfi_endproc
.LFE1:
	.size	zincr, .-zincr
	.globl	zincr_2
	.type	zincr_2, @function
zincr_2:
.LFB2:
	.cfi_startproc
	movl	$0, %eax
	jmp	.L6
	.p2align 5
.L7:
	leaq	(%rdi,%rax,4), %rcx
	movl	(%rcx), %esi
	leal	1(%rsi), %edx
	movl	%edx, (%rcx)
	addq	$1, %rax
.L6:
	cmpq	$5, %rax
	jbe	.L7
	ret
	.cfi_endproc
.LFE2:
	.size	zincr_2, .-zincr_2
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
