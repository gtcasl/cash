function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f86ed028130 <.text>:
    7f86ed028130:	55                   	push   %rbp
    7f86ed028131:	48 8b ec             	mov    %rsp,%rbp
    7f86ed028134:	48 83 ec 70          	sub    $0x70,%rsp
    7f86ed028138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f86ed02813c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f86ed028141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f86ed028146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f86ed02814b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f86ed028150:	48 8b df             	mov    %rdi,%rbx
    7f86ed028153:	4c 8b 7b 08          	mov    0x8(%rbx),%r15
    7f86ed028157:	4c 8b 23             	mov    (%rbx),%r12
    7f86ed02815a:	45 8b 77 08          	mov    0x8(%r15),%r14d
    7f86ed02815e:	45 8b 6f 10          	mov    0x10(%r15),%r13d
    7f86ed028162:	49 8b 44 24 18       	mov    0x18(%r12),%rax
    7f86ed028167:	8b 00                	mov    (%rax),%eax
    7f86ed028169:	41 8b 4f 18          	mov    0x18(%r15),%ecx
    7f86ed02816d:	33 c8                	xor    %eax,%ecx
    7f86ed02816f:	23 c8                	and    %eax,%ecx
    7f86ed028171:	41 89 47 18          	mov    %eax,0x18(%r15)
    7f86ed028175:	85 c9                	test   %ecx,%ecx
    7f86ed028177:	0f 84 66 01 00 00    	je     0x7f86ed0282e3
    7f86ed02817d:	41 8b c6             	mov    %r14d,%eax
    7f86ed028180:	ff c0                	inc    %eax
    7f86ed028182:	83 e0 03             	and    $0x3,%eax
    7f86ed028185:	89 45 f8             	mov    %eax,-0x8(%rbp)
    7f86ed028188:	49 8b 44 24 20       	mov    0x20(%r12),%rax
    7f86ed02818d:	8b 00                	mov    (%rax),%eax
    7f86ed02818f:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f86ed028192:	49 8b 44 24 10       	mov    0x10(%r12),%rax
    7f86ed028197:	8b 00                	mov    (%rax),%eax
    7f86ed028199:	45 3b ee             	cmp    %r14d,%r13d
    7f86ed02819c:	0f 94 c1             	sete   %cl
    7f86ed02819f:	0f b6 c9             	movzbl %cl,%ecx
    7f86ed0281a2:	85 c9                	test   %ecx,%ecx
    7f86ed0281a4:	0f 94 c1             	sete   %cl
    7f86ed0281a7:	0f b6 c9             	movzbl %cl,%ecx
    7f86ed0281aa:	23 c1                	and    %ecx,%eax
    7f86ed0281ac:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f86ed0281af:	41 8b c5             	mov    %r13d,%eax
    7f86ed0281b2:	ff c0                	inc    %eax
    7f86ed0281b4:	83 e0 03             	and    $0x3,%eax
    7f86ed0281b7:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f86ed0281ba:	49 8b 44 24 08       	mov    0x8(%r12),%rax
    7f86ed0281bf:	8b 00                	mov    (%rax),%eax
    7f86ed0281c1:	41 8b cd             	mov    %r13d,%ecx
    7f86ed0281c4:	83 e1 01             	and    $0x1,%ecx
    7f86ed0281c7:	41 8b d6             	mov    %r14d,%edx
    7f86ed0281ca:	83 e2 01             	and    $0x1,%edx
    7f86ed0281cd:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7f86ed0281d0:	3b ca                	cmp    %edx,%ecx
    7f86ed0281d2:	0f 94 c1             	sete   %cl
    7f86ed0281d5:	0f b6 c9             	movzbl %cl,%ecx
    7f86ed0281d8:	41 8b d5             	mov    %r13d,%edx
    7f86ed0281db:	d1 ea                	shr    %edx
    7f86ed0281dd:	83 e2 01             	and    $0x1,%edx
    7f86ed0281e0:	41 8b f6             	mov    %r14d,%esi
    7f86ed0281e3:	d1 ee                	shr    %esi
    7f86ed0281e5:	83 e6 01             	and    $0x1,%esi
    7f86ed0281e8:	3b d6                	cmp    %esi,%edx
    7f86ed0281ea:	0f 95 c2             	setne  %dl
    7f86ed0281ed:	0f b6 d2             	movzbl %dl,%edx
    7f86ed0281f0:	23 ca                	and    %edx,%ecx
    7f86ed0281f2:	85 c9                	test   %ecx,%ecx
    7f86ed0281f4:	0f 94 c1             	sete   %cl
    7f86ed0281f7:	0f b6 c9             	movzbl %cl,%ecx
    7f86ed0281fa:	23 c1                	and    %ecx,%eax
    7f86ed0281fc:	49 8b 0c 24          	mov    (%r12),%rcx
    7f86ed028200:	8b 09                	mov    (%rcx),%ecx
    7f86ed028202:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7f86ed028205:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f86ed028208:	85 c0                	test   %eax,%eax
    7f86ed02820a:	0f 84 2b 00 00 00    	je     0x7f86ed02823b
    7f86ed028210:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f86ed028213:	03 c0                	add    %eax,%eax
    7f86ed028215:	41 8b 0f             	mov    (%r15),%ecx
    7f86ed028218:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7f86ed02821b:	ba 03 00 00 00       	mov    $0x3,%edx
    7f86ed028220:	8b c8                	mov    %eax,%ecx
    7f86ed028222:	d3 e2                	shl    %cl,%edx
    7f86ed028224:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f86ed028227:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f86ed02822a:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f86ed02822d:	d3 e0                	shl    %cl,%eax
    7f86ed02822f:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f86ed028232:	33 c1                	xor    %ecx,%eax
    7f86ed028234:	23 d0                	and    %eax,%edx
    7f86ed028236:	33 ca                	xor    %edx,%ecx
    7f86ed028238:	41 89 0f             	mov    %ecx,(%r15)
    7f86ed02823b:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f86ed02823e:	85 c0                	test   %eax,%eax
    7f86ed028240:	0f 84 1b 00 00 00    	je     0x7f86ed028261
    7f86ed028246:	41 c7 47 10 00 00 00 	movl   $0x0,0x10(%r15)
    7f86ed02824d:	00 
    7f86ed02824e:	45 33 ed             	xor    %r13d,%r13d
    7f86ed028251:	41 c7 47 08 00 00 00 	movl   $0x0,0x8(%r15)
    7f86ed028258:	00 
    7f86ed028259:	45 33 f6             	xor    %r14d,%r14d
    7f86ed02825c:	e9 2a 00 00 00       	jmpq   0x7f86ed02828b
    7f86ed028261:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f86ed028264:	85 c0                	test   %eax,%eax
    7f86ed028266:	0f 84 0a 00 00 00    	je     0x7f86ed028276
    7f86ed02826c:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f86ed02826f:	41 89 47 10          	mov    %eax,0x10(%r15)
    7f86ed028273:	4c 8b e8             	mov    %rax,%r13
    7f86ed028276:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7f86ed028279:	85 c0                	test   %eax,%eax
    7f86ed02827b:	0f 84 0a 00 00 00    	je     0x7f86ed02828b
    7f86ed028281:	8b 45 f8             	mov    -0x8(%rbp),%eax
    7f86ed028284:	41 89 47 08          	mov    %eax,0x8(%r15)
    7f86ed028288:	4c 8b f0             	mov    %rax,%r14
    7f86ed02828b:	41 8b c6             	mov    %r14d,%eax
    7f86ed02828e:	83 e0 01             	and    $0x1,%eax
    7f86ed028291:	8b c8                	mov    %eax,%ecx
    7f86ed028293:	03 c9                	add    %ecx,%ecx
    7f86ed028295:	41 8b 17             	mov    (%r15),%edx
    7f86ed028298:	d3 ea                	shr    %cl,%edx
    7f86ed02829a:	83 e2 03             	and    $0x3,%edx
    7f86ed02829d:	49 8b 4c 24 28       	mov    0x28(%r12),%rcx
    7f86ed0282a2:	89 11                	mov    %edx,(%rcx)
    7f86ed0282a4:	45 3b ee             	cmp    %r14d,%r13d
    7f86ed0282a7:	0f 94 c1             	sete   %cl
    7f86ed0282aa:	0f b6 c9             	movzbl %cl,%ecx
    7f86ed0282ad:	49 8b 54 24 30       	mov    0x30(%r12),%rdx
    7f86ed0282b2:	89 0a                	mov    %ecx,(%rdx)
    7f86ed0282b4:	41 8b cd             	mov    %r13d,%ecx
    7f86ed0282b7:	83 e1 01             	and    $0x1,%ecx
    7f86ed0282ba:	3b c8                	cmp    %eax,%ecx
    7f86ed0282bc:	0f 94 c0             	sete   %al
    7f86ed0282bf:	0f b6 c0             	movzbl %al,%eax
    7f86ed0282c2:	41 8b cd             	mov    %r13d,%ecx
    7f86ed0282c5:	d1 e9                	shr    %ecx
    7f86ed0282c7:	83 e1 01             	and    $0x1,%ecx
    7f86ed0282ca:	41 8b d6             	mov    %r14d,%edx
    7f86ed0282cd:	d1 ea                	shr    %edx
    7f86ed0282cf:	83 e2 01             	and    $0x1,%edx
    7f86ed0282d2:	3b ca                	cmp    %edx,%ecx
    7f86ed0282d4:	0f 95 c1             	setne  %cl
    7f86ed0282d7:	0f b6 c9             	movzbl %cl,%ecx
    7f86ed0282da:	23 c1                	and    %ecx,%eax
    7f86ed0282dc:	49 8b 4c 24 38       	mov    0x38(%r12),%rcx
    7f86ed0282e1:	89 01                	mov    %eax,(%rcx)
    7f86ed0282e3:	33 c0                	xor    %eax,%eax
    7f86ed0282e5:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f86ed0282e9:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f86ed0282ee:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f86ed0282f3:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f86ed0282f8:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f86ed0282fd:	48 8b e5             	mov    %rbp,%rsp
    7f86ed028300:	5d                   	pop    %rbp
    7f86ed028301:	c3                   	retq   

end

