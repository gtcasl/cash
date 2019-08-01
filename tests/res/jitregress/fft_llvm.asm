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
	subq	$168, %rsp
	.cfi_def_cfa_offset 224
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %rsi
	movq	8(%rdi), %rcx
	movl	320(%rcx), %eax
	movl	%eax, -68(%rsp)
	movl	328(%rcx), %r15d
	movl	468(%rcx), %r11d
	movl	476(%rcx), %eax
	movl	%eax, -20(%rsp)
	movl	492(%rcx), %eax
	movl	%eax, 4(%rsp)
	movl	500(%rcx), %eax
	movl	508(%rcx), %edx
	movl	%edx, -96(%rsp)
	movl	516(%rcx), %edx
	movl	%edx, -24(%rsp)
	movl	524(%rcx), %edx
	movl	%edx, (%rsp)
	movl	532(%rcx), %edx
	movl	%edx, -100(%rsp)
	movl	608(%rcx), %r14d
	movq	%rsi, 16(%rsp)
	movq	24(%rsi), %rdx
	movl	(%rdx), %edx
	movl	1112(%rcx), %esi
	notl	%esi
	testl	%edx, %esi
	movl	616(%rcx), %esi
	movl	%esi, -28(%rsp)
	movslq	632(%rcx), %rsi
	movq	%rsi, 136(%rsp)
	movl	640(%rcx), %esi
	movq	%rsi, 160(%rsp)
	movl	648(%rcx), %esi
	movl	%esi, 96(%rsp)
	movl	656(%rcx), %r8d
	movl	684(%rcx), %esi
	movl	%esi, -32(%rsp)
	movl	700(%rcx), %esi
	movl	%esi, -4(%rsp)
	movl	708(%rcx), %esi
	movq	%rsi, 24(%rsp)
	movl	752(%rcx), %esi
	movl	%esi, 8(%rsp)
	movl	760(%rcx), %esi
	movl	%esi, -36(%rsp)
	movl	776(%rcx), %esi
	movl	%esi, -8(%rsp)
	movl	784(%rcx), %esi
	movl	%esi, -92(%rsp)
	movl	792(%rcx), %esi
	movl	%esi, -88(%rsp)
	movl	800(%rcx), %esi
	movq	%rsi, 120(%rsp)
	movl	808(%rcx), %esi
	movl	%esi, -12(%rsp)
	movl	816(%rcx), %esi
	movl	%esi, -84(%rsp)
	movl	844(%rcx), %esi
	movl	%esi, 92(%rsp)
	movl	852(%rcx), %esi
	movl	%esi, -40(%rsp)
	movslq	868(%rcx), %rsi
	movq	%rsi, 128(%rsp)
	movl	876(%rcx), %esi
	movq	%rsi, 152(%rsp)
	movl	884(%rcx), %esi
	movl	892(%rcx), %edi
	movq	%rdi, 32(%rsp)
	movl	920(%rcx), %ebx
	movq	%rbx, 112(%rsp)
	movl	936(%rcx), %edi
	movl	%edi, -72(%rsp)
	movl	944(%rcx), %edi
	movq	%rdi, 40(%rsp)
	movl	960(%rcx), %edi
	movl	%edi, -76(%rsp)
	movl	968(%rcx), %ebx
	movl	%ebx, -44(%rsp)
	movl	984(%rcx), %ebx
	movl	992(%rcx), %edi
	movl	%edi, -80(%rsp)
	movl	1000(%rcx), %edi
	movl	%edi, -124(%rsp)
	movl	1008(%rcx), %edi
	movl	%edi, -48(%rsp)
	movl	1016(%rcx), %edi
	movl	%edi, 12(%rsp)
	movl	1024(%rcx), %edi
	movl	%edi, -120(%rsp)
	movl	1032(%rcx), %edi
	movl	%edi, 100(%rsp)
	movl	1040(%rcx), %r13d
	movl	1056(%rcx), %edi
	movl	1064(%rcx), %ebp
	movq	%rbp, -112(%rsp)
	movl	1072(%rcx), %r9d
	movl	1080(%rcx), %ebp
	movl	%ebp, -116(%rsp)
	movl	1088(%rcx), %r10d
	movl	1096(%rcx), %r12d
	movl	%r12d, 108(%rsp)
	movl	1104(%rcx), %ebp
	movl	%ebp, 104(%rsp)
	movl	%edx, 1112(%rcx)
	je	.LBB0_136
	movl	%esi, 52(%rsp)
	movl	%r14d, 68(%rsp)
	xorl	%ebp, %ebp
	movl	%edi, 80(%rsp)
	testl	%edi, %edi
	setne	%bpl
	movl	%r15d, %edx
	shrl	$16, %edx
	movl	%r9d, %esi
	shrl	$16, %esi
	movl	%edx, %edi
	subl	%esi, %edi
	movl	%ebx, -16(%rsp)
	movl	%r15d, %ebx
	subl	%r9d, %ebx
	movzwl	%bx, %ebx
	shll	$16, %edi
	orl	%ebx, %edi
	addl	%edx, %esi
	leal	(%r9,%r15), %edx
	movzwl	%dx, %edx
	shll	$16, %esi
	orl	%edx, %esi
	movq	-112(%rsp), %rdx
	movl	%edx, %ebx
	notl	%ebx
	andl	$1, %ebx
	andl	%edx, %ebp
	xorl	$1, %ebp
	movl	%ebp, -60(%rsp)
	andl	%ebp, %r13d
	movq	%r10, 144(%rsp)
	movl	%r10d, %edx
	shrl	$2, %edx
	andl	$1, %edx
	movl	%edx, %r12d
	xorl	$1, %r12d
	movl	%r13d, -52(%rsp)
	andl	%r13d, %edx
	xorl	$1, %edx
	movl	%edx, 88(%rsp)
	movl	%edx, %r13d
	movl	%ebx, -64(%rsp)
	andl	%ebx, %r13d
	btl	$5, -68(%rsp)
	cmovael	%r9d, %edi
	movl	%edi, 76(%rsp)
	cmovael	%r15d, %esi
	movl	%esi, 72(%rsp)
	movl	%r11d, %ebp
	shrl	$16, %ebp
	movl	%r11d, %edx
	shll	$16, %edx
	negl	%edx
	orl	%ebp, %edx
	testb	$32, 4(%rsp)
	movl	%r11d, -56(%rsp)
	cmovel	%r11d, %edx
	movl	%edx, 64(%rsp)
	movl	-100(%rsp), %edi
	movl	%edi, %ebp
	shrl	$16, %ebp
	movl	%eax, %esi
	shrl	$16, %esi
	movl	%ebp, %edx
	subl	%esi, %edx
	movl	%edi, %ebx
	subl	%eax, %ebx
	movzwl	%bx, %ebx
	shll	$16, %edx
	orl	%ebx, %edx
	addl	%ebp, %esi
	addl	%edi, %eax
	movzwl	%ax, %eax
	shll	$16, %esi
	orl	%eax, %esi
	movl	(%rsp), %eax
	btl	$4, %eax
	cmovael	-96(%rsp), %edx
	movl	%edx, -96(%rsp)
	cmovael	%edi, %esi
	movl	%esi, -100(%rsp)
	movq	24(%rsp), %rdi
	movl	%edi, %eax
	shrl	$16, %eax
	movl	%r8d, %esi
	shrl	$16, %esi
	movl	%eax, %edx
	subl	%esi, %edx
	movl	%edi, %ebp
	subl	%r8d, %ebp
	movzwl	%bp, %ebp
	shll	$16, %edx
	orl	%ebp, %edx
	addl	%eax, %esi
	leal	(%rdi,%r8), %eax
	movzwl	%ax, %eax
	shll	$16, %esi
	orl	%eax, %esi
	movl	-4(%rsp), %eax
	btl	$3, %eax
	cmovael	%r8d, %edx
	movl	%edx, 60(%rsp)
	cmovael	%edi, %esi
	movl	%esi, 24(%rsp)
	movl	8(%rsp), %esi
	movl	%esi, %eax
	shrl	$16, %eax
	movl	%esi, %edx
	shll	$16, %edx
	negl	%edx
	orl	%eax, %edx
	movl	-8(%rsp), %eax
	testb	$8, %al
	cmovel	%esi, %edx
	movl	%edx, 56(%rsp)
	movl	-84(%rsp), %ebp
	movl	%ebp, %eax
	shrl	$16, %eax
	movl	-92(%rsp), %ebx
	movl	%ebx, %edi
	shrl	$16, %edi
	movl	%eax, %edx
	subl	%edi, %edx
	movl	%ebp, %esi
	subl	%ebx, %esi
	movzwl	%si, %esi
	shll	$16, %edx
	orl	%esi, %edx
	addl	%eax, %edi
	addl	%ebp, %ebx
	movzwl	%bx, %eax
	shll	$16, %edi
	orl	%eax, %edi
	movl	-12(%rsp), %eax
	btl	$2, %eax
	cmovael	-88(%rsp), %edx
	movl	%edx, -88(%rsp)
	cmovael	%ebp, %edi
	movl	%edi, -84(%rsp)
	movq	40(%rsp), %rdi
	movl	%edi, %eax
	shrl	$16, %eax
	movq	32(%rsp), %rbp
	movl	%ebp, %r10d
	shrl	$16, %r10d
	movl	%eax, %edx
	subl	%r10d, %edx
	movl	%edi, %esi
	subl	%ebp, %esi
	movzwl	%si, %esi
	shll	$16, %edx
	orl	%esi, %edx
	addl	%eax, %r10d
	leal	(%rdi,%rbp), %eax
	movzwl	%ax, %eax
	shll	$16, %r10d
	orl	%eax, %r10d
	btl	$1, -72(%rsp)
	cmovael	%ebp, %edx
	movl	%edx, -92(%rsp)
	cmovael	%edi, %r10d
	movl	-76(%rsp), %edx
	movl	%edx, %eax
	shrl	$16, %eax
	movl	%edx, %ebx
	shll	$16, %ebx
	negl	%ebx
	orl	%eax, %ebx
	testb	$2, -16(%rsp)
	cmovel	%edx, %ebx
	movl	-120(%rsp), %edx
	movl	%edx, %eax
	shrl	$16, %eax
	movl	-80(%rsp), %edi
	movl	%edi, %r11d
	shrl	$16, %r11d
	movl	%eax, %r8d
	subl	%r11d, %r8d
	movl	%edx, %esi
	subl	%edi, %esi
	movzwl	%si, %esi
	shll	$16, %r8d
	orl	%esi, %r8d
	addl	%eax, %r11d
	addl	%edx, %edi
	movzwl	%di, %eax
	shll	$16, %r11d
	orl	%eax, %r11d
	cmpl	$0, 12(%rsp)
	cmovel	-124(%rsp), %r8d
	cmovel	%edx, %r11d
	movq	-112(%rsp), %rsi
	movl	%esi, %r9d
	shrl	$2, %r9d
	notl	%r9d
	movq	16(%rsp), %rdx
	movq	8(%rdx), %rax
	andl	(%rax), %r9d
	movq	32(%rdx), %rax
	movl	(%rax), %eax
	movl	%eax, -120(%rsp)
	andl	$1, %r9d
	movl	%r13d, %ebp
	xorl	$1, %ebp
	movl	%esi, %r14d
	shrl	%r14d
	testl	%ebp, %r9d
	movq	136(%rsp), %rax
	movl	(%rcx,%rax,4), %eax
	movl	%eax, 40(%rsp)
	movq	128(%rsp), %rax
	movl	256(%rcx,%rax,4), %eax
	movl	%eax, 32(%rsp)
	movl	%r13d, 84(%rsp)
	movl	%ebx, 48(%rsp)
	je	.LBB0_2
	movq	-112(%rsp), %rax
	movq	%rax, %rdx
	leal	(%rax,%rax), %eax
	andl	$6, %eax
	jmp	.LBB0_4
