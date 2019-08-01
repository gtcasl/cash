function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007faf796ac12d <.text>:
    7faf796ac12d:	55                   	push   %rbp
    7faf796ac12e:	48 8b ec             	mov    %rsp,%rbp
    7faf796ac131:	48 81 ec 30 02 00 00 	sub    $0x230,%rsp
    7faf796ac138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7faf796ac13c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7faf796ac141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7faf796ac146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7faf796ac14b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7faf796ac150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7faf796ac154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7faf796ac158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7faf796ac15c:	4c 8b 30             	mov    (%rax),%r14
    7faf796ac15f:	41 8b 07             	mov    (%r15),%eax
    7faf796ac162:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7faf796ac165:	41 8b 47 4c          	mov    0x4c(%r15),%eax
    7faf796ac169:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7faf796ac16c:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7faf796ac173:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7faf796ac176:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7faf796ac17d:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7faf796ac180:	45 8b af a8 00 00 00 	mov    0xa8(%r15),%r13d
    7faf796ac187:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7faf796ac18e:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7faf796ac191:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7faf796ac198:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7faf796ac19b:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7faf796ac1a2:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7faf796ac1a5:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7faf796ac1ac:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7faf796ac1af:	41 8b 87 d0 00 00 00 	mov    0xd0(%r15),%eax
    7faf796ac1b6:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7faf796ac1b9:	41 8b 87 d8 00 00 00 	mov    0xd8(%r15),%eax
    7faf796ac1c0:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7faf796ac1c3:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7faf796ac1ca:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7faf796ac1cd:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7faf796ac1d4:	89 45 98             	mov    %eax,-0x68(%rbp)
    7faf796ac1d7:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7faf796ac1de:	89 45 90             	mov    %eax,-0x70(%rbp)
    7faf796ac1e1:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7faf796ac1e8:	89 45 88             	mov    %eax,-0x78(%rbp)
    7faf796ac1eb:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7faf796ac1f2:	89 45 80             	mov    %eax,-0x80(%rbp)
    7faf796ac1f5:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7faf796ac1fc:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7faf796ac202:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7faf796ac209:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7faf796ac20f:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7faf796ac216:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7faf796ac21c:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7faf796ac223:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7faf796ac229:	49 8b 46 18          	mov    0x18(%r14),%rax
    7faf796ac22d:	8b 00                	mov    (%rax),%eax
    7faf796ac22f:	41 8b 8f 30 01 00 00 	mov    0x130(%r15),%ecx
    7faf796ac236:	33 c8                	xor    %eax,%ecx
    7faf796ac238:	23 c8                	and    %eax,%ecx
    7faf796ac23a:	41 89 87 30 01 00 00 	mov    %eax,0x130(%r15)
    7faf796ac241:	85 c9                	test   %ecx,%ecx
    7faf796ac243:	0f 84 2e 07 00 00    	je     0x7faf796ac977
    7faf796ac249:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7faf796ac24c:	81 f9 00 10 00 00    	cmp    $0x1000,%ecx
    7faf796ac252:	0f 92 c0             	setb   %al
    7faf796ac255:	0f b6 c0             	movzbl %al,%eax
    7faf796ac258:	85 c0                	test   %eax,%eax
    7faf796ac25a:	0f 94 c0             	sete   %al
    7faf796ac25d:	0f b6 c0             	movzbl %al,%eax
    7faf796ac260:	85 c0                	test   %eax,%eax
    7faf796ac262:	0f 94 c0             	sete   %al
    7faf796ac265:	0f b6 c0             	movzbl %al,%eax
    7faf796ac268:	8b 55 88             	mov    -0x78(%rbp),%edx
    7faf796ac26b:	83 e2 01             	and    $0x1,%edx
    7faf796ac26e:	85 d2                	test   %edx,%edx
    7faf796ac270:	0f 94 c2             	sete   %dl
    7faf796ac273:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac276:	89 95 58 ff ff ff    	mov    %edx,-0xa8(%rbp)
    7faf796ac27c:	85 d2                	test   %edx,%edx
    7faf796ac27e:	0f 94 c2             	sete   %dl
    7faf796ac281:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac284:	23 c2                	and    %edx,%eax
    7faf796ac286:	85 c0                	test   %eax,%eax
    7faf796ac288:	0f 94 c0             	sete   %al
    7faf796ac28b:	0f b6 c0             	movzbl %al,%eax
    7faf796ac28e:	81 f9 87 00 00 00    	cmp    $0x87,%ecx
    7faf796ac294:	0f 93 c2             	setae  %dl
    7faf796ac297:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac29a:	8b 75 98             	mov    -0x68(%rbp),%esi
    7faf796ac29d:	85 f6                	test   %esi,%esi
    7faf796ac29f:	40 0f 94 c6          	sete   %sil
    7faf796ac2a3:	40 0f b6 f6          	movzbl %sil,%esi
    7faf796ac2a7:	23 d6                	and    %esi,%edx
    7faf796ac2a9:	23 d0                	and    %eax,%edx
    7faf796ac2ab:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7faf796ac2b1:	c1 ee 02             	shr    $0x2,%esi
    7faf796ac2b4:	83 e6 01             	and    $0x1,%esi
    7faf796ac2b7:	85 f6                	test   %esi,%esi
    7faf796ac2b9:	40 0f 94 c6          	sete   %sil
    7faf796ac2bd:	40 0f b6 f6          	movzbl %sil,%esi
    7faf796ac2c1:	89 b5 50 ff ff ff    	mov    %esi,-0xb0(%rbp)
    7faf796ac2c7:	85 f6                	test   %esi,%esi
    7faf796ac2c9:	40 0f 94 c6          	sete   %sil
    7faf796ac2cd:	40 0f b6 f6          	movzbl %sil,%esi
    7faf796ac2d1:	89 95 48 ff ff ff    	mov    %edx,-0xb8(%rbp)
    7faf796ac2d7:	23 d6                	and    %esi,%edx
    7faf796ac2d9:	85 d2                	test   %edx,%edx
    7faf796ac2db:	0f 94 c2             	sete   %dl
    7faf796ac2de:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac2e1:	89 95 40 ff ff ff    	mov    %edx,-0xc0(%rbp)
    7faf796ac2e7:	23 c2                	and    %edx,%eax
    7faf796ac2e9:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7faf796ac2ef:	81 f9 fe ff ff ff    	cmp    $0xfffffffe,%ecx
    7faf796ac2f5:	0f 93 c0             	setae  %al
    7faf796ac2f8:	0f b6 c0             	movzbl %al,%eax
    7faf796ac2fb:	81 e9 fe ff ff ff    	sub    $0xfffffffe,%ecx
    7faf796ac301:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7faf796ac307:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7faf796ac30a:	ff c1                	inc    %ecx
    7faf796ac30c:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7faf796ac312:	85 c0                	test   %eax,%eax
    7faf796ac314:	0f 85 0c 00 00 00    	jne    0x7faf796ac326
    7faf796ac31a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7faf796ac320:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7faf796ac326:	49 8b 46 20          	mov    0x20(%r14),%rax
    7faf796ac32a:	8b 00                	mov    (%rax),%eax
    7faf796ac32c:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7faf796ac332:	83 c8 00             	or     $0x0,%eax
    7faf796ac335:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7faf796ac33b:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7faf796ac33e:	3d 04 10 00 00       	cmp    $0x1004,%eax
    7faf796ac343:	0f 97 c0             	seta   %al
    7faf796ac346:	0f b6 c0             	movzbl %al,%eax
    7faf796ac349:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7faf796ac34f:	41 8b c5             	mov    %r13d,%eax
    7faf796ac352:	03 45 a8             	add    -0x58(%rbp),%eax
    7faf796ac355:	25 ff 01 00 00       	and    $0x1ff,%eax
    7faf796ac35a:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7faf796ac35d:	d1 e1                	shl    %ecx
    7faf796ac35f:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7faf796ac365:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7faf796ac36b:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7faf796ac371:	03 c1                	add    %ecx,%eax
    7faf796ac373:	25 ff 03 00 00       	and    $0x3ff,%eax
    7faf796ac378:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7faf796ac37b:	03 4d b8             	add    -0x48(%rbp),%ecx
    7faf796ac37e:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7faf796ac384:	8b 55 d0             	mov    -0x30(%rbp),%edx
    7faf796ac387:	d1 e2                	shl    %edx
    7faf796ac389:	89 95 f8 fe ff ff    	mov    %edx,-0x108(%rbp)
    7faf796ac38f:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7faf796ac395:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7faf796ac39b:	03 ca                	add    %edx,%ecx
    7faf796ac39d:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7faf796ac3a3:	3b c1                	cmp    %ecx,%eax
    7faf796ac3a5:	0f 97 c2             	seta   %dl
    7faf796ac3a8:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac3ab:	8b f0                	mov    %eax,%esi
    7faf796ac3ad:	2b f1                	sub    %ecx,%esi
    7faf796ac3af:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7faf796ac3b5:	89 b5 e8 fe ff ff    	mov    %esi,-0x118(%rbp)
    7faf796ac3bb:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7faf796ac3c1:	2b c8                	sub    %eax,%ecx
    7faf796ac3c3:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7faf796ac3c9:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7faf796ac3cf:	85 d2                	test   %edx,%edx
    7faf796ac3d1:	0f 85 0c 00 00 00    	jne    0x7faf796ac3e3
    7faf796ac3d7:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7faf796ac3dd:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7faf796ac3e3:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7faf796ac3e6:	03 45 a8             	add    -0x58(%rbp),%eax
    7faf796ac3e9:	25 ff 01 00 00       	and    $0x1ff,%eax
    7faf796ac3ee:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7faf796ac3f1:	d1 e1                	shl    %ecx
    7faf796ac3f3:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7faf796ac3f9:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7faf796ac3ff:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7faf796ac405:	03 c1                	add    %ecx,%eax
    7faf796ac407:	25 ff 03 00 00       	and    $0x3ff,%eax
    7faf796ac40c:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7faf796ac40f:	41 03 cd             	add    %r13d,%ecx
    7faf796ac412:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7faf796ac418:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7faf796ac41b:	d1 e2                	shl    %edx
    7faf796ac41d:	89 95 c0 fe ff ff    	mov    %edx,-0x140(%rbp)
    7faf796ac423:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7faf796ac429:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7faf796ac42f:	03 ca                	add    %edx,%ecx
    7faf796ac431:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7faf796ac437:	3b c1                	cmp    %ecx,%eax
    7faf796ac439:	0f 97 c2             	seta   %dl
    7faf796ac43c:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac43f:	8b f0                	mov    %eax,%esi
    7faf796ac441:	2b f1                	sub    %ecx,%esi
    7faf796ac443:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7faf796ac449:	89 b5 b0 fe ff ff    	mov    %esi,-0x150(%rbp)
    7faf796ac44f:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7faf796ac455:	2b c8                	sub    %eax,%ecx
    7faf796ac457:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7faf796ac45d:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7faf796ac463:	85 d2                	test   %edx,%edx
    7faf796ac465:	0f 85 0c 00 00 00    	jne    0x7faf796ac477
    7faf796ac46b:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7faf796ac471:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7faf796ac477:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7faf796ac47d:	03 85 b0 fe ff ff    	add    -0x150(%rbp),%eax
    7faf796ac483:	25 ff 07 00 00       	and    $0x7ff,%eax
    7faf796ac488:	3d ff 00 00 00       	cmp    $0xff,%eax
    7faf796ac48d:	0f 92 c1             	setb   %cl
    7faf796ac490:	0f b6 c9             	movzbl %cl,%ecx
    7faf796ac493:	25 ff 00 00 00       	and    $0xff,%eax
    7faf796ac498:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7faf796ac49e:	85 c9                	test   %ecx,%ecx
    7faf796ac4a0:	0f 85 0a 00 00 00    	jne    0x7faf796ac4b0
    7faf796ac4a6:	c7 85 98 fe ff ff ff 	movl   $0xff,-0x168(%rbp)
    7faf796ac4ad:	00 00 00 
    7faf796ac4b0:	49 8b 46 08          	mov    0x8(%r14),%rax
    7faf796ac4b4:	8b 00                	mov    (%rax),%eax
    7faf796ac4b6:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7faf796ac4b9:	c1 e9 02             	shr    $0x2,%ecx
    7faf796ac4bc:	83 e1 01             	and    $0x1,%ecx
    7faf796ac4bf:	85 c9                	test   %ecx,%ecx
    7faf796ac4c1:	0f 94 c1             	sete   %cl
    7faf796ac4c4:	0f b6 c9             	movzbl %cl,%ecx
    7faf796ac4c7:	23 c1                	and    %ecx,%eax
    7faf796ac4c9:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7faf796ac4cf:	23 8d 58 ff ff ff    	and    -0xa8(%rbp),%ecx
    7faf796ac4d5:	85 c9                	test   %ecx,%ecx
    7faf796ac4d7:	0f 94 c2             	sete   %dl
    7faf796ac4da:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac4dd:	89 95 90 fe ff ff    	mov    %edx,-0x170(%rbp)
    7faf796ac4e3:	23 d0                	and    %eax,%edx
    7faf796ac4e5:	8b 75 88             	mov    -0x78(%rbp),%esi
    7faf796ac4e8:	83 e6 03             	and    $0x3,%esi
    7faf796ac4eb:	d1 e6                	shl    %esi
    7faf796ac4ed:	89 b5 88 fe ff ff    	mov    %esi,-0x178(%rbp)
    7faf796ac4f3:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7faf796ac4f9:	85 c0                	test   %eax,%eax
    7faf796ac4fb:	0f 94 c0             	sete   %al
    7faf796ac4fe:	0f b6 c0             	movzbl %al,%eax
    7faf796ac501:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7faf796ac507:	23 c8                	and    %eax,%ecx
    7faf796ac509:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7faf796ac50f:	8b 45 88             	mov    -0x78(%rbp),%eax
    7faf796ac512:	d1 e8                	shr    %eax
    7faf796ac514:	83 e0 03             	and    $0x3,%eax
    7faf796ac517:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7faf796ac51d:	85 d2                	test   %edx,%edx
    7faf796ac51f:	0f 85 16 00 00 00    	jne    0x7faf796ac53b
    7faf796ac525:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7faf796ac52b:	85 c0                	test   %eax,%eax
    7faf796ac52d:	0f 85 13 00 00 00    	jne    0x7faf796ac546
    7faf796ac533:	8b 5d 88             	mov    -0x78(%rbp),%ebx
    7faf796ac536:	e9 11 00 00 00       	jmpq   0x7faf796ac54c
    7faf796ac53b:	8b 9d 88 fe ff ff    	mov    -0x178(%rbp),%ebx
    7faf796ac541:	e9 06 00 00 00       	jmpq   0x7faf796ac54c
    7faf796ac546:	8b 9d 68 fe ff ff    	mov    -0x198(%rbp),%ebx
    7faf796ac54c:	8b 45 88             	mov    -0x78(%rbp),%eax
    7faf796ac54f:	d1 e8                	shr    %eax
    7faf796ac551:	83 e0 01             	and    $0x1,%eax
    7faf796ac554:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7faf796ac55a:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7faf796ac560:	0b c1                	or     %ecx,%eax
    7faf796ac562:	49 8b 0e             	mov    (%r14),%rcx
    7faf796ac565:	8b 09                	mov    (%rcx),%ecx
    7faf796ac567:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7faf796ac56d:	89 8d 50 fe ff ff    	mov    %ecx,-0x1b0(%rbp)
    7faf796ac573:	85 c0                	test   %eax,%eax
    7faf796ac575:	0f 85 0c 00 00 00    	jne    0x7faf796ac587
    7faf796ac57b:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7faf796ac581:	89 85 50 fe ff ff    	mov    %eax,-0x1b0(%rbp)
    7faf796ac587:	8b 45 88             	mov    -0x78(%rbp),%eax
    7faf796ac58a:	83 e0 01             	and    $0x1,%eax
    7faf796ac58d:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7faf796ac593:	23 c1                	and    %ecx,%eax
    7faf796ac595:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7faf796ac59b:	0b c2                	or     %edx,%eax
    7faf796ac59d:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7faf796ac5a3:	23 8d 60 fe ff ff    	and    -0x1a0(%rbp),%ecx
    7faf796ac5a9:	0b d1                	or     %ecx,%edx
    7faf796ac5ab:	89 95 40 fe ff ff    	mov    %edx,-0x1c0(%rbp)
    7faf796ac5b1:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7faf796ac5b7:	23 85 50 ff ff ff    	and    -0xb0(%rbp),%eax
    7faf796ac5bd:	49 8b 4e 10          	mov    0x10(%r14),%rcx
    7faf796ac5c1:	8b 09                	mov    (%rcx),%ecx
    7faf796ac5c3:	8b 95 70 ff ff ff    	mov    -0x90(%rbp),%edx
    7faf796ac5c9:	83 e2 01             	and    $0x1,%edx
    7faf796ac5cc:	85 d2                	test   %edx,%edx
    7faf796ac5ce:	0f 94 c2             	sete   %dl
    7faf796ac5d1:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac5d4:	23 ca                	and    %edx,%ecx
    7faf796ac5d6:	85 c9                	test   %ecx,%ecx
    7faf796ac5d8:	0f 94 c2             	sete   %dl
    7faf796ac5db:	0f b6 d2             	movzbl %dl,%edx
    7faf796ac5de:	89 95 38 fe ff ff    	mov    %edx,-0x1c8(%rbp)
    7faf796ac5e4:	23 d0                	and    %eax,%edx
    7faf796ac5e6:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7faf796ac5ec:	83 e6 03             	and    $0x3,%esi
    7faf796ac5ef:	d1 e6                	shl    %esi
    7faf796ac5f1:	89 b5 30 fe ff ff    	mov    %esi,-0x1d0(%rbp)
    7faf796ac5f7:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7faf796ac5fd:	85 c0                	test   %eax,%eax
    7faf796ac5ff:	0f 94 c0             	sete   %al
    7faf796ac602:	0f b6 c0             	movzbl %al,%eax
    7faf796ac605:	89 8d 20 fe ff ff    	mov    %ecx,-0x1e0(%rbp)
    7faf796ac60b:	23 c8                	and    %eax,%ecx
    7faf796ac60d:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7faf796ac613:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7faf796ac619:	d1 e8                	shr    %eax
    7faf796ac61b:	83 e0 03             	and    $0x3,%eax
    7faf796ac61e:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7faf796ac624:	85 d2                	test   %edx,%edx
    7faf796ac626:	0f 85 1a 00 00 00    	jne    0x7faf796ac646
    7faf796ac62c:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7faf796ac632:	85 c0                	test   %eax,%eax
    7faf796ac634:	0f 85 18 00 00 00    	jne    0x7faf796ac652
    7faf796ac63a:	44 8b a5 70 ff ff ff 	mov    -0x90(%rbp),%r12d
    7faf796ac641:	e9 13 00 00 00       	jmpq   0x7faf796ac659
    7faf796ac646:	44 8b a5 30 fe ff ff 	mov    -0x1d0(%rbp),%r12d
    7faf796ac64d:	e9 07 00 00 00       	jmpq   0x7faf796ac659
    7faf796ac652:	44 8b a5 10 fe ff ff 	mov    -0x1f0(%rbp),%r12d
    7faf796ac659:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7faf796ac65f:	d1 e8                	shr    %eax
    7faf796ac661:	83 e0 01             	and    $0x1,%eax
    7faf796ac664:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7faf796ac66a:	8b 8d 38 fe ff ff    	mov    -0x1c8(%rbp),%ecx
    7faf796ac670:	0b c1                	or     %ecx,%eax
    7faf796ac672:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7faf796ac675:	89 8d 00 fe ff ff    	mov    %ecx,-0x200(%rbp)
    7faf796ac67b:	85 c0                	test   %eax,%eax
    7faf796ac67d:	0f 85 0c 00 00 00    	jne    0x7faf796ac68f
    7faf796ac683:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7faf796ac689:	89 85 00 fe ff ff    	mov    %eax,-0x200(%rbp)
    7faf796ac68f:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7faf796ac695:	83 e0 01             	and    $0x1,%eax
    7faf796ac698:	8b 8d 28 fe ff ff    	mov    -0x1d8(%rbp),%ecx
    7faf796ac69e:	23 c1                	and    %ecx,%eax
    7faf796ac6a0:	8b 95 20 fe ff ff    	mov    -0x1e0(%rbp),%edx
    7faf796ac6a6:	0b c2                	or     %edx,%eax
    7faf796ac6a8:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%rbp)
    7faf796ac6ae:	23 8d 08 fe ff ff    	and    -0x1f8(%rbp),%ecx
    7faf796ac6b4:	0b d1                	or     %ecx,%edx
    7faf796ac6b6:	85 d2                	test   %edx,%edx
    7faf796ac6b8:	0f 84 10 00 00 00    	je     0x7faf796ac6ce
    7faf796ac6be:	8b 45 90             	mov    -0x70(%rbp),%eax
    7faf796ac6c1:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7faf796ac6c8:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7faf796ac6ce:	8b 85 f8 fd ff ff    	mov    -0x208(%rbp),%eax
    7faf796ac6d4:	85 c0                	test   %eax,%eax
    7faf796ac6d6:	0f 84 13 00 00 00    	je     0x7faf796ac6ef
    7faf796ac6dc:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7faf796ac6e2:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7faf796ac6e9:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7faf796ac6ef:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7faf796ac6f5:	85 c0                	test   %eax,%eax
    7faf796ac6f7:	0f 84 1a 00 00 00    	je     0x7faf796ac717
    7faf796ac6fd:	41 c7 87 18 01 00 00 	movl   $0x1,0x118(%r15)
    7faf796ac704:	01 00 00 00 
    7faf796ac708:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%rbp)
    7faf796ac70f:	00 00 00 
    7faf796ac712:	e9 10 00 00 00       	jmpq   0x7faf796ac727
    7faf796ac717:	45 89 a7 18 01 00 00 	mov    %r12d,0x118(%r15)
    7faf796ac71e:	41 8b c4             	mov    %r12d,%eax
    7faf796ac721:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7faf796ac727:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7faf796ac72d:	85 c0                	test   %eax,%eax
    7faf796ac72f:	0f 84 13 00 00 00    	je     0x7faf796ac748
    7faf796ac735:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7faf796ac73b:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7faf796ac742:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7faf796ac748:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7faf796ac74e:	85 c0                	test   %eax,%eax
    7faf796ac750:	0f 84 17 00 00 00    	je     0x7faf796ac76d
    7faf796ac756:	41 c7 87 00 01 00 00 	movl   $0x1,0x100(%r15)
    7faf796ac75d:	01 00 00 00 
    7faf796ac761:	c7 45 88 01 00 00 00 	movl   $0x1,-0x78(%rbp)
    7faf796ac768:	e9 0c 00 00 00       	jmpq   0x7faf796ac779
    7faf796ac76d:	41 89 9f 00 01 00 00 	mov    %ebx,0x100(%r15)
    7faf796ac774:	8b c3                	mov    %ebx,%eax
    7faf796ac776:	89 45 88             	mov    %eax,-0x78(%rbp)
    7faf796ac779:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7faf796ac77f:	85 c0                	test   %eax,%eax
    7faf796ac781:	0f 84 2e 00 00 00    	je     0x7faf796ac7b5
    7faf796ac787:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7faf796ac78e:	8b c8                	mov    %eax,%ecx
    7faf796ac790:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7faf796ac796:	41 89 8f f0 00 00 00 	mov    %ecx,0xf0(%r15)
    7faf796ac79d:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7faf796ac7a0:	c1 e8 08             	shr    $0x8,%eax
    7faf796ac7a3:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7faf796ac7a9:	c1 e1 10             	shl    $0x10,%ecx
    7faf796ac7ac:	0b c1                	or     %ecx,%eax
    7faf796ac7ae:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7faf796ac7b5:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7faf796ac7bb:	85 c0                	test   %eax,%eax
    7faf796ac7bd:	0f 84 17 00 00 00    	je     0x7faf796ac7da
    7faf796ac7c3:	41 c7 87 e8 00 00 00 	movl   $0x0,0xe8(%r15)
    7faf796ac7ca:	00 00 00 00 
    7faf796ac7ce:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7faf796ac7d5:	e9 10 00 00 00       	jmpq   0x7faf796ac7ea
    7faf796ac7da:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7faf796ac7e0:	41 89 87 e8 00 00 00 	mov    %eax,0xe8(%r15)
    7faf796ac7e7:	89 45 98             	mov    %eax,-0x68(%rbp)
    7faf796ac7ea:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7faf796ac7f0:	85 c0                	test   %eax,%eax
    7faf796ac7f2:	0f 84 17 00 00 00    	je     0x7faf796ac80f
    7faf796ac7f8:	41 c7 87 e0 00 00 00 	movl   $0x0,0xe0(%r15)
    7faf796ac7ff:	00 00 00 00 
    7faf796ac803:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7faf796ac80a:	e9 1e 00 00 00       	jmpq   0x7faf796ac82d
    7faf796ac80f:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7faf796ac815:	85 c0                	test   %eax,%eax
    7faf796ac817:	0f 84 10 00 00 00    	je     0x7faf796ac82d
    7faf796ac81d:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7faf796ac823:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7faf796ac82a:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7faf796ac82d:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7faf796ac833:	85 c0                	test   %eax,%eax
    7faf796ac835:	0f 84 db 00 00 00    	je     0x7faf796ac916
    7faf796ac83b:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7faf796ac83e:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7faf796ac845:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7faf796ac848:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7faf796ac84b:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7faf796ac852:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7faf796ac855:	8b 45 80             	mov    -0x80(%rbp),%eax
    7faf796ac858:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7faf796ac85f:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7faf796ac862:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7faf796ac865:	41 89 8f b0 00 00 00 	mov    %ecx,0xb0(%r15)
    7faf796ac86c:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7faf796ac86f:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7faf796ac872:	41 89 8f b8 00 00 00 	mov    %ecx,0xb8(%r15)
    7faf796ac879:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7faf796ac87c:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7faf796ac87f:	41 89 8f c0 00 00 00 	mov    %ecx,0xc0(%r15)
    7faf796ac886:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7faf796ac889:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7faf796ac88c:	41 89 97 98 00 00 00 	mov    %edx,0x98(%r15)
    7faf796ac893:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7faf796ac896:	45 89 af a0 00 00 00 	mov    %r13d,0xa0(%r15)
    7faf796ac89d:	41 8b d5             	mov    %r13d,%edx
    7faf796ac8a0:	89 55 d8             	mov    %edx,-0x28(%rbp)
    7faf796ac8a3:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7faf796ac8a6:	41 89 97 a8 00 00 00 	mov    %edx,0xa8(%r15)
    7faf796ac8ad:	4c 8b ea             	mov    %rdx,%r13
    7faf796ac8b0:	41 8b 97 94 00 00 00 	mov    0x94(%r15),%edx
    7faf796ac8b7:	49 8b f7             	mov    %r15,%rsi
    7faf796ac8ba:	48 83 c6 54          	add    $0x54,%rsi
    7faf796ac8be:	8b fa                	mov    %edx,%edi
    7faf796ac8c0:	0f b6 3c 3e          	movzbl (%rsi,%rdi,1),%edi
    7faf796ac8c4:	41 89 7f 4c          	mov    %edi,0x4c(%r15)
    7faf796ac8c8:	89 7d e8             	mov    %edi,-0x18(%rbp)
    7faf796ac8cb:	0f b6 c9             	movzbl %cl,%ecx
    7faf796ac8ce:	8b fa                	mov    %edx,%edi
    7faf796ac8d0:	40 88 0c 3e          	mov    %cl,(%rsi,%rdi,1)
    7faf796ac8d4:	ff ca                	dec    %edx
    7faf796ac8d6:	b9 3e 00 00 00       	mov    $0x3e,%ecx
    7faf796ac8db:	3b d1                	cmp    %ecx,%edx
    7faf796ac8dd:	0f 47 d1             	cmova  %ecx,%edx
    7faf796ac8e0:	41 89 97 94 00 00 00 	mov    %edx,0x94(%r15)
    7faf796ac8e7:	41 8b 4f 48          	mov    0x48(%r15),%ecx
    7faf796ac8eb:	49 8b d7             	mov    %r15,%rdx
    7faf796ac8ee:	48 83 c2 08          	add    $0x8,%rdx
    7faf796ac8f2:	8b f1                	mov    %ecx,%esi
    7faf796ac8f4:	0f b6 34 32          	movzbl (%rdx,%rsi,1),%esi
    7faf796ac8f8:	41 89 37             	mov    %esi,(%r15)
    7faf796ac8fb:	89 75 f0             	mov    %esi,-0x10(%rbp)
    7faf796ac8fe:	0f b6 c0             	movzbl %al,%eax
    7faf796ac901:	8b f1                	mov    %ecx,%esi
    7faf796ac903:	88 04 32             	mov    %al,(%rdx,%rsi,1)
    7faf796ac906:	ff c9                	dec    %ecx
    7faf796ac908:	b8 3e 00 00 00       	mov    $0x3e,%eax
    7faf796ac90d:	3b c8                	cmp    %eax,%ecx
    7faf796ac90f:	0f 47 c8             	cmova  %eax,%ecx
    7faf796ac912:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7faf796ac916:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7faf796ac91c:	85 c0                	test   %eax,%eax
    7faf796ac91e:	0f 84 10 00 00 00    	je     0x7faf796ac934
    7faf796ac924:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7faf796ac92a:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7faf796ac931:	89 45 80             	mov    %eax,-0x80(%rbp)
    7faf796ac934:	8b 45 88             	mov    -0x78(%rbp),%eax
    7faf796ac937:	c1 e8 02             	shr    $0x2,%eax
    7faf796ac93a:	83 e0 01             	and    $0x1,%eax
    7faf796ac93d:	85 c0                	test   %eax,%eax
    7faf796ac93f:	0f 94 c0             	sete   %al
    7faf796ac942:	0f b6 c0             	movzbl %al,%eax
    7faf796ac945:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7faf796ac949:	89 01                	mov    %eax,(%rcx)
    7faf796ac94b:	49 8b 46 30          	mov    0x30(%r14),%rax
    7faf796ac94f:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7faf796ac955:	89 08                	mov    %ecx,(%rax)
    7faf796ac957:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7faf796ac95d:	83 e0 01             	and    $0x1,%eax
    7faf796ac960:	85 c0                	test   %eax,%eax
    7faf796ac962:	0f 94 c0             	sete   %al
    7faf796ac965:	0f b6 c0             	movzbl %al,%eax
    7faf796ac968:	49 8b 4e 38          	mov    0x38(%r14),%rcx
    7faf796ac96c:	89 01                	mov    %eax,(%rcx)
    7faf796ac96e:	49 8b 46 40          	mov    0x40(%r14),%rax
    7faf796ac972:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7faf796ac975:	89 08                	mov    %ecx,(%rax)
    7faf796ac977:	33 c0                	xor    %eax,%eax
    7faf796ac979:	48 8b 1c 24          	mov    (%rsp),%rbx
    7faf796ac97d:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7faf796ac982:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7faf796ac987:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7faf796ac98c:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7faf796ac991:	48 8b e5             	mov    %rbp,%rsp
    7faf796ac994:	5d                   	pop    %rbp
    7faf796ac995:	c3                   	retq   

end

