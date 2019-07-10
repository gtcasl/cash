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
	subq	$80, %rsp
	.cfi_def_cfa_offset 136
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %r13
	movq	8(%rdi), %rcx
	movl	(%rcx), %r9d
	movl	8(%rcx), %eax
	movl	%eax, -4(%rsp)
	movl	16(%rcx), %eax
	movl	%eax, -8(%rsp)
	movl	32(%rcx), %eax
	movl	%eax, -16(%rsp)
	movl	48(%rcx), %eax
	movl	%eax, -20(%rsp)
	movl	56(%rcx), %eax
	movl	%eax, -28(%rsp)
	movl	72(%rcx), %eax
	movl	%eax, -32(%rsp)
	movl	88(%rcx), %eax
	movl	%eax, -128(%rsp)
	movl	96(%rcx), %eax
	movl	%eax, -12(%rsp)
	movl	104(%rcx), %eax
	movl	%eax, -24(%rsp)
	movl	112(%rcx), %eax
	movl	%eax, -120(%rsp)
	movq	24(%r13), %rax
	movl	(%rax), %eax
	movl	464(%rcx), %edx
	notl	%edx
	testl	%eax, %edx
	movl	120(%rcx), %edx
	movl	%edx, -36(%rsp)
	movl	128(%rcx), %edx
	movl	%edx, -40(%rsp)
	movl	136(%rcx), %ebx
	movl	144(%rcx), %edx
	movl	%edx, -100(%rsp)
	movl	152(%rcx), %edx
	movl	%edx, -48(%rsp)
	movl	160(%rcx), %r8d
	movl	168(%rcx), %edx
	movl	%edx, -56(%rsp)
	movl	176(%rcx), %r10d
	movl	184(%rcx), %edx
	movl	%edx, -44(%rsp)
	movl	192(%rcx), %edx
	movl	%edx, -60(%rsp)
	movl	200(%rcx), %edx
	movq	%rdx, -96(%rsp)
	movl	208(%rcx), %edx
	movl	%edx, -52(%rsp)
	movl	216(%rcx), %edx
	movl	%edx, -64(%rsp)
	movl	224(%rcx), %r12d
	movl	232(%rcx), %edx
	movl	%edx, 12(%rsp)
	movl	240(%rcx), %edx
	movl	%edx, -72(%rsp)
	movl	248(%rcx), %ebp
	movl	256(%rcx), %edx
	movl	%edx, -80(%rsp)
	movl	264(%rcx), %r11d
	movl	272(%rcx), %edx
	movl	%edx, -68(%rsp)
	movl	280(%rcx), %edx
	movl	%edx, 20(%rsp)
	movl	288(%rcx), %edx
	movl	%edx, -108(%rsp)
	movl	296(%rcx), %edx
	movl	%edx, -76(%rsp)
	movl	304(%rcx), %edx
	movl	%edx, 24(%rsp)
	movl	312(%rcx), %edx
	movl	320(%rcx), %esi
	movl	%esi, 16(%rsp)
	movl	328(%rcx), %esi
	movl	%esi, 28(%rsp)
	movl	336(%rcx), %esi
	movq	%rsi, 56(%rsp)
	movl	344(%rcx), %esi
	movl	%esi, 36(%rsp)
	movl	352(%rcx), %r15d
	movl	360(%rcx), %esi
	movl	%esi, -84(%rsp)
	movl	368(%rcx), %edi
	movl	376(%rcx), %esi
	movl	%esi, 40(%rsp)
	movl	384(%rcx), %esi
	movq	%rsi, 64(%rsp)
	movl	392(%rcx), %esi
	movl	%esi, 32(%rsp)
	movl	400(%rcx), %esi
	movl	408(%rcx), %r14d
	movl	%eax, 464(%rcx)
	je	.LBB0_10
	movl	%ebx, -116(%rsp)
	movl	%ebp, -112(%rsp)
	movl	%edx, -104(%rsp)
	movq	%rdi, 48(%rsp)
	movl	%esi, -88(%rsp)
	movq	(%r13), %rax
	movl	(%rax), %eax
	cmpl	$10, %r9d
	seta	%bl
	shlb	$2, %bl
	movzbl	%bl, %ebx
	leal	1(%rbx,%r9), %esi
	andl	$15, %esi
	testl	%eax, %eax
	cmovel	%r9d, %esi
	movq	%r13, 72(%rsp)
	movq	32(%r13), %rbx
	movl	(%rbx), %edi
	cmpl	$11, %r9d
	sete	%dl
	movl	%edi, 44(%rsp)
	testl	%edi, %edi
	je	.LBB0_3
	movl	$0, 408(%rcx)
	movl	$0, 400(%rcx)
	movl	$0, 392(%rcx)
	movl	$0, 384(%rcx)
	movl	$0, 376(%rcx)
	movl	$0, 368(%rcx)
	movl	$0, 360(%rcx)
	movl	$0, 352(%rcx)
	movl	$0, 344(%rcx)
	movl	$0, 336(%rcx)
	movl	$0, 328(%rcx)
	movl	$0, 320(%rcx)
	movl	$0, 312(%rcx)
	movl	$0, 304(%rcx)
	movl	$0, 296(%rcx)
	movl	$0, 288(%rcx)
	movl	$0, 280(%rcx)
	movl	$0, 272(%rcx)
	movl	$0, 264(%rcx)
	movl	$0, 256(%rcx)
	movl	$0, 248(%rcx)
	movl	$0, 240(%rcx)
	movl	$0, 232(%rcx)
	movl	$0, 224(%rcx)
	movl	$0, 216(%rcx)
	movl	$0, 208(%rcx)
	movl	$0, 200(%rcx)
	movl	$0, 192(%rcx)
	movl	$0, 184(%rcx)
	movl	$0, 176(%rcx)
	movl	$0, 168(%rcx)
	movl	$0, 160(%rcx)
	movl	$0, 152(%rcx)
	movl	$0, 144(%rcx)
	movl	$0, 136(%rcx)
	movl	$0, 128(%rcx)
	movl	$0, 120(%rcx)
	movl	$0, 112(%rcx)
	movl	$0, 104(%rcx)
	movl	$0, 96(%rcx)
	movl	$0, 88(%rcx)
	movl	$0, 72(%rcx)
	movl	$0, 80(%rcx)
	movl	$0, 56(%rcx)
	movl	$0, 64(%rcx)
	movl	$0, 48(%rcx)
	movl	$0, 32(%rcx)
	movl	$0, 40(%rcx)
	movl	$0, 16(%rcx)
	movl	$0, 24(%rcx)
	movl	$0, 8(%rcx)
	movl	$0, -128(%rsp)
	xorl	%eax, %eax
	movl	$0, -116(%rsp)
	xorl	%r8d, %r8d
	xorl	%r10d, %r10d
	xorl	%ebx, %ebx
	xorl	%r12d, %r12d
	movl	$0, -112(%rsp)
	xorl	%r11d, %r11d
	movl	$0, -108(%rsp)
	movl	$0, -104(%rsp)
	xorl	%edx, %edx
	xorl	%r15d, %r15d
	xorl	%r13d, %r13d
	xorl	%edi, %edi
	xorl	%r9d, %r9d
	xorl	%r14d, %r14d
	cmpl	$0, 44(%rsp)
	je	.LBB0_8
