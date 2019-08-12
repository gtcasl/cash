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
	subq	$408, %rsp
	.cfi_def_cfa_offset 464
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %r9
	movq	8(%rdi), %rbx
	movl	3264(%rbx), %r13d
	movl	3272(%rbx), %eax
	movq	%rax, 56(%rsp)
	movl	3280(%rbx), %eax
	movq	%rax, 392(%rsp)
	movl	3296(%rbx), %eax
	movl	%eax, 116(%rsp)
	movq	3312(%rbx), %rax
	movq	%rax, 256(%rsp)
	movl	3320(%rbx), %eax
	movq	%rax, 128(%rsp)
	movl	3328(%rbx), %eax
	movq	%rax, 64(%rsp)
	movl	3336(%rbx), %eax
	movl	%eax, 48(%rsp)
	movl	3344(%rbx), %eax
	movq	%rax, 136(%rsp)
	movl	3416(%rbx), %eax
	movl	%eax, 44(%rsp)
	movl	3424(%rbx), %eax
	movl	%eax, 52(%rsp)
	movq	144(%r9), %rcx
	movl	(%rcx), %ecx
	movl	4936(%rbx), %edi
	notl	%edi
	testl	%ecx, %edi
	movl	3432(%rbx), %eax
	movq	%rax, 216(%rsp)
	movl	3440(%rbx), %eax
	movl	%eax, 16(%rsp)
	movl	3448(%rbx), %r15d
	movl	3456(%rbx), %edx
	movq	%rdx, 384(%rsp)
	movl	3464(%rbx), %eax
	movq	%rax, 288(%rsp)
	movl	3472(%rbx), %edi
	movl	%edi, 204(%rsp)
	movl	3480(%rbx), %eax
	movl	%eax, 240(%rsp)
	movq	3616(%rbx), %rax
	movq	%rax, 264(%rsp)
	movl	3624(%rbx), %eax
	movq	%rax, 224(%rsp)
	movl	3632(%rbx), %eax
	movq	%rax, 232(%rsp)
	movl	3640(%rbx), %r12d
	movl	3648(%rbx), %r8d
	movl	3720(%rbx), %edi
	movl	%edi, 24(%rsp)
	movl	3728(%rbx), %edi
	movl	%edi, 200(%rsp)
	movl	3736(%rbx), %eax
	movl	3744(%rbx), %edx
	movl	%edx, 124(%rsp)
	movl	3752(%rbx), %r10d
	movl	3760(%rbx), %edi
	movl	3768(%rbx), %edx
	movl	%edx, 196(%rsp)
	movl	3776(%rbx), %edx
	movl	%edx, 192(%rsp)
	movl	3784(%rbx), %edx
	movl	%edx, 20(%rsp)
	movq	3920(%rbx), %rdx
	movq	%rdx, 208(%rsp)
	movl	3928(%rbx), %edx
	movq	%rdx, 144(%rsp)
	movl	3936(%rbx), %r11d
	movl	3944(%rbx), %edx
	movl	%edx, 172(%rsp)
	movl	3952(%rbx), %r14d
	movl	4024(%rbx), %edx
	movl	4032(%rbx), %esi
	movl	%esi, 188(%rsp)
	movl	4040(%rbx), %esi
	movl	%esi, 92(%rsp)
	movl	4048(%rbx), %esi
	movq	%rsi, 304(%rsp)
	movl	4056(%rbx), %esi
	movl	%esi, 120(%rsp)
	movl	4064(%rbx), %esi
	movl	4072(%rbx), %ebp
	movl	%ebp, 176(%rsp)
	movl	4080(%rbx), %ebp
	movl	%ebp, 184(%rsp)
	movl	4088(%rbx), %ebp
	movl	%ebp, 180(%rsp)
	movl	4096(%rbx), %ebp
	movl	%ecx, 4936(%rbx)
	je	.LBB0_1
	movl	%r12d, 84(%rsp)
	movq	%r8, 272(%rsp)
	movq	%rax, 280(%rsp)
	movl	%r11d, 28(%rsp)
	movq	%r9, %r8
	movq	32(%r9), %rcx
	movl	(%rcx), %r12d
	testl	%r13d, %r13d
	movl	%r14d, 96(%rsp)
	movl	%r15d, 40(%rsp)
	movl	%edi, 156(%rsp)
	jle	.LBB0_6
	cmpl	$2, %r13d
	jge	.LBB0_4
	cmpl	$1, 56(%rsp)
	movl	$1, %eax
	adcl	$0, %eax
	jmp	.LBB0_9
.LBB0_1:
	movl	%r12d, %edi
	movl	%r11d, %edx
	movq	256(%rsp), %r15
	movl	48(%rsp), %r11d
	movl	%ebp, %ecx
	movq	136(%rsp), %r13
	movq	264(%rsp), %rbp
	movq	%r9, %r12
	movl	%r14d, %esi
	jmp	.LBB0_128
.LBB0_6:
	movl	%r13d, %eax
	jne	.LBB0_9
	xorl	%eax, %eax
	testl	%r12d, %r12d
	setne	%al
	jmp	.LBB0_9
.LBB0_4:
	movl	%r13d, %eax
	jne	.LBB0_9
	movq	40(%r8), %rcx
	xorl	%edi, %edi
	cmpl	$0, 172(%rsp)
	sete	%dil
	xorl	%eax, %eax
	testl	%edi, (%rcx)
	sete	%al
	addl	%eax, %eax
.LBB0_9:
	movl	%r10d, 32(%rsp)
	movl	%eax, 372(%rsp)
	movq	%r8, %r9
	movq	24(%r8), %rcx
	movq	152(%r8), %rdi
	movl	(%rdi), %eax
	movl	%eax, 168(%rsp)
	xorl	%r14d, %r14d
	movl	%r13d, 368(%rsp)
	testl	%r13d, %r13d
	sete	%r14b
	movl	(%rcx), %r13d
	movl	%edx, 100(%rsp)
	testl	%edx, %edx
	sete	%cl
	movl	%esi, 104(%rsp)
	testl	%esi, %esi
	sete	%al
	movb	%al, 88(%rsp)
	orb	%al, %cl
	movzbl	%cl, %esi
	testl	%r14d, %r12d
	movl	%r13d, %eax
	movl	116(%rsp), %edx
	movl	%r12d, 12(%rsp)
	jne	.LBB0_11
	movq	56(%rsp), %rdi
	leal	-1(%rdi), %eax
	testl	%edx, %esi
	cmovel	%edi, %eax
