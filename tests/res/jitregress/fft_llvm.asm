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
	subq	$192, %rsp
	.cfi_def_cfa_offset 248
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	.cfi_offset %rbp, -16
	movq	(%rdi), %rax
	movq	8(%rdi), %rcx
	movl	320(%rcx), %edx
	movq	%rdx, -112(%rsp)
	movl	328(%rcx), %edx
	movq	%rdx, 40(%rsp)
	movl	468(%rcx), %edx
	movl	%edx, -40(%rsp)
	movl	476(%rcx), %edx
	movl	%edx, 16(%rsp)
	movl	492(%rcx), %edx
	movq	%rdx, 48(%rsp)
	movl	500(%rcx), %edx
	movl	%edx, -96(%rsp)
	movl	508(%rcx), %edx
	movl	%edx, -88(%rsp)
	movl	516(%rcx), %edx
	movl	%edx, -44(%rsp)
	movl	524(%rcx), %edx
	movq	%rdx, 64(%rsp)
	movl	532(%rcx), %edx
	movl	%edx, -92(%rsp)
	movl	608(%rcx), %edx
	movl	%edx, 152(%rsp)
	movq	%rax, 168(%rsp)
	movq	24(%rax), %rdx
	movl	(%rdx), %esi
	movl	1088(%rcx), %edx
	notl	%edx
	testl	%esi, %edx
	movl	616(%rcx), %eax
	movl	%eax, 12(%rsp)
	movslq	632(%rcx), %rax
	movq	%rax, 32(%rsp)
	movl	640(%rcx), %r13d
	movl	648(%rcx), %r12d
	movl	656(%rcx), %eax
	movl	%eax, 156(%rsp)
	movl	664(%rcx), %eax
	movl	%eax, -116(%rsp)
	movl	672(%rcx), %eax
	movl	%eax, -48(%rsp)
	movl	688(%rcx), %eax
	movq	%rax, 56(%rsp)
	movl	696(%rcx), %eax
	movl	%eax, -100(%rsp)
	movl	740(%rcx), %eax
	movl	%eax, 20(%rsp)
	movl	748(%rcx), %eax
	movl	%eax, 8(%rsp)
	movl	764(%rcx), %eax
	movq	%rax, 72(%rsp)
	movl	772(%rcx), %eax
	movl	%eax, -84(%rsp)
	movl	780(%rcx), %eax
	movl	%eax, -80(%rsp)
	movl	788(%rcx), %eax
	movl	%eax, 4(%rsp)
	movl	796(%rcx), %eax
	movq	%rax, 80(%rsp)
	movl	804(%rcx), %eax
	movl	%eax, -76(%rsp)
	movl	832(%rcx), %r15d
	movl	%r15d, 148(%rsp)
	movl	840(%rcx), %eax
	movl	%eax, (%rsp)
	movslq	856(%rcx), %rax
	movq	%rax, 24(%rsp)
	movl	864(%rcx), %r15d
	movl	872(%rcx), %r14d
	movl	880(%rcx), %eax
	movl	%eax, -72(%rsp)
	movl	888(%rcx), %eax
	movl	%eax, -36(%rsp)
	movl	896(%rcx), %r9d
	movl	912(%rcx), %eax
	movq	%rax, 88(%rsp)
	movl	920(%rcx), %eax
	movl	%eax, -68(%rsp)
	movl	936(%rcx), %r11d
	movl	944(%rcx), %edx
	movl	%edx, -4(%rsp)
	movl	960(%rcx), %eax
	movq	%rax, 96(%rsp)
	movl	968(%rcx), %eax
	movl	%eax, -64(%rsp)
	movl	976(%rcx), %eax
	movl	%eax, -56(%rsp)
	movl	984(%rcx), %edx
	movl	%edx, -8(%rsp)
	movl	992(%rcx), %eax
	movl	%eax, -60(%rsp)
	movl	1000(%rcx), %eax
	movl	%eax, -120(%rsp)
	movl	1008(%rcx), %r10d
	movl	%r10d, -12(%rsp)
	movl	1016(%rcx), %ebx
	movl	1032(%rcx), %r10d
	movl	1040(%rcx), %edx
	movq	%rdx, -128(%rsp)
	movl	1048(%rcx), %eax
	movl	1056(%rcx), %ebp
	movl	1064(%rcx), %r8d
	movl	1072(%rcx), %edi
	movl	1080(%rcx), %edx
	movl	%esi, 1088(%rcx)
	je	.LBB0_116
	movl	%ebp, 128(%rsp)
	movl	%edi, 140(%rsp)
	movl	%edx, 144(%rsp)
	movl	%r14d, 116(%rsp)
	movl	%r15d, 120(%rsp)
	movl	%r12d, -28(%rsp)
	movl	%r13d, -24(%rsp)
	movl	%ebx, %edx
	movq	%rax, %rdi
	movq	%r10, %rax
	movq	%r10, 184(%rsp)
	xorl	%ebx, %ebx
	testl	%eax, %eax
	setne	%bl
	movq	-128(%rsp), %r12
	andl	%r12d, %ebx
	xorl	$1, %ebx
	andl	%ebx, %edx
	movl	%r9d, -20(%rsp)
	movl	%r11d, -16(%rsp)
	movq	%r8, 160(%rsp)
	movl	%r8d, %r9d
	shrl	$2, %r9d
	andl	$1, %r9d
	movl	%r9d, %eax
	movl	%edx, 132(%rsp)
	andl	%edx, %r9d
	xorl	$1, %r9d
	movl	%r9d, %esi
	andl	%ebx, %r9d
	movq	40(%rsp), %r10
	movl	%r10d, %ebx
	shrl	$16, %ebx
	movl	-116(%rsp), %r14d
	movl	%edi, %r13d
	shrl	$16, %r13d
	movl	-36(%rsp), %r11d
	movl	%ebx, %r15d
	subl	%r13d, %r15d
	movl	%r10d, %edx
	subl	%edi, %edx
	movzwl	%dx, %edx
	shll	$16, %r15d
	orl	%edx, %r15d
	addl	%ebx, %r13d
	leal	(%rdi,%r10), %edx
	movq	%rdi, 176(%rsp)
	movzwl	%dx, %edx
	shll	$16, %r13d
	orl	%edx, %r13d
	movl	%r12d, %ebx
	notl	%ebx
	andl	$1, %ebx
	xorl	$1, %eax
	movl	%eax, 136(%rsp)
	andl	%ebx, %esi
	movl	%esi, %r12d
	movq	-112(%rsp), %rax
	leal	1(%rax), %edx
	andl	$63, %edx
	movl	%edx, -52(%rsp)
	btl	$5, %eax
	cmovael	%r10d, %r13d
	movl	%r13d, 124(%rsp)
	cmovael	%edi, %r15d
	movl	%r15d, 40(%rsp)
	movq	48(%rsp), %rdi
	leal	1(%rdi), %eax
	andl	$63, %eax
	testl	%r9d, 16(%rsp)
	cmovel	%edi, %eax
	movl	%eax, 112(%rsp)
	movl	-40(%rsp), %esi
	movl	%esi, %eax
	shrl	$16, %eax
	movl	%esi, %edx
	shll	$16, %edx
	negl	%edx
	orl	%eax, %edx
	testb	$32, %dil
	cmovel	%esi, %edx
	movl	%edx, 48(%rsp)
	movq	64(%rsp), %r15
	leal	1(%r15), %eax
	andl	$31, %eax
	testl	%r9d, -44(%rsp)
	cmovel	%r15d, %eax
	movl	%eax, 108(%rsp)
	movl	-92(%rsp), %r13d
	movl	%r13d, %eax
	shrl	$16, %eax
	movl	-96(%rsp), %esi
	movl	%esi, %ebp
	shrl	$16, %ebp
	movl	%eax, %edi
	subl	%ebp, %edi
	movl	%r13d, %edx
	subl	%esi, %edx
	movzwl	%dx, %edx
	shll	$16, %edi
	orl	%edx, %edi
	addl	%eax, %ebp
	addl	%r13d, %esi
	movzwl	%si, %eax
	shll	$16, %ebp
	orl	%eax, %ebp
	btl	$4, %r15d
	cmovael	-88(%rsp), %edi
	movl	%edi, -88(%rsp)
	cmovael	%r13d, %ebp
	movl	%ebp, -92(%rsp)
	movq	32(%rsp), %rsi
	leal	1(%rsi), %eax
	andl	$63, %eax
	movl	12(%rsp), %r8d
	testl	%r8d, %r9d
	cmovel	%esi, %eax
	movl	%eax, -96(%rsp)
	movq	56(%rsp), %r15
	leal	1(%r15), %eax
	andl	$15, %eax
	testl	%r9d, -48(%rsp)
	cmovel	%r15d, %eax
	movl	%eax, 104(%rsp)
	movl	-100(%rsp), %r13d
	movl	%r13d, %edi
	shrl	$16, %edi
	movl	%edi, %eax
	subl	%r14d, %eax
	movl	%r13d, %edx
	movl	156(%rsp), %ebp
	subl	%ebp, %edx
	movzwl	%dx, %edx
	shll	$16, %eax
	orl	%edx, %eax
	addl	%r14d, %edi
	shll	$16, %r14d
	orl	%ebp, %r14d
	addl	%r13d, %ebp
	movzwl	%bp, %edx
	shll	$16, %edi
	orl	%edx, %edi
	btl	$3, %r15d
	cmovbl	%eax, %r14d
	movl	%r14d, -116(%rsp)
	cmovael	%r13d, %edi
	movl	%edi, 64(%rsp)
	movq	72(%rsp), %rdi
	leal	1(%rdi), %eax
	andl	$15, %eax
	testl	%r9d, 8(%rsp)
	cmovel	%edi, %eax
	movl	%eax, -100(%rsp)
	movl	20(%rsp), %ebp
	movl	%ebp, %eax
	shrl	$16, %eax
	movl	%ebp, %edx
	shll	$16, %edx
	negl	%edx
	orl	%eax, %edx
	testb	$8, %dil
	cmovel	%ebp, %edx
	movl	%edx, 72(%rsp)
	movq	80(%rsp), %r15
	leal	1(%r15), %eax
	andl	$7, %eax
	movl	4(%rsp), %edx
	testl	%edx, %r9d
	cmovel	%r15d, %eax
	movl	%eax, 56(%rsp)
	movl	-76(%rsp), %r14d
	movl	%r14d, %r13d
	shrl	$16, %r13d
	movl	-84(%rsp), %eax
	movl	%eax, %ebp
	shrl	$16, %ebp
	movl	%r13d, %edi
	subl	%ebp, %edi
	movl	%r14d, %edx
	subl	%eax, %edx
	movzwl	%dx, %edx
	shll	$16, %edi
	orl	%edx, %edi
	addl	%r13d, %ebp
	addl	%r14d, %eax
	movzwl	%ax, %eax
	shll	$16, %ebp
	orl	%eax, %ebp
	btl	$2, %r15d
	cmovael	-80(%rsp), %edi
	movl	%edi, -80(%rsp)
	cmovael	%r14d, %ebp
	movl	%ebp, -76(%rsp)
	movq	24(%rsp), %r13
	leal	1(%r13), %eax
	andl	$15, %eax
	testl	%r9d, (%rsp)
	cmovel	%r13d, %eax
	movl	%eax, 80(%rsp)
	movq	88(%rsp), %r8
	leal	1(%r8), %eax
	andl	$3, %eax
	testl	%r9d, -20(%rsp)
	cmovel	%r8d, %eax
	movl	%eax, -84(%rsp)
	movl	-68(%rsp), %r14d
	movl	%r14d, %edi
	shrl	$16, %edi
	movl	%edi, %eax
	subl	%r11d, %eax
	movl	%r14d, %edx
	movl	-72(%rsp), %ebp
	subl	%ebp, %edx
	movzwl	%dx, %edx
	shll	$16, %eax
	orl	%edx, %eax
	addl	%r11d, %edi
	shll	$16, %r11d
	orl	%ebp, %r11d
	addl	%r14d, %ebp
	movzwl	%bp, %edx
	shll	$16, %edi
	orl	%edx, %edi
	btl	$1, %r8d
	cmovbl	%eax, %r11d
	movl	%r11d, -36(%rsp)
	cmovael	%r14d, %edi
	movl	%edi, -68(%rsp)
	movq	96(%rsp), %rdi
	leal	1(%rdi), %edx
	andl	$3, %edx
	movl	-4(%rsp), %eax
	testl	%eax, %r9d
	cmovel	%edi, %edx
	movl	%edx, 88(%rsp)
	movl	-16(%rsp), %eax
	movl	%eax, %ebp
	shrl	$16, %ebp
	movl	%eax, %edx
	shll	$16, %edx
	negl	%edx
	orl	%ebp, %edx
	testb	$2, %dil
	cmovel	%eax, %edx
	movl	%edx, 96(%rsp)
	movl	-60(%rsp), %r8d
	movl	%r8d, %edx
	notl	%edx
	andl	$1, %edx
	movl	-8(%rsp), %eax
	testl	%eax, %r9d
	cmovel	%r8d, %edx
	movl	%edx, -72(%rsp)
	movl	-120(%rsp), %edi
	movl	%edi, %eax
	shrl	$16, %eax
	movl	-64(%rsp), %ebp
	movl	%ebp, %r11d
	shrl	$16, %r11d
	movl	%eax, %r15d
	subl	%r11d, %r15d
	movl	%edi, %edx
	subl	%ebp, %edx
	movzwl	%dx, %edx
	shll	$16, %r15d
	orl	%edx, %r15d
	addl	%eax, %r11d
	addl	%edi, %ebp
	movzwl	%bp, %eax
	shll	$16, %r11d
	orl	%eax, %r11d
	testl	%r8d, %r8d
	cmovel	-56(%rsp), %r15d
	cmovel	%edi, %r11d
	movq	184(%rsp), %rax
	leal	1(%rax), %edi
	andl	$63, %edi
	testl	%ebx, %r9d
	movl	-52(%rsp), %edx
	cmovel	-112(%rsp), %edx
	movl	%edx, -52(%rsp)
	cmovel	%eax, %edi
	movl	%edi, -64(%rsp)
	movq	-128(%rsp), %rdx
	movl	%edx, %r14d
	shrl	$2, %r14d
	notl	%r14d
	movq	168(%rsp), %rdi
	movq	8(%rdi), %rax
	andl	(%rax), %r14d
	movq	32(%rdi), %rax
	movl	(%rax), %eax
	movl	%eax, -120(%rsp)
	movl	(%rcx,%rsi,4), %r8d
	movl	256(%rcx,%r13,4), %ebx
	andl	$1, %r14d
	movl	%r12d, %eax
	xorl	$1, %eax
	movl	%edx, %ebp
	shrl	%ebp
	testl	%eax, %r14d
	movq	176(%rsp), %r13
	movl	%r8d, -56(%rsp)
	movl	%r9d, -32(%rsp)
	movl	%ebx, -60(%rsp)
	je	.LBB0_2
	movq	-128(%rsp), %rdx
	leal	(%rdx,%rdx), %edx
	andl	$6, %edx
	movl	%edx, -112(%rsp)
	jmp	.LBB0_4
