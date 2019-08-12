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
	subq	$176, %rsp
	.cfi_def_cfa_offset 232
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %rsi
	movq	8(%rdi), %rcx
	movl	320(%rcx), %eax
	movl	%eax, 8(%rsp)
	movl	328(%rcx), %eax
	movq	%rax, 16(%rsp)
	movl	468(%rcx), %eax
	movl	%eax, -64(%rsp)
	movl	476(%rcx), %eax
	movl	%eax, -4(%rsp)
	movl	492(%rcx), %eax
	movl	%eax, 4(%rsp)
	movl	500(%rcx), %r10d
	movl	508(%rcx), %eax
	movl	%eax, -104(%rsp)
	movl	516(%rcx), %edx
	movl	%edx, -8(%rsp)
	movl	524(%rcx), %eax
	movl	%eax, -68(%rsp)
	movl	532(%rcx), %eax
	movl	%eax, -108(%rsp)
	movl	608(%rcx), %eax
	movl	%eax, 108(%rsp)
	movq	%rsi, 152(%rsp)
	movq	24(%rsi), %rdx
	movl	(%rdx), %edi
	movl	1112(%rcx), %edx
	notl	%edx
	testl	%edi, %edx
	movl	616(%rcx), %edx
	movslq	632(%rcx), %r12
	movl	640(%rcx), %ebx
	movl	648(%rcx), %eax
	movl	656(%rcx), %esi
	movq	%rsi, 24(%rsp)
	movl	684(%rcx), %ebp
	movl	700(%rcx), %r15d
	movl	708(%rcx), %esi
	movq	%rsi, 32(%rsp)
	movl	752(%rcx), %esi
	movl	%esi, -72(%rsp)
	movl	760(%rcx), %esi
	movl	%esi, -12(%rsp)
	movl	776(%rcx), %r13d
	movl	784(%rcx), %esi
	movl	%esi, -100(%rsp)
	movl	792(%rcx), %esi
	movl	%esi, -96(%rsp)
	movl	800(%rcx), %esi
	movq	%rsi, 128(%rsp)
	movl	808(%rcx), %esi
	movl	%esi, -76(%rsp)
	movl	816(%rcx), %esi
	movl	%esi, -92(%rsp)
	movl	844(%rcx), %esi
	movl	%esi, 104(%rsp)
	movl	852(%rcx), %esi
	movl	%esi, -16(%rsp)
	movslq	868(%rcx), %rsi
	movq	%rsi, 144(%rsp)
	movl	876(%rcx), %esi
	movq	%rsi, 168(%rsp)
	movl	884(%rcx), %esi
	movl	%esi, 100(%rsp)
	movl	892(%rcx), %esi
	movq	%rsi, 40(%rsp)
	movl	920(%rcx), %esi
	movq	%rsi, 120(%rsp)
	movl	936(%rcx), %esi
	movl	%esi, -80(%rsp)
	movl	944(%rcx), %esi
	movq	%rsi, 48(%rsp)
	movl	960(%rcx), %esi
	movl	%esi, -88(%rsp)
	movl	968(%rcx), %esi
	movl	%esi, -20(%rsp)
	movl	984(%rcx), %esi
	movl	%esi, -84(%rsp)
	movl	992(%rcx), %esi
	movl	%esi, -124(%rsp)
	movl	1000(%rcx), %esi
	movl	%esi, -120(%rsp)
	movl	1008(%rcx), %esi
	movl	%esi, -24(%rsp)
	movl	1016(%rcx), %esi
	movl	%esi, 12(%rsp)
	movl	1024(%rcx), %esi
	movl	%esi, -116(%rsp)
	movl	1032(%rcx), %esi
	movl	%esi, 112(%rsp)
	movl	1040(%rcx), %r9d
	movl	1056(%rcx), %r14d
	movl	1064(%rcx), %esi
	movq	%rsi, -56(%rsp)
	movl	1072(%rcx), %r8d
	movl	1080(%rcx), %esi
	movl	%esi, -112(%rsp)
	movl	1088(%rcx), %r11d
	movl	1096(%rcx), %esi
	movl	%esi, 116(%rsp)
	movl	1104(%rcx), %esi
	movl	%edi, 1112(%rcx)
	je	.LBB0_136
	movl	%esi, -60(%rsp)
	movl	%ebp, -44(%rsp)
	movl	%eax, 72(%rsp)
	movq	%rbx, 160(%rsp)
	movl	%edx, -40(%rsp)
	xorl	%eax, %eax
	movl	%r14d, 92(%rsp)
	testl	%r14d, %r14d
	setne	%al
	movq	16(%rsp), %rbp
	movl	%ebp, %edi
	shrl	$16, %edi
	movl	%r15d, %ebx
	movl	%r8d, %r15d
	shrl	$16, %r15d
	movq	%r12, 136(%rsp)
	movl	%r13d, (%rsp)
	movl	%edi, %r13d
	subl	%r15d, %r13d
	movl	%ebp, %esi
	subl	%r8d, %esi
	movzwl	%si, %esi
	shll	$16, %r13d
	orl	%esi, %r13d
	addl	%edi, %r15d
	leal	(%r8,%rbp), %esi
	movzwl	%si, %esi
	shll	$16, %r15d
	orl	%esi, %r15d
	movq	-56(%rsp), %rdx
	movl	%edx, %r12d
	notl	%r12d
	andl	$1, %r12d
	andl	%edx, %eax
	xorl	$1, %eax
	movl	%eax, 88(%rsp)
	andl	%eax, %r9d
	movl	%r11d, 84(%rsp)
	shrl	$2, %r11d
	movl	%r11d, %eax
	xorl	$1, %eax
	movl	%eax, -28(%rsp)
	movl	%r9d, -32(%rsp)
	andl	%r9d, %r11d
	xorl	$1, %r11d
	movl	%r11d, 96(%rsp)
	movl	%r12d, -36(%rsp)
	andl	%r12d, %r11d
	btl	$5, 8(%rsp)
	cmovael	%r8d, %r13d
	movl	%r13d, 80(%rsp)
	cmovael	%ebp, %r15d
	movl	%r15d, 16(%rsp)
	movl	-64(%rsp), %eax
	movl	%eax, %esi
	shrl	$16, %esi
	movl	%eax, %r13d
	shll	$16, %r13d
	negl	%r13d
	orl	%esi, %r13d
	testb	$32, 4(%rsp)
	cmovel	%eax, %r13d
	movl	-108(%rsp), %ebp
	movl	%ebp, %esi
	shrl	$16, %esi
	movl	%r10d, %edx
	shrl	$16, %edx
	movl	%esi, %r15d
	subl	%edx, %r15d
	movl	%ebp, %edi
	subl	%r10d, %edi
	movzwl	%di, %edi
	shll	$16, %r15d
	orl	%edi, %r15d
	addl	%esi, %edx
	addl	%ebp, %r10d
	movzwl	%r10w, %eax
	shll	$16, %edx
	orl	%eax, %edx
	btl	$4, -68(%rsp)
	cmovael	-104(%rsp), %r15d
	cmovael	%ebp, %edx
	movl	%edx, -108(%rsp)
	movq	32(%rsp), %r8
	movl	%r8d, %eax
	shrl	$16, %eax
	movq	24(%rsp), %rbp
	movl	%ebp, %edi
	shrl	$16, %edi
	movl	%eax, %edx
	subl	%edi, %edx
	movl	%r8d, %esi
	subl	%ebp, %esi
	movzwl	%si, %esi
	shll	$16, %edx
	orl	%esi, %edx
	addl	%eax, %edi
	leal	(%r8,%rbp), %eax
	movzwl	%ax, %eax
	shll	$16, %edi
	orl	%eax, %edi
	movl	%ebx, 56(%rsp)
	btl	$3, %ebx
	cmovael	%ebp, %edx
	movl	%edx, 24(%rsp)
	cmovael	%r8d, %edi
	movl	%edi, 32(%rsp)
	movl	%r11d, %r10d
	movl	-72(%rsp), %esi
	movl	%esi, %eax
	shrl	$16, %eax
	movl	%esi, %edx
	shll	$16, %edx
	negl	%edx
	orl	%eax, %edx
	testb	$8, (%rsp)
	cmovel	%esi, %edx
	movl	%edx, 68(%rsp)
	movl	-92(%rsp), %ebx
	movl	%ebx, %eax
	shrl	$16, %eax
	movl	-100(%rsp), %ebp
	movl	%ebp, %edi
	shrl	$16, %edi
	movl	%eax, %esi
	subl	%edi, %esi
	movl	%ebx, %edx
	subl	%ebp, %edx
	movzwl	%dx, %edx
	shll	$16, %esi
	orl	%edx, %esi
	addl	%eax, %edi
	addl	%ebx, %ebp
	movzwl	%bp, %eax
	shll	$16, %edi
	orl	%eax, %edi
	btl	$2, -76(%rsp)
	cmovael	-96(%rsp), %esi
	movl	%esi, -96(%rsp)
	cmovael	%ebx, %edi
	movl	%edi, -92(%rsp)
	movq	48(%rsp), %rdi
	movl	%edi, %eax
	shrl	$16, %eax
	movq	40(%rsp), %rbx
	movl	%ebx, %r9d
	shrl	$16, %r9d
	movl	%eax, %esi
	subl	%r9d, %esi
	movl	%edi, %edx
	subl	%ebx, %edx
	movzwl	%dx, %edx
	shll	$16, %esi
	orl	%edx, %esi
	addl	%eax, %r9d
	leal	(%rdi,%rbx), %eax
	movzwl	%ax, %eax
	shll	$16, %r9d
	orl	%eax, %r9d
	movl	-80(%rsp), %eax
	btl	$1, %eax
	cmovael	%ebx, %esi
	movl	%esi, 64(%rsp)
	cmovael	%edi, %r9d
	movl	-88(%rsp), %esi
	movl	%esi, %eax
	shrl	$16, %eax
	movl	%esi, %edx
	shll	$16, %edx
	negl	%edx
	orl	%eax, %edx
	testb	$2, -84(%rsp)
	cmovel	%esi, %edx
	movl	%edx, 60(%rsp)
	movl	-116(%rsp), %esi
	movl	%esi, %eax
	shrl	$16, %eax
	movl	-124(%rsp), %edi
	movl	%edi, %r11d
	shrl	$16, %r11d
	movl	%eax, %r8d
	subl	%r11d, %r8d
	movl	%esi, %edx
	subl	%edi, %edx
	movzwl	%dx, %edx
	shll	$16, %r8d
	orl	%edx, %r8d
	addl	%eax, %r11d
	addl	%esi, %edi
	movzwl	%di, %eax
	shll	$16, %r11d
	orl	%eax, %r11d
	cmpl	$0, 12(%rsp)
	cmovel	-120(%rsp), %r8d
	cmovel	%esi, %r11d
	movq	-56(%rsp), %rdx
	movl	%edx, %esi
	shrl	$2, %esi
	notl	%esi
	movq	152(%rsp), %rdi
	movq	8(%rdi), %rax
	andl	(%rax), %esi
	movq	32(%rdi), %rax
	movl	(%rax), %r14d
	andl	$1, %esi
	movl	%r10d, %ebx
	xorl	$1, %ebx
	movl	%edx, %r12d
	shrl	%r12d
	testl	%ebx, %esi
	movq	136(%rsp), %rax
	movl	(%rcx,%rax,4), %edx
	movq	144(%rsp), %rax
	movl	256(%rcx,%rax,4), %eax
	movl	%eax, -100(%rsp)
	movq	%rdi, %rax
	movl	%r10d, -116(%rsp)
	movl	%r13d, 76(%rsp)
	movl	%r15d, -104(%rsp)
	movl	%edx, 40(%rsp)
	je	.LBB0_2
	movq	-56(%rsp), %rdx
	leal	(%rdx,%rdx), %edi
	andl	$6, %edi
	movl	%edi, -120(%rsp)
	jmp	.LBB0_4
