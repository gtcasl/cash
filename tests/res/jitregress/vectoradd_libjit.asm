function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f8535d0b12d <.text>:
    7f8535d0b12d:	55                   	push   %rbp
    7f8535d0b12e:	48 8b ec             	mov    %rsp,%rbp
    7f8535d0b131:	48 81 ec 40 06 00 00 	sub    $0x640,%rsp
    7f8535d0b138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f8535d0b13c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f8535d0b141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f8535d0b146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f8535d0b14b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f8535d0b150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f8535d0b154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f8535d0b158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f8535d0b15c:	4c 8b 30             	mov    (%rax),%r14
    7f8535d0b15f:	45 8b af c0 0c 00 00 	mov    0xcc0(%r15),%r13d
    7f8535d0b166:	41 8b 87 c8 0c 00 00 	mov    0xcc8(%r15),%eax
    7f8535d0b16d:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f8535d0b170:	41 8b 87 d0 0c 00 00 	mov    0xcd0(%r15),%eax
    7f8535d0b177:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f8535d0b17a:	41 8b 87 e0 0c 00 00 	mov    0xce0(%r15),%eax
    7f8535d0b181:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f8535d0b184:	49 8b 87 f0 0c 00 00 	mov    0xcf0(%r15),%rax
    7f8535d0b18b:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    7f8535d0b18f:	41 8b 87 f8 0c 00 00 	mov    0xcf8(%r15),%eax
    7f8535d0b196:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f8535d0b199:	41 8b 87 00 0d 00 00 	mov    0xd00(%r15),%eax
    7f8535d0b1a0:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f8535d0b1a3:	41 8b 87 08 0d 00 00 	mov    0xd08(%r15),%eax
    7f8535d0b1aa:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f8535d0b1ad:	41 8b 87 10 0d 00 00 	mov    0xd10(%r15),%eax
    7f8535d0b1b4:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f8535d0b1b7:	41 8b 87 58 0d 00 00 	mov    0xd58(%r15),%eax
    7f8535d0b1be:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f8535d0b1c1:	41 8b 87 60 0d 00 00 	mov    0xd60(%r15),%eax
    7f8535d0b1c8:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f8535d0b1cb:	41 8b 87 68 0d 00 00 	mov    0xd68(%r15),%eax
    7f8535d0b1d2:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f8535d0b1d5:	41 8b 87 70 0d 00 00 	mov    0xd70(%r15),%eax
    7f8535d0b1dc:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f8535d0b1df:	41 8b 87 78 0d 00 00 	mov    0xd78(%r15),%eax
    7f8535d0b1e6:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f8535d0b1e9:	41 8b 87 80 0d 00 00 	mov    0xd80(%r15),%eax
    7f8535d0b1f0:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f8535d0b1f3:	41 8b 87 88 0d 00 00 	mov    0xd88(%r15),%eax
    7f8535d0b1fa:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f8535d0b1fd:	41 8b 87 90 0d 00 00 	mov    0xd90(%r15),%eax
    7f8535d0b204:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f8535d0b20a:	41 8b 87 98 0d 00 00 	mov    0xd98(%r15),%eax
    7f8535d0b211:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f8535d0b217:	49 8b 87 20 0e 00 00 	mov    0xe20(%r15),%rax
    7f8535d0b21e:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
    7f8535d0b225:	41 8b 87 28 0e 00 00 	mov    0xe28(%r15),%eax
    7f8535d0b22c:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f8535d0b232:	41 8b 87 30 0e 00 00 	mov    0xe30(%r15),%eax
    7f8535d0b239:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f8535d0b23f:	41 8b 87 38 0e 00 00 	mov    0xe38(%r15),%eax
    7f8535d0b246:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f8535d0b24c:	41 8b 87 40 0e 00 00 	mov    0xe40(%r15),%eax
    7f8535d0b253:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f8535d0b259:	41 8b 87 88 0e 00 00 	mov    0xe88(%r15),%eax
    7f8535d0b260:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f8535d0b266:	41 8b 87 90 0e 00 00 	mov    0xe90(%r15),%eax
    7f8535d0b26d:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f8535d0b273:	41 8b 87 98 0e 00 00 	mov    0xe98(%r15),%eax
    7f8535d0b27a:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f8535d0b280:	41 8b 87 a0 0e 00 00 	mov    0xea0(%r15),%eax
    7f8535d0b287:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f8535d0b28d:	41 8b 87 a8 0e 00 00 	mov    0xea8(%r15),%eax
    7f8535d0b294:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f8535d0b29a:	41 8b 87 b0 0e 00 00 	mov    0xeb0(%r15),%eax
    7f8535d0b2a1:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f8535d0b2a7:	41 8b 87 b8 0e 00 00 	mov    0xeb8(%r15),%eax
    7f8535d0b2ae:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f8535d0b2b4:	41 8b 87 c0 0e 00 00 	mov    0xec0(%r15),%eax
    7f8535d0b2bb:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f8535d0b2c1:	41 8b 87 c8 0e 00 00 	mov    0xec8(%r15),%eax
    7f8535d0b2c8:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f8535d0b2ce:	49 8b 87 50 0f 00 00 	mov    0xf50(%r15),%rax
    7f8535d0b2d5:	48 89 85 f8 fe ff ff 	mov    %rax,-0x108(%rbp)
    7f8535d0b2dc:	41 8b 87 58 0f 00 00 	mov    0xf58(%r15),%eax
    7f8535d0b2e3:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f8535d0b2e9:	41 8b 87 60 0f 00 00 	mov    0xf60(%r15),%eax
    7f8535d0b2f0:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f8535d0b2f6:	41 8b 87 68 0f 00 00 	mov    0xf68(%r15),%eax
    7f8535d0b2fd:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f8535d0b303:	41 8b 87 70 0f 00 00 	mov    0xf70(%r15),%eax
    7f8535d0b30a:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f8535d0b310:	41 8b 87 b8 0f 00 00 	mov    0xfb8(%r15),%eax
    7f8535d0b317:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f8535d0b31d:	41 8b 87 c0 0f 00 00 	mov    0xfc0(%r15),%eax
    7f8535d0b324:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f8535d0b32a:	41 8b 87 c8 0f 00 00 	mov    0xfc8(%r15),%eax
    7f8535d0b331:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f8535d0b337:	41 8b 9f d0 0f 00 00 	mov    0xfd0(%r15),%ebx
    7f8535d0b33e:	41 8b 87 d8 0f 00 00 	mov    0xfd8(%r15),%eax
    7f8535d0b345:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f8535d0b34b:	41 8b 87 e0 0f 00 00 	mov    0xfe0(%r15),%eax
    7f8535d0b352:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f8535d0b358:	41 8b 87 e8 0f 00 00 	mov    0xfe8(%r15),%eax
    7f8535d0b35f:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f8535d0b365:	41 8b 87 f0 0f 00 00 	mov    0xff0(%r15),%eax
    7f8535d0b36c:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f8535d0b372:	41 8b 87 f8 0f 00 00 	mov    0xff8(%r15),%eax
    7f8535d0b379:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f8535d0b37f:	41 8b 87 00 10 00 00 	mov    0x1000(%r15),%eax
    7f8535d0b386:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f8535d0b38c:	49 8b 86 90 00 00 00 	mov    0x90(%r14),%rax
    7f8535d0b393:	8b 00                	mov    (%rax),%eax
    7f8535d0b395:	41 8b 8f 48 13 00 00 	mov    0x1348(%r15),%ecx
    7f8535d0b39c:	33 c8                	xor    %eax,%ecx
    7f8535d0b39e:	23 c8                	and    %eax,%ecx
    7f8535d0b3a0:	41 89 87 48 13 00 00 	mov    %eax,0x1348(%r15)
    7f8535d0b3a7:	85 c9                	test   %ecx,%ecx
    7f8535d0b3a9:	0f 84 5f 22 00 00    	je     0x7f8535d0d60e
    7f8535d0b3af:	49 8b 46 20          	mov    0x20(%r14),%rax
    7f8535d0b3b3:	8b 00                	mov    (%rax),%eax
    7f8535d0b3b5:	c7 85 88 fe ff ff 01 	movl   $0x1,-0x178(%rbp)
    7f8535d0b3bc:	00 00 00 
    7f8535d0b3bf:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7f8535d0b3c5:	85 c0                	test   %eax,%eax
    7f8535d0b3c7:	0f 85 09 00 00 00    	jne    0x7f8535d0b3d6
    7f8535d0b3cd:	41 8b c5             	mov    %r13d,%eax
    7f8535d0b3d0:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7f8535d0b3d6:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f8535d0b3d9:	85 c0                	test   %eax,%eax
    7f8535d0b3db:	0f 94 c0             	sete   %al
    7f8535d0b3de:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b3e1:	c7 85 78 fe ff ff 02 	movl   $0x2,-0x188(%rbp)
    7f8535d0b3e8:	00 00 00 
    7f8535d0b3eb:	85 c0                	test   %eax,%eax
    7f8535d0b3ed:	0f 85 09 00 00 00    	jne    0x7f8535d0b3fc
    7f8535d0b3f3:	41 8b c5             	mov    %r13d,%eax
    7f8535d0b3f6:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7f8535d0b3fc:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7f8535d0b402:	85 c0                	test   %eax,%eax
    7f8535d0b404:	0f 94 c0             	sete   %al
    7f8535d0b407:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b40a:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7f8535d0b40e:	8b 09                	mov    (%rcx),%ecx
    7f8535d0b410:	23 c1                	and    %ecx,%eax
    7f8535d0b412:	c7 85 70 fe ff ff 00 	movl   $0x0,-0x190(%rbp)
    7f8535d0b419:	00 00 00 
    7f8535d0b41c:	85 c0                	test   %eax,%eax
    7f8535d0b41e:	0f 85 09 00 00 00    	jne    0x7f8535d0b42d
    7f8535d0b424:	41 8b c5             	mov    %r13d,%eax
    7f8535d0b427:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7f8535d0b42d:	45 85 ed             	test   %r13d,%r13d
    7f8535d0b430:	0f 84 22 00 00 00    	je     0x7f8535d0b458
    7f8535d0b436:	41 83 fd 01          	cmp    $0x1,%r13d
    7f8535d0b43a:	0f 84 29 00 00 00    	je     0x7f8535d0b469
    7f8535d0b440:	41 83 fd 02          	cmp    $0x2,%r13d
    7f8535d0b444:	0f 84 30 00 00 00    	je     0x7f8535d0b47a
    7f8535d0b44a:	41 8b c5             	mov    %r13d,%eax
    7f8535d0b44d:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f8535d0b453:	e9 2e 00 00 00       	jmpq   0x7f8535d0b486
    7f8535d0b458:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7f8535d0b45e:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f8535d0b464:	e9 1d 00 00 00       	jmpq   0x7f8535d0b486
    7f8535d0b469:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7f8535d0b46f:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f8535d0b475:	e9 0c 00 00 00       	jmpq   0x7f8535d0b486
    7f8535d0b47a:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f8535d0b480:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f8535d0b486:	49 8b 86 98 00 00 00 	mov    0x98(%r14),%rax
    7f8535d0b48d:	44 8b 20             	mov    (%rax),%r12d
    7f8535d0b490:	45 85 ed             	test   %r13d,%r13d
    7f8535d0b493:	0f 94 c0             	sete   %al
    7f8535d0b496:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b499:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7f8535d0b49f:	23 c1                	and    %ecx,%eax
    7f8535d0b4a1:	49 8b 4e 18          	mov    0x18(%r14),%rcx
    7f8535d0b4a5:	8b 09                	mov    (%rcx),%ecx
    7f8535d0b4a7:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7f8535d0b4ad:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f8535d0b4b3:	85 c9                	test   %ecx,%ecx
    7f8535d0b4b5:	0f 94 c1             	sete   %cl
    7f8535d0b4b8:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0b4bb:	8b 95 b0 fe ff ff    	mov    -0x150(%rbp),%edx
    7f8535d0b4c1:	85 d2                	test   %edx,%edx
    7f8535d0b4c3:	0f 94 c2             	sete   %dl
    7f8535d0b4c6:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0b4c9:	89 95 58 fe ff ff    	mov    %edx,-0x1a8(%rbp)
    7f8535d0b4cf:	0b ca                	or     %edx,%ecx
    7f8535d0b4d1:	89 8d 50 fe ff ff    	mov    %ecx,-0x1b0(%rbp)
    7f8535d0b4d7:	23 4d e0             	and    -0x20(%rbp),%ecx
    7f8535d0b4da:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7f8535d0b4e0:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7f8535d0b4e3:	ff c9                	dec    %ecx
    7f8535d0b4e5:	89 8d 40 fe ff ff    	mov    %ecx,-0x1c0(%rbp)
    7f8535d0b4eb:	89 85 38 fe ff ff    	mov    %eax,-0x1c8(%rbp)
    7f8535d0b4f1:	85 c0                	test   %eax,%eax
    7f8535d0b4f3:	0f 85 1c 00 00 00    	jne    0x7f8535d0b515
    7f8535d0b4f9:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f8535d0b4ff:	85 c0                	test   %eax,%eax
    7f8535d0b501:	0f 85 1f 00 00 00    	jne    0x7f8535d0b526
    7f8535d0b507:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f8535d0b50a:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7f8535d0b510:	e9 1d 00 00 00       	jmpq   0x7f8535d0b532
    7f8535d0b515:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f8535d0b51b:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7f8535d0b521:	e9 0c 00 00 00       	jmpq   0x7f8535d0b532
    7f8535d0b526:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7f8535d0b52c:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7f8535d0b532:	41 8b 87 18 0d 00 00 	mov    0xd18(%r15),%eax
    7f8535d0b539:	41 8b 8f 48 0e 00 00 	mov    0xe48(%r15),%ecx
    7f8535d0b540:	03 c1                	add    %ecx,%eax
    7f8535d0b542:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7f8535d0b548:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f8535d0b54b:	85 c0                	test   %eax,%eax
    7f8535d0b54d:	0f 94 c0             	sete   %al
    7f8535d0b550:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b553:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7f8535d0b559:	0b c1                	or     %ecx,%eax
    7f8535d0b55b:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7f8535d0b561:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f8535d0b564:	23 85 40 ff ff ff    	and    -0xc0(%rbp),%eax
    7f8535d0b56a:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%rbp)
    7f8535d0b570:	49 8b 46 08          	mov    0x8(%r14),%rax
    7f8535d0b574:	48 8b 00             	mov    (%rax),%rax
    7f8535d0b577:	48 89 85 10 fe ff ff 	mov    %rax,-0x1f0(%rbp)
    7f8535d0b57e:	49 8b 46 60          	mov    0x60(%r14),%rax
    7f8535d0b582:	8b 00                	mov    (%rax),%eax
    7f8535d0b584:	85 c0                	test   %eax,%eax
    7f8535d0b586:	0f 94 c0             	sete   %al
    7f8535d0b589:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b58c:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f8535d0b58f:	23 c1                	and    %ecx,%eax
    7f8535d0b591:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7f8535d0b597:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f8535d0b59a:	8b c0                	mov    %eax,%eax
    7f8535d0b59c:	48 c1 e0 06          	shl    $0x6,%rax
    7f8535d0b5a0:	48 89 85 00 fe ff ff 	mov    %rax,-0x200(%rbp)
    7f8535d0b5a7:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
    7f8535d0b5ab:	48 03 c1             	add    %rcx,%rax
    7f8535d0b5ae:	48 89 85 f8 fd ff ff 	mov    %rax,-0x208(%rbp)
    7f8535d0b5b5:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0b5bb:	85 c0                	test   %eax,%eax
    7f8535d0b5bd:	0f 85 1e 00 00 00    	jne    0x7f8535d0b5e1
    7f8535d0b5c3:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f8535d0b5c9:	85 c0                	test   %eax,%eax
    7f8535d0b5cb:	0f 85 23 00 00 00    	jne    0x7f8535d0b5f4
    7f8535d0b5d1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    7f8535d0b5d5:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7f8535d0b5dc:	e9 21 00 00 00       	jmpq   0x7f8535d0b602
    7f8535d0b5e1:	48 8b 85 10 fe ff ff 	mov    -0x1f0(%rbp),%rax
    7f8535d0b5e8:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7f8535d0b5ef:	e9 0e 00 00 00       	jmpq   0x7f8535d0b602
    7f8535d0b5f4:	48 8b 85 f8 fd ff ff 	mov    -0x208(%rbp),%rax
    7f8535d0b5fb:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7f8535d0b602:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f8535d0b605:	85 c0                	test   %eax,%eax
    7f8535d0b607:	0f 94 c0             	sete   %al
    7f8535d0b60a:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b60d:	8b 55 b0             	mov    -0x50(%rbp),%edx
    7f8535d0b610:	85 d2                	test   %edx,%edx
    7f8535d0b612:	0f 94 c1             	sete   %cl
    7f8535d0b615:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0b618:	8b 75 a8             	mov    -0x58(%rbp),%esi
    7f8535d0b61b:	83 fe 0f             	cmp    $0xf,%esi
    7f8535d0b61e:	40 0f 94 c6          	sete   %sil
    7f8535d0b622:	40 0f b6 f6          	movzbl %sil,%esi
    7f8535d0b626:	8b bd 40 ff ff ff    	mov    -0xc0(%rbp),%edi
    7f8535d0b62c:	85 ff                	test   %edi,%edi
    7f8535d0b62e:	40 0f 94 c7          	sete   %dil
    7f8535d0b632:	40 0f b6 ff          	movzbl %dil,%edi
    7f8535d0b636:	23 d7                	and    %edi,%edx
    7f8535d0b638:	85 d2                	test   %edx,%edx
    7f8535d0b63a:	0f 94 c2             	sete   %dl
    7f8535d0b63d:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0b640:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7f8535d0b646:	23 d7                	and    %edi,%edx
    7f8535d0b648:	89 95 e8 fd ff ff    	mov    %edx,-0x218(%rbp)
    7f8535d0b64e:	23 f2                	and    %edx,%esi
    7f8535d0b650:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7f8535d0b656:	89 b5 d8 fd ff ff    	mov    %esi,-0x228(%rbp)
    7f8535d0b65c:	0b ce                	or     %esi,%ecx
    7f8535d0b65e:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7f8535d0b664:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7f8535d0b66a:	23 c1                	and    %ecx,%eax
    7f8535d0b66c:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7f8535d0b66f:	03 4d b8             	add    -0x48(%rbp),%ecx
    7f8535d0b672:	83 e1 1f             	and    $0x1f,%ecx
    7f8535d0b675:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7f8535d0b67b:	ff c9                	dec    %ecx
    7f8535d0b67d:	83 e1 1f             	and    $0x1f,%ecx
    7f8535d0b680:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7f8535d0b686:	89 85 b0 fd ff ff    	mov    %eax,-0x250(%rbp)
    7f8535d0b68c:	85 c0                	test   %eax,%eax
    7f8535d0b68e:	0f 85 0c 00 00 00    	jne    0x7f8535d0b6a0
    7f8535d0b694:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7f8535d0b69a:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7f8535d0b6a0:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f8535d0b6a3:	ff c8                	dec    %eax
    7f8535d0b6a5:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0b6a8:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7f8535d0b6ae:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f8535d0b6b4:	85 c0                	test   %eax,%eax
    7f8535d0b6b6:	0f 85 09 00 00 00    	jne    0x7f8535d0b6c5
    7f8535d0b6bc:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f8535d0b6bf:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7f8535d0b6c5:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0b6cb:	85 c0                	test   %eax,%eax
    7f8535d0b6cd:	0f 85 1f 00 00 00    	jne    0x7f8535d0b6f2
    7f8535d0b6d3:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f8535d0b6d9:	85 c0                	test   %eax,%eax
    7f8535d0b6db:	0f 85 20 00 00 00    	jne    0x7f8535d0b701
    7f8535d0b6e1:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7f8535d0b6e7:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7f8535d0b6ed:	e9 1b 00 00 00       	jmpq   0x7f8535d0b70d
    7f8535d0b6f2:	c7 85 a0 fd ff ff 00 	movl   $0x0,-0x260(%rbp)
    7f8535d0b6f9:	00 00 00 
    7f8535d0b6fc:	e9 0c 00 00 00       	jmpq   0x7f8535d0b70d
    7f8535d0b701:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7f8535d0b707:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7f8535d0b70d:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f8535d0b713:	c1 e0 05             	shl    $0x5,%eax
    7f8535d0b716:	05 ff 01 00 00       	add    $0x1ff,%eax
    7f8535d0b71b:	c1 e8 09             	shr    $0x9,%eax
    7f8535d0b71e:	89 85 98 fd ff ff    	mov    %eax,-0x268(%rbp)
    7f8535d0b724:	83 c0 10             	add    $0x10,%eax
    7f8535d0b727:	ff c8                	dec    %eax
    7f8535d0b729:	c1 e8 04             	shr    $0x4,%eax
    7f8535d0b72c:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7f8535d0b732:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f8535d0b735:	ff c8                	dec    %eax
    7f8535d0b737:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7f8535d0b73c:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7f8535d0b742:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0b748:	85 c0                	test   %eax,%eax
    7f8535d0b74a:	0f 85 1c 00 00 00    	jne    0x7f8535d0b76c
    7f8535d0b750:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f8535d0b756:	85 c0                	test   %eax,%eax
    7f8535d0b758:	0f 85 1f 00 00 00    	jne    0x7f8535d0b77d
    7f8535d0b75e:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f8535d0b761:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f8535d0b767:	e9 1d 00 00 00       	jmpq   0x7f8535d0b789
    7f8535d0b76c:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f8535d0b772:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f8535d0b778:	e9 0c 00 00 00       	jmpq   0x7f8535d0b789
    7f8535d0b77d:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7f8535d0b783:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f8535d0b789:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7f8535d0b78f:	85 c0                	test   %eax,%eax
    7f8535d0b791:	0f 95 c0             	setne  %al
    7f8535d0b794:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b797:	83 e0 01             	and    $0x1,%eax
    7f8535d0b79a:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7f8535d0b7a0:	b8 01 00 00 00       	mov    $0x1,%eax
    7f8535d0b7a5:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7f8535d0b7a8:	3b c1                	cmp    %ecx,%eax
    7f8535d0b7aa:	0f 94 c0             	sete   %al
    7f8535d0b7ad:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b7b0:	8b 95 08 fe ff ff    	mov    -0x1f8(%rbp),%edx
    7f8535d0b7b6:	23 c2                	and    %edx,%eax
    7f8535d0b7b8:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7f8535d0b7be:	85 c9                	test   %ecx,%ecx
    7f8535d0b7c0:	0f 95 c0             	setne  %al
    7f8535d0b7c3:	0f b6 c0             	movzbl %al,%eax
    7f8535d0b7c6:	83 e0 01             	and    $0x1,%eax
    7f8535d0b7c9:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7f8535d0b7cf:	83 f9 00             	cmp    $0x0,%ecx
    7f8535d0b7d2:	0f 96 c1             	setbe  %cl
    7f8535d0b7d5:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0b7d8:	23 c1                	and    %ecx,%eax
    7f8535d0b7da:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7f8535d0b7e0:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0b7e6:	85 c0                	test   %eax,%eax
    7f8535d0b7e8:	0f 85 1f 00 00 00    	jne    0x7f8535d0b80d
    7f8535d0b7ee:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7f8535d0b7f4:	85 c0                	test   %eax,%eax
    7f8535d0b7f6:	0f 85 22 00 00 00    	jne    0x7f8535d0b81e
    7f8535d0b7fc:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7f8535d0b802:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f8535d0b808:	e9 1b 00 00 00       	jmpq   0x7f8535d0b828
    7f8535d0b80d:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7f8535d0b813:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f8535d0b819:	e9 0a 00 00 00       	jmpq   0x7f8535d0b828
    7f8535d0b81e:	c7 85 60 fd ff ff 00 	movl   $0x0,-0x2a0(%rbp)
    7f8535d0b825:	00 00 00 
    7f8535d0b828:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7f8535d0b82e:	ff c8                	dec    %eax
    7f8535d0b830:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0b833:	83 e0 0f             	and    $0xf,%eax
    7f8535d0b836:	ff c0                	inc    %eax
    7f8535d0b838:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0b83b:	89 85 58 fd ff ff    	mov    %eax,-0x2a8(%rbp)
    7f8535d0b841:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0b847:	85 c0                	test   %eax,%eax
    7f8535d0b849:	0f 85 1c 00 00 00    	jne    0x7f8535d0b86b
    7f8535d0b84f:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f8535d0b855:	85 c0                	test   %eax,%eax
    7f8535d0b857:	0f 85 1f 00 00 00    	jne    0x7f8535d0b87c
    7f8535d0b85d:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f8535d0b860:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7f8535d0b866:	e9 1b 00 00 00       	jmpq   0x7f8535d0b886
    7f8535d0b86b:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7f8535d0b871:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7f8535d0b877:	e9 0a 00 00 00       	jmpq   0x7f8535d0b886
    7f8535d0b87c:	c7 85 50 fd ff ff 10 	movl   $0x10,-0x2b0(%rbp)
    7f8535d0b883:	00 00 00 
    7f8535d0b886:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f8535d0b88c:	85 c0                	test   %eax,%eax
    7f8535d0b88e:	0f 85 36 00 00 00    	jne    0x7f8535d0b8ca
    7f8535d0b894:	49 8b c7             	mov    %r15,%rax
    7f8535d0b897:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7f8535d0b89d:	49 8b cf             	mov    %r15,%rcx
    7f8535d0b8a0:	48 81 c1 e0 0d 00 00 	add    $0xde0,%rcx
    7f8535d0b8a7:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0b8aa:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0b8ad:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0b8b1:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0b8b5:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0b8b9:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0b8bd:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0b8c1:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0b8c5:	e9 31 00 00 00       	jmpq   0x7f8535d0b8fb
    7f8535d0b8ca:	49 8b c7             	mov    %r15,%rax
    7f8535d0b8cd:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7f8535d0b8d3:	49 8b cf             	mov    %r15,%rcx
    7f8535d0b8d6:	48 81 c1 a0 0d 00 00 	add    $0xda0,%rcx
    7f8535d0b8dd:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0b8e0:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0b8e3:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0b8e7:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0b8eb:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0b8ef:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0b8f3:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0b8f7:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0b8fb:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f8535d0b8fe:	23 85 e8 fd ff ff    	and    -0x218(%rbp),%eax
    7f8535d0b904:	89 85 48 fd ff ff    	mov    %eax,-0x2b8(%rbp)
    7f8535d0b90a:	49 8b c7             	mov    %r15,%rax
    7f8535d0b90d:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7f8535d0b913:	49 8b cf             	mov    %r15,%rcx
    7f8535d0b916:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7f8535d0b91d:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7f8535d0b923:	48 89 8d 40 fd ff ff 	mov    %rcx,-0x2c0(%rbp)
    7f8535d0b92a:	b9 00 02 00 00       	mov    $0x200,%ecx
    7f8535d0b92f:	48 8b d0             	mov    %rax,%rdx
    7f8535d0b932:	be 00 02 00 00       	mov    $0x200,%esi
    7f8535d0b937:	48 8b bd 40 fd ff ff 	mov    -0x2c0(%rbp),%rdi
    7f8535d0b93e:	48 89 85 38 fd ff ff 	mov    %rax,-0x2c8(%rbp)
    7f8535d0b945:	b8 08 00 00 00       	mov    $0x8,%eax
    7f8535d0b94a:	e8 11 a1 b3 ff       	callq  0x7f8535845a60
    7f8535d0b94f:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f8535d0b955:	85 c0                	test   %eax,%eax
    7f8535d0b957:	0f 85 44 00 00 00    	jne    0x7f8535d0b9a1
    7f8535d0b95d:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7f8535d0b963:	85 c0                	test   %eax,%eax
    7f8535d0b965:	0f 85 6c 00 00 00    	jne    0x7f8535d0b9d7
    7f8535d0b96b:	49 8b c7             	mov    %r15,%rax
    7f8535d0b96e:	48 05 88 10 00 00    	add    $0x1088,%rax
    7f8535d0b974:	49 8b cf             	mov    %r15,%rcx
    7f8535d0b977:	48 81 c1 18 0d 00 00 	add    $0xd18,%rcx
    7f8535d0b97e:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0b981:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0b984:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0b988:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0b98c:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0b990:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0b994:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0b998:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0b99c:	e9 67 00 00 00       	jmpq   0x7f8535d0ba08
    7f8535d0b9a1:	49 8b c7             	mov    %r15,%rax
    7f8535d0b9a4:	48 05 88 10 00 00    	add    $0x1088,%rax
    7f8535d0b9aa:	49 8b cf             	mov    %r15,%rcx
    7f8535d0b9ad:	48 81 c1 c8 10 00 00 	add    $0x10c8,%rcx
    7f8535d0b9b4:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0b9b7:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0b9ba:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0b9be:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0b9c2:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0b9c6:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0b9ca:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0b9ce:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0b9d2:	e9 31 00 00 00       	jmpq   0x7f8535d0ba08
    7f8535d0b9d7:	49 8b c7             	mov    %r15,%rax
    7f8535d0b9da:	48 05 88 10 00 00    	add    $0x1088,%rax
    7f8535d0b9e0:	49 8b cf             	mov    %r15,%rcx
    7f8535d0b9e3:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7f8535d0b9ea:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0b9ed:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0b9f0:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0b9f4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0b9f8:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0b9fc:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0ba00:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0ba04:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0ba08:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f8535d0ba0e:	85 c0                	test   %eax,%eax
    7f8535d0ba10:	0f 85 1c 00 00 00    	jne    0x7f8535d0ba32
    7f8535d0ba16:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7f8535d0ba1c:	85 c0                	test   %eax,%eax
    7f8535d0ba1e:	0f 85 1d 00 00 00    	jne    0x7f8535d0ba41
    7f8535d0ba24:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f8535d0ba27:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7f8535d0ba2d:	e9 19 00 00 00       	jmpq   0x7f8535d0ba4b
    7f8535d0ba32:	c7 85 30 fd ff ff 01 	movl   $0x1,-0x2d0(%rbp)
    7f8535d0ba39:	00 00 00 
    7f8535d0ba3c:	e9 0a 00 00 00       	jmpq   0x7f8535d0ba4b
    7f8535d0ba41:	c7 85 30 fd ff ff 00 	movl   $0x0,-0x2d0(%rbp)
    7f8535d0ba48:	00 00 00 
    7f8535d0ba4b:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f8535d0ba4e:	ff c0                	inc    %eax
    7f8535d0ba50:	83 e0 0f             	and    $0xf,%eax
    7f8535d0ba53:	89 85 28 fd ff ff    	mov    %eax,-0x2d8(%rbp)
    7f8535d0ba59:	41 8b c4             	mov    %r12d,%eax
    7f8535d0ba5c:	83 c8 00             	or     $0x0,%eax
    7f8535d0ba5f:	89 85 20 fd ff ff    	mov    %eax,-0x2e0(%rbp)
    7f8535d0ba65:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f8535d0ba68:	85 c0                	test   %eax,%eax
    7f8535d0ba6a:	0f 94 c0             	sete   %al
    7f8535d0ba6d:	0f b6 c0             	movzbl %al,%eax
    7f8535d0ba70:	49 8b 4e 58          	mov    0x58(%r14),%rcx
    7f8535d0ba74:	8b 09                	mov    (%rcx),%ecx
    7f8535d0ba76:	23 c1                	and    %ecx,%eax
    7f8535d0ba78:	8b 8d d0 fd ff ff    	mov    -0x230(%rbp),%ecx
    7f8535d0ba7e:	23 8d c8 fd ff ff    	and    -0x238(%rbp),%ecx
    7f8535d0ba84:	85 c9                	test   %ecx,%ecx
    7f8535d0ba86:	0f 94 c2             	sete   %dl
    7f8535d0ba89:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0ba8c:	89 95 18 fd ff ff    	mov    %edx,-0x2e8(%rbp)
    7f8535d0ba92:	23 d0                	and    %eax,%edx
    7f8535d0ba94:	8b 75 a0             	mov    -0x60(%rbp),%esi
    7f8535d0ba97:	ff c6                	inc    %esi
    7f8535d0ba99:	83 e6 1f             	and    $0x1f,%esi
    7f8535d0ba9c:	89 b5 10 fd ff ff    	mov    %esi,-0x2f0(%rbp)
    7f8535d0baa2:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7f8535d0baa8:	85 c0                	test   %eax,%eax
    7f8535d0baaa:	0f 94 c0             	sete   %al
    7f8535d0baad:	0f b6 c0             	movzbl %al,%eax
    7f8535d0bab0:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7f8535d0bab6:	89 85 f8 fc ff ff    	mov    %eax,-0x308(%rbp)
    7f8535d0babc:	23 c8                	and    %eax,%ecx
    7f8535d0babe:	89 8d f0 fc ff ff    	mov    %ecx,-0x310(%rbp)
    7f8535d0bac4:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f8535d0bac7:	ff c8                	dec    %eax
    7f8535d0bac9:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0bacc:	89 85 e8 fc ff ff    	mov    %eax,-0x318(%rbp)
    7f8535d0bad2:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7f8535d0bad8:	85 d2                	test   %edx,%edx
    7f8535d0bada:	0f 85 1c 00 00 00    	jne    0x7f8535d0bafc
    7f8535d0bae0:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7f8535d0bae6:	85 c0                	test   %eax,%eax
    7f8535d0bae8:	0f 85 1f 00 00 00    	jne    0x7f8535d0bb0d
    7f8535d0baee:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f8535d0baf1:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f8535d0baf7:	e9 1d 00 00 00       	jmpq   0x7f8535d0bb19
    7f8535d0bafc:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7f8535d0bb02:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f8535d0bb08:	e9 0c 00 00 00       	jmpq   0x7f8535d0bb19
    7f8535d0bb0d:	8b 85 e8 fc ff ff    	mov    -0x318(%rbp),%eax
    7f8535d0bb13:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f8535d0bb19:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f8535d0bb1c:	83 f8 01             	cmp    $0x1,%eax
    7f8535d0bb1f:	0f 94 c0             	sete   %al
    7f8535d0bb22:	0f b6 c0             	movzbl %al,%eax
    7f8535d0bb25:	23 85 00 fd ff ff    	and    -0x300(%rbp),%eax
    7f8535d0bb2b:	23 85 f8 fc ff ff    	and    -0x308(%rbp),%eax
    7f8535d0bb31:	85 c0                	test   %eax,%eax
    7f8535d0bb33:	0f 85 1c 00 00 00    	jne    0x7f8535d0bb55
    7f8535d0bb39:	8b 85 e0 fc ff ff    	mov    -0x320(%rbp),%eax
    7f8535d0bb3f:	85 c0                	test   %eax,%eax
    7f8535d0bb41:	0f 85 1d 00 00 00    	jne    0x7f8535d0bb64
    7f8535d0bb47:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f8535d0bb4a:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7f8535d0bb50:	e9 19 00 00 00       	jmpq   0x7f8535d0bb6e
    7f8535d0bb55:	c7 85 d0 fc ff ff 01 	movl   $0x1,-0x330(%rbp)
    7f8535d0bb5c:	00 00 00 
    7f8535d0bb5f:	e9 0a 00 00 00       	jmpq   0x7f8535d0bb6e
    7f8535d0bb64:	c7 85 d0 fc ff ff 00 	movl   $0x0,-0x330(%rbp)
    7f8535d0bb6b:	00 00 00 
    7f8535d0bb6e:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f8535d0bb71:	83 f8 0f             	cmp    $0xf,%eax
    7f8535d0bb74:	0f 94 c0             	sete   %al
    7f8535d0bb77:	0f b6 c0             	movzbl %al,%eax
    7f8535d0bb7a:	23 85 08 fd ff ff    	and    -0x2f8(%rbp),%eax
    7f8535d0bb80:	23 85 18 fd ff ff    	and    -0x2e8(%rbp),%eax
    7f8535d0bb86:	85 c0                	test   %eax,%eax
    7f8535d0bb88:	0f 85 1c 00 00 00    	jne    0x7f8535d0bbaa
    7f8535d0bb8e:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7f8535d0bb94:	85 c0                	test   %eax,%eax
    7f8535d0bb96:	0f 85 1d 00 00 00    	jne    0x7f8535d0bbb9
    7f8535d0bb9c:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f8535d0bb9f:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7f8535d0bba5:	e9 19 00 00 00       	jmpq   0x7f8535d0bbc3
    7f8535d0bbaa:	c7 85 c8 fc ff ff 01 	movl   $0x1,-0x338(%rbp)
    7f8535d0bbb1:	00 00 00 
    7f8535d0bbb4:	e9 0a 00 00 00       	jmpq   0x7f8535d0bbc3
    7f8535d0bbb9:	c7 85 c8 fc ff ff 00 	movl   $0x0,-0x338(%rbp)
    7f8535d0bbc0:	00 00 00 
    7f8535d0bbc3:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f8535d0bbc6:	ff c0                	inc    %eax
    7f8535d0bbc8:	83 e0 0f             	and    $0xf,%eax
    7f8535d0bbcb:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7f8535d0bbd1:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f8535d0bbd4:	83 c0 02             	add    $0x2,%eax
    7f8535d0bbd7:	83 e0 0f             	and    $0xf,%eax
    7f8535d0bbda:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7f8535d0bbe0:	b8 01 00 00 00       	mov    $0x1,%eax
    7f8535d0bbe5:	3b 45 a0             	cmp    -0x60(%rbp),%eax
    7f8535d0bbe8:	0f 94 c0             	sete   %al
    7f8535d0bbeb:	0f b6 c0             	movzbl %al,%eax
    7f8535d0bbee:	8b 8d 00 fd ff ff    	mov    -0x300(%rbp),%ecx
    7f8535d0bbf4:	23 c1                	and    %ecx,%eax
    7f8535d0bbf6:	8b 55 98             	mov    -0x68(%rbp),%edx
    7f8535d0bbf9:	0b c2                	or     %edx,%eax
    7f8535d0bbfb:	8b 95 08 fd ff ff    	mov    -0x2f8(%rbp),%edx
    7f8535d0bc01:	23 c2                	and    %edx,%eax
    7f8535d0bc03:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7f8535d0bc09:	49 8b 46 50          	mov    0x50(%r14),%rax
    7f8535d0bc0d:	48 89 85 a8 fc ff ff 	mov    %rax,-0x358(%rbp)
    7f8535d0bc14:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7f8535d0bc1a:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7f8535d0bc20:	85 c9                	test   %ecx,%ecx
    7f8535d0bc22:	0f 85 09 00 00 00    	jne    0x7f8535d0bc31
    7f8535d0bc28:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f8535d0bc2b:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7f8535d0bc31:	49 8b c7             	mov    %r15,%rax
    7f8535d0bc34:	48 05 00 0c 00 00    	add    $0xc00,%rax
    7f8535d0bc3a:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7f8535d0bc40:	c1 e1 06             	shl    $0x6,%ecx
    7f8535d0bc43:	8b c9                	mov    %ecx,%ecx
    7f8535d0bc45:	49 03 cf             	add    %r15,%rcx
    7f8535d0bc48:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0bc4b:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0bc4e:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0bc52:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0bc56:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0bc5a:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0bc5e:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0bc62:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0bc66:	49 8b 46 10          	mov    0x10(%r14),%rax
    7f8535d0bc6a:	48 8b 00             	mov    (%rax),%rax
    7f8535d0bc6d:	48 89 85 98 fc ff ff 	mov    %rax,-0x368(%rbp)
    7f8535d0bc74:	49 8b 86 80 00 00 00 	mov    0x80(%r14),%rax
    7f8535d0bc7b:	8b 00                	mov    (%rax),%eax
    7f8535d0bc7d:	85 c0                	test   %eax,%eax
    7f8535d0bc7f:	0f 94 c0             	sete   %al
    7f8535d0bc82:	0f b6 c0             	movzbl %al,%eax
    7f8535d0bc85:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7f8535d0bc8b:	23 c1                	and    %ecx,%eax
    7f8535d0bc8d:	89 85 90 fc ff ff    	mov    %eax,-0x370(%rbp)
    7f8535d0bc93:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f8535d0bc99:	8b c0                	mov    %eax,%eax
    7f8535d0bc9b:	48 c1 e0 06          	shl    $0x6,%rax
    7f8535d0bc9f:	48 89 85 88 fc ff ff 	mov    %rax,-0x378(%rbp)
    7f8535d0bca6:	48 8b 8d 68 ff ff ff 	mov    -0x98(%rbp),%rcx
    7f8535d0bcad:	48 03 c1             	add    %rcx,%rax
    7f8535d0bcb0:	48 89 85 80 fc ff ff 	mov    %rax,-0x380(%rbp)
    7f8535d0bcb7:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0bcbd:	85 c0                	test   %eax,%eax
    7f8535d0bcbf:	0f 85 21 00 00 00    	jne    0x7f8535d0bce6
    7f8535d0bcc5:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f8535d0bccb:	85 c0                	test   %eax,%eax
    7f8535d0bccd:	0f 85 26 00 00 00    	jne    0x7f8535d0bcf9
    7f8535d0bcd3:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
    7f8535d0bcda:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7f8535d0bce1:	e9 21 00 00 00       	jmpq   0x7f8535d0bd07
    7f8535d0bce6:	48 8b 85 98 fc ff ff 	mov    -0x368(%rbp),%rax
    7f8535d0bced:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7f8535d0bcf4:	e9 0e 00 00 00       	jmpq   0x7f8535d0bd07
    7f8535d0bcf9:	48 8b 85 80 fc ff ff 	mov    -0x380(%rbp),%rax
    7f8535d0bd00:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7f8535d0bd07:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f8535d0bd0d:	85 c0                	test   %eax,%eax
    7f8535d0bd0f:	0f 94 c0             	sete   %al
    7f8535d0bd12:	0f b6 c0             	movzbl %al,%eax
    7f8535d0bd15:	8b 95 40 ff ff ff    	mov    -0xc0(%rbp),%edx
    7f8535d0bd1b:	85 d2                	test   %edx,%edx
    7f8535d0bd1d:	0f 94 c1             	sete   %cl
    7f8535d0bd20:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0bd23:	8b b5 38 ff ff ff    	mov    -0xc8(%rbp),%esi
    7f8535d0bd29:	83 fe 0f             	cmp    $0xf,%esi
    7f8535d0bd2c:	40 0f 94 c6          	sete   %sil
    7f8535d0bd30:	40 0f b6 f6          	movzbl %sil,%esi
    7f8535d0bd34:	23 95 e0 fd ff ff    	and    -0x220(%rbp),%edx
    7f8535d0bd3a:	85 d2                	test   %edx,%edx
    7f8535d0bd3c:	0f 94 c2             	sete   %dl
    7f8535d0bd3f:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0bd42:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7f8535d0bd48:	23 d7                	and    %edi,%edx
    7f8535d0bd4a:	89 95 70 fc ff ff    	mov    %edx,-0x390(%rbp)
    7f8535d0bd50:	23 f2                	and    %edx,%esi
    7f8535d0bd52:	89 b5 68 fc ff ff    	mov    %esi,-0x398(%rbp)
    7f8535d0bd58:	0b ce                	or     %esi,%ecx
    7f8535d0bd5a:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7f8535d0bd60:	89 8d 58 fc ff ff    	mov    %ecx,-0x3a8(%rbp)
    7f8535d0bd66:	23 c1                	and    %ecx,%eax
    7f8535d0bd68:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7f8535d0bd6e:	03 8d 48 ff ff ff    	add    -0xb8(%rbp),%ecx
    7f8535d0bd74:	83 e1 1f             	and    $0x1f,%ecx
    7f8535d0bd77:	89 8d 50 fc ff ff    	mov    %ecx,-0x3b0(%rbp)
    7f8535d0bd7d:	ff c9                	dec    %ecx
    7f8535d0bd7f:	83 e1 1f             	and    $0x1f,%ecx
    7f8535d0bd82:	89 8d 48 fc ff ff    	mov    %ecx,-0x3b8(%rbp)
    7f8535d0bd88:	89 85 40 fc ff ff    	mov    %eax,-0x3c0(%rbp)
    7f8535d0bd8e:	85 c0                	test   %eax,%eax
    7f8535d0bd90:	0f 85 0c 00 00 00    	jne    0x7f8535d0bda2
    7f8535d0bd96:	8b 85 50 fc ff ff    	mov    -0x3b0(%rbp),%eax
    7f8535d0bd9c:	89 85 48 fc ff ff    	mov    %eax,-0x3b8(%rbp)
    7f8535d0bda2:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f8535d0bda8:	ff c8                	dec    %eax
    7f8535d0bdaa:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0bdad:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7f8535d0bdb3:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f8535d0bdb9:	85 c0                	test   %eax,%eax
    7f8535d0bdbb:	0f 85 0c 00 00 00    	jne    0x7f8535d0bdcd
    7f8535d0bdc1:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f8535d0bdc7:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7f8535d0bdcd:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0bdd3:	85 c0                	test   %eax,%eax
    7f8535d0bdd5:	0f 85 1f 00 00 00    	jne    0x7f8535d0bdfa
    7f8535d0bddb:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f8535d0bde1:	85 c0                	test   %eax,%eax
    7f8535d0bde3:	0f 85 20 00 00 00    	jne    0x7f8535d0be09
    7f8535d0bde9:	8b 85 38 fc ff ff    	mov    -0x3c8(%rbp),%eax
    7f8535d0bdef:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7f8535d0bdf5:	e9 1b 00 00 00       	jmpq   0x7f8535d0be15
    7f8535d0bdfa:	c7 85 30 fc ff ff 00 	movl   $0x0,-0x3d0(%rbp)
    7f8535d0be01:	00 00 00 
    7f8535d0be04:	e9 0c 00 00 00       	jmpq   0x7f8535d0be15
    7f8535d0be09:	8b 85 48 fc ff ff    	mov    -0x3b8(%rbp),%eax
    7f8535d0be0f:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7f8535d0be15:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f8535d0be1b:	ff c8                	dec    %eax
    7f8535d0be1d:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7f8535d0be22:	89 85 28 fc ff ff    	mov    %eax,-0x3d8(%rbp)
    7f8535d0be28:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0be2e:	85 c0                	test   %eax,%eax
    7f8535d0be30:	0f 85 1f 00 00 00    	jne    0x7f8535d0be55
    7f8535d0be36:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f8535d0be3c:	85 c0                	test   %eax,%eax
    7f8535d0be3e:	0f 85 22 00 00 00    	jne    0x7f8535d0be66
    7f8535d0be44:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f8535d0be4a:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f8535d0be50:	e9 1d 00 00 00       	jmpq   0x7f8535d0be72
    7f8535d0be55:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f8535d0be5b:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f8535d0be61:	e9 0c 00 00 00       	jmpq   0x7f8535d0be72
    7f8535d0be66:	8b 85 28 fc ff ff    	mov    -0x3d8(%rbp),%eax
    7f8535d0be6c:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f8535d0be72:	b8 01 00 00 00       	mov    $0x1,%eax
    7f8535d0be77:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7f8535d0be7d:	3b c1                	cmp    %ecx,%eax
    7f8535d0be7f:	0f 94 c0             	sete   %al
    7f8535d0be82:	0f b6 c0             	movzbl %al,%eax
    7f8535d0be85:	8b 95 90 fc ff ff    	mov    -0x370(%rbp),%edx
    7f8535d0be8b:	23 c2                	and    %edx,%eax
    7f8535d0be8d:	89 85 18 fc ff ff    	mov    %eax,-0x3e8(%rbp)
    7f8535d0be93:	85 c9                	test   %ecx,%ecx
    7f8535d0be95:	0f 95 c0             	setne  %al
    7f8535d0be98:	0f b6 c0             	movzbl %al,%eax
    7f8535d0be9b:	83 e0 01             	and    $0x1,%eax
    7f8535d0be9e:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7f8535d0bea4:	83 f9 00             	cmp    $0x0,%ecx
    7f8535d0bea7:	0f 96 c1             	setbe  %cl
    7f8535d0beaa:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0bead:	23 c1                	and    %ecx,%eax
    7f8535d0beaf:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7f8535d0beb5:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0bebb:	85 c0                	test   %eax,%eax
    7f8535d0bebd:	0f 85 1f 00 00 00    	jne    0x7f8535d0bee2
    7f8535d0bec3:	8b 85 18 fc ff ff    	mov    -0x3e8(%rbp),%eax
    7f8535d0bec9:	85 c0                	test   %eax,%eax
    7f8535d0becb:	0f 85 22 00 00 00    	jne    0x7f8535d0bef3
    7f8535d0bed1:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7f8535d0bed7:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7f8535d0bedd:	e9 1b 00 00 00       	jmpq   0x7f8535d0befd
    7f8535d0bee2:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7f8535d0bee8:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7f8535d0beee:	e9 0a 00 00 00       	jmpq   0x7f8535d0befd
    7f8535d0bef3:	c7 85 08 fc ff ff 00 	movl   $0x0,-0x3f8(%rbp)
    7f8535d0befa:	00 00 00 
    7f8535d0befd:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0bf03:	85 c0                	test   %eax,%eax
    7f8535d0bf05:	0f 85 1f 00 00 00    	jne    0x7f8535d0bf2a
    7f8535d0bf0b:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f8535d0bf11:	85 c0                	test   %eax,%eax
    7f8535d0bf13:	0f 85 22 00 00 00    	jne    0x7f8535d0bf3b
    7f8535d0bf19:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f8535d0bf1f:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f8535d0bf25:	e9 1b 00 00 00       	jmpq   0x7f8535d0bf45
    7f8535d0bf2a:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7f8535d0bf30:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f8535d0bf36:	e9 0a 00 00 00       	jmpq   0x7f8535d0bf45
    7f8535d0bf3b:	c7 85 00 fc ff ff 10 	movl   $0x10,-0x400(%rbp)
    7f8535d0bf42:	00 00 00 
    7f8535d0bf45:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f8535d0bf4b:	85 c0                	test   %eax,%eax
    7f8535d0bf4d:	0f 85 36 00 00 00    	jne    0x7f8535d0bf89
    7f8535d0bf53:	49 8b c7             	mov    %r15,%rax
    7f8535d0bf56:	48 05 48 11 00 00    	add    $0x1148,%rax
    7f8535d0bf5c:	49 8b cf             	mov    %r15,%rcx
    7f8535d0bf5f:	48 81 c1 10 0f 00 00 	add    $0xf10,%rcx
    7f8535d0bf66:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0bf69:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0bf6c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0bf70:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0bf74:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0bf78:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0bf7c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0bf80:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0bf84:	e9 31 00 00 00       	jmpq   0x7f8535d0bfba
    7f8535d0bf89:	49 8b c7             	mov    %r15,%rax
    7f8535d0bf8c:	48 05 48 11 00 00    	add    $0x1148,%rax
    7f8535d0bf92:	49 8b cf             	mov    %r15,%rcx
    7f8535d0bf95:	48 81 c1 d0 0e 00 00 	add    $0xed0,%rcx
    7f8535d0bf9c:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0bf9f:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0bfa2:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0bfa6:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0bfaa:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0bfae:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0bfb2:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0bfb6:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0bfba:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f8535d0bfc0:	23 85 70 fc ff ff    	and    -0x390(%rbp),%eax
    7f8535d0bfc6:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7f8535d0bfcc:	49 8b c7             	mov    %r15,%rax
    7f8535d0bfcf:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7f8535d0bfd5:	49 8b cf             	mov    %r15,%rcx
    7f8535d0bfd8:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7f8535d0bfdf:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7f8535d0bfe5:	48 89 8d f0 fb ff ff 	mov    %rcx,-0x410(%rbp)
    7f8535d0bfec:	b9 00 02 00 00       	mov    $0x200,%ecx
    7f8535d0bff1:	48 8b d0             	mov    %rax,%rdx
    7f8535d0bff4:	be 00 02 00 00       	mov    $0x200,%esi
    7f8535d0bff9:	48 8b bd f0 fb ff ff 	mov    -0x410(%rbp),%rdi
    7f8535d0c000:	48 89 85 e8 fb ff ff 	mov    %rax,-0x418(%rbp)
    7f8535d0c007:	b8 08 00 00 00       	mov    $0x8,%eax
    7f8535d0c00c:	e8 4f 9a b3 ff       	callq  0x7f8535845a60
    7f8535d0c011:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f8535d0c017:	85 c0                	test   %eax,%eax
    7f8535d0c019:	0f 85 44 00 00 00    	jne    0x7f8535d0c063
    7f8535d0c01f:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7f8535d0c025:	85 c0                	test   %eax,%eax
    7f8535d0c027:	0f 85 6c 00 00 00    	jne    0x7f8535d0c099
    7f8535d0c02d:	49 8b c7             	mov    %r15,%rax
    7f8535d0c030:	48 05 08 11 00 00    	add    $0x1108,%rax
    7f8535d0c036:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c039:	48 81 c1 48 0e 00 00 	add    $0xe48,%rcx
    7f8535d0c040:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0c043:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0c046:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0c04a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0c04e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0c052:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0c056:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0c05a:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0c05e:	e9 67 00 00 00       	jmpq   0x7f8535d0c0ca
    7f8535d0c063:	49 8b c7             	mov    %r15,%rax
    7f8535d0c066:	48 05 08 11 00 00    	add    $0x1108,%rax
    7f8535d0c06c:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c06f:	48 81 c1 48 11 00 00 	add    $0x1148,%rcx
    7f8535d0c076:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0c079:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0c07c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0c080:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0c084:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0c088:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0c08c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0c090:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0c094:	e9 31 00 00 00       	jmpq   0x7f8535d0c0ca
    7f8535d0c099:	49 8b c7             	mov    %r15,%rax
    7f8535d0c09c:	48 05 08 11 00 00    	add    $0x1108,%rax
    7f8535d0c0a2:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c0a5:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7f8535d0c0ac:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0c0af:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0c0b2:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0c0b6:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0c0ba:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0c0be:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0c0c2:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0c0c6:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0c0ca:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f8535d0c0d0:	85 c0                	test   %eax,%eax
    7f8535d0c0d2:	0f 85 1f 00 00 00    	jne    0x7f8535d0c0f7
    7f8535d0c0d8:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7f8535d0c0de:	85 c0                	test   %eax,%eax
    7f8535d0c0e0:	0f 85 20 00 00 00    	jne    0x7f8535d0c106
    7f8535d0c0e6:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f8535d0c0ec:	89 85 e0 fb ff ff    	mov    %eax,-0x420(%rbp)
    7f8535d0c0f2:	e9 19 00 00 00       	jmpq   0x7f8535d0c110
    7f8535d0c0f7:	c7 85 e0 fb ff ff 01 	movl   $0x1,-0x420(%rbp)
    7f8535d0c0fe:	00 00 00 
    7f8535d0c101:	e9 0a 00 00 00       	jmpq   0x7f8535d0c110
    7f8535d0c106:	c7 85 e0 fb ff ff 00 	movl   $0x0,-0x420(%rbp)
    7f8535d0c10d:	00 00 00 
    7f8535d0c110:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f8535d0c116:	ff c0                	inc    %eax
    7f8535d0c118:	83 e0 0f             	and    $0xf,%eax
    7f8535d0c11b:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7f8535d0c121:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f8535d0c127:	85 c0                	test   %eax,%eax
    7f8535d0c129:	0f 94 c0             	sete   %al
    7f8535d0c12c:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c12f:	49 8b 4e 78          	mov    0x78(%r14),%rcx
    7f8535d0c133:	8b 09                	mov    (%rcx),%ecx
    7f8535d0c135:	23 c1                	and    %ecx,%eax
    7f8535d0c137:	8b 8d 60 fc ff ff    	mov    -0x3a0(%rbp),%ecx
    7f8535d0c13d:	23 8d 58 fc ff ff    	and    -0x3a8(%rbp),%ecx
    7f8535d0c143:	85 c9                	test   %ecx,%ecx
    7f8535d0c145:	0f 94 c2             	sete   %dl
    7f8535d0c148:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0c14b:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7f8535d0c151:	23 d0                	and    %eax,%edx
    7f8535d0c153:	8b b5 30 ff ff ff    	mov    -0xd0(%rbp),%esi
    7f8535d0c159:	ff c6                	inc    %esi
    7f8535d0c15b:	83 e6 1f             	and    $0x1f,%esi
    7f8535d0c15e:	89 b5 c8 fb ff ff    	mov    %esi,-0x438(%rbp)
    7f8535d0c164:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7f8535d0c16a:	85 c0                	test   %eax,%eax
    7f8535d0c16c:	0f 94 c0             	sete   %al
    7f8535d0c16f:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c172:	89 8d b8 fb ff ff    	mov    %ecx,-0x448(%rbp)
    7f8535d0c178:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7f8535d0c17e:	23 c8                	and    %eax,%ecx
    7f8535d0c180:	89 8d a8 fb ff ff    	mov    %ecx,-0x458(%rbp)
    7f8535d0c186:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f8535d0c18c:	ff c8                	dec    %eax
    7f8535d0c18e:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0c191:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7f8535d0c197:	89 95 98 fb ff ff    	mov    %edx,-0x468(%rbp)
    7f8535d0c19d:	85 d2                	test   %edx,%edx
    7f8535d0c19f:	0f 85 1f 00 00 00    	jne    0x7f8535d0c1c4
    7f8535d0c1a5:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7f8535d0c1ab:	85 c0                	test   %eax,%eax
    7f8535d0c1ad:	0f 85 22 00 00 00    	jne    0x7f8535d0c1d5
    7f8535d0c1b3:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f8535d0c1b9:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f8535d0c1bf:	e9 1d 00 00 00       	jmpq   0x7f8535d0c1e1
    7f8535d0c1c4:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7f8535d0c1ca:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f8535d0c1d0:	e9 0c 00 00 00       	jmpq   0x7f8535d0c1e1
    7f8535d0c1d5:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7f8535d0c1db:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f8535d0c1e1:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f8535d0c1e7:	83 f8 01             	cmp    $0x1,%eax
    7f8535d0c1ea:	0f 94 c0             	sete   %al
    7f8535d0c1ed:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c1f0:	23 85 b8 fb ff ff    	and    -0x448(%rbp),%eax
    7f8535d0c1f6:	23 85 b0 fb ff ff    	and    -0x450(%rbp),%eax
    7f8535d0c1fc:	85 c0                	test   %eax,%eax
    7f8535d0c1fe:	0f 85 1f 00 00 00    	jne    0x7f8535d0c223
    7f8535d0c204:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7f8535d0c20a:	85 c0                	test   %eax,%eax
    7f8535d0c20c:	0f 85 20 00 00 00    	jne    0x7f8535d0c232
    7f8535d0c212:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f8535d0c218:	89 85 88 fb ff ff    	mov    %eax,-0x478(%rbp)
    7f8535d0c21e:	e9 19 00 00 00       	jmpq   0x7f8535d0c23c
    7f8535d0c223:	c7 85 88 fb ff ff 01 	movl   $0x1,-0x478(%rbp)
    7f8535d0c22a:	00 00 00 
    7f8535d0c22d:	e9 0a 00 00 00       	jmpq   0x7f8535d0c23c
    7f8535d0c232:	c7 85 88 fb ff ff 00 	movl   $0x0,-0x478(%rbp)
    7f8535d0c239:	00 00 00 
    7f8535d0c23c:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f8535d0c242:	83 f8 0f             	cmp    $0xf,%eax
    7f8535d0c245:	0f 94 c0             	sete   %al
    7f8535d0c248:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c24b:	23 85 c0 fb ff ff    	and    -0x440(%rbp),%eax
    7f8535d0c251:	23 85 d0 fb ff ff    	and    -0x430(%rbp),%eax
    7f8535d0c257:	85 c0                	test   %eax,%eax
    7f8535d0c259:	0f 85 1f 00 00 00    	jne    0x7f8535d0c27e
    7f8535d0c25f:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7f8535d0c265:	85 c0                	test   %eax,%eax
    7f8535d0c267:	0f 85 20 00 00 00    	jne    0x7f8535d0c28d
    7f8535d0c26d:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f8535d0c273:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7f8535d0c279:	e9 19 00 00 00       	jmpq   0x7f8535d0c297
    7f8535d0c27e:	c7 85 80 fb ff ff 01 	movl   $0x1,-0x480(%rbp)
    7f8535d0c285:	00 00 00 
    7f8535d0c288:	e9 0a 00 00 00       	jmpq   0x7f8535d0c297
    7f8535d0c28d:	c7 85 80 fb ff ff 00 	movl   $0x0,-0x480(%rbp)
    7f8535d0c294:	00 00 00 
    7f8535d0c297:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f8535d0c29d:	ff c0                	inc    %eax
    7f8535d0c29f:	83 e0 0f             	and    $0xf,%eax
    7f8535d0c2a2:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7f8535d0c2a8:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f8535d0c2ae:	83 c0 02             	add    $0x2,%eax
    7f8535d0c2b1:	83 e0 0f             	and    $0xf,%eax
    7f8535d0c2b4:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7f8535d0c2ba:	b8 01 00 00 00       	mov    $0x1,%eax
    7f8535d0c2bf:	3b 85 30 ff ff ff    	cmp    -0xd0(%rbp),%eax
    7f8535d0c2c5:	0f 94 c0             	sete   %al
    7f8535d0c2c8:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c2cb:	8b 8d b8 fb ff ff    	mov    -0x448(%rbp),%ecx
    7f8535d0c2d1:	23 c1                	and    %ecx,%eax
    7f8535d0c2d3:	8b 95 28 ff ff ff    	mov    -0xd8(%rbp),%edx
    7f8535d0c2d9:	0b c2                	or     %edx,%eax
    7f8535d0c2db:	8b 95 c0 fb ff ff    	mov    -0x440(%rbp),%edx
    7f8535d0c2e1:	23 c2                	and    %edx,%eax
    7f8535d0c2e3:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7f8535d0c2e9:	49 8b 46 70          	mov    0x70(%r14),%rax
    7f8535d0c2ed:	48 89 85 60 fb ff ff 	mov    %rax,-0x4a0(%rbp)
    7f8535d0c2f4:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f8535d0c2fa:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7f8535d0c300:	85 c9                	test   %ecx,%ecx
    7f8535d0c302:	0f 85 0c 00 00 00    	jne    0x7f8535d0c314
    7f8535d0c308:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f8535d0c30e:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7f8535d0c314:	49 8b c7             	mov    %r15,%rax
    7f8535d0c317:	48 05 00 04 00 00    	add    $0x400,%rax
    7f8535d0c31d:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c320:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7f8535d0c327:	8b 95 58 fb ff ff    	mov    -0x4a8(%rbp),%edx
    7f8535d0c32d:	c1 e2 06             	shl    $0x6,%edx
    7f8535d0c330:	8b d2                	mov    %edx,%edx
    7f8535d0c332:	48 03 c2             	add    %rdx,%rax
    7f8535d0c335:	0f 10 00             	movups (%rax),%xmm0
    7f8535d0c338:	0f 11 01             	movups %xmm0,(%rcx)
    7f8535d0c33b:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7f8535d0c33f:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7f8535d0c343:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7f8535d0c347:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7f8535d0c34b:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7f8535d0c34f:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7f8535d0c353:	49 8b 06             	mov    (%r14),%rax
    7f8535d0c356:	48 8b 00             	mov    (%rax),%rax
    7f8535d0c359:	48 89 85 50 fb ff ff 	mov    %rax,-0x4b0(%rbp)
    7f8535d0c360:	49 8b 46 40          	mov    0x40(%r14),%rax
    7f8535d0c364:	8b 00                	mov    (%rax),%eax
    7f8535d0c366:	85 c0                	test   %eax,%eax
    7f8535d0c368:	0f 94 c0             	sete   %al
    7f8535d0c36b:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c36e:	89 85 48 fb ff ff    	mov    %eax,-0x4b8(%rbp)
    7f8535d0c374:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7f8535d0c37a:	23 c1                	and    %ecx,%eax
    7f8535d0c37c:	89 85 40 fb ff ff    	mov    %eax,-0x4c0(%rbp)
    7f8535d0c382:	48 8b 85 f8 fe ff ff 	mov    -0x108(%rbp),%rax
    7f8535d0c389:	48 83 c0 40          	add    $0x40,%rax
    7f8535d0c38d:	48 89 85 38 fb ff ff 	mov    %rax,-0x4c8(%rbp)
    7f8535d0c394:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f8535d0c39a:	85 c0                	test   %eax,%eax
    7f8535d0c39c:	0f 85 21 00 00 00    	jne    0x7f8535d0c3c3
    7f8535d0c3a2:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f8535d0c3a8:	85 c0                	test   %eax,%eax
    7f8535d0c3aa:	0f 85 26 00 00 00    	jne    0x7f8535d0c3d6
    7f8535d0c3b0:	48 8b 85 f8 fe ff ff 	mov    -0x108(%rbp),%rax
    7f8535d0c3b7:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7f8535d0c3be:	e9 21 00 00 00       	jmpq   0x7f8535d0c3e4
    7f8535d0c3c3:	48 8b 85 50 fb ff ff 	mov    -0x4b0(%rbp),%rax
    7f8535d0c3ca:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7f8535d0c3d1:	e9 0e 00 00 00       	jmpq   0x7f8535d0c3e4
    7f8535d0c3d6:	48 8b 85 38 fb ff ff 	mov    -0x4c8(%rbp),%rax
    7f8535d0c3dd:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7f8535d0c3e4:	8b 8d f0 fe ff ff    	mov    -0x110(%rbp),%ecx
    7f8535d0c3ea:	85 c9                	test   %ecx,%ecx
    7f8535d0c3ec:	0f 94 c0             	sete   %al
    7f8535d0c3ef:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c3f2:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7f8535d0c3f8:	85 d2                	test   %edx,%edx
    7f8535d0c3fa:	0f 94 c2             	sete   %dl
    7f8535d0c3fd:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0c400:	89 95 28 fb ff ff    	mov    %edx,-0x4d8(%rbp)
    7f8535d0c406:	8b b5 c0 fe ff ff    	mov    -0x140(%rbp),%esi
    7f8535d0c40c:	23 d6                	and    %esi,%edx
    7f8535d0c40e:	83 fb 10             	cmp    $0x10,%ebx
    7f8535d0c411:	40 0f 93 c7          	setae  %dil
    7f8535d0c415:	40 0f b6 ff          	movzbl %dil,%edi
    7f8535d0c419:	0b d7                	or     %edi,%edx
    7f8535d0c41b:	23 c2                	and    %edx,%eax
    7f8535d0c41d:	ba 01 00 00 00       	mov    $0x1,%edx
    7f8535d0c422:	3b d1                	cmp    %ecx,%edx
    7f8535d0c424:	0f 94 c2             	sete   %dl
    7f8535d0c427:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0c42a:	89 95 20 fb ff ff    	mov    %edx,-0x4e0(%rbp)
    7f8535d0c430:	23 95 48 fb ff ff    	and    -0x4b8(%rbp),%edx
    7f8535d0c436:	83 fb 01             	cmp    $0x1,%ebx
    7f8535d0c439:	40 0f 97 c7          	seta   %dil
    7f8535d0c43d:	40 0f b6 ff          	movzbl %dil,%edi
    7f8535d0c441:	23 f7                	and    %edi,%esi
    7f8535d0c443:	83 fb 10             	cmp    $0x10,%ebx
    7f8535d0c446:	40 0f 97 c7          	seta   %dil
    7f8535d0c44a:	40 0f b6 ff          	movzbl %dil,%edi
    7f8535d0c44e:	0b f7                	or     %edi,%esi
    7f8535d0c450:	23 d6                	and    %esi,%edx
    7f8535d0c452:	0b c2                	or     %edx,%eax
    7f8535d0c454:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7f8535d0c45a:	83 fb 10             	cmp    $0x10,%ebx
    7f8535d0c45d:	0f 94 c0             	sete   %al
    7f8535d0c460:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c463:	85 c9                	test   %ecx,%ecx
    7f8535d0c465:	0f 94 c2             	sete   %dl
    7f8535d0c468:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0c46b:	23 c2                	and    %edx,%eax
    7f8535d0c46d:	0b f8                	or     %eax,%edi
    7f8535d0c46f:	85 c9                	test   %ecx,%ecx
    7f8535d0c471:	0f 95 c0             	setne  %al
    7f8535d0c474:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c477:	83 e0 01             	and    $0x1,%eax
    7f8535d0c47a:	8b cb                	mov    %ebx,%ecx
    7f8535d0c47c:	2b c8                	sub    %eax,%ecx
    7f8535d0c47e:	83 e1 1f             	and    $0x1f,%ecx
    7f8535d0c481:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7f8535d0c487:	c7 85 08 fb ff ff 10 	movl   $0x10,-0x4f8(%rbp)
    7f8535d0c48e:	00 00 00 
    7f8535d0c491:	85 ff                	test   %edi,%edi
    7f8535d0c493:	0f 85 0c 00 00 00    	jne    0x7f8535d0c4a5
    7f8535d0c499:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7f8535d0c49f:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7f8535d0c4a5:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f8535d0c4ab:	ff c8                	dec    %eax
    7f8535d0c4ad:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0c4b0:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7f8535d0c4b6:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f8535d0c4bc:	85 c0                	test   %eax,%eax
    7f8535d0c4be:	0f 85 1f 00 00 00    	jne    0x7f8535d0c4e3
    7f8535d0c4c4:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f8535d0c4ca:	85 c0                	test   %eax,%eax
    7f8535d0c4cc:	0f 85 22 00 00 00    	jne    0x7f8535d0c4f4
    7f8535d0c4d2:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f8535d0c4d8:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f8535d0c4de:	e9 1d 00 00 00       	jmpq   0x7f8535d0c500
    7f8535d0c4e3:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7f8535d0c4e9:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f8535d0c4ef:	e9 0c 00 00 00       	jmpq   0x7f8535d0c500
    7f8535d0c4f4:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7f8535d0c4fa:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f8535d0c500:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f8535d0c506:	23 85 20 fb ff ff    	and    -0x4e0(%rbp),%eax
    7f8535d0c50c:	89 85 f0 fa ff ff    	mov    %eax,-0x510(%rbp)
    7f8535d0c512:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f8535d0c518:	85 c0                	test   %eax,%eax
    7f8535d0c51a:	0f 85 1f 00 00 00    	jne    0x7f8535d0c53f
    7f8535d0c520:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7f8535d0c526:	85 c0                	test   %eax,%eax
    7f8535d0c528:	0f 85 20 00 00 00    	jne    0x7f8535d0c54e
    7f8535d0c52e:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7f8535d0c534:	89 85 e8 fa ff ff    	mov    %eax,-0x518(%rbp)
    7f8535d0c53a:	e9 19 00 00 00       	jmpq   0x7f8535d0c558
    7f8535d0c53f:	c7 85 e8 fa ff ff 01 	movl   $0x1,-0x518(%rbp)
    7f8535d0c546:	00 00 00 
    7f8535d0c549:	e9 0a 00 00 00       	jmpq   0x7f8535d0c558
    7f8535d0c54e:	c7 85 e8 fa ff ff 00 	movl   $0x0,-0x518(%rbp)
    7f8535d0c555:	00 00 00 
    7f8535d0c558:	41 83 fd 02          	cmp    $0x2,%r13d
    7f8535d0c55c:	0f 94 c0             	sete   %al
    7f8535d0c55f:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c562:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7f8535d0c568:	85 c9                	test   %ecx,%ecx
    7f8535d0c56a:	0f 95 c1             	setne  %cl
    7f8535d0c56d:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0c570:	89 85 e0 fa ff ff    	mov    %eax,-0x520(%rbp)
    7f8535d0c576:	23 c8                	and    %eax,%ecx
    7f8535d0c578:	8b c1                	mov    %ecx,%eax
    7f8535d0c57a:	89 85 d8 fa ff ff    	mov    %eax,-0x528(%rbp)
    7f8535d0c580:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f8535d0c586:	0b c1                	or     %ecx,%eax
    7f8535d0c588:	8b 8d 58 fe ff ff    	mov    -0x1a8(%rbp),%ecx
    7f8535d0c58e:	23 c1                	and    %ecx,%eax
    7f8535d0c590:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7f8535d0c596:	23 c8                	and    %eax,%ecx
    7f8535d0c598:	b8 01 00 00 00       	mov    $0x1,%eax
    7f8535d0c59d:	3b c3                	cmp    %ebx,%eax
    7f8535d0c59f:	0f 94 c0             	sete   %al
    7f8535d0c5a2:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c5a5:	89 85 c8 fa ff ff    	mov    %eax,-0x538(%rbp)
    7f8535d0c5ab:	8b 95 40 fb ff ff    	mov    -0x4c0(%rbp),%edx
    7f8535d0c5b1:	23 c2                	and    %edx,%eax
    7f8535d0c5b3:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7f8535d0c5b9:	85 c9                	test   %ecx,%ecx
    7f8535d0c5bb:	0f 85 1f 00 00 00    	jne    0x7f8535d0c5e0
    7f8535d0c5c1:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7f8535d0c5c7:	85 c0                	test   %eax,%eax
    7f8535d0c5c9:	0f 85 20 00 00 00    	jne    0x7f8535d0c5ef
    7f8535d0c5cf:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7f8535d0c5d5:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7f8535d0c5db:	e9 19 00 00 00       	jmpq   0x7f8535d0c5f9
    7f8535d0c5e0:	c7 85 b8 fa ff ff 01 	movl   $0x1,-0x548(%rbp)
    7f8535d0c5e7:	00 00 00 
    7f8535d0c5ea:	e9 0a 00 00 00       	jmpq   0x7f8535d0c5f9
    7f8535d0c5ef:	c7 85 b8 fa ff ff 00 	movl   $0x0,-0x548(%rbp)
    7f8535d0c5f6:	00 00 00 
    7f8535d0c5f9:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7f8535d0c5ff:	85 c9                	test   %ecx,%ecx
    7f8535d0c601:	0f 94 c0             	sete   %al
    7f8535d0c604:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c607:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f8535d0c60a:	8b d2                	mov    %edx,%edx
    7f8535d0c60c:	48 89 95 b0 fa ff ff 	mov    %rdx,-0x550(%rbp)
    7f8535d0c613:	48 8d 95 b0 fa ff ff 	lea    -0x550(%rbp),%rdx
    7f8535d0c61a:	49 8b f7             	mov    %r15,%rsi
    7f8535d0c61d:	48 81 c6 88 12 00 00 	add    $0x1288,%rsi
    7f8535d0c624:	b9 20 00 00 00       	mov    $0x20,%ecx
    7f8535d0c629:	48 89 95 a8 fa ff ff 	mov    %rdx,-0x558(%rbp)
    7f8535d0c630:	48 89 b5 a0 fa ff ff 	mov    %rsi,-0x560(%rbp)
    7f8535d0c637:	be 00 02 00 00       	mov    $0x200,%esi
    7f8535d0c63c:	48 8b bd a0 fa ff ff 	mov    -0x560(%rbp),%rdi
    7f8535d0c643:	89 85 98 fa ff ff    	mov    %eax,-0x568(%rbp)
    7f8535d0c649:	b8 08 00 00 00       	mov    $0x8,%eax
    7f8535d0c64e:	e8 ad a1 b3 ff       	callq  0x7f8535846800
    7f8535d0c653:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f8535d0c659:	c1 e0 05             	shl    $0x5,%eax
    7f8535d0c65c:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f8535d0c661:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c664:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7f8535d0c66b:	49 8b d7             	mov    %r15,%rdx
    7f8535d0c66e:	48 81 c2 c8 12 00 00 	add    $0x12c8,%rdx
    7f8535d0c675:	44 8b c0             	mov    %eax,%r8d
    7f8535d0c678:	48 89 8d 90 fa ff ff 	mov    %rcx,-0x570(%rbp)
    7f8535d0c67f:	b9 00 02 00 00       	mov    $0x200,%ecx
    7f8535d0c684:	48 89 95 88 fa ff ff 	mov    %rdx,-0x578(%rbp)
    7f8535d0c68b:	48 8b 95 90 fa ff ff 	mov    -0x570(%rbp),%rdx
    7f8535d0c692:	be 00 02 00 00       	mov    $0x200,%esi
    7f8535d0c697:	48 8b bd 88 fa ff ff 	mov    -0x578(%rbp),%rdi
    7f8535d0c69e:	89 85 80 fa ff ff    	mov    %eax,-0x580(%rbp)
    7f8535d0c6a4:	b8 08 00 00 00       	mov    $0x8,%eax
    7f8535d0c6a9:	e8 22 8d b3 ff       	callq  0x7f85358453d0
    7f8535d0c6ae:	49 8b 87 c8 12 00 00 	mov    0x12c8(%r15),%rax
    7f8535d0c6b5:	49 8b 8f 78 0f 00 00 	mov    0xf78(%r15),%rcx
    7f8535d0c6bc:	48 0b c1             	or     %rcx,%rax
    7f8535d0c6bf:	49 89 87 08 13 00 00 	mov    %rax,0x1308(%r15)
    7f8535d0c6c6:	49 8b 87 d0 12 00 00 	mov    0x12d0(%r15),%rax
    7f8535d0c6cd:	49 8b 8f 80 0f 00 00 	mov    0xf80(%r15),%rcx
    7f8535d0c6d4:	48 0b c1             	or     %rcx,%rax
    7f8535d0c6d7:	49 89 87 10 13 00 00 	mov    %rax,0x1310(%r15)
    7f8535d0c6de:	49 8b 87 d8 12 00 00 	mov    0x12d8(%r15),%rax
    7f8535d0c6e5:	49 8b 8f 88 0f 00 00 	mov    0xf88(%r15),%rcx
    7f8535d0c6ec:	48 0b c1             	or     %rcx,%rax
    7f8535d0c6ef:	49 89 87 18 13 00 00 	mov    %rax,0x1318(%r15)
    7f8535d0c6f6:	49 8b 87 e0 12 00 00 	mov    0x12e0(%r15),%rax
    7f8535d0c6fd:	49 8b 8f 90 0f 00 00 	mov    0xf90(%r15),%rcx
    7f8535d0c704:	48 0b c1             	or     %rcx,%rax
    7f8535d0c707:	49 89 87 20 13 00 00 	mov    %rax,0x1320(%r15)
    7f8535d0c70e:	49 8b 87 e8 12 00 00 	mov    0x12e8(%r15),%rax
    7f8535d0c715:	49 8b 8f 98 0f 00 00 	mov    0xf98(%r15),%rcx
    7f8535d0c71c:	48 0b c1             	or     %rcx,%rax
    7f8535d0c71f:	49 89 87 28 13 00 00 	mov    %rax,0x1328(%r15)
    7f8535d0c726:	49 8b 87 f0 12 00 00 	mov    0x12f0(%r15),%rax
    7f8535d0c72d:	49 8b 8f a0 0f 00 00 	mov    0xfa0(%r15),%rcx
    7f8535d0c734:	48 0b c1             	or     %rcx,%rax
    7f8535d0c737:	49 89 87 30 13 00 00 	mov    %rax,0x1330(%r15)
    7f8535d0c73e:	49 8b 87 f8 12 00 00 	mov    0x12f8(%r15),%rax
    7f8535d0c745:	49 8b 8f a8 0f 00 00 	mov    0xfa8(%r15),%rcx
    7f8535d0c74c:	48 0b c1             	or     %rcx,%rax
    7f8535d0c74f:	49 89 87 38 13 00 00 	mov    %rax,0x1338(%r15)
    7f8535d0c756:	49 8b 87 00 13 00 00 	mov    0x1300(%r15),%rax
    7f8535d0c75d:	49 8b 8f b0 0f 00 00 	mov    0xfb0(%r15),%rcx
    7f8535d0c764:	48 0b c1             	or     %rcx,%rax
    7f8535d0c767:	49 89 87 40 13 00 00 	mov    %rax,0x1340(%r15)
    7f8535d0c76e:	8b 85 98 fa ff ff    	mov    -0x568(%rbp),%eax
    7f8535d0c774:	85 c0                	test   %eax,%eax
    7f8535d0c776:	0f 85 36 00 00 00    	jne    0x7f8535d0c7b2
    7f8535d0c77c:	49 8b c7             	mov    %r15,%rax
    7f8535d0c77f:	48 05 88 11 00 00    	add    $0x1188,%rax
    7f8535d0c785:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c788:	48 81 c1 08 13 00 00 	add    $0x1308,%rcx
    7f8535d0c78f:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0c792:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0c795:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0c799:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0c79d:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0c7a1:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0c7a5:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0c7a9:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0c7ad:	e9 31 00 00 00       	jmpq   0x7f8535d0c7e3
    7f8535d0c7b2:	49 8b c7             	mov    %r15,%rax
    7f8535d0c7b5:	48 05 88 11 00 00    	add    $0x1188,%rax
    7f8535d0c7bb:	49 8b cf             	mov    %r15,%rcx
    7f8535d0c7be:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7f8535d0c7c5:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0c7c8:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0c7cb:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0c7cf:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0c7d3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0c7d7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0c7db:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0c7df:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0c7e3:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f8535d0c7e6:	23 85 50 fe ff ff    	and    -0x1b0(%rbp),%eax
    7f8535d0c7ec:	89 85 78 fa ff ff    	mov    %eax,-0x588(%rbp)
    7f8535d0c7f2:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f8535d0c7f8:	83 f8 0f             	cmp    $0xf,%eax
    7f8535d0c7fb:	0f 94 c0             	sete   %al
    7f8535d0c7fe:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c801:	23 45 e0             	and    -0x20(%rbp),%eax
    7f8535d0c804:	85 c0                	test   %eax,%eax
    7f8535d0c806:	0f 85 1f 00 00 00    	jne    0x7f8535d0c82b
    7f8535d0c80c:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7f8535d0c812:	85 c0                	test   %eax,%eax
    7f8535d0c814:	0f 85 20 00 00 00    	jne    0x7f8535d0c83a
    7f8535d0c81a:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7f8535d0c820:	89 85 70 fa ff ff    	mov    %eax,-0x590(%rbp)
    7f8535d0c826:	e9 19 00 00 00       	jmpq   0x7f8535d0c844
    7f8535d0c82b:	c7 85 70 fa ff ff 01 	movl   $0x1,-0x590(%rbp)
    7f8535d0c832:	00 00 00 
    7f8535d0c835:	e9 0a 00 00 00       	jmpq   0x7f8535d0c844
    7f8535d0c83a:	c7 85 70 fa ff ff 00 	movl   $0x0,-0x590(%rbp)
    7f8535d0c841:	00 00 00 
    7f8535d0c844:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f8535d0c84a:	ff c0                	inc    %eax
    7f8535d0c84c:	83 e0 0f             	and    $0xf,%eax
    7f8535d0c84f:	89 85 68 fa ff ff    	mov    %eax,-0x598(%rbp)
    7f8535d0c855:	41 8b c4             	mov    %r12d,%eax
    7f8535d0c858:	0b 85 d8 fa ff ff    	or     -0x528(%rbp),%eax
    7f8535d0c85e:	89 85 60 fa ff ff    	mov    %eax,-0x5a0(%rbp)
    7f8535d0c864:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f8535d0c86a:	23 85 d0 fa ff ff    	and    -0x530(%rbp),%eax
    7f8535d0c870:	8b 8d 28 fb ff ff    	mov    -0x4d8(%rbp),%ecx
    7f8535d0c876:	23 8d 40 fb ff ff    	and    -0x4c0(%rbp),%ecx
    7f8535d0c87c:	85 c9                	test   %ecx,%ecx
    7f8535d0c87e:	0f 94 c2             	sete   %dl
    7f8535d0c881:	0f b6 d2             	movzbl %dl,%edx
    7f8535d0c884:	89 95 58 fa ff ff    	mov    %edx,-0x5a8(%rbp)
    7f8535d0c88a:	23 d0                	and    %eax,%edx
    7f8535d0c88c:	8b f3                	mov    %ebx,%esi
    7f8535d0c88e:	ff c6                	inc    %esi
    7f8535d0c890:	83 e6 1f             	and    $0x1f,%esi
    7f8535d0c893:	89 b5 50 fa ff ff    	mov    %esi,-0x5b0(%rbp)
    7f8535d0c899:	89 85 48 fa ff ff    	mov    %eax,-0x5b8(%rbp)
    7f8535d0c89f:	85 c0                	test   %eax,%eax
    7f8535d0c8a1:	0f 94 c0             	sete   %al
    7f8535d0c8a4:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c8a7:	89 8d 40 fa ff ff    	mov    %ecx,-0x5c0(%rbp)
    7f8535d0c8ad:	89 85 38 fa ff ff    	mov    %eax,-0x5c8(%rbp)
    7f8535d0c8b3:	23 c8                	and    %eax,%ecx
    7f8535d0c8b5:	89 8d 30 fa ff ff    	mov    %ecx,-0x5d0(%rbp)
    7f8535d0c8bb:	8b c3                	mov    %ebx,%eax
    7f8535d0c8bd:	ff c8                	dec    %eax
    7f8535d0c8bf:	83 e0 1f             	and    $0x1f,%eax
    7f8535d0c8c2:	89 85 28 fa ff ff    	mov    %eax,-0x5d8(%rbp)
    7f8535d0c8c8:	85 d2                	test   %edx,%edx
    7f8535d0c8ca:	0f 85 1b 00 00 00    	jne    0x7f8535d0c8eb
    7f8535d0c8d0:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7f8535d0c8d6:	85 c0                	test   %eax,%eax
    7f8535d0c8d8:	0f 85 1e 00 00 00    	jne    0x7f8535d0c8fc
    7f8535d0c8de:	8b c3                	mov    %ebx,%eax
    7f8535d0c8e0:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7f8535d0c8e6:	e9 1d 00 00 00       	jmpq   0x7f8535d0c908
    7f8535d0c8eb:	8b 85 50 fa ff ff    	mov    -0x5b0(%rbp),%eax
    7f8535d0c8f1:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7f8535d0c8f7:	e9 0c 00 00 00       	jmpq   0x7f8535d0c908
    7f8535d0c8fc:	8b 85 28 fa ff ff    	mov    -0x5d8(%rbp),%eax
    7f8535d0c902:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7f8535d0c908:	83 fb 01             	cmp    $0x1,%ebx
    7f8535d0c90b:	0f 94 c0             	sete   %al
    7f8535d0c90e:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c911:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7f8535d0c917:	23 c1                	and    %ecx,%eax
    7f8535d0c919:	23 85 38 fa ff ff    	and    -0x5c8(%rbp),%eax
    7f8535d0c91f:	85 c9                	test   %ecx,%ecx
    7f8535d0c921:	0f 94 c1             	sete   %cl
    7f8535d0c924:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0c927:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7f8535d0c92d:	23 ca                	and    %edx,%ecx
    7f8535d0c92f:	89 8d 18 fa ff ff    	mov    %ecx,-0x5e8(%rbp)
    7f8535d0c935:	85 c0                	test   %eax,%eax
    7f8535d0c937:	0f 85 1f 00 00 00    	jne    0x7f8535d0c95c
    7f8535d0c93d:	8b 85 18 fa ff ff    	mov    -0x5e8(%rbp),%eax
    7f8535d0c943:	85 c0                	test   %eax,%eax
    7f8535d0c945:	0f 85 20 00 00 00    	jne    0x7f8535d0c96b
    7f8535d0c94b:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7f8535d0c951:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7f8535d0c957:	e9 19 00 00 00       	jmpq   0x7f8535d0c975
    7f8535d0c95c:	c7 85 10 fa ff ff 01 	movl   $0x1,-0x5f0(%rbp)
    7f8535d0c963:	00 00 00 
    7f8535d0c966:	e9 0a 00 00 00       	jmpq   0x7f8535d0c975
    7f8535d0c96b:	c7 85 10 fa ff ff 00 	movl   $0x0,-0x5f0(%rbp)
    7f8535d0c972:	00 00 00 
    7f8535d0c975:	83 fb 0f             	cmp    $0xf,%ebx
    7f8535d0c978:	0f 94 c0             	sete   %al
    7f8535d0c97b:	0f b6 c0             	movzbl %al,%eax
    7f8535d0c97e:	23 85 48 fa ff ff    	and    -0x5b8(%rbp),%eax
    7f8535d0c984:	23 85 58 fa ff ff    	and    -0x5a8(%rbp),%eax
    7f8535d0c98a:	85 c0                	test   %eax,%eax
    7f8535d0c98c:	0f 85 1f 00 00 00    	jne    0x7f8535d0c9b1
    7f8535d0c992:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7f8535d0c998:	85 c0                	test   %eax,%eax
    7f8535d0c99a:	0f 85 20 00 00 00    	jne    0x7f8535d0c9c0
    7f8535d0c9a0:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f8535d0c9a6:	89 85 08 fa ff ff    	mov    %eax,-0x5f8(%rbp)
    7f8535d0c9ac:	e9 19 00 00 00       	jmpq   0x7f8535d0c9ca
    7f8535d0c9b1:	c7 85 08 fa ff ff 01 	movl   $0x1,-0x5f8(%rbp)
    7f8535d0c9b8:	00 00 00 
    7f8535d0c9bb:	e9 0a 00 00 00       	jmpq   0x7f8535d0c9ca
    7f8535d0c9c0:	c7 85 08 fa ff ff 00 	movl   $0x0,-0x5f8(%rbp)
    7f8535d0c9c7:	00 00 00 
    7f8535d0c9ca:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f8535d0c9d0:	ff c0                	inc    %eax
    7f8535d0c9d2:	83 e0 0f             	and    $0xf,%eax
    7f8535d0c9d5:	89 85 00 fa ff ff    	mov    %eax,-0x600(%rbp)
    7f8535d0c9db:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f8535d0c9e1:	83 c0 02             	add    $0x2,%eax
    7f8535d0c9e4:	83 e0 0f             	and    $0xf,%eax
    7f8535d0c9e7:	89 85 f8 f9 ff ff    	mov    %eax,-0x608(%rbp)
    7f8535d0c9ed:	8b 85 c8 fa ff ff    	mov    -0x538(%rbp),%eax
    7f8535d0c9f3:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7f8535d0c9f9:	23 c1                	and    %ecx,%eax
    7f8535d0c9fb:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7f8535d0ca01:	0b c2                	or     %edx,%eax
    7f8535d0ca03:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7f8535d0ca09:	23 c2                	and    %edx,%eax
    7f8535d0ca0b:	89 85 f0 f9 ff ff    	mov    %eax,-0x610(%rbp)
    7f8535d0ca11:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f8535d0ca17:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7f8535d0ca1d:	85 c9                	test   %ecx,%ecx
    7f8535d0ca1f:	0f 85 0c 00 00 00    	jne    0x7f8535d0ca31
    7f8535d0ca25:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f8535d0ca2b:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7f8535d0ca31:	49 8b c7             	mov    %r15,%rax
    7f8535d0ca34:	48 05 00 08 00 00    	add    $0x800,%rax
    7f8535d0ca3a:	49 8b cf             	mov    %r15,%rcx
    7f8535d0ca3d:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7f8535d0ca44:	8b 95 e8 f9 ff ff    	mov    -0x618(%rbp),%edx
    7f8535d0ca4a:	c1 e2 06             	shl    $0x6,%edx
    7f8535d0ca4d:	8b d2                	mov    %edx,%edx
    7f8535d0ca4f:	48 03 c2             	add    %rdx,%rax
    7f8535d0ca52:	0f 10 00             	movups (%rax),%xmm0
    7f8535d0ca55:	0f 11 01             	movups %xmm0,(%rcx)
    7f8535d0ca58:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7f8535d0ca5c:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7f8535d0ca60:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7f8535d0ca64:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7f8535d0ca68:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7f8535d0ca6c:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7f8535d0ca70:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7f8535d0ca76:	85 c0                	test   %eax,%eax
    7f8535d0ca78:	0f 84 3f 00 00 00    	je     0x7f8535d0cabd
    7f8535d0ca7e:	49 8b c7             	mov    %r15,%rax
    7f8535d0ca81:	48 05 00 08 00 00    	add    $0x800,%rax
    7f8535d0ca87:	49 8b cf             	mov    %r15,%rcx
    7f8535d0ca8a:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7f8535d0ca91:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7f8535d0ca97:	c1 e2 06             	shl    $0x6,%edx
    7f8535d0ca9a:	8b d2                	mov    %edx,%edx
    7f8535d0ca9c:	48 03 c2             	add    %rdx,%rax
    7f8535d0ca9f:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0caa2:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0caa5:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0caa9:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0caad:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cab1:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cab5:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cab9:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cabd:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f8535d0cac3:	85 c0                	test   %eax,%eax
    7f8535d0cac5:	0f 84 3c 00 00 00    	je     0x7f8535d0cb07
    7f8535d0cacb:	49 8b c7             	mov    %r15,%rax
    7f8535d0cace:	48 05 00 04 00 00    	add    $0x400,%rax
    7f8535d0cad4:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7f8535d0cada:	c1 e1 06             	shl    $0x6,%ecx
    7f8535d0cadd:	8b c9                	mov    %ecx,%ecx
    7f8535d0cadf:	48 03 c1             	add    %rcx,%rax
    7f8535d0cae2:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7f8535d0cae9:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0caec:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0caef:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0caf3:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0caf7:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cafb:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0caff:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cb03:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cb07:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7f8535d0cb0d:	85 c0                	test   %eax,%eax
    7f8535d0cb0f:	0f 84 30 00 00 00    	je     0x7f8535d0cb45
    7f8535d0cb15:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f8535d0cb18:	c1 e0 06             	shl    $0x6,%eax
    7f8535d0cb1b:	8b c0                	mov    %eax,%eax
    7f8535d0cb1d:	49 03 c7             	add    %r15,%rax
    7f8535d0cb20:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7f8535d0cb27:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0cb2a:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0cb2d:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0cb31:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0cb35:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cb39:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cb3d:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cb41:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cb45:	49 8b c7             	mov    %r15,%rax
    7f8535d0cb48:	48 05 48 10 00 00    	add    $0x1048,%rax
    7f8535d0cb4e:	49 8b cf             	mov    %r15,%rcx
    7f8535d0cb51:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7f8535d0cb58:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0cb5b:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0cb5e:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0cb62:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0cb66:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cb6a:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cb6e:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cb72:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cb76:	49 8b c7             	mov    %r15,%rax
    7f8535d0cb79:	48 05 08 10 00 00    	add    $0x1008,%rax
    7f8535d0cb7f:	49 8b cf             	mov    %r15,%rcx
    7f8535d0cb82:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7f8535d0cb89:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0cb8c:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0cb8f:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0cb93:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0cb97:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cb9b:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cb9f:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cba3:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cba7:	45 85 e4             	test   %r12d,%r12d
    7f8535d0cbaa:	0f 84 44 00 00 00    	je     0x7f8535d0cbf4
    7f8535d0cbb0:	41 c7 87 00 10 00 00 	movl   $0x0,0x1000(%r15)
    7f8535d0cbb7:	00 00 00 00 
    7f8535d0cbbb:	c7 85 90 fe ff ff 00 	movl   $0x0,-0x170(%rbp)
    7f8535d0cbc2:	00 00 00 
    7f8535d0cbc5:	41 c7 87 f0 0f 00 00 	movl   $0x0,0xff0(%r15)
    7f8535d0cbcc:	00 00 00 00 
    7f8535d0cbd0:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7f8535d0cbd7:	00 00 00 
    7f8535d0cbda:	41 c7 87 f8 0f 00 00 	movl   $0x1,0xff8(%r15)
    7f8535d0cbe1:	01 00 00 00 
    7f8535d0cbe5:	c7 85 98 fe ff ff 01 	movl   $0x1,-0x168(%rbp)
    7f8535d0cbec:	00 00 00 
    7f8535d0cbef:	e9 47 00 00 00       	jmpq   0x7f8535d0cc3b
    7f8535d0cbf4:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7f8535d0cbfa:	41 89 87 00 10 00 00 	mov    %eax,0x1000(%r15)
    7f8535d0cc01:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f8535d0cc07:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7f8535d0cc0d:	85 c0                	test   %eax,%eax
    7f8535d0cc0f:	0f 84 26 00 00 00    	je     0x7f8535d0cc3b
    7f8535d0cc15:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f8535d0cc1b:	41 89 87 f0 0f 00 00 	mov    %eax,0xff0(%r15)
    7f8535d0cc22:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f8535d0cc28:	8b 85 f8 f9 ff ff    	mov    -0x608(%rbp),%eax
    7f8535d0cc2e:	41 89 87 f8 0f 00 00 	mov    %eax,0xff8(%r15)
    7f8535d0cc35:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f8535d0cc3b:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f8535d0cc41:	85 c0                	test   %eax,%eax
    7f8535d0cc43:	0f 84 1a 00 00 00    	je     0x7f8535d0cc63
    7f8535d0cc49:	41 c7 87 e8 0f 00 00 	movl   $0x0,0xfe8(%r15)
    7f8535d0cc50:	00 00 00 00 
    7f8535d0cc54:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7f8535d0cc5b:	00 00 00 
    7f8535d0cc5e:	e9 21 00 00 00       	jmpq   0x7f8535d0cc84
    7f8535d0cc63:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7f8535d0cc69:	85 c0                	test   %eax,%eax
    7f8535d0cc6b:	0f 84 13 00 00 00    	je     0x7f8535d0cc84
    7f8535d0cc71:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7f8535d0cc77:	41 89 87 e8 0f 00 00 	mov    %eax,0xfe8(%r15)
    7f8535d0cc7e:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f8535d0cc84:	45 85 e4             	test   %r12d,%r12d
    7f8535d0cc87:	0f 84 51 00 00 00    	je     0x7f8535d0ccde
    7f8535d0cc8d:	41 c7 87 e0 0f 00 00 	movl   $0x0,0xfe0(%r15)
    7f8535d0cc94:	00 00 00 00 
    7f8535d0cc98:	c7 85 b0 fe ff ff 00 	movl   $0x0,-0x150(%rbp)
    7f8535d0cc9f:	00 00 00 
    7f8535d0cca2:	41 c7 87 d8 0f 00 00 	movl   $0x1,0xfd8(%r15)
    7f8535d0cca9:	01 00 00 00 
    7f8535d0ccad:	c7 85 b8 fe ff ff 01 	movl   $0x1,-0x148(%rbp)
    7f8535d0ccb4:	00 00 00 
    7f8535d0ccb7:	41 c7 87 d0 0f 00 00 	movl   $0x0,0xfd0(%r15)
    7f8535d0ccbe:	00 00 00 00 
    7f8535d0ccc2:	33 db                	xor    %ebx,%ebx
    7f8535d0ccc4:	41 c7 87 c8 0f 00 00 	movl   $0x0,0xfc8(%r15)
    7f8535d0cccb:	00 00 00 00 
    7f8535d0cccf:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7f8535d0ccd6:	00 00 00 
    7f8535d0ccd9:	e9 49 00 00 00       	jmpq   0x7f8535d0cd27
    7f8535d0ccde:	8b 85 08 fa ff ff    	mov    -0x5f8(%rbp),%eax
    7f8535d0cce4:	41 89 87 e0 0f 00 00 	mov    %eax,0xfe0(%r15)
    7f8535d0cceb:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f8535d0ccf1:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7f8535d0ccf7:	41 89 87 d8 0f 00 00 	mov    %eax,0xfd8(%r15)
    7f8535d0ccfe:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f8535d0cd04:	8b 85 20 fa ff ff    	mov    -0x5e0(%rbp),%eax
    7f8535d0cd0a:	41 89 87 d0 0f 00 00 	mov    %eax,0xfd0(%r15)
    7f8535d0cd11:	48 8b d8             	mov    %rax,%rbx
    7f8535d0cd14:	8b 85 e0 fa ff ff    	mov    -0x520(%rbp),%eax
    7f8535d0cd1a:	41 89 87 c8 0f 00 00 	mov    %eax,0xfc8(%r15)
    7f8535d0cd21:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f8535d0cd27:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7f8535d0cd2d:	85 c0                	test   %eax,%eax
    7f8535d0cd2f:	0f 84 1a 00 00 00    	je     0x7f8535d0cd4f
    7f8535d0cd35:	41 c7 87 c0 0f 00 00 	movl   $0x0,0xfc0(%r15)
    7f8535d0cd3c:	00 00 00 00 
    7f8535d0cd40:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7f8535d0cd47:	00 00 00 
    7f8535d0cd4a:	e9 21 00 00 00       	jmpq   0x7f8535d0cd70
    7f8535d0cd4f:	8b 85 78 fa ff ff    	mov    -0x588(%rbp),%eax
    7f8535d0cd55:	85 c0                	test   %eax,%eax
    7f8535d0cd57:	0f 84 13 00 00 00    	je     0x7f8535d0cd70
    7f8535d0cd5d:	8b 85 68 fa ff ff    	mov    -0x598(%rbp),%eax
    7f8535d0cd63:	41 89 87 c0 0f 00 00 	mov    %eax,0xfc0(%r15)
    7f8535d0cd6a:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f8535d0cd70:	45 85 e4             	test   %r12d,%r12d
    7f8535d0cd73:	0f 84 1a 00 00 00    	je     0x7f8535d0cd93
    7f8535d0cd79:	41 c7 87 b8 0f 00 00 	movl   $0x0,0xfb8(%r15)
    7f8535d0cd80:	00 00 00 00 
    7f8535d0cd84:	c7 85 d0 fe ff ff 00 	movl   $0x0,-0x130(%rbp)
    7f8535d0cd8b:	00 00 00 
    7f8535d0cd8e:	e9 13 00 00 00       	jmpq   0x7f8535d0cda6
    7f8535d0cd93:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7f8535d0cd99:	41 89 87 b8 0f 00 00 	mov    %eax,0xfb8(%r15)
    7f8535d0cda0:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f8535d0cda6:	8b 85 78 fa ff ff    	mov    -0x588(%rbp),%eax
    7f8535d0cdac:	85 c0                	test   %eax,%eax
    7f8535d0cdae:	0f 84 31 00 00 00    	je     0x7f8535d0cde5
    7f8535d0cdb4:	49 8b c7             	mov    %r15,%rax
    7f8535d0cdb7:	48 05 78 0f 00 00    	add    $0xf78,%rax
    7f8535d0cdbd:	49 8b cf             	mov    %r15,%rcx
    7f8535d0cdc0:	48 81 c1 88 11 00 00 	add    $0x1188,%rcx
    7f8535d0cdc7:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0cdca:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0cdcd:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0cdd1:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0cdd5:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cdd9:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cddd:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cde1:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cde5:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f8535d0cdeb:	85 c0                	test   %eax,%eax
    7f8535d0cded:	0f 84 13 00 00 00    	je     0x7f8535d0ce06
    7f8535d0cdf3:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7f8535d0cdf9:	41 89 87 70 0f 00 00 	mov    %eax,0xf70(%r15)
    7f8535d0ce00:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f8535d0ce06:	45 85 e4             	test   %r12d,%r12d
    7f8535d0ce09:	0f 84 5a 00 00 00    	je     0x7f8535d0ce69
    7f8535d0ce0f:	41 c7 87 68 0f 00 00 	movl   $0x0,0xf68(%r15)
    7f8535d0ce16:	00 00 00 00 
    7f8535d0ce1a:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7f8535d0ce21:	00 00 00 
    7f8535d0ce24:	41 c7 87 60 0f 00 00 	movl   $0x0,0xf60(%r15)
    7f8535d0ce2b:	00 00 00 00 
    7f8535d0ce2f:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7f8535d0ce36:	00 00 00 
    7f8535d0ce39:	41 c7 87 58 0f 00 00 	movl   $0x0,0xf58(%r15)
    7f8535d0ce40:	00 00 00 00 
    7f8535d0ce44:	c7 85 f0 fe ff ff 00 	movl   $0x0,-0x110(%rbp)
    7f8535d0ce4b:	00 00 00 
    7f8535d0ce4e:	49 c7 87 50 0f 00 00 	movq   $0x0,0xf50(%r15)
    7f8535d0ce55:	00 00 00 00 
    7f8535d0ce59:	48 c7 85 f8 fe ff ff 	movq   $0x0,-0x108(%rbp)
    7f8535d0ce60:	00 00 00 00 
    7f8535d0ce64:	e9 4e 00 00 00       	jmpq   0x7f8535d0ceb7
    7f8535d0ce69:	8b 85 b8 fa ff ff    	mov    -0x548(%rbp),%eax
    7f8535d0ce6f:	41 89 87 68 0f 00 00 	mov    %eax,0xf68(%r15)
    7f8535d0ce76:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f8535d0ce7c:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7f8535d0ce82:	41 89 87 60 0f 00 00 	mov    %eax,0xf60(%r15)
    7f8535d0ce89:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f8535d0ce8f:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7f8535d0ce95:	41 89 87 58 0f 00 00 	mov    %eax,0xf58(%r15)
    7f8535d0ce9c:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f8535d0cea2:	48 8b 85 30 fb ff ff 	mov    -0x4d0(%rbp),%rax
    7f8535d0cea9:	49 89 87 50 0f 00 00 	mov    %rax,0xf50(%r15)
    7f8535d0ceb0:	48 89 85 f8 fe ff ff 	mov    %rax,-0x108(%rbp)
    7f8535d0ceb7:	49 8b c7             	mov    %r15,%rax
    7f8535d0ceba:	48 05 10 0f 00 00    	add    $0xf10,%rax
    7f8535d0cec0:	49 8b cf             	mov    %r15,%rcx
    7f8535d0cec3:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7f8535d0ceca:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0cecd:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0ced0:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0ced4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0ced8:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cedc:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cee0:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cee4:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cee8:	49 8b c7             	mov    %r15,%rax
    7f8535d0ceeb:	48 05 d0 0e 00 00    	add    $0xed0,%rax
    7f8535d0cef1:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7f8535d0cef8:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0cefb:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0cefe:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0cf02:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0cf06:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0cf0a:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0cf0e:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0cf12:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0cf16:	45 85 e4             	test   %r12d,%r12d
    7f8535d0cf19:	0f 84 44 00 00 00    	je     0x7f8535d0cf63
    7f8535d0cf1f:	41 c7 87 c8 0e 00 00 	movl   $0x0,0xec8(%r15)
    7f8535d0cf26:	00 00 00 00 
    7f8535d0cf2a:	c7 85 00 ff ff ff 00 	movl   $0x0,-0x100(%rbp)
    7f8535d0cf31:	00 00 00 
    7f8535d0cf34:	41 c7 87 b8 0e 00 00 	movl   $0x0,0xeb8(%r15)
    7f8535d0cf3b:	00 00 00 00 
    7f8535d0cf3f:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7f8535d0cf46:	00 00 00 
    7f8535d0cf49:	41 c7 87 c0 0e 00 00 	movl   $0x1,0xec0(%r15)
    7f8535d0cf50:	01 00 00 00 
    7f8535d0cf54:	c7 85 08 ff ff ff 01 	movl   $0x1,-0xf8(%rbp)
    7f8535d0cf5b:	00 00 00 
    7f8535d0cf5e:	e9 47 00 00 00       	jmpq   0x7f8535d0cfaa
    7f8535d0cf63:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7f8535d0cf69:	41 89 87 c8 0e 00 00 	mov    %eax,0xec8(%r15)
    7f8535d0cf70:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f8535d0cf76:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7f8535d0cf7c:	85 c0                	test   %eax,%eax
    7f8535d0cf7e:	0f 84 26 00 00 00    	je     0x7f8535d0cfaa
    7f8535d0cf84:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f8535d0cf8a:	41 89 87 b8 0e 00 00 	mov    %eax,0xeb8(%r15)
    7f8535d0cf91:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f8535d0cf97:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7f8535d0cf9d:	41 89 87 c0 0e 00 00 	mov    %eax,0xec0(%r15)
    7f8535d0cfa4:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f8535d0cfaa:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f8535d0cfb0:	85 c0                	test   %eax,%eax
    7f8535d0cfb2:	0f 84 1a 00 00 00    	je     0x7f8535d0cfd2
    7f8535d0cfb8:	41 c7 87 b0 0e 00 00 	movl   $0x0,0xeb0(%r15)
    7f8535d0cfbf:	00 00 00 00 
    7f8535d0cfc3:	c7 85 18 ff ff ff 00 	movl   $0x0,-0xe8(%rbp)
    7f8535d0cfca:	00 00 00 
    7f8535d0cfcd:	e9 21 00 00 00       	jmpq   0x7f8535d0cff3
    7f8535d0cfd2:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f8535d0cfd8:	85 c0                	test   %eax,%eax
    7f8535d0cfda:	0f 84 13 00 00 00    	je     0x7f8535d0cff3
    7f8535d0cfe0:	8b 85 78 fb ff ff    	mov    -0x488(%rbp),%eax
    7f8535d0cfe6:	41 89 87 b0 0e 00 00 	mov    %eax,0xeb0(%r15)
    7f8535d0cfed:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f8535d0cff3:	45 85 e4             	test   %r12d,%r12d
    7f8535d0cff6:	0f 84 44 00 00 00    	je     0x7f8535d0d040
    7f8535d0cffc:	41 c7 87 a8 0e 00 00 	movl   $0x0,0xea8(%r15)
    7f8535d0d003:	00 00 00 00 
    7f8535d0d007:	c7 85 20 ff ff ff 00 	movl   $0x0,-0xe0(%rbp)
    7f8535d0d00e:	00 00 00 
    7f8535d0d011:	41 c7 87 a0 0e 00 00 	movl   $0x1,0xea0(%r15)
    7f8535d0d018:	01 00 00 00 
    7f8535d0d01c:	c7 85 28 ff ff ff 01 	movl   $0x1,-0xd8(%rbp)
    7f8535d0d023:	00 00 00 
    7f8535d0d026:	41 c7 87 98 0e 00 00 	movl   $0x0,0xe98(%r15)
    7f8535d0d02d:	00 00 00 00 
    7f8535d0d031:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7f8535d0d038:	00 00 00 
    7f8535d0d03b:	e9 39 00 00 00       	jmpq   0x7f8535d0d079
    7f8535d0d040:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7f8535d0d046:	41 89 87 a8 0e 00 00 	mov    %eax,0xea8(%r15)
    7f8535d0d04d:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f8535d0d053:	8b 85 88 fb ff ff    	mov    -0x478(%rbp),%eax
    7f8535d0d059:	41 89 87 a0 0e 00 00 	mov    %eax,0xea0(%r15)
    7f8535d0d060:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f8535d0d066:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7f8535d0d06c:	41 89 87 98 0e 00 00 	mov    %eax,0xe98(%r15)
    7f8535d0d073:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f8535d0d079:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f8535d0d07f:	85 c0                	test   %eax,%eax
    7f8535d0d081:	0f 84 1a 00 00 00    	je     0x7f8535d0d0a1
    7f8535d0d087:	41 c7 87 90 0e 00 00 	movl   $0x0,0xe90(%r15)
    7f8535d0d08e:	00 00 00 00 
    7f8535d0d092:	c7 85 38 ff ff ff 00 	movl   $0x0,-0xc8(%rbp)
    7f8535d0d099:	00 00 00 
    7f8535d0d09c:	e9 21 00 00 00       	jmpq   0x7f8535d0d0c2
    7f8535d0d0a1:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7f8535d0d0a7:	85 c0                	test   %eax,%eax
    7f8535d0d0a9:	0f 84 13 00 00 00    	je     0x7f8535d0d0c2
    7f8535d0d0af:	8b 85 d8 fb ff ff    	mov    -0x428(%rbp),%eax
    7f8535d0d0b5:	41 89 87 90 0e 00 00 	mov    %eax,0xe90(%r15)
    7f8535d0d0bc:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f8535d0d0c2:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d0c5:	0f 84 1a 00 00 00    	je     0x7f8535d0d0e5
    7f8535d0d0cb:	41 c7 87 88 0e 00 00 	movl   $0x0,0xe88(%r15)
    7f8535d0d0d2:	00 00 00 00 
    7f8535d0d0d6:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7f8535d0d0dd:	00 00 00 
    7f8535d0d0e0:	e9 13 00 00 00       	jmpq   0x7f8535d0d0f8
    7f8535d0d0e5:	8b 85 e0 fb ff ff    	mov    -0x420(%rbp),%eax
    7f8535d0d0eb:	41 89 87 88 0e 00 00 	mov    %eax,0xe88(%r15)
    7f8535d0d0f2:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f8535d0d0f8:	49 8b c7             	mov    %r15,%rax
    7f8535d0d0fb:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7f8535d0d101:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d104:	48 81 c1 08 11 00 00 	add    $0x1108,%rcx
    7f8535d0d10b:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d10e:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d111:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d115:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d119:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d11d:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d121:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d125:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d129:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d12c:	0f 84 6f 00 00 00    	je     0x7f8535d0d1a1
    7f8535d0d132:	41 c7 87 40 0e 00 00 	movl   $0x0,0xe40(%r15)
    7f8535d0d139:	00 00 00 00 
    7f8535d0d13d:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7f8535d0d144:	00 00 00 
    7f8535d0d147:	41 c7 87 38 0e 00 00 	movl   $0x0,0xe38(%r15)
    7f8535d0d14e:	00 00 00 00 
    7f8535d0d152:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7f8535d0d159:	00 00 00 
    7f8535d0d15c:	41 c7 87 30 0e 00 00 	movl   $0x0,0xe30(%r15)
    7f8535d0d163:	00 00 00 00 
    7f8535d0d167:	c7 85 58 ff ff ff 00 	movl   $0x0,-0xa8(%rbp)
    7f8535d0d16e:	00 00 00 
    7f8535d0d171:	41 c7 87 28 0e 00 00 	movl   $0x0,0xe28(%r15)
    7f8535d0d178:	00 00 00 00 
    7f8535d0d17c:	c7 85 60 ff ff ff 00 	movl   $0x0,-0xa0(%rbp)
    7f8535d0d183:	00 00 00 
    7f8535d0d186:	49 c7 87 20 0e 00 00 	movq   $0x0,0xe20(%r15)
    7f8535d0d18d:	00 00 00 00 
    7f8535d0d191:	48 c7 85 68 ff ff ff 	movq   $0x0,-0x98(%rbp)
    7f8535d0d198:	00 00 00 00 
    7f8535d0d19c:	e9 61 00 00 00       	jmpq   0x7f8535d0d202
    7f8535d0d1a1:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7f8535d0d1a7:	41 89 87 40 0e 00 00 	mov    %eax,0xe40(%r15)
    7f8535d0d1ae:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f8535d0d1b4:	8b 85 08 fc ff ff    	mov    -0x3f8(%rbp),%eax
    7f8535d0d1ba:	41 89 87 38 0e 00 00 	mov    %eax,0xe38(%r15)
    7f8535d0d1c1:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f8535d0d1c7:	8b 85 20 fc ff ff    	mov    -0x3e0(%rbp),%eax
    7f8535d0d1cd:	41 89 87 30 0e 00 00 	mov    %eax,0xe30(%r15)
    7f8535d0d1d4:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f8535d0d1da:	8b 85 30 fc ff ff    	mov    -0x3d0(%rbp),%eax
    7f8535d0d1e0:	41 89 87 28 0e 00 00 	mov    %eax,0xe28(%r15)
    7f8535d0d1e7:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f8535d0d1ed:	48 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%rax
    7f8535d0d1f4:	49 89 87 20 0e 00 00 	mov    %rax,0xe20(%r15)
    7f8535d0d1fb:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
    7f8535d0d202:	49 8b c7             	mov    %r15,%rax
    7f8535d0d205:	48 05 e0 0d 00 00    	add    $0xde0,%rax
    7f8535d0d20b:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d20e:	48 81 c1 00 0c 00 00 	add    $0xc00,%rcx
    7f8535d0d215:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d218:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d21b:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d21f:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d223:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d227:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d22b:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d22f:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d233:	49 8b c7             	mov    %r15,%rax
    7f8535d0d236:	48 05 a0 0d 00 00    	add    $0xda0,%rax
    7f8535d0d23c:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7f8535d0d243:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d246:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d249:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d24d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d251:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d255:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d259:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d25d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d261:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d264:	0f 84 41 00 00 00    	je     0x7f8535d0d2ab
    7f8535d0d26a:	41 c7 87 98 0d 00 00 	movl   $0x0,0xd98(%r15)
    7f8535d0d271:	00 00 00 00 
    7f8535d0d275:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7f8535d0d27c:	00 00 00 
    7f8535d0d27f:	41 c7 87 88 0d 00 00 	movl   $0x0,0xd88(%r15)
    7f8535d0d286:	00 00 00 00 
    7f8535d0d28a:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
    7f8535d0d291:	41 c7 87 90 0d 00 00 	movl   $0x1,0xd90(%r15)
    7f8535d0d298:	01 00 00 00 
    7f8535d0d29c:	c7 85 78 ff ff ff 01 	movl   $0x1,-0x88(%rbp)
    7f8535d0d2a3:	00 00 00 
    7f8535d0d2a6:	e9 44 00 00 00       	jmpq   0x7f8535d0d2ef
    7f8535d0d2ab:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7f8535d0d2b1:	41 89 87 98 0d 00 00 	mov    %eax,0xd98(%r15)
    7f8535d0d2b8:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f8535d0d2be:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7f8535d0d2c4:	85 c0                	test   %eax,%eax
    7f8535d0d2c6:	0f 84 23 00 00 00    	je     0x7f8535d0d2ef
    7f8535d0d2cc:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7f8535d0d2d2:	41 89 87 88 0d 00 00 	mov    %eax,0xd88(%r15)
    7f8535d0d2d9:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f8535d0d2dc:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7f8535d0d2e2:	41 89 87 90 0d 00 00 	mov    %eax,0xd90(%r15)
    7f8535d0d2e9:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f8535d0d2ef:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f8535d0d2f5:	85 c0                	test   %eax,%eax
    7f8535d0d2f7:	0f 84 17 00 00 00    	je     0x7f8535d0d314
    7f8535d0d2fd:	41 c7 87 80 0d 00 00 	movl   $0x0,0xd80(%r15)
    7f8535d0d304:	00 00 00 00 
    7f8535d0d308:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
    7f8535d0d30f:	e9 1e 00 00 00       	jmpq   0x7f8535d0d332
    7f8535d0d314:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7f8535d0d31a:	85 c0                	test   %eax,%eax
    7f8535d0d31c:	0f 84 10 00 00 00    	je     0x7f8535d0d332
    7f8535d0d322:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7f8535d0d328:	41 89 87 80 0d 00 00 	mov    %eax,0xd80(%r15)
    7f8535d0d32f:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f8535d0d332:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d335:	0f 84 3b 00 00 00    	je     0x7f8535d0d376
    7f8535d0d33b:	41 c7 87 78 0d 00 00 	movl   $0x0,0xd78(%r15)
    7f8535d0d342:	00 00 00 00 
    7f8535d0d346:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7f8535d0d34d:	41 c7 87 70 0d 00 00 	movl   $0x1,0xd70(%r15)
    7f8535d0d354:	01 00 00 00 
    7f8535d0d358:	c7 45 98 01 00 00 00 	movl   $0x1,-0x68(%rbp)
    7f8535d0d35f:	41 c7 87 68 0d 00 00 	movl   $0x0,0xd68(%r15)
    7f8535d0d366:	00 00 00 00 
    7f8535d0d36a:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7f8535d0d371:	e9 30 00 00 00       	jmpq   0x7f8535d0d3a6
    7f8535d0d376:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7f8535d0d37c:	41 89 87 78 0d 00 00 	mov    %eax,0xd78(%r15)
    7f8535d0d383:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f8535d0d386:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7f8535d0d38c:	41 89 87 70 0d 00 00 	mov    %eax,0xd70(%r15)
    7f8535d0d393:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f8535d0d396:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7f8535d0d39c:	41 89 87 68 0d 00 00 	mov    %eax,0xd68(%r15)
    7f8535d0d3a3:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f8535d0d3a6:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f8535d0d3ac:	85 c0                	test   %eax,%eax
    7f8535d0d3ae:	0f 84 17 00 00 00    	je     0x7f8535d0d3cb
    7f8535d0d3b4:	41 c7 87 60 0d 00 00 	movl   $0x0,0xd60(%r15)
    7f8535d0d3bb:	00 00 00 00 
    7f8535d0d3bf:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
    7f8535d0d3c6:	e9 1e 00 00 00       	jmpq   0x7f8535d0d3e9
    7f8535d0d3cb:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7f8535d0d3d1:	85 c0                	test   %eax,%eax
    7f8535d0d3d3:	0f 84 10 00 00 00    	je     0x7f8535d0d3e9
    7f8535d0d3d9:	8b 85 28 fd ff ff    	mov    -0x2d8(%rbp),%eax
    7f8535d0d3df:	41 89 87 60 0d 00 00 	mov    %eax,0xd60(%r15)
    7f8535d0d3e6:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f8535d0d3e9:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d3ec:	0f 84 17 00 00 00    	je     0x7f8535d0d409
    7f8535d0d3f2:	41 c7 87 58 0d 00 00 	movl   $0x0,0xd58(%r15)
    7f8535d0d3f9:	00 00 00 00 
    7f8535d0d3fd:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7f8535d0d404:	e9 10 00 00 00       	jmpq   0x7f8535d0d419
    7f8535d0d409:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7f8535d0d40f:	41 89 87 58 0d 00 00 	mov    %eax,0xd58(%r15)
    7f8535d0d416:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f8535d0d419:	49 8b c7             	mov    %r15,%rax
    7f8535d0d41c:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7f8535d0d422:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d425:	48 81 c1 88 10 00 00 	add    $0x1088,%rcx
    7f8535d0d42c:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d42f:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d432:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d436:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d43a:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d43e:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d442:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d446:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d44a:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d44d:	0f 84 7d 00 00 00    	je     0x7f8535d0d4d0
    7f8535d0d453:	41 c7 87 10 0d 00 00 	movl   $0x0,0xd10(%r15)
    7f8535d0d45a:	00 00 00 00 
    7f8535d0d45e:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7f8535d0d465:	41 c7 87 08 0d 00 00 	movl   $0x0,0xd08(%r15)
    7f8535d0d46c:	00 00 00 00 
    7f8535d0d470:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    7f8535d0d477:	41 c7 87 00 0d 00 00 	movl   $0x0,0xd00(%r15)
    7f8535d0d47e:	00 00 00 00 
    7f8535d0d482:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
    7f8535d0d489:	41 c7 87 f8 0c 00 00 	movl   $0x0,0xcf8(%r15)
    7f8535d0d490:	00 00 00 00 
    7f8535d0d494:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7f8535d0d49b:	49 c7 87 f0 0c 00 00 	movq   $0x0,0xcf0(%r15)
    7f8535d0d4a2:	00 00 00 00 
    7f8535d0d4a6:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
    7f8535d0d4ad:	00 
    7f8535d0d4ae:	41 c7 87 e0 0c 00 00 	movl   $0x0,0xce0(%r15)
    7f8535d0d4b5:	00 00 00 00 
    7f8535d0d4b9:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
    7f8535d0d4c0:	41 c7 87 e8 0c 00 00 	movl   $0x0,0xce8(%r15)
    7f8535d0d4c7:	00 00 00 00 
    7f8535d0d4cb:	e9 7e 00 00 00       	jmpq   0x7f8535d0d54e
    7f8535d0d4d0:	8b 85 50 fd ff ff    	mov    -0x2b0(%rbp),%eax
    7f8535d0d4d6:	41 89 87 10 0d 00 00 	mov    %eax,0xd10(%r15)
    7f8535d0d4dd:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f8535d0d4e0:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7f8535d0d4e6:	41 89 87 08 0d 00 00 	mov    %eax,0xd08(%r15)
    7f8535d0d4ed:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f8535d0d4f0:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7f8535d0d4f6:	41 89 87 00 0d 00 00 	mov    %eax,0xd00(%r15)
    7f8535d0d4fd:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f8535d0d500:	8b 85 a0 fd ff ff    	mov    -0x260(%rbp),%eax
    7f8535d0d506:	41 89 87 f8 0c 00 00 	mov    %eax,0xcf8(%r15)
    7f8535d0d50d:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f8535d0d510:	48 8b 85 f0 fd ff ff 	mov    -0x210(%rbp),%rax
    7f8535d0d517:	49 89 87 f0 0c 00 00 	mov    %rax,0xcf0(%r15)
    7f8535d0d51e:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    7f8535d0d522:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f8535d0d528:	85 c0                	test   %eax,%eax
    7f8535d0d52a:	0f 84 1e 00 00 00    	je     0x7f8535d0d54e
    7f8535d0d530:	41 8b 87 e8 0c 00 00 	mov    0xce8(%r15),%eax
    7f8535d0d537:	41 89 87 e0 0c 00 00 	mov    %eax,0xce0(%r15)
    7f8535d0d53e:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f8535d0d541:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f8535d0d547:	41 89 87 e8 0c 00 00 	mov    %eax,0xce8(%r15)
    7f8535d0d54e:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f8535d0d554:	85 c0                	test   %eax,%eax
    7f8535d0d556:	0f 84 1e 00 00 00    	je     0x7f8535d0d57a
    7f8535d0d55c:	41 8b 87 d8 0c 00 00 	mov    0xcd8(%r15),%eax
    7f8535d0d563:	41 89 87 d0 0c 00 00 	mov    %eax,0xcd0(%r15)
    7f8535d0d56a:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f8535d0d56d:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7f8535d0d573:	41 89 87 d8 0c 00 00 	mov    %eax,0xcd8(%r15)
    7f8535d0d57a:	45 85 e4             	test   %r12d,%r12d
    7f8535d0d57d:	0f 84 25 00 00 00    	je     0x7f8535d0d5a8
    7f8535d0d583:	41 c7 87 c8 0c 00 00 	movl   $0x0,0xcc8(%r15)
    7f8535d0d58a:	00 00 00 00 
    7f8535d0d58e:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7f8535d0d595:	41 c7 87 c0 0c 00 00 	movl   $0x0,0xcc0(%r15)
    7f8535d0d59c:	00 00 00 00 
    7f8535d0d5a0:	45 33 ed             	xor    %r13d,%r13d
    7f8535d0d5a3:	e9 20 00 00 00       	jmpq   0x7f8535d0d5c8
    7f8535d0d5a8:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7f8535d0d5ae:	41 89 87 c8 0c 00 00 	mov    %eax,0xcc8(%r15)
    7f8535d0d5b5:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f8535d0d5b8:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f8535d0d5be:	41 89 87 c0 0c 00 00 	mov    %eax,0xcc0(%r15)
    7f8535d0d5c5:	4c 8b e8             	mov    %rax,%r13
    7f8535d0d5c8:	45 85 ed             	test   %r13d,%r13d
    7f8535d0d5cb:	0f 94 c0             	sete   %al
    7f8535d0d5ce:	0f b6 c0             	movzbl %al,%eax
    7f8535d0d5d1:	49 8b 8e a0 00 00 00 	mov    0xa0(%r14),%rcx
    7f8535d0d5d8:	89 01                	mov    %eax,(%rcx)
    7f8535d0d5da:	41 83 fd 02          	cmp    $0x2,%r13d
    7f8535d0d5de:	0f 94 c0             	sete   %al
    7f8535d0d5e1:	0f b6 c0             	movzbl %al,%eax
    7f8535d0d5e4:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7f8535d0d5ea:	85 c9                	test   %ecx,%ecx
    7f8535d0d5ec:	0f 94 c1             	sete   %cl
    7f8535d0d5ef:	0f b6 c9             	movzbl %cl,%ecx
    7f8535d0d5f2:	23 c1                	and    %ecx,%eax
    7f8535d0d5f4:	49 8b 8e a8 00 00 00 	mov    0xa8(%r14),%rcx
    7f8535d0d5fb:	89 01                	mov    %eax,(%rcx)
    7f8535d0d5fd:	49 8b 86 b0 00 00 00 	mov    0xb0(%r14),%rax
    7f8535d0d604:	48 8b 8d f8 fe ff ff 	mov    -0x108(%rbp),%rcx
    7f8535d0d60b:	48 89 08             	mov    %rcx,(%rax)
    7f8535d0d60e:	49 8b 86 b8 00 00 00 	mov    0xb8(%r14),%rax
    7f8535d0d615:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7f8535d0d61b:	49 8b 86 c0 00 00 00 	mov    0xc0(%r14),%rax
    7f8535d0d622:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7f8535d0d628:	89 08                	mov    %ecx,(%rax)
    7f8535d0d62a:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7f8535d0d630:	85 c0                	test   %eax,%eax
    7f8535d0d632:	0f 85 36 00 00 00    	jne    0x7f8535d0d66e
    7f8535d0d638:	49 8b c7             	mov    %r15,%rax
    7f8535d0d63b:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7f8535d0d641:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d644:	48 81 c1 48 10 00 00 	add    $0x1048,%rcx
    7f8535d0d64b:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d64e:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d651:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d655:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d659:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d65d:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d661:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d665:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d669:	e9 31 00 00 00       	jmpq   0x7f8535d0d69f
    7f8535d0d66e:	49 8b c7             	mov    %r15,%rax
    7f8535d0d671:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7f8535d0d677:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d67a:	48 81 c1 08 10 00 00 	add    $0x1008,%rcx
    7f8535d0d681:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d684:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d687:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d68b:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d68f:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d693:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d697:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d69b:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d69f:	49 8b 86 c8 00 00 00 	mov    0xc8(%r14),%rax
    7f8535d0d6a6:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d6a9:	48 81 c1 c8 11 00 00 	add    $0x11c8,%rcx
    7f8535d0d6b0:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d6b3:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d6b6:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d6ba:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d6be:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d6c2:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d6c6:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d6ca:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d6ce:	49 8b 86 d0 00 00 00 	mov    0xd0(%r14),%rax
    7f8535d0d6d5:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7f8535d0d6dc:	49 8b 86 d8 00 00 00 	mov    0xd8(%r14),%rax
    7f8535d0d6e3:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7f8535d0d6e9:	89 08                	mov    %ecx,(%rax)
    7f8535d0d6eb:	49 8b 86 e0 00 00 00 	mov    0xe0(%r14),%rax
    7f8535d0d6f2:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
    7f8535d0d6f6:	48 89 08             	mov    %rcx,(%rax)
    7f8535d0d6f9:	49 8b 86 e8 00 00 00 	mov    0xe8(%r14),%rax
    7f8535d0d700:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f8535d0d703:	89 08                	mov    %ecx,(%rax)
    7f8535d0d705:	49 8b 86 f0 00 00 00 	mov    0xf0(%r14),%rax
    7f8535d0d70c:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7f8535d0d712:	49 8b 86 f8 00 00 00 	mov    0xf8(%r14),%rax
    7f8535d0d719:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d71c:	48 81 c1 50 13 00 00 	add    $0x1350,%rcx
    7f8535d0d723:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d726:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d729:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d72d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d731:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d735:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d739:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d73d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d741:	49 8b 86 00 01 00 00 	mov    0x100(%r14),%rax
    7f8535d0d748:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7f8535d0d74f:	49 8b 86 08 01 00 00 	mov    0x108(%r14),%rax
    7f8535d0d756:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f8535d0d759:	89 08                	mov    %ecx,(%rax)
    7f8535d0d75b:	49 8b 86 10 01 00 00 	mov    0x110(%r14),%rax
    7f8535d0d762:	48 8b 8d 68 ff ff ff 	mov    -0x98(%rbp),%rcx
    7f8535d0d769:	48 89 08             	mov    %rcx,(%rax)
    7f8535d0d76c:	49 8b 86 18 01 00 00 	mov    0x118(%r14),%rax
    7f8535d0d773:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7f8535d0d779:	89 08                	mov    %ecx,(%rax)
    7f8535d0d77b:	49 8b 86 20 01 00 00 	mov    0x120(%r14),%rax
    7f8535d0d782:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7f8535d0d788:	49 8b 86 28 01 00 00 	mov    0x128(%r14),%rax
    7f8535d0d78f:	49 8b cf             	mov    %r15,%rcx
    7f8535d0d792:	48 81 c1 50 13 00 00 	add    $0x1350,%rcx
    7f8535d0d799:	0f 10 01             	movups (%rcx),%xmm0
    7f8535d0d79c:	0f 11 00             	movups %xmm0,(%rax)
    7f8535d0d79f:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f8535d0d7a3:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f8535d0d7a7:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f8535d0d7ab:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f8535d0d7af:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f8535d0d7b3:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f8535d0d7b7:	49 8b 86 30 01 00 00 	mov    0x130(%r14),%rax
    7f8535d0d7be:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7f8535d0d7c5:	49 8b 86 38 01 00 00 	mov    0x138(%r14),%rax
    7f8535d0d7cc:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7f8535d0d7d2:	89 08                	mov    %ecx,(%rax)
    7f8535d0d7d4:	33 c0                	xor    %eax,%eax
    7f8535d0d7d6:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f8535d0d7da:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f8535d0d7df:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f8535d0d7e4:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f8535d0d7e9:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f8535d0d7ee:	48 8b e5             	mov    %rbp,%rsp
    7f8535d0d7f1:	5d                   	pop    %rbp
    7f8535d0d7f2:	c3                   	retq   

end