.LBB0_11:
	movl	%esi, 164(%rsp)
	movl	%eax, 360(%rsp)
	movl	3656(%rbx), %eax
	addl	3352(%rbx), %eax
	movl	%eax, 364(%rsp)
	testl	%edx, %edx
	sete	%al
	orb	%cl, %al
	movzbl	%al, %edx
	movl	24(%rsp), %r11d
	movl	%r11d, %eax
	movl	44(%rsp), %ebp
	andl	%ebp, %eax
	movl	%eax, 316(%rsp)
	movq	96(%r9), %rax
	xorl	%r12d, %r12d
	cmpl	$0, (%rax)
	sete	%r12b
	movq	136(%rsp), %r10
	movq	%r10, %rdi
	shlq	$6, %rdi
	movq	256(%rsp), %r8
	addq	%r8, %rdi
	xorl	%ecx, %ecx
	cmpl	$0, 16(%rsp)
	sete	%cl
	xorl	%r15d, %r15d
	testl	%ebp, %ebp
	sete	%r15b
	xorl	%esi, %esi
	cmpl	$15, 52(%rsp)
	sete	%sil
	xorl	%eax, %eax
	testl	%r11d, %r11d
	sete	%al
	movl	%eax, 56(%rsp)
	andl	%ebp, %eax
	xorl	$1, %eax
	movl	%edx, 112(%rsp)
	andl	%edx, %eax
	movl	%eax, 152(%rsp)
	andl	%eax, %esi
	movl	%esi, 80(%rsp)
	movl	%esi, %edx
	movl	%r15d, 36(%rsp)
	orl	%r15d, %edx
	movq	128(%rsp), %rsi
	leal	(%r10,%rsi), %eax
	leal	-1(%rsi), %ebp
	andl	$31, %ebp
	andl	%ecx, %edx
	movl	%edx, 108(%rsp)
	movq	%r10, %r11
	leal	-1(%r10,%rsi), %ecx
	cmovel	%eax, %ecx
	cmovel	%esi, %ebp
	andl	$31, %ecx
	movq	64(%rsp), %rsi
	leal	-1(%rsi), %eax
	andl	$268435455, %eax
	andl	48(%rsp), %r12d
	cmovneq	%rdi, %r8
	cmovel	%ebp, %ecx
	cmovel	%esi, %eax
	movl	%eax, 160(%rsp)
	xorl	%ebp, %ebp
	movl	12(%rsp), %edi
	testl	%r14d, %edi
	cmovel	%ecx, %ebp
	shll	$5, %r13d
	addl	$511, %r13d
	shrl	$9, %r13d
	leal	15(%r13), %r10d
	shrl	$4, %r10d
	movq	%r13, %r15
	testl	%r13d, %r13d
	setne	%dl
	testl	%esi, %esi
	setne	%al
	movl	%ebp, 356(%rsp)
	testl	%ebp, %ebp
	sete	%cl
	andb	%al, %cl
	leaq	3352(%rbx), %rax
	movq	%rax, 296(%rsp)
	testl	%r14d, %edi
	leaq	3656(%rbx), %rbp
	je	.LBB0_13
	movq	8(%r9), %rax
	movq	(%rax), %r8
	movl	%r10d, 160(%rsp)
.LBB0_13:
	movq	%rbp, 248(%rsp)
	movl	$0, %eax
	movb	%dl, %al
	movl	%eax, 128(%rsp)
	movl	%eax, %edx
	jne	.LBB0_15
	movzbl	%cl, %eax
	xorl	%ecx, %ecx
	cmpl	$1, %esi
	sete	%cl
	xorl	%edx, %edx
	testl	%ecx, %r12d
	cmovel	%eax, %edx
.LBB0_15:
	movq	%r15, %rdi
	decl	%edi
	andl	$15, %edi
	incl	%edi
	testl	%r12d, %r12d
	movl	$16, %eax
	cmovel	%r11d, %eax
	testl	%r14d, 12(%rsp)
	movl	%eax, %ecx
	movq	%rdi, %rbp
	cmovnel	%edi, %ecx
	leaq	4296(%rbx), %rax
	cmpl	$0, 240(%rsp)
	movl	%r14d, 64(%rsp)
	movq	%rcx, 136(%rsp)
	movq	%r8, 256(%rsp)
	movl	%edx, 48(%rsp)
	movl	%r10d, 76(%rsp)
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
	movq	%r9, %r12
	leaq	4616(%rbx), %r13
	movabsq	$"bv_shr_vector<false, block_type>", %rax
	movq	%r13, %rdi
	movl	$512, %esi
	movq	296(%rsp), %rdx
	movl	$512, %ecx
	movl	$32, %r8d
	callq	*%rax
	cmpl	$0, 108(%rsp)
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
	movq	%rbp, %r8
	jmp	.LBB0_24
