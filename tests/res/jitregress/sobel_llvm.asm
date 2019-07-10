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
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %r10
	movq	8(%rdi), %rcx
	movl	(%rcx), %eax
	movl	%eax, -24(%rsp)
	movl	76(%rcx), %r9d
	movl	152(%rcx), %eax
	movq	%rax, 48(%rsp)
	movl	160(%rcx), %r8d
	movl	168(%rcx), %r11d
	movl	176(%rcx), %eax
	movl	%eax, -28(%rsp)
	movl	184(%rcx), %r12d
	movl	192(%rcx), %r13d
	movl	200(%rcx), %eax
	movq	%rax, 40(%rsp)
	movl	208(%rcx), %eax
	movq	%rax, 64(%rsp)
	movl	216(%rcx), %eax
	movq	%rax, 56(%rsp)
	movq	24(%r10), %rax
	movl	(%rax), %edi
	movl	424(%rcx), %eax
	notl	%eax
	testl	%edi, %eax
	movl	224(%rcx), %eax
	movl	%eax, -76(%rsp)
	movl	232(%rcx), %eax
	movl	%eax, -32(%rsp)
	movl	240(%rcx), %eax
	movl	%eax, -72(%rsp)
	movl	248(%rcx), %eax
	movl	%eax, -36(%rsp)
	movl	256(%rcx), %eax
	movl	%eax, -68(%rsp)
	movl	264(%rcx), %eax
	movl	%eax, -40(%rsp)
	movl	272(%rcx), %esi
	movl	280(%rcx), %eax
	movq	%rax, 32(%rsp)
	movl	288(%rcx), %eax
	movl	%eax, -64(%rsp)
	movl	296(%rcx), %eax
	movl	%eax, -44(%rsp)
	movl	304(%rcx), %eax
	movl	%eax, -60(%rsp)
	movl	312(%rcx), %eax
	movl	%eax, -48(%rsp)
	movl	320(%rcx), %eax
	movl	%eax, -56(%rsp)
	movl	328(%rcx), %eax
	movl	%eax, -52(%rsp)
	movl	336(%rcx), %ebp
	movl	344(%rcx), %eax
	movq	%rax, 24(%rsp)
	movl	352(%rcx), %eax
	movl	%eax, -16(%rsp)
	movl	360(%rcx), %r15d
	movl	368(%rcx), %edx
	movl	376(%rcx), %ebx
	movl	384(%rcx), %eax
	movl	%eax, -112(%rsp)
	movl	392(%rcx), %eax
	movl	%eax, -20(%rsp)
	movl	400(%rcx), %r14d
	movl	408(%rcx), %eax
	movl	%eax, -12(%rsp)
	movl	416(%rcx), %eax
	movl	%edi, 424(%rcx)
	je	.LBB0_19
	movl	%eax, -84(%rsp)
	movq	%r13, (%rsp)
	movl	%r12d, -96(%rsp)
	movq	%r8, 8(%rsp)
	movq	%r11, 16(%rsp)
	movl	%r9d, -92(%rsp)
	xorl	%r8d, %r8d
	cmpl	$4096, %r15d
	setb	%r8b
	movl	%ebx, %r12d
	notl	%r12d
	andl	%ebx, %r8d
	xorl	$1, %r8d
	cmpl	$135, %r15d
	seta	%al
	testl	%edx, %edx
	sete	%dl
	andb	%al, %dl
	movzbl	%dl, %edx
	andl	%r8d, %edx
	movl	%r14d, %r11d
	shrl	$2, %r11d
	andl	$1, %r11d
	movl	%r11d, %r9d
	xorl	$1, %r9d
	andl	%edx, %r11d
	xorl	$1, %r11d
	andl	%r11d, %r12d
	movl	%r11d, %eax
	andl	%r8d, %eax
	movl	%esi, %edi
	negl	%edi
	andl	$2047, %edi
	testl	$1024, %esi
	cmovel	%esi, %edi
	movl	%edi, -100(%rsp)
	movl	%ebp, %esi
	negl	%esi
	andl	$2047, %esi
	testl	$1024, %ebp
	cmovel	%ebp, %esi
	movl	%esi, -104(%rsp)
	xorl	%esi, %esi
	cmpl	$-3, %r15d
	seta	%sil
	incl	%esi
	testl	%eax, %eax
	cmovel	%eax, %esi
	movl	%esi, -108(%rsp)
	movq	8(%r10), %rsi
	movq	32(%r10), %rax
	movl	(%rax), %eax
	movl	%eax, -88(%rsp)
	movl	%r15d, -116(%rsp)
	cmpl	$4100, %r15d
	seta	-121(%rsp)
	movl	%ebx, %eax
	shrl	$2, %eax
	notl	%eax
	andl	(%rsi), %eax
	andl	$1, %eax
	movl	%r12d, %r15d
	xorl	$1, %r15d
	movl	%ebx, %r13d
	shrl	%r13d
	testl	%r15d, %eax
	je	.LBB0_2
	leal	(%rbx,%rbx), %esi
	andl	$6, %esi
	movl	%esi, -120(%rsp)
	jmp	.LBB0_4
