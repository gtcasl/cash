function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f5fd9daf12d <.text>:
    7f5fd9daf12d:	55                   	push   %rbp
    7f5fd9daf12e:	48 8b ec             	mov    %rsp,%rbp
    7f5fd9daf131:	48 81 ec 00 03 00 00 	sub    $0x300,%rsp
    7f5fd9daf138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f5fd9daf13c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f5fd9daf141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f5fd9daf146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f5fd9daf14b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f5fd9daf150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f5fd9daf154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f5fd9daf158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f5fd9daf15c:	48 8b 18             	mov    (%rax),%rbx
    7f5fd9daf15f:	41 8b 07             	mov    (%r15),%eax
    7f5fd9daf162:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f5fd9daf165:	41 8b 47 4c          	mov    0x4c(%r15),%eax
    7f5fd9daf169:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f5fd9daf16c:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7f5fd9daf173:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f5fd9daf176:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7f5fd9daf17d:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7f5fd9daf180:	41 8b 87 a8 00 00 00 	mov    0xa8(%r15),%eax
    7f5fd9daf187:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f5fd9daf18a:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7f5fd9daf191:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f5fd9daf194:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7f5fd9daf19b:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f5fd9daf19e:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7f5fd9daf1a5:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f5fd9daf1a8:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7f5fd9daf1af:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f5fd9daf1b2:	41 8b 87 d0 00 00 00 	mov    0xd0(%r15),%eax
    7f5fd9daf1b9:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f5fd9daf1bc:	41 8b 87 d8 00 00 00 	mov    0xd8(%r15),%eax
    7f5fd9daf1c3:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f5fd9daf1c6:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7f5fd9daf1cd:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f5fd9daf1d0:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7f5fd9daf1d7:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f5fd9daf1da:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7f5fd9daf1e1:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f5fd9daf1e4:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7f5fd9daf1eb:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f5fd9daf1ee:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7f5fd9daf1f5:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f5fd9daf1fb:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7f5fd9daf202:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f5fd9daf208:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7f5fd9daf20f:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f5fd9daf215:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7f5fd9daf21c:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f5fd9daf222:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7f5fd9daf229:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f5fd9daf22f:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7f5fd9daf236:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f5fd9daf23c:	41 8b 87 30 01 00 00 	mov    0x130(%r15),%eax
    7f5fd9daf243:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f5fd9daf249:	41 8b 87 38 01 00 00 	mov    0x138(%r15),%eax
    7f5fd9daf250:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f5fd9daf256:	41 8b 87 40 01 00 00 	mov    0x140(%r15),%eax
    7f5fd9daf25d:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f5fd9daf263:	41 8b 87 48 01 00 00 	mov    0x148(%r15),%eax
    7f5fd9daf26a:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f5fd9daf270:	41 8b 87 50 01 00 00 	mov    0x150(%r15),%eax
    7f5fd9daf277:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f5fd9daf27d:	41 8b 87 58 01 00 00 	mov    0x158(%r15),%eax
    7f5fd9daf284:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f5fd9daf28a:	41 8b 87 60 01 00 00 	mov    0x160(%r15),%eax
    7f5fd9daf291:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f5fd9daf297:	45 8b a7 68 01 00 00 	mov    0x168(%r15),%r12d
    7f5fd9daf29e:	41 8b 87 70 01 00 00 	mov    0x170(%r15),%eax
    7f5fd9daf2a5:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f5fd9daf2ab:	45 8b b7 78 01 00 00 	mov    0x178(%r15),%r14d
    7f5fd9daf2b2:	41 8b 87 80 01 00 00 	mov    0x180(%r15),%eax
    7f5fd9daf2b9:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f5fd9daf2bf:	41 8b 87 88 01 00 00 	mov    0x188(%r15),%eax
    7f5fd9daf2c6:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f5fd9daf2cc:	45 8b af 90 01 00 00 	mov    0x190(%r15),%r13d
    7f5fd9daf2d3:	41 8b 87 98 01 00 00 	mov    0x198(%r15),%eax
    7f5fd9daf2da:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7f5fd9daf2e0:	41 8b 87 a0 01 00 00 	mov    0x1a0(%r15),%eax
    7f5fd9daf2e7:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f5fd9daf2ed:	48 8b 43 18          	mov    0x18(%rbx),%rax
    7f5fd9daf2f1:	8b 00                	mov    (%rax),%eax
    7f5fd9daf2f3:	41 8b 8f a8 01 00 00 	mov    0x1a8(%r15),%ecx
    7f5fd9daf2fa:	33 c8                	xor    %eax,%ecx
    7f5fd9daf2fc:	23 c8                	and    %eax,%ecx
    7f5fd9daf2fe:	41 89 87 a8 01 00 00 	mov    %eax,0x1a8(%r15)
    7f5fd9daf305:	85 c9                	test   %ecx,%ecx
    7f5fd9daf307:	0f 84 23 09 00 00    	je     0x7f5fd9dafc30
    7f5fd9daf30d:	41 81 fc 00 10 00 00 	cmp    $0x1000,%r12d
    7f5fd9daf314:	0f 92 c0             	setb   %al
    7f5fd9daf317:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf31a:	85 c0                	test   %eax,%eax
    7f5fd9daf31c:	0f 94 c0             	sete   %al
    7f5fd9daf31f:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf322:	85 c0                	test   %eax,%eax
    7f5fd9daf324:	0f 94 c0             	sete   %al
    7f5fd9daf327:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf32a:	41 8b ce             	mov    %r14d,%ecx
    7f5fd9daf32d:	83 e1 01             	and    $0x1,%ecx
    7f5fd9daf330:	85 c9                	test   %ecx,%ecx
    7f5fd9daf332:	0f 94 c1             	sete   %cl
    7f5fd9daf335:	0f b6 c9             	movzbl %cl,%ecx
    7f5fd9daf338:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7f5fd9daf33e:	85 c9                	test   %ecx,%ecx
    7f5fd9daf340:	0f 94 c1             	sete   %cl
    7f5fd9daf343:	0f b6 c9             	movzbl %cl,%ecx
    7f5fd9daf346:	23 c1                	and    %ecx,%eax
    7f5fd9daf348:	85 c0                	test   %eax,%eax
    7f5fd9daf34a:	0f 94 c0             	sete   %al
    7f5fd9daf34d:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf350:	41 81 fc 88 00 00 00 	cmp    $0x88,%r12d
    7f5fd9daf357:	0f 93 c1             	setae  %cl
    7f5fd9daf35a:	0f b6 c9             	movzbl %cl,%ecx
    7f5fd9daf35d:	8b 95 10 ff ff ff    	mov    -0xf0(%rbp),%edx
    7f5fd9daf363:	85 d2                	test   %edx,%edx
    7f5fd9daf365:	0f 94 c2             	sete   %dl
    7f5fd9daf368:	0f b6 d2             	movzbl %dl,%edx
    7f5fd9daf36b:	23 ca                	and    %edx,%ecx
    7f5fd9daf36d:	23 c8                	and    %eax,%ecx
    7f5fd9daf36f:	41 8b d5             	mov    %r13d,%edx
    7f5fd9daf372:	c1 ea 02             	shr    $0x2,%edx
    7f5fd9daf375:	83 e2 01             	and    $0x1,%edx
    7f5fd9daf378:	85 d2                	test   %edx,%edx
    7f5fd9daf37a:	0f 94 c2             	sete   %dl
    7f5fd9daf37d:	0f b6 d2             	movzbl %dl,%edx
    7f5fd9daf380:	89 95 e0 fe ff ff    	mov    %edx,-0x120(%rbp)
    7f5fd9daf386:	85 d2                	test   %edx,%edx
    7f5fd9daf388:	0f 94 c2             	sete   %dl
    7f5fd9daf38b:	0f b6 d2             	movzbl %dl,%edx
    7f5fd9daf38e:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7f5fd9daf394:	23 ca                	and    %edx,%ecx
    7f5fd9daf396:	85 c9                	test   %ecx,%ecx
    7f5fd9daf398:	0f 94 c1             	sete   %cl
    7f5fd9daf39b:	0f b6 c9             	movzbl %cl,%ecx
    7f5fd9daf39e:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7f5fd9daf3a4:	23 c1                	and    %ecx,%eax
    7f5fd9daf3a6:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f5fd9daf3ac:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f5fd9daf3af:	03 45 b0             	add    -0x50(%rbp),%eax
    7f5fd9daf3b2:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f5fd9daf3b7:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f5fd9daf3bd:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f5fd9daf3c0:	d1 e0                	shl    %eax
    7f5fd9daf3c2:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f5fd9daf3c8:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f5fd9daf3cb:	03 45 a0             	add    -0x60(%rbp),%eax
    7f5fd9daf3ce:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f5fd9daf3d3:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f5fd9daf3d9:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f5fd9daf3dc:	d1 e0                	shl    %eax
    7f5fd9daf3de:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f5fd9daf3e4:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f5fd9daf3e7:	03 45 90             	add    -0x70(%rbp),%eax
    7f5fd9daf3ea:	25 ff 03 00 00       	and    $0x3ff,%eax
    7f5fd9daf3ef:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f5fd9daf3f5:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f5fd9daf3f8:	03 45 80             	add    -0x80(%rbp),%eax
    7f5fd9daf3fb:	25 ff 03 00 00       	and    $0x3ff,%eax
    7f5fd9daf400:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f5fd9daf406:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f5fd9daf40c:	2b 85 78 ff ff ff    	sub    -0x88(%rbp),%eax
    7f5fd9daf412:	25 ff 07 00 00       	and    $0x7ff,%eax
    7f5fd9daf417:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f5fd9daf41d:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7f5fd9daf423:	c1 e8 0a             	shr    $0xa,%eax
    7f5fd9daf426:	83 e0 01             	and    $0x1,%eax
    7f5fd9daf429:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7f5fd9daf42f:	f7 d9                	neg    %ecx
    7f5fd9daf431:	81 e1 ff 07 00 00    	and    $0x7ff,%ecx
    7f5fd9daf437:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7f5fd9daf43d:	85 c0                	test   %eax,%eax
    7f5fd9daf43f:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf451
    7f5fd9daf445:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7f5fd9daf44b:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7f5fd9daf451:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f5fd9daf454:	03 45 d0             	add    -0x30(%rbp),%eax
    7f5fd9daf457:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f5fd9daf45c:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7f5fd9daf462:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f5fd9daf465:	d1 e0                	shl    %eax
    7f5fd9daf467:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7f5fd9daf46d:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f5fd9daf470:	03 45 a0             	add    -0x60(%rbp),%eax
    7f5fd9daf473:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f5fd9daf478:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7f5fd9daf47e:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f5fd9daf481:	d1 e0                	shl    %eax
    7f5fd9daf483:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f5fd9daf489:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f5fd9daf48f:	03 85 50 ff ff ff    	add    -0xb0(%rbp),%eax
    7f5fd9daf495:	25 ff 03 00 00       	and    $0x3ff,%eax
    7f5fd9daf49a:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7f5fd9daf4a0:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7f5fd9daf4a6:	03 85 40 ff ff ff    	add    -0xc0(%rbp),%eax
    7f5fd9daf4ac:	25 ff 03 00 00       	and    $0x3ff,%eax
    7f5fd9daf4b1:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7f5fd9daf4b7:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f5fd9daf4bd:	2b 85 38 ff ff ff    	sub    -0xc8(%rbp),%eax
    7f5fd9daf4c3:	25 ff 07 00 00       	and    $0x7ff,%eax
    7f5fd9daf4c8:	89 85 50 fe ff ff    	mov    %eax,-0x1b0(%rbp)
    7f5fd9daf4ce:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f5fd9daf4d4:	c1 e8 0a             	shr    $0xa,%eax
    7f5fd9daf4d7:	83 e0 01             	and    $0x1,%eax
    7f5fd9daf4da:	8b 8d 28 ff ff ff    	mov    -0xd8(%rbp),%ecx
    7f5fd9daf4e0:	f7 d9                	neg    %ecx
    7f5fd9daf4e2:	81 e1 ff 07 00 00    	and    $0x7ff,%ecx
    7f5fd9daf4e8:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7f5fd9daf4ee:	85 c0                	test   %eax,%eax
    7f5fd9daf4f0:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf502
    7f5fd9daf4f6:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f5fd9daf4fc:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7f5fd9daf502:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f5fd9daf508:	35 00 04 00 00       	xor    $0x400,%eax
    7f5fd9daf50d:	2d 00 04 00 00       	sub    $0x400,%eax
    7f5fd9daf512:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7f5fd9daf518:	81 f1 00 04 00 00    	xor    $0x400,%ecx
    7f5fd9daf51e:	81 e9 00 04 00 00    	sub    $0x400,%ecx
    7f5fd9daf524:	03 c1                	add    %ecx,%eax
    7f5fd9daf526:	25 ff 0f 00 00       	and    $0xfff,%eax
    7f5fd9daf52b:	89 85 40 fe ff ff    	mov    %eax,-0x1c0(%rbp)
    7f5fd9daf531:	41 81 fc fe ff ff ff 	cmp    $0xfffffffe,%r12d
    7f5fd9daf538:	0f 93 c0             	setae  %al
    7f5fd9daf53b:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf53e:	41 8b cc             	mov    %r12d,%ecx
    7f5fd9daf541:	81 e9 fe ff ff ff    	sub    $0xfffffffe,%ecx
    7f5fd9daf547:	89 8d 38 fe ff ff    	mov    %ecx,-0x1c8(%rbp)
    7f5fd9daf54d:	41 8b cc             	mov    %r12d,%ecx
    7f5fd9daf550:	ff c1                	inc    %ecx
    7f5fd9daf552:	89 8d 30 fe ff ff    	mov    %ecx,-0x1d0(%rbp)
    7f5fd9daf558:	85 c0                	test   %eax,%eax
    7f5fd9daf55a:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf56c
    7f5fd9daf560:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7f5fd9daf566:	89 85 38 fe ff ff    	mov    %eax,-0x1c8(%rbp)
    7f5fd9daf56c:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f5fd9daf572:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7f5fd9daf578:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f5fd9daf57e:	85 c0                	test   %eax,%eax
    7f5fd9daf580:	0f 85 09 00 00 00    	jne    0x7f5fd9daf58f
    7f5fd9daf586:	41 8b c4             	mov    %r12d,%eax
    7f5fd9daf589:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7f5fd9daf58f:	48 8b 43 20          	mov    0x20(%rbx),%rax
    7f5fd9daf593:	8b 00                	mov    (%rax),%eax
    7f5fd9daf595:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7f5fd9daf59b:	83 c8 00             	or     $0x0,%eax
    7f5fd9daf59e:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%rbp)
    7f5fd9daf5a4:	41 81 fc 05 10 00 00 	cmp    $0x1005,%r12d
    7f5fd9daf5ab:	0f 93 c0             	setae  %al
    7f5fd9daf5ae:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf5b1:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7f5fd9daf5b7:	48 8b 43 08          	mov    0x8(%rbx),%rax
    7f5fd9daf5bb:	8b 00                	mov    (%rax),%eax
    7f5fd9daf5bd:	41 8b ce             	mov    %r14d,%ecx
    7f5fd9daf5c0:	c1 e9 02             	shr    $0x2,%ecx
    7f5fd9daf5c3:	83 e1 01             	and    $0x1,%ecx
    7f5fd9daf5c6:	85 c9                	test   %ecx,%ecx
    7f5fd9daf5c8:	0f 94 c1             	sete   %cl
    7f5fd9daf5cb:	0f b6 c9             	movzbl %cl,%ecx
    7f5fd9daf5ce:	23 c1                	and    %ecx,%eax
    7f5fd9daf5d0:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7f5fd9daf5d6:	23 8d e8 fe ff ff    	and    -0x118(%rbp),%ecx
    7f5fd9daf5dc:	85 c9                	test   %ecx,%ecx
    7f5fd9daf5de:	0f 94 c2             	sete   %dl
    7f5fd9daf5e1:	0f b6 d2             	movzbl %dl,%edx
    7f5fd9daf5e4:	89 95 08 fe ff ff    	mov    %edx,-0x1f8(%rbp)
    7f5fd9daf5ea:	23 d0                	and    %eax,%edx
    7f5fd9daf5ec:	41 8b f6             	mov    %r14d,%esi
    7f5fd9daf5ef:	83 e6 03             	and    $0x3,%esi
    7f5fd9daf5f2:	d1 e6                	shl    %esi
    7f5fd9daf5f4:	89 b5 00 fe ff ff    	mov    %esi,-0x200(%rbp)
    7f5fd9daf5fa:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%rbp)
    7f5fd9daf600:	85 c0                	test   %eax,%eax
    7f5fd9daf602:	0f 94 c0             	sete   %al
    7f5fd9daf605:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf608:	89 8d f0 fd ff ff    	mov    %ecx,-0x210(%rbp)
    7f5fd9daf60e:	23 c8                	and    %eax,%ecx
    7f5fd9daf610:	89 8d e8 fd ff ff    	mov    %ecx,-0x218(%rbp)
    7f5fd9daf616:	41 8b c6             	mov    %r14d,%eax
    7f5fd9daf619:	d1 e8                	shr    %eax
    7f5fd9daf61b:	83 e0 03             	and    $0x3,%eax
    7f5fd9daf61e:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7f5fd9daf624:	85 d2                	test   %edx,%edx
    7f5fd9daf626:	0f 85 1c 00 00 00    	jne    0x7f5fd9daf648
    7f5fd9daf62c:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7f5fd9daf632:	85 c0                	test   %eax,%eax
    7f5fd9daf634:	0f 85 1f 00 00 00    	jne    0x7f5fd9daf659
    7f5fd9daf63a:	41 8b c6             	mov    %r14d,%eax
    7f5fd9daf63d:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7f5fd9daf643:	e9 1d 00 00 00       	jmpq   0x7f5fd9daf665
    7f5fd9daf648:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7f5fd9daf64e:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7f5fd9daf654:	e9 0c 00 00 00       	jmpq   0x7f5fd9daf665
    7f5fd9daf659:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7f5fd9daf65f:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7f5fd9daf665:	41 8b c6             	mov    %r14d,%eax
    7f5fd9daf668:	83 e0 01             	and    $0x1,%eax
    7f5fd9daf66b:	8b 8d f8 fd ff ff    	mov    -0x208(%rbp),%ecx
    7f5fd9daf671:	23 c1                	and    %ecx,%eax
    7f5fd9daf673:	8b 8d f0 fd ff ff    	mov    -0x210(%rbp),%ecx
    7f5fd9daf679:	0b c1                	or     %ecx,%eax
    7f5fd9daf67b:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7f5fd9daf681:	41 8b c6             	mov    %r14d,%eax
    7f5fd9daf684:	d1 e8                	shr    %eax
    7f5fd9daf686:	83 e0 01             	and    $0x1,%eax
    7f5fd9daf689:	89 85 c8 fd ff ff    	mov    %eax,-0x238(%rbp)
    7f5fd9daf68f:	8b 8d 08 fe ff ff    	mov    -0x1f8(%rbp),%ecx
    7f5fd9daf695:	0b c1                	or     %ecx,%eax
    7f5fd9daf697:	48 8b 0b             	mov    (%rbx),%rcx
    7f5fd9daf69a:	8b 09                	mov    (%rcx),%ecx
    7f5fd9daf69c:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7f5fd9daf6a2:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7f5fd9daf6a8:	85 c0                	test   %eax,%eax
    7f5fd9daf6aa:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf6bc
    7f5fd9daf6b0:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f5fd9daf6b6:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7f5fd9daf6bc:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7f5fd9daf6c2:	89 85 b0 fd ff ff    	mov    %eax,-0x250(%rbp)
    7f5fd9daf6c8:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7f5fd9daf6ce:	85 c0                	test   %eax,%eax
    7f5fd9daf6d0:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf6e2
    7f5fd9daf6d6:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f5fd9daf6dc:	89 85 b0 fd ff ff    	mov    %eax,-0x250(%rbp)
    7f5fd9daf6e2:	8b 85 f8 fd ff ff    	mov    -0x208(%rbp),%eax
    7f5fd9daf6e8:	23 85 c8 fd ff ff    	and    -0x238(%rbp),%eax
    7f5fd9daf6ee:	8b 8d f0 fd ff ff    	mov    -0x210(%rbp),%ecx
    7f5fd9daf6f4:	0b c1                	or     %ecx,%eax
    7f5fd9daf6f6:	8b 8d c0 fd ff ff    	mov    -0x240(%rbp),%ecx
    7f5fd9daf6fc:	89 8d a8 fd ff ff    	mov    %ecx,-0x258(%rbp)
    7f5fd9daf702:	85 c0                	test   %eax,%eax
    7f5fd9daf704:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf716
    7f5fd9daf70a:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f5fd9daf710:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7f5fd9daf716:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7f5fd9daf71c:	23 85 e0 fe ff ff    	and    -0x120(%rbp),%eax
    7f5fd9daf722:	48 8b 4b 10          	mov    0x10(%rbx),%rcx
    7f5fd9daf726:	8b 09                	mov    (%rcx),%ecx
    7f5fd9daf728:	41 8b d5             	mov    %r13d,%edx
    7f5fd9daf72b:	83 e2 01             	and    $0x1,%edx
    7f5fd9daf72e:	85 d2                	test   %edx,%edx
    7f5fd9daf730:	0f 94 c2             	sete   %dl
    7f5fd9daf733:	0f b6 d2             	movzbl %dl,%edx
    7f5fd9daf736:	23 ca                	and    %edx,%ecx
    7f5fd9daf738:	85 c9                	test   %ecx,%ecx
    7f5fd9daf73a:	0f 94 c2             	sete   %dl
    7f5fd9daf73d:	0f b6 d2             	movzbl %dl,%edx
    7f5fd9daf740:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7f5fd9daf746:	23 d0                	and    %eax,%edx
    7f5fd9daf748:	41 8b f5             	mov    %r13d,%esi
    7f5fd9daf74b:	83 e6 03             	and    $0x3,%esi
    7f5fd9daf74e:	d1 e6                	shl    %esi
    7f5fd9daf750:	89 b5 98 fd ff ff    	mov    %esi,-0x268(%rbp)
    7f5fd9daf756:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7f5fd9daf75c:	85 c0                	test   %eax,%eax
    7f5fd9daf75e:	0f 94 c0             	sete   %al
    7f5fd9daf761:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf764:	89 8d 88 fd ff ff    	mov    %ecx,-0x278(%rbp)
    7f5fd9daf76a:	23 c8                	and    %eax,%ecx
    7f5fd9daf76c:	89 8d 80 fd ff ff    	mov    %ecx,-0x280(%rbp)
    7f5fd9daf772:	41 8b c5             	mov    %r13d,%eax
    7f5fd9daf775:	d1 e8                	shr    %eax
    7f5fd9daf777:	83 e0 03             	and    $0x3,%eax
    7f5fd9daf77a:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7f5fd9daf780:	85 d2                	test   %edx,%edx
    7f5fd9daf782:	0f 85 1c 00 00 00    	jne    0x7f5fd9daf7a4
    7f5fd9daf788:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7f5fd9daf78e:	85 c0                	test   %eax,%eax
    7f5fd9daf790:	0f 85 1f 00 00 00    	jne    0x7f5fd9daf7b5
    7f5fd9daf796:	41 8b c5             	mov    %r13d,%eax
    7f5fd9daf799:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7f5fd9daf79f:	e9 1d 00 00 00       	jmpq   0x7f5fd9daf7c1
    7f5fd9daf7a4:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7f5fd9daf7aa:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7f5fd9daf7b0:	e9 0c 00 00 00       	jmpq   0x7f5fd9daf7c1
    7f5fd9daf7b5:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7f5fd9daf7bb:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7f5fd9daf7c1:	41 8b c5             	mov    %r13d,%eax
    7f5fd9daf7c4:	83 e0 01             	and    $0x1,%eax
    7f5fd9daf7c7:	8b 8d 90 fd ff ff    	mov    -0x270(%rbp),%ecx
    7f5fd9daf7cd:	23 c1                	and    %ecx,%eax
    7f5fd9daf7cf:	8b 8d 88 fd ff ff    	mov    -0x278(%rbp),%ecx
    7f5fd9daf7d5:	0b c1                	or     %ecx,%eax
    7f5fd9daf7d7:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7f5fd9daf7dd:	41 8b c5             	mov    %r13d,%eax
    7f5fd9daf7e0:	d1 e8                	shr    %eax
    7f5fd9daf7e2:	83 e0 01             	and    $0x1,%eax
    7f5fd9daf7e5:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7f5fd9daf7eb:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7f5fd9daf7f1:	0b c1                	or     %ecx,%eax
    7f5fd9daf7f3:	89 85 58 fd ff ff    	mov    %eax,-0x2a8(%rbp)
    7f5fd9daf7f9:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f5fd9daf7ff:	35 00 08 00 00       	xor    $0x800,%eax
    7f5fd9daf804:	2d 00 08 00 00       	sub    $0x800,%eax
    7f5fd9daf809:	3d ff 00 00 00       	cmp    $0xff,%eax
    7f5fd9daf80e:	0f 9c c0             	setl   %al
    7f5fd9daf811:	0f b6 c0             	movzbl %al,%eax
    7f5fd9daf814:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7f5fd9daf81a:	89 8d 50 fd ff ff    	mov    %ecx,-0x2b0(%rbp)
    7f5fd9daf820:	85 c0                	test   %eax,%eax
    7f5fd9daf822:	0f 85 0a 00 00 00    	jne    0x7f5fd9daf832
    7f5fd9daf828:	c7 85 50 fd ff ff ff 	movl   $0xff,-0x2b0(%rbp)
    7f5fd9daf82f:	00 00 00 
    7f5fd9daf832:	8b 85 50 fd ff ff    	mov    -0x2b0(%rbp),%eax
    7f5fd9daf838:	25 ff 00 00 00       	and    $0xff,%eax
    7f5fd9daf83d:	89 85 48 fd ff ff    	mov    %eax,-0x2b8(%rbp)
    7f5fd9daf843:	89 85 40 fd ff ff    	mov    %eax,-0x2c0(%rbp)
    7f5fd9daf849:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7f5fd9daf84f:	85 c0                	test   %eax,%eax
    7f5fd9daf851:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf863
    7f5fd9daf857:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f5fd9daf85d:	89 85 40 fd ff ff    	mov    %eax,-0x2c0(%rbp)
    7f5fd9daf863:	8b 85 40 fd ff ff    	mov    -0x2c0(%rbp),%eax
    7f5fd9daf869:	89 85 38 fd ff ff    	mov    %eax,-0x2c8(%rbp)
    7f5fd9daf86f:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7f5fd9daf875:	85 c0                	test   %eax,%eax
    7f5fd9daf877:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf889
    7f5fd9daf87d:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7f5fd9daf883:	89 85 38 fd ff ff    	mov    %eax,-0x2c8(%rbp)
    7f5fd9daf889:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7f5fd9daf88f:	23 85 60 fd ff ff    	and    -0x2a0(%rbp),%eax
    7f5fd9daf895:	8b 8d 88 fd ff ff    	mov    -0x278(%rbp),%ecx
    7f5fd9daf89b:	0b c1                	or     %ecx,%eax
    7f5fd9daf89d:	8b 8d 48 fd ff ff    	mov    -0x2b8(%rbp),%ecx
    7f5fd9daf8a3:	89 8d 30 fd ff ff    	mov    %ecx,-0x2d0(%rbp)
    7f5fd9daf8a9:	85 c0                	test   %eax,%eax
    7f5fd9daf8ab:	0f 85 0c 00 00 00    	jne    0x7f5fd9daf8bd
    7f5fd9daf8b1:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f5fd9daf8b7:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7f5fd9daf8bd:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7f5fd9daf8c3:	41 89 87 a0 01 00 00 	mov    %eax,0x1a0(%r15)
    7f5fd9daf8ca:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f5fd9daf8d0:	8b 85 38 fd ff ff    	mov    -0x2c8(%rbp),%eax
    7f5fd9daf8d6:	41 89 87 98 01 00 00 	mov    %eax,0x198(%r15)
    7f5fd9daf8dd:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7f5fd9daf8e3:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f5fd9daf8e9:	85 c0                	test   %eax,%eax
    7f5fd9daf8eb:	0f 84 16 00 00 00    	je     0x7f5fd9daf907
    7f5fd9daf8f1:	41 c7 87 90 01 00 00 	movl   $0x1,0x190(%r15)
    7f5fd9daf8f8:	01 00 00 00 
    7f5fd9daf8fc:	41 bd 01 00 00 00    	mov    $0x1,%r13d
    7f5fd9daf902:	e9 10 00 00 00       	jmpq   0x7f5fd9daf917
    7f5fd9daf907:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7f5fd9daf90d:	41 89 87 90 01 00 00 	mov    %eax,0x190(%r15)
    7f5fd9daf914:	4c 8b e8             	mov    %rax,%r13
    7f5fd9daf917:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7f5fd9daf91d:	41 89 87 88 01 00 00 	mov    %eax,0x188(%r15)
    7f5fd9daf924:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f5fd9daf92a:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f5fd9daf930:	85 c0                	test   %eax,%eax
    7f5fd9daf932:	0f 84 2b 00 00 00    	je     0x7f5fd9daf963
    7f5fd9daf938:	41 c7 87 78 01 00 00 	movl   $0x1,0x178(%r15)
    7f5fd9daf93f:	01 00 00 00 
    7f5fd9daf943:	41 be 01 00 00 00    	mov    $0x1,%r14d
    7f5fd9daf949:	41 c7 87 70 01 00 00 	movl   $0x0,0x170(%r15)
    7f5fd9daf950:	00 00 00 00 
    7f5fd9daf954:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7f5fd9daf95b:	00 00 00 
    7f5fd9daf95e:	e9 23 00 00 00       	jmpq   0x7f5fd9daf986
    7f5fd9daf963:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7f5fd9daf969:	41 89 87 78 01 00 00 	mov    %eax,0x178(%r15)
    7f5fd9daf970:	4c 8b f0             	mov    %rax,%r14
    7f5fd9daf973:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7f5fd9daf979:	41 89 87 70 01 00 00 	mov    %eax,0x170(%r15)
    7f5fd9daf980:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f5fd9daf986:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f5fd9daf98c:	85 c0                	test   %eax,%eax
    7f5fd9daf98e:	0f 84 13 00 00 00    	je     0x7f5fd9daf9a7
    7f5fd9daf994:	41 c7 87 68 01 00 00 	movl   $0x0,0x168(%r15)
    7f5fd9daf99b:	00 00 00 00 
    7f5fd9daf99f:	45 33 e4             	xor    %r12d,%r12d
    7f5fd9daf9a2:	e9 10 00 00 00       	jmpq   0x7f5fd9daf9b7
    7f5fd9daf9a7:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7f5fd9daf9ad:	41 89 87 68 01 00 00 	mov    %eax,0x168(%r15)
    7f5fd9daf9b4:	4c 8b e0             	mov    %rax,%r12
    7f5fd9daf9b7:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f5fd9daf9bd:	85 c0                	test   %eax,%eax
    7f5fd9daf9bf:	0f 84 15 02 00 00    	je     0x7f5fd9dafbda
    7f5fd9daf9c5:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7f5fd9daf9cb:	41 89 87 60 01 00 00 	mov    %eax,0x160(%r15)
    7f5fd9daf9d2:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f5fd9daf9d8:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f5fd9daf9de:	41 89 87 58 01 00 00 	mov    %eax,0x158(%r15)
    7f5fd9daf9e5:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f5fd9daf9eb:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7f5fd9daf9f1:	41 89 87 50 01 00 00 	mov    %eax,0x150(%r15)
    7f5fd9daf9f8:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f5fd9daf9fe:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f5fd9dafa04:	41 89 87 48 01 00 00 	mov    %eax,0x148(%r15)
    7f5fd9dafa0b:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f5fd9dafa11:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f5fd9dafa17:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7f5fd9dafa1e:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f5fd9dafa24:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f5fd9dafa2a:	41 89 87 38 01 00 00 	mov    %eax,0x138(%r15)
    7f5fd9dafa31:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f5fd9dafa37:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f5fd9dafa3d:	41 89 87 30 01 00 00 	mov    %eax,0x130(%r15)
    7f5fd9dafa44:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f5fd9dafa4a:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7f5fd9dafa50:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7f5fd9dafa57:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f5fd9dafa5d:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7f5fd9dafa63:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7f5fd9dafa6a:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f5fd9dafa70:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7f5fd9dafa76:	41 89 87 18 01 00 00 	mov    %eax,0x118(%r15)
    7f5fd9dafa7d:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f5fd9dafa83:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7f5fd9dafa89:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7f5fd9dafa90:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f5fd9dafa96:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f5fd9dafa9c:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7f5fd9dafaa3:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f5fd9dafaa9:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f5fd9dafaaf:	41 89 87 00 01 00 00 	mov    %eax,0x100(%r15)
    7f5fd9dafab6:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f5fd9dafabc:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f5fd9dafac2:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7f5fd9dafac9:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f5fd9dafacc:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f5fd9dafad2:	41 89 87 f0 00 00 00 	mov    %eax,0xf0(%r15)
    7f5fd9dafad9:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f5fd9dafadc:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7f5fd9dafae2:	41 89 87 e8 00 00 00 	mov    %eax,0xe8(%r15)
    7f5fd9dafae9:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f5fd9dafaec:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f5fd9dafaf2:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7f5fd9dafaf9:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f5fd9dafafc:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f5fd9dafaff:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7f5fd9dafb06:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f5fd9dafb09:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f5fd9dafb0c:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7f5fd9dafb13:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f5fd9dafb16:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7f5fd9dafb1c:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7f5fd9dafb23:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f5fd9dafb26:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f5fd9dafb29:	41 89 8f b0 00 00 00 	mov    %ecx,0xb0(%r15)
    7f5fd9dafb30:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7f5fd9dafb33:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f5fd9dafb36:	41 89 8f b8 00 00 00 	mov    %ecx,0xb8(%r15)
    7f5fd9dafb3d:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7f5fd9dafb40:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7f5fd9dafb43:	41 89 8f c0 00 00 00 	mov    %ecx,0xc0(%r15)
    7f5fd9dafb4a:	89 4d b8             	mov    %ecx,-0x48(%rbp)
    7f5fd9dafb4d:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7f5fd9dafb50:	41 89 97 98 00 00 00 	mov    %edx,0x98(%r15)
    7f5fd9dafb57:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7f5fd9dafb5a:	8b 55 d0             	mov    -0x30(%rbp),%edx
    7f5fd9dafb5d:	41 89 97 a0 00 00 00 	mov    %edx,0xa0(%r15)
    7f5fd9dafb64:	89 55 d8             	mov    %edx,-0x28(%rbp)
    7f5fd9dafb67:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f5fd9dafb6a:	41 89 97 a8 00 00 00 	mov    %edx,0xa8(%r15)
    7f5fd9dafb71:	89 55 d0             	mov    %edx,-0x30(%rbp)
    7f5fd9dafb74:	41 8b 97 94 00 00 00 	mov    0x94(%r15),%edx
    7f5fd9dafb7b:	49 8b f7             	mov    %r15,%rsi
    7f5fd9dafb7e:	48 83 c6 54          	add    $0x54,%rsi
    7f5fd9dafb82:	8b fa                	mov    %edx,%edi
    7f5fd9dafb84:	0f b6 3c 3e          	movzbl (%rsi,%rdi,1),%edi
    7f5fd9dafb88:	41 89 7f 4c          	mov    %edi,0x4c(%r15)
    7f5fd9dafb8c:	89 7d e8             	mov    %edi,-0x18(%rbp)
    7f5fd9dafb8f:	0f b6 c9             	movzbl %cl,%ecx
    7f5fd9dafb92:	8b fa                	mov    %edx,%edi
    7f5fd9dafb94:	40 88 0c 3e          	mov    %cl,(%rsi,%rdi,1)
    7f5fd9dafb98:	ff ca                	dec    %edx
    7f5fd9dafb9a:	b9 3e 00 00 00       	mov    $0x3e,%ecx
    7f5fd9dafb9f:	3b d1                	cmp    %ecx,%edx
    7f5fd9dafba1:	0f 47 d1             	cmova  %ecx,%edx
    7f5fd9dafba4:	41 89 97 94 00 00 00 	mov    %edx,0x94(%r15)
    7f5fd9dafbab:	41 8b 4f 48          	mov    0x48(%r15),%ecx
    7f5fd9dafbaf:	49 8b d7             	mov    %r15,%rdx
    7f5fd9dafbb2:	48 83 c2 08          	add    $0x8,%rdx
    7f5fd9dafbb6:	8b f1                	mov    %ecx,%esi
    7f5fd9dafbb8:	0f b6 34 32          	movzbl (%rdx,%rsi,1),%esi
    7f5fd9dafbbc:	41 89 37             	mov    %esi,(%r15)
    7f5fd9dafbbf:	89 75 f0             	mov    %esi,-0x10(%rbp)
    7f5fd9dafbc2:	0f b6 c0             	movzbl %al,%eax
    7f5fd9dafbc5:	8b f1                	mov    %ecx,%esi
    7f5fd9dafbc7:	88 04 32             	mov    %al,(%rdx,%rsi,1)
    7f5fd9dafbca:	ff c9                	dec    %ecx
    7f5fd9dafbcc:	b8 3e 00 00 00       	mov    $0x3e,%eax
    7f5fd9dafbd1:	3b c8                	cmp    %eax,%ecx
    7f5fd9dafbd3:	0f 47 c8             	cmova  %eax,%ecx
    7f5fd9dafbd6:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7f5fd9dafbda:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f5fd9dafbe0:	41 89 87 80 01 00 00 	mov    %eax,0x180(%r15)
    7f5fd9dafbe7:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f5fd9dafbed:	41 8b c6             	mov    %r14d,%eax
    7f5fd9dafbf0:	c1 e8 02             	shr    $0x2,%eax
    7f5fd9dafbf3:	83 e0 01             	and    $0x1,%eax
    7f5fd9dafbf6:	85 c0                	test   %eax,%eax
    7f5fd9dafbf8:	0f 94 c0             	sete   %al
    7f5fd9dafbfb:	0f b6 c0             	movzbl %al,%eax
    7f5fd9dafbfe:	48 8b 4b 28          	mov    0x28(%rbx),%rcx
    7f5fd9dafc02:	89 01                	mov    %eax,(%rcx)
    7f5fd9dafc04:	48 8b 43 30          	mov    0x30(%rbx),%rax
    7f5fd9dafc08:	8b 8d f8 fe ff ff    	mov    -0x108(%rbp),%ecx
    7f5fd9dafc0e:	89 08                	mov    %ecx,(%rax)
    7f5fd9dafc10:	41 8b c5             	mov    %r13d,%eax
    7f5fd9dafc13:	83 e0 01             	and    $0x1,%eax
    7f5fd9dafc16:	85 c0                	test   %eax,%eax
    7f5fd9dafc18:	0f 94 c0             	sete   %al
    7f5fd9dafc1b:	0f b6 c0             	movzbl %al,%eax
    7f5fd9dafc1e:	48 8b 4b 38          	mov    0x38(%rbx),%rcx
    7f5fd9dafc22:	89 01                	mov    %eax,(%rcx)
    7f5fd9dafc24:	48 8b 43 40          	mov    0x40(%rbx),%rax
    7f5fd9dafc28:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7f5fd9dafc2e:	89 08                	mov    %ecx,(%rax)
    7f5fd9dafc30:	33 c0                	xor    %eax,%eax
    7f5fd9dafc32:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f5fd9dafc36:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f5fd9dafc3b:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f5fd9dafc40:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f5fd9dafc45:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f5fd9dafc4a:	48 8b e5             	mov    %rbp,%rsp
    7f5fd9dafc4d:	5d                   	pop    %rbp
    7f5fd9dafc4e:	c3                   	retq   

end

