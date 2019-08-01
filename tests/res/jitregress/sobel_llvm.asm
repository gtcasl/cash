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
	movq	(%rdi), %r8
	movq	8(%rdi), %rcx
	movl	(%rcx), %r15d
	movl	76(%rcx), %r9d
	movl	152(%rcx), %r12d
	movl	160(%rcx), %eax
	movl	%eax, -84(%rsp)
	movl	168(%rcx), %eax
	movq	%rax, -24(%rsp)
	movl	176(%rcx), %eax
	movl	%eax, -116(%rsp)
	movl	184(%rcx), %edx
	movl	%edx, -40(%rsp)
	movl	192(%rcx), %eax
	movl	%eax, -100(%rsp)
	movl	200(%rcx), %esi
	movl	208(%rcx), %eax
	movl	%eax, -104(%rsp)
	movl	216(%rcx), %eax
	movq	%rax, -72(%rsp)
	movq	24(%r8), %rdx
	movl	(%rdx), %ebp
	movl	304(%rcx), %edx
	notl	%edx
	testl	%ebp, %edx
	movl	224(%rcx), %r10d
	movl	232(%rcx), %edx
	movl	240(%rcx), %eax
	movl	%eax, -36(%rsp)
	movl	256(%rcx), %r13d
	movl	264(%rcx), %edi
	movl	272(%rcx), %eax
	movl	280(%rcx), %r11d
	movl	288(%rcx), %ebx
	movl	296(%rcx), %r14d
	movl	%r14d, -112(%rsp)
	movl	%ebp, 304(%rcx)
	je	.LBB0_33
	movl	%eax, -96(%rsp)
	movl	%edi, -44(%rsp)
	movl	%r9d, -64(%rsp)
	movl	%r15d, -60(%rsp)
	movl	%ebx, -88(%rsp)
	xorl	%ebp, %ebp
	cmpl	$4096, %r10d
	setb	%bpl
	movl	%r13d, %r9d
	notl	%r9d
	andl	%r13d, %ebp
	xorl	$1, %ebp
	cmpl	$134, %r10d
	seta	%bl
	testl	%edx, %edx
	sete	%dl
	andb	%bl, %dl
	movzbl	%dl, %edx
	movl	%ebp, -48(%rsp)
	andl	%ebp, %edx
	movl	%r11d, %eax
	shrl	$2, %eax
	andl	$1, %eax
	movl	%eax, %r14d
	xorl	$1, %r14d
	movl	%edx, -92(%rsp)
	andl	%edx, %eax
	xorl	$1, %eax
	movl	%eax, -108(%rsp)
	andl	%eax, %r9d
	cmpl	$-3, %r10d
	seta	-118(%rsp)
	movq	-24(%rsp), %r15
	movq	8(%r8), %rax
	movq	%rax, -16(%rsp)
	movq	%r10, -32(%rsp)
	cmpl	$4100, %r10d
	seta	-117(%rsp)
	movq	-72(%rsp), %rdi
	leal	(%rdi,%r15), %edx
	andl	$511, %edx
	movzbl	-100(%rsp), %ebp
	leal	(%rdx,%rbp,2), %eax
	leal	(%rsi,%r12), %ebp
	andl	$511, %ebp
	movzbl	-116(%rsp), %edx
	leal	(%rbp,%rdx,2), %ebp
	movl	%ebp, %edx
	subl	%eax, %edx
	subl	%ebp, %eax
	movq	%r8, -80(%rsp)
	movq	32(%r8), %rbp
	movl	(%rbp), %ebp
	movl	%ebp, -52(%rsp)
	cmovbel	%edx, %eax
	movl	%eax, -56(%rsp)
	addl	%edi, %esi
	andl	$511, %esi
	movzbl	-104(%rsp), %edx
	leal	(%rsi,%rdx,2), %r8d
	addl	%r15d, %r12d
	andl	$511, %r12d
	movzbl	-84(%rsp), %edx
	leal	(%r12,%rdx,2), %eax
	movl	%eax, %edx
	subl	%r8d, %edx
	subl	%eax, %r8d
	cmovbel	%edx, %r8d
	movl	%r13d, %r10d
	shrl	$2, %r10d
	notl	%r10d
	movq	-16(%rsp), %rax
	andl	(%rax), %r10d
	andl	$1, %r10d
	movl	%r9d, %ebp
	xorl	$1, %ebp
	movl	%r13d, %eax
	shrl	%eax
	testl	%ebp, %r10d
	movl	%r9d, -116(%rsp)
	movq	%r13, -8(%rsp)
	je	.LBB0_2
	leal	(%r13,%r13), %r15d
	andl	$6, %r15d
	jmp	.LBB0_4
.LBB0_2:
	movl	%eax, %r15d
	andl	$3, %r15d
	movl	%r10d, %edx
	notl	%edx
	testl	%r9d, %edx
	cmovel	%r13d, %r15d
.LBB0_4:
	movl	-112(%rsp), %r9d
	movq	-80(%rsp), %rsi
	movl	-92(%rsp), %edi
	movl	%eax, %edx
	andl	$1, %edx
	movq	(%rsi), %rbx
	movq	16(%rsi), %rsi
	movl	(%rbx), %ebx
	orl	%edx, %ebp
	movl	-96(%rsp), %edx
	cmovnel	%ebx, %edx
	movl	%edx, -96(%rsp)
	andl	%edi, %r14d
	movl	%r11d, %ebp
	notl	%ebp
	andl	(%rsi), %ebp
	andl	$1, %ebp
	movl	%ebp, %r12d
	xorl	$1, %r12d
	movl	%r11d, %r13d
	shrl	%r13d
	testl	%r14d, %r12d
	movl	%ebx, -112(%rsp)
	je	.LBB0_5
	leal	(%r11,%r11), %ebx
	andl	$6, %ebx
	jmp	.LBB0_7