.LBB0_2:
	movl	%r13d, %edi
	andl	$3, %edi
	movl	%eax, %esi
	notl	%esi
	testl	%r12d, %esi
	cmovel	%ebx, %edi
	movl	%edi, -120(%rsp)
.LBB0_4:
	andl	%eax, %ebx
	andl	%r13d, %eax
	andl	$1, %r13d
	movq	(%r10), %rsi
	movq	%r10, -8(%rsp)
	movq	16(%r10), %rbp
	movl	(%rsi), %r10d
	orl	%r13d, %r15d
	movl	%r10d, %esi
	movl	-20(%rsp), %edi
	cmovel	%edi, %esi
	orl	%r12d, %ebx
	cmovel	-112(%rsp), %esi
	movl	%esi, -80(%rsp)
	orl	%r12d, %eax
	cmovel	%edi, %r10d
	andl	%edx, %r9d
	movl	%r14d, %edx
	notl	%edx
	andl	(%rbp), %edx
	andl	$1, %edx
	movl	%edx, %edi
	xorl	$1, %edi
	movl	%r14d, %eax
	shrl	%eax
	testl	%r9d, %edi
	je	.LBB0_5
	leal	(%r14,%r14), %r15d
	andl	$6, %r15d
	jmp	.LBB0_7
.LBB0_5:
	movl	%eax, %r15d
	andl	$3, %r15d
	movl	%r9d, %ebp
	xorl	$1, %ebp
	testl	%ebp, %edx
	cmovel	%r14d, %r15d
.LBB0_7:
	andl	%r9d, %r14d
	movl	%eax, %ebp
	andl	$1, %ebp
	movl	-16(%rsp), %ebx
	movl	%ebx, %esi
	xorl	$2048, %esi
	addl	$-2048, %esi
	cmpl	$255, %esi
	movzbl	%bl, %esi
	movl	$255, %ebx
	cmovll	%esi, %ebx
	orl	%ebp, %edi
	movl	%ebx, %r12d
	movl	-84(%rsp), %esi
	cmovel	%esi, %r12d
	orl	%edx, %r14d
	cmovel	-12(%rsp), %r12d
	andl	%eax, %r9d
	orl	%edx, %r9d
	cmovel	%esi, %ebx
	movl	%ebx, 416(%rcx)
	movl	%r12d, 408(%rcx)
	movl	-88(%rsp), %edx
	testl	%edx, %edx
	je	.LBB0_9
	movl	$1, 400(%rcx)
	movl	$1, %r15d
	movl	-116(%rsp), %eax
	testl	%edx, %edx
	movl	%r10d, 392(%rcx)
	je	.LBB0_12
.LBB0_11:
	movl	$1, 376(%rcx)
	movl	$0, 368(%rcx)
	movl	$1, %ebp
	xorl	%r13d, %r13d
	movq	-8(%rsp), %r9
	testl	%edx, %edx
	je	.LBB0_15
.LBB0_14:
	movl	$0, 360(%rcx)
	testl	%r8d, %r11d
	je	.LBB0_18