.LBB0_2:
	movl	%ebp, %esi
	andl	$3, %esi
	movl	%r14d, %edx
	notl	%edx
	testl	%r12d, %edx
	cmovel	-128(%rsp), %esi
	movl	%esi, -112(%rsp)
.LBB0_4:
	movl	-12(%rsp), %r10d
	movl	%r12d, %ebx
	movq	-128(%rsp), %rdx
	movq	%rdx, %rsi
	andl	%r14d, %esi
	andl	%ebp, %r14d
	andl	$1, %ebp
	movq	(%rdi), %rdx
	movq	16(%rdi), %rdi
	movl	(%rdx), %r12d
	orl	%ebp, %eax
	movl	%r12d, %r8d
	movl	128(%rsp), %eax
	cmovel	%eax, %r8d
	orl	%ebx, %esi
	cmovel	%r13d, %r8d
	movl	%ebx, 32(%rsp)
	orl	%ebx, %r14d
	cmovel	%eax, %r12d
	movl	136(%rsp), %eax
	andl	132(%rsp), %eax
	movq	160(%rsp), %rsi
	movl	%esi, %ebp
	notl	%ebp
	andl	(%rdi), %ebp
	andl	$1, %ebp
	movl	%ebp, %edi
	xorl	$1, %edi
	movl	%esi, %edx
	shrl	%edx
	testl	%eax, %edi
	je	.LBB0_5
	leal	(%rsi,%rsi), %ebx
	andl	$6, %ebx
	movl	%ebx, -128(%rsp)
	jmp	.LBB0_7