.LBB0_2:
	movl	%r12d, %ebp
	andl	$3, %ebp
	movl	%esi, %edi
	notl	%edi
	testl	%r10d, %edi
	cmovel	-56(%rsp), %ebp
	movl	%ebp, -120(%rsp)
.LBB0_4:
	movl	-112(%rsp), %r10d
	movl	-28(%rsp), %r15d
	movl	-32(%rsp), %edx
	movl	%r12d, %edi
	andl	$1, %edi
	movq	(%rax), %rbp
	movq	16(%rax), %rax
	movl	(%rbp), %ebp
	orl	%edi, %ebx
	movl	%ebp, 48(%rsp)
	cmovnel	%ebp, %r10d
	andl	%edx, %r15d
	movl	84(%rsp), %edi
	movl	%edi, %ebx
	andl	$1, %ebx
	movl	%ebx, %ebp
	xorl	$1, %ebp
	andl	(%rax), %ebp
	movl	%edi, %eax
	movl	%ebp, %edi
	xorl	$1, %edi
	movl	%eax, %r13d
	shrl	%r13d
	testl	%r15d, %edi
	je	.LBB0_5
	addl	%eax, %eax
	andl	$6, %eax
	movl	%eax, -124(%rsp)
	jmp	.LBB0_7
.LBB0_5:
	movl	%r10d, -112(%rsp)
	movl	%r13d, %edx
	andl	$3, %edx
	movl	%eax, %r10d
	movl	%r15d, %eax
	xorl	$1, %eax
	testl	%eax, %ebp
	cmovel	%r10d, %edx
	movl	%edx, -124(%rsp)
	movl	-112(%rsp), %r10d