.LBB0_17:
	movl	%ebp, -120(%rsp)
	movl	-32(%rsp), %r10d
	addl	-76(%rsp), %r10d
	movl	-36(%rsp), %r11d
	addl	-72(%rsp), %r11d
	movl	-40(%rsp), %r14d
	subl	-68(%rsp), %r14d
	movl	-44(%rsp), %edx
	addl	-64(%rsp), %edx
	movl	-48(%rsp), %esi
	addl	-60(%rsp), %esi
	movl	-52(%rsp), %edi
	subl	-56(%rsp), %edi
	movq	32(%rsp), %rax
	xorl	$1024, %eax
	movq	24(%rsp), %rbp
	xorl	$1024, %ebp
	leal	2048(%rax,%rbp), %eax
	andl	$4095, %eax
	movl	%eax, 352(%rcx)
	movl	-104(%rsp), %eax
	movl	%eax, 344(%rcx)
	andl	$2047, %edi
	movl	%edi, 336(%rcx)
	andl	$1023, %esi
	movl	%esi, 328(%rcx)
	andl	$1023, %edx
	movl	%edx, 320(%rcx)
	movq	64(%rsp), %rdi
	leal	(%rdi,%rdi), %eax
	movl	%eax, 312(%rcx)
	movq	48(%rsp), %rbp
	movq	40(%rsp), %rdx
	leal	(%rdx,%rbp), %eax
	movq	56(%rsp), %rsi
	addl	%esi, %edx
	andl	$511, %edx
	movl	%edx, 304(%rcx)
	movq	8(%rsp), %r8
	leal	(%r8,%r8), %edx
	movl	%edx, 296(%rcx)
	movq	16(%rsp), %rbx
	addl	%ebx, %ebp
	andl	$511, %ebp
	movl	%ebp, 288(%rcx)
	movl	-100(%rsp), %edx
	movl	%edx, 280(%rcx)
	andl	$2047, %r14d
	movl	%r14d, 272(%rcx)
	andl	$1023, %r11d
	movl	%r11d, 264(%rcx)
	andl	$1023, %r10d
	movl	%r10d, 256(%rcx)
	movl	-120(%rsp), %ebp
	movq	(%rsp), %r10
	leal	(%r10,%r10), %edx
	movl	%edx, 248(%rcx)
	leal	(%rsi,%rbx), %edx
	andl	$511, %edx
	movl	%edx, 240(%rcx)
	movl	-28(%rsp), %edx
	addl	%edx, %edx
	movl	%edx, 232(%rcx)
	andl	$511, %eax
	movl	%eax, 224(%rcx)
	movl	%edi, 200(%rcx)
	movl	%esi, 208(%rcx)
	movl	-112(%rsp), %esi
	movl	%esi, 216(%rcx)
	movl	-96(%rsp), %eax
	movl	%eax, 176(%rcx)
	movl	%r10d, 184(%rcx)
	movl	-24(%rsp), %edi
	movl	%edi, 192(%rcx)
	movl	%r8d, 152(%rcx)
	movl	%ebx, 160(%rcx)
	movl	-92(%rsp), %eax
	movl	%eax, 168(%rcx)
	movslq	148(%rcx), %rax
	movzbl	84(%rcx,%rax), %edx
	movl	%edx, 76(%rcx)
	movb	%dil, 84(%rcx,%rax)
	leal	-1(%rax), %eax
	cmpl	$62, %eax
	movl	$62, %edx
	cmovael	%edx, %eax
	movl	%eax, 148(%rcx)
	movslq	72(%rcx), %rax
	movzbl	8(%rcx,%rax), %edi
	movl	%edi, (%rcx)
	movb	%sil, 8(%rcx,%rax)
	leal	-1(%rax), %eax
	cmpl	$62, %eax
	cmovbl	%eax, %edx
	movl	%edx, 72(%rcx)
.LBB0_18:
	movl	-80(%rsp), %eax
	movl	%eax, 384(%rcx)
	shrl	$2, %ebp
	notl	%ebp
	andl	$1, %ebp
	movq	40(%r9), %rax
	movl	%ebp, (%rax)
	movq	48(%r9), %rax
	movl	%r12d, (%rax)
	notl	%r15d
	andl	$1, %r15d
	movq	56(%r9), %rax
	movl	%r15d, (%rax)
	movq	64(%r9), %rax
	movl	%r13d, (%rax)
.LBB0_19:
	xorl	%eax, %eax
	addq	$72, %rsp
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
.LBB0_9:
	.cfi_def_cfa_offset 128
	movl	%r15d, 400(%rcx)
	movl	-116(%rsp), %eax
	testl	%edx, %edx
	movl	%r10d, 392(%rcx)
	jne	.LBB0_11
.LBB0_12:
	xorl	%r13d, %r13d
	movb	-121(%rsp), %bl
	movb	%bl, %r13b
	movl	-120(%rsp), %ebp
	movl	%ebp, 376(%rcx)
	movl	%r13d, 368(%rcx)
	movq	-8(%rsp), %r9
	testl	%edx, %edx
	jne	.LBB0_14
.LBB0_15:
	movl	-108(%rsp), %edx
	addl	%eax, %edx
	movl	%edx, 360(%rcx)
	testl	%r8d, %r11d
	jne	.LBB0_17
	jmp	.LBB0_18
.Lfunc_end0:
	.size	eval, .Lfunc_end0-eval
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
