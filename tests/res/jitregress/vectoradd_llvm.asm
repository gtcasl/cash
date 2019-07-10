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
	subq	$424, %rsp
	.cfi_def_cfa_offset 480
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %r15
	movq	8(%rdi), %rbx
	movl	3264(%rbx), %r9d
	movl	3272(%rbx), %eax
	movq	%rax, 80(%rsp)
	movl	3280(%rbx), %eax
	movq	%rax, 392(%rsp)
	movl	3296(%rbx), %eax
	movl	%eax, 36(%rsp)
	movq	3312(%rbx), %r11
	movl	3320(%rbx), %eax
	movq	%rax, 136(%rsp)
	movl	3328(%rbx), %eax
	movq	%rax, 64(%rsp)
	movl	3336(%rbx), %eax
	movl	%eax, 20(%rsp)
	movl	3344(%rbx), %eax
	movq	%rax, 152(%rsp)
	movl	3416(%rbx), %eax
	movl	%eax, 128(%rsp)
	movl	3424(%rbx), %eax
	movq	%rax, 208(%rsp)
	movq	144(%r15), %rcx
	movl	(%rcx), %ecx
	movl	5000(%rbx), %edi
	notl	%edi
	testl	%ecx, %edi
	movl	3432(%rbx), %eax
	movq	%rax, 248(%rsp)
	movl	3440(%rbx), %eax
	movl	%eax, 216(%rsp)
	movl	3448(%rbx), %eax
	movl	3456(%rbx), %edx
	movq	%rdx, 376(%rsp)
	movl	3464(%rbx), %edx
	movq	%rdx, 256(%rsp)
	movl	3472(%rbx), %edx
	movl	%edx, 196(%rsp)
	movl	3480(%rbx), %edx
	movl	%edx, 16(%rsp)
	movq	3616(%rbx), %r10
	movl	3624(%rbx), %edx
	movq	%rdx, 264(%rsp)
	movl	3632(%rbx), %edx
	movq	%rdx, 200(%rsp)
	movl	3640(%rbx), %r12d
	movl	3648(%rbx), %r14d
	movl	3720(%rbx), %edx
	movl	%edx, 12(%rsp)
	movl	3728(%rbx), %edx
	movq	%rdx, 144(%rsp)
	movl	3736(%rbx), %edx
	movq	%rdx, 272(%rsp)
	movl	3744(%rbx), %edx
	movl	%edx, 124(%rsp)
	movl	3752(%rbx), %edx
	movl	3760(%rbx), %edi
	movq	%rdi, 368(%rsp)
	movl	3768(%rbx), %edi
	movl	%edi, 192(%rsp)
	movl	3776(%rbx), %edi
	movl	%edi, 188(%rsp)
	movl	3784(%rbx), %esi
	movl	%esi, 100(%rsp)
	movq	3920(%rbx), %rsi
	movq	%rsi, 240(%rsp)
	movl	3928(%rbx), %esi
	movq	%rsi, 280(%rsp)
	movl	3936(%rbx), %r13d
	movl	3944(%rbx), %esi
	movl	%esi, 176(%rsp)
	movl	3952(%rbx), %r8d
	movl	4024(%rbx), %ebp
	movl	4032(%rbx), %esi
	movq	%rsi, 400(%rsp)
	movl	4040(%rbx), %esi
	movl	%esi, 104(%rsp)
	movl	4048(%rbx), %esi
	movl	4056(%rbx), %edi
	movl	%edi, 120(%rsp)
	movl	4064(%rbx), %edi
	movl	%edi, 60(%rsp)
	movl	4072(%rbx), %edi
	movq	%rdi, 408(%rsp)
	movl	4080(%rbx), %edi
	movl	%edi, 184(%rsp)
	movl	4088(%rbx), %edi
	movl	%edi, 180(%rsp)
	movl	4096(%rbx), %edi
	movl	%ecx, 5000(%rbx)
	je	.LBB0_1
	movq	%r11, %rdi
	movl	%r12d, 92(%rsp)
	movq	%r14, 232(%rsp)
	movl	%r13d, 32(%rsp)
	movq	32(%r15), %rcx
	movl	(%rcx), %ecx
	movl	%ecx, 40(%rsp)
	testl	%r9d, %r9d
	movq	%r15, %r14
	movl	%r8d, 172(%rsp)
	movl	%eax, 52(%rsp)
	movl	%edx, 48(%rsp)
	movq	%rsi, 288(%rsp)
	movl	%r9d, 28(%rsp)
	jle	.LBB0_6
	cmpl	$2, %r9d
	jge	.LBB0_4
	cmpl	$1, 80(%rsp)
	movl	$1, %r9d
	adcl	$0, %r9d
	movq	%rdi, %r15
	jmp	.LBB0_9
.LBB0_1:
	movq	%r11, 136(%rsp)
	movl	%r12d, %ebp
	movq	152(%rsp), %rsi
	movl	20(%rsp), %r9d
	movq	%r15, %r12
	jmp	.LBB0_123
.LBB0_6:
	movq	%rdi, %r15
	jne	.LBB0_9
	xorl	%r9d, %r9d
	cmpl	$0, 40(%rsp)
	setne	%r9b
	jmp	.LBB0_9
.LBB0_4:
	movq	%rdi, %r15
	jne	.LBB0_9
	movq	40(%r14), %rcx
	xorl	%edi, %edi
	cmpl	$0, 176(%rsp)
	sete	%dil
	xorl	%r9d, %r9d
	testl	%edi, (%rcx)
	sete	%r9b
	addl	%r9d, %r9d
.LBB0_9:
	movl	%r9d, 356(%rsp)
	movq	%r10, 224(%rsp)
	movq	24(%r14), %rcx
	movq	152(%r14), %rdi
	movl	(%rdi), %eax
	movl	%eax, 168(%rsp)
	xorl	%r9d, %r9d
	cmpl	$0, 28(%rsp)
	sete	%r9b
	movl	(%rcx), %r13d
	movl	%ebp, 56(%rsp)
	testl	%ebp, %ebp
	sete	%cl
	cmpl	$0, 60(%rsp)
	sete	%al
	movb	%al, 27(%rsp)
	orb	%al, %cl
	movzbl	%cl, %eax
	movl	%eax, 96(%rsp)
	movl	40(%rsp), %r11d
	testl	%r9d, %r11d
	movl	%r13d, %eax
	movl	36(%rsp), %edx
	jne	.LBB0_11
	movq	80(%rsp), %rsi
	leal	-1(%rsi), %eax
	testl	%edx, 96(%rsp)
	cmovel	%esi, %eax