.LBB0_19:
	leaq	4232(%rbx), %rax
	movl	152(%rsp), %ecx
	testl	%ecx, 44(%rsp)
	movq	%rbp, %r8
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
.LBB0_23:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
.LBB0_24:
	xorl	%r9d, %r9d
	cmpl	$0, 80(%rsp)
	movl	$0, %r10d
	cmovel	44(%rsp), %r10d
	movl	52(%rsp), %ecx
	incl	%ecx
	andl	$15, %ecx
	movl	%ecx, 52(%rsp)
	xorl	%r15d, %r15d
	movl	40(%rsp), %r14d
	testl	%r14d, %r14d
	sete	%r15b
	movq	80(%r12), %rcx
	movq	%rcx, 240(%rsp)
	movq	88(%r12), %rcx
	andl	(%rcx), %r15d
	movl	108(%rsp), %r11d
	movl	%r11d, %ecx
	xorl	$1, %ecx
	andl	%r15d, %ecx
	movl	%r15d, %edx
	xorl	$1, %edx
	andl	%r11d, %edx
	movq	216(%rsp), %rax
	leal	-1(%rax), %ebp
	andl	$31, %ebp
	leal	1(%rax), %esi
	andl	$31, %esi
	xorl	%edi, %edi
	cmpl	$1, %eax
	sete	%dil
	testl	%edx, %edx
	cmovel	%eax, %ebp
	cmovnel	%r9d, %r14d
	testl	%ecx, %ecx
	cmovnel	%esi, %ebp
	movl	%ebp, 352(%rsp)
	movl	$0, %esi
	movl	16(%rsp), %ebp
	cmovel	%ebp, %esi
	testl	%edi, %edx
	movl	$1, %edx
	cmovnel	%edx, %esi
	movl	%esi, 348(%rsp)
	xorl	%esi, %esi
	cmpl	$15, %eax
	sete	%sil
	testl	%esi, %ecx
	cmovnel	%edx, %r14d
	movl	%r14d, 40(%rsp)
	movq	384(%rsp), %rcx
	leal	1(%rcx), %ecx
	andl	$15, %ecx
	movl	%ecx, 324(%rsp)
	movq	288(%rsp), %rsi
	leal	2(%rsi), %ecx
	andl	$15, %ecx
	movl	%ecx, 320(%rsp)
	andl	%r11d, %edi
	orl	%ebp, %edi
	movl	%r15d, 216(%rsp)
	andl	%r15d, %edi
	movl	%edi, 344(%rsp)
	testl	%r11d, %r11d
	cmovnel	%edx, %r10d
	movl	%r10d, 80(%rsp)
	cmovnel	204(%rsp), %esi
	shll	$6, %esi
	movslq	%esi, %rcx
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
	xorl	%r10d, %r10d
	cmpl	$0, (%rdx)
	sete	%r10b
	movq	272(%rsp), %r11
	movq	%r11, %rdx
	shlq	$6, %rdx
	movq	264(%rsp), %r14
	addq	%r14, %rdx
	xorl	%esi, %esi
	cmpl	$0, 124(%rsp)
	sete	%sil
	xorl	%r15d, %r15d
	cmpl	$15, 200(%rsp)
	sete	%r15b
	movl	36(%rsp), %edi
	andl	24(%rsp), %edi
	xorl	$1, %edi
	andl	112(%rsp), %edi
	movl	%edi, 36(%rsp)
	andl	%edi, %r15d
	movl	56(%rsp), %eax
	orl	%r15d, %eax
	movq	224(%rsp), %rcx
	leal	-1(%rcx), %edi
	andl	$31, %edi
	andl	%esi, %eax
	movl	%eax, 56(%rsp)
	leal	(%r11,%rcx), %esi
	leal	-1(%r11,%rcx), %eax
	cmovel	%esi, %eax
	cmovel	%ecx, %edi
	andl	$31, %eax
	movq	232(%rsp), %rsi
	leal	-1(%rsi), %ebp
	andl	$268435455, %ebp
	andl	84(%rsp), %r10d
	cmovneq	%rdx, %r14
	cmovel	%edi, %eax
	cmovel	%esi, %ebp
	movl	12(%rsp), %edi
	movl	64(%rsp), %ecx
	testl	%ecx, %edi
	cmovnel	%r9d, %eax
	testl	%esi, %esi
	setne	%dl
	movl	%eax, 84(%rsp)
	testl	%eax, %eax
	sete	%al
	andb	%dl, %al
	leaq	3072(%rbx), %rdx
	movq	%rdx, 288(%rsp)
	testl	%ecx, %edi
	je	.LBB0_26
	movq	16(%r12), %rdx
	movq	(%rdx), %r14
	movl	76(%rsp), %ebp
.LBB0_26:
	jne	.LBB0_28
	movzbl	%al, %eax
	xorl	%edx, %edx
	cmpl	$1, %esi
	sete	%dl
	xorl	%esi, %esi
	testl	%edx, %r10d
	cmovel	%eax, %esi
	movl	%esi, 128(%rsp)
.LBB0_28:
	testl	%r10d, %r10d
	movl	$16, %eax
	cmovel	%r11d, %eax
	testl	%ecx, %edi
	cmovel	%eax, %r8d
	leaq	4424(%rbx), %rax
	cmpl	$0, 20(%rsp)
	movq	%r8, 224(%rsp)
	movl	%ebp, 76(%rsp)
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
	leaq	4680(%rbx), %r13
	movq	%r13, %rdi
	movl	$512, %esi
	movq	248(%rsp), %rbp
	movq	%rbp, %rdx
	movl	$512, %ecx
	movl	$32, %r8d
	movabsq	$"bv_shr_vector<false, block_type>", %rax
	callq	*%rax
	cmpl	$0, 56(%rsp)
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
	movl	32(%rsp), %r8d
	movq	304(%rsp), %r11
	jmp	.LBB0_37