.LBB0_7:
	movl	$0, (%rcx)
	jmp	.LBB0_9
.LBB0_3:
	testl	%eax, %eax
	je	.LBB0_4
	movq	72(%rsp), %rbx
	movq	16(%rbx), %rax
	movb	%dl, -121(%rsp)
	movl	(%rax), %edx
	movl	%edx, -128(%rsp)
	movq	8(%rbx), %rax
	movl	(%rax), %eax
	movl	%eax, 8(%rsp)
	movzbl	%al, %eax
	movl	%eax, 4(%rsp)
	movzbl	%dl, %edx
	movl	%edx, (%rsp)
	movsbl	%al, %eax
	movsbl	%dl, %edx
	imull	%eax, %edx
	addl	-120(%rsp), %edx
	movl	%edx, -120(%rsp)
	movsbl	-12(%rsp), %eax
	movsbl	-4(%rsp), %ebx
	imull	%eax, %ebx
	addl	%ebx, -116(%rsp)
	movsbl	-36(%rsp), %eax
	movsbl	-8(%rsp), %ebx
	imull	%eax, %ebx
	addl	%ebx, %r8d
	movsbl	-100(%rsp), %eax
	movl	%esi, -100(%rsp)
	movsbl	-16(%rsp), %esi
	imull	%eax, %esi
	addl	%esi, %r10d
	movsbl	-20(%rsp), %eax
	movsbl	-24(%rsp), %esi
	imull	%eax, %esi
	movq	-96(%rsp), %rax
	addl	%esi, %eax
	movq	%rax, -96(%rsp)
	movsbl	-44(%rsp), %eax
	movsbl	-40(%rsp), %esi
	imull	%eax, %esi
	addl	%esi, %r12d
	movsbl	-52(%rsp), %eax
	movsbl	-48(%rsp), %esi
	imull	%eax, %esi
	addl	%esi, -112(%rsp)
	movsbl	12(%rsp), %eax
	movsbl	-56(%rsp), %esi
	imull	%eax, %esi
	addl	%esi, %r11d
	movsbl	-28(%rsp), %eax
	movsbl	-60(%rsp), %esi
	imull	%eax, %esi
	addl	%esi, -108(%rsp)
	movsbl	-68(%rsp), %eax
	movsbl	-64(%rsp), %esi
	imull	%eax, %esi
	movl	-104(%rsp), %ebx
	addl	%esi, %ebx
	movsbl	-76(%rsp), %eax
	movsbl	-72(%rsp), %esi
	imull	%eax, %esi
	movq	56(%rsp), %rbp
	addl	%esi, %ebp
	movsbl	16(%rsp), %eax
	movsbl	-80(%rsp), %esi
	imull	%eax, %esi
	addl	%esi, %r15d
	movsbl	20(%rsp), %eax
	movsbl	-32(%rsp), %esi
	imull	%esi, %eax
	movq	48(%rsp), %r13
	addl	%eax, %r13d
	movsbl	24(%rsp), %eax
	movsbl	-84(%rsp), %esi
	imull	%esi, %eax
	movq	64(%rsp), %rdi
	addl	%eax, %edi
	movsbl	28(%rsp), %eax
	movl	40(%rsp), %edx
	movsbl	%dl, %esi
	imull	%esi, %eax
	movl	-88(%rsp), %r9d
	addl	%eax, %r9d
	movsbl	32(%rsp), %eax
	movsbl	36(%rsp), %esi
	imull	%eax, %esi
	addl	%r14d, %esi
	andl	$16777215, %r9d
	andl	$16777215, %esi
	movl	%esi, 408(%rcx)
	movl	%r9d, 400(%rcx)
	movl	%edx, 392(%rcx)
	andl	$16777215, %edi
	movl	%edi, 384(%rcx)
	movl	-84(%rsp), %eax
	movl	%eax, 376(%rcx)
	andl	$16777215, %r13d
	movl	%r13d, 368(%rcx)
	movl	-32(%rsp), %eax
	movl	%eax, 360(%rcx)
	andl	$16777215, %r15d
	movl	%r15d, 352(%rcx)
	movl	-80(%rsp), %eax
	movl	%eax, 344(%rcx)
	andl	$16777215, %ebp
	movl	%ebp, 336(%rcx)
	movl	-72(%rsp), %eax
	movl	%eax, 328(%rcx)
	movl	-76(%rsp), %eax
	movl	%eax, 320(%rcx)
	andl	$16777215, %ebx
	movl	%ebx, -104(%rsp)
	movl	%ebx, 312(%rcx)
	movl	-64(%rsp), %eax
	movl	%eax, 304(%rcx)
	movl	-68(%rsp), %eax
	movl	%eax, 296(%rcx)
	movl	-108(%rsp), %eax
	andl	$16777215, %eax
	movl	%eax, -108(%rsp)
	movl	%eax, 288(%rcx)
	movl	-60(%rsp), %eax
	movl	%eax, 280(%rcx)
	movl	-28(%rsp), %eax
	movl	%eax, 272(%rcx)
	andl	$16777215, %r11d
	movl	%r11d, 264(%rcx)
	movl	-56(%rsp), %eax
	movl	%eax, 256(%rcx)
	movl	-112(%rsp), %eax
	andl	$16777215, %eax
	movl	%eax, -112(%rsp)
	movl	%eax, 248(%rcx)
	movq	%rbp, %rdx
	movl	-48(%rsp), %eax
	movl	%eax, 240(%rcx)
	movl	-52(%rsp), %eax
	movl	%eax, 232(%rcx)
	andl	$16777215, %r12d
	movl	%r12d, 224(%rcx)
	movl	-40(%rsp), %eax
	movl	%eax, 216(%rcx)
	movl	-44(%rsp), %eax
	movl	%eax, 208(%rcx)
	movq	-96(%rsp), %rax
	andl	$16777215, %eax
	movq	%rax, -96(%rsp)
	movl	%eax, 200(%rcx)
	movl	-24(%rsp), %eax
	movl	%eax, 192(%rcx)
	movl	-20(%rsp), %eax
	movl	%eax, 184(%rcx)
	andl	$16777215, %r10d
	movl	%r10d, 176(%rcx)
	movl	-16(%rsp), %eax
	movl	%eax, 168(%rcx)
	andl	$16777215, %r8d
	movl	%r8d, 160(%rcx)
	movl	-8(%rsp), %eax
	movl	%eax, 152(%rcx)
	movl	-36(%rsp), %eax
	movl	%eax, 144(%rcx)
	movl	-116(%rsp), %eax
	andl	$16777215, %eax
	movl	%eax, -116(%rsp)
	movl	%eax, 136(%rcx)
	movl	-4(%rsp), %eax
	movl	%eax, 128(%rcx)
	movl	-12(%rsp), %eax
	movl	%eax, 120(%rcx)
	movb	-121(%rsp), %al
	xorl	%r14d, %r14d
	movb	%al, %r14b
	movl	-120(%rsp), %eax
	andl	$16777215, %eax
	movl	%eax, -120(%rsp)
	movl	%eax, 112(%rcx)
	movl	(%rsp), %eax
	movl	%eax, 104(%rcx)
	movl	4(%rsp), %eax
	movl	%eax, 96(%rcx)
	movl	%r14d, 88(%rcx)
	movl	80(%rcx), %eax
	movzbl	%al, %ebx
	movl	%ebx, 72(%rcx)
	movl	8(%rsp), %ebp
	movl	%ebp, %ebx
	shrl	$24, %ebx
	shrl	$8, %eax
	shll	$8, %ebx
	orl	%eax, %ebx
	movl	%ebx, 80(%rcx)
	movl	64(%rcx), %eax
	movl	%eax, 56(%rcx)
	movl	%ebp, %ebx
	movzbl	%bh, %eax
	shrl	$16, %ebx
	movzbl	%bl, %ebx
	movl	%ebx, 64(%rcx)
	movl	%eax, 48(%rcx)
	movl	40(%rcx), %eax
	movzbl	%al, %ebx
	movl	%ebx, 32(%rcx)
	movl	-128(%rsp), %ebx
	shrl	$24, %ebx
	shrl	$8, %eax
	shll	$8, %ebx
	orl	%eax, %ebx
	movl	%ebx, 40(%rcx)
	movq	-96(%rsp), %rbx
	movl	24(%rcx), %eax
	movl	%eax, 16(%rcx)
	movl	-128(%rsp), %eax
	shrl	$16, %eax
	movzbl	%al, %eax
	movl	%eax, 24(%rcx)
	movl	-128(%rsp), %eax
	movzbl	%ah, %eax
	movl	%eax, 8(%rcx)
	movl	%r14d, -128(%rsp)
	movl	-120(%rsp), %eax
	movl	%esi, %r14d
	movl	-100(%rsp), %esi
	cmpl	$0, 44(%rsp)
	jne	.LBB0_7
