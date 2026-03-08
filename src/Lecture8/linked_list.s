	.file	"linked_list.c"
	.text
	.globl	set_val
	.type	set_val, @function
set_val:
.LFB0:
	.cfi_startproc
	jmp	.L2
	.p2align 4
.L3:
	movslq	(%rdi), %rax
	movl	%esi, 8(%rdi,%rax,4)
	movq	24(%rdi), %rdi
.L2:
	testq	%rdi, %rdi
	jne	.L3
	ret
	.cfi_endproc
.LFE0:
	.size	set_val, .-set_val
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