.LBB0_32:
	leaq	4360(%rbx), %rax
	movl	36(%rsp), %ecx
	testl	%ecx, 24(%rsp)
	movl	32(%rsp), %r8d
	movq	304(%rsp), %r11
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
.LBB0_36:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
.LBB0_37:
	xorl	%r13d, %r13d
	testl	%r15d, %r15d
	movl	$0, %r10d
	cmovel	24(%rsp), %r10d
	xorl	%ecx, %ecx
	testl	%r8d, %r8d
	sete	%cl
	movq	120(%r12), %rax
	andl	(%rax), %ecx
	movl	56(%rsp), %r9d
	movl	%r9d, %eax
	xorl	$1, %eax
	andl	%ecx, %eax
	movl	%ecx, 20(%rsp)
	xorl	$1, %ecx
	andl	%r9d, %ecx
	movq	280(%rsp), %rdi
	leal	-1(%rdi), %esi
	andl	$31, %esi
	leal	1(%rdi), %edx
	andl	$31, %edx
	xorl	%ebp, %ebp
	cmpl	$1, %edi
	sete	%bpl
	testl	%ecx, %ecx
	cmovel	%edi, %esi
	cmovnel	%r13d, %r8d
	testl	%eax, %eax
	cmovnel	%edx, %esi
	movl	%esi, 336(%rsp)
	cmovel	124(%rsp), %r13d
	movl	%ebp, 332(%rsp)
	testl	%ebp, %ecx
	movl	$1, %ecx
	cmovnel	%ecx, %r13d
	movl	%r13d, 340(%rsp)
	xorl	%edx, %edx
	cmpl	$15, %edi
	sete	%dl
	testl	%edx, %eax
	movq	112(%r12), %rax
	movq	%rax, 232(%rsp)
	cmovnel	%ecx, %r8d
	testl	%r9d, %r9d
	cmovnel	%ecx, %r10d
	movl	%r10d, 272(%rsp)
	movl	192(%rsp), %eax
	cmovel	196(%rsp), %eax
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
	xorl	%r15d, %r15d
	testl	%eax, %eax
	sete	%r15b
	andl	28(%rsp), %r15d
	movl	64(%rsp), %ecx
	testl	%ecx, 12(%rsp)
	movl	$0, %r10d
	movq	%r14, 264(%rsp)
	je	.LBB0_38
	movq	(%r12), %rcx
	movq	(%rcx), %rcx
	jmp	.LBB0_40
.LBB0_38:
	movq	208(%rsp), %rdx
	leaq	64(%rdx), %rcx
	testl	%r15d, %r15d
	cmoveq	%rdx, %rcx
.LBB0_40:
	movq	%rcx, 208(%rsp)
	movb	88(%rsp), %cl
	movb	%cl, %r10b
	xorl	%ecx, %ecx
	movq	144(%rsp), %rbp
	testl	%ebp, %ebp
	setne	%cl
	movl	%r11d, %edx
	subl	%ecx, %edx
	andl	$31, %edx
	cmpl	$16, %r11d
	movl	%edx, %esi
	cmovel	%r11d, %esi
	xorl	%edi, %edi
	testl	%ebp, %ebp
	sete	%dil
	cmovnel	%edx, %esi
	xorl	%ecx, %ecx
	cmpl	$16, %r11d
	seta	%cl
	movl	$16, %r13d
	cmovbel	%esi, %r13d
	testl	%eax, %eax
	sete	%al
	xorl	%esi, %esi
	cmpl	$0, 120(%rsp)
	sete	%sil
	movl	%esi, 280(%rsp)
	movl	92(%rsp), %r9d
	andl	%r9d, %esi
	xorl	%edx, %edx
	cmpl	$15, %r11d
	seta	%dl
	orl	%esi, %edx
	andl	%edi, %edx
	xorl	%esi, %esi
	cmpl	$1, %ebp
	sete	%dil
	andb	%dil, %al
	movzbl	%al, %eax
	xorl	%r14d, %r14d
	cmpl	$1, %r11d
	seta	%r14b
	andl	%r9d, %r14d
	orl	%ecx, %r14d
	andl	%eax, %r14d
	leal	-1(%rbp), %eax
	andl	$31, %eax
	testl	%r15d, %r15d
	cmovel	%ebp, %eax
	orl	%edx, %r14d
	movl	%r13d, 88(%rsp)
	cmovnel	%r13d, %eax
	movl	%eax, 328(%rsp)
	movl	$1, 16(%rsp)
	movl	$1, %eax
	jne	.LBB0_42
	movb	%dil, %sil
	xorl	%eax, %eax
	testl	%esi, %r15d
	cmovel	28(%rsp), %eax
.LBB0_42:
	movl	%eax, 144(%rsp)
	movl	%r8d, 32(%rsp)
	cmpl	$2, 368(%rsp)
	sete	%cl
	movl	188(%rsp), %ebp
	testl	%ebp, %ebp
	setne	%al
	movb	%cl, 28(%rsp)
	andb	%cl, %al
	movzbl	%al, %eax
	movl	%eax, 92(%rsp)
	orl	100(%rsp), %eax
	xorl	%ecx, %ecx
	cmpl	$1, %r11d
	sete	%cl
	andl	%eax, %r10d
	movl	%r10d, 64(%rsp)
	jne	.LBB0_44
	xorl	%eax, %eax
	testl	%ecx, %r15d
	cmovel	172(%rsp), %eax
	movl	%eax, 16(%rsp)