.LBB0_11:
	movl	%eax, 348(%rsp)
	movl	3656(%rbx), %eax
	addl	3352(%rbx), %eax
	movl	%eax, 352(%rsp)
	testl	%edx, %edx
	sete	%al
	orb	%cl, %al
	movzbl	%al, %edx
	movl	12(%rsp), %ebp
	movl	%ebp, %eax
	movl	128(%rsp), %esi
	andl	%esi, %eax
	movl	%eax, 308(%rsp)
	movq	%r14, 360(%rsp)
	movq	96(%r14), %rax
	xorl	%r10d, %r10d
	cmpl	$0, (%rax)
	sete	%r10b
	movq	152(%rsp), %r8
	movq	%r8, %rdi
	shlq	$6, %rdi
	addq	%r15, %rdi
	xorl	%ecx, %ecx
	cmpl	$0, 216(%rsp)
	sete	%cl
	xorl	%eax, %eax
	testl	%esi, %esi
	sete	%al
	xorl	%r12d, %r12d
	cmpl	$15, 208(%rsp)
	sete	%r12b
	xorl	%r14d, %r14d
	testl	%ebp, %ebp
	sete	%r14b
	movl	%r14d, 108(%rsp)
	andl	%esi, %r14d
	xorl	$1, %r14d
	movl	%edx, 116(%rsp)
	andl	%edx, %r14d
	andl	%r14d, %r12d
	movl	%r12d, %ebp
	movl	%eax, 72(%rsp)
	orl	%eax, %ebp
	movq	136(%rsp), %rsi
	leal	(%r8,%rsi), %eax
	leal	-1(%rsi), %edx
	andl	$31, %edx
	andl	%ecx, %ebp
	movl	%ebp, 112(%rsp)
	leal	-1(%r8,%rsi), %ecx
	movq	%r15, %r8
	cmovel	%eax, %ecx
	cmovel	%esi, %edx
	andl	$31, %ecx
	movq	64(%rsp), %rsi
	leal	-1(%rsi), %eax
	andl	$268435455, %eax
	andl	20(%rsp), %r10d
	cmovneq	%rdi, %r8
	cmovel	%edx, %ecx
	cmovel	%esi, %eax
	movl	%eax, 164(%rsp)
	xorl	%ebp, %ebp
	testl	%r9d, %r11d
	cmovel	%ecx, %ebp
	shll	$5, %r13d
	addl	$511, %r13d
	shrl	$9, %r13d
	leal	15(%r13), %r15d
	shrl	$4, %r15d
	xorl	%edi, %edi
	testl	%r13d, %r13d
	setne	%dl
	testl	%esi, %esi
	setne	%al
	movl	%ebp, 344(%rsp)
	testl	%ebp, %ebp
	sete	%cl
	andb	%al, %cl
	leaq	3352(%rbx), %rbp
	testl	%r9d, %r11d
	leaq	3656(%rbx), %rax
	movq	%rax, 296(%rsp)
	je	.LBB0_13
	movq	360(%rsp), %rax
	movq	8(%rax), %rax
	movq	(%rax), %r8
	movl	%r15d, 164(%rsp)
.LBB0_13:
	movb	%dl, %dil
	movl	%edi, 20(%rsp)
	jne	.LBB0_15
	movzbl	%cl, %eax
	xorl	%ecx, %ecx
	cmpl	$1, %esi
	sete	%cl
	xorl	%edx, %edx
	testl	%ecx, %r10d
	cmovel	%eax, %edx
	movl	%edx, 20(%rsp)
