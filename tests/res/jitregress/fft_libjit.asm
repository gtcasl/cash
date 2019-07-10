function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f5c5a53f12d <.text>:
    7f5c5a53f12d:	55                   	push   %rbp
    7f5c5a53f12e:	48 8b ec             	mov    %rsp,%rbp
    7f5c5a53f131:	48 81 ec c0 04 00 00 	sub    $0x4c0,%rsp
    7f5c5a53f138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f5c5a53f13c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f5c5a53f141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f5c5a53f146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f5c5a53f14b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f5c5a53f150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f5c5a53f154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f5c5a53f158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f5c5a53f15c:	48 8b 00             	mov    (%rax),%rax
    7f5c5a53f15f:	41 8b 8f 40 01 00 00 	mov    0x140(%r15),%ecx
    7f5c5a53f166:	89 4d f0             	mov    %ecx,-0x10(%rbp)
    7f5c5a53f169:	41 8b 8f 48 01 00 00 	mov    0x148(%r15),%ecx
    7f5c5a53f170:	89 4d e8             	mov    %ecx,-0x18(%rbp)
    7f5c5a53f173:	41 8b 8f d4 01 00 00 	mov    0x1d4(%r15),%ecx
    7f5c5a53f17a:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7f5c5a53f17d:	41 8b 8f dc 01 00 00 	mov    0x1dc(%r15),%ecx
    7f5c5a53f184:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7f5c5a53f187:	41 8b 8f ec 01 00 00 	mov    0x1ec(%r15),%ecx
    7f5c5a53f18e:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7f5c5a53f191:	41 8b 8f f4 01 00 00 	mov    0x1f4(%r15),%ecx
    7f5c5a53f198:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7f5c5a53f19b:	41 8b 8f fc 01 00 00 	mov    0x1fc(%r15),%ecx
    7f5c5a53f1a2:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7f5c5a53f1a5:	41 8b 8f 04 02 00 00 	mov    0x204(%r15),%ecx
    7f5c5a53f1ac:	89 4d b8             	mov    %ecx,-0x48(%rbp)
    7f5c5a53f1af:	41 8b 8f 0c 02 00 00 	mov    0x20c(%r15),%ecx
    7f5c5a53f1b6:	89 4d b0             	mov    %ecx,-0x50(%rbp)
    7f5c5a53f1b9:	41 8b 8f 14 02 00 00 	mov    0x214(%r15),%ecx
    7f5c5a53f1c0:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    7f5c5a53f1c3:	41 8b 8f 60 02 00 00 	mov    0x260(%r15),%ecx
    7f5c5a53f1ca:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7f5c5a53f1cd:	41 8b 8f 68 02 00 00 	mov    0x268(%r15),%ecx
    7f5c5a53f1d4:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7f5c5a53f1d7:	41 8b 8f 78 02 00 00 	mov    0x278(%r15),%ecx
    7f5c5a53f1de:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7f5c5a53f1e1:	41 8b 8f 80 02 00 00 	mov    0x280(%r15),%ecx
    7f5c5a53f1e8:	89 4d 88             	mov    %ecx,-0x78(%rbp)
    7f5c5a53f1eb:	41 8b 8f 88 02 00 00 	mov    0x288(%r15),%ecx
    7f5c5a53f1f2:	89 4d 80             	mov    %ecx,-0x80(%rbp)
    7f5c5a53f1f5:	41 8b 8f 90 02 00 00 	mov    0x290(%r15),%ecx
    7f5c5a53f1fc:	89 8d 78 ff ff ff    	mov    %ecx,-0x88(%rbp)
    7f5c5a53f202:	41 8b 8f 98 02 00 00 	mov    0x298(%r15),%ecx
    7f5c5a53f209:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7f5c5a53f20f:	41 8b 8f a0 02 00 00 	mov    0x2a0(%r15),%ecx
    7f5c5a53f216:	89 8d 68 ff ff ff    	mov    %ecx,-0x98(%rbp)
    7f5c5a53f21c:	41 8b 8f b0 02 00 00 	mov    0x2b0(%r15),%ecx
    7f5c5a53f223:	89 8d 60 ff ff ff    	mov    %ecx,-0xa0(%rbp)
    7f5c5a53f229:	41 8b 8f b8 02 00 00 	mov    0x2b8(%r15),%ecx
    7f5c5a53f230:	89 8d 58 ff ff ff    	mov    %ecx,-0xa8(%rbp)
    7f5c5a53f236:	41 8b 8f e4 02 00 00 	mov    0x2e4(%r15),%ecx
    7f5c5a53f23d:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7f5c5a53f243:	41 8b 8f ec 02 00 00 	mov    0x2ec(%r15),%ecx
    7f5c5a53f24a:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%rbp)
    7f5c5a53f250:	41 8b 8f fc 02 00 00 	mov    0x2fc(%r15),%ecx
    7f5c5a53f257:	89 8d 40 ff ff ff    	mov    %ecx,-0xc0(%rbp)
    7f5c5a53f25d:	41 8b 8f 04 03 00 00 	mov    0x304(%r15),%ecx
    7f5c5a53f264:	89 8d 38 ff ff ff    	mov    %ecx,-0xc8(%rbp)
    7f5c5a53f26a:	41 8b 8f 0c 03 00 00 	mov    0x30c(%r15),%ecx
    7f5c5a53f271:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7f5c5a53f277:	41 8b 8f 14 03 00 00 	mov    0x314(%r15),%ecx
    7f5c5a53f27e:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7f5c5a53f284:	41 8b 8f 1c 03 00 00 	mov    0x31c(%r15),%ecx
    7f5c5a53f28b:	89 8d 20 ff ff ff    	mov    %ecx,-0xe0(%rbp)
    7f5c5a53f291:	41 8b 8f 24 03 00 00 	mov    0x324(%r15),%ecx
    7f5c5a53f298:	89 8d 18 ff ff ff    	mov    %ecx,-0xe8(%rbp)
    7f5c5a53f29e:	41 8b 8f 40 03 00 00 	mov    0x340(%r15),%ecx
    7f5c5a53f2a5:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7f5c5a53f2ab:	41 8b 8f 48 03 00 00 	mov    0x348(%r15),%ecx
    7f5c5a53f2b2:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7f5c5a53f2b8:	41 8b 8f 58 03 00 00 	mov    0x358(%r15),%ecx
    7f5c5a53f2bf:	89 8d 00 ff ff ff    	mov    %ecx,-0x100(%rbp)
    7f5c5a53f2c5:	41 8b 8f 60 03 00 00 	mov    0x360(%r15),%ecx
    7f5c5a53f2cc:	89 8d f8 fe ff ff    	mov    %ecx,-0x108(%rbp)
    7f5c5a53f2d2:	41 8b 8f 68 03 00 00 	mov    0x368(%r15),%ecx
    7f5c5a53f2d9:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7f5c5a53f2df:	41 8b 8f 70 03 00 00 	mov    0x370(%r15),%ecx
    7f5c5a53f2e6:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7f5c5a53f2ec:	41 8b 8f 78 03 00 00 	mov    0x378(%r15),%ecx
    7f5c5a53f2f3:	89 8d e0 fe ff ff    	mov    %ecx,-0x120(%rbp)
    7f5c5a53f2f9:	41 8b 8f 80 03 00 00 	mov    0x380(%r15),%ecx
    7f5c5a53f300:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7f5c5a53f306:	41 8b 8f 90 03 00 00 	mov    0x390(%r15),%ecx
    7f5c5a53f30d:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7f5c5a53f313:	41 8b 8f 98 03 00 00 	mov    0x398(%r15),%ecx
    7f5c5a53f31a:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7f5c5a53f320:	41 8b 8f a8 03 00 00 	mov    0x3a8(%r15),%ecx
    7f5c5a53f327:	89 8d c0 fe ff ff    	mov    %ecx,-0x140(%rbp)
    7f5c5a53f32d:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7f5c5a53f334:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7f5c5a53f33a:	41 8b 8f c0 03 00 00 	mov    0x3c0(%r15),%ecx
    7f5c5a53f341:	89 8d b0 fe ff ff    	mov    %ecx,-0x150(%rbp)
    7f5c5a53f347:	41 8b 8f c8 03 00 00 	mov    0x3c8(%r15),%ecx
    7f5c5a53f34e:	89 8d a8 fe ff ff    	mov    %ecx,-0x158(%rbp)
    7f5c5a53f354:	41 8b 8f d0 03 00 00 	mov    0x3d0(%r15),%ecx
    7f5c5a53f35b:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7f5c5a53f361:	41 8b 8f d8 03 00 00 	mov    0x3d8(%r15),%ecx
    7f5c5a53f368:	89 8d 98 fe ff ff    	mov    %ecx,-0x168(%rbp)
    7f5c5a53f36e:	41 8b 8f e0 03 00 00 	mov    0x3e0(%r15),%ecx
    7f5c5a53f375:	89 8d 90 fe ff ff    	mov    %ecx,-0x170(%rbp)
    7f5c5a53f37b:	41 8b 8f e8 03 00 00 	mov    0x3e8(%r15),%ecx
    7f5c5a53f382:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7f5c5a53f388:	41 8b 8f f0 03 00 00 	mov    0x3f0(%r15),%ecx
    7f5c5a53f38f:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7f5c5a53f395:	41 8b 8f f8 03 00 00 	mov    0x3f8(%r15),%ecx
    7f5c5a53f39c:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7f5c5a53f3a2:	41 8b 8f 08 04 00 00 	mov    0x408(%r15),%ecx
    7f5c5a53f3a9:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7f5c5a53f3af:	41 8b 9f 10 04 00 00 	mov    0x410(%r15),%ebx
    7f5c5a53f3b6:	41 8b 8f 18 04 00 00 	mov    0x418(%r15),%ecx
    7f5c5a53f3bd:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7f5c5a53f3c3:	41 8b 8f 20 04 00 00 	mov    0x420(%r15),%ecx
    7f5c5a53f3ca:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7f5c5a53f3d0:	41 8b 8f 28 04 00 00 	mov    0x428(%r15),%ecx
    7f5c5a53f3d7:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7f5c5a53f3dd:	41 8b 8f 30 04 00 00 	mov    0x430(%r15),%ecx
    7f5c5a53f3e4:	89 8d 50 fe ff ff    	mov    %ecx,-0x1b0(%rbp)
    7f5c5a53f3ea:	41 8b 8f 38 04 00 00 	mov    0x438(%r15),%ecx
    7f5c5a53f3f1:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7f5c5a53f3f7:	48 89 85 40 fe ff ff 	mov    %rax,-0x1c0(%rbp)
    7f5c5a53f3fe:	48 8b 40 18          	mov    0x18(%rax),%rax
    7f5c5a53f402:	8b 00                	mov    (%rax),%eax
    7f5c5a53f404:	41 8b 8f 40 04 00 00 	mov    0x440(%r15),%ecx
    7f5c5a53f40b:	33 c8                	xor    %eax,%ecx
    7f5c5a53f40d:	23 c8                	and    %eax,%ecx
    7f5c5a53f40f:	41 89 87 40 04 00 00 	mov    %eax,0x440(%r15)
    7f5c5a53f416:	85 c9                	test   %ecx,%ecx
    7f5c5a53f418:	0f 84 9c 16 00 00    	je     0x7f5c5a540aba
    7f5c5a53f41e:	33 c0                	xor    %eax,%eax
    7f5c5a53f420:	3b 85 70 fe ff ff    	cmp    -0x190(%rbp),%eax
    7f5c5a53f426:	0f 94 c0             	sete   %al
    7f5c5a53f429:	0f b6 c0             	movzbl %al,%eax
    7f5c5a53f42c:	85 c0                	test   %eax,%eax
    7f5c5a53f42e:	0f 94 c0             	sete   %al
    7f5c5a53f431:	0f b6 c0             	movzbl %al,%eax
    7f5c5a53f434:	8b cb                	mov    %ebx,%ecx
    7f5c5a53f436:	83 e1 01             	and    $0x1,%ecx
    7f5c5a53f439:	85 c9                	test   %ecx,%ecx
    7f5c5a53f43b:	0f 94 c1             	sete   %cl
    7f5c5a53f43e:	0f b6 c9             	movzbl %cl,%ecx
    7f5c5a53f441:	85 c9                	test   %ecx,%ecx
    7f5c5a53f443:	0f 94 c2             	sete   %dl
    7f5c5a53f446:	0f b6 d2             	movzbl %dl,%edx
    7f5c5a53f449:	23 c2                	and    %edx,%eax
    7f5c5a53f44b:	85 c0                	test   %eax,%eax
    7f5c5a53f44d:	0f 94 c0             	sete   %al
    7f5c5a53f450:	0f b6 c0             	movzbl %al,%eax
    7f5c5a53f453:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7f5c5a53f459:	23 d0                	and    %eax,%edx
    7f5c5a53f45b:	8b b5 58 fe ff ff    	mov    -0x1a8(%rbp),%esi
    7f5c5a53f461:	c1 ee 02             	shr    $0x2,%esi
    7f5c5a53f464:	83 e6 01             	and    $0x1,%esi
    7f5c5a53f467:	85 f6                	test   %esi,%esi
    7f5c5a53f469:	40 0f 94 c6          	sete   %sil
    7f5c5a53f46d:	40 0f b6 f6          	movzbl %sil,%esi
    7f5c5a53f471:	89 b5 38 fe ff ff    	mov    %esi,-0x1c8(%rbp)
    7f5c5a53f477:	85 f6                	test   %esi,%esi
    7f5c5a53f479:	40 0f 94 c6          	sete   %sil
    7f5c5a53f47d:	40 0f b6 f6          	movzbl %sil,%esi
    7f5c5a53f481:	89 95 30 fe ff ff    	mov    %edx,-0x1d0(%rbp)
    7f5c5a53f487:	23 d6                	and    %esi,%edx
    7f5c5a53f489:	85 d2                	test   %edx,%edx
    7f5c5a53f48b:	0f 94 c2             	sete   %dl
    7f5c5a53f48e:	0f b6 d2             	movzbl %dl,%edx
    7f5c5a53f491:	89 8d 28 fe ff ff    	mov    %ecx,-0x1d8(%rbp)
    7f5c5a53f497:	23 ca                	and    %edx,%ecx
    7f5c5a53f499:	89 95 20 fe ff ff    	mov    %edx,-0x1e0(%rbp)
    7f5c5a53f49f:	23 c2                	and    %edx,%eax
    7f5c5a53f4a1:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7f5c5a53f4a7:	4c 8b f0             	mov    %rax,%r14
    7f5c5a53f4aa:	23 c8                	and    %eax,%ecx
    7f5c5a53f4ac:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f5c5a53f4af:	ff c0                	inc    %eax
    7f5c5a53f4b1:	83 e0 3f             	and    $0x3f,%eax
    7f5c5a53f4b4:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7f5c5a53f4ba:	85 c9                	test   %ecx,%ecx
    7f5c5a53f4bc:	0f 85 09 00 00 00    	jne    0x7f5c5a53f4cb
    7f5c5a53f4c2:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f5c5a53f4c5:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7f5c5a53f4cb:	48 8b 85 40 fe ff ff 	mov    -0x1c0(%rbp),%rax
    7f5c5a53f4d2:	48 8b 40 20          	mov    0x20(%rax),%rax
    7f5c5a53f4d6:	44 8b 28             	mov    (%rax),%r13d
    7f5c5a53f4d9:	45 8b e5             	mov    %r13d,%r12d
    7f5c5a53f4dc:	41 83 cc 00          	or     $0x0,%r12d
    7f5c5a53f4e0:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f5c5a53f4e3:	c1 e8 05             	shr    $0x5,%eax
    7f5c5a53f4e6:	83 e0 01             	and    $0x1,%eax
    7f5c5a53f4e9:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7f5c5a53f4ec:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53f4ef:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f4f5:	8b 95 68 fe ff ff    	mov    -0x198(%rbp),%edx
    7f5c5a53f4fb:	c1 ea 10             	shr    $0x10,%edx
    7f5c5a53f4fe:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f504:	89 8d 08 fe ff ff    	mov    %ecx,-0x1f8(%rbp)
    7f5c5a53f50a:	89 95 00 fe ff ff    	mov    %edx,-0x200(%rbp)
    7f5c5a53f510:	2b ca                	sub    %edx,%ecx
    7f5c5a53f512:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f518:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f5c5a53f51b:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f521:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7f5c5a53f527:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53f52d:	89 95 f8 fd ff ff    	mov    %edx,-0x208(%rbp)
    7f5c5a53f533:	89 b5 f0 fd ff ff    	mov    %esi,-0x210(%rbp)
    7f5c5a53f539:	2b d6                	sub    %esi,%edx
    7f5c5a53f53b:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f541:	c1 e1 10             	shl    $0x10,%ecx
    7f5c5a53f544:	0b d1                	or     %ecx,%edx
    7f5c5a53f546:	89 95 e8 fd ff ff    	mov    %edx,-0x218(%rbp)
    7f5c5a53f54c:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7f5c5a53f552:	85 c0                	test   %eax,%eax
    7f5c5a53f554:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f566
    7f5c5a53f55a:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f5c5a53f560:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%rbp)
    7f5c5a53f566:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f5c5a53f56c:	03 85 00 fe ff ff    	add    -0x200(%rbp),%eax
    7f5c5a53f572:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53f577:	8b 8d f8 fd ff ff    	mov    -0x208(%rbp),%ecx
    7f5c5a53f57d:	03 8d f0 fd ff ff    	add    -0x210(%rbp),%ecx
    7f5c5a53f583:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f589:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53f58c:	0b c8                	or     %eax,%ecx
    7f5c5a53f58e:	89 8d d8 fd ff ff    	mov    %ecx,-0x228(%rbp)
    7f5c5a53f594:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7f5c5a53f59a:	85 c0                	test   %eax,%eax
    7f5c5a53f59c:	0f 85 09 00 00 00    	jne    0x7f5c5a53f5ab
    7f5c5a53f5a2:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7f5c5a53f5a5:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7f5c5a53f5ab:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f5c5a53f5ae:	41 23 c6             	and    %r14d,%eax
    7f5c5a53f5b1:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7f5c5a53f5b4:	ff c1                	inc    %ecx
    7f5c5a53f5b6:	83 e1 3f             	and    $0x3f,%ecx
    7f5c5a53f5b9:	89 8d d0 fd ff ff    	mov    %ecx,-0x230(%rbp)
    7f5c5a53f5bf:	85 c0                	test   %eax,%eax
    7f5c5a53f5c1:	0f 85 09 00 00 00    	jne    0x7f5c5a53f5d0
    7f5c5a53f5c7:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f5c5a53f5ca:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7f5c5a53f5d0:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f5c5a53f5d3:	c1 e8 05             	shr    $0x5,%eax
    7f5c5a53f5d6:	83 e0 01             	and    $0x1,%eax
    7f5c5a53f5d9:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7f5c5a53f5dc:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53f5df:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f5e5:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7f5c5a53f5e8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f5ee:	f7 da                	neg    %edx
    7f5c5a53f5f0:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f5f6:	c1 e2 10             	shl    $0x10,%edx
    7f5c5a53f5f9:	0b ca                	or     %edx,%ecx
    7f5c5a53f5fb:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7f5c5a53f601:	85 c0                	test   %eax,%eax
    7f5c5a53f603:	0f 85 09 00 00 00    	jne    0x7f5c5a53f612
    7f5c5a53f609:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f5c5a53f60c:	89 85 c8 fd ff ff    	mov    %eax,-0x238(%rbp)
    7f5c5a53f612:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f5c5a53f615:	41 23 c6             	and    %r14d,%eax
    7f5c5a53f618:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7f5c5a53f61b:	ff c1                	inc    %ecx
    7f5c5a53f61d:	83 e1 1f             	and    $0x1f,%ecx
    7f5c5a53f620:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7f5c5a53f626:	85 c0                	test   %eax,%eax
    7f5c5a53f628:	0f 85 09 00 00 00    	jne    0x7f5c5a53f637
    7f5c5a53f62e:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f5c5a53f631:	89 85 c0 fd ff ff    	mov    %eax,-0x240(%rbp)
    7f5c5a53f637:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f5c5a53f63a:	c1 e8 04             	shr    $0x4,%eax
    7f5c5a53f63d:	83 e0 01             	and    $0x1,%eax
    7f5c5a53f640:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7f5c5a53f643:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53f646:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f64c:	8b 55 c8             	mov    -0x38(%rbp),%edx
    7f5c5a53f64f:	c1 ea 10             	shr    $0x10,%edx
    7f5c5a53f652:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f658:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7f5c5a53f65e:	89 95 b0 fd ff ff    	mov    %edx,-0x250(%rbp)
    7f5c5a53f664:	2b ca                	sub    %edx,%ecx
    7f5c5a53f666:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f66c:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7f5c5a53f66f:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f675:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7f5c5a53f678:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53f67e:	89 95 a8 fd ff ff    	mov    %edx,-0x258(%rbp)
    7f5c5a53f684:	89 b5 a0 fd ff ff    	mov    %esi,-0x260(%rbp)
    7f5c5a53f68a:	2b d6                	sub    %esi,%edx
    7f5c5a53f68c:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f692:	c1 e1 10             	shl    $0x10,%ecx
    7f5c5a53f695:	0b d1                	or     %ecx,%edx
    7f5c5a53f697:	89 95 98 fd ff ff    	mov    %edx,-0x268(%rbp)
    7f5c5a53f69d:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7f5c5a53f6a3:	85 c0                	test   %eax,%eax
    7f5c5a53f6a5:	0f 85 09 00 00 00    	jne    0x7f5c5a53f6b4
    7f5c5a53f6ab:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7f5c5a53f6ae:	89 85 98 fd ff ff    	mov    %eax,-0x268(%rbp)
    7f5c5a53f6b4:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7f5c5a53f6ba:	03 85 b0 fd ff ff    	add    -0x250(%rbp),%eax
    7f5c5a53f6c0:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53f6c5:	8b 8d a8 fd ff ff    	mov    -0x258(%rbp),%ecx
    7f5c5a53f6cb:	03 8d a0 fd ff ff    	add    -0x260(%rbp),%ecx
    7f5c5a53f6d1:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f6d7:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53f6da:	0b c8                	or     %eax,%ecx
    7f5c5a53f6dc:	89 8d 88 fd ff ff    	mov    %ecx,-0x278(%rbp)
    7f5c5a53f6e2:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f5c5a53f6e8:	85 c0                	test   %eax,%eax
    7f5c5a53f6ea:	0f 85 09 00 00 00    	jne    0x7f5c5a53f6f9
    7f5c5a53f6f0:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f5c5a53f6f3:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7f5c5a53f6f9:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f5c5a53f6fc:	41 23 c6             	and    %r14d,%eax
    7f5c5a53f6ff:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7f5c5a53f702:	ff c1                	inc    %ecx
    7f5c5a53f704:	83 e1 3f             	and    $0x3f,%ecx
    7f5c5a53f707:	89 8d 80 fd ff ff    	mov    %ecx,-0x280(%rbp)
    7f5c5a53f70d:	85 c0                	test   %eax,%eax
    7f5c5a53f70f:	0f 85 09 00 00 00    	jne    0x7f5c5a53f71e
    7f5c5a53f715:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f5c5a53f718:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f5c5a53f71e:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f5c5a53f721:	8b c0                	mov    %eax,%eax
    7f5c5a53f723:	41 8b 04 87          	mov    (%r15,%rax,4),%eax
    7f5c5a53f727:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7f5c5a53f72d:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f5c5a53f730:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53f735:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7f5c5a53f738:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f73e:	0f b7 d0             	movzwl %ax,%edx
    7f5c5a53f741:	0f bf d2             	movswl %dx,%edx
    7f5c5a53f744:	0f b7 f1             	movzwl %cx,%esi
    7f5c5a53f747:	0f bf f6             	movswl %si,%esi
    7f5c5a53f74a:	0f af d6             	imul   %esi,%edx
    7f5c5a53f74d:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53f753:	8b 75 80             	mov    -0x80(%rbp),%esi
    7f5c5a53f756:	c1 ee 10             	shr    $0x10,%esi
    7f5c5a53f759:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53f75f:	8b 7d 88             	mov    -0x78(%rbp),%edi
    7f5c5a53f762:	c1 ef 10             	shr    $0x10,%edi
    7f5c5a53f765:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7f5c5a53f76b:	44 0f b7 c6          	movzwl %si,%r8d
    7f5c5a53f76f:	45 0f bf c0          	movswl %r8w,%r8d
    7f5c5a53f773:	44 0f b7 cf          	movzwl %di,%r9d
    7f5c5a53f777:	45 0f bf c9          	movswl %r9w,%r9d
    7f5c5a53f77b:	45 0f af c1          	imul   %r9d,%r8d
    7f5c5a53f77f:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7f5c5a53f786:	41 2b d0             	sub    %r8d,%edx
    7f5c5a53f789:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53f78f:	c1 ea 0f             	shr    $0xf,%edx
    7f5c5a53f792:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f798:	89 95 70 fd ff ff    	mov    %edx,-0x290(%rbp)
    7f5c5a53f79e:	0f b7 f6             	movzwl %si,%esi
    7f5c5a53f7a1:	0f bf d6             	movswl %si,%edx
    7f5c5a53f7a4:	0f b7 c9             	movzwl %cx,%ecx
    7f5c5a53f7a7:	0f bf c9             	movswl %cx,%ecx
    7f5c5a53f7aa:	0f af d1             	imul   %ecx,%edx
    7f5c5a53f7ad:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53f7b3:	0f b7 c0             	movzwl %ax,%eax
    7f5c5a53f7b6:	0f bf c0             	movswl %ax,%eax
    7f5c5a53f7b9:	0f b7 ff             	movzwl %di,%edi
    7f5c5a53f7bc:	0f bf cf             	movswl %di,%ecx
    7f5c5a53f7bf:	0f af c1             	imul   %ecx,%eax
    7f5c5a53f7c2:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7f5c5a53f7c7:	03 d0                	add    %eax,%edx
    7f5c5a53f7c9:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53f7cf:	c1 ea 0f             	shr    $0xf,%edx
    7f5c5a53f7d2:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f7d8:	89 95 68 fd ff ff    	mov    %edx,-0x298(%rbp)
    7f5c5a53f7de:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7f5c5a53f7e4:	41 23 c6             	and    %r14d,%eax
    7f5c5a53f7e7:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7f5c5a53f7ed:	ff c1                	inc    %ecx
    7f5c5a53f7ef:	83 e1 0f             	and    $0xf,%ecx
    7f5c5a53f7f2:	89 8d 60 fd ff ff    	mov    %ecx,-0x2a0(%rbp)
    7f5c5a53f7f8:	85 c0                	test   %eax,%eax
    7f5c5a53f7fa:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f80c
    7f5c5a53f800:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f5c5a53f806:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f5c5a53f80c:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f5c5a53f812:	c1 e8 03             	shr    $0x3,%eax
    7f5c5a53f815:	83 e0 01             	and    $0x1,%eax
    7f5c5a53f818:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7f5c5a53f81e:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53f821:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f827:	89 8d 58 fd ff ff    	mov    %ecx,-0x2a8(%rbp)
    7f5c5a53f82d:	8b 95 70 ff ff ff    	mov    -0x90(%rbp),%edx
    7f5c5a53f833:	2b ca                	sub    %edx,%ecx
    7f5c5a53f835:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f83b:	8b b5 58 ff ff ff    	mov    -0xa8(%rbp),%esi
    7f5c5a53f841:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53f847:	89 b5 50 fd ff ff    	mov    %esi,-0x2b0(%rbp)
    7f5c5a53f84d:	8b bd 78 ff ff ff    	mov    -0x88(%rbp),%edi
    7f5c5a53f853:	2b f7                	sub    %edi,%esi
    7f5c5a53f855:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53f85b:	c1 e1 10             	shl    $0x10,%ecx
    7f5c5a53f85e:	0b f1                	or     %ecx,%esi
    7f5c5a53f860:	89 b5 48 fd ff ff    	mov    %esi,-0x2b8(%rbp)
    7f5c5a53f866:	c1 e2 10             	shl    $0x10,%edx
    7f5c5a53f869:	0b fa                	or     %edx,%edi
    7f5c5a53f86b:	89 bd 40 fd ff ff    	mov    %edi,-0x2c0(%rbp)
    7f5c5a53f871:	89 85 38 fd ff ff    	mov    %eax,-0x2c8(%rbp)
    7f5c5a53f877:	85 c0                	test   %eax,%eax
    7f5c5a53f879:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f88b
    7f5c5a53f87f:	8b 85 40 fd ff ff    	mov    -0x2c0(%rbp),%eax
    7f5c5a53f885:	89 85 48 fd ff ff    	mov    %eax,-0x2b8(%rbp)
    7f5c5a53f88b:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7f5c5a53f891:	03 85 70 ff ff ff    	add    -0x90(%rbp),%eax
    7f5c5a53f897:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53f89c:	8b 8d 50 fd ff ff    	mov    -0x2b0(%rbp),%ecx
    7f5c5a53f8a2:	03 8d 78 ff ff ff    	add    -0x88(%rbp),%ecx
    7f5c5a53f8a8:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f8ae:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53f8b1:	0b c8                	or     %eax,%ecx
    7f5c5a53f8b3:	89 8d 30 fd ff ff    	mov    %ecx,-0x2d0(%rbp)
    7f5c5a53f8b9:	8b 85 38 fd ff ff    	mov    -0x2c8(%rbp),%eax
    7f5c5a53f8bf:	85 c0                	test   %eax,%eax
    7f5c5a53f8c1:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f8d3
    7f5c5a53f8c7:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f5c5a53f8cd:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7f5c5a53f8d3:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f5c5a53f8d9:	41 23 c6             	and    %r14d,%eax
    7f5c5a53f8dc:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7f5c5a53f8e2:	ff c1                	inc    %ecx
    7f5c5a53f8e4:	83 e1 0f             	and    $0xf,%ecx
    7f5c5a53f8e7:	89 8d 28 fd ff ff    	mov    %ecx,-0x2d8(%rbp)
    7f5c5a53f8ed:	85 c0                	test   %eax,%eax
    7f5c5a53f8ef:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f901
    7f5c5a53f8f5:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f5c5a53f8fb:	89 85 28 fd ff ff    	mov    %eax,-0x2d8(%rbp)
    7f5c5a53f901:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f5c5a53f907:	c1 e8 03             	shr    $0x3,%eax
    7f5c5a53f90a:	83 e0 01             	and    $0x1,%eax
    7f5c5a53f90d:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7f5c5a53f913:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53f916:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f91c:	8b 95 50 ff ff ff    	mov    -0xb0(%rbp),%edx
    7f5c5a53f922:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f928:	f7 da                	neg    %edx
    7f5c5a53f92a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f930:	c1 e2 10             	shl    $0x10,%edx
    7f5c5a53f933:	0b ca                	or     %edx,%ecx
    7f5c5a53f935:	89 8d 20 fd ff ff    	mov    %ecx,-0x2e0(%rbp)
    7f5c5a53f93b:	85 c0                	test   %eax,%eax
    7f5c5a53f93d:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f94f
    7f5c5a53f943:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7f5c5a53f949:	89 85 20 fd ff ff    	mov    %eax,-0x2e0(%rbp)
    7f5c5a53f94f:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f5c5a53f955:	41 23 c6             	and    %r14d,%eax
    7f5c5a53f958:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7f5c5a53f95e:	ff c1                	inc    %ecx
    7f5c5a53f960:	83 e1 07             	and    $0x7,%ecx
    7f5c5a53f963:	89 8d 18 fd ff ff    	mov    %ecx,-0x2e8(%rbp)
    7f5c5a53f969:	85 c0                	test   %eax,%eax
    7f5c5a53f96b:	0f 85 0c 00 00 00    	jne    0x7f5c5a53f97d
    7f5c5a53f971:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f5c5a53f977:	89 85 18 fd ff ff    	mov    %eax,-0x2e8(%rbp)
    7f5c5a53f97d:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f5c5a53f983:	c1 e8 02             	shr    $0x2,%eax
    7f5c5a53f986:	83 e0 01             	and    $0x1,%eax
    7f5c5a53f989:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7f5c5a53f98f:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53f992:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f998:	8b 95 38 ff ff ff    	mov    -0xc8(%rbp),%edx
    7f5c5a53f99e:	c1 ea 10             	shr    $0x10,%edx
    7f5c5a53f9a1:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f9a7:	89 8d 10 fd ff ff    	mov    %ecx,-0x2f0(%rbp)
    7f5c5a53f9ad:	89 95 08 fd ff ff    	mov    %edx,-0x2f8(%rbp)
    7f5c5a53f9b3:	2b ca                	sub    %edx,%ecx
    7f5c5a53f9b5:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53f9bb:	8b 95 18 ff ff ff    	mov    -0xe8(%rbp),%edx
    7f5c5a53f9c1:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f9c7:	8b b5 38 ff ff ff    	mov    -0xc8(%rbp),%esi
    7f5c5a53f9cd:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53f9d3:	89 95 00 fd ff ff    	mov    %edx,-0x300(%rbp)
    7f5c5a53f9d9:	89 b5 f8 fc ff ff    	mov    %esi,-0x308(%rbp)
    7f5c5a53f9df:	2b d6                	sub    %esi,%edx
    7f5c5a53f9e1:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53f9e7:	c1 e1 10             	shl    $0x10,%ecx
    7f5c5a53f9ea:	0b d1                	or     %ecx,%edx
    7f5c5a53f9ec:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7f5c5a53f9f2:	89 85 e8 fc ff ff    	mov    %eax,-0x318(%rbp)
    7f5c5a53f9f8:	85 c0                	test   %eax,%eax
    7f5c5a53f9fa:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fa0c
    7f5c5a53fa00:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f5c5a53fa06:	89 85 f0 fc ff ff    	mov    %eax,-0x310(%rbp)
    7f5c5a53fa0c:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7f5c5a53fa12:	03 85 08 fd ff ff    	add    -0x2f8(%rbp),%eax
    7f5c5a53fa18:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53fa1d:	8b 8d 00 fd ff ff    	mov    -0x300(%rbp),%ecx
    7f5c5a53fa23:	03 8d f8 fc ff ff    	add    -0x308(%rbp),%ecx
    7f5c5a53fa29:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fa2f:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53fa32:	0b c8                	or     %eax,%ecx
    7f5c5a53fa34:	89 8d e0 fc ff ff    	mov    %ecx,-0x320(%rbp)
    7f5c5a53fa3a:	8b 85 e8 fc ff ff    	mov    -0x318(%rbp),%eax
    7f5c5a53fa40:	85 c0                	test   %eax,%eax
    7f5c5a53fa42:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fa54
    7f5c5a53fa48:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f5c5a53fa4e:	89 85 e0 fc ff ff    	mov    %eax,-0x320(%rbp)
    7f5c5a53fa54:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f5c5a53fa5a:	41 23 c6             	and    %r14d,%eax
    7f5c5a53fa5d:	8b 8d 00 ff ff ff    	mov    -0x100(%rbp),%ecx
    7f5c5a53fa63:	ff c1                	inc    %ecx
    7f5c5a53fa65:	83 e1 0f             	and    $0xf,%ecx
    7f5c5a53fa68:	89 8d d8 fc ff ff    	mov    %ecx,-0x328(%rbp)
    7f5c5a53fa6e:	85 c0                	test   %eax,%eax
    7f5c5a53fa70:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fa82
    7f5c5a53fa76:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f5c5a53fa7c:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f5c5a53fa82:	49 8b c7             	mov    %r15,%rax
    7f5c5a53fa85:	48 05 00 01 00 00    	add    $0x100,%rax
    7f5c5a53fa8b:	8b 8d 00 ff ff ff    	mov    -0x100(%rbp),%ecx
    7f5c5a53fa91:	8b c9                	mov    %ecx,%ecx
    7f5c5a53fa93:	8b 04 88             	mov    (%rax,%rcx,4),%eax
    7f5c5a53fa96:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7f5c5a53fa9c:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f5c5a53faa2:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53faa7:	8b 8d f8 fe ff ff    	mov    -0x108(%rbp),%ecx
    7f5c5a53faad:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fab3:	0f b7 d0             	movzwl %ax,%edx
    7f5c5a53fab6:	0f bf d2             	movswl %dx,%edx
    7f5c5a53fab9:	0f b7 f1             	movzwl %cx,%esi
    7f5c5a53fabc:	0f bf f6             	movswl %si,%esi
    7f5c5a53fabf:	0f af d6             	imul   %esi,%edx
    7f5c5a53fac2:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53fac8:	8b b5 f0 fe ff ff    	mov    -0x110(%rbp),%esi
    7f5c5a53face:	c1 ee 10             	shr    $0x10,%esi
    7f5c5a53fad1:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53fad7:	8b bd f8 fe ff ff    	mov    -0x108(%rbp),%edi
    7f5c5a53fadd:	c1 ef 10             	shr    $0x10,%edi
    7f5c5a53fae0:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7f5c5a53fae6:	44 0f b7 c6          	movzwl %si,%r8d
    7f5c5a53faea:	45 0f bf c0          	movswl %r8w,%r8d
    7f5c5a53faee:	44 0f b7 cf          	movzwl %di,%r9d
    7f5c5a53faf2:	45 0f bf c9          	movswl %r9w,%r9d
    7f5c5a53faf6:	45 0f af c1          	imul   %r9d,%r8d
    7f5c5a53fafa:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7f5c5a53fb01:	41 2b d0             	sub    %r8d,%edx
    7f5c5a53fb04:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53fb0a:	c1 ea 0f             	shr    $0xf,%edx
    7f5c5a53fb0d:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53fb13:	89 95 c8 fc ff ff    	mov    %edx,-0x338(%rbp)
    7f5c5a53fb19:	0f b7 f6             	movzwl %si,%esi
    7f5c5a53fb1c:	0f bf d6             	movswl %si,%edx
    7f5c5a53fb1f:	0f b7 c9             	movzwl %cx,%ecx
    7f5c5a53fb22:	0f bf c9             	movswl %cx,%ecx
    7f5c5a53fb25:	0f af d1             	imul   %ecx,%edx
    7f5c5a53fb28:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53fb2e:	0f b7 c0             	movzwl %ax,%eax
    7f5c5a53fb31:	0f bf c0             	movswl %ax,%eax
    7f5c5a53fb34:	0f b7 ff             	movzwl %di,%edi
    7f5c5a53fb37:	0f bf cf             	movswl %di,%ecx
    7f5c5a53fb3a:	0f af c1             	imul   %ecx,%eax
    7f5c5a53fb3d:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7f5c5a53fb42:	03 d0                	add    %eax,%edx
    7f5c5a53fb44:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f5c5a53fb4a:	c1 ea 0f             	shr    $0xf,%edx
    7f5c5a53fb4d:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53fb53:	89 95 c0 fc ff ff    	mov    %edx,-0x340(%rbp)
    7f5c5a53fb59:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7f5c5a53fb5f:	41 23 c6             	and    %r14d,%eax
    7f5c5a53fb62:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f5c5a53fb68:	ff c1                	inc    %ecx
    7f5c5a53fb6a:	83 e1 03             	and    $0x3,%ecx
    7f5c5a53fb6d:	89 8d b8 fc ff ff    	mov    %ecx,-0x348(%rbp)
    7f5c5a53fb73:	85 c0                	test   %eax,%eax
    7f5c5a53fb75:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fb87
    7f5c5a53fb7b:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7f5c5a53fb81:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7f5c5a53fb87:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7f5c5a53fb8d:	d1 e8                	shr    %eax
    7f5c5a53fb8f:	83 e0 01             	and    $0x1,%eax
    7f5c5a53fb92:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7f5c5a53fb98:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53fb9b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fba1:	89 8d b0 fc ff ff    	mov    %ecx,-0x350(%rbp)
    7f5c5a53fba7:	8b 95 e0 fe ff ff    	mov    -0x120(%rbp),%edx
    7f5c5a53fbad:	2b ca                	sub    %edx,%ecx
    7f5c5a53fbaf:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fbb5:	8b b5 c8 fe ff ff    	mov    -0x138(%rbp),%esi
    7f5c5a53fbbb:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53fbc1:	89 b5 a8 fc ff ff    	mov    %esi,-0x358(%rbp)
    7f5c5a53fbc7:	8b bd e8 fe ff ff    	mov    -0x118(%rbp),%edi
    7f5c5a53fbcd:	2b f7                	sub    %edi,%esi
    7f5c5a53fbcf:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f5c5a53fbd5:	c1 e1 10             	shl    $0x10,%ecx
    7f5c5a53fbd8:	0b f1                	or     %ecx,%esi
    7f5c5a53fbda:	89 b5 a0 fc ff ff    	mov    %esi,-0x360(%rbp)
    7f5c5a53fbe0:	c1 e2 10             	shl    $0x10,%edx
    7f5c5a53fbe3:	0b fa                	or     %edx,%edi
    7f5c5a53fbe5:	89 bd 98 fc ff ff    	mov    %edi,-0x368(%rbp)
    7f5c5a53fbeb:	89 85 90 fc ff ff    	mov    %eax,-0x370(%rbp)
    7f5c5a53fbf1:	85 c0                	test   %eax,%eax
    7f5c5a53fbf3:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fc05
    7f5c5a53fbf9:	8b 85 98 fc ff ff    	mov    -0x368(%rbp),%eax
    7f5c5a53fbff:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7f5c5a53fc05:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7f5c5a53fc0b:	03 85 e0 fe ff ff    	add    -0x120(%rbp),%eax
    7f5c5a53fc11:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53fc16:	8b 8d a8 fc ff ff    	mov    -0x358(%rbp),%ecx
    7f5c5a53fc1c:	03 8d e8 fe ff ff    	add    -0x118(%rbp),%ecx
    7f5c5a53fc22:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fc28:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53fc2b:	0b c8                	or     %eax,%ecx
    7f5c5a53fc2d:	89 8d 88 fc ff ff    	mov    %ecx,-0x378(%rbp)
    7f5c5a53fc33:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f5c5a53fc39:	85 c0                	test   %eax,%eax
    7f5c5a53fc3b:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fc4d
    7f5c5a53fc41:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f5c5a53fc47:	89 85 88 fc ff ff    	mov    %eax,-0x378(%rbp)
    7f5c5a53fc4d:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7f5c5a53fc53:	41 23 c6             	and    %r14d,%eax
    7f5c5a53fc56:	8b 8d b0 fe ff ff    	mov    -0x150(%rbp),%ecx
    7f5c5a53fc5c:	ff c1                	inc    %ecx
    7f5c5a53fc5e:	83 e1 03             	and    $0x3,%ecx
    7f5c5a53fc61:	89 8d 80 fc ff ff    	mov    %ecx,-0x380(%rbp)
    7f5c5a53fc67:	85 c0                	test   %eax,%eax
    7f5c5a53fc69:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fc7b
    7f5c5a53fc6f:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f5c5a53fc75:	89 85 80 fc ff ff    	mov    %eax,-0x380(%rbp)
    7f5c5a53fc7b:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f5c5a53fc81:	d1 e8                	shr    %eax
    7f5c5a53fc83:	83 e0 01             	and    $0x1,%eax
    7f5c5a53fc86:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7f5c5a53fc8c:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53fc8f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fc95:	8b 95 c0 fe ff ff    	mov    -0x140(%rbp),%edx
    7f5c5a53fc9b:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53fca1:	f7 da                	neg    %edx
    7f5c5a53fca3:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53fca9:	c1 e2 10             	shl    $0x10,%edx
    7f5c5a53fcac:	0b ca                	or     %edx,%ecx
    7f5c5a53fcae:	89 8d 78 fc ff ff    	mov    %ecx,-0x388(%rbp)
    7f5c5a53fcb4:	85 c0                	test   %eax,%eax
    7f5c5a53fcb6:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fcc8
    7f5c5a53fcbc:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f5c5a53fcc2:	89 85 78 fc ff ff    	mov    %eax,-0x388(%rbp)
    7f5c5a53fcc8:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f5c5a53fcce:	41 23 c6             	and    %r14d,%eax
    7f5c5a53fcd1:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7f5c5a53fcd7:	ff c1                	inc    %ecx
    7f5c5a53fcd9:	83 e1 01             	and    $0x1,%ecx
    7f5c5a53fcdc:	89 8d 70 fc ff ff    	mov    %ecx,-0x390(%rbp)
    7f5c5a53fce2:	85 c0                	test   %eax,%eax
    7f5c5a53fce4:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fcf6
    7f5c5a53fcea:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7f5c5a53fcf0:	89 85 70 fc ff ff    	mov    %eax,-0x390(%rbp)
    7f5c5a53fcf6:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7f5c5a53fcfc:	c1 e8 10             	shr    $0x10,%eax
    7f5c5a53fcff:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53fd04:	8b 8d a8 fe ff ff    	mov    -0x158(%rbp),%ecx
    7f5c5a53fd0a:	c1 e9 10             	shr    $0x10,%ecx
    7f5c5a53fd0d:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fd13:	89 85 68 fc ff ff    	mov    %eax,-0x398(%rbp)
    7f5c5a53fd19:	89 8d 60 fc ff ff    	mov    %ecx,-0x3a0(%rbp)
    7f5c5a53fd1f:	2b c1                	sub    %ecx,%eax
    7f5c5a53fd21:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53fd26:	8b 8d 88 fe ff ff    	mov    -0x178(%rbp),%ecx
    7f5c5a53fd2c:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fd32:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7f5c5a53fd38:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f5c5a53fd3e:	89 8d 58 fc ff ff    	mov    %ecx,-0x3a8(%rbp)
    7f5c5a53fd44:	89 95 50 fc ff ff    	mov    %edx,-0x3b0(%rbp)
    7f5c5a53fd4a:	2b ca                	sub    %edx,%ecx
    7f5c5a53fd4c:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fd52:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53fd55:	0b c8                	or     %eax,%ecx
    7f5c5a53fd57:	89 8d 48 fc ff ff    	mov    %ecx,-0x3b8(%rbp)
    7f5c5a53fd5d:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7f5c5a53fd63:	85 c0                	test   %eax,%eax
    7f5c5a53fd65:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fd77
    7f5c5a53fd6b:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f5c5a53fd71:	89 85 48 fc ff ff    	mov    %eax,-0x3b8(%rbp)
    7f5c5a53fd77:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7f5c5a53fd7d:	03 85 60 fc ff ff    	add    -0x3a0(%rbp),%eax
    7f5c5a53fd83:	25 ff ff 00 00       	and    $0xffff,%eax
    7f5c5a53fd88:	8b 8d 58 fc ff ff    	mov    -0x3a8(%rbp),%ecx
    7f5c5a53fd8e:	03 8d 50 fc ff ff    	add    -0x3b0(%rbp),%ecx
    7f5c5a53fd94:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f5c5a53fd9a:	c1 e0 10             	shl    $0x10,%eax
    7f5c5a53fd9d:	0b c8                	or     %eax,%ecx
    7f5c5a53fd9f:	89 8d 40 fc ff ff    	mov    %ecx,-0x3c0(%rbp)
    7f5c5a53fda5:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7f5c5a53fdab:	85 c0                	test   %eax,%eax
    7f5c5a53fdad:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fdbf
    7f5c5a53fdb3:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7f5c5a53fdb9:	89 85 40 fc ff ff    	mov    %eax,-0x3c0(%rbp)
    7f5c5a53fdbf:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f5c5a53fdc5:	41 23 c6             	and    %r14d,%eax
    7f5c5a53fdc8:	8b 8d 70 fe ff ff    	mov    -0x190(%rbp),%ecx
    7f5c5a53fdce:	ff c1                	inc    %ecx
    7f5c5a53fdd0:	83 e1 3f             	and    $0x3f,%ecx
    7f5c5a53fdd3:	89 8d 38 fc ff ff    	mov    %ecx,-0x3c8(%rbp)
    7f5c5a53fdd9:	85 c0                	test   %eax,%eax
    7f5c5a53fddb:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fded
    7f5c5a53fde1:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f5c5a53fde7:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7f5c5a53fded:	48 8b 85 40 fe ff ff 	mov    -0x1c0(%rbp),%rax
    7f5c5a53fdf4:	48 8b 40 08          	mov    0x8(%rax),%rax
    7f5c5a53fdf8:	8b 00                	mov    (%rax),%eax
    7f5c5a53fdfa:	8b cb                	mov    %ebx,%ecx
    7f5c5a53fdfc:	c1 e9 02             	shr    $0x2,%ecx
    7f5c5a53fdff:	83 e1 01             	and    $0x1,%ecx
    7f5c5a53fe02:	85 c9                	test   %ecx,%ecx
    7f5c5a53fe04:	0f 94 c1             	sete   %cl
    7f5c5a53fe07:	0f b6 c9             	movzbl %cl,%ecx
    7f5c5a53fe0a:	23 c1                	and    %ecx,%eax
    7f5c5a53fe0c:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7f5c5a53fe12:	23 8d 28 fe ff ff    	and    -0x1d8(%rbp),%ecx
    7f5c5a53fe18:	85 c9                	test   %ecx,%ecx
    7f5c5a53fe1a:	0f 94 c2             	sete   %dl
    7f5c5a53fe1d:	0f b6 d2             	movzbl %dl,%edx
    7f5c5a53fe20:	89 95 30 fc ff ff    	mov    %edx,-0x3d0(%rbp)
    7f5c5a53fe26:	23 d0                	and    %eax,%edx
    7f5c5a53fe28:	8b f3                	mov    %ebx,%esi
    7f5c5a53fe2a:	83 e6 03             	and    $0x3,%esi
    7f5c5a53fe2d:	d1 e6                	shl    %esi
    7f5c5a53fe2f:	89 b5 28 fc ff ff    	mov    %esi,-0x3d8(%rbp)
    7f5c5a53fe35:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f5c5a53fe3b:	85 c0                	test   %eax,%eax
    7f5c5a53fe3d:	0f 94 c0             	sete   %al
    7f5c5a53fe40:	0f b6 c0             	movzbl %al,%eax
    7f5c5a53fe43:	89 8d 18 fc ff ff    	mov    %ecx,-0x3e8(%rbp)
    7f5c5a53fe49:	23 c8                	and    %eax,%ecx
    7f5c5a53fe4b:	89 8d 10 fc ff ff    	mov    %ecx,-0x3f0(%rbp)
    7f5c5a53fe51:	8b c3                	mov    %ebx,%eax
    7f5c5a53fe53:	d1 e8                	shr    %eax
    7f5c5a53fe55:	83 e0 03             	and    $0x3,%eax
    7f5c5a53fe58:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7f5c5a53fe5e:	85 d2                	test   %edx,%edx
    7f5c5a53fe60:	0f 85 1b 00 00 00    	jne    0x7f5c5a53fe81
    7f5c5a53fe66:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7f5c5a53fe6c:	85 c0                	test   %eax,%eax
    7f5c5a53fe6e:	0f 85 1e 00 00 00    	jne    0x7f5c5a53fe92
    7f5c5a53fe74:	8b c3                	mov    %ebx,%eax
    7f5c5a53fe76:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f5c5a53fe7c:	e9 1d 00 00 00       	jmpq   0x7f5c5a53fe9e
    7f5c5a53fe81:	8b 85 28 fc ff ff    	mov    -0x3d8(%rbp),%eax
    7f5c5a53fe87:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f5c5a53fe8d:	e9 0c 00 00 00       	jmpq   0x7f5c5a53fe9e
    7f5c5a53fe92:	8b 85 08 fc ff ff    	mov    -0x3f8(%rbp),%eax
    7f5c5a53fe98:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f5c5a53fe9e:	8b c3                	mov    %ebx,%eax
    7f5c5a53fea0:	83 e0 01             	and    $0x1,%eax
    7f5c5a53fea3:	8b 8d 20 fc ff ff    	mov    -0x3e0(%rbp),%ecx
    7f5c5a53fea9:	23 c1                	and    %ecx,%eax
    7f5c5a53feab:	8b 8d 18 fc ff ff    	mov    -0x3e8(%rbp),%ecx
    7f5c5a53feb1:	0b c1                	or     %ecx,%eax
    7f5c5a53feb3:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7f5c5a53feb9:	8b c3                	mov    %ebx,%eax
    7f5c5a53febb:	d1 e8                	shr    %eax
    7f5c5a53febd:	83 e0 01             	and    $0x1,%eax
    7f5c5a53fec0:	89 85 f0 fb ff ff    	mov    %eax,-0x410(%rbp)
    7f5c5a53fec6:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7f5c5a53fecc:	0b c1                	or     %ecx,%eax
    7f5c5a53fece:	48 8b 8d 40 fe ff ff 	mov    -0x1c0(%rbp),%rcx
    7f5c5a53fed5:	48 8b 09             	mov    (%rcx),%rcx
    7f5c5a53fed8:	8b 09                	mov    (%rcx),%ecx
    7f5c5a53feda:	89 8d e8 fb ff ff    	mov    %ecx,-0x418(%rbp)
    7f5c5a53fee0:	89 8d e0 fb ff ff    	mov    %ecx,-0x420(%rbp)
    7f5c5a53fee6:	85 c0                	test   %eax,%eax
    7f5c5a53fee8:	0f 85 0c 00 00 00    	jne    0x7f5c5a53fefa
    7f5c5a53feee:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f5c5a53fef4:	89 85 e0 fb ff ff    	mov    %eax,-0x420(%rbp)
    7f5c5a53fefa:	8b 85 e0 fb ff ff    	mov    -0x420(%rbp),%eax
    7f5c5a53ff00:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7f5c5a53ff06:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7f5c5a53ff0c:	85 c0                	test   %eax,%eax
    7f5c5a53ff0e:	0f 85 0c 00 00 00    	jne    0x7f5c5a53ff20
    7f5c5a53ff14:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f5c5a53ff1a:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7f5c5a53ff20:	8b 85 20 fc ff ff    	mov    -0x3e0(%rbp),%eax
    7f5c5a53ff26:	23 85 f0 fb ff ff    	and    -0x410(%rbp),%eax
    7f5c5a53ff2c:	8b 8d 18 fc ff ff    	mov    -0x3e8(%rbp),%ecx
    7f5c5a53ff32:	0b c1                	or     %ecx,%eax
    7f5c5a53ff34:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7f5c5a53ff3a:	89 8d d0 fb ff ff    	mov    %ecx,-0x430(%rbp)
    7f5c5a53ff40:	85 c0                	test   %eax,%eax
    7f5c5a53ff42:	0f 85 0c 00 00 00    	jne    0x7f5c5a53ff54
    7f5c5a53ff48:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f5c5a53ff4e:	89 85 d0 fb ff ff    	mov    %eax,-0x430(%rbp)
    7f5c5a53ff54:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7f5c5a53ff5a:	23 85 38 fe ff ff    	and    -0x1c8(%rbp),%eax
    7f5c5a53ff60:	48 8b 8d 40 fe ff ff 	mov    -0x1c0(%rbp),%rcx
    7f5c5a53ff67:	48 8b 49 10          	mov    0x10(%rcx),%rcx
    7f5c5a53ff6b:	8b 09                	mov    (%rcx),%ecx
    7f5c5a53ff6d:	8b 95 58 fe ff ff    	mov    -0x1a8(%rbp),%edx
    7f5c5a53ff73:	83 e2 01             	and    $0x1,%edx
    7f5c5a53ff76:	85 d2                	test   %edx,%edx
    7f5c5a53ff78:	0f 94 c2             	sete   %dl
    7f5c5a53ff7b:	0f b6 d2             	movzbl %dl,%edx
    7f5c5a53ff7e:	23 ca                	and    %edx,%ecx
    7f5c5a53ff80:	85 c9                	test   %ecx,%ecx
    7f5c5a53ff82:	0f 94 c2             	sete   %dl
    7f5c5a53ff85:	0f b6 d2             	movzbl %dl,%edx
    7f5c5a53ff88:	89 95 c8 fb ff ff    	mov    %edx,-0x438(%rbp)
    7f5c5a53ff8e:	23 d0                	and    %eax,%edx
    7f5c5a53ff90:	8b b5 58 fe ff ff    	mov    -0x1a8(%rbp),%esi
    7f5c5a53ff96:	83 e6 03             	and    $0x3,%esi
    7f5c5a53ff99:	d1 e6                	shl    %esi
    7f5c5a53ff9b:	89 b5 c0 fb ff ff    	mov    %esi,-0x440(%rbp)
    7f5c5a53ffa1:	89 85 b8 fb ff ff    	mov    %eax,-0x448(%rbp)
    7f5c5a53ffa7:	85 c0                	test   %eax,%eax
    7f5c5a53ffa9:	0f 94 c0             	sete   %al
    7f5c5a53ffac:	0f b6 c0             	movzbl %al,%eax
    7f5c5a53ffaf:	89 8d b0 fb ff ff    	mov    %ecx,-0x450(%rbp)
    7f5c5a53ffb5:	23 c8                	and    %eax,%ecx
    7f5c5a53ffb7:	89 8d a8 fb ff ff    	mov    %ecx,-0x458(%rbp)
    7f5c5a53ffbd:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f5c5a53ffc3:	d1 e8                	shr    %eax
    7f5c5a53ffc5:	83 e0 03             	and    $0x3,%eax
    7f5c5a53ffc8:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7f5c5a53ffce:	85 d2                	test   %edx,%edx
    7f5c5a53ffd0:	0f 85 1f 00 00 00    	jne    0x7f5c5a53fff5
    7f5c5a53ffd6:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7f5c5a53ffdc:	85 c0                	test   %eax,%eax
    7f5c5a53ffde:	0f 85 22 00 00 00    	jne    0x7f5c5a540006
    7f5c5a53ffe4:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f5c5a53ffea:	89 85 98 fb ff ff    	mov    %eax,-0x468(%rbp)
    7f5c5a53fff0:	e9 1d 00 00 00       	jmpq   0x7f5c5a540012
    7f5c5a53fff5:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f5c5a53fffb:	89 85 98 fb ff ff    	mov    %eax,-0x468(%rbp)
    7f5c5a540001:	e9 0c 00 00 00       	jmpq   0x7f5c5a540012
    7f5c5a540006:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7f5c5a54000c:	89 85 98 fb ff ff    	mov    %eax,-0x468(%rbp)
    7f5c5a540012:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f5c5a540018:	83 e0 01             	and    $0x1,%eax
    7f5c5a54001b:	8b 8d b8 fb ff ff    	mov    -0x448(%rbp),%ecx
    7f5c5a540021:	23 c1                	and    %ecx,%eax
    7f5c5a540023:	8b 8d b0 fb ff ff    	mov    -0x450(%rbp),%ecx
    7f5c5a540029:	0b c1                	or     %ecx,%eax
    7f5c5a54002b:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f5c5a540031:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f5c5a540037:	d1 e8                	shr    %eax
    7f5c5a540039:	83 e0 01             	and    $0x1,%eax
    7f5c5a54003c:	89 85 88 fb ff ff    	mov    %eax,-0x478(%rbp)
    7f5c5a540042:	8b 8d c8 fb ff ff    	mov    -0x438(%rbp),%ecx
    7f5c5a540048:	0b c1                	or     %ecx,%eax
    7f5c5a54004a:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7f5c5a540050:	89 8d 80 fb ff ff    	mov    %ecx,-0x480(%rbp)
    7f5c5a540056:	85 c0                	test   %eax,%eax
    7f5c5a540058:	0f 85 0c 00 00 00    	jne    0x7f5c5a54006a
    7f5c5a54005e:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f5c5a540064:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7f5c5a54006a:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7f5c5a540070:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7f5c5a540076:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7f5c5a54007c:	85 c0                	test   %eax,%eax
    7f5c5a54007e:	0f 85 0c 00 00 00    	jne    0x7f5c5a540090
    7f5c5a540084:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7f5c5a54008a:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7f5c5a540090:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7f5c5a540096:	23 85 88 fb ff ff    	and    -0x478(%rbp),%eax
    7f5c5a54009c:	8b 8d b0 fb ff ff    	mov    -0x450(%rbp),%ecx
    7f5c5a5400a2:	0b c1                	or     %ecx,%eax
    7f5c5a5400a4:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7f5c5a5400aa:	89 8d 70 fb ff ff    	mov    %ecx,-0x490(%rbp)
    7f5c5a5400b0:	85 c0                	test   %eax,%eax
    7f5c5a5400b2:	0f 85 0c 00 00 00    	jne    0x7f5c5a5400c4
    7f5c5a5400b8:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f5c5a5400be:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7f5c5a5400c4:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7f5c5a5400ca:	41 89 87 38 04 00 00 	mov    %eax,0x438(%r15)
    7f5c5a5400d1:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7f5c5a5400d7:	8b 85 78 fb ff ff    	mov    -0x488(%rbp),%eax
    7f5c5a5400dd:	41 89 87 30 04 00 00 	mov    %eax,0x430(%r15)
    7f5c5a5400e4:	89 85 50 fe ff ff    	mov    %eax,-0x1b0(%rbp)
    7f5c5a5400ea:	45 85 ed             	test   %r13d,%r13d
    7f5c5a5400ed:	0f 84 1a 00 00 00    	je     0x7f5c5a54010d
    7f5c5a5400f3:	41 c7 87 28 04 00 00 	movl   $0x1,0x428(%r15)
    7f5c5a5400fa:	01 00 00 00 
    7f5c5a5400fe:	c7 85 58 fe ff ff 01 	movl   $0x1,-0x1a8(%rbp)
    7f5c5a540105:	00 00 00 
    7f5c5a540108:	e9 13 00 00 00       	jmpq   0x7f5c5a540120
    7f5c5a54010d:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7f5c5a540113:	41 89 87 28 04 00 00 	mov    %eax,0x428(%r15)
    7f5c5a54011a:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7f5c5a540120:	8b 85 d0 fb ff ff    	mov    -0x430(%rbp),%eax
    7f5c5a540126:	41 89 87 20 04 00 00 	mov    %eax,0x420(%r15)
    7f5c5a54012d:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7f5c5a540133:	8b 85 d8 fb ff ff    	mov    -0x428(%rbp),%eax
    7f5c5a540139:	41 89 87 18 04 00 00 	mov    %eax,0x418(%r15)
    7f5c5a540140:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f5c5a540146:	45 85 ed             	test   %r13d,%r13d
    7f5c5a540149:	0f 84 15 00 00 00    	je     0x7f5c5a540164
    7f5c5a54014f:	41 c7 87 10 04 00 00 	movl   $0x1,0x410(%r15)
    7f5c5a540156:	01 00 00 00 
    7f5c5a54015a:	bb 01 00 00 00       	mov    $0x1,%ebx
    7f5c5a54015f:	e9 10 00 00 00       	jmpq   0x7f5c5a540174
    7f5c5a540164:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7f5c5a54016a:	41 89 87 10 04 00 00 	mov    %eax,0x410(%r15)
    7f5c5a540171:	48 8b d8             	mov    %rax,%rbx
    7f5c5a540174:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540177:	0f 84 1a 00 00 00    	je     0x7f5c5a540197
    7f5c5a54017d:	41 c7 87 08 04 00 00 	movl   $0x0,0x408(%r15)
    7f5c5a540184:	00 00 00 00 
    7f5c5a540188:	c7 85 70 fe ff ff 00 	movl   $0x0,-0x190(%rbp)
    7f5c5a54018f:	00 00 00 
    7f5c5a540192:	e9 13 00 00 00       	jmpq   0x7f5c5a5401aa
    7f5c5a540197:	8b 85 38 fc ff ff    	mov    -0x3c8(%rbp),%eax
    7f5c5a54019d:	41 89 87 08 04 00 00 	mov    %eax,0x408(%r15)
    7f5c5a5401a4:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7f5c5a5401aa:	45 85 ed             	test   %r13d,%r13d
    7f5c5a5401ad:	0f 84 25 00 00 00    	je     0x7f5c5a5401d8
    7f5c5a5401b3:	41 c7 87 f8 03 00 00 	movl   $0x0,0x3f8(%r15)
    7f5c5a5401ba:	00 00 00 00 
    7f5c5a5401be:	c7 85 78 fe ff ff 00 	movl   $0x0,-0x188(%rbp)
    7f5c5a5401c5:	00 00 00 
    7f5c5a5401c8:	41 c7 87 00 04 00 00 	movl   $0x0,0x400(%r15)
    7f5c5a5401cf:	00 00 00 00 
    7f5c5a5401d3:	e9 2a 00 00 00       	jmpq   0x7f5c5a540202
    7f5c5a5401d8:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5401db:	0f 84 21 00 00 00    	je     0x7f5c5a540202
    7f5c5a5401e1:	41 8b 87 00 04 00 00 	mov    0x400(%r15),%eax
    7f5c5a5401e8:	41 89 87 f8 03 00 00 	mov    %eax,0x3f8(%r15)
    7f5c5a5401ef:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7f5c5a5401f5:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f5c5a5401fb:	41 89 87 00 04 00 00 	mov    %eax,0x400(%r15)
    7f5c5a540202:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540205:	0f 84 26 00 00 00    	je     0x7f5c5a540231
    7f5c5a54020b:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f5c5a540211:	41 89 87 f0 03 00 00 	mov    %eax,0x3f0(%r15)
    7f5c5a540218:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7f5c5a54021e:	8b 85 48 fc ff ff    	mov    -0x3b8(%rbp),%eax
    7f5c5a540224:	41 89 87 e8 03 00 00 	mov    %eax,0x3e8(%r15)
    7f5c5a54022b:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7f5c5a540231:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540234:	0f 84 1a 00 00 00    	je     0x7f5c5a540254
    7f5c5a54023a:	41 c7 87 e0 03 00 00 	movl   $0x0,0x3e0(%r15)
    7f5c5a540241:	00 00 00 00 
    7f5c5a540245:	c7 85 90 fe ff ff 00 	movl   $0x0,-0x170(%rbp)
    7f5c5a54024c:	00 00 00 
    7f5c5a54024f:	e9 13 00 00 00       	jmpq   0x7f5c5a540267
    7f5c5a540254:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7f5c5a54025a:	41 89 87 e0 03 00 00 	mov    %eax,0x3e0(%r15)
    7f5c5a540261:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f5c5a540267:	45 85 ed             	test   %r13d,%r13d
    7f5c5a54026a:	0f 84 1a 00 00 00    	je     0x7f5c5a54028a
    7f5c5a540270:	41 c7 87 d8 03 00 00 	movl   $0x0,0x3d8(%r15)
    7f5c5a540277:	00 00 00 00 
    7f5c5a54027b:	c7 85 98 fe ff ff 00 	movl   $0x0,-0x168(%rbp)
    7f5c5a540282:	00 00 00 
    7f5c5a540285:	e9 1c 00 00 00       	jmpq   0x7f5c5a5402a6
    7f5c5a54028a:	45 85 f6             	test   %r14d,%r14d
    7f5c5a54028d:	0f 84 13 00 00 00    	je     0x7f5c5a5402a6
    7f5c5a540293:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7f5c5a540299:	41 89 87 d8 03 00 00 	mov    %eax,0x3d8(%r15)
    7f5c5a5402a0:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f5c5a5402a6:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5402a9:	0f 84 26 00 00 00    	je     0x7f5c5a5402d5
    7f5c5a5402af:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f5c5a5402b5:	41 89 87 d0 03 00 00 	mov    %eax,0x3d0(%r15)
    7f5c5a5402bc:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f5c5a5402c2:	8b 85 78 fc ff ff    	mov    -0x388(%rbp),%eax
    7f5c5a5402c8:	41 89 87 c8 03 00 00 	mov    %eax,0x3c8(%r15)
    7f5c5a5402cf:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f5c5a5402d5:	45 85 e4             	test   %r12d,%r12d
    7f5c5a5402d8:	0f 84 1a 00 00 00    	je     0x7f5c5a5402f8
    7f5c5a5402de:	41 c7 87 c0 03 00 00 	movl   $0x0,0x3c0(%r15)
    7f5c5a5402e5:	00 00 00 00 
    7f5c5a5402e9:	c7 85 b0 fe ff ff 00 	movl   $0x0,-0x150(%rbp)
    7f5c5a5402f0:	00 00 00 
    7f5c5a5402f3:	e9 13 00 00 00       	jmpq   0x7f5c5a54030b
    7f5c5a5402f8:	8b 85 80 fc ff ff    	mov    -0x380(%rbp),%eax
    7f5c5a5402fe:	41 89 87 c0 03 00 00 	mov    %eax,0x3c0(%r15)
    7f5c5a540305:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f5c5a54030b:	45 85 ed             	test   %r13d,%r13d
    7f5c5a54030e:	0f 84 25 00 00 00    	je     0x7f5c5a540339
    7f5c5a540314:	41 c7 87 b0 03 00 00 	movl   $0x0,0x3b0(%r15)
    7f5c5a54031b:	00 00 00 00 
    7f5c5a54031f:	c7 85 b8 fe ff ff 00 	movl   $0x0,-0x148(%rbp)
    7f5c5a540326:	00 00 00 
    7f5c5a540329:	41 c7 87 b8 03 00 00 	movl   $0x0,0x3b8(%r15)
    7f5c5a540330:	00 00 00 00 
    7f5c5a540334:	e9 35 00 00 00       	jmpq   0x7f5c5a54036e
    7f5c5a540339:	45 85 f6             	test   %r14d,%r14d
    7f5c5a54033c:	0f 84 2c 00 00 00    	je     0x7f5c5a54036e
    7f5c5a540342:	41 8b 87 b8 03 00 00 	mov    0x3b8(%r15),%eax
    7f5c5a540349:	8b c8                	mov    %eax,%ecx
    7f5c5a54034b:	83 e1 01             	and    $0x1,%ecx
    7f5c5a54034e:	41 89 8f b0 03 00 00 	mov    %ecx,0x3b0(%r15)
    7f5c5a540355:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7f5c5a54035b:	d1 e8                	shr    %eax
    7f5c5a54035d:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7f5c5a540363:	d1 e1                	shl    %ecx
    7f5c5a540365:	0b c1                	or     %ecx,%eax
    7f5c5a540367:	41 89 87 b8 03 00 00 	mov    %eax,0x3b8(%r15)
    7f5c5a54036e:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540371:	0f 84 34 00 00 00    	je     0x7f5c5a5403ab
    7f5c5a540377:	8b 85 88 fc ff ff    	mov    -0x378(%rbp),%eax
    7f5c5a54037d:	41 89 87 a8 03 00 00 	mov    %eax,0x3a8(%r15)
    7f5c5a540384:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f5c5a54038a:	41 8b 87 a0 03 00 00 	mov    0x3a0(%r15),%eax
    7f5c5a540391:	41 89 87 98 03 00 00 	mov    %eax,0x398(%r15)
    7f5c5a540398:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f5c5a54039e:	8b 85 a0 fc ff ff    	mov    -0x360(%rbp),%eax
    7f5c5a5403a4:	41 89 87 a0 03 00 00 	mov    %eax,0x3a0(%r15)
    7f5c5a5403ab:	45 85 e4             	test   %r12d,%r12d
    7f5c5a5403ae:	0f 84 1a 00 00 00    	je     0x7f5c5a5403ce
    7f5c5a5403b4:	41 c7 87 90 03 00 00 	movl   $0x0,0x390(%r15)
    7f5c5a5403bb:	00 00 00 00 
    7f5c5a5403bf:	c7 85 d0 fe ff ff 00 	movl   $0x0,-0x130(%rbp)
    7f5c5a5403c6:	00 00 00 
    7f5c5a5403c9:	e9 13 00 00 00       	jmpq   0x7f5c5a5403e1
    7f5c5a5403ce:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7f5c5a5403d4:	41 89 87 90 03 00 00 	mov    %eax,0x390(%r15)
    7f5c5a5403db:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f5c5a5403e1:	45 85 ed             	test   %r13d,%r13d
    7f5c5a5403e4:	0f 84 25 00 00 00    	je     0x7f5c5a54040f
    7f5c5a5403ea:	41 c7 87 80 03 00 00 	movl   $0x0,0x380(%r15)
    7f5c5a5403f1:	00 00 00 00 
    7f5c5a5403f5:	c7 85 d8 fe ff ff 00 	movl   $0x0,-0x128(%rbp)
    7f5c5a5403fc:	00 00 00 
    7f5c5a5403ff:	41 c7 87 88 03 00 00 	movl   $0x0,0x388(%r15)
    7f5c5a540406:	00 00 00 00 
    7f5c5a54040a:	e9 2a 00 00 00       	jmpq   0x7f5c5a540439
    7f5c5a54040f:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540412:	0f 84 21 00 00 00    	je     0x7f5c5a540439
    7f5c5a540418:	41 8b 87 88 03 00 00 	mov    0x388(%r15),%eax
    7f5c5a54041f:	41 89 87 80 03 00 00 	mov    %eax,0x380(%r15)
    7f5c5a540426:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f5c5a54042c:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f5c5a540432:	41 89 87 88 03 00 00 	mov    %eax,0x388(%r15)
    7f5c5a540439:	45 85 f6             	test   %r14d,%r14d
    7f5c5a54043c:	0f 84 4c 00 00 00    	je     0x7f5c5a54048e
    7f5c5a540442:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7f5c5a540448:	41 89 87 78 03 00 00 	mov    %eax,0x378(%r15)
    7f5c5a54044f:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f5c5a540455:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7f5c5a54045b:	41 89 87 70 03 00 00 	mov    %eax,0x370(%r15)
    7f5c5a540462:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f5c5a540468:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f5c5a54046e:	41 89 87 68 03 00 00 	mov    %eax,0x368(%r15)
    7f5c5a540475:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f5c5a54047b:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7f5c5a540481:	41 89 87 60 03 00 00 	mov    %eax,0x360(%r15)
    7f5c5a540488:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7f5c5a54048e:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540491:	0f 84 1a 00 00 00    	je     0x7f5c5a5404b1
    7f5c5a540497:	41 c7 87 58 03 00 00 	movl   $0x0,0x358(%r15)
    7f5c5a54049e:	00 00 00 00 
    7f5c5a5404a2:	c7 85 00 ff ff ff 00 	movl   $0x0,-0x100(%rbp)
    7f5c5a5404a9:	00 00 00 
    7f5c5a5404ac:	e9 13 00 00 00       	jmpq   0x7f5c5a5404c4
    7f5c5a5404b1:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7f5c5a5404b7:	41 89 87 58 03 00 00 	mov    %eax,0x358(%r15)
    7f5c5a5404be:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f5c5a5404c4:	45 85 ed             	test   %r13d,%r13d
    7f5c5a5404c7:	0f 84 25 00 00 00    	je     0x7f5c5a5404f2
    7f5c5a5404cd:	41 c7 87 48 03 00 00 	movl   $0x0,0x348(%r15)
    7f5c5a5404d4:	00 00 00 00 
    7f5c5a5404d8:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7f5c5a5404df:	00 00 00 
    7f5c5a5404e2:	41 c7 87 50 03 00 00 	movl   $0x0,0x350(%r15)
    7f5c5a5404e9:	00 00 00 00 
    7f5c5a5404ed:	e9 36 00 00 00       	jmpq   0x7f5c5a540528
    7f5c5a5404f2:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5404f5:	0f 84 2d 00 00 00    	je     0x7f5c5a540528
    7f5c5a5404fb:	41 8b 87 50 03 00 00 	mov    0x350(%r15),%eax
    7f5c5a540502:	8b c8                	mov    %eax,%ecx
    7f5c5a540504:	83 e1 01             	and    $0x1,%ecx
    7f5c5a540507:	41 89 8f 48 03 00 00 	mov    %ecx,0x348(%r15)
    7f5c5a54050e:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7f5c5a540514:	d1 e8                	shr    %eax
    7f5c5a540516:	8b 8d 28 ff ff ff    	mov    -0xd8(%rbp),%ecx
    7f5c5a54051c:	c1 e1 03             	shl    $0x3,%ecx
    7f5c5a54051f:	0b c1                	or     %ecx,%eax
    7f5c5a540521:	41 89 87 50 03 00 00 	mov    %eax,0x350(%r15)
    7f5c5a540528:	45 85 f6             	test   %r14d,%r14d
    7f5c5a54052b:	0f 84 54 00 00 00    	je     0x7f5c5a540585
    7f5c5a540531:	8b 85 e0 fc ff ff    	mov    -0x320(%rbp),%eax
    7f5c5a540537:	41 89 87 40 03 00 00 	mov    %eax,0x340(%r15)
    7f5c5a54053e:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f5c5a540544:	41 8b 87 3c 03 00 00 	mov    0x33c(%r15),%eax
    7f5c5a54054b:	49 8b cf             	mov    %r15,%rcx
    7f5c5a54054e:	48 81 c1 2c 03 00 00 	add    $0x32c,%rcx
    7f5c5a540555:	8b d0                	mov    %eax,%edx
    7f5c5a540557:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f5c5a54055a:	41 89 97 24 03 00 00 	mov    %edx,0x324(%r15)
    7f5c5a540561:	89 95 18 ff ff ff    	mov    %edx,-0xe8(%rbp)
    7f5c5a540567:	8b d0                	mov    %eax,%edx
    7f5c5a540569:	8b b5 f0 fc ff ff    	mov    -0x310(%rbp),%esi
    7f5c5a54056f:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f5c5a540572:	ff c8                	dec    %eax
    7f5c5a540574:	b9 02 00 00 00       	mov    $0x2,%ecx
    7f5c5a540579:	3b c1                	cmp    %ecx,%eax
    7f5c5a54057b:	0f 47 c1             	cmova  %ecx,%eax
    7f5c5a54057e:	41 89 87 3c 03 00 00 	mov    %eax,0x33c(%r15)
    7f5c5a540585:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540588:	0f 84 1a 00 00 00    	je     0x7f5c5a5405a8
    7f5c5a54058e:	41 c7 87 1c 03 00 00 	movl   $0x0,0x31c(%r15)
    7f5c5a540595:	00 00 00 00 
    7f5c5a540599:	c7 85 20 ff ff ff 00 	movl   $0x0,-0xe0(%rbp)
    7f5c5a5405a0:	00 00 00 
    7f5c5a5405a3:	e9 13 00 00 00       	jmpq   0x7f5c5a5405bb
    7f5c5a5405a8:	8b 85 18 fd ff ff    	mov    -0x2e8(%rbp),%eax
    7f5c5a5405ae:	41 89 87 1c 03 00 00 	mov    %eax,0x31c(%r15)
    7f5c5a5405b5:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f5c5a5405bb:	45 85 ed             	test   %r13d,%r13d
    7f5c5a5405be:	0f 84 1a 00 00 00    	je     0x7f5c5a5405de
    7f5c5a5405c4:	41 c7 87 14 03 00 00 	movl   $0x0,0x314(%r15)
    7f5c5a5405cb:	00 00 00 00 
    7f5c5a5405cf:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7f5c5a5405d6:	00 00 00 
    7f5c5a5405d9:	e9 1c 00 00 00       	jmpq   0x7f5c5a5405fa
    7f5c5a5405de:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5405e1:	0f 84 13 00 00 00    	je     0x7f5c5a5405fa
    7f5c5a5405e7:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f5c5a5405ed:	41 89 87 14 03 00 00 	mov    %eax,0x314(%r15)
    7f5c5a5405f4:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f5c5a5405fa:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5405fd:	0f 84 26 00 00 00    	je     0x7f5c5a540629
    7f5c5a540603:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7f5c5a540609:	41 89 87 0c 03 00 00 	mov    %eax,0x30c(%r15)
    7f5c5a540610:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f5c5a540616:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f5c5a54061c:	41 89 87 04 03 00 00 	mov    %eax,0x304(%r15)
    7f5c5a540623:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f5c5a540629:	45 85 e4             	test   %r12d,%r12d
    7f5c5a54062c:	0f 84 1a 00 00 00    	je     0x7f5c5a54064c
    7f5c5a540632:	41 c7 87 fc 02 00 00 	movl   $0x0,0x2fc(%r15)
    7f5c5a540639:	00 00 00 00 
    7f5c5a54063d:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7f5c5a540644:	00 00 00 
    7f5c5a540647:	e9 13 00 00 00       	jmpq   0x7f5c5a54065f
    7f5c5a54064c:	8b 85 28 fd ff ff    	mov    -0x2d8(%rbp),%eax
    7f5c5a540652:	41 89 87 fc 02 00 00 	mov    %eax,0x2fc(%r15)
    7f5c5a540659:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f5c5a54065f:	45 85 ed             	test   %r13d,%r13d
    7f5c5a540662:	0f 84 25 00 00 00    	je     0x7f5c5a54068d
    7f5c5a540668:	41 c7 87 ec 02 00 00 	movl   $0x0,0x2ec(%r15)
    7f5c5a54066f:	00 00 00 00 
    7f5c5a540673:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7f5c5a54067a:	00 00 00 
    7f5c5a54067d:	41 c7 87 f4 02 00 00 	movl   $0x0,0x2f4(%r15)
    7f5c5a540684:	00 00 00 00 
    7f5c5a540688:	e9 36 00 00 00       	jmpq   0x7f5c5a5406c3
    7f5c5a54068d:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540690:	0f 84 2d 00 00 00    	je     0x7f5c5a5406c3
    7f5c5a540696:	41 8b 87 f4 02 00 00 	mov    0x2f4(%r15),%eax
    7f5c5a54069d:	8b c8                	mov    %eax,%ecx
    7f5c5a54069f:	83 e1 01             	and    $0x1,%ecx
    7f5c5a5406a2:	41 89 8f ec 02 00 00 	mov    %ecx,0x2ec(%r15)
    7f5c5a5406a9:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%rbp)
    7f5c5a5406af:	d1 e8                	shr    %eax
    7f5c5a5406b1:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7f5c5a5406b7:	c1 e1 07             	shl    $0x7,%ecx
    7f5c5a5406ba:	0b c1                	or     %ecx,%eax
    7f5c5a5406bc:	41 89 87 f4 02 00 00 	mov    %eax,0x2f4(%r15)
    7f5c5a5406c3:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5406c6:	0f 84 54 00 00 00    	je     0x7f5c5a540720
    7f5c5a5406cc:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7f5c5a5406d2:	41 89 87 e4 02 00 00 	mov    %eax,0x2e4(%r15)
    7f5c5a5406d9:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f5c5a5406df:	41 8b 87 e0 02 00 00 	mov    0x2e0(%r15),%eax
    7f5c5a5406e6:	49 8b cf             	mov    %r15,%rcx
    7f5c5a5406e9:	48 81 c1 c0 02 00 00 	add    $0x2c0,%rcx
    7f5c5a5406f0:	8b d0                	mov    %eax,%edx
    7f5c5a5406f2:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f5c5a5406f5:	41 89 97 b8 02 00 00 	mov    %edx,0x2b8(%r15)
    7f5c5a5406fc:	89 95 58 ff ff ff    	mov    %edx,-0xa8(%rbp)
    7f5c5a540702:	8b d0                	mov    %eax,%edx
    7f5c5a540704:	8b b5 48 fd ff ff    	mov    -0x2b8(%rbp),%esi
    7f5c5a54070a:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f5c5a54070d:	ff c8                	dec    %eax
    7f5c5a54070f:	b9 06 00 00 00       	mov    $0x6,%ecx
    7f5c5a540714:	3b c1                	cmp    %ecx,%eax
    7f5c5a540716:	0f 47 c1             	cmova  %ecx,%eax
    7f5c5a540719:	41 89 87 e0 02 00 00 	mov    %eax,0x2e0(%r15)
    7f5c5a540720:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540723:	0f 84 1a 00 00 00    	je     0x7f5c5a540743
    7f5c5a540729:	41 c7 87 b0 02 00 00 	movl   $0x0,0x2b0(%r15)
    7f5c5a540730:	00 00 00 00 
    7f5c5a540734:	c7 85 60 ff ff ff 00 	movl   $0x0,-0xa0(%rbp)
    7f5c5a54073b:	00 00 00 
    7f5c5a54073e:	e9 13 00 00 00       	jmpq   0x7f5c5a540756
    7f5c5a540743:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7f5c5a540749:	41 89 87 b0 02 00 00 	mov    %eax,0x2b0(%r15)
    7f5c5a540750:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f5c5a540756:	45 85 ed             	test   %r13d,%r13d
    7f5c5a540759:	0f 84 25 00 00 00    	je     0x7f5c5a540784
    7f5c5a54075f:	41 c7 87 a0 02 00 00 	movl   $0x0,0x2a0(%r15)
    7f5c5a540766:	00 00 00 00 
    7f5c5a54076a:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7f5c5a540771:	00 00 00 
    7f5c5a540774:	41 c7 87 a8 02 00 00 	movl   $0x0,0x2a8(%r15)
    7f5c5a54077b:	00 00 00 00 
    7f5c5a54077f:	e9 27 00 00 00       	jmpq   0x7f5c5a5407ab
    7f5c5a540784:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540787:	0f 84 1e 00 00 00    	je     0x7f5c5a5407ab
    7f5c5a54078d:	41 8b 87 a8 02 00 00 	mov    0x2a8(%r15),%eax
    7f5c5a540794:	41 89 87 a0 02 00 00 	mov    %eax,0x2a0(%r15)
    7f5c5a54079b:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f5c5a5407a1:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f5c5a5407a4:	41 89 87 a8 02 00 00 	mov    %eax,0x2a8(%r15)
    7f5c5a5407ab:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5407ae:	0f 84 43 00 00 00    	je     0x7f5c5a5407f7
    7f5c5a5407b4:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7f5c5a5407ba:	41 89 87 98 02 00 00 	mov    %eax,0x298(%r15)
    7f5c5a5407c1:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f5c5a5407c7:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7f5c5a5407cd:	41 89 87 90 02 00 00 	mov    %eax,0x290(%r15)
    7f5c5a5407d4:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f5c5a5407da:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f5c5a5407dd:	41 89 87 88 02 00 00 	mov    %eax,0x288(%r15)
    7f5c5a5407e4:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f5c5a5407e7:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7f5c5a5407ed:	41 89 87 80 02 00 00 	mov    %eax,0x280(%r15)
    7f5c5a5407f4:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f5c5a5407f7:	45 85 e4             	test   %r12d,%r12d
    7f5c5a5407fa:	0f 84 17 00 00 00    	je     0x7f5c5a540817
    7f5c5a540800:	41 c7 87 78 02 00 00 	movl   $0x0,0x278(%r15)
    7f5c5a540807:	00 00 00 00 
    7f5c5a54080b:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7f5c5a540812:	e9 10 00 00 00       	jmpq   0x7f5c5a540827
    7f5c5a540817:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7f5c5a54081d:	41 89 87 78 02 00 00 	mov    %eax,0x278(%r15)
    7f5c5a540824:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f5c5a540827:	45 85 ed             	test   %r13d,%r13d
    7f5c5a54082a:	0f 84 22 00 00 00    	je     0x7f5c5a540852
    7f5c5a540830:	41 c7 87 68 02 00 00 	movl   $0x0,0x268(%r15)
    7f5c5a540837:	00 00 00 00 
    7f5c5a54083b:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7f5c5a540842:	41 c7 87 70 02 00 00 	movl   $0x0,0x270(%r15)
    7f5c5a540849:	00 00 00 00 
    7f5c5a54084d:	e9 30 00 00 00       	jmpq   0x7f5c5a540882
    7f5c5a540852:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540855:	0f 84 27 00 00 00    	je     0x7f5c5a540882
    7f5c5a54085b:	41 8b 87 70 02 00 00 	mov    0x270(%r15),%eax
    7f5c5a540862:	8b c8                	mov    %eax,%ecx
    7f5c5a540864:	83 e1 01             	and    $0x1,%ecx
    7f5c5a540867:	41 89 8f 68 02 00 00 	mov    %ecx,0x268(%r15)
    7f5c5a54086e:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7f5c5a540871:	d1 e8                	shr    %eax
    7f5c5a540873:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f5c5a540876:	c1 e1 0f             	shl    $0xf,%ecx
    7f5c5a540879:	0b c1                	or     %ecx,%eax
    7f5c5a54087b:	41 89 87 70 02 00 00 	mov    %eax,0x270(%r15)
    7f5c5a540882:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540885:	0f 84 4e 00 00 00    	je     0x7f5c5a5408d9
    7f5c5a54088b:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7f5c5a540891:	41 89 87 60 02 00 00 	mov    %eax,0x260(%r15)
    7f5c5a540898:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f5c5a54089b:	41 8b 87 5c 02 00 00 	mov    0x25c(%r15),%eax
    7f5c5a5408a2:	49 8b cf             	mov    %r15,%rcx
    7f5c5a5408a5:	48 81 c1 1c 02 00 00 	add    $0x21c,%rcx
    7f5c5a5408ac:	8b d0                	mov    %eax,%edx
    7f5c5a5408ae:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f5c5a5408b1:	41 89 97 14 02 00 00 	mov    %edx,0x214(%r15)
    7f5c5a5408b8:	89 55 a8             	mov    %edx,-0x58(%rbp)
    7f5c5a5408bb:	8b d0                	mov    %eax,%edx
    7f5c5a5408bd:	8b b5 98 fd ff ff    	mov    -0x268(%rbp),%esi
    7f5c5a5408c3:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f5c5a5408c6:	ff c8                	dec    %eax
    7f5c5a5408c8:	b9 0e 00 00 00       	mov    $0xe,%ecx
    7f5c5a5408cd:	3b c1                	cmp    %ecx,%eax
    7f5c5a5408cf:	0f 47 c1             	cmova  %ecx,%eax
    7f5c5a5408d2:	41 89 87 5c 02 00 00 	mov    %eax,0x25c(%r15)
    7f5c5a5408d9:	45 85 e4             	test   %r12d,%r12d
    7f5c5a5408dc:	0f 84 17 00 00 00    	je     0x7f5c5a5408f9
    7f5c5a5408e2:	41 c7 87 0c 02 00 00 	movl   $0x0,0x20c(%r15)
    7f5c5a5408e9:	00 00 00 00 
    7f5c5a5408ed:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7f5c5a5408f4:	e9 10 00 00 00       	jmpq   0x7f5c5a540909
    7f5c5a5408f9:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7f5c5a5408ff:	41 89 87 0c 02 00 00 	mov    %eax,0x20c(%r15)
    7f5c5a540906:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f5c5a540909:	45 85 ed             	test   %r13d,%r13d
    7f5c5a54090c:	0f 84 17 00 00 00    	je     0x7f5c5a540929
    7f5c5a540912:	41 c7 87 04 02 00 00 	movl   $0x0,0x204(%r15)
    7f5c5a540919:	00 00 00 00 
    7f5c5a54091d:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7f5c5a540924:	e9 16 00 00 00       	jmpq   0x7f5c5a54093f
    7f5c5a540929:	45 85 f6             	test   %r14d,%r14d
    7f5c5a54092c:	0f 84 0d 00 00 00    	je     0x7f5c5a54093f
    7f5c5a540932:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f5c5a540935:	41 89 87 04 02 00 00 	mov    %eax,0x204(%r15)
    7f5c5a54093c:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f5c5a54093f:	45 85 f6             	test   %r14d,%r14d
    7f5c5a540942:	0f 84 1d 00 00 00    	je     0x7f5c5a540965
    7f5c5a540948:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f5c5a54094b:	41 89 87 fc 01 00 00 	mov    %eax,0x1fc(%r15)
    7f5c5a540952:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f5c5a540955:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7f5c5a54095b:	41 89 87 f4 01 00 00 	mov    %eax,0x1f4(%r15)
    7f5c5a540962:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f5c5a540965:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540968:	0f 84 17 00 00 00    	je     0x7f5c5a540985
    7f5c5a54096e:	41 c7 87 ec 01 00 00 	movl   $0x0,0x1ec(%r15)
    7f5c5a540975:	00 00 00 00 
    7f5c5a540979:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7f5c5a540980:	e9 10 00 00 00       	jmpq   0x7f5c5a540995
    7f5c5a540985:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7f5c5a54098b:	41 89 87 ec 01 00 00 	mov    %eax,0x1ec(%r15)
    7f5c5a540992:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f5c5a540995:	45 85 ed             	test   %r13d,%r13d
    7f5c5a540998:	0f 84 22 00 00 00    	je     0x7f5c5a5409c0
    7f5c5a54099e:	41 c7 87 dc 01 00 00 	movl   $0x0,0x1dc(%r15)
    7f5c5a5409a5:	00 00 00 00 
    7f5c5a5409a9:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7f5c5a5409b0:	41 c7 87 e4 01 00 00 	movl   $0x0,0x1e4(%r15)
    7f5c5a5409b7:	00 00 00 00 
    7f5c5a5409bb:	e9 33 00 00 00       	jmpq   0x7f5c5a5409f3
    7f5c5a5409c0:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5409c3:	0f 84 2a 00 00 00    	je     0x7f5c5a5409f3
    7f5c5a5409c9:	41 8b 87 e4 01 00 00 	mov    0x1e4(%r15),%eax
    7f5c5a5409d0:	8b c8                	mov    %eax,%ecx
    7f5c5a5409d2:	83 e1 01             	and    $0x1,%ecx
    7f5c5a5409d5:	41 89 8f dc 01 00 00 	mov    %ecx,0x1dc(%r15)
    7f5c5a5409dc:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7f5c5a5409df:	d1 e8                	shr    %eax
    7f5c5a5409e1:	8b 8d 18 fe ff ff    	mov    -0x1e8(%rbp),%ecx
    7f5c5a5409e7:	c1 e1 1f             	shl    $0x1f,%ecx
    7f5c5a5409ea:	0b c1                	or     %ecx,%eax
    7f5c5a5409ec:	41 89 87 e4 01 00 00 	mov    %eax,0x1e4(%r15)
    7f5c5a5409f3:	45 85 f6             	test   %r14d,%r14d
    7f5c5a5409f6:	0f 84 4e 00 00 00    	je     0x7f5c5a540a4a
    7f5c5a5409fc:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7f5c5a540a02:	41 89 87 d4 01 00 00 	mov    %eax,0x1d4(%r15)
    7f5c5a540a09:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f5c5a540a0c:	41 8b 87 d0 01 00 00 	mov    0x1d0(%r15),%eax
    7f5c5a540a13:	49 8b cf             	mov    %r15,%rcx
    7f5c5a540a16:	48 81 c1 50 01 00 00 	add    $0x150,%rcx
    7f5c5a540a1d:	8b d0                	mov    %eax,%edx
    7f5c5a540a1f:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f5c5a540a22:	41 89 97 48 01 00 00 	mov    %edx,0x148(%r15)
    7f5c5a540a29:	89 55 e8             	mov    %edx,-0x18(%rbp)
    7f5c5a540a2c:	8b d0                	mov    %eax,%edx
    7f5c5a540a2e:	8b b5 e8 fd ff ff    	mov    -0x218(%rbp),%esi
    7f5c5a540a34:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f5c5a540a37:	ff c8                	dec    %eax
    7f5c5a540a39:	b9 1e 00 00 00       	mov    $0x1e,%ecx
    7f5c5a540a3e:	3b c1                	cmp    %ecx,%eax
    7f5c5a540a40:	0f 47 c1             	cmova  %ecx,%eax
    7f5c5a540a43:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7f5c5a540a4a:	45 85 e4             	test   %r12d,%r12d
    7f5c5a540a4d:	0f 84 17 00 00 00    	je     0x7f5c5a540a6a
    7f5c5a540a53:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7f5c5a540a5a:	00 00 00 00 
    7f5c5a540a5e:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7f5c5a540a65:	e9 10 00 00 00       	jmpq   0x7f5c5a540a7a
    7f5c5a540a6a:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7f5c5a540a70:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7f5c5a540a77:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f5c5a540a7a:	8b c3                	mov    %ebx,%eax
    7f5c5a540a7c:	c1 e8 02             	shr    $0x2,%eax
    7f5c5a540a7f:	83 e0 01             	and    $0x1,%eax
    7f5c5a540a82:	85 c0                	test   %eax,%eax
    7f5c5a540a84:	0f 94 c0             	sete   %al
    7f5c5a540a87:	0f b6 c0             	movzbl %al,%eax
    7f5c5a540a8a:	48 8b 95 40 fe ff ff 	mov    -0x1c0(%rbp),%rdx
    7f5c5a540a91:	48 8b 4a 28          	mov    0x28(%rdx),%rcx
    7f5c5a540a95:	89 01                	mov    %eax,(%rcx)
    7f5c5a540a97:	48 8b 42 30          	mov    0x30(%rdx),%rax
    7f5c5a540a9b:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7f5c5a540aa1:	89 08                	mov    %ecx,(%rax)
    7f5c5a540aa3:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f5c5a540aa9:	83 e0 01             	and    $0x1,%eax
    7f5c5a540aac:	85 c0                	test   %eax,%eax
    7f5c5a540aae:	0f 94 c0             	sete   %al
    7f5c5a540ab1:	0f b6 c0             	movzbl %al,%eax
    7f5c5a540ab4:	48 8b 52 38          	mov    0x38(%rdx),%rdx
    7f5c5a540ab8:	89 02                	mov    %eax,(%rdx)
    7f5c5a540aba:	33 c0                	xor    %eax,%eax
    7f5c5a540abc:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f5c5a540ac0:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f5c5a540ac5:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f5c5a540aca:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f5c5a540acf:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f5c5a540ad4:	48 8b e5             	mov    %rbp,%rsp
    7f5c5a540ad7:	5d                   	pop    %rbp
    7f5c5a540ad8:	c3                   	retq   

end