.LBB0_44:
	movl	%ecx, 12(%rsp)
	movq	392(%rsp), %rax
	movq	%rax, 400(%rsp)
	leaq	4744(%rbx), %r13
	movabsq	$bv_pad_vector, %rax
	leaq	400(%rsp), %rdx
	movq	%r13, %rdi
	movl	$512, %esi
	movl	$32, %ecx
	callq	*%rax
	movl	%ebp, %r8d
	andl	$15, %r8d
	shll	$5, %r8d
	leaq	4808(%rbx), %rdi
	movabsq	$bv_shl_vector, %rax
	movl	$512, %esi
	movq	%r13, %rdx
	movl	$512, %ecx
	callq	*%rax
	movq	3960(%rbx), %rax
	movq	3968(%rbx), %rcx
	orq	4808(%rbx), %rax
	movq	%rax, 4872(%rbx)
	orq	4816(%rbx), %rcx
	movq	%rcx, 4880(%rbx)
	movq	3976(%rbx), %rax
	orq	4824(%rbx), %rax
	movq	%rax, 4888(%rbx)
	movq	3984(%rbx), %rax
	orq	4832(%rbx), %rax
	movq	%rax, 4896(%rbx)
	movq	3992(%rbx), %rax
	orq	4840(%rbx), %rax
	movq	%rax, 4904(%rbx)
	movq	4000(%rbx), %rcx
	orq	4848(%rbx), %rcx
	movq	4008(%rbx), %rdx
	movq	4016(%rbx), %rsi
	orq	4856(%rbx), %rdx
	orq	4864(%rbx), %rsi
	leaq	4488(%rbx), %rax
	testl	%ebp, %ebp
	movq	%rcx, 4912(%rbx)
	movq	%rdx, 4920(%rbx)
	movq	%rsi, 4928(%rbx)
	movq	%r12, 376(%rsp)
	je	.LBB0_46
	leaq	4872(%rbx), %rcx
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
	movl	168(%rsp), %r9d
	movl	116(%rsp), %edx
	movl	100(%rsp), %r10d
	xorl	%ecx, %ecx
	cmpl	$15, %ebp
	sete	%cl
	xorl	%r8d, %r8d
	movl	64(%rsp), %r13d
	testl	%r13d, %r13d
	cmovnel	%r8d, %r10d
	testl	%edx, %ecx
	movl	$1, %ecx
	cmovnel	%ecx, %r10d
	andl	280(%rsp), %r15d
	movl	%r15d, %esi
	xorl	$1, %esi
	andl	%r13d, %esi
	movl	%r13d, %edi
	xorl	$1, %edi
	andl	%r15d, %edi
	movq	304(%rsp), %r11
	leal	-1(%r11), %r12d
	andl	$31, %r12d
	leal	1(%r11), %ebp
	andl	$31, %ebp
	testl	%edi, %edi
	cmovel	%r11d, %r12d
	movl	104(%rsp), %eax
	cmovnel	%r8d, %eax
	testl	%esi, %esi
	cmovnel	%ebp, %r12d
	cmovel	120(%rsp), %r8d
	testl	%edi, 12(%rsp)
	cmovnel	%ecx, %r8d
	xorl	%edi, %edi
	cmpl	$15, %r11d
	sete	%dil
	testl	%edi, %esi
	cmovnel	%ecx, %eax
	movl	%eax, 104(%rsp)
	testl	%r15d, %r15d
	movl	180(%rsp), %ecx
	cmovel	184(%rsp), %ecx
	shll	$6, %ecx
	movslq	%ecx, %rcx
	movq	2104(%rbx,%rcx), %rsi
	movq	%rsi, 3256(%rbx)
	movq	2096(%rbx,%rcx), %rsi
	movq	%rsi, 3248(%rbx)
	movq	2088(%rbx,%rcx), %rsi
	movq	%rsi, 3240(%rbx)
	movq	2080(%rbx,%rcx), %rsi
	movq	%rsi, 3232(%rbx)
	movq	2072(%rbx,%rcx), %rsi
	movq	%rsi, 3224(%rbx)
	movq	2064(%rbx,%rcx), %rsi
	movq	%rsi, 3216(%rbx)
	movq	2048(%rbx,%rcx), %rsi
	movq	2056(%rbx,%rcx), %rcx
	movq	%rcx, 3208(%rbx)
	movq	%rsi, 3200(%rbx)
	leaq	3960(%rbx), %rcx
	testl	%r13d, %r13d
	je	.LBB0_49
	leaq	2048(%rbx), %rsi
	movl	176(%rsp), %edi
	shll	$6, %edi
	movslq	%edi, %rdi
	movq	56(%rcx), %rbp
	movq	%rbp, 56(%rsi,%rdi)
	movq	48(%rcx), %rbp
	movq	%rbp, 48(%rsi,%rdi)
	movq	40(%rcx), %rbp
	movq	%rbp, 40(%rsi,%rdi)
	movq	32(%rcx), %rbp
	movq	%rbp, 32(%rsi,%rdi)
	movq	24(%rcx), %rbp
	movq	%rbp, 24(%rsi,%rdi)
	movq	16(%rcx), %rbp
	movq	%rbp, 16(%rsi,%rdi)
	movq	(%rcx), %rbp
	movq	8(%rcx), %rax
	movq	%rax, 8(%rsi,%rdi)
	movq	%rbp, (%rsi,%rdi)
.LBB0_49:
	cmpl	$0, 20(%rsp)
	je	.LBB0_51
	leaq	1024(%rbx), %rax
	movl	156(%rsp), %esi
	shll	$6, %esi
	movslq	%esi, %rsi
	movq	232(%rsp), %rbp
	movq	56(%rbp), %rdi
	movq	%rdi, 56(%rax,%rsi)
	movq	48(%rbp), %rdi
	movq	%rdi, 48(%rax,%rsi)
	movq	40(%rbp), %rdi
	movq	%rdi, 40(%rax,%rsi)
	movq	32(%rbp), %rdi
	movq	%rdi, 32(%rax,%rsi)
	movq	24(%rbp), %rdi
	movq	%rdi, 24(%rax,%rsi)
	movq	16(%rbp), %rdi
	movq	%rdi, 16(%rax,%rsi)
	movq	(%rbp), %rdi
	movq	8(%rbp), %rbp
	movq	%rbp, 8(%rax,%rsi)
	movq	%rdi, (%rax,%rsi)
.LBB0_51:
	leaq	3200(%rbx), %rsi
	cmpl	$0, 216(%rsp)
	je	.LBB0_53
	movq	384(%rsp), %rax
	shll	$6, %eax
	cltq
	movq	240(%rsp), %rbp
	movq	56(%rbp), %rdi
	movq	%rdi, 56(%rbx,%rax)
	movq	48(%rbp), %rdi
	movq	%rdi, 48(%rbx,%rax)
	movq	40(%rbp), %rdi
	movq	%rdi, 40(%rbx,%rax)
	movq	32(%rbp), %rdi
	movq	%rdi, 32(%rbx,%rax)
	movq	24(%rbp), %rdi
	movq	%rdi, 24(%rbx,%rax)
	movq	16(%rbp), %rdi
	movq	%rdi, 16(%rbx,%rax)
	movq	(%rbp), %rdi
	movq	8(%rbp), %rbp
	movq	%rbp, 8(%rbx,%rax)
	movq	%rdi, (%rbx,%rax)
