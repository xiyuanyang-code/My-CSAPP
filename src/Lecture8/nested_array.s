	.file	"nested_array.c"
	.text
	.globl	get_pgh_zip
	.type	get_pgh_zip, @function
get_pgh_zip:
.LFB11:
	.cfi_startproc
	movslq	%edi, %rdi
	leaq	(%rdi,%rdi,2), %rax
	leaq	pgh(,%rax,8), %rax
	ret
	.cfi_endproc
.LFE11:
	.size	get_pgh_zip, .-get_pgh_zip
	.globl	get_pgh_digit
	.type	get_pgh_digit, @function
get_pgh_digit:
.LFB12:
	.cfi_startproc
	movslq	%esi, %rsi
	movslq	%edi, %rdi
	leaq	(%rdi,%rdi,2), %rax
	leaq	(%rsi,%rax,2), %rax
	movl	pgh(,%rax,4), %eax
	ret
	.cfi_endproc
.LFE12:
	.size	get_pgh_digit, .-get_pgh_digit
	.globl	get_univ_digit
	.type	get_univ_digit, @function
get_univ_digit:
.LFB13:
	.cfi_startproc
	movq	univ(,%rdi,8), %rax
	movl	(%rax,%rsi,4), %eax
	ret
	.cfi_endproc
.LFE13:
	.size	get_univ_digit, .-get_univ_digit
	.globl	univ
	.data
	.align 16
	.type	univ, @object
	.size	univ, 24
univ:
	.quad	mit
	.quad	cmu
	.quad	ucb
	.globl	ucb
	.align 16
	.type	ucb, @object
	.size	ucb, 24
ucb:
	.long	9
	.long	4
	.long	5
	.long	2
	.long	0
	.zero	4
	.globl	mit
	.align 16
	.type	mit, @object
	.size	mit, 24
mit:
	.long	0
	.long	2
	.long	1
	.long	3
	.long	9
	.zero	4
	.globl	cmu
	.align 16
	.type	cmu, @object
	.size	cmu, 24
cmu:
	.long	1
	.long	5
	.long	2
	.long	1
	.long	3
	.zero	4
	.globl	pgh
	.align 32
	.type	pgh, @object
	.size	pgh, 96
pgh:
	.long	1
	.long	5
	.long	2
	.long	0
	.long	6
	.zero	4
	.long	1
	.long	5
	.long	2
	.long	1
	.long	3
	.zero	4
	.long	1
	.long	5
	.long	2
	.long	1
	.long	7
	.zero	4
	.long	1
	.long	5
	.long	2
	.long	2
	.long	1
	.zero	4
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
