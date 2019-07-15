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
	subq	$216, %rsp
	.cfi_def_cfa_offset 272
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %rax
	movq	8(%rdi), %rcx
	movl	320(%rcx), %edx
	movq	%rdx, -56(%rsp)
	movl	328(%rcx), %edx
	movq	%rdx, -8(%rsp)
	movl	468(%rcx), %edx
	movl	%edx, -12(%rsp)
	movl	476(%rcx), %edx
	movl	%edx, -16(%rsp)
	movl	492(%rcx), %edx
	movq	%rdx, (%rsp)
	movl	500(%rcx), %edx
	movl	%edx, -104(%rsp)
	movl	508(%rcx), %edx
	movl	%edx, -96(%rsp)
	movl	516(%rcx), %edx
	movl	%edx, -20(%rsp)
	movl	524(%rcx), %edx
	movq	%rdx, 32(%rsp)
	movl	532(%rcx), %edx
	movl	%edx, -100(%rsp)
	movl	608(%rcx), %edx
	movl	%edx, 172(%rsp)
	movq	%rax, 192(%rsp)
	movq	24(%rax), %rdx
	movl	(%rdx), %edi
	movl	1112(%rcx), %edx
	notl	%edx
	testl	%edi, %edx
	movl	616(%rcx), %eax
	movl	%eax, -24(%rsp)
	movslq	632(%rcx), %rax
	movq	%rax, 96(%rsp)
	movl	640(%rcx), %r14d
	movl	648(%rcx), %r13d
	movl	656(%rcx), %eax
	movq	%rax, 16(%rsp)
	movl	684(%rcx), %eax
	movl	%eax, -28(%rsp)
	movl	700(%rcx), %eax
	movq	%rax, 8(%rsp)
	movl	708(%rcx), %eax
	movq	%rax, 24(%rsp)
	movl	752(%rcx), %ebp
	movl	760(%rcx), %ebx
	movl	776(%rcx), %eax
	movq	%rax, 40(%rsp)
	movl	784(%rcx), %eax
	movl	%eax, -92(%rsp)
	movl	792(%rcx), %eax
	movl	%eax, -88(%rsp)
	movl	800(%rcx), %eax
	movl	%eax, -60(%rsp)
	movl	808(%rcx), %eax
	movq	%rax, 48(%rsp)
	movl	816(%rcx), %eax
	movl	%eax, -84(%rsp)
	movl	844(%rcx), %r11d
	movl	%r11d, 168(%rsp)
	movl	852(%rcx), %eax
	movl	%eax, -32(%rsp)
	movslq	868(%rcx), %rax
	movq	%rax, 88(%rsp)
	movl	876(%rcx), %r10d
	movl	884(%rcx), %r11d
	movl	892(%rcx), %eax
	movq	%rax, 64(%rsp)
	movl	920(%rcx), %eax
	movl	%eax, -36(%rsp)
	movl	936(%rcx), %eax
	movq	%rax, 56(%rsp)
	movl	944(%rcx), %eax
	movq	%rax, 72(%rsp)
	movl	960(%rcx), %eax
	movl	%eax, -64(%rsp)
	movl	968(%rcx), %eax
	movl	%eax, -68(%rsp)
	movl	984(%rcx), %eax
	movq	%rax, 80(%rsp)
	movl	992(%rcx), %eax
	movl	%eax, -120(%rsp)
	movl	1000(%rcx), %eax
	movl	%eax, -76(%rsp)
	movl	1008(%rcx), %eax
	movl	%eax, -40(%rsp)
	movl	1016(%rcx), %eax
	movl	%eax, -80(%rsp)
	movl	1024(%rcx), %eax
	movl	%eax, -124(%rsp)
	movl	1032(%rcx), %r8d
	movl	%r8d, -116(%rsp)
	movl	1040(%rcx), %edx
	movl	1056(%rcx), %r9d
	movl	1064(%rcx), %eax
	movq	%rax, -112(%rsp)
	movl	1072(%rcx), %r15d
	movl	1080(%rcx), %r8d
	movl	1088(%rcx), %r12d
	movl	1096(%rcx), %eax
	movl	1104(%rcx), %esi
	movl	%edi, 1112(%rcx)
	je	.LBB0_116
	movl	%r8d, 148(%rsp)
	movl	%eax, 160(%rsp)
	movl	%esi, 164(%rsp)
	movl	%r11d, 128(%rsp)
	movq	%r10, 176(%rsp)
	movl	%r13d, 132(%rsp)
	movq	%r14, 200(%rsp)
	xorl	%edi, %edi
	movq	%r9, 208(%rsp)
	testl	%r9d, %r9d
	setne	%dil
	movq	-112(%rsp), %r9
	andl	%r9d, %edi
	xorl	$1, %edi
	andl	%edi, %edx
	movl	-12(%rsp), %r14d
	movl	%ebx, -44(%rsp)
	movq	%r12, 184(%rsp)
	shrl	$2, %r12d
	andl	$1, %r12d
	movl	%r12d, %eax
	movl	%edx, 152(%rsp)
	andl	%edx, %r12d
	xorl	$1, %r12d
	movl	%r12d, %r10d
	andl	%edi, %r12d
	movq	-8(%rsp), %r8
	movl	%r8d, %edi
	shrl	$16, %edi
	movl	%r15d, %r11d
	shrl	$16, %r11d
	movl	%edi, %edx
	subl	%r11d, %edx
	movl	%r8d, %esi
	subl	%r15d, %esi
	movzwl	%si, %esi
	shll	$16, %edx
	orl	%esi, %edx
	addl	%edi, %r11d
	leal	(%r15,%r8), %esi
	movzwl	%si, %esi
	shll	$16, %r11d
	orl	%esi, %r11d
	movl	%r9d, %esi
	notl	%esi
	andl	$1, %esi
	movl	%esi, 144(%rsp)
	xorl	$1, %eax
	movl	%eax, 156(%rsp)
	andl	%esi, %r10d
	movl	%r10d, -48(%rsp)
	movq	-56(%rsp), %rax
	leal	1(%rax), %esi
	andl	$63, %esi
	movl	%esi, -72(%rsp)
	btl	$5, %eax
	cmovael	%r8d, %r11d
	movl	%r11d, 136(%rsp)
	movq	%r15, -8(%rsp)
	cmovael	%r15d, %edx
	movl	%edx, 140(%rsp)
	movq	(%rsp), %rsi
	leal	1(%rsi), %eax
	andl	$63, %eax
	testl	%r12d, -16(%rsp)
	cmovel	%esi, %eax
	movl	%eax, 124(%rsp)
	movl	%r14d, %eax
	shrl	$16, %eax
	movl	%r14d, %edx
	shll	$16, %edx
	negl	%edx
	orl	%eax, %edx
	testb	$32, %sil
	cmovel	%r14d, %edx
	movl	%edx, (%rsp)
	movq	32(%rsp), %r8
	leal	1(%r8), %eax
	andl	$31, %eax
	testl	%r12d, -20(%rsp)
	cmovel	%r8d, %eax
	movl	%eax, 120(%rsp)
	movl	-100(%rsp), %edx
	movl	%edx, %eax
	shrl	$16, %eax
	movl	-104(%rsp), %ebx
	movl	%ebx, %edi
	shrl	$16, %edi
	movl	%eax, %r15d
	subl	%edi, %r15d
	movl	%edx, %esi
	subl	%ebx, %esi
	movzwl	%si, %esi
	shll	$16, %r15d
	orl	%esi, %r15d
	addl	%eax, %edi
	addl	%edx, %ebx
	movzwl	%bx, %eax
	shll	$16, %edi
	orl	%eax, %edi
	btl	$4, %r8d
	cmovael	-96(%rsp), %r15d
	cmovael	%edx, %edi
	movl	%edi, -100(%rsp)
	movq	96(%rsp), %r14
	leal	1(%r14), %eax
	andl	$63, %eax
	movl	-24(%rsp), %edx
	testl	%edx, %r12d
	cmovel	%r14d, %eax
	movl	%eax, 116(%rsp)
	movq	8(%rsp), %r9
	leal	1(%r9), %eax
	andl	$15, %eax
	testl	%r12d, -28(%rsp)
	cmovel	%r9d, %eax
	movl	%eax, 112(%rsp)
	movq	24(%rsp), %r8
	movl	%r8d, %eax
	shrl	$16, %eax
	movq	16(%rsp), %rdx
	movl	%edx, %ebx
	shrl	$16, %ebx
	movl	%eax, %edi
	subl	%ebx, %edi
	movl	%r8d, %esi
	subl	%edx, %esi
	movzwl	%si, %esi
	shll	$16, %edi
	orl	%esi, %edi
	addl	%eax, %ebx
	leal	(%r8,%rdx), %eax
	movzwl	%ax, %eax
	shll	$16, %ebx
	orl	%eax, %ebx
	btl	$3, %r9d
	cmovael	%edx, %edi
	movl	%edi, 32(%rsp)
	cmovael	%r8d, %ebx
	movl	%ebx, -104(%rsp)
	movq	40(%rsp), %rdx
	leal	1(%rdx), %eax
	andl	$15, %eax
	testl	%r12d, -44(%rsp)
	cmovel	%edx, %eax
	movl	%eax, 16(%rsp)
	movl	%ebp, %eax
	shrl	$16, %eax
	movl	%ebp, %esi
	shll	$16, %esi
	negl	%esi
	orl	%eax, %esi
	testb	$8, %dl
	movl	%ebp, 40(%rsp)
	cmovel	%ebp, %esi
	movl	%esi, 24(%rsp)
	movq	48(%rsp), %r8
	leal	1(%r8), %r11d
	andl	$7, %r11d
	movl	-60(%rsp), %eax
	testl	%eax, %r12d
	cmovel	%r8d, %r11d
	movl	-84(%rsp), %edx
	movl	%edx, %eax
	shrl	$16, %eax
	movl	-92(%rsp), %ebx
	movl	%ebx, %ebp
	shrl	$16, %ebp
	movl	%eax, %edi
	subl	%ebp, %edi
	movl	%edx, %esi
	subl	%ebx, %esi
	movzwl	%si, %esi
	shll	$16, %edi
	orl	%esi, %edi
	addl	%eax, %ebp
	addl	%edx, %ebx
	movzwl	%bx, %eax
	shll	$16, %ebp
	orl	%eax, %ebp
	btl	$2, %r8d
	cmovael	-88(%rsp), %edi
	movl	%edi, -88(%rsp)
	cmovael	%edx, %ebp
	movl	%ebp, -84(%rsp)
	movq	88(%rsp), %r13
	leal	1(%r13), %eax
	andl	$15, %eax
	testl	%r12d, -32(%rsp)
	cmovel	%r13d, %eax
	movl	%eax, 48(%rsp)
	movq	56(%rsp), %r8
	leal	1(%r8), %eax
	andl	$3, %eax
	movl	-36(%rsp), %esi
	testl	%esi, %r12d
	cmovel	%r8d, %eax
	movl	%eax, -92(%rsp)
	movq	72(%rsp), %rdx
	movl	%edx, %eax
	shrl	$16, %eax
	movq	64(%rsp), %rbx
	movl	%ebx, %edi
	shrl	$16, %edi
	movl	%eax, %ebp
	subl	%edi, %ebp
	movl	%edx, %esi
	subl	%ebx, %esi
	movzwl	%si, %esi
	shll	$16, %ebp
	orl	%esi, %ebp
	addl	%eax, %edi
	leal	(%rdx,%rbx), %eax
	movzwl	%ax, %eax
	shll	$16, %edi
	orl	%eax, %edi
	btl	$1, %r8d
	cmovael	%ebx, %ebp
	cmovael	%edx, %edi
	movl	%edi, 72(%rsp)
	movq	80(%rsp), %rsi
	leal	1(%rsi), %eax
	andl	$3, %eax
	testl	%r12d, -68(%rsp)
	cmovel	%esi, %eax
	movl	%eax, 56(%rsp)
	movl	-64(%rsp), %edx
	movl	%edx, %eax
	shrl	$16, %eax
	movl	%edx, %edi
	shll	$16, %edi
	negl	%edi
	orl	%eax, %edi
	testb	$2, %sil
	cmovel	%edx, %edi
	movl	%edi, 80(%rsp)
	movl	-80(%rsp), %r8d
	movl	%r8d, %eax
	notl	%eax
	andl	$1, %eax
	testl	%r12d, -40(%rsp)
	cmovel	%r8d, %eax
	movl	%eax, 108(%rsp)
	movl	-124(%rsp), %ebx
	movl	%ebx, %eax
	shrl	$16, %eax
	movl	-120(%rsp), %edi
	movl	%edi, %r9d
	shrl	$16, %r9d
	movl	%eax, %edx
	subl	%r9d, %edx
	movl	%ebx, %esi
	subl	%edi, %esi
	movzwl	%si, %esi
	shll	$16, %edx
	orl	%esi, %edx
	addl	%eax, %r9d
	addl	%ebx, %edi
	movzwl	%di, %eax
	movl	-48(%rsp), %edi
	shll	$16, %r9d
	orl	%eax, %r9d
	testl	%r8d, %r8d
	cmovel	-76(%rsp), %edx
	movl	%edx, -76(%rsp)
	cmovel	%ebx, %r9d
	movq	208(%rsp), %rax
	leal	1(%rax), %esi
	andl	$63, %esi
	movl	%r12d, -124(%rsp)
	testl	%r12d, 144(%rsp)
	movl	-72(%rsp), %edx
	cmovel	-56(%rsp), %edx
	movl	%edx, -72(%rsp)
	cmovel	%eax, %esi
	movl	%esi, -80(%rsp)
	movq	-112(%rsp), %rsi
	movl	%esi, %r8d
	shrl	$2, %r8d
	notl	%r8d
	movq	192(%rsp), %r12
	movq	8(%r12), %rax
	andl	(%rax), %r8d
	movq	32(%r12), %rax
	movl	(%rax), %ebx
	movl	(%rcx,%r14,4), %eax
	movl	%eax, 96(%rsp)
	movl	256(%rcx,%r13,4), %eax
	movl	%eax, 88(%rsp)
	andl	$1, %r8d
	movl	%edi, %eax
	xorl	$1, %eax
	movl	%esi, %r14d
	shrl	%r14d
	testl	%eax, %r8d
	movl	%r15d, -96(%rsp)
	movl	%r11d, 8(%rsp)
	movl	%ebx, -56(%rsp)
	movl	%ebp, 64(%rsp)
	je	.LBB0_2
	movq	-112(%rsp), %rdx
	leal	(%rdx,%rdx), %edx
	andl	$6, %edx
	jmp	.LBB0_4
