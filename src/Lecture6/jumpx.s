	.file	"jumpx.c"
	.text
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB0:
	.cfi_startproc
	cmpq	%rsi, %rdi
	jle	.L2
	movq	%rdi, %rax
	subq	%rsi, %rax
	ret
.L2:
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	absdiff, .-absdiff
	.globl	abs_diff_j
	.type	abs_diff_j, @function
abs_diff_j:
.LFB1:
	.cfi_startproc
	cmpq	%rsi, %rdi
	jg	.L5
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
.L5:
	movq	%rdi, %rax
	subq	%rsi, %rax
.L6:
	ret
	.cfi_endproc
.LFE1:
	.size	abs_diff_j, .-abs_diff_j
	.globl	abs_diff_complex
	.type	abs_diff_complex, @function
abs_diff_complex:
.LFB2:
	.cfi_startproc
	movq	%rdi, %rax
	subq	%rsi, %rax
	cmpq	$5, %rax
	jle	.L8
	addq	$5, %rax
	ret
.L8:
	testq	%rax, %rax
	jle	.L10
.L7:
	ret
.L10:
	movq	%rsi, %rax
	subq	%rdi, %rax
	ret
	.cfi_endproc
.LFE2:
	.size	abs_diff_complex, .-abs_diff_complex
	.globl	abs_diff_complex_switch
	.type	abs_diff_complex_switch, @function
abs_diff_complex_switch:
.LFB3:
	.cfi_startproc
	movq	%rdi, %rax
	subq	%rsi, %rax
	cmpq	$5, %rax
	je	.L12
	cmpq	$10, %rax
	jne	.L11
	addq	$10, %rax
	ret
.L12:
	addq	$5, %rax
.L11:
	ret
	.cfi_endproc
.LFE3:
	.size	abs_diff_complex_switch, .-abs_diff_complex_switch
	.globl	abs_diff_complex_no_switch
	.type	abs_diff_complex_no_switch, @function
abs_diff_complex_no_switch:
.LFB4:
	.cfi_startproc
	movq	%rdi, %rax
	subq	%rsi, %rax
	cmpq	$10, %rax
	je	.L17
	cmpq	$5, %rax
	je	.L18
.L14:
	ret
.L17:
	addq	$10, %rax
	ret
.L18:
	addq	$5, %rax
	ret
	.cfi_endproc
.LFE4:
	.size	abs_diff_complex_no_switch, .-abs_diff_complex_no_switch
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
