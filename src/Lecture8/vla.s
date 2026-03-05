	.file	"vla.c"
	.text
	.globl	vec_ele
	.type	vec_ele, @function
vec_ele:
.LFB0:
	.cfi_startproc
	imulq	%rdx, %rdi
	leaq	(%rsi,%rdi,4), %rax
	movl	(%rax,%rcx,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	vec_ele, .-vec_ele
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