.LBB0_5:
	movl	%edx, %r13d
	andl	$3, %r13d
	movl	%eax, %r14d
	xorl	$1, %r14d
	testl	%r14d, %ebp
	movq	160(%rsp), %rsi
	cmovel	%esi, %r13d
	movl	%r13d, -128(%rsp)
.LBB0_7:
	andl	%eax, %esi
	andl	%edx, %eax
	andl	$1, %edx
	orl	%edx, %edi
	movl	%r10d, %edx
	movl	144(%rsp), %edi
	cmovel	%edi, %edx
	orl	%ebp, %esi
	cmovel	140(%rsp), %edx
	orl	%ebp, %eax
	cmovel	%edi, %r10d
	movl	%r10d, 1080(%rcx)
	movl	%edx, 1072(%rcx)
	movl	-120(%rsp), %ebp
	testl	%ebp, %ebp
	je	.LBB0_9
	movl	$1, 1064(%rcx)
	movl	$1, -128(%rsp)
	testl	%ebp, %ebp
	movl	%r12d, 1056(%rcx)
	movl	%r8d, 1048(%rcx)
	je	.LBB0_12
.LBB0_11:
	movl	$1, 1040(%rcx)
	movl	$1, -112(%rsp)
	movl	-32(%rsp), %ebx
	testl	%ebp, %ebp
	movl	%edx, 24(%rsp)
	je	.LBB0_15
