	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 0
	.globl	_compare_long                   ## -- Begin function compare_long
	.p2align	4, 0x90
_compare_long:                          ## @compare_long
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	cmpq	-16(%rbp), %rax
	setg	%al
	andb	$1, %al
	movzbl	%al, %eax
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$12, %edi
	movl	$3, %esi
	callq	_compare_long
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
                                        ## -- End function
.subsections_via_symbols