.LBB0_15:
	decl	%r13d
	andl	$15, %r13d
	incl	%r13d
	testl	%r10d, %r10d
	movl	$16, %eax
	cmovel	152(%rsp), %eax
	testl	%r9d, %r11d
	movl	%eax, %ecx
	cmovnel	%r13d, %ecx
	leaq	4296(%rbx), %rax
	cmpl	$0, 16(%rsp)
	movl	%r9d, 16(%rsp)
	movq	%rcx, 152(%rsp)
	movq	%r8, 136(%rsp)
	movq	%r13, 64(%rsp)
	movl	%edi, 80(%rsp)
	movl	%r15d, 88(%rsp)
	je	.LBB0_16
	movq	3544(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	3536(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	3528(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	3520(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	3512(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	3504(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	3488(%rbx), %rcx
	movq	3496(%rbx), %rdx
	jmp	.LBB0_18
.LBB0_16:
	movq	3608(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	3600(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	3592(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	3584(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	3576(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	3568(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	3552(%rbx), %rcx
	movq	3560(%rbx), %rdx
.LBB0_18:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	leaq	4680(%rbx), %r13
	movabsq	$"bv_shr_vector<false, block_type>", %rax
	movq	%r13, %rdi
	movl	$512, %esi
	movq	%rbp, %rdx
	movl	$512, %ecx
	movl	$32, %r8d
	callq	*%rax
	cmpl	$0, 112(%rsp)
	movq	%rbp, 384(%rsp)
	je	.LBB0_19
	movq	4352(%rbx), %rax
	movq	%rax, 4288(%rbx)
	movq	4344(%rbx), %rax
	movq	%rax, 4280(%rbx)
	movq	4336(%rbx), %rax
	movq	%rax, 4272(%rbx)
	movq	4328(%rbx), %rax
	movq	%rax, 4264(%rbx)
	movq	4320(%rbx), %rax
	movq	%rax, 4256(%rbx)
	movq	4312(%rbx), %rax
	movq	%rax, 4248(%rbx)
	movq	4296(%rbx), %rax
	movq	4304(%rbx), %rcx
	movq	%rcx, 4240(%rbx)
	movq	%rax, 4232(%rbx)
	movq	64(%rsp), %r8
	movl	52(%rsp), %r10d
	jmp	.LBB0_24
.LBB0_19:
	leaq	4232(%rbx), %rax
	testl	%r14d, 128(%rsp)
	movl	52(%rsp), %r10d
	je	.LBB0_20
	movq	56(%r13), %rcx
	movq	%rcx, 56(%rax)
	movq	48(%r13), %rcx
	movq	%rcx, 48(%rax)
	movq	40(%r13), %rcx
	movq	%rcx, 40(%rax)
	movq	32(%r13), %rcx
	movq	%rcx, 32(%rax)
	movq	24(%r13), %rcx
	movq	%rcx, 24(%rax)
	movq	16(%r13), %rcx
	movq	%rcx, 16(%rax)
	movq	(%r13), %rcx
	movq	8(%r13), %rdx
	jmp	.LBB0_23
.LBB0_20:
	movq	56(%rbp), %rcx
	movq	%rcx, 56(%rax)
	movq	48(%rbp), %rcx
	movq	%rcx, 48(%rax)
	movq	40(%rbp), %rcx
	movq	%rcx, 40(%rax)
	movq	32(%rbp), %rcx
	movq	%rcx, 32(%rax)
	movq	24(%rbp), %rcx
	movq	%rcx, 24(%rax)
	movq	16(%rbp), %rcx
	movq	%rcx, 16(%rax)
	movq	(%rbp), %rcx
	movq	8(%rbp), %rdx
.LBB0_23:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	64(%rsp), %r8
.LBB0_24:
	xorl	%r9d, %r9d
	testl	%r12d, %r12d
	movl	$0, %r15d
	movl	128(%rsp), %edx
	cmovel	%edx, %r15d
	movq	208(%rsp), %rax
	leal	1(%rax), %ecx
	andl	$15, %ecx
	testl	%edx, %r14d
	cmovel	%eax, %ecx
	movl	%ecx, 340(%rsp)
	movq	360(%rsp), %r12
	movq	88(%r12), %rcx
	xorl	%edi, %edi
	testl	%r10d, %r10d
	sete	%dil
	andl	(%rcx), %edi
	movl	112(%rsp), %r14d
	movl	%r14d, %r13d
	xorl	$1, %r13d
	andl	%edi, %r13d
	movl	%edi, %edx
	xorl	$1, %edx
	andl	%r14d, %edx
	movq	248(%rsp), %rcx
	leal	-1(%rcx), %eax
	andl	$31, %eax
	leal	1(%rcx), %esi
	andl	$31, %esi
	xorl	%ebp, %ebp
	cmpl	$1, %ecx
	sete	%bpl
	testl	%edx, %edx
	cmovel	%ecx, %eax
	cmovnel	%r9d, %r10d
	testl	%r13d, %r13d
	cmovnel	%esi, %eax
	movl	%eax, 336(%rsp)
	movl	$0, %eax
	movl	216(%rsp), %r9d
	cmovel	%r9d, %eax
	testl	%ebp, %edx
	movl	$1, %edx
	cmovnel	%edx, %eax
	movl	%eax, 332(%rsp)
	xorl	%esi, %esi
	cmpl	$15, %ecx
	movq	80(%r12), %rax
	movq	%rax, 128(%rsp)
	sete	%sil
	testl	%esi, %r13d
	cmovnel	%edx, %r10d
	movq	376(%rsp), %rax
	leal	1(%rax), %ecx
	andl	$15, %ecx
	testl	%edi, %edi
	cmovel	%eax, %ecx
	movl	%ecx, 324(%rsp)
	movq	256(%rsp), %rcx
	leal	2(%rcx), %eax
	andl	$15, %eax
	movl	%eax, 312(%rsp)
	andl	%r14d, %ebp
	orl	%r9d, %ebp
	movl	%edi, 208(%rsp)
	andl	%edi, %ebp
	movl	%ebp, 328(%rsp)
	testl	%r14d, %r14d
	cmovnel	%edx, %r15d
	movl	%r15d, 248(%rsp)
	cmovnel	196(%rsp), %ecx
	shll	$6, %ecx
	movslq	%ecx, %rcx
	movq	56(%rbx,%rcx), %rdx
	movq	%rdx, 3128(%rbx)
	movq	48(%rbx,%rcx), %rdx
	movq	%rdx, 3120(%rbx)
	movq	40(%rbx,%rcx), %rdx
	movq	%rdx, 3112(%rbx)
	movq	32(%rbx,%rcx), %rdx
	movq	%rdx, 3104(%rbx)
	movq	24(%rbx,%rcx), %rdx
	movq	%rdx, 3096(%rbx)
	movq	16(%rbx,%rcx), %rdx
	movq	%rdx, 3088(%rbx)
	movq	(%rbx,%rcx), %rdx
	movq	8(%rbx,%rcx), %rcx
	movq	%rcx, 3080(%rbx)
	movq	%rdx, 3072(%rbx)
	movq	128(%r12), %rdx
	xorl	%ecx, %ecx
	cmpl	$0, (%rdx)
	sete	%cl
	movq	232(%rsp), %r13
	movq	%r13, %rdx
	shlq	$6, %rdx
	movq	224(%rsp), %r11
	addq	%r11, %rdx
	xorl	%esi, %esi
	cmpl	$0, 124(%rsp)
	sete	%sil
	xorl	%r14d, %r14d
	cmpl	$15, 144(%rsp)
	sete	%r14b
	movl	72(%rsp), %eax
	andl	12(%rsp), %eax
	xorl	$1, %eax
	andl	116(%rsp), %eax
	movl	%eax, 72(%rsp)
	andl	%eax, %r14d
	movl	108(%rsp), %r15d
	orl	%r14d, %r15d
	movq	264(%rsp), %rbp
	leal	-1(%rbp), %edi
	andl	$31, %edi
	andl	%esi, %r15d
	leal	(%r13,%rbp), %esi
	leal	-1(%r13,%rbp), %eax
	cmovel	%esi, %eax
	cmovel	%ebp, %edi
	andl	$31, %eax
	movq	200(%rsp), %r9
	leal	-1(%r9), %esi
	andl	$268435455, %esi
	andl	92(%rsp), %ecx
	cmovneq	%rdx, %r11
	movq	%r11, 224(%rsp)
	cmovel	%edi, %eax
	cmovel	%r9d, %esi
	movl	40(%rsp), %edi
	movl	16(%rsp), %ebp
	testl	%ebp, %edi
	movl	$0, %edx
	cmovnel	%edx, %eax
	testl	%r9d, %r9d
	setne	%dl
	movl	%eax, 264(%rsp)
	testl	%eax, %eax
	sete	%al
	andb	%dl, %al
	leaq	3072(%rbx), %rdx
	movq	%rdx, 216(%rsp)
	testl	%ebp, %edi
	je	.LBB0_26
	movq	16(%r12), %rdx
	movq	(%rdx), %rdx
	movq	%rdx, 224(%rsp)
	movl	88(%rsp), %esi
.LBB0_26:
	movl	80(%rsp), %ebp
	jne	.LBB0_28
	movzbl	%al, %eax
	xorl	%edx, %edx
	cmpl	$1, 200(%rsp)
	sete	%dl
	xorl	%ebp, %ebp
	testl	%edx, %ecx
	cmovel	%eax, %ebp
.LBB0_28:
	testl	%ecx, %ecx
	movl	$16, %eax
	cmovel	%r13d, %eax
	testl	%edi, 16(%rsp)
	cmovel	%eax, %r8d
	leaq	4424(%rbx), %rax
	cmpl	$0, 100(%rsp)
	movq	%r8, 64(%rsp)
	movl	%ebp, 80(%rsp)
	movl	%r10d, 52(%rsp)
	movl	%esi, 256(%rsp)
	je	.LBB0_29
	movq	3848(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	3840(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	3832(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	3824(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	3816(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	3808(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	3792(%rbx), %rcx
	movq	3800(%rbx), %rdx
	jmp	.LBB0_31
.LBB0_29:
	movq	3912(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	3904(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	3896(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	3888(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	3880(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	3872(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	3856(%rbx), %rcx
	movq	3864(%rbx), %rdx
.LBB0_31:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	leaq	4744(%rbx), %r13
	movq	%r13, %rdi
	movl	$512, %esi
	movq	296(%rsp), %rdx
	movl	$512, %ecx
	movl	$32, %r8d
	movabsq	$"bv_shr_vector<false, block_type>", %rax
	callq	*%rax
	testl	%r15d, %r15d
	je	.LBB0_32
	movq	4480(%rbx), %rax
	movq	%rax, 4416(%rbx)
	movq	4472(%rbx), %rax
	movq	%rax, 4408(%rbx)
	movq	4464(%rbx), %rax
	movq	%rax, 4400(%rbx)
	movq	4456(%rbx), %rax
	movq	%rax, 4392(%rbx)
	movq	4448(%rbx), %rax
	movq	%rax, 4384(%rbx)
	movq	4440(%rbx), %rax
	movq	%rax, 4376(%rbx)
	movq	4424(%rbx), %rax
	movq	4432(%rbx), %rcx
	movq	%rcx, 4368(%rbx)
	movq	%rax, 4360(%rbx)
	movl	48(%rsp), %r8d
	movq	288(%rsp), %r9
	movl	32(%rsp), %r11d
	movl	72(%rsp), %esi
	jmp	.LBB0_37
.LBB0_32:
	leaq	4360(%rbx), %rax
	movl	72(%rsp), %esi
	testl	%esi, 12(%rsp)
	movl	48(%rsp), %r8d
	movq	288(%rsp), %r9
	movl	32(%rsp), %r11d
	je	.LBB0_33
	movq	56(%r13), %rcx
	movq	%rcx, 56(%rax)
	movq	48(%r13), %rcx
	movq	%rcx, 48(%rax)
	movq	40(%r13), %rcx
	movq	%rcx, 40(%rax)
	movq	32(%r13), %rcx
	movq	%rcx, 32(%rax)
	movq	24(%r13), %rcx
	movq	%rcx, 24(%rax)
	movq	16(%r13), %rcx
	movq	%rcx, 16(%rax)
	movq	(%r13), %rcx
	movq	8(%r13), %rdx
	jmp	.LBB0_36
.LBB0_33:
	movq	296(%rsp), %rdx
	movq	56(%rdx), %rcx
	movq	%rcx, 56(%rax)
	movq	48(%rdx), %rcx
	movq	%rcx, 48(%rax)
	movq	40(%rdx), %rcx
	movq	%rcx, 40(%rax)
	movq	32(%rdx), %rcx
	movq	%rcx, 32(%rax)
	movq	24(%rdx), %rcx
	movq	%rcx, 24(%rax)
	movq	16(%rdx), %rcx
	movq	%rcx, 16(%rax)
	movq	(%rdx), %rcx
	movq	8(%rdx), %rdx
.LBB0_36:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
.LBB0_37:
	xorl	%r13d, %r13d
	testl	%r14d, %r14d
	movl	$0, %r14d
	movl	12(%rsp), %edx
	cmovel	%edx, %r14d
	movq	144(%rsp), %rcx
	leal	1(%rcx), %eax
	andl	$15, %eax
	testl	%edx, %esi
	cmovel	%ecx, %eax
	movl	%eax, 232(%rsp)
	movq	120(%r12), %rax
	xorl	%esi, %esi
	testl	%r8d, %r8d
	sete	%sil
	andl	(%rax), %esi
	movl	%r15d, %eax
	xorl	$1, %eax
	andl	%esi, %eax
	movl	%esi, %ecx
	xorl	$1, %ecx
	andl	%r15d, %ecx
	movq	272(%rsp), %rdi
	leal	-1(%rdi), %ebp
	andl	$31, %ebp
	leal	1(%rdi), %edx
	andl	$31, %edx
	xorl	%r10d, %r10d
	cmpl	$1, %edi
	sete	%r10b
	testl	%ecx, %ecx
	cmovel	%edi, %ebp
	cmovnel	%r13d, %r8d
	testl	%eax, %eax
	cmovnel	%edx, %ebp
	movl	%ebp, 88(%rsp)
	cmovel	124(%rsp), %r13d
	movl	%r10d, 320(%rsp)
	testl	%r10d, %ecx
	movl	$1, %ecx
	cmovnel	%ecx, %r13d
	movl	%r13d, 92(%rsp)
	xorl	%edx, %edx
	cmpl	$15, %edi
	movq	112(%r12), %rdi
	movq	%rdi, 72(%rsp)
	sete	%dl
	testl	%edx, %eax
	cmovnel	%ecx, %r8d
	movq	368(%rsp), %rax
	leal	1(%rax), %edx
	andl	$15, %edx
	movl	%esi, 144(%rsp)
	testl	%esi, %esi
	cmovel	%eax, %edx
	movl	%edx, 316(%rsp)
	movl	%r15d, 108(%rsp)
	testl	%r15d, %r15d
	cmovnel	%ecx, %r14d
	movl	%r14d, 100(%rsp)
	movl	188(%rsp), %eax
	cmovel	192(%rsp), %eax
	shll	$6, %eax
	cltq
	movq	1080(%rbx,%rax), %rcx
	movq	%rcx, 3192(%rbx)
	movq	1072(%rbx,%rax), %rcx
	movq	%rcx, 3184(%rbx)
	movq	1064(%rbx,%rax), %rcx
	movq	%rcx, 3176(%rbx)
	movq	1056(%rbx,%rax), %rcx
	movq	%rcx, 3168(%rbx)
	movq	1048(%rbx,%rax), %rcx
	movq	%rcx, 3160(%rbx)
	movq	1040(%rbx,%rax), %rcx
	movq	%rcx, 3152(%rbx)
	movq	1024(%rbx,%rax), %rcx
	movq	1032(%rbx,%rax), %rax
	movq	%rax, 3144(%rbx)
	movq	%rcx, 3136(%rbx)
	movq	64(%r12), %rax
	movl	(%rax), %eax
	xorl	%r14d, %r14d
	testl	%eax, %eax
	sete	%r14b
	andl	%r11d, %r14d
	movl	16(%rsp), %ecx
	testl	%ecx, 40(%rsp)
	movl	$0, %ebp
	je	.LBB0_38
	movq	(%r12), %rcx
	movq	(%rcx), %rcx
	jmp	.LBB0_40
.LBB0_38:
	movq	240(%rsp), %rdx
	leaq	64(%rdx), %rcx
	testl	%r14d, %r14d
	cmoveq	%rdx, %rcx
.LBB0_40:
	movq	%rcx, 40(%rsp)
	movb	27(%rsp), %cl
	movb	%cl, %bpl
	xorl	%ecx, %ecx
	movq	280(%rsp), %r15
	testl	%r15d, %r15d
	setne	%cl
	movl	%r9d, %edx
	subl	%ecx, %edx
	andl	$31, %edx
	cmpl	$16, %r9d
	movl	%edx, %esi
	cmovel	%r9d, %esi
	xorl	%edi, %edi
	testl	%r15d, %r15d
	sete	%dil
	cmovnel	%edx, %esi
	xorl	%r13d, %r13d
	cmpl	$16, %r9d
	seta	%r13b
	movl	$16, %ecx
	cmovbel	%esi, %ecx
	testl	%eax, %eax
	sete	%al
	xorl	%esi, %esi
	cmpl	$0, 120(%rsp)
	sete	%sil
	movl	%esi, 272(%rsp)
	movl	104(%rsp), %r10d
	andl	%r10d, %esi
	xorl	%edx, %edx
	cmpl	$15, %r9d
	seta	%dl
	orl	%esi, %edx
	andl	%edi, %edx
	xorl	%esi, %esi
	cmpl	$1, %r15d
	sete	%dil
	andb	%dil, %al
	movzbl	%al, %eax
	xorl	%r11d, %r11d
	cmpl	$1, %r9d
	seta	%r11b
	andl	%r10d, %r11d
	orl	%r13d, %r11d
	andl	%eax, %r11d
	leal	-1(%r15), %eax
	andl	$31, %eax
	testl	%r14d, %r14d
	cmovel	%r15d, %eax
	orl	%edx, %r11d
	movl	%r11d, 200(%rsp)
	movl	%ecx, 104(%rsp)
	cmovnel	%ecx, %eax
	movl	%eax, 240(%rsp)
	movl	$1, %edx
	movl	$1, %ecx
	movl	28(%rsp), %eax
	jne	.LBB0_42
	movb	%dil, %sil
	xorl	%ecx, %ecx
	testl	%esi, %r14d
	cmovel	32(%rsp), %ecx
.LBB0_42:
	movl	%ecx, 16(%rsp)
	movl	%r8d, 48(%rsp)
	cmpl	$2, %eax
	sete	%cl
	movq	400(%rsp), %r15
	testl	%r15d, %r15d
	setne	%al
	movb	%cl, 32(%rsp)
	andb	%cl, %al
	movzbl	%al, %eax
	movl	%eax, 280(%rsp)
	orl	56(%rsp), %eax
	xorl	%ecx, %ecx
	cmpl	$1, %r9d
	sete	%cl
	andl	%eax, %ebp
	jne	.LBB0_44
	xorl	%edx, %edx
	testl	%ecx, %r14d
	cmovel	176(%rsp), %edx
.LBB0_44:
	movl	%edx, 28(%rsp)
	movl	%ecx, 12(%rsp)
	movq	392(%rsp), %rax
	movq	%rax, 416(%rsp)
	leaq	4808(%rbx), %r13
	movabsq	$bv_pad_vector, %rax
	leaq	416(%rsp), %rdx
	movq	%r13, %rdi
	movl	$512, %esi
	movl	$32, %ecx
	callq	*%rax
	movl	%r15d, %r8d
	andl	$15, %r8d
	shll	$5, %r8d
	leaq	4872(%rbx), %rdi
	movabsq	$bv_shl_vector, %rax
	movl	$512, %esi
	movq	%r13, %rdx
	movl	$512, %ecx
	callq	*%rax
	movq	3960(%rbx), %rax
	movq	3968(%rbx), %rcx
	orq	4872(%rbx), %rax
	movq	%rax, 4936(%rbx)
	orq	4880(%rbx), %rcx
	movq	%rcx, 4944(%rbx)
	movq	3976(%rbx), %rax
	orq	4888(%rbx), %rax
	movq	%rax, 4952(%rbx)
	movq	3984(%rbx), %rax
	orq	4896(%rbx), %rax
	movq	%rax, 4960(%rbx)
	movq	3992(%rbx), %rax
	orq	4904(%rbx), %rax
	movq	%rax, 4968(%rbx)
	movq	4000(%rbx), %rcx
	orq	4912(%rbx), %rcx
	movq	4008(%rbx), %rdx
	movq	4016(%rbx), %rsi
	orq	4920(%rbx), %rdx
	orq	4928(%rbx), %rsi
	leaq	4488(%rbx), %rax
	testl	%r15d, %r15d
	movq	%rcx, 4976(%rbx)
	movq	%rdx, 4984(%rbx)
	movq	%rsi, 4992(%rbx)
	movq	%r15, %r8
	je	.LBB0_46
	leaq	4936(%rbx), %rcx
	movq	56(%rcx), %rdx
	movq	%rdx, 56(%rax)
	movq	48(%rcx), %rdx
	movq	%rdx, 48(%rax)
	movq	40(%rcx), %rdx
	movq	%rdx, 40(%rax)
	movq	32(%rcx), %rdx
	movq	%rdx, 32(%rax)
	movq	24(%rcx), %rdx
	movq	%rdx, 24(%rax)
	movq	16(%rcx), %rdx
	movq	%rdx, 16(%rax)
	movq	(%rcx), %rdx
	movq	8(%rcx), %rcx
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
	jmp	.LBB0_47
.LBB0_46:
	movq	56(%r13), %rcx
	movq	%rcx, 56(%rax)
	movq	48(%r13), %rcx
	movq	%rcx, 48(%rax)
	movq	40(%r13), %rcx
	movq	%rcx, 40(%rax)
	movq	32(%r13), %rcx
	movq	%rcx, 32(%rax)
	movq	24(%r13), %rcx
	movq	%rcx, 24(%rax)
	movq	16(%r13), %rcx
	movq	%rcx, 16(%rax)
	movq	(%r13), %rcx
	movq	8(%r13), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
.LBB0_47:
	movl	168(%rsp), %r11d
	movl	36(%rsp), %edi
	movl	96(%rsp), %r15d
	leaq	3960(%rbx), %rax
	leaq	4552(%rbx), %rcx
	testl	%edi, %r15d
	movl	%ebp, %r13d
	je	.LBB0_48
	movq	4544(%rbx), %rdx
	movq	%rdx, 56(%rcx)
	movq	4536(%rbx), %rdx
	movq	%rdx, 48(%rcx)
	movq	4528(%rbx), %rdx
	movq	%rdx, 40(%rcx)
	movq	4520(%rbx), %rdx
	movq	%rdx, 32(%rcx)
	movq	4512(%rbx), %rdx
	movq	%rdx, 24(%rcx)
	movq	4504(%rbx), %rdx
	movq	%rdx, 16(%rcx)
	movq	4488(%rbx), %rdx
	movq	4496(%rbx), %rsi
	jmp	.LBB0_50
.LBB0_48:
	movq	56(%rax), %rdx
	movq	%rdx, 56(%rcx)
	movq	48(%rax), %rdx
	movq	%rdx, 48(%rcx)
	movq	40(%rax), %rdx
	movq	%rdx, 40(%rcx)
	movq	32(%rax), %rdx
	movq	%rdx, 32(%rcx)
	movq	24(%rax), %rdx
	movq	%rdx, 24(%rcx)
	movq	16(%rax), %rdx
	movq	%rdx, 16(%rcx)
	movq	(%rax), %rdx
	movq	8(%rax), %rsi
.LBB0_50:
	movq	%rsi, 8(%rcx)
	movq	%rdx, (%rcx)
	xorl	%ecx, %ecx
	cmpl	$15, %r8d
	sete	%cl
	xorl	%r10d, %r10d
	testl	%r13d, %r13d
	movl	56(%rsp), %edx
	cmovnel	%r10d, %edx
	testl	%edi, %ecx
	movl	$1, %r9d
	cmovnel	%r9d, %edx
	movl	%edx, 56(%rsp)
	leal	1(%r8), %ecx
	andl	$15, %ecx
	testl	%edi, %r15d
	cmovel	%r8d, %ecx
	movl	%ecx, 36(%rsp)
	andl	272(%rsp), %r14d
	movl	%r14d, %ecx
	xorl	$1, %ecx
	andl	%r13d, %ecx
	movl	%r13d, %ebp
	xorl	$1, %ebp
	andl	%r14d, %ebp
	movq	288(%rsp), %r8
	leal	-1(%r8), %esi
	andl	$31, %esi
	leal	1(%r8), %edi
	andl	$31, %edi
	testl	%ebp, %ebp
	cmovel	%r8d, %esi
	movl	60(%rsp), %edx
	cmovnel	%r10d, %edx
	testl	%ecx, %ecx
	cmovnel	%edi, %esi
	cmovel	120(%rsp), %r10d
	testl	%ebp, 12(%rsp)
	cmovnel	%r9d, %r10d
	xorl	%edi, %edi
	cmpl	$15, %r8d
	sete	%dil
	testl	%edi, %ecx
	cmovnel	%r9d, %edx
	movl	%edx, 60(%rsp)
	movq	408(%rsp), %rdx
	leal	1(%rdx), %r9d
	andl	$15, %r9d
	testl	%r14d, %r14d
	movl	180(%rsp), %ecx
	cmovel	184(%rsp), %ecx
	shll	$6, %ecx
	movslq	%ecx, %rcx
	movq	2104(%rbx,%rcx), %rbp
	movq	%rbp, 3256(%rbx)
	movq	2096(%rbx,%rcx), %rbp
	movq	%rbp, 3248(%rbx)
	movq	2088(%rbx,%rcx), %rbp
	movq	%rbp, 3240(%rbx)
	movq	2080(%rbx,%rcx), %rbp
	movq	%rbp, 3232(%rbx)
	movq	2072(%rbx,%rcx), %rbp
	movq	%rbp, 3224(%rbx)
	movq	2064(%rbx,%rcx), %rbp
	movq	%rbp, 3216(%rbx)
	movq	2048(%rbx,%rcx), %rbp
	movq	2056(%rbx,%rcx), %rcx
	movq	%rcx, 3208(%rbx)
	movq	%rbp, 3200(%rbx)
	testl	%r13d, %r13d
	cmovel	%edx, %r9d
	je	.LBB0_52
	leaq	2048(%rbx), %rcx
	shll	$6, %edx
	movslq	%edx, %rbp
	movq	56(%rax), %rdi
	movq	%rdi, 56(%rcx,%rbp)
	movq	48(%rax), %rdi
	movq	%rdi, 48(%rcx,%rbp)
	movq	40(%rax), %rdi
	movq	%rdi, 40(%rcx,%rbp)
	movq	32(%rax), %rdi
	movq	%rdi, 32(%rcx,%rbp)
	movq	24(%rax), %rdi
	movq	%rdi, 24(%rcx,%rbp)
	movq	16(%rax), %rdi
	movq	%rdi, 16(%rcx,%rbp)
	movq	(%rax), %rdi
	movq	8(%rax), %rdx
	movq	%rdx, 8(%rcx,%rbp)
	movq	%rdi, (%rcx,%rbp)
.LBB0_52:
	cmpl	$0, 144(%rsp)
	movl	16(%rsp), %r15d
	je	.LBB0_54
	leaq	1024(%rbx), %rcx
	movq	368(%rsp), %rdx
	shll	$6, %edx
	movslq	%edx, %rdx
	movq	72(%rsp), %rbp
	movq	56(%rbp), %rdi
	movq	%rdi, 56(%rcx,%rdx)
	movq	48(%rbp), %rdi
	movq	%rdi, 48(%rcx,%rdx)
	movq	40(%rbp), %rdi
	movq	%rdi, 40(%rcx,%rdx)
	movq	32(%rbp), %rdi
	movq	%rdi, 32(%rcx,%rdx)
	movq	24(%rbp), %rdi
	movq	%rdi, 24(%rcx,%rdx)
	movq	16(%rbp), %rdi
	movq	%rdi, 16(%rcx,%rdx)
	movq	(%rbp), %rdi
	movq	8(%rbp), %rbp
	movq	%rbp, 8(%rcx,%rdx)
	movq	%rdi, (%rcx,%rdx)
.LBB0_54:
	leaq	3200(%rbx), %rcx
	cmpl	$0, 208(%rsp)
	je	.LBB0_56
	movq	376(%rsp), %rdx
	shll	$6, %edx
	movslq	%edx, %rdx
	movq	128(%rsp), %rbp
	movq	56(%rbp), %rdi
	movq	%rdi, 56(%rbx,%rdx)
	movq	48(%rbp), %rdi
	movq	%rdi, 48(%rbx,%rdx)
	movq	40(%rbp), %rdi
	movq	%rdi, 40(%rbx,%rdx)
	movq	32(%rbp), %rdi
	movq	%rdi, 32(%rbx,%rdx)
	movq	24(%rbp), %rdi
	movq	%rdi, 24(%rbx,%rdx)
	movq	16(%rbp), %rdi
	movq	%rdi, 16(%rbx,%rdx)
	movq	(%rbp), %rdi
	movq	8(%rbp), %rbp
	movq	%rbp, 8(%rbx,%rdx)
	movq	%rdi, (%rbx,%rdx)
.LBB0_56:
	movq	56(%rcx), %rdx
	movq	%rdx, 4224(%rbx)
	movq	48(%rcx), %rdx
	movq	%rdx, 4216(%rbx)
	movq	40(%rcx), %rdx
	movq	%rdx, 4208(%rbx)
	movq	32(%rcx), %rdx
	movq	%rdx, 4200(%rbx)
	movq	24(%rcx), %rdx
	movq	%rdx, 4192(%rbx)
	movq	16(%rcx), %rdx
	movq	%rdx, 4184(%rbx)
	movq	(%rcx), %rdx
	movq	8(%rcx), %rcx
	movq	%rcx, 4176(%rbx)
	movq	%rdx, 4168(%rbx)
	movq	(%rax), %rcx
	movq	8(%rax), %rdx
	movq	%rcx, 4104(%rbx)
	movq	%rdx, 4112(%rbx)
	movq	16(%rax), %rcx
	movq	%rcx, 4120(%rbx)
	movq	24(%rax), %rcx
	movq	%rcx, 4128(%rbx)
	movq	32(%rax), %rcx
	movq	%rcx, 4136(%rbx)
	movq	40(%rax), %rcx
	movq	%rcx, 4144(%rbx)
	movq	48(%rax), %rcx
	movq	%rcx, 4152(%rbx)
	movq	56(%rax), %rcx
	movq	%rcx, 4160(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_58
	movl	$0, 4096(%rbx)
	movl	$0, 4080(%rbx)
	movl	$1, 4088(%rbx)
	movl	$0, 12(%rsp)
	movl	20(%rsp), %r14d
	movl	172(%rsp), %r8d
	movl	28(%rsp), %edi
	testl	%r11d, %r11d
	movl	280(%rsp), %edx
	je	.LBB0_63
.LBB0_62:
	movl	$0, 4072(%rbx)
	orl	%r11d, %edx
	testl	%r11d, %r11d
	je	.LBB0_66
.LBB0_65:
	movl	$0, 4064(%rbx)
	movl	$1, 4056(%rbx)
	movl	$0, 4048(%rbx)
	movl	$0, 4040(%rbx)
	jmp	.LBB0_67
.LBB0_58:
	movl	12(%rsp), %ecx
	andl	%r14d, %ecx
	orl	120(%rsp), %ecx
	andl	%r13d, %ecx
	testl	%r14d, %r14d
	movl	%ecx, 12(%rsp)
	movl	%ecx, 4096(%rbx)
	movl	172(%rsp), %r8d
	je	.LBB0_60
	movl	184(%rsp), %ecx
	addl	$2, %ecx
	andl	$15, %ecx
	movl	180(%rsp), %edx
	movl	%edx, 4080(%rbx)
	movl	%ecx, 4088(%rbx)
.LBB0_60:
	movl	20(%rsp), %r14d
	movl	28(%rsp), %edi
	testl	%r11d, %r11d
	movl	280(%rsp), %edx
	jne	.LBB0_62
.LBB0_63:
	movl	%r9d, 4072(%rbx)
	orl	%r11d, %edx
	testl	%r11d, %r11d
	jne	.LBB0_65
.LBB0_66:
	xorl	%ebp, %ebp
	movb	32(%rsp), %cl
	movb	%cl, %bpl
	movl	60(%rsp), %ecx
	movl	%ecx, 4064(%rbx)
	movl	%r10d, 4056(%rbx)
	movl	%esi, 4048(%rbx)
	movl	%ebp, 4040(%rbx)
.LBB0_67:
	movq	64(%rsp), %rcx
	movl	80(%rsp), %ebp
	movl	%r15d, %r13d
	testl	%edx, %edx
	je	.LBB0_69
	movl	$0, 4032(%rbx)
	movq	%rcx, %r15
	testl	%r11d, %r11d
	je	.LBB0_72
.LBB0_71:
	movl	$0, 4024(%rbx)
	jmp	.LBB0_73
.LBB0_69:
	movl	36(%rsp), %edx
	movl	%edx, 4032(%rbx)
	movq	%rcx, %r15
	testl	%r11d, %r11d
	jne	.LBB0_71
.LBB0_72:
	movl	56(%rsp), %ecx
	movl	%ecx, 4024(%rbx)
.LBB0_73:
	cmpl	$0, 200(%rsp)
	movq	4608(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	4600(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	4592(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	4584(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	4576(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	4568(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	4552(%rbx), %rcx
	movq	4560(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	je	.LBB0_75
	movl	104(%rsp), %r8d
	movl	%r8d, 3952(%rbx)
.LBB0_75:
	leaq	3136(%rbx), %rax
	testl	%r11d, %r11d
	movq	224(%rsp), %r10
	movl	356(%rsp), %edx
	je	.LBB0_77
	movl	$0, 3944(%rbx)
	movl	$0, 3936(%rbx)
	movl	$0, 3928(%rbx)
	movq	$0, 3920(%rbx)
	xorl	%ecx, %ecx
	movq	%rcx, 40(%rsp)
	xorl	%r13d, %r13d
	xorl	%edi, %edi
	jmp	.LBB0_78
.LBB0_77:
	movl	%edi, 3944(%rbx)
	movl	%r13d, 3936(%rbx)
	movl	240(%rsp), %ecx
	movl	%ecx, 3928(%rbx)
	movq	40(%rsp), %rcx
	movq	%rcx, 3920(%rbx)
.LBB0_78:
	testl	%r11d, %r11d
	movq	56(%rax), %rcx
	movq	%rcx, 3912(%rbx)
	movq	48(%rax), %rcx
	movq	%rcx, 3904(%rbx)
	movq	40(%rax), %rcx
	movq	%rcx, 3896(%rbx)
	movq	32(%rax), %rcx
	movq	%rcx, 3888(%rbx)
	movq	24(%rax), %rcx
	movq	%rcx, 3880(%rbx)
	movq	16(%rax), %rcx
	movq	%rcx, 3872(%rbx)
	movq	(%rax), %rcx
	movq	8(%rax), %rax
	movq	%rax, 3864(%rbx)
	movq	%rcx, 3856(%rbx)
	movq	72(%rsp), %rsi
	movq	(%rsi), %rax
	movq	8(%rsi), %rcx
	movq	%rax, 3792(%rbx)
	movq	%rcx, 3800(%rbx)
	movq	16(%rsi), %rax
	movq	%rax, 3808(%rbx)
	movq	24(%rsi), %rax
	movq	%rax, 3816(%rbx)
	movq	32(%rsi), %rax
	movq	%rax, 3824(%rbx)
	movq	40(%rsi), %rax
	movq	%rax, 3832(%rbx)
	movq	48(%rsi), %rax
	movq	%rax, 3840(%rbx)
	movq	56(%rsi), %rax
	movq	%rax, 3848(%rbx)
	je	.LBB0_80
	movl	$0, 3784(%rbx)
	movl	$0, 3768(%rbx)
	movl	$1, 3776(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_83
	jmp	.LBB0_84
.LBB0_80:
	movl	108(%rsp), %eax
	movl	320(%rsp), %esi
	andl	%eax, %esi
	orl	124(%rsp), %esi
	movl	144(%rsp), %ecx
	andl	%esi, %ecx
	testl	%eax, %eax
	movl	%ecx, 3784(%rbx)
	je	.LBB0_82
	movl	192(%rsp), %eax
	addl	$2, %eax
	andl	$15, %eax
	movl	188(%rsp), %ecx
	movl	%ecx, 3768(%rbx)
	movl	%eax, 3776(%rbx)
.LBB0_82:
	testl	%r11d, %r11d
	je	.LBB0_84
.LBB0_83:
	movl	$0, 3760(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_87
.LBB0_86:
	movl	$0, 3752(%rbx)
	movl	$1, 3744(%rbx)
	movl	$0, 3736(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_90
.LBB0_89:
	movl	$0, 3728(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_93
.LBB0_92:
	movl	$0, 3720(%rbx)
	jmp	.LBB0_94
.LBB0_84:
	movl	316(%rsp), %eax
	movl	%eax, 3760(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_86
.LBB0_87:
	movl	48(%rsp), %eax
	movl	%eax, 3752(%rbx)
	movl	92(%rsp), %eax
	movl	%eax, 3744(%rbx)
	movl	88(%rsp), %eax
	movl	%eax, 3736(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_89
.LBB0_90:
	movl	232(%rsp), %eax
	movl	%eax, 3728(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_92
.LBB0_93:
	movl	100(%rsp), %eax
	movl	%eax, 3720(%rbx)
.LBB0_94:
	testl	%r11d, %r11d
	movq	4416(%rbx), %rax
	movq	296(%rsp), %rsi
	movq	%rax, 56(%rsi)
	movq	4408(%rbx), %rax
	movq	%rax, 48(%rsi)
	movq	4400(%rbx), %rax
	movq	%rax, 40(%rsi)
	movq	4392(%rbx), %rax
	movq	%rax, 32(%rsi)
	movq	4384(%rbx), %rax
	movq	%rax, 24(%rsi)
	movq	4376(%rbx), %rax
	movq	%rax, 16(%rsi)
	movq	4360(%rbx), %rax
	movq	4368(%rbx), %rcx
	movq	%rcx, 8(%rsi)
	movq	%rax, (%rsi)
	je	.LBB0_96
	movl	$0, 3648(%rbx)
	movl	$0, 3640(%rbx)
	movl	$0, 3632(%rbx)
	movl	$0, 3624(%rbx)
	movq	$0, 3616(%rbx)
	xorl	%r10d, %r10d
	xorl	%ebp, %ebp
	xorl	%r15d, %r15d
	jmp	.LBB0_97
.LBB0_96:
	movl	%r15d, 3648(%rbx)
	movl	%ebp, 3640(%rbx)
	movl	256(%rsp), %eax
	movl	%eax, 3632(%rbx)
	movl	264(%rsp), %eax
	movl	%eax, 3624(%rbx)
	movq	%r10, 3616(%rbx)
.LBB0_97:
	testl	%r11d, %r11d
	movq	216(%rsp), %rcx
	movq	56(%rcx), %rax
	movq	%rax, 3608(%rbx)
	movq	48(%rcx), %rax
	movq	%rax, 3600(%rbx)
	movq	40(%rcx), %rax
	movq	%rax, 3592(%rbx)
	movq	32(%rcx), %rax
	movq	%rax, 3584(%rbx)
	movq	24(%rcx), %rax
	movq	%rax, 3576(%rbx)
	movq	16(%rcx), %rax
	movq	%rax, 3568(%rbx)
	movq	(%rcx), %rax
	movq	8(%rcx), %rcx
	movq	%rcx, 3560(%rbx)
	movq	%rax, 3552(%rbx)
	movq	128(%rsp), %rsi
	movq	(%rsi), %rax
	movq	8(%rsi), %rcx
	movq	%rax, 3488(%rbx)
	movq	%rcx, 3496(%rbx)
	movq	16(%rsi), %rax
	movq	%rax, 3504(%rbx)
	movq	24(%rsi), %rax
	movq	%rax, 3512(%rbx)
	movq	32(%rsi), %rax
	movq	%rax, 3520(%rbx)
	movq	40(%rsi), %rax
	movq	%rax, 3528(%rbx)
	movq	48(%rsi), %rax
	movq	%rax, 3536(%rbx)
	movq	56(%rsi), %rax
	movq	%rax, 3544(%rbx)
	je	.LBB0_99
	movl	$0, 3480(%rbx)
	movl	$0, 3464(%rbx)
	movl	$1, 3472(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_102
	jmp	.LBB0_103
.LBB0_99:
	cmpl	$0, 112(%rsp)
	movl	328(%rsp), %eax
	movl	%eax, 3480(%rbx)
	je	.LBB0_101
	movl	196(%rsp), %eax
	movl	%eax, 3464(%rbx)
	movl	312(%rsp), %eax
	movl	%eax, 3472(%rbx)
.LBB0_101:
	testl	%r11d, %r11d
	je	.LBB0_103
.LBB0_102:
	movl	$0, 3456(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_106
.LBB0_105:
	movl	$0, 3448(%rbx)
	movl	$1, 3440(%rbx)
	movl	$0, 3432(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_109
.LBB0_108:
	movl	$0, 3424(%rbx)
	testl	%r11d, %r11d
	je	.LBB0_112
.LBB0_111:
	movl	$0, 3416(%rbx)
	jmp	.LBB0_113
.LBB0_103:
	movl	324(%rsp), %eax
	movl	%eax, 3456(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_105
.LBB0_106:
	movl	52(%rsp), %eax
	movl	%eax, 3448(%rbx)
	movl	332(%rsp), %eax
	movl	%eax, 3440(%rbx)
	movl	336(%rsp), %eax
	movl	%eax, 3432(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_108
.LBB0_109:
	movl	340(%rsp), %eax
	movl	%eax, 3424(%rbx)
	testl	%r11d, %r11d
	jne	.LBB0_111
.LBB0_112:
	movl	248(%rsp), %eax
	movl	%eax, 3416(%rbx)
.LBB0_113:
	testl	%r11d, %r11d
	movq	4288(%rbx), %rax
	movq	384(%rsp), %rsi
	movq	%rax, 56(%rsi)
	movq	4280(%rbx), %rax
	movq	%rax, 48(%rsi)
	movq	4272(%rbx), %rax
	movq	%rax, 40(%rsi)
	movq	4264(%rbx), %rax
	movq	%rax, 32(%rsi)
	movq	4256(%rbx), %rax
	movq	%rax, 24(%rsi)
	movq	4248(%rbx), %rax
	movq	%rax, 16(%rsi)
	movq	4232(%rbx), %rax
	movq	4240(%rbx), %rcx
	movq	%rcx, 8(%rsi)
	movq	%rax, (%rsi)
	je	.LBB0_115
	movl	$0, 3344(%rbx)
	movl	$0, 3336(%rbx)
	movl	$0, 3328(%rbx)
	movl	$0, 3320(%rbx)
	movq	$0, 3312(%rbx)
	movl	$0, 3296(%rbx)
	movl	$0, 3304(%rbx)
	xorl	%esi, %esi
	xorl	%r14d, %r14d
	xorl	%eax, %eax
	movq	%rax, 136(%rsp)
	cmpl	$0, 116(%rsp)
	je	.LBB0_119
	jmp	.LBB0_118
.LBB0_115:
	movq	152(%rsp), %rsi
	movl	%esi, 3344(%rbx)
	movl	%r14d, 3336(%rbx)
	movl	164(%rsp), %eax
	movl	%eax, 3328(%rbx)
	movl	344(%rsp), %eax
	movl	%eax, 3320(%rbx)
	movq	136(%rsp), %rax
	movq	%rax, 3312(%rbx)
	cmpl	$0, 116(%rsp)
	jne	.LBB0_116
	cmpl	$0, 116(%rsp)
	jne	.LBB0_118
.LBB0_119:
	movl	%r14d, %r9d
	movq	%r15, %r14
	testl	%r11d, %r11d
	je	.LBB0_121
.LBB0_120:
	movl	$0, 3272(%rbx)
	movl	$0, 3264(%rbx)
	xorl	%edx, %edx
	jmp	.LBB0_122
.LBB0_116:
	movl	3304(%rbx), %eax
	movl	%eax, 3296(%rbx)
	movl	308(%rsp), %eax
	movl	%eax, 3304(%rbx)
	cmpl	$0, 116(%rsp)
	je	.LBB0_119
.LBB0_118:
	movl	3288(%rbx), %eax
	movl	%eax, 3280(%rbx)
	movl	352(%rsp), %eax
	movl	%eax, 3288(%rbx)
	movl	%r14d, %r9d
	movq	%r15, %r14
	testl	%r11d, %r11d
	jne	.LBB0_120
.LBB0_121:
	movl	348(%rsp), %eax
	movl	%eax, 3272(%rbx)
	movl	%edx, 3264(%rbx)
.LBB0_122:
	xorl	%eax, %eax
	testl	%edx, %edx
	sete	%al
	movq	160(%r12), %rcx
	movl	%eax, (%rcx)
	xorl	$2, %edx
	xorl	%eax, %eax
	orl	%edx, %edi
	sete	%al
	movq	168(%r12), %rcx
	movl	%eax, (%rcx)
	movq	176(%r12), %rax
	movq	40(%rsp), %rcx
	movq	%rcx, (%rax)
	movl	12(%rsp), %edi
.LBB0_123:
	movq	184(%r12), %rax
	movl	$0, (%rax)
	movq	192(%r12), %rax
	movl	%r13d, (%rax)
	leaq	4616(%rbx), %rax
	testl	%edi, %edi
	je	.LBB0_124
	movq	4160(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	4152(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	4144(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	4136(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	4128(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	4120(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	4104(%rbx), %rcx
	movq	4112(%rbx), %rdx
	jmp	.LBB0_126
.LBB0_124:
	movq	4224(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	4216(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	4208(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	4200(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	4192(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	4184(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	4168(%rbx), %rcx
	movq	4176(%rbx), %rdx
.LBB0_126:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	200(%r12), %rax
	movq	4672(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	4664(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	4656(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	4648(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	4640(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	4632(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	4616(%rbx), %rcx
	movq	4624(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	208(%r12), %rax
	movq	$-1, (%rax)
	movq	216(%r12), %rax
	movl	%r8d, (%rax)
	movq	224(%r12), %rax
	movq	136(%rsp), %rcx
	movq	%rcx, (%rax)
	movq	232(%r12), %rax
	movl	%r9d, (%rax)
	movq	240(%r12), %rax
	movl	$0, (%rax)
	movq	248(%r12), %rax
	movq	5064(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	5056(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	5048(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	5040(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	5032(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	5024(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	5008(%rbx), %rcx
	movq	5016(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	256(%r12), %rax
	movq	$-1, (%rax)
	movq	264(%r12), %rax
	movl	%esi, (%rax)
	movq	272(%r12), %rax
	movq	%r10, (%rax)
	movq	280(%r12), %rax
	movl	%ebp, (%rax)
	movq	288(%r12), %rax
	movl	$0, (%rax)
	movq	296(%r12), %rax
	movq	5064(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	5056(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	5048(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	5040(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	5032(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	5024(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	5008(%rbx), %rcx
	movq	5016(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	304(%r12), %rax
	movq	$-1, (%rax)
	movq	312(%r12), %rax
	movl	%r14d, (%rax)
	xorl	%eax, %eax
	addq	$424, %rsp
	.cfi_def_cfa_offset 56
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