.LBB0_7:
	andl	$1, %r13d
	orl	%r13d, %edi
	movl	-60(%rsp), %eax
	movl	112(%rsp), %edi
	cmovnel	%edi, %eax
	movl	%eax, -60(%rsp)
	andl	%r15d, %ebx
	orl	%ebp, %ebx
	andl	%r15d, %r13d
	orl	%ebp, %r13d
	je	.LBB0_9
	movl	%edi, 1104(%rcx)
.LBB0_9:
	andl	%esi, %r12d
	testl	%ebx, %ebx
	movq	152(%rsp), %r13
	movl	116(%rsp), %ebp
	movl	-116(%rsp), %eax
	movq	-56(%rsp), %rdi
	movl	96(%rsp), %ebx
	je	.LBB0_11
	movl	-60(%rsp), %ebp
	movl	%ebp, 1096(%rcx)
.LBB0_11:
	andl	%edi, %esi
	orl	%eax, %r12d
	testl	%r14d, %r14d
	movl	12(%rsp), %r15d
	je	.LBB0_13
	movl	$1, 1088(%rcx)
	movl	$1, -124(%rsp)
	orl	%eax, %esi
	testl	%r12d, %r12d
	je	.LBB0_16
.LBB0_15:
	movl	48(%rsp), %eax
	movl	%eax, 1080(%rcx)
