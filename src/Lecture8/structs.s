	.file	"structs.c"
	.text
	.globl	get_a
	.type	get_a, @function
get_a:
.LFB0:
	.cfi_startproc
	movl	8(%rdi,%rsi,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	get_a, .-get_a
	.globl	get_ap
	.type	get_ap, @function
get_ap:
.LFB1:
	.cfi_startproc
	leaq	8(%rdi,%rsi,4), %rax
	ret
	.cfi_endproc
.LFE1:
	.size	get_ap, .-get_ap
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