.LBB0_2:
	movl	%r14d, %edx
	andl	$3, %edx
	movl	%r8d, %esi
	notl	%esi
	testl	%edi, %esi
	cmovel	-112(%rsp), %edx
.LBB0_4:
	movl	%edx, -120(%rsp)
	movl	%edi, %r15d
	movq	184(%rsp), %rbx
	movq	-8(%rsp), %r10
	movq	-112(%rsp), %r13
	andl	%r8d, %r13d
	andl	%r14d, %r8d
	andl	$1, %r14d
	movq	(%r12), %rsi
	movq	16(%r12), %rbp
	movl	(%rsi), %r11d
	orl	%r14d, %eax
	movl	%r11d, %eax
	movl	148(%rsp), %edx
	cmovel	%edx, %eax
	orl	%edi, %r13d
	cmovel	%r10d, %eax
	orl	%edi, %r8d
	cmovel	%edx, %r11d
	movl	156(%rsp), %r10d
	andl	152(%rsp), %r10d
	movl	%ebx, %edx
	notl	%edx
	andl	(%rbp), %edx
	andl	$1, %edx
	movl	%edx, %ebp
	xorl	$1, %ebp
	movl	%ebx, %esi
	shrl	%esi
	testl	%r10d, %ebp
	movq	%rbx, %r14
	je	.LBB0_5
	leal	(%r14,%r14), %r8d
	andl	$6, %r8d
	jmp	.LBB0_7
