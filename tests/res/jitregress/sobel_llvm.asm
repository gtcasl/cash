	.text
	.file	"llvmjit"
	.globl	eval
	.p2align	4, 0x90
	.type	eval,@function
eval:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%r15
	.cfi_def_cfa_offset 24
	pushq	%r14
	.cfi_def_cfa_offset 32
	pushq	%r13
	.cfi_def_cfa_offset 40
	pushq	%r12
	.cfi_def_cfa_offset 48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %rdx
	movq	8(%rdi), %rcx
	movl	(%rcx), %eax
	movl	%eax, -32(%rsp)
	movl	76(%rcx), %r12d
	movl	152(%rcx), %r10d
	movl	160(%rcx), %eax
	movl	%eax, -96(%rsp)
	movl	168(%rcx), %r15d
	movl	176(%rcx), %eax
	movl	%eax, -112(%rsp)
	movl	184(%rcx), %r9d
	movl	192(%rcx), %eax
	movl	%eax, -76(%rsp)
	movl	200(%rcx), %r11d
	movl	208(%rcx), %eax
	movl	%eax, -80(%rsp)
	movl	216(%rcx), %eax
	movq	%rax, -72(%rsp)
	movq	%rdx, -16(%rsp)
	movq	24(%rdx), %rax
	movl	(%rax), %esi
	movl	304(%rcx), %eax
	notl	%eax
	testl	%esi, %eax
	movl	224(%rcx), %r14d
	movl	232(%rcx), %r8d
	movl	240(%rcx), %ebp
	movl	256(%rcx), %ebx
	movl	264(%rcx), %edi
	movl	272(%rcx), %eax
	movl	280(%rcx), %r13d
	movl	288(%rcx), %edx
	movl	%edx, -28(%rsp)
	movl	296(%rcx), %edx
	movl	%edx, -84(%rsp)
	movl	%esi, 304(%rcx)
	je	.LBB0_33
	movl	%ebp, -108(%rsp)
	movl	%r9d, -36(%rsp)
	movl	%edi, -60(%rsp)
	movl	%r12d, -56(%rsp)
	movl	%eax, -92(%rsp)
	xorl	%esi, %esi
	cmpl	$4096, %r14d
	setb	%sil
	movq	%rbx, %r12
	movl	%r12d, %r9d
	xorl	$1, %r9d
	andl	%r12d, %esi
	xorl	$1, %esi
	cmpl	$134, %r14d
	seta	%al
	testl	%r8d, %r8d
	sete	%dl
	andb	%al, %dl
	movzbl	%dl, %edi
	movl	%esi, -40(%rsp)
	andl	%esi, %edi
	movl	%r13d, -44(%rsp)
	shrl	$2, %r13d
	movl	%edi, -88(%rsp)
	andl	%r13d, %edi
	xorl	$1, %r13d
	xorl	$1, %edi
	cmpl	$-3, %r14d
	seta	-114(%rsp)
	movq	-16(%rsp), %rbx
	movq	8(%rbx), %r8
	movq	%r14, -24(%rsp)
	cmpl	$4100, %r14d
	seta	%r14b
	movq	-72(%rsp), %rbp
	leal	(%rbp,%r15), %eax
	andl	$511, %eax
	movzbl	-76(%rsp), %edx
	leal	(%rax,%rdx,2), %edx
	leal	(%r11,%r10), %eax
	andl	$511, %eax
	movzbl	-112(%rsp), %esi
	leal	(%rax,%rsi,2), %eax
	movl	%eax, %esi
	subl	%edx, %esi
	subl	%eax, %edx
	movq	32(%rbx), %rax
	movl	(%rax), %eax
	movl	%eax, -100(%rsp)
	cmovbel	%esi, %edx
	addl	%ebp, %r11d
	andl	$511, %r11d
	movl	-80(%rsp), %eax
	movzbl	%al, %eax
	leal	(%r11,%rax,2), %ebp
	movq	%r15, -8(%rsp)
	addl	%r15d, %r10d
	andl	$511, %r10d
	movzbl	-96(%rsp), %eax
	leal	(%r10,%rax,2), %eax
	movl	%eax, %esi
	subl	%ebp, %esi
	subl	%eax, %ebp
	cmovbel	%esi, %ebp
	movl	%r12d, %r10d
	shrl	$2, %r10d
	notl	%r10d
	andl	(%r8), %r10d
	andl	$1, %r10d
	movl	%edi, -112(%rsp)
	andl	%edi, %r9d
	movl	%r9d, %esi
	xorl	$1, %esi
	movl	%r12d, %r15d
	shrl	%r15d
	testl	%esi, %r10d
	movq	%rbx, %rdi
	movb	%r14b, -113(%rsp)
	movl	%edx, -48(%rsp)
	movl	%ebp, -52(%rsp)
	je	.LBB0_2
	movl	%r9d, %r8d
	leal	(%r12,%r12), %eax
	andl	$6, %eax
	movl	%eax, -104(%rsp)
	jmp	.LBB0_4