.LBB0_5:
	movl	%r13d, %ebx
	andl	$3, %ebx
	movl	%r14d, %edx
	xorl	$1, %edx
	testl	%edx, %ebp
	cmovel	%r11d, %ebx
.LBB0_7:
	movl	-88(%rsp), %esi
	movl	-116(%rsp), %edi
	movl	%r13d, %edx
	andl	$1, %edx
	orl	%edx, %r12d
	movl	-36(%rsp), %edx
	cmovnel	%edx, %r9d
	andl	%r14d, %r11d
	orl	%ebp, %r11d
	andl	%r13d, %r14d
	orl	%ebp, %r14d
	je	.LBB0_9
	movl	%edx, 296(%rcx)
.LBB0_9:
	andl	%r10d, %eax
	testl	%r11d, %r11d
	movq	-80(%rsp), %r12
	movl	-44(%rsp), %r14d
	movl	-48(%rsp), %r13d
	movl	%esi, %r11d
	je	.LBB0_11
	movl	%r9d, 288(%rcx)
	movl	%r9d, %r11d
.LBB0_11:
	orl	%edi, %eax
	movl	-52(%rsp), %edi
	testl	%edi, %edi
	je	.LBB0_13
	movl	$1, 280(%rcx)
	movl	$1, %ebx
	testl	%eax, %eax
	je	.LBB0_16
.LBB0_15:
	movl	-112(%rsp), %eax
	movl	%eax, 272(%rcx)
.LBB0_16:
	testl	%edi, %edi
	je	.LBB0_18
	movl	$1, 256(%rcx)
	movl	$1, %r15d
	testl	%r13d, -108(%rsp)
	je	.LBB0_21
.LBB0_20:
	movl	-56(%rsp), %eax
	andl	$1023, %eax
	andl	$1023, %r8d
	addl	%eax, %r8d
	movl	248(%rcx), %eax
	movzbl	%al, %edx
	shrl	$8, %eax
	movl	%r8d, %esi
	shll	$16, %esi
	andl	$16711680, %esi
	cmpl	$255, %r8d
	movl	%edx, 240(%rcx)
	movl	$16711680, %edx
	cmovbl	%esi, %edx
	orl	%eax, %edx
	movl	%edx, 248(%rcx)
.LBB0_21:
	andl	-8(%rsp), %r10d
	testl	%edi, %edi
	je	.LBB0_23
	movl	$0, 232(%rcx)
	xorl	%r9d, %r9d
	jmp	.LBB0_24
.LBB0_13:
	movl	%ebx, 280(%rcx)
	testl	%eax, %eax
	jne	.LBB0_15
	jmp	.LBB0_16
.LBB0_18:
	movl	%r15d, 256(%rcx)
	testl	%r13d, -108(%rsp)
	jne	.LBB0_20
	jmp	.LBB0_21
.LBB0_23:
	xorl	%r9d, %r9d
	movb	-117(%rsp), %al
	movb	%al, %r9b
	movl	%r9d, 232(%rcx)
.LBB0_24:
	movl	-100(%rsp), %edx
	movl	-104(%rsp), %esi
	movq	-72(%rsp), %rbp
	movq	-32(%rsp), %rax
	orl	-116(%rsp), %r10d
	testl	%edi, %edi
	je	.LBB0_26
	movl	$0, 224(%rcx)
	testl	%r13d, -108(%rsp)
	jne	.LBB0_29
	jmp	.LBB0_30
.LBB0_26:
	testl	%r13d, -108(%rsp)
	je	.LBB0_30
	xorl	%edi, %edi
	movl	%r11d, %r8d
	movb	-118(%rsp), %r11b
	movb	%r11b, %dil
	movl	%r8d, %r11d
	leal	1(%rdi,%rax), %eax
	movl	%eax, 224(%rcx)
	testl	%r13d, -108(%rsp)
	je	.LBB0_30
.LBB0_29:
	movl	%esi, 200(%rcx)
	movl	%ebp, 208(%rcx)
	movl	%r14d, 216(%rcx)
	movl	-40(%rsp), %eax
	movl	%eax, 176(%rcx)
	movl	%edx, 184(%rcx)
	movl	-60(%rsp), %esi
	movl	%esi, 192(%rcx)
	movl	-84(%rsp), %eax
	movl	%eax, 152(%rcx)
	movq	-24(%rsp), %rax
	movl	%eax, 160(%rcx)
	movl	-64(%rsp), %eax
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
	movb	%r14b, 8(%rcx,%rax)
	leal	-1(%rax), %eax
	cmpl	$62, %eax
	cmovbl	%eax, %edx
	movl	%edx, 72(%rcx)
.LBB0_30:
	testl	%r10d, %r10d
	je	.LBB0_32
	movl	-96(%rsp), %eax
	movl	%eax, 264(%rcx)
.LBB0_32:
	shrl	$2, %r15d
	notl	%r15d
	andl	$1, %r15d
	movq	40(%r12), %rax
	movl	%r15d, (%rax)
	movq	48(%r12), %rax
	movl	%r11d, (%rax)
	notl	%ebx
	andl	$1, %ebx
	movq	56(%r12), %rax
	movl	%ebx, (%rax)
	movq	64(%r12), %rax
	movl	%r9d, (%rax)
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