.LBB0_14:
	movl	$0, 1032(%rcx)
	movl	-24(%rsp), %r8d
	movl	-28(%rsp), %r12d
	testl	%ebp, %ebp
	je	.LBB0_18
.LBB0_17:
	movl	$0, 1016(%rcx)
	movl	$0, 1024(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_21
	jmp	.LBB0_22
.LBB0_9:
	movl	-128(%rsp), %esi
	movl	%esi, 1064(%rcx)
	testl	%ebp, %ebp
	movl	%r12d, 1056(%rcx)
	movl	%r8d, 1048(%rcx)
	jne	.LBB0_11
.LBB0_12:
	movl	-112(%rsp), %eax
	movl	%eax, 1040(%rcx)
	movl	-32(%rsp), %ebx
	testl	%ebp, %ebp
	movl	%edx, 24(%rsp)
	jne	.LBB0_14
.LBB0_15:
	movl	-64(%rsp), %eax
	movl	%eax, 1032(%rcx)
	movl	-24(%rsp), %r8d
	movl	-28(%rsp), %r12d
	testl	%ebp, %ebp
	jne	.LBB0_17
.LBB0_18:
	testl	%ebx, %ebx
	je	.LBB0_20
	movl	1024(%rcx), %eax
	movl	%eax, 1016(%rcx)
	movl	-8(%rsp), %eax
	movl	%eax, 1024(%rcx)
.LBB0_20:
	testl	%ebx, %ebx
	je	.LBB0_22
.LBB0_21:
	movl	%r11d, 1008(%rcx)
	movl	%r15d, 1000(%rcx)
.LBB0_22:
	testl	%ebp, %ebp
	je	.LBB0_24
	movl	$0, 992(%rcx)
	testl	%ebp, %ebp
	je	.LBB0_27
.LBB0_26:
	movl	$0, 984(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_30
	jmp	.LBB0_31
.LBB0_24:
	movl	-72(%rsp), %eax
	movl	%eax, 992(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_26
.LBB0_27:
	testl	%ebx, %ebx
	je	.LBB0_31
	movl	-4(%rsp), %eax
	movl	%eax, 984(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_31
.LBB0_30:
	movl	-16(%rsp), %eax
	movl	%eax, 976(%rcx)
	movl	96(%rsp), %eax
	movl	%eax, 968(%rcx)
.LBB0_31:
	testl	%ebp, %ebp
	je	.LBB0_33
	movl	$0, 960(%rcx)
	jmp	.LBB0_34
.LBB0_33:
	movl	88(%rsp), %eax
	movl	%eax, 960(%rcx)
.LBB0_34:
	movl	-40(%rsp), %r10d
	movl	-116(%rsp), %r9d
	movl	-48(%rsp), %r14d
	testl	%ebp, %ebp
	je	.LBB0_36
	movl	$0, 944(%rcx)
	movl	$0, 952(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_39
	jmp	.LBB0_40
.LBB0_36:
	testl	%ebx, %ebx
	je	.LBB0_40
	movl	952(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 944(%rcx)
	shrl	%eax
	movl	-20(%rsp), %edx
	addl	%edx, %edx
	orl	%eax, %edx
	movl	%edx, 952(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_40
.LBB0_39:
	movl	-68(%rsp), %eax
	movl	%eax, 936(%rcx)
	movl	928(%rcx), %eax
	movl	%eax, 920(%rcx)
	movl	-36(%rsp), %eax
	movl	%eax, 928(%rcx)
.LBB0_40:
	testl	%ebp, %ebp
	je	.LBB0_42
	movl	$0, 912(%rcx)
	movl	-44(%rsp), %r13d
	testl	%ebp, %ebp
	je	.LBB0_45
.LBB0_44:
	movl	$0, 896(%rcx)
	movl	$0, 904(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_48
	jmp	.LBB0_49
.LBB0_42:
	movl	-84(%rsp), %eax
	movl	%eax, 912(%rcx)
	movl	-44(%rsp), %r13d
	testl	%ebp, %ebp
	jne	.LBB0_44
.LBB0_45:
	testl	%ebx, %ebx
	je	.LBB0_49
	movl	904(%rcx), %eax
	movl	%eax, 896(%rcx)
	movl	(%rsp), %eax
	movl	%eax, 904(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_49
.LBB0_48:
	movl	116(%rsp), %edi
	movswl	%di, %eax
	movl	120(%rsp), %ebp
	movswl	%bp, %edx
	sarl	$16, %edi
	sarl	$16, %ebp
	movl	%edi, %esi
	imull	%ebp, %esi
	imull	%eax, %ebp
	imull	%edx, %eax
	subl	%esi, %eax
	imull	%edx, %edi
	addl	%edi, %ebp
	shrl	$15, %eax
	shrl	$15, %ebp
	movzwl	%ax, %eax
	movzwl	%bp, %edx
	movl	-120(%rsp), %ebp
	movl	%edx, 888(%rcx)
	movl	%eax, 880(%rcx)
	movl	148(%rsp), %eax
	movl	%eax, 872(%rcx)
	movl	-60(%rsp), %eax
	movl	%eax, 864(%rcx)
.LBB0_49:
	testl	%ebp, %ebp
	je	.LBB0_51
	movl	$0, 856(%rcx)
	testl	%ebp, %ebp
	je	.LBB0_54
.LBB0_53:
	movl	$0, 840(%rcx)
	movl	$0, 848(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_57
	jmp	.LBB0_58
.LBB0_51:
	movl	80(%rsp), %eax
	movl	%eax, 856(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_53
.LBB0_54:
	testl	%ebx, %ebx
	je	.LBB0_58
	movl	848(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 840(%rcx)
	shrl	%eax
	movl	4(%rsp), %edx
	shll	$3, %edx
	orl	%eax, %edx
	movl	%edx, 848(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_58
.LBB0_57:
	movl	-76(%rsp), %eax
	movl	%eax, 832(%rcx)
	movslq	828(%rcx), %rax
	movl	812(%rcx,%rax,4), %edx
	movl	%edx, 804(%rcx)
	movl	-80(%rsp), %edx
	movl	%edx, 812(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$2, %eax
	movl	$2, %edx
	cmovbl	%eax, %edx
	movl	%edx, 828(%rcx)
.LBB0_58:
	testl	%ebp, %ebp
	je	.LBB0_60
	movl	$0, 796(%rcx)
	testl	%ebp, %ebp
	je	.LBB0_63
.LBB0_62:
	movl	$0, 788(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_66
	jmp	.LBB0_67
.LBB0_60:
	movl	56(%rsp), %eax
	movl	%eax, 796(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_62
.LBB0_63:
	testl	%ebx, %ebx
	je	.LBB0_67
	movl	8(%rsp), %eax
	movl	%eax, 788(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_67
.LBB0_66:
	movl	20(%rsp), %eax
	movl	%eax, 780(%rcx)
	movl	72(%rsp), %eax
	movl	%eax, 772(%rcx)
.LBB0_67:
	testl	%ebp, %ebp
	je	.LBB0_69
	movl	$0, 764(%rcx)
	testl	%ebp, %ebp
	je	.LBB0_72
.LBB0_71:
	movl	$0, 748(%rcx)
	movl	$0, 756(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_75
	jmp	.LBB0_76
.LBB0_69:
	movl	-100(%rsp), %eax
	movl	%eax, 764(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_71
.LBB0_72:
	testl	%ebx, %ebx
	je	.LBB0_76
	movl	756(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 748(%rcx)
	shrl	%eax
	shll	$7, %r14d
	orl	%eax, %r14d
	movl	%r14d, 756(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_76
.LBB0_75:
	movl	64(%rsp), %eax
	movl	%eax, 740(%rcx)
	movslq	736(%rcx), %rax
	movl	704(%rcx,%rax,4), %edx
	movl	%edx, 696(%rcx)
	movl	%r9d, 704(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$6, %eax
	movl	$6, %edx
	cmovbl	%eax, %edx
	movl	%edx, 736(%rcx)
.LBB0_76:
	testl	%ebp, %ebp
	je	.LBB0_78
	movl	$0, 688(%rcx)
	testl	%ebp, %ebp
	je	.LBB0_81
.LBB0_80:
	movl	$0, 672(%rcx)
	movl	$0, 680(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_84
	jmp	.LBB0_85
.LBB0_78:
	movl	104(%rsp), %eax
	movl	%eax, 688(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_80
.LBB0_81:
	testl	%ebx, %ebx
	je	.LBB0_85
	movl	680(%rcx), %eax
	movl	%eax, 672(%rcx)
	movl	12(%rsp), %eax
	movl	%eax, 680(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_85
.LBB0_84:
	movswl	%r12w, %eax
	movswl	%r8w, %edx
	sarl	$16, %r12d
	sarl	$16, %r8d
	movl	%r12d, %edi
	imull	%r8d, %edi
	imull	%eax, %r8d
	imull	%edx, %eax
	subl	%edi, %eax
	imull	%edx, %r12d
	addl	%r12d, %r8d
	shrl	$15, %eax
	shrl	$15, %r8d
	movzwl	%ax, %eax
	movzwl	%r8w, %edx
	movl	%edx, 664(%rcx)
	movl	%eax, 656(%rcx)
	movl	152(%rsp), %eax
	movl	%eax, 648(%rcx)
	movl	-56(%rsp), %eax
	movl	%eax, 640(%rcx)
.LBB0_85:
	testl	%ebp, %ebp
	je	.LBB0_87
	movl	$0, 632(%rcx)
	movl	24(%rsp), %edi
	testl	%ebp, %ebp
	je	.LBB0_90
.LBB0_89:
	movl	$0, 616(%rcx)
	movl	$0, 624(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_93
	jmp	.LBB0_94
.LBB0_87:
	movl	-96(%rsp), %eax
	movl	%eax, 632(%rcx)
	movl	24(%rsp), %edi
	testl	%ebp, %ebp
	jne	.LBB0_89
.LBB0_90:
	testl	%ebx, %ebx
	je	.LBB0_94
	movl	624(%rcx), %eax
	movl	%eax, %edx
	andl	$1, %edx
	movl	%edx, 616(%rcx)
	shrl	%eax
	shll	$15, %r13d
	orl	%eax, %r13d
	movl	%r13d, 624(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_94
.LBB0_93:
	movl	-92(%rsp), %eax
	movl	%eax, 608(%rcx)
	movslq	604(%rcx), %rax
	movl	540(%rcx,%rax,4), %edx
	movl	%edx, 532(%rcx)
	movl	-88(%rsp), %edx
	movl	%edx, 540(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$14, %eax
	movl	$14, %edx
	cmovbl	%eax, %edx
	movl	%edx, 604(%rcx)
.LBB0_94:
	testl	%ebp, %ebp
	je	.LBB0_96
	movl	$0, 524(%rcx)
	movl	32(%rsp), %edx
	testl	%ebp, %ebp
	je	.LBB0_99
.LBB0_98:
	movl	$0, 516(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_102
	jmp	.LBB0_103
.LBB0_96:
	movl	108(%rsp), %eax
	movl	%eax, 524(%rcx)
	movl	32(%rsp), %edx
	testl	%ebp, %ebp
	jne	.LBB0_98
.LBB0_99:
	testl	%ebx, %ebx
	je	.LBB0_103
	movl	16(%rsp), %eax
	movl	%eax, 516(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_103
.LBB0_102:
	movl	%r10d, 508(%rcx)
	movl	48(%rsp), %eax
	movl	%eax, 500(%rcx)
.LBB0_103:
	testl	%ebp, %ebp
	je	.LBB0_105
	movl	$0, 492(%rcx)
	testl	%ebp, %ebp
	je	.LBB0_108
.LBB0_107:
	movl	$0, 476(%rcx)
	movl	$0, 484(%rcx)
	testl	%ebx, %ebx
	jne	.LBB0_111
	jmp	.LBB0_112
.LBB0_105:
	movl	112(%rsp), %eax
	movl	%eax, 492(%rcx)
	testl	%ebp, %ebp
	jne	.LBB0_107
.LBB0_108:
	testl	%ebx, %ebx
	je	.LBB0_112
	movl	484(%rcx), %eax
	shldl	$31, %eax, %edx
	andl	$1, %eax
	movl	%eax, 476(%rcx)
	movl	%edx, 484(%rcx)
	testl	%ebx, %ebx
	je	.LBB0_112
.LBB0_111:
	movl	124(%rsp), %eax
	movl	%eax, 468(%rcx)
	movslq	464(%rcx), %rax
	movl	336(%rcx,%rax,4), %edx
	movl	%edx, 328(%rcx)
	movl	40(%rsp), %edx
	movl	%edx, 336(%rcx,%rax,4)
	leal	-1(%rax), %eax
	cmpl	$30, %eax
	movl	$30, %edx
	cmovbl	%eax, %edx
	movl	%edx, 464(%rcx)
.LBB0_112:
	testl	%ebp, %ebp
	je	.LBB0_114
	movl	$0, 320(%rcx)
	jmp	.LBB0_115
.LBB0_114:
	movl	-52(%rsp), %eax
	movl	%eax, 320(%rcx)
.LBB0_115:
	movl	-112(%rsp), %ecx
	shrl	$2, %ecx
	notl	%ecx
	andl	$1, %ecx
	movq	168(%rsp), %rdx
	movq	40(%rdx), %rax
	movl	%ecx, (%rax)
	movq	48(%rdx), %rax
	movl	%edi, (%rax)
	movl	-128(%rsp), %ecx
	notl	%ecx
	andl	$1, %ecx
	movq	56(%rdx), %rax
	movl	%ecx, (%rax)
.LBB0_116:
	xorl	%eax, %eax
	addq	$192, %rsp
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
