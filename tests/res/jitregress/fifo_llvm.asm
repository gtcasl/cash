	.text
	.file	"llvmjit"
	.globl	eval
	.p2align	4, 0x90
	.type	eval,@function
eval:
	.cfi_startproc
	movq	(%rdi), %r8
	movq	8(%rdi), %rsi
	movl	8(%rsi), %edi
	movl	16(%rsi), %r11d
	movq	24(%r8), %rcx
	movl	(%rcx), %ecx
	movl	24(%rsi), %edx
	notl	%edx
	movl	%ecx, 24(%rsi)
	testl	%ecx, %edx
	je	.LBB0_7
	movq	8(%r8), %r10
	movq	16(%r8), %r9
	xorl	%ecx, %ecx
	cmpl	%edi, %r11d
	setne	%cl
	leal	1(%rdi), %edx
	andl	$3, %edx
	testl	%ecx, (%r9)
	cmovel	%edi, %edx
	movq	32(%r8), %rcx
	movl	(%rcx), %r9d
	movl	%r11d, %ecx
	andl	$1, %ecx
	movl	%r11d, %eax
	xorl	%edi, %eax
	andl	$1, %edi
	xorl	%ecx, %edi
	xorl	$1, %edi
	shrl	%eax
	andl	%edi, %eax
	xorl	$1, %eax
	leal	1(%r11), %edi
	andl	$3, %edi
	testl	%eax, (%r10)
	cmovel	%r11d, %edi
	je	.LBB0_3
	movq	(%r8), %rax
	movl	(%rax), %eax
	movl	(%rsi), %r10d
	addb	%cl, %cl
	movl	$3, %r11d
	shll	%cl, %r11d
	shll	%cl, %eax
	xorl	%r10d, %eax
	andl	%r11d, %eax
	xorl	%r10d, %eax
	movl	%eax, (%rsi)
.LBB0_3:
	testl	%r9d, %r9d
	je	.LBB0_5
	movl	$0, 16(%rsi)
	movl	$0, 8(%rsi)
	xorl	%edi, %edi
	xorl	%edx, %edx
	jmp	.LBB0_6
.LBB0_5:
	movl	%edi, 16(%rsi)
	movl	%edx, 8(%rsi)
.LBB0_6:
	movl	%edx, %eax
	andl	$1, %eax
	movl	(%rsi), %esi
	leal	(%rax,%rax), %ecx
	shrl	%cl, %esi
	andl	$3, %esi
	movq	40(%r8), %rcx
	movl	%esi, (%rcx)
	xorl	%ecx, %ecx
	cmpl	%edx, %edi
	sete	%cl
	movq	48(%r8), %rsi
	movl	%ecx, (%rsi)
	xorl	%edi, %edx
	andl	$1, %edi
	xorl	%eax, %edi
	xorl	$1, %edi
	shrl	%edx
	andl	%edi, %edx
	movq	56(%r8), %rax
	movl	%edx, (%rax)
.LBB0_7:
	xorl	%eax, %eax
	retq
.Lfunc_end0:
	.size	eval, .Lfunc_end0-eval
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
