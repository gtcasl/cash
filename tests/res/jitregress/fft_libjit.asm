function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f4b3c7d012d <.text>:
    7f4b3c7d012d:	55                   	push   %rbp
    7f4b3c7d012e:	48 8b ec             	mov    %rsp,%rbp
    7f4b3c7d0131:	48 81 ec 40 05 00 00 	sub    $0x540,%rsp
    7f4b3c7d0138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f4b3c7d013c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f4b3c7d0141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f4b3c7d0146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f4b3c7d014b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f4b3c7d0150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f4b3c7d0154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f4b3c7d0158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f4b3c7d015c:	48 8b 00             	mov    (%rax),%rax
    7f4b3c7d015f:	41 8b 8f 40 01 00 00 	mov    0x140(%r15),%ecx
    7f4b3c7d0166:	89 4d f0             	mov    %ecx,-0x10(%rbp)
    7f4b3c7d0169:	41 8b 8f 48 01 00 00 	mov    0x148(%r15),%ecx
    7f4b3c7d0170:	89 4d e8             	mov    %ecx,-0x18(%rbp)
    7f4b3c7d0173:	41 8b 8f d4 01 00 00 	mov    0x1d4(%r15),%ecx
    7f4b3c7d017a:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7f4b3c7d017d:	41 8b 8f dc 01 00 00 	mov    0x1dc(%r15),%ecx
    7f4b3c7d0184:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7f4b3c7d0187:	41 8b 8f ec 01 00 00 	mov    0x1ec(%r15),%ecx
    7f4b3c7d018e:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7f4b3c7d0191:	41 8b 8f f4 01 00 00 	mov    0x1f4(%r15),%ecx
    7f4b3c7d0198:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7f4b3c7d019b:	41 8b 8f fc 01 00 00 	mov    0x1fc(%r15),%ecx
    7f4b3c7d01a2:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7f4b3c7d01a5:	41 8b 8f 04 02 00 00 	mov    0x204(%r15),%ecx
    7f4b3c7d01ac:	89 4d b8             	mov    %ecx,-0x48(%rbp)
    7f4b3c7d01af:	41 8b 8f 0c 02 00 00 	mov    0x20c(%r15),%ecx
    7f4b3c7d01b6:	89 4d b0             	mov    %ecx,-0x50(%rbp)
    7f4b3c7d01b9:	41 8b 8f 14 02 00 00 	mov    0x214(%r15),%ecx
    7f4b3c7d01c0:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    7f4b3c7d01c3:	41 8b 8f 60 02 00 00 	mov    0x260(%r15),%ecx
    7f4b3c7d01ca:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7f4b3c7d01cd:	41 8b 8f 68 02 00 00 	mov    0x268(%r15),%ecx
    7f4b3c7d01d4:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7f4b3c7d01d7:	41 8b 8f 78 02 00 00 	mov    0x278(%r15),%ecx
    7f4b3c7d01de:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7f4b3c7d01e1:	41 8b 8f 80 02 00 00 	mov    0x280(%r15),%ecx
    7f4b3c7d01e8:	89 4d 88             	mov    %ecx,-0x78(%rbp)
    7f4b3c7d01eb:	41 8b 8f 88 02 00 00 	mov    0x288(%r15),%ecx
    7f4b3c7d01f2:	89 4d 80             	mov    %ecx,-0x80(%rbp)
    7f4b3c7d01f5:	41 8b 8f 90 02 00 00 	mov    0x290(%r15),%ecx
    7f4b3c7d01fc:	89 8d 78 ff ff ff    	mov    %ecx,-0x88(%rbp)
    7f4b3c7d0202:	41 8b 8f ac 02 00 00 	mov    0x2ac(%r15),%ecx
    7f4b3c7d0209:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7f4b3c7d020f:	41 8b 8f bc 02 00 00 	mov    0x2bc(%r15),%ecx
    7f4b3c7d0216:	89 8d 68 ff ff ff    	mov    %ecx,-0x98(%rbp)
    7f4b3c7d021c:	41 8b 8f c4 02 00 00 	mov    0x2c4(%r15),%ecx
    7f4b3c7d0223:	89 8d 60 ff ff ff    	mov    %ecx,-0xa0(%rbp)
    7f4b3c7d0229:	41 8b 8f f0 02 00 00 	mov    0x2f0(%r15),%ecx
    7f4b3c7d0230:	89 8d 58 ff ff ff    	mov    %ecx,-0xa8(%rbp)
    7f4b3c7d0236:	41 8b 8f f8 02 00 00 	mov    0x2f8(%r15),%ecx
    7f4b3c7d023d:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7f4b3c7d0243:	41 8b 8f 08 03 00 00 	mov    0x308(%r15),%ecx
    7f4b3c7d024a:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%rbp)
    7f4b3c7d0250:	41 8b 8f 10 03 00 00 	mov    0x310(%r15),%ecx
    7f4b3c7d0257:	89 8d 40 ff ff ff    	mov    %ecx,-0xc0(%rbp)
    7f4b3c7d025d:	41 8b 8f 18 03 00 00 	mov    0x318(%r15),%ecx
    7f4b3c7d0264:	89 8d 38 ff ff ff    	mov    %ecx,-0xc8(%rbp)
    7f4b3c7d026a:	41 8b 8f 20 03 00 00 	mov    0x320(%r15),%ecx
    7f4b3c7d0271:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7f4b3c7d0277:	41 8b 8f 28 03 00 00 	mov    0x328(%r15),%ecx
    7f4b3c7d027e:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7f4b3c7d0284:	41 8b 8f 30 03 00 00 	mov    0x330(%r15),%ecx
    7f4b3c7d028b:	89 8d 20 ff ff ff    	mov    %ecx,-0xe0(%rbp)
    7f4b3c7d0291:	41 8b 8f 4c 03 00 00 	mov    0x34c(%r15),%ecx
    7f4b3c7d0298:	89 8d 18 ff ff ff    	mov    %ecx,-0xe8(%rbp)
    7f4b3c7d029e:	41 8b 8f 54 03 00 00 	mov    0x354(%r15),%ecx
    7f4b3c7d02a5:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7f4b3c7d02ab:	41 8b 8f 64 03 00 00 	mov    0x364(%r15),%ecx
    7f4b3c7d02b2:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7f4b3c7d02b8:	41 8b 8f 6c 03 00 00 	mov    0x36c(%r15),%ecx
    7f4b3c7d02bf:	89 8d 00 ff ff ff    	mov    %ecx,-0x100(%rbp)
    7f4b3c7d02c5:	41 8b 8f 74 03 00 00 	mov    0x374(%r15),%ecx
    7f4b3c7d02cc:	89 8d f8 fe ff ff    	mov    %ecx,-0x108(%rbp)
    7f4b3c7d02d2:	41 8b 8f 7c 03 00 00 	mov    0x37c(%r15),%ecx
    7f4b3c7d02d9:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7f4b3c7d02df:	41 8b 8f 98 03 00 00 	mov    0x398(%r15),%ecx
    7f4b3c7d02e6:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7f4b3c7d02ec:	41 8b 8f a8 03 00 00 	mov    0x3a8(%r15),%ecx
    7f4b3c7d02f3:	89 8d e0 fe ff ff    	mov    %ecx,-0x120(%rbp)
    7f4b3c7d02f9:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7f4b3c7d0300:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7f4b3c7d0306:	41 8b 8f c0 03 00 00 	mov    0x3c0(%r15),%ecx
    7f4b3c7d030d:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7f4b3c7d0313:	41 8b 8f c8 03 00 00 	mov    0x3c8(%r15),%ecx
    7f4b3c7d031a:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7f4b3c7d0320:	41 8b 8f d8 03 00 00 	mov    0x3d8(%r15),%ecx
    7f4b3c7d0327:	89 8d c0 fe ff ff    	mov    %ecx,-0x140(%rbp)
    7f4b3c7d032d:	41 8b 8f e0 03 00 00 	mov    0x3e0(%r15),%ecx
    7f4b3c7d0334:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7f4b3c7d033a:	41 8b 8f e8 03 00 00 	mov    0x3e8(%r15),%ecx
    7f4b3c7d0341:	89 8d b0 fe ff ff    	mov    %ecx,-0x150(%rbp)
    7f4b3c7d0347:	41 8b 8f f0 03 00 00 	mov    0x3f0(%r15),%ecx
    7f4b3c7d034e:	89 8d a8 fe ff ff    	mov    %ecx,-0x158(%rbp)
    7f4b3c7d0354:	41 8b 8f f8 03 00 00 	mov    0x3f8(%r15),%ecx
    7f4b3c7d035b:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7f4b3c7d0361:	41 8b 8f 00 04 00 00 	mov    0x400(%r15),%ecx
    7f4b3c7d0368:	89 8d 98 fe ff ff    	mov    %ecx,-0x168(%rbp)
    7f4b3c7d036e:	41 8b 8f 08 04 00 00 	mov    0x408(%r15),%ecx
    7f4b3c7d0375:	89 8d 90 fe ff ff    	mov    %ecx,-0x170(%rbp)
    7f4b3c7d037b:	41 8b 8f 10 04 00 00 	mov    0x410(%r15),%ecx
    7f4b3c7d0382:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7f4b3c7d0388:	41 8b 8f 20 04 00 00 	mov    0x420(%r15),%ecx
    7f4b3c7d038f:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7f4b3c7d0395:	41 8b 9f 28 04 00 00 	mov    0x428(%r15),%ebx
    7f4b3c7d039c:	41 8b 8f 30 04 00 00 	mov    0x430(%r15),%ecx
    7f4b3c7d03a3:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7f4b3c7d03a9:	41 8b 8f 38 04 00 00 	mov    0x438(%r15),%ecx
    7f4b3c7d03b0:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7f4b3c7d03b6:	41 8b 8f 40 04 00 00 	mov    0x440(%r15),%ecx
    7f4b3c7d03bd:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7f4b3c7d03c3:	41 8b 8f 48 04 00 00 	mov    0x448(%r15),%ecx
    7f4b3c7d03ca:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7f4b3c7d03d0:	41 8b 8f 50 04 00 00 	mov    0x450(%r15),%ecx
    7f4b3c7d03d7:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7f4b3c7d03dd:	48 89 85 50 fe ff ff 	mov    %rax,-0x1b0(%rbp)
    7f4b3c7d03e4:	48 8b 40 18          	mov    0x18(%rax),%rax
    7f4b3c7d03e8:	8b 00                	mov    (%rax),%eax
    7f4b3c7d03ea:	41 8b 8f 58 04 00 00 	mov    0x458(%r15),%ecx
    7f4b3c7d03f1:	33 c8                	xor    %eax,%ecx
    7f4b3c7d03f3:	23 c8                	and    %eax,%ecx
    7f4b3c7d03f5:	41 89 87 58 04 00 00 	mov    %eax,0x458(%r15)
    7f4b3c7d03fc:	85 c9                	test   %ecx,%ecx
    7f4b3c7d03fe:	0f 84 a4 17 00 00    	je     0x7f4b3c7d1ba8
    7f4b3c7d0404:	33 c0                	xor    %eax,%eax
    7f4b3c7d0406:	3b 85 80 fe ff ff    	cmp    -0x180(%rbp),%eax
    7f4b3c7d040c:	0f 94 c0             	sete   %al
    7f4b3c7d040f:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d0412:	85 c0                	test   %eax,%eax
    7f4b3c7d0414:	0f 94 c0             	sete   %al
    7f4b3c7d0417:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d041a:	8b cb                	mov    %ebx,%ecx
    7f4b3c7d041c:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d041f:	85 c9                	test   %ecx,%ecx
    7f4b3c7d0421:	0f 94 c1             	sete   %cl
    7f4b3c7d0424:	0f b6 c9             	movzbl %cl,%ecx
    7f4b3c7d0427:	85 c9                	test   %ecx,%ecx
    7f4b3c7d0429:	0f 94 c2             	sete   %dl
    7f4b3c7d042c:	0f b6 d2             	movzbl %dl,%edx
    7f4b3c7d042f:	23 c2                	and    %edx,%eax
    7f4b3c7d0431:	85 c0                	test   %eax,%eax
    7f4b3c7d0433:	0f 94 c0             	sete   %al
    7f4b3c7d0436:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d0439:	8b 95 88 fe ff ff    	mov    -0x178(%rbp),%edx
    7f4b3c7d043f:	23 d0                	and    %eax,%edx
    7f4b3c7d0441:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7f4b3c7d0447:	c1 ee 02             	shr    $0x2,%esi
    7f4b3c7d044a:	83 e6 01             	and    $0x1,%esi
    7f4b3c7d044d:	85 f6                	test   %esi,%esi
    7f4b3c7d044f:	40 0f 94 c6          	sete   %sil
    7f4b3c7d0453:	40 0f b6 f6          	movzbl %sil,%esi
    7f4b3c7d0457:	89 b5 48 fe ff ff    	mov    %esi,-0x1b8(%rbp)
    7f4b3c7d045d:	85 f6                	test   %esi,%esi
    7f4b3c7d045f:	40 0f 94 c6          	sete   %sil
    7f4b3c7d0463:	40 0f b6 f6          	movzbl %sil,%esi
    7f4b3c7d0467:	89 95 40 fe ff ff    	mov    %edx,-0x1c0(%rbp)
    7f4b3c7d046d:	23 d6                	and    %esi,%edx
    7f4b3c7d046f:	85 d2                	test   %edx,%edx
    7f4b3c7d0471:	0f 94 c2             	sete   %dl
    7f4b3c7d0474:	0f b6 d2             	movzbl %dl,%edx
    7f4b3c7d0477:	89 8d 38 fe ff ff    	mov    %ecx,-0x1c8(%rbp)
    7f4b3c7d047d:	23 ca                	and    %edx,%ecx
    7f4b3c7d047f:	89 95 30 fe ff ff    	mov    %edx,-0x1d0(%rbp)
    7f4b3c7d0485:	23 c2                	and    %edx,%eax
    7f4b3c7d0487:	89 8d 28 fe ff ff    	mov    %ecx,-0x1d8(%rbp)
    7f4b3c7d048d:	4c 8b f0             	mov    %rax,%r14
    7f4b3c7d0490:	23 c8                	and    %eax,%ecx
    7f4b3c7d0492:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f4b3c7d0495:	ff c0                	inc    %eax
    7f4b3c7d0497:	83 e0 3f             	and    $0x3f,%eax
    7f4b3c7d049a:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7f4b3c7d04a0:	85 c9                	test   %ecx,%ecx
    7f4b3c7d04a2:	0f 85 09 00 00 00    	jne    0x7f4b3c7d04b1
    7f4b3c7d04a8:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f4b3c7d04ab:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7f4b3c7d04b1:	48 8b 85 50 fe ff ff 	mov    -0x1b0(%rbp),%rax
    7f4b3c7d04b8:	48 8b 40 20          	mov    0x20(%rax),%rax
    7f4b3c7d04bc:	44 8b 28             	mov    (%rax),%r13d
    7f4b3c7d04bf:	45 8b e5             	mov    %r13d,%r12d
    7f4b3c7d04c2:	41 83 cc 00          	or     $0x0,%r12d
    7f4b3c7d04c6:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f4b3c7d04c9:	c1 e8 05             	shr    $0x5,%eax
    7f4b3c7d04cc:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d04cf:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7f4b3c7d04d2:	c1 e9 10             	shr    $0x10,%ecx
    7f4b3c7d04d5:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d04db:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7f4b3c7d04e1:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d04e4:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d04ea:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7f4b3c7d04f0:	89 95 10 fe ff ff    	mov    %edx,-0x1f0(%rbp)
    7f4b3c7d04f6:	2b ca                	sub    %edx,%ecx
    7f4b3c7d04f8:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d04fe:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f4b3c7d0501:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0507:	8b b5 78 fe ff ff    	mov    -0x188(%rbp),%esi
    7f4b3c7d050d:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0513:	89 95 08 fe ff ff    	mov    %edx,-0x1f8(%rbp)
    7f4b3c7d0519:	89 b5 00 fe ff ff    	mov    %esi,-0x200(%rbp)
    7f4b3c7d051f:	2b d6                	sub    %esi,%edx
    7f4b3c7d0521:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0527:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d052a:	0b d1                	or     %ecx,%edx
    7f4b3c7d052c:	89 95 f8 fd ff ff    	mov    %edx,-0x208(%rbp)
    7f4b3c7d0532:	89 85 f0 fd ff ff    	mov    %eax,-0x210(%rbp)
    7f4b3c7d0538:	85 c0                	test   %eax,%eax
    7f4b3c7d053a:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d054c
    7f4b3c7d0540:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7f4b3c7d0546:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%rbp)
    7f4b3c7d054c:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f4b3c7d0552:	03 85 10 fe ff ff    	add    -0x1f0(%rbp),%eax
    7f4b3c7d0558:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d055d:	8b 8d 08 fe ff ff    	mov    -0x1f8(%rbp),%ecx
    7f4b3c7d0563:	03 8d 00 fe ff ff    	add    -0x200(%rbp),%ecx
    7f4b3c7d0569:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d056f:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d0572:	0b c8                	or     %eax,%ecx
    7f4b3c7d0574:	89 8d e8 fd ff ff    	mov    %ecx,-0x218(%rbp)
    7f4b3c7d057a:	8b 85 f0 fd ff ff    	mov    -0x210(%rbp),%eax
    7f4b3c7d0580:	85 c0                	test   %eax,%eax
    7f4b3c7d0582:	0f 85 09 00 00 00    	jne    0x7f4b3c7d0591
    7f4b3c7d0588:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7f4b3c7d058b:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%rbp)
    7f4b3c7d0591:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f4b3c7d0594:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d0597:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7f4b3c7d059a:	ff c1                	inc    %ecx
    7f4b3c7d059c:	83 e1 3f             	and    $0x3f,%ecx
    7f4b3c7d059f:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7f4b3c7d05a5:	85 c0                	test   %eax,%eax
    7f4b3c7d05a7:	0f 85 09 00 00 00    	jne    0x7f4b3c7d05b6
    7f4b3c7d05ad:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f4b3c7d05b0:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7f4b3c7d05b6:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f4b3c7d05b9:	c1 e8 05             	shr    $0x5,%eax
    7f4b3c7d05bc:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d05bf:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7f4b3c7d05c2:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d05c8:	f7 d9                	neg    %ecx
    7f4b3c7d05ca:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d05d0:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7f4b3c7d05d3:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d05d6:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d05dc:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d05df:	0b d1                	or     %ecx,%edx
    7f4b3c7d05e1:	89 95 d8 fd ff ff    	mov    %edx,-0x228(%rbp)
    7f4b3c7d05e7:	85 c0                	test   %eax,%eax
    7f4b3c7d05e9:	0f 85 09 00 00 00    	jne    0x7f4b3c7d05f8
    7f4b3c7d05ef:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f4b3c7d05f2:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7f4b3c7d05f8:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f4b3c7d05fb:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d05fe:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7f4b3c7d0601:	ff c1                	inc    %ecx
    7f4b3c7d0603:	83 e1 1f             	and    $0x1f,%ecx
    7f4b3c7d0606:	89 8d d0 fd ff ff    	mov    %ecx,-0x230(%rbp)
    7f4b3c7d060c:	85 c0                	test   %eax,%eax
    7f4b3c7d060e:	0f 85 09 00 00 00    	jne    0x7f4b3c7d061d
    7f4b3c7d0614:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f4b3c7d0617:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7f4b3c7d061d:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f4b3c7d0620:	c1 e8 04             	shr    $0x4,%eax
    7f4b3c7d0623:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d0626:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7f4b3c7d0629:	c1 e9 10             	shr    $0x10,%ecx
    7f4b3c7d062c:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0632:	8b 55 c8             	mov    -0x38(%rbp),%edx
    7f4b3c7d0635:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d0638:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d063e:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7f4b3c7d0644:	89 95 c0 fd ff ff    	mov    %edx,-0x240(%rbp)
    7f4b3c7d064a:	2b ca                	sub    %edx,%ecx
    7f4b3c7d064c:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0652:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7f4b3c7d0655:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d065b:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7f4b3c7d065e:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0664:	89 95 b8 fd ff ff    	mov    %edx,-0x248(%rbp)
    7f4b3c7d066a:	89 b5 b0 fd ff ff    	mov    %esi,-0x250(%rbp)
    7f4b3c7d0670:	2b d6                	sub    %esi,%edx
    7f4b3c7d0672:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0678:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d067b:	0b d1                	or     %ecx,%edx
    7f4b3c7d067d:	89 95 a8 fd ff ff    	mov    %edx,-0x258(%rbp)
    7f4b3c7d0683:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7f4b3c7d0689:	85 c0                	test   %eax,%eax
    7f4b3c7d068b:	0f 85 09 00 00 00    	jne    0x7f4b3c7d069a
    7f4b3c7d0691:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7f4b3c7d0694:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7f4b3c7d069a:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7f4b3c7d06a0:	03 85 c0 fd ff ff    	add    -0x240(%rbp),%eax
    7f4b3c7d06a6:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d06ab:	8b 8d b8 fd ff ff    	mov    -0x248(%rbp),%ecx
    7f4b3c7d06b1:	03 8d b0 fd ff ff    	add    -0x250(%rbp),%ecx
    7f4b3c7d06b7:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d06bd:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d06c0:	0b c8                	or     %eax,%ecx
    7f4b3c7d06c2:	89 8d 98 fd ff ff    	mov    %ecx,-0x268(%rbp)
    7f4b3c7d06c8:	8b 85 a0 fd ff ff    	mov    -0x260(%rbp),%eax
    7f4b3c7d06ce:	85 c0                	test   %eax,%eax
    7f4b3c7d06d0:	0f 85 09 00 00 00    	jne    0x7f4b3c7d06df
    7f4b3c7d06d6:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f4b3c7d06d9:	89 85 98 fd ff ff    	mov    %eax,-0x268(%rbp)
    7f4b3c7d06df:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f4b3c7d06e2:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d06e5:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7f4b3c7d06e8:	ff c1                	inc    %ecx
    7f4b3c7d06ea:	83 e1 3f             	and    $0x3f,%ecx
    7f4b3c7d06ed:	89 8d 90 fd ff ff    	mov    %ecx,-0x270(%rbp)
    7f4b3c7d06f3:	85 c0                	test   %eax,%eax
    7f4b3c7d06f5:	0f 85 09 00 00 00    	jne    0x7f4b3c7d0704
    7f4b3c7d06fb:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f4b3c7d06fe:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7f4b3c7d0704:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f4b3c7d0707:	8b c0                	mov    %eax,%eax
    7f4b3c7d0709:	41 8b 04 87          	mov    (%r15,%rax,4),%eax
    7f4b3c7d070d:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7f4b3c7d0713:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f4b3c7d0716:	c1 e8 10             	shr    $0x10,%eax
    7f4b3c7d0719:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d071e:	8b 4d 80             	mov    -0x80(%rbp),%ecx
    7f4b3c7d0721:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0727:	0f b7 d0             	movzwl %ax,%edx
    7f4b3c7d072a:	0f bf d2             	movswl %dx,%edx
    7f4b3c7d072d:	0f b7 f1             	movzwl %cx,%esi
    7f4b3c7d0730:	0f bf f6             	movswl %si,%esi
    7f4b3c7d0733:	0f af d6             	imul   %esi,%edx
    7f4b3c7d0736:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f4b3c7d073c:	8b 75 88             	mov    -0x78(%rbp),%esi
    7f4b3c7d073f:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0745:	8b 7d 80             	mov    -0x80(%rbp),%edi
    7f4b3c7d0748:	c1 ef 10             	shr    $0x10,%edi
    7f4b3c7d074b:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7f4b3c7d0751:	44 0f b7 c6          	movzwl %si,%r8d
    7f4b3c7d0755:	45 0f bf c0          	movswl %r8w,%r8d
    7f4b3c7d0759:	44 0f b7 cf          	movzwl %di,%r9d
    7f4b3c7d075d:	45 0f bf c9          	movswl %r9w,%r9d
    7f4b3c7d0761:	45 0f af c1          	imul   %r9d,%r8d
    7f4b3c7d0765:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7f4b3c7d076c:	41 03 d0             	add    %r8d,%edx
    7f4b3c7d076f:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f4b3c7d0775:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7f4b3c7d077b:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7f4b3c7d0781:	89 95 80 fd ff ff    	mov    %edx,-0x280(%rbp)
    7f4b3c7d0787:	c1 fa 0f             	sar    $0xf,%edx
    7f4b3c7d078a:	89 95 78 fd ff ff    	mov    %edx,-0x288(%rbp)
    7f4b3c7d0790:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0796:	89 b5 70 fd ff ff    	mov    %esi,-0x290(%rbp)
    7f4b3c7d079c:	0f b7 f6             	movzwl %si,%esi
    7f4b3c7d079f:	0f bf f6             	movswl %si,%esi
    7f4b3c7d07a2:	89 8d 68 fd ff ff    	mov    %ecx,-0x298(%rbp)
    7f4b3c7d07a8:	0f b7 c9             	movzwl %cx,%ecx
    7f4b3c7d07ab:	0f bf c9             	movswl %cx,%ecx
    7f4b3c7d07ae:	0f af f1             	imul   %ecx,%esi
    7f4b3c7d07b1:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7f4b3c7d07b7:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f4b3c7d07bd:	0f b7 c0             	movzwl %ax,%eax
    7f4b3c7d07c0:	0f bf c0             	movswl %ax,%eax
    7f4b3c7d07c3:	89 bd 58 fd ff ff    	mov    %edi,-0x2a8(%rbp)
    7f4b3c7d07c9:	0f b7 ff             	movzwl %di,%edi
    7f4b3c7d07cc:	0f bf cf             	movswl %di,%ecx
    7f4b3c7d07cf:	0f af c1             	imul   %ecx,%eax
    7f4b3c7d07d2:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7f4b3c7d07d7:	2b f0                	sub    %eax,%esi
    7f4b3c7d07d9:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7f4b3c7d07df:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7f4b3c7d07e5:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7f4b3c7d07eb:	89 b5 50 fd ff ff    	mov    %esi,-0x2b0(%rbp)
    7f4b3c7d07f1:	c1 fe 0f             	sar    $0xf,%esi
    7f4b3c7d07f4:	89 b5 48 fd ff ff    	mov    %esi,-0x2b8(%rbp)
    7f4b3c7d07fa:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0800:	89 95 40 fd ff ff    	mov    %edx,-0x2c0(%rbp)
    7f4b3c7d0806:	c1 e2 10             	shl    $0x10,%edx
    7f4b3c7d0809:	0b f2                	or     %edx,%esi
    7f4b3c7d080b:	89 b5 38 fd ff ff    	mov    %esi,-0x2c8(%rbp)
    7f4b3c7d0811:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f4b3c7d0817:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d081a:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7f4b3c7d0820:	ff c1                	inc    %ecx
    7f4b3c7d0822:	83 e1 0f             	and    $0xf,%ecx
    7f4b3c7d0825:	89 8d 30 fd ff ff    	mov    %ecx,-0x2d0(%rbp)
    7f4b3c7d082b:	85 c0                	test   %eax,%eax
    7f4b3c7d082d:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d083f
    7f4b3c7d0833:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7f4b3c7d0839:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7f4b3c7d083f:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7f4b3c7d0845:	c1 e8 03             	shr    $0x3,%eax
    7f4b3c7d0848:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d084b:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7f4b3c7d0851:	c1 e9 10             	shr    $0x10,%ecx
    7f4b3c7d0854:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d085a:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7f4b3c7d0860:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d0863:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0869:	89 8d 28 fd ff ff    	mov    %ecx,-0x2d8(%rbp)
    7f4b3c7d086f:	89 95 20 fd ff ff    	mov    %edx,-0x2e0(%rbp)
    7f4b3c7d0875:	2b ca                	sub    %edx,%ecx
    7f4b3c7d0877:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d087d:	8b 95 60 ff ff ff    	mov    -0xa0(%rbp),%edx
    7f4b3c7d0883:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0889:	8b b5 78 ff ff ff    	mov    -0x88(%rbp),%esi
    7f4b3c7d088f:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0895:	89 95 18 fd ff ff    	mov    %edx,-0x2e8(%rbp)
    7f4b3c7d089b:	89 b5 10 fd ff ff    	mov    %esi,-0x2f0(%rbp)
    7f4b3c7d08a1:	2b d6                	sub    %esi,%edx
    7f4b3c7d08a3:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d08a9:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d08ac:	0b d1                	or     %ecx,%edx
    7f4b3c7d08ae:	89 95 08 fd ff ff    	mov    %edx,-0x2f8(%rbp)
    7f4b3c7d08b4:	89 85 00 fd ff ff    	mov    %eax,-0x300(%rbp)
    7f4b3c7d08ba:	85 c0                	test   %eax,%eax
    7f4b3c7d08bc:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d08ce
    7f4b3c7d08c2:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7f4b3c7d08c8:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7f4b3c7d08ce:	8b 85 28 fd ff ff    	mov    -0x2d8(%rbp),%eax
    7f4b3c7d08d4:	03 85 20 fd ff ff    	add    -0x2e0(%rbp),%eax
    7f4b3c7d08da:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d08df:	8b 8d 18 fd ff ff    	mov    -0x2e8(%rbp),%ecx
    7f4b3c7d08e5:	03 8d 10 fd ff ff    	add    -0x2f0(%rbp),%ecx
    7f4b3c7d08eb:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d08f1:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d08f4:	0b c8                	or     %eax,%ecx
    7f4b3c7d08f6:	89 8d f8 fc ff ff    	mov    %ecx,-0x308(%rbp)
    7f4b3c7d08fc:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7f4b3c7d0902:	85 c0                	test   %eax,%eax
    7f4b3c7d0904:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0916
    7f4b3c7d090a:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f4b3c7d0910:	89 85 f8 fc ff ff    	mov    %eax,-0x308(%rbp)
    7f4b3c7d0916:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7f4b3c7d091c:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d091f:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7f4b3c7d0925:	ff c1                	inc    %ecx
    7f4b3c7d0927:	83 e1 0f             	and    $0xf,%ecx
    7f4b3c7d092a:	89 8d f0 fc ff ff    	mov    %ecx,-0x310(%rbp)
    7f4b3c7d0930:	85 c0                	test   %eax,%eax
    7f4b3c7d0932:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0944
    7f4b3c7d0938:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f4b3c7d093e:	89 85 f0 fc ff ff    	mov    %eax,-0x310(%rbp)
    7f4b3c7d0944:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f4b3c7d094a:	c1 e8 03             	shr    $0x3,%eax
    7f4b3c7d094d:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d0950:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7f4b3c7d0956:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d095c:	f7 d9                	neg    %ecx
    7f4b3c7d095e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0964:	8b 95 58 ff ff ff    	mov    -0xa8(%rbp),%edx
    7f4b3c7d096a:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d096d:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0973:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d0976:	0b d1                	or     %ecx,%edx
    7f4b3c7d0978:	89 95 e8 fc ff ff    	mov    %edx,-0x318(%rbp)
    7f4b3c7d097e:	85 c0                	test   %eax,%eax
    7f4b3c7d0980:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0992
    7f4b3c7d0986:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f4b3c7d098c:	89 85 e8 fc ff ff    	mov    %eax,-0x318(%rbp)
    7f4b3c7d0992:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f4b3c7d0998:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d099b:	8b 8d 28 ff ff ff    	mov    -0xd8(%rbp),%ecx
    7f4b3c7d09a1:	ff c1                	inc    %ecx
    7f4b3c7d09a3:	83 e1 07             	and    $0x7,%ecx
    7f4b3c7d09a6:	89 8d e0 fc ff ff    	mov    %ecx,-0x320(%rbp)
    7f4b3c7d09ac:	85 c0                	test   %eax,%eax
    7f4b3c7d09ae:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d09c0
    7f4b3c7d09b4:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f4b3c7d09ba:	89 85 e0 fc ff ff    	mov    %eax,-0x320(%rbp)
    7f4b3c7d09c0:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f4b3c7d09c6:	c1 e8 02             	shr    $0x2,%eax
    7f4b3c7d09c9:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d09cc:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7f4b3c7d09d2:	c1 e9 10             	shr    $0x10,%ecx
    7f4b3c7d09d5:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d09db:	8b 95 40 ff ff ff    	mov    -0xc0(%rbp),%edx
    7f4b3c7d09e1:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d09e4:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d09ea:	89 8d d8 fc ff ff    	mov    %ecx,-0x328(%rbp)
    7f4b3c7d09f0:	89 95 d0 fc ff ff    	mov    %edx,-0x330(%rbp)
    7f4b3c7d09f6:	2b ca                	sub    %edx,%ecx
    7f4b3c7d09f8:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d09fe:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7f4b3c7d0a04:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0a0a:	8b b5 40 ff ff ff    	mov    -0xc0(%rbp),%esi
    7f4b3c7d0a10:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0a16:	89 95 c8 fc ff ff    	mov    %edx,-0x338(%rbp)
    7f4b3c7d0a1c:	89 b5 c0 fc ff ff    	mov    %esi,-0x340(%rbp)
    7f4b3c7d0a22:	2b d6                	sub    %esi,%edx
    7f4b3c7d0a24:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0a2a:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d0a2d:	0b d1                	or     %ecx,%edx
    7f4b3c7d0a2f:	89 95 b8 fc ff ff    	mov    %edx,-0x348(%rbp)
    7f4b3c7d0a35:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7f4b3c7d0a3b:	85 c0                	test   %eax,%eax
    7f4b3c7d0a3d:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0a4f
    7f4b3c7d0a43:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f4b3c7d0a49:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7f4b3c7d0a4f:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7f4b3c7d0a55:	03 85 d0 fc ff ff    	add    -0x330(%rbp),%eax
    7f4b3c7d0a5b:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d0a60:	8b 8d c8 fc ff ff    	mov    -0x338(%rbp),%ecx
    7f4b3c7d0a66:	03 8d c0 fc ff ff    	add    -0x340(%rbp),%ecx
    7f4b3c7d0a6c:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0a72:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d0a75:	0b c8                	or     %eax,%ecx
    7f4b3c7d0a77:	89 8d a8 fc ff ff    	mov    %ecx,-0x358(%rbp)
    7f4b3c7d0a7d:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7f4b3c7d0a83:	85 c0                	test   %eax,%eax
    7f4b3c7d0a85:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0a97
    7f4b3c7d0a8b:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f4b3c7d0a91:	89 85 a8 fc ff ff    	mov    %eax,-0x358(%rbp)
    7f4b3c7d0a97:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f4b3c7d0a9d:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d0aa0:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7f4b3c7d0aa6:	ff c1                	inc    %ecx
    7f4b3c7d0aa8:	83 e1 0f             	and    $0xf,%ecx
    7f4b3c7d0aab:	89 8d a0 fc ff ff    	mov    %ecx,-0x360(%rbp)
    7f4b3c7d0ab1:	85 c0                	test   %eax,%eax
    7f4b3c7d0ab3:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0ac5
    7f4b3c7d0ab9:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f4b3c7d0abf:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7f4b3c7d0ac5:	49 8b c7             	mov    %r15,%rax
    7f4b3c7d0ac8:	48 05 00 01 00 00    	add    $0x100,%rax
    7f4b3c7d0ace:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7f4b3c7d0ad4:	8b c9                	mov    %ecx,%ecx
    7f4b3c7d0ad6:	8b 04 88             	mov    (%rax,%rcx,4),%eax
    7f4b3c7d0ad9:	89 85 98 fc ff ff    	mov    %eax,-0x368(%rbp)
    7f4b3c7d0adf:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f4b3c7d0ae5:	c1 e8 10             	shr    $0x10,%eax
    7f4b3c7d0ae8:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d0aed:	8b 8d f8 fe ff ff    	mov    -0x108(%rbp),%ecx
    7f4b3c7d0af3:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0af9:	0f b7 d0             	movzwl %ax,%edx
    7f4b3c7d0afc:	0f bf d2             	movswl %dx,%edx
    7f4b3c7d0aff:	0f b7 f1             	movzwl %cx,%esi
    7f4b3c7d0b02:	0f bf f6             	movswl %si,%esi
    7f4b3c7d0b05:	0f af d6             	imul   %esi,%edx
    7f4b3c7d0b08:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f4b3c7d0b0e:	8b b5 00 ff ff ff    	mov    -0x100(%rbp),%esi
    7f4b3c7d0b14:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0b1a:	8b bd f8 fe ff ff    	mov    -0x108(%rbp),%edi
    7f4b3c7d0b20:	c1 ef 10             	shr    $0x10,%edi
    7f4b3c7d0b23:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7f4b3c7d0b29:	44 0f b7 c6          	movzwl %si,%r8d
    7f4b3c7d0b2d:	45 0f bf c0          	movswl %r8w,%r8d
    7f4b3c7d0b31:	44 0f b7 cf          	movzwl %di,%r9d
    7f4b3c7d0b35:	45 0f bf c9          	movswl %r9w,%r9d
    7f4b3c7d0b39:	45 0f af c1          	imul   %r9d,%r8d
    7f4b3c7d0b3d:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7f4b3c7d0b44:	41 03 d0             	add    %r8d,%edx
    7f4b3c7d0b47:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7f4b3c7d0b4d:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7f4b3c7d0b53:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7f4b3c7d0b59:	89 95 90 fc ff ff    	mov    %edx,-0x370(%rbp)
    7f4b3c7d0b5f:	c1 fa 0f             	sar    $0xf,%edx
    7f4b3c7d0b62:	89 95 88 fc ff ff    	mov    %edx,-0x378(%rbp)
    7f4b3c7d0b68:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0b6e:	89 b5 80 fc ff ff    	mov    %esi,-0x380(%rbp)
    7f4b3c7d0b74:	0f b7 f6             	movzwl %si,%esi
    7f4b3c7d0b77:	0f bf f6             	movswl %si,%esi
    7f4b3c7d0b7a:	89 8d 78 fc ff ff    	mov    %ecx,-0x388(%rbp)
    7f4b3c7d0b80:	0f b7 c9             	movzwl %cx,%ecx
    7f4b3c7d0b83:	0f bf c9             	movswl %cx,%ecx
    7f4b3c7d0b86:	0f af f1             	imul   %ecx,%esi
    7f4b3c7d0b89:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7f4b3c7d0b8f:	89 85 70 fc ff ff    	mov    %eax,-0x390(%rbp)
    7f4b3c7d0b95:	0f b7 c0             	movzwl %ax,%eax
    7f4b3c7d0b98:	0f bf c0             	movswl %ax,%eax
    7f4b3c7d0b9b:	89 bd 68 fc ff ff    	mov    %edi,-0x398(%rbp)
    7f4b3c7d0ba1:	0f b7 ff             	movzwl %di,%edi
    7f4b3c7d0ba4:	0f bf cf             	movswl %di,%ecx
    7f4b3c7d0ba7:	0f af c1             	imul   %ecx,%eax
    7f4b3c7d0baa:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7f4b3c7d0baf:	2b f0                	sub    %eax,%esi
    7f4b3c7d0bb1:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7f4b3c7d0bb7:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7f4b3c7d0bbd:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7f4b3c7d0bc3:	89 b5 60 fc ff ff    	mov    %esi,-0x3a0(%rbp)
    7f4b3c7d0bc9:	c1 fe 0f             	sar    $0xf,%esi
    7f4b3c7d0bcc:	89 b5 58 fc ff ff    	mov    %esi,-0x3a8(%rbp)
    7f4b3c7d0bd2:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0bd8:	89 95 50 fc ff ff    	mov    %edx,-0x3b0(%rbp)
    7f4b3c7d0bde:	c1 e2 10             	shl    $0x10,%edx
    7f4b3c7d0be1:	0b f2                	or     %edx,%esi
    7f4b3c7d0be3:	89 b5 48 fc ff ff    	mov    %esi,-0x3b8(%rbp)
    7f4b3c7d0be9:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7f4b3c7d0bef:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d0bf2:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7f4b3c7d0bf8:	ff c1                	inc    %ecx
    7f4b3c7d0bfa:	83 e1 03             	and    $0x3,%ecx
    7f4b3c7d0bfd:	89 8d 40 fc ff ff    	mov    %ecx,-0x3c0(%rbp)
    7f4b3c7d0c03:	85 c0                	test   %eax,%eax
    7f4b3c7d0c05:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0c17
    7f4b3c7d0c0b:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7f4b3c7d0c11:	89 85 40 fc ff ff    	mov    %eax,-0x3c0(%rbp)
    7f4b3c7d0c17:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7f4b3c7d0c1d:	d1 e8                	shr    %eax
    7f4b3c7d0c1f:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d0c22:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7f4b3c7d0c28:	c1 e9 10             	shr    $0x10,%ecx
    7f4b3c7d0c2b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0c31:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7f4b3c7d0c37:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d0c3a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0c40:	89 8d 38 fc ff ff    	mov    %ecx,-0x3c8(%rbp)
    7f4b3c7d0c46:	89 95 30 fc ff ff    	mov    %edx,-0x3d0(%rbp)
    7f4b3c7d0c4c:	2b ca                	sub    %edx,%ecx
    7f4b3c7d0c4e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0c54:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7f4b3c7d0c5a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0c60:	8b b5 f0 fe ff ff    	mov    -0x110(%rbp),%esi
    7f4b3c7d0c66:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7f4b3c7d0c6c:	89 95 28 fc ff ff    	mov    %edx,-0x3d8(%rbp)
    7f4b3c7d0c72:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7f4b3c7d0c78:	2b d6                	sub    %esi,%edx
    7f4b3c7d0c7a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0c80:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d0c83:	0b d1                	or     %ecx,%edx
    7f4b3c7d0c85:	89 95 18 fc ff ff    	mov    %edx,-0x3e8(%rbp)
    7f4b3c7d0c8b:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7f4b3c7d0c91:	85 c0                	test   %eax,%eax
    7f4b3c7d0c93:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0ca5
    7f4b3c7d0c99:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f4b3c7d0c9f:	89 85 18 fc ff ff    	mov    %eax,-0x3e8(%rbp)
    7f4b3c7d0ca5:	8b 85 38 fc ff ff    	mov    -0x3c8(%rbp),%eax
    7f4b3c7d0cab:	03 85 30 fc ff ff    	add    -0x3d0(%rbp),%eax
    7f4b3c7d0cb1:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d0cb6:	8b 8d 28 fc ff ff    	mov    -0x3d8(%rbp),%ecx
    7f4b3c7d0cbc:	03 8d 20 fc ff ff    	add    -0x3e0(%rbp),%ecx
    7f4b3c7d0cc2:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0cc8:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d0ccb:	0b c8                	or     %eax,%ecx
    7f4b3c7d0ccd:	89 8d 08 fc ff ff    	mov    %ecx,-0x3f8(%rbp)
    7f4b3c7d0cd3:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7f4b3c7d0cd9:	85 c0                	test   %eax,%eax
    7f4b3c7d0cdb:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0ced
    7f4b3c7d0ce1:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7f4b3c7d0ce7:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7f4b3c7d0ced:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f4b3c7d0cf3:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d0cf6:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7f4b3c7d0cfc:	ff c1                	inc    %ecx
    7f4b3c7d0cfe:	83 e1 03             	and    $0x3,%ecx
    7f4b3c7d0d01:	89 8d 00 fc ff ff    	mov    %ecx,-0x400(%rbp)
    7f4b3c7d0d07:	85 c0                	test   %eax,%eax
    7f4b3c7d0d09:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0d1b
    7f4b3c7d0d0f:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f4b3c7d0d15:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f4b3c7d0d1b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f4b3c7d0d21:	d1 e8                	shr    %eax
    7f4b3c7d0d23:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d0d26:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f4b3c7d0d2c:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0d32:	f7 d9                	neg    %ecx
    7f4b3c7d0d34:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0d3a:	8b 95 d0 fe ff ff    	mov    -0x130(%rbp),%edx
    7f4b3c7d0d40:	c1 ea 10             	shr    $0x10,%edx
    7f4b3c7d0d43:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0d49:	c1 e1 10             	shl    $0x10,%ecx
    7f4b3c7d0d4c:	0b d1                	or     %ecx,%edx
    7f4b3c7d0d4e:	89 95 f8 fb ff ff    	mov    %edx,-0x408(%rbp)
    7f4b3c7d0d54:	85 c0                	test   %eax,%eax
    7f4b3c7d0d56:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0d68
    7f4b3c7d0d5c:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7f4b3c7d0d62:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7f4b3c7d0d68:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f4b3c7d0d6e:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d0d71:	8b 8d a0 fe ff ff    	mov    -0x160(%rbp),%ecx
    7f4b3c7d0d77:	ff c1                	inc    %ecx
    7f4b3c7d0d79:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d0d7c:	89 8d f0 fb ff ff    	mov    %ecx,-0x410(%rbp)
    7f4b3c7d0d82:	85 c0                	test   %eax,%eax
    7f4b3c7d0d84:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0d96
    7f4b3c7d0d8a:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f4b3c7d0d90:	89 85 f0 fb ff ff    	mov    %eax,-0x410(%rbp)
    7f4b3c7d0d96:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f4b3c7d0d9c:	c1 e8 10             	shr    $0x10,%eax
    7f4b3c7d0d9f:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d0da4:	8b 8d b8 fe ff ff    	mov    -0x148(%rbp),%ecx
    7f4b3c7d0daa:	c1 e9 10             	shr    $0x10,%ecx
    7f4b3c7d0dad:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0db3:	89 85 e8 fb ff ff    	mov    %eax,-0x418(%rbp)
    7f4b3c7d0db9:	89 8d e0 fb ff ff    	mov    %ecx,-0x420(%rbp)
    7f4b3c7d0dbf:	2b c1                	sub    %ecx,%eax
    7f4b3c7d0dc1:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d0dc6:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7f4b3c7d0dcc:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0dd2:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7f4b3c7d0dd8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7f4b3c7d0dde:	89 8d d8 fb ff ff    	mov    %ecx,-0x428(%rbp)
    7f4b3c7d0de4:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7f4b3c7d0dea:	2b ca                	sub    %edx,%ecx
    7f4b3c7d0dec:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0df2:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d0df5:	0b c8                	or     %eax,%ecx
    7f4b3c7d0df7:	89 8d c8 fb ff ff    	mov    %ecx,-0x438(%rbp)
    7f4b3c7d0dfd:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f4b3c7d0e03:	85 c0                	test   %eax,%eax
    7f4b3c7d0e05:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0e17
    7f4b3c7d0e0b:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f4b3c7d0e11:	89 85 c8 fb ff ff    	mov    %eax,-0x438(%rbp)
    7f4b3c7d0e17:	8b 85 e8 fb ff ff    	mov    -0x418(%rbp),%eax
    7f4b3c7d0e1d:	03 85 e0 fb ff ff    	add    -0x420(%rbp),%eax
    7f4b3c7d0e23:	25 ff ff 00 00       	and    $0xffff,%eax
    7f4b3c7d0e28:	8b 8d d8 fb ff ff    	mov    -0x428(%rbp),%ecx
    7f4b3c7d0e2e:	03 8d d0 fb ff ff    	add    -0x430(%rbp),%ecx
    7f4b3c7d0e34:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7f4b3c7d0e3a:	c1 e0 10             	shl    $0x10,%eax
    7f4b3c7d0e3d:	0b c8                	or     %eax,%ecx
    7f4b3c7d0e3f:	89 8d c0 fb ff ff    	mov    %ecx,-0x440(%rbp)
    7f4b3c7d0e45:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f4b3c7d0e4b:	85 c0                	test   %eax,%eax
    7f4b3c7d0e4d:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0e5f
    7f4b3c7d0e53:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f4b3c7d0e59:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7f4b3c7d0e5f:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7f4b3c7d0e65:	41 23 c6             	and    %r14d,%eax
    7f4b3c7d0e68:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7f4b3c7d0e6e:	ff c1                	inc    %ecx
    7f4b3c7d0e70:	83 e1 3f             	and    $0x3f,%ecx
    7f4b3c7d0e73:	89 8d b8 fb ff ff    	mov    %ecx,-0x448(%rbp)
    7f4b3c7d0e79:	85 c0                	test   %eax,%eax
    7f4b3c7d0e7b:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0e8d
    7f4b3c7d0e81:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7f4b3c7d0e87:	89 85 b8 fb ff ff    	mov    %eax,-0x448(%rbp)
    7f4b3c7d0e8d:	48 8b 85 50 fe ff ff 	mov    -0x1b0(%rbp),%rax
    7f4b3c7d0e94:	48 8b 40 08          	mov    0x8(%rax),%rax
    7f4b3c7d0e98:	8b 00                	mov    (%rax),%eax
    7f4b3c7d0e9a:	8b cb                	mov    %ebx,%ecx
    7f4b3c7d0e9c:	c1 e9 02             	shr    $0x2,%ecx
    7f4b3c7d0e9f:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d0ea2:	85 c9                	test   %ecx,%ecx
    7f4b3c7d0ea4:	0f 94 c1             	sete   %cl
    7f4b3c7d0ea7:	0f b6 c9             	movzbl %cl,%ecx
    7f4b3c7d0eaa:	23 c1                	and    %ecx,%eax
    7f4b3c7d0eac:	8b 8d 30 fe ff ff    	mov    -0x1d0(%rbp),%ecx
    7f4b3c7d0eb2:	23 8d 38 fe ff ff    	and    -0x1c8(%rbp),%ecx
    7f4b3c7d0eb8:	85 c9                	test   %ecx,%ecx
    7f4b3c7d0eba:	0f 94 c2             	sete   %dl
    7f4b3c7d0ebd:	0f b6 d2             	movzbl %dl,%edx
    7f4b3c7d0ec0:	89 95 b0 fb ff ff    	mov    %edx,-0x450(%rbp)
    7f4b3c7d0ec6:	23 d0                	and    %eax,%edx
    7f4b3c7d0ec8:	8b f3                	mov    %ebx,%esi
    7f4b3c7d0eca:	83 e6 03             	and    $0x3,%esi
    7f4b3c7d0ecd:	d1 e6                	shl    %esi
    7f4b3c7d0ecf:	89 b5 a8 fb ff ff    	mov    %esi,-0x458(%rbp)
    7f4b3c7d0ed5:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7f4b3c7d0edb:	85 c0                	test   %eax,%eax
    7f4b3c7d0edd:	0f 94 c0             	sete   %al
    7f4b3c7d0ee0:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d0ee3:	89 8d 98 fb ff ff    	mov    %ecx,-0x468(%rbp)
    7f4b3c7d0ee9:	23 c8                	and    %eax,%ecx
    7f4b3c7d0eeb:	89 8d 90 fb ff ff    	mov    %ecx,-0x470(%rbp)
    7f4b3c7d0ef1:	8b c3                	mov    %ebx,%eax
    7f4b3c7d0ef3:	d1 e8                	shr    %eax
    7f4b3c7d0ef5:	83 e0 03             	and    $0x3,%eax
    7f4b3c7d0ef8:	89 85 88 fb ff ff    	mov    %eax,-0x478(%rbp)
    7f4b3c7d0efe:	85 d2                	test   %edx,%edx
    7f4b3c7d0f00:	0f 85 1b 00 00 00    	jne    0x7f4b3c7d0f21
    7f4b3c7d0f06:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7f4b3c7d0f0c:	85 c0                	test   %eax,%eax
    7f4b3c7d0f0e:	0f 85 1e 00 00 00    	jne    0x7f4b3c7d0f32
    7f4b3c7d0f14:	8b c3                	mov    %ebx,%eax
    7f4b3c7d0f16:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7f4b3c7d0f1c:	e9 1d 00 00 00       	jmpq   0x7f4b3c7d0f3e
    7f4b3c7d0f21:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7f4b3c7d0f27:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7f4b3c7d0f2d:	e9 0c 00 00 00       	jmpq   0x7f4b3c7d0f3e
    7f4b3c7d0f32:	8b 85 88 fb ff ff    	mov    -0x478(%rbp),%eax
    7f4b3c7d0f38:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7f4b3c7d0f3e:	8b c3                	mov    %ebx,%eax
    7f4b3c7d0f40:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d0f43:	8b 8d a0 fb ff ff    	mov    -0x460(%rbp),%ecx
    7f4b3c7d0f49:	23 c1                	and    %ecx,%eax
    7f4b3c7d0f4b:	8b 8d 98 fb ff ff    	mov    -0x468(%rbp),%ecx
    7f4b3c7d0f51:	0b c1                	or     %ecx,%eax
    7f4b3c7d0f53:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7f4b3c7d0f59:	8b c3                	mov    %ebx,%eax
    7f4b3c7d0f5b:	d1 e8                	shr    %eax
    7f4b3c7d0f5d:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d0f60:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7f4b3c7d0f66:	8b 8d b0 fb ff ff    	mov    -0x450(%rbp),%ecx
    7f4b3c7d0f6c:	0b c1                	or     %ecx,%eax
    7f4b3c7d0f6e:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7f4b3c7d0f75:	48 8b 09             	mov    (%rcx),%rcx
    7f4b3c7d0f78:	8b 09                	mov    (%rcx),%ecx
    7f4b3c7d0f7a:	89 8d 68 fb ff ff    	mov    %ecx,-0x498(%rbp)
    7f4b3c7d0f80:	89 8d 60 fb ff ff    	mov    %ecx,-0x4a0(%rbp)
    7f4b3c7d0f86:	85 c0                	test   %eax,%eax
    7f4b3c7d0f88:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0f9a
    7f4b3c7d0f8e:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f4b3c7d0f94:	89 85 60 fb ff ff    	mov    %eax,-0x4a0(%rbp)
    7f4b3c7d0f9a:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7f4b3c7d0fa0:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7f4b3c7d0fa6:	8b 85 78 fb ff ff    	mov    -0x488(%rbp),%eax
    7f4b3c7d0fac:	85 c0                	test   %eax,%eax
    7f4b3c7d0fae:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0fc0
    7f4b3c7d0fb4:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7f4b3c7d0fba:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7f4b3c7d0fc0:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7f4b3c7d0fc6:	23 85 70 fb ff ff    	and    -0x490(%rbp),%eax
    7f4b3c7d0fcc:	8b 8d 98 fb ff ff    	mov    -0x468(%rbp),%ecx
    7f4b3c7d0fd2:	0b c1                	or     %ecx,%eax
    7f4b3c7d0fd4:	8b 8d 68 fb ff ff    	mov    -0x498(%rbp),%ecx
    7f4b3c7d0fda:	89 8d 50 fb ff ff    	mov    %ecx,-0x4b0(%rbp)
    7f4b3c7d0fe0:	85 c0                	test   %eax,%eax
    7f4b3c7d0fe2:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d0ff4
    7f4b3c7d0fe8:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f4b3c7d0fee:	89 85 50 fb ff ff    	mov    %eax,-0x4b0(%rbp)
    7f4b3c7d0ff4:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7f4b3c7d0ffa:	23 85 48 fe ff ff    	and    -0x1b8(%rbp),%eax
    7f4b3c7d1000:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7f4b3c7d1007:	48 8b 49 10          	mov    0x10(%rcx),%rcx
    7f4b3c7d100b:	8b 09                	mov    (%rcx),%ecx
    7f4b3c7d100d:	8b 95 68 fe ff ff    	mov    -0x198(%rbp),%edx
    7f4b3c7d1013:	83 e2 01             	and    $0x1,%edx
    7f4b3c7d1016:	85 d2                	test   %edx,%edx
    7f4b3c7d1018:	0f 94 c2             	sete   %dl
    7f4b3c7d101b:	0f b6 d2             	movzbl %dl,%edx
    7f4b3c7d101e:	23 ca                	and    %edx,%ecx
    7f4b3c7d1020:	85 c9                	test   %ecx,%ecx
    7f4b3c7d1022:	0f 94 c2             	sete   %dl
    7f4b3c7d1025:	0f b6 d2             	movzbl %dl,%edx
    7f4b3c7d1028:	89 95 48 fb ff ff    	mov    %edx,-0x4b8(%rbp)
    7f4b3c7d102e:	23 d0                	and    %eax,%edx
    7f4b3c7d1030:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7f4b3c7d1036:	83 e6 03             	and    $0x3,%esi
    7f4b3c7d1039:	d1 e6                	shl    %esi
    7f4b3c7d103b:	89 b5 40 fb ff ff    	mov    %esi,-0x4c0(%rbp)
    7f4b3c7d1041:	89 85 38 fb ff ff    	mov    %eax,-0x4c8(%rbp)
    7f4b3c7d1047:	85 c0                	test   %eax,%eax
    7f4b3c7d1049:	0f 94 c0             	sete   %al
    7f4b3c7d104c:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d104f:	89 8d 30 fb ff ff    	mov    %ecx,-0x4d0(%rbp)
    7f4b3c7d1055:	23 c8                	and    %eax,%ecx
    7f4b3c7d1057:	89 8d 28 fb ff ff    	mov    %ecx,-0x4d8(%rbp)
    7f4b3c7d105d:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f4b3c7d1063:	d1 e8                	shr    %eax
    7f4b3c7d1065:	83 e0 03             	and    $0x3,%eax
    7f4b3c7d1068:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7f4b3c7d106e:	85 d2                	test   %edx,%edx
    7f4b3c7d1070:	0f 85 1f 00 00 00    	jne    0x7f4b3c7d1095
    7f4b3c7d1076:	8b 85 28 fb ff ff    	mov    -0x4d8(%rbp),%eax
    7f4b3c7d107c:	85 c0                	test   %eax,%eax
    7f4b3c7d107e:	0f 85 22 00 00 00    	jne    0x7f4b3c7d10a6
    7f4b3c7d1084:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f4b3c7d108a:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7f4b3c7d1090:	e9 1d 00 00 00       	jmpq   0x7f4b3c7d10b2
    7f4b3c7d1095:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f4b3c7d109b:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7f4b3c7d10a1:	e9 0c 00 00 00       	jmpq   0x7f4b3c7d10b2
    7f4b3c7d10a6:	8b 85 20 fb ff ff    	mov    -0x4e0(%rbp),%eax
    7f4b3c7d10ac:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7f4b3c7d10b2:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f4b3c7d10b8:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d10bb:	8b 8d 38 fb ff ff    	mov    -0x4c8(%rbp),%ecx
    7f4b3c7d10c1:	23 c1                	and    %ecx,%eax
    7f4b3c7d10c3:	8b 8d 30 fb ff ff    	mov    -0x4d0(%rbp),%ecx
    7f4b3c7d10c9:	0b c1                	or     %ecx,%eax
    7f4b3c7d10cb:	89 85 10 fb ff ff    	mov    %eax,-0x4f0(%rbp)
    7f4b3c7d10d1:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f4b3c7d10d7:	d1 e8                	shr    %eax
    7f4b3c7d10d9:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d10dc:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7f4b3c7d10e2:	8b 8d 48 fb ff ff    	mov    -0x4b8(%rbp),%ecx
    7f4b3c7d10e8:	0b c1                	or     %ecx,%eax
    7f4b3c7d10ea:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7f4b3c7d10f0:	89 8d 00 fb ff ff    	mov    %ecx,-0x500(%rbp)
    7f4b3c7d10f6:	85 c0                	test   %eax,%eax
    7f4b3c7d10f8:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d110a
    7f4b3c7d10fe:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f4b3c7d1104:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7f4b3c7d110a:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7f4b3c7d1110:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f4b3c7d1116:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7f4b3c7d111c:	85 c0                	test   %eax,%eax
    7f4b3c7d111e:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d1130
    7f4b3c7d1124:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f4b3c7d112a:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f4b3c7d1130:	8b 85 38 fb ff ff    	mov    -0x4c8(%rbp),%eax
    7f4b3c7d1136:	23 85 08 fb ff ff    	and    -0x4f8(%rbp),%eax
    7f4b3c7d113c:	8b 8d 30 fb ff ff    	mov    -0x4d0(%rbp),%ecx
    7f4b3c7d1142:	0b c1                	or     %ecx,%eax
    7f4b3c7d1144:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7f4b3c7d114a:	89 8d f0 fa ff ff    	mov    %ecx,-0x510(%rbp)
    7f4b3c7d1150:	85 c0                	test   %eax,%eax
    7f4b3c7d1152:	0f 85 0c 00 00 00    	jne    0x7f4b3c7d1164
    7f4b3c7d1158:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f4b3c7d115e:	89 85 f0 fa ff ff    	mov    %eax,-0x510(%rbp)
    7f4b3c7d1164:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7f4b3c7d116a:	41 89 87 50 04 00 00 	mov    %eax,0x450(%r15)
    7f4b3c7d1171:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7f4b3c7d1177:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7f4b3c7d117d:	41 89 87 48 04 00 00 	mov    %eax,0x448(%r15)
    7f4b3c7d1184:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7f4b3c7d118a:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d118d:	0f 84 1a 00 00 00    	je     0x7f4b3c7d11ad
    7f4b3c7d1193:	41 c7 87 40 04 00 00 	movl   $0x1,0x440(%r15)
    7f4b3c7d119a:	01 00 00 00 
    7f4b3c7d119e:	c7 85 68 fe ff ff 01 	movl   $0x1,-0x198(%rbp)
    7f4b3c7d11a5:	00 00 00 
    7f4b3c7d11a8:	e9 13 00 00 00       	jmpq   0x7f4b3c7d11c0
    7f4b3c7d11ad:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f4b3c7d11b3:	41 89 87 40 04 00 00 	mov    %eax,0x440(%r15)
    7f4b3c7d11ba:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f4b3c7d11c0:	8b 85 50 fb ff ff    	mov    -0x4b0(%rbp),%eax
    7f4b3c7d11c6:	41 89 87 38 04 00 00 	mov    %eax,0x438(%r15)
    7f4b3c7d11cd:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7f4b3c7d11d3:	8b 85 58 fb ff ff    	mov    -0x4a8(%rbp),%eax
    7f4b3c7d11d9:	41 89 87 30 04 00 00 	mov    %eax,0x430(%r15)
    7f4b3c7d11e0:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7f4b3c7d11e6:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d11e9:	0f 84 15 00 00 00    	je     0x7f4b3c7d1204
    7f4b3c7d11ef:	41 c7 87 28 04 00 00 	movl   $0x1,0x428(%r15)
    7f4b3c7d11f6:	01 00 00 00 
    7f4b3c7d11fa:	bb 01 00 00 00       	mov    $0x1,%ebx
    7f4b3c7d11ff:	e9 10 00 00 00       	jmpq   0x7f4b3c7d1214
    7f4b3c7d1204:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7f4b3c7d120a:	41 89 87 28 04 00 00 	mov    %eax,0x428(%r15)
    7f4b3c7d1211:	48 8b d8             	mov    %rax,%rbx
    7f4b3c7d1214:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d1217:	0f 84 1a 00 00 00    	je     0x7f4b3c7d1237
    7f4b3c7d121d:	41 c7 87 20 04 00 00 	movl   $0x0,0x420(%r15)
    7f4b3c7d1224:	00 00 00 00 
    7f4b3c7d1228:	c7 85 80 fe ff ff 00 	movl   $0x0,-0x180(%rbp)
    7f4b3c7d122f:	00 00 00 
    7f4b3c7d1232:	e9 13 00 00 00       	jmpq   0x7f4b3c7d124a
    7f4b3c7d1237:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7f4b3c7d123d:	41 89 87 20 04 00 00 	mov    %eax,0x420(%r15)
    7f4b3c7d1244:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7f4b3c7d124a:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d124d:	0f 84 25 00 00 00    	je     0x7f4b3c7d1278
    7f4b3c7d1253:	41 c7 87 10 04 00 00 	movl   $0x0,0x410(%r15)
    7f4b3c7d125a:	00 00 00 00 
    7f4b3c7d125e:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%rbp)
    7f4b3c7d1265:	00 00 00 
    7f4b3c7d1268:	41 c7 87 18 04 00 00 	movl   $0x0,0x418(%r15)
    7f4b3c7d126f:	00 00 00 00 
    7f4b3c7d1273:	e9 2a 00 00 00       	jmpq   0x7f4b3c7d12a2
    7f4b3c7d1278:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d127b:	0f 84 21 00 00 00    	je     0x7f4b3c7d12a2
    7f4b3c7d1281:	41 8b 87 18 04 00 00 	mov    0x418(%r15),%eax
    7f4b3c7d1288:	41 89 87 10 04 00 00 	mov    %eax,0x410(%r15)
    7f4b3c7d128f:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7f4b3c7d1295:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f4b3c7d129b:	41 89 87 18 04 00 00 	mov    %eax,0x418(%r15)
    7f4b3c7d12a2:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d12a5:	0f 84 26 00 00 00    	je     0x7f4b3c7d12d1
    7f4b3c7d12ab:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f4b3c7d12b1:	41 89 87 08 04 00 00 	mov    %eax,0x408(%r15)
    7f4b3c7d12b8:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f4b3c7d12be:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7f4b3c7d12c4:	41 89 87 00 04 00 00 	mov    %eax,0x400(%r15)
    7f4b3c7d12cb:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f4b3c7d12d1:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d12d4:	0f 84 1a 00 00 00    	je     0x7f4b3c7d12f4
    7f4b3c7d12da:	41 c7 87 f8 03 00 00 	movl   $0x0,0x3f8(%r15)
    7f4b3c7d12e1:	00 00 00 00 
    7f4b3c7d12e5:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7f4b3c7d12ec:	00 00 00 
    7f4b3c7d12ef:	e9 13 00 00 00       	jmpq   0x7f4b3c7d1307
    7f4b3c7d12f4:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7f4b3c7d12fa:	41 89 87 f8 03 00 00 	mov    %eax,0x3f8(%r15)
    7f4b3c7d1301:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f4b3c7d1307:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d130a:	0f 84 1a 00 00 00    	je     0x7f4b3c7d132a
    7f4b3c7d1310:	41 c7 87 f0 03 00 00 	movl   $0x0,0x3f0(%r15)
    7f4b3c7d1317:	00 00 00 00 
    7f4b3c7d131b:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7f4b3c7d1322:	00 00 00 
    7f4b3c7d1325:	e9 1c 00 00 00       	jmpq   0x7f4b3c7d1346
    7f4b3c7d132a:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d132d:	0f 84 13 00 00 00    	je     0x7f4b3c7d1346
    7f4b3c7d1333:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f4b3c7d1339:	41 89 87 f0 03 00 00 	mov    %eax,0x3f0(%r15)
    7f4b3c7d1340:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f4b3c7d1346:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1349:	0f 84 26 00 00 00    	je     0x7f4b3c7d1375
    7f4b3c7d134f:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7f4b3c7d1355:	41 89 87 e8 03 00 00 	mov    %eax,0x3e8(%r15)
    7f4b3c7d135c:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f4b3c7d1362:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7f4b3c7d1368:	41 89 87 e0 03 00 00 	mov    %eax,0x3e0(%r15)
    7f4b3c7d136f:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f4b3c7d1375:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d1378:	0f 84 1a 00 00 00    	je     0x7f4b3c7d1398
    7f4b3c7d137e:	41 c7 87 d8 03 00 00 	movl   $0x0,0x3d8(%r15)
    7f4b3c7d1385:	00 00 00 00 
    7f4b3c7d1389:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7f4b3c7d1390:	00 00 00 
    7f4b3c7d1393:	e9 13 00 00 00       	jmpq   0x7f4b3c7d13ab
    7f4b3c7d1398:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7f4b3c7d139e:	41 89 87 d8 03 00 00 	mov    %eax,0x3d8(%r15)
    7f4b3c7d13a5:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f4b3c7d13ab:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d13ae:	0f 84 25 00 00 00    	je     0x7f4b3c7d13d9
    7f4b3c7d13b4:	41 c7 87 c8 03 00 00 	movl   $0x0,0x3c8(%r15)
    7f4b3c7d13bb:	00 00 00 00 
    7f4b3c7d13bf:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7f4b3c7d13c6:	00 00 00 
    7f4b3c7d13c9:	41 c7 87 d0 03 00 00 	movl   $0x0,0x3d0(%r15)
    7f4b3c7d13d0:	00 00 00 00 
    7f4b3c7d13d4:	e9 35 00 00 00       	jmpq   0x7f4b3c7d140e
    7f4b3c7d13d9:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d13dc:	0f 84 2c 00 00 00    	je     0x7f4b3c7d140e
    7f4b3c7d13e2:	41 8b 87 d0 03 00 00 	mov    0x3d0(%r15),%eax
    7f4b3c7d13e9:	8b c8                	mov    %eax,%ecx
    7f4b3c7d13eb:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d13ee:	41 89 8f c8 03 00 00 	mov    %ecx,0x3c8(%r15)
    7f4b3c7d13f5:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7f4b3c7d13fb:	d1 e8                	shr    %eax
    7f4b3c7d13fd:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7f4b3c7d1403:	d1 e1                	shl    %ecx
    7f4b3c7d1405:	0b c1                	or     %ecx,%eax
    7f4b3c7d1407:	41 89 87 d0 03 00 00 	mov    %eax,0x3d0(%r15)
    7f4b3c7d140e:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1411:	0f 84 34 00 00 00    	je     0x7f4b3c7d144b
    7f4b3c7d1417:	8b 85 08 fc ff ff    	mov    -0x3f8(%rbp),%eax
    7f4b3c7d141d:	41 89 87 c0 03 00 00 	mov    %eax,0x3c0(%r15)
    7f4b3c7d1424:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f4b3c7d142a:	41 8b 87 b8 03 00 00 	mov    0x3b8(%r15),%eax
    7f4b3c7d1431:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7f4b3c7d1438:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f4b3c7d143e:	8b 85 18 fc ff ff    	mov    -0x3e8(%rbp),%eax
    7f4b3c7d1444:	41 89 87 b8 03 00 00 	mov    %eax,0x3b8(%r15)
    7f4b3c7d144b:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d144e:	0f 84 1a 00 00 00    	je     0x7f4b3c7d146e
    7f4b3c7d1454:	41 c7 87 a8 03 00 00 	movl   $0x0,0x3a8(%r15)
    7f4b3c7d145b:	00 00 00 00 
    7f4b3c7d145f:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7f4b3c7d1466:	00 00 00 
    7f4b3c7d1469:	e9 13 00 00 00       	jmpq   0x7f4b3c7d1481
    7f4b3c7d146e:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f4b3c7d1474:	41 89 87 a8 03 00 00 	mov    %eax,0x3a8(%r15)
    7f4b3c7d147b:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f4b3c7d1481:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d1484:	0f 84 25 00 00 00    	je     0x7f4b3c7d14af
    7f4b3c7d148a:	41 c7 87 98 03 00 00 	movl   $0x0,0x398(%r15)
    7f4b3c7d1491:	00 00 00 00 
    7f4b3c7d1495:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7f4b3c7d149c:	00 00 00 
    7f4b3c7d149f:	41 c7 87 a0 03 00 00 	movl   $0x0,0x3a0(%r15)
    7f4b3c7d14a6:	00 00 00 00 
    7f4b3c7d14aa:	e9 36 00 00 00       	jmpq   0x7f4b3c7d14e5
    7f4b3c7d14af:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d14b2:	0f 84 2d 00 00 00    	je     0x7f4b3c7d14e5
    7f4b3c7d14b8:	41 8b 87 a0 03 00 00 	mov    0x3a0(%r15),%eax
    7f4b3c7d14bf:	8b c8                	mov    %eax,%ecx
    7f4b3c7d14c1:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d14c4:	41 89 8f 98 03 00 00 	mov    %ecx,0x398(%r15)
    7f4b3c7d14cb:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7f4b3c7d14d1:	d1 e8                	shr    %eax
    7f4b3c7d14d3:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7f4b3c7d14d9:	c1 e1 04             	shl    $0x4,%ecx
    7f4b3c7d14dc:	0b c1                	or     %ecx,%eax
    7f4b3c7d14de:	41 89 87 a0 03 00 00 	mov    %eax,0x3a0(%r15)
    7f4b3c7d14e5:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d14e8:	0f 84 67 00 00 00    	je     0x7f4b3c7d1555
    7f4b3c7d14ee:	41 8b 87 94 03 00 00 	mov    0x394(%r15),%eax
    7f4b3c7d14f5:	49 8b cf             	mov    %r15,%rcx
    7f4b3c7d14f8:	48 81 c1 84 03 00 00 	add    $0x384,%rcx
    7f4b3c7d14ff:	8b d0                	mov    %eax,%edx
    7f4b3c7d1501:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f4b3c7d1504:	41 89 97 7c 03 00 00 	mov    %edx,0x37c(%r15)
    7f4b3c7d150b:	89 95 f0 fe ff ff    	mov    %edx,-0x110(%rbp)
    7f4b3c7d1511:	8b d0                	mov    %eax,%edx
    7f4b3c7d1513:	8b b5 48 fc ff ff    	mov    -0x3b8(%rbp),%esi
    7f4b3c7d1519:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f4b3c7d151c:	ff c8                	dec    %eax
    7f4b3c7d151e:	b9 03 00 00 00       	mov    $0x3,%ecx
    7f4b3c7d1523:	3b c1                	cmp    %ecx,%eax
    7f4b3c7d1525:	0f 47 c1             	cmova  %ecx,%eax
    7f4b3c7d1528:	41 89 87 94 03 00 00 	mov    %eax,0x394(%r15)
    7f4b3c7d152f:	8b 85 98 fc ff ff    	mov    -0x368(%rbp),%eax
    7f4b3c7d1535:	41 89 87 74 03 00 00 	mov    %eax,0x374(%r15)
    7f4b3c7d153c:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7f4b3c7d1542:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f4b3c7d1548:	41 89 87 6c 03 00 00 	mov    %eax,0x36c(%r15)
    7f4b3c7d154f:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f4b3c7d1555:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d1558:	0f 84 1a 00 00 00    	je     0x7f4b3c7d1578
    7f4b3c7d155e:	41 c7 87 64 03 00 00 	movl   $0x0,0x364(%r15)
    7f4b3c7d1565:	00 00 00 00 
    7f4b3c7d1569:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7f4b3c7d1570:	00 00 00 
    7f4b3c7d1573:	e9 13 00 00 00       	jmpq   0x7f4b3c7d158b
    7f4b3c7d1578:	8b 85 a0 fc ff ff    	mov    -0x360(%rbp),%eax
    7f4b3c7d157e:	41 89 87 64 03 00 00 	mov    %eax,0x364(%r15)
    7f4b3c7d1585:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f4b3c7d158b:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d158e:	0f 84 25 00 00 00    	je     0x7f4b3c7d15b9
    7f4b3c7d1594:	41 c7 87 54 03 00 00 	movl   $0x0,0x354(%r15)
    7f4b3c7d159b:	00 00 00 00 
    7f4b3c7d159f:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7f4b3c7d15a6:	00 00 00 
    7f4b3c7d15a9:	41 c7 87 5c 03 00 00 	movl   $0x0,0x35c(%r15)
    7f4b3c7d15b0:	00 00 00 00 
    7f4b3c7d15b4:	e9 36 00 00 00       	jmpq   0x7f4b3c7d15ef
    7f4b3c7d15b9:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d15bc:	0f 84 2d 00 00 00    	je     0x7f4b3c7d15ef
    7f4b3c7d15c2:	41 8b 87 5c 03 00 00 	mov    0x35c(%r15),%eax
    7f4b3c7d15c9:	8b c8                	mov    %eax,%ecx
    7f4b3c7d15cb:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d15ce:	41 89 8f 54 03 00 00 	mov    %ecx,0x354(%r15)
    7f4b3c7d15d5:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7f4b3c7d15db:	d1 e8                	shr    %eax
    7f4b3c7d15dd:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7f4b3c7d15e3:	c1 e1 03             	shl    $0x3,%ecx
    7f4b3c7d15e6:	0b c1                	or     %ecx,%eax
    7f4b3c7d15e8:	41 89 87 5c 03 00 00 	mov    %eax,0x35c(%r15)
    7f4b3c7d15ef:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d15f2:	0f 84 54 00 00 00    	je     0x7f4b3c7d164c
    7f4b3c7d15f8:	8b 85 a8 fc ff ff    	mov    -0x358(%rbp),%eax
    7f4b3c7d15fe:	41 89 87 4c 03 00 00 	mov    %eax,0x34c(%r15)
    7f4b3c7d1605:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f4b3c7d160b:	41 8b 87 48 03 00 00 	mov    0x348(%r15),%eax
    7f4b3c7d1612:	49 8b cf             	mov    %r15,%rcx
    7f4b3c7d1615:	48 81 c1 38 03 00 00 	add    $0x338,%rcx
    7f4b3c7d161c:	8b d0                	mov    %eax,%edx
    7f4b3c7d161e:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f4b3c7d1621:	41 89 97 30 03 00 00 	mov    %edx,0x330(%r15)
    7f4b3c7d1628:	89 95 20 ff ff ff    	mov    %edx,-0xe0(%rbp)
    7f4b3c7d162e:	8b d0                	mov    %eax,%edx
    7f4b3c7d1630:	8b b5 b8 fc ff ff    	mov    -0x348(%rbp),%esi
    7f4b3c7d1636:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f4b3c7d1639:	ff c8                	dec    %eax
    7f4b3c7d163b:	b9 02 00 00 00       	mov    $0x2,%ecx
    7f4b3c7d1640:	3b c1                	cmp    %ecx,%eax
    7f4b3c7d1642:	0f 47 c1             	cmova  %ecx,%eax
    7f4b3c7d1645:	41 89 87 48 03 00 00 	mov    %eax,0x348(%r15)
    7f4b3c7d164c:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d164f:	0f 84 1a 00 00 00    	je     0x7f4b3c7d166f
    7f4b3c7d1655:	41 c7 87 28 03 00 00 	movl   $0x0,0x328(%r15)
    7f4b3c7d165c:	00 00 00 00 
    7f4b3c7d1660:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7f4b3c7d1667:	00 00 00 
    7f4b3c7d166a:	e9 13 00 00 00       	jmpq   0x7f4b3c7d1682
    7f4b3c7d166f:	8b 85 e0 fc ff ff    	mov    -0x320(%rbp),%eax
    7f4b3c7d1675:	41 89 87 28 03 00 00 	mov    %eax,0x328(%r15)
    7f4b3c7d167c:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f4b3c7d1682:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d1685:	0f 84 1a 00 00 00    	je     0x7f4b3c7d16a5
    7f4b3c7d168b:	41 c7 87 20 03 00 00 	movl   $0x0,0x320(%r15)
    7f4b3c7d1692:	00 00 00 00 
    7f4b3c7d1696:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7f4b3c7d169d:	00 00 00 
    7f4b3c7d16a0:	e9 1c 00 00 00       	jmpq   0x7f4b3c7d16c1
    7f4b3c7d16a5:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d16a8:	0f 84 13 00 00 00    	je     0x7f4b3c7d16c1
    7f4b3c7d16ae:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7f4b3c7d16b4:	41 89 87 20 03 00 00 	mov    %eax,0x320(%r15)
    7f4b3c7d16bb:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f4b3c7d16c1:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d16c4:	0f 84 26 00 00 00    	je     0x7f4b3c7d16f0
    7f4b3c7d16ca:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f4b3c7d16d0:	41 89 87 18 03 00 00 	mov    %eax,0x318(%r15)
    7f4b3c7d16d7:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f4b3c7d16dd:	8b 85 e8 fc ff ff    	mov    -0x318(%rbp),%eax
    7f4b3c7d16e3:	41 89 87 10 03 00 00 	mov    %eax,0x310(%r15)
    7f4b3c7d16ea:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f4b3c7d16f0:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d16f3:	0f 84 1a 00 00 00    	je     0x7f4b3c7d1713
    7f4b3c7d16f9:	41 c7 87 08 03 00 00 	movl   $0x0,0x308(%r15)
    7f4b3c7d1700:	00 00 00 00 
    7f4b3c7d1704:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7f4b3c7d170b:	00 00 00 
    7f4b3c7d170e:	e9 13 00 00 00       	jmpq   0x7f4b3c7d1726
    7f4b3c7d1713:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7f4b3c7d1719:	41 89 87 08 03 00 00 	mov    %eax,0x308(%r15)
    7f4b3c7d1720:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f4b3c7d1726:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d1729:	0f 84 25 00 00 00    	je     0x7f4b3c7d1754
    7f4b3c7d172f:	41 c7 87 f8 02 00 00 	movl   $0x0,0x2f8(%r15)
    7f4b3c7d1736:	00 00 00 00 
    7f4b3c7d173a:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7f4b3c7d1741:	00 00 00 
    7f4b3c7d1744:	41 c7 87 00 03 00 00 	movl   $0x0,0x300(%r15)
    7f4b3c7d174b:	00 00 00 00 
    7f4b3c7d174f:	e9 36 00 00 00       	jmpq   0x7f4b3c7d178a
    7f4b3c7d1754:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1757:	0f 84 2d 00 00 00    	je     0x7f4b3c7d178a
    7f4b3c7d175d:	41 8b 87 00 03 00 00 	mov    0x300(%r15),%eax
    7f4b3c7d1764:	8b c8                	mov    %eax,%ecx
    7f4b3c7d1766:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d1769:	41 89 8f f8 02 00 00 	mov    %ecx,0x2f8(%r15)
    7f4b3c7d1770:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7f4b3c7d1776:	d1 e8                	shr    %eax
    7f4b3c7d1778:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7f4b3c7d177e:	c1 e1 07             	shl    $0x7,%ecx
    7f4b3c7d1781:	0b c1                	or     %ecx,%eax
    7f4b3c7d1783:	41 89 87 00 03 00 00 	mov    %eax,0x300(%r15)
    7f4b3c7d178a:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d178d:	0f 84 54 00 00 00    	je     0x7f4b3c7d17e7
    7f4b3c7d1793:	8b 85 f8 fc ff ff    	mov    -0x308(%rbp),%eax
    7f4b3c7d1799:	41 89 87 f0 02 00 00 	mov    %eax,0x2f0(%r15)
    7f4b3c7d17a0:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f4b3c7d17a6:	41 8b 87 ec 02 00 00 	mov    0x2ec(%r15),%eax
    7f4b3c7d17ad:	49 8b cf             	mov    %r15,%rcx
    7f4b3c7d17b0:	48 81 c1 cc 02 00 00 	add    $0x2cc,%rcx
    7f4b3c7d17b7:	8b d0                	mov    %eax,%edx
    7f4b3c7d17b9:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f4b3c7d17bc:	41 89 97 c4 02 00 00 	mov    %edx,0x2c4(%r15)
    7f4b3c7d17c3:	89 95 60 ff ff ff    	mov    %edx,-0xa0(%rbp)
    7f4b3c7d17c9:	8b d0                	mov    %eax,%edx
    7f4b3c7d17cb:	8b b5 08 fd ff ff    	mov    -0x2f8(%rbp),%esi
    7f4b3c7d17d1:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f4b3c7d17d4:	ff c8                	dec    %eax
    7f4b3c7d17d6:	b9 06 00 00 00       	mov    $0x6,%ecx
    7f4b3c7d17db:	3b c1                	cmp    %ecx,%eax
    7f4b3c7d17dd:	0f 47 c1             	cmova  %ecx,%eax
    7f4b3c7d17e0:	41 89 87 ec 02 00 00 	mov    %eax,0x2ec(%r15)
    7f4b3c7d17e7:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d17ea:	0f 84 1a 00 00 00    	je     0x7f4b3c7d180a
    7f4b3c7d17f0:	41 c7 87 bc 02 00 00 	movl   $0x0,0x2bc(%r15)
    7f4b3c7d17f7:	00 00 00 00 
    7f4b3c7d17fb:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7f4b3c7d1802:	00 00 00 
    7f4b3c7d1805:	e9 13 00 00 00       	jmpq   0x7f4b3c7d181d
    7f4b3c7d180a:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7f4b3c7d1810:	41 89 87 bc 02 00 00 	mov    %eax,0x2bc(%r15)
    7f4b3c7d1817:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f4b3c7d181d:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d1820:	0f 84 25 00 00 00    	je     0x7f4b3c7d184b
    7f4b3c7d1826:	41 c7 87 ac 02 00 00 	movl   $0x0,0x2ac(%r15)
    7f4b3c7d182d:	00 00 00 00 
    7f4b3c7d1831:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7f4b3c7d1838:	00 00 00 
    7f4b3c7d183b:	41 c7 87 b4 02 00 00 	movl   $0x0,0x2b4(%r15)
    7f4b3c7d1842:	00 00 00 00 
    7f4b3c7d1846:	e9 33 00 00 00       	jmpq   0x7f4b3c7d187e
    7f4b3c7d184b:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d184e:	0f 84 2a 00 00 00    	je     0x7f4b3c7d187e
    7f4b3c7d1854:	41 8b 87 b4 02 00 00 	mov    0x2b4(%r15),%eax
    7f4b3c7d185b:	8b c8                	mov    %eax,%ecx
    7f4b3c7d185d:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d1860:	41 89 8f ac 02 00 00 	mov    %ecx,0x2ac(%r15)
    7f4b3c7d1867:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7f4b3c7d186d:	d1 e8                	shr    %eax
    7f4b3c7d186f:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7f4b3c7d1872:	c1 e1 04             	shl    $0x4,%ecx
    7f4b3c7d1875:	0b c1                	or     %ecx,%eax
    7f4b3c7d1877:	41 89 87 b4 02 00 00 	mov    %eax,0x2b4(%r15)
    7f4b3c7d187e:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1881:	0f 84 5e 00 00 00    	je     0x7f4b3c7d18e5
    7f4b3c7d1887:	41 8b 87 a8 02 00 00 	mov    0x2a8(%r15),%eax
    7f4b3c7d188e:	49 8b cf             	mov    %r15,%rcx
    7f4b3c7d1891:	48 81 c1 98 02 00 00 	add    $0x298,%rcx
    7f4b3c7d1898:	8b d0                	mov    %eax,%edx
    7f4b3c7d189a:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f4b3c7d189d:	41 89 97 90 02 00 00 	mov    %edx,0x290(%r15)
    7f4b3c7d18a4:	89 95 78 ff ff ff    	mov    %edx,-0x88(%rbp)
    7f4b3c7d18aa:	8b d0                	mov    %eax,%edx
    7f4b3c7d18ac:	8b b5 38 fd ff ff    	mov    -0x2c8(%rbp),%esi
    7f4b3c7d18b2:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f4b3c7d18b5:	ff c8                	dec    %eax
    7f4b3c7d18b7:	b9 03 00 00 00       	mov    $0x3,%ecx
    7f4b3c7d18bc:	3b c1                	cmp    %ecx,%eax
    7f4b3c7d18be:	0f 47 c1             	cmova  %ecx,%eax
    7f4b3c7d18c1:	41 89 87 a8 02 00 00 	mov    %eax,0x2a8(%r15)
    7f4b3c7d18c8:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7f4b3c7d18ce:	41 89 87 88 02 00 00 	mov    %eax,0x288(%r15)
    7f4b3c7d18d5:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f4b3c7d18d8:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f4b3c7d18db:	41 89 87 80 02 00 00 	mov    %eax,0x280(%r15)
    7f4b3c7d18e2:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f4b3c7d18e5:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d18e8:	0f 84 17 00 00 00    	je     0x7f4b3c7d1905
    7f4b3c7d18ee:	41 c7 87 78 02 00 00 	movl   $0x0,0x278(%r15)
    7f4b3c7d18f5:	00 00 00 00 
    7f4b3c7d18f9:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7f4b3c7d1900:	e9 10 00 00 00       	jmpq   0x7f4b3c7d1915
    7f4b3c7d1905:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f4b3c7d190b:	41 89 87 78 02 00 00 	mov    %eax,0x278(%r15)
    7f4b3c7d1912:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f4b3c7d1915:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d1918:	0f 84 22 00 00 00    	je     0x7f4b3c7d1940
    7f4b3c7d191e:	41 c7 87 68 02 00 00 	movl   $0x0,0x268(%r15)
    7f4b3c7d1925:	00 00 00 00 
    7f4b3c7d1929:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7f4b3c7d1930:	41 c7 87 70 02 00 00 	movl   $0x0,0x270(%r15)
    7f4b3c7d1937:	00 00 00 00 
    7f4b3c7d193b:	e9 30 00 00 00       	jmpq   0x7f4b3c7d1970
    7f4b3c7d1940:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1943:	0f 84 27 00 00 00    	je     0x7f4b3c7d1970
    7f4b3c7d1949:	41 8b 87 70 02 00 00 	mov    0x270(%r15),%eax
    7f4b3c7d1950:	8b c8                	mov    %eax,%ecx
    7f4b3c7d1952:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d1955:	41 89 8f 68 02 00 00 	mov    %ecx,0x268(%r15)
    7f4b3c7d195c:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7f4b3c7d195f:	d1 e8                	shr    %eax
    7f4b3c7d1961:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f4b3c7d1964:	c1 e1 0f             	shl    $0xf,%ecx
    7f4b3c7d1967:	0b c1                	or     %ecx,%eax
    7f4b3c7d1969:	41 89 87 70 02 00 00 	mov    %eax,0x270(%r15)
    7f4b3c7d1970:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1973:	0f 84 4e 00 00 00    	je     0x7f4b3c7d19c7
    7f4b3c7d1979:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7f4b3c7d197f:	41 89 87 60 02 00 00 	mov    %eax,0x260(%r15)
    7f4b3c7d1986:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f4b3c7d1989:	41 8b 87 5c 02 00 00 	mov    0x25c(%r15),%eax
    7f4b3c7d1990:	49 8b cf             	mov    %r15,%rcx
    7f4b3c7d1993:	48 81 c1 1c 02 00 00 	add    $0x21c,%rcx
    7f4b3c7d199a:	8b d0                	mov    %eax,%edx
    7f4b3c7d199c:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f4b3c7d199f:	41 89 97 14 02 00 00 	mov    %edx,0x214(%r15)
    7f4b3c7d19a6:	89 55 a8             	mov    %edx,-0x58(%rbp)
    7f4b3c7d19a9:	8b d0                	mov    %eax,%edx
    7f4b3c7d19ab:	8b b5 a8 fd ff ff    	mov    -0x258(%rbp),%esi
    7f4b3c7d19b1:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f4b3c7d19b4:	ff c8                	dec    %eax
    7f4b3c7d19b6:	b9 0e 00 00 00       	mov    $0xe,%ecx
    7f4b3c7d19bb:	3b c1                	cmp    %ecx,%eax
    7f4b3c7d19bd:	0f 47 c1             	cmova  %ecx,%eax
    7f4b3c7d19c0:	41 89 87 5c 02 00 00 	mov    %eax,0x25c(%r15)
    7f4b3c7d19c7:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d19ca:	0f 84 17 00 00 00    	je     0x7f4b3c7d19e7
    7f4b3c7d19d0:	41 c7 87 0c 02 00 00 	movl   $0x0,0x20c(%r15)
    7f4b3c7d19d7:	00 00 00 00 
    7f4b3c7d19db:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7f4b3c7d19e2:	e9 10 00 00 00       	jmpq   0x7f4b3c7d19f7
    7f4b3c7d19e7:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7f4b3c7d19ed:	41 89 87 0c 02 00 00 	mov    %eax,0x20c(%r15)
    7f4b3c7d19f4:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f4b3c7d19f7:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d19fa:	0f 84 17 00 00 00    	je     0x7f4b3c7d1a17
    7f4b3c7d1a00:	41 c7 87 04 02 00 00 	movl   $0x0,0x204(%r15)
    7f4b3c7d1a07:	00 00 00 00 
    7f4b3c7d1a0b:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7f4b3c7d1a12:	e9 16 00 00 00       	jmpq   0x7f4b3c7d1a2d
    7f4b3c7d1a17:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1a1a:	0f 84 0d 00 00 00    	je     0x7f4b3c7d1a2d
    7f4b3c7d1a20:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f4b3c7d1a23:	41 89 87 04 02 00 00 	mov    %eax,0x204(%r15)
    7f4b3c7d1a2a:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f4b3c7d1a2d:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1a30:	0f 84 1d 00 00 00    	je     0x7f4b3c7d1a53
    7f4b3c7d1a36:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f4b3c7d1a39:	41 89 87 fc 01 00 00 	mov    %eax,0x1fc(%r15)
    7f4b3c7d1a40:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f4b3c7d1a43:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7f4b3c7d1a49:	41 89 87 f4 01 00 00 	mov    %eax,0x1f4(%r15)
    7f4b3c7d1a50:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f4b3c7d1a53:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d1a56:	0f 84 17 00 00 00    	je     0x7f4b3c7d1a73
    7f4b3c7d1a5c:	41 c7 87 ec 01 00 00 	movl   $0x0,0x1ec(%r15)
    7f4b3c7d1a63:	00 00 00 00 
    7f4b3c7d1a67:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7f4b3c7d1a6e:	e9 10 00 00 00       	jmpq   0x7f4b3c7d1a83
    7f4b3c7d1a73:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7f4b3c7d1a79:	41 89 87 ec 01 00 00 	mov    %eax,0x1ec(%r15)
    7f4b3c7d1a80:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f4b3c7d1a83:	45 85 ed             	test   %r13d,%r13d
    7f4b3c7d1a86:	0f 84 22 00 00 00    	je     0x7f4b3c7d1aae
    7f4b3c7d1a8c:	41 c7 87 dc 01 00 00 	movl   $0x0,0x1dc(%r15)
    7f4b3c7d1a93:	00 00 00 00 
    7f4b3c7d1a97:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7f4b3c7d1a9e:	41 c7 87 e4 01 00 00 	movl   $0x0,0x1e4(%r15)
    7f4b3c7d1aa5:	00 00 00 00 
    7f4b3c7d1aa9:	e9 33 00 00 00       	jmpq   0x7f4b3c7d1ae1
    7f4b3c7d1aae:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1ab1:	0f 84 2a 00 00 00    	je     0x7f4b3c7d1ae1
    7f4b3c7d1ab7:	41 8b 87 e4 01 00 00 	mov    0x1e4(%r15),%eax
    7f4b3c7d1abe:	8b c8                	mov    %eax,%ecx
    7f4b3c7d1ac0:	83 e1 01             	and    $0x1,%ecx
    7f4b3c7d1ac3:	41 89 8f dc 01 00 00 	mov    %ecx,0x1dc(%r15)
    7f4b3c7d1aca:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7f4b3c7d1acd:	d1 e8                	shr    %eax
    7f4b3c7d1acf:	8b 8d 28 fe ff ff    	mov    -0x1d8(%rbp),%ecx
    7f4b3c7d1ad5:	c1 e1 1f             	shl    $0x1f,%ecx
    7f4b3c7d1ad8:	0b c1                	or     %ecx,%eax
    7f4b3c7d1ada:	41 89 87 e4 01 00 00 	mov    %eax,0x1e4(%r15)
    7f4b3c7d1ae1:	45 85 f6             	test   %r14d,%r14d
    7f4b3c7d1ae4:	0f 84 4e 00 00 00    	je     0x7f4b3c7d1b38
    7f4b3c7d1aea:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7f4b3c7d1af0:	41 89 87 d4 01 00 00 	mov    %eax,0x1d4(%r15)
    7f4b3c7d1af7:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f4b3c7d1afa:	41 8b 87 d0 01 00 00 	mov    0x1d0(%r15),%eax
    7f4b3c7d1b01:	49 8b cf             	mov    %r15,%rcx
    7f4b3c7d1b04:	48 81 c1 50 01 00 00 	add    $0x150,%rcx
    7f4b3c7d1b0b:	8b d0                	mov    %eax,%edx
    7f4b3c7d1b0d:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7f4b3c7d1b10:	41 89 97 48 01 00 00 	mov    %edx,0x148(%r15)
    7f4b3c7d1b17:	89 55 e8             	mov    %edx,-0x18(%rbp)
    7f4b3c7d1b1a:	8b d0                	mov    %eax,%edx
    7f4b3c7d1b1c:	8b b5 f8 fd ff ff    	mov    -0x208(%rbp),%esi
    7f4b3c7d1b22:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7f4b3c7d1b25:	ff c8                	dec    %eax
    7f4b3c7d1b27:	b9 1e 00 00 00       	mov    $0x1e,%ecx
    7f4b3c7d1b2c:	3b c1                	cmp    %ecx,%eax
    7f4b3c7d1b2e:	0f 47 c1             	cmova  %ecx,%eax
    7f4b3c7d1b31:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7f4b3c7d1b38:	45 85 e4             	test   %r12d,%r12d
    7f4b3c7d1b3b:	0f 84 17 00 00 00    	je     0x7f4b3c7d1b58
    7f4b3c7d1b41:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7f4b3c7d1b48:	00 00 00 00 
    7f4b3c7d1b4c:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7f4b3c7d1b53:	e9 10 00 00 00       	jmpq   0x7f4b3c7d1b68
    7f4b3c7d1b58:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f4b3c7d1b5e:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7f4b3c7d1b65:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f4b3c7d1b68:	8b c3                	mov    %ebx,%eax
    7f4b3c7d1b6a:	c1 e8 02             	shr    $0x2,%eax
    7f4b3c7d1b6d:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d1b70:	85 c0                	test   %eax,%eax
    7f4b3c7d1b72:	0f 94 c0             	sete   %al
    7f4b3c7d1b75:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d1b78:	48 8b 95 50 fe ff ff 	mov    -0x1b0(%rbp),%rdx
    7f4b3c7d1b7f:	48 8b 4a 28          	mov    0x28(%rdx),%rcx
    7f4b3c7d1b83:	89 01                	mov    %eax,(%rcx)
    7f4b3c7d1b85:	48 8b 42 30          	mov    0x30(%rdx),%rax
    7f4b3c7d1b89:	8b 8d 60 fe ff ff    	mov    -0x1a0(%rbp),%ecx
    7f4b3c7d1b8f:	89 08                	mov    %ecx,(%rax)
    7f4b3c7d1b91:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f4b3c7d1b97:	83 e0 01             	and    $0x1,%eax
    7f4b3c7d1b9a:	85 c0                	test   %eax,%eax
    7f4b3c7d1b9c:	0f 94 c0             	sete   %al
    7f4b3c7d1b9f:	0f b6 c0             	movzbl %al,%eax
    7f4b3c7d1ba2:	48 8b 52 38          	mov    0x38(%rdx),%rdx
    7f4b3c7d1ba6:	89 02                	mov    %eax,(%rdx)
    7f4b3c7d1ba8:	33 c0                	xor    %eax,%eax
    7f4b3c7d1baa:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f4b3c7d1bae:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f4b3c7d1bb3:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f4b3c7d1bb8:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f4b3c7d1bbd:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f4b3c7d1bc2:	48 8b e5             	mov    %rbp,%rsp
    7f4b3c7d1bc5:	5d                   	pop    %rbp
    7f4b3c7d1bc6:	c3                   	retq   

end

