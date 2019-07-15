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
	movl	(%rcx), %r11d
	movl	76(%rcx), %r14d
	movl	152(%rcx), %r8d
	movl	160(%rcx), %eax
	movl	%eax, -92(%rsp)
	movl	168(%rcx), %eax
	movq	%rax, -16(%rsp)
	movl	176(%rcx), %eax
	movl	%eax, -88(%rsp)
	movl	184(%rcx), %r12d
	movl	192(%rcx), %r15d
	movl	200(%rcx), %r13d
	movl	208(%rcx), %eax
	movl	%eax, -96(%rsp)
	movl	216(%rcx), %r10d
	movq	%rdx, -80(%rsp)
	movq	24(%rdx), %rdx
	movl	(%rdx), %esi
	movl	304(%rcx), %edx
	notl	%edx
	testl	%esi, %edx
	movl	224(%rcx), %r9d
	movl	232(%rcx), %edx
	movl	240(%rcx), %eax
	movl	%eax, -24(%rsp)
	movl	256(%rcx), %ebx
	movl	264(%rcx), %eax
	movl	%eax, -20(%rsp)
	movl	272(%rcx), %ebp
	movl	280(%rcx), %edi
	movl	288(%rcx), %eax
	movl	%eax, -28(%rsp)
	movl	296(%rcx), %eax
	movl	%esi, 304(%rcx)
	je	.LBB0_24
	movl	%ebp, -40(%rsp)
	movl	%eax, -32(%rsp)
	movl	%r12d, -56(%rsp)
	movl	%r14d, -52(%rsp)
	movl	%r11d, -48(%rsp)
	xorl	%ebp, %ebp
	cmpl	$4096, %r9d
	setb	%bpl
	movl	%ebx, %r11d
	notl	%r11d
	andl	%ebx, %ebp
	xorl	$1, %ebp
	cmpl	$134, %r9d
	seta	%al
	testl	%edx, %edx
	sete	%dl
	andb	%al, %dl
	movzbl	%dl, %eax
	andl	%ebp, %eax
	movl	%r15d, %edx
	movq	%rdi, -8(%rsp)
	movl	%edi, %r12d
	shrl	$2, %r12d
	andl	$1, %r12d
	movl	%r12d, %r15d
	xorl	$1, %r15d
	movl	%eax, -44(%rsp)
	andl	%eax, %r12d
	xorl	$1, %r12d
	andl	%r12d, %r11d
	movl	%r12d, %eax
	movl	%ebp, -104(%rsp)
	andl	%ebp, %eax
	xorl	%ebp, %ebp
	cmpl	$-3, %r9d
	seta	%bpl
	incl	%ebp
	testl	%eax, %eax
	cmovel	%eax, %ebp
	movl	%ebp, -68(%rsp)
	movq	-80(%rsp), %rbp
	movq	8(%rbp), %r14
	movl	%r9d, -100(%rsp)
	cmpl	$4099, %r9d
	seta	-109(%rsp)
	movq	-16(%rsp), %rdi
	leal	(%r10,%rdi), %eax
	andl	$511, %eax
	movl	%edx, -60(%rsp)
	movzbl	%dl, %edx
	leal	(%rax,%rdx,2), %esi
	leal	(%r13,%r8), %eax
	andl	$511, %eax
	movzbl	-88(%rsp), %edx
	leal	(%rax,%rdx,2), %eax
	movl	%eax, %edx
	subl	%esi, %edx
	subl	%eax, %esi
	movq	32(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -108(%rsp)
	cmovbel	%edx, %esi
	movl	%esi, -64(%rsp)
	movq	%r10, -88(%rsp)
	addl	%r10d, %r13d
	andl	$511, %r13d
	movl	-96(%rsp), %eax
	movzbl	%al, %eax
	leal	(%r13,%rax,2), %r13d
	addl	%edi, %r8d
	andl	$511, %r8d
	movzbl	-92(%rsp), %eax
	leal	(%r8,%rax,2), %eax
	movl	%eax, %edx
	subl	%r13d, %edx
	subl	%eax, %r13d
	cmovbel	%edx, %r13d
	movl	%ebx, %r9d
	shrl	$2, %r9d
	notl	%r9d
	andl	(%r14), %r9d
	andl	$1, %r9d
	movl	%r11d, %edx
	xorl	$1, %edx
	movl	%ebx, %r10d
	shrl	%r10d
	testl	%edx, %r9d
	je	.LBB0_2
	leal	(%rbx,%rbx), %r8d
	andl	$6, %r8d
	jmp	.LBB0_4
.LBB0_2:
	movl	%r10d, %r8d
	andl	$3, %r8d
	movl	%r9d, %eax
	notl	%eax
	testl	%r11d, %eax
	cmovel	%ebx, %r8d
.LBB0_4:
	andl	%r9d, %ebx
	andl	%r10d, %r9d
	andl	$1, %r10d
	movq	-80(%rsp), %rbp
	movq	(%rbp), %rax
	movq	16(%rbp), %rdi
	movl	(%rax), %r14d
	orl	%r10d, %edx
	movl	%r14d, %eax
	movl	-40(%rsp), %edx
	cmovel	%edx, %eax
	orl	%r11d, %ebx
	movl	-20(%rsp), %r10d
	cmovel	%r10d, %eax
	movl	%eax, -36(%rsp)
	orl	%r11d, %r9d
	cmovel	%edx, %r14d
	andl	-44(%rsp), %r15d
	movq	-8(%rsp), %rsi
	movl	%esi, %edx
	notl	%edx
	andl	(%rdi), %edx
	andl	$1, %edx
	movl	%edx, %ebx
	xorl	$1, %ebx
	movl	%esi, %eax
	shrl	%eax
	testl	%r15d, %ebx
	je	.LBB0_5
	leal	(%rsi,%rsi), %r11d
	andl	$6, %r11d
	jmp	.LBB0_7
.LBB0_5:
	movl	%eax, %r11d
	andl	$3, %r11d
	movl	%r15d, %ebp
	xorl	$1, %ebp
	testl	%ebp, %edx
	cmovel	%esi, %r11d
.LBB0_7:
	movl	-108(%rsp), %r9d
	andl	%r15d, %esi
	andl	%eax, %r15d
	andl	$1, %eax
	orl	%eax, %ebx
	movl	-24(%rsp), %eax
	movl	%eax, %ebx
	movl	-32(%rsp), %ebp
	cmovel	%ebp, %ebx
	orl	%edx, %esi
	cmovel	-28(%rsp), %ebx
	orl	%edx, %r15d
	cmovel	%ebp, %eax
	movl	%eax, 296(%rcx)
	movl	%ebx, 288(%rcx)
	testl	%r9d, %r9d
	movq	-16(%rsp), %r15
	je	.LBB0_9
	movl	$1, 280(%rcx)
	movl	$1, %r11d
	testl	%r9d, %r9d
	movl	%r14d, 272(%rcx)
	je	.LBB0_12
.LBB0_11:
	movl	$1, 256(%rcx)
	movl	$1, %r8d
	movl	-100(%rsp), %r14d
	movl	-104(%rsp), %ebp
	testl	%ebp, %r12d
	je	.LBB0_15
.LBB0_14:
	movl	-64(%rsp), %eax
	andl	$1023, %eax
	andl	$1023, %r13d
	addl	%eax, %r13d
	movl	248(%rcx), %eax
	movzbl	%al, %edx
	shrl	$8, %eax
	movl	%r13d, %esi
	shll	$16, %esi
	andl	$16711680, %esi
	cmpl	$255, %r13d
	movl	%edx, 240(%rcx)
	movl	$16711680, %edx
	cmovbl	%esi, %edx
	orl	%eax, %edx
	movl	%edx, 248(%rcx)
.LBB0_15:
	testl	%r9d, %r9d
	je	.LBB0_17
	movl	$0, 232(%rcx)
	xorl	%edi, %edi
	movq	-88(%rsp), %rdx
	testl	%r9d, %r9d
	je	.LBB0_20
.LBB0_19:
	movl	$0, 224(%rcx)
	testl	%ebp, %r12d
	je	.LBB0_23
.LBB0_22:
	movl	-96(%rsp), %eax
	movl	%eax, 200(%rcx)
	movl	%edx, 208(%rcx)
	movl	%r10d, 216(%rcx)
	movl	-56(%rsp), %eax
	movl	%eax, 176(%rcx)
	movl	-60(%rsp), %eax
	movl	%eax, 184(%rcx)
	movl	-48(%rsp), %esi
	movl	%esi, 192(%rcx)
	movl	-92(%rsp), %eax
	movl	%eax, 152(%rcx)
	movl	%r15d, 160(%rcx)
	movl	-52(%rsp), %eax
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
	movb	%r10b, 8(%rcx,%rax)
	leal	-1(%rax), %eax
	cmpl	$62, %eax
	cmovbl	%eax, %edx
	movl	%edx, 72(%rcx)
.LBB0_23:
	movl	-36(%rsp), %eax
	movl	%eax, 264(%rcx)
	shrl	$2, %r8d
	notl	%r8d
	andl	$1, %r8d
	movq	-80(%rsp), %rcx
	movq	40(%rcx), %rax
	movl	%r8d, (%rax)
	movq	48(%rcx), %rax
	movl	%ebx, (%rax)
	notl	%r11d
	andl	$1, %r11d
	movq	56(%rcx), %rax
	movl	%r11d, (%rax)
	movq	64(%rcx), %rax
	movl	%edi, (%rax)
.LBB0_24:
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
.LBB0_9:
	.cfi_def_cfa_offset 56
	movl	%r11d, 280(%rcx)
	testl	%r9d, %r9d
	movl	%r14d, 272(%rcx)
	jne	.LBB0_11
.LBB0_12:
	movl	%r8d, 256(%rcx)
	movl	-100(%rsp), %r14d
	movl	-104(%rsp), %ebp
	testl	%ebp, %r12d
	jne	.LBB0_14
	jmp	.LBB0_15
.LBB0_17:
	xorl	%edi, %edi
	movb	-109(%rsp), %al
	movb	%al, %dil
	movl	%edi, 232(%rcx)
	movq	-88(%rsp), %rdx
	testl	%r9d, %r9d
	jne	.LBB0_19
.LBB0_20:
	movl	-68(%rsp), %eax
	addl	%r14d, %eax
	movl	%eax, 224(%rcx)
	testl	%ebp, %r12d
	jne	.LBB0_22
	jmp	.LBB0_23
.Lfunc_end0:
	.size	eval, .Lfunc_end0-eval
	.cfi_endproc


	.section	".note.GNU-stack","",@progbits