.LBB0_2:
	movl	%r14d, %eax
	andl	$3, %eax
	movl	%r9d, %ebx
	notl	%ebx
	testl	%r13d, %ebx
	movq	-112(%rsp), %rsi
	movq	%rsi, %rdx
	cmovel	%esi, %eax
.LBB0_4:
	movl	%eax, -124(%rsp)
	movl	-116(%rsp), %esi
	movl	-52(%rsp), %r15d
	movl	%r14d, %ebx
	andl	$1, %ebx
	movq	16(%rsp), %rdi
	movq	(%rdi), %rax
	movq	16(%rdi), %rdi
	movl	(%rax), %eax
	orl	%ebx, %ebp
	movl	%eax, -80(%rsp)
	cmovnel	%eax, %esi
	movl	%esi, -116(%rsp)
	andl	%r15d, %r12d
	movq	144(%rsp), %rbx
	movl	%ebx, %ebp
	notl	%ebp
	andl	(%rdi), %ebp
	andl	$1, %ebp
	movl	%ebp, %r15d
	xorl	$1, %r15d
	movl	%ebx, %r13d
	shrl	%r13d
	testl	%r12d, %r15d
	je	.LBB0_5
	leal	(%rbx,%rbx), %edi
	andl	$6, %edi
	jmp	.LBB0_7