.LBB0_2:
	movl	%r15d, %edx
	andl	$3, %edx
	movl	%r10d, %eax
	xorl	$1, %eax
	movl	%r9d, %r8d
	testl	%r9d, %eax
	cmovel	%r12d, %edx
	movl	%edx, -104(%rsp)
.LBB0_4:
	movl	-108(%rsp), %r9d
	movl	-88(%rsp), %ebp
	movl	%r15d, %eax
	andl	$1, %eax
	movq	(%rdi), %rbx
	movq	16(%rdi), %rdx
	movl	(%rbx), %edi
	orl	%eax, %esi
	movl	-92(%rsp), %eax
	movl	%edi, -108(%rsp)
	cmovnel	%edi, %eax
	movl	%eax, -92(%rsp)
	andl	%ebp, %r13d
	movl	-44(%rsp), %ebx
	movl	%ebx, %esi
	andl	$1, %esi
	movl	%esi, %edi
	xorl	$1, %edi
	andl	(%rdx), %edi
	movl	%edi, %r14d
	xorl	$1, %r14d
	movl	%ebx, %r11d
	shrl	%r11d
	testl	%r13d, %r14d
	je	.LBB0_5
	addl	%ebx, %ebx
	andl	$6, %ebx
	jmp	.LBB0_7
.LBB0_5:
	movl	%ebx, %edx
	movl	%r11d, %ebx
	andl	$3, %ebx
	movl	%r13d, %eax
	xorl	$1, %eax
	testl	%eax, %edi
	cmovel	%edx, %ebx
.LBB0_7:
	movl	-100(%rsp), %edx
	movl	-84(%rsp), %eax
	andl	$1, %r11d
	orl	%r11d, %r14d
	cmovnel	%r9d, %eax
	andl	%r13d, %esi
	orl	%edi, %esi
	andl	%r13d, %r11d
	orl	%edi, %r11d
	je	.LBB0_9
	movl	%r9d, 296(%rcx)
.LBB0_9:
	andl	%r10d, %r15d
	testl	%esi, %esi
	movq	-16(%rsp), %rdi
	movl	-28(%rsp), %r9d
	movl	-36(%rsp), %r11d
	movl	-40(%rsp), %r13d
	je	.LBB0_11
	movl	%eax, 288(%rcx)
	movl	%eax, %r9d
.LBB0_11:
	orl	%r8d, %r15d
	testl	%edx, %edx
	je	.LBB0_13
	movl	$1, 280(%rcx)
	movl	$1, %ebx
	testl	%r15d, %r15d
	je	.LBB0_16
.LBB0_15:
	movl	-108(%rsp), %eax
	movl	%eax, 272(%rcx)
.LBB0_16:
	testl	%edx, %edx
	movq	-8(%rsp), %r14
	movl	$0, %r15d
	je	.LBB0_18
	movl	$1, 256(%rcx)
	movl	$1, -104(%rsp)
	testl	%r13d, -112(%rsp)
	je	.LBB0_21