.LBB0_53:
	movq	56(%rsi), %rax
	movq	%rax, 4224(%rbx)
	movq	48(%rsi), %rax
	movq	%rax, 4216(%rbx)
	movq	40(%rsi), %rax
	movq	%rax, 4208(%rbx)
	movq	32(%rsi), %rax
	movq	%rax, 4200(%rbx)
	movq	24(%rsi), %rax
	movq	%rax, 4192(%rbx)
	movq	16(%rsi), %rax
	movq	%rax, 4184(%rbx)
	movq	(%rsi), %rax
	movq	8(%rsi), %rsi
	movq	%rsi, 4176(%rbx)
	movq	%rax, 4168(%rbx)
	movq	(%rcx), %rax
	movq	8(%rcx), %rsi
	movq	%rax, 4104(%rbx)
	movq	%rsi, 4112(%rbx)
	movq	16(%rcx), %rax
	movq	%rax, 4120(%rbx)
	movq	24(%rcx), %rax
	movq	%rax, 4128(%rbx)
	movq	32(%rcx), %rax
	movq	%rax, 4136(%rbx)
	movq	40(%rcx), %rax
	movq	%rax, 4144(%rbx)
	movq	48(%rcx), %rax
	movq	%rax, 4152(%rbx)
	movq	56(%rcx), %rax
	movq	%rax, 4160(%rbx)
	testl	%r9d, %r9d
	je	.LBB0_55
	movl	$0, 4096(%rbx)
	movl	$0, 4080(%rbx)
	movl	$1, 4088(%rbx)
	movl	$0, 12(%rsp)
	movq	248(%rsp), %rsi
	movl	164(%rsp), %r13d
	movq	136(%rsp), %r15
	movl	144(%rsp), %r11d
	testl	%r9d, %r9d
	je	.LBB0_60
.LBB0_59:
	movl	$0, 4072(%rbx)
	movl	92(%rsp), %eax
	orl	%r9d, %eax
	testl	%r9d, %r9d
	jne	.LBB0_63
	jmp	.LBB0_64
.LBB0_55:
	movl	12(%rsp), %eax
	andl	%r15d, %eax
	orl	120(%rsp), %eax
	andl	%r13d, %eax
	testl	%r15d, %r15d
	movl	%eax, 12(%rsp)
	movl	%eax, 4096(%rbx)
	movl	164(%rsp), %r13d
	je	.LBB0_57
	movl	184(%rsp), %eax
	addl	$2, %eax
	andl	$15, %eax
	movl	180(%rsp), %esi
	movl	%esi, 4080(%rbx)
	movl	%eax, 4088(%rbx)
.LBB0_57:
	movq	248(%rsp), %rsi
	movq	136(%rsp), %r15
	movl	144(%rsp), %r11d
	testl	%r9d, %r9d
	jne	.LBB0_59
