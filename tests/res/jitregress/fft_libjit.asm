function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fa2eda3312d <.text>:
    7fa2eda3312d:	55                   	push   %rbp
    7fa2eda3312e:	48 8b ec             	mov    %rsp,%rbp
    7fa2eda33131:	48 81 ec 80 05 00 00 	sub    $0x580,%rsp
    7fa2eda33138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fa2eda3313c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fa2eda33141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fa2eda33146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fa2eda3314b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fa2eda33150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fa2eda33154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fa2eda33158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fa2eda3315c:	48 8b 00             	mov    (%rax),%rax
    7fa2eda3315f:	41 8b 8f 40 01 00 00 	mov    0x140(%r15),%ecx
    7fa2eda33166:	89 4d f0             	mov    %ecx,-0x10(%rbp)
    7fa2eda33169:	41 8b 8f 48 01 00 00 	mov    0x148(%r15),%ecx
    7fa2eda33170:	89 4d e8             	mov    %ecx,-0x18(%rbp)
    7fa2eda33173:	41 8b 8f d4 01 00 00 	mov    0x1d4(%r15),%ecx
    7fa2eda3317a:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7fa2eda3317d:	41 8b 8f dc 01 00 00 	mov    0x1dc(%r15),%ecx
    7fa2eda33184:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7fa2eda33187:	41 8b 8f ec 01 00 00 	mov    0x1ec(%r15),%ecx
    7fa2eda3318e:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7fa2eda33191:	41 8b 8f f4 01 00 00 	mov    0x1f4(%r15),%ecx
    7fa2eda33198:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7fa2eda3319b:	41 8b 8f fc 01 00 00 	mov    0x1fc(%r15),%ecx
    7fa2eda331a2:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7fa2eda331a5:	41 8b 8f 04 02 00 00 	mov    0x204(%r15),%ecx
    7fa2eda331ac:	89 4d b8             	mov    %ecx,-0x48(%rbp)
    7fa2eda331af:	41 8b 8f 0c 02 00 00 	mov    0x20c(%r15),%ecx
    7fa2eda331b6:	89 4d b0             	mov    %ecx,-0x50(%rbp)
    7fa2eda331b9:	41 8b 8f 14 02 00 00 	mov    0x214(%r15),%ecx
    7fa2eda331c0:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    7fa2eda331c3:	41 8b 8f 60 02 00 00 	mov    0x260(%r15),%ecx
    7fa2eda331ca:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7fa2eda331cd:	41 8b 8f 68 02 00 00 	mov    0x268(%r15),%ecx
    7fa2eda331d4:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7fa2eda331d7:	41 8b 8f 78 02 00 00 	mov    0x278(%r15),%ecx
    7fa2eda331de:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7fa2eda331e1:	41 8b 8f 80 02 00 00 	mov    0x280(%r15),%ecx
    7fa2eda331e8:	89 4d 88             	mov    %ecx,-0x78(%rbp)
    7fa2eda331eb:	41 8b 8f 88 02 00 00 	mov    0x288(%r15),%ecx
    7fa2eda331f2:	89 4d 80             	mov    %ecx,-0x80(%rbp)
    7fa2eda331f5:	41 8b 8f 90 02 00 00 	mov    0x290(%r15),%ecx
    7fa2eda331fc:	89 8d 78 ff ff ff    	mov    %ecx,-0x88(%rbp)
    7fa2eda33202:	41 8b 8f ac 02 00 00 	mov    0x2ac(%r15),%ecx
    7fa2eda33209:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7fa2eda3320f:	41 8b 8f bc 02 00 00 	mov    0x2bc(%r15),%ecx
    7fa2eda33216:	89 8d 68 ff ff ff    	mov    %ecx,-0x98(%rbp)
    7fa2eda3321c:	41 8b 8f c4 02 00 00 	mov    0x2c4(%r15),%ecx
    7fa2eda33223:	89 8d 60 ff ff ff    	mov    %ecx,-0xa0(%rbp)
    7fa2eda33229:	41 8b 8f f0 02 00 00 	mov    0x2f0(%r15),%ecx
    7fa2eda33230:	89 8d 58 ff ff ff    	mov    %ecx,-0xa8(%rbp)
    7fa2eda33236:	41 8b 8f f8 02 00 00 	mov    0x2f8(%r15),%ecx
    7fa2eda3323d:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7fa2eda33243:	41 8b 8f 08 03 00 00 	mov    0x308(%r15),%ecx
    7fa2eda3324a:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%rbp)
    7fa2eda33250:	41 8b 8f 10 03 00 00 	mov    0x310(%r15),%ecx
    7fa2eda33257:	89 8d 40 ff ff ff    	mov    %ecx,-0xc0(%rbp)
    7fa2eda3325d:	41 8b 8f 18 03 00 00 	mov    0x318(%r15),%ecx
    7fa2eda33264:	89 8d 38 ff ff ff    	mov    %ecx,-0xc8(%rbp)
    7fa2eda3326a:	41 8b 8f 20 03 00 00 	mov    0x320(%r15),%ecx
    7fa2eda33271:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7fa2eda33277:	41 8b 8f 28 03 00 00 	mov    0x328(%r15),%ecx
    7fa2eda3327e:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7fa2eda33284:	41 8b 8f 30 03 00 00 	mov    0x330(%r15),%ecx
    7fa2eda3328b:	89 8d 20 ff ff ff    	mov    %ecx,-0xe0(%rbp)
    7fa2eda33291:	41 8b 8f 4c 03 00 00 	mov    0x34c(%r15),%ecx
    7fa2eda33298:	89 8d 18 ff ff ff    	mov    %ecx,-0xe8(%rbp)
    7fa2eda3329e:	41 8b 8f 54 03 00 00 	mov    0x354(%r15),%ecx
    7fa2eda332a5:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7fa2eda332ab:	41 8b 8f 64 03 00 00 	mov    0x364(%r15),%ecx
    7fa2eda332b2:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7fa2eda332b8:	41 8b 8f 6c 03 00 00 	mov    0x36c(%r15),%ecx
    7fa2eda332bf:	89 8d 00 ff ff ff    	mov    %ecx,-0x100(%rbp)
    7fa2eda332c5:	41 8b 8f 74 03 00 00 	mov    0x374(%r15),%ecx
    7fa2eda332cc:	89 8d f8 fe ff ff    	mov    %ecx,-0x108(%rbp)
    7fa2eda332d2:	41 8b 8f 7c 03 00 00 	mov    0x37c(%r15),%ecx
    7fa2eda332d9:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7fa2eda332df:	41 8b 8f 98 03 00 00 	mov    0x398(%r15),%ecx
    7fa2eda332e6:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fa2eda332ec:	41 8b 8f a8 03 00 00 	mov    0x3a8(%r15),%ecx
    7fa2eda332f3:	89 8d e0 fe ff ff    	mov    %ecx,-0x120(%rbp)
    7fa2eda332f9:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7fa2eda33300:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7fa2eda33306:	41 8b 8f c0 03 00 00 	mov    0x3c0(%r15),%ecx
    7fa2eda3330d:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7fa2eda33313:	41 8b 8f c8 03 00 00 	mov    0x3c8(%r15),%ecx
    7fa2eda3331a:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fa2eda33320:	41 8b 8f d8 03 00 00 	mov    0x3d8(%r15),%ecx
    7fa2eda33327:	89 8d c0 fe ff ff    	mov    %ecx,-0x140(%rbp)
    7fa2eda3332d:	41 8b 8f e0 03 00 00 	mov    0x3e0(%r15),%ecx
    7fa2eda33334:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7fa2eda3333a:	41 8b 8f e8 03 00 00 	mov    0x3e8(%r15),%ecx
    7fa2eda33341:	89 8d b0 fe ff ff    	mov    %ecx,-0x150(%rbp)
    7fa2eda33347:	41 8b 8f f0 03 00 00 	mov    0x3f0(%r15),%ecx
    7fa2eda3334e:	89 8d a8 fe ff ff    	mov    %ecx,-0x158(%rbp)
    7fa2eda33354:	41 8b 8f f8 03 00 00 	mov    0x3f8(%r15),%ecx
    7fa2eda3335b:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7fa2eda33361:	41 8b 8f 00 04 00 00 	mov    0x400(%r15),%ecx
    7fa2eda33368:	89 8d 98 fe ff ff    	mov    %ecx,-0x168(%rbp)
    7fa2eda3336e:	41 8b 8f 08 04 00 00 	mov    0x408(%r15),%ecx
    7fa2eda33375:	89 8d 90 fe ff ff    	mov    %ecx,-0x170(%rbp)
    7fa2eda3337b:	41 8b 8f 10 04 00 00 	mov    0x410(%r15),%ecx
    7fa2eda33382:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7fa2eda33388:	41 8b 8f 20 04 00 00 	mov    0x420(%r15),%ecx
    7fa2eda3338f:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7fa2eda33395:	41 8b 9f 28 04 00 00 	mov    0x428(%r15),%ebx
    7fa2eda3339c:	41 8b 8f 30 04 00 00 	mov    0x430(%r15),%ecx
    7fa2eda333a3:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7fa2eda333a9:	41 8b 8f 38 04 00 00 	mov    0x438(%r15),%ecx
    7fa2eda333b0:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7fa2eda333b6:	41 8b 8f 40 04 00 00 	mov    0x440(%r15),%ecx
    7fa2eda333bd:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7fa2eda333c3:	41 8b 8f 48 04 00 00 	mov    0x448(%r15),%ecx
    7fa2eda333ca:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7fa2eda333d0:	41 8b 8f 50 04 00 00 	mov    0x450(%r15),%ecx
    7fa2eda333d7:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7fa2eda333dd:	48 89 85 50 fe ff ff 	mov    %rax,-0x1b0(%rbp)
    7fa2eda333e4:	48 8b 40 18          	mov    0x18(%rax),%rax
    7fa2eda333e8:	8b 00                	mov    (%rax),%eax
    7fa2eda333ea:	41 8b 8f 58 04 00 00 	mov    0x458(%r15),%ecx
    7fa2eda333f1:	33 c8                	xor    %eax,%ecx
    7fa2eda333f3:	23 c8                	and    %eax,%ecx
    7fa2eda333f5:	41 89 87 58 04 00 00 	mov    %eax,0x458(%r15)
    7fa2eda333fc:	85 c9                	test   %ecx,%ecx
    7fa2eda333fe:	0f 84 44 17 00 00    	je     0x7fa2eda34b48
    7fa2eda33404:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fa2eda33407:	ff c0                	inc    %eax
    7fa2eda33409:	83 e0 3f             	and    $0x3f,%eax
    7fa2eda3340c:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7fa2eda33412:	48 8b 85 50 fe ff ff 	mov    -0x1b0(%rbp),%rax
    7fa2eda33419:	48 8b 40 20          	mov    0x20(%rax),%rax
    7fa2eda3341d:	44 8b 28             	mov    (%rax),%r13d
    7fa2eda33420:	45 8b e5             	mov    %r13d,%r12d
    7fa2eda33423:	41 83 cc 00          	or     $0x0,%r12d
    7fa2eda33427:	33 c0                	xor    %eax,%eax
    7fa2eda33429:	3b 85 80 fe ff ff    	cmp    -0x180(%rbp),%eax
    7fa2eda3342f:	0f 94 c0             	sete   %al
    7fa2eda33432:	0f b6 c0             	movzbl %al,%eax
    7fa2eda33435:	85 c0                	test   %eax,%eax
    7fa2eda33437:	0f 94 c0             	sete   %al
    7fa2eda3343a:	0f b6 c0             	movzbl %al,%eax
    7fa2eda3343d:	8b cb                	mov    %ebx,%ecx
    7fa2eda3343f:	83 e1 01             	and    $0x1,%ecx
    7fa2eda33442:	85 c9                	test   %ecx,%ecx
    7fa2eda33444:	0f 94 c1             	sete   %cl
    7fa2eda33447:	0f b6 c9             	movzbl %cl,%ecx
    7fa2eda3344a:	85 c9                	test   %ecx,%ecx
    7fa2eda3344c:	0f 94 c2             	sete   %dl
    7fa2eda3344f:	0f b6 d2             	movzbl %dl,%edx
    7fa2eda33452:	23 c2                	and    %edx,%eax
    7fa2eda33454:	85 c0                	test   %eax,%eax
    7fa2eda33456:	0f 94 c0             	sete   %al
    7fa2eda33459:	0f b6 c0             	movzbl %al,%eax
    7fa2eda3345c:	8b 95 88 fe ff ff    	mov    -0x178(%rbp),%edx
    7fa2eda33462:	23 d0                	and    %eax,%edx
    7fa2eda33464:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7fa2eda3346a:	c1 ee 02             	shr    $0x2,%esi
    7fa2eda3346d:	83 e6 01             	and    $0x1,%esi
    7fa2eda33470:	85 f6                	test   %esi,%esi
    7fa2eda33472:	40 0f 94 c6          	sete   %sil
    7fa2eda33476:	40 0f b6 f6          	movzbl %sil,%esi
    7fa2eda3347a:	89 b5 40 fe ff ff    	mov    %esi,-0x1c0(%rbp)
    7fa2eda33480:	85 f6                	test   %esi,%esi
    7fa2eda33482:	40 0f 94 c6          	sete   %sil
    7fa2eda33486:	40 0f b6 f6          	movzbl %sil,%esi
    7fa2eda3348a:	89 95 38 fe ff ff    	mov    %edx,-0x1c8(%rbp)
    7fa2eda33490:	23 d6                	and    %esi,%edx
    7fa2eda33492:	85 d2                	test   %edx,%edx
    7fa2eda33494:	0f 94 c2             	sete   %dl
    7fa2eda33497:	0f b6 d2             	movzbl %dl,%edx
    7fa2eda3349a:	89 8d 30 fe ff ff    	mov    %ecx,-0x1d0(%rbp)
    7fa2eda334a0:	23 ca                	and    %edx,%ecx
    7fa2eda334a2:	89 95 28 fe ff ff    	mov    %edx,-0x1d8(%rbp)
    7fa2eda334a8:	23 c2                	and    %edx,%eax
    7fa2eda334aa:	89 8d 20 fe ff ff    	mov    %ecx,-0x1e0(%rbp)
    7fa2eda334b0:	4c 8b f0             	mov    %rax,%r14
    7fa2eda334b3:	23 c8                	and    %eax,%ecx
    7fa2eda334b5:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7fa2eda334bb:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fa2eda334be:	c1 e8 05             	shr    $0x5,%eax
    7fa2eda334c1:	83 e0 01             	and    $0x1,%eax
    7fa2eda334c4:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7fa2eda334c7:	c1 e9 10             	shr    $0x10,%ecx
    7fa2eda334ca:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda334d0:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7fa2eda334d6:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda334d9:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda334df:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7fa2eda334e5:	89 95 08 fe ff ff    	mov    %edx,-0x1f8(%rbp)
    7fa2eda334eb:	2b ca                	sub    %edx,%ecx
    7fa2eda334ed:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda334f3:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fa2eda334f6:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda334fc:	8b b5 78 fe ff ff    	mov    -0x188(%rbp),%esi
    7fa2eda33502:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda33508:	89 95 00 fe ff ff    	mov    %edx,-0x200(%rbp)
    7fa2eda3350e:	89 b5 f8 fd ff ff    	mov    %esi,-0x208(%rbp)
    7fa2eda33514:	2b d6                	sub    %esi,%edx
    7fa2eda33516:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3351c:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda3351f:	0b d1                	or     %ecx,%edx
    7fa2eda33521:	89 95 f0 fd ff ff    	mov    %edx,-0x210(%rbp)
    7fa2eda33527:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%rbp)
    7fa2eda3352d:	85 c0                	test   %eax,%eax
    7fa2eda3352f:	0f 85 0c 00 00 00    	jne    0x7fa2eda33541
    7fa2eda33535:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7fa2eda3353b:	89 85 f0 fd ff ff    	mov    %eax,-0x210(%rbp)
    7fa2eda33541:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fa2eda33547:	03 85 08 fe ff ff    	add    -0x1f8(%rbp),%eax
    7fa2eda3354d:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33552:	8b 8d 00 fe ff ff    	mov    -0x200(%rbp),%ecx
    7fa2eda33558:	03 8d f8 fd ff ff    	add    -0x208(%rbp),%ecx
    7fa2eda3355e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33564:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda33567:	0b c8                	or     %eax,%ecx
    7fa2eda33569:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fa2eda3356f:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7fa2eda33575:	85 c0                	test   %eax,%eax
    7fa2eda33577:	0f 85 09 00 00 00    	jne    0x7fa2eda33586
    7fa2eda3357d:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7fa2eda33580:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7fa2eda33586:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fa2eda33589:	ff c0                	inc    %eax
    7fa2eda3358b:	83 e0 3f             	and    $0x3f,%eax
    7fa2eda3358e:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7fa2eda33594:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fa2eda33597:	41 23 c6             	and    %r14d,%eax
    7fa2eda3359a:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7fa2eda335a0:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fa2eda335a3:	c1 e8 05             	shr    $0x5,%eax
    7fa2eda335a6:	83 e0 01             	and    $0x1,%eax
    7fa2eda335a9:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fa2eda335ac:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda335b2:	f7 d9                	neg    %ecx
    7fa2eda335b4:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda335ba:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fa2eda335bd:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda335c0:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda335c6:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda335c9:	0b d1                	or     %ecx,%edx
    7fa2eda335cb:	89 95 c8 fd ff ff    	mov    %edx,-0x238(%rbp)
    7fa2eda335d1:	85 c0                	test   %eax,%eax
    7fa2eda335d3:	0f 85 09 00 00 00    	jne    0x7fa2eda335e2
    7fa2eda335d9:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fa2eda335dc:	89 85 c8 fd ff ff    	mov    %eax,-0x238(%rbp)
    7fa2eda335e2:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fa2eda335e5:	ff c0                	inc    %eax
    7fa2eda335e7:	83 e0 1f             	and    $0x1f,%eax
    7fa2eda335ea:	89 85 c0 fd ff ff    	mov    %eax,-0x240(%rbp)
    7fa2eda335f0:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7fa2eda335f3:	41 23 c6             	and    %r14d,%eax
    7fa2eda335f6:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7fa2eda335fc:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fa2eda335ff:	c1 e8 04             	shr    $0x4,%eax
    7fa2eda33602:	83 e0 01             	and    $0x1,%eax
    7fa2eda33605:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fa2eda33608:	c1 e9 10             	shr    $0x10,%ecx
    7fa2eda3360b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33611:	8b 55 c8             	mov    -0x38(%rbp),%edx
    7fa2eda33614:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda33617:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3361d:	89 8d b0 fd ff ff    	mov    %ecx,-0x250(%rbp)
    7fa2eda33623:	89 95 a8 fd ff ff    	mov    %edx,-0x258(%rbp)
    7fa2eda33629:	2b ca                	sub    %edx,%ecx
    7fa2eda3362b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33631:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7fa2eda33634:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3363a:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7fa2eda3363d:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda33643:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7fa2eda33649:	89 b5 98 fd ff ff    	mov    %esi,-0x268(%rbp)
    7fa2eda3364f:	2b d6                	sub    %esi,%edx
    7fa2eda33651:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33657:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda3365a:	0b d1                	or     %ecx,%edx
    7fa2eda3365c:	89 95 90 fd ff ff    	mov    %edx,-0x270(%rbp)
    7fa2eda33662:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7fa2eda33668:	85 c0                	test   %eax,%eax
    7fa2eda3366a:	0f 85 09 00 00 00    	jne    0x7fa2eda33679
    7fa2eda33670:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fa2eda33673:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7fa2eda33679:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fa2eda3367f:	03 85 a8 fd ff ff    	add    -0x258(%rbp),%eax
    7fa2eda33685:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda3368a:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fa2eda33690:	03 8d 98 fd ff ff    	add    -0x268(%rbp),%ecx
    7fa2eda33696:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda3369c:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda3369f:	0b c8                	or     %eax,%ecx
    7fa2eda336a1:	89 8d 80 fd ff ff    	mov    %ecx,-0x280(%rbp)
    7fa2eda336a7:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7fa2eda336ad:	85 c0                	test   %eax,%eax
    7fa2eda336af:	0f 85 09 00 00 00    	jne    0x7fa2eda336be
    7fa2eda336b5:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fa2eda336b8:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fa2eda336be:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fa2eda336c1:	ff c0                	inc    %eax
    7fa2eda336c3:	83 e0 3f             	and    $0x3f,%eax
    7fa2eda336c6:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7fa2eda336cc:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fa2eda336cf:	41 23 c6             	and    %r14d,%eax
    7fa2eda336d2:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7fa2eda336d8:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fa2eda336db:	8b c0                	mov    %eax,%eax
    7fa2eda336dd:	41 8b 04 87          	mov    (%r15,%rax,4),%eax
    7fa2eda336e1:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7fa2eda336e7:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fa2eda336ea:	c1 e8 10             	shr    $0x10,%eax
    7fa2eda336ed:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda336f2:	8b 4d 80             	mov    -0x80(%rbp),%ecx
    7fa2eda336f5:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda336fb:	0f b7 d0             	movzwl %ax,%edx
    7fa2eda336fe:	0f bf d2             	movswl %dx,%edx
    7fa2eda33701:	0f b7 f1             	movzwl %cx,%esi
    7fa2eda33704:	0f bf f6             	movswl %si,%esi
    7fa2eda33707:	0f af d6             	imul   %esi,%edx
    7fa2eda3370a:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fa2eda33710:	8b 75 88             	mov    -0x78(%rbp),%esi
    7fa2eda33713:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda33719:	8b 7d 80             	mov    -0x80(%rbp),%edi
    7fa2eda3371c:	c1 ef 10             	shr    $0x10,%edi
    7fa2eda3371f:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7fa2eda33725:	44 0f b7 c6          	movzwl %si,%r8d
    7fa2eda33729:	45 0f bf c0          	movswl %r8w,%r8d
    7fa2eda3372d:	44 0f b7 cf          	movzwl %di,%r9d
    7fa2eda33731:	45 0f bf c9          	movswl %r9w,%r9d
    7fa2eda33735:	45 0f af c1          	imul   %r9d,%r8d
    7fa2eda33739:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7fa2eda33740:	41 03 d0             	add    %r8d,%edx
    7fa2eda33743:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fa2eda33749:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7fa2eda3374f:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7fa2eda33755:	89 95 60 fd ff ff    	mov    %edx,-0x2a0(%rbp)
    7fa2eda3375b:	c1 fa 0f             	sar    $0xf,%edx
    7fa2eda3375e:	89 95 58 fd ff ff    	mov    %edx,-0x2a8(%rbp)
    7fa2eda33764:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3376a:	89 b5 50 fd ff ff    	mov    %esi,-0x2b0(%rbp)
    7fa2eda33770:	0f b7 f6             	movzwl %si,%esi
    7fa2eda33773:	0f bf f6             	movswl %si,%esi
    7fa2eda33776:	89 8d 48 fd ff ff    	mov    %ecx,-0x2b8(%rbp)
    7fa2eda3377c:	0f b7 c9             	movzwl %cx,%ecx
    7fa2eda3377f:	0f bf c9             	movswl %cx,%ecx
    7fa2eda33782:	0f af f1             	imul   %ecx,%esi
    7fa2eda33785:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fa2eda3378b:	89 85 40 fd ff ff    	mov    %eax,-0x2c0(%rbp)
    7fa2eda33791:	0f b7 c0             	movzwl %ax,%eax
    7fa2eda33794:	0f bf c0             	movswl %ax,%eax
    7fa2eda33797:	89 bd 38 fd ff ff    	mov    %edi,-0x2c8(%rbp)
    7fa2eda3379d:	0f b7 ff             	movzwl %di,%edi
    7fa2eda337a0:	0f bf cf             	movswl %di,%ecx
    7fa2eda337a3:	0f af c1             	imul   %ecx,%eax
    7fa2eda337a6:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7fa2eda337ab:	2b f0                	sub    %eax,%esi
    7fa2eda337ad:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fa2eda337b3:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7fa2eda337b9:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7fa2eda337bf:	89 b5 30 fd ff ff    	mov    %esi,-0x2d0(%rbp)
    7fa2eda337c5:	c1 fe 0f             	sar    $0xf,%esi
    7fa2eda337c8:	89 b5 28 fd ff ff    	mov    %esi,-0x2d8(%rbp)
    7fa2eda337ce:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda337d4:	89 95 20 fd ff ff    	mov    %edx,-0x2e0(%rbp)
    7fa2eda337da:	c1 e2 10             	shl    $0x10,%edx
    7fa2eda337dd:	0b f2                	or     %edx,%esi
    7fa2eda337df:	89 b5 18 fd ff ff    	mov    %esi,-0x2e8(%rbp)
    7fa2eda337e5:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fa2eda337eb:	ff c0                	inc    %eax
    7fa2eda337ed:	83 e0 0f             	and    $0xf,%eax
    7fa2eda337f0:	89 85 10 fd ff ff    	mov    %eax,-0x2f0(%rbp)
    7fa2eda337f6:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fa2eda337fc:	41 23 c6             	and    %r14d,%eax
    7fa2eda337ff:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7fa2eda33805:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fa2eda3380b:	c1 e8 03             	shr    $0x3,%eax
    7fa2eda3380e:	83 e0 01             	and    $0x1,%eax
    7fa2eda33811:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7fa2eda33817:	c1 e9 10             	shr    $0x10,%ecx
    7fa2eda3381a:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33820:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7fa2eda33826:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda33829:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3382f:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7fa2eda33835:	89 95 f8 fc ff ff    	mov    %edx,-0x308(%rbp)
    7fa2eda3383b:	2b ca                	sub    %edx,%ecx
    7fa2eda3383d:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33843:	8b 95 60 ff ff ff    	mov    -0xa0(%rbp),%edx
    7fa2eda33849:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3384f:	8b b5 78 ff ff ff    	mov    -0x88(%rbp),%esi
    7fa2eda33855:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda3385b:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7fa2eda33861:	89 b5 e8 fc ff ff    	mov    %esi,-0x318(%rbp)
    7fa2eda33867:	2b d6                	sub    %esi,%edx
    7fa2eda33869:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3386f:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda33872:	0b d1                	or     %ecx,%edx
    7fa2eda33874:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7fa2eda3387a:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fa2eda33880:	85 c0                	test   %eax,%eax
    7fa2eda33882:	0f 85 0c 00 00 00    	jne    0x7fa2eda33894
    7fa2eda33888:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fa2eda3388e:	89 85 e0 fc ff ff    	mov    %eax,-0x320(%rbp)
    7fa2eda33894:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fa2eda3389a:	03 85 f8 fc ff ff    	add    -0x308(%rbp),%eax
    7fa2eda338a0:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda338a5:	8b 8d f0 fc ff ff    	mov    -0x310(%rbp),%ecx
    7fa2eda338ab:	03 8d e8 fc ff ff    	add    -0x318(%rbp),%ecx
    7fa2eda338b1:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda338b7:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda338ba:	0b c8                	or     %eax,%ecx
    7fa2eda338bc:	89 8d d0 fc ff ff    	mov    %ecx,-0x330(%rbp)
    7fa2eda338c2:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7fa2eda338c8:	85 c0                	test   %eax,%eax
    7fa2eda338ca:	0f 85 0c 00 00 00    	jne    0x7fa2eda338dc
    7fa2eda338d0:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fa2eda338d6:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7fa2eda338dc:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fa2eda338e2:	ff c0                	inc    %eax
    7fa2eda338e4:	83 e0 0f             	and    $0xf,%eax
    7fa2eda338e7:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7fa2eda338ed:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fa2eda338f3:	41 23 c6             	and    %r14d,%eax
    7fa2eda338f6:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7fa2eda338fc:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fa2eda33902:	c1 e8 03             	shr    $0x3,%eax
    7fa2eda33905:	83 e0 01             	and    $0x1,%eax
    7fa2eda33908:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7fa2eda3390e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33914:	f7 d9                	neg    %ecx
    7fa2eda33916:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda3391c:	8b 95 58 ff ff ff    	mov    -0xa8(%rbp),%edx
    7fa2eda33922:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda33925:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda3392b:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda3392e:	0b d1                	or     %ecx,%edx
    7fa2eda33930:	89 95 b8 fc ff ff    	mov    %edx,-0x348(%rbp)
    7fa2eda33936:	85 c0                	test   %eax,%eax
    7fa2eda33938:	0f 85 0c 00 00 00    	jne    0x7fa2eda3394a
    7fa2eda3393e:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fa2eda33944:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7fa2eda3394a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fa2eda33950:	ff c0                	inc    %eax
    7fa2eda33952:	83 e0 07             	and    $0x7,%eax
    7fa2eda33955:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7fa2eda3395b:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fa2eda33961:	41 23 c6             	and    %r14d,%eax
    7fa2eda33964:	89 85 a8 fc ff ff    	mov    %eax,-0x358(%rbp)
    7fa2eda3396a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fa2eda33970:	c1 e8 02             	shr    $0x2,%eax
    7fa2eda33973:	83 e0 01             	and    $0x1,%eax
    7fa2eda33976:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7fa2eda3397c:	c1 e9 10             	shr    $0x10,%ecx
    7fa2eda3397f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33985:	8b 95 40 ff ff ff    	mov    -0xc0(%rbp),%edx
    7fa2eda3398b:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda3398e:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33994:	89 8d a0 fc ff ff    	mov    %ecx,-0x360(%rbp)
    7fa2eda3399a:	89 95 98 fc ff ff    	mov    %edx,-0x368(%rbp)
    7fa2eda339a0:	2b ca                	sub    %edx,%ecx
    7fa2eda339a2:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda339a8:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7fa2eda339ae:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda339b4:	8b b5 40 ff ff ff    	mov    -0xc0(%rbp),%esi
    7fa2eda339ba:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda339c0:	89 95 90 fc ff ff    	mov    %edx,-0x370(%rbp)
    7fa2eda339c6:	89 b5 88 fc ff ff    	mov    %esi,-0x378(%rbp)
    7fa2eda339cc:	2b d6                	sub    %esi,%edx
    7fa2eda339ce:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda339d4:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda339d7:	0b d1                	or     %ecx,%edx
    7fa2eda339d9:	89 95 80 fc ff ff    	mov    %edx,-0x380(%rbp)
    7fa2eda339df:	89 85 78 fc ff ff    	mov    %eax,-0x388(%rbp)
    7fa2eda339e5:	85 c0                	test   %eax,%eax
    7fa2eda339e7:	0f 85 0c 00 00 00    	jne    0x7fa2eda339f9
    7fa2eda339ed:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fa2eda339f3:	89 85 80 fc ff ff    	mov    %eax,-0x380(%rbp)
    7fa2eda339f9:	8b 85 a0 fc ff ff    	mov    -0x360(%rbp),%eax
    7fa2eda339ff:	03 85 98 fc ff ff    	add    -0x368(%rbp),%eax
    7fa2eda33a05:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33a0a:	8b 8d 90 fc ff ff    	mov    -0x370(%rbp),%ecx
    7fa2eda33a10:	03 8d 88 fc ff ff    	add    -0x378(%rbp),%ecx
    7fa2eda33a16:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33a1c:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda33a1f:	0b c8                	or     %eax,%ecx
    7fa2eda33a21:	89 8d 70 fc ff ff    	mov    %ecx,-0x390(%rbp)
    7fa2eda33a27:	8b 85 78 fc ff ff    	mov    -0x388(%rbp),%eax
    7fa2eda33a2d:	85 c0                	test   %eax,%eax
    7fa2eda33a2f:	0f 85 0c 00 00 00    	jne    0x7fa2eda33a41
    7fa2eda33a35:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fa2eda33a3b:	89 85 70 fc ff ff    	mov    %eax,-0x390(%rbp)
    7fa2eda33a41:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fa2eda33a47:	ff c0                	inc    %eax
    7fa2eda33a49:	83 e0 0f             	and    $0xf,%eax
    7fa2eda33a4c:	89 85 68 fc ff ff    	mov    %eax,-0x398(%rbp)
    7fa2eda33a52:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fa2eda33a58:	41 23 c6             	and    %r14d,%eax
    7fa2eda33a5b:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7fa2eda33a61:	49 8b c7             	mov    %r15,%rax
    7fa2eda33a64:	48 05 00 01 00 00    	add    $0x100,%rax
    7fa2eda33a6a:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7fa2eda33a70:	8b c9                	mov    %ecx,%ecx
    7fa2eda33a72:	8b 04 88             	mov    (%rax,%rcx,4),%eax
    7fa2eda33a75:	89 85 58 fc ff ff    	mov    %eax,-0x3a8(%rbp)
    7fa2eda33a7b:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fa2eda33a81:	c1 e8 10             	shr    $0x10,%eax
    7fa2eda33a84:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33a89:	8b 8d f8 fe ff ff    	mov    -0x108(%rbp),%ecx
    7fa2eda33a8f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33a95:	0f b7 d0             	movzwl %ax,%edx
    7fa2eda33a98:	0f bf d2             	movswl %dx,%edx
    7fa2eda33a9b:	0f b7 f1             	movzwl %cx,%esi
    7fa2eda33a9e:	0f bf f6             	movswl %si,%esi
    7fa2eda33aa1:	0f af d6             	imul   %esi,%edx
    7fa2eda33aa4:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fa2eda33aaa:	8b b5 00 ff ff ff    	mov    -0x100(%rbp),%esi
    7fa2eda33ab0:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda33ab6:	8b bd f8 fe ff ff    	mov    -0x108(%rbp),%edi
    7fa2eda33abc:	c1 ef 10             	shr    $0x10,%edi
    7fa2eda33abf:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7fa2eda33ac5:	44 0f b7 c6          	movzwl %si,%r8d
    7fa2eda33ac9:	45 0f bf c0          	movswl %r8w,%r8d
    7fa2eda33acd:	44 0f b7 cf          	movzwl %di,%r9d
    7fa2eda33ad1:	45 0f bf c9          	movswl %r9w,%r9d
    7fa2eda33ad5:	45 0f af c1          	imul   %r9d,%r8d
    7fa2eda33ad9:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7fa2eda33ae0:	41 03 d0             	add    %r8d,%edx
    7fa2eda33ae3:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fa2eda33ae9:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7fa2eda33aef:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7fa2eda33af5:	89 95 50 fc ff ff    	mov    %edx,-0x3b0(%rbp)
    7fa2eda33afb:	c1 fa 0f             	sar    $0xf,%edx
    7fa2eda33afe:	89 95 48 fc ff ff    	mov    %edx,-0x3b8(%rbp)
    7fa2eda33b04:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33b0a:	89 b5 40 fc ff ff    	mov    %esi,-0x3c0(%rbp)
    7fa2eda33b10:	0f b7 f6             	movzwl %si,%esi
    7fa2eda33b13:	0f bf f6             	movswl %si,%esi
    7fa2eda33b16:	89 8d 38 fc ff ff    	mov    %ecx,-0x3c8(%rbp)
    7fa2eda33b1c:	0f b7 c9             	movzwl %cx,%ecx
    7fa2eda33b1f:	0f bf c9             	movswl %cx,%ecx
    7fa2eda33b22:	0f af f1             	imul   %ecx,%esi
    7fa2eda33b25:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fa2eda33b2b:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fa2eda33b31:	0f b7 c0             	movzwl %ax,%eax
    7fa2eda33b34:	0f bf c0             	movswl %ax,%eax
    7fa2eda33b37:	89 bd 28 fc ff ff    	mov    %edi,-0x3d8(%rbp)
    7fa2eda33b3d:	0f b7 ff             	movzwl %di,%edi
    7fa2eda33b40:	0f bf cf             	movswl %di,%ecx
    7fa2eda33b43:	0f af c1             	imul   %ecx,%eax
    7fa2eda33b46:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7fa2eda33b4b:	2b f0                	sub    %eax,%esi
    7fa2eda33b4d:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fa2eda33b53:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7fa2eda33b59:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7fa2eda33b5f:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7fa2eda33b65:	c1 fe 0f             	sar    $0xf,%esi
    7fa2eda33b68:	89 b5 18 fc ff ff    	mov    %esi,-0x3e8(%rbp)
    7fa2eda33b6e:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda33b74:	89 95 10 fc ff ff    	mov    %edx,-0x3f0(%rbp)
    7fa2eda33b7a:	c1 e2 10             	shl    $0x10,%edx
    7fa2eda33b7d:	0b f2                	or     %edx,%esi
    7fa2eda33b7f:	89 b5 08 fc ff ff    	mov    %esi,-0x3f8(%rbp)
    7fa2eda33b85:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fa2eda33b8b:	ff c0                	inc    %eax
    7fa2eda33b8d:	83 e0 03             	and    $0x3,%eax
    7fa2eda33b90:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fa2eda33b96:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fa2eda33b9c:	41 23 c6             	and    %r14d,%eax
    7fa2eda33b9f:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7fa2eda33ba5:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fa2eda33bab:	d1 e8                	shr    %eax
    7fa2eda33bad:	83 e0 01             	and    $0x1,%eax
    7fa2eda33bb0:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7fa2eda33bb6:	c1 e9 10             	shr    $0x10,%ecx
    7fa2eda33bb9:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33bbf:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fa2eda33bc5:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda33bc8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33bce:	89 8d f0 fb ff ff    	mov    %ecx,-0x410(%rbp)
    7fa2eda33bd4:	89 95 e8 fb ff ff    	mov    %edx,-0x418(%rbp)
    7fa2eda33bda:	2b ca                	sub    %edx,%ecx
    7fa2eda33bdc:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33be2:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7fa2eda33be8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33bee:	8b b5 f0 fe ff ff    	mov    -0x110(%rbp),%esi
    7fa2eda33bf4:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fa2eda33bfa:	89 95 e0 fb ff ff    	mov    %edx,-0x420(%rbp)
    7fa2eda33c00:	89 b5 d8 fb ff ff    	mov    %esi,-0x428(%rbp)
    7fa2eda33c06:	2b d6                	sub    %esi,%edx
    7fa2eda33c08:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33c0e:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda33c11:	0b d1                	or     %ecx,%edx
    7fa2eda33c13:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7fa2eda33c19:	89 85 c8 fb ff ff    	mov    %eax,-0x438(%rbp)
    7fa2eda33c1f:	85 c0                	test   %eax,%eax
    7fa2eda33c21:	0f 85 0c 00 00 00    	jne    0x7fa2eda33c33
    7fa2eda33c27:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7fa2eda33c2d:	89 85 d0 fb ff ff    	mov    %eax,-0x430(%rbp)
    7fa2eda33c33:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7fa2eda33c39:	03 85 e8 fb ff ff    	add    -0x418(%rbp),%eax
    7fa2eda33c3f:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33c44:	8b 8d e0 fb ff ff    	mov    -0x420(%rbp),%ecx
    7fa2eda33c4a:	03 8d d8 fb ff ff    	add    -0x428(%rbp),%ecx
    7fa2eda33c50:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33c56:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda33c59:	0b c8                	or     %eax,%ecx
    7fa2eda33c5b:	89 8d c0 fb ff ff    	mov    %ecx,-0x440(%rbp)
    7fa2eda33c61:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7fa2eda33c67:	85 c0                	test   %eax,%eax
    7fa2eda33c69:	0f 85 0c 00 00 00    	jne    0x7fa2eda33c7b
    7fa2eda33c6f:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fa2eda33c75:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7fa2eda33c7b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fa2eda33c81:	ff c0                	inc    %eax
    7fa2eda33c83:	83 e0 03             	and    $0x3,%eax
    7fa2eda33c86:	89 85 b8 fb ff ff    	mov    %eax,-0x448(%rbp)
    7fa2eda33c8c:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fa2eda33c92:	41 23 c6             	and    %r14d,%eax
    7fa2eda33c95:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7fa2eda33c9b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fa2eda33ca1:	d1 e8                	shr    %eax
    7fa2eda33ca3:	83 e0 01             	and    $0x1,%eax
    7fa2eda33ca6:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7fa2eda33cac:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33cb2:	f7 d9                	neg    %ecx
    7fa2eda33cb4:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33cba:	8b 95 d0 fe ff ff    	mov    -0x130(%rbp),%edx
    7fa2eda33cc0:	c1 ea 10             	shr    $0x10,%edx
    7fa2eda33cc3:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33cc9:	c1 e1 10             	shl    $0x10,%ecx
    7fa2eda33ccc:	0b d1                	or     %ecx,%edx
    7fa2eda33cce:	89 95 a8 fb ff ff    	mov    %edx,-0x458(%rbp)
    7fa2eda33cd4:	85 c0                	test   %eax,%eax
    7fa2eda33cd6:	0f 85 0c 00 00 00    	jne    0x7fa2eda33ce8
    7fa2eda33cdc:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fa2eda33ce2:	89 85 a8 fb ff ff    	mov    %eax,-0x458(%rbp)
    7fa2eda33ce8:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fa2eda33cee:	ff c0                	inc    %eax
    7fa2eda33cf0:	83 e0 01             	and    $0x1,%eax
    7fa2eda33cf3:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7fa2eda33cf9:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fa2eda33cff:	41 23 c6             	and    %r14d,%eax
    7fa2eda33d02:	89 85 98 fb ff ff    	mov    %eax,-0x468(%rbp)
    7fa2eda33d08:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fa2eda33d0e:	c1 e8 10             	shr    $0x10,%eax
    7fa2eda33d11:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33d16:	8b 8d b8 fe ff ff    	mov    -0x148(%rbp),%ecx
    7fa2eda33d1c:	c1 e9 10             	shr    $0x10,%ecx
    7fa2eda33d1f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33d25:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fa2eda33d2b:	89 8d 88 fb ff ff    	mov    %ecx,-0x478(%rbp)
    7fa2eda33d31:	2b c1                	sub    %ecx,%eax
    7fa2eda33d33:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33d38:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7fa2eda33d3e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33d44:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7fa2eda33d4a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fa2eda33d50:	89 8d 80 fb ff ff    	mov    %ecx,-0x480(%rbp)
    7fa2eda33d56:	89 95 78 fb ff ff    	mov    %edx,-0x488(%rbp)
    7fa2eda33d5c:	2b ca                	sub    %edx,%ecx
    7fa2eda33d5e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33d64:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda33d67:	0b c8                	or     %eax,%ecx
    7fa2eda33d69:	89 8d 70 fb ff ff    	mov    %ecx,-0x490(%rbp)
    7fa2eda33d6f:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fa2eda33d75:	85 c0                	test   %eax,%eax
    7fa2eda33d77:	0f 85 0c 00 00 00    	jne    0x7fa2eda33d89
    7fa2eda33d7d:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7fa2eda33d83:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7fa2eda33d89:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7fa2eda33d8f:	03 85 88 fb ff ff    	add    -0x478(%rbp),%eax
    7fa2eda33d95:	25 ff ff 00 00       	and    $0xffff,%eax
    7fa2eda33d9a:	8b 8d 80 fb ff ff    	mov    -0x480(%rbp),%ecx
    7fa2eda33da0:	03 8d 78 fb ff ff    	add    -0x488(%rbp),%ecx
    7fa2eda33da6:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fa2eda33dac:	c1 e0 10             	shl    $0x10,%eax
    7fa2eda33daf:	0b c8                	or     %eax,%ecx
    7fa2eda33db1:	89 8d 68 fb ff ff    	mov    %ecx,-0x498(%rbp)
    7fa2eda33db7:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fa2eda33dbd:	85 c0                	test   %eax,%eax
    7fa2eda33dbf:	0f 85 0c 00 00 00    	jne    0x7fa2eda33dd1
    7fa2eda33dc5:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fa2eda33dcb:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7fa2eda33dd1:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fa2eda33dd7:	ff c0                	inc    %eax
    7fa2eda33dd9:	83 e0 3f             	and    $0x3f,%eax
    7fa2eda33ddc:	89 85 60 fb ff ff    	mov    %eax,-0x4a0(%rbp)
    7fa2eda33de2:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fa2eda33de8:	41 23 c6             	and    %r14d,%eax
    7fa2eda33deb:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fa2eda33df1:	8b c3                	mov    %ebx,%eax
    7fa2eda33df3:	c1 e8 02             	shr    $0x2,%eax
    7fa2eda33df6:	83 e0 01             	and    $0x1,%eax
    7fa2eda33df9:	85 c0                	test   %eax,%eax
    7fa2eda33dfb:	0f 94 c0             	sete   %al
    7fa2eda33dfe:	0f b6 c0             	movzbl %al,%eax
    7fa2eda33e01:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7fa2eda33e08:	48 8b 49 08          	mov    0x8(%rcx),%rcx
    7fa2eda33e0c:	8b 09                	mov    (%rcx),%ecx
    7fa2eda33e0e:	23 c1                	and    %ecx,%eax
    7fa2eda33e10:	8b 8d 30 fe ff ff    	mov    -0x1d0(%rbp),%ecx
    7fa2eda33e16:	23 8d 28 fe ff ff    	and    -0x1d8(%rbp),%ecx
    7fa2eda33e1c:	85 c9                	test   %ecx,%ecx
    7fa2eda33e1e:	0f 94 c2             	sete   %dl
    7fa2eda33e21:	0f b6 d2             	movzbl %dl,%edx
    7fa2eda33e24:	89 95 50 fb ff ff    	mov    %edx,-0x4b0(%rbp)
    7fa2eda33e2a:	23 d0                	and    %eax,%edx
    7fa2eda33e2c:	8b f3                	mov    %ebx,%esi
    7fa2eda33e2e:	83 e6 03             	and    $0x3,%esi
    7fa2eda33e31:	d1 e6                	shl    %esi
    7fa2eda33e33:	89 b5 48 fb ff ff    	mov    %esi,-0x4b8(%rbp)
    7fa2eda33e39:	89 85 40 fb ff ff    	mov    %eax,-0x4c0(%rbp)
    7fa2eda33e3f:	85 c0                	test   %eax,%eax
    7fa2eda33e41:	0f 94 c0             	sete   %al
    7fa2eda33e44:	0f b6 c0             	movzbl %al,%eax
    7fa2eda33e47:	89 8d 38 fb ff ff    	mov    %ecx,-0x4c8(%rbp)
    7fa2eda33e4d:	23 c8                	and    %eax,%ecx
    7fa2eda33e4f:	89 8d 30 fb ff ff    	mov    %ecx,-0x4d0(%rbp)
    7fa2eda33e55:	8b c3                	mov    %ebx,%eax
    7fa2eda33e57:	d1 e8                	shr    %eax
    7fa2eda33e59:	83 e0 03             	and    $0x3,%eax
    7fa2eda33e5c:	89 85 28 fb ff ff    	mov    %eax,-0x4d8(%rbp)
    7fa2eda33e62:	85 d2                	test   %edx,%edx
    7fa2eda33e64:	0f 85 1b 00 00 00    	jne    0x7fa2eda33e85
    7fa2eda33e6a:	8b 85 30 fb ff ff    	mov    -0x4d0(%rbp),%eax
    7fa2eda33e70:	85 c0                	test   %eax,%eax
    7fa2eda33e72:	0f 85 1e 00 00 00    	jne    0x7fa2eda33e96
    7fa2eda33e78:	8b c3                	mov    %ebx,%eax
    7fa2eda33e7a:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7fa2eda33e80:	e9 1d 00 00 00       	jmpq   0x7fa2eda33ea2
    7fa2eda33e85:	8b 85 48 fb ff ff    	mov    -0x4b8(%rbp),%eax
    7fa2eda33e8b:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7fa2eda33e91:	e9 0c 00 00 00       	jmpq   0x7fa2eda33ea2
    7fa2eda33e96:	8b 85 28 fb ff ff    	mov    -0x4d8(%rbp),%eax
    7fa2eda33e9c:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7fa2eda33ea2:	8b c3                	mov    %ebx,%eax
    7fa2eda33ea4:	d1 e8                	shr    %eax
    7fa2eda33ea6:	83 e0 01             	and    $0x1,%eax
    7fa2eda33ea9:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7fa2eda33eaf:	8b 8d 50 fb ff ff    	mov    -0x4b0(%rbp),%ecx
    7fa2eda33eb5:	0b c1                	or     %ecx,%eax
    7fa2eda33eb7:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7fa2eda33ebe:	48 8b 09             	mov    (%rcx),%rcx
    7fa2eda33ec1:	8b 09                	mov    (%rcx),%ecx
    7fa2eda33ec3:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7fa2eda33ec9:	89 8d 08 fb ff ff    	mov    %ecx,-0x4f8(%rbp)
    7fa2eda33ecf:	85 c0                	test   %eax,%eax
    7fa2eda33ed1:	0f 85 0c 00 00 00    	jne    0x7fa2eda33ee3
    7fa2eda33ed7:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fa2eda33edd:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7fa2eda33ee3:	8b c3                	mov    %ebx,%eax
    7fa2eda33ee5:	83 e0 01             	and    $0x1,%eax
    7fa2eda33ee8:	8b 8d 40 fb ff ff    	mov    -0x4c0(%rbp),%ecx
    7fa2eda33eee:	23 c1                	and    %ecx,%eax
    7fa2eda33ef0:	8b 95 38 fb ff ff    	mov    -0x4c8(%rbp),%edx
    7fa2eda33ef6:	0b c2                	or     %edx,%eax
    7fa2eda33ef8:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7fa2eda33efe:	23 8d 18 fb ff ff    	and    -0x4e8(%rbp),%ecx
    7fa2eda33f04:	0b d1                	or     %ecx,%edx
    7fa2eda33f06:	89 95 f8 fa ff ff    	mov    %edx,-0x508(%rbp)
    7fa2eda33f0c:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fa2eda33f12:	23 85 38 fe ff ff    	and    -0x1c8(%rbp),%eax
    7fa2eda33f18:	8b 8d 68 fe ff ff    	mov    -0x198(%rbp),%ecx
    7fa2eda33f1e:	83 e1 01             	and    $0x1,%ecx
    7fa2eda33f21:	85 c9                	test   %ecx,%ecx
    7fa2eda33f23:	0f 94 c1             	sete   %cl
    7fa2eda33f26:	0f b6 c9             	movzbl %cl,%ecx
    7fa2eda33f29:	48 8b 95 50 fe ff ff 	mov    -0x1b0(%rbp),%rdx
    7fa2eda33f30:	48 8b 52 10          	mov    0x10(%rdx),%rdx
    7fa2eda33f34:	8b 12                	mov    (%rdx),%edx
    7fa2eda33f36:	23 ca                	and    %edx,%ecx
    7fa2eda33f38:	85 c9                	test   %ecx,%ecx
    7fa2eda33f3a:	0f 94 c2             	sete   %dl
    7fa2eda33f3d:	0f b6 d2             	movzbl %dl,%edx
    7fa2eda33f40:	89 95 f0 fa ff ff    	mov    %edx,-0x510(%rbp)
    7fa2eda33f46:	23 d0                	and    %eax,%edx
    7fa2eda33f48:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7fa2eda33f4e:	83 e6 03             	and    $0x3,%esi
    7fa2eda33f51:	d1 e6                	shl    %esi
    7fa2eda33f53:	89 b5 e8 fa ff ff    	mov    %esi,-0x518(%rbp)
    7fa2eda33f59:	89 85 e0 fa ff ff    	mov    %eax,-0x520(%rbp)
    7fa2eda33f5f:	85 c0                	test   %eax,%eax
    7fa2eda33f61:	0f 94 c0             	sete   %al
    7fa2eda33f64:	0f b6 c0             	movzbl %al,%eax
    7fa2eda33f67:	89 8d d8 fa ff ff    	mov    %ecx,-0x528(%rbp)
    7fa2eda33f6d:	23 c8                	and    %eax,%ecx
    7fa2eda33f6f:	89 8d d0 fa ff ff    	mov    %ecx,-0x530(%rbp)
    7fa2eda33f75:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fa2eda33f7b:	d1 e8                	shr    %eax
    7fa2eda33f7d:	83 e0 03             	and    $0x3,%eax
    7fa2eda33f80:	89 85 c8 fa ff ff    	mov    %eax,-0x538(%rbp)
    7fa2eda33f86:	85 d2                	test   %edx,%edx
    7fa2eda33f88:	0f 85 1f 00 00 00    	jne    0x7fa2eda33fad
    7fa2eda33f8e:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7fa2eda33f94:	85 c0                	test   %eax,%eax
    7fa2eda33f96:	0f 85 22 00 00 00    	jne    0x7fa2eda33fbe
    7fa2eda33f9c:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fa2eda33fa2:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fa2eda33fa8:	e9 1d 00 00 00       	jmpq   0x7fa2eda33fca
    7fa2eda33fad:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7fa2eda33fb3:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fa2eda33fb9:	e9 0c 00 00 00       	jmpq   0x7fa2eda33fca
    7fa2eda33fbe:	8b 85 c8 fa ff ff    	mov    -0x538(%rbp),%eax
    7fa2eda33fc4:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fa2eda33fca:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fa2eda33fd0:	d1 e8                	shr    %eax
    7fa2eda33fd2:	83 e0 01             	and    $0x1,%eax
    7fa2eda33fd5:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7fa2eda33fdb:	8b 8d f0 fa ff ff    	mov    -0x510(%rbp),%ecx
    7fa2eda33fe1:	0b c1                	or     %ecx,%eax
    7fa2eda33fe3:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fa2eda33fe9:	89 8d b0 fa ff ff    	mov    %ecx,-0x550(%rbp)
    7fa2eda33fef:	85 c0                	test   %eax,%eax
    7fa2eda33ff1:	0f 85 0c 00 00 00    	jne    0x7fa2eda34003
    7fa2eda33ff7:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fa2eda33ffd:	89 85 b0 fa ff ff    	mov    %eax,-0x550(%rbp)
    7fa2eda34003:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fa2eda34009:	83 e0 01             	and    $0x1,%eax
    7fa2eda3400c:	8b 8d e0 fa ff ff    	mov    -0x520(%rbp),%ecx
    7fa2eda34012:	23 c1                	and    %ecx,%eax
    7fa2eda34014:	8b 95 d8 fa ff ff    	mov    -0x528(%rbp),%edx
    7fa2eda3401a:	0b c2                	or     %edx,%eax
    7fa2eda3401c:	89 85 a8 fa ff ff    	mov    %eax,-0x558(%rbp)
    7fa2eda34022:	23 8d b8 fa ff ff    	and    -0x548(%rbp),%ecx
    7fa2eda34028:	0b d1                	or     %ecx,%edx
    7fa2eda3402a:	85 d2                	test   %edx,%edx
    7fa2eda3402c:	0f 84 13 00 00 00    	je     0x7fa2eda34045
    7fa2eda34032:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fa2eda34038:	41 89 87 50 04 00 00 	mov    %eax,0x450(%r15)
    7fa2eda3403f:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7fa2eda34045:	8b 85 a8 fa ff ff    	mov    -0x558(%rbp),%eax
    7fa2eda3404b:	85 c0                	test   %eax,%eax
    7fa2eda3404d:	0f 84 13 00 00 00    	je     0x7fa2eda34066
    7fa2eda34053:	8b 85 b0 fa ff ff    	mov    -0x550(%rbp),%eax
    7fa2eda34059:	41 89 87 48 04 00 00 	mov    %eax,0x448(%r15)
    7fa2eda34060:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fa2eda34066:	45 85 ed             	test   %r13d,%r13d
    7fa2eda34069:	0f 84 1a 00 00 00    	je     0x7fa2eda34089
    7fa2eda3406f:	41 c7 87 40 04 00 00 	movl   $0x1,0x440(%r15)
    7fa2eda34076:	01 00 00 00 
    7fa2eda3407a:	c7 85 68 fe ff ff 01 	movl   $0x1,-0x198(%rbp)
    7fa2eda34081:	00 00 00 
    7fa2eda34084:	e9 13 00 00 00       	jmpq   0x7fa2eda3409c
    7fa2eda34089:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fa2eda3408f:	41 89 87 40 04 00 00 	mov    %eax,0x440(%r15)
    7fa2eda34096:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7fa2eda3409c:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7fa2eda340a2:	85 c0                	test   %eax,%eax
    7fa2eda340a4:	0f 84 13 00 00 00    	je     0x7fa2eda340bd
    7fa2eda340aa:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fa2eda340b0:	41 89 87 38 04 00 00 	mov    %eax,0x438(%r15)
    7fa2eda340b7:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fa2eda340bd:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fa2eda340c3:	85 c0                	test   %eax,%eax
    7fa2eda340c5:	0f 84 13 00 00 00    	je     0x7fa2eda340de
    7fa2eda340cb:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fa2eda340d1:	41 89 87 30 04 00 00 	mov    %eax,0x430(%r15)
    7fa2eda340d8:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fa2eda340de:	45 85 ed             	test   %r13d,%r13d
    7fa2eda340e1:	0f 84 15 00 00 00    	je     0x7fa2eda340fc
    7fa2eda340e7:	41 c7 87 28 04 00 00 	movl   $0x1,0x428(%r15)
    7fa2eda340ee:	01 00 00 00 
    7fa2eda340f2:	bb 01 00 00 00       	mov    $0x1,%ebx
    7fa2eda340f7:	e9 10 00 00 00       	jmpq   0x7fa2eda3410c
    7fa2eda340fc:	8b 85 20 fb ff ff    	mov    -0x4e0(%rbp),%eax
    7fa2eda34102:	41 89 87 28 04 00 00 	mov    %eax,0x428(%r15)
    7fa2eda34109:	48 8b d8             	mov    %rax,%rbx
    7fa2eda3410c:	45 85 e4             	test   %r12d,%r12d
    7fa2eda3410f:	0f 84 1a 00 00 00    	je     0x7fa2eda3412f
    7fa2eda34115:	41 c7 87 20 04 00 00 	movl   $0x0,0x420(%r15)
    7fa2eda3411c:	00 00 00 00 
    7fa2eda34120:	c7 85 80 fe ff ff 00 	movl   $0x0,-0x180(%rbp)
    7fa2eda34127:	00 00 00 
    7fa2eda3412a:	e9 21 00 00 00       	jmpq   0x7fa2eda34150
    7fa2eda3412f:	8b 85 58 fb ff ff    	mov    -0x4a8(%rbp),%eax
    7fa2eda34135:	85 c0                	test   %eax,%eax
    7fa2eda34137:	0f 84 13 00 00 00    	je     0x7fa2eda34150
    7fa2eda3413d:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7fa2eda34143:	41 89 87 20 04 00 00 	mov    %eax,0x420(%r15)
    7fa2eda3414a:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fa2eda34150:	45 85 ed             	test   %r13d,%r13d
    7fa2eda34153:	0f 84 25 00 00 00    	je     0x7fa2eda3417e
    7fa2eda34159:	41 c7 87 10 04 00 00 	movl   $0x0,0x410(%r15)
    7fa2eda34160:	00 00 00 00 
    7fa2eda34164:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%rbp)
    7fa2eda3416b:	00 00 00 
    7fa2eda3416e:	41 c7 87 18 04 00 00 	movl   $0x0,0x418(%r15)
    7fa2eda34175:	00 00 00 00 
    7fa2eda34179:	e9 2a 00 00 00       	jmpq   0x7fa2eda341a8
    7fa2eda3417e:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34181:	0f 84 21 00 00 00    	je     0x7fa2eda341a8
    7fa2eda34187:	41 8b 87 18 04 00 00 	mov    0x418(%r15),%eax
    7fa2eda3418e:	41 89 87 10 04 00 00 	mov    %eax,0x410(%r15)
    7fa2eda34195:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fa2eda3419b:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fa2eda341a1:	41 89 87 18 04 00 00 	mov    %eax,0x418(%r15)
    7fa2eda341a8:	45 85 f6             	test   %r14d,%r14d
    7fa2eda341ab:	0f 84 26 00 00 00    	je     0x7fa2eda341d7
    7fa2eda341b1:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7fa2eda341b7:	41 89 87 08 04 00 00 	mov    %eax,0x408(%r15)
    7fa2eda341be:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fa2eda341c4:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fa2eda341ca:	41 89 87 00 04 00 00 	mov    %eax,0x400(%r15)
    7fa2eda341d1:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fa2eda341d7:	45 85 e4             	test   %r12d,%r12d
    7fa2eda341da:	0f 84 1a 00 00 00    	je     0x7fa2eda341fa
    7fa2eda341e0:	41 c7 87 f8 03 00 00 	movl   $0x0,0x3f8(%r15)
    7fa2eda341e7:	00 00 00 00 
    7fa2eda341eb:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7fa2eda341f2:	00 00 00 
    7fa2eda341f5:	e9 21 00 00 00       	jmpq   0x7fa2eda3421b
    7fa2eda341fa:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7fa2eda34200:	85 c0                	test   %eax,%eax
    7fa2eda34202:	0f 84 13 00 00 00    	je     0x7fa2eda3421b
    7fa2eda34208:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7fa2eda3420e:	41 89 87 f8 03 00 00 	mov    %eax,0x3f8(%r15)
    7fa2eda34215:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fa2eda3421b:	45 85 ed             	test   %r13d,%r13d
    7fa2eda3421e:	0f 84 1a 00 00 00    	je     0x7fa2eda3423e
    7fa2eda34224:	41 c7 87 f0 03 00 00 	movl   $0x0,0x3f0(%r15)
    7fa2eda3422b:	00 00 00 00 
    7fa2eda3422f:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7fa2eda34236:	00 00 00 
    7fa2eda34239:	e9 1c 00 00 00       	jmpq   0x7fa2eda3425a
    7fa2eda3423e:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34241:	0f 84 13 00 00 00    	je     0x7fa2eda3425a
    7fa2eda34247:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fa2eda3424d:	41 89 87 f0 03 00 00 	mov    %eax,0x3f0(%r15)
    7fa2eda34254:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fa2eda3425a:	45 85 f6             	test   %r14d,%r14d
    7fa2eda3425d:	0f 84 26 00 00 00    	je     0x7fa2eda34289
    7fa2eda34263:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fa2eda34269:	41 89 87 e8 03 00 00 	mov    %eax,0x3e8(%r15)
    7fa2eda34270:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fa2eda34276:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fa2eda3427c:	41 89 87 e0 03 00 00 	mov    %eax,0x3e0(%r15)
    7fa2eda34283:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fa2eda34289:	45 85 e4             	test   %r12d,%r12d
    7fa2eda3428c:	0f 84 1a 00 00 00    	je     0x7fa2eda342ac
    7fa2eda34292:	41 c7 87 d8 03 00 00 	movl   $0x0,0x3d8(%r15)
    7fa2eda34299:	00 00 00 00 
    7fa2eda3429d:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7fa2eda342a4:	00 00 00 
    7fa2eda342a7:	e9 21 00 00 00       	jmpq   0x7fa2eda342cd
    7fa2eda342ac:	8b 85 b0 fb ff ff    	mov    -0x450(%rbp),%eax
    7fa2eda342b2:	85 c0                	test   %eax,%eax
    7fa2eda342b4:	0f 84 13 00 00 00    	je     0x7fa2eda342cd
    7fa2eda342ba:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7fa2eda342c0:	41 89 87 d8 03 00 00 	mov    %eax,0x3d8(%r15)
    7fa2eda342c7:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fa2eda342cd:	45 85 ed             	test   %r13d,%r13d
    7fa2eda342d0:	0f 84 25 00 00 00    	je     0x7fa2eda342fb
    7fa2eda342d6:	41 c7 87 c8 03 00 00 	movl   $0x0,0x3c8(%r15)
    7fa2eda342dd:	00 00 00 00 
    7fa2eda342e1:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7fa2eda342e8:	00 00 00 
    7fa2eda342eb:	41 c7 87 d0 03 00 00 	movl   $0x0,0x3d0(%r15)
    7fa2eda342f2:	00 00 00 00 
    7fa2eda342f6:	e9 35 00 00 00       	jmpq   0x7fa2eda34330
    7fa2eda342fb:	45 85 f6             	test   %r14d,%r14d
    7fa2eda342fe:	0f 84 2c 00 00 00    	je     0x7fa2eda34330
    7fa2eda34304:	41 8b 87 d0 03 00 00 	mov    0x3d0(%r15),%eax
    7fa2eda3430b:	8b c8                	mov    %eax,%ecx
    7fa2eda3430d:	83 e1 01             	and    $0x1,%ecx
    7fa2eda34310:	41 89 8f c8 03 00 00 	mov    %ecx,0x3c8(%r15)
    7fa2eda34317:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fa2eda3431d:	d1 e8                	shr    %eax
    7fa2eda3431f:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7fa2eda34325:	d1 e1                	shl    %ecx
    7fa2eda34327:	0b c1                	or     %ecx,%eax
    7fa2eda34329:	41 89 87 d0 03 00 00 	mov    %eax,0x3d0(%r15)
    7fa2eda34330:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34333:	0f 84 34 00 00 00    	je     0x7fa2eda3436d
    7fa2eda34339:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fa2eda3433f:	41 89 87 c0 03 00 00 	mov    %eax,0x3c0(%r15)
    7fa2eda34346:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fa2eda3434c:	41 8b 87 b8 03 00 00 	mov    0x3b8(%r15),%eax
    7fa2eda34353:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7fa2eda3435a:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fa2eda34360:	8b 85 d0 fb ff ff    	mov    -0x430(%rbp),%eax
    7fa2eda34366:	41 89 87 b8 03 00 00 	mov    %eax,0x3b8(%r15)
    7fa2eda3436d:	45 85 e4             	test   %r12d,%r12d
    7fa2eda34370:	0f 84 1a 00 00 00    	je     0x7fa2eda34390
    7fa2eda34376:	41 c7 87 a8 03 00 00 	movl   $0x0,0x3a8(%r15)
    7fa2eda3437d:	00 00 00 00 
    7fa2eda34381:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7fa2eda34388:	00 00 00 
    7fa2eda3438b:	e9 21 00 00 00       	jmpq   0x7fa2eda343b1
    7fa2eda34390:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fa2eda34396:	85 c0                	test   %eax,%eax
    7fa2eda34398:	0f 84 13 00 00 00    	je     0x7fa2eda343b1
    7fa2eda3439e:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fa2eda343a4:	41 89 87 a8 03 00 00 	mov    %eax,0x3a8(%r15)
    7fa2eda343ab:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fa2eda343b1:	45 85 ed             	test   %r13d,%r13d
    7fa2eda343b4:	0f 84 25 00 00 00    	je     0x7fa2eda343df
    7fa2eda343ba:	41 c7 87 98 03 00 00 	movl   $0x0,0x398(%r15)
    7fa2eda343c1:	00 00 00 00 
    7fa2eda343c5:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7fa2eda343cc:	00 00 00 
    7fa2eda343cf:	41 c7 87 a0 03 00 00 	movl   $0x0,0x3a0(%r15)
    7fa2eda343d6:	00 00 00 00 
    7fa2eda343da:	e9 36 00 00 00       	jmpq   0x7fa2eda34415
    7fa2eda343df:	45 85 f6             	test   %r14d,%r14d
    7fa2eda343e2:	0f 84 2d 00 00 00    	je     0x7fa2eda34415
    7fa2eda343e8:	41 8b 87 a0 03 00 00 	mov    0x3a0(%r15),%eax
    7fa2eda343ef:	8b c8                	mov    %eax,%ecx
    7fa2eda343f1:	83 e1 01             	and    $0x1,%ecx
    7fa2eda343f4:	41 89 8f 98 03 00 00 	mov    %ecx,0x398(%r15)
    7fa2eda343fb:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fa2eda34401:	d1 e8                	shr    %eax
    7fa2eda34403:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7fa2eda34409:	c1 e1 04             	shl    $0x4,%ecx
    7fa2eda3440c:	0b c1                	or     %ecx,%eax
    7fa2eda3440e:	41 89 87 a0 03 00 00 	mov    %eax,0x3a0(%r15)
    7fa2eda34415:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34418:	0f 84 67 00 00 00    	je     0x7fa2eda34485
    7fa2eda3441e:	41 8b 87 94 03 00 00 	mov    0x394(%r15),%eax
    7fa2eda34425:	49 8b cf             	mov    %r15,%rcx
    7fa2eda34428:	48 81 c1 84 03 00 00 	add    $0x384,%rcx
    7fa2eda3442f:	8b d0                	mov    %eax,%edx
    7fa2eda34431:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fa2eda34434:	41 89 97 7c 03 00 00 	mov    %edx,0x37c(%r15)
    7fa2eda3443b:	89 95 f0 fe ff ff    	mov    %edx,-0x110(%rbp)
    7fa2eda34441:	8b d0                	mov    %eax,%edx
    7fa2eda34443:	8b b5 08 fc ff ff    	mov    -0x3f8(%rbp),%esi
    7fa2eda34449:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fa2eda3444c:	ff c8                	dec    %eax
    7fa2eda3444e:	b9 03 00 00 00       	mov    $0x3,%ecx
    7fa2eda34453:	3b c1                	cmp    %ecx,%eax
    7fa2eda34455:	0f 47 c1             	cmova  %ecx,%eax
    7fa2eda34458:	41 89 87 94 03 00 00 	mov    %eax,0x394(%r15)
    7fa2eda3445f:	8b 85 58 fc ff ff    	mov    -0x3a8(%rbp),%eax
    7fa2eda34465:	41 89 87 74 03 00 00 	mov    %eax,0x374(%r15)
    7fa2eda3446c:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fa2eda34472:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fa2eda34478:	41 89 87 6c 03 00 00 	mov    %eax,0x36c(%r15)
    7fa2eda3447f:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fa2eda34485:	45 85 e4             	test   %r12d,%r12d
    7fa2eda34488:	0f 84 1a 00 00 00    	je     0x7fa2eda344a8
    7fa2eda3448e:	41 c7 87 64 03 00 00 	movl   $0x0,0x364(%r15)
    7fa2eda34495:	00 00 00 00 
    7fa2eda34499:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7fa2eda344a0:	00 00 00 
    7fa2eda344a3:	e9 21 00 00 00       	jmpq   0x7fa2eda344c9
    7fa2eda344a8:	8b 85 60 fc ff ff    	mov    -0x3a0(%rbp),%eax
    7fa2eda344ae:	85 c0                	test   %eax,%eax
    7fa2eda344b0:	0f 84 13 00 00 00    	je     0x7fa2eda344c9
    7fa2eda344b6:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7fa2eda344bc:	41 89 87 64 03 00 00 	mov    %eax,0x364(%r15)
    7fa2eda344c3:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fa2eda344c9:	45 85 ed             	test   %r13d,%r13d
    7fa2eda344cc:	0f 84 25 00 00 00    	je     0x7fa2eda344f7
    7fa2eda344d2:	41 c7 87 54 03 00 00 	movl   $0x0,0x354(%r15)
    7fa2eda344d9:	00 00 00 00 
    7fa2eda344dd:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7fa2eda344e4:	00 00 00 
    7fa2eda344e7:	41 c7 87 5c 03 00 00 	movl   $0x0,0x35c(%r15)
    7fa2eda344ee:	00 00 00 00 
    7fa2eda344f2:	e9 36 00 00 00       	jmpq   0x7fa2eda3452d
    7fa2eda344f7:	45 85 f6             	test   %r14d,%r14d
    7fa2eda344fa:	0f 84 2d 00 00 00    	je     0x7fa2eda3452d
    7fa2eda34500:	41 8b 87 5c 03 00 00 	mov    0x35c(%r15),%eax
    7fa2eda34507:	8b c8                	mov    %eax,%ecx
    7fa2eda34509:	83 e1 01             	and    $0x1,%ecx
    7fa2eda3450c:	41 89 8f 54 03 00 00 	mov    %ecx,0x354(%r15)
    7fa2eda34513:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7fa2eda34519:	d1 e8                	shr    %eax
    7fa2eda3451b:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7fa2eda34521:	c1 e1 03             	shl    $0x3,%ecx
    7fa2eda34524:	0b c1                	or     %ecx,%eax
    7fa2eda34526:	41 89 87 5c 03 00 00 	mov    %eax,0x35c(%r15)
    7fa2eda3452d:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34530:	0f 84 54 00 00 00    	je     0x7fa2eda3458a
    7fa2eda34536:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7fa2eda3453c:	41 89 87 4c 03 00 00 	mov    %eax,0x34c(%r15)
    7fa2eda34543:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fa2eda34549:	41 8b 87 48 03 00 00 	mov    0x348(%r15),%eax
    7fa2eda34550:	49 8b cf             	mov    %r15,%rcx
    7fa2eda34553:	48 81 c1 38 03 00 00 	add    $0x338,%rcx
    7fa2eda3455a:	8b d0                	mov    %eax,%edx
    7fa2eda3455c:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fa2eda3455f:	41 89 97 30 03 00 00 	mov    %edx,0x330(%r15)
    7fa2eda34566:	89 95 20 ff ff ff    	mov    %edx,-0xe0(%rbp)
    7fa2eda3456c:	8b d0                	mov    %eax,%edx
    7fa2eda3456e:	8b b5 80 fc ff ff    	mov    -0x380(%rbp),%esi
    7fa2eda34574:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fa2eda34577:	ff c8                	dec    %eax
    7fa2eda34579:	b9 02 00 00 00       	mov    $0x2,%ecx
    7fa2eda3457e:	3b c1                	cmp    %ecx,%eax
    7fa2eda34580:	0f 47 c1             	cmova  %ecx,%eax
    7fa2eda34583:	41 89 87 48 03 00 00 	mov    %eax,0x348(%r15)
    7fa2eda3458a:	45 85 e4             	test   %r12d,%r12d
    7fa2eda3458d:	0f 84 1a 00 00 00    	je     0x7fa2eda345ad
    7fa2eda34593:	41 c7 87 28 03 00 00 	movl   $0x0,0x328(%r15)
    7fa2eda3459a:	00 00 00 00 
    7fa2eda3459e:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7fa2eda345a5:	00 00 00 
    7fa2eda345a8:	e9 21 00 00 00       	jmpq   0x7fa2eda345ce
    7fa2eda345ad:	8b 85 a8 fc ff ff    	mov    -0x358(%rbp),%eax
    7fa2eda345b3:	85 c0                	test   %eax,%eax
    7fa2eda345b5:	0f 84 13 00 00 00    	je     0x7fa2eda345ce
    7fa2eda345bb:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7fa2eda345c1:	41 89 87 28 03 00 00 	mov    %eax,0x328(%r15)
    7fa2eda345c8:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fa2eda345ce:	45 85 ed             	test   %r13d,%r13d
    7fa2eda345d1:	0f 84 1a 00 00 00    	je     0x7fa2eda345f1
    7fa2eda345d7:	41 c7 87 20 03 00 00 	movl   $0x0,0x320(%r15)
    7fa2eda345de:	00 00 00 00 
    7fa2eda345e2:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7fa2eda345e9:	00 00 00 
    7fa2eda345ec:	e9 1c 00 00 00       	jmpq   0x7fa2eda3460d
    7fa2eda345f1:	45 85 f6             	test   %r14d,%r14d
    7fa2eda345f4:	0f 84 13 00 00 00    	je     0x7fa2eda3460d
    7fa2eda345fa:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fa2eda34600:	41 89 87 20 03 00 00 	mov    %eax,0x320(%r15)
    7fa2eda34607:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fa2eda3460d:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34610:	0f 84 26 00 00 00    	je     0x7fa2eda3463c
    7fa2eda34616:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fa2eda3461c:	41 89 87 18 03 00 00 	mov    %eax,0x318(%r15)
    7fa2eda34623:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fa2eda34629:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7fa2eda3462f:	41 89 87 10 03 00 00 	mov    %eax,0x310(%r15)
    7fa2eda34636:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fa2eda3463c:	45 85 e4             	test   %r12d,%r12d
    7fa2eda3463f:	0f 84 1a 00 00 00    	je     0x7fa2eda3465f
    7fa2eda34645:	41 c7 87 08 03 00 00 	movl   $0x0,0x308(%r15)
    7fa2eda3464c:	00 00 00 00 
    7fa2eda34650:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7fa2eda34657:	00 00 00 
    7fa2eda3465a:	e9 21 00 00 00       	jmpq   0x7fa2eda34680
    7fa2eda3465f:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fa2eda34665:	85 c0                	test   %eax,%eax
    7fa2eda34667:	0f 84 13 00 00 00    	je     0x7fa2eda34680
    7fa2eda3466d:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7fa2eda34673:	41 89 87 08 03 00 00 	mov    %eax,0x308(%r15)
    7fa2eda3467a:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fa2eda34680:	45 85 ed             	test   %r13d,%r13d
    7fa2eda34683:	0f 84 25 00 00 00    	je     0x7fa2eda346ae
    7fa2eda34689:	41 c7 87 f8 02 00 00 	movl   $0x0,0x2f8(%r15)
    7fa2eda34690:	00 00 00 00 
    7fa2eda34694:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7fa2eda3469b:	00 00 00 
    7fa2eda3469e:	41 c7 87 00 03 00 00 	movl   $0x0,0x300(%r15)
    7fa2eda346a5:	00 00 00 00 
    7fa2eda346a9:	e9 36 00 00 00       	jmpq   0x7fa2eda346e4
    7fa2eda346ae:	45 85 f6             	test   %r14d,%r14d
    7fa2eda346b1:	0f 84 2d 00 00 00    	je     0x7fa2eda346e4
    7fa2eda346b7:	41 8b 87 00 03 00 00 	mov    0x300(%r15),%eax
    7fa2eda346be:	8b c8                	mov    %eax,%ecx
    7fa2eda346c0:	83 e1 01             	and    $0x1,%ecx
    7fa2eda346c3:	41 89 8f f8 02 00 00 	mov    %ecx,0x2f8(%r15)
    7fa2eda346ca:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7fa2eda346d0:	d1 e8                	shr    %eax
    7fa2eda346d2:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7fa2eda346d8:	c1 e1 07             	shl    $0x7,%ecx
    7fa2eda346db:	0b c1                	or     %ecx,%eax
    7fa2eda346dd:	41 89 87 00 03 00 00 	mov    %eax,0x300(%r15)
    7fa2eda346e4:	45 85 f6             	test   %r14d,%r14d
    7fa2eda346e7:	0f 84 54 00 00 00    	je     0x7fa2eda34741
    7fa2eda346ed:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7fa2eda346f3:	41 89 87 f0 02 00 00 	mov    %eax,0x2f0(%r15)
    7fa2eda346fa:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fa2eda34700:	41 8b 87 ec 02 00 00 	mov    0x2ec(%r15),%eax
    7fa2eda34707:	49 8b cf             	mov    %r15,%rcx
    7fa2eda3470a:	48 81 c1 cc 02 00 00 	add    $0x2cc,%rcx
    7fa2eda34711:	8b d0                	mov    %eax,%edx
    7fa2eda34713:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fa2eda34716:	41 89 97 c4 02 00 00 	mov    %edx,0x2c4(%r15)
    7fa2eda3471d:	89 95 60 ff ff ff    	mov    %edx,-0xa0(%rbp)
    7fa2eda34723:	8b d0                	mov    %eax,%edx
    7fa2eda34725:	8b b5 e0 fc ff ff    	mov    -0x320(%rbp),%esi
    7fa2eda3472b:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fa2eda3472e:	ff c8                	dec    %eax
    7fa2eda34730:	b9 06 00 00 00       	mov    $0x6,%ecx
    7fa2eda34735:	3b c1                	cmp    %ecx,%eax
    7fa2eda34737:	0f 47 c1             	cmova  %ecx,%eax
    7fa2eda3473a:	41 89 87 ec 02 00 00 	mov    %eax,0x2ec(%r15)
    7fa2eda34741:	45 85 e4             	test   %r12d,%r12d
    7fa2eda34744:	0f 84 1a 00 00 00    	je     0x7fa2eda34764
    7fa2eda3474a:	41 c7 87 bc 02 00 00 	movl   $0x0,0x2bc(%r15)
    7fa2eda34751:	00 00 00 00 
    7fa2eda34755:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7fa2eda3475c:	00 00 00 
    7fa2eda3475f:	e9 21 00 00 00       	jmpq   0x7fa2eda34785
    7fa2eda34764:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fa2eda3476a:	85 c0                	test   %eax,%eax
    7fa2eda3476c:	0f 84 13 00 00 00    	je     0x7fa2eda34785
    7fa2eda34772:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fa2eda34778:	41 89 87 bc 02 00 00 	mov    %eax,0x2bc(%r15)
    7fa2eda3477f:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fa2eda34785:	45 85 ed             	test   %r13d,%r13d
    7fa2eda34788:	0f 84 25 00 00 00    	je     0x7fa2eda347b3
    7fa2eda3478e:	41 c7 87 ac 02 00 00 	movl   $0x0,0x2ac(%r15)
    7fa2eda34795:	00 00 00 00 
    7fa2eda34799:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7fa2eda347a0:	00 00 00 
    7fa2eda347a3:	41 c7 87 b4 02 00 00 	movl   $0x0,0x2b4(%r15)
    7fa2eda347aa:	00 00 00 00 
    7fa2eda347ae:	e9 33 00 00 00       	jmpq   0x7fa2eda347e6
    7fa2eda347b3:	45 85 f6             	test   %r14d,%r14d
    7fa2eda347b6:	0f 84 2a 00 00 00    	je     0x7fa2eda347e6
    7fa2eda347bc:	41 8b 87 b4 02 00 00 	mov    0x2b4(%r15),%eax
    7fa2eda347c3:	8b c8                	mov    %eax,%ecx
    7fa2eda347c5:	83 e1 01             	and    $0x1,%ecx
    7fa2eda347c8:	41 89 8f ac 02 00 00 	mov    %ecx,0x2ac(%r15)
    7fa2eda347cf:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7fa2eda347d5:	d1 e8                	shr    %eax
    7fa2eda347d7:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7fa2eda347da:	c1 e1 04             	shl    $0x4,%ecx
    7fa2eda347dd:	0b c1                	or     %ecx,%eax
    7fa2eda347df:	41 89 87 b4 02 00 00 	mov    %eax,0x2b4(%r15)
    7fa2eda347e6:	45 85 f6             	test   %r14d,%r14d
    7fa2eda347e9:	0f 84 5e 00 00 00    	je     0x7fa2eda3484d
    7fa2eda347ef:	41 8b 87 a8 02 00 00 	mov    0x2a8(%r15),%eax
    7fa2eda347f6:	49 8b cf             	mov    %r15,%rcx
    7fa2eda347f9:	48 81 c1 98 02 00 00 	add    $0x298,%rcx
    7fa2eda34800:	8b d0                	mov    %eax,%edx
    7fa2eda34802:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fa2eda34805:	41 89 97 90 02 00 00 	mov    %edx,0x290(%r15)
    7fa2eda3480c:	89 95 78 ff ff ff    	mov    %edx,-0x88(%rbp)
    7fa2eda34812:	8b d0                	mov    %eax,%edx
    7fa2eda34814:	8b b5 18 fd ff ff    	mov    -0x2e8(%rbp),%esi
    7fa2eda3481a:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fa2eda3481d:	ff c8                	dec    %eax
    7fa2eda3481f:	b9 03 00 00 00       	mov    $0x3,%ecx
    7fa2eda34824:	3b c1                	cmp    %ecx,%eax
    7fa2eda34826:	0f 47 c1             	cmova  %ecx,%eax
    7fa2eda34829:	41 89 87 a8 02 00 00 	mov    %eax,0x2a8(%r15)
    7fa2eda34830:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7fa2eda34836:	41 89 87 88 02 00 00 	mov    %eax,0x288(%r15)
    7fa2eda3483d:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fa2eda34840:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fa2eda34843:	41 89 87 80 02 00 00 	mov    %eax,0x280(%r15)
    7fa2eda3484a:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fa2eda3484d:	45 85 e4             	test   %r12d,%r12d
    7fa2eda34850:	0f 84 17 00 00 00    	je     0x7fa2eda3486d
    7fa2eda34856:	41 c7 87 78 02 00 00 	movl   $0x0,0x278(%r15)
    7fa2eda3485d:	00 00 00 00 
    7fa2eda34861:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7fa2eda34868:	e9 1e 00 00 00       	jmpq   0x7fa2eda3488b
    7fa2eda3486d:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fa2eda34873:	85 c0                	test   %eax,%eax
    7fa2eda34875:	0f 84 10 00 00 00    	je     0x7fa2eda3488b
    7fa2eda3487b:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fa2eda34881:	41 89 87 78 02 00 00 	mov    %eax,0x278(%r15)
    7fa2eda34888:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fa2eda3488b:	45 85 ed             	test   %r13d,%r13d
    7fa2eda3488e:	0f 84 22 00 00 00    	je     0x7fa2eda348b6
    7fa2eda34894:	41 c7 87 68 02 00 00 	movl   $0x0,0x268(%r15)
    7fa2eda3489b:	00 00 00 00 
    7fa2eda3489f:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fa2eda348a6:	41 c7 87 70 02 00 00 	movl   $0x0,0x270(%r15)
    7fa2eda348ad:	00 00 00 00 
    7fa2eda348b1:	e9 30 00 00 00       	jmpq   0x7fa2eda348e6
    7fa2eda348b6:	45 85 f6             	test   %r14d,%r14d
    7fa2eda348b9:	0f 84 27 00 00 00    	je     0x7fa2eda348e6
    7fa2eda348bf:	41 8b 87 70 02 00 00 	mov    0x270(%r15),%eax
    7fa2eda348c6:	8b c8                	mov    %eax,%ecx
    7fa2eda348c8:	83 e1 01             	and    $0x1,%ecx
    7fa2eda348cb:	41 89 8f 68 02 00 00 	mov    %ecx,0x268(%r15)
    7fa2eda348d2:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7fa2eda348d5:	d1 e8                	shr    %eax
    7fa2eda348d7:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fa2eda348da:	c1 e1 0f             	shl    $0xf,%ecx
    7fa2eda348dd:	0b c1                	or     %ecx,%eax
    7fa2eda348df:	41 89 87 70 02 00 00 	mov    %eax,0x270(%r15)
    7fa2eda348e6:	45 85 f6             	test   %r14d,%r14d
    7fa2eda348e9:	0f 84 4e 00 00 00    	je     0x7fa2eda3493d
    7fa2eda348ef:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fa2eda348f5:	41 89 87 60 02 00 00 	mov    %eax,0x260(%r15)
    7fa2eda348fc:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fa2eda348ff:	41 8b 87 5c 02 00 00 	mov    0x25c(%r15),%eax
    7fa2eda34906:	49 8b cf             	mov    %r15,%rcx
    7fa2eda34909:	48 81 c1 1c 02 00 00 	add    $0x21c,%rcx
    7fa2eda34910:	8b d0                	mov    %eax,%edx
    7fa2eda34912:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fa2eda34915:	41 89 97 14 02 00 00 	mov    %edx,0x214(%r15)
    7fa2eda3491c:	89 55 a8             	mov    %edx,-0x58(%rbp)
    7fa2eda3491f:	8b d0                	mov    %eax,%edx
    7fa2eda34921:	8b b5 90 fd ff ff    	mov    -0x270(%rbp),%esi
    7fa2eda34927:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fa2eda3492a:	ff c8                	dec    %eax
    7fa2eda3492c:	b9 0e 00 00 00       	mov    $0xe,%ecx
    7fa2eda34931:	3b c1                	cmp    %ecx,%eax
    7fa2eda34933:	0f 47 c1             	cmova  %ecx,%eax
    7fa2eda34936:	41 89 87 5c 02 00 00 	mov    %eax,0x25c(%r15)
    7fa2eda3493d:	45 85 e4             	test   %r12d,%r12d
    7fa2eda34940:	0f 84 17 00 00 00    	je     0x7fa2eda3495d
    7fa2eda34946:	41 c7 87 0c 02 00 00 	movl   $0x0,0x20c(%r15)
    7fa2eda3494d:	00 00 00 00 
    7fa2eda34951:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7fa2eda34958:	e9 1e 00 00 00       	jmpq   0x7fa2eda3497b
    7fa2eda3495d:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7fa2eda34963:	85 c0                	test   %eax,%eax
    7fa2eda34965:	0f 84 10 00 00 00    	je     0x7fa2eda3497b
    7fa2eda3496b:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fa2eda34971:	41 89 87 0c 02 00 00 	mov    %eax,0x20c(%r15)
    7fa2eda34978:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fa2eda3497b:	45 85 ed             	test   %r13d,%r13d
    7fa2eda3497e:	0f 84 17 00 00 00    	je     0x7fa2eda3499b
    7fa2eda34984:	41 c7 87 04 02 00 00 	movl   $0x0,0x204(%r15)
    7fa2eda3498b:	00 00 00 00 
    7fa2eda3498f:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7fa2eda34996:	e9 16 00 00 00       	jmpq   0x7fa2eda349b1
    7fa2eda3499b:	45 85 f6             	test   %r14d,%r14d
    7fa2eda3499e:	0f 84 0d 00 00 00    	je     0x7fa2eda349b1
    7fa2eda349a4:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fa2eda349a7:	41 89 87 04 02 00 00 	mov    %eax,0x204(%r15)
    7fa2eda349ae:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fa2eda349b1:	45 85 f6             	test   %r14d,%r14d
    7fa2eda349b4:	0f 84 1d 00 00 00    	je     0x7fa2eda349d7
    7fa2eda349ba:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fa2eda349bd:	41 89 87 fc 01 00 00 	mov    %eax,0x1fc(%r15)
    7fa2eda349c4:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fa2eda349c7:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7fa2eda349cd:	41 89 87 f4 01 00 00 	mov    %eax,0x1f4(%r15)
    7fa2eda349d4:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fa2eda349d7:	45 85 e4             	test   %r12d,%r12d
    7fa2eda349da:	0f 84 17 00 00 00    	je     0x7fa2eda349f7
    7fa2eda349e0:	41 c7 87 ec 01 00 00 	movl   $0x0,0x1ec(%r15)
    7fa2eda349e7:	00 00 00 00 
    7fa2eda349eb:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7fa2eda349f2:	e9 1e 00 00 00       	jmpq   0x7fa2eda34a15
    7fa2eda349f7:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7fa2eda349fd:	85 c0                	test   %eax,%eax
    7fa2eda349ff:	0f 84 10 00 00 00    	je     0x7fa2eda34a15
    7fa2eda34a05:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fa2eda34a0b:	41 89 87 ec 01 00 00 	mov    %eax,0x1ec(%r15)
    7fa2eda34a12:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fa2eda34a15:	45 85 ed             	test   %r13d,%r13d
    7fa2eda34a18:	0f 84 22 00 00 00    	je     0x7fa2eda34a40
    7fa2eda34a1e:	41 c7 87 dc 01 00 00 	movl   $0x0,0x1dc(%r15)
    7fa2eda34a25:	00 00 00 00 
    7fa2eda34a29:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7fa2eda34a30:	41 c7 87 e4 01 00 00 	movl   $0x0,0x1e4(%r15)
    7fa2eda34a37:	00 00 00 00 
    7fa2eda34a3b:	e9 33 00 00 00       	jmpq   0x7fa2eda34a73
    7fa2eda34a40:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34a43:	0f 84 2a 00 00 00    	je     0x7fa2eda34a73
    7fa2eda34a49:	41 8b 87 e4 01 00 00 	mov    0x1e4(%r15),%eax
    7fa2eda34a50:	8b c8                	mov    %eax,%ecx
    7fa2eda34a52:	83 e1 01             	and    $0x1,%ecx
    7fa2eda34a55:	41 89 8f dc 01 00 00 	mov    %ecx,0x1dc(%r15)
    7fa2eda34a5c:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7fa2eda34a5f:	d1 e8                	shr    %eax
    7fa2eda34a61:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7fa2eda34a67:	c1 e1 1f             	shl    $0x1f,%ecx
    7fa2eda34a6a:	0b c1                	or     %ecx,%eax
    7fa2eda34a6c:	41 89 87 e4 01 00 00 	mov    %eax,0x1e4(%r15)
    7fa2eda34a73:	45 85 f6             	test   %r14d,%r14d
    7fa2eda34a76:	0f 84 4e 00 00 00    	je     0x7fa2eda34aca
    7fa2eda34a7c:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7fa2eda34a82:	41 89 87 d4 01 00 00 	mov    %eax,0x1d4(%r15)
    7fa2eda34a89:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fa2eda34a8c:	41 8b 87 d0 01 00 00 	mov    0x1d0(%r15),%eax
    7fa2eda34a93:	49 8b cf             	mov    %r15,%rcx
    7fa2eda34a96:	48 81 c1 50 01 00 00 	add    $0x150,%rcx
    7fa2eda34a9d:	8b d0                	mov    %eax,%edx
    7fa2eda34a9f:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fa2eda34aa2:	41 89 97 48 01 00 00 	mov    %edx,0x148(%r15)
    7fa2eda34aa9:	89 55 e8             	mov    %edx,-0x18(%rbp)
    7fa2eda34aac:	8b d0                	mov    %eax,%edx
    7fa2eda34aae:	8b b5 f0 fd ff ff    	mov    -0x210(%rbp),%esi
    7fa2eda34ab4:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fa2eda34ab7:	ff c8                	dec    %eax
    7fa2eda34ab9:	b9 1e 00 00 00       	mov    $0x1e,%ecx
    7fa2eda34abe:	3b c1                	cmp    %ecx,%eax
    7fa2eda34ac0:	0f 47 c1             	cmova  %ecx,%eax
    7fa2eda34ac3:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7fa2eda34aca:	45 85 e4             	test   %r12d,%r12d
    7fa2eda34acd:	0f 84 17 00 00 00    	je     0x7fa2eda34aea
    7fa2eda34ad3:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7fa2eda34ada:	00 00 00 00 
    7fa2eda34ade:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7fa2eda34ae5:	e9 1e 00 00 00       	jmpq   0x7fa2eda34b08
    7fa2eda34aea:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fa2eda34af0:	85 c0                	test   %eax,%eax
    7fa2eda34af2:	0f 84 10 00 00 00    	je     0x7fa2eda34b08
    7fa2eda34af8:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7fa2eda34afe:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7fa2eda34b05:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fa2eda34b08:	8b c3                	mov    %ebx,%eax
    7fa2eda34b0a:	c1 e8 02             	shr    $0x2,%eax
    7fa2eda34b0d:	83 e0 01             	and    $0x1,%eax
    7fa2eda34b10:	85 c0                	test   %eax,%eax
    7fa2eda34b12:	0f 94 c0             	sete   %al
    7fa2eda34b15:	0f b6 c0             	movzbl %al,%eax
    7fa2eda34b18:	48 8b 95 50 fe ff ff 	mov    -0x1b0(%rbp),%rdx
    7fa2eda34b1f:	48 8b 4a 28          	mov    0x28(%rdx),%rcx
    7fa2eda34b23:	89 01                	mov    %eax,(%rcx)
    7fa2eda34b25:	48 8b 42 30          	mov    0x30(%rdx),%rax
    7fa2eda34b29:	8b 8d 60 fe ff ff    	mov    -0x1a0(%rbp),%ecx
    7fa2eda34b2f:	89 08                	mov    %ecx,(%rax)
    7fa2eda34b31:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fa2eda34b37:	83 e0 01             	and    $0x1,%eax
    7fa2eda34b3a:	85 c0                	test   %eax,%eax
    7fa2eda34b3c:	0f 94 c0             	sete   %al
    7fa2eda34b3f:	0f b6 c0             	movzbl %al,%eax
    7fa2eda34b42:	48 8b 52 38          	mov    0x38(%rdx),%rdx
    7fa2eda34b46:	89 02                	mov    %eax,(%rdx)
    7fa2eda34b48:	33 c0                	xor    %eax,%eax
    7fa2eda34b4a:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fa2eda34b4e:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fa2eda34b53:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fa2eda34b58:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fa2eda34b5d:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fa2eda34b62:	48 8b e5             	mov    %rbp,%rsp
    7fa2eda34b65:	5d                   	pop    %rbp
    7fa2eda34b66:	c3                   	retq   

end