.LBB0_20:
	movl	-48(%rsp), %eax
	andl	$1023, %eax
	movl	-52(%rsp), %ebp
	andl	$1023, %ebp
	addl	%eax, %ebp
	movl	248(%rcx), %eax
	movzbl	%al, %edx
	shrl	$8, %eax
	movl	%ebp, %esi
	shll	$16, %esi
	andl	$16711680, %esi
	cmpl	$255, %ebp
	movl	%edx, 240(%rcx)
	movl	$16711680, %edx
	cmovbl	%esi, %edx
	orl	%eax, %edx
	movl	%edx, 248(%rcx)
	movl	-100(%rsp), %edx
.LBB0_21:
	andl	%r12d, %r10d
	testl	%edx, %edx
	je	.LBB0_23
	movl	$0, 232(%rcx)
	xorl	%r15d, %r15d
	jmp	.LBB0_24
.LBB0_13:
	movl	%ebx, 280(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_15
	jmp	.LBB0_16
.LBB0_18:
	movl	-104(%rsp), %eax
	movl	%eax, 256(%rcx)
	testl	%r13d, -112(%rsp)
	jne	.LBB0_20
	jmp	.LBB0_21
.LBB0_23:
	movb	-113(%rsp), %al
	movb	%al, %r15b
	movl	%r15d, 232(%rcx)
.LBB0_24:
	movl	-96(%rsp), %r12d
	movq	-72(%rsp), %rsi
	movq	-24(%rsp), %rax
	orl	%r8d, %r10d
	testl	%edx, %edx
	je	.LBB0_26
	movl	$0, 224(%rcx)
	testl	%r13d, -112(%rsp)
	jne	.LBB0_29
	jmp	.LBB0_30
.LBB0_26:
	testl	%r13d, -112(%rsp)
	je	.LBB0_30
	xorl	%ebp, %ebp
	movb	-114(%rsp), %dl
	movb	%dl, %bpl
	leal	1(%rbp,%rax), %eax
	movl	%eax, 224(%rcx)
	testl	%r13d, -112(%rsp)
	je	.LBB0_30
.LBB0_29:
	movl	-80(%rsp), %eax
	movl	%eax, 200(%rcx)
	movl	%esi, 208(%rcx)
	movl	-60(%rsp), %ebp
	movl	%ebp, 216(%rcx)
	movl	%r11d, 176(%rcx)
	movl	-76(%rsp), %eax
	movl	%eax, 184(%rcx)
	movl	-32(%rsp), %esi
	movl	%esi, 192(%rcx)
	movl	%r12d, 152(%rcx)
	movl	%r14d, 160(%rcx)
	movl	-56(%rsp), %eax
	movl	%eax, 168(%rcx)
	movslq	148(%rcx), %rax
	movzbl	84(%rcx,%rax), %edx
	movl	%edx, 76(%rcx)
	movb	%sil, 84(%rcx,%rax)
	leal	-1(%rax), %eax
	cmpl	$62, %eax
	movl	$62, %edx
	cmovael	%edx, %eax
	movl	%eax, 148(%rcx)
	movslq	72(%rcx), %rax
	movzbl	8(%rcx,%rax), %esi
	movl	%esi, (%rcx)
	movb	%bpl, 8(%rcx,%rax)
	leal	-1(%rax), %eax
	cmpl	$62, %eax
	cmovbl	%eax, %edx
	movl	%edx, 72(%rcx)
.LBB0_30:
	testl	%r10d, %r10d
	je	.LBB0_32
	movl	-92(%rsp), %eax
	movl	%eax, 264(%rcx)
.LBB0_32:
	movl	-104(%rsp), %ecx
	shrl	$2, %ecx
	notl	%ecx
	andl	$1, %ecx
	movq	40(%rdi), %rax
	movl	%ecx, (%rax)
	movq	48(%rdi), %rax
	movl	%r9d, (%rax)
	notl	%ebx
	andl	$1, %ebx
	movq	56(%rdi), %rax
	movl	%ebx, (%rax)
	movq	64(%rdi), %rax
	movl	%r15d, (%rax)
.LBB0_33:
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%r12
	.cfi_def_cfa_offset 40
	popq	%r13
	.cfi_def_cfa_offset 32
	popq	%r14
	.cfi_def_cfa_offset 24
	popq	%r15
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	eval, .Lfunc_end0-eval
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