.LBB0_5:
	movl	%r13d, %edi
	andl	$3, %edi
	movl	%r12d, %eax
	xorl	$1, %eax
	testl	%eax, %ebp
	cmovel	%ebx, %edi
.LBB0_7:
	movl	%r13d, %eax
	andl	$1, %eax
	orl	%eax, %r15d
	movl	104(%rsp), %eax
	movl	100(%rsp), %esi
	cmovnel	%esi, %eax
	andl	%r12d, %ebx
	orl	%ebp, %ebx
	andl	%r13d, %r12d
	orl	%ebp, %r12d
	je	.LBB0_9
	movl	%esi, 1104(%rcx)
.LBB0_9:
	andl	%r9d, %r14d
	testl	%ebx, %ebx
	movl	108(%rsp), %r15d
	movl	84(%rsp), %r12d
	movl	-124(%rsp), %r13d
	movl	-120(%rsp), %ebp
	je	.LBB0_11
	movl	%eax, 1096(%rcx)
	movl	%eax, %r15d
.LBB0_11:
	andl	%edx, %r9d
	orl	%r12d, %r14d
	testl	%ebp, %ebp
	je	.LBB0_13
	movl	$1, 1088(%rcx)
	movl	$1, %edi
	movl	-60(%rsp), %edx
	orl	%r12d, %r9d
	testl	%r14d, %r14d
	je	.LBB0_16
