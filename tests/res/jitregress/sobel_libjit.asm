function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fc10da8812d <.text>:
    7fc10da8812d:	55                   	push   %rbp
    7fc10da8812e:	48 8b ec             	mov    %rsp,%rbp
    7fc10da88131:	48 81 ec 20 02 00 00 	sub    $0x220,%rsp
    7fc10da88138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fc10da8813c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fc10da88141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fc10da88146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fc10da8814b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fc10da88150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fc10da88154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fc10da88158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fc10da8815c:	4c 8b 30             	mov    (%rax),%r14
    7fc10da8815f:	41 8b 07             	mov    (%r15),%eax
    7fc10da88162:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fc10da88165:	41 8b 47 4c          	mov    0x4c(%r15),%eax
    7fc10da88169:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fc10da8816c:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7fc10da88173:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fc10da88176:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7fc10da8817d:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fc10da88180:	45 8b af a8 00 00 00 	mov    0xa8(%r15),%r13d
    7fc10da88187:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7fc10da8818e:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fc10da88191:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7fc10da88198:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fc10da8819b:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7fc10da881a2:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fc10da881a5:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7fc10da881ac:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fc10da881af:	41 8b 87 d0 00 00 00 	mov    0xd0(%r15),%eax
    7fc10da881b6:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fc10da881b9:	41 8b 87 d8 00 00 00 	mov    0xd8(%r15),%eax
    7fc10da881c0:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fc10da881c3:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7fc10da881ca:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fc10da881cd:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7fc10da881d4:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fc10da881d7:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7fc10da881de:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fc10da881e1:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7fc10da881e8:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fc10da881eb:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7fc10da881f2:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fc10da881f5:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7fc10da881fc:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fc10da88202:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7fc10da88209:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fc10da8820f:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7fc10da88216:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fc10da8821c:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7fc10da88223:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7fc10da88229:	49 8b 46 18          	mov    0x18(%r14),%rax
    7fc10da8822d:	8b 00                	mov    (%rax),%eax
    7fc10da8822f:	41 8b 8f 30 01 00 00 	mov    0x130(%r15),%ecx
    7fc10da88236:	33 c8                	xor    %eax,%ecx
    7fc10da88238:	23 c8                	and    %eax,%ecx
    7fc10da8823a:	41 89 87 30 01 00 00 	mov    %eax,0x130(%r15)
    7fc10da88241:	85 c9                	test   %ecx,%ecx
    7fc10da88243:	0f 84 32 07 00 00    	je     0x7fc10da8897b
    7fc10da88249:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fc10da8824c:	81 f9 00 10 00 00    	cmp    $0x1000,%ecx
    7fc10da88252:	0f 92 c0             	setb   %al
    7fc10da88255:	0f b6 c0             	movzbl %al,%eax
    7fc10da88258:	85 c0                	test   %eax,%eax
    7fc10da8825a:	0f 94 c0             	sete   %al
    7fc10da8825d:	0f b6 c0             	movzbl %al,%eax
    7fc10da88260:	85 c0                	test   %eax,%eax
    7fc10da88262:	0f 94 c0             	sete   %al
    7fc10da88265:	0f b6 c0             	movzbl %al,%eax
    7fc10da88268:	8b 55 88             	mov    -0x78(%rbp),%edx
    7fc10da8826b:	83 e2 01             	and    $0x1,%edx
    7fc10da8826e:	85 d2                	test   %edx,%edx
    7fc10da88270:	0f 94 c2             	sete   %dl
    7fc10da88273:	0f b6 d2             	movzbl %dl,%edx
    7fc10da88276:	89 95 58 ff ff ff    	mov    %edx,-0xa8(%rbp)
    7fc10da8827c:	85 d2                	test   %edx,%edx
    7fc10da8827e:	0f 94 c2             	sete   %dl
    7fc10da88281:	0f b6 d2             	movzbl %dl,%edx
    7fc10da88284:	23 c2                	and    %edx,%eax
    7fc10da88286:	85 c0                	test   %eax,%eax
    7fc10da88288:	0f 94 c0             	sete   %al
    7fc10da8828b:	0f b6 c0             	movzbl %al,%eax
    7fc10da8828e:	81 f9 87 00 00 00    	cmp    $0x87,%ecx
    7fc10da88294:	0f 93 c2             	setae  %dl
    7fc10da88297:	0f b6 d2             	movzbl %dl,%edx
    7fc10da8829a:	8b 75 98             	mov    -0x68(%rbp),%esi
    7fc10da8829d:	85 f6                	test   %esi,%esi
    7fc10da8829f:	40 0f 94 c6          	sete   %sil
    7fc10da882a3:	40 0f b6 f6          	movzbl %sil,%esi
    7fc10da882a7:	23 d6                	and    %esi,%edx
    7fc10da882a9:	23 d0                	and    %eax,%edx
    7fc10da882ab:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7fc10da882b1:	c1 ee 02             	shr    $0x2,%esi
    7fc10da882b4:	83 e6 01             	and    $0x1,%esi
    7fc10da882b7:	85 f6                	test   %esi,%esi
    7fc10da882b9:	40 0f 94 c6          	sete   %sil
    7fc10da882bd:	40 0f b6 f6          	movzbl %sil,%esi
    7fc10da882c1:	89 b5 50 ff ff ff    	mov    %esi,-0xb0(%rbp)
    7fc10da882c7:	85 f6                	test   %esi,%esi
    7fc10da882c9:	40 0f 94 c6          	sete   %sil
    7fc10da882cd:	40 0f b6 f6          	movzbl %sil,%esi
    7fc10da882d1:	89 95 48 ff ff ff    	mov    %edx,-0xb8(%rbp)
    7fc10da882d7:	23 d6                	and    %esi,%edx
    7fc10da882d9:	85 d2                	test   %edx,%edx
    7fc10da882db:	0f 94 c2             	sete   %dl
    7fc10da882de:	0f b6 d2             	movzbl %dl,%edx
    7fc10da882e1:	89 95 40 ff ff ff    	mov    %edx,-0xc0(%rbp)
    7fc10da882e7:	23 c2                	and    %edx,%eax
    7fc10da882e9:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fc10da882ef:	81 f9 fe ff ff ff    	cmp    $0xfffffffe,%ecx
    7fc10da882f5:	0f 93 c0             	setae  %al
    7fc10da882f8:	0f b6 c0             	movzbl %al,%eax
    7fc10da882fb:	81 e9 fe ff ff ff    	sub    $0xfffffffe,%ecx
    7fc10da88301:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7fc10da88307:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fc10da8830a:	ff c1                	inc    %ecx
    7fc10da8830c:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7fc10da88312:	85 c0                	test   %eax,%eax
    7fc10da88314:	0f 85 0c 00 00 00    	jne    0x7fc10da88326
    7fc10da8831a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fc10da88320:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fc10da88326:	49 8b 46 20          	mov    0x20(%r14),%rax
    7fc10da8832a:	8b 00                	mov    (%rax),%eax
    7fc10da8832c:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fc10da88332:	83 c8 00             	or     $0x0,%eax
    7fc10da88335:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fc10da8833b:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fc10da8833e:	3d 04 10 00 00       	cmp    $0x1004,%eax
    7fc10da88343:	0f 97 c0             	seta   %al
    7fc10da88346:	0f b6 c0             	movzbl %al,%eax
    7fc10da88349:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fc10da8834f:	41 8b c5             	mov    %r13d,%eax
    7fc10da88352:	03 45 a8             	add    -0x58(%rbp),%eax
    7fc10da88355:	25 ff 01 00 00       	and    $0x1ff,%eax
    7fc10da8835a:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fc10da8835d:	d1 e1                	shl    %ecx
    7fc10da8835f:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7fc10da88365:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fc10da8836b:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fc10da88371:	03 c1                	add    %ecx,%eax
    7fc10da88373:	25 ff 03 00 00       	and    $0x3ff,%eax
    7fc10da88378:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fc10da8837b:	03 4d b8             	add    -0x48(%rbp),%ecx
    7fc10da8837e:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fc10da88384:	8b 55 d0             	mov    -0x30(%rbp),%edx
    7fc10da88387:	d1 e2                	shl    %edx
    7fc10da88389:	89 95 f8 fe ff ff    	mov    %edx,-0x108(%rbp)
    7fc10da8838f:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7fc10da88395:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7fc10da8839b:	03 ca                	add    %edx,%ecx
    7fc10da8839d:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fc10da883a3:	3b c1                	cmp    %ecx,%eax
    7fc10da883a5:	0f 97 c2             	seta   %dl
    7fc10da883a8:	0f b6 d2             	movzbl %dl,%edx
    7fc10da883ab:	8b f0                	mov    %eax,%esi
    7fc10da883ad:	2b f1                	sub    %ecx,%esi
    7fc10da883af:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7fc10da883b5:	89 b5 e8 fe ff ff    	mov    %esi,-0x118(%rbp)
    7fc10da883bb:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fc10da883c1:	2b c8                	sub    %eax,%ecx
    7fc10da883c3:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fc10da883c9:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7fc10da883cf:	85 d2                	test   %edx,%edx
    7fc10da883d1:	0f 85 0c 00 00 00    	jne    0x7fc10da883e3
    7fc10da883d7:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fc10da883dd:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fc10da883e3:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7fc10da883e6:	03 45 a8             	add    -0x58(%rbp),%eax
    7fc10da883e9:	25 ff 01 00 00       	and    $0x1ff,%eax
    7fc10da883ee:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7fc10da883f1:	d1 e1                	shl    %ecx
    7fc10da883f3:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7fc10da883f9:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fc10da883ff:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fc10da88405:	03 c1                	add    %ecx,%eax
    7fc10da88407:	25 ff 03 00 00       	and    $0x3ff,%eax
    7fc10da8840c:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fc10da8840f:	41 03 cd             	add    %r13d,%ecx
    7fc10da88412:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7fc10da88418:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7fc10da8841b:	d1 e2                	shl    %edx
    7fc10da8841d:	89 95 c0 fe ff ff    	mov    %edx,-0x140(%rbp)
    7fc10da88423:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7fc10da88429:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7fc10da8842f:	03 ca                	add    %edx,%ecx
    7fc10da88431:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fc10da88437:	3b c1                	cmp    %ecx,%eax
    7fc10da88439:	0f 97 c2             	seta   %dl
    7fc10da8843c:	0f b6 d2             	movzbl %dl,%edx
    7fc10da8843f:	8b f0                	mov    %eax,%esi
    7fc10da88441:	2b f1                	sub    %ecx,%esi
    7fc10da88443:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7fc10da88449:	89 b5 b0 fe ff ff    	mov    %esi,-0x150(%rbp)
    7fc10da8844f:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fc10da88455:	2b c8                	sub    %eax,%ecx
    7fc10da88457:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7fc10da8845d:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7fc10da88463:	85 d2                	test   %edx,%edx
    7fc10da88465:	0f 85 0c 00 00 00    	jne    0x7fc10da88477
    7fc10da8846b:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fc10da88471:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fc10da88477:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fc10da8847d:	03 85 b0 fe ff ff    	add    -0x150(%rbp),%eax
    7fc10da88483:	25 ff 07 00 00       	and    $0x7ff,%eax
    7fc10da88488:	3d ff 00 00 00       	cmp    $0xff,%eax
    7fc10da8848d:	0f 92 c1             	setb   %cl
    7fc10da88490:	0f b6 c9             	movzbl %cl,%ecx
    7fc10da88493:	25 ff 00 00 00       	and    $0xff,%eax
    7fc10da88498:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fc10da8849e:	85 c9                	test   %ecx,%ecx
    7fc10da884a0:	0f 85 0a 00 00 00    	jne    0x7fc10da884b0
    7fc10da884a6:	c7 85 98 fe ff ff ff 	movl   $0xff,-0x168(%rbp)
    7fc10da884ad:	00 00 00 
    7fc10da884b0:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fc10da884b3:	c1 e8 02             	shr    $0x2,%eax
    7fc10da884b6:	83 e0 01             	and    $0x1,%eax
    7fc10da884b9:	85 c0                	test   %eax,%eax
    7fc10da884bb:	0f 94 c0             	sete   %al
    7fc10da884be:	0f b6 c0             	movzbl %al,%eax
    7fc10da884c1:	49 8b 4e 08          	mov    0x8(%r14),%rcx
    7fc10da884c5:	8b 09                	mov    (%rcx),%ecx
    7fc10da884c7:	23 c1                	and    %ecx,%eax
    7fc10da884c9:	8b 9d 58 ff ff ff    	mov    -0xa8(%rbp),%ebx
    7fc10da884cf:	23 9d 40 ff ff ff    	and    -0xc0(%rbp),%ebx
    7fc10da884d5:	85 db                	test   %ebx,%ebx
    7fc10da884d7:	0f 94 c1             	sete   %cl
    7fc10da884da:	0f b6 c9             	movzbl %cl,%ecx
    7fc10da884dd:	23 c8                	and    %eax,%ecx
    7fc10da884df:	8b 55 88             	mov    -0x78(%rbp),%edx
    7fc10da884e2:	83 e2 03             	and    $0x3,%edx
    7fc10da884e5:	d1 e2                	shl    %edx
    7fc10da884e7:	89 95 90 fe ff ff    	mov    %edx,-0x170(%rbp)
    7fc10da884ed:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fc10da884f3:	85 c0                	test   %eax,%eax
    7fc10da884f5:	0f 94 c0             	sete   %al
    7fc10da884f8:	0f b6 c0             	movzbl %al,%eax
    7fc10da884fb:	23 c3                	and    %ebx,%eax
    7fc10da884fd:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fc10da88503:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fc10da88506:	d1 e8                	shr    %eax
    7fc10da88508:	83 e0 03             	and    $0x3,%eax
    7fc10da8850b:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fc10da88511:	85 c9                	test   %ecx,%ecx
    7fc10da88513:	0f 85 1c 00 00 00    	jne    0x7fc10da88535
    7fc10da88519:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fc10da8851f:	85 c0                	test   %eax,%eax
    7fc10da88521:	0f 85 1f 00 00 00    	jne    0x7fc10da88546
    7fc10da88527:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fc10da8852a:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fc10da88530:	e9 1d 00 00 00       	jmpq   0x7fc10da88552
    7fc10da88535:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fc10da8853b:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fc10da88541:	e9 0c 00 00 00       	jmpq   0x7fc10da88552
    7fc10da88546:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7fc10da8854c:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fc10da88552:	8b c3                	mov    %ebx,%eax
    7fc10da88554:	f7 d0                	not    %eax
    7fc10da88556:	83 e0 01             	and    $0x1,%eax
    7fc10da88559:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7fc10da8855c:	d1 e9                	shr    %ecx
    7fc10da8855e:	83 e1 01             	and    $0x1,%ecx
    7fc10da88561:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7fc10da88567:	0b c1                	or     %ecx,%eax
    7fc10da88569:	49 8b 0e             	mov    (%r14),%rcx
    7fc10da8856c:	8b 09                	mov    (%rcx),%ecx
    7fc10da8856e:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7fc10da88574:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7fc10da8857a:	85 c0                	test   %eax,%eax
    7fc10da8857c:	0f 85 0c 00 00 00    	jne    0x7fc10da8858e
    7fc10da88582:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fc10da88588:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7fc10da8858e:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fc10da88591:	83 e0 01             	and    $0x1,%eax
    7fc10da88594:	8b 8d 88 fe ff ff    	mov    -0x178(%rbp),%ecx
    7fc10da8859a:	23 c1                	and    %ecx,%eax
    7fc10da8859c:	0b c3                	or     %ebx,%eax
    7fc10da8859e:	89 85 50 fe ff ff    	mov    %eax,-0x1b0(%rbp)
    7fc10da885a4:	23 8d 68 fe ff ff    	and    -0x198(%rbp),%ecx
    7fc10da885aa:	0b cb                	or     %ebx,%ecx
    7fc10da885ac:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7fc10da885b2:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fc10da885b8:	23 85 48 ff ff ff    	and    -0xb8(%rbp),%eax
    7fc10da885be:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7fc10da885c4:	83 e1 01             	and    $0x1,%ecx
    7fc10da885c7:	85 c9                	test   %ecx,%ecx
    7fc10da885c9:	0f 94 c1             	sete   %cl
    7fc10da885cc:	0f b6 c9             	movzbl %cl,%ecx
    7fc10da885cf:	49 8b 56 10          	mov    0x10(%r14),%rdx
    7fc10da885d3:	8b 12                	mov    (%rdx),%edx
    7fc10da885d5:	23 ca                	and    %edx,%ecx
    7fc10da885d7:	85 c9                	test   %ecx,%ecx
    7fc10da885d9:	0f 94 c2             	sete   %dl
    7fc10da885dc:	0f b6 d2             	movzbl %dl,%edx
    7fc10da885df:	23 d0                	and    %eax,%edx
    7fc10da885e1:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7fc10da885e7:	83 e6 03             	and    $0x3,%esi
    7fc10da885ea:	d1 e6                	shl    %esi
    7fc10da885ec:	89 b5 40 fe ff ff    	mov    %esi,-0x1c0(%rbp)
    7fc10da885f2:	89 85 38 fe ff ff    	mov    %eax,-0x1c8(%rbp)
    7fc10da885f8:	85 c0                	test   %eax,%eax
    7fc10da885fa:	0f 94 c0             	sete   %al
    7fc10da885fd:	0f b6 c0             	movzbl %al,%eax
    7fc10da88600:	89 8d 30 fe ff ff    	mov    %ecx,-0x1d0(%rbp)
    7fc10da88606:	23 c8                	and    %eax,%ecx
    7fc10da88608:	89 8d 28 fe ff ff    	mov    %ecx,-0x1d8(%rbp)
    7fc10da8860e:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fc10da88614:	d1 e8                	shr    %eax
    7fc10da88616:	83 e0 03             	and    $0x3,%eax
    7fc10da88619:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7fc10da8861f:	85 d2                	test   %edx,%edx
    7fc10da88621:	0f 85 1a 00 00 00    	jne    0x7fc10da88641
    7fc10da88627:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7fc10da8862d:	85 c0                	test   %eax,%eax
    7fc10da8862f:	0f 85 18 00 00 00    	jne    0x7fc10da8864d
    7fc10da88635:	44 8b a5 70 ff ff ff 	mov    -0x90(%rbp),%r12d
    7fc10da8863c:	e9 13 00 00 00       	jmpq   0x7fc10da88654
    7fc10da88641:	44 8b a5 40 fe ff ff 	mov    -0x1c0(%rbp),%r12d
    7fc10da88648:	e9 07 00 00 00       	jmpq   0x7fc10da88654
    7fc10da8864d:	44 8b a5 20 fe ff ff 	mov    -0x1e0(%rbp),%r12d
    7fc10da88654:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7fc10da8865a:	f7 d0                	not    %eax
    7fc10da8865c:	83 e0 01             	and    $0x1,%eax
    7fc10da8865f:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7fc10da88665:	d1 e9                	shr    %ecx
    7fc10da88667:	83 e1 01             	and    $0x1,%ecx
    7fc10da8866a:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7fc10da88670:	0b c1                	or     %ecx,%eax
    7fc10da88672:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7fc10da88675:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7fc10da8867b:	85 c0                	test   %eax,%eax
    7fc10da8867d:	0f 85 0c 00 00 00    	jne    0x7fc10da8868f
    7fc10da88683:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fc10da88689:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7fc10da8868f:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fc10da88695:	83 e0 01             	and    $0x1,%eax
    7fc10da88698:	8b 8d 38 fe ff ff    	mov    -0x1c8(%rbp),%ecx
    7fc10da8869e:	23 c1                	and    %ecx,%eax
    7fc10da886a0:	8b 95 30 fe ff ff    	mov    -0x1d0(%rbp),%edx
    7fc10da886a6:	0b c2                	or     %edx,%eax
    7fc10da886a8:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7fc10da886ae:	23 8d 18 fe ff ff    	and    -0x1e8(%rbp),%ecx
    7fc10da886b4:	0b d1                	or     %ecx,%edx
    7fc10da886b6:	85 d2                	test   %edx,%edx
    7fc10da886b8:	0f 84 10 00 00 00    	je     0x7fc10da886ce
    7fc10da886be:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fc10da886c1:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7fc10da886c8:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7fc10da886ce:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fc10da886d4:	85 c0                	test   %eax,%eax
    7fc10da886d6:	0f 84 13 00 00 00    	je     0x7fc10da886ef
    7fc10da886dc:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fc10da886e2:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7fc10da886e9:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fc10da886ef:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fc10da886f5:	85 c0                	test   %eax,%eax
    7fc10da886f7:	0f 84 1a 00 00 00    	je     0x7fc10da88717
    7fc10da886fd:	41 c7 87 18 01 00 00 	movl   $0x1,0x118(%r15)
    7fc10da88704:	01 00 00 00 
    7fc10da88708:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%rbp)
    7fc10da8870f:	00 00 00 
    7fc10da88712:	e9 10 00 00 00       	jmpq   0x7fc10da88727
    7fc10da88717:	45 89 a7 18 01 00 00 	mov    %r12d,0x118(%r15)
    7fc10da8871e:	41 8b c4             	mov    %r12d,%eax
    7fc10da88721:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fc10da88727:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7fc10da8872d:	85 c0                	test   %eax,%eax
    7fc10da8872f:	0f 84 13 00 00 00    	je     0x7fc10da88748
    7fc10da88735:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7fc10da8873b:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7fc10da88742:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fc10da88748:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fc10da8874e:	85 c0                	test   %eax,%eax
    7fc10da88750:	0f 84 17 00 00 00    	je     0x7fc10da8876d
    7fc10da88756:	41 c7 87 00 01 00 00 	movl   $0x1,0x100(%r15)
    7fc10da8875d:	01 00 00 00 
    7fc10da88761:	c7 45 88 01 00 00 00 	movl   $0x1,-0x78(%rbp)
    7fc10da88768:	e9 10 00 00 00       	jmpq   0x7fc10da8877d
    7fc10da8876d:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fc10da88773:	41 89 87 00 01 00 00 	mov    %eax,0x100(%r15)
    7fc10da8877a:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fc10da8877d:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fc10da88783:	85 c0                	test   %eax,%eax
    7fc10da88785:	0f 84 2e 00 00 00    	je     0x7fc10da887b9
    7fc10da8878b:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7fc10da88792:	8b c8                	mov    %eax,%ecx
    7fc10da88794:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fc10da8879a:	41 89 8f f0 00 00 00 	mov    %ecx,0xf0(%r15)
    7fc10da887a1:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7fc10da887a4:	c1 e8 08             	shr    $0x8,%eax
    7fc10da887a7:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7fc10da887ad:	c1 e1 10             	shl    $0x10,%ecx
    7fc10da887b0:	0b c1                	or     %ecx,%eax
    7fc10da887b2:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7fc10da887b9:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fc10da887bf:	85 c0                	test   %eax,%eax
    7fc10da887c1:	0f 84 17 00 00 00    	je     0x7fc10da887de
    7fc10da887c7:	41 c7 87 e8 00 00 00 	movl   $0x0,0xe8(%r15)
    7fc10da887ce:	00 00 00 00 
    7fc10da887d2:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fc10da887d9:	e9 10 00 00 00       	jmpq   0x7fc10da887ee
    7fc10da887de:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fc10da887e4:	41 89 87 e8 00 00 00 	mov    %eax,0xe8(%r15)
    7fc10da887eb:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fc10da887ee:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fc10da887f4:	85 c0                	test   %eax,%eax
    7fc10da887f6:	0f 84 17 00 00 00    	je     0x7fc10da88813
    7fc10da887fc:	41 c7 87 e0 00 00 00 	movl   $0x0,0xe0(%r15)
    7fc10da88803:	00 00 00 00 
    7fc10da88807:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7fc10da8880e:	e9 1e 00 00 00       	jmpq   0x7fc10da88831
    7fc10da88813:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fc10da88819:	85 c0                	test   %eax,%eax
    7fc10da8881b:	0f 84 10 00 00 00    	je     0x7fc10da88831
    7fc10da88821:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fc10da88827:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7fc10da8882e:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fc10da88831:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fc10da88837:	85 c0                	test   %eax,%eax
    7fc10da88839:	0f 84 db 00 00 00    	je     0x7fc10da8891a
    7fc10da8883f:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fc10da88842:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7fc10da88849:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fc10da8884c:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fc10da8884f:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7fc10da88856:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fc10da88859:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fc10da8885c:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7fc10da88863:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fc10da88866:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7fc10da88869:	41 89 8f b0 00 00 00 	mov    %ecx,0xb0(%r15)
    7fc10da88870:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7fc10da88873:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fc10da88876:	41 89 8f b8 00 00 00 	mov    %ecx,0xb8(%r15)
    7fc10da8887d:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7fc10da88880:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7fc10da88883:	41 89 8f c0 00 00 00 	mov    %ecx,0xc0(%r15)
    7fc10da8888a:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7fc10da8888d:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7fc10da88890:	41 89 97 98 00 00 00 	mov    %edx,0x98(%r15)
    7fc10da88897:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7fc10da8889a:	45 89 af a0 00 00 00 	mov    %r13d,0xa0(%r15)
    7fc10da888a1:	41 8b d5             	mov    %r13d,%edx
    7fc10da888a4:	89 55 d8             	mov    %edx,-0x28(%rbp)
    7fc10da888a7:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fc10da888aa:	41 89 97 a8 00 00 00 	mov    %edx,0xa8(%r15)
    7fc10da888b1:	4c 8b ea             	mov    %rdx,%r13
    7fc10da888b4:	41 8b 97 94 00 00 00 	mov    0x94(%r15),%edx
    7fc10da888bb:	49 8b f7             	mov    %r15,%rsi
    7fc10da888be:	48 83 c6 54          	add    $0x54,%rsi
    7fc10da888c2:	8b fa                	mov    %edx,%edi
    7fc10da888c4:	0f b6 3c 3e          	movzbl (%rsi,%rdi,1),%edi
    7fc10da888c8:	41 89 7f 4c          	mov    %edi,0x4c(%r15)
    7fc10da888cc:	89 7d e8             	mov    %edi,-0x18(%rbp)
    7fc10da888cf:	0f b6 c9             	movzbl %cl,%ecx
    7fc10da888d2:	8b fa                	mov    %edx,%edi
    7fc10da888d4:	40 88 0c 3e          	mov    %cl,(%rsi,%rdi,1)
    7fc10da888d8:	ff ca                	dec    %edx
    7fc10da888da:	b9 3e 00 00 00       	mov    $0x3e,%ecx
    7fc10da888df:	3b d1                	cmp    %ecx,%edx
    7fc10da888e1:	0f 47 d1             	cmova  %ecx,%edx
    7fc10da888e4:	41 89 97 94 00 00 00 	mov    %edx,0x94(%r15)
    7fc10da888eb:	41 8b 4f 48          	mov    0x48(%r15),%ecx
    7fc10da888ef:	49 8b d7             	mov    %r15,%rdx
    7fc10da888f2:	48 83 c2 08          	add    $0x8,%rdx
    7fc10da888f6:	8b f1                	mov    %ecx,%esi
    7fc10da888f8:	0f b6 34 32          	movzbl (%rdx,%rsi,1),%esi
    7fc10da888fc:	41 89 37             	mov    %esi,(%r15)
    7fc10da888ff:	89 75 f0             	mov    %esi,-0x10(%rbp)
    7fc10da88902:	0f b6 c0             	movzbl %al,%eax
    7fc10da88905:	8b f1                	mov    %ecx,%esi
    7fc10da88907:	88 04 32             	mov    %al,(%rdx,%rsi,1)
    7fc10da8890a:	ff c9                	dec    %ecx
    7fc10da8890c:	b8 3e 00 00 00       	mov    $0x3e,%eax
    7fc10da88911:	3b c8                	cmp    %eax,%ecx
    7fc10da88913:	0f 47 c8             	cmova  %eax,%ecx
    7fc10da88916:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7fc10da8891a:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7fc10da88920:	85 c0                	test   %eax,%eax
    7fc10da88922:	0f 84 10 00 00 00    	je     0x7fc10da88938
    7fc10da88928:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fc10da8892e:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7fc10da88935:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fc10da88938:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fc10da8893b:	c1 e8 02             	shr    $0x2,%eax
    7fc10da8893e:	83 e0 01             	and    $0x1,%eax
    7fc10da88941:	85 c0                	test   %eax,%eax
    7fc10da88943:	0f 94 c0             	sete   %al
    7fc10da88946:	0f b6 c0             	movzbl %al,%eax
    7fc10da88949:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7fc10da8894d:	89 01                	mov    %eax,(%rcx)
    7fc10da8894f:	49 8b 46 30          	mov    0x30(%r14),%rax
    7fc10da88953:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7fc10da88959:	89 08                	mov    %ecx,(%rax)
    7fc10da8895b:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fc10da88961:	83 e0 01             	and    $0x1,%eax
    7fc10da88964:	85 c0                	test   %eax,%eax
    7fc10da88966:	0f 94 c0             	sete   %al
    7fc10da88969:	0f b6 c0             	movzbl %al,%eax
    7fc10da8896c:	49 8b 4e 38          	mov    0x38(%r14),%rcx
    7fc10da88970:	89 01                	mov    %eax,(%rcx)
    7fc10da88972:	49 8b 46 40          	mov    0x40(%r14),%rax
    7fc10da88976:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7fc10da88979:	89 08                	mov    %ecx,(%rax)
    7fc10da8897b:	33 c0                	xor    %eax,%eax
    7fc10da8897d:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fc10da88981:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fc10da88986:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fc10da8898b:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fc10da88990:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fc10da88995:	48 8b e5             	mov    %rbp,%rsp
    7fc10da88998:	5d                   	pop    %rbp
    7fc10da88999:	c3                   	retq   

end

