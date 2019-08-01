function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fb7657a412d <.text>:
    7fb7657a412d:	55                   	push   %rbp
    7fb7657a412e:	48 8b ec             	mov    %rsp,%rbp
    7fb7657a4131:	48 81 ec 40 06 00 00 	sub    $0x640,%rsp
    7fb7657a4138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fb7657a413c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fb7657a4141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fb7657a4146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fb7657a414b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fb7657a4150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fb7657a4154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fb7657a4158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fb7657a415c:	4c 8b 30             	mov    (%rax),%r14
    7fb7657a415f:	41 8b 87 c0 0c 00 00 	mov    0xcc0(%r15),%eax
    7fb7657a4166:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fb7657a4169:	41 8b 87 c8 0c 00 00 	mov    0xcc8(%r15),%eax
    7fb7657a4170:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fb7657a4173:	41 8b 87 d0 0c 00 00 	mov    0xcd0(%r15),%eax
    7fb7657a417a:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fb7657a417d:	41 8b 87 e0 0c 00 00 	mov    0xce0(%r15),%eax
    7fb7657a4184:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fb7657a4187:	49 8b 87 f0 0c 00 00 	mov    0xcf0(%r15),%rax
    7fb7657a418e:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    7fb7657a4192:	41 8b 87 f8 0c 00 00 	mov    0xcf8(%r15),%eax
    7fb7657a4199:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fb7657a419c:	41 8b 87 00 0d 00 00 	mov    0xd00(%r15),%eax
    7fb7657a41a3:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fb7657a41a6:	41 8b 87 08 0d 00 00 	mov    0xd08(%r15),%eax
    7fb7657a41ad:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fb7657a41b0:	41 8b 87 10 0d 00 00 	mov    0xd10(%r15),%eax
    7fb7657a41b7:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fb7657a41ba:	41 8b 87 58 0d 00 00 	mov    0xd58(%r15),%eax
    7fb7657a41c1:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fb7657a41c4:	41 8b 87 60 0d 00 00 	mov    0xd60(%r15),%eax
    7fb7657a41cb:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fb7657a41ce:	41 8b 87 68 0d 00 00 	mov    0xd68(%r15),%eax
    7fb7657a41d5:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fb7657a41d8:	41 8b 87 70 0d 00 00 	mov    0xd70(%r15),%eax
    7fb7657a41df:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fb7657a41e2:	41 8b 87 78 0d 00 00 	mov    0xd78(%r15),%eax
    7fb7657a41e9:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fb7657a41ec:	41 8b 87 80 0d 00 00 	mov    0xd80(%r15),%eax
    7fb7657a41f3:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fb7657a41f6:	41 8b 87 88 0d 00 00 	mov    0xd88(%r15),%eax
    7fb7657a41fd:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fb7657a4203:	41 8b 87 90 0d 00 00 	mov    0xd90(%r15),%eax
    7fb7657a420a:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fb7657a4210:	41 8b 87 98 0d 00 00 	mov    0xd98(%r15),%eax
    7fb7657a4217:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fb7657a421d:	49 8b 87 20 0e 00 00 	mov    0xe20(%r15),%rax
    7fb7657a4224:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
    7fb7657a422b:	41 8b 87 28 0e 00 00 	mov    0xe28(%r15),%eax
    7fb7657a4232:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fb7657a4238:	41 8b 87 30 0e 00 00 	mov    0xe30(%r15),%eax
    7fb7657a423f:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7fb7657a4245:	41 8b 87 38 0e 00 00 	mov    0xe38(%r15),%eax
    7fb7657a424c:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fb7657a4252:	41 8b 87 40 0e 00 00 	mov    0xe40(%r15),%eax
    7fb7657a4259:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fb7657a425f:	41 8b 87 88 0e 00 00 	mov    0xe88(%r15),%eax
    7fb7657a4266:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fb7657a426c:	41 8b 87 90 0e 00 00 	mov    0xe90(%r15),%eax
    7fb7657a4273:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fb7657a4279:	41 8b 87 98 0e 00 00 	mov    0xe98(%r15),%eax
    7fb7657a4280:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fb7657a4286:	41 8b 87 a0 0e 00 00 	mov    0xea0(%r15),%eax
    7fb7657a428d:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fb7657a4293:	41 8b 87 a8 0e 00 00 	mov    0xea8(%r15),%eax
    7fb7657a429a:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fb7657a42a0:	41 8b 87 b0 0e 00 00 	mov    0xeb0(%r15),%eax
    7fb7657a42a7:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fb7657a42ad:	41 8b 87 b8 0e 00 00 	mov    0xeb8(%r15),%eax
    7fb7657a42b4:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fb7657a42ba:	41 8b 87 c0 0e 00 00 	mov    0xec0(%r15),%eax
    7fb7657a42c1:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fb7657a42c7:	41 8b 87 c8 0e 00 00 	mov    0xec8(%r15),%eax
    7fb7657a42ce:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fb7657a42d4:	49 8b 87 50 0f 00 00 	mov    0xf50(%r15),%rax
    7fb7657a42db:	48 89 85 f0 fe ff ff 	mov    %rax,-0x110(%rbp)
    7fb7657a42e2:	41 8b 87 58 0f 00 00 	mov    0xf58(%r15),%eax
    7fb7657a42e9:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fb7657a42ef:	41 8b 87 60 0f 00 00 	mov    0xf60(%r15),%eax
    7fb7657a42f6:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fb7657a42fc:	41 8b 87 68 0f 00 00 	mov    0xf68(%r15),%eax
    7fb7657a4303:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fb7657a4309:	41 8b 87 70 0f 00 00 	mov    0xf70(%r15),%eax
    7fb7657a4310:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fb7657a4316:	41 8b 87 b8 0f 00 00 	mov    0xfb8(%r15),%eax
    7fb7657a431d:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fb7657a4323:	41 8b 87 c0 0f 00 00 	mov    0xfc0(%r15),%eax
    7fb7657a432a:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fb7657a4330:	41 8b 87 c8 0f 00 00 	mov    0xfc8(%r15),%eax
    7fb7657a4337:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fb7657a433d:	45 8b a7 d0 0f 00 00 	mov    0xfd0(%r15),%r12d
    7fb7657a4344:	41 8b 87 d8 0f 00 00 	mov    0xfd8(%r15),%eax
    7fb7657a434b:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fb7657a4351:	41 8b 87 e0 0f 00 00 	mov    0xfe0(%r15),%eax
    7fb7657a4358:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fb7657a435e:	41 8b 87 e8 0f 00 00 	mov    0xfe8(%r15),%eax
    7fb7657a4365:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fb7657a436b:	41 8b 87 f0 0f 00 00 	mov    0xff0(%r15),%eax
    7fb7657a4372:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fb7657a4378:	41 8b 87 f8 0f 00 00 	mov    0xff8(%r15),%eax
    7fb7657a437f:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fb7657a4385:	41 8b 87 00 10 00 00 	mov    0x1000(%r15),%eax
    7fb7657a438c:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fb7657a4392:	49 8b 86 90 00 00 00 	mov    0x90(%r14),%rax
    7fb7657a4399:	8b 00                	mov    (%rax),%eax
    7fb7657a439b:	41 8b 8f 48 13 00 00 	mov    0x1348(%r15),%ecx
    7fb7657a43a2:	33 c8                	xor    %eax,%ecx
    7fb7657a43a4:	23 c8                	and    %eax,%ecx
    7fb7657a43a6:	41 89 87 48 13 00 00 	mov    %eax,0x1348(%r15)
    7fb7657a43ad:	85 c9                	test   %ecx,%ecx
    7fb7657a43af:	0f 84 43 22 00 00    	je     0x7fb7657a65f8
    7fb7657a43b5:	49 8b 46 20          	mov    0x20(%r14),%rax
    7fb7657a43b9:	8b 00                	mov    (%rax),%eax
    7fb7657a43bb:	c7 85 80 fe ff ff 01 	movl   $0x1,-0x180(%rbp)
    7fb7657a43c2:	00 00 00 
    7fb7657a43c5:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fb7657a43cb:	85 c0                	test   %eax,%eax
    7fb7657a43cd:	0f 85 09 00 00 00    	jne    0x7fb7657a43dc
    7fb7657a43d3:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a43d6:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fb7657a43dc:	33 c0                	xor    %eax,%eax
    7fb7657a43de:	3b 45 e8             	cmp    -0x18(%rbp),%eax
    7fb7657a43e1:	0f 94 c0             	sete   %al
    7fb7657a43e4:	0f b6 c0             	movzbl %al,%eax
    7fb7657a43e7:	c7 85 70 fe ff ff 02 	movl   $0x2,-0x190(%rbp)
    7fb7657a43ee:	00 00 00 
    7fb7657a43f1:	85 c0                	test   %eax,%eax
    7fb7657a43f3:	0f 85 09 00 00 00    	jne    0x7fb7657a4402
    7fb7657a43f9:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a43fc:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fb7657a4402:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fb7657a4408:	85 c0                	test   %eax,%eax
    7fb7657a440a:	0f 94 c0             	sete   %al
    7fb7657a440d:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4410:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7fb7657a4414:	8b 09                	mov    (%rcx),%ecx
    7fb7657a4416:	23 c1                	and    %ecx,%eax
    7fb7657a4418:	c7 85 68 fe ff ff 00 	movl   $0x0,-0x198(%rbp)
    7fb7657a441f:	00 00 00 
    7fb7657a4422:	85 c0                	test   %eax,%eax
    7fb7657a4424:	0f 85 09 00 00 00    	jne    0x7fb7657a4433
    7fb7657a442a:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a442d:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7fb7657a4433:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a4436:	85 c0                	test   %eax,%eax
    7fb7657a4438:	0f 84 26 00 00 00    	je     0x7fb7657a4464
    7fb7657a443e:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a4441:	83 f8 01             	cmp    $0x1,%eax
    7fb7657a4444:	0f 84 2b 00 00 00    	je     0x7fb7657a4475
    7fb7657a444a:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a444d:	83 f8 02             	cmp    $0x2,%eax
    7fb7657a4450:	0f 84 30 00 00 00    	je     0x7fb7657a4486
    7fb7657a4456:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a4459:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fb7657a445f:	e9 2e 00 00 00       	jmpq   0x7fb7657a4492
    7fb7657a4464:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fb7657a446a:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fb7657a4470:	e9 1d 00 00 00       	jmpq   0x7fb7657a4492
    7fb7657a4475:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fb7657a447b:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fb7657a4481:	e9 0c 00 00 00       	jmpq   0x7fb7657a4492
    7fb7657a4486:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fb7657a448c:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fb7657a4492:	49 8b 86 98 00 00 00 	mov    0x98(%r14),%rax
    7fb7657a4499:	44 8b 28             	mov    (%rax),%r13d
    7fb7657a449c:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a449f:	85 c0                	test   %eax,%eax
    7fb7657a44a1:	0f 94 c0             	sete   %al
    7fb7657a44a4:	0f b6 c0             	movzbl %al,%eax
    7fb7657a44a7:	8b 8d 78 fe ff ff    	mov    -0x188(%rbp),%ecx
    7fb7657a44ad:	23 c1                	and    %ecx,%eax
    7fb7657a44af:	49 8b 4e 18          	mov    0x18(%r14),%rcx
    7fb7657a44b3:	8b 09                	mov    (%rcx),%ecx
    7fb7657a44b5:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7fb7657a44bb:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7fb7657a44c1:	85 c9                	test   %ecx,%ecx
    7fb7657a44c3:	0f 94 c1             	sete   %cl
    7fb7657a44c6:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a44c9:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7fb7657a44cf:	85 d2                	test   %edx,%edx
    7fb7657a44d1:	0f 94 c2             	sete   %dl
    7fb7657a44d4:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a44d7:	89 95 50 fe ff ff    	mov    %edx,-0x1b0(%rbp)
    7fb7657a44dd:	0b ca                	or     %edx,%ecx
    7fb7657a44df:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7fb7657a44e5:	23 4d d8             	and    -0x28(%rbp),%ecx
    7fb7657a44e8:	89 8d 40 fe ff ff    	mov    %ecx,-0x1c0(%rbp)
    7fb7657a44ee:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7fb7657a44f1:	ff c9                	dec    %ecx
    7fb7657a44f3:	89 8d 38 fe ff ff    	mov    %ecx,-0x1c8(%rbp)
    7fb7657a44f9:	48 8b d8             	mov    %rax,%rbx
    7fb7657a44fc:	85 c0                	test   %eax,%eax
    7fb7657a44fe:	0f 85 1c 00 00 00    	jne    0x7fb7657a4520
    7fb7657a4504:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fb7657a450a:	85 c0                	test   %eax,%eax
    7fb7657a450c:	0f 85 1f 00 00 00    	jne    0x7fb7657a4531
    7fb7657a4512:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7fb7657a4515:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fb7657a451b:	e9 1d 00 00 00       	jmpq   0x7fb7657a453d
    7fb7657a4520:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fb7657a4526:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fb7657a452c:	e9 0c 00 00 00       	jmpq   0x7fb7657a453d
    7fb7657a4531:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7fb7657a4537:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fb7657a453d:	41 8b 87 18 0d 00 00 	mov    0xd18(%r15),%eax
    7fb7657a4544:	41 8b 8f 48 0e 00 00 	mov    0xe48(%r15),%ecx
    7fb7657a454b:	03 c1                	add    %ecx,%eax
    7fb7657a454d:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7fb7657a4553:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fb7657a4556:	85 c0                	test   %eax,%eax
    7fb7657a4558:	0f 94 c0             	sete   %al
    7fb7657a455b:	0f b6 c0             	movzbl %al,%eax
    7fb7657a455e:	8b 8d 48 fe ff ff    	mov    -0x1b8(%rbp),%ecx
    7fb7657a4564:	0b c1                	or     %ecx,%eax
    7fb7657a4566:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7fb7657a456c:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fb7657a456f:	23 85 38 ff ff ff    	and    -0xc8(%rbp),%eax
    7fb7657a4575:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%rbp)
    7fb7657a457b:	49 8b 46 08          	mov    0x8(%r14),%rax
    7fb7657a457f:	48 8b 00             	mov    (%rax),%rax
    7fb7657a4582:	48 89 85 10 fe ff ff 	mov    %rax,-0x1f0(%rbp)
    7fb7657a4589:	49 8b 46 60          	mov    0x60(%r14),%rax
    7fb7657a458d:	8b 00                	mov    (%rax),%eax
    7fb7657a458f:	85 c0                	test   %eax,%eax
    7fb7657a4591:	0f 94 c0             	sete   %al
    7fb7657a4594:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4597:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fb7657a459a:	23 c1                	and    %ecx,%eax
    7fb7657a459c:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7fb7657a45a2:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fb7657a45a5:	8b c0                	mov    %eax,%eax
    7fb7657a45a7:	48 c1 e0 06          	shl    $0x6,%rax
    7fb7657a45ab:	48 89 85 00 fe ff ff 	mov    %rax,-0x200(%rbp)
    7fb7657a45b2:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
    7fb7657a45b6:	48 03 c1             	add    %rcx,%rax
    7fb7657a45b9:	48 89 85 f8 fd ff ff 	mov    %rax,-0x208(%rbp)
    7fb7657a45c0:	85 db                	test   %ebx,%ebx
    7fb7657a45c2:	0f 85 1e 00 00 00    	jne    0x7fb7657a45e6
    7fb7657a45c8:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fb7657a45ce:	85 c0                	test   %eax,%eax
    7fb7657a45d0:	0f 85 23 00 00 00    	jne    0x7fb7657a45f9
    7fb7657a45d6:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    7fb7657a45da:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7fb7657a45e1:	e9 21 00 00 00       	jmpq   0x7fb7657a4607
    7fb7657a45e6:	48 8b 85 10 fe ff ff 	mov    -0x1f0(%rbp),%rax
    7fb7657a45ed:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7fb7657a45f4:	e9 0e 00 00 00       	jmpq   0x7fb7657a4607
    7fb7657a45f9:	48 8b 85 f8 fd ff ff 	mov    -0x208(%rbp),%rax
    7fb7657a4600:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7fb7657a4607:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fb7657a460a:	85 c0                	test   %eax,%eax
    7fb7657a460c:	0f 94 c0             	sete   %al
    7fb7657a460f:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4612:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7fb7657a4615:	85 d2                	test   %edx,%edx
    7fb7657a4617:	0f 94 c1             	sete   %cl
    7fb7657a461a:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a461d:	8b 75 a0             	mov    -0x60(%rbp),%esi
    7fb7657a4620:	83 fe 0f             	cmp    $0xf,%esi
    7fb7657a4623:	40 0f 94 c6          	sete   %sil
    7fb7657a4627:	40 0f b6 f6          	movzbl %sil,%esi
    7fb7657a462b:	8b bd 38 ff ff ff    	mov    -0xc8(%rbp),%edi
    7fb7657a4631:	85 ff                	test   %edi,%edi
    7fb7657a4633:	40 0f 94 c7          	sete   %dil
    7fb7657a4637:	40 0f b6 ff          	movzbl %dil,%edi
    7fb7657a463b:	23 d7                	and    %edi,%edx
    7fb7657a463d:	85 d2                	test   %edx,%edx
    7fb7657a463f:	0f 94 c2             	sete   %dl
    7fb7657a4642:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a4645:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7fb7657a464b:	23 d7                	and    %edi,%edx
    7fb7657a464d:	89 95 e8 fd ff ff    	mov    %edx,-0x218(%rbp)
    7fb7657a4653:	23 f2                	and    %edx,%esi
    7fb7657a4655:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fb7657a465b:	89 b5 d8 fd ff ff    	mov    %esi,-0x228(%rbp)
    7fb7657a4661:	0b ce                	or     %esi,%ecx
    7fb7657a4663:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7fb7657a4669:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7fb7657a466f:	23 c1                	and    %ecx,%eax
    7fb7657a4671:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7fb7657a4674:	03 4d b0             	add    -0x50(%rbp),%ecx
    7fb7657a4677:	83 e1 1f             	and    $0x1f,%ecx
    7fb7657a467a:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7fb7657a4680:	ff c9                	dec    %ecx
    7fb7657a4682:	83 e1 1f             	and    $0x1f,%ecx
    7fb7657a4685:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7fb7657a468b:	89 85 b0 fd ff ff    	mov    %eax,-0x250(%rbp)
    7fb7657a4691:	85 c0                	test   %eax,%eax
    7fb7657a4693:	0f 85 0c 00 00 00    	jne    0x7fb7657a46a5
    7fb7657a4699:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fb7657a469f:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7fb7657a46a5:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7fb7657a46a8:	ff c8                	dec    %eax
    7fb7657a46aa:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a46ad:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7fb7657a46b3:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fb7657a46b9:	85 c0                	test   %eax,%eax
    7fb7657a46bb:	0f 85 09 00 00 00    	jne    0x7fb7657a46ca
    7fb7657a46c1:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7fb7657a46c4:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7fb7657a46ca:	85 db                	test   %ebx,%ebx
    7fb7657a46cc:	0f 85 1f 00 00 00    	jne    0x7fb7657a46f1
    7fb7657a46d2:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fb7657a46d8:	85 c0                	test   %eax,%eax
    7fb7657a46da:	0f 85 20 00 00 00    	jne    0x7fb7657a4700
    7fb7657a46e0:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7fb7657a46e6:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7fb7657a46ec:	e9 1b 00 00 00       	jmpq   0x7fb7657a470c
    7fb7657a46f1:	c7 85 a0 fd ff ff 00 	movl   $0x0,-0x260(%rbp)
    7fb7657a46f8:	00 00 00 
    7fb7657a46fb:	e9 0c 00 00 00       	jmpq   0x7fb7657a470c
    7fb7657a4700:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7fb7657a4706:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7fb7657a470c:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fb7657a4712:	c1 e0 05             	shl    $0x5,%eax
    7fb7657a4715:	05 ff 01 00 00       	add    $0x1ff,%eax
    7fb7657a471a:	c1 e8 09             	shr    $0x9,%eax
    7fb7657a471d:	89 85 98 fd ff ff    	mov    %eax,-0x268(%rbp)
    7fb7657a4723:	83 c0 10             	add    $0x10,%eax
    7fb7657a4726:	ff c8                	dec    %eax
    7fb7657a4728:	c1 e8 04             	shr    $0x4,%eax
    7fb7657a472b:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7fb7657a4731:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fb7657a4734:	ff c8                	dec    %eax
    7fb7657a4736:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7fb7657a473b:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7fb7657a4741:	85 db                	test   %ebx,%ebx
    7fb7657a4743:	0f 85 1c 00 00 00    	jne    0x7fb7657a4765
    7fb7657a4749:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fb7657a474f:	85 c0                	test   %eax,%eax
    7fb7657a4751:	0f 85 1f 00 00 00    	jne    0x7fb7657a4776
    7fb7657a4757:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fb7657a475a:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fb7657a4760:	e9 1d 00 00 00       	jmpq   0x7fb7657a4782
    7fb7657a4765:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7fb7657a476b:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fb7657a4771:	e9 0c 00 00 00       	jmpq   0x7fb7657a4782
    7fb7657a4776:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7fb7657a477c:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fb7657a4782:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7fb7657a4788:	85 c0                	test   %eax,%eax
    7fb7657a478a:	0f 95 c0             	setne  %al
    7fb7657a478d:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4790:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7fb7657a4796:	b8 01 00 00 00       	mov    $0x1,%eax
    7fb7657a479b:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fb7657a479e:	3b c1                	cmp    %ecx,%eax
    7fb7657a47a0:	0f 94 c0             	sete   %al
    7fb7657a47a3:	0f b6 c0             	movzbl %al,%eax
    7fb7657a47a6:	8b 95 08 fe ff ff    	mov    -0x1f8(%rbp),%edx
    7fb7657a47ac:	23 c2                	and    %edx,%eax
    7fb7657a47ae:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7fb7657a47b4:	85 c9                	test   %ecx,%ecx
    7fb7657a47b6:	0f 95 c1             	setne  %cl
    7fb7657a47b9:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a47bc:	8b c1                	mov    %ecx,%eax
    7fb7657a47be:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fb7657a47c4:	83 f9 00             	cmp    $0x0,%ecx
    7fb7657a47c7:	0f 96 c1             	setbe  %cl
    7fb7657a47ca:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a47cd:	23 c1                	and    %ecx,%eax
    7fb7657a47cf:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7fb7657a47d5:	85 db                	test   %ebx,%ebx
    7fb7657a47d7:	0f 85 1f 00 00 00    	jne    0x7fb7657a47fc
    7fb7657a47dd:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fb7657a47e3:	85 c0                	test   %eax,%eax
    7fb7657a47e5:	0f 85 22 00 00 00    	jne    0x7fb7657a480d
    7fb7657a47eb:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7fb7657a47f1:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7fb7657a47f7:	e9 1b 00 00 00       	jmpq   0x7fb7657a4817
    7fb7657a47fc:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fb7657a4802:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7fb7657a4808:	e9 0a 00 00 00       	jmpq   0x7fb7657a4817
    7fb7657a480d:	c7 85 60 fd ff ff 00 	movl   $0x0,-0x2a0(%rbp)
    7fb7657a4814:	00 00 00 
    7fb7657a4817:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7fb7657a481d:	ff c8                	dec    %eax
    7fb7657a481f:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a4822:	83 e0 0f             	and    $0xf,%eax
    7fb7657a4825:	ff c0                	inc    %eax
    7fb7657a4827:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a482a:	89 85 58 fd ff ff    	mov    %eax,-0x2a8(%rbp)
    7fb7657a4830:	85 db                	test   %ebx,%ebx
    7fb7657a4832:	0f 85 1c 00 00 00    	jne    0x7fb7657a4854
    7fb7657a4838:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fb7657a483e:	85 c0                	test   %eax,%eax
    7fb7657a4840:	0f 85 1f 00 00 00    	jne    0x7fb7657a4865
    7fb7657a4846:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fb7657a4849:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7fb7657a484f:	e9 1b 00 00 00       	jmpq   0x7fb7657a486f
    7fb7657a4854:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7fb7657a485a:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7fb7657a4860:	e9 0a 00 00 00       	jmpq   0x7fb7657a486f
    7fb7657a4865:	c7 85 50 fd ff ff 10 	movl   $0x10,-0x2b0(%rbp)
    7fb7657a486c:	00 00 00 
    7fb7657a486f:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fb7657a4875:	85 c0                	test   %eax,%eax
    7fb7657a4877:	0f 85 36 00 00 00    	jne    0x7fb7657a48b3
    7fb7657a487d:	49 8b c7             	mov    %r15,%rax
    7fb7657a4880:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7fb7657a4886:	49 8b cf             	mov    %r15,%rcx
    7fb7657a4889:	48 81 c1 e0 0d 00 00 	add    $0xde0,%rcx
    7fb7657a4890:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a4893:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a4896:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a489a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a489e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a48a2:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a48a6:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a48aa:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a48ae:	e9 31 00 00 00       	jmpq   0x7fb7657a48e4
    7fb7657a48b3:	49 8b c7             	mov    %r15,%rax
    7fb7657a48b6:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7fb7657a48bc:	49 8b cf             	mov    %r15,%rcx
    7fb7657a48bf:	48 81 c1 a0 0d 00 00 	add    $0xda0,%rcx
    7fb7657a48c6:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a48c9:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a48cc:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a48d0:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a48d4:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a48d8:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a48dc:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a48e0:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a48e4:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fb7657a48e7:	23 85 e8 fd ff ff    	and    -0x218(%rbp),%eax
    7fb7657a48ed:	89 85 48 fd ff ff    	mov    %eax,-0x2b8(%rbp)
    7fb7657a48f3:	49 8b c7             	mov    %r15,%rax
    7fb7657a48f6:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7fb7657a48fc:	49 8b cf             	mov    %r15,%rcx
    7fb7657a48ff:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7fb7657a4906:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7fb7657a490c:	48 89 8d 40 fd ff ff 	mov    %rcx,-0x2c0(%rbp)
    7fb7657a4913:	b9 00 02 00 00       	mov    $0x200,%ecx
    7fb7657a4918:	48 8b d0             	mov    %rax,%rdx
    7fb7657a491b:	be 00 02 00 00       	mov    $0x200,%esi
    7fb7657a4920:	48 8b bd 40 fd ff ff 	mov    -0x2c0(%rbp),%rdi
    7fb7657a4927:	48 89 85 38 fd ff ff 	mov    %rax,-0x2c8(%rbp)
    7fb7657a492e:	b8 08 00 00 00       	mov    $0x8,%eax
    7fb7657a4933:	e8 a8 ea b3 ff       	callq  0x7fb7652e33e0
    7fb7657a4938:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fb7657a493e:	85 c0                	test   %eax,%eax
    7fb7657a4940:	0f 85 44 00 00 00    	jne    0x7fb7657a498a
    7fb7657a4946:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7fb7657a494c:	85 c0                	test   %eax,%eax
    7fb7657a494e:	0f 85 6c 00 00 00    	jne    0x7fb7657a49c0
    7fb7657a4954:	49 8b c7             	mov    %r15,%rax
    7fb7657a4957:	48 05 88 10 00 00    	add    $0x1088,%rax
    7fb7657a495d:	49 8b cf             	mov    %r15,%rcx
    7fb7657a4960:	48 81 c1 18 0d 00 00 	add    $0xd18,%rcx
    7fb7657a4967:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a496a:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a496d:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a4971:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a4975:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a4979:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a497d:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a4981:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a4985:	e9 67 00 00 00       	jmpq   0x7fb7657a49f1
    7fb7657a498a:	49 8b c7             	mov    %r15,%rax
    7fb7657a498d:	48 05 88 10 00 00    	add    $0x1088,%rax
    7fb7657a4993:	49 8b cf             	mov    %r15,%rcx
    7fb7657a4996:	48 81 c1 c8 10 00 00 	add    $0x10c8,%rcx
    7fb7657a499d:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a49a0:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a49a3:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a49a7:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a49ab:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a49af:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a49b3:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a49b7:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a49bb:	e9 31 00 00 00       	jmpq   0x7fb7657a49f1
    7fb7657a49c0:	49 8b c7             	mov    %r15,%rax
    7fb7657a49c3:	48 05 88 10 00 00    	add    $0x1088,%rax
    7fb7657a49c9:	49 8b cf             	mov    %r15,%rcx
    7fb7657a49cc:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7fb7657a49d3:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a49d6:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a49d9:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a49dd:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a49e1:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a49e5:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a49e9:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a49ed:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a49f1:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fb7657a49f7:	85 c0                	test   %eax,%eax
    7fb7657a49f9:	0f 85 1c 00 00 00    	jne    0x7fb7657a4a1b
    7fb7657a49ff:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fb7657a4a05:	85 c0                	test   %eax,%eax
    7fb7657a4a07:	0f 85 1d 00 00 00    	jne    0x7fb7657a4a2a
    7fb7657a4a0d:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fb7657a4a10:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7fb7657a4a16:	e9 19 00 00 00       	jmpq   0x7fb7657a4a34
    7fb7657a4a1b:	c7 85 30 fd ff ff 01 	movl   $0x1,-0x2d0(%rbp)
    7fb7657a4a22:	00 00 00 
    7fb7657a4a25:	e9 0a 00 00 00       	jmpq   0x7fb7657a4a34
    7fb7657a4a2a:	c7 85 30 fd ff ff 00 	movl   $0x0,-0x2d0(%rbp)
    7fb7657a4a31:	00 00 00 
    7fb7657a4a34:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fb7657a4a37:	ff c0                	inc    %eax
    7fb7657a4a39:	83 e0 0f             	and    $0xf,%eax
    7fb7657a4a3c:	89 85 28 fd ff ff    	mov    %eax,-0x2d8(%rbp)
    7fb7657a4a42:	41 8b c5             	mov    %r13d,%eax
    7fb7657a4a45:	83 c8 00             	or     $0x0,%eax
    7fb7657a4a48:	89 85 20 fd ff ff    	mov    %eax,-0x2e0(%rbp)
    7fb7657a4a4e:	49 8b 46 58          	mov    0x58(%r14),%rax
    7fb7657a4a52:	8b 00                	mov    (%rax),%eax
    7fb7657a4a54:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7fb7657a4a57:	85 c9                	test   %ecx,%ecx
    7fb7657a4a59:	0f 94 c1             	sete   %cl
    7fb7657a4a5c:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a4a5f:	23 c1                	and    %ecx,%eax
    7fb7657a4a61:	8b 8d c8 fd ff ff    	mov    -0x238(%rbp),%ecx
    7fb7657a4a67:	23 8d d0 fd ff ff    	and    -0x230(%rbp),%ecx
    7fb7657a4a6d:	85 c9                	test   %ecx,%ecx
    7fb7657a4a6f:	0f 94 c2             	sete   %dl
    7fb7657a4a72:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a4a75:	89 95 18 fd ff ff    	mov    %edx,-0x2e8(%rbp)
    7fb7657a4a7b:	23 d0                	and    %eax,%edx
    7fb7657a4a7d:	8b 75 98             	mov    -0x68(%rbp),%esi
    7fb7657a4a80:	ff c6                	inc    %esi
    7fb7657a4a82:	83 e6 1f             	and    $0x1f,%esi
    7fb7657a4a85:	89 b5 10 fd ff ff    	mov    %esi,-0x2f0(%rbp)
    7fb7657a4a8b:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7fb7657a4a91:	85 c0                	test   %eax,%eax
    7fb7657a4a93:	0f 94 c0             	sete   %al
    7fb7657a4a96:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4a99:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7fb7657a4a9f:	89 85 f8 fc ff ff    	mov    %eax,-0x308(%rbp)
    7fb7657a4aa5:	23 c8                	and    %eax,%ecx
    7fb7657a4aa7:	89 8d f0 fc ff ff    	mov    %ecx,-0x310(%rbp)
    7fb7657a4aad:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fb7657a4ab0:	ff c8                	dec    %eax
    7fb7657a4ab2:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a4ab5:	89 85 e8 fc ff ff    	mov    %eax,-0x318(%rbp)
    7fb7657a4abb:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7fb7657a4ac1:	85 d2                	test   %edx,%edx
    7fb7657a4ac3:	0f 85 1c 00 00 00    	jne    0x7fb7657a4ae5
    7fb7657a4ac9:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7fb7657a4acf:	85 c0                	test   %eax,%eax
    7fb7657a4ad1:	0f 85 1f 00 00 00    	jne    0x7fb7657a4af6
    7fb7657a4ad7:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fb7657a4ada:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fb7657a4ae0:	e9 1d 00 00 00       	jmpq   0x7fb7657a4b02
    7fb7657a4ae5:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fb7657a4aeb:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fb7657a4af1:	e9 0c 00 00 00       	jmpq   0x7fb7657a4b02
    7fb7657a4af6:	8b 85 e8 fc ff ff    	mov    -0x318(%rbp),%eax
    7fb7657a4afc:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fb7657a4b02:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fb7657a4b05:	83 f8 01             	cmp    $0x1,%eax
    7fb7657a4b08:	0f 94 c0             	sete   %al
    7fb7657a4b0b:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4b0e:	23 85 00 fd ff ff    	and    -0x300(%rbp),%eax
    7fb7657a4b14:	23 85 f8 fc ff ff    	and    -0x308(%rbp),%eax
    7fb7657a4b1a:	85 c0                	test   %eax,%eax
    7fb7657a4b1c:	0f 85 1c 00 00 00    	jne    0x7fb7657a4b3e
    7fb7657a4b22:	8b 85 e0 fc ff ff    	mov    -0x320(%rbp),%eax
    7fb7657a4b28:	85 c0                	test   %eax,%eax
    7fb7657a4b2a:	0f 85 1d 00 00 00    	jne    0x7fb7657a4b4d
    7fb7657a4b30:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fb7657a4b33:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7fb7657a4b39:	e9 19 00 00 00       	jmpq   0x7fb7657a4b57
    7fb7657a4b3e:	c7 85 d0 fc ff ff 01 	movl   $0x1,-0x330(%rbp)
    7fb7657a4b45:	00 00 00 
    7fb7657a4b48:	e9 0a 00 00 00       	jmpq   0x7fb7657a4b57
    7fb7657a4b4d:	c7 85 d0 fc ff ff 00 	movl   $0x0,-0x330(%rbp)
    7fb7657a4b54:	00 00 00 
    7fb7657a4b57:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fb7657a4b5a:	83 f8 0f             	cmp    $0xf,%eax
    7fb7657a4b5d:	0f 94 c0             	sete   %al
    7fb7657a4b60:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4b63:	23 85 08 fd ff ff    	and    -0x2f8(%rbp),%eax
    7fb7657a4b69:	23 85 18 fd ff ff    	and    -0x2e8(%rbp),%eax
    7fb7657a4b6f:	85 c0                	test   %eax,%eax
    7fb7657a4b71:	0f 85 1c 00 00 00    	jne    0x7fb7657a4b93
    7fb7657a4b77:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7fb7657a4b7d:	85 c0                	test   %eax,%eax
    7fb7657a4b7f:	0f 85 1d 00 00 00    	jne    0x7fb7657a4ba2
    7fb7657a4b85:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fb7657a4b88:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7fb7657a4b8e:	e9 19 00 00 00       	jmpq   0x7fb7657a4bac
    7fb7657a4b93:	c7 85 c8 fc ff ff 01 	movl   $0x1,-0x338(%rbp)
    7fb7657a4b9a:	00 00 00 
    7fb7657a4b9d:	e9 0a 00 00 00       	jmpq   0x7fb7657a4bac
    7fb7657a4ba2:	c7 85 c8 fc ff ff 00 	movl   $0x0,-0x338(%rbp)
    7fb7657a4ba9:	00 00 00 
    7fb7657a4bac:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fb7657a4baf:	ff c0                	inc    %eax
    7fb7657a4bb1:	83 e0 0f             	and    $0xf,%eax
    7fb7657a4bb4:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7fb7657a4bba:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fb7657a4bc0:	83 c0 02             	add    $0x2,%eax
    7fb7657a4bc3:	83 e0 0f             	and    $0xf,%eax
    7fb7657a4bc6:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7fb7657a4bcc:	b8 01 00 00 00       	mov    $0x1,%eax
    7fb7657a4bd1:	3b 45 98             	cmp    -0x68(%rbp),%eax
    7fb7657a4bd4:	0f 94 c0             	sete   %al
    7fb7657a4bd7:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4bda:	8b 8d 00 fd ff ff    	mov    -0x300(%rbp),%ecx
    7fb7657a4be0:	23 c1                	and    %ecx,%eax
    7fb7657a4be2:	8b 55 90             	mov    -0x70(%rbp),%edx
    7fb7657a4be5:	0b c2                	or     %edx,%eax
    7fb7657a4be7:	8b 95 08 fd ff ff    	mov    -0x2f8(%rbp),%edx
    7fb7657a4bed:	23 c2                	and    %edx,%eax
    7fb7657a4bef:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7fb7657a4bf5:	49 8b 46 50          	mov    0x50(%r14),%rax
    7fb7657a4bf9:	48 89 85 a8 fc ff ff 	mov    %rax,-0x358(%rbp)
    7fb7657a4c00:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fb7657a4c06:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7fb7657a4c0c:	85 c9                	test   %ecx,%ecx
    7fb7657a4c0e:	0f 85 0c 00 00 00    	jne    0x7fb7657a4c20
    7fb7657a4c14:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fb7657a4c1a:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7fb7657a4c20:	49 8b c7             	mov    %r15,%rax
    7fb7657a4c23:	48 05 00 0c 00 00    	add    $0xc00,%rax
    7fb7657a4c29:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7fb7657a4c2f:	c1 e1 06             	shl    $0x6,%ecx
    7fb7657a4c32:	8b c9                	mov    %ecx,%ecx
    7fb7657a4c34:	49 03 cf             	add    %r15,%rcx
    7fb7657a4c37:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a4c3a:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a4c3d:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a4c41:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a4c45:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a4c49:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a4c4d:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a4c51:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a4c55:	49 8b 46 10          	mov    0x10(%r14),%rax
    7fb7657a4c59:	48 8b 00             	mov    (%rax),%rax
    7fb7657a4c5c:	48 89 85 98 fc ff ff 	mov    %rax,-0x368(%rbp)
    7fb7657a4c63:	49 8b 86 80 00 00 00 	mov    0x80(%r14),%rax
    7fb7657a4c6a:	8b 00                	mov    (%rax),%eax
    7fb7657a4c6c:	85 c0                	test   %eax,%eax
    7fb7657a4c6e:	0f 94 c0             	sete   %al
    7fb7657a4c71:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4c74:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7fb7657a4c7a:	23 c1                	and    %ecx,%eax
    7fb7657a4c7c:	89 85 90 fc ff ff    	mov    %eax,-0x370(%rbp)
    7fb7657a4c82:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7fb7657a4c88:	8b c0                	mov    %eax,%eax
    7fb7657a4c8a:	48 c1 e0 06          	shl    $0x6,%rax
    7fb7657a4c8e:	48 89 85 88 fc ff ff 	mov    %rax,-0x378(%rbp)
    7fb7657a4c95:	48 8b 8d 60 ff ff ff 	mov    -0xa0(%rbp),%rcx
    7fb7657a4c9c:	48 03 c1             	add    %rcx,%rax
    7fb7657a4c9f:	48 89 85 80 fc ff ff 	mov    %rax,-0x380(%rbp)
    7fb7657a4ca6:	85 db                	test   %ebx,%ebx
    7fb7657a4ca8:	0f 85 21 00 00 00    	jne    0x7fb7657a4ccf
    7fb7657a4cae:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fb7657a4cb4:	85 c0                	test   %eax,%eax
    7fb7657a4cb6:	0f 85 26 00 00 00    	jne    0x7fb7657a4ce2
    7fb7657a4cbc:	48 8b 85 60 ff ff ff 	mov    -0xa0(%rbp),%rax
    7fb7657a4cc3:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7fb7657a4cca:	e9 21 00 00 00       	jmpq   0x7fb7657a4cf0
    7fb7657a4ccf:	48 8b 85 98 fc ff ff 	mov    -0x368(%rbp),%rax
    7fb7657a4cd6:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7fb7657a4cdd:	e9 0e 00 00 00       	jmpq   0x7fb7657a4cf0
    7fb7657a4ce2:	48 8b 85 80 fc ff ff 	mov    -0x380(%rbp),%rax
    7fb7657a4ce9:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7fb7657a4cf0:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fb7657a4cf6:	85 c0                	test   %eax,%eax
    7fb7657a4cf8:	0f 94 c0             	sete   %al
    7fb7657a4cfb:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4cfe:	8b 95 38 ff ff ff    	mov    -0xc8(%rbp),%edx
    7fb7657a4d04:	85 d2                	test   %edx,%edx
    7fb7657a4d06:	0f 94 c1             	sete   %cl
    7fb7657a4d09:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a4d0c:	8b b5 30 ff ff ff    	mov    -0xd0(%rbp),%esi
    7fb7657a4d12:	83 fe 0f             	cmp    $0xf,%esi
    7fb7657a4d15:	40 0f 94 c6          	sete   %sil
    7fb7657a4d19:	40 0f b6 f6          	movzbl %sil,%esi
    7fb7657a4d1d:	23 95 e0 fd ff ff    	and    -0x220(%rbp),%edx
    7fb7657a4d23:	85 d2                	test   %edx,%edx
    7fb7657a4d25:	0f 94 c2             	sete   %dl
    7fb7657a4d28:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a4d2b:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7fb7657a4d31:	23 d7                	and    %edi,%edx
    7fb7657a4d33:	89 95 70 fc ff ff    	mov    %edx,-0x390(%rbp)
    7fb7657a4d39:	23 f2                	and    %edx,%esi
    7fb7657a4d3b:	89 b5 68 fc ff ff    	mov    %esi,-0x398(%rbp)
    7fb7657a4d41:	0b ce                	or     %esi,%ecx
    7fb7657a4d43:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7fb7657a4d49:	89 8d 58 fc ff ff    	mov    %ecx,-0x3a8(%rbp)
    7fb7657a4d4f:	23 c1                	and    %ecx,%eax
    7fb7657a4d51:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7fb7657a4d57:	03 8d 40 ff ff ff    	add    -0xc0(%rbp),%ecx
    7fb7657a4d5d:	83 e1 1f             	and    $0x1f,%ecx
    7fb7657a4d60:	89 8d 50 fc ff ff    	mov    %ecx,-0x3b0(%rbp)
    7fb7657a4d66:	ff c9                	dec    %ecx
    7fb7657a4d68:	83 e1 1f             	and    $0x1f,%ecx
    7fb7657a4d6b:	89 8d 48 fc ff ff    	mov    %ecx,-0x3b8(%rbp)
    7fb7657a4d71:	89 85 40 fc ff ff    	mov    %eax,-0x3c0(%rbp)
    7fb7657a4d77:	85 c0                	test   %eax,%eax
    7fb7657a4d79:	0f 85 0c 00 00 00    	jne    0x7fb7657a4d8b
    7fb7657a4d7f:	8b 85 50 fc ff ff    	mov    -0x3b0(%rbp),%eax
    7fb7657a4d85:	89 85 48 fc ff ff    	mov    %eax,-0x3b8(%rbp)
    7fb7657a4d8b:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fb7657a4d91:	ff c8                	dec    %eax
    7fb7657a4d93:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a4d96:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7fb7657a4d9c:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fb7657a4da2:	85 c0                	test   %eax,%eax
    7fb7657a4da4:	0f 85 0c 00 00 00    	jne    0x7fb7657a4db6
    7fb7657a4daa:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fb7657a4db0:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7fb7657a4db6:	85 db                	test   %ebx,%ebx
    7fb7657a4db8:	0f 85 1f 00 00 00    	jne    0x7fb7657a4ddd
    7fb7657a4dbe:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fb7657a4dc4:	85 c0                	test   %eax,%eax
    7fb7657a4dc6:	0f 85 20 00 00 00    	jne    0x7fb7657a4dec
    7fb7657a4dcc:	8b 85 38 fc ff ff    	mov    -0x3c8(%rbp),%eax
    7fb7657a4dd2:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fb7657a4dd8:	e9 1b 00 00 00       	jmpq   0x7fb7657a4df8
    7fb7657a4ddd:	c7 85 30 fc ff ff 00 	movl   $0x0,-0x3d0(%rbp)
    7fb7657a4de4:	00 00 00 
    7fb7657a4de7:	e9 0c 00 00 00       	jmpq   0x7fb7657a4df8
    7fb7657a4dec:	8b 85 48 fc ff ff    	mov    -0x3b8(%rbp),%eax
    7fb7657a4df2:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fb7657a4df8:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fb7657a4dfe:	ff c8                	dec    %eax
    7fb7657a4e00:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7fb7657a4e05:	89 85 28 fc ff ff    	mov    %eax,-0x3d8(%rbp)
    7fb7657a4e0b:	85 db                	test   %ebx,%ebx
    7fb7657a4e0d:	0f 85 1f 00 00 00    	jne    0x7fb7657a4e32
    7fb7657a4e13:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fb7657a4e19:	85 c0                	test   %eax,%eax
    7fb7657a4e1b:	0f 85 22 00 00 00    	jne    0x7fb7657a4e43
    7fb7657a4e21:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fb7657a4e27:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7fb7657a4e2d:	e9 1d 00 00 00       	jmpq   0x7fb7657a4e4f
    7fb7657a4e32:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7fb7657a4e38:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7fb7657a4e3e:	e9 0c 00 00 00       	jmpq   0x7fb7657a4e4f
    7fb7657a4e43:	8b 85 28 fc ff ff    	mov    -0x3d8(%rbp),%eax
    7fb7657a4e49:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7fb7657a4e4f:	b8 01 00 00 00       	mov    $0x1,%eax
    7fb7657a4e54:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7fb7657a4e5a:	3b c1                	cmp    %ecx,%eax
    7fb7657a4e5c:	0f 94 c0             	sete   %al
    7fb7657a4e5f:	0f b6 c0             	movzbl %al,%eax
    7fb7657a4e62:	8b 95 90 fc ff ff    	mov    -0x370(%rbp),%edx
    7fb7657a4e68:	23 c2                	and    %edx,%eax
    7fb7657a4e6a:	89 85 18 fc ff ff    	mov    %eax,-0x3e8(%rbp)
    7fb7657a4e70:	85 c9                	test   %ecx,%ecx
    7fb7657a4e72:	0f 95 c1             	setne  %cl
    7fb7657a4e75:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a4e78:	8b c1                	mov    %ecx,%eax
    7fb7657a4e7a:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7fb7657a4e80:	83 f9 00             	cmp    $0x0,%ecx
    7fb7657a4e83:	0f 96 c1             	setbe  %cl
    7fb7657a4e86:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a4e89:	23 c1                	and    %ecx,%eax
    7fb7657a4e8b:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7fb7657a4e91:	85 db                	test   %ebx,%ebx
    7fb7657a4e93:	0f 85 1f 00 00 00    	jne    0x7fb7657a4eb8
    7fb7657a4e99:	8b 85 18 fc ff ff    	mov    -0x3e8(%rbp),%eax
    7fb7657a4e9f:	85 c0                	test   %eax,%eax
    7fb7657a4ea1:	0f 85 22 00 00 00    	jne    0x7fb7657a4ec9
    7fb7657a4ea7:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7fb7657a4ead:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7fb7657a4eb3:	e9 1b 00 00 00       	jmpq   0x7fb7657a4ed3
    7fb7657a4eb8:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fb7657a4ebe:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7fb7657a4ec4:	e9 0a 00 00 00       	jmpq   0x7fb7657a4ed3
    7fb7657a4ec9:	c7 85 08 fc ff ff 00 	movl   $0x0,-0x3f8(%rbp)
    7fb7657a4ed0:	00 00 00 
    7fb7657a4ed3:	85 db                	test   %ebx,%ebx
    7fb7657a4ed5:	0f 85 1f 00 00 00    	jne    0x7fb7657a4efa
    7fb7657a4edb:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fb7657a4ee1:	85 c0                	test   %eax,%eax
    7fb7657a4ee3:	0f 85 22 00 00 00    	jne    0x7fb7657a4f0b
    7fb7657a4ee9:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7fb7657a4eef:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fb7657a4ef5:	e9 1b 00 00 00       	jmpq   0x7fb7657a4f15
    7fb7657a4efa:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7fb7657a4f00:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fb7657a4f06:	e9 0a 00 00 00       	jmpq   0x7fb7657a4f15
    7fb7657a4f0b:	c7 85 00 fc ff ff 10 	movl   $0x10,-0x400(%rbp)
    7fb7657a4f12:	00 00 00 
    7fb7657a4f15:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7fb7657a4f1b:	85 c0                	test   %eax,%eax
    7fb7657a4f1d:	0f 85 36 00 00 00    	jne    0x7fb7657a4f59
    7fb7657a4f23:	49 8b c7             	mov    %r15,%rax
    7fb7657a4f26:	48 05 48 11 00 00    	add    $0x1148,%rax
    7fb7657a4f2c:	49 8b cf             	mov    %r15,%rcx
    7fb7657a4f2f:	48 81 c1 10 0f 00 00 	add    $0xf10,%rcx
    7fb7657a4f36:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a4f39:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a4f3c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a4f40:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a4f44:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a4f48:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a4f4c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a4f50:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a4f54:	e9 31 00 00 00       	jmpq   0x7fb7657a4f8a
    7fb7657a4f59:	49 8b c7             	mov    %r15,%rax
    7fb7657a4f5c:	48 05 48 11 00 00    	add    $0x1148,%rax
    7fb7657a4f62:	49 8b cf             	mov    %r15,%rcx
    7fb7657a4f65:	48 81 c1 d0 0e 00 00 	add    $0xed0,%rcx
    7fb7657a4f6c:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a4f6f:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a4f72:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a4f76:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a4f7a:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a4f7e:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a4f82:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a4f86:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a4f8a:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fb7657a4f90:	23 85 70 fc ff ff    	and    -0x390(%rbp),%eax
    7fb7657a4f96:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7fb7657a4f9c:	49 8b c7             	mov    %r15,%rax
    7fb7657a4f9f:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7fb7657a4fa5:	49 8b cf             	mov    %r15,%rcx
    7fb7657a4fa8:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7fb7657a4faf:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7fb7657a4fb5:	48 89 8d f0 fb ff ff 	mov    %rcx,-0x410(%rbp)
    7fb7657a4fbc:	b9 00 02 00 00       	mov    $0x200,%ecx
    7fb7657a4fc1:	48 8b d0             	mov    %rax,%rdx
    7fb7657a4fc4:	be 00 02 00 00       	mov    $0x200,%esi
    7fb7657a4fc9:	48 8b bd f0 fb ff ff 	mov    -0x410(%rbp),%rdi
    7fb7657a4fd0:	48 89 85 e8 fb ff ff 	mov    %rax,-0x418(%rbp)
    7fb7657a4fd7:	b8 08 00 00 00       	mov    $0x8,%eax
    7fb7657a4fdc:	e8 ff e3 b3 ff       	callq  0x7fb7652e33e0
    7fb7657a4fe1:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fb7657a4fe7:	85 c0                	test   %eax,%eax
    7fb7657a4fe9:	0f 85 44 00 00 00    	jne    0x7fb7657a5033
    7fb7657a4fef:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fb7657a4ff5:	85 c0                	test   %eax,%eax
    7fb7657a4ff7:	0f 85 6c 00 00 00    	jne    0x7fb7657a5069
    7fb7657a4ffd:	49 8b c7             	mov    %r15,%rax
    7fb7657a5000:	48 05 08 11 00 00    	add    $0x1108,%rax
    7fb7657a5006:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5009:	48 81 c1 48 0e 00 00 	add    $0xe48,%rcx
    7fb7657a5010:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5013:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5016:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a501a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a501e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5022:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5026:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a502a:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a502e:	e9 67 00 00 00       	jmpq   0x7fb7657a509a
    7fb7657a5033:	49 8b c7             	mov    %r15,%rax
    7fb7657a5036:	48 05 08 11 00 00    	add    $0x1108,%rax
    7fb7657a503c:	49 8b cf             	mov    %r15,%rcx
    7fb7657a503f:	48 81 c1 48 11 00 00 	add    $0x1148,%rcx
    7fb7657a5046:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5049:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a504c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5050:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5054:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5058:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a505c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5060:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5064:	e9 31 00 00 00       	jmpq   0x7fb7657a509a
    7fb7657a5069:	49 8b c7             	mov    %r15,%rax
    7fb7657a506c:	48 05 08 11 00 00    	add    $0x1108,%rax
    7fb7657a5072:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5075:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7fb7657a507c:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a507f:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5082:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5086:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a508a:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a508e:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5092:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5096:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a509a:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fb7657a50a0:	85 c0                	test   %eax,%eax
    7fb7657a50a2:	0f 85 1f 00 00 00    	jne    0x7fb7657a50c7
    7fb7657a50a8:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7fb7657a50ae:	85 c0                	test   %eax,%eax
    7fb7657a50b0:	0f 85 20 00 00 00    	jne    0x7fb7657a50d6
    7fb7657a50b6:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fb7657a50bc:	89 85 e0 fb ff ff    	mov    %eax,-0x420(%rbp)
    7fb7657a50c2:	e9 19 00 00 00       	jmpq   0x7fb7657a50e0
    7fb7657a50c7:	c7 85 e0 fb ff ff 01 	movl   $0x1,-0x420(%rbp)
    7fb7657a50ce:	00 00 00 
    7fb7657a50d1:	e9 0a 00 00 00       	jmpq   0x7fb7657a50e0
    7fb7657a50d6:	c7 85 e0 fb ff ff 00 	movl   $0x0,-0x420(%rbp)
    7fb7657a50dd:	00 00 00 
    7fb7657a50e0:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fb7657a50e6:	ff c0                	inc    %eax
    7fb7657a50e8:	83 e0 0f             	and    $0xf,%eax
    7fb7657a50eb:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7fb7657a50f1:	49 8b 46 78          	mov    0x78(%r14),%rax
    7fb7657a50f5:	8b 00                	mov    (%rax),%eax
    7fb7657a50f7:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7fb7657a50fd:	85 c9                	test   %ecx,%ecx
    7fb7657a50ff:	0f 94 c1             	sete   %cl
    7fb7657a5102:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a5105:	23 c1                	and    %ecx,%eax
    7fb7657a5107:	8b 8d 58 fc ff ff    	mov    -0x3a8(%rbp),%ecx
    7fb7657a510d:	23 8d 60 fc ff ff    	and    -0x3a0(%rbp),%ecx
    7fb7657a5113:	85 c9                	test   %ecx,%ecx
    7fb7657a5115:	0f 94 c2             	sete   %dl
    7fb7657a5118:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a511b:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7fb7657a5121:	23 d0                	and    %eax,%edx
    7fb7657a5123:	8b b5 28 ff ff ff    	mov    -0xd8(%rbp),%esi
    7fb7657a5129:	ff c6                	inc    %esi
    7fb7657a512b:	83 e6 1f             	and    $0x1f,%esi
    7fb7657a512e:	89 b5 c8 fb ff ff    	mov    %esi,-0x438(%rbp)
    7fb7657a5134:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7fb7657a513a:	85 c0                	test   %eax,%eax
    7fb7657a513c:	0f 94 c0             	sete   %al
    7fb7657a513f:	0f b6 c0             	movzbl %al,%eax
    7fb7657a5142:	89 8d b8 fb ff ff    	mov    %ecx,-0x448(%rbp)
    7fb7657a5148:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7fb7657a514e:	23 c8                	and    %eax,%ecx
    7fb7657a5150:	89 8d a8 fb ff ff    	mov    %ecx,-0x458(%rbp)
    7fb7657a5156:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fb7657a515c:	ff c8                	dec    %eax
    7fb7657a515e:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a5161:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7fb7657a5167:	89 95 98 fb ff ff    	mov    %edx,-0x468(%rbp)
    7fb7657a516d:	85 d2                	test   %edx,%edx
    7fb7657a516f:	0f 85 1f 00 00 00    	jne    0x7fb7657a5194
    7fb7657a5175:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fb7657a517b:	85 c0                	test   %eax,%eax
    7fb7657a517d:	0f 85 22 00 00 00    	jne    0x7fb7657a51a5
    7fb7657a5183:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fb7657a5189:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fb7657a518f:	e9 1d 00 00 00       	jmpq   0x7fb7657a51b1
    7fb7657a5194:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7fb7657a519a:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fb7657a51a0:	e9 0c 00 00 00       	jmpq   0x7fb7657a51b1
    7fb7657a51a5:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7fb7657a51ab:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fb7657a51b1:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fb7657a51b7:	83 f8 01             	cmp    $0x1,%eax
    7fb7657a51ba:	0f 94 c0             	sete   %al
    7fb7657a51bd:	0f b6 c0             	movzbl %al,%eax
    7fb7657a51c0:	23 85 b8 fb ff ff    	and    -0x448(%rbp),%eax
    7fb7657a51c6:	23 85 b0 fb ff ff    	and    -0x450(%rbp),%eax
    7fb7657a51cc:	85 c0                	test   %eax,%eax
    7fb7657a51ce:	0f 85 1f 00 00 00    	jne    0x7fb7657a51f3
    7fb7657a51d4:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7fb7657a51da:	85 c0                	test   %eax,%eax
    7fb7657a51dc:	0f 85 20 00 00 00    	jne    0x7fb7657a5202
    7fb7657a51e2:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fb7657a51e8:	89 85 88 fb ff ff    	mov    %eax,-0x478(%rbp)
    7fb7657a51ee:	e9 19 00 00 00       	jmpq   0x7fb7657a520c
    7fb7657a51f3:	c7 85 88 fb ff ff 01 	movl   $0x1,-0x478(%rbp)
    7fb7657a51fa:	00 00 00 
    7fb7657a51fd:	e9 0a 00 00 00       	jmpq   0x7fb7657a520c
    7fb7657a5202:	c7 85 88 fb ff ff 00 	movl   $0x0,-0x478(%rbp)
    7fb7657a5209:	00 00 00 
    7fb7657a520c:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fb7657a5212:	83 f8 0f             	cmp    $0xf,%eax
    7fb7657a5215:	0f 94 c0             	sete   %al
    7fb7657a5218:	0f b6 c0             	movzbl %al,%eax
    7fb7657a521b:	23 85 c0 fb ff ff    	and    -0x440(%rbp),%eax
    7fb7657a5221:	23 85 d0 fb ff ff    	and    -0x430(%rbp),%eax
    7fb7657a5227:	85 c0                	test   %eax,%eax
    7fb7657a5229:	0f 85 1f 00 00 00    	jne    0x7fb7657a524e
    7fb7657a522f:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fb7657a5235:	85 c0                	test   %eax,%eax
    7fb7657a5237:	0f 85 20 00 00 00    	jne    0x7fb7657a525d
    7fb7657a523d:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fb7657a5243:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7fb7657a5249:	e9 19 00 00 00       	jmpq   0x7fb7657a5267
    7fb7657a524e:	c7 85 80 fb ff ff 01 	movl   $0x1,-0x480(%rbp)
    7fb7657a5255:	00 00 00 
    7fb7657a5258:	e9 0a 00 00 00       	jmpq   0x7fb7657a5267
    7fb7657a525d:	c7 85 80 fb ff ff 00 	movl   $0x0,-0x480(%rbp)
    7fb7657a5264:	00 00 00 
    7fb7657a5267:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fb7657a526d:	ff c0                	inc    %eax
    7fb7657a526f:	83 e0 0f             	and    $0xf,%eax
    7fb7657a5272:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7fb7657a5278:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fb7657a527e:	83 c0 02             	add    $0x2,%eax
    7fb7657a5281:	83 e0 0f             	and    $0xf,%eax
    7fb7657a5284:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7fb7657a528a:	b8 01 00 00 00       	mov    $0x1,%eax
    7fb7657a528f:	3b 85 28 ff ff ff    	cmp    -0xd8(%rbp),%eax
    7fb7657a5295:	0f 94 c0             	sete   %al
    7fb7657a5298:	0f b6 c0             	movzbl %al,%eax
    7fb7657a529b:	8b 8d b8 fb ff ff    	mov    -0x448(%rbp),%ecx
    7fb7657a52a1:	23 c1                	and    %ecx,%eax
    7fb7657a52a3:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7fb7657a52a9:	0b c2                	or     %edx,%eax
    7fb7657a52ab:	8b 95 c0 fb ff ff    	mov    -0x440(%rbp),%edx
    7fb7657a52b1:	23 c2                	and    %edx,%eax
    7fb7657a52b3:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7fb7657a52b9:	49 8b 46 70          	mov    0x70(%r14),%rax
    7fb7657a52bd:	48 89 85 60 fb ff ff 	mov    %rax,-0x4a0(%rbp)
    7fb7657a52c4:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fb7657a52ca:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fb7657a52d0:	85 c9                	test   %ecx,%ecx
    7fb7657a52d2:	0f 85 0c 00 00 00    	jne    0x7fb7657a52e4
    7fb7657a52d8:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fb7657a52de:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fb7657a52e4:	49 8b c7             	mov    %r15,%rax
    7fb7657a52e7:	48 05 00 04 00 00    	add    $0x400,%rax
    7fb7657a52ed:	49 8b cf             	mov    %r15,%rcx
    7fb7657a52f0:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7fb7657a52f7:	8b 95 58 fb ff ff    	mov    -0x4a8(%rbp),%edx
    7fb7657a52fd:	c1 e2 06             	shl    $0x6,%edx
    7fb7657a5300:	8b d2                	mov    %edx,%edx
    7fb7657a5302:	48 03 c2             	add    %rdx,%rax
    7fb7657a5305:	0f 10 00             	movups (%rax),%xmm0
    7fb7657a5308:	0f 11 01             	movups %xmm0,(%rcx)
    7fb7657a530b:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7fb7657a530f:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7fb7657a5313:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7fb7657a5317:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7fb7657a531b:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7fb7657a531f:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7fb7657a5323:	49 8b 06             	mov    (%r14),%rax
    7fb7657a5326:	48 8b 00             	mov    (%rax),%rax
    7fb7657a5329:	48 89 85 50 fb ff ff 	mov    %rax,-0x4b0(%rbp)
    7fb7657a5330:	49 8b 46 40          	mov    0x40(%r14),%rax
    7fb7657a5334:	8b 00                	mov    (%rax),%eax
    7fb7657a5336:	85 c0                	test   %eax,%eax
    7fb7657a5338:	0f 94 c0             	sete   %al
    7fb7657a533b:	0f b6 c0             	movzbl %al,%eax
    7fb7657a533e:	89 85 48 fb ff ff    	mov    %eax,-0x4b8(%rbp)
    7fb7657a5344:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7fb7657a534a:	23 c1                	and    %ecx,%eax
    7fb7657a534c:	89 85 40 fb ff ff    	mov    %eax,-0x4c0(%rbp)
    7fb7657a5352:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
    7fb7657a5359:	48 83 c0 40          	add    $0x40,%rax
    7fb7657a535d:	48 89 85 38 fb ff ff 	mov    %rax,-0x4c8(%rbp)
    7fb7657a5364:	85 db                	test   %ebx,%ebx
    7fb7657a5366:	0f 85 21 00 00 00    	jne    0x7fb7657a538d
    7fb7657a536c:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fb7657a5372:	85 c0                	test   %eax,%eax
    7fb7657a5374:	0f 85 26 00 00 00    	jne    0x7fb7657a53a0
    7fb7657a537a:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
    7fb7657a5381:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7fb7657a5388:	e9 21 00 00 00       	jmpq   0x7fb7657a53ae
    7fb7657a538d:	48 8b 85 50 fb ff ff 	mov    -0x4b0(%rbp),%rax
    7fb7657a5394:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7fb7657a539b:	e9 0e 00 00 00       	jmpq   0x7fb7657a53ae
    7fb7657a53a0:	48 8b 85 38 fb ff ff 	mov    -0x4c8(%rbp),%rax
    7fb7657a53a7:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7fb7657a53ae:	33 c0                	xor    %eax,%eax
    7fb7657a53b0:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7fb7657a53b6:	3b c1                	cmp    %ecx,%eax
    7fb7657a53b8:	0f 94 c0             	sete   %al
    7fb7657a53bb:	0f b6 c0             	movzbl %al,%eax
    7fb7657a53be:	8b 95 b0 fe ff ff    	mov    -0x150(%rbp),%edx
    7fb7657a53c4:	85 d2                	test   %edx,%edx
    7fb7657a53c6:	0f 94 c2             	sete   %dl
    7fb7657a53c9:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a53cc:	89 95 28 fb ff ff    	mov    %edx,-0x4d8(%rbp)
    7fb7657a53d2:	8b b5 b8 fe ff ff    	mov    -0x148(%rbp),%esi
    7fb7657a53d8:	23 d6                	and    %esi,%edx
    7fb7657a53da:	41 83 fc 10          	cmp    $0x10,%r12d
    7fb7657a53de:	40 0f 93 c7          	setae  %dil
    7fb7657a53e2:	40 0f b6 ff          	movzbl %dil,%edi
    7fb7657a53e6:	0b d7                	or     %edi,%edx
    7fb7657a53e8:	23 c2                	and    %edx,%eax
    7fb7657a53ea:	ba 01 00 00 00       	mov    $0x1,%edx
    7fb7657a53ef:	3b d1                	cmp    %ecx,%edx
    7fb7657a53f1:	0f 94 c2             	sete   %dl
    7fb7657a53f4:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a53f7:	89 95 20 fb ff ff    	mov    %edx,-0x4e0(%rbp)
    7fb7657a53fd:	23 95 48 fb ff ff    	and    -0x4b8(%rbp),%edx
    7fb7657a5403:	41 83 fc 01          	cmp    $0x1,%r12d
    7fb7657a5407:	40 0f 97 c7          	seta   %dil
    7fb7657a540b:	40 0f b6 ff          	movzbl %dil,%edi
    7fb7657a540f:	23 f7                	and    %edi,%esi
    7fb7657a5411:	41 83 fc 10          	cmp    $0x10,%r12d
    7fb7657a5415:	40 0f 97 c7          	seta   %dil
    7fb7657a5419:	40 0f b6 ff          	movzbl %dil,%edi
    7fb7657a541d:	0b f7                	or     %edi,%esi
    7fb7657a541f:	23 d6                	and    %esi,%edx
    7fb7657a5421:	0b c2                	or     %edx,%eax
    7fb7657a5423:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7fb7657a5429:	41 83 fc 10          	cmp    $0x10,%r12d
    7fb7657a542d:	0f 94 c0             	sete   %al
    7fb7657a5430:	0f b6 c0             	movzbl %al,%eax
    7fb7657a5433:	33 d2                	xor    %edx,%edx
    7fb7657a5435:	3b d1                	cmp    %ecx,%edx
    7fb7657a5437:	0f 94 c2             	sete   %dl
    7fb7657a543a:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a543d:	23 c2                	and    %edx,%eax
    7fb7657a543f:	0b f8                	or     %eax,%edi
    7fb7657a5441:	85 c9                	test   %ecx,%ecx
    7fb7657a5443:	0f 95 c1             	setne  %cl
    7fb7657a5446:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a5449:	8b c1                	mov    %ecx,%eax
    7fb7657a544b:	41 8b cc             	mov    %r12d,%ecx
    7fb7657a544e:	2b c8                	sub    %eax,%ecx
    7fb7657a5450:	83 e1 1f             	and    $0x1f,%ecx
    7fb7657a5453:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7fb7657a5459:	c7 85 08 fb ff ff 10 	movl   $0x10,-0x4f8(%rbp)
    7fb7657a5460:	00 00 00 
    7fb7657a5463:	85 ff                	test   %edi,%edi
    7fb7657a5465:	0f 85 0c 00 00 00    	jne    0x7fb7657a5477
    7fb7657a546b:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fb7657a5471:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7fb7657a5477:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fb7657a547d:	ff c8                	dec    %eax
    7fb7657a547f:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a5482:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7fb7657a5488:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fb7657a548e:	85 c0                	test   %eax,%eax
    7fb7657a5490:	0f 85 1f 00 00 00    	jne    0x7fb7657a54b5
    7fb7657a5496:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fb7657a549c:	85 c0                	test   %eax,%eax
    7fb7657a549e:	0f 85 22 00 00 00    	jne    0x7fb7657a54c6
    7fb7657a54a4:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fb7657a54aa:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7fb7657a54b0:	e9 1d 00 00 00       	jmpq   0x7fb7657a54d2
    7fb7657a54b5:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fb7657a54bb:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7fb7657a54c1:	e9 0c 00 00 00       	jmpq   0x7fb7657a54d2
    7fb7657a54c6:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fb7657a54cc:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7fb7657a54d2:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fb7657a54d8:	23 85 20 fb ff ff    	and    -0x4e0(%rbp),%eax
    7fb7657a54de:	89 85 f0 fa ff ff    	mov    %eax,-0x510(%rbp)
    7fb7657a54e4:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fb7657a54ea:	85 c0                	test   %eax,%eax
    7fb7657a54ec:	0f 85 1f 00 00 00    	jne    0x7fb7657a5511
    7fb7657a54f2:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7fb7657a54f8:	85 c0                	test   %eax,%eax
    7fb7657a54fa:	0f 85 20 00 00 00    	jne    0x7fb7657a5520
    7fb7657a5500:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fb7657a5506:	89 85 e8 fa ff ff    	mov    %eax,-0x518(%rbp)
    7fb7657a550c:	e9 19 00 00 00       	jmpq   0x7fb7657a552a
    7fb7657a5511:	c7 85 e8 fa ff ff 01 	movl   $0x1,-0x518(%rbp)
    7fb7657a5518:	00 00 00 
    7fb7657a551b:	e9 0a 00 00 00       	jmpq   0x7fb7657a552a
    7fb7657a5520:	c7 85 e8 fa ff ff 00 	movl   $0x0,-0x518(%rbp)
    7fb7657a5527:	00 00 00 
    7fb7657a552a:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fb7657a552d:	83 f8 02             	cmp    $0x2,%eax
    7fb7657a5530:	0f 94 c0             	sete   %al
    7fb7657a5533:	0f b6 c0             	movzbl %al,%eax
    7fb7657a5536:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7fb7657a553c:	85 c9                	test   %ecx,%ecx
    7fb7657a553e:	0f 95 c1             	setne  %cl
    7fb7657a5541:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a5544:	89 85 e0 fa ff ff    	mov    %eax,-0x520(%rbp)
    7fb7657a554a:	23 c8                	and    %eax,%ecx
    7fb7657a554c:	8b c1                	mov    %ecx,%eax
    7fb7657a554e:	89 85 d8 fa ff ff    	mov    %eax,-0x528(%rbp)
    7fb7657a5554:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7fb7657a555a:	0b c1                	or     %ecx,%eax
    7fb7657a555c:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7fb7657a5562:	23 c1                	and    %ecx,%eax
    7fb7657a5564:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7fb7657a556a:	23 c8                	and    %eax,%ecx
    7fb7657a556c:	b8 01 00 00 00       	mov    $0x1,%eax
    7fb7657a5571:	41 3b c4             	cmp    %r12d,%eax
    7fb7657a5574:	0f 94 c0             	sete   %al
    7fb7657a5577:	0f b6 c0             	movzbl %al,%eax
    7fb7657a557a:	89 85 c8 fa ff ff    	mov    %eax,-0x538(%rbp)
    7fb7657a5580:	8b 95 40 fb ff ff    	mov    -0x4c0(%rbp),%edx
    7fb7657a5586:	23 c2                	and    %edx,%eax
    7fb7657a5588:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fb7657a558e:	85 c9                	test   %ecx,%ecx
    7fb7657a5590:	0f 85 1f 00 00 00    	jne    0x7fb7657a55b5
    7fb7657a5596:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fb7657a559c:	85 c0                	test   %eax,%eax
    7fb7657a559e:	0f 85 20 00 00 00    	jne    0x7fb7657a55c4
    7fb7657a55a4:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fb7657a55aa:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7fb7657a55b0:	e9 19 00 00 00       	jmpq   0x7fb7657a55ce
    7fb7657a55b5:	c7 85 b8 fa ff ff 01 	movl   $0x1,-0x548(%rbp)
    7fb7657a55bc:	00 00 00 
    7fb7657a55bf:	e9 0a 00 00 00       	jmpq   0x7fb7657a55ce
    7fb7657a55c4:	c7 85 b8 fa ff ff 00 	movl   $0x0,-0x548(%rbp)
    7fb7657a55cb:	00 00 00 
    7fb7657a55ce:	33 c0                	xor    %eax,%eax
    7fb7657a55d0:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7fb7657a55d6:	3b c1                	cmp    %ecx,%eax
    7fb7657a55d8:	0f 94 c0             	sete   %al
    7fb7657a55db:	0f b6 c0             	movzbl %al,%eax
    7fb7657a55de:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fb7657a55e1:	8b d2                	mov    %edx,%edx
    7fb7657a55e3:	48 89 95 b0 fa ff ff 	mov    %rdx,-0x550(%rbp)
    7fb7657a55ea:	48 8d 95 b0 fa ff ff 	lea    -0x550(%rbp),%rdx
    7fb7657a55f1:	49 8b f7             	mov    %r15,%rsi
    7fb7657a55f4:	48 81 c6 88 12 00 00 	add    $0x1288,%rsi
    7fb7657a55fb:	b9 20 00 00 00       	mov    $0x20,%ecx
    7fb7657a5600:	48 89 95 a8 fa ff ff 	mov    %rdx,-0x558(%rbp)
    7fb7657a5607:	48 89 b5 a0 fa ff ff 	mov    %rsi,-0x560(%rbp)
    7fb7657a560e:	be 00 02 00 00       	mov    $0x200,%esi
    7fb7657a5613:	48 8b bd a0 fa ff ff 	mov    -0x560(%rbp),%rdi
    7fb7657a561a:	89 85 98 fa ff ff    	mov    %eax,-0x568(%rbp)
    7fb7657a5620:	b8 08 00 00 00       	mov    $0x8,%eax
    7fb7657a5625:	e8 56 eb b3 ff       	callq  0x7fb7652e4180
    7fb7657a562a:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fb7657a5630:	c1 e0 05             	shl    $0x5,%eax
    7fb7657a5633:	25 ff 01 00 00       	and    $0x1ff,%eax
    7fb7657a5638:	49 8b cf             	mov    %r15,%rcx
    7fb7657a563b:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7fb7657a5642:	49 8b d7             	mov    %r15,%rdx
    7fb7657a5645:	48 81 c2 c8 12 00 00 	add    $0x12c8,%rdx
    7fb7657a564c:	44 8b c0             	mov    %eax,%r8d
    7fb7657a564f:	48 89 8d 90 fa ff ff 	mov    %rcx,-0x570(%rbp)
    7fb7657a5656:	b9 00 02 00 00       	mov    $0x200,%ecx
    7fb7657a565b:	48 89 95 88 fa ff ff 	mov    %rdx,-0x578(%rbp)
    7fb7657a5662:	48 8b 95 90 fa ff ff 	mov    -0x570(%rbp),%rdx
    7fb7657a5669:	be 00 02 00 00       	mov    $0x200,%esi
    7fb7657a566e:	48 8b bd 88 fa ff ff 	mov    -0x578(%rbp),%rdi
    7fb7657a5675:	89 85 80 fa ff ff    	mov    %eax,-0x580(%rbp)
    7fb7657a567b:	b8 08 00 00 00       	mov    $0x8,%eax
    7fb7657a5680:	e8 cb d6 b3 ff       	callq  0x7fb7652e2d50
    7fb7657a5685:	49 8b 87 c8 12 00 00 	mov    0x12c8(%r15),%rax
    7fb7657a568c:	49 8b 8f 78 0f 00 00 	mov    0xf78(%r15),%rcx
    7fb7657a5693:	48 0b c1             	or     %rcx,%rax
    7fb7657a5696:	49 89 87 08 13 00 00 	mov    %rax,0x1308(%r15)
    7fb7657a569d:	49 8b 87 d0 12 00 00 	mov    0x12d0(%r15),%rax
    7fb7657a56a4:	49 8b 8f 80 0f 00 00 	mov    0xf80(%r15),%rcx
    7fb7657a56ab:	48 0b c1             	or     %rcx,%rax
    7fb7657a56ae:	49 89 87 10 13 00 00 	mov    %rax,0x1310(%r15)
    7fb7657a56b5:	49 8b 87 d8 12 00 00 	mov    0x12d8(%r15),%rax
    7fb7657a56bc:	49 8b 8f 88 0f 00 00 	mov    0xf88(%r15),%rcx
    7fb7657a56c3:	48 0b c1             	or     %rcx,%rax
    7fb7657a56c6:	49 89 87 18 13 00 00 	mov    %rax,0x1318(%r15)
    7fb7657a56cd:	49 8b 87 e0 12 00 00 	mov    0x12e0(%r15),%rax
    7fb7657a56d4:	49 8b 8f 90 0f 00 00 	mov    0xf90(%r15),%rcx
    7fb7657a56db:	48 0b c1             	or     %rcx,%rax
    7fb7657a56de:	49 89 87 20 13 00 00 	mov    %rax,0x1320(%r15)
    7fb7657a56e5:	49 8b 87 e8 12 00 00 	mov    0x12e8(%r15),%rax
    7fb7657a56ec:	49 8b 8f 98 0f 00 00 	mov    0xf98(%r15),%rcx
    7fb7657a56f3:	48 0b c1             	or     %rcx,%rax
    7fb7657a56f6:	49 89 87 28 13 00 00 	mov    %rax,0x1328(%r15)
    7fb7657a56fd:	49 8b 87 f0 12 00 00 	mov    0x12f0(%r15),%rax
    7fb7657a5704:	49 8b 8f a0 0f 00 00 	mov    0xfa0(%r15),%rcx
    7fb7657a570b:	48 0b c1             	or     %rcx,%rax
    7fb7657a570e:	49 89 87 30 13 00 00 	mov    %rax,0x1330(%r15)
    7fb7657a5715:	49 8b 87 f8 12 00 00 	mov    0x12f8(%r15),%rax
    7fb7657a571c:	49 8b 8f a8 0f 00 00 	mov    0xfa8(%r15),%rcx
    7fb7657a5723:	48 0b c1             	or     %rcx,%rax
    7fb7657a5726:	49 89 87 38 13 00 00 	mov    %rax,0x1338(%r15)
    7fb7657a572d:	49 8b 87 00 13 00 00 	mov    0x1300(%r15),%rax
    7fb7657a5734:	49 8b 8f b0 0f 00 00 	mov    0xfb0(%r15),%rcx
    7fb7657a573b:	48 0b c1             	or     %rcx,%rax
    7fb7657a573e:	49 89 87 40 13 00 00 	mov    %rax,0x1340(%r15)
    7fb7657a5745:	8b 85 98 fa ff ff    	mov    -0x568(%rbp),%eax
    7fb7657a574b:	85 c0                	test   %eax,%eax
    7fb7657a574d:	0f 85 36 00 00 00    	jne    0x7fb7657a5789
    7fb7657a5753:	49 8b c7             	mov    %r15,%rax
    7fb7657a5756:	48 05 88 11 00 00    	add    $0x1188,%rax
    7fb7657a575c:	49 8b cf             	mov    %r15,%rcx
    7fb7657a575f:	48 81 c1 08 13 00 00 	add    $0x1308,%rcx
    7fb7657a5766:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5769:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a576c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5770:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5774:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5778:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a577c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5780:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5784:	e9 31 00 00 00       	jmpq   0x7fb7657a57ba
    7fb7657a5789:	49 8b c7             	mov    %r15,%rax
    7fb7657a578c:	48 05 88 11 00 00    	add    $0x1188,%rax
    7fb7657a5792:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5795:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7fb7657a579c:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a579f:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a57a2:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a57a6:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a57aa:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a57ae:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a57b2:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a57b6:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a57ba:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fb7657a57bd:	23 85 48 fe ff ff    	and    -0x1b8(%rbp),%eax
    7fb7657a57c3:	89 85 78 fa ff ff    	mov    %eax,-0x588(%rbp)
    7fb7657a57c9:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fb7657a57cf:	83 f8 0f             	cmp    $0xf,%eax
    7fb7657a57d2:	0f 94 c0             	sete   %al
    7fb7657a57d5:	0f b6 c0             	movzbl %al,%eax
    7fb7657a57d8:	23 45 d8             	and    -0x28(%rbp),%eax
    7fb7657a57db:	85 c0                	test   %eax,%eax
    7fb7657a57dd:	0f 85 1f 00 00 00    	jne    0x7fb7657a5802
    7fb7657a57e3:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7fb7657a57e9:	85 c0                	test   %eax,%eax
    7fb7657a57eb:	0f 85 20 00 00 00    	jne    0x7fb7657a5811
    7fb7657a57f1:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fb7657a57f7:	89 85 70 fa ff ff    	mov    %eax,-0x590(%rbp)
    7fb7657a57fd:	e9 19 00 00 00       	jmpq   0x7fb7657a581b
    7fb7657a5802:	c7 85 70 fa ff ff 01 	movl   $0x1,-0x590(%rbp)
    7fb7657a5809:	00 00 00 
    7fb7657a580c:	e9 0a 00 00 00       	jmpq   0x7fb7657a581b
    7fb7657a5811:	c7 85 70 fa ff ff 00 	movl   $0x0,-0x590(%rbp)
    7fb7657a5818:	00 00 00 
    7fb7657a581b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fb7657a5821:	ff c0                	inc    %eax
    7fb7657a5823:	83 e0 0f             	and    $0xf,%eax
    7fb7657a5826:	89 85 68 fa ff ff    	mov    %eax,-0x598(%rbp)
    7fb7657a582c:	41 8b c5             	mov    %r13d,%eax
    7fb7657a582f:	0b 85 d8 fa ff ff    	or     -0x528(%rbp),%eax
    7fb7657a5835:	89 85 60 fa ff ff    	mov    %eax,-0x5a0(%rbp)
    7fb7657a583b:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7fb7657a5841:	23 85 50 fe ff ff    	and    -0x1b0(%rbp),%eax
    7fb7657a5847:	8b 8d 40 fb ff ff    	mov    -0x4c0(%rbp),%ecx
    7fb7657a584d:	23 8d 28 fb ff ff    	and    -0x4d8(%rbp),%ecx
    7fb7657a5853:	85 c9                	test   %ecx,%ecx
    7fb7657a5855:	0f 94 c2             	sete   %dl
    7fb7657a5858:	0f b6 d2             	movzbl %dl,%edx
    7fb7657a585b:	89 95 58 fa ff ff    	mov    %edx,-0x5a8(%rbp)
    7fb7657a5861:	23 d0                	and    %eax,%edx
    7fb7657a5863:	41 8b f4             	mov    %r12d,%esi
    7fb7657a5866:	ff c6                	inc    %esi
    7fb7657a5868:	83 e6 1f             	and    $0x1f,%esi
    7fb7657a586b:	89 b5 50 fa ff ff    	mov    %esi,-0x5b0(%rbp)
    7fb7657a5871:	89 85 48 fa ff ff    	mov    %eax,-0x5b8(%rbp)
    7fb7657a5877:	85 c0                	test   %eax,%eax
    7fb7657a5879:	0f 94 c0             	sete   %al
    7fb7657a587c:	0f b6 c0             	movzbl %al,%eax
    7fb7657a587f:	89 8d 40 fa ff ff    	mov    %ecx,-0x5c0(%rbp)
    7fb7657a5885:	89 85 38 fa ff ff    	mov    %eax,-0x5c8(%rbp)
    7fb7657a588b:	23 c8                	and    %eax,%ecx
    7fb7657a588d:	89 8d 30 fa ff ff    	mov    %ecx,-0x5d0(%rbp)
    7fb7657a5893:	41 8b c4             	mov    %r12d,%eax
    7fb7657a5896:	ff c8                	dec    %eax
    7fb7657a5898:	83 e0 1f             	and    $0x1f,%eax
    7fb7657a589b:	89 85 28 fa ff ff    	mov    %eax,-0x5d8(%rbp)
    7fb7657a58a1:	85 d2                	test   %edx,%edx
    7fb7657a58a3:	0f 85 1c 00 00 00    	jne    0x7fb7657a58c5
    7fb7657a58a9:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7fb7657a58af:	85 c0                	test   %eax,%eax
    7fb7657a58b1:	0f 85 1f 00 00 00    	jne    0x7fb7657a58d6
    7fb7657a58b7:	41 8b c4             	mov    %r12d,%eax
    7fb7657a58ba:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7fb7657a58c0:	e9 1d 00 00 00       	jmpq   0x7fb7657a58e2
    7fb7657a58c5:	8b 85 50 fa ff ff    	mov    -0x5b0(%rbp),%eax
    7fb7657a58cb:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7fb7657a58d1:	e9 0c 00 00 00       	jmpq   0x7fb7657a58e2
    7fb7657a58d6:	8b 85 28 fa ff ff    	mov    -0x5d8(%rbp),%eax
    7fb7657a58dc:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7fb7657a58e2:	41 83 fc 01          	cmp    $0x1,%r12d
    7fb7657a58e6:	0f 94 c0             	sete   %al
    7fb7657a58e9:	0f b6 c0             	movzbl %al,%eax
    7fb7657a58ec:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7fb7657a58f2:	23 c1                	and    %ecx,%eax
    7fb7657a58f4:	23 85 38 fa ff ff    	and    -0x5c8(%rbp),%eax
    7fb7657a58fa:	85 c9                	test   %ecx,%ecx
    7fb7657a58fc:	0f 94 c1             	sete   %cl
    7fb7657a58ff:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a5902:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7fb7657a5908:	23 ca                	and    %edx,%ecx
    7fb7657a590a:	89 8d 18 fa ff ff    	mov    %ecx,-0x5e8(%rbp)
    7fb7657a5910:	85 c0                	test   %eax,%eax
    7fb7657a5912:	0f 85 1f 00 00 00    	jne    0x7fb7657a5937
    7fb7657a5918:	8b 85 18 fa ff ff    	mov    -0x5e8(%rbp),%eax
    7fb7657a591e:	85 c0                	test   %eax,%eax
    7fb7657a5920:	0f 85 20 00 00 00    	jne    0x7fb7657a5946
    7fb7657a5926:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7fb7657a592c:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7fb7657a5932:	e9 19 00 00 00       	jmpq   0x7fb7657a5950
    7fb7657a5937:	c7 85 10 fa ff ff 01 	movl   $0x1,-0x5f0(%rbp)
    7fb7657a593e:	00 00 00 
    7fb7657a5941:	e9 0a 00 00 00       	jmpq   0x7fb7657a5950
    7fb7657a5946:	c7 85 10 fa ff ff 00 	movl   $0x0,-0x5f0(%rbp)
    7fb7657a594d:	00 00 00 
    7fb7657a5950:	41 83 fc 0f          	cmp    $0xf,%r12d
    7fb7657a5954:	0f 94 c0             	sete   %al
    7fb7657a5957:	0f b6 c0             	movzbl %al,%eax
    7fb7657a595a:	23 85 48 fa ff ff    	and    -0x5b8(%rbp),%eax
    7fb7657a5960:	23 85 58 fa ff ff    	and    -0x5a8(%rbp),%eax
    7fb7657a5966:	85 c0                	test   %eax,%eax
    7fb7657a5968:	0f 85 1f 00 00 00    	jne    0x7fb7657a598d
    7fb7657a596e:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7fb7657a5974:	85 c0                	test   %eax,%eax
    7fb7657a5976:	0f 85 20 00 00 00    	jne    0x7fb7657a599c
    7fb7657a597c:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fb7657a5982:	89 85 08 fa ff ff    	mov    %eax,-0x5f8(%rbp)
    7fb7657a5988:	e9 19 00 00 00       	jmpq   0x7fb7657a59a6
    7fb7657a598d:	c7 85 08 fa ff ff 01 	movl   $0x1,-0x5f8(%rbp)
    7fb7657a5994:	00 00 00 
    7fb7657a5997:	e9 0a 00 00 00       	jmpq   0x7fb7657a59a6
    7fb7657a599c:	c7 85 08 fa ff ff 00 	movl   $0x0,-0x5f8(%rbp)
    7fb7657a59a3:	00 00 00 
    7fb7657a59a6:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fb7657a59ac:	ff c0                	inc    %eax
    7fb7657a59ae:	83 e0 0f             	and    $0xf,%eax
    7fb7657a59b1:	89 85 00 fa ff ff    	mov    %eax,-0x600(%rbp)
    7fb7657a59b7:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fb7657a59bd:	83 c0 02             	add    $0x2,%eax
    7fb7657a59c0:	83 e0 0f             	and    $0xf,%eax
    7fb7657a59c3:	89 85 f8 f9 ff ff    	mov    %eax,-0x608(%rbp)
    7fb7657a59c9:	8b 85 c8 fa ff ff    	mov    -0x538(%rbp),%eax
    7fb7657a59cf:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7fb7657a59d5:	23 c1                	and    %ecx,%eax
    7fb7657a59d7:	8b 95 b0 fe ff ff    	mov    -0x150(%rbp),%edx
    7fb7657a59dd:	0b c2                	or     %edx,%eax
    7fb7657a59df:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7fb7657a59e5:	23 c2                	and    %edx,%eax
    7fb7657a59e7:	89 85 f0 f9 ff ff    	mov    %eax,-0x610(%rbp)
    7fb7657a59ed:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fb7657a59f3:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7fb7657a59f9:	85 c9                	test   %ecx,%ecx
    7fb7657a59fb:	0f 85 0c 00 00 00    	jne    0x7fb7657a5a0d
    7fb7657a5a01:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fb7657a5a07:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7fb7657a5a0d:	49 8b c7             	mov    %r15,%rax
    7fb7657a5a10:	48 05 00 08 00 00    	add    $0x800,%rax
    7fb7657a5a16:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5a19:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7fb7657a5a20:	8b 95 e8 f9 ff ff    	mov    -0x618(%rbp),%edx
    7fb7657a5a26:	c1 e2 06             	shl    $0x6,%edx
    7fb7657a5a29:	8b d2                	mov    %edx,%edx
    7fb7657a5a2b:	48 03 c2             	add    %rdx,%rax
    7fb7657a5a2e:	0f 10 00             	movups (%rax),%xmm0
    7fb7657a5a31:	0f 11 01             	movups %xmm0,(%rcx)
    7fb7657a5a34:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7fb7657a5a38:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7fb7657a5a3c:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7fb7657a5a40:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7fb7657a5a44:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7fb7657a5a48:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7fb7657a5a4c:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7fb7657a5a52:	85 c0                	test   %eax,%eax
    7fb7657a5a54:	0f 84 3f 00 00 00    	je     0x7fb7657a5a99
    7fb7657a5a5a:	49 8b c7             	mov    %r15,%rax
    7fb7657a5a5d:	48 05 00 08 00 00    	add    $0x800,%rax
    7fb7657a5a63:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5a66:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7fb7657a5a6d:	8b 95 a0 fe ff ff    	mov    -0x160(%rbp),%edx
    7fb7657a5a73:	c1 e2 06             	shl    $0x6,%edx
    7fb7657a5a76:	8b d2                	mov    %edx,%edx
    7fb7657a5a78:	48 03 c2             	add    %rdx,%rax
    7fb7657a5a7b:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5a7e:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5a81:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5a85:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5a89:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5a8d:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5a91:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5a95:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5a99:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fb7657a5a9f:	85 c0                	test   %eax,%eax
    7fb7657a5aa1:	0f 84 3c 00 00 00    	je     0x7fb7657a5ae3
    7fb7657a5aa7:	49 8b c7             	mov    %r15,%rax
    7fb7657a5aaa:	48 05 00 04 00 00    	add    $0x400,%rax
    7fb7657a5ab0:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7fb7657a5ab6:	c1 e1 06             	shl    $0x6,%ecx
    7fb7657a5ab9:	8b c9                	mov    %ecx,%ecx
    7fb7657a5abb:	48 03 c1             	add    %rcx,%rax
    7fb7657a5abe:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7fb7657a5ac5:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5ac8:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5acb:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5acf:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5ad3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5ad7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5adb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5adf:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5ae3:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fb7657a5ae9:	85 c0                	test   %eax,%eax
    7fb7657a5aeb:	0f 84 30 00 00 00    	je     0x7fb7657a5b21
    7fb7657a5af1:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fb7657a5af4:	c1 e0 06             	shl    $0x6,%eax
    7fb7657a5af7:	8b c0                	mov    %eax,%eax
    7fb7657a5af9:	49 03 c7             	add    %r15,%rax
    7fb7657a5afc:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7fb7657a5b03:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5b06:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5b09:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5b0d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5b11:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5b15:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5b19:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5b1d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5b21:	49 8b c7             	mov    %r15,%rax
    7fb7657a5b24:	48 05 48 10 00 00    	add    $0x1048,%rax
    7fb7657a5b2a:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5b2d:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7fb7657a5b34:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5b37:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5b3a:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5b3e:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5b42:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5b46:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5b4a:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5b4e:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5b52:	49 8b c7             	mov    %r15,%rax
    7fb7657a5b55:	48 05 08 10 00 00    	add    $0x1008,%rax
    7fb7657a5b5b:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5b5e:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7fb7657a5b65:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5b68:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5b6b:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5b6f:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5b73:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5b77:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5b7b:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5b7f:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5b83:	45 85 ed             	test   %r13d,%r13d
    7fb7657a5b86:	0f 84 44 00 00 00    	je     0x7fb7657a5bd0
    7fb7657a5b8c:	41 c7 87 00 10 00 00 	movl   $0x0,0x1000(%r15)
    7fb7657a5b93:	00 00 00 00 
    7fb7657a5b97:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%rbp)
    7fb7657a5b9e:	00 00 00 
    7fb7657a5ba1:	41 c7 87 f0 0f 00 00 	movl   $0x0,0xff0(%r15)
    7fb7657a5ba8:	00 00 00 00 
    7fb7657a5bac:	c7 85 98 fe ff ff 00 	movl   $0x0,-0x168(%rbp)
    7fb7657a5bb3:	00 00 00 
    7fb7657a5bb6:	41 c7 87 f8 0f 00 00 	movl   $0x1,0xff8(%r15)
    7fb7657a5bbd:	01 00 00 00 
    7fb7657a5bc1:	c7 85 90 fe ff ff 01 	movl   $0x1,-0x170(%rbp)
    7fb7657a5bc8:	00 00 00 
    7fb7657a5bcb:	e9 47 00 00 00       	jmpq   0x7fb7657a5c17
    7fb7657a5bd0:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7fb7657a5bd6:	41 89 87 00 10 00 00 	mov    %eax,0x1000(%r15)
    7fb7657a5bdd:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fb7657a5be3:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7fb7657a5be9:	85 c0                	test   %eax,%eax
    7fb7657a5beb:	0f 84 26 00 00 00    	je     0x7fb7657a5c17
    7fb7657a5bf1:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fb7657a5bf7:	41 89 87 f0 0f 00 00 	mov    %eax,0xff0(%r15)
    7fb7657a5bfe:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fb7657a5c04:	8b 85 f8 f9 ff ff    	mov    -0x608(%rbp),%eax
    7fb7657a5c0a:	41 89 87 f8 0f 00 00 	mov    %eax,0xff8(%r15)
    7fb7657a5c11:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fb7657a5c17:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fb7657a5c1d:	85 c0                	test   %eax,%eax
    7fb7657a5c1f:	0f 84 1a 00 00 00    	je     0x7fb7657a5c3f
    7fb7657a5c25:	41 c7 87 e8 0f 00 00 	movl   $0x0,0xfe8(%r15)
    7fb7657a5c2c:	00 00 00 00 
    7fb7657a5c30:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7fb7657a5c37:	00 00 00 
    7fb7657a5c3a:	e9 21 00 00 00       	jmpq   0x7fb7657a5c60
    7fb7657a5c3f:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7fb7657a5c45:	85 c0                	test   %eax,%eax
    7fb7657a5c47:	0f 84 13 00 00 00    	je     0x7fb7657a5c60
    7fb7657a5c4d:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7fb7657a5c53:	41 89 87 e8 0f 00 00 	mov    %eax,0xfe8(%r15)
    7fb7657a5c5a:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fb7657a5c60:	45 85 ed             	test   %r13d,%r13d
    7fb7657a5c63:	0f 84 52 00 00 00    	je     0x7fb7657a5cbb
    7fb7657a5c69:	41 c7 87 e0 0f 00 00 	movl   $0x0,0xfe0(%r15)
    7fb7657a5c70:	00 00 00 00 
    7fb7657a5c74:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7fb7657a5c7b:	00 00 00 
    7fb7657a5c7e:	41 c7 87 d8 0f 00 00 	movl   $0x1,0xfd8(%r15)
    7fb7657a5c85:	01 00 00 00 
    7fb7657a5c89:	c7 85 b0 fe ff ff 01 	movl   $0x1,-0x150(%rbp)
    7fb7657a5c90:	00 00 00 
    7fb7657a5c93:	41 c7 87 d0 0f 00 00 	movl   $0x0,0xfd0(%r15)
    7fb7657a5c9a:	00 00 00 00 
    7fb7657a5c9e:	45 33 e4             	xor    %r12d,%r12d
    7fb7657a5ca1:	41 c7 87 c8 0f 00 00 	movl   $0x0,0xfc8(%r15)
    7fb7657a5ca8:	00 00 00 00 
    7fb7657a5cac:	c7 85 b8 fe ff ff 00 	movl   $0x0,-0x148(%rbp)
    7fb7657a5cb3:	00 00 00 
    7fb7657a5cb6:	e9 49 00 00 00       	jmpq   0x7fb7657a5d04
    7fb7657a5cbb:	8b 85 08 fa ff ff    	mov    -0x5f8(%rbp),%eax
    7fb7657a5cc1:	41 89 87 e0 0f 00 00 	mov    %eax,0xfe0(%r15)
    7fb7657a5cc8:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fb7657a5cce:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7fb7657a5cd4:	41 89 87 d8 0f 00 00 	mov    %eax,0xfd8(%r15)
    7fb7657a5cdb:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fb7657a5ce1:	8b 85 20 fa ff ff    	mov    -0x5e0(%rbp),%eax
    7fb7657a5ce7:	41 89 87 d0 0f 00 00 	mov    %eax,0xfd0(%r15)
    7fb7657a5cee:	4c 8b e0             	mov    %rax,%r12
    7fb7657a5cf1:	8b 85 e0 fa ff ff    	mov    -0x520(%rbp),%eax
    7fb7657a5cf7:	41 89 87 c8 0f 00 00 	mov    %eax,0xfc8(%r15)
    7fb7657a5cfe:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fb7657a5d04:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7fb7657a5d0a:	85 c0                	test   %eax,%eax
    7fb7657a5d0c:	0f 84 1a 00 00 00    	je     0x7fb7657a5d2c
    7fb7657a5d12:	41 c7 87 c0 0f 00 00 	movl   $0x0,0xfc0(%r15)
    7fb7657a5d19:	00 00 00 00 
    7fb7657a5d1d:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7fb7657a5d24:	00 00 00 
    7fb7657a5d27:	e9 21 00 00 00       	jmpq   0x7fb7657a5d4d
    7fb7657a5d2c:	8b 85 78 fa ff ff    	mov    -0x588(%rbp),%eax
    7fb7657a5d32:	85 c0                	test   %eax,%eax
    7fb7657a5d34:	0f 84 13 00 00 00    	je     0x7fb7657a5d4d
    7fb7657a5d3a:	8b 85 68 fa ff ff    	mov    -0x598(%rbp),%eax
    7fb7657a5d40:	41 89 87 c0 0f 00 00 	mov    %eax,0xfc0(%r15)
    7fb7657a5d47:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fb7657a5d4d:	45 85 ed             	test   %r13d,%r13d
    7fb7657a5d50:	0f 84 1a 00 00 00    	je     0x7fb7657a5d70
    7fb7657a5d56:	41 c7 87 b8 0f 00 00 	movl   $0x0,0xfb8(%r15)
    7fb7657a5d5d:	00 00 00 00 
    7fb7657a5d61:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7fb7657a5d68:	00 00 00 
    7fb7657a5d6b:	e9 13 00 00 00       	jmpq   0x7fb7657a5d83
    7fb7657a5d70:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7fb7657a5d76:	41 89 87 b8 0f 00 00 	mov    %eax,0xfb8(%r15)
    7fb7657a5d7d:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fb7657a5d83:	8b 85 78 fa ff ff    	mov    -0x588(%rbp),%eax
    7fb7657a5d89:	85 c0                	test   %eax,%eax
    7fb7657a5d8b:	0f 84 31 00 00 00    	je     0x7fb7657a5dc2
    7fb7657a5d91:	49 8b c7             	mov    %r15,%rax
    7fb7657a5d94:	48 05 78 0f 00 00    	add    $0xf78,%rax
    7fb7657a5d9a:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5d9d:	48 81 c1 88 11 00 00 	add    $0x1188,%rcx
    7fb7657a5da4:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5da7:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5daa:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5dae:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5db2:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5db6:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5dba:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5dbe:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5dc2:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fb7657a5dc8:	85 c0                	test   %eax,%eax
    7fb7657a5dca:	0f 84 13 00 00 00    	je     0x7fb7657a5de3
    7fb7657a5dd0:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fb7657a5dd6:	41 89 87 70 0f 00 00 	mov    %eax,0xf70(%r15)
    7fb7657a5ddd:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fb7657a5de3:	45 85 ed             	test   %r13d,%r13d
    7fb7657a5de6:	0f 84 5a 00 00 00    	je     0x7fb7657a5e46
    7fb7657a5dec:	41 c7 87 68 0f 00 00 	movl   $0x0,0xf68(%r15)
    7fb7657a5df3:	00 00 00 00 
    7fb7657a5df7:	c7 85 d8 fe ff ff 00 	movl   $0x0,-0x128(%rbp)
    7fb7657a5dfe:	00 00 00 
    7fb7657a5e01:	41 c7 87 60 0f 00 00 	movl   $0x0,0xf60(%r15)
    7fb7657a5e08:	00 00 00 00 
    7fb7657a5e0c:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7fb7657a5e13:	00 00 00 
    7fb7657a5e16:	41 c7 87 58 0f 00 00 	movl   $0x0,0xf58(%r15)
    7fb7657a5e1d:	00 00 00 00 
    7fb7657a5e21:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7fb7657a5e28:	00 00 00 
    7fb7657a5e2b:	49 c7 87 50 0f 00 00 	movq   $0x0,0xf50(%r15)
    7fb7657a5e32:	00 00 00 00 
    7fb7657a5e36:	48 c7 85 f0 fe ff ff 	movq   $0x0,-0x110(%rbp)
    7fb7657a5e3d:	00 00 00 00 
    7fb7657a5e41:	e9 4e 00 00 00       	jmpq   0x7fb7657a5e94
    7fb7657a5e46:	8b 85 b8 fa ff ff    	mov    -0x548(%rbp),%eax
    7fb7657a5e4c:	41 89 87 68 0f 00 00 	mov    %eax,0xf68(%r15)
    7fb7657a5e53:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fb7657a5e59:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7fb7657a5e5f:	41 89 87 60 0f 00 00 	mov    %eax,0xf60(%r15)
    7fb7657a5e66:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fb7657a5e6c:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7fb7657a5e72:	41 89 87 58 0f 00 00 	mov    %eax,0xf58(%r15)
    7fb7657a5e79:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fb7657a5e7f:	48 8b 85 30 fb ff ff 	mov    -0x4d0(%rbp),%rax
    7fb7657a5e86:	49 89 87 50 0f 00 00 	mov    %rax,0xf50(%r15)
    7fb7657a5e8d:	48 89 85 f0 fe ff ff 	mov    %rax,-0x110(%rbp)
    7fb7657a5e94:	49 8b c7             	mov    %r15,%rax
    7fb7657a5e97:	48 05 10 0f 00 00    	add    $0xf10,%rax
    7fb7657a5e9d:	49 8b cf             	mov    %r15,%rcx
    7fb7657a5ea0:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7fb7657a5ea7:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5eaa:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5ead:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5eb1:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5eb5:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5eb9:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5ebd:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5ec1:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5ec5:	49 8b c7             	mov    %r15,%rax
    7fb7657a5ec8:	48 05 d0 0e 00 00    	add    $0xed0,%rax
    7fb7657a5ece:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7fb7657a5ed5:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a5ed8:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a5edb:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a5edf:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a5ee3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a5ee7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a5eeb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a5eef:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a5ef3:	45 85 ed             	test   %r13d,%r13d
    7fb7657a5ef6:	0f 84 44 00 00 00    	je     0x7fb7657a5f40
    7fb7657a5efc:	41 c7 87 c8 0e 00 00 	movl   $0x0,0xec8(%r15)
    7fb7657a5f03:	00 00 00 00 
    7fb7657a5f07:	c7 85 f8 fe ff ff 00 	movl   $0x0,-0x108(%rbp)
    7fb7657a5f0e:	00 00 00 
    7fb7657a5f11:	41 c7 87 b8 0e 00 00 	movl   $0x0,0xeb8(%r15)
    7fb7657a5f18:	00 00 00 00 
    7fb7657a5f1c:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7fb7657a5f23:	00 00 00 
    7fb7657a5f26:	41 c7 87 c0 0e 00 00 	movl   $0x1,0xec0(%r15)
    7fb7657a5f2d:	01 00 00 00 
    7fb7657a5f31:	c7 85 00 ff ff ff 01 	movl   $0x1,-0x100(%rbp)
    7fb7657a5f38:	00 00 00 
    7fb7657a5f3b:	e9 47 00 00 00       	jmpq   0x7fb7657a5f87
    7fb7657a5f40:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7fb7657a5f46:	41 89 87 c8 0e 00 00 	mov    %eax,0xec8(%r15)
    7fb7657a5f4d:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fb7657a5f53:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7fb7657a5f59:	85 c0                	test   %eax,%eax
    7fb7657a5f5b:	0f 84 26 00 00 00    	je     0x7fb7657a5f87
    7fb7657a5f61:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fb7657a5f67:	41 89 87 b8 0e 00 00 	mov    %eax,0xeb8(%r15)
    7fb7657a5f6e:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fb7657a5f74:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fb7657a5f7a:	41 89 87 c0 0e 00 00 	mov    %eax,0xec0(%r15)
    7fb7657a5f81:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fb7657a5f87:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fb7657a5f8d:	85 c0                	test   %eax,%eax
    7fb7657a5f8f:	0f 84 1a 00 00 00    	je     0x7fb7657a5faf
    7fb7657a5f95:	41 c7 87 b0 0e 00 00 	movl   $0x0,0xeb0(%r15)
    7fb7657a5f9c:	00 00 00 00 
    7fb7657a5fa0:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7fb7657a5fa7:	00 00 00 
    7fb7657a5faa:	e9 21 00 00 00       	jmpq   0x7fb7657a5fd0
    7fb7657a5faf:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fb7657a5fb5:	85 c0                	test   %eax,%eax
    7fb7657a5fb7:	0f 84 13 00 00 00    	je     0x7fb7657a5fd0
    7fb7657a5fbd:	8b 85 78 fb ff ff    	mov    -0x488(%rbp),%eax
    7fb7657a5fc3:	41 89 87 b0 0e 00 00 	mov    %eax,0xeb0(%r15)
    7fb7657a5fca:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fb7657a5fd0:	45 85 ed             	test   %r13d,%r13d
    7fb7657a5fd3:	0f 84 44 00 00 00    	je     0x7fb7657a601d
    7fb7657a5fd9:	41 c7 87 a8 0e 00 00 	movl   $0x0,0xea8(%r15)
    7fb7657a5fe0:	00 00 00 00 
    7fb7657a5fe4:	c7 85 18 ff ff ff 00 	movl   $0x0,-0xe8(%rbp)
    7fb7657a5feb:	00 00 00 
    7fb7657a5fee:	41 c7 87 a0 0e 00 00 	movl   $0x1,0xea0(%r15)
    7fb7657a5ff5:	01 00 00 00 
    7fb7657a5ff9:	c7 85 20 ff ff ff 01 	movl   $0x1,-0xe0(%rbp)
    7fb7657a6000:	00 00 00 
    7fb7657a6003:	41 c7 87 98 0e 00 00 	movl   $0x0,0xe98(%r15)
    7fb7657a600a:	00 00 00 00 
    7fb7657a600e:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7fb7657a6015:	00 00 00 
    7fb7657a6018:	e9 39 00 00 00       	jmpq   0x7fb7657a6056
    7fb7657a601d:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7fb7657a6023:	41 89 87 a8 0e 00 00 	mov    %eax,0xea8(%r15)
    7fb7657a602a:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fb7657a6030:	8b 85 88 fb ff ff    	mov    -0x478(%rbp),%eax
    7fb7657a6036:	41 89 87 a0 0e 00 00 	mov    %eax,0xea0(%r15)
    7fb7657a603d:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fb7657a6043:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7fb7657a6049:	41 89 87 98 0e 00 00 	mov    %eax,0xe98(%r15)
    7fb7657a6050:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fb7657a6056:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fb7657a605c:	85 c0                	test   %eax,%eax
    7fb7657a605e:	0f 84 1a 00 00 00    	je     0x7fb7657a607e
    7fb7657a6064:	41 c7 87 90 0e 00 00 	movl   $0x0,0xe90(%r15)
    7fb7657a606b:	00 00 00 00 
    7fb7657a606f:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7fb7657a6076:	00 00 00 
    7fb7657a6079:	e9 21 00 00 00       	jmpq   0x7fb7657a609f
    7fb7657a607e:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fb7657a6084:	85 c0                	test   %eax,%eax
    7fb7657a6086:	0f 84 13 00 00 00    	je     0x7fb7657a609f
    7fb7657a608c:	8b 85 d8 fb ff ff    	mov    -0x428(%rbp),%eax
    7fb7657a6092:	41 89 87 90 0e 00 00 	mov    %eax,0xe90(%r15)
    7fb7657a6099:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fb7657a609f:	45 85 ed             	test   %r13d,%r13d
    7fb7657a60a2:	0f 84 1a 00 00 00    	je     0x7fb7657a60c2
    7fb7657a60a8:	41 c7 87 88 0e 00 00 	movl   $0x0,0xe88(%r15)
    7fb7657a60af:	00 00 00 00 
    7fb7657a60b3:	c7 85 38 ff ff ff 00 	movl   $0x0,-0xc8(%rbp)
    7fb7657a60ba:	00 00 00 
    7fb7657a60bd:	e9 13 00 00 00       	jmpq   0x7fb7657a60d5
    7fb7657a60c2:	8b 85 e0 fb ff ff    	mov    -0x420(%rbp),%eax
    7fb7657a60c8:	41 89 87 88 0e 00 00 	mov    %eax,0xe88(%r15)
    7fb7657a60cf:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fb7657a60d5:	49 8b c7             	mov    %r15,%rax
    7fb7657a60d8:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7fb7657a60de:	49 8b cf             	mov    %r15,%rcx
    7fb7657a60e1:	48 81 c1 08 11 00 00 	add    $0x1108,%rcx
    7fb7657a60e8:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a60eb:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a60ee:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a60f2:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a60f6:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a60fa:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a60fe:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a6102:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a6106:	45 85 ed             	test   %r13d,%r13d
    7fb7657a6109:	0f 84 6f 00 00 00    	je     0x7fb7657a617e
    7fb7657a610f:	41 c7 87 40 0e 00 00 	movl   $0x0,0xe40(%r15)
    7fb7657a6116:	00 00 00 00 
    7fb7657a611a:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7fb7657a6121:	00 00 00 
    7fb7657a6124:	41 c7 87 38 0e 00 00 	movl   $0x0,0xe38(%r15)
    7fb7657a612b:	00 00 00 00 
    7fb7657a612f:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7fb7657a6136:	00 00 00 
    7fb7657a6139:	41 c7 87 30 0e 00 00 	movl   $0x0,0xe30(%r15)
    7fb7657a6140:	00 00 00 00 
    7fb7657a6144:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7fb7657a614b:	00 00 00 
    7fb7657a614e:	41 c7 87 28 0e 00 00 	movl   $0x0,0xe28(%r15)
    7fb7657a6155:	00 00 00 00 
    7fb7657a6159:	c7 85 58 ff ff ff 00 	movl   $0x0,-0xa8(%rbp)
    7fb7657a6160:	00 00 00 
    7fb7657a6163:	49 c7 87 20 0e 00 00 	movq   $0x0,0xe20(%r15)
    7fb7657a616a:	00 00 00 00 
    7fb7657a616e:	48 c7 85 60 ff ff ff 	movq   $0x0,-0xa0(%rbp)
    7fb7657a6175:	00 00 00 00 
    7fb7657a6179:	e9 61 00 00 00       	jmpq   0x7fb7657a61df
    7fb7657a617e:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fb7657a6184:	41 89 87 40 0e 00 00 	mov    %eax,0xe40(%r15)
    7fb7657a618b:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fb7657a6191:	8b 85 08 fc ff ff    	mov    -0x3f8(%rbp),%eax
    7fb7657a6197:	41 89 87 38 0e 00 00 	mov    %eax,0xe38(%r15)
    7fb7657a619e:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fb7657a61a4:	8b 85 20 fc ff ff    	mov    -0x3e0(%rbp),%eax
    7fb7657a61aa:	41 89 87 30 0e 00 00 	mov    %eax,0xe30(%r15)
    7fb7657a61b1:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7fb7657a61b7:	8b 85 30 fc ff ff    	mov    -0x3d0(%rbp),%eax
    7fb7657a61bd:	41 89 87 28 0e 00 00 	mov    %eax,0xe28(%r15)
    7fb7657a61c4:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fb7657a61ca:	48 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%rax
    7fb7657a61d1:	49 89 87 20 0e 00 00 	mov    %rax,0xe20(%r15)
    7fb7657a61d8:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
    7fb7657a61df:	49 8b c7             	mov    %r15,%rax
    7fb7657a61e2:	48 05 e0 0d 00 00    	add    $0xde0,%rax
    7fb7657a61e8:	49 8b cf             	mov    %r15,%rcx
    7fb7657a61eb:	48 81 c1 00 0c 00 00 	add    $0xc00,%rcx
    7fb7657a61f2:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a61f5:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a61f8:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a61fc:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a6200:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a6204:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a6208:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a620c:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a6210:	49 8b c7             	mov    %r15,%rax
    7fb7657a6213:	48 05 a0 0d 00 00    	add    $0xda0,%rax
    7fb7657a6219:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7fb7657a6220:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a6223:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a6226:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a622a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a622e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a6232:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a6236:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a623a:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a623e:	45 85 ed             	test   %r13d,%r13d
    7fb7657a6241:	0f 84 44 00 00 00    	je     0x7fb7657a628b
    7fb7657a6247:	41 c7 87 98 0d 00 00 	movl   $0x0,0xd98(%r15)
    7fb7657a624e:	00 00 00 00 
    7fb7657a6252:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7fb7657a6259:	00 00 00 
    7fb7657a625c:	41 c7 87 88 0d 00 00 	movl   $0x0,0xd88(%r15)
    7fb7657a6263:	00 00 00 00 
    7fb7657a6267:	c7 85 78 ff ff ff 00 	movl   $0x0,-0x88(%rbp)
    7fb7657a626e:	00 00 00 
    7fb7657a6271:	41 c7 87 90 0d 00 00 	movl   $0x1,0xd90(%r15)
    7fb7657a6278:	01 00 00 00 
    7fb7657a627c:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%rbp)
    7fb7657a6283:	00 00 00 
    7fb7657a6286:	e9 47 00 00 00       	jmpq   0x7fb7657a62d2
    7fb7657a628b:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7fb7657a6291:	41 89 87 98 0d 00 00 	mov    %eax,0xd98(%r15)
    7fb7657a6298:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fb7657a629e:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fb7657a62a4:	85 c0                	test   %eax,%eax
    7fb7657a62a6:	0f 84 26 00 00 00    	je     0x7fb7657a62d2
    7fb7657a62ac:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fb7657a62b2:	41 89 87 88 0d 00 00 	mov    %eax,0xd88(%r15)
    7fb7657a62b9:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fb7657a62bf:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7fb7657a62c5:	41 89 87 90 0d 00 00 	mov    %eax,0xd90(%r15)
    7fb7657a62cc:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fb7657a62d2:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fb7657a62d8:	85 c0                	test   %eax,%eax
    7fb7657a62da:	0f 84 17 00 00 00    	je     0x7fb7657a62f7
    7fb7657a62e0:	41 c7 87 80 0d 00 00 	movl   $0x0,0xd80(%r15)
    7fb7657a62e7:	00 00 00 00 
    7fb7657a62eb:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
    7fb7657a62f2:	e9 1e 00 00 00       	jmpq   0x7fb7657a6315
    7fb7657a62f7:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fb7657a62fd:	85 c0                	test   %eax,%eax
    7fb7657a62ff:	0f 84 10 00 00 00    	je     0x7fb7657a6315
    7fb7657a6305:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fb7657a630b:	41 89 87 80 0d 00 00 	mov    %eax,0xd80(%r15)
    7fb7657a6312:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fb7657a6315:	45 85 ed             	test   %r13d,%r13d
    7fb7657a6318:	0f 84 3b 00 00 00    	je     0x7fb7657a6359
    7fb7657a631e:	41 c7 87 78 0d 00 00 	movl   $0x0,0xd78(%r15)
    7fb7657a6325:	00 00 00 00 
    7fb7657a6329:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
    7fb7657a6330:	41 c7 87 70 0d 00 00 	movl   $0x1,0xd70(%r15)
    7fb7657a6337:	01 00 00 00 
    7fb7657a633b:	c7 45 90 01 00 00 00 	movl   $0x1,-0x70(%rbp)
    7fb7657a6342:	41 c7 87 68 0d 00 00 	movl   $0x0,0xd68(%r15)
    7fb7657a6349:	00 00 00 00 
    7fb7657a634d:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fb7657a6354:	e9 30 00 00 00       	jmpq   0x7fb7657a6389
    7fb7657a6359:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7fb7657a635f:	41 89 87 78 0d 00 00 	mov    %eax,0xd78(%r15)
    7fb7657a6366:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fb7657a6369:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7fb7657a636f:	41 89 87 70 0d 00 00 	mov    %eax,0xd70(%r15)
    7fb7657a6376:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fb7657a6379:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7fb7657a637f:	41 89 87 68 0d 00 00 	mov    %eax,0xd68(%r15)
    7fb7657a6386:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fb7657a6389:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fb7657a638f:	85 c0                	test   %eax,%eax
    7fb7657a6391:	0f 84 17 00 00 00    	je     0x7fb7657a63ae
    7fb7657a6397:	41 c7 87 60 0d 00 00 	movl   $0x0,0xd60(%r15)
    7fb7657a639e:	00 00 00 00 
    7fb7657a63a2:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7fb7657a63a9:	e9 1e 00 00 00       	jmpq   0x7fb7657a63cc
    7fb7657a63ae:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7fb7657a63b4:	85 c0                	test   %eax,%eax
    7fb7657a63b6:	0f 84 10 00 00 00    	je     0x7fb7657a63cc
    7fb7657a63bc:	8b 85 28 fd ff ff    	mov    -0x2d8(%rbp),%eax
    7fb7657a63c2:	41 89 87 60 0d 00 00 	mov    %eax,0xd60(%r15)
    7fb7657a63c9:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fb7657a63cc:	45 85 ed             	test   %r13d,%r13d
    7fb7657a63cf:	0f 84 17 00 00 00    	je     0x7fb7657a63ec
    7fb7657a63d5:	41 c7 87 58 0d 00 00 	movl   $0x0,0xd58(%r15)
    7fb7657a63dc:	00 00 00 00 
    7fb7657a63e0:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
    7fb7657a63e7:	e9 10 00 00 00       	jmpq   0x7fb7657a63fc
    7fb7657a63ec:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7fb7657a63f2:	41 89 87 58 0d 00 00 	mov    %eax,0xd58(%r15)
    7fb7657a63f9:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fb7657a63fc:	49 8b c7             	mov    %r15,%rax
    7fb7657a63ff:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7fb7657a6405:	49 8b cf             	mov    %r15,%rcx
    7fb7657a6408:	48 81 c1 88 10 00 00 	add    $0x1088,%rcx
    7fb7657a640f:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a6412:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a6415:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a6419:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a641d:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a6421:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a6425:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a6429:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a642d:	45 85 ed             	test   %r13d,%r13d
    7fb7657a6430:	0f 84 7d 00 00 00    	je     0x7fb7657a64b3
    7fb7657a6436:	41 c7 87 10 0d 00 00 	movl   $0x0,0xd10(%r15)
    7fb7657a643d:	00 00 00 00 
    7fb7657a6441:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7fb7657a6448:	41 c7 87 08 0d 00 00 	movl   $0x0,0xd08(%r15)
    7fb7657a644f:	00 00 00 00 
    7fb7657a6453:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7fb7657a645a:	41 c7 87 00 0d 00 00 	movl   $0x0,0xd00(%r15)
    7fb7657a6461:	00 00 00 00 
    7fb7657a6465:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    7fb7657a646c:	41 c7 87 f8 0c 00 00 	movl   $0x0,0xcf8(%r15)
    7fb7657a6473:	00 00 00 00 
    7fb7657a6477:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
    7fb7657a647e:	49 c7 87 f0 0c 00 00 	movq   $0x0,0xcf0(%r15)
    7fb7657a6485:	00 00 00 00 
    7fb7657a6489:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
    7fb7657a6490:	00 
    7fb7657a6491:	41 c7 87 e0 0c 00 00 	movl   $0x0,0xce0(%r15)
    7fb7657a6498:	00 00 00 00 
    7fb7657a649c:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7fb7657a64a3:	41 c7 87 e8 0c 00 00 	movl   $0x0,0xce8(%r15)
    7fb7657a64aa:	00 00 00 00 
    7fb7657a64ae:	e9 7e 00 00 00       	jmpq   0x7fb7657a6531
    7fb7657a64b3:	8b 85 50 fd ff ff    	mov    -0x2b0(%rbp),%eax
    7fb7657a64b9:	41 89 87 10 0d 00 00 	mov    %eax,0xd10(%r15)
    7fb7657a64c0:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fb7657a64c3:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7fb7657a64c9:	41 89 87 08 0d 00 00 	mov    %eax,0xd08(%r15)
    7fb7657a64d0:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fb7657a64d3:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fb7657a64d9:	41 89 87 00 0d 00 00 	mov    %eax,0xd00(%r15)
    7fb7657a64e0:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fb7657a64e3:	8b 85 a0 fd ff ff    	mov    -0x260(%rbp),%eax
    7fb7657a64e9:	41 89 87 f8 0c 00 00 	mov    %eax,0xcf8(%r15)
    7fb7657a64f0:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fb7657a64f3:	48 8b 85 f0 fd ff ff 	mov    -0x210(%rbp),%rax
    7fb7657a64fa:	49 89 87 f0 0c 00 00 	mov    %rax,0xcf0(%r15)
    7fb7657a6501:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    7fb7657a6505:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fb7657a650b:	85 c0                	test   %eax,%eax
    7fb7657a650d:	0f 84 1e 00 00 00    	je     0x7fb7657a6531
    7fb7657a6513:	41 8b 87 e8 0c 00 00 	mov    0xce8(%r15),%eax
    7fb7657a651a:	41 89 87 e0 0c 00 00 	mov    %eax,0xce0(%r15)
    7fb7657a6521:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fb7657a6524:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fb7657a652a:	41 89 87 e8 0c 00 00 	mov    %eax,0xce8(%r15)
    7fb7657a6531:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fb7657a6537:	85 c0                	test   %eax,%eax
    7fb7657a6539:	0f 84 1e 00 00 00    	je     0x7fb7657a655d
    7fb7657a653f:	41 8b 87 d8 0c 00 00 	mov    0xcd8(%r15),%eax
    7fb7657a6546:	41 89 87 d0 0c 00 00 	mov    %eax,0xcd0(%r15)
    7fb7657a654d:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fb7657a6550:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7fb7657a6556:	41 89 87 d8 0c 00 00 	mov    %eax,0xcd8(%r15)
    7fb7657a655d:	45 85 ed             	test   %r13d,%r13d
    7fb7657a6560:	0f 84 29 00 00 00    	je     0x7fb7657a658f
    7fb7657a6566:	41 c7 87 c8 0c 00 00 	movl   $0x0,0xcc8(%r15)
    7fb7657a656d:	00 00 00 00 
    7fb7657a6571:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
    7fb7657a6578:	41 c7 87 c0 0c 00 00 	movl   $0x0,0xcc0(%r15)
    7fb7657a657f:	00 00 00 00 
    7fb7657a6583:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7fb7657a658a:	e9 20 00 00 00       	jmpq   0x7fb7657a65af
    7fb7657a658f:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7fb7657a6595:	41 89 87 c8 0c 00 00 	mov    %eax,0xcc8(%r15)
    7fb7657a659c:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fb7657a659f:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7fb7657a65a5:	41 89 87 c0 0c 00 00 	mov    %eax,0xcc0(%r15)
    7fb7657a65ac:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fb7657a65af:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7fb7657a65b2:	85 c9                	test   %ecx,%ecx
    7fb7657a65b4:	0f 94 c0             	sete   %al
    7fb7657a65b7:	0f b6 c0             	movzbl %al,%eax
    7fb7657a65ba:	49 8b 96 a0 00 00 00 	mov    0xa0(%r14),%rdx
    7fb7657a65c1:	89 02                	mov    %eax,(%rdx)
    7fb7657a65c3:	83 f9 02             	cmp    $0x2,%ecx
    7fb7657a65c6:	0f 94 c1             	sete   %cl
    7fb7657a65c9:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a65cc:	8b c1                	mov    %ecx,%eax
    7fb7657a65ce:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7fb7657a65d4:	85 c9                	test   %ecx,%ecx
    7fb7657a65d6:	0f 94 c1             	sete   %cl
    7fb7657a65d9:	0f b6 c9             	movzbl %cl,%ecx
    7fb7657a65dc:	23 c1                	and    %ecx,%eax
    7fb7657a65de:	49 8b 8e a8 00 00 00 	mov    0xa8(%r14),%rcx
    7fb7657a65e5:	89 01                	mov    %eax,(%rcx)
    7fb7657a65e7:	49 8b 86 b0 00 00 00 	mov    0xb0(%r14),%rax
    7fb7657a65ee:	48 8b 8d f0 fe ff ff 	mov    -0x110(%rbp),%rcx
    7fb7657a65f5:	48 89 08             	mov    %rcx,(%rax)
    7fb7657a65f8:	49 8b 86 b8 00 00 00 	mov    0xb8(%r14),%rax
    7fb7657a65ff:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7fb7657a6605:	49 8b 86 c0 00 00 00 	mov    0xc0(%r14),%rax
    7fb7657a660c:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7fb7657a6612:	89 08                	mov    %ecx,(%rax)
    7fb7657a6614:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7fb7657a661a:	85 c0                	test   %eax,%eax
    7fb7657a661c:	0f 85 36 00 00 00    	jne    0x7fb7657a6658
    7fb7657a6622:	49 8b c7             	mov    %r15,%rax
    7fb7657a6625:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7fb7657a662b:	49 8b cf             	mov    %r15,%rcx
    7fb7657a662e:	48 81 c1 48 10 00 00 	add    $0x1048,%rcx
    7fb7657a6635:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a6638:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a663b:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a663f:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a6643:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a6647:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a664b:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a664f:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a6653:	e9 31 00 00 00       	jmpq   0x7fb7657a6689
    7fb7657a6658:	49 8b c7             	mov    %r15,%rax
    7fb7657a665b:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7fb7657a6661:	49 8b cf             	mov    %r15,%rcx
    7fb7657a6664:	48 81 c1 08 10 00 00 	add    $0x1008,%rcx
    7fb7657a666b:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a666e:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a6671:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a6675:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a6679:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a667d:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a6681:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a6685:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a6689:	49 8b 86 c8 00 00 00 	mov    0xc8(%r14),%rax
    7fb7657a6690:	49 8b cf             	mov    %r15,%rcx
    7fb7657a6693:	48 81 c1 c8 11 00 00 	add    $0x11c8,%rcx
    7fb7657a669a:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a669d:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a66a0:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a66a4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a66a8:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a66ac:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a66b0:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a66b4:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a66b8:	49 8b 86 d0 00 00 00 	mov    0xd0(%r14),%rax
    7fb7657a66bf:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7fb7657a66c6:	49 8b 86 d8 00 00 00 	mov    0xd8(%r14),%rax
    7fb7657a66cd:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7fb7657a66d3:	89 08                	mov    %ecx,(%rax)
    7fb7657a66d5:	49 8b 86 e0 00 00 00 	mov    0xe0(%r14),%rax
    7fb7657a66dc:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
    7fb7657a66e0:	48 89 08             	mov    %rcx,(%rax)
    7fb7657a66e3:	49 8b 86 e8 00 00 00 	mov    0xe8(%r14),%rax
    7fb7657a66ea:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fb7657a66ed:	89 08                	mov    %ecx,(%rax)
    7fb7657a66ef:	49 8b 86 f0 00 00 00 	mov    0xf0(%r14),%rax
    7fb7657a66f6:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7fb7657a66fc:	49 8b 86 f8 00 00 00 	mov    0xf8(%r14),%rax
    7fb7657a6703:	49 8b cf             	mov    %r15,%rcx
    7fb7657a6706:	48 81 c1 50 13 00 00 	add    $0x1350,%rcx
    7fb7657a670d:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a6710:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a6713:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a6717:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a671b:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a671f:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a6723:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a6727:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a672b:	49 8b 86 00 01 00 00 	mov    0x100(%r14),%rax
    7fb7657a6732:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7fb7657a6739:	49 8b 86 08 01 00 00 	mov    0x108(%r14),%rax
    7fb7657a6740:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7fb7657a6743:	89 08                	mov    %ecx,(%rax)
    7fb7657a6745:	49 8b 86 10 01 00 00 	mov    0x110(%r14),%rax
    7fb7657a674c:	48 8b 8d 60 ff ff ff 	mov    -0xa0(%rbp),%rcx
    7fb7657a6753:	48 89 08             	mov    %rcx,(%rax)
    7fb7657a6756:	49 8b 86 18 01 00 00 	mov    0x118(%r14),%rax
    7fb7657a675d:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7fb7657a6763:	89 08                	mov    %ecx,(%rax)
    7fb7657a6765:	49 8b 86 20 01 00 00 	mov    0x120(%r14),%rax
    7fb7657a676c:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7fb7657a6772:	49 8b 86 28 01 00 00 	mov    0x128(%r14),%rax
    7fb7657a6779:	49 8b cf             	mov    %r15,%rcx
    7fb7657a677c:	48 81 c1 50 13 00 00 	add    $0x1350,%rcx
    7fb7657a6783:	0f 10 01             	movups (%rcx),%xmm0
    7fb7657a6786:	0f 11 00             	movups %xmm0,(%rax)
    7fb7657a6789:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fb7657a678d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fb7657a6791:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fb7657a6795:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fb7657a6799:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fb7657a679d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fb7657a67a1:	49 8b 86 30 01 00 00 	mov    0x130(%r14),%rax
    7fb7657a67a8:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7fb7657a67af:	49 8b 86 38 01 00 00 	mov    0x138(%r14),%rax
    7fb7657a67b6:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7fb7657a67bc:	89 08                	mov    %ecx,(%rax)
    7fb7657a67be:	33 c0                	xor    %eax,%eax
    7fb7657a67c0:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fb7657a67c4:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fb7657a67c9:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fb7657a67ce:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fb7657a67d3:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fb7657a67d8:	48 8b e5             	mov    %rbp,%rsp
    7fb7657a67db:	5d                   	pop    %rbp
    7fb7657a67dc:	c3                   	retq   

end