.LBB0_15:
	movl	-80(%rsp), %eax
	movl	%eax, 1080(%rcx)
.LBB0_16:
	movl	%edi, -112(%rsp)
	testl	%r9d, %r9d
	je	.LBB0_18
	movl	-116(%rsp), %eax
	movl	%eax, 1072(%rcx)
.LBB0_18:
	testl	%ebp, %ebp
	movl	88(%rsp), %r14d
	movl	12(%rsp), %esi
	movl	80(%rsp), %eax
	je	.LBB0_20
	movl	$1, 1064(%rcx)
	movl	$1, %r13d
	andl	%edx, %r14d
	testl	%ebp, %ebp
	je	.LBB0_23
.LBB0_22:
	movl	$0, 1056(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_26
	jmp	.LBB0_27
.LBB0_13:
	movl	%edi, 1088(%rcx)
	movl	-60(%rsp), %edx
	orl	%r12d, %r9d
	testl	%r14d, %r14d
	jne	.LBB0_15
	jmp	.LBB0_16
.LBB0_20:
	movl	%r13d, 1064(%rcx)
	andl	%edx, %r14d
	testl	%ebp, %ebp
	jne	.LBB0_22
.LBB0_23:
	testl	%r14d, -64(%rsp)
	je	.LBB0_25
	incl	%eax
	andl	$63, %eax
	movl	%eax, 1056(%rcx)
.LBB0_25:
	testl	%ebp, %ebp
	je	.LBB0_27
.LBB0_26:
	movl	$0, 1040(%rcx)
	movl	$0, 1048(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_30
	jmp	.LBB0_31
.LBB0_27:
	testl	%r14d, %r14d
	je	.LBB0_29
	movl	1048(%rcx), %eax
	movl	%eax, 1040(%rcx)
	movl	-48(%rsp), %eax
	movl	%eax, 1048(%rcx)
.LBB0_29:
	testl	%r14d, %r14d
	je	.LBB0_31
.LBB0_30:
	movl	%r11d, 1032(%rcx)
	movl	%r8d, 1024(%rcx)
.LBB0_31:
	testl	%ebp, %ebp
	je	.LBB0_33
	movl	$0, 1016(%rcx)
	movl	-56(%rsp), %r8d
	movl	-72(%rsp), %edi
	movl	-76(%rsp), %ebx
	testl	%ebp, %ebp
	jne	.LBB0_36
	jmp	.LBB0_37
.LBB0_33:
	testl	%r14d, -48(%rsp)
	movl	-56(%rsp), %r8d
	movl	-72(%rsp), %edi
	movl	-76(%rsp), %ebx
	je	.LBB0_35
	notl	%esi
	andl	$1, %esi
	movl	%esi, 1016(%rcx)
.LBB0_35:
	testl	%ebp, %ebp
	je	.LBB0_37
.LBB0_36:
	movl	$0, 1008(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_40
	jmp	.LBB0_41
.LBB0_37:
	testl	%r14d, %r14d
	je	.LBB0_41
	movl	-44(%rsp), %eax
	movl	%eax, 1008(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_41
.LBB0_40:
	movl	%ebx, 1000(%rcx)
	movl	48(%rsp), %eax
	movl	%eax, 992(%rcx)
.LBB0_41:
	testl	%ebp, %ebp
	je	.LBB0_43
	movl	$0, 984(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_46
	jmp	.LBB0_47
.LBB0_43:
	testl	%r14d, -44(%rsp)
	je	.LBB0_45
	movl	-16(%rsp), %eax
	incl	%eax
	andl	$3, %eax
	movl	%eax, 984(%rcx)
.LBB0_45:
	testl	%ebp, %ebp
	je	.LBB0_47
.LBB0_46:
	movl	$0, 968(%rcx)
	movl	$0, 976(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_50
	jmp	.LBB0_51
.LBB0_47:
	testl	%r14d, %r14d
	je	.LBB0_51
	movl	976(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 968(%rcx)
	shrl	%eax
	movq	112(%rsp), %rdx
	leal	(%rdx,%rdx), %edx
	orl	%eax, %edx
	movl	%edx, 976(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_51
.LBB0_50:
	movl	%r10d, 960(%rcx)
	movl	952(%rcx), %eax
	movl	%eax, 944(%rcx)
	movl	-92(%rsp), %eax
	movl	%eax, 952(%rcx)
.LBB0_51:
	testl	%ebp, %ebp
	je	.LBB0_53
	movl	$0, 936(%rcx)
	movl	-68(%rsp), %r9d
	testl	%ebp, %ebp
	jne	.LBB0_56
	jmp	.LBB0_57
.LBB0_53:
	testl	%r14d, 112(%rsp)
	movl	-68(%rsp), %r9d
	je	.LBB0_55
	incl	%edi
	andl	$3, %edi
	movl	%edi, 936(%rcx)
.LBB0_55:
	testl	%ebp, %ebp
	je	.LBB0_57
.LBB0_56:
	movl	$0, 920(%rcx)
	movl	$0, 928(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_60
	jmp	.LBB0_61
.LBB0_57:
	testl	%r14d, %r14d
	je	.LBB0_61
	movl	928(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 920(%rcx)
	shrl	%eax
	movl	-40(%rsp), %edx
	shll	$4, %edx
	orl	%eax, %edx
	movl	%edx, 928(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_61
.LBB0_60:
	movq	152(%rsp), %rbx
	movswl	%bx, %eax
	movl	52(%rsp), %esi
	movl	%esi, %edx
	sarl	$16, %edx
	sarl	$16, %ebx
	movswl	%si, %esi
	movl	%edx, %edi
	imull	%ebx, %edi
	imull	%esi, %ebx
	imull	%eax, %esi
	subl	%edi, %esi
	imull	%eax, %edx
	addl	%edx, %ebx
	addl	%esi, %esi
	andl	$2147450880, %ebx
	shrl	$16, %esi
	leal	(%rsi,%rbx,2), %eax
	movslq	916(%rcx), %rdx
	movl	900(%rcx,%rdx,4), %esi
	movl	%esi, 892(%rcx)
	movl	%eax, 900(%rcx,%rdx,4)
	leal	-1(%rdx), %eax
	cmpl	$3, %eax
	movl	$3, %edx
	cmovbl	%eax, %edx
	movl	%edx, 916(%rcx)
	movl	32(%rsp), %eax
	movl	%eax, 884(%rcx)
	movl	92(%rsp), %eax
	movl	%eax, 876(%rcx)
.LBB0_61:
	testl	%ebp, %ebp
	je	.LBB0_63
	movl	$0, 868(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_66
	jmp	.LBB0_67
.LBB0_63:
	testl	%r14d, -40(%rsp)
	je	.LBB0_65
	movq	128(%rsp), %rax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 868(%rcx)
.LBB0_65:
	testl	%ebp, %ebp
	je	.LBB0_67
.LBB0_66:
	movl	$0, 852(%rcx)
	movl	$0, 860(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_70
	jmp	.LBB0_71
.LBB0_67:
	testl	%r14d, %r14d
	je	.LBB0_71
	movl	860(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 852(%rcx)
	shrl	%eax
	movq	120(%rsp), %rdx
	leal	(,%rdx,8), %edx
	orl	%eax, %edx
	movl	%edx, 860(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_71
.LBB0_70:
	movl	-84(%rsp), %eax
	movl	%eax, 844(%rcx)
	movslq	840(%rcx), %rax
	movl	824(%rcx,%rax,4), %edx
	movl	%edx, 816(%rcx)
	movl	-88(%rsp), %edx
	movl	%edx, 824(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$2, %eax
	movl	$2, %edx
	cmovbl	%eax, %edx
	movl	%edx, 840(%rcx)
.LBB0_71:
	testl	%ebp, %ebp
	je	.LBB0_73
	movl	$0, 808(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_76
	jmp	.LBB0_77
.LBB0_73:
	testl	%r14d, 120(%rsp)
	je	.LBB0_75
	movl	-12(%rsp), %eax
	incl	%eax
	andl	$7, %eax
	movl	%eax, 808(%rcx)
.LBB0_75:
	testl	%ebp, %ebp
	je	.LBB0_77
.LBB0_76:
	movl	$0, 800(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_80
	jmp	.LBB0_81
.LBB0_77:
	testl	%r14d, %r14d
	je	.LBB0_81
	movl	-36(%rsp), %eax
	movl	%eax, 800(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_81
.LBB0_80:
	movl	8(%rsp), %eax
	movl	%eax, 792(%rcx)
	movl	56(%rsp), %eax
	movl	%eax, 784(%rcx)
.LBB0_81:
	testl	%ebp, %ebp
	je	.LBB0_83
	movl	$0, 776(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_86
	jmp	.LBB0_87
.LBB0_83:
	testl	%r14d, -36(%rsp)
	je	.LBB0_85
	movl	-8(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 776(%rcx)
.LBB0_85:
	testl	%ebp, %ebp
	je	.LBB0_87
.LBB0_86:
	movl	$0, 760(%rcx)
	movl	$0, 768(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_90
	jmp	.LBB0_91
.LBB0_87:
	testl	%r14d, %r14d
	je	.LBB0_91
	movl	768(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 760(%rcx)
	shrl	%eax
	movl	-32(%rsp), %edx
	shll	$7, %edx
	orl	%eax, %edx
	movl	%edx, 768(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_91
.LBB0_90:
	movl	24(%rsp), %eax
	movl	%eax, 752(%rcx)
	movslq	748(%rcx), %rax
	movl	716(%rcx,%rax,4), %edx
	movl	%edx, 708(%rcx)
	movl	60(%rsp), %edx
	movl	%edx, 716(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$6, %eax
	movl	$6, %edx
	cmovbl	%eax, %edx
	movl	%edx, 748(%rcx)
.LBB0_91:
	testl	%ebp, %ebp
	je	.LBB0_93
	movl	$0, 700(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_96
	jmp	.LBB0_97
.LBB0_93:
	testl	%r14d, -32(%rsp)
	je	.LBB0_95
	movl	-4(%rsp), %eax
	incl	%eax
	andl	$15, %eax
	movl	%eax, 700(%rcx)
.LBB0_95:
	testl	%ebp, %ebp
	je	.LBB0_97
.LBB0_96:
	movl	$0, 684(%rcx)
	movl	$0, 692(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_100
	jmp	.LBB0_101
.LBB0_97:
	testl	%r14d, %r14d
	je	.LBB0_101
	movl	692(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 684(%rcx)
	shrl	%eax
	movl	-28(%rsp), %edx
	shll	$4, %edx
	orl	%eax, %edx
	movl	%edx, 692(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_101
.LBB0_100:
	movq	160(%rsp), %rbp
	movswl	%bp, %eax
	movl	96(%rsp), %esi
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
	movl	-120(%rsp), %ebp
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
	movl	68(%rsp), %eax
	movl	%eax, 640(%rcx)
.LBB0_101:
	testl	%ebp, %ebp
	je	.LBB0_103
	movl	$0, 632(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_106
	jmp	.LBB0_107
.LBB0_103:
	testl	%r14d, -28(%rsp)
	je	.LBB0_105
	movq	136(%rsp), %rax
	incl	%eax
	andl	$63, %eax
	movl	%eax, 632(%rcx)
.LBB0_105:
	testl	%ebp, %ebp
	je	.LBB0_107
.LBB0_106:
	movl	$0, 616(%rcx)
	movl	$0, 624(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_110
	jmp	.LBB0_111
.LBB0_107:
	testl	%r14d, %r14d
	je	.LBB0_111
	movl	624(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 616(%rcx)
	shrl	%eax
	movl	-24(%rsp), %edx
	shll	$15, %edx
	orl	%eax, %edx
	movl	%edx, 624(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_111
.LBB0_110:
	movl	-100(%rsp), %eax
	movl	%eax, 608(%rcx)
	movslq	604(%rcx), %rax
	movl	540(%rcx,%rax,4), %edx
	movl	%edx, 532(%rcx)
	movl	-96(%rsp), %edx
	movl	%edx, 540(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$14, %eax
	movl	$14, %edx
	cmovbl	%eax, %edx
	movl	%edx, 604(%rcx)
.LBB0_111:
	testl	%ebp, %ebp
	je	.LBB0_113
	movl	$0, 524(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_116
	jmp	.LBB0_117
.LBB0_113:
	testl	%r14d, -24(%rsp)
	je	.LBB0_115
	movl	(%rsp), %eax
	incl	%eax
	andl	$31, %eax
	movl	%eax, 524(%rcx)
.LBB0_115:
	testl	%ebp, %ebp
	je	.LBB0_117
.LBB0_116:
	movl	$0, 516(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_120
	jmp	.LBB0_121
.LBB0_117:
	testl	%r14d, %r14d
	je	.LBB0_121
	movl	-20(%rsp), %eax
	movl	%eax, 516(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_121
.LBB0_120:
	movl	%r8d, 508(%rcx)
	movl	64(%rsp), %eax
	movl	%eax, 500(%rcx)
.LBB0_121:
	testl	%ebp, %ebp
	je	.LBB0_123
	movl	$0, 492(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_126
	jmp	.LBB0_127
.LBB0_123:
	testl	%r14d, -20(%rsp)
	je	.LBB0_125
	movl	4(%rsp), %eax
	incl	%eax
	andl	$63, %eax
	movl	%eax, 492(%rcx)
.LBB0_125:
	testl	%ebp, %ebp
	je	.LBB0_127
.LBB0_126:
	movl	$0, 476(%rcx)
	movl	$0, 484(%rcx)
	testl	%r14d, %r14d
	jne	.LBB0_130
	jmp	.LBB0_131
.LBB0_127:
	testl	%r14d, %r14d
	je	.LBB0_131
	movl	484(%rcx), %eax
	shldl	$31, %eax, %r12d
	andl	$1, %eax
	movl	%eax, 476(%rcx)
	movl	%r12d, 484(%rcx)
	testl	%r14d, %r14d
	je	.LBB0_131
.LBB0_130:
	movl	72(%rsp), %eax
	movl	%eax, 468(%rcx)
	movslq	464(%rcx), %rax
	movl	336(%rcx,%rax,4), %edx
	movl	%edx, 328(%rcx)
	movl	76(%rsp), %edx
	movl	%edx, 336(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$30, %eax
	movl	$30, %edx
	cmovbl	%eax, %edx
	movl	%edx, 464(%rcx)
.LBB0_131:
	testl	%ebp, %ebp
	je	.LBB0_133
	movl	$0, 320(%rcx)
	movq	16(%rsp), %rdx
	movl	-112(%rsp), %esi
	jmp	.LBB0_135
.LBB0_133:
	testl	%r14d, -64(%rsp)
	movq	16(%rsp), %rdx
	movl	-112(%rsp), %esi
	je	.LBB0_135
	incl	%r9d
	andl	$63, %r9d
	movl	%r9d, 320(%rcx)
.LBB0_135:
	shrl	$2, %r13d
	notl	%r13d
	andl	$1, %r13d
	movq	40(%rdx), %rax
	movl	%r13d, (%rax)
	movq	48(%rdx), %rax
	movl	%r15d, (%rax)
	notl	%esi
	andl	$1, %esi
	movq	56(%rdx), %rax
	movl	%esi, (%rax)
.LBB0_136:
	xorl	%eax, %eax
	addq	$168, %rsp
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
