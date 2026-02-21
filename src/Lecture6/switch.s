	.file	"switch.c"
	.text
	.globl	switch_eg
	.type	switch_eg, @function
switch_eg:
.LFB0:
	.cfi_startproc
	movq	%rdx, %rcx
	cmpq	$3, %rdx
	je	.L8
	jg	.L3
	cmpq	$1, %rdx
	je	.L4
	cmpq	$2, %rdx
	jne	.L11
	movq	%rsi, %rax
	cqto
	idivq	%rcx
.L2:
	addq	%rcx, %rax
	ret
.L11:
	movl	$2, %eax
	ret
.L3:
	leaq	-5(%rdx), %rax
	cmpq	$1, %rax
	ja	.L12
	movl	$1, %eax
	subq	%rdx, %rax
	ret
.L4:
	movq	%rdx, %rax
	imulq	%rsi, %rax
	ret
.L8:
	movl	$1, %eax
	jmp	.L2
.L12:
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	switch_eg, .-switch_eg
	.globl	switch_eg_jump_table
	.type	switch_eg_jump_table, @function
switch_eg_jump_table:
.LFB1:
	.cfi_startproc
	movq	%rdx, %rcx
	leaq	-100(%rdx), %rax
	cmpq	$6, %rax
	ja	.L22
	jmp	*.L16(,%rax,8)
	.section	.rodata
	.align 8
	.align 4
.L16:
	.quad	.L21
	.quad	.L20
	.quad	.L23
	.quad	.L18
	.quad	.L17
	.quad	.L17
	.quad	.L15
	.text
.L21:
	movq	%rdx, %rax
	imulq	%rsi, %rax
	ret
.L20:
	movq	%rsi, %rax
	cqto
	idivq	%rcx
.L19:
	addq	%rcx, %rax
	ret
.L23:
	movl	$1, %eax
	jmp	.L19
.L18:
	movq	%rsi, %rax
	subq	%rdx, %rax
	ret
.L17:
	movl	$1, %eax
	subq	%rdx, %rax
	ret
.L15:
	movq	%rdi, %rax
	sarq	$2, %rax
	ret
.L22:
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	switch_eg_jump_table, .-switch_eg_jump_table
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
