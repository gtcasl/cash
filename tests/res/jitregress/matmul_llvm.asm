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
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %rbx
	movq	8(%rdi), %rcx
	movl	(%rcx), %r11d
	movl	8(%rcx), %eax
	movl	%eax, 4(%rsp)
	movl	16(%rcx), %eax
	movl	%eax, (%rsp)
	movl	32(%rcx), %eax
	movl	%eax, -8(%rsp)
	movl	48(%rcx), %eax
	movl	%eax, -12(%rsp)
	movl	56(%rcx), %eax
	movl	%eax, -20(%rsp)
	movl	72(%rcx), %eax
	movl	%eax, -24(%rsp)
	movl	88(%rcx), %eax
	movl	%eax, -120(%rsp)
	movl	96(%rcx), %eax
	movl	%eax, -4(%rsp)
	movl	104(%rcx), %eax
	movl	%eax, -16(%rsp)
	movl	112(%rcx), %eax
	movl	%eax, -108(%rsp)
	movq	24(%rbx), %rax
	movl	(%rax), %eax
	movl	464(%rcx), %edx
	notl	%edx
	testl	%eax, %edx
	movl	120(%rcx), %r12d
	movl	128(%rcx), %edx
	movl	%edx, -28(%rsp)
	movl	136(%rcx), %edx
	movl	%edx, -116(%rsp)
	movl	144(%rcx), %r13d
	movl	152(%rcx), %edx
	movl	%edx, -36(%rsp)
	movl	160(%rcx), %r8d
	movl	168(%rcx), %edx
	movl	%edx, -44(%rsp)
	movl	176(%rcx), %ebp
	movl	184(%rcx), %edx
	movl	%edx, -32(%rsp)
	movl	192(%rcx), %edx
	movl	%edx, -48(%rsp)
	movl	200(%rcx), %edx
	movq	%rdx, -88(%rsp)
	movl	208(%rcx), %edx
	movl	%edx, -40(%rsp)
	movl	216(%rcx), %edx
	movl	%edx, -52(%rsp)
	movl	224(%rcx), %r9d
	movl	232(%rcx), %edx
	movl	%edx, 36(%rsp)
	movl	240(%rcx), %edx
	movl	%edx, -60(%rsp)
	movl	248(%rcx), %edx
	movl	%edx, -112(%rsp)
	movl	256(%rcx), %edx
	movl	%edx, -68(%rsp)
	movl	264(%rcx), %esi
	movl	272(%rcx), %edx
	movl	%edx, -56(%rsp)
	movl	280(%rcx), %edx
	movl	%edx, 44(%rsp)
	movl	288(%rcx), %edx
	movl	%edx, -104(%rsp)
	movl	296(%rcx), %edx
	movl	%edx, -64(%rsp)
	movl	304(%rcx), %edx
	movl	%edx, 48(%rsp)
	movl	312(%rcx), %edx
	movl	%edx, -100(%rsp)
	movl	320(%rcx), %edx
	movl	%edx, 40(%rsp)
	movl	328(%rcx), %edx
	movl	%edx, 52(%rsp)
	movl	336(%rcx), %r10d
	movl	344(%rcx), %edx
	movl	%edx, 60(%rsp)
	movl	352(%rcx), %r15d
	movl	360(%rcx), %edx
	movl	%edx, -72(%rsp)
	movl	368(%rcx), %edi
	movq	%rdi, 72(%rsp)
	movl	376(%rcx), %edx
	movl	%edx, 64(%rsp)
	movl	384(%rcx), %edx
	movl	392(%rcx), %edi
	movl	%edi, 56(%rsp)
	movl	400(%rcx), %edi
	movl	%edi, -76(%rsp)
	movl	408(%rcx), %r14d
	movl	%eax, 464(%rcx)
	je	.LBB0_12
	cmpl	$10, %r11d
	seta	-121(%rsp)
	movq	32(%rbx), %rax
	movl	(%rax), %edi
	movq	(%rbx), %rax
	movl	(%rax), %eax
	movq	%r11, 8(%rsp)
	cmpl	$11, %r11d
	sete	-122(%rsp)
	movl	%edi, 68(%rsp)
	testl	%edi, %edi
	movq	%rbx, 80(%rsp)
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
	movl	$0, -120(%rsp)
	xorl	%r12d, %r12d
	movl	$0, -116(%rsp)
	xorl	%r8d, %r8d
	xorl	%ebp, %ebp
	xorl	%ebx, %ebx
	xorl	%r9d, %r9d
	movl	$0, -112(%rsp)
	xorl	%esi, %esi
	movl	$0, -104(%rsp)
	movl	$0, -100(%rsp)
	xorl	%r10d, %r10d
	xorl	%r15d, %r15d
	xorl	%r13d, %r13d
	xorl	%edx, %edx
	xorl	%r11d, %r11d
	xorl	%r14d, %r14d
	movq	8(%rsp), %rdi
	cmpl	$0, 68(%rsp)
	jne	.LBB0_8
	jmp	.LBB0_9