.LBB0_8:
	movl	%esi, (%rcx)
.LBB0_9:
	movl	%eax, %eax
	movq	%r8, %rsi
	shlq	$48, %rsi
	orq	%rax, %rsi
	movl	-116(%rsp), %eax
	shlq	$24, %rax
	orq	%rax, %rsi
	shrl	$16, %r8d
	shll	$8, %r10d
	orl	%r8d, %r10d
	shlq	$32, %rbx
	orq	%rbx, %r10
	movq	%r12, %rbx
	shlq	$56, %rbx
	orq	%r10, %rbx
	shrl	$8, %r12d
	shlq	$40, %r11
	orq	%r12, %r11
	movl	-112(%rsp), %eax
	shlq	$16, %rax
	orq	%rax, %r11
	movl	-108(%rsp), %ebp
	movq	%rdx, %rax
	shlq	$48, %rax
	orq	%rbp, %rax
	movl	-104(%rsp), %ebp
	shlq	$24, %rbp
	orq	%rbp, %rax
	shrl	$16, %edx
	shll	$8, %r15d
	orl	%edx, %r15d
	shlq	$32, %r13
	orq	%r13, %r15
	movq	%rdi, %rbp
	shlq	$56, %rbp
	orq	%r15, %rbp
	shrl	$8, %edi
	shlq	$40, %r14
	orq	%rdi, %r14
	movl	%r9d, %edi
	shlq	$16, %rdi
	orq	%rdi, %r14
	movq	%rsi, 416(%rcx)
	movq	%rbx, 424(%rcx)
	movq	%r11, 432(%rcx)
	movq	%rax, 440(%rcx)
	movq	%rbp, 448(%rcx)
	movq	%r14, 456(%rcx)
	movq	72(%rsp), %rdi
	movq	40(%rdi), %rcx
	movq	%r14, 40(%rcx)
	movq	%rbp, 32(%rcx)
	movq	%rax, 24(%rcx)
	movq	%r11, 16(%rcx)
	movq	%rbx, 8(%rcx)
	movq	%rsi, (%rcx)
	movq	48(%rdi), %rax
	movl	-128(%rsp), %ecx
	movl	%ecx, (%rax)
.LBB0_10:
	xorl	%eax, %eax
	addq	$80, %rsp
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
.LBB0_4:
	.cfi_def_cfa_offset 136
	movl	-88(%rsp), %r9d
	movq	48(%rsp), %r13
	movq	64(%rsp), %rdi
	movq	56(%rsp), %rdx
	movq	-96(%rsp), %rbx
	movl	-120(%rsp), %eax
	cmpl	$0, 44(%rsp)
	jne	.LBB0_7
	jmp	.LBB0_8
.Lfunc_end0:
	.size	eval, .Lfunc_end0-eval
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
