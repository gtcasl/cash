function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fc61f99912d <.text>:
    7fc61f99912d:	55                   	push   %rbp
    7fc61f99912e:	48 8b ec             	mov    %rsp,%rbp
    7fc61f999131:	48 81 ec 70 05 00 00 	sub    $0x570,%rsp
    7fc61f999138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fc61f99913c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fc61f999141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fc61f999146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fc61f99914b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fc61f999150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fc61f999154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fc61f999158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fc61f99915c:	48 8b 00             	mov    (%rax),%rax
    7fc61f99915f:	41 8b 8f 40 01 00 00 	mov    0x140(%r15),%ecx
    7fc61f999166:	89 4d f0             	mov    %ecx,-0x10(%rbp)
    7fc61f999169:	41 8b 8f 48 01 00 00 	mov    0x148(%r15),%ecx
    7fc61f999170:	89 4d e8             	mov    %ecx,-0x18(%rbp)
    7fc61f999173:	41 8b 8f d4 01 00 00 	mov    0x1d4(%r15),%ecx
    7fc61f99917a:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7fc61f99917d:	41 8b 8f dc 01 00 00 	mov    0x1dc(%r15),%ecx
    7fc61f999184:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7fc61f999187:	41 8b 8f ec 01 00 00 	mov    0x1ec(%r15),%ecx
    7fc61f99918e:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7fc61f999191:	41 8b 8f f4 01 00 00 	mov    0x1f4(%r15),%ecx
    7fc61f999198:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7fc61f99919b:	41 8b 8f fc 01 00 00 	mov    0x1fc(%r15),%ecx
    7fc61f9991a2:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7fc61f9991a5:	41 8b 8f 04 02 00 00 	mov    0x204(%r15),%ecx
    7fc61f9991ac:	89 4d b8             	mov    %ecx,-0x48(%rbp)
    7fc61f9991af:	41 8b 8f 0c 02 00 00 	mov    0x20c(%r15),%ecx
    7fc61f9991b6:	89 4d b0             	mov    %ecx,-0x50(%rbp)
    7fc61f9991b9:	41 8b 8f 14 02 00 00 	mov    0x214(%r15),%ecx
    7fc61f9991c0:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    7fc61f9991c3:	41 8b 8f 60 02 00 00 	mov    0x260(%r15),%ecx
    7fc61f9991ca:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7fc61f9991cd:	41 8b 8f 68 02 00 00 	mov    0x268(%r15),%ecx
    7fc61f9991d4:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7fc61f9991d7:	41 8b 8f 78 02 00 00 	mov    0x278(%r15),%ecx
    7fc61f9991de:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7fc61f9991e1:	41 8b 8f 80 02 00 00 	mov    0x280(%r15),%ecx
    7fc61f9991e8:	89 4d 88             	mov    %ecx,-0x78(%rbp)
    7fc61f9991eb:	41 8b 8f 88 02 00 00 	mov    0x288(%r15),%ecx
    7fc61f9991f2:	89 4d 80             	mov    %ecx,-0x80(%rbp)
    7fc61f9991f5:	41 8b 8f 90 02 00 00 	mov    0x290(%r15),%ecx
    7fc61f9991fc:	89 8d 78 ff ff ff    	mov    %ecx,-0x88(%rbp)
    7fc61f999202:	41 8b 8f ac 02 00 00 	mov    0x2ac(%r15),%ecx
    7fc61f999209:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7fc61f99920f:	41 8b 8f bc 02 00 00 	mov    0x2bc(%r15),%ecx
    7fc61f999216:	89 8d 68 ff ff ff    	mov    %ecx,-0x98(%rbp)
    7fc61f99921c:	41 8b 8f c4 02 00 00 	mov    0x2c4(%r15),%ecx
    7fc61f999223:	89 8d 60 ff ff ff    	mov    %ecx,-0xa0(%rbp)
    7fc61f999229:	41 8b 8f f0 02 00 00 	mov    0x2f0(%r15),%ecx
    7fc61f999230:	89 8d 58 ff ff ff    	mov    %ecx,-0xa8(%rbp)
    7fc61f999236:	41 8b 8f f8 02 00 00 	mov    0x2f8(%r15),%ecx
    7fc61f99923d:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7fc61f999243:	41 8b 8f 08 03 00 00 	mov    0x308(%r15),%ecx
    7fc61f99924a:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%rbp)
    7fc61f999250:	41 8b 8f 10 03 00 00 	mov    0x310(%r15),%ecx
    7fc61f999257:	89 8d 40 ff ff ff    	mov    %ecx,-0xc0(%rbp)
    7fc61f99925d:	41 8b 8f 18 03 00 00 	mov    0x318(%r15),%ecx
    7fc61f999264:	89 8d 38 ff ff ff    	mov    %ecx,-0xc8(%rbp)
    7fc61f99926a:	41 8b 8f 20 03 00 00 	mov    0x320(%r15),%ecx
    7fc61f999271:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7fc61f999277:	41 8b 8f 28 03 00 00 	mov    0x328(%r15),%ecx
    7fc61f99927e:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7fc61f999284:	41 8b 8f 30 03 00 00 	mov    0x330(%r15),%ecx
    7fc61f99928b:	89 8d 20 ff ff ff    	mov    %ecx,-0xe0(%rbp)
    7fc61f999291:	41 8b 8f 4c 03 00 00 	mov    0x34c(%r15),%ecx
    7fc61f999298:	89 8d 18 ff ff ff    	mov    %ecx,-0xe8(%rbp)
    7fc61f99929e:	41 8b 8f 54 03 00 00 	mov    0x354(%r15),%ecx
    7fc61f9992a5:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7fc61f9992ab:	41 8b 8f 64 03 00 00 	mov    0x364(%r15),%ecx
    7fc61f9992b2:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7fc61f9992b8:	41 8b 8f 6c 03 00 00 	mov    0x36c(%r15),%ecx
    7fc61f9992bf:	89 8d 00 ff ff ff    	mov    %ecx,-0x100(%rbp)
    7fc61f9992c5:	41 8b 8f 74 03 00 00 	mov    0x374(%r15),%ecx
    7fc61f9992cc:	89 8d f8 fe ff ff    	mov    %ecx,-0x108(%rbp)
    7fc61f9992d2:	41 8b 8f 7c 03 00 00 	mov    0x37c(%r15),%ecx
    7fc61f9992d9:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7fc61f9992df:	41 8b 8f 98 03 00 00 	mov    0x398(%r15),%ecx
    7fc61f9992e6:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fc61f9992ec:	41 8b 8f a8 03 00 00 	mov    0x3a8(%r15),%ecx
    7fc61f9992f3:	89 8d e0 fe ff ff    	mov    %ecx,-0x120(%rbp)
    7fc61f9992f9:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7fc61f999300:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7fc61f999306:	41 8b 8f c0 03 00 00 	mov    0x3c0(%r15),%ecx
    7fc61f99930d:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7fc61f999313:	41 8b 8f c8 03 00 00 	mov    0x3c8(%r15),%ecx
    7fc61f99931a:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fc61f999320:	41 8b 8f d8 03 00 00 	mov    0x3d8(%r15),%ecx
    7fc61f999327:	89 8d c0 fe ff ff    	mov    %ecx,-0x140(%rbp)
    7fc61f99932d:	41 8b 8f e0 03 00 00 	mov    0x3e0(%r15),%ecx
    7fc61f999334:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7fc61f99933a:	41 8b 8f e8 03 00 00 	mov    0x3e8(%r15),%ecx
    7fc61f999341:	89 8d b0 fe ff ff    	mov    %ecx,-0x150(%rbp)
    7fc61f999347:	41 8b 8f f0 03 00 00 	mov    0x3f0(%r15),%ecx
    7fc61f99934e:	89 8d a8 fe ff ff    	mov    %ecx,-0x158(%rbp)
    7fc61f999354:	41 8b 8f f8 03 00 00 	mov    0x3f8(%r15),%ecx
    7fc61f99935b:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7fc61f999361:	41 8b 8f 00 04 00 00 	mov    0x400(%r15),%ecx
    7fc61f999368:	89 8d 98 fe ff ff    	mov    %ecx,-0x168(%rbp)
    7fc61f99936e:	41 8b 8f 08 04 00 00 	mov    0x408(%r15),%ecx
    7fc61f999375:	89 8d 90 fe ff ff    	mov    %ecx,-0x170(%rbp)
    7fc61f99937b:	41 8b 8f 10 04 00 00 	mov    0x410(%r15),%ecx
    7fc61f999382:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7fc61f999388:	41 8b 8f 20 04 00 00 	mov    0x420(%r15),%ecx
    7fc61f99938f:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7fc61f999395:	41 8b 9f 28 04 00 00 	mov    0x428(%r15),%ebx
    7fc61f99939c:	41 8b 8f 30 04 00 00 	mov    0x430(%r15),%ecx
    7fc61f9993a3:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7fc61f9993a9:	41 8b 8f 38 04 00 00 	mov    0x438(%r15),%ecx
    7fc61f9993b0:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7fc61f9993b6:	41 8b 8f 40 04 00 00 	mov    0x440(%r15),%ecx
    7fc61f9993bd:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7fc61f9993c3:	41 8b 8f 48 04 00 00 	mov    0x448(%r15),%ecx
    7fc61f9993ca:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7fc61f9993d0:	41 8b 8f 50 04 00 00 	mov    0x450(%r15),%ecx
    7fc61f9993d7:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7fc61f9993dd:	48 89 85 50 fe ff ff 	mov    %rax,-0x1b0(%rbp)
    7fc61f9993e4:	48 8b 40 18          	mov    0x18(%rax),%rax
    7fc61f9993e8:	8b 00                	mov    (%rax),%eax
    7fc61f9993ea:	41 8b 8f 58 04 00 00 	mov    0x458(%r15),%ecx
    7fc61f9993f1:	33 c8                	xor    %eax,%ecx
    7fc61f9993f3:	23 c8                	and    %eax,%ecx
    7fc61f9993f5:	41 89 87 58 04 00 00 	mov    %eax,0x458(%r15)
    7fc61f9993fc:	85 c9                	test   %ecx,%ecx
    7fc61f9993fe:	0f 84 42 17 00 00    	je     0x7fc61f99ab46
    7fc61f999404:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fc61f999407:	ff c0                	inc    %eax
    7fc61f999409:	83 e0 3f             	and    $0x3f,%eax
    7fc61f99940c:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7fc61f999412:	48 8b 85 50 fe ff ff 	mov    -0x1b0(%rbp),%rax
    7fc61f999419:	48 8b 40 20          	mov    0x20(%rax),%rax
    7fc61f99941d:	44 8b 28             	mov    (%rax),%r13d
    7fc61f999420:	45 8b e5             	mov    %r13d,%r12d
    7fc61f999423:	41 83 cc 00          	or     $0x0,%r12d
    7fc61f999427:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fc61f99942d:	85 c0                	test   %eax,%eax
    7fc61f99942f:	0f 94 c0             	sete   %al
    7fc61f999432:	0f b6 c0             	movzbl %al,%eax
    7fc61f999435:	85 c0                	test   %eax,%eax
    7fc61f999437:	0f 94 c0             	sete   %al
    7fc61f99943a:	0f b6 c0             	movzbl %al,%eax
    7fc61f99943d:	8b cb                	mov    %ebx,%ecx
    7fc61f99943f:	83 e1 01             	and    $0x1,%ecx
    7fc61f999442:	85 c9                	test   %ecx,%ecx
    7fc61f999444:	0f 94 c1             	sete   %cl
    7fc61f999447:	0f b6 c9             	movzbl %cl,%ecx
    7fc61f99944a:	85 c9                	test   %ecx,%ecx
    7fc61f99944c:	0f 94 c2             	sete   %dl
    7fc61f99944f:	0f b6 d2             	movzbl %dl,%edx
    7fc61f999452:	23 c2                	and    %edx,%eax
    7fc61f999454:	85 c0                	test   %eax,%eax
    7fc61f999456:	0f 94 c0             	sete   %al
    7fc61f999459:	0f b6 c0             	movzbl %al,%eax
    7fc61f99945c:	8b 95 88 fe ff ff    	mov    -0x178(%rbp),%edx
    7fc61f999462:	23 d0                	and    %eax,%edx
    7fc61f999464:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7fc61f99946a:	c1 ee 02             	shr    $0x2,%esi
    7fc61f99946d:	83 e6 01             	and    $0x1,%esi
    7fc61f999470:	85 f6                	test   %esi,%esi
    7fc61f999472:	40 0f 94 c6          	sete   %sil
    7fc61f999476:	40 0f b6 f6          	movzbl %sil,%esi
    7fc61f99947a:	89 b5 40 fe ff ff    	mov    %esi,-0x1c0(%rbp)
    7fc61f999480:	85 f6                	test   %esi,%esi
    7fc61f999482:	40 0f 94 c6          	sete   %sil
    7fc61f999486:	40 0f b6 f6          	movzbl %sil,%esi
    7fc61f99948a:	89 95 38 fe ff ff    	mov    %edx,-0x1c8(%rbp)
    7fc61f999490:	23 d6                	and    %esi,%edx
    7fc61f999492:	85 d2                	test   %edx,%edx
    7fc61f999494:	0f 94 c2             	sete   %dl
    7fc61f999497:	0f b6 d2             	movzbl %dl,%edx
    7fc61f99949a:	89 8d 30 fe ff ff    	mov    %ecx,-0x1d0(%rbp)
    7fc61f9994a0:	23 ca                	and    %edx,%ecx
    7fc61f9994a2:	89 95 28 fe ff ff    	mov    %edx,-0x1d8(%rbp)
    7fc61f9994a8:	23 c2                	and    %edx,%eax
    7fc61f9994aa:	89 8d 20 fe ff ff    	mov    %ecx,-0x1e0(%rbp)
    7fc61f9994b0:	4c 8b f0             	mov    %rax,%r14
    7fc61f9994b3:	23 c8                	and    %eax,%ecx
    7fc61f9994b5:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7fc61f9994bb:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fc61f9994be:	c1 e8 05             	shr    $0x5,%eax
    7fc61f9994c1:	83 e0 01             	and    $0x1,%eax
    7fc61f9994c4:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7fc61f9994c7:	c1 e9 10             	shr    $0x10,%ecx
    7fc61f9994ca:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9994d0:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7fc61f9994d6:	c1 ea 10             	shr    $0x10,%edx
    7fc61f9994d9:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f9994df:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7fc61f9994e5:	89 95 08 fe ff ff    	mov    %edx,-0x1f8(%rbp)
    7fc61f9994eb:	2b ca                	sub    %edx,%ecx
    7fc61f9994ed:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9994f3:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fc61f9994f6:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f9994fc:	8b b5 78 fe ff ff    	mov    -0x188(%rbp),%esi
    7fc61f999502:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f999508:	89 95 00 fe ff ff    	mov    %edx,-0x200(%rbp)
    7fc61f99950e:	89 b5 f8 fd ff ff    	mov    %esi,-0x208(%rbp)
    7fc61f999514:	2b d6                	sub    %esi,%edx
    7fc61f999516:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99951c:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f99951f:	0b d1                	or     %ecx,%edx
    7fc61f999521:	89 95 f0 fd ff ff    	mov    %edx,-0x210(%rbp)
    7fc61f999527:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%rbp)
    7fc61f99952d:	85 c0                	test   %eax,%eax
    7fc61f99952f:	0f 85 0c 00 00 00    	jne    0x7fc61f999541
    7fc61f999535:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7fc61f99953b:	89 85 f0 fd ff ff    	mov    %eax,-0x210(%rbp)
    7fc61f999541:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fc61f999547:	03 85 08 fe ff ff    	add    -0x1f8(%rbp),%eax
    7fc61f99954d:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999552:	8b 8d 00 fe ff ff    	mov    -0x200(%rbp),%ecx
    7fc61f999558:	03 8d f8 fd ff ff    	add    -0x208(%rbp),%ecx
    7fc61f99955e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999564:	c1 e0 10             	shl    $0x10,%eax
    7fc61f999567:	0b c8                	or     %eax,%ecx
    7fc61f999569:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fc61f99956f:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7fc61f999575:	85 c0                	test   %eax,%eax
    7fc61f999577:	0f 85 09 00 00 00    	jne    0x7fc61f999586
    7fc61f99957d:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7fc61f999580:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7fc61f999586:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fc61f999589:	ff c0                	inc    %eax
    7fc61f99958b:	83 e0 3f             	and    $0x3f,%eax
    7fc61f99958e:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7fc61f999594:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fc61f999597:	41 23 c6             	and    %r14d,%eax
    7fc61f99959a:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7fc61f9995a0:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fc61f9995a3:	c1 e8 05             	shr    $0x5,%eax
    7fc61f9995a6:	83 e0 01             	and    $0x1,%eax
    7fc61f9995a9:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fc61f9995ac:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9995b2:	f7 d9                	neg    %ecx
    7fc61f9995b4:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9995ba:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fc61f9995bd:	c1 ea 10             	shr    $0x10,%edx
    7fc61f9995c0:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f9995c6:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f9995c9:	0b d1                	or     %ecx,%edx
    7fc61f9995cb:	89 95 c8 fd ff ff    	mov    %edx,-0x238(%rbp)
    7fc61f9995d1:	85 c0                	test   %eax,%eax
    7fc61f9995d3:	0f 85 09 00 00 00    	jne    0x7fc61f9995e2
    7fc61f9995d9:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fc61f9995dc:	89 85 c8 fd ff ff    	mov    %eax,-0x238(%rbp)
    7fc61f9995e2:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fc61f9995e5:	ff c0                	inc    %eax
    7fc61f9995e7:	83 e0 1f             	and    $0x1f,%eax
    7fc61f9995ea:	89 85 c0 fd ff ff    	mov    %eax,-0x240(%rbp)
    7fc61f9995f0:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7fc61f9995f3:	41 23 c6             	and    %r14d,%eax
    7fc61f9995f6:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7fc61f9995fc:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fc61f9995ff:	c1 e8 04             	shr    $0x4,%eax
    7fc61f999602:	83 e0 01             	and    $0x1,%eax
    7fc61f999605:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fc61f999608:	c1 e9 10             	shr    $0x10,%ecx
    7fc61f99960b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999611:	8b 55 c8             	mov    -0x38(%rbp),%edx
    7fc61f999614:	c1 ea 10             	shr    $0x10,%edx
    7fc61f999617:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99961d:	89 8d b0 fd ff ff    	mov    %ecx,-0x250(%rbp)
    7fc61f999623:	89 95 a8 fd ff ff    	mov    %edx,-0x258(%rbp)
    7fc61f999629:	2b ca                	sub    %edx,%ecx
    7fc61f99962b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999631:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7fc61f999634:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99963a:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7fc61f99963d:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f999643:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7fc61f999649:	89 b5 98 fd ff ff    	mov    %esi,-0x268(%rbp)
    7fc61f99964f:	2b d6                	sub    %esi,%edx
    7fc61f999651:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999657:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f99965a:	0b d1                	or     %ecx,%edx
    7fc61f99965c:	89 95 90 fd ff ff    	mov    %edx,-0x270(%rbp)
    7fc61f999662:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7fc61f999668:	85 c0                	test   %eax,%eax
    7fc61f99966a:	0f 85 09 00 00 00    	jne    0x7fc61f999679
    7fc61f999670:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fc61f999673:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7fc61f999679:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fc61f99967f:	03 85 a8 fd ff ff    	add    -0x258(%rbp),%eax
    7fc61f999685:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f99968a:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fc61f999690:	03 8d 98 fd ff ff    	add    -0x268(%rbp),%ecx
    7fc61f999696:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f99969c:	c1 e0 10             	shl    $0x10,%eax
    7fc61f99969f:	0b c8                	or     %eax,%ecx
    7fc61f9996a1:	89 8d 80 fd ff ff    	mov    %ecx,-0x280(%rbp)
    7fc61f9996a7:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7fc61f9996ad:	85 c0                	test   %eax,%eax
    7fc61f9996af:	0f 85 09 00 00 00    	jne    0x7fc61f9996be
    7fc61f9996b5:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fc61f9996b8:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fc61f9996be:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fc61f9996c1:	ff c0                	inc    %eax
    7fc61f9996c3:	83 e0 3f             	and    $0x3f,%eax
    7fc61f9996c6:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7fc61f9996cc:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fc61f9996cf:	41 23 c6             	and    %r14d,%eax
    7fc61f9996d2:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7fc61f9996d8:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fc61f9996db:	8b c0                	mov    %eax,%eax
    7fc61f9996dd:	41 8b 04 87          	mov    (%r15,%rax,4),%eax
    7fc61f9996e1:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7fc61f9996e7:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fc61f9996ea:	c1 e8 10             	shr    $0x10,%eax
    7fc61f9996ed:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f9996f2:	8b 4d 80             	mov    -0x80(%rbp),%ecx
    7fc61f9996f5:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9996fb:	0f b7 d0             	movzwl %ax,%edx
    7fc61f9996fe:	0f bf d2             	movswl %dx,%edx
    7fc61f999701:	0f b7 f1             	movzwl %cx,%esi
    7fc61f999704:	0f bf f6             	movswl %si,%esi
    7fc61f999707:	0f af d6             	imul   %esi,%edx
    7fc61f99970a:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fc61f999710:	8b 75 88             	mov    -0x78(%rbp),%esi
    7fc61f999713:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f999719:	8b 7d 80             	mov    -0x80(%rbp),%edi
    7fc61f99971c:	c1 ef 10             	shr    $0x10,%edi
    7fc61f99971f:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7fc61f999725:	44 0f b7 c6          	movzwl %si,%r8d
    7fc61f999729:	45 0f bf c0          	movswl %r8w,%r8d
    7fc61f99972d:	44 0f b7 cf          	movzwl %di,%r9d
    7fc61f999731:	45 0f bf c9          	movswl %r9w,%r9d
    7fc61f999735:	45 0f af c1          	imul   %r9d,%r8d
    7fc61f999739:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7fc61f999740:	41 03 d0             	add    %r8d,%edx
    7fc61f999743:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fc61f999749:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7fc61f99974f:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7fc61f999755:	89 95 60 fd ff ff    	mov    %edx,-0x2a0(%rbp)
    7fc61f99975b:	c1 fa 0f             	sar    $0xf,%edx
    7fc61f99975e:	89 95 58 fd ff ff    	mov    %edx,-0x2a8(%rbp)
    7fc61f999764:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99976a:	89 b5 50 fd ff ff    	mov    %esi,-0x2b0(%rbp)
    7fc61f999770:	0f b7 f6             	movzwl %si,%esi
    7fc61f999773:	0f bf f6             	movswl %si,%esi
    7fc61f999776:	89 8d 48 fd ff ff    	mov    %ecx,-0x2b8(%rbp)
    7fc61f99977c:	0f b7 c9             	movzwl %cx,%ecx
    7fc61f99977f:	0f bf c9             	movswl %cx,%ecx
    7fc61f999782:	0f af f1             	imul   %ecx,%esi
    7fc61f999785:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fc61f99978b:	89 85 40 fd ff ff    	mov    %eax,-0x2c0(%rbp)
    7fc61f999791:	0f b7 c0             	movzwl %ax,%eax
    7fc61f999794:	0f bf c0             	movswl %ax,%eax
    7fc61f999797:	89 bd 38 fd ff ff    	mov    %edi,-0x2c8(%rbp)
    7fc61f99979d:	0f b7 ff             	movzwl %di,%edi
    7fc61f9997a0:	0f bf cf             	movswl %di,%ecx
    7fc61f9997a3:	0f af c1             	imul   %ecx,%eax
    7fc61f9997a6:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7fc61f9997ab:	2b f0                	sub    %eax,%esi
    7fc61f9997ad:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fc61f9997b3:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7fc61f9997b9:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7fc61f9997bf:	89 b5 30 fd ff ff    	mov    %esi,-0x2d0(%rbp)
    7fc61f9997c5:	c1 fe 0f             	sar    $0xf,%esi
    7fc61f9997c8:	89 b5 28 fd ff ff    	mov    %esi,-0x2d8(%rbp)
    7fc61f9997ce:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f9997d4:	89 95 20 fd ff ff    	mov    %edx,-0x2e0(%rbp)
    7fc61f9997da:	c1 e2 10             	shl    $0x10,%edx
    7fc61f9997dd:	0b f2                	or     %edx,%esi
    7fc61f9997df:	89 b5 18 fd ff ff    	mov    %esi,-0x2e8(%rbp)
    7fc61f9997e5:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fc61f9997eb:	ff c0                	inc    %eax
    7fc61f9997ed:	83 e0 0f             	and    $0xf,%eax
    7fc61f9997f0:	89 85 10 fd ff ff    	mov    %eax,-0x2f0(%rbp)
    7fc61f9997f6:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fc61f9997fc:	41 23 c6             	and    %r14d,%eax
    7fc61f9997ff:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7fc61f999805:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fc61f99980b:	c1 e8 03             	shr    $0x3,%eax
    7fc61f99980e:	83 e0 01             	and    $0x1,%eax
    7fc61f999811:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7fc61f999817:	c1 e9 10             	shr    $0x10,%ecx
    7fc61f99981a:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999820:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7fc61f999826:	c1 ea 10             	shr    $0x10,%edx
    7fc61f999829:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99982f:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7fc61f999835:	89 95 f8 fc ff ff    	mov    %edx,-0x308(%rbp)
    7fc61f99983b:	2b ca                	sub    %edx,%ecx
    7fc61f99983d:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999843:	8b 95 60 ff ff ff    	mov    -0xa0(%rbp),%edx
    7fc61f999849:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99984f:	8b b5 78 ff ff ff    	mov    -0x88(%rbp),%esi
    7fc61f999855:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f99985b:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7fc61f999861:	89 b5 e8 fc ff ff    	mov    %esi,-0x318(%rbp)
    7fc61f999867:	2b d6                	sub    %esi,%edx
    7fc61f999869:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99986f:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f999872:	0b d1                	or     %ecx,%edx
    7fc61f999874:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7fc61f99987a:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fc61f999880:	85 c0                	test   %eax,%eax
    7fc61f999882:	0f 85 0c 00 00 00    	jne    0x7fc61f999894
    7fc61f999888:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fc61f99988e:	89 85 e0 fc ff ff    	mov    %eax,-0x320(%rbp)
    7fc61f999894:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fc61f99989a:	03 85 f8 fc ff ff    	add    -0x308(%rbp),%eax
    7fc61f9998a0:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f9998a5:	8b 8d f0 fc ff ff    	mov    -0x310(%rbp),%ecx
    7fc61f9998ab:	03 8d e8 fc ff ff    	add    -0x318(%rbp),%ecx
    7fc61f9998b1:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9998b7:	c1 e0 10             	shl    $0x10,%eax
    7fc61f9998ba:	0b c8                	or     %eax,%ecx
    7fc61f9998bc:	89 8d d0 fc ff ff    	mov    %ecx,-0x330(%rbp)
    7fc61f9998c2:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7fc61f9998c8:	85 c0                	test   %eax,%eax
    7fc61f9998ca:	0f 85 0c 00 00 00    	jne    0x7fc61f9998dc
    7fc61f9998d0:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fc61f9998d6:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7fc61f9998dc:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fc61f9998e2:	ff c0                	inc    %eax
    7fc61f9998e4:	83 e0 0f             	and    $0xf,%eax
    7fc61f9998e7:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7fc61f9998ed:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fc61f9998f3:	41 23 c6             	and    %r14d,%eax
    7fc61f9998f6:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7fc61f9998fc:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fc61f999902:	c1 e8 03             	shr    $0x3,%eax
    7fc61f999905:	83 e0 01             	and    $0x1,%eax
    7fc61f999908:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7fc61f99990e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999914:	f7 d9                	neg    %ecx
    7fc61f999916:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f99991c:	8b 95 58 ff ff ff    	mov    -0xa8(%rbp),%edx
    7fc61f999922:	c1 ea 10             	shr    $0x10,%edx
    7fc61f999925:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f99992b:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f99992e:	0b d1                	or     %ecx,%edx
    7fc61f999930:	89 95 b8 fc ff ff    	mov    %edx,-0x348(%rbp)
    7fc61f999936:	85 c0                	test   %eax,%eax
    7fc61f999938:	0f 85 0c 00 00 00    	jne    0x7fc61f99994a
    7fc61f99993e:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fc61f999944:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7fc61f99994a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fc61f999950:	ff c0                	inc    %eax
    7fc61f999952:	83 e0 07             	and    $0x7,%eax
    7fc61f999955:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7fc61f99995b:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fc61f999961:	41 23 c6             	and    %r14d,%eax
    7fc61f999964:	89 85 a8 fc ff ff    	mov    %eax,-0x358(%rbp)
    7fc61f99996a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fc61f999970:	c1 e8 02             	shr    $0x2,%eax
    7fc61f999973:	83 e0 01             	and    $0x1,%eax
    7fc61f999976:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7fc61f99997c:	c1 e9 10             	shr    $0x10,%ecx
    7fc61f99997f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999985:	8b 95 40 ff ff ff    	mov    -0xc0(%rbp),%edx
    7fc61f99998b:	c1 ea 10             	shr    $0x10,%edx
    7fc61f99998e:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999994:	89 8d a0 fc ff ff    	mov    %ecx,-0x360(%rbp)
    7fc61f99999a:	89 95 98 fc ff ff    	mov    %edx,-0x368(%rbp)
    7fc61f9999a0:	2b ca                	sub    %edx,%ecx
    7fc61f9999a2:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f9999a8:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7fc61f9999ae:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f9999b4:	8b b5 40 ff ff ff    	mov    -0xc0(%rbp),%esi
    7fc61f9999ba:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f9999c0:	89 95 90 fc ff ff    	mov    %edx,-0x370(%rbp)
    7fc61f9999c6:	89 b5 88 fc ff ff    	mov    %esi,-0x378(%rbp)
    7fc61f9999cc:	2b d6                	sub    %esi,%edx
    7fc61f9999ce:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f9999d4:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f9999d7:	0b d1                	or     %ecx,%edx
    7fc61f9999d9:	89 95 80 fc ff ff    	mov    %edx,-0x380(%rbp)
    7fc61f9999df:	89 85 78 fc ff ff    	mov    %eax,-0x388(%rbp)
    7fc61f9999e5:	85 c0                	test   %eax,%eax
    7fc61f9999e7:	0f 85 0c 00 00 00    	jne    0x7fc61f9999f9
    7fc61f9999ed:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fc61f9999f3:	89 85 80 fc ff ff    	mov    %eax,-0x380(%rbp)
    7fc61f9999f9:	8b 85 a0 fc ff ff    	mov    -0x360(%rbp),%eax
    7fc61f9999ff:	03 85 98 fc ff ff    	add    -0x368(%rbp),%eax
    7fc61f999a05:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999a0a:	8b 8d 90 fc ff ff    	mov    -0x370(%rbp),%ecx
    7fc61f999a10:	03 8d 88 fc ff ff    	add    -0x378(%rbp),%ecx
    7fc61f999a16:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999a1c:	c1 e0 10             	shl    $0x10,%eax
    7fc61f999a1f:	0b c8                	or     %eax,%ecx
    7fc61f999a21:	89 8d 70 fc ff ff    	mov    %ecx,-0x390(%rbp)
    7fc61f999a27:	8b 85 78 fc ff ff    	mov    -0x388(%rbp),%eax
    7fc61f999a2d:	85 c0                	test   %eax,%eax
    7fc61f999a2f:	0f 85 0c 00 00 00    	jne    0x7fc61f999a41
    7fc61f999a35:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fc61f999a3b:	89 85 70 fc ff ff    	mov    %eax,-0x390(%rbp)
    7fc61f999a41:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fc61f999a47:	ff c0                	inc    %eax
    7fc61f999a49:	83 e0 0f             	and    $0xf,%eax
    7fc61f999a4c:	89 85 68 fc ff ff    	mov    %eax,-0x398(%rbp)
    7fc61f999a52:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fc61f999a58:	41 23 c6             	and    %r14d,%eax
    7fc61f999a5b:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7fc61f999a61:	49 8b c7             	mov    %r15,%rax
    7fc61f999a64:	48 05 00 01 00 00    	add    $0x100,%rax
    7fc61f999a6a:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7fc61f999a70:	8b c9                	mov    %ecx,%ecx
    7fc61f999a72:	8b 04 88             	mov    (%rax,%rcx,4),%eax
    7fc61f999a75:	89 85 58 fc ff ff    	mov    %eax,-0x3a8(%rbp)
    7fc61f999a7b:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fc61f999a81:	c1 e8 10             	shr    $0x10,%eax
    7fc61f999a84:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999a89:	8b 8d f8 fe ff ff    	mov    -0x108(%rbp),%ecx
    7fc61f999a8f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999a95:	0f b7 d0             	movzwl %ax,%edx
    7fc61f999a98:	0f bf d2             	movswl %dx,%edx
    7fc61f999a9b:	0f b7 f1             	movzwl %cx,%esi
    7fc61f999a9e:	0f bf f6             	movswl %si,%esi
    7fc61f999aa1:	0f af d6             	imul   %esi,%edx
    7fc61f999aa4:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fc61f999aaa:	8b b5 00 ff ff ff    	mov    -0x100(%rbp),%esi
    7fc61f999ab0:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f999ab6:	8b bd f8 fe ff ff    	mov    -0x108(%rbp),%edi
    7fc61f999abc:	c1 ef 10             	shr    $0x10,%edi
    7fc61f999abf:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7fc61f999ac5:	44 0f b7 c6          	movzwl %si,%r8d
    7fc61f999ac9:	45 0f bf c0          	movswl %r8w,%r8d
    7fc61f999acd:	44 0f b7 cf          	movzwl %di,%r9d
    7fc61f999ad1:	45 0f bf c9          	movswl %r9w,%r9d
    7fc61f999ad5:	45 0f af c1          	imul   %r9d,%r8d
    7fc61f999ad9:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7fc61f999ae0:	41 03 d0             	add    %r8d,%edx
    7fc61f999ae3:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fc61f999ae9:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7fc61f999aef:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7fc61f999af5:	89 95 50 fc ff ff    	mov    %edx,-0x3b0(%rbp)
    7fc61f999afb:	c1 fa 0f             	sar    $0xf,%edx
    7fc61f999afe:	89 95 48 fc ff ff    	mov    %edx,-0x3b8(%rbp)
    7fc61f999b04:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999b0a:	89 b5 40 fc ff ff    	mov    %esi,-0x3c0(%rbp)
    7fc61f999b10:	0f b7 f6             	movzwl %si,%esi
    7fc61f999b13:	0f bf f6             	movswl %si,%esi
    7fc61f999b16:	89 8d 38 fc ff ff    	mov    %ecx,-0x3c8(%rbp)
    7fc61f999b1c:	0f b7 c9             	movzwl %cx,%ecx
    7fc61f999b1f:	0f bf c9             	movswl %cx,%ecx
    7fc61f999b22:	0f af f1             	imul   %ecx,%esi
    7fc61f999b25:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fc61f999b2b:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fc61f999b31:	0f b7 c0             	movzwl %ax,%eax
    7fc61f999b34:	0f bf c0             	movswl %ax,%eax
    7fc61f999b37:	89 bd 28 fc ff ff    	mov    %edi,-0x3d8(%rbp)
    7fc61f999b3d:	0f b7 ff             	movzwl %di,%edi
    7fc61f999b40:	0f bf cf             	movswl %di,%ecx
    7fc61f999b43:	0f af c1             	imul   %ecx,%eax
    7fc61f999b46:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7fc61f999b4b:	2b f0                	sub    %eax,%esi
    7fc61f999b4d:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fc61f999b53:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7fc61f999b59:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7fc61f999b5f:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7fc61f999b65:	c1 fe 0f             	sar    $0xf,%esi
    7fc61f999b68:	89 b5 18 fc ff ff    	mov    %esi,-0x3e8(%rbp)
    7fc61f999b6e:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f999b74:	89 95 10 fc ff ff    	mov    %edx,-0x3f0(%rbp)
    7fc61f999b7a:	c1 e2 10             	shl    $0x10,%edx
    7fc61f999b7d:	0b f2                	or     %edx,%esi
    7fc61f999b7f:	89 b5 08 fc ff ff    	mov    %esi,-0x3f8(%rbp)
    7fc61f999b85:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fc61f999b8b:	ff c0                	inc    %eax
    7fc61f999b8d:	83 e0 03             	and    $0x3,%eax
    7fc61f999b90:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fc61f999b96:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fc61f999b9c:	41 23 c6             	and    %r14d,%eax
    7fc61f999b9f:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7fc61f999ba5:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fc61f999bab:	d1 e8                	shr    %eax
    7fc61f999bad:	83 e0 01             	and    $0x1,%eax
    7fc61f999bb0:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7fc61f999bb6:	c1 e9 10             	shr    $0x10,%ecx
    7fc61f999bb9:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999bbf:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fc61f999bc5:	c1 ea 10             	shr    $0x10,%edx
    7fc61f999bc8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999bce:	89 8d f0 fb ff ff    	mov    %ecx,-0x410(%rbp)
    7fc61f999bd4:	89 95 e8 fb ff ff    	mov    %edx,-0x418(%rbp)
    7fc61f999bda:	2b ca                	sub    %edx,%ecx
    7fc61f999bdc:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999be2:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7fc61f999be8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999bee:	8b b5 f0 fe ff ff    	mov    -0x110(%rbp),%esi
    7fc61f999bf4:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fc61f999bfa:	89 95 e0 fb ff ff    	mov    %edx,-0x420(%rbp)
    7fc61f999c00:	89 b5 d8 fb ff ff    	mov    %esi,-0x428(%rbp)
    7fc61f999c06:	2b d6                	sub    %esi,%edx
    7fc61f999c08:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999c0e:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f999c11:	0b d1                	or     %ecx,%edx
    7fc61f999c13:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7fc61f999c19:	89 85 c8 fb ff ff    	mov    %eax,-0x438(%rbp)
    7fc61f999c1f:	85 c0                	test   %eax,%eax
    7fc61f999c21:	0f 85 0c 00 00 00    	jne    0x7fc61f999c33
    7fc61f999c27:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7fc61f999c2d:	89 85 d0 fb ff ff    	mov    %eax,-0x430(%rbp)
    7fc61f999c33:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7fc61f999c39:	03 85 e8 fb ff ff    	add    -0x418(%rbp),%eax
    7fc61f999c3f:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999c44:	8b 8d e0 fb ff ff    	mov    -0x420(%rbp),%ecx
    7fc61f999c4a:	03 8d d8 fb ff ff    	add    -0x428(%rbp),%ecx
    7fc61f999c50:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999c56:	c1 e0 10             	shl    $0x10,%eax
    7fc61f999c59:	0b c8                	or     %eax,%ecx
    7fc61f999c5b:	89 8d c0 fb ff ff    	mov    %ecx,-0x440(%rbp)
    7fc61f999c61:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7fc61f999c67:	85 c0                	test   %eax,%eax
    7fc61f999c69:	0f 85 0c 00 00 00    	jne    0x7fc61f999c7b
    7fc61f999c6f:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fc61f999c75:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7fc61f999c7b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fc61f999c81:	ff c0                	inc    %eax
    7fc61f999c83:	83 e0 03             	and    $0x3,%eax
    7fc61f999c86:	89 85 b8 fb ff ff    	mov    %eax,-0x448(%rbp)
    7fc61f999c8c:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fc61f999c92:	41 23 c6             	and    %r14d,%eax
    7fc61f999c95:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7fc61f999c9b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fc61f999ca1:	d1 e8                	shr    %eax
    7fc61f999ca3:	83 e0 01             	and    $0x1,%eax
    7fc61f999ca6:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7fc61f999cac:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999cb2:	f7 d9                	neg    %ecx
    7fc61f999cb4:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999cba:	8b 95 d0 fe ff ff    	mov    -0x130(%rbp),%edx
    7fc61f999cc0:	c1 ea 10             	shr    $0x10,%edx
    7fc61f999cc3:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999cc9:	c1 e1 10             	shl    $0x10,%ecx
    7fc61f999ccc:	0b d1                	or     %ecx,%edx
    7fc61f999cce:	89 95 a8 fb ff ff    	mov    %edx,-0x458(%rbp)
    7fc61f999cd4:	85 c0                	test   %eax,%eax
    7fc61f999cd6:	0f 85 0c 00 00 00    	jne    0x7fc61f999ce8
    7fc61f999cdc:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fc61f999ce2:	89 85 a8 fb ff ff    	mov    %eax,-0x458(%rbp)
    7fc61f999ce8:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fc61f999cee:	ff c0                	inc    %eax
    7fc61f999cf0:	83 e0 01             	and    $0x1,%eax
    7fc61f999cf3:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7fc61f999cf9:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fc61f999cff:	41 23 c6             	and    %r14d,%eax
    7fc61f999d02:	89 85 98 fb ff ff    	mov    %eax,-0x468(%rbp)
    7fc61f999d08:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fc61f999d0e:	c1 e8 10             	shr    $0x10,%eax
    7fc61f999d11:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999d16:	8b 8d b8 fe ff ff    	mov    -0x148(%rbp),%ecx
    7fc61f999d1c:	c1 e9 10             	shr    $0x10,%ecx
    7fc61f999d1f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999d25:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fc61f999d2b:	89 8d 88 fb ff ff    	mov    %ecx,-0x478(%rbp)
    7fc61f999d31:	2b c1                	sub    %ecx,%eax
    7fc61f999d33:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999d38:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7fc61f999d3e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999d44:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7fc61f999d4a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fc61f999d50:	89 8d 80 fb ff ff    	mov    %ecx,-0x480(%rbp)
    7fc61f999d56:	89 95 78 fb ff ff    	mov    %edx,-0x488(%rbp)
    7fc61f999d5c:	2b ca                	sub    %edx,%ecx
    7fc61f999d5e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999d64:	c1 e0 10             	shl    $0x10,%eax
    7fc61f999d67:	0b c8                	or     %eax,%ecx
    7fc61f999d69:	89 8d 70 fb ff ff    	mov    %ecx,-0x490(%rbp)
    7fc61f999d6f:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fc61f999d75:	85 c0                	test   %eax,%eax
    7fc61f999d77:	0f 85 0c 00 00 00    	jne    0x7fc61f999d89
    7fc61f999d7d:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7fc61f999d83:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7fc61f999d89:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7fc61f999d8f:	03 85 88 fb ff ff    	add    -0x478(%rbp),%eax
    7fc61f999d95:	25 ff ff 00 00       	and    $0xffff,%eax
    7fc61f999d9a:	8b 8d 80 fb ff ff    	mov    -0x480(%rbp),%ecx
    7fc61f999da0:	03 8d 78 fb ff ff    	add    -0x488(%rbp),%ecx
    7fc61f999da6:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fc61f999dac:	c1 e0 10             	shl    $0x10,%eax
    7fc61f999daf:	0b c8                	or     %eax,%ecx
    7fc61f999db1:	89 8d 68 fb ff ff    	mov    %ecx,-0x498(%rbp)
    7fc61f999db7:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fc61f999dbd:	85 c0                	test   %eax,%eax
    7fc61f999dbf:	0f 85 0c 00 00 00    	jne    0x7fc61f999dd1
    7fc61f999dc5:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fc61f999dcb:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7fc61f999dd1:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fc61f999dd7:	ff c0                	inc    %eax
    7fc61f999dd9:	83 e0 3f             	and    $0x3f,%eax
    7fc61f999ddc:	89 85 60 fb ff ff    	mov    %eax,-0x4a0(%rbp)
    7fc61f999de2:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fc61f999de8:	41 23 c6             	and    %r14d,%eax
    7fc61f999deb:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fc61f999df1:	8b c3                	mov    %ebx,%eax
    7fc61f999df3:	c1 e8 02             	shr    $0x2,%eax
    7fc61f999df6:	83 e0 01             	and    $0x1,%eax
    7fc61f999df9:	85 c0                	test   %eax,%eax
    7fc61f999dfb:	0f 94 c0             	sete   %al
    7fc61f999dfe:	0f b6 c0             	movzbl %al,%eax
    7fc61f999e01:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7fc61f999e08:	48 8b 49 08          	mov    0x8(%rcx),%rcx
    7fc61f999e0c:	8b 09                	mov    (%rcx),%ecx
    7fc61f999e0e:	23 c1                	and    %ecx,%eax
    7fc61f999e10:	8b 8d 30 fe ff ff    	mov    -0x1d0(%rbp),%ecx
    7fc61f999e16:	23 8d 28 fe ff ff    	and    -0x1d8(%rbp),%ecx
    7fc61f999e1c:	85 c9                	test   %ecx,%ecx
    7fc61f999e1e:	0f 94 c2             	sete   %dl
    7fc61f999e21:	0f b6 d2             	movzbl %dl,%edx
    7fc61f999e24:	23 d0                	and    %eax,%edx
    7fc61f999e26:	8b f3                	mov    %ebx,%esi
    7fc61f999e28:	83 e6 03             	and    $0x3,%esi
    7fc61f999e2b:	d1 e6                	shl    %esi
    7fc61f999e2d:	89 b5 50 fb ff ff    	mov    %esi,-0x4b0(%rbp)
    7fc61f999e33:	89 85 48 fb ff ff    	mov    %eax,-0x4b8(%rbp)
    7fc61f999e39:	85 c0                	test   %eax,%eax
    7fc61f999e3b:	0f 94 c0             	sete   %al
    7fc61f999e3e:	0f b6 c0             	movzbl %al,%eax
    7fc61f999e41:	89 8d 40 fb ff ff    	mov    %ecx,-0x4c0(%rbp)
    7fc61f999e47:	23 c8                	and    %eax,%ecx
    7fc61f999e49:	89 8d 38 fb ff ff    	mov    %ecx,-0x4c8(%rbp)
    7fc61f999e4f:	8b c3                	mov    %ebx,%eax
    7fc61f999e51:	d1 e8                	shr    %eax
    7fc61f999e53:	83 e0 03             	and    $0x3,%eax
    7fc61f999e56:	89 85 30 fb ff ff    	mov    %eax,-0x4d0(%rbp)
    7fc61f999e5c:	85 d2                	test   %edx,%edx
    7fc61f999e5e:	0f 85 1b 00 00 00    	jne    0x7fc61f999e7f
    7fc61f999e64:	8b 85 38 fb ff ff    	mov    -0x4c8(%rbp),%eax
    7fc61f999e6a:	85 c0                	test   %eax,%eax
    7fc61f999e6c:	0f 85 1e 00 00 00    	jne    0x7fc61f999e90
    7fc61f999e72:	8b c3                	mov    %ebx,%eax
    7fc61f999e74:	89 85 28 fb ff ff    	mov    %eax,-0x4d8(%rbp)
    7fc61f999e7a:	e9 1d 00 00 00       	jmpq   0x7fc61f999e9c
    7fc61f999e7f:	8b 85 50 fb ff ff    	mov    -0x4b0(%rbp),%eax
    7fc61f999e85:	89 85 28 fb ff ff    	mov    %eax,-0x4d8(%rbp)
    7fc61f999e8b:	e9 0c 00 00 00       	jmpq   0x7fc61f999e9c
    7fc61f999e90:	8b 85 30 fb ff ff    	mov    -0x4d0(%rbp),%eax
    7fc61f999e96:	89 85 28 fb ff ff    	mov    %eax,-0x4d8(%rbp)
    7fc61f999e9c:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fc61f999ea2:	f7 d0                	not    %eax
    7fc61f999ea4:	83 e0 01             	and    $0x1,%eax
    7fc61f999ea7:	8b cb                	mov    %ebx,%ecx
    7fc61f999ea9:	d1 e9                	shr    %ecx
    7fc61f999eab:	83 e1 01             	and    $0x1,%ecx
    7fc61f999eae:	89 8d 20 fb ff ff    	mov    %ecx,-0x4e0(%rbp)
    7fc61f999eb4:	0b c1                	or     %ecx,%eax
    7fc61f999eb6:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7fc61f999ebd:	48 8b 09             	mov    (%rcx),%rcx
    7fc61f999ec0:	8b 09                	mov    (%rcx),%ecx
    7fc61f999ec2:	89 8d 18 fb ff ff    	mov    %ecx,-0x4e8(%rbp)
    7fc61f999ec8:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7fc61f999ece:	85 c0                	test   %eax,%eax
    7fc61f999ed0:	0f 85 0c 00 00 00    	jne    0x7fc61f999ee2
    7fc61f999ed6:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fc61f999edc:	89 85 10 fb ff ff    	mov    %eax,-0x4f0(%rbp)
    7fc61f999ee2:	8b c3                	mov    %ebx,%eax
    7fc61f999ee4:	83 e0 01             	and    $0x1,%eax
    7fc61f999ee7:	8b 8d 48 fb ff ff    	mov    -0x4b8(%rbp),%ecx
    7fc61f999eed:	23 c1                	and    %ecx,%eax
    7fc61f999eef:	8b 95 40 fb ff ff    	mov    -0x4c0(%rbp),%edx
    7fc61f999ef5:	0b c2                	or     %edx,%eax
    7fc61f999ef7:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7fc61f999efd:	23 8d 20 fb ff ff    	and    -0x4e0(%rbp),%ecx
    7fc61f999f03:	0b d1                	or     %ecx,%edx
    7fc61f999f05:	89 95 00 fb ff ff    	mov    %edx,-0x500(%rbp)
    7fc61f999f0b:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fc61f999f11:	23 85 38 fe ff ff    	and    -0x1c8(%rbp),%eax
    7fc61f999f17:	8b 8d 68 fe ff ff    	mov    -0x198(%rbp),%ecx
    7fc61f999f1d:	83 e1 01             	and    $0x1,%ecx
    7fc61f999f20:	85 c9                	test   %ecx,%ecx
    7fc61f999f22:	0f 94 c1             	sete   %cl
    7fc61f999f25:	0f b6 c9             	movzbl %cl,%ecx
    7fc61f999f28:	48 8b 95 50 fe ff ff 	mov    -0x1b0(%rbp),%rdx
    7fc61f999f2f:	48 8b 52 10          	mov    0x10(%rdx),%rdx
    7fc61f999f33:	8b 12                	mov    (%rdx),%edx
    7fc61f999f35:	23 ca                	and    %edx,%ecx
    7fc61f999f37:	85 c9                	test   %ecx,%ecx
    7fc61f999f39:	0f 94 c2             	sete   %dl
    7fc61f999f3c:	0f b6 d2             	movzbl %dl,%edx
    7fc61f999f3f:	23 d0                	and    %eax,%edx
    7fc61f999f41:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7fc61f999f47:	83 e6 03             	and    $0x3,%esi
    7fc61f999f4a:	d1 e6                	shl    %esi
    7fc61f999f4c:	89 b5 f8 fa ff ff    	mov    %esi,-0x508(%rbp)
    7fc61f999f52:	89 85 f0 fa ff ff    	mov    %eax,-0x510(%rbp)
    7fc61f999f58:	85 c0                	test   %eax,%eax
    7fc61f999f5a:	0f 94 c0             	sete   %al
    7fc61f999f5d:	0f b6 c0             	movzbl %al,%eax
    7fc61f999f60:	89 8d e8 fa ff ff    	mov    %ecx,-0x518(%rbp)
    7fc61f999f66:	23 c8                	and    %eax,%ecx
    7fc61f999f68:	89 8d e0 fa ff ff    	mov    %ecx,-0x520(%rbp)
    7fc61f999f6e:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fc61f999f74:	d1 e8                	shr    %eax
    7fc61f999f76:	83 e0 03             	and    $0x3,%eax
    7fc61f999f79:	89 85 d8 fa ff ff    	mov    %eax,-0x528(%rbp)
    7fc61f999f7f:	85 d2                	test   %edx,%edx
    7fc61f999f81:	0f 85 1f 00 00 00    	jne    0x7fc61f999fa6
    7fc61f999f87:	8b 85 e0 fa ff ff    	mov    -0x520(%rbp),%eax
    7fc61f999f8d:	85 c0                	test   %eax,%eax
    7fc61f999f8f:	0f 85 22 00 00 00    	jne    0x7fc61f999fb7
    7fc61f999f95:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fc61f999f9b:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7fc61f999fa1:	e9 1d 00 00 00       	jmpq   0x7fc61f999fc3
    7fc61f999fa6:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7fc61f999fac:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7fc61f999fb2:	e9 0c 00 00 00       	jmpq   0x7fc61f999fc3
    7fc61f999fb7:	8b 85 d8 fa ff ff    	mov    -0x528(%rbp),%eax
    7fc61f999fbd:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7fc61f999fc3:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7fc61f999fc9:	f7 d0                	not    %eax
    7fc61f999fcb:	83 e0 01             	and    $0x1,%eax
    7fc61f999fce:	8b 8d 68 fe ff ff    	mov    -0x198(%rbp),%ecx
    7fc61f999fd4:	d1 e9                	shr    %ecx
    7fc61f999fd6:	83 e1 01             	and    $0x1,%ecx
    7fc61f999fd9:	89 8d c8 fa ff ff    	mov    %ecx,-0x538(%rbp)
    7fc61f999fdf:	0b c1                	or     %ecx,%eax
    7fc61f999fe1:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fc61f999fe7:	89 8d c0 fa ff ff    	mov    %ecx,-0x540(%rbp)
    7fc61f999fed:	85 c0                	test   %eax,%eax
    7fc61f999fef:	0f 85 0c 00 00 00    	jne    0x7fc61f99a001
    7fc61f999ff5:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fc61f999ffb:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fc61f99a001:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fc61f99a007:	83 e0 01             	and    $0x1,%eax
    7fc61f99a00a:	8b 8d f0 fa ff ff    	mov    -0x510(%rbp),%ecx
    7fc61f99a010:	23 c1                	and    %ecx,%eax
    7fc61f99a012:	8b 95 e8 fa ff ff    	mov    -0x518(%rbp),%edx
    7fc61f99a018:	0b c2                	or     %edx,%eax
    7fc61f99a01a:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7fc61f99a020:	23 8d c8 fa ff ff    	and    -0x538(%rbp),%ecx
    7fc61f99a026:	0b d1                	or     %ecx,%edx
    7fc61f99a028:	85 d2                	test   %edx,%edx
    7fc61f99a02a:	0f 84 13 00 00 00    	je     0x7fc61f99a043
    7fc61f99a030:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fc61f99a036:	41 89 87 50 04 00 00 	mov    %eax,0x450(%r15)
    7fc61f99a03d:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7fc61f99a043:	8b 85 b8 fa ff ff    	mov    -0x548(%rbp),%eax
    7fc61f99a049:	85 c0                	test   %eax,%eax
    7fc61f99a04b:	0f 84 13 00 00 00    	je     0x7fc61f99a064
    7fc61f99a051:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fc61f99a057:	41 89 87 48 04 00 00 	mov    %eax,0x448(%r15)
    7fc61f99a05e:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fc61f99a064:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a067:	0f 84 1a 00 00 00    	je     0x7fc61f99a087
    7fc61f99a06d:	41 c7 87 40 04 00 00 	movl   $0x1,0x440(%r15)
    7fc61f99a074:	01 00 00 00 
    7fc61f99a078:	c7 85 68 fe ff ff 01 	movl   $0x1,-0x198(%rbp)
    7fc61f99a07f:	00 00 00 
    7fc61f99a082:	e9 13 00 00 00       	jmpq   0x7fc61f99a09a
    7fc61f99a087:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7fc61f99a08d:	41 89 87 40 04 00 00 	mov    %eax,0x440(%r15)
    7fc61f99a094:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7fc61f99a09a:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fc61f99a0a0:	85 c0                	test   %eax,%eax
    7fc61f99a0a2:	0f 84 13 00 00 00    	je     0x7fc61f99a0bb
    7fc61f99a0a8:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fc61f99a0ae:	41 89 87 38 04 00 00 	mov    %eax,0x438(%r15)
    7fc61f99a0b5:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fc61f99a0bb:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fc61f99a0c1:	85 c0                	test   %eax,%eax
    7fc61f99a0c3:	0f 84 13 00 00 00    	je     0x7fc61f99a0dc
    7fc61f99a0c9:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fc61f99a0cf:	41 89 87 30 04 00 00 	mov    %eax,0x430(%r15)
    7fc61f99a0d6:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fc61f99a0dc:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a0df:	0f 84 15 00 00 00    	je     0x7fc61f99a0fa
    7fc61f99a0e5:	41 c7 87 28 04 00 00 	movl   $0x1,0x428(%r15)
    7fc61f99a0ec:	01 00 00 00 
    7fc61f99a0f0:	bb 01 00 00 00       	mov    $0x1,%ebx
    7fc61f99a0f5:	e9 10 00 00 00       	jmpq   0x7fc61f99a10a
    7fc61f99a0fa:	8b 85 28 fb ff ff    	mov    -0x4d8(%rbp),%eax
    7fc61f99a100:	41 89 87 28 04 00 00 	mov    %eax,0x428(%r15)
    7fc61f99a107:	48 8b d8             	mov    %rax,%rbx
    7fc61f99a10a:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a10d:	0f 84 1a 00 00 00    	je     0x7fc61f99a12d
    7fc61f99a113:	41 c7 87 20 04 00 00 	movl   $0x0,0x420(%r15)
    7fc61f99a11a:	00 00 00 00 
    7fc61f99a11e:	c7 85 80 fe ff ff 00 	movl   $0x0,-0x180(%rbp)
    7fc61f99a125:	00 00 00 
    7fc61f99a128:	e9 21 00 00 00       	jmpq   0x7fc61f99a14e
    7fc61f99a12d:	8b 85 58 fb ff ff    	mov    -0x4a8(%rbp),%eax
    7fc61f99a133:	85 c0                	test   %eax,%eax
    7fc61f99a135:	0f 84 13 00 00 00    	je     0x7fc61f99a14e
    7fc61f99a13b:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7fc61f99a141:	41 89 87 20 04 00 00 	mov    %eax,0x420(%r15)
    7fc61f99a148:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fc61f99a14e:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a151:	0f 84 25 00 00 00    	je     0x7fc61f99a17c
    7fc61f99a157:	41 c7 87 10 04 00 00 	movl   $0x0,0x410(%r15)
    7fc61f99a15e:	00 00 00 00 
    7fc61f99a162:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%rbp)
    7fc61f99a169:	00 00 00 
    7fc61f99a16c:	41 c7 87 18 04 00 00 	movl   $0x0,0x418(%r15)
    7fc61f99a173:	00 00 00 00 
    7fc61f99a177:	e9 2a 00 00 00       	jmpq   0x7fc61f99a1a6
    7fc61f99a17c:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a17f:	0f 84 21 00 00 00    	je     0x7fc61f99a1a6
    7fc61f99a185:	41 8b 87 18 04 00 00 	mov    0x418(%r15),%eax
    7fc61f99a18c:	41 89 87 10 04 00 00 	mov    %eax,0x410(%r15)
    7fc61f99a193:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fc61f99a199:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fc61f99a19f:	41 89 87 18 04 00 00 	mov    %eax,0x418(%r15)
    7fc61f99a1a6:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a1a9:	0f 84 26 00 00 00    	je     0x7fc61f99a1d5
    7fc61f99a1af:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7fc61f99a1b5:	41 89 87 08 04 00 00 	mov    %eax,0x408(%r15)
    7fc61f99a1bc:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fc61f99a1c2:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fc61f99a1c8:	41 89 87 00 04 00 00 	mov    %eax,0x400(%r15)
    7fc61f99a1cf:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fc61f99a1d5:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a1d8:	0f 84 1a 00 00 00    	je     0x7fc61f99a1f8
    7fc61f99a1de:	41 c7 87 f8 03 00 00 	movl   $0x0,0x3f8(%r15)
    7fc61f99a1e5:	00 00 00 00 
    7fc61f99a1e9:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7fc61f99a1f0:	00 00 00 
    7fc61f99a1f3:	e9 21 00 00 00       	jmpq   0x7fc61f99a219
    7fc61f99a1f8:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7fc61f99a1fe:	85 c0                	test   %eax,%eax
    7fc61f99a200:	0f 84 13 00 00 00    	je     0x7fc61f99a219
    7fc61f99a206:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7fc61f99a20c:	41 89 87 f8 03 00 00 	mov    %eax,0x3f8(%r15)
    7fc61f99a213:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fc61f99a219:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a21c:	0f 84 1a 00 00 00    	je     0x7fc61f99a23c
    7fc61f99a222:	41 c7 87 f0 03 00 00 	movl   $0x0,0x3f0(%r15)
    7fc61f99a229:	00 00 00 00 
    7fc61f99a22d:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7fc61f99a234:	00 00 00 
    7fc61f99a237:	e9 1c 00 00 00       	jmpq   0x7fc61f99a258
    7fc61f99a23c:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a23f:	0f 84 13 00 00 00    	je     0x7fc61f99a258
    7fc61f99a245:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fc61f99a24b:	41 89 87 f0 03 00 00 	mov    %eax,0x3f0(%r15)
    7fc61f99a252:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fc61f99a258:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a25b:	0f 84 26 00 00 00    	je     0x7fc61f99a287
    7fc61f99a261:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fc61f99a267:	41 89 87 e8 03 00 00 	mov    %eax,0x3e8(%r15)
    7fc61f99a26e:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fc61f99a274:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fc61f99a27a:	41 89 87 e0 03 00 00 	mov    %eax,0x3e0(%r15)
    7fc61f99a281:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fc61f99a287:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a28a:	0f 84 1a 00 00 00    	je     0x7fc61f99a2aa
    7fc61f99a290:	41 c7 87 d8 03 00 00 	movl   $0x0,0x3d8(%r15)
    7fc61f99a297:	00 00 00 00 
    7fc61f99a29b:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7fc61f99a2a2:	00 00 00 
    7fc61f99a2a5:	e9 21 00 00 00       	jmpq   0x7fc61f99a2cb
    7fc61f99a2aa:	8b 85 b0 fb ff ff    	mov    -0x450(%rbp),%eax
    7fc61f99a2b0:	85 c0                	test   %eax,%eax
    7fc61f99a2b2:	0f 84 13 00 00 00    	je     0x7fc61f99a2cb
    7fc61f99a2b8:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7fc61f99a2be:	41 89 87 d8 03 00 00 	mov    %eax,0x3d8(%r15)
    7fc61f99a2c5:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fc61f99a2cb:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a2ce:	0f 84 25 00 00 00    	je     0x7fc61f99a2f9
    7fc61f99a2d4:	41 c7 87 c8 03 00 00 	movl   $0x0,0x3c8(%r15)
    7fc61f99a2db:	00 00 00 00 
    7fc61f99a2df:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7fc61f99a2e6:	00 00 00 
    7fc61f99a2e9:	41 c7 87 d0 03 00 00 	movl   $0x0,0x3d0(%r15)
    7fc61f99a2f0:	00 00 00 00 
    7fc61f99a2f4:	e9 35 00 00 00       	jmpq   0x7fc61f99a32e
    7fc61f99a2f9:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a2fc:	0f 84 2c 00 00 00    	je     0x7fc61f99a32e
    7fc61f99a302:	41 8b 87 d0 03 00 00 	mov    0x3d0(%r15),%eax
    7fc61f99a309:	8b c8                	mov    %eax,%ecx
    7fc61f99a30b:	83 e1 01             	and    $0x1,%ecx
    7fc61f99a30e:	41 89 8f c8 03 00 00 	mov    %ecx,0x3c8(%r15)
    7fc61f99a315:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fc61f99a31b:	d1 e8                	shr    %eax
    7fc61f99a31d:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7fc61f99a323:	d1 e1                	shl    %ecx
    7fc61f99a325:	0b c1                	or     %ecx,%eax
    7fc61f99a327:	41 89 87 d0 03 00 00 	mov    %eax,0x3d0(%r15)
    7fc61f99a32e:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a331:	0f 84 34 00 00 00    	je     0x7fc61f99a36b
    7fc61f99a337:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fc61f99a33d:	41 89 87 c0 03 00 00 	mov    %eax,0x3c0(%r15)
    7fc61f99a344:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fc61f99a34a:	41 8b 87 b8 03 00 00 	mov    0x3b8(%r15),%eax
    7fc61f99a351:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7fc61f99a358:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fc61f99a35e:	8b 85 d0 fb ff ff    	mov    -0x430(%rbp),%eax
    7fc61f99a364:	41 89 87 b8 03 00 00 	mov    %eax,0x3b8(%r15)
    7fc61f99a36b:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a36e:	0f 84 1a 00 00 00    	je     0x7fc61f99a38e
    7fc61f99a374:	41 c7 87 a8 03 00 00 	movl   $0x0,0x3a8(%r15)
    7fc61f99a37b:	00 00 00 00 
    7fc61f99a37f:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7fc61f99a386:	00 00 00 
    7fc61f99a389:	e9 21 00 00 00       	jmpq   0x7fc61f99a3af
    7fc61f99a38e:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fc61f99a394:	85 c0                	test   %eax,%eax
    7fc61f99a396:	0f 84 13 00 00 00    	je     0x7fc61f99a3af
    7fc61f99a39c:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fc61f99a3a2:	41 89 87 a8 03 00 00 	mov    %eax,0x3a8(%r15)
    7fc61f99a3a9:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fc61f99a3af:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a3b2:	0f 84 25 00 00 00    	je     0x7fc61f99a3dd
    7fc61f99a3b8:	41 c7 87 98 03 00 00 	movl   $0x0,0x398(%r15)
    7fc61f99a3bf:	00 00 00 00 
    7fc61f99a3c3:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7fc61f99a3ca:	00 00 00 
    7fc61f99a3cd:	41 c7 87 a0 03 00 00 	movl   $0x0,0x3a0(%r15)
    7fc61f99a3d4:	00 00 00 00 
    7fc61f99a3d8:	e9 36 00 00 00       	jmpq   0x7fc61f99a413
    7fc61f99a3dd:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a3e0:	0f 84 2d 00 00 00    	je     0x7fc61f99a413
    7fc61f99a3e6:	41 8b 87 a0 03 00 00 	mov    0x3a0(%r15),%eax
    7fc61f99a3ed:	8b c8                	mov    %eax,%ecx
    7fc61f99a3ef:	83 e1 01             	and    $0x1,%ecx
    7fc61f99a3f2:	41 89 8f 98 03 00 00 	mov    %ecx,0x398(%r15)
    7fc61f99a3f9:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fc61f99a3ff:	d1 e8                	shr    %eax
    7fc61f99a401:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7fc61f99a407:	c1 e1 04             	shl    $0x4,%ecx
    7fc61f99a40a:	0b c1                	or     %ecx,%eax
    7fc61f99a40c:	41 89 87 a0 03 00 00 	mov    %eax,0x3a0(%r15)
    7fc61f99a413:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a416:	0f 84 67 00 00 00    	je     0x7fc61f99a483
    7fc61f99a41c:	41 8b 87 94 03 00 00 	mov    0x394(%r15),%eax
    7fc61f99a423:	49 8b cf             	mov    %r15,%rcx
    7fc61f99a426:	48 81 c1 84 03 00 00 	add    $0x384,%rcx
    7fc61f99a42d:	8b d0                	mov    %eax,%edx
    7fc61f99a42f:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fc61f99a432:	41 89 97 7c 03 00 00 	mov    %edx,0x37c(%r15)
    7fc61f99a439:	89 95 f0 fe ff ff    	mov    %edx,-0x110(%rbp)
    7fc61f99a43f:	8b d0                	mov    %eax,%edx
    7fc61f99a441:	8b b5 08 fc ff ff    	mov    -0x3f8(%rbp),%esi
    7fc61f99a447:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fc61f99a44a:	ff c8                	dec    %eax
    7fc61f99a44c:	b9 03 00 00 00       	mov    $0x3,%ecx
    7fc61f99a451:	3b c1                	cmp    %ecx,%eax
    7fc61f99a453:	0f 47 c1             	cmova  %ecx,%eax
    7fc61f99a456:	41 89 87 94 03 00 00 	mov    %eax,0x394(%r15)
    7fc61f99a45d:	8b 85 58 fc ff ff    	mov    -0x3a8(%rbp),%eax
    7fc61f99a463:	41 89 87 74 03 00 00 	mov    %eax,0x374(%r15)
    7fc61f99a46a:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fc61f99a470:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fc61f99a476:	41 89 87 6c 03 00 00 	mov    %eax,0x36c(%r15)
    7fc61f99a47d:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fc61f99a483:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a486:	0f 84 1a 00 00 00    	je     0x7fc61f99a4a6
    7fc61f99a48c:	41 c7 87 64 03 00 00 	movl   $0x0,0x364(%r15)
    7fc61f99a493:	00 00 00 00 
    7fc61f99a497:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7fc61f99a49e:	00 00 00 
    7fc61f99a4a1:	e9 21 00 00 00       	jmpq   0x7fc61f99a4c7
    7fc61f99a4a6:	8b 85 60 fc ff ff    	mov    -0x3a0(%rbp),%eax
    7fc61f99a4ac:	85 c0                	test   %eax,%eax
    7fc61f99a4ae:	0f 84 13 00 00 00    	je     0x7fc61f99a4c7
    7fc61f99a4b4:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7fc61f99a4ba:	41 89 87 64 03 00 00 	mov    %eax,0x364(%r15)
    7fc61f99a4c1:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fc61f99a4c7:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a4ca:	0f 84 25 00 00 00    	je     0x7fc61f99a4f5
    7fc61f99a4d0:	41 c7 87 54 03 00 00 	movl   $0x0,0x354(%r15)
    7fc61f99a4d7:	00 00 00 00 
    7fc61f99a4db:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7fc61f99a4e2:	00 00 00 
    7fc61f99a4e5:	41 c7 87 5c 03 00 00 	movl   $0x0,0x35c(%r15)
    7fc61f99a4ec:	00 00 00 00 
    7fc61f99a4f0:	e9 36 00 00 00       	jmpq   0x7fc61f99a52b
    7fc61f99a4f5:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a4f8:	0f 84 2d 00 00 00    	je     0x7fc61f99a52b
    7fc61f99a4fe:	41 8b 87 5c 03 00 00 	mov    0x35c(%r15),%eax
    7fc61f99a505:	8b c8                	mov    %eax,%ecx
    7fc61f99a507:	83 e1 01             	and    $0x1,%ecx
    7fc61f99a50a:	41 89 8f 54 03 00 00 	mov    %ecx,0x354(%r15)
    7fc61f99a511:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7fc61f99a517:	d1 e8                	shr    %eax
    7fc61f99a519:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7fc61f99a51f:	c1 e1 03             	shl    $0x3,%ecx
    7fc61f99a522:	0b c1                	or     %ecx,%eax
    7fc61f99a524:	41 89 87 5c 03 00 00 	mov    %eax,0x35c(%r15)
    7fc61f99a52b:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a52e:	0f 84 54 00 00 00    	je     0x7fc61f99a588
    7fc61f99a534:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7fc61f99a53a:	41 89 87 4c 03 00 00 	mov    %eax,0x34c(%r15)
    7fc61f99a541:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fc61f99a547:	41 8b 87 48 03 00 00 	mov    0x348(%r15),%eax
    7fc61f99a54e:	49 8b cf             	mov    %r15,%rcx
    7fc61f99a551:	48 81 c1 38 03 00 00 	add    $0x338,%rcx
    7fc61f99a558:	8b d0                	mov    %eax,%edx
    7fc61f99a55a:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fc61f99a55d:	41 89 97 30 03 00 00 	mov    %edx,0x330(%r15)
    7fc61f99a564:	89 95 20 ff ff ff    	mov    %edx,-0xe0(%rbp)
    7fc61f99a56a:	8b d0                	mov    %eax,%edx
    7fc61f99a56c:	8b b5 80 fc ff ff    	mov    -0x380(%rbp),%esi
    7fc61f99a572:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fc61f99a575:	ff c8                	dec    %eax
    7fc61f99a577:	b9 02 00 00 00       	mov    $0x2,%ecx
    7fc61f99a57c:	3b c1                	cmp    %ecx,%eax
    7fc61f99a57e:	0f 47 c1             	cmova  %ecx,%eax
    7fc61f99a581:	41 89 87 48 03 00 00 	mov    %eax,0x348(%r15)
    7fc61f99a588:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a58b:	0f 84 1a 00 00 00    	je     0x7fc61f99a5ab
    7fc61f99a591:	41 c7 87 28 03 00 00 	movl   $0x0,0x328(%r15)
    7fc61f99a598:	00 00 00 00 
    7fc61f99a59c:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7fc61f99a5a3:	00 00 00 
    7fc61f99a5a6:	e9 21 00 00 00       	jmpq   0x7fc61f99a5cc
    7fc61f99a5ab:	8b 85 a8 fc ff ff    	mov    -0x358(%rbp),%eax
    7fc61f99a5b1:	85 c0                	test   %eax,%eax
    7fc61f99a5b3:	0f 84 13 00 00 00    	je     0x7fc61f99a5cc
    7fc61f99a5b9:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7fc61f99a5bf:	41 89 87 28 03 00 00 	mov    %eax,0x328(%r15)
    7fc61f99a5c6:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fc61f99a5cc:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a5cf:	0f 84 1a 00 00 00    	je     0x7fc61f99a5ef
    7fc61f99a5d5:	41 c7 87 20 03 00 00 	movl   $0x0,0x320(%r15)
    7fc61f99a5dc:	00 00 00 00 
    7fc61f99a5e0:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7fc61f99a5e7:	00 00 00 
    7fc61f99a5ea:	e9 1c 00 00 00       	jmpq   0x7fc61f99a60b
    7fc61f99a5ef:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a5f2:	0f 84 13 00 00 00    	je     0x7fc61f99a60b
    7fc61f99a5f8:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fc61f99a5fe:	41 89 87 20 03 00 00 	mov    %eax,0x320(%r15)
    7fc61f99a605:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fc61f99a60b:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a60e:	0f 84 26 00 00 00    	je     0x7fc61f99a63a
    7fc61f99a614:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fc61f99a61a:	41 89 87 18 03 00 00 	mov    %eax,0x318(%r15)
    7fc61f99a621:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fc61f99a627:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7fc61f99a62d:	41 89 87 10 03 00 00 	mov    %eax,0x310(%r15)
    7fc61f99a634:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fc61f99a63a:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a63d:	0f 84 1a 00 00 00    	je     0x7fc61f99a65d
    7fc61f99a643:	41 c7 87 08 03 00 00 	movl   $0x0,0x308(%r15)
    7fc61f99a64a:	00 00 00 00 
    7fc61f99a64e:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7fc61f99a655:	00 00 00 
    7fc61f99a658:	e9 21 00 00 00       	jmpq   0x7fc61f99a67e
    7fc61f99a65d:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fc61f99a663:	85 c0                	test   %eax,%eax
    7fc61f99a665:	0f 84 13 00 00 00    	je     0x7fc61f99a67e
    7fc61f99a66b:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7fc61f99a671:	41 89 87 08 03 00 00 	mov    %eax,0x308(%r15)
    7fc61f99a678:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fc61f99a67e:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a681:	0f 84 25 00 00 00    	je     0x7fc61f99a6ac
    7fc61f99a687:	41 c7 87 f8 02 00 00 	movl   $0x0,0x2f8(%r15)
    7fc61f99a68e:	00 00 00 00 
    7fc61f99a692:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7fc61f99a699:	00 00 00 
    7fc61f99a69c:	41 c7 87 00 03 00 00 	movl   $0x0,0x300(%r15)
    7fc61f99a6a3:	00 00 00 00 
    7fc61f99a6a7:	e9 36 00 00 00       	jmpq   0x7fc61f99a6e2
    7fc61f99a6ac:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a6af:	0f 84 2d 00 00 00    	je     0x7fc61f99a6e2
    7fc61f99a6b5:	41 8b 87 00 03 00 00 	mov    0x300(%r15),%eax
    7fc61f99a6bc:	8b c8                	mov    %eax,%ecx
    7fc61f99a6be:	83 e1 01             	and    $0x1,%ecx
    7fc61f99a6c1:	41 89 8f f8 02 00 00 	mov    %ecx,0x2f8(%r15)
    7fc61f99a6c8:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7fc61f99a6ce:	d1 e8                	shr    %eax
    7fc61f99a6d0:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7fc61f99a6d6:	c1 e1 07             	shl    $0x7,%ecx
    7fc61f99a6d9:	0b c1                	or     %ecx,%eax
    7fc61f99a6db:	41 89 87 00 03 00 00 	mov    %eax,0x300(%r15)
    7fc61f99a6e2:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a6e5:	0f 84 54 00 00 00    	je     0x7fc61f99a73f
    7fc61f99a6eb:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7fc61f99a6f1:	41 89 87 f0 02 00 00 	mov    %eax,0x2f0(%r15)
    7fc61f99a6f8:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fc61f99a6fe:	41 8b 87 ec 02 00 00 	mov    0x2ec(%r15),%eax
    7fc61f99a705:	49 8b cf             	mov    %r15,%rcx
    7fc61f99a708:	48 81 c1 cc 02 00 00 	add    $0x2cc,%rcx
    7fc61f99a70f:	8b d0                	mov    %eax,%edx
    7fc61f99a711:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fc61f99a714:	41 89 97 c4 02 00 00 	mov    %edx,0x2c4(%r15)
    7fc61f99a71b:	89 95 60 ff ff ff    	mov    %edx,-0xa0(%rbp)
    7fc61f99a721:	8b d0                	mov    %eax,%edx
    7fc61f99a723:	8b b5 e0 fc ff ff    	mov    -0x320(%rbp),%esi
    7fc61f99a729:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fc61f99a72c:	ff c8                	dec    %eax
    7fc61f99a72e:	b9 06 00 00 00       	mov    $0x6,%ecx
    7fc61f99a733:	3b c1                	cmp    %ecx,%eax
    7fc61f99a735:	0f 47 c1             	cmova  %ecx,%eax
    7fc61f99a738:	41 89 87 ec 02 00 00 	mov    %eax,0x2ec(%r15)
    7fc61f99a73f:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a742:	0f 84 1a 00 00 00    	je     0x7fc61f99a762
    7fc61f99a748:	41 c7 87 bc 02 00 00 	movl   $0x0,0x2bc(%r15)
    7fc61f99a74f:	00 00 00 00 
    7fc61f99a753:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7fc61f99a75a:	00 00 00 
    7fc61f99a75d:	e9 21 00 00 00       	jmpq   0x7fc61f99a783
    7fc61f99a762:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fc61f99a768:	85 c0                	test   %eax,%eax
    7fc61f99a76a:	0f 84 13 00 00 00    	je     0x7fc61f99a783
    7fc61f99a770:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fc61f99a776:	41 89 87 bc 02 00 00 	mov    %eax,0x2bc(%r15)
    7fc61f99a77d:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fc61f99a783:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a786:	0f 84 25 00 00 00    	je     0x7fc61f99a7b1
    7fc61f99a78c:	41 c7 87 ac 02 00 00 	movl   $0x0,0x2ac(%r15)
    7fc61f99a793:	00 00 00 00 
    7fc61f99a797:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7fc61f99a79e:	00 00 00 
    7fc61f99a7a1:	41 c7 87 b4 02 00 00 	movl   $0x0,0x2b4(%r15)
    7fc61f99a7a8:	00 00 00 00 
    7fc61f99a7ac:	e9 33 00 00 00       	jmpq   0x7fc61f99a7e4
    7fc61f99a7b1:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a7b4:	0f 84 2a 00 00 00    	je     0x7fc61f99a7e4
    7fc61f99a7ba:	41 8b 87 b4 02 00 00 	mov    0x2b4(%r15),%eax
    7fc61f99a7c1:	8b c8                	mov    %eax,%ecx
    7fc61f99a7c3:	83 e1 01             	and    $0x1,%ecx
    7fc61f99a7c6:	41 89 8f ac 02 00 00 	mov    %ecx,0x2ac(%r15)
    7fc61f99a7cd:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7fc61f99a7d3:	d1 e8                	shr    %eax
    7fc61f99a7d5:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7fc61f99a7d8:	c1 e1 04             	shl    $0x4,%ecx
    7fc61f99a7db:	0b c1                	or     %ecx,%eax
    7fc61f99a7dd:	41 89 87 b4 02 00 00 	mov    %eax,0x2b4(%r15)
    7fc61f99a7e4:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a7e7:	0f 84 5e 00 00 00    	je     0x7fc61f99a84b
    7fc61f99a7ed:	41 8b 87 a8 02 00 00 	mov    0x2a8(%r15),%eax
    7fc61f99a7f4:	49 8b cf             	mov    %r15,%rcx
    7fc61f99a7f7:	48 81 c1 98 02 00 00 	add    $0x298,%rcx
    7fc61f99a7fe:	8b d0                	mov    %eax,%edx
    7fc61f99a800:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fc61f99a803:	41 89 97 90 02 00 00 	mov    %edx,0x290(%r15)
    7fc61f99a80a:	89 95 78 ff ff ff    	mov    %edx,-0x88(%rbp)
    7fc61f99a810:	8b d0                	mov    %eax,%edx
    7fc61f99a812:	8b b5 18 fd ff ff    	mov    -0x2e8(%rbp),%esi
    7fc61f99a818:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fc61f99a81b:	ff c8                	dec    %eax
    7fc61f99a81d:	b9 03 00 00 00       	mov    $0x3,%ecx
    7fc61f99a822:	3b c1                	cmp    %ecx,%eax
    7fc61f99a824:	0f 47 c1             	cmova  %ecx,%eax
    7fc61f99a827:	41 89 87 a8 02 00 00 	mov    %eax,0x2a8(%r15)
    7fc61f99a82e:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7fc61f99a834:	41 89 87 88 02 00 00 	mov    %eax,0x288(%r15)
    7fc61f99a83b:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fc61f99a83e:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fc61f99a841:	41 89 87 80 02 00 00 	mov    %eax,0x280(%r15)
    7fc61f99a848:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fc61f99a84b:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a84e:	0f 84 17 00 00 00    	je     0x7fc61f99a86b
    7fc61f99a854:	41 c7 87 78 02 00 00 	movl   $0x0,0x278(%r15)
    7fc61f99a85b:	00 00 00 00 
    7fc61f99a85f:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7fc61f99a866:	e9 1e 00 00 00       	jmpq   0x7fc61f99a889
    7fc61f99a86b:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fc61f99a871:	85 c0                	test   %eax,%eax
    7fc61f99a873:	0f 84 10 00 00 00    	je     0x7fc61f99a889
    7fc61f99a879:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fc61f99a87f:	41 89 87 78 02 00 00 	mov    %eax,0x278(%r15)
    7fc61f99a886:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fc61f99a889:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a88c:	0f 84 22 00 00 00    	je     0x7fc61f99a8b4
    7fc61f99a892:	41 c7 87 68 02 00 00 	movl   $0x0,0x268(%r15)
    7fc61f99a899:	00 00 00 00 
    7fc61f99a89d:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fc61f99a8a4:	41 c7 87 70 02 00 00 	movl   $0x0,0x270(%r15)
    7fc61f99a8ab:	00 00 00 00 
    7fc61f99a8af:	e9 30 00 00 00       	jmpq   0x7fc61f99a8e4
    7fc61f99a8b4:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a8b7:	0f 84 27 00 00 00    	je     0x7fc61f99a8e4
    7fc61f99a8bd:	41 8b 87 70 02 00 00 	mov    0x270(%r15),%eax
    7fc61f99a8c4:	8b c8                	mov    %eax,%ecx
    7fc61f99a8c6:	83 e1 01             	and    $0x1,%ecx
    7fc61f99a8c9:	41 89 8f 68 02 00 00 	mov    %ecx,0x268(%r15)
    7fc61f99a8d0:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7fc61f99a8d3:	d1 e8                	shr    %eax
    7fc61f99a8d5:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fc61f99a8d8:	c1 e1 0f             	shl    $0xf,%ecx
    7fc61f99a8db:	0b c1                	or     %ecx,%eax
    7fc61f99a8dd:	41 89 87 70 02 00 00 	mov    %eax,0x270(%r15)
    7fc61f99a8e4:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a8e7:	0f 84 4e 00 00 00    	je     0x7fc61f99a93b
    7fc61f99a8ed:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fc61f99a8f3:	41 89 87 60 02 00 00 	mov    %eax,0x260(%r15)
    7fc61f99a8fa:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fc61f99a8fd:	41 8b 87 5c 02 00 00 	mov    0x25c(%r15),%eax
    7fc61f99a904:	49 8b cf             	mov    %r15,%rcx
    7fc61f99a907:	48 81 c1 1c 02 00 00 	add    $0x21c,%rcx
    7fc61f99a90e:	8b d0                	mov    %eax,%edx
    7fc61f99a910:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fc61f99a913:	41 89 97 14 02 00 00 	mov    %edx,0x214(%r15)
    7fc61f99a91a:	89 55 a8             	mov    %edx,-0x58(%rbp)
    7fc61f99a91d:	8b d0                	mov    %eax,%edx
    7fc61f99a91f:	8b b5 90 fd ff ff    	mov    -0x270(%rbp),%esi
    7fc61f99a925:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fc61f99a928:	ff c8                	dec    %eax
    7fc61f99a92a:	b9 0e 00 00 00       	mov    $0xe,%ecx
    7fc61f99a92f:	3b c1                	cmp    %ecx,%eax
    7fc61f99a931:	0f 47 c1             	cmova  %ecx,%eax
    7fc61f99a934:	41 89 87 5c 02 00 00 	mov    %eax,0x25c(%r15)
    7fc61f99a93b:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a93e:	0f 84 17 00 00 00    	je     0x7fc61f99a95b
    7fc61f99a944:	41 c7 87 0c 02 00 00 	movl   $0x0,0x20c(%r15)
    7fc61f99a94b:	00 00 00 00 
    7fc61f99a94f:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7fc61f99a956:	e9 1e 00 00 00       	jmpq   0x7fc61f99a979
    7fc61f99a95b:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7fc61f99a961:	85 c0                	test   %eax,%eax
    7fc61f99a963:	0f 84 10 00 00 00    	je     0x7fc61f99a979
    7fc61f99a969:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fc61f99a96f:	41 89 87 0c 02 00 00 	mov    %eax,0x20c(%r15)
    7fc61f99a976:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fc61f99a979:	45 85 ed             	test   %r13d,%r13d
    7fc61f99a97c:	0f 84 17 00 00 00    	je     0x7fc61f99a999
    7fc61f99a982:	41 c7 87 04 02 00 00 	movl   $0x0,0x204(%r15)
    7fc61f99a989:	00 00 00 00 
    7fc61f99a98d:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7fc61f99a994:	e9 16 00 00 00       	jmpq   0x7fc61f99a9af
    7fc61f99a999:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a99c:	0f 84 0d 00 00 00    	je     0x7fc61f99a9af
    7fc61f99a9a2:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fc61f99a9a5:	41 89 87 04 02 00 00 	mov    %eax,0x204(%r15)
    7fc61f99a9ac:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fc61f99a9af:	45 85 f6             	test   %r14d,%r14d
    7fc61f99a9b2:	0f 84 1d 00 00 00    	je     0x7fc61f99a9d5
    7fc61f99a9b8:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fc61f99a9bb:	41 89 87 fc 01 00 00 	mov    %eax,0x1fc(%r15)
    7fc61f99a9c2:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fc61f99a9c5:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7fc61f99a9cb:	41 89 87 f4 01 00 00 	mov    %eax,0x1f4(%r15)
    7fc61f99a9d2:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fc61f99a9d5:	45 85 e4             	test   %r12d,%r12d
    7fc61f99a9d8:	0f 84 17 00 00 00    	je     0x7fc61f99a9f5
    7fc61f99a9de:	41 c7 87 ec 01 00 00 	movl   $0x0,0x1ec(%r15)
    7fc61f99a9e5:	00 00 00 00 
    7fc61f99a9e9:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7fc61f99a9f0:	e9 1e 00 00 00       	jmpq   0x7fc61f99aa13
    7fc61f99a9f5:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7fc61f99a9fb:	85 c0                	test   %eax,%eax
    7fc61f99a9fd:	0f 84 10 00 00 00    	je     0x7fc61f99aa13
    7fc61f99aa03:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fc61f99aa09:	41 89 87 ec 01 00 00 	mov    %eax,0x1ec(%r15)
    7fc61f99aa10:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fc61f99aa13:	45 85 ed             	test   %r13d,%r13d
    7fc61f99aa16:	0f 84 22 00 00 00    	je     0x7fc61f99aa3e
    7fc61f99aa1c:	41 c7 87 dc 01 00 00 	movl   $0x0,0x1dc(%r15)
    7fc61f99aa23:	00 00 00 00 
    7fc61f99aa27:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7fc61f99aa2e:	41 c7 87 e4 01 00 00 	movl   $0x0,0x1e4(%r15)
    7fc61f99aa35:	00 00 00 00 
    7fc61f99aa39:	e9 33 00 00 00       	jmpq   0x7fc61f99aa71
    7fc61f99aa3e:	45 85 f6             	test   %r14d,%r14d
    7fc61f99aa41:	0f 84 2a 00 00 00    	je     0x7fc61f99aa71
    7fc61f99aa47:	41 8b 87 e4 01 00 00 	mov    0x1e4(%r15),%eax
    7fc61f99aa4e:	8b c8                	mov    %eax,%ecx
    7fc61f99aa50:	83 e1 01             	and    $0x1,%ecx
    7fc61f99aa53:	41 89 8f dc 01 00 00 	mov    %ecx,0x1dc(%r15)
    7fc61f99aa5a:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7fc61f99aa5d:	d1 e8                	shr    %eax
    7fc61f99aa5f:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7fc61f99aa65:	c1 e1 1f             	shl    $0x1f,%ecx
    7fc61f99aa68:	0b c1                	or     %ecx,%eax
    7fc61f99aa6a:	41 89 87 e4 01 00 00 	mov    %eax,0x1e4(%r15)
    7fc61f99aa71:	45 85 f6             	test   %r14d,%r14d
    7fc61f99aa74:	0f 84 4e 00 00 00    	je     0x7fc61f99aac8
    7fc61f99aa7a:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7fc61f99aa80:	41 89 87 d4 01 00 00 	mov    %eax,0x1d4(%r15)
    7fc61f99aa87:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fc61f99aa8a:	41 8b 87 d0 01 00 00 	mov    0x1d0(%r15),%eax
    7fc61f99aa91:	49 8b cf             	mov    %r15,%rcx
    7fc61f99aa94:	48 81 c1 50 01 00 00 	add    $0x150,%rcx
    7fc61f99aa9b:	8b d0                	mov    %eax,%edx
    7fc61f99aa9d:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fc61f99aaa0:	41 89 97 48 01 00 00 	mov    %edx,0x148(%r15)
    7fc61f99aaa7:	89 55 e8             	mov    %edx,-0x18(%rbp)
    7fc61f99aaaa:	8b d0                	mov    %eax,%edx
    7fc61f99aaac:	8b b5 f0 fd ff ff    	mov    -0x210(%rbp),%esi
    7fc61f99aab2:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fc61f99aab5:	ff c8                	dec    %eax
    7fc61f99aab7:	b9 1e 00 00 00       	mov    $0x1e,%ecx
    7fc61f99aabc:	3b c1                	cmp    %ecx,%eax
    7fc61f99aabe:	0f 47 c1             	cmova  %ecx,%eax
    7fc61f99aac1:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7fc61f99aac8:	45 85 e4             	test   %r12d,%r12d
    7fc61f99aacb:	0f 84 17 00 00 00    	je     0x7fc61f99aae8
    7fc61f99aad1:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7fc61f99aad8:	00 00 00 00 
    7fc61f99aadc:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7fc61f99aae3:	e9 1e 00 00 00       	jmpq   0x7fc61f99ab06
    7fc61f99aae8:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fc61f99aaee:	85 c0                	test   %eax,%eax
    7fc61f99aaf0:	0f 84 10 00 00 00    	je     0x7fc61f99ab06
    7fc61f99aaf6:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7fc61f99aafc:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7fc61f99ab03:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fc61f99ab06:	8b c3                	mov    %ebx,%eax
    7fc61f99ab08:	c1 e8 02             	shr    $0x2,%eax
    7fc61f99ab0b:	83 e0 01             	and    $0x1,%eax
    7fc61f99ab0e:	85 c0                	test   %eax,%eax
    7fc61f99ab10:	0f 94 c0             	sete   %al
    7fc61f99ab13:	0f b6 c0             	movzbl %al,%eax
    7fc61f99ab16:	48 8b 95 50 fe ff ff 	mov    -0x1b0(%rbp),%rdx
    7fc61f99ab1d:	48 8b 4a 28          	mov    0x28(%rdx),%rcx
    7fc61f99ab21:	89 01                	mov    %eax,(%rcx)
    7fc61f99ab23:	48 8b 42 30          	mov    0x30(%rdx),%rax
    7fc61f99ab27:	8b 8d 60 fe ff ff    	mov    -0x1a0(%rbp),%ecx
    7fc61f99ab2d:	89 08                	mov    %ecx,(%rax)
    7fc61f99ab2f:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fc61f99ab35:	83 e0 01             	and    $0x1,%eax
    7fc61f99ab38:	85 c0                	test   %eax,%eax
    7fc61f99ab3a:	0f 94 c0             	sete   %al
    7fc61f99ab3d:	0f b6 c0             	movzbl %al,%eax
    7fc61f99ab40:	48 8b 52 38          	mov    0x38(%rdx),%rdx
    7fc61f99ab44:	89 02                	mov    %eax,(%rdx)
    7fc61f99ab46:	33 c0                	xor    %eax,%eax
    7fc61f99ab48:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fc61f99ab4c:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fc61f99ab51:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fc61f99ab56:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fc61f99ab5b:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fc61f99ab60:	48 8b e5             	mov    %rbp,%rsp
    7fc61f99ab63:	5d                   	pop    %rbp
    7fc61f99ab64:	c3                   	retq   

end