.LBB0_3:
	testl	%eax, %eax
	je	.LBB0_4
	movl	%eax, 32(%rsp)
	movq	16(%rbx), %rax
	movq	%rdx, -96(%rsp)
	movl	(%rax), %edx
	movl	%edx, -120(%rsp)
	movq	8(%rbx), %rax
	movl	(%rax), %eax
	movl	%eax, 28(%rsp)
	movzbl	%al, %eax
	movl	%eax, 24(%rsp)
	movzbl	%dl, %edx
	movl	%edx, 20(%rsp)
	movsbl	%al, %eax
	movsbl	%dl, %edx
	imull	%eax, %edx
	addl	-108(%rsp), %edx
	movl	%edx, -108(%rsp)
	movsbl	-4(%rsp), %eax
	movsbl	4(%rsp), %ebx
	imull	%eax, %ebx
	addl	%ebx, -116(%rsp)
	movl	%r12d, 16(%rsp)
	movsbl	%r12b, %eax
	movsbl	(%rsp), %ebx
	imull	%eax, %ebx
	addl	%ebx, %r8d
	movsbl	%r13b, %eax
	movsbl	-8(%rsp), %edi
	imull	%eax, %edi
	addl	%edi, %ebp
	movsbl	-12(%rsp), %eax
	movsbl	-16(%rsp), %edi
	imull	%eax, %edi
	movq	-88(%rsp), %rax
	addl	%edi, %eax
	movq	%rax, -88(%rsp)
	movsbl	-32(%rsp), %eax
	movsbl	-28(%rsp), %edi
	imull	%eax, %edi
	addl	%edi, %r9d
	movsbl	-40(%rsp), %eax
	movsbl	-36(%rsp), %edi
	imull	%eax, %edi
	addl	%edi, -112(%rsp)
	movsbl	36(%rsp), %eax
	movsbl	-44(%rsp), %edi
	imull	%eax, %edi
	addl	%edi, %esi
	movsbl	-20(%rsp), %eax
	movsbl	-48(%rsp), %edi
	imull	%eax, %edi
	movl	-104(%rsp), %r12d
	addl	%edi, %r12d
	movsbl	-56(%rsp), %eax
	movsbl	-52(%rsp), %edi
	imull	%eax, %edi
	movl	-100(%rsp), %ebx
	addl	%edi, %ebx
	movsbl	-64(%rsp), %eax
	movsbl	-60(%rsp), %edi
	imull	%eax, %edi
	addl	%edi, %r10d
	movsbl	40(%rsp), %eax
	movsbl	-68(%rsp), %edi
	imull	%eax, %edi
	addl	%edi, %r15d
	movsbl	44(%rsp), %eax
	movsbl	-24(%rsp), %edi
	imull	%edi, %eax
	movq	72(%rsp), %r13
	addl	%eax, %r13d
	movsbl	48(%rsp), %eax
	movsbl	-72(%rsp), %edi
	imull	%edi, %eax
	movq	-96(%rsp), %rdi
	addl	%eax, %edi
	movq	%rdi, -96(%rsp)
	movsbl	52(%rsp), %eax
	movl	64(%rsp), %edx
	movsbl	%dl, %edi
	imull	%edi, %eax
	movl	-76(%rsp), %r11d
	addl	%eax, %r11d
	movsbl	56(%rsp), %eax
	movsbl	60(%rsp), %edi
	imull	%eax, %edi
	addl	%r14d, %edi
	andl	$16777215, %r11d
	andl	$16777215, %edi
	movl	%edi, 408(%rcx)
	movl	%r11d, 400(%rcx)
	movl	%edx, 392(%rcx)
	movq	-96(%rsp), %rax
	andl	$16777215, %eax
	movq	%rax, -96(%rsp)
	movq	-96(%rsp), %rax
	movl	%eax, 384(%rcx)
	movl	-72(%rsp), %eax
	movl	%eax, 376(%rcx)
	andl	$16777215, %r13d
	movl	%r13d, 368(%rcx)
	movl	-24(%rsp), %eax
	movl	%eax, 360(%rcx)
	andl	$16777215, %r15d
	movl	%r15d, 352(%rcx)
	movl	-68(%rsp), %eax
	movl	%eax, 344(%rcx)
	andl	$16777215, %r10d
	movl	%r10d, 336(%rcx)
	movl	-60(%rsp), %eax
	movl	%eax, 328(%rcx)
	movl	-64(%rsp), %eax
	movl	%eax, 320(%rcx)
	andl	$16777215, %ebx
	movl	%ebx, -100(%rsp)
	movl	%ebx, 312(%rcx)
	movl	-52(%rsp), %eax
	movl	%eax, 304(%rcx)
	movl	-56(%rsp), %eax
	movl	%eax, 296(%rcx)
	andl	$16777215, %r12d
	movl	%r12d, -104(%rsp)
	movl	%r12d, 288(%rcx)
	movl	-48(%rsp), %eax
	movl	%eax, 280(%rcx)
	movl	-20(%rsp), %eax
	movl	%eax, 272(%rcx)
	andl	$16777215, %esi
	movl	%esi, 264(%rcx)
	movl	-44(%rsp), %eax
	movl	%eax, 256(%rcx)
	movl	-112(%rsp), %eax
	andl	$16777215, %eax
	movl	%eax, -112(%rsp)
	movl	%eax, 248(%rcx)
	movl	-36(%rsp), %eax
	movl	%eax, 240(%rcx)
	movl	-40(%rsp), %eax
	movl	%eax, 232(%rcx)
	andl	$16777215, %r9d
	movl	%r9d, 224(%rcx)
	movl	-28(%rsp), %eax
	movl	%eax, 216(%rcx)
	movl	-32(%rsp), %eax
	movl	%eax, 208(%rcx)
	movq	-88(%rsp), %rax
	andl	$16777215, %eax
	movq	%rax, -88(%rsp)
	movl	%eax, 200(%rcx)
	movl	-16(%rsp), %eax
	movl	%eax, 192(%rcx)
	movl	-12(%rsp), %eax
	movl	%eax, 184(%rcx)
	andl	$16777215, %ebp
	movl	%ebp, 176(%rcx)
	movl	-8(%rsp), %eax
	movl	%eax, 168(%rcx)
	andl	$16777215, %r8d
	movl	%r8d, 160(%rcx)
	movl	(%rsp), %eax
	movl	%eax, 152(%rcx)
	movl	16(%rsp), %eax
	movl	%eax, 144(%rcx)
	movl	-116(%rsp), %eax
	andl	$16777215, %eax
	movl	%eax, -116(%rsp)
	movl	%eax, 136(%rcx)
	movl	4(%rsp), %eax
	movl	%eax, 128(%rcx)
	movl	-4(%rsp), %eax
	movl	%eax, 120(%rcx)
	xorl	%r14d, %r14d
	movb	-122(%rsp), %al
	movb	%al, %r14b
	movl	-108(%rsp), %edx
	andl	$16777215, %edx
	movl	%edx, 112(%rcx)
	movl	%edx, %r12d
	movl	20(%rsp), %eax
	movl	%eax, 104(%rcx)
	movl	24(%rsp), %eax
	movl	%eax, 96(%rcx)
	movl	%r14d, 88(%rcx)
	movl	80(%rcx), %eax
	movzbl	%al, %ebx
	movl	%ebx, 72(%rcx)
	movl	28(%rsp), %edx
	movl	%edx, %ebx
	shrl	$24, %ebx
	shrl	$8, %eax
	shll	$8, %ebx
	orl	%eax, %ebx
	movl	%ebx, 80(%rcx)
	movl	64(%rcx), %eax
	movl	%eax, 56(%rcx)
	movzbl	%dh, %eax
	movl	%edx, %ebx
	shrl	$16, %ebx
	movzbl	%bl, %ebx
	movl	%ebx, 64(%rcx)
	movl	%eax, 48(%rcx)
	movl	40(%rcx), %eax
	movzbl	%al, %ebx
	movl	%ebx, 32(%rcx)
	movl	-120(%rsp), %edx
	movl	%edx, %ebx
	shrl	$24, %ebx
	shrl	$8, %eax
	shll	$8, %ebx
	orl	%eax, %ebx
	movl	%ebx, 40(%rcx)
	movq	-88(%rsp), %rbx
	movl	24(%rcx), %eax
	movl	%eax, 16(%rcx)
	movl	%edx, %eax
	shrl	$16, %eax
	movzbl	%al, %eax
	movl	%eax, 24(%rcx)
	movzbl	%dh, %eax
	movq	-96(%rsp), %rdx
	movl	%eax, 8(%rcx)
	movl	32(%rsp), %eax
	movl	%r14d, -120(%rsp)
	movl	%edi, %r14d
	movq	8(%rsp), %rdi
	cmpl	$0, 68(%rsp)
	je	.LBB0_9
