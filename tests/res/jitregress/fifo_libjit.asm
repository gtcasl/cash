function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f364d636130 <.text>:
    7f364d636130:	55                   	push   %rbp
    7f364d636131:	48 8b ec             	mov    %rsp,%rbp
    7f364d636134:	48 83 ec 70          	sub    $0x70,%rsp
    7f364d636138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f364d63613c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f364d636141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f364d636146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f364d63614b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f364d636150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f364d636154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f364d636158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f364d63615c:	4c 8b 20             	mov    (%rax),%r12
    7f364d63615f:	45 8b 77 08          	mov    0x8(%r15),%r14d
    7f364d636163:	45 8b 6f 10          	mov    0x10(%r15),%r13d
    7f364d636167:	49 8b 44 24 18       	mov    0x18(%r12),%rax
    7f364d63616c:	8b 00                	mov    (%rax),%eax
    7f364d63616e:	41 8b 4f 18          	mov    0x18(%r15),%ecx
    7f364d636172:	33 c8                	xor    %eax,%ecx
    7f364d636174:	23 c8                	and    %eax,%ecx
    7f364d636176:	41 89 47 18          	mov    %eax,0x18(%r15)
    7f364d63617a:	85 c9                	test   %ecx,%ecx
    7f364d63617c:	0f 84 66 01 00 00    	je     0x7f364d6362e8
    7f364d636182:	49 8b 44 24 10       	mov    0x10(%r12),%rax
    7f364d636187:	8b 00                	mov    (%rax),%eax
    7f364d636189:	45 3b ee             	cmp    %r14d,%r13d
    7f364d63618c:	0f 94 c1             	sete   %cl
    7f364d63618f:	0f b6 c9             	movzbl %cl,%ecx
    7f364d636192:	85 c9                	test   %ecx,%ecx
    7f364d636194:	0f 94 c1             	sete   %cl
    7f364d636197:	0f b6 c9             	movzbl %cl,%ecx
    7f364d63619a:	23 c1                	and    %ecx,%eax
    7f364d63619c:	41 8b ce             	mov    %r14d,%ecx
    7f364d63619f:	ff c1                	inc    %ecx
    7f364d6361a1:	83 e1 03             	and    $0x3,%ecx
    7f364d6361a4:	48 8b d9             	mov    %rcx,%rbx
    7f364d6361a7:	85 c0                	test   %eax,%eax
    7f364d6361a9:	0f 85 03 00 00 00    	jne    0x7f364d6361b2
    7f364d6361af:	41 8b de             	mov    %r14d,%ebx
    7f364d6361b2:	49 8b 44 24 20       	mov    0x20(%r12),%rax
    7f364d6361b7:	8b 00                	mov    (%rax),%eax
    7f364d6361b9:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f364d6361bc:	49 8b 44 24 08       	mov    0x8(%r12),%rax
    7f364d6361c1:	8b 00                	mov    (%rax),%eax
    7f364d6361c3:	41 8b cd             	mov    %r13d,%ecx
    7f364d6361c6:	83 e1 01             	and    $0x1,%ecx
    7f364d6361c9:	41 8b d6             	mov    %r14d,%edx
    7f364d6361cc:	83 e2 01             	and    $0x1,%edx
    7f364d6361cf:	89 4d e8             	mov    %ecx,-0x18(%rbp)
    7f364d6361d2:	3b ca                	cmp    %edx,%ecx
    7f364d6361d4:	0f 94 c1             	sete   %cl
    7f364d6361d7:	0f b6 c9             	movzbl %cl,%ecx
    7f364d6361da:	41 8b d5             	mov    %r13d,%edx
    7f364d6361dd:	d1 ea                	shr    %edx
    7f364d6361df:	83 e2 01             	and    $0x1,%edx
    7f364d6361e2:	41 8b f6             	mov    %r14d,%esi
    7f364d6361e5:	d1 ee                	shr    %esi
    7f364d6361e7:	83 e6 01             	and    $0x1,%esi
    7f364d6361ea:	3b d6                	cmp    %esi,%edx
    7f364d6361ec:	0f 95 c2             	setne  %dl
    7f364d6361ef:	0f b6 d2             	movzbl %dl,%edx
    7f364d6361f2:	23 ca                	and    %edx,%ecx
    7f364d6361f4:	85 c9                	test   %ecx,%ecx
    7f364d6361f6:	0f 94 c1             	sete   %cl
    7f364d6361f9:	0f b6 c9             	movzbl %cl,%ecx
    7f364d6361fc:	23 c1                	and    %ecx,%eax
    7f364d6361fe:	41 8b cd             	mov    %r13d,%ecx
    7f364d636201:	ff c1                	inc    %ecx
    7f364d636203:	83 e1 03             	and    $0x3,%ecx
    7f364d636206:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7f364d636209:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7f364d63620c:	85 c0                	test   %eax,%eax
    7f364d63620e:	0f 85 06 00 00 00    	jne    0x7f364d63621a
    7f364d636214:	41 8b c5             	mov    %r13d,%eax
    7f364d636217:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f364d63621a:	49 8b 04 24          	mov    (%r12),%rax
    7f364d63621e:	8b 00                	mov    (%rax),%eax
    7f364d636220:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f364d636223:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f364d636226:	85 c0                	test   %eax,%eax
    7f364d636228:	0f 84 2b 00 00 00    	je     0x7f364d636259
    7f364d63622e:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7f364d636231:	03 c0                	add    %eax,%eax
    7f364d636233:	41 8b 0f             	mov    (%r15),%ecx
    7f364d636236:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7f364d636239:	ba 03 00 00 00       	mov    $0x3,%edx
    7f364d63623e:	8b c8                	mov    %eax,%ecx
    7f364d636240:	d3 e2                	shl    %cl,%edx
    7f364d636242:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f364d636245:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f364d636248:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f364d63624b:	d3 e0                	shl    %cl,%eax
    7f364d63624d:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7f364d636250:	33 c1                	xor    %ecx,%eax
    7f364d636252:	23 d0                	and    %eax,%edx
    7f364d636254:	33 ca                	xor    %edx,%ecx
    7f364d636256:	41 89 0f             	mov    %ecx,(%r15)
    7f364d636259:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f364d63625c:	85 c0                	test   %eax,%eax
    7f364d63625e:	0f 84 1b 00 00 00    	je     0x7f364d63627f
    7f364d636264:	41 c7 47 10 00 00 00 	movl   $0x0,0x10(%r15)
    7f364d63626b:	00 
    7f364d63626c:	45 33 ed             	xor    %r13d,%r13d
    7f364d63626f:	41 c7 47 08 00 00 00 	movl   $0x0,0x8(%r15)
    7f364d636276:	00 
    7f364d636277:	45 33 f6             	xor    %r14d,%r14d
    7f364d63627a:	e9 11 00 00 00       	jmpq   0x7f364d636290
    7f364d63627f:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f364d636282:	41 89 47 10          	mov    %eax,0x10(%r15)
    7f364d636286:	4c 8b e8             	mov    %rax,%r13
    7f364d636289:	41 89 5f 08          	mov    %ebx,0x8(%r15)
    7f364d63628d:	44 8b f3             	mov    %ebx,%r14d
    7f364d636290:	41 8b c6             	mov    %r14d,%eax
    7f364d636293:	83 e0 01             	and    $0x1,%eax
    7f364d636296:	8b c8                	mov    %eax,%ecx
    7f364d636298:	03 c9                	add    %ecx,%ecx
    7f364d63629a:	41 8b 17             	mov    (%r15),%edx
    7f364d63629d:	d3 ea                	shr    %cl,%edx
    7f364d63629f:	83 e2 03             	and    $0x3,%edx
    7f364d6362a2:	49 8b 4c 24 28       	mov    0x28(%r12),%rcx
    7f364d6362a7:	89 11                	mov    %edx,(%rcx)
    7f364d6362a9:	45 3b ee             	cmp    %r14d,%r13d
    7f364d6362ac:	0f 94 c1             	sete   %cl
    7f364d6362af:	0f b6 c9             	movzbl %cl,%ecx
    7f364d6362b2:	49 8b 54 24 30       	mov    0x30(%r12),%rdx
    7f364d6362b7:	89 0a                	mov    %ecx,(%rdx)
    7f364d6362b9:	41 8b cd             	mov    %r13d,%ecx
    7f364d6362bc:	83 e1 01             	and    $0x1,%ecx
    7f364d6362bf:	3b c8                	cmp    %eax,%ecx
    7f364d6362c1:	0f 94 c0             	sete   %al
    7f364d6362c4:	0f b6 c0             	movzbl %al,%eax
    7f364d6362c7:	41 8b cd             	mov    %r13d,%ecx
    7f364d6362ca:	d1 e9                	shr    %ecx
    7f364d6362cc:	83 e1 01             	and    $0x1,%ecx
    7f364d6362cf:	41 8b d6             	mov    %r14d,%edx
    7f364d6362d2:	d1 ea                	shr    %edx
    7f364d6362d4:	83 e2 01             	and    $0x1,%edx
    7f364d6362d7:	3b ca                	cmp    %edx,%ecx
    7f364d6362d9:	0f 95 c1             	setne  %cl
    7f364d6362dc:	0f b6 c9             	movzbl %cl,%ecx
    7f364d6362df:	23 c1                	and    %ecx,%eax
    7f364d6362e1:	49 8b 4c 24 38       	mov    0x38(%r12),%rcx
    7f364d6362e6:	89 01                	mov    %eax,(%rcx)
    7f364d6362e8:	33 c0                	xor    %eax,%eax
    7f364d6362ea:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f364d6362ee:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f364d6362f3:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f364d6362f8:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f364d6362fd:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f364d636302:	48 8b e5             	mov    %rbp,%rsp
    7f364d636305:	5d                   	pop    %rbp
    7f364d636306:	c3                   	retq   

end