.LBB0_16:
	testl	%esi, %esi
	movq	144(%rsp), %r12
	je	.LBB0_18
	movl	%r10d, 1072(%rcx)
.LBB0_18:
	testl	%r14d, %r14d
	movl	92(%rsp), %edx
	je	.LBB0_20
	movl	$1, 1064(%rcx)
	movl	$1, -120(%rsp)
	andl	88(%rsp), %ebx
	testl	%r14d, %r14d
	je	.LBB0_23
.LBB0_22:
	movl	$0, 1056(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_26
	jmp	.LBB0_27
.LBB0_13:
	movq	%r13, %rdi
	movl	-124(%rsp), %edx
	movl	%edx, 1088(%rcx)
	orl	%eax, %esi
	testl	%r12d, %r12d
	jne	.LBB0_15
	jmp	.LBB0_16
.LBB0_20:
	movl	-120(%rsp), %eax
	movl	%eax, 1064(%rcx)
	andl	88(%rsp), %ebx
	testl	%r14d, %r14d
	jne	.LBB0_22
.LBB0_23:
	testl	%ebx, -36(%rsp)
	je	.LBB0_25
	incl	%edx
	andl	$63, %edx
	movl	%edx, 1056(%rcx)
.LBB0_25:
	testl	%r14d, %r14d
	je	.LBB0_27
.LBB0_26:
	movl	$0, 1040(%rcx)
	movl	$0, 1048(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_30
	jmp	.LBB0_31
.LBB0_27:
	testl	%ebx, %ebx
	je	.LBB0_29
	movl	1048(%rcx), %eax
	movl	%eax, 1040(%rcx)
	movl	-24(%rsp), %eax
	movl	%eax, 1048(%rcx)
.LBB0_29:
	testl	%ebx, %ebx
	je	.LBB0_31
.LBB0_30:
	movl	%r11d, 1032(%rcx)
	movl	%r8d, 1024(%rcx)
.LBB0_31:
	testl	%r14d, %r14d
	je	.LBB0_33
	movl	$0, 1016(%rcx)
	movl	-64(%rsp), %r8d
	movl	-84(%rsp), %eax
	movl	-88(%rsp), %esi
	testl	%r14d, %r14d
	jne	.LBB0_36
	jmp	.LBB0_37
.LBB0_33:
	testl	%ebx, -24(%rsp)
	movl	-64(%rsp), %r8d
	movl	-84(%rsp), %eax
	movl	-88(%rsp), %esi
	je	.LBB0_35
	notl	%r15d
	andl	$1, %r15d
	movl	%r15d, 1016(%rcx)
.LBB0_35:
	testl	%r14d, %r14d
	je	.LBB0_37
.LBB0_36:
	movl	$0, 1008(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_40
	jmp	.LBB0_41
.LBB0_37:
	testl	%ebx, %ebx
	je	.LBB0_41
	movl	-20(%rsp), %edx
	movl	%edx, 1008(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_41
.LBB0_40:
	movl	%esi, 1000(%rcx)
	movl	60(%rsp), %edx
	movl	%edx, 992(%rcx)
.LBB0_41:
	testl	%r14d, %r14d
	je	.LBB0_43
	movl	$0, 984(%rcx)
	movl	-72(%rsp), %r10d
	movl	-76(%rsp), %r15d
	movl	-80(%rsp), %esi
	testl	%r14d, %r14d
	jne	.LBB0_46
	jmp	.LBB0_47
.LBB0_43:
	testl	%ebx, -20(%rsp)
	movl	-72(%rsp), %r10d
	movl	-76(%rsp), %r15d
	movl	-80(%rsp), %esi
	je	.LBB0_45
	incl	%eax
	andl	$3, %eax
	movl	%eax, 984(%rcx)
.LBB0_45:
	testl	%r14d, %r14d
	je	.LBB0_47
.LBB0_46:
	movl	$0, 968(%rcx)
	movl	$0, 976(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_50
	jmp	.LBB0_51
.LBB0_47:
	testl	%ebx, %ebx
	je	.LBB0_51
	movl	976(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 968(%rcx)
	shrl	%eax
	movq	120(%rsp), %rdx
	leal	(%rdx,%rdx), %edx
	orl	%eax, %edx
	movl	%edx, 976(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_51
.LBB0_50:
	movl	%r9d, 960(%rcx)
	movl	952(%rcx), %eax
	movl	%eax, 944(%rcx)
	movl	64(%rsp), %eax
	movl	%eax, 952(%rcx)
.LBB0_51:
	testl	%r14d, %r14d
	je	.LBB0_53
	movl	$0, 936(%rcx)
	movl	-68(%rsp), %r9d
	testl	%r14d, %r14d
	jne	.LBB0_56
	jmp	.LBB0_57
.LBB0_53:
	testl	%ebx, 120(%rsp)
	movl	-68(%rsp), %r9d
	je	.LBB0_55
	incl	%esi
	andl	$3, %esi
	movl	%esi, 936(%rcx)
.LBB0_55:
	testl	%r14d, %r14d
	je	.LBB0_57
.LBB0_56:
	movl	$0, 920(%rcx)
	movl	$0, 928(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_60
	jmp	.LBB0_61
.LBB0_57:
	testl	%ebx, %ebx
	je	.LBB0_61
	movl	928(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 920(%rcx)
	shrl	%eax
	movl	-16(%rsp), %edx
	shll	$4, %edx
	orl	%eax, %edx
	movl	%edx, 928(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_61
.LBB0_60:
	movq	168(%rsp), %r11
	movswl	%r11w, %eax
	movl	100(%rsp), %esi
	movl	%esi, %edx
	sarl	$16, %edx
	sarl	$16, %r11d
	movswl	%si, %esi
	movl	%edx, %edi
	imull	%r11d, %edi
	imull	%esi, %r11d
	imull	%eax, %esi
	subl	%edi, %esi
	imull	%eax, %edx
	addl	%edx, %r11d
	addl	%esi, %esi
	andl	$2147450880, %r11d
	shrl	$16, %esi
	leal	(%rsi,%r11,2), %eax
	movslq	916(%rcx), %rdx
	movl	900(%rcx,%rdx,4), %esi
	movl	%esi, 892(%rcx)
	movl	%eax, 900(%rcx,%rdx,4)
	leal	-1(%rdx), %eax
	cmpl	$3, %eax
	movl	$3, %edx
	cmovbl	%eax, %edx
	movl	%edx, 916(%rcx)
	movl	-100(%rsp), %eax
	movl	%eax, 884(%rcx)
	movl	104(%rsp), %eax
	movl	%eax, 876(%rcx)
.LBB0_61:
	testl	%r14d, %r14d
	je	.LBB0_63
	movl	$0, 868(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_66
	jmp	.LBB0_67
.LBB0_63:
	testl	%ebx, -16(%rsp)
	je	.LBB0_65
	incl	%r12d
	andl	$15, %r12d
	movl	%r12d, 868(%rcx)
.LBB0_65:
	testl	%r14d, %r14d
	je	.LBB0_67
.LBB0_66:
	movl	$0, 852(%rcx)
	movl	$0, 860(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_70
	jmp	.LBB0_71
.LBB0_67:
	testl	%ebx, %ebx
	je	.LBB0_71
	movl	860(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 852(%rcx)
	shrl	%eax
	movq	128(%rsp), %rdx
	leal	(,%rdx,8), %edx
	orl	%eax, %edx
	movl	%edx, 860(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_71
.LBB0_70:
	movl	-92(%rsp), %eax
	movl	%eax, 844(%rcx)
	movslq	840(%rcx), %rax
	movl	824(%rcx,%rax,4), %edx
	movl	%edx, 816(%rcx)
	movl	-96(%rsp), %edx
	movl	%edx, 824(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$2, %eax
	movl	$2, %edx
	cmovbl	%eax, %edx
	movl	%edx, 840(%rcx)
.LBB0_71:
	testl	%r14d, %r14d
	je	.LBB0_73
	movl	$0, 808(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_76
	jmp	.LBB0_77
.LBB0_73:
	testl	%ebx, 128(%rsp)
	je	.LBB0_75
	incl	%r15d
	andl	$7, %r15d
	movl	%r15d, 808(%rcx)
.LBB0_75:
	testl	%r14d, %r14d
	je	.LBB0_77
.LBB0_76:
	movl	$0, 800(%rcx)
	movl	%ebp, %r15d
	testl	%ebx, %ebx
	jne	.LBB0_80
	jmp	.LBB0_81
.LBB0_77:
	testl	%ebx, %ebx
	movl	%ebp, %r15d
	je	.LBB0_81
	movl	-12(%rsp), %eax
	movl	%eax, 800(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_81
.LBB0_80:
	movl	%r10d, 792(%rcx)
	movl	68(%rsp), %eax
	movl	%eax, 784(%rcx)
.LBB0_81:
	testl	%r14d, %r14d
	je	.LBB0_83
	movl	$0, 776(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_86
	jmp	.LBB0_87
.LBB0_83:
	testl	%ebx, -12(%rsp)
	je	.LBB0_85
	movl	(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 776(%rcx)
.LBB0_85:
	testl	%r14d, %r14d
	je	.LBB0_87
.LBB0_86:
	movl	$0, 760(%rcx)
	movl	$0, 768(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_90
	jmp	.LBB0_91
.LBB0_87:
	testl	%ebx, %ebx
	je	.LBB0_91
	movl	768(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 760(%rcx)
	shrl	%eax
	movl	-44(%rsp), %edx
	shll	$7, %edx
	orl	%eax, %edx
	movl	%edx, 768(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_91
.LBB0_90:
	movl	32(%rsp), %eax
	movl	%eax, 752(%rcx)
	movslq	748(%rcx), %rax
	movl	716(%rcx,%rax,4), %edx
	movl	%edx, 708(%rcx)
	movl	24(%rsp), %edx
	movl	%edx, 716(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$6, %eax
	movl	$6, %edx
	cmovbl	%eax, %edx
	movl	%edx, 748(%rcx)
.LBB0_91:
	testl	%r14d, %r14d
	je	.LBB0_93
	movl	$0, 700(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_96
	jmp	.LBB0_97
.LBB0_93:
	testl	%ebx, -44(%rsp)
	je	.LBB0_95
	movl	56(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 700(%rcx)
.LBB0_95:
	testl	%r14d, %r14d
	je	.LBB0_97
.LBB0_96:
	movl	$0, 684(%rcx)
	movl	$0, 692(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_100
	jmp	.LBB0_101
.LBB0_97:
	testl	%ebx, %ebx
	je	.LBB0_101
	movl	692(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 684(%rcx)
	shrl	%eax
	movl	-40(%rsp), %edx
	shll	$4, %edx
	orl	%eax, %edx
	movl	%edx, 692(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_101
.LBB0_100:
	movq	160(%rsp), %rbp
	movswl	%bp, %eax
	movl	72(%rsp), %esi
	movl	%esi, %edx
	sarl	$16, %edx
	sarl	$16, %ebp
	movswl	%si, %esi
	movl	%edx, %edi
	imull	%ebp, %edi
	imull	%esi, %ebp
	imull	%eax, %esi
	subl	%edi, %esi
	imull	%eax, %edx
	addl	%edx, %ebp
	addl	%esi, %esi
	andl	$2147450880, %ebp
	shrl	$16, %esi
	leal	(%rsi,%rbp,2), %eax
	movslq	680(%rcx), %rdx
	movl	664(%rcx,%rdx,4), %esi
	movl	%esi, 656(%rcx)
	movl	%eax, 664(%rcx,%rdx,4)
	leal	-1(%rdx), %eax
	cmpl	$3, %eax
	movl	$3, %edx
	cmovbl	%eax, %edx
	movl	%edx, 680(%rcx)
	movl	40(%rsp), %eax
	movl	%eax, 648(%rcx)
	movl	108(%rsp), %eax
	movl	%eax, 640(%rcx)
.LBB0_101:
	testl	%r14d, %r14d
	je	.LBB0_103
	movl	$0, 632(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_106
	jmp	.LBB0_107
.LBB0_103:
	testl	%ebx, -40(%rsp)
	je	.LBB0_105
	movq	136(%rsp), %rax
	incl	%eax
	andl	$63, %eax
	movl	%eax, 632(%rcx)
.LBB0_105:
	testl	%r14d, %r14d
	je	.LBB0_107
.LBB0_106:
	movl	$0, 616(%rcx)
	movl	$0, 624(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_110
	jmp	.LBB0_111
.LBB0_107:
	testl	%ebx, %ebx
	je	.LBB0_111
	movl	624(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 616(%rcx)
	shrl	%eax
	movl	-8(%rsp), %edx
	shll	$15, %edx
	orl	%eax, %edx
	movl	%edx, 624(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_111
.LBB0_110:
	movl	-108(%rsp), %eax
	movl	%eax, 608(%rcx)
	movslq	604(%rcx), %rax
	movl	540(%rcx,%rax,4), %edx
	movl	%edx, 532(%rcx)
	movl	-104(%rsp), %edx
	movl	%edx, 540(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$14, %eax
	movl	$14, %edx
	cmovbl	%eax, %edx
	movl	%edx, 604(%rcx)
.LBB0_111:
	testl	%r14d, %r14d
	je	.LBB0_113
	movl	$0, 524(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_116
	jmp	.LBB0_117
.LBB0_113:
	testl	%ebx, -8(%rsp)
	je	.LBB0_115
	incl	%r9d
	andl	$31, %r9d
	movl	%r9d, 524(%rcx)
.LBB0_115:
	testl	%r14d, %r14d
	je	.LBB0_117
.LBB0_116:
	movl	$0, 516(%rcx)
	movl	-116(%rsp), %r12d
	testl	%ebx, %ebx
	jne	.LBB0_120
	jmp	.LBB0_121
.LBB0_117:
	testl	%ebx, %ebx
	movl	-116(%rsp), %r12d
	je	.LBB0_121
	movl	-4(%rsp), %eax
	movl	%eax, 516(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_121
.LBB0_120:
	movl	%r8d, 508(%rcx)
	movl	76(%rsp), %eax
	movl	%eax, 500(%rcx)
.LBB0_121:
	testl	%r14d, %r14d
	je	.LBB0_123
	movl	$0, 492(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_126
	jmp	.LBB0_127
.LBB0_123:
	testl	%ebx, -4(%rsp)
	je	.LBB0_125
	movl	4(%rsp), %r11d
	incl	%r11d
	andl	$63, %r11d
	movl	%r11d, 492(%rcx)
.LBB0_125:
	testl	%r14d, %r14d
	je	.LBB0_127
.LBB0_126:
	movl	$0, 476(%rcx)
	movl	$0, 484(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_130
	jmp	.LBB0_131
.LBB0_127:
	testl	%ebx, %ebx
	je	.LBB0_131
	movl	484(%rcx), %eax
	shldl	$31, %eax, %r12d
	andl	$1, %eax
	movl	%eax, 476(%rcx)
	movl	%r12d, 484(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_131
.LBB0_130:
	movl	16(%rsp), %eax
	movl	%eax, 468(%rcx)
	movslq	464(%rcx), %rax
	movl	336(%rcx,%rax,4), %edx
	movl	%edx, 328(%rcx)
	movl	80(%rsp), %edx
	movl	%edx, 336(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$30, %eax
	movl	$30, %edx
	cmovbl	%eax, %edx
	movl	%edx, 464(%rcx)
.LBB0_131:
	testl	%r14d, %r14d
	je	.LBB0_133
	movl	$0, 320(%rcx)
	jmp	.LBB0_135
.LBB0_133:
	testl	%ebx, -36(%rsp)
	je	.LBB0_135
	movl	8(%rsp), %eax
	incl	%eax
	andl	$63, %eax
	movl	%eax, 320(%rcx)
.LBB0_135:
	movl	-120(%rsp), %ecx
	shrl	$2, %ecx
	notl	%ecx
	andl	$1, %ecx
	movq	40(%r13), %rax
	movl	%ecx, (%rax)
	movq	48(%r13), %rax
	movl	%r15d, (%rax)
	movl	-124(%rsp), %ecx
	notl	%ecx
	andl	$1, %ecx
	movq	56(%r13), %rax
	movl	%ecx, (%rax)
.LBB0_136:
	xorl	%eax, %eax
	addq	$176, %rsp
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
