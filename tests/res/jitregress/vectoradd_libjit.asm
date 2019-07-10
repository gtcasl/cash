function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f9bb08df12d <.text>:
    7f9bb08df12d:	55                   	push   %rbp
    7f9bb08df12e:	48 8b ec             	mov    %rsp,%rbp
    7f9bb08df131:	48 81 ec 40 06 00 00 	sub    $0x640,%rsp
    7f9bb08df138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f9bb08df13c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f9bb08df141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f9bb08df146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f9bb08df14b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f9bb08df150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f9bb08df154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f9bb08df158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f9bb08df15c:	4c 8b 30             	mov    (%rax),%r14
    7f9bb08df15f:	45 8b af c0 0c 00 00 	mov    0xcc0(%r15),%r13d
    7f9bb08df166:	41 8b 87 c8 0c 00 00 	mov    0xcc8(%r15),%eax
    7f9bb08df16d:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f9bb08df170:	41 8b 87 d0 0c 00 00 	mov    0xcd0(%r15),%eax
    7f9bb08df177:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f9bb08df17a:	41 8b 87 e0 0c 00 00 	mov    0xce0(%r15),%eax
    7f9bb08df181:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f9bb08df184:	49 8b 87 f0 0c 00 00 	mov    0xcf0(%r15),%rax
    7f9bb08df18b:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    7f9bb08df18f:	41 8b 87 f8 0c 00 00 	mov    0xcf8(%r15),%eax
    7f9bb08df196:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f9bb08df199:	41 8b 87 00 0d 00 00 	mov    0xd00(%r15),%eax
    7f9bb08df1a0:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f9bb08df1a3:	41 8b 87 08 0d 00 00 	mov    0xd08(%r15),%eax
    7f9bb08df1aa:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f9bb08df1ad:	41 8b 87 10 0d 00 00 	mov    0xd10(%r15),%eax
    7f9bb08df1b4:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f9bb08df1b7:	41 8b 87 58 0d 00 00 	mov    0xd58(%r15),%eax
    7f9bb08df1be:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f9bb08df1c1:	41 8b 87 60 0d 00 00 	mov    0xd60(%r15),%eax
    7f9bb08df1c8:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f9bb08df1cb:	41 8b 87 68 0d 00 00 	mov    0xd68(%r15),%eax
    7f9bb08df1d2:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f9bb08df1d5:	41 8b 87 70 0d 00 00 	mov    0xd70(%r15),%eax
    7f9bb08df1dc:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f9bb08df1df:	41 8b 87 78 0d 00 00 	mov    0xd78(%r15),%eax
    7f9bb08df1e6:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f9bb08df1e9:	41 8b 87 80 0d 00 00 	mov    0xd80(%r15),%eax
    7f9bb08df1f0:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f9bb08df1f3:	41 8b 87 88 0d 00 00 	mov    0xd88(%r15),%eax
    7f9bb08df1fa:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f9bb08df1fd:	41 8b 87 90 0d 00 00 	mov    0xd90(%r15),%eax
    7f9bb08df204:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f9bb08df20a:	41 8b 87 98 0d 00 00 	mov    0xd98(%r15),%eax
    7f9bb08df211:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f9bb08df217:	49 8b 87 20 0e 00 00 	mov    0xe20(%r15),%rax
    7f9bb08df21e:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
    7f9bb08df225:	41 8b 87 28 0e 00 00 	mov    0xe28(%r15),%eax
    7f9bb08df22c:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f9bb08df232:	41 8b 87 30 0e 00 00 	mov    0xe30(%r15),%eax
    7f9bb08df239:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f9bb08df23f:	41 8b 87 38 0e 00 00 	mov    0xe38(%r15),%eax
    7f9bb08df246:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f9bb08df24c:	41 8b 87 40 0e 00 00 	mov    0xe40(%r15),%eax
    7f9bb08df253:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f9bb08df259:	41 8b 87 88 0e 00 00 	mov    0xe88(%r15),%eax
    7f9bb08df260:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f9bb08df266:	41 8b 87 90 0e 00 00 	mov    0xe90(%r15),%eax
    7f9bb08df26d:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f9bb08df273:	41 8b 87 98 0e 00 00 	mov    0xe98(%r15),%eax
    7f9bb08df27a:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f9bb08df280:	41 8b 87 a0 0e 00 00 	mov    0xea0(%r15),%eax
    7f9bb08df287:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f9bb08df28d:	41 8b 87 a8 0e 00 00 	mov    0xea8(%r15),%eax
    7f9bb08df294:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f9bb08df29a:	41 8b 87 b0 0e 00 00 	mov    0xeb0(%r15),%eax
    7f9bb08df2a1:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f9bb08df2a7:	41 8b 87 b8 0e 00 00 	mov    0xeb8(%r15),%eax
    7f9bb08df2ae:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f9bb08df2b4:	41 8b 87 c0 0e 00 00 	mov    0xec0(%r15),%eax
    7f9bb08df2bb:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f9bb08df2c1:	41 8b 87 c8 0e 00 00 	mov    0xec8(%r15),%eax
    7f9bb08df2c8:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f9bb08df2ce:	49 8b 87 50 0f 00 00 	mov    0xf50(%r15),%rax
    7f9bb08df2d5:	48 89 85 f8 fe ff ff 	mov    %rax,-0x108(%rbp)
    7f9bb08df2dc:	41 8b 87 58 0f 00 00 	mov    0xf58(%r15),%eax
    7f9bb08df2e3:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f9bb08df2e9:	41 8b 87 60 0f 00 00 	mov    0xf60(%r15),%eax
    7f9bb08df2f0:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f9bb08df2f6:	41 8b 87 68 0f 00 00 	mov    0xf68(%r15),%eax
    7f9bb08df2fd:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f9bb08df303:	41 8b 87 70 0f 00 00 	mov    0xf70(%r15),%eax
    7f9bb08df30a:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f9bb08df310:	41 8b 87 b8 0f 00 00 	mov    0xfb8(%r15),%eax
    7f9bb08df317:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f9bb08df31d:	41 8b 87 c0 0f 00 00 	mov    0xfc0(%r15),%eax
    7f9bb08df324:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f9bb08df32a:	41 8b 87 c8 0f 00 00 	mov    0xfc8(%r15),%eax
    7f9bb08df331:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f9bb08df337:	41 8b 9f d0 0f 00 00 	mov    0xfd0(%r15),%ebx
    7f9bb08df33e:	41 8b 87 d8 0f 00 00 	mov    0xfd8(%r15),%eax
    7f9bb08df345:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f9bb08df34b:	41 8b 87 e0 0f 00 00 	mov    0xfe0(%r15),%eax
    7f9bb08df352:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f9bb08df358:	41 8b 87 e8 0f 00 00 	mov    0xfe8(%r15),%eax
    7f9bb08df35f:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f9bb08df365:	41 8b 87 f0 0f 00 00 	mov    0xff0(%r15),%eax
    7f9bb08df36c:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f9bb08df372:	41 8b 87 f8 0f 00 00 	mov    0xff8(%r15),%eax
    7f9bb08df379:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f9bb08df37f:	41 8b 87 00 10 00 00 	mov    0x1000(%r15),%eax
    7f9bb08df386:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f9bb08df38c:	49 8b 86 90 00 00 00 	mov    0x90(%r14),%rax
    7f9bb08df393:	8b 00                	mov    (%rax),%eax
    7f9bb08df395:	41 8b 8f 88 13 00 00 	mov    0x1388(%r15),%ecx
    7f9bb08df39c:	33 c8                	xor    %eax,%ecx
    7f9bb08df39e:	23 c8                	and    %eax,%ecx
    7f9bb08df3a0:	41 89 87 88 13 00 00 	mov    %eax,0x1388(%r15)
    7f9bb08df3a7:	85 c9                	test   %ecx,%ecx
    7f9bb08df3a9:	0f 84 08 23 00 00    	je     0x7f9bb08e16b7
    7f9bb08df3af:	49 8b 46 20          	mov    0x20(%r14),%rax
    7f9bb08df3b3:	8b 00                	mov    (%rax),%eax
    7f9bb08df3b5:	c7 85 88 fe ff ff 01 	movl   $0x1,-0x178(%rbp)
    7f9bb08df3bc:	00 00 00 
    7f9bb08df3bf:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7f9bb08df3c5:	85 c0                	test   %eax,%eax
    7f9bb08df3c7:	0f 85 09 00 00 00    	jne    0x7f9bb08df3d6
    7f9bb08df3cd:	41 8b c5             	mov    %r13d,%eax
    7f9bb08df3d0:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7f9bb08df3d6:	33 c0                	xor    %eax,%eax
    7f9bb08df3d8:	3b 45 f0             	cmp    -0x10(%rbp),%eax
    7f9bb08df3db:	0f 94 c0             	sete   %al
    7f9bb08df3de:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df3e1:	c7 85 78 fe ff ff 02 	movl   $0x2,-0x188(%rbp)
    7f9bb08df3e8:	00 00 00 
    7f9bb08df3eb:	85 c0                	test   %eax,%eax
    7f9bb08df3ed:	0f 85 09 00 00 00    	jne    0x7f9bb08df3fc
    7f9bb08df3f3:	41 8b c5             	mov    %r13d,%eax
    7f9bb08df3f6:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7f9bb08df3fc:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7f9bb08df402:	85 c0                	test   %eax,%eax
    7f9bb08df404:	0f 94 c0             	sete   %al
    7f9bb08df407:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df40a:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7f9bb08df40e:	8b 09                	mov    (%rcx),%ecx
    7f9bb08df410:	23 c1                	and    %ecx,%eax
    7f9bb08df412:	c7 85 70 fe ff ff 00 	movl   $0x0,-0x190(%rbp)
    7f9bb08df419:	00 00 00 
    7f9bb08df41c:	85 c0                	test   %eax,%eax
    7f9bb08df41e:	0f 85 09 00 00 00    	jne    0x7f9bb08df42d
    7f9bb08df424:	41 8b c5             	mov    %r13d,%eax
    7f9bb08df427:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7f9bb08df42d:	45 85 ed             	test   %r13d,%r13d
    7f9bb08df430:	0f 84 22 00 00 00    	je     0x7f9bb08df458
    7f9bb08df436:	41 83 fd 01          	cmp    $0x1,%r13d
    7f9bb08df43a:	0f 84 29 00 00 00    	je     0x7f9bb08df469
    7f9bb08df440:	41 83 fd 02          	cmp    $0x2,%r13d
    7f9bb08df444:	0f 84 30 00 00 00    	je     0x7f9bb08df47a
    7f9bb08df44a:	41 8b c5             	mov    %r13d,%eax
    7f9bb08df44d:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f9bb08df453:	e9 2e 00 00 00       	jmpq   0x7f9bb08df486
    7f9bb08df458:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7f9bb08df45e:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f9bb08df464:	e9 1d 00 00 00       	jmpq   0x7f9bb08df486
    7f9bb08df469:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7f9bb08df46f:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f9bb08df475:	e9 0c 00 00 00       	jmpq   0x7f9bb08df486
    7f9bb08df47a:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f9bb08df480:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f9bb08df486:	49 8b 86 98 00 00 00 	mov    0x98(%r14),%rax
    7f9bb08df48d:	44 8b 20             	mov    (%rax),%r12d
    7f9bb08df490:	45 85 ed             	test   %r13d,%r13d
    7f9bb08df493:	0f 94 c0             	sete   %al
    7f9bb08df496:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df499:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7f9bb08df49f:	23 c1                	and    %ecx,%eax
    7f9bb08df4a1:	49 8b 4e 18          	mov    0x18(%r14),%rcx
    7f9bb08df4a5:	8b 09                	mov    (%rcx),%ecx
    7f9bb08df4a7:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7f9bb08df4ad:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f9bb08df4b3:	85 c9                	test   %ecx,%ecx
    7f9bb08df4b5:	0f 94 c1             	sete   %cl
    7f9bb08df4b8:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08df4bb:	8b 95 b0 fe ff ff    	mov    -0x150(%rbp),%edx
    7f9bb08df4c1:	85 d2                	test   %edx,%edx
    7f9bb08df4c3:	0f 94 c2             	sete   %dl
    7f9bb08df4c6:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08df4c9:	89 95 58 fe ff ff    	mov    %edx,-0x1a8(%rbp)
    7f9bb08df4cf:	0b ca                	or     %edx,%ecx
    7f9bb08df4d1:	89 8d 50 fe ff ff    	mov    %ecx,-0x1b0(%rbp)
    7f9bb08df4d7:	23 4d e0             	and    -0x20(%rbp),%ecx
    7f9bb08df4da:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7f9bb08df4e0:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7f9bb08df4e3:	ff c9                	dec    %ecx
    7f9bb08df4e5:	89 8d 40 fe ff ff    	mov    %ecx,-0x1c0(%rbp)
    7f9bb08df4eb:	89 85 38 fe ff ff    	mov    %eax,-0x1c8(%rbp)
    7f9bb08df4f1:	85 c0                	test   %eax,%eax
    7f9bb08df4f3:	0f 85 1c 00 00 00    	jne    0x7f9bb08df515
    7f9bb08df4f9:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f9bb08df4ff:	85 c0                	test   %eax,%eax
    7f9bb08df501:	0f 85 1f 00 00 00    	jne    0x7f9bb08df526
    7f9bb08df507:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f9bb08df50a:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7f9bb08df510:	e9 1d 00 00 00       	jmpq   0x7f9bb08df532
    7f9bb08df515:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f9bb08df51b:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7f9bb08df521:	e9 0c 00 00 00       	jmpq   0x7f9bb08df532
    7f9bb08df526:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7f9bb08df52c:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7f9bb08df532:	41 8b 87 18 0d 00 00 	mov    0xd18(%r15),%eax
    7f9bb08df539:	41 8b 8f 48 0e 00 00 	mov    0xe48(%r15),%ecx
    7f9bb08df540:	03 c1                	add    %ecx,%eax
    7f9bb08df542:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7f9bb08df548:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f9bb08df54b:	85 c0                	test   %eax,%eax
    7f9bb08df54d:	0f 94 c0             	sete   %al
    7f9bb08df550:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df553:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7f9bb08df559:	0b c1                	or     %ecx,%eax
    7f9bb08df55b:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7f9bb08df561:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f9bb08df564:	23 85 40 ff ff ff    	and    -0xc0(%rbp),%eax
    7f9bb08df56a:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%rbp)
    7f9bb08df570:	49 8b 46 08          	mov    0x8(%r14),%rax
    7f9bb08df574:	48 8b 00             	mov    (%rax),%rax
    7f9bb08df577:	48 89 85 10 fe ff ff 	mov    %rax,-0x1f0(%rbp)
    7f9bb08df57e:	49 8b 46 60          	mov    0x60(%r14),%rax
    7f9bb08df582:	8b 00                	mov    (%rax),%eax
    7f9bb08df584:	85 c0                	test   %eax,%eax
    7f9bb08df586:	0f 94 c0             	sete   %al
    7f9bb08df589:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df58c:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f9bb08df58f:	23 c1                	and    %ecx,%eax
    7f9bb08df591:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7f9bb08df597:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f9bb08df59a:	8b c0                	mov    %eax,%eax
    7f9bb08df59c:	48 c1 e0 06          	shl    $0x6,%rax
    7f9bb08df5a0:	48 89 85 00 fe ff ff 	mov    %rax,-0x200(%rbp)
    7f9bb08df5a7:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
    7f9bb08df5ab:	48 03 c1             	add    %rcx,%rax
    7f9bb08df5ae:	48 89 85 f8 fd ff ff 	mov    %rax,-0x208(%rbp)
    7f9bb08df5b5:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08df5bb:	85 c0                	test   %eax,%eax
    7f9bb08df5bd:	0f 85 1e 00 00 00    	jne    0x7f9bb08df5e1
    7f9bb08df5c3:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f9bb08df5c9:	85 c0                	test   %eax,%eax
    7f9bb08df5cb:	0f 85 23 00 00 00    	jne    0x7f9bb08df5f4
    7f9bb08df5d1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    7f9bb08df5d5:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7f9bb08df5dc:	e9 21 00 00 00       	jmpq   0x7f9bb08df602
    7f9bb08df5e1:	48 8b 85 10 fe ff ff 	mov    -0x1f0(%rbp),%rax
    7f9bb08df5e8:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7f9bb08df5ef:	e9 0e 00 00 00       	jmpq   0x7f9bb08df602
    7f9bb08df5f4:	48 8b 85 f8 fd ff ff 	mov    -0x208(%rbp),%rax
    7f9bb08df5fb:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7f9bb08df602:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f9bb08df605:	85 c0                	test   %eax,%eax
    7f9bb08df607:	0f 94 c0             	sete   %al
    7f9bb08df60a:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df60d:	8b 55 b0             	mov    -0x50(%rbp),%edx
    7f9bb08df610:	85 d2                	test   %edx,%edx
    7f9bb08df612:	0f 94 c1             	sete   %cl
    7f9bb08df615:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08df618:	8b 75 a8             	mov    -0x58(%rbp),%esi
    7f9bb08df61b:	83 fe 0f             	cmp    $0xf,%esi
    7f9bb08df61e:	40 0f 94 c6          	sete   %sil
    7f9bb08df622:	40 0f b6 f6          	movzbl %sil,%esi
    7f9bb08df626:	8b bd 40 ff ff ff    	mov    -0xc0(%rbp),%edi
    7f9bb08df62c:	85 ff                	test   %edi,%edi
    7f9bb08df62e:	40 0f 94 c7          	sete   %dil
    7f9bb08df632:	40 0f b6 ff          	movzbl %dil,%edi
    7f9bb08df636:	23 d7                	and    %edi,%edx
    7f9bb08df638:	85 d2                	test   %edx,%edx
    7f9bb08df63a:	0f 94 c2             	sete   %dl
    7f9bb08df63d:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08df640:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7f9bb08df646:	23 d7                	and    %edi,%edx
    7f9bb08df648:	89 95 e8 fd ff ff    	mov    %edx,-0x218(%rbp)
    7f9bb08df64e:	23 f2                	and    %edx,%esi
    7f9bb08df650:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7f9bb08df656:	89 b5 d8 fd ff ff    	mov    %esi,-0x228(%rbp)
    7f9bb08df65c:	0b ce                	or     %esi,%ecx
    7f9bb08df65e:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7f9bb08df664:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7f9bb08df66a:	23 c1                	and    %ecx,%eax
    7f9bb08df66c:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7f9bb08df66f:	03 4d b8             	add    -0x48(%rbp),%ecx
    7f9bb08df672:	83 e1 1f             	and    $0x1f,%ecx
    7f9bb08df675:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7f9bb08df67b:	ff c9                	dec    %ecx
    7f9bb08df67d:	83 e1 1f             	and    $0x1f,%ecx
    7f9bb08df680:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7f9bb08df686:	89 85 b0 fd ff ff    	mov    %eax,-0x250(%rbp)
    7f9bb08df68c:	85 c0                	test   %eax,%eax
    7f9bb08df68e:	0f 85 0c 00 00 00    	jne    0x7f9bb08df6a0
    7f9bb08df694:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7f9bb08df69a:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7f9bb08df6a0:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f9bb08df6a3:	ff c8                	dec    %eax
    7f9bb08df6a5:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08df6a8:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7f9bb08df6ae:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f9bb08df6b4:	85 c0                	test   %eax,%eax
    7f9bb08df6b6:	0f 85 09 00 00 00    	jne    0x7f9bb08df6c5
    7f9bb08df6bc:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f9bb08df6bf:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7f9bb08df6c5:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08df6cb:	85 c0                	test   %eax,%eax
    7f9bb08df6cd:	0f 85 1f 00 00 00    	jne    0x7f9bb08df6f2
    7f9bb08df6d3:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f9bb08df6d9:	85 c0                	test   %eax,%eax
    7f9bb08df6db:	0f 85 20 00 00 00    	jne    0x7f9bb08df701
    7f9bb08df6e1:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7f9bb08df6e7:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7f9bb08df6ed:	e9 1b 00 00 00       	jmpq   0x7f9bb08df70d
    7f9bb08df6f2:	c7 85 a0 fd ff ff 00 	movl   $0x0,-0x260(%rbp)
    7f9bb08df6f9:	00 00 00 
    7f9bb08df6fc:	e9 0c 00 00 00       	jmpq   0x7f9bb08df70d
    7f9bb08df701:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7f9bb08df707:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7f9bb08df70d:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f9bb08df713:	c1 e0 05             	shl    $0x5,%eax
    7f9bb08df716:	05 ff 01 00 00       	add    $0x1ff,%eax
    7f9bb08df71b:	c1 e8 09             	shr    $0x9,%eax
    7f9bb08df71e:	89 85 98 fd ff ff    	mov    %eax,-0x268(%rbp)
    7f9bb08df724:	83 c0 10             	add    $0x10,%eax
    7f9bb08df727:	ff c8                	dec    %eax
    7f9bb08df729:	c1 e8 04             	shr    $0x4,%eax
    7f9bb08df72c:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7f9bb08df732:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f9bb08df735:	ff c8                	dec    %eax
    7f9bb08df737:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7f9bb08df73c:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7f9bb08df742:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08df748:	85 c0                	test   %eax,%eax
    7f9bb08df74a:	0f 85 1c 00 00 00    	jne    0x7f9bb08df76c
    7f9bb08df750:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f9bb08df756:	85 c0                	test   %eax,%eax
    7f9bb08df758:	0f 85 1f 00 00 00    	jne    0x7f9bb08df77d
    7f9bb08df75e:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f9bb08df761:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f9bb08df767:	e9 1d 00 00 00       	jmpq   0x7f9bb08df789
    7f9bb08df76c:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f9bb08df772:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f9bb08df778:	e9 0c 00 00 00       	jmpq   0x7f9bb08df789
    7f9bb08df77d:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7f9bb08df783:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7f9bb08df789:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7f9bb08df78f:	85 c0                	test   %eax,%eax
    7f9bb08df791:	0f 95 c0             	setne  %al
    7f9bb08df794:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df797:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7f9bb08df79d:	b8 01 00 00 00       	mov    $0x1,%eax
    7f9bb08df7a2:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7f9bb08df7a5:	3b c1                	cmp    %ecx,%eax
    7f9bb08df7a7:	0f 94 c0             	sete   %al
    7f9bb08df7aa:	0f b6 c0             	movzbl %al,%eax
    7f9bb08df7ad:	8b 95 08 fe ff ff    	mov    -0x1f8(%rbp),%edx
    7f9bb08df7b3:	23 c2                	and    %edx,%eax
    7f9bb08df7b5:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7f9bb08df7bb:	85 c9                	test   %ecx,%ecx
    7f9bb08df7bd:	0f 95 c1             	setne  %cl
    7f9bb08df7c0:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08df7c3:	8b c1                	mov    %ecx,%eax
    7f9bb08df7c5:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7f9bb08df7cb:	83 f9 00             	cmp    $0x0,%ecx
    7f9bb08df7ce:	0f 96 c1             	setbe  %cl
    7f9bb08df7d1:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08df7d4:	23 c1                	and    %ecx,%eax
    7f9bb08df7d6:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7f9bb08df7dc:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08df7e2:	85 c0                	test   %eax,%eax
    7f9bb08df7e4:	0f 85 1f 00 00 00    	jne    0x7f9bb08df809
    7f9bb08df7ea:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7f9bb08df7f0:	85 c0                	test   %eax,%eax
    7f9bb08df7f2:	0f 85 22 00 00 00    	jne    0x7f9bb08df81a
    7f9bb08df7f8:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7f9bb08df7fe:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f9bb08df804:	e9 1b 00 00 00       	jmpq   0x7f9bb08df824
    7f9bb08df809:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7f9bb08df80f:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f9bb08df815:	e9 0a 00 00 00       	jmpq   0x7f9bb08df824
    7f9bb08df81a:	c7 85 60 fd ff ff 00 	movl   $0x0,-0x2a0(%rbp)
    7f9bb08df821:	00 00 00 
    7f9bb08df824:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7f9bb08df82a:	ff c8                	dec    %eax
    7f9bb08df82c:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08df82f:	83 e0 0f             	and    $0xf,%eax
    7f9bb08df832:	ff c0                	inc    %eax
    7f9bb08df834:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08df837:	89 85 58 fd ff ff    	mov    %eax,-0x2a8(%rbp)
    7f9bb08df83d:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08df843:	85 c0                	test   %eax,%eax
    7f9bb08df845:	0f 85 1c 00 00 00    	jne    0x7f9bb08df867
    7f9bb08df84b:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f9bb08df851:	85 c0                	test   %eax,%eax
    7f9bb08df853:	0f 85 1f 00 00 00    	jne    0x7f9bb08df878
    7f9bb08df859:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f9bb08df85c:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7f9bb08df862:	e9 1b 00 00 00       	jmpq   0x7f9bb08df882
    7f9bb08df867:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7f9bb08df86d:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7f9bb08df873:	e9 0a 00 00 00       	jmpq   0x7f9bb08df882
    7f9bb08df878:	c7 85 50 fd ff ff 10 	movl   $0x10,-0x2b0(%rbp)
    7f9bb08df87f:	00 00 00 
    7f9bb08df882:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f9bb08df888:	85 c0                	test   %eax,%eax
    7f9bb08df88a:	0f 85 36 00 00 00    	jne    0x7f9bb08df8c6
    7f9bb08df890:	49 8b c7             	mov    %r15,%rax
    7f9bb08df893:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7f9bb08df899:	49 8b cf             	mov    %r15,%rcx
    7f9bb08df89c:	48 81 c1 e0 0d 00 00 	add    $0xde0,%rcx
    7f9bb08df8a3:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08df8a6:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08df8a9:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08df8ad:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08df8b1:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08df8b5:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08df8b9:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08df8bd:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08df8c1:	e9 31 00 00 00       	jmpq   0x7f9bb08df8f7
    7f9bb08df8c6:	49 8b c7             	mov    %r15,%rax
    7f9bb08df8c9:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7f9bb08df8cf:	49 8b cf             	mov    %r15,%rcx
    7f9bb08df8d2:	48 81 c1 a0 0d 00 00 	add    $0xda0,%rcx
    7f9bb08df8d9:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08df8dc:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08df8df:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08df8e3:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08df8e7:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08df8eb:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08df8ef:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08df8f3:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08df8f7:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f9bb08df8fa:	23 85 e8 fd ff ff    	and    -0x218(%rbp),%eax
    7f9bb08df900:	89 85 48 fd ff ff    	mov    %eax,-0x2b8(%rbp)
    7f9bb08df906:	49 8b c7             	mov    %r15,%rax
    7f9bb08df909:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7f9bb08df90f:	49 8b cf             	mov    %r15,%rcx
    7f9bb08df912:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7f9bb08df919:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7f9bb08df91f:	48 89 8d 40 fd ff ff 	mov    %rcx,-0x2c0(%rbp)
    7f9bb08df926:	b9 00 02 00 00       	mov    $0x200,%ecx
    7f9bb08df92b:	48 8b d0             	mov    %rax,%rdx
    7f9bb08df92e:	be 00 02 00 00       	mov    $0x200,%esi
    7f9bb08df933:	48 8b bd 40 fd ff ff 	mov    -0x2c0(%rbp),%rdi
    7f9bb08df93a:	48 89 85 38 fd ff ff 	mov    %rax,-0x2c8(%rbp)
    7f9bb08df941:	b8 08 00 00 00       	mov    $0x8,%eax
    7f9bb08df946:	e8 b5 b3 bd ff       	callq  0x7f9bb04bad00
    7f9bb08df94b:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f9bb08df951:	85 c0                	test   %eax,%eax
    7f9bb08df953:	0f 85 44 00 00 00    	jne    0x7f9bb08df99d
    7f9bb08df959:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7f9bb08df95f:	85 c0                	test   %eax,%eax
    7f9bb08df961:	0f 85 6c 00 00 00    	jne    0x7f9bb08df9d3
    7f9bb08df967:	49 8b c7             	mov    %r15,%rax
    7f9bb08df96a:	48 05 88 10 00 00    	add    $0x1088,%rax
    7f9bb08df970:	49 8b cf             	mov    %r15,%rcx
    7f9bb08df973:	48 81 c1 18 0d 00 00 	add    $0xd18,%rcx
    7f9bb08df97a:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08df97d:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08df980:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08df984:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08df988:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08df98c:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08df990:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08df994:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08df998:	e9 67 00 00 00       	jmpq   0x7f9bb08dfa04
    7f9bb08df99d:	49 8b c7             	mov    %r15,%rax
    7f9bb08df9a0:	48 05 88 10 00 00    	add    $0x1088,%rax
    7f9bb08df9a6:	49 8b cf             	mov    %r15,%rcx
    7f9bb08df9a9:	48 81 c1 c8 10 00 00 	add    $0x10c8,%rcx
    7f9bb08df9b0:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08df9b3:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08df9b6:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08df9ba:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08df9be:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08df9c2:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08df9c6:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08df9ca:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08df9ce:	e9 31 00 00 00       	jmpq   0x7f9bb08dfa04
    7f9bb08df9d3:	49 8b c7             	mov    %r15,%rax
    7f9bb08df9d6:	48 05 88 10 00 00    	add    $0x1088,%rax
    7f9bb08df9dc:	49 8b cf             	mov    %r15,%rcx
    7f9bb08df9df:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7f9bb08df9e6:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08df9e9:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08df9ec:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08df9f0:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08df9f4:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08df9f8:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08df9fc:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08dfa00:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08dfa04:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f9bb08dfa0a:	85 c0                	test   %eax,%eax
    7f9bb08dfa0c:	0f 85 1c 00 00 00    	jne    0x7f9bb08dfa2e
    7f9bb08dfa12:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7f9bb08dfa18:	85 c0                	test   %eax,%eax
    7f9bb08dfa1a:	0f 85 1d 00 00 00    	jne    0x7f9bb08dfa3d
    7f9bb08dfa20:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f9bb08dfa23:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7f9bb08dfa29:	e9 19 00 00 00       	jmpq   0x7f9bb08dfa47
    7f9bb08dfa2e:	c7 85 30 fd ff ff 01 	movl   $0x1,-0x2d0(%rbp)
    7f9bb08dfa35:	00 00 00 
    7f9bb08dfa38:	e9 0a 00 00 00       	jmpq   0x7f9bb08dfa47
    7f9bb08dfa3d:	c7 85 30 fd ff ff 00 	movl   $0x0,-0x2d0(%rbp)
    7f9bb08dfa44:	00 00 00 
    7f9bb08dfa47:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f9bb08dfa4a:	ff c0                	inc    %eax
    7f9bb08dfa4c:	83 e0 0f             	and    $0xf,%eax
    7f9bb08dfa4f:	89 85 28 fd ff ff    	mov    %eax,-0x2d8(%rbp)
    7f9bb08dfa55:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7f9bb08dfa5b:	85 c0                	test   %eax,%eax
    7f9bb08dfa5d:	0f 85 09 00 00 00    	jne    0x7f9bb08dfa6c
    7f9bb08dfa63:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f9bb08dfa66:	89 85 28 fd ff ff    	mov    %eax,-0x2d8(%rbp)
    7f9bb08dfa6c:	41 8b c4             	mov    %r12d,%eax
    7f9bb08dfa6f:	83 c8 00             	or     $0x0,%eax
    7f9bb08dfa72:	89 85 20 fd ff ff    	mov    %eax,-0x2e0(%rbp)
    7f9bb08dfa78:	49 8b 46 58          	mov    0x58(%r14),%rax
    7f9bb08dfa7c:	8b 00                	mov    (%rax),%eax
    7f9bb08dfa7e:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7f9bb08dfa81:	85 c9                	test   %ecx,%ecx
    7f9bb08dfa83:	0f 94 c1             	sete   %cl
    7f9bb08dfa86:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08dfa89:	23 c1                	and    %ecx,%eax
    7f9bb08dfa8b:	8b 8d c8 fd ff ff    	mov    -0x238(%rbp),%ecx
    7f9bb08dfa91:	23 8d d0 fd ff ff    	and    -0x230(%rbp),%ecx
    7f9bb08dfa97:	85 c9                	test   %ecx,%ecx
    7f9bb08dfa99:	0f 94 c2             	sete   %dl
    7f9bb08dfa9c:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08dfa9f:	89 95 18 fd ff ff    	mov    %edx,-0x2e8(%rbp)
    7f9bb08dfaa5:	23 d0                	and    %eax,%edx
    7f9bb08dfaa7:	8b 75 a0             	mov    -0x60(%rbp),%esi
    7f9bb08dfaaa:	ff c6                	inc    %esi
    7f9bb08dfaac:	83 e6 1f             	and    $0x1f,%esi
    7f9bb08dfaaf:	89 b5 10 fd ff ff    	mov    %esi,-0x2f0(%rbp)
    7f9bb08dfab5:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7f9bb08dfabb:	85 c0                	test   %eax,%eax
    7f9bb08dfabd:	0f 94 c0             	sete   %al
    7f9bb08dfac0:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfac3:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7f9bb08dfac9:	89 85 f8 fc ff ff    	mov    %eax,-0x308(%rbp)
    7f9bb08dfacf:	23 c8                	and    %eax,%ecx
    7f9bb08dfad1:	89 8d f0 fc ff ff    	mov    %ecx,-0x310(%rbp)
    7f9bb08dfad7:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f9bb08dfada:	ff c8                	dec    %eax
    7f9bb08dfadc:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08dfadf:	89 85 e8 fc ff ff    	mov    %eax,-0x318(%rbp)
    7f9bb08dfae5:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7f9bb08dfaeb:	85 d2                	test   %edx,%edx
    7f9bb08dfaed:	0f 85 1c 00 00 00    	jne    0x7f9bb08dfb0f
    7f9bb08dfaf3:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7f9bb08dfaf9:	85 c0                	test   %eax,%eax
    7f9bb08dfafb:	0f 85 1f 00 00 00    	jne    0x7f9bb08dfb20
    7f9bb08dfb01:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f9bb08dfb04:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f9bb08dfb0a:	e9 1d 00 00 00       	jmpq   0x7f9bb08dfb2c
    7f9bb08dfb0f:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7f9bb08dfb15:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f9bb08dfb1b:	e9 0c 00 00 00       	jmpq   0x7f9bb08dfb2c
    7f9bb08dfb20:	8b 85 e8 fc ff ff    	mov    -0x318(%rbp),%eax
    7f9bb08dfb26:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7f9bb08dfb2c:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f9bb08dfb2f:	83 f8 01             	cmp    $0x1,%eax
    7f9bb08dfb32:	0f 94 c0             	sete   %al
    7f9bb08dfb35:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfb38:	23 85 00 fd ff ff    	and    -0x300(%rbp),%eax
    7f9bb08dfb3e:	23 85 f8 fc ff ff    	and    -0x308(%rbp),%eax
    7f9bb08dfb44:	85 c0                	test   %eax,%eax
    7f9bb08dfb46:	0f 85 1c 00 00 00    	jne    0x7f9bb08dfb68
    7f9bb08dfb4c:	8b 85 e0 fc ff ff    	mov    -0x320(%rbp),%eax
    7f9bb08dfb52:	85 c0                	test   %eax,%eax
    7f9bb08dfb54:	0f 85 1d 00 00 00    	jne    0x7f9bb08dfb77
    7f9bb08dfb5a:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f9bb08dfb5d:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7f9bb08dfb63:	e9 19 00 00 00       	jmpq   0x7f9bb08dfb81
    7f9bb08dfb68:	c7 85 d0 fc ff ff 01 	movl   $0x1,-0x330(%rbp)
    7f9bb08dfb6f:	00 00 00 
    7f9bb08dfb72:	e9 0a 00 00 00       	jmpq   0x7f9bb08dfb81
    7f9bb08dfb77:	c7 85 d0 fc ff ff 00 	movl   $0x0,-0x330(%rbp)
    7f9bb08dfb7e:	00 00 00 
    7f9bb08dfb81:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f9bb08dfb84:	83 f8 0f             	cmp    $0xf,%eax
    7f9bb08dfb87:	0f 94 c0             	sete   %al
    7f9bb08dfb8a:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfb8d:	23 85 08 fd ff ff    	and    -0x2f8(%rbp),%eax
    7f9bb08dfb93:	23 85 18 fd ff ff    	and    -0x2e8(%rbp),%eax
    7f9bb08dfb99:	85 c0                	test   %eax,%eax
    7f9bb08dfb9b:	0f 85 1c 00 00 00    	jne    0x7f9bb08dfbbd
    7f9bb08dfba1:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7f9bb08dfba7:	85 c0                	test   %eax,%eax
    7f9bb08dfba9:	0f 85 1d 00 00 00    	jne    0x7f9bb08dfbcc
    7f9bb08dfbaf:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f9bb08dfbb2:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7f9bb08dfbb8:	e9 19 00 00 00       	jmpq   0x7f9bb08dfbd6
    7f9bb08dfbbd:	c7 85 c8 fc ff ff 01 	movl   $0x1,-0x338(%rbp)
    7f9bb08dfbc4:	00 00 00 
    7f9bb08dfbc7:	e9 0a 00 00 00       	jmpq   0x7f9bb08dfbd6
    7f9bb08dfbcc:	c7 85 c8 fc ff ff 00 	movl   $0x0,-0x338(%rbp)
    7f9bb08dfbd3:	00 00 00 
    7f9bb08dfbd6:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f9bb08dfbd9:	ff c0                	inc    %eax
    7f9bb08dfbdb:	83 e0 0f             	and    $0xf,%eax
    7f9bb08dfbde:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7f9bb08dfbe4:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7f9bb08dfbea:	85 c0                	test   %eax,%eax
    7f9bb08dfbec:	0f 85 09 00 00 00    	jne    0x7f9bb08dfbfb
    7f9bb08dfbf2:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f9bb08dfbf5:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7f9bb08dfbfb:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f9bb08dfbfe:	83 c0 02             	add    $0x2,%eax
    7f9bb08dfc01:	83 e0 0f             	and    $0xf,%eax
    7f9bb08dfc04:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7f9bb08dfc0a:	b8 01 00 00 00       	mov    $0x1,%eax
    7f9bb08dfc0f:	3b 45 a0             	cmp    -0x60(%rbp),%eax
    7f9bb08dfc12:	0f 94 c0             	sete   %al
    7f9bb08dfc15:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfc18:	8b 8d 00 fd ff ff    	mov    -0x300(%rbp),%ecx
    7f9bb08dfc1e:	23 c1                	and    %ecx,%eax
    7f9bb08dfc20:	8b 55 98             	mov    -0x68(%rbp),%edx
    7f9bb08dfc23:	0b c2                	or     %edx,%eax
    7f9bb08dfc25:	8b 95 08 fd ff ff    	mov    -0x2f8(%rbp),%edx
    7f9bb08dfc2b:	23 c2                	and    %edx,%eax
    7f9bb08dfc2d:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7f9bb08dfc33:	49 8b 46 50          	mov    0x50(%r14),%rax
    7f9bb08dfc37:	48 89 85 a8 fc ff ff 	mov    %rax,-0x358(%rbp)
    7f9bb08dfc3e:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7f9bb08dfc44:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7f9bb08dfc4a:	85 c9                	test   %ecx,%ecx
    7f9bb08dfc4c:	0f 85 09 00 00 00    	jne    0x7f9bb08dfc5b
    7f9bb08dfc52:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f9bb08dfc55:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7f9bb08dfc5b:	49 8b c7             	mov    %r15,%rax
    7f9bb08dfc5e:	48 05 00 0c 00 00    	add    $0xc00,%rax
    7f9bb08dfc64:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7f9bb08dfc6a:	c1 e1 06             	shl    $0x6,%ecx
    7f9bb08dfc6d:	8b c9                	mov    %ecx,%ecx
    7f9bb08dfc6f:	49 03 cf             	add    %r15,%rcx
    7f9bb08dfc72:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08dfc75:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08dfc78:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08dfc7c:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08dfc80:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08dfc84:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08dfc88:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08dfc8c:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08dfc90:	49 8b 46 10          	mov    0x10(%r14),%rax
    7f9bb08dfc94:	48 8b 00             	mov    (%rax),%rax
    7f9bb08dfc97:	48 89 85 98 fc ff ff 	mov    %rax,-0x368(%rbp)
    7f9bb08dfc9e:	49 8b 86 80 00 00 00 	mov    0x80(%r14),%rax
    7f9bb08dfca5:	8b 00                	mov    (%rax),%eax
    7f9bb08dfca7:	85 c0                	test   %eax,%eax
    7f9bb08dfca9:	0f 94 c0             	sete   %al
    7f9bb08dfcac:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfcaf:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7f9bb08dfcb5:	23 c1                	and    %ecx,%eax
    7f9bb08dfcb7:	89 85 90 fc ff ff    	mov    %eax,-0x370(%rbp)
    7f9bb08dfcbd:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f9bb08dfcc3:	8b c0                	mov    %eax,%eax
    7f9bb08dfcc5:	48 c1 e0 06          	shl    $0x6,%rax
    7f9bb08dfcc9:	48 89 85 88 fc ff ff 	mov    %rax,-0x378(%rbp)
    7f9bb08dfcd0:	48 8b 8d 68 ff ff ff 	mov    -0x98(%rbp),%rcx
    7f9bb08dfcd7:	48 03 c1             	add    %rcx,%rax
    7f9bb08dfcda:	48 89 85 80 fc ff ff 	mov    %rax,-0x380(%rbp)
    7f9bb08dfce1:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08dfce7:	85 c0                	test   %eax,%eax
    7f9bb08dfce9:	0f 85 21 00 00 00    	jne    0x7f9bb08dfd10
    7f9bb08dfcef:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f9bb08dfcf5:	85 c0                	test   %eax,%eax
    7f9bb08dfcf7:	0f 85 26 00 00 00    	jne    0x7f9bb08dfd23
    7f9bb08dfcfd:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
    7f9bb08dfd04:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7f9bb08dfd0b:	e9 21 00 00 00       	jmpq   0x7f9bb08dfd31
    7f9bb08dfd10:	48 8b 85 98 fc ff ff 	mov    -0x368(%rbp),%rax
    7f9bb08dfd17:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7f9bb08dfd1e:	e9 0e 00 00 00       	jmpq   0x7f9bb08dfd31
    7f9bb08dfd23:	48 8b 85 80 fc ff ff 	mov    -0x380(%rbp),%rax
    7f9bb08dfd2a:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7f9bb08dfd31:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f9bb08dfd37:	85 c0                	test   %eax,%eax
    7f9bb08dfd39:	0f 94 c0             	sete   %al
    7f9bb08dfd3c:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfd3f:	8b 95 40 ff ff ff    	mov    -0xc0(%rbp),%edx
    7f9bb08dfd45:	85 d2                	test   %edx,%edx
    7f9bb08dfd47:	0f 94 c1             	sete   %cl
    7f9bb08dfd4a:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08dfd4d:	8b b5 38 ff ff ff    	mov    -0xc8(%rbp),%esi
    7f9bb08dfd53:	83 fe 0f             	cmp    $0xf,%esi
    7f9bb08dfd56:	40 0f 94 c6          	sete   %sil
    7f9bb08dfd5a:	40 0f b6 f6          	movzbl %sil,%esi
    7f9bb08dfd5e:	23 95 e0 fd ff ff    	and    -0x220(%rbp),%edx
    7f9bb08dfd64:	85 d2                	test   %edx,%edx
    7f9bb08dfd66:	0f 94 c2             	sete   %dl
    7f9bb08dfd69:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08dfd6c:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7f9bb08dfd72:	23 d7                	and    %edi,%edx
    7f9bb08dfd74:	89 95 70 fc ff ff    	mov    %edx,-0x390(%rbp)
    7f9bb08dfd7a:	23 f2                	and    %edx,%esi
    7f9bb08dfd7c:	89 b5 68 fc ff ff    	mov    %esi,-0x398(%rbp)
    7f9bb08dfd82:	0b ce                	or     %esi,%ecx
    7f9bb08dfd84:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7f9bb08dfd8a:	89 8d 58 fc ff ff    	mov    %ecx,-0x3a8(%rbp)
    7f9bb08dfd90:	23 c1                	and    %ecx,%eax
    7f9bb08dfd92:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7f9bb08dfd98:	03 8d 48 ff ff ff    	add    -0xb8(%rbp),%ecx
    7f9bb08dfd9e:	83 e1 1f             	and    $0x1f,%ecx
    7f9bb08dfda1:	89 8d 50 fc ff ff    	mov    %ecx,-0x3b0(%rbp)
    7f9bb08dfda7:	ff c9                	dec    %ecx
    7f9bb08dfda9:	83 e1 1f             	and    $0x1f,%ecx
    7f9bb08dfdac:	89 8d 48 fc ff ff    	mov    %ecx,-0x3b8(%rbp)
    7f9bb08dfdb2:	89 85 40 fc ff ff    	mov    %eax,-0x3c0(%rbp)
    7f9bb08dfdb8:	85 c0                	test   %eax,%eax
    7f9bb08dfdba:	0f 85 0c 00 00 00    	jne    0x7f9bb08dfdcc
    7f9bb08dfdc0:	8b 85 50 fc ff ff    	mov    -0x3b0(%rbp),%eax
    7f9bb08dfdc6:	89 85 48 fc ff ff    	mov    %eax,-0x3b8(%rbp)
    7f9bb08dfdcc:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f9bb08dfdd2:	ff c8                	dec    %eax
    7f9bb08dfdd4:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08dfdd7:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7f9bb08dfddd:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f9bb08dfde3:	85 c0                	test   %eax,%eax
    7f9bb08dfde5:	0f 85 0c 00 00 00    	jne    0x7f9bb08dfdf7
    7f9bb08dfdeb:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f9bb08dfdf1:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7f9bb08dfdf7:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08dfdfd:	85 c0                	test   %eax,%eax
    7f9bb08dfdff:	0f 85 1f 00 00 00    	jne    0x7f9bb08dfe24
    7f9bb08dfe05:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f9bb08dfe0b:	85 c0                	test   %eax,%eax
    7f9bb08dfe0d:	0f 85 20 00 00 00    	jne    0x7f9bb08dfe33
    7f9bb08dfe13:	8b 85 38 fc ff ff    	mov    -0x3c8(%rbp),%eax
    7f9bb08dfe19:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7f9bb08dfe1f:	e9 1b 00 00 00       	jmpq   0x7f9bb08dfe3f
    7f9bb08dfe24:	c7 85 30 fc ff ff 00 	movl   $0x0,-0x3d0(%rbp)
    7f9bb08dfe2b:	00 00 00 
    7f9bb08dfe2e:	e9 0c 00 00 00       	jmpq   0x7f9bb08dfe3f
    7f9bb08dfe33:	8b 85 48 fc ff ff    	mov    -0x3b8(%rbp),%eax
    7f9bb08dfe39:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7f9bb08dfe3f:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f9bb08dfe45:	ff c8                	dec    %eax
    7f9bb08dfe47:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7f9bb08dfe4c:	89 85 28 fc ff ff    	mov    %eax,-0x3d8(%rbp)
    7f9bb08dfe52:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08dfe58:	85 c0                	test   %eax,%eax
    7f9bb08dfe5a:	0f 85 1f 00 00 00    	jne    0x7f9bb08dfe7f
    7f9bb08dfe60:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f9bb08dfe66:	85 c0                	test   %eax,%eax
    7f9bb08dfe68:	0f 85 22 00 00 00    	jne    0x7f9bb08dfe90
    7f9bb08dfe6e:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f9bb08dfe74:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f9bb08dfe7a:	e9 1d 00 00 00       	jmpq   0x7f9bb08dfe9c
    7f9bb08dfe7f:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f9bb08dfe85:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f9bb08dfe8b:	e9 0c 00 00 00       	jmpq   0x7f9bb08dfe9c
    7f9bb08dfe90:	8b 85 28 fc ff ff    	mov    -0x3d8(%rbp),%eax
    7f9bb08dfe96:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7f9bb08dfe9c:	b8 01 00 00 00       	mov    $0x1,%eax
    7f9bb08dfea1:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7f9bb08dfea7:	3b c1                	cmp    %ecx,%eax
    7f9bb08dfea9:	0f 94 c0             	sete   %al
    7f9bb08dfeac:	0f b6 c0             	movzbl %al,%eax
    7f9bb08dfeaf:	8b 95 90 fc ff ff    	mov    -0x370(%rbp),%edx
    7f9bb08dfeb5:	23 c2                	and    %edx,%eax
    7f9bb08dfeb7:	89 85 18 fc ff ff    	mov    %eax,-0x3e8(%rbp)
    7f9bb08dfebd:	85 c9                	test   %ecx,%ecx
    7f9bb08dfebf:	0f 95 c1             	setne  %cl
    7f9bb08dfec2:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08dfec5:	8b c1                	mov    %ecx,%eax
    7f9bb08dfec7:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7f9bb08dfecd:	83 f9 00             	cmp    $0x0,%ecx
    7f9bb08dfed0:	0f 96 c1             	setbe  %cl
    7f9bb08dfed3:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08dfed6:	23 c1                	and    %ecx,%eax
    7f9bb08dfed8:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7f9bb08dfede:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08dfee4:	85 c0                	test   %eax,%eax
    7f9bb08dfee6:	0f 85 1f 00 00 00    	jne    0x7f9bb08dff0b
    7f9bb08dfeec:	8b 85 18 fc ff ff    	mov    -0x3e8(%rbp),%eax
    7f9bb08dfef2:	85 c0                	test   %eax,%eax
    7f9bb08dfef4:	0f 85 22 00 00 00    	jne    0x7f9bb08dff1c
    7f9bb08dfefa:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7f9bb08dff00:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7f9bb08dff06:	e9 1b 00 00 00       	jmpq   0x7f9bb08dff26
    7f9bb08dff0b:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7f9bb08dff11:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7f9bb08dff17:	e9 0a 00 00 00       	jmpq   0x7f9bb08dff26
    7f9bb08dff1c:	c7 85 08 fc ff ff 00 	movl   $0x0,-0x3f8(%rbp)
    7f9bb08dff23:	00 00 00 
    7f9bb08dff26:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08dff2c:	85 c0                	test   %eax,%eax
    7f9bb08dff2e:	0f 85 1f 00 00 00    	jne    0x7f9bb08dff53
    7f9bb08dff34:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7f9bb08dff3a:	85 c0                	test   %eax,%eax
    7f9bb08dff3c:	0f 85 22 00 00 00    	jne    0x7f9bb08dff64
    7f9bb08dff42:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f9bb08dff48:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f9bb08dff4e:	e9 1b 00 00 00       	jmpq   0x7f9bb08dff6e
    7f9bb08dff53:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7f9bb08dff59:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7f9bb08dff5f:	e9 0a 00 00 00       	jmpq   0x7f9bb08dff6e
    7f9bb08dff64:	c7 85 00 fc ff ff 10 	movl   $0x10,-0x400(%rbp)
    7f9bb08dff6b:	00 00 00 
    7f9bb08dff6e:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f9bb08dff74:	85 c0                	test   %eax,%eax
    7f9bb08dff76:	0f 85 36 00 00 00    	jne    0x7f9bb08dffb2
    7f9bb08dff7c:	49 8b c7             	mov    %r15,%rax
    7f9bb08dff7f:	48 05 48 11 00 00    	add    $0x1148,%rax
    7f9bb08dff85:	49 8b cf             	mov    %r15,%rcx
    7f9bb08dff88:	48 81 c1 10 0f 00 00 	add    $0xf10,%rcx
    7f9bb08dff8f:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08dff92:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08dff95:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08dff99:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08dff9d:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08dffa1:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08dffa5:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08dffa9:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08dffad:	e9 31 00 00 00       	jmpq   0x7f9bb08dffe3
    7f9bb08dffb2:	49 8b c7             	mov    %r15,%rax
    7f9bb08dffb5:	48 05 48 11 00 00    	add    $0x1148,%rax
    7f9bb08dffbb:	49 8b cf             	mov    %r15,%rcx
    7f9bb08dffbe:	48 81 c1 d0 0e 00 00 	add    $0xed0,%rcx
    7f9bb08dffc5:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08dffc8:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08dffcb:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08dffcf:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08dffd3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08dffd7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08dffdb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08dffdf:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08dffe3:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f9bb08dffe9:	23 85 70 fc ff ff    	and    -0x390(%rbp),%eax
    7f9bb08dffef:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7f9bb08dfff5:	49 8b c7             	mov    %r15,%rax
    7f9bb08dfff8:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7f9bb08dfffe:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0001:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7f9bb08e0008:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7f9bb08e000e:	48 89 8d f0 fb ff ff 	mov    %rcx,-0x410(%rbp)
    7f9bb08e0015:	b9 00 02 00 00       	mov    $0x200,%ecx
    7f9bb08e001a:	48 8b d0             	mov    %rax,%rdx
    7f9bb08e001d:	be 00 02 00 00       	mov    $0x200,%esi
    7f9bb08e0022:	48 8b bd f0 fb ff ff 	mov    -0x410(%rbp),%rdi
    7f9bb08e0029:	48 89 85 e8 fb ff ff 	mov    %rax,-0x418(%rbp)
    7f9bb08e0030:	b8 08 00 00 00       	mov    $0x8,%eax
    7f9bb08e0035:	e8 c6 ac bd ff       	callq  0x7f9bb04bad00
    7f9bb08e003a:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f9bb08e0040:	85 c0                	test   %eax,%eax
    7f9bb08e0042:	0f 85 44 00 00 00    	jne    0x7f9bb08e008c
    7f9bb08e0048:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7f9bb08e004e:	85 c0                	test   %eax,%eax
    7f9bb08e0050:	0f 85 6c 00 00 00    	jne    0x7f9bb08e00c2
    7f9bb08e0056:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0059:	48 05 08 11 00 00    	add    $0x1108,%rax
    7f9bb08e005f:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0062:	48 81 c1 48 0e 00 00 	add    $0xe48,%rcx
    7f9bb08e0069:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e006c:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e006f:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0073:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0077:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e007b:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e007f:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0083:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0087:	e9 67 00 00 00       	jmpq   0x7f9bb08e00f3
    7f9bb08e008c:	49 8b c7             	mov    %r15,%rax
    7f9bb08e008f:	48 05 08 11 00 00    	add    $0x1108,%rax
    7f9bb08e0095:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0098:	48 81 c1 48 11 00 00 	add    $0x1148,%rcx
    7f9bb08e009f:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e00a2:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e00a5:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e00a9:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e00ad:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e00b1:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e00b5:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e00b9:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e00bd:	e9 31 00 00 00       	jmpq   0x7f9bb08e00f3
    7f9bb08e00c2:	49 8b c7             	mov    %r15,%rax
    7f9bb08e00c5:	48 05 08 11 00 00    	add    $0x1108,%rax
    7f9bb08e00cb:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e00ce:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7f9bb08e00d5:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e00d8:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e00db:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e00df:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e00e3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e00e7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e00eb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e00ef:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e00f3:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f9bb08e00f9:	85 c0                	test   %eax,%eax
    7f9bb08e00fb:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0120
    7f9bb08e0101:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7f9bb08e0107:	85 c0                	test   %eax,%eax
    7f9bb08e0109:	0f 85 20 00 00 00    	jne    0x7f9bb08e012f
    7f9bb08e010f:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f9bb08e0115:	89 85 e0 fb ff ff    	mov    %eax,-0x420(%rbp)
    7f9bb08e011b:	e9 19 00 00 00       	jmpq   0x7f9bb08e0139
    7f9bb08e0120:	c7 85 e0 fb ff ff 01 	movl   $0x1,-0x420(%rbp)
    7f9bb08e0127:	00 00 00 
    7f9bb08e012a:	e9 0a 00 00 00       	jmpq   0x7f9bb08e0139
    7f9bb08e012f:	c7 85 e0 fb ff ff 00 	movl   $0x0,-0x420(%rbp)
    7f9bb08e0136:	00 00 00 
    7f9bb08e0139:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f9bb08e013f:	ff c0                	inc    %eax
    7f9bb08e0141:	83 e0 0f             	and    $0xf,%eax
    7f9bb08e0144:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7f9bb08e014a:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7f9bb08e0150:	85 c0                	test   %eax,%eax
    7f9bb08e0152:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0164
    7f9bb08e0158:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f9bb08e015e:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7f9bb08e0164:	49 8b 46 78          	mov    0x78(%r14),%rax
    7f9bb08e0168:	8b 00                	mov    (%rax),%eax
    7f9bb08e016a:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7f9bb08e0170:	85 c9                	test   %ecx,%ecx
    7f9bb08e0172:	0f 94 c1             	sete   %cl
    7f9bb08e0175:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08e0178:	23 c1                	and    %ecx,%eax
    7f9bb08e017a:	8b 8d 58 fc ff ff    	mov    -0x3a8(%rbp),%ecx
    7f9bb08e0180:	23 8d 60 fc ff ff    	and    -0x3a0(%rbp),%ecx
    7f9bb08e0186:	85 c9                	test   %ecx,%ecx
    7f9bb08e0188:	0f 94 c2             	sete   %dl
    7f9bb08e018b:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08e018e:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7f9bb08e0194:	23 d0                	and    %eax,%edx
    7f9bb08e0196:	8b b5 30 ff ff ff    	mov    -0xd0(%rbp),%esi
    7f9bb08e019c:	ff c6                	inc    %esi
    7f9bb08e019e:	83 e6 1f             	and    $0x1f,%esi
    7f9bb08e01a1:	89 b5 c8 fb ff ff    	mov    %esi,-0x438(%rbp)
    7f9bb08e01a7:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7f9bb08e01ad:	85 c0                	test   %eax,%eax
    7f9bb08e01af:	0f 94 c0             	sete   %al
    7f9bb08e01b2:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e01b5:	89 8d b8 fb ff ff    	mov    %ecx,-0x448(%rbp)
    7f9bb08e01bb:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7f9bb08e01c1:	23 c8                	and    %eax,%ecx
    7f9bb08e01c3:	89 8d a8 fb ff ff    	mov    %ecx,-0x458(%rbp)
    7f9bb08e01c9:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f9bb08e01cf:	ff c8                	dec    %eax
    7f9bb08e01d1:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08e01d4:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7f9bb08e01da:	89 95 98 fb ff ff    	mov    %edx,-0x468(%rbp)
    7f9bb08e01e0:	85 d2                	test   %edx,%edx
    7f9bb08e01e2:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0207
    7f9bb08e01e8:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7f9bb08e01ee:	85 c0                	test   %eax,%eax
    7f9bb08e01f0:	0f 85 22 00 00 00    	jne    0x7f9bb08e0218
    7f9bb08e01f6:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f9bb08e01fc:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f9bb08e0202:	e9 1d 00 00 00       	jmpq   0x7f9bb08e0224
    7f9bb08e0207:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7f9bb08e020d:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f9bb08e0213:	e9 0c 00 00 00       	jmpq   0x7f9bb08e0224
    7f9bb08e0218:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7f9bb08e021e:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7f9bb08e0224:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f9bb08e022a:	83 f8 01             	cmp    $0x1,%eax
    7f9bb08e022d:	0f 94 c0             	sete   %al
    7f9bb08e0230:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0233:	23 85 b8 fb ff ff    	and    -0x448(%rbp),%eax
    7f9bb08e0239:	23 85 b0 fb ff ff    	and    -0x450(%rbp),%eax
    7f9bb08e023f:	85 c0                	test   %eax,%eax
    7f9bb08e0241:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0266
    7f9bb08e0247:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7f9bb08e024d:	85 c0                	test   %eax,%eax
    7f9bb08e024f:	0f 85 20 00 00 00    	jne    0x7f9bb08e0275
    7f9bb08e0255:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f9bb08e025b:	89 85 88 fb ff ff    	mov    %eax,-0x478(%rbp)
    7f9bb08e0261:	e9 19 00 00 00       	jmpq   0x7f9bb08e027f
    7f9bb08e0266:	c7 85 88 fb ff ff 01 	movl   $0x1,-0x478(%rbp)
    7f9bb08e026d:	00 00 00 
    7f9bb08e0270:	e9 0a 00 00 00       	jmpq   0x7f9bb08e027f
    7f9bb08e0275:	c7 85 88 fb ff ff 00 	movl   $0x0,-0x478(%rbp)
    7f9bb08e027c:	00 00 00 
    7f9bb08e027f:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f9bb08e0285:	83 f8 0f             	cmp    $0xf,%eax
    7f9bb08e0288:	0f 94 c0             	sete   %al
    7f9bb08e028b:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e028e:	23 85 c0 fb ff ff    	and    -0x440(%rbp),%eax
    7f9bb08e0294:	23 85 d0 fb ff ff    	and    -0x430(%rbp),%eax
    7f9bb08e029a:	85 c0                	test   %eax,%eax
    7f9bb08e029c:	0f 85 1f 00 00 00    	jne    0x7f9bb08e02c1
    7f9bb08e02a2:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7f9bb08e02a8:	85 c0                	test   %eax,%eax
    7f9bb08e02aa:	0f 85 20 00 00 00    	jne    0x7f9bb08e02d0
    7f9bb08e02b0:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f9bb08e02b6:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7f9bb08e02bc:	e9 19 00 00 00       	jmpq   0x7f9bb08e02da
    7f9bb08e02c1:	c7 85 80 fb ff ff 01 	movl   $0x1,-0x480(%rbp)
    7f9bb08e02c8:	00 00 00 
    7f9bb08e02cb:	e9 0a 00 00 00       	jmpq   0x7f9bb08e02da
    7f9bb08e02d0:	c7 85 80 fb ff ff 00 	movl   $0x0,-0x480(%rbp)
    7f9bb08e02d7:	00 00 00 
    7f9bb08e02da:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f9bb08e02e0:	ff c0                	inc    %eax
    7f9bb08e02e2:	83 e0 0f             	and    $0xf,%eax
    7f9bb08e02e5:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7f9bb08e02eb:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f9bb08e02f1:	85 c0                	test   %eax,%eax
    7f9bb08e02f3:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0305
    7f9bb08e02f9:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f9bb08e02ff:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7f9bb08e0305:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f9bb08e030b:	83 c0 02             	add    $0x2,%eax
    7f9bb08e030e:	83 e0 0f             	and    $0xf,%eax
    7f9bb08e0311:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7f9bb08e0317:	b8 01 00 00 00       	mov    $0x1,%eax
    7f9bb08e031c:	3b 85 30 ff ff ff    	cmp    -0xd0(%rbp),%eax
    7f9bb08e0322:	0f 94 c0             	sete   %al
    7f9bb08e0325:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0328:	8b 8d b8 fb ff ff    	mov    -0x448(%rbp),%ecx
    7f9bb08e032e:	23 c1                	and    %ecx,%eax
    7f9bb08e0330:	8b 95 28 ff ff ff    	mov    -0xd8(%rbp),%edx
    7f9bb08e0336:	0b c2                	or     %edx,%eax
    7f9bb08e0338:	8b 95 c0 fb ff ff    	mov    -0x440(%rbp),%edx
    7f9bb08e033e:	23 c2                	and    %edx,%eax
    7f9bb08e0340:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7f9bb08e0346:	49 8b 46 70          	mov    0x70(%r14),%rax
    7f9bb08e034a:	48 89 85 60 fb ff ff 	mov    %rax,-0x4a0(%rbp)
    7f9bb08e0351:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f9bb08e0357:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7f9bb08e035d:	85 c9                	test   %ecx,%ecx
    7f9bb08e035f:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0371
    7f9bb08e0365:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f9bb08e036b:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7f9bb08e0371:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0374:	48 05 00 04 00 00    	add    $0x400,%rax
    7f9bb08e037a:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e037d:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7f9bb08e0384:	8b 95 58 fb ff ff    	mov    -0x4a8(%rbp),%edx
    7f9bb08e038a:	c1 e2 06             	shl    $0x6,%edx
    7f9bb08e038d:	8b d2                	mov    %edx,%edx
    7f9bb08e038f:	48 03 c2             	add    %rdx,%rax
    7f9bb08e0392:	0f 10 00             	movups (%rax),%xmm0
    7f9bb08e0395:	0f 11 01             	movups %xmm0,(%rcx)
    7f9bb08e0398:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7f9bb08e039c:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7f9bb08e03a0:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7f9bb08e03a4:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7f9bb08e03a8:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7f9bb08e03ac:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7f9bb08e03b0:	49 8b 06             	mov    (%r14),%rax
    7f9bb08e03b3:	48 8b 00             	mov    (%rax),%rax
    7f9bb08e03b6:	48 89 85 50 fb ff ff 	mov    %rax,-0x4b0(%rbp)
    7f9bb08e03bd:	49 8b 46 40          	mov    0x40(%r14),%rax
    7f9bb08e03c1:	8b 00                	mov    (%rax),%eax
    7f9bb08e03c3:	85 c0                	test   %eax,%eax
    7f9bb08e03c5:	0f 94 c0             	sete   %al
    7f9bb08e03c8:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e03cb:	89 85 48 fb ff ff    	mov    %eax,-0x4b8(%rbp)
    7f9bb08e03d1:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7f9bb08e03d7:	23 c1                	and    %ecx,%eax
    7f9bb08e03d9:	89 85 40 fb ff ff    	mov    %eax,-0x4c0(%rbp)
    7f9bb08e03df:	48 8b 85 f8 fe ff ff 	mov    -0x108(%rbp),%rax
    7f9bb08e03e6:	48 83 c0 40          	add    $0x40,%rax
    7f9bb08e03ea:	48 89 85 38 fb ff ff 	mov    %rax,-0x4c8(%rbp)
    7f9bb08e03f1:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f9bb08e03f7:	85 c0                	test   %eax,%eax
    7f9bb08e03f9:	0f 85 21 00 00 00    	jne    0x7f9bb08e0420
    7f9bb08e03ff:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f9bb08e0405:	85 c0                	test   %eax,%eax
    7f9bb08e0407:	0f 85 26 00 00 00    	jne    0x7f9bb08e0433
    7f9bb08e040d:	48 8b 85 f8 fe ff ff 	mov    -0x108(%rbp),%rax
    7f9bb08e0414:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7f9bb08e041b:	e9 21 00 00 00       	jmpq   0x7f9bb08e0441
    7f9bb08e0420:	48 8b 85 50 fb ff ff 	mov    -0x4b0(%rbp),%rax
    7f9bb08e0427:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7f9bb08e042e:	e9 0e 00 00 00       	jmpq   0x7f9bb08e0441
    7f9bb08e0433:	48 8b 85 38 fb ff ff 	mov    -0x4c8(%rbp),%rax
    7f9bb08e043a:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7f9bb08e0441:	33 c0                	xor    %eax,%eax
    7f9bb08e0443:	8b 8d f0 fe ff ff    	mov    -0x110(%rbp),%ecx
    7f9bb08e0449:	3b c1                	cmp    %ecx,%eax
    7f9bb08e044b:	0f 94 c0             	sete   %al
    7f9bb08e044e:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0451:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7f9bb08e0457:	85 d2                	test   %edx,%edx
    7f9bb08e0459:	0f 94 c2             	sete   %dl
    7f9bb08e045c:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08e045f:	89 95 28 fb ff ff    	mov    %edx,-0x4d8(%rbp)
    7f9bb08e0465:	8b b5 c0 fe ff ff    	mov    -0x140(%rbp),%esi
    7f9bb08e046b:	23 d6                	and    %esi,%edx
    7f9bb08e046d:	83 fb 10             	cmp    $0x10,%ebx
    7f9bb08e0470:	40 0f 93 c7          	setae  %dil
    7f9bb08e0474:	40 0f b6 ff          	movzbl %dil,%edi
    7f9bb08e0478:	0b d7                	or     %edi,%edx
    7f9bb08e047a:	23 c2                	and    %edx,%eax
    7f9bb08e047c:	ba 01 00 00 00       	mov    $0x1,%edx
    7f9bb08e0481:	3b d1                	cmp    %ecx,%edx
    7f9bb08e0483:	0f 94 c2             	sete   %dl
    7f9bb08e0486:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08e0489:	89 95 20 fb ff ff    	mov    %edx,-0x4e0(%rbp)
    7f9bb08e048f:	23 95 48 fb ff ff    	and    -0x4b8(%rbp),%edx
    7f9bb08e0495:	83 fb 01             	cmp    $0x1,%ebx
    7f9bb08e0498:	40 0f 97 c7          	seta   %dil
    7f9bb08e049c:	40 0f b6 ff          	movzbl %dil,%edi
    7f9bb08e04a0:	23 f7                	and    %edi,%esi
    7f9bb08e04a2:	83 fb 10             	cmp    $0x10,%ebx
    7f9bb08e04a5:	40 0f 97 c7          	seta   %dil
    7f9bb08e04a9:	40 0f b6 ff          	movzbl %dil,%edi
    7f9bb08e04ad:	0b f7                	or     %edi,%esi
    7f9bb08e04af:	23 d6                	and    %esi,%edx
    7f9bb08e04b1:	0b c2                	or     %edx,%eax
    7f9bb08e04b3:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7f9bb08e04b9:	83 fb 10             	cmp    $0x10,%ebx
    7f9bb08e04bc:	0f 94 c0             	sete   %al
    7f9bb08e04bf:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e04c2:	33 d2                	xor    %edx,%edx
    7f9bb08e04c4:	3b d1                	cmp    %ecx,%edx
    7f9bb08e04c6:	0f 94 c2             	sete   %dl
    7f9bb08e04c9:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08e04cc:	23 c2                	and    %edx,%eax
    7f9bb08e04ce:	0b f8                	or     %eax,%edi
    7f9bb08e04d0:	85 c9                	test   %ecx,%ecx
    7f9bb08e04d2:	0f 95 c1             	setne  %cl
    7f9bb08e04d5:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08e04d8:	8b c1                	mov    %ecx,%eax
    7f9bb08e04da:	8b cb                	mov    %ebx,%ecx
    7f9bb08e04dc:	2b c8                	sub    %eax,%ecx
    7f9bb08e04de:	83 e1 1f             	and    $0x1f,%ecx
    7f9bb08e04e1:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7f9bb08e04e7:	c7 85 08 fb ff ff 10 	movl   $0x10,-0x4f8(%rbp)
    7f9bb08e04ee:	00 00 00 
    7f9bb08e04f1:	85 ff                	test   %edi,%edi
    7f9bb08e04f3:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0505
    7f9bb08e04f9:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7f9bb08e04ff:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7f9bb08e0505:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f9bb08e050b:	ff c8                	dec    %eax
    7f9bb08e050d:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08e0510:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7f9bb08e0516:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f9bb08e051c:	85 c0                	test   %eax,%eax
    7f9bb08e051e:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0543
    7f9bb08e0524:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f9bb08e052a:	85 c0                	test   %eax,%eax
    7f9bb08e052c:	0f 85 22 00 00 00    	jne    0x7f9bb08e0554
    7f9bb08e0532:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f9bb08e0538:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f9bb08e053e:	e9 1d 00 00 00       	jmpq   0x7f9bb08e0560
    7f9bb08e0543:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7f9bb08e0549:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f9bb08e054f:	e9 0c 00 00 00       	jmpq   0x7f9bb08e0560
    7f9bb08e0554:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7f9bb08e055a:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7f9bb08e0560:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f9bb08e0566:	23 85 20 fb ff ff    	and    -0x4e0(%rbp),%eax
    7f9bb08e056c:	89 85 f0 fa ff ff    	mov    %eax,-0x510(%rbp)
    7f9bb08e0572:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f9bb08e0578:	85 c0                	test   %eax,%eax
    7f9bb08e057a:	0f 85 1f 00 00 00    	jne    0x7f9bb08e059f
    7f9bb08e0580:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7f9bb08e0586:	85 c0                	test   %eax,%eax
    7f9bb08e0588:	0f 85 20 00 00 00    	jne    0x7f9bb08e05ae
    7f9bb08e058e:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7f9bb08e0594:	89 85 e8 fa ff ff    	mov    %eax,-0x518(%rbp)
    7f9bb08e059a:	e9 19 00 00 00       	jmpq   0x7f9bb08e05b8
    7f9bb08e059f:	c7 85 e8 fa ff ff 01 	movl   $0x1,-0x518(%rbp)
    7f9bb08e05a6:	00 00 00 
    7f9bb08e05a9:	e9 0a 00 00 00       	jmpq   0x7f9bb08e05b8
    7f9bb08e05ae:	c7 85 e8 fa ff ff 00 	movl   $0x0,-0x518(%rbp)
    7f9bb08e05b5:	00 00 00 
    7f9bb08e05b8:	41 83 fd 02          	cmp    $0x2,%r13d
    7f9bb08e05bc:	0f 94 c0             	sete   %al
    7f9bb08e05bf:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e05c2:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7f9bb08e05c8:	85 c9                	test   %ecx,%ecx
    7f9bb08e05ca:	0f 95 c1             	setne  %cl
    7f9bb08e05cd:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08e05d0:	89 85 e0 fa ff ff    	mov    %eax,-0x520(%rbp)
    7f9bb08e05d6:	23 c8                	and    %eax,%ecx
    7f9bb08e05d8:	8b c1                	mov    %ecx,%eax
    7f9bb08e05da:	89 85 d8 fa ff ff    	mov    %eax,-0x528(%rbp)
    7f9bb08e05e0:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f9bb08e05e6:	0b c1                	or     %ecx,%eax
    7f9bb08e05e8:	8b 8d 58 fe ff ff    	mov    -0x1a8(%rbp),%ecx
    7f9bb08e05ee:	23 c1                	and    %ecx,%eax
    7f9bb08e05f0:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7f9bb08e05f6:	23 c8                	and    %eax,%ecx
    7f9bb08e05f8:	b8 01 00 00 00       	mov    $0x1,%eax
    7f9bb08e05fd:	3b c3                	cmp    %ebx,%eax
    7f9bb08e05ff:	0f 94 c0             	sete   %al
    7f9bb08e0602:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0605:	89 85 c8 fa ff ff    	mov    %eax,-0x538(%rbp)
    7f9bb08e060b:	8b 95 40 fb ff ff    	mov    -0x4c0(%rbp),%edx
    7f9bb08e0611:	23 c2                	and    %edx,%eax
    7f9bb08e0613:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7f9bb08e0619:	85 c9                	test   %ecx,%ecx
    7f9bb08e061b:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0640
    7f9bb08e0621:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7f9bb08e0627:	85 c0                	test   %eax,%eax
    7f9bb08e0629:	0f 85 20 00 00 00    	jne    0x7f9bb08e064f
    7f9bb08e062f:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7f9bb08e0635:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7f9bb08e063b:	e9 19 00 00 00       	jmpq   0x7f9bb08e0659
    7f9bb08e0640:	c7 85 b8 fa ff ff 01 	movl   $0x1,-0x548(%rbp)
    7f9bb08e0647:	00 00 00 
    7f9bb08e064a:	e9 0a 00 00 00       	jmpq   0x7f9bb08e0659
    7f9bb08e064f:	c7 85 b8 fa ff ff 00 	movl   $0x0,-0x548(%rbp)
    7f9bb08e0656:	00 00 00 
    7f9bb08e0659:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f9bb08e065c:	23 85 50 fe ff ff    	and    -0x1b0(%rbp),%eax
    7f9bb08e0662:	89 85 b0 fa ff ff    	mov    %eax,-0x550(%rbp)
    7f9bb08e0668:	33 c0                	xor    %eax,%eax
    7f9bb08e066a:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7f9bb08e0670:	3b c1                	cmp    %ecx,%eax
    7f9bb08e0672:	0f 94 c0             	sete   %al
    7f9bb08e0675:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0678:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f9bb08e067b:	8b d2                	mov    %edx,%edx
    7f9bb08e067d:	48 89 95 a8 fa ff ff 	mov    %rdx,-0x558(%rbp)
    7f9bb08e0684:	48 8d 95 a8 fa ff ff 	lea    -0x558(%rbp),%rdx
    7f9bb08e068b:	49 8b f7             	mov    %r15,%rsi
    7f9bb08e068e:	48 81 c6 c8 12 00 00 	add    $0x12c8,%rsi
    7f9bb08e0695:	b9 20 00 00 00       	mov    $0x20,%ecx
    7f9bb08e069a:	48 89 95 a0 fa ff ff 	mov    %rdx,-0x560(%rbp)
    7f9bb08e06a1:	48 89 b5 98 fa ff ff 	mov    %rsi,-0x568(%rbp)
    7f9bb08e06a8:	be 00 02 00 00       	mov    $0x200,%esi
    7f9bb08e06ad:	48 8b bd 98 fa ff ff 	mov    -0x568(%rbp),%rdi
    7f9bb08e06b4:	89 85 90 fa ff ff    	mov    %eax,-0x570(%rbp)
    7f9bb08e06ba:	b8 08 00 00 00       	mov    $0x8,%eax
    7f9bb08e06bf:	e8 2c ca bd ff       	callq  0x7f9bb04bd0f0
    7f9bb08e06c4:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f9bb08e06ca:	c1 e0 05             	shl    $0x5,%eax
    7f9bb08e06cd:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f9bb08e06d2:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e06d5:	48 81 c1 c8 12 00 00 	add    $0x12c8,%rcx
    7f9bb08e06dc:	49 8b d7             	mov    %r15,%rdx
    7f9bb08e06df:	48 81 c2 08 13 00 00 	add    $0x1308,%rdx
    7f9bb08e06e6:	44 8b c0             	mov    %eax,%r8d
    7f9bb08e06e9:	48 89 8d 88 fa ff ff 	mov    %rcx,-0x578(%rbp)
    7f9bb08e06f0:	b9 00 02 00 00       	mov    $0x200,%ecx
    7f9bb08e06f5:	48 89 95 80 fa ff ff 	mov    %rdx,-0x580(%rbp)
    7f9bb08e06fc:	48 8b 95 88 fa ff ff 	mov    -0x578(%rbp),%rdx
    7f9bb08e0703:	be 00 02 00 00       	mov    $0x200,%esi
    7f9bb08e0708:	48 8b bd 80 fa ff ff 	mov    -0x580(%rbp),%rdi
    7f9bb08e070f:	89 85 78 fa ff ff    	mov    %eax,-0x588(%rbp)
    7f9bb08e0715:	b8 08 00 00 00       	mov    $0x8,%eax
    7f9bb08e071a:	e8 61 9e bd ff       	callq  0x7f9bb04ba580
    7f9bb08e071f:	49 8b 87 08 13 00 00 	mov    0x1308(%r15),%rax
    7f9bb08e0726:	49 8b 8f 78 0f 00 00 	mov    0xf78(%r15),%rcx
    7f9bb08e072d:	48 0b c1             	or     %rcx,%rax
    7f9bb08e0730:	49 89 87 48 13 00 00 	mov    %rax,0x1348(%r15)
    7f9bb08e0737:	49 8b 87 10 13 00 00 	mov    0x1310(%r15),%rax
    7f9bb08e073e:	49 8b 8f 80 0f 00 00 	mov    0xf80(%r15),%rcx
    7f9bb08e0745:	48 0b c1             	or     %rcx,%rax
    7f9bb08e0748:	49 89 87 50 13 00 00 	mov    %rax,0x1350(%r15)
    7f9bb08e074f:	49 8b 87 18 13 00 00 	mov    0x1318(%r15),%rax
    7f9bb08e0756:	49 8b 8f 88 0f 00 00 	mov    0xf88(%r15),%rcx
    7f9bb08e075d:	48 0b c1             	or     %rcx,%rax
    7f9bb08e0760:	49 89 87 58 13 00 00 	mov    %rax,0x1358(%r15)
    7f9bb08e0767:	49 8b 87 20 13 00 00 	mov    0x1320(%r15),%rax
    7f9bb08e076e:	49 8b 8f 90 0f 00 00 	mov    0xf90(%r15),%rcx
    7f9bb08e0775:	48 0b c1             	or     %rcx,%rax
    7f9bb08e0778:	49 89 87 60 13 00 00 	mov    %rax,0x1360(%r15)
    7f9bb08e077f:	49 8b 87 28 13 00 00 	mov    0x1328(%r15),%rax
    7f9bb08e0786:	49 8b 8f 98 0f 00 00 	mov    0xf98(%r15),%rcx
    7f9bb08e078d:	48 0b c1             	or     %rcx,%rax
    7f9bb08e0790:	49 89 87 68 13 00 00 	mov    %rax,0x1368(%r15)
    7f9bb08e0797:	49 8b 87 30 13 00 00 	mov    0x1330(%r15),%rax
    7f9bb08e079e:	49 8b 8f a0 0f 00 00 	mov    0xfa0(%r15),%rcx
    7f9bb08e07a5:	48 0b c1             	or     %rcx,%rax
    7f9bb08e07a8:	49 89 87 70 13 00 00 	mov    %rax,0x1370(%r15)
    7f9bb08e07af:	49 8b 87 38 13 00 00 	mov    0x1338(%r15),%rax
    7f9bb08e07b6:	49 8b 8f a8 0f 00 00 	mov    0xfa8(%r15),%rcx
    7f9bb08e07bd:	48 0b c1             	or     %rcx,%rax
    7f9bb08e07c0:	49 89 87 78 13 00 00 	mov    %rax,0x1378(%r15)
    7f9bb08e07c7:	49 8b 87 40 13 00 00 	mov    0x1340(%r15),%rax
    7f9bb08e07ce:	49 8b 8f b0 0f 00 00 	mov    0xfb0(%r15),%rcx
    7f9bb08e07d5:	48 0b c1             	or     %rcx,%rax
    7f9bb08e07d8:	49 89 87 80 13 00 00 	mov    %rax,0x1380(%r15)
    7f9bb08e07df:	8b 85 90 fa ff ff    	mov    -0x570(%rbp),%eax
    7f9bb08e07e5:	85 c0                	test   %eax,%eax
    7f9bb08e07e7:	0f 85 36 00 00 00    	jne    0x7f9bb08e0823
    7f9bb08e07ed:	49 8b c7             	mov    %r15,%rax
    7f9bb08e07f0:	48 05 88 11 00 00    	add    $0x1188,%rax
    7f9bb08e07f6:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e07f9:	48 81 c1 48 13 00 00 	add    $0x1348,%rcx
    7f9bb08e0800:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0803:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0806:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e080a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e080e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0812:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0816:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e081a:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e081e:	e9 31 00 00 00       	jmpq   0x7f9bb08e0854
    7f9bb08e0823:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0826:	48 05 88 11 00 00    	add    $0x1188,%rax
    7f9bb08e082c:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e082f:	48 81 c1 c8 12 00 00 	add    $0x12c8,%rcx
    7f9bb08e0836:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0839:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e083c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0840:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0844:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0848:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e084c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0850:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0854:	8b 85 b0 fa ff ff    	mov    -0x550(%rbp),%eax
    7f9bb08e085a:	85 c0                	test   %eax,%eax
    7f9bb08e085c:	0f 85 36 00 00 00    	jne    0x7f9bb08e0898
    7f9bb08e0862:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0865:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7f9bb08e086b:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e086e:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7f9bb08e0875:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0878:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e087b:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e087f:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0883:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0887:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e088b:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e088f:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0893:	e9 31 00 00 00       	jmpq   0x7f9bb08e08c9
    7f9bb08e0898:	49 8b c7             	mov    %r15,%rax
    7f9bb08e089b:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7f9bb08e08a1:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e08a4:	48 81 c1 88 11 00 00 	add    $0x1188,%rcx
    7f9bb08e08ab:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e08ae:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e08b1:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e08b5:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e08b9:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e08bd:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e08c1:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e08c5:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e08c9:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f9bb08e08cf:	83 f8 0f             	cmp    $0xf,%eax
    7f9bb08e08d2:	0f 94 c0             	sete   %al
    7f9bb08e08d5:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e08d8:	23 45 e0             	and    -0x20(%rbp),%eax
    7f9bb08e08db:	85 c0                	test   %eax,%eax
    7f9bb08e08dd:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0902
    7f9bb08e08e3:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7f9bb08e08e9:	85 c0                	test   %eax,%eax
    7f9bb08e08eb:	0f 85 20 00 00 00    	jne    0x7f9bb08e0911
    7f9bb08e08f1:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7f9bb08e08f7:	89 85 70 fa ff ff    	mov    %eax,-0x590(%rbp)
    7f9bb08e08fd:	e9 19 00 00 00       	jmpq   0x7f9bb08e091b
    7f9bb08e0902:	c7 85 70 fa ff ff 01 	movl   $0x1,-0x590(%rbp)
    7f9bb08e0909:	00 00 00 
    7f9bb08e090c:	e9 0a 00 00 00       	jmpq   0x7f9bb08e091b
    7f9bb08e0911:	c7 85 70 fa ff ff 00 	movl   $0x0,-0x590(%rbp)
    7f9bb08e0918:	00 00 00 
    7f9bb08e091b:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f9bb08e0921:	ff c0                	inc    %eax
    7f9bb08e0923:	83 e0 0f             	and    $0xf,%eax
    7f9bb08e0926:	89 85 68 fa ff ff    	mov    %eax,-0x598(%rbp)
    7f9bb08e092c:	8b 85 b0 fa ff ff    	mov    -0x550(%rbp),%eax
    7f9bb08e0932:	85 c0                	test   %eax,%eax
    7f9bb08e0934:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0946
    7f9bb08e093a:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f9bb08e0940:	89 85 68 fa ff ff    	mov    %eax,-0x598(%rbp)
    7f9bb08e0946:	41 8b c4             	mov    %r12d,%eax
    7f9bb08e0949:	0b 85 d8 fa ff ff    	or     -0x528(%rbp),%eax
    7f9bb08e094f:	89 85 60 fa ff ff    	mov    %eax,-0x5a0(%rbp)
    7f9bb08e0955:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7f9bb08e095b:	23 85 58 fe ff ff    	and    -0x1a8(%rbp),%eax
    7f9bb08e0961:	8b 8d 40 fb ff ff    	mov    -0x4c0(%rbp),%ecx
    7f9bb08e0967:	23 8d 28 fb ff ff    	and    -0x4d8(%rbp),%ecx
    7f9bb08e096d:	85 c9                	test   %ecx,%ecx
    7f9bb08e096f:	0f 94 c2             	sete   %dl
    7f9bb08e0972:	0f b6 d2             	movzbl %dl,%edx
    7f9bb08e0975:	89 95 58 fa ff ff    	mov    %edx,-0x5a8(%rbp)
    7f9bb08e097b:	23 d0                	and    %eax,%edx
    7f9bb08e097d:	8b f3                	mov    %ebx,%esi
    7f9bb08e097f:	ff c6                	inc    %esi
    7f9bb08e0981:	83 e6 1f             	and    $0x1f,%esi
    7f9bb08e0984:	89 b5 50 fa ff ff    	mov    %esi,-0x5b0(%rbp)
    7f9bb08e098a:	89 85 48 fa ff ff    	mov    %eax,-0x5b8(%rbp)
    7f9bb08e0990:	85 c0                	test   %eax,%eax
    7f9bb08e0992:	0f 94 c0             	sete   %al
    7f9bb08e0995:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0998:	89 8d 40 fa ff ff    	mov    %ecx,-0x5c0(%rbp)
    7f9bb08e099e:	89 85 38 fa ff ff    	mov    %eax,-0x5c8(%rbp)
    7f9bb08e09a4:	23 c8                	and    %eax,%ecx
    7f9bb08e09a6:	89 8d 30 fa ff ff    	mov    %ecx,-0x5d0(%rbp)
    7f9bb08e09ac:	8b c3                	mov    %ebx,%eax
    7f9bb08e09ae:	ff c8                	dec    %eax
    7f9bb08e09b0:	83 e0 1f             	and    $0x1f,%eax
    7f9bb08e09b3:	89 85 28 fa ff ff    	mov    %eax,-0x5d8(%rbp)
    7f9bb08e09b9:	85 d2                	test   %edx,%edx
    7f9bb08e09bb:	0f 85 1b 00 00 00    	jne    0x7f9bb08e09dc
    7f9bb08e09c1:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7f9bb08e09c7:	85 c0                	test   %eax,%eax
    7f9bb08e09c9:	0f 85 1e 00 00 00    	jne    0x7f9bb08e09ed
    7f9bb08e09cf:	8b c3                	mov    %ebx,%eax
    7f9bb08e09d1:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7f9bb08e09d7:	e9 1d 00 00 00       	jmpq   0x7f9bb08e09f9
    7f9bb08e09dc:	8b 85 50 fa ff ff    	mov    -0x5b0(%rbp),%eax
    7f9bb08e09e2:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7f9bb08e09e8:	e9 0c 00 00 00       	jmpq   0x7f9bb08e09f9
    7f9bb08e09ed:	8b 85 28 fa ff ff    	mov    -0x5d8(%rbp),%eax
    7f9bb08e09f3:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7f9bb08e09f9:	83 fb 01             	cmp    $0x1,%ebx
    7f9bb08e09fc:	0f 94 c0             	sete   %al
    7f9bb08e09ff:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0a02:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7f9bb08e0a08:	23 c1                	and    %ecx,%eax
    7f9bb08e0a0a:	23 85 38 fa ff ff    	and    -0x5c8(%rbp),%eax
    7f9bb08e0a10:	85 c9                	test   %ecx,%ecx
    7f9bb08e0a12:	0f 94 c1             	sete   %cl
    7f9bb08e0a15:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08e0a18:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7f9bb08e0a1e:	23 ca                	and    %edx,%ecx
    7f9bb08e0a20:	89 8d 18 fa ff ff    	mov    %ecx,-0x5e8(%rbp)
    7f9bb08e0a26:	85 c0                	test   %eax,%eax
    7f9bb08e0a28:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0a4d
    7f9bb08e0a2e:	8b 85 18 fa ff ff    	mov    -0x5e8(%rbp),%eax
    7f9bb08e0a34:	85 c0                	test   %eax,%eax
    7f9bb08e0a36:	0f 85 20 00 00 00    	jne    0x7f9bb08e0a5c
    7f9bb08e0a3c:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7f9bb08e0a42:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7f9bb08e0a48:	e9 19 00 00 00       	jmpq   0x7f9bb08e0a66
    7f9bb08e0a4d:	c7 85 10 fa ff ff 01 	movl   $0x1,-0x5f0(%rbp)
    7f9bb08e0a54:	00 00 00 
    7f9bb08e0a57:	e9 0a 00 00 00       	jmpq   0x7f9bb08e0a66
    7f9bb08e0a5c:	c7 85 10 fa ff ff 00 	movl   $0x0,-0x5f0(%rbp)
    7f9bb08e0a63:	00 00 00 
    7f9bb08e0a66:	83 fb 0f             	cmp    $0xf,%ebx
    7f9bb08e0a69:	0f 94 c0             	sete   %al
    7f9bb08e0a6c:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e0a6f:	23 85 48 fa ff ff    	and    -0x5b8(%rbp),%eax
    7f9bb08e0a75:	23 85 58 fa ff ff    	and    -0x5a8(%rbp),%eax
    7f9bb08e0a7b:	85 c0                	test   %eax,%eax
    7f9bb08e0a7d:	0f 85 1f 00 00 00    	jne    0x7f9bb08e0aa2
    7f9bb08e0a83:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7f9bb08e0a89:	85 c0                	test   %eax,%eax
    7f9bb08e0a8b:	0f 85 20 00 00 00    	jne    0x7f9bb08e0ab1
    7f9bb08e0a91:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f9bb08e0a97:	89 85 08 fa ff ff    	mov    %eax,-0x5f8(%rbp)
    7f9bb08e0a9d:	e9 19 00 00 00       	jmpq   0x7f9bb08e0abb
    7f9bb08e0aa2:	c7 85 08 fa ff ff 01 	movl   $0x1,-0x5f8(%rbp)
    7f9bb08e0aa9:	00 00 00 
    7f9bb08e0aac:	e9 0a 00 00 00       	jmpq   0x7f9bb08e0abb
    7f9bb08e0ab1:	c7 85 08 fa ff ff 00 	movl   $0x0,-0x5f8(%rbp)
    7f9bb08e0ab8:	00 00 00 
    7f9bb08e0abb:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f9bb08e0ac1:	ff c0                	inc    %eax
    7f9bb08e0ac3:	83 e0 0f             	and    $0xf,%eax
    7f9bb08e0ac6:	89 85 00 fa ff ff    	mov    %eax,-0x600(%rbp)
    7f9bb08e0acc:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7f9bb08e0ad2:	85 c0                	test   %eax,%eax
    7f9bb08e0ad4:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0ae6
    7f9bb08e0ada:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f9bb08e0ae0:	89 85 00 fa ff ff    	mov    %eax,-0x600(%rbp)
    7f9bb08e0ae6:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f9bb08e0aec:	83 c0 02             	add    $0x2,%eax
    7f9bb08e0aef:	83 e0 0f             	and    $0xf,%eax
    7f9bb08e0af2:	89 85 f8 f9 ff ff    	mov    %eax,-0x608(%rbp)
    7f9bb08e0af8:	8b 85 c8 fa ff ff    	mov    -0x538(%rbp),%eax
    7f9bb08e0afe:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7f9bb08e0b04:	23 c1                	and    %ecx,%eax
    7f9bb08e0b06:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7f9bb08e0b0c:	0b c2                	or     %edx,%eax
    7f9bb08e0b0e:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7f9bb08e0b14:	23 c2                	and    %edx,%eax
    7f9bb08e0b16:	89 85 f0 f9 ff ff    	mov    %eax,-0x610(%rbp)
    7f9bb08e0b1c:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f9bb08e0b22:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7f9bb08e0b28:	85 c9                	test   %ecx,%ecx
    7f9bb08e0b2a:	0f 85 0c 00 00 00    	jne    0x7f9bb08e0b3c
    7f9bb08e0b30:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f9bb08e0b36:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7f9bb08e0b3c:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0b3f:	48 05 00 08 00 00    	add    $0x800,%rax
    7f9bb08e0b45:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0b48:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7f9bb08e0b4f:	8b 95 e8 f9 ff ff    	mov    -0x618(%rbp),%edx
    7f9bb08e0b55:	c1 e2 06             	shl    $0x6,%edx
    7f9bb08e0b58:	8b d2                	mov    %edx,%edx
    7f9bb08e0b5a:	48 03 c2             	add    %rdx,%rax
    7f9bb08e0b5d:	0f 10 00             	movups (%rax),%xmm0
    7f9bb08e0b60:	0f 11 01             	movups %xmm0,(%rcx)
    7f9bb08e0b63:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7f9bb08e0b67:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7f9bb08e0b6b:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7f9bb08e0b6f:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7f9bb08e0b73:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7f9bb08e0b77:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7f9bb08e0b7b:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7f9bb08e0b81:	85 c0                	test   %eax,%eax
    7f9bb08e0b83:	0f 84 3f 00 00 00    	je     0x7f9bb08e0bc8
    7f9bb08e0b89:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0b8c:	48 05 00 08 00 00    	add    $0x800,%rax
    7f9bb08e0b92:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0b95:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7f9bb08e0b9c:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7f9bb08e0ba2:	c1 e2 06             	shl    $0x6,%edx
    7f9bb08e0ba5:	8b d2                	mov    %edx,%edx
    7f9bb08e0ba7:	48 03 c2             	add    %rdx,%rax
    7f9bb08e0baa:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0bad:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0bb0:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0bb4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0bb8:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0bbc:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0bc0:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0bc4:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0bc8:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f9bb08e0bce:	85 c0                	test   %eax,%eax
    7f9bb08e0bd0:	0f 84 3c 00 00 00    	je     0x7f9bb08e0c12
    7f9bb08e0bd6:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0bd9:	48 05 00 04 00 00    	add    $0x400,%rax
    7f9bb08e0bdf:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7f9bb08e0be5:	c1 e1 06             	shl    $0x6,%ecx
    7f9bb08e0be8:	8b c9                	mov    %ecx,%ecx
    7f9bb08e0bea:	48 03 c1             	add    %rcx,%rax
    7f9bb08e0bed:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7f9bb08e0bf4:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0bf7:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0bfa:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0bfe:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0c02:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0c06:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0c0a:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0c0e:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0c12:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7f9bb08e0c18:	85 c0                	test   %eax,%eax
    7f9bb08e0c1a:	0f 84 30 00 00 00    	je     0x7f9bb08e0c50
    7f9bb08e0c20:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f9bb08e0c23:	c1 e0 06             	shl    $0x6,%eax
    7f9bb08e0c26:	8b c0                	mov    %eax,%eax
    7f9bb08e0c28:	49 03 c7             	add    %r15,%rax
    7f9bb08e0c2b:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7f9bb08e0c32:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0c35:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0c38:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0c3c:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0c40:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0c44:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0c48:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0c4c:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0c50:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0c53:	48 05 48 10 00 00    	add    $0x1048,%rax
    7f9bb08e0c59:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0c5c:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7f9bb08e0c63:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0c66:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0c69:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0c6d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0c71:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0c75:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0c79:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0c7d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0c81:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0c84:	48 05 08 10 00 00    	add    $0x1008,%rax
    7f9bb08e0c8a:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0c8d:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7f9bb08e0c94:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0c97:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0c9a:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0c9e:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0ca2:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0ca6:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0caa:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0cae:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0cb2:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e0cb5:	0f 84 44 00 00 00    	je     0x7f9bb08e0cff
    7f9bb08e0cbb:	41 c7 87 00 10 00 00 	movl   $0x0,0x1000(%r15)
    7f9bb08e0cc2:	00 00 00 00 
    7f9bb08e0cc6:	c7 85 90 fe ff ff 00 	movl   $0x0,-0x170(%rbp)
    7f9bb08e0ccd:	00 00 00 
    7f9bb08e0cd0:	41 c7 87 f0 0f 00 00 	movl   $0x0,0xff0(%r15)
    7f9bb08e0cd7:	00 00 00 00 
    7f9bb08e0cdb:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7f9bb08e0ce2:	00 00 00 
    7f9bb08e0ce5:	41 c7 87 f8 0f 00 00 	movl   $0x1,0xff8(%r15)
    7f9bb08e0cec:	01 00 00 00 
    7f9bb08e0cf0:	c7 85 98 fe ff ff 01 	movl   $0x1,-0x168(%rbp)
    7f9bb08e0cf7:	00 00 00 
    7f9bb08e0cfa:	e9 47 00 00 00       	jmpq   0x7f9bb08e0d46
    7f9bb08e0cff:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7f9bb08e0d05:	41 89 87 00 10 00 00 	mov    %eax,0x1000(%r15)
    7f9bb08e0d0c:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f9bb08e0d12:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7f9bb08e0d18:	85 c0                	test   %eax,%eax
    7f9bb08e0d1a:	0f 84 26 00 00 00    	je     0x7f9bb08e0d46
    7f9bb08e0d20:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f9bb08e0d26:	41 89 87 f0 0f 00 00 	mov    %eax,0xff0(%r15)
    7f9bb08e0d2d:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f9bb08e0d33:	8b 85 f8 f9 ff ff    	mov    -0x608(%rbp),%eax
    7f9bb08e0d39:	41 89 87 f8 0f 00 00 	mov    %eax,0xff8(%r15)
    7f9bb08e0d40:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f9bb08e0d46:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f9bb08e0d4c:	85 c0                	test   %eax,%eax
    7f9bb08e0d4e:	0f 84 1a 00 00 00    	je     0x7f9bb08e0d6e
    7f9bb08e0d54:	41 c7 87 e8 0f 00 00 	movl   $0x0,0xfe8(%r15)
    7f9bb08e0d5b:	00 00 00 00 
    7f9bb08e0d5f:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7f9bb08e0d66:	00 00 00 
    7f9bb08e0d69:	e9 13 00 00 00       	jmpq   0x7f9bb08e0d81
    7f9bb08e0d6e:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7f9bb08e0d74:	41 89 87 e8 0f 00 00 	mov    %eax,0xfe8(%r15)
    7f9bb08e0d7b:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f9bb08e0d81:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e0d84:	0f 84 51 00 00 00    	je     0x7f9bb08e0ddb
    7f9bb08e0d8a:	41 c7 87 e0 0f 00 00 	movl   $0x0,0xfe0(%r15)
    7f9bb08e0d91:	00 00 00 00 
    7f9bb08e0d95:	c7 85 b0 fe ff ff 00 	movl   $0x0,-0x150(%rbp)
    7f9bb08e0d9c:	00 00 00 
    7f9bb08e0d9f:	41 c7 87 d8 0f 00 00 	movl   $0x1,0xfd8(%r15)
    7f9bb08e0da6:	01 00 00 00 
    7f9bb08e0daa:	c7 85 b8 fe ff ff 01 	movl   $0x1,-0x148(%rbp)
    7f9bb08e0db1:	00 00 00 
    7f9bb08e0db4:	41 c7 87 d0 0f 00 00 	movl   $0x0,0xfd0(%r15)
    7f9bb08e0dbb:	00 00 00 00 
    7f9bb08e0dbf:	33 db                	xor    %ebx,%ebx
    7f9bb08e0dc1:	41 c7 87 c8 0f 00 00 	movl   $0x0,0xfc8(%r15)
    7f9bb08e0dc8:	00 00 00 00 
    7f9bb08e0dcc:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7f9bb08e0dd3:	00 00 00 
    7f9bb08e0dd6:	e9 49 00 00 00       	jmpq   0x7f9bb08e0e24
    7f9bb08e0ddb:	8b 85 08 fa ff ff    	mov    -0x5f8(%rbp),%eax
    7f9bb08e0de1:	41 89 87 e0 0f 00 00 	mov    %eax,0xfe0(%r15)
    7f9bb08e0de8:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f9bb08e0dee:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7f9bb08e0df4:	41 89 87 d8 0f 00 00 	mov    %eax,0xfd8(%r15)
    7f9bb08e0dfb:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f9bb08e0e01:	8b 85 20 fa ff ff    	mov    -0x5e0(%rbp),%eax
    7f9bb08e0e07:	41 89 87 d0 0f 00 00 	mov    %eax,0xfd0(%r15)
    7f9bb08e0e0e:	48 8b d8             	mov    %rax,%rbx
    7f9bb08e0e11:	8b 85 e0 fa ff ff    	mov    -0x520(%rbp),%eax
    7f9bb08e0e17:	41 89 87 c8 0f 00 00 	mov    %eax,0xfc8(%r15)
    7f9bb08e0e1e:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f9bb08e0e24:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7f9bb08e0e2a:	85 c0                	test   %eax,%eax
    7f9bb08e0e2c:	0f 84 1a 00 00 00    	je     0x7f9bb08e0e4c
    7f9bb08e0e32:	41 c7 87 c0 0f 00 00 	movl   $0x0,0xfc0(%r15)
    7f9bb08e0e39:	00 00 00 00 
    7f9bb08e0e3d:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7f9bb08e0e44:	00 00 00 
    7f9bb08e0e47:	e9 13 00 00 00       	jmpq   0x7f9bb08e0e5f
    7f9bb08e0e4c:	8b 85 68 fa ff ff    	mov    -0x598(%rbp),%eax
    7f9bb08e0e52:	41 89 87 c0 0f 00 00 	mov    %eax,0xfc0(%r15)
    7f9bb08e0e59:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f9bb08e0e5f:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e0e62:	0f 84 1a 00 00 00    	je     0x7f9bb08e0e82
    7f9bb08e0e68:	41 c7 87 b8 0f 00 00 	movl   $0x0,0xfb8(%r15)
    7f9bb08e0e6f:	00 00 00 00 
    7f9bb08e0e73:	c7 85 d0 fe ff ff 00 	movl   $0x0,-0x130(%rbp)
    7f9bb08e0e7a:	00 00 00 
    7f9bb08e0e7d:	e9 13 00 00 00       	jmpq   0x7f9bb08e0e95
    7f9bb08e0e82:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7f9bb08e0e88:	41 89 87 b8 0f 00 00 	mov    %eax,0xfb8(%r15)
    7f9bb08e0e8f:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f9bb08e0e95:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0e98:	48 05 78 0f 00 00    	add    $0xf78,%rax
    7f9bb08e0e9e:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0ea1:	48 81 c1 c8 11 00 00 	add    $0x11c8,%rcx
    7f9bb08e0ea8:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0eab:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0eae:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0eb2:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0eb6:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0eba:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0ebe:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0ec2:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0ec6:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7f9bb08e0ecc:	85 c0                	test   %eax,%eax
    7f9bb08e0ece:	0f 84 13 00 00 00    	je     0x7f9bb08e0ee7
    7f9bb08e0ed4:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7f9bb08e0eda:	41 89 87 70 0f 00 00 	mov    %eax,0xf70(%r15)
    7f9bb08e0ee1:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f9bb08e0ee7:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e0eea:	0f 84 5a 00 00 00    	je     0x7f9bb08e0f4a
    7f9bb08e0ef0:	41 c7 87 68 0f 00 00 	movl   $0x0,0xf68(%r15)
    7f9bb08e0ef7:	00 00 00 00 
    7f9bb08e0efb:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7f9bb08e0f02:	00 00 00 
    7f9bb08e0f05:	41 c7 87 60 0f 00 00 	movl   $0x0,0xf60(%r15)
    7f9bb08e0f0c:	00 00 00 00 
    7f9bb08e0f10:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7f9bb08e0f17:	00 00 00 
    7f9bb08e0f1a:	41 c7 87 58 0f 00 00 	movl   $0x0,0xf58(%r15)
    7f9bb08e0f21:	00 00 00 00 
    7f9bb08e0f25:	c7 85 f0 fe ff ff 00 	movl   $0x0,-0x110(%rbp)
    7f9bb08e0f2c:	00 00 00 
    7f9bb08e0f2f:	49 c7 87 50 0f 00 00 	movq   $0x0,0xf50(%r15)
    7f9bb08e0f36:	00 00 00 00 
    7f9bb08e0f3a:	48 c7 85 f8 fe ff ff 	movq   $0x0,-0x108(%rbp)
    7f9bb08e0f41:	00 00 00 00 
    7f9bb08e0f45:	e9 4e 00 00 00       	jmpq   0x7f9bb08e0f98
    7f9bb08e0f4a:	8b 85 b8 fa ff ff    	mov    -0x548(%rbp),%eax
    7f9bb08e0f50:	41 89 87 68 0f 00 00 	mov    %eax,0xf68(%r15)
    7f9bb08e0f57:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f9bb08e0f5d:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7f9bb08e0f63:	41 89 87 60 0f 00 00 	mov    %eax,0xf60(%r15)
    7f9bb08e0f6a:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f9bb08e0f70:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7f9bb08e0f76:	41 89 87 58 0f 00 00 	mov    %eax,0xf58(%r15)
    7f9bb08e0f7d:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f9bb08e0f83:	48 8b 85 30 fb ff ff 	mov    -0x4d0(%rbp),%rax
    7f9bb08e0f8a:	49 89 87 50 0f 00 00 	mov    %rax,0xf50(%r15)
    7f9bb08e0f91:	48 89 85 f8 fe ff ff 	mov    %rax,-0x108(%rbp)
    7f9bb08e0f98:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0f9b:	48 05 10 0f 00 00    	add    $0xf10,%rax
    7f9bb08e0fa1:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e0fa4:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7f9bb08e0fab:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0fae:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0fb1:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0fb5:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0fb9:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0fbd:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0fc1:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0fc5:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0fc9:	49 8b c7             	mov    %r15,%rax
    7f9bb08e0fcc:	48 05 d0 0e 00 00    	add    $0xed0,%rax
    7f9bb08e0fd2:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7f9bb08e0fd9:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e0fdc:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e0fdf:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e0fe3:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e0fe7:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e0feb:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e0fef:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e0ff3:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e0ff7:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e0ffa:	0f 84 44 00 00 00    	je     0x7f9bb08e1044
    7f9bb08e1000:	41 c7 87 c8 0e 00 00 	movl   $0x0,0xec8(%r15)
    7f9bb08e1007:	00 00 00 00 
    7f9bb08e100b:	c7 85 00 ff ff ff 00 	movl   $0x0,-0x100(%rbp)
    7f9bb08e1012:	00 00 00 
    7f9bb08e1015:	41 c7 87 b8 0e 00 00 	movl   $0x0,0xeb8(%r15)
    7f9bb08e101c:	00 00 00 00 
    7f9bb08e1020:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7f9bb08e1027:	00 00 00 
    7f9bb08e102a:	41 c7 87 c0 0e 00 00 	movl   $0x1,0xec0(%r15)
    7f9bb08e1031:	01 00 00 00 
    7f9bb08e1035:	c7 85 08 ff ff ff 01 	movl   $0x1,-0xf8(%rbp)
    7f9bb08e103c:	00 00 00 
    7f9bb08e103f:	e9 47 00 00 00       	jmpq   0x7f9bb08e108b
    7f9bb08e1044:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7f9bb08e104a:	41 89 87 c8 0e 00 00 	mov    %eax,0xec8(%r15)
    7f9bb08e1051:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f9bb08e1057:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7f9bb08e105d:	85 c0                	test   %eax,%eax
    7f9bb08e105f:	0f 84 26 00 00 00    	je     0x7f9bb08e108b
    7f9bb08e1065:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f9bb08e106b:	41 89 87 b8 0e 00 00 	mov    %eax,0xeb8(%r15)
    7f9bb08e1072:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f9bb08e1078:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7f9bb08e107e:	41 89 87 c0 0e 00 00 	mov    %eax,0xec0(%r15)
    7f9bb08e1085:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f9bb08e108b:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f9bb08e1091:	85 c0                	test   %eax,%eax
    7f9bb08e1093:	0f 84 1a 00 00 00    	je     0x7f9bb08e10b3
    7f9bb08e1099:	41 c7 87 b0 0e 00 00 	movl   $0x0,0xeb0(%r15)
    7f9bb08e10a0:	00 00 00 00 
    7f9bb08e10a4:	c7 85 18 ff ff ff 00 	movl   $0x0,-0xe8(%rbp)
    7f9bb08e10ab:	00 00 00 
    7f9bb08e10ae:	e9 13 00 00 00       	jmpq   0x7f9bb08e10c6
    7f9bb08e10b3:	8b 85 78 fb ff ff    	mov    -0x488(%rbp),%eax
    7f9bb08e10b9:	41 89 87 b0 0e 00 00 	mov    %eax,0xeb0(%r15)
    7f9bb08e10c0:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f9bb08e10c6:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e10c9:	0f 84 44 00 00 00    	je     0x7f9bb08e1113
    7f9bb08e10cf:	41 c7 87 a8 0e 00 00 	movl   $0x0,0xea8(%r15)
    7f9bb08e10d6:	00 00 00 00 
    7f9bb08e10da:	c7 85 20 ff ff ff 00 	movl   $0x0,-0xe0(%rbp)
    7f9bb08e10e1:	00 00 00 
    7f9bb08e10e4:	41 c7 87 a0 0e 00 00 	movl   $0x1,0xea0(%r15)
    7f9bb08e10eb:	01 00 00 00 
    7f9bb08e10ef:	c7 85 28 ff ff ff 01 	movl   $0x1,-0xd8(%rbp)
    7f9bb08e10f6:	00 00 00 
    7f9bb08e10f9:	41 c7 87 98 0e 00 00 	movl   $0x0,0xe98(%r15)
    7f9bb08e1100:	00 00 00 00 
    7f9bb08e1104:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7f9bb08e110b:	00 00 00 
    7f9bb08e110e:	e9 39 00 00 00       	jmpq   0x7f9bb08e114c
    7f9bb08e1113:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7f9bb08e1119:	41 89 87 a8 0e 00 00 	mov    %eax,0xea8(%r15)
    7f9bb08e1120:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f9bb08e1126:	8b 85 88 fb ff ff    	mov    -0x478(%rbp),%eax
    7f9bb08e112c:	41 89 87 a0 0e 00 00 	mov    %eax,0xea0(%r15)
    7f9bb08e1133:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f9bb08e1139:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7f9bb08e113f:	41 89 87 98 0e 00 00 	mov    %eax,0xe98(%r15)
    7f9bb08e1146:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f9bb08e114c:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f9bb08e1152:	85 c0                	test   %eax,%eax
    7f9bb08e1154:	0f 84 1a 00 00 00    	je     0x7f9bb08e1174
    7f9bb08e115a:	41 c7 87 90 0e 00 00 	movl   $0x0,0xe90(%r15)
    7f9bb08e1161:	00 00 00 00 
    7f9bb08e1165:	c7 85 38 ff ff ff 00 	movl   $0x0,-0xc8(%rbp)
    7f9bb08e116c:	00 00 00 
    7f9bb08e116f:	e9 13 00 00 00       	jmpq   0x7f9bb08e1187
    7f9bb08e1174:	8b 85 d8 fb ff ff    	mov    -0x428(%rbp),%eax
    7f9bb08e117a:	41 89 87 90 0e 00 00 	mov    %eax,0xe90(%r15)
    7f9bb08e1181:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f9bb08e1187:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e118a:	0f 84 1a 00 00 00    	je     0x7f9bb08e11aa
    7f9bb08e1190:	41 c7 87 88 0e 00 00 	movl   $0x0,0xe88(%r15)
    7f9bb08e1197:	00 00 00 00 
    7f9bb08e119b:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7f9bb08e11a2:	00 00 00 
    7f9bb08e11a5:	e9 13 00 00 00       	jmpq   0x7f9bb08e11bd
    7f9bb08e11aa:	8b 85 e0 fb ff ff    	mov    -0x420(%rbp),%eax
    7f9bb08e11b0:	41 89 87 88 0e 00 00 	mov    %eax,0xe88(%r15)
    7f9bb08e11b7:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f9bb08e11bd:	49 8b c7             	mov    %r15,%rax
    7f9bb08e11c0:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7f9bb08e11c6:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e11c9:	48 81 c1 08 11 00 00 	add    $0x1108,%rcx
    7f9bb08e11d0:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e11d3:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e11d6:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e11da:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e11de:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e11e2:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e11e6:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e11ea:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e11ee:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e11f1:	0f 84 6f 00 00 00    	je     0x7f9bb08e1266
    7f9bb08e11f7:	41 c7 87 40 0e 00 00 	movl   $0x0,0xe40(%r15)
    7f9bb08e11fe:	00 00 00 00 
    7f9bb08e1202:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7f9bb08e1209:	00 00 00 
    7f9bb08e120c:	41 c7 87 38 0e 00 00 	movl   $0x0,0xe38(%r15)
    7f9bb08e1213:	00 00 00 00 
    7f9bb08e1217:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7f9bb08e121e:	00 00 00 
    7f9bb08e1221:	41 c7 87 30 0e 00 00 	movl   $0x0,0xe30(%r15)
    7f9bb08e1228:	00 00 00 00 
    7f9bb08e122c:	c7 85 58 ff ff ff 00 	movl   $0x0,-0xa8(%rbp)
    7f9bb08e1233:	00 00 00 
    7f9bb08e1236:	41 c7 87 28 0e 00 00 	movl   $0x0,0xe28(%r15)
    7f9bb08e123d:	00 00 00 00 
    7f9bb08e1241:	c7 85 60 ff ff ff 00 	movl   $0x0,-0xa0(%rbp)
    7f9bb08e1248:	00 00 00 
    7f9bb08e124b:	49 c7 87 20 0e 00 00 	movq   $0x0,0xe20(%r15)
    7f9bb08e1252:	00 00 00 00 
    7f9bb08e1256:	48 c7 85 68 ff ff ff 	movq   $0x0,-0x98(%rbp)
    7f9bb08e125d:	00 00 00 00 
    7f9bb08e1261:	e9 61 00 00 00       	jmpq   0x7f9bb08e12c7
    7f9bb08e1266:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7f9bb08e126c:	41 89 87 40 0e 00 00 	mov    %eax,0xe40(%r15)
    7f9bb08e1273:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f9bb08e1279:	8b 85 08 fc ff ff    	mov    -0x3f8(%rbp),%eax
    7f9bb08e127f:	41 89 87 38 0e 00 00 	mov    %eax,0xe38(%r15)
    7f9bb08e1286:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f9bb08e128c:	8b 85 20 fc ff ff    	mov    -0x3e0(%rbp),%eax
    7f9bb08e1292:	41 89 87 30 0e 00 00 	mov    %eax,0xe30(%r15)
    7f9bb08e1299:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f9bb08e129f:	8b 85 30 fc ff ff    	mov    -0x3d0(%rbp),%eax
    7f9bb08e12a5:	41 89 87 28 0e 00 00 	mov    %eax,0xe28(%r15)
    7f9bb08e12ac:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f9bb08e12b2:	48 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%rax
    7f9bb08e12b9:	49 89 87 20 0e 00 00 	mov    %rax,0xe20(%r15)
    7f9bb08e12c0:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
    7f9bb08e12c7:	49 8b c7             	mov    %r15,%rax
    7f9bb08e12ca:	48 05 e0 0d 00 00    	add    $0xde0,%rax
    7f9bb08e12d0:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e12d3:	48 81 c1 00 0c 00 00 	add    $0xc00,%rcx
    7f9bb08e12da:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e12dd:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e12e0:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e12e4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e12e8:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e12ec:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e12f0:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e12f4:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e12f8:	49 8b c7             	mov    %r15,%rax
    7f9bb08e12fb:	48 05 a0 0d 00 00    	add    $0xda0,%rax
    7f9bb08e1301:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7f9bb08e1308:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e130b:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e130e:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e1312:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e1316:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e131a:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e131e:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e1322:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e1326:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e1329:	0f 84 41 00 00 00    	je     0x7f9bb08e1370
    7f9bb08e132f:	41 c7 87 98 0d 00 00 	movl   $0x0,0xd98(%r15)
    7f9bb08e1336:	00 00 00 00 
    7f9bb08e133a:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7f9bb08e1341:	00 00 00 
    7f9bb08e1344:	41 c7 87 88 0d 00 00 	movl   $0x0,0xd88(%r15)
    7f9bb08e134b:	00 00 00 00 
    7f9bb08e134f:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
    7f9bb08e1356:	41 c7 87 90 0d 00 00 	movl   $0x1,0xd90(%r15)
    7f9bb08e135d:	01 00 00 00 
    7f9bb08e1361:	c7 85 78 ff ff ff 01 	movl   $0x1,-0x88(%rbp)
    7f9bb08e1368:	00 00 00 
    7f9bb08e136b:	e9 44 00 00 00       	jmpq   0x7f9bb08e13b4
    7f9bb08e1370:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7f9bb08e1376:	41 89 87 98 0d 00 00 	mov    %eax,0xd98(%r15)
    7f9bb08e137d:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f9bb08e1383:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7f9bb08e1389:	85 c0                	test   %eax,%eax
    7f9bb08e138b:	0f 84 23 00 00 00    	je     0x7f9bb08e13b4
    7f9bb08e1391:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7f9bb08e1397:	41 89 87 88 0d 00 00 	mov    %eax,0xd88(%r15)
    7f9bb08e139e:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f9bb08e13a1:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7f9bb08e13a7:	41 89 87 90 0d 00 00 	mov    %eax,0xd90(%r15)
    7f9bb08e13ae:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f9bb08e13b4:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f9bb08e13ba:	85 c0                	test   %eax,%eax
    7f9bb08e13bc:	0f 84 17 00 00 00    	je     0x7f9bb08e13d9
    7f9bb08e13c2:	41 c7 87 80 0d 00 00 	movl   $0x0,0xd80(%r15)
    7f9bb08e13c9:	00 00 00 00 
    7f9bb08e13cd:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
    7f9bb08e13d4:	e9 10 00 00 00       	jmpq   0x7f9bb08e13e9
    7f9bb08e13d9:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7f9bb08e13df:	41 89 87 80 0d 00 00 	mov    %eax,0xd80(%r15)
    7f9bb08e13e6:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f9bb08e13e9:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e13ec:	0f 84 3b 00 00 00    	je     0x7f9bb08e142d
    7f9bb08e13f2:	41 c7 87 78 0d 00 00 	movl   $0x0,0xd78(%r15)
    7f9bb08e13f9:	00 00 00 00 
    7f9bb08e13fd:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7f9bb08e1404:	41 c7 87 70 0d 00 00 	movl   $0x1,0xd70(%r15)
    7f9bb08e140b:	01 00 00 00 
    7f9bb08e140f:	c7 45 98 01 00 00 00 	movl   $0x1,-0x68(%rbp)
    7f9bb08e1416:	41 c7 87 68 0d 00 00 	movl   $0x0,0xd68(%r15)
    7f9bb08e141d:	00 00 00 00 
    7f9bb08e1421:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7f9bb08e1428:	e9 30 00 00 00       	jmpq   0x7f9bb08e145d
    7f9bb08e142d:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7f9bb08e1433:	41 89 87 78 0d 00 00 	mov    %eax,0xd78(%r15)
    7f9bb08e143a:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f9bb08e143d:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7f9bb08e1443:	41 89 87 70 0d 00 00 	mov    %eax,0xd70(%r15)
    7f9bb08e144a:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f9bb08e144d:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7f9bb08e1453:	41 89 87 68 0d 00 00 	mov    %eax,0xd68(%r15)
    7f9bb08e145a:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f9bb08e145d:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7f9bb08e1463:	85 c0                	test   %eax,%eax
    7f9bb08e1465:	0f 84 17 00 00 00    	je     0x7f9bb08e1482
    7f9bb08e146b:	41 c7 87 60 0d 00 00 	movl   $0x0,0xd60(%r15)
    7f9bb08e1472:	00 00 00 00 
    7f9bb08e1476:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
    7f9bb08e147d:	e9 10 00 00 00       	jmpq   0x7f9bb08e1492
    7f9bb08e1482:	8b 85 28 fd ff ff    	mov    -0x2d8(%rbp),%eax
    7f9bb08e1488:	41 89 87 60 0d 00 00 	mov    %eax,0xd60(%r15)
    7f9bb08e148f:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f9bb08e1492:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e1495:	0f 84 17 00 00 00    	je     0x7f9bb08e14b2
    7f9bb08e149b:	41 c7 87 58 0d 00 00 	movl   $0x0,0xd58(%r15)
    7f9bb08e14a2:	00 00 00 00 
    7f9bb08e14a6:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7f9bb08e14ad:	e9 10 00 00 00       	jmpq   0x7f9bb08e14c2
    7f9bb08e14b2:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7f9bb08e14b8:	41 89 87 58 0d 00 00 	mov    %eax,0xd58(%r15)
    7f9bb08e14bf:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f9bb08e14c2:	49 8b c7             	mov    %r15,%rax
    7f9bb08e14c5:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7f9bb08e14cb:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e14ce:	48 81 c1 88 10 00 00 	add    $0x1088,%rcx
    7f9bb08e14d5:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e14d8:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e14db:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e14df:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e14e3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e14e7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e14eb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e14ef:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e14f3:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e14f6:	0f 84 7d 00 00 00    	je     0x7f9bb08e1579
    7f9bb08e14fc:	41 c7 87 10 0d 00 00 	movl   $0x0,0xd10(%r15)
    7f9bb08e1503:	00 00 00 00 
    7f9bb08e1507:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7f9bb08e150e:	41 c7 87 08 0d 00 00 	movl   $0x0,0xd08(%r15)
    7f9bb08e1515:	00 00 00 00 
    7f9bb08e1519:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    7f9bb08e1520:	41 c7 87 00 0d 00 00 	movl   $0x0,0xd00(%r15)
    7f9bb08e1527:	00 00 00 00 
    7f9bb08e152b:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
    7f9bb08e1532:	41 c7 87 f8 0c 00 00 	movl   $0x0,0xcf8(%r15)
    7f9bb08e1539:	00 00 00 00 
    7f9bb08e153d:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7f9bb08e1544:	49 c7 87 f0 0c 00 00 	movq   $0x0,0xcf0(%r15)
    7f9bb08e154b:	00 00 00 00 
    7f9bb08e154f:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
    7f9bb08e1556:	00 
    7f9bb08e1557:	41 c7 87 e0 0c 00 00 	movl   $0x0,0xce0(%r15)
    7f9bb08e155e:	00 00 00 00 
    7f9bb08e1562:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
    7f9bb08e1569:	41 c7 87 e8 0c 00 00 	movl   $0x0,0xce8(%r15)
    7f9bb08e1570:	00 00 00 00 
    7f9bb08e1574:	e9 7e 00 00 00       	jmpq   0x7f9bb08e15f7
    7f9bb08e1579:	8b 85 50 fd ff ff    	mov    -0x2b0(%rbp),%eax
    7f9bb08e157f:	41 89 87 10 0d 00 00 	mov    %eax,0xd10(%r15)
    7f9bb08e1586:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f9bb08e1589:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7f9bb08e158f:	41 89 87 08 0d 00 00 	mov    %eax,0xd08(%r15)
    7f9bb08e1596:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f9bb08e1599:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7f9bb08e159f:	41 89 87 00 0d 00 00 	mov    %eax,0xd00(%r15)
    7f9bb08e15a6:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f9bb08e15a9:	8b 85 a0 fd ff ff    	mov    -0x260(%rbp),%eax
    7f9bb08e15af:	41 89 87 f8 0c 00 00 	mov    %eax,0xcf8(%r15)
    7f9bb08e15b6:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f9bb08e15b9:	48 8b 85 f0 fd ff ff 	mov    -0x210(%rbp),%rax
    7f9bb08e15c0:	49 89 87 f0 0c 00 00 	mov    %rax,0xcf0(%r15)
    7f9bb08e15c7:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    7f9bb08e15cb:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f9bb08e15d1:	85 c0                	test   %eax,%eax
    7f9bb08e15d3:	0f 84 1e 00 00 00    	je     0x7f9bb08e15f7
    7f9bb08e15d9:	41 8b 87 e8 0c 00 00 	mov    0xce8(%r15),%eax
    7f9bb08e15e0:	41 89 87 e0 0c 00 00 	mov    %eax,0xce0(%r15)
    7f9bb08e15e7:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f9bb08e15ea:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f9bb08e15f0:	41 89 87 e8 0c 00 00 	mov    %eax,0xce8(%r15)
    7f9bb08e15f7:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f9bb08e15fd:	85 c0                	test   %eax,%eax
    7f9bb08e15ff:	0f 84 1e 00 00 00    	je     0x7f9bb08e1623
    7f9bb08e1605:	41 8b 87 d8 0c 00 00 	mov    0xcd8(%r15),%eax
    7f9bb08e160c:	41 89 87 d0 0c 00 00 	mov    %eax,0xcd0(%r15)
    7f9bb08e1613:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f9bb08e1616:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7f9bb08e161c:	41 89 87 d8 0c 00 00 	mov    %eax,0xcd8(%r15)
    7f9bb08e1623:	45 85 e4             	test   %r12d,%r12d
    7f9bb08e1626:	0f 84 25 00 00 00    	je     0x7f9bb08e1651
    7f9bb08e162c:	41 c7 87 c8 0c 00 00 	movl   $0x0,0xcc8(%r15)
    7f9bb08e1633:	00 00 00 00 
    7f9bb08e1637:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7f9bb08e163e:	41 c7 87 c0 0c 00 00 	movl   $0x0,0xcc0(%r15)
    7f9bb08e1645:	00 00 00 00 
    7f9bb08e1649:	45 33 ed             	xor    %r13d,%r13d
    7f9bb08e164c:	e9 20 00 00 00       	jmpq   0x7f9bb08e1671
    7f9bb08e1651:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7f9bb08e1657:	41 89 87 c8 0c 00 00 	mov    %eax,0xcc8(%r15)
    7f9bb08e165e:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f9bb08e1661:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f9bb08e1667:	41 89 87 c0 0c 00 00 	mov    %eax,0xcc0(%r15)
    7f9bb08e166e:	4c 8b e8             	mov    %rax,%r13
    7f9bb08e1671:	45 85 ed             	test   %r13d,%r13d
    7f9bb08e1674:	0f 94 c0             	sete   %al
    7f9bb08e1677:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e167a:	49 8b 8e a0 00 00 00 	mov    0xa0(%r14),%rcx
    7f9bb08e1681:	89 01                	mov    %eax,(%rcx)
    7f9bb08e1683:	41 83 fd 02          	cmp    $0x2,%r13d
    7f9bb08e1687:	0f 94 c0             	sete   %al
    7f9bb08e168a:	0f b6 c0             	movzbl %al,%eax
    7f9bb08e168d:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7f9bb08e1693:	85 c9                	test   %ecx,%ecx
    7f9bb08e1695:	0f 94 c1             	sete   %cl
    7f9bb08e1698:	0f b6 c9             	movzbl %cl,%ecx
    7f9bb08e169b:	23 c1                	and    %ecx,%eax
    7f9bb08e169d:	49 8b 8e a8 00 00 00 	mov    0xa8(%r14),%rcx
    7f9bb08e16a4:	89 01                	mov    %eax,(%rcx)
    7f9bb08e16a6:	49 8b 86 b0 00 00 00 	mov    0xb0(%r14),%rax
    7f9bb08e16ad:	48 8b 8d f8 fe ff ff 	mov    -0x108(%rbp),%rcx
    7f9bb08e16b4:	48 89 08             	mov    %rcx,(%rax)
    7f9bb08e16b7:	49 8b 86 b8 00 00 00 	mov    0xb8(%r14),%rax
    7f9bb08e16be:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7f9bb08e16c4:	49 8b 86 c0 00 00 00 	mov    0xc0(%r14),%rax
    7f9bb08e16cb:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7f9bb08e16d1:	89 08                	mov    %ecx,(%rax)
    7f9bb08e16d3:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7f9bb08e16d9:	85 c0                	test   %eax,%eax
    7f9bb08e16db:	0f 85 36 00 00 00    	jne    0x7f9bb08e1717
    7f9bb08e16e1:	49 8b c7             	mov    %r15,%rax
    7f9bb08e16e4:	48 05 08 12 00 00    	add    $0x1208,%rax
    7f9bb08e16ea:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e16ed:	48 81 c1 48 10 00 00 	add    $0x1048,%rcx
    7f9bb08e16f4:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e16f7:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e16fa:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e16fe:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e1702:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e1706:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e170a:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e170e:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e1712:	e9 31 00 00 00       	jmpq   0x7f9bb08e1748
    7f9bb08e1717:	49 8b c7             	mov    %r15,%rax
    7f9bb08e171a:	48 05 08 12 00 00    	add    $0x1208,%rax
    7f9bb08e1720:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e1723:	48 81 c1 08 10 00 00 	add    $0x1008,%rcx
    7f9bb08e172a:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e172d:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e1730:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e1734:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e1738:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e173c:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e1740:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e1744:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e1748:	49 8b 86 c8 00 00 00 	mov    0xc8(%r14),%rax
    7f9bb08e174f:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e1752:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7f9bb08e1759:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e175c:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e175f:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e1763:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e1767:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e176b:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e176f:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e1773:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e1777:	49 8b 86 d0 00 00 00 	mov    0xd0(%r14),%rax
    7f9bb08e177e:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7f9bb08e1785:	49 8b 86 d8 00 00 00 	mov    0xd8(%r14),%rax
    7f9bb08e178c:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7f9bb08e1792:	89 08                	mov    %ecx,(%rax)
    7f9bb08e1794:	49 8b 86 e0 00 00 00 	mov    0xe0(%r14),%rax
    7f9bb08e179b:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
    7f9bb08e179f:	48 89 08             	mov    %rcx,(%rax)
    7f9bb08e17a2:	49 8b 86 e8 00 00 00 	mov    0xe8(%r14),%rax
    7f9bb08e17a9:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f9bb08e17ac:	89 08                	mov    %ecx,(%rax)
    7f9bb08e17ae:	49 8b 86 f0 00 00 00 	mov    0xf0(%r14),%rax
    7f9bb08e17b5:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7f9bb08e17bb:	49 8b 86 f8 00 00 00 	mov    0xf8(%r14),%rax
    7f9bb08e17c2:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e17c5:	48 81 c1 90 13 00 00 	add    $0x1390,%rcx
    7f9bb08e17cc:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e17cf:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e17d2:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e17d6:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e17da:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e17de:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e17e2:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e17e6:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e17ea:	49 8b 86 00 01 00 00 	mov    0x100(%r14),%rax
    7f9bb08e17f1:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7f9bb08e17f8:	49 8b 86 08 01 00 00 	mov    0x108(%r14),%rax
    7f9bb08e17ff:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f9bb08e1802:	89 08                	mov    %ecx,(%rax)
    7f9bb08e1804:	49 8b 86 10 01 00 00 	mov    0x110(%r14),%rax
    7f9bb08e180b:	48 8b 8d 68 ff ff ff 	mov    -0x98(%rbp),%rcx
    7f9bb08e1812:	48 89 08             	mov    %rcx,(%rax)
    7f9bb08e1815:	49 8b 86 18 01 00 00 	mov    0x118(%r14),%rax
    7f9bb08e181c:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7f9bb08e1822:	89 08                	mov    %ecx,(%rax)
    7f9bb08e1824:	49 8b 86 20 01 00 00 	mov    0x120(%r14),%rax
    7f9bb08e182b:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7f9bb08e1831:	49 8b 86 28 01 00 00 	mov    0x128(%r14),%rax
    7f9bb08e1838:	49 8b cf             	mov    %r15,%rcx
    7f9bb08e183b:	48 81 c1 90 13 00 00 	add    $0x1390,%rcx
    7f9bb08e1842:	0f 10 01             	movups (%rcx),%xmm0
    7f9bb08e1845:	0f 11 00             	movups %xmm0,(%rax)
    7f9bb08e1848:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f9bb08e184c:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f9bb08e1850:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f9bb08e1854:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f9bb08e1858:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7f9bb08e185c:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7f9bb08e1860:	49 8b 86 30 01 00 00 	mov    0x130(%r14),%rax
    7f9bb08e1867:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7f9bb08e186e:	49 8b 86 38 01 00 00 	mov    0x138(%r14),%rax
    7f9bb08e1875:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7f9bb08e187b:	89 08                	mov    %ecx,(%rax)
    7f9bb08e187d:	33 c0                	xor    %eax,%eax
    7f9bb08e187f:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f9bb08e1883:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f9bb08e1888:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f9bb08e188d:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f9bb08e1892:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f9bb08e1897:	48 8b e5             	mov    %rbp,%rsp
    7f9bb08e189a:	5d                   	pop    %rbp
    7f9bb08e189b:	c3                   	retq   

end

