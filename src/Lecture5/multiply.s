	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 0
	.globl	_multiply                       ## -- Begin function multiply
	.p2align	4, 0x90
_multiply:                              ## @multiply
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	imulq	-16(%rbp), %rax
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_m12                            ## -- Begin function m12
	.p2align	4, 0x90
_m12:                                   ## @m12
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)
	imulq	$12, -8(%rbp), %rax
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, -4(%rbp)
	xorl	%eax, %eax
	popq	%rbp
	retq
                                        ## -- End function
.subsections_via_symbols