.LBB0_5:
	movl	%esi, %r8d
	andl	$3, %r8d
	movl	%r10d, %ebx
	xorl	$1, %ebx
	testl	%ebx, %edx
	movq	192(%rsp), %r12
	cmovel	%r14d, %r8d
.LBB0_7:
	movq	%r14, %rbx
	movl	-56(%rsp), %r15d
	andl	%r10d, %ebx
	andl	%esi, %r10d
	andl	$1, %esi
	orl	%esi, %ebp
	movl	-116(%rsp), %ebp
	movl	%ebp, %esi
	movl	164(%rsp), %r14d
	cmovel	%r14d, %esi
	orl	%edx, %ebx
	cmovel	160(%rsp), %esi
	orl	%edx, %r10d
	cmovel	%r14d, %ebp
	movl	%ebp, 1104(%rcx)
	movl	%esi, -116(%rsp)
	movl	%esi, 1096(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_9
	movl	$1, 1088(%rcx)
	movl	$1, %r8d
	jmp	.LBB0_10
.LBB0_9:
	movl	%r8d, 1088(%rcx)
.LBB0_10:
	movl	-64(%rsp), %edx
	movl	-68(%rsp), %esi
	testl	%r15d, %r15d
	movl	%r11d, 1080(%rcx)
	movl	%eax, 1072(%rcx)
	movl	%r8d, -112(%rsp)
	movq	%r12, %r8
	je	.LBB0_12
	movl	$1, 1064(%rcx)
	movl	$1, %ebx
	movl	-60(%rsp), %r11d
	movq	176(%rsp), %rbp
	testl	%r15d, %r15d
	je	.LBB0_15
.LBB0_14:
	movl	$0, 1056(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_18
.LBB0_17:
	movl	$0, 1040(%rcx)
	movl	$0, 1048(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_21
	jmp	.LBB0_22
.LBB0_12:
	movl	-120(%rsp), %ebx
	movl	%ebx, 1064(%rcx)
	movl	-60(%rsp), %r11d
	movq	176(%rsp), %rbp
	testl	%r15d, %r15d
	jne	.LBB0_14
.LBB0_15:
	movl	-80(%rsp), %eax
	movl	%eax, 1056(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_17
.LBB0_18:
	cmpl	$0, -124(%rsp)
	je	.LBB0_20
	movl	1048(%rcx), %eax
	movl	%eax, 1040(%rcx)
	movl	-40(%rsp), %eax
	movl	%eax, 1048(%rcx)
.LBB0_20:
	cmpl	$0, -124(%rsp)
	je	.LBB0_22
.LBB0_21:
	movl	%r9d, 1032(%rcx)
	movl	-76(%rsp), %eax
	movl	%eax, 1024(%rcx)
.LBB0_22:
	testl	%r15d, %r15d
	je	.LBB0_24
	movl	$0, 1016(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_27
.LBB0_26:
	movl	$0, 1008(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_30
	jmp	.LBB0_31
.LBB0_24:
	movl	108(%rsp), %eax
	movl	%eax, 1016(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_26
.LBB0_27:
	cmpl	$0, -124(%rsp)
	je	.LBB0_31
	movl	%esi, 1008(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_31
.LBB0_30:
	movl	%edx, 1000(%rcx)
	movl	80(%rsp), %eax
	movl	%eax, 992(%rcx)
.LBB0_31:
	testl	%r15d, %r15d
	je	.LBB0_33
	movl	$0, 984(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_36
.LBB0_35:
	movl	$0, 968(%rcx)
	movl	$0, 976(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_39
	jmp	.LBB0_40
.LBB0_33:
	movl	56(%rsp), %eax
	movl	%eax, 984(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_35
.LBB0_36:
	cmpl	$0, -124(%rsp)
	je	.LBB0_40
	movl	976(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 968(%rcx)
	shrl	%eax
	movl	-36(%rsp), %edx
	addl	%edx, %edx
	orl	%eax, %edx
	movl	%edx, 976(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_40
.LBB0_39:
	movl	72(%rsp), %eax
	movl	%eax, 960(%rcx)
	movl	952(%rcx), %eax
	movl	%eax, 944(%rcx)
	movl	64(%rsp), %eax
	movl	%eax, 952(%rcx)
.LBB0_40:
	testl	%r15d, %r15d
	je	.LBB0_42
	movl	$0, 936(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_45
.LBB0_44:
	movl	$0, 920(%rcx)
	movl	$0, 928(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_48
	jmp	.LBB0_49
.LBB0_42:
	movl	-92(%rsp), %eax
	movl	%eax, 936(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_44
.LBB0_45:
	cmpl	$0, -124(%rsp)
	je	.LBB0_49
	movl	928(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 920(%rcx)
	shrl	%eax
	movl	-32(%rsp), %edx
	shll	$4, %edx
	orl	%eax, %edx
	movl	%edx, 928(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_49
.LBB0_48:
	movswl	%bp, %eax
	movl	128(%rsp), %esi
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
	movslq	916(%rcx), %rdx
	movl	900(%rcx,%rdx,4), %esi
	movl	%esi, 892(%rcx)
	movl	%eax, 900(%rcx,%rdx,4)
	leal	-1(%rdx), %eax
	cmpl	$3, %eax
	movl	$3, %edx
	cmovbl	%eax, %edx
	movl	%edx, 916(%rcx)
	movl	88(%rsp), %eax
	movl	%eax, 884(%rcx)
	movl	168(%rsp), %eax
	movl	%eax, 876(%rcx)
.LBB0_49:
	testl	%r15d, %r15d
	je	.LBB0_51
	movl	$0, 868(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_54
.LBB0_53:
	movl	$0, 852(%rcx)
	movl	$0, 860(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_57
	jmp	.LBB0_58
.LBB0_51:
	movl	48(%rsp), %eax
	movl	%eax, 868(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_53
.LBB0_54:
	cmpl	$0, -124(%rsp)
	je	.LBB0_58
	movl	860(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 852(%rcx)
	shrl	%eax
	shll	$3, %r11d
	orl	%eax, %r11d
	movl	%r11d, 860(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_58
.LBB0_57:
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
.LBB0_58:
	testl	%r15d, %r15d
	je	.LBB0_60
	movl	$0, 808(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_63
.LBB0_62:
	movl	$0, 800(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_66
	jmp	.LBB0_67
.LBB0_60:
	movl	8(%rsp), %eax
	movl	%eax, 808(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_62
.LBB0_63:
	cmpl	$0, -124(%rsp)
	je	.LBB0_67
	movl	-44(%rsp), %eax
	movl	%eax, 800(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_67
.LBB0_66:
	movl	40(%rsp), %eax
	movl	%eax, 792(%rcx)
	movl	24(%rsp), %eax
	movl	%eax, 784(%rcx)
.LBB0_67:
	testl	%r15d, %r15d
	je	.LBB0_69
	movl	$0, 776(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_72
.LBB0_71:
	movl	$0, 760(%rcx)
	movl	$0, 768(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_75
	jmp	.LBB0_76
.LBB0_69:
	movl	16(%rsp), %eax
	movl	%eax, 776(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_71
.LBB0_72:
	cmpl	$0, -124(%rsp)
	je	.LBB0_76
	movl	768(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 760(%rcx)
	shrl	%eax
	movl	-28(%rsp), %edx
	shll	$7, %edx
	orl	%eax, %edx
	movl	%edx, 768(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_76
.LBB0_75:
	movl	-104(%rsp), %eax
	movl	%eax, 752(%rcx)
	movslq	748(%rcx), %rax
	movl	716(%rcx,%rax,4), %edx
	movl	%edx, 708(%rcx)
	movl	32(%rsp), %edx
	movl	%edx, 716(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$6, %eax
	movl	$6, %edx
	cmovbl	%eax, %edx
	movl	%edx, 748(%rcx)
.LBB0_76:
	testl	%r15d, %r15d
	je	.LBB0_78
	movl	$0, 700(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_81
.LBB0_80:
	movl	$0, 684(%rcx)
	movl	$0, 692(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_84
	jmp	.LBB0_85
.LBB0_78:
	movl	112(%rsp), %eax
	movl	%eax, 700(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_80
.LBB0_81:
	cmpl	$0, -124(%rsp)
	je	.LBB0_85
	movl	692(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 684(%rcx)
	shrl	%eax
	movl	-24(%rsp), %edx
	shll	$4, %edx
	orl	%eax, %edx
	movl	%edx, 692(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_85
.LBB0_84:
	movq	200(%rsp), %rbp
	movswl	%bp, %eax
	movl	132(%rsp), %esi
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
	movl	96(%rsp), %eax
	movl	%eax, 648(%rcx)
	movl	172(%rsp), %eax
	movl	%eax, 640(%rcx)
.LBB0_85:
	testl	%r15d, %r15d
	je	.LBB0_87
	movl	$0, 632(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_90
.LBB0_89:
	movl	$0, 616(%rcx)
	movl	$0, 624(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_93
	jmp	.LBB0_94
.LBB0_87:
	movl	116(%rsp), %eax
	movl	%eax, 632(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_89
.LBB0_90:
	cmpl	$0, -124(%rsp)
	je	.LBB0_94
	movl	624(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 616(%rcx)
	shrl	%eax
	movl	-20(%rsp), %edx
	shll	$15, %edx
	orl	%eax, %edx
	movl	%edx, 624(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_94
.LBB0_93:
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
.LBB0_94:
	testl	%r15d, %r15d
	je	.LBB0_96
	movl	$0, 524(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_99
.LBB0_98:
	movl	$0, 516(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_102
	jmp	.LBB0_103
.LBB0_96:
	movl	120(%rsp), %eax
	movl	%eax, 524(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_98
.LBB0_99:
	cmpl	$0, -124(%rsp)
	je	.LBB0_103
	movl	-16(%rsp), %eax
	movl	%eax, 516(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_103
.LBB0_102:
	movl	-12(%rsp), %eax
	movl	%eax, 508(%rcx)
	movl	(%rsp), %eax
	movl	%eax, 500(%rcx)
.LBB0_103:
	testl	%r15d, %r15d
	je	.LBB0_105
	movl	$0, 492(%rcx)
	testl	%r15d, %r15d
	je	.LBB0_108
.LBB0_107:
	movl	$0, 476(%rcx)
	movl	$0, 484(%rcx)
	cmpl	$0, -124(%rsp)
	jne	.LBB0_111
	jmp	.LBB0_112
.LBB0_105:
	movl	124(%rsp), %eax
	movl	%eax, 492(%rcx)
	testl	%r15d, %r15d
	jne	.LBB0_107
.LBB0_108:
	cmpl	$0, -124(%rsp)
	je	.LBB0_112
	movl	484(%rcx), %eax
	movl	-48(%rsp), %edx
	shldl	$31, %eax, %edx
	andl	$1, %eax
	movl	%eax, 476(%rcx)
	movl	%edx, 484(%rcx)
	cmpl	$0, -124(%rsp)
	je	.LBB0_112
.LBB0_111:
	movl	136(%rsp), %eax
	movl	%eax, 468(%rcx)
	movslq	464(%rcx), %rax
	movl	336(%rcx,%rax,4), %edx
	movl	%edx, 328(%rcx)
	movl	140(%rsp), %edx
	movl	%edx, 336(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$30, %eax
	movl	$30, %edx
	cmovbl	%eax, %edx
	movl	%edx, 464(%rcx)
.LBB0_112:
	testl	%r15d, %r15d
	je	.LBB0_114
	movl	$0, 320(%rcx)
	jmp	.LBB0_115
.LBB0_114:
	movl	-72(%rsp), %eax
	movl	%eax, 320(%rcx)
.LBB0_115:
	movl	-116(%rsp), %ecx
	shrl	$2, %ebx
	notl	%ebx
	andl	$1, %ebx
	movq	40(%r8), %rax
	movl	%ebx, (%rax)
	movq	48(%r8), %rax
	movl	%ecx, (%rax)
	movl	-112(%rsp), %ecx
	notl	%ecx
	andl	$1, %ecx
	movq	56(%r8), %rax
	movl	%ecx, (%rax)
.LBB0_116:
	xorl	%eax, %eax
	addq	$216, %rsp
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
