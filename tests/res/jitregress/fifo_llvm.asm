	.text
	.file	"llvmjit"
	.globl	eval
	.p2align	4, 0x90
	.type	eval,@function
eval:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %r10
	movq	8(%rdi), %rdi
	movl	8(%rdi), %esi
	movl	16(%rdi), %eax
	movq	24(%r10), %rcx
	movl	(%rcx), %ecx
	movl	24(%rdi), %edx
	notl	%edx
	movl	%ecx, 24(%rdi)
	testl	%ecx, %edx
	je	.LBB0_10
	movq	32(%r10), %rcx
	movl	(%rcx), %r9d
	movq	8(%r10), %r11
	movq	16(%r10), %rcx
	xorl	%r8d, %r8d
	cmpl	%esi, %eax
	setne	%r8b
	andl	(%rcx), %r8d
	movl	%eax, %ecx
	andl	$1, %ecx
	movl	%esi, %ebx
	andl	$1, %ebx
	xorl	%ecx, %ebx
	xorl	$1, %ebx
	movl	%eax, %edx
	xorl	%esi, %edx
	shrl	%edx
	andl	%ebx, %edx
	xorl	$1, %edx
	andl	(%r11), %edx
	je	.LBB0_3
	movq	(%r10), %rbx
	movl	(%rbx), %ebx
	movl	(%rdi), %r11d
	addb	%cl, %cl
	movl	$3, %ebp
	shll	%cl, %ebp
	shll	%cl, %ebx
	xorl	%r11d, %ebx
	andl	%ebp, %ebx
	xorl	%r11d, %ebx
	movl	%ebx, (%rdi)
.LBB0_3:
	testl	%r9d, %r9d
	je	.LBB0_5
	movl	$0, 16(%rdi)
	movl	$0, 8(%rdi)
	xorl	%esi, %esi
	xorl	%eax, %eax
	jmp	.LBB0_9
.LBB0_5:
	testl	%edx, %edx
	je	.LBB0_7
	incl	%eax
	andl	$3, %eax
	movl	%eax, 16(%rdi)
.LBB0_7:
	testl	%r8d, %r8d
	je	.LBB0_9
	incl	%esi
	andl	$3, %esi
	movl	%esi, 8(%rdi)
.LBB0_9:
	movl	%esi, %edx
	andl	$1, %edx
	movl	(%rdi), %edi
	leal	(%rdx,%rdx), %ecx
	shrl	%cl, %edi
	andl	$3, %edi
	movq	40(%r10), %rcx
	movl	%edi, (%rcx)
	xorl	%ecx, %ecx
	cmpl	%esi, %eax
	sete	%cl
	movq	48(%r10), %rdi
	movl	%ecx, (%rdi)
	movl	%eax, %ecx
	andl	$1, %ecx
	xorl	%edx, %ecx
	xorl	$1, %ecx
	xorl	%esi, %eax
	shrl	%eax
	andl	%ecx, %eax
	movq	56(%r10), %rcx
	movl	%eax, (%rcx)
.LBB0_10:
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	eval, .Lfunc_end0-eval
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
