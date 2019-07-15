function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fa49f17012d <.text>:
    7fa49f17012d:	55                   	push   %rbp
    7fa49f17012e:	48 8b ec             	mov    %rsp,%rbp
    7fa49f170131:	48 81 ec 50 02 00 00 	sub    $0x250,%rsp
    7fa49f170138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fa49f17013c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fa49f170141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fa49f170146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fa49f17014b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fa49f170150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fa49f170154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fa49f170158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fa49f17015c:	4c 8b 30             	mov    (%rax),%r14
    7fa49f17015f:	41 8b 07             	mov    (%r15),%eax
    7fa49f170162:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fa49f170165:	41 8b 47 4c          	mov    0x4c(%r15),%eax
    7fa49f170169:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fa49f17016c:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7fa49f170173:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fa49f170176:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7fa49f17017d:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fa49f170180:	45 8b af a8 00 00 00 	mov    0xa8(%r15),%r13d
    7fa49f170187:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7fa49f17018e:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fa49f170191:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7fa49f170198:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fa49f17019b:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7fa49f1701a2:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fa49f1701a5:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7fa49f1701ac:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fa49f1701af:	41 8b 87 d0 00 00 00 	mov    0xd0(%r15),%eax
    7fa49f1701b6:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fa49f1701b9:	41 8b 87 d8 00 00 00 	mov    0xd8(%r15),%eax
    7fa49f1701c0:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fa49f1701c3:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7fa49f1701ca:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fa49f1701cd:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7fa49f1701d4:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fa49f1701d7:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7fa49f1701de:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fa49f1701e1:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7fa49f1701e8:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fa49f1701eb:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7fa49f1701f2:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fa49f1701f5:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7fa49f1701fc:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fa49f170202:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7fa49f170209:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fa49f17020f:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7fa49f170216:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fa49f17021c:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7fa49f170223:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7fa49f170229:	49 8b 46 18          	mov    0x18(%r14),%rax
    7fa49f17022d:	8b 00                	mov    (%rax),%eax
    7fa49f17022f:	41 8b 8f 30 01 00 00 	mov    0x130(%r15),%ecx
    7fa49f170236:	33 c8                	xor    %eax,%ecx
    7fa49f170238:	23 c8                	and    %eax,%ecx
    7fa49f17023a:	41 89 87 30 01 00 00 	mov    %eax,0x130(%r15)
    7fa49f170241:	85 c9                	test   %ecx,%ecx
    7fa49f170243:	0f 84 ac 07 00 00    	je     0x7fa49f1709f5
    7fa49f170249:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fa49f17024c:	81 f9 00 10 00 00    	cmp    $0x1000,%ecx
    7fa49f170252:	0f 92 c0             	setb   %al
    7fa49f170255:	0f b6 c0             	movzbl %al,%eax
    7fa49f170258:	85 c0                	test   %eax,%eax
    7fa49f17025a:	0f 94 c0             	sete   %al
    7fa49f17025d:	0f b6 c0             	movzbl %al,%eax
    7fa49f170260:	85 c0                	test   %eax,%eax
    7fa49f170262:	0f 94 c0             	sete   %al
    7fa49f170265:	0f b6 c0             	movzbl %al,%eax
    7fa49f170268:	8b 55 88             	mov    -0x78(%rbp),%edx
    7fa49f17026b:	83 e2 01             	and    $0x1,%edx
    7fa49f17026e:	85 d2                	test   %edx,%edx
    7fa49f170270:	0f 94 c2             	sete   %dl
    7fa49f170273:	0f b6 d2             	movzbl %dl,%edx
    7fa49f170276:	89 95 58 ff ff ff    	mov    %edx,-0xa8(%rbp)
    7fa49f17027c:	85 d2                	test   %edx,%edx
    7fa49f17027e:	0f 94 c2             	sete   %dl
    7fa49f170281:	0f b6 d2             	movzbl %dl,%edx
    7fa49f170284:	23 c2                	and    %edx,%eax
    7fa49f170286:	85 c0                	test   %eax,%eax
    7fa49f170288:	0f 94 c0             	sete   %al
    7fa49f17028b:	0f b6 c0             	movzbl %al,%eax
    7fa49f17028e:	81 f9 87 00 00 00    	cmp    $0x87,%ecx
    7fa49f170294:	0f 93 c2             	setae  %dl
    7fa49f170297:	0f b6 d2             	movzbl %dl,%edx
    7fa49f17029a:	8b 75 98             	mov    -0x68(%rbp),%esi
    7fa49f17029d:	85 f6                	test   %esi,%esi
    7fa49f17029f:	40 0f 94 c6          	sete   %sil
    7fa49f1702a3:	40 0f b6 f6          	movzbl %sil,%esi
    7fa49f1702a7:	23 d6                	and    %esi,%edx
    7fa49f1702a9:	23 d0                	and    %eax,%edx
    7fa49f1702ab:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7fa49f1702b1:	c1 ee 02             	shr    $0x2,%esi
    7fa49f1702b4:	83 e6 01             	and    $0x1,%esi
    7fa49f1702b7:	85 f6                	test   %esi,%esi
    7fa49f1702b9:	40 0f 94 c6          	sete   %sil
    7fa49f1702bd:	40 0f b6 f6          	movzbl %sil,%esi
    7fa49f1702c1:	89 b5 50 ff ff ff    	mov    %esi,-0xb0(%rbp)
    7fa49f1702c7:	85 f6                	test   %esi,%esi
    7fa49f1702c9:	40 0f 94 c6          	sete   %sil
    7fa49f1702cd:	40 0f b6 f6          	movzbl %sil,%esi
    7fa49f1702d1:	89 95 48 ff ff ff    	mov    %edx,-0xb8(%rbp)
    7fa49f1702d7:	23 d6                	and    %esi,%edx
    7fa49f1702d9:	85 d2                	test   %edx,%edx
    7fa49f1702db:	0f 94 c2             	sete   %dl
    7fa49f1702de:	0f b6 d2             	movzbl %dl,%edx
    7fa49f1702e1:	89 95 40 ff ff ff    	mov    %edx,-0xc0(%rbp)
    7fa49f1702e7:	23 c2                	and    %edx,%eax
    7fa49f1702e9:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fa49f1702ef:	81 f9 fe ff ff ff    	cmp    $0xfffffffe,%ecx
    7fa49f1702f5:	0f 93 c0             	setae  %al
    7fa49f1702f8:	0f b6 c0             	movzbl %al,%eax
    7fa49f1702fb:	81 e9 fe ff ff ff    	sub    $0xfffffffe,%ecx
    7fa49f170301:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7fa49f170307:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fa49f17030a:	ff c1                	inc    %ecx
    7fa49f17030c:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7fa49f170312:	85 c0                	test   %eax,%eax
    7fa49f170314:	0f 85 0c 00 00 00    	jne    0x7fa49f170326
    7fa49f17031a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fa49f170320:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fa49f170326:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fa49f17032c:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fa49f170332:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fa49f170338:	85 c0                	test   %eax,%eax
    7fa49f17033a:	0f 85 09 00 00 00    	jne    0x7fa49f170349
    7fa49f170340:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fa49f170343:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fa49f170349:	49 8b 46 20          	mov    0x20(%r14),%rax
    7fa49f17034d:	8b 00                	mov    (%rax),%eax
    7fa49f17034f:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fa49f170355:	83 c8 00             	or     $0x0,%eax
    7fa49f170358:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fa49f17035e:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fa49f170361:	3d 04 10 00 00       	cmp    $0x1004,%eax
    7fa49f170366:	0f 93 c0             	setae  %al
    7fa49f170369:	0f b6 c0             	movzbl %al,%eax
    7fa49f17036c:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fa49f170372:	41 8b c5             	mov    %r13d,%eax
    7fa49f170375:	03 45 a8             	add    -0x58(%rbp),%eax
    7fa49f170378:	25 ff 01 00 00       	and    $0x1ff,%eax
    7fa49f17037d:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fa49f170380:	d1 e1                	shl    %ecx
    7fa49f170382:	89 8d 00 ff ff ff    	mov    %ecx,-0x100(%rbp)
    7fa49f170388:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fa49f17038e:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fa49f170394:	03 c1                	add    %ecx,%eax
    7fa49f170396:	25 ff 03 00 00       	and    $0x3ff,%eax
    7fa49f17039b:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fa49f17039e:	03 4d b8             	add    -0x48(%rbp),%ecx
    7fa49f1703a1:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fa49f1703a7:	8b 55 d0             	mov    -0x30(%rbp),%edx
    7fa49f1703aa:	d1 e2                	shl    %edx
    7fa49f1703ac:	89 95 f0 fe ff ff    	mov    %edx,-0x110(%rbp)
    7fa49f1703b2:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7fa49f1703b8:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fa49f1703be:	03 ca                	add    %edx,%ecx
    7fa49f1703c0:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fa49f1703c6:	3b c1                	cmp    %ecx,%eax
    7fa49f1703c8:	0f 97 c2             	seta   %dl
    7fa49f1703cb:	0f b6 d2             	movzbl %dl,%edx
    7fa49f1703ce:	8b f0                	mov    %eax,%esi
    7fa49f1703d0:	2b f1                	sub    %ecx,%esi
    7fa49f1703d2:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7fa49f1703d8:	89 b5 e0 fe ff ff    	mov    %esi,-0x120(%rbp)
    7fa49f1703de:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fa49f1703e4:	2b c8                	sub    %eax,%ecx
    7fa49f1703e6:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fa49f1703ec:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7fa49f1703f2:	85 d2                	test   %edx,%edx
    7fa49f1703f4:	0f 85 0c 00 00 00    	jne    0x7fa49f170406
    7fa49f1703fa:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fa49f170400:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fa49f170406:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7fa49f170409:	03 45 a8             	add    -0x58(%rbp),%eax
    7fa49f17040c:	25 ff 01 00 00       	and    $0x1ff,%eax
    7fa49f170411:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7fa49f170414:	d1 e1                	shl    %ecx
    7fa49f170416:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fa49f17041c:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fa49f170422:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fa49f170428:	03 c1                	add    %ecx,%eax
    7fa49f17042a:	25 ff 03 00 00       	and    $0x3ff,%eax
    7fa49f17042f:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fa49f170432:	41 03 cd             	add    %r13d,%ecx
    7fa49f170435:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fa49f17043b:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7fa49f17043e:	d1 e2                	shl    %edx
    7fa49f170440:	89 95 b8 fe ff ff    	mov    %edx,-0x148(%rbp)
    7fa49f170446:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7fa49f17044c:	89 8d b0 fe ff ff    	mov    %ecx,-0x150(%rbp)
    7fa49f170452:	03 ca                	add    %edx,%ecx
    7fa49f170454:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fa49f17045a:	3b c1                	cmp    %ecx,%eax
    7fa49f17045c:	0f 97 c2             	seta   %dl
    7fa49f17045f:	0f b6 d2             	movzbl %dl,%edx
    7fa49f170462:	8b f0                	mov    %eax,%esi
    7fa49f170464:	2b f1                	sub    %ecx,%esi
    7fa49f170466:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7fa49f17046c:	89 b5 a8 fe ff ff    	mov    %esi,-0x158(%rbp)
    7fa49f170472:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fa49f170478:	2b c8                	sub    %eax,%ecx
    7fa49f17047a:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fa49f170480:	89 8d 98 fe ff ff    	mov    %ecx,-0x168(%rbp)
    7fa49f170486:	85 d2                	test   %edx,%edx
    7fa49f170488:	0f 85 0c 00 00 00    	jne    0x7fa49f17049a
    7fa49f17048e:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fa49f170494:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fa49f17049a:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fa49f1704a0:	03 85 a8 fe ff ff    	add    -0x158(%rbp),%eax
    7fa49f1704a6:	25 ff 07 00 00       	and    $0x7ff,%eax
    7fa49f1704ab:	3d ff 00 00 00       	cmp    $0xff,%eax
    7fa49f1704b0:	0f 92 c1             	setb   %cl
    7fa49f1704b3:	0f b6 c9             	movzbl %cl,%ecx
    7fa49f1704b6:	25 ff 00 00 00       	and    $0xff,%eax
    7fa49f1704bb:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fa49f1704c1:	85 c9                	test   %ecx,%ecx
    7fa49f1704c3:	0f 85 0a 00 00 00    	jne    0x7fa49f1704d3
    7fa49f1704c9:	c7 85 90 fe ff ff ff 	movl   $0xff,-0x170(%rbp)
    7fa49f1704d0:	00 00 00 
    7fa49f1704d3:	49 8b 46 08          	mov    0x8(%r14),%rax
    7fa49f1704d7:	8b 00                	mov    (%rax),%eax
    7fa49f1704d9:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7fa49f1704dc:	c1 e9 02             	shr    $0x2,%ecx
    7fa49f1704df:	83 e1 01             	and    $0x1,%ecx
    7fa49f1704e2:	85 c9                	test   %ecx,%ecx
    7fa49f1704e4:	0f 94 c1             	sete   %cl
    7fa49f1704e7:	0f b6 c9             	movzbl %cl,%ecx
    7fa49f1704ea:	23 c1                	and    %ecx,%eax
    7fa49f1704ec:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7fa49f1704f2:	23 8d 58 ff ff ff    	and    -0xa8(%rbp),%ecx
    7fa49f1704f8:	85 c9                	test   %ecx,%ecx
    7fa49f1704fa:	0f 94 c2             	sete   %dl
    7fa49f1704fd:	0f b6 d2             	movzbl %dl,%edx
    7fa49f170500:	89 95 88 fe ff ff    	mov    %edx,-0x178(%rbp)
    7fa49f170506:	23 d0                	and    %eax,%edx
    7fa49f170508:	8b 75 88             	mov    -0x78(%rbp),%esi
    7fa49f17050b:	83 e6 03             	and    $0x3,%esi
    7fa49f17050e:	d1 e6                	shl    %esi
    7fa49f170510:	89 b5 80 fe ff ff    	mov    %esi,-0x180(%rbp)
    7fa49f170516:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fa49f17051c:	85 c0                	test   %eax,%eax
    7fa49f17051e:	0f 94 c0             	sete   %al
    7fa49f170521:	0f b6 c0             	movzbl %al,%eax
    7fa49f170524:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7fa49f17052a:	23 c8                	and    %eax,%ecx
    7fa49f17052c:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7fa49f170532:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fa49f170535:	d1 e8                	shr    %eax
    7fa49f170537:	83 e0 03             	and    $0x3,%eax
    7fa49f17053a:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fa49f170540:	85 d2                	test   %edx,%edx
    7fa49f170542:	0f 85 16 00 00 00    	jne    0x7fa49f17055e
    7fa49f170548:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fa49f17054e:	85 c0                	test   %eax,%eax
    7fa49f170550:	0f 85 13 00 00 00    	jne    0x7fa49f170569
    7fa49f170556:	8b 5d 88             	mov    -0x78(%rbp),%ebx
    7fa49f170559:	e9 11 00 00 00       	jmpq   0x7fa49f17056f
    7fa49f17055e:	8b 9d 80 fe ff ff    	mov    -0x180(%rbp),%ebx
    7fa49f170564:	e9 06 00 00 00       	jmpq   0x7fa49f17056f
    7fa49f170569:	8b 9d 60 fe ff ff    	mov    -0x1a0(%rbp),%ebx
    7fa49f17056f:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fa49f170572:	83 e0 01             	and    $0x1,%eax
    7fa49f170575:	8b 8d 78 fe ff ff    	mov    -0x188(%rbp),%ecx
    7fa49f17057b:	23 c1                	and    %ecx,%eax
    7fa49f17057d:	8b 8d 70 fe ff ff    	mov    -0x190(%rbp),%ecx
    7fa49f170583:	0b c1                	or     %ecx,%eax
    7fa49f170585:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7fa49f17058b:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fa49f17058e:	d1 e8                	shr    %eax
    7fa49f170590:	83 e0 01             	and    $0x1,%eax
    7fa49f170593:	89 85 50 fe ff ff    	mov    %eax,-0x1b0(%rbp)
    7fa49f170599:	8b 8d 88 fe ff ff    	mov    -0x178(%rbp),%ecx
    7fa49f17059f:	0b c1                	or     %ecx,%eax
    7fa49f1705a1:	49 8b 0e             	mov    (%r14),%rcx
    7fa49f1705a4:	8b 09                	mov    (%rcx),%ecx
    7fa49f1705a6:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7fa49f1705ac:	89 8d 40 fe ff ff    	mov    %ecx,-0x1c0(%rbp)
    7fa49f1705b2:	85 c0                	test   %eax,%eax
    7fa49f1705b4:	0f 85 0c 00 00 00    	jne    0x7fa49f1705c6
    7fa49f1705ba:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fa49f1705c0:	89 85 40 fe ff ff    	mov    %eax,-0x1c0(%rbp)
    7fa49f1705c6:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fa49f1705cc:	89 85 38 fe ff ff    	mov    %eax,-0x1c8(%rbp)
    7fa49f1705d2:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fa49f1705d8:	85 c0                	test   %eax,%eax
    7fa49f1705da:	0f 85 09 00 00 00    	jne    0x7fa49f1705e9
    7fa49f1705e0:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fa49f1705e3:	89 85 38 fe ff ff    	mov    %eax,-0x1c8(%rbp)
    7fa49f1705e9:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7fa49f1705ef:	23 85 50 fe ff ff    	and    -0x1b0(%rbp),%eax
    7fa49f1705f5:	8b 8d 70 fe ff ff    	mov    -0x190(%rbp),%ecx
    7fa49f1705fb:	0b c1                	or     %ecx,%eax
    7fa49f1705fd:	8b 8d 48 fe ff ff    	mov    -0x1b8(%rbp),%ecx
    7fa49f170603:	89 8d 30 fe ff ff    	mov    %ecx,-0x1d0(%rbp)
    7fa49f170609:	85 c0                	test   %eax,%eax
    7fa49f17060b:	0f 85 0c 00 00 00    	jne    0x7fa49f17061d
    7fa49f170611:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fa49f170617:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fa49f17061d:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fa49f170623:	23 85 50 ff ff ff    	and    -0xb0(%rbp),%eax
    7fa49f170629:	49 8b 4e 10          	mov    0x10(%r14),%rcx
    7fa49f17062d:	8b 09                	mov    (%rcx),%ecx
    7fa49f17062f:	8b 95 70 ff ff ff    	mov    -0x90(%rbp),%edx
    7fa49f170635:	83 e2 01             	and    $0x1,%edx
    7fa49f170638:	85 d2                	test   %edx,%edx
    7fa49f17063a:	0f 94 c2             	sete   %dl
    7fa49f17063d:	0f b6 d2             	movzbl %dl,%edx
    7fa49f170640:	23 ca                	and    %edx,%ecx
    7fa49f170642:	85 c9                	test   %ecx,%ecx
    7fa49f170644:	0f 94 c2             	sete   %dl
    7fa49f170647:	0f b6 d2             	movzbl %dl,%edx
    7fa49f17064a:	89 95 28 fe ff ff    	mov    %edx,-0x1d8(%rbp)
    7fa49f170650:	23 d0                	and    %eax,%edx
    7fa49f170652:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7fa49f170658:	83 e6 03             	and    $0x3,%esi
    7fa49f17065b:	d1 e6                	shl    %esi
    7fa49f17065d:	89 b5 20 fe ff ff    	mov    %esi,-0x1e0(%rbp)
    7fa49f170663:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%rbp)
    7fa49f170669:	85 c0                	test   %eax,%eax
    7fa49f17066b:	0f 94 c0             	sete   %al
    7fa49f17066e:	0f b6 c0             	movzbl %al,%eax
    7fa49f170671:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7fa49f170677:	23 c8                	and    %eax,%ecx
    7fa49f170679:	89 8d 08 fe ff ff    	mov    %ecx,-0x1f8(%rbp)
    7fa49f17067f:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fa49f170685:	d1 e8                	shr    %eax
    7fa49f170687:	83 e0 03             	and    $0x3,%eax
    7fa49f17068a:	89 85 00 fe ff ff    	mov    %eax,-0x200(%rbp)
    7fa49f170690:	85 d2                	test   %edx,%edx
    7fa49f170692:	0f 85 1a 00 00 00    	jne    0x7fa49f1706b2
    7fa49f170698:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fa49f17069e:	85 c0                	test   %eax,%eax
    7fa49f1706a0:	0f 85 18 00 00 00    	jne    0x7fa49f1706be
    7fa49f1706a6:	44 8b a5 70 ff ff ff 	mov    -0x90(%rbp),%r12d
    7fa49f1706ad:	e9 13 00 00 00       	jmpq   0x7fa49f1706c5
    7fa49f1706b2:	44 8b a5 20 fe ff ff 	mov    -0x1e0(%rbp),%r12d
    7fa49f1706b9:	e9 07 00 00 00       	jmpq   0x7fa49f1706c5
    7fa49f1706be:	44 8b a5 00 fe ff ff 	mov    -0x200(%rbp),%r12d
    7fa49f1706c5:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fa49f1706cb:	83 e0 01             	and    $0x1,%eax
    7fa49f1706ce:	8b 8d 18 fe ff ff    	mov    -0x1e8(%rbp),%ecx
    7fa49f1706d4:	23 c1                	and    %ecx,%eax
    7fa49f1706d6:	8b 8d 10 fe ff ff    	mov    -0x1f0(%rbp),%ecx
    7fa49f1706dc:	0b c1                	or     %ecx,%eax
    7fa49f1706de:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%rbp)
    7fa49f1706e4:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fa49f1706ea:	d1 e8                	shr    %eax
    7fa49f1706ec:	83 e0 01             	and    $0x1,%eax
    7fa49f1706ef:	89 85 f0 fd ff ff    	mov    %eax,-0x210(%rbp)
    7fa49f1706f5:	8b 8d 28 fe ff ff    	mov    -0x1d8(%rbp),%ecx
    7fa49f1706fb:	0b c1                	or     %ecx,%eax
    7fa49f1706fd:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7fa49f170700:	89 8d e8 fd ff ff    	mov    %ecx,-0x218(%rbp)
    7fa49f170706:	85 c0                	test   %eax,%eax
    7fa49f170708:	0f 85 0c 00 00 00    	jne    0x7fa49f17071a
    7fa49f17070e:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fa49f170714:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%rbp)
    7fa49f17071a:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7fa49f170720:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7fa49f170726:	8b 85 f8 fd ff ff    	mov    -0x208(%rbp),%eax
    7fa49f17072c:	85 c0                	test   %eax,%eax
    7fa49f17072e:	0f 85 0c 00 00 00    	jne    0x7fa49f170740
    7fa49f170734:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fa49f17073a:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7fa49f170740:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fa49f170746:	23 85 f0 fd ff ff    	and    -0x210(%rbp),%eax
    7fa49f17074c:	8b 8d 10 fe ff ff    	mov    -0x1f0(%rbp),%ecx
    7fa49f170752:	0b c1                	or     %ecx,%eax
    7fa49f170754:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7fa49f170757:	89 8d d8 fd ff ff    	mov    %ecx,-0x228(%rbp)
    7fa49f17075d:	85 c0                	test   %eax,%eax
    7fa49f17075f:	0f 85 0c 00 00 00    	jne    0x7fa49f170771
    7fa49f170765:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fa49f17076b:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7fa49f170771:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fa49f170777:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7fa49f17077e:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7fa49f170784:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7fa49f17078a:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7fa49f170791:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fa49f170797:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fa49f17079d:	85 c0                	test   %eax,%eax
    7fa49f17079f:	0f 84 1a 00 00 00    	je     0x7fa49f1707bf
    7fa49f1707a5:	41 c7 87 18 01 00 00 	movl   $0x1,0x118(%r15)
    7fa49f1707ac:	01 00 00 00 
    7fa49f1707b0:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%rbp)
    7fa49f1707b7:	00 00 00 
    7fa49f1707ba:	e9 10 00 00 00       	jmpq   0x7fa49f1707cf
    7fa49f1707bf:	45 89 a7 18 01 00 00 	mov    %r12d,0x118(%r15)
    7fa49f1707c6:	41 8b c4             	mov    %r12d,%eax
    7fa49f1707c9:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fa49f1707cf:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7fa49f1707d5:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7fa49f1707dc:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fa49f1707e2:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fa49f1707e8:	85 c0                	test   %eax,%eax
    7fa49f1707ea:	0f 84 17 00 00 00    	je     0x7fa49f170807
    7fa49f1707f0:	41 c7 87 00 01 00 00 	movl   $0x1,0x100(%r15)
    7fa49f1707f7:	01 00 00 00 
    7fa49f1707fb:	c7 45 88 01 00 00 00 	movl   $0x1,-0x78(%rbp)
    7fa49f170802:	e9 0c 00 00 00       	jmpq   0x7fa49f170813
    7fa49f170807:	41 89 9f 00 01 00 00 	mov    %ebx,0x100(%r15)
    7fa49f17080e:	8b c3                	mov    %ebx,%eax
    7fa49f170810:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fa49f170813:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fa49f170819:	85 c0                	test   %eax,%eax
    7fa49f17081b:	0f 84 2e 00 00 00    	je     0x7fa49f17084f
    7fa49f170821:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7fa49f170828:	8b c8                	mov    %eax,%ecx
    7fa49f17082a:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa49f170830:	41 89 8f f0 00 00 00 	mov    %ecx,0xf0(%r15)
    7fa49f170837:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7fa49f17083a:	c1 e8 08             	shr    $0x8,%eax
    7fa49f17083d:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fa49f170843:	c1 e1 10             	shl    $0x10,%ecx
    7fa49f170846:	0b c1                	or     %ecx,%eax
    7fa49f170848:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7fa49f17084f:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fa49f170855:	85 c0                	test   %eax,%eax
    7fa49f170857:	0f 84 17 00 00 00    	je     0x7fa49f170874
    7fa49f17085d:	41 c7 87 e8 00 00 00 	movl   $0x0,0xe8(%r15)
    7fa49f170864:	00 00 00 00 
    7fa49f170868:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fa49f17086f:	e9 10 00 00 00       	jmpq   0x7fa49f170884
    7fa49f170874:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fa49f17087a:	41 89 87 e8 00 00 00 	mov    %eax,0xe8(%r15)
    7fa49f170881:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fa49f170884:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fa49f17088a:	85 c0                	test   %eax,%eax
    7fa49f17088c:	0f 84 17 00 00 00    	je     0x7fa49f1708a9
    7fa49f170892:	41 c7 87 e0 00 00 00 	movl   $0x0,0xe0(%r15)
    7fa49f170899:	00 00 00 00 
    7fa49f17089d:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7fa49f1708a4:	e9 10 00 00 00       	jmpq   0x7fa49f1708b9
    7fa49f1708a9:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fa49f1708af:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7fa49f1708b6:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fa49f1708b9:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fa49f1708bf:	85 c0                	test   %eax,%eax
    7fa49f1708c1:	0f 84 db 00 00 00    	je     0x7fa49f1709a2
    7fa49f1708c7:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fa49f1708ca:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7fa49f1708d1:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fa49f1708d4:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fa49f1708d7:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7fa49f1708de:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fa49f1708e1:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fa49f1708e4:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7fa49f1708eb:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fa49f1708ee:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7fa49f1708f1:	41 89 8f b0 00 00 00 	mov    %ecx,0xb0(%r15)
    7fa49f1708f8:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7fa49f1708fb:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fa49f1708fe:	41 89 8f b8 00 00 00 	mov    %ecx,0xb8(%r15)
    7fa49f170905:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7fa49f170908:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7fa49f17090b:	41 89 8f c0 00 00 00 	mov    %ecx,0xc0(%r15)
    7fa49f170912:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7fa49f170915:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7fa49f170918:	41 89 97 98 00 00 00 	mov    %edx,0x98(%r15)
    7fa49f17091f:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7fa49f170922:	45 89 af a0 00 00 00 	mov    %r13d,0xa0(%r15)
    7fa49f170929:	41 8b d5             	mov    %r13d,%edx
    7fa49f17092c:	89 55 d8             	mov    %edx,-0x28(%rbp)
    7fa49f17092f:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fa49f170932:	41 89 97 a8 00 00 00 	mov    %edx,0xa8(%r15)
    7fa49f170939:	4c 8b ea             	mov    %rdx,%r13
    7fa49f17093c:	41 8b 97 94 00 00 00 	mov    0x94(%r15),%edx
    7fa49f170943:	49 8b f7             	mov    %r15,%rsi
    7fa49f170946:	48 83 c6 54          	add    $0x54,%rsi
    7fa49f17094a:	8b fa                	mov    %edx,%edi
    7fa49f17094c:	0f b6 3c 3e          	movzbl (%rsi,%rdi,1),%edi
    7fa49f170950:	41 89 7f 4c          	mov    %edi,0x4c(%r15)
    7fa49f170954:	89 7d e8             	mov    %edi,-0x18(%rbp)
    7fa49f170957:	0f b6 c9             	movzbl %cl,%ecx
    7fa49f17095a:	8b fa                	mov    %edx,%edi
    7fa49f17095c:	40 88 0c 3e          	mov    %cl,(%rsi,%rdi,1)
    7fa49f170960:	ff ca                	dec    %edx
    7fa49f170962:	b9 3e 00 00 00       	mov    $0x3e,%ecx
    7fa49f170967:	3b d1                	cmp    %ecx,%edx
    7fa49f170969:	0f 47 d1             	cmova  %ecx,%edx
    7fa49f17096c:	41 89 97 94 00 00 00 	mov    %edx,0x94(%r15)
    7fa49f170973:	41 8b 4f 48          	mov    0x48(%r15),%ecx
    7fa49f170977:	49 8b d7             	mov    %r15,%rdx
    7fa49f17097a:	48 83 c2 08          	add    $0x8,%rdx
    7fa49f17097e:	8b f1                	mov    %ecx,%esi
    7fa49f170980:	0f b6 34 32          	movzbl (%rdx,%rsi,1),%esi
    7fa49f170984:	41 89 37             	mov    %esi,(%r15)
    7fa49f170987:	89 75 f0             	mov    %esi,-0x10(%rbp)
    7fa49f17098a:	0f b6 c0             	movzbl %al,%eax
    7fa49f17098d:	8b f1                	mov    %ecx,%esi
    7fa49f17098f:	88 04 32             	mov    %al,(%rdx,%rsi,1)
    7fa49f170992:	ff c9                	dec    %ecx
    7fa49f170994:	b8 3e 00 00 00       	mov    $0x3e,%eax
    7fa49f170999:	3b c8                	cmp    %eax,%ecx
    7fa49f17099b:	0f 47 c8             	cmova  %eax,%ecx
    7fa49f17099e:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7fa49f1709a2:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7fa49f1709a8:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7fa49f1709af:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fa49f1709b2:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fa49f1709b5:	c1 e8 02             	shr    $0x2,%eax
    7fa49f1709b8:	83 e0 01             	and    $0x1,%eax
    7fa49f1709bb:	85 c0                	test   %eax,%eax
    7fa49f1709bd:	0f 94 c0             	sete   %al
    7fa49f1709c0:	0f b6 c0             	movzbl %al,%eax
    7fa49f1709c3:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7fa49f1709c7:	89 01                	mov    %eax,(%rcx)
    7fa49f1709c9:	49 8b 46 30          	mov    0x30(%r14),%rax
    7fa49f1709cd:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7fa49f1709d3:	89 08                	mov    %ecx,(%rax)
    7fa49f1709d5:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fa49f1709db:	83 e0 01             	and    $0x1,%eax
    7fa49f1709de:	85 c0                	test   %eax,%eax
    7fa49f1709e0:	0f 94 c0             	sete   %al
    7fa49f1709e3:	0f b6 c0             	movzbl %al,%eax
    7fa49f1709e6:	49 8b 4e 38          	mov    0x38(%r14),%rcx
    7fa49f1709ea:	89 01                	mov    %eax,(%rcx)
    7fa49f1709ec:	49 8b 46 40          	mov    0x40(%r14),%rax
    7fa49f1709f0:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7fa49f1709f3:	89 08                	mov    %ecx,(%rax)
    7fa49f1709f5:	33 c0                	xor    %eax,%eax
    7fa49f1709f7:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fa49f1709fb:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fa49f170a00:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fa49f170a05:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fa49f170a0a:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fa49f170a0f:	48 8b e5             	mov    %rbp,%rsp
    7fa49f170a12:	5d                   	pop    %rbp
    7fa49f170a13:	c3                   	retq   

end