.LBB0_60:
	cmpl	$0, 64(%rsp)
	je	.LBB0_62
	movl	176(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 4072(%rbx)
.LBB0_62:
	movl	92(%rsp), %eax
	orl	%r9d, %eax
	testl	%r9d, %r9d
	je	.LBB0_64
.LBB0_63:
	movl	$0, 4064(%rbx)
	movl	$1, 4056(%rbx)
	movl	$0, 4048(%rbx)
	movl	$0, 4040(%rbx)
	movq	224(%rsp), %r8
	movq	376(%rsp), %r12
	testl	%eax, %eax
	je	.LBB0_67
.LBB0_66:
	movl	$0, 4032(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_70
	jmp	.LBB0_71
.LBB0_64:
	xorl	%ebp, %ebp
	movl	%edx, %edi
	movb	28(%rsp), %dl
	movb	%dl, %bpl
	movl	%edi, %edx
	movl	104(%rsp), %edi
	movl	%edi, 4064(%rbx)
	movl	%r8d, 4056(%rbx)
	movl	%r12d, 4048(%rbx)
	movl	%ebp, 4040(%rbx)
	movq	224(%rsp), %r8
	movq	376(%rsp), %r12
	testl	%eax, %eax
	jne	.LBB0_66
.LBB0_67:
	testl	%edx, %r13d
	je	.LBB0_69
	movl	%edx, %eax
	movl	188(%rsp), %edx
	incl	%edx
	andl	$15, %edx
	movl	%edx, 4032(%rbx)
	movl	%eax, %edx
.LBB0_69:
	testl	%r9d, %r9d
	je	.LBB0_71
.LBB0_70:
	movl	$0, 4024(%rbx)
	testl	%edx, %r13d
	je	.LBB0_74
.LBB0_73:
	movq	4544(%rbx), %rax
	movq	%rax, 56(%rcx)
	movq	4536(%rbx), %rax
	movq	%rax, 48(%rcx)
	movq	4528(%rbx), %rax
	movq	%rax, 40(%rcx)
	movq	4520(%rbx), %rax
	movq	%rax, 32(%rcx)
	movq	4512(%rbx), %rax
	movq	%rax, 24(%rcx)
	movq	4504(%rbx), %rax
	movq	%rax, 16(%rcx)
	movq	4488(%rbx), %rax
	movq	4496(%rbx), %rdx
	movq	%rdx, 8(%rcx)
	movq	%rax, (%rcx)
.LBB0_74:
	testl	%r14d, %r14d
	movl	16(%rsp), %ecx
	je	.LBB0_76
	movl	88(%rsp), %eax
	movl	%eax, 3952(%rbx)
	movl	%eax, 96(%rsp)
.LBB0_76:
	leaq	3136(%rbx), %rax
	testl	%r9d, %r9d
	movq	264(%rsp), %rbp
	movl	372(%rsp), %r10d
	movq	208(%rsp), %rdi
	je	.LBB0_78
	movl	$0, 3944(%rbx)
	movl	$0, 3936(%rbx)
	movl	$0, 3928(%rbx)
	movq	$0, 3920(%rbx)
	xorl	%edx, %edx
	xorl	%r11d, %r11d
	movl	$0, 16(%rsp)
	jmp	.LBB0_79
.LBB0_71:
	movl	%r10d, 4024(%rbx)
	testl	%edx, %r13d
	jne	.LBB0_73
	jmp	.LBB0_74
.LBB0_78:
	movl	%ecx, 16(%rsp)
	movl	%ecx, 3944(%rbx)
	movl	%r11d, 3936(%rbx)
	movl	328(%rsp), %ecx
	movl	%ecx, 3928(%rbx)
	movq	%rdi, %rdx
	movq	%rdi, 3920(%rbx)
.LBB0_79:
	testl	%r9d, %r9d
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
	movq	232(%rsp), %rdi
	movq	(%rdi), %rax
	movq	8(%rdi), %rcx
	movq	%rax, 3792(%rbx)
	movq	%rcx, 3800(%rbx)
	movq	16(%rdi), %rax
	movq	%rax, 3808(%rbx)
	movq	24(%rdi), %rax
	movq	%rax, 3816(%rbx)
	movq	32(%rdi), %rax
	movq	%rax, 3824(%rbx)
	movq	40(%rdi), %rax
	movq	%rax, 3832(%rbx)
	movq	48(%rdi), %rax
	movq	%rax, 3840(%rbx)
	movq	56(%rdi), %rax
	movq	%rax, 3848(%rbx)
	je	.LBB0_81
	movl	$0, 3784(%rbx)
	movl	$0, 3768(%rbx)
	movl	$1, 3776(%rbx)
	testl	%r9d, %r9d
	movq	%rdx, %rdi
	jne	.LBB0_84
	jmp	.LBB0_85
.LBB0_81:
	movl	56(%rsp), %eax
	movl	332(%rsp), %ecx
	andl	%eax, %ecx
	orl	124(%rsp), %ecx
	andl	20(%rsp), %ecx
	testl	%eax, %eax
	movl	%ecx, 3784(%rbx)
	je	.LBB0_83
	movl	196(%rsp), %eax
	addl	$2, %eax
	andl	$15, %eax
	movl	192(%rsp), %ecx
	movl	%ecx, 3768(%rbx)
	movl	%eax, 3776(%rbx)
.LBB0_83:
	testl	%r9d, %r9d
	movq	%rdx, %rdi
	je	.LBB0_85
.LBB0_84:
	movl	$0, 3760(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_88
	jmp	.LBB0_89
.LBB0_85:
	cmpl	$0, 20(%rsp)
	je	.LBB0_87
	movl	156(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 3760(%rbx)
.LBB0_87:
	testl	%r9d, %r9d
	je	.LBB0_89
.LBB0_88:
	movl	$0, 3752(%rbx)
	movl	$1, 3744(%rbx)
	movl	$0, 3736(%rbx)
	testl	%r9d, %r9d
	je	.LBB0_92
.LBB0_91:
	movl	$0, 3728(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_95
	jmp	.LBB0_96
.LBB0_89:
	movl	32(%rsp), %eax
	movl	%eax, 3752(%rbx)
	movl	340(%rsp), %eax
	movl	%eax, 3744(%rbx)
	movl	336(%rsp), %eax
	movl	%eax, 3736(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_91
.LBB0_92:
	movl	36(%rsp), %eax
	testl	%eax, 24(%rsp)
	je	.LBB0_94
	movl	200(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 3728(%rbx)
.LBB0_94:
	testl	%r9d, %r9d
	je	.LBB0_96
.LBB0_95:
	movl	$0, 3720(%rbx)
	jmp	.LBB0_97
.LBB0_96:
	movl	272(%rsp), %eax
	movl	%eax, 3720(%rbx)
.LBB0_97:
	testl	%r9d, %r9d
	movq	4416(%rbx), %rax
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
	je	.LBB0_99
	movl	$0, 3648(%rbx)
	movl	$0, 3640(%rbx)
	movl	$0, 3632(%rbx)
	movl	$0, 3624(%rbx)
	movq	$0, 3616(%rbx)
	xorl	%ebp, %ebp
	movl	$0, 128(%rsp)
	xorl	%r8d, %r8d
	jmp	.LBB0_100
.LBB0_99:
	movl	%r8d, 3648(%rbx)
	movl	128(%rsp), %eax
	movl	%eax, 3640(%rbx)
	movl	76(%rsp), %eax
	movl	%eax, 3632(%rbx)
	movl	84(%rsp), %eax
	movl	%eax, 3624(%rbx)
	movq	%rbp, 3616(%rbx)
.LBB0_100:
	testl	%r9d, %r9d
	movq	288(%rsp), %rcx
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
	movq	240(%rsp), %rsi
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
	je	.LBB0_102
	movl	$0, 3480(%rbx)
	movl	$0, 3464(%rbx)
	movl	$1, 3472(%rbx)
	movl	40(%rsp), %eax
	testl	%r9d, %r9d
	jne	.LBB0_105
	jmp	.LBB0_106
.LBB0_102:
	cmpl	$0, 108(%rsp)
	movl	344(%rsp), %eax
	movl	%eax, 3480(%rbx)
	movl	40(%rsp), %eax
	je	.LBB0_104
	movl	204(%rsp), %ecx
	movl	%ecx, 3464(%rbx)
	movl	320(%rsp), %ecx
	movl	%ecx, 3472(%rbx)
.LBB0_104:
	testl	%r9d, %r9d
	je	.LBB0_106
.LBB0_105:
	movl	$0, 3456(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_109
	jmp	.LBB0_110
.LBB0_106:
	cmpl	$0, 216(%rsp)
	je	.LBB0_108
	movl	324(%rsp), %ecx
	movl	%ecx, 3456(%rbx)
.LBB0_108:
	testl	%r9d, %r9d
	je	.LBB0_110
.LBB0_109:
	movl	$0, 3448(%rbx)
	movl	$1, 3440(%rbx)
	movl	$0, 3432(%rbx)
	testl	%r9d, %r9d
	je	.LBB0_113
.LBB0_112:
	movl	$0, 3424(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_116
	jmp	.LBB0_117
.LBB0_110:
	movl	%eax, 3448(%rbx)
	movl	348(%rsp), %eax
	movl	%eax, 3440(%rbx)
	movl	352(%rsp), %eax
	movl	%eax, 3432(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_112
.LBB0_113:
	movl	152(%rsp), %eax
	testl	%eax, 44(%rsp)
	je	.LBB0_115
	movl	52(%rsp), %eax
	movl	%eax, 3424(%rbx)
.LBB0_115:
	testl	%r9d, %r9d
	je	.LBB0_117
.LBB0_116:
	movl	$0, 3416(%rbx)
	jmp	.LBB0_118
.LBB0_117:
	movl	80(%rsp), %eax
	movl	%eax, 3416(%rbx)
.LBB0_118:
	movl	%r11d, %r14d
	testl	%r9d, %r9d
	movq	4288(%rbx), %rax
	movq	296(%rsp), %rsi
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
	je	.LBB0_120
	movl	$0, 3344(%rbx)
	movl	$0, 3336(%rbx)
	movl	$0, 3328(%rbx)
	movl	$0, 3320(%rbx)
	movq	$0, 3312(%rbx)
	movl	$0, 3296(%rbx)
	movl	$0, 3304(%rbx)
	xorl	%r13d, %r13d
	xorl	%r11d, %r11d
	xorl	%r15d, %r15d
	cmpl	$0, 112(%rsp)
	je	.LBB0_124
	jmp	.LBB0_123
.LBB0_120:
	movq	%r15, %r13
	movl	%r15d, 3344(%rbx)
	movl	48(%rsp), %r11d
	movl	%r11d, 3336(%rbx)
	movl	160(%rsp), %eax
	movl	%eax, 3328(%rbx)
	movl	356(%rsp), %eax
	movl	%eax, 3320(%rbx)
	movq	256(%rsp), %r15
	movq	%r15, 3312(%rbx)
	cmpl	$0, 112(%rsp)
	jne	.LBB0_121
	cmpl	$0, 112(%rsp)
	jne	.LBB0_123
.LBB0_124:
	testl	%r9d, %r9d
	je	.LBB0_126
.LBB0_125:
	movl	$0, 3272(%rbx)
	movl	$0, 3264(%rbx)
	xorl	%r10d, %r10d
	jmp	.LBB0_127
.LBB0_121:
	movl	3304(%rbx), %eax
	movl	%eax, 3296(%rbx)
	movl	316(%rsp), %eax
	movl	%eax, 3304(%rbx)
	cmpl	$0, 112(%rsp)
	je	.LBB0_124
.LBB0_123:
	movl	3288(%rbx), %eax
	movl	%eax, 3280(%rbx)
	movl	364(%rsp), %eax
	movl	%eax, 3288(%rbx)
	testl	%r9d, %r9d
	jne	.LBB0_125
.LBB0_126:
	movl	360(%rsp), %eax
	movl	%eax, 3272(%rbx)
	movl	%r10d, 3264(%rbx)
.LBB0_127:
	movl	96(%rsp), %esi
	xorl	%eax, %eax
	testl	%r10d, %r10d
	sete	%al
	movq	160(%r12), %rcx
	movl	%eax, (%rcx)
	xorl	$2, %r10d
	xorl	%eax, %eax
	orl	%r10d, 16(%rsp)
	sete	%al
	movq	168(%r12), %rcx
	movl	%eax, (%rcx)
	movq	176(%r12), %rax
	movq	%rdi, (%rax)
	movl	128(%rsp), %edi
	movl	12(%rsp), %ecx
	movl	%r14d, %edx
.LBB0_128:
	movq	184(%r12), %rax
	movl	$0, (%rax)
	movq	192(%r12), %rax
	movl	%edx, (%rax)
	leaq	4552(%rbx), %rax
	testl	%ecx, %ecx
	je	.LBB0_129
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
	jmp	.LBB0_131
.LBB0_129:
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
.LBB0_131:
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	200(%r12), %rax
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
	movq	208(%r12), %rax
	movq	$-1, (%rax)
	movq	216(%r12), %rax
	movl	%esi, (%rax)
	movq	224(%r12), %rax
	movq	%r15, (%rax)
	movq	232(%r12), %rax
	movl	%r11d, (%rax)
	movq	240(%r12), %rax
	movl	$0, (%rax)
	movq	248(%r12), %rax
	movq	5000(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	4992(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	4984(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	4976(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	4968(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	4960(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	4944(%rbx), %rcx
	movq	4952(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	256(%r12), %rax
	movq	$-1, (%rax)
	movq	264(%r12), %rax
	movl	%r13d, (%rax)
	movq	272(%r12), %rax
	movq	%rbp, (%rax)
	movq	280(%r12), %rax
	movl	%edi, (%rax)
	movq	288(%r12), %rax
	movl	$0, (%rax)
	movq	296(%r12), %rax
	movq	5000(%rbx), %rcx
	movq	%rcx, 56(%rax)
	movq	4992(%rbx), %rcx
	movq	%rcx, 48(%rax)
	movq	4984(%rbx), %rcx
	movq	%rcx, 40(%rax)
	movq	4976(%rbx), %rcx
	movq	%rcx, 32(%rax)
	movq	4968(%rbx), %rcx
	movq	%rcx, 24(%rax)
	movq	4960(%rbx), %rcx
	movq	%rcx, 16(%rax)
	movq	4944(%rbx), %rcx
	movq	4952(%rbx), %rdx
	movq	%rdx, 8(%rax)
	movq	%rcx, (%rax)
	movq	304(%r12), %rax
	movq	$-1, (%rax)
	movq	312(%r12), %rax
	movl	%r8d, (%rax)
	xorl	%eax, %eax
	addq	$408, %rsp
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