.LBB0_8:
	movl	$0, (%rcx)
	jmp	.LBB0_11
.LBB0_4:
	movq	8(%rsp), %rdi
	movl	-76(%rsp), %r11d
	movq	72(%rsp), %r13
	movq	-88(%rsp), %rbx
	movl	-108(%rsp), %r12d
	cmpl	$0, 68(%rsp)
	jne	.LBB0_8
.LBB0_9:
	testl	%eax, %eax
	je	.LBB0_11
	movb	-121(%rsp), %al
	shlb	$2, %al
	movzbl	%al, %eax
	leal	1(%rax,%rdi), %eax
	andl	$15, %eax
	movl	%eax, (%rcx)
.LBB0_11:
	movl	%r12d, %eax
	movq	%r8, %rdi
	shlq	$48, %rdi
	orq	%rax, %rdi
	movl	-116(%rsp), %eax
	shlq	$24, %rax
	orq	%rax, %rdi
	shrl	$16, %r8d
	shll	$8, %ebp
	orl	%r8d, %ebp
	shlq	$32, %rbx
	orq	%rbx, %rbp
	movq	%r9, %rbx
	shlq	$56, %rbx
	orq	%rbp, %rbx
	shrl	$8, %r9d
	shlq	$40, %rsi
	orq	%r9, %rsi
	movl	-112(%rsp), %eax
	shlq	$16, %rax
	orq	%rax, %rsi
	movl	-104(%rsp), %ebp
	movq	%r10, %rax
	shlq	$48, %rax
	orq	%rbp, %rax
	movl	-100(%rsp), %ebp
	shlq	$24, %rbp
	orq	%rbp, %rax
	shrl	$16, %r10d
	shll	$8, %r15d
	orl	%r10d, %r15d
	shlq	$32, %r13
	orq	%r13, %r15
	movq	%rdx, %rbp
	shlq	$56, %rbp
	orq	%r15, %rbp
	shrl	$8, %edx
	shlq	$40, %r14
	orq	%rdx, %r14
	movl	%r11d, %edx
	shlq	$16, %rdx
	orq	%rdx, %r14
	movq	%rdi, 416(%rcx)
	movq	%rbx, 424(%rcx)
	movq	%rsi, 432(%rcx)
	movq	%rax, 440(%rcx)
	movq	%rbp, 448(%rcx)
	movq	%r14, 456(%rcx)
	movq	80(%rsp), %rdx
	movq	40(%rdx), %rcx
	movq	%r14, 40(%rcx)
	movq	%rbp, 32(%rcx)
	movq	%rax, 24(%rcx)
	movq	%rsi, 16(%rcx)
	movq	%rbx, 8(%rcx)
	movq	%rdi, (%rcx)
	movq	48(%rdx), %rax
	movl	-120(%rsp), %ecx
	movl	%ecx, (%rax)
.LBB0_12:
	xorl	%eax, %eax
	addq	$88, %rsp
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
