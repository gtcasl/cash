function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f3a6b46712d <.text>:
    7f3a6b46712d:	55                   	push   %rbp
    7f3a6b46712e:	48 8b ec             	mov    %rsp,%rbp
    7f3a6b467131:	48 81 ec 80 02 00 00 	sub    $0x280,%rsp
    7f3a6b467138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f3a6b46713c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f3a6b467141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f3a6b467146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f3a6b46714b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f3a6b467150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f3a6b467154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f3a6b467158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f3a6b46715c:	4c 8b 30             	mov    (%rax),%r14
    7f3a6b46715f:	45 8b 2f             	mov    (%r15),%r13d
    7f3a6b467162:	41 8b 47 08          	mov    0x8(%r15),%eax
    7f3a6b467166:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f3a6b467169:	41 8b 47 10          	mov    0x10(%r15),%eax
    7f3a6b46716d:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f3a6b467170:	41 8b 47 20          	mov    0x20(%r15),%eax
    7f3a6b467174:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f3a6b467177:	41 8b 47 30          	mov    0x30(%r15),%eax
    7f3a6b46717b:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7f3a6b46717e:	41 8b 47 38          	mov    0x38(%r15),%eax
    7f3a6b467182:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f3a6b467185:	41 8b 47 48          	mov    0x48(%r15),%eax
    7f3a6b467189:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f3a6b46718c:	41 8b 47 58          	mov    0x58(%r15),%eax
    7f3a6b467190:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f3a6b467193:	41 8b 47 60          	mov    0x60(%r15),%eax
    7f3a6b467197:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f3a6b46719a:	41 8b 47 68          	mov    0x68(%r15),%eax
    7f3a6b46719e:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f3a6b4671a1:	41 8b 47 70          	mov    0x70(%r15),%eax
    7f3a6b4671a5:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f3a6b4671a8:	41 8b 47 78          	mov    0x78(%r15),%eax
    7f3a6b4671ac:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f3a6b4671af:	41 8b 87 80 00 00 00 	mov    0x80(%r15),%eax
    7f3a6b4671b6:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f3a6b4671b9:	41 8b 87 88 00 00 00 	mov    0x88(%r15),%eax
    7f3a6b4671c0:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f3a6b4671c3:	41 8b 87 90 00 00 00 	mov    0x90(%r15),%eax
    7f3a6b4671ca:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f3a6b4671cd:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7f3a6b4671d4:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f3a6b4671d7:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7f3a6b4671de:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f3a6b4671e4:	41 8b 87 a8 00 00 00 	mov    0xa8(%r15),%eax
    7f3a6b4671eb:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f3a6b4671f1:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7f3a6b4671f8:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f3a6b4671fe:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7f3a6b467205:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f3a6b46720b:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7f3a6b467212:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f3a6b467218:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7f3a6b46721f:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f3a6b467225:	45 8b a7 d0 00 00 00 	mov    0xd0(%r15),%r12d
    7f3a6b46722c:	41 8b 9f d8 00 00 00 	mov    0xd8(%r15),%ebx
    7f3a6b467233:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7f3a6b46723a:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f3a6b467240:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7f3a6b467247:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f3a6b46724d:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7f3a6b467254:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f3a6b46725a:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7f3a6b467261:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f3a6b467267:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7f3a6b46726e:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f3a6b467274:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7f3a6b46727b:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f3a6b467281:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7f3a6b467288:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f3a6b46728e:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7f3a6b467295:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f3a6b46729b:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7f3a6b4672a2:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f3a6b4672a8:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7f3a6b4672af:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f3a6b4672b5:	41 8b 87 30 01 00 00 	mov    0x130(%r15),%eax
    7f3a6b4672bc:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7f3a6b4672c2:	41 8b 87 38 01 00 00 	mov    0x138(%r15),%eax
    7f3a6b4672c9:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f3a6b4672cf:	41 8b 87 40 01 00 00 	mov    0x140(%r15),%eax
    7f3a6b4672d6:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f3a6b4672dc:	41 8b 87 48 01 00 00 	mov    0x148(%r15),%eax
    7f3a6b4672e3:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f3a6b4672e9:	41 8b 87 50 01 00 00 	mov    0x150(%r15),%eax
    7f3a6b4672f0:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f3a6b4672f6:	41 8b 87 58 01 00 00 	mov    0x158(%r15),%eax
    7f3a6b4672fd:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f3a6b467303:	41 8b 87 60 01 00 00 	mov    0x160(%r15),%eax
    7f3a6b46730a:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f3a6b467310:	41 8b 87 68 01 00 00 	mov    0x168(%r15),%eax
    7f3a6b467317:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f3a6b46731d:	41 8b 87 70 01 00 00 	mov    0x170(%r15),%eax
    7f3a6b467324:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f3a6b46732a:	41 8b 87 78 01 00 00 	mov    0x178(%r15),%eax
    7f3a6b467331:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f3a6b467337:	41 8b 87 80 01 00 00 	mov    0x180(%r15),%eax
    7f3a6b46733e:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f3a6b467344:	41 8b 87 88 01 00 00 	mov    0x188(%r15),%eax
    7f3a6b46734b:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f3a6b467351:	41 8b 87 90 01 00 00 	mov    0x190(%r15),%eax
    7f3a6b467358:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f3a6b46735e:	41 8b 87 98 01 00 00 	mov    0x198(%r15),%eax
    7f3a6b467365:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f3a6b46736b:	49 8b 46 18          	mov    0x18(%r14),%rax
    7f3a6b46736f:	8b 00                	mov    (%rax),%eax
    7f3a6b467371:	41 8b 8f d0 01 00 00 	mov    0x1d0(%r15),%ecx
    7f3a6b467378:	33 c8                	xor    %eax,%ecx
    7f3a6b46737a:	23 c8                	and    %eax,%ecx
    7f3a6b46737c:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7f3a6b467383:	85 c9                	test   %ecx,%ecx
    7f3a6b467385:	0f 84 72 0c 00 00    	je     0x7f3a6b467ffd
    7f3a6b46738b:	41 83 fd 0b          	cmp    $0xb,%r13d
    7f3a6b46738f:	0f 93 c0             	setae  %al
    7f3a6b467392:	0f b6 c0             	movzbl %al,%eax
    7f3a6b467395:	41 8b cd             	mov    %r13d,%ecx
    7f3a6b467398:	83 e9 0b             	sub    $0xb,%ecx
    7f3a6b46739b:	83 e1 0f             	and    $0xf,%ecx
    7f3a6b46739e:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7f3a6b4673a4:	41 8b cd             	mov    %r13d,%ecx
    7f3a6b4673a7:	ff c1                	inc    %ecx
    7f3a6b4673a9:	83 e1 0f             	and    $0xf,%ecx
    7f3a6b4673ac:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7f3a6b4673b2:	85 c0                	test   %eax,%eax
    7f3a6b4673b4:	0f 85 0c 00 00 00    	jne    0x7f3a6b4673c6
    7f3a6b4673ba:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7f3a6b4673c0:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7f3a6b4673c6:	49 8b 46 20          	mov    0x20(%r14),%rax
    7f3a6b4673ca:	8b 00                	mov    (%rax),%eax
    7f3a6b4673cc:	8b c8                	mov    %eax,%ecx
    7f3a6b4673ce:	83 c9 00             	or     $0x0,%ecx
    7f3a6b4673d1:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7f3a6b4673d7:	49 8b 0e             	mov    (%r14),%rcx
    7f3a6b4673da:	8b 09                	mov    (%rcx),%ecx
    7f3a6b4673dc:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7f3a6b4673e2:	49 8b 4e 10          	mov    0x10(%r14),%rcx
    7f3a6b4673e6:	8b 09                	mov    (%rcx),%ecx
    7f3a6b4673e8:	8b d1                	mov    %ecx,%edx
    7f3a6b4673ea:	c1 ea 08             	shr    $0x8,%edx
    7f3a6b4673ed:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f3a6b4673f3:	89 95 68 fe ff ff    	mov    %edx,-0x198(%rbp)
    7f3a6b4673f9:	8b d1                	mov    %ecx,%edx
    7f3a6b4673fb:	c1 ea 10             	shr    $0x10,%edx
    7f3a6b4673fe:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f3a6b467404:	89 95 60 fe ff ff    	mov    %edx,-0x1a0(%rbp)
    7f3a6b46740a:	8b d1                	mov    %ecx,%edx
    7f3a6b46740c:	c1 ea 18             	shr    $0x18,%edx
    7f3a6b46740f:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f3a6b467415:	89 95 58 fe ff ff    	mov    %edx,-0x1a8(%rbp)
    7f3a6b46741b:	49 8b 56 08          	mov    0x8(%r14),%rdx
    7f3a6b46741f:	8b 12                	mov    (%rdx),%edx
    7f3a6b467421:	8b f2                	mov    %edx,%esi
    7f3a6b467423:	c1 ee 08             	shr    $0x8,%esi
    7f3a6b467426:	81 e6 ff 00 00 00    	and    $0xff,%esi
    7f3a6b46742c:	89 b5 50 fe ff ff    	mov    %esi,-0x1b0(%rbp)
    7f3a6b467432:	8b f2                	mov    %edx,%esi
    7f3a6b467434:	c1 ee 10             	shr    $0x10,%esi
    7f3a6b467437:	81 e6 ff 00 00 00    	and    $0xff,%esi
    7f3a6b46743d:	89 b5 48 fe ff ff    	mov    %esi,-0x1b8(%rbp)
    7f3a6b467443:	8b f2                	mov    %edx,%esi
    7f3a6b467445:	c1 ee 18             	shr    $0x18,%esi
    7f3a6b467448:	81 e6 ff 00 00 00    	and    $0xff,%esi
    7f3a6b46744e:	89 b5 40 fe ff ff    	mov    %esi,-0x1c0(%rbp)
    7f3a6b467454:	41 83 fd 0b          	cmp    $0xb,%r13d
    7f3a6b467458:	40 0f 94 c6          	sete   %sil
    7f3a6b46745c:	40 0f b6 f6          	movzbl %sil,%esi
    7f3a6b467460:	89 b5 38 fe ff ff    	mov    %esi,-0x1c8(%rbp)
    7f3a6b467466:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f3a6b46746c:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f3a6b467472:	89 95 30 fe ff ff    	mov    %edx,-0x1d0(%rbp)
    7f3a6b467478:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46747b:	0f be d2             	movsbl %dl,%edx
    7f3a6b46747e:	89 8d 28 fe ff ff    	mov    %ecx,-0x1d8(%rbp)
    7f3a6b467484:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b467487:	0f be c9             	movsbl %cl,%ecx
    7f3a6b46748a:	0f af d1             	imul   %ecx,%edx
    7f3a6b46748d:	81 e2 ff ff ff 00    	and    $0xffffff,%edx
    7f3a6b467493:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7f3a6b467496:	03 d1                	add    %ecx,%edx
    7f3a6b467498:	81 e2 ff ff ff 00    	and    $0xffffff,%edx
    7f3a6b46749e:	89 95 20 fe ff ff    	mov    %edx,-0x1e0(%rbp)
    7f3a6b4674a4:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7f3a6b4674a7:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b4674aa:	0f be c9             	movsbl %cl,%ecx
    7f3a6b4674ad:	8b 55 f0             	mov    -0x10(%rbp),%edx
    7f3a6b4674b0:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b4674b3:	0f be d2             	movsbl %dl,%edx
    7f3a6b4674b6:	0f af ca             	imul   %edx,%ecx
    7f3a6b4674b9:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4674bf:	8b 55 90             	mov    -0x70(%rbp),%edx
    7f3a6b4674c2:	03 ca                	add    %edx,%ecx
    7f3a6b4674c4:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4674ca:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7f3a6b4674d0:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7f3a6b4674d3:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b4674d6:	0f be c9             	movsbl %cl,%ecx
    7f3a6b4674d9:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f3a6b4674dc:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b4674df:	0f be d2             	movsbl %dl,%edx
    7f3a6b4674e2:	0f af ca             	imul   %edx,%ecx
    7f3a6b4674e5:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4674eb:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7f3a6b4674f1:	03 ca                	add    %edx,%ecx
    7f3a6b4674f3:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4674f9:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7f3a6b4674ff:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7f3a6b467502:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b467505:	0f be c9             	movsbl %cl,%ecx
    7f3a6b467508:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7f3a6b46750b:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46750e:	0f be d2             	movsbl %dl,%edx
    7f3a6b467511:	0f af ca             	imul   %edx,%ecx
    7f3a6b467514:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46751a:	8b 95 68 ff ff ff    	mov    -0x98(%rbp),%edx
    7f3a6b467520:	03 ca                	add    %edx,%ecx
    7f3a6b467522:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467528:	89 8d 08 fe ff ff    	mov    %ecx,-0x1f8(%rbp)
    7f3a6b46752e:	8b 4d d8             	mov    -0x28(%rbp),%ecx
    7f3a6b467531:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b467534:	0f be c9             	movsbl %cl,%ecx
    7f3a6b467537:	8b 55 b0             	mov    -0x50(%rbp),%edx
    7f3a6b46753a:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46753d:	0f be d2             	movsbl %dl,%edx
    7f3a6b467540:	0f af ca             	imul   %edx,%ecx
    7f3a6b467543:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467549:	8b 95 50 ff ff ff    	mov    -0xb0(%rbp),%edx
    7f3a6b46754f:	03 ca                	add    %edx,%ecx
    7f3a6b467551:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467557:	89 8d 00 fe ff ff    	mov    %ecx,-0x200(%rbp)
    7f3a6b46755d:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7f3a6b467563:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b467566:	0f be c9             	movsbl %cl,%ecx
    7f3a6b467569:	8b 55 98             	mov    -0x68(%rbp),%edx
    7f3a6b46756c:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46756f:	0f be d2             	movsbl %dl,%edx
    7f3a6b467572:	0f af ca             	imul   %edx,%ecx
    7f3a6b467575:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46757b:	8b 95 48 ff ff ff    	mov    -0xb8(%rbp),%edx
    7f3a6b467581:	03 ca                	add    %edx,%ecx
    7f3a6b467583:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467589:	89 8d f8 fd ff ff    	mov    %ecx,-0x208(%rbp)
    7f3a6b46758f:	41 0f b6 cc          	movzbl %r12b,%ecx
    7f3a6b467593:	0f be c9             	movsbl %cl,%ecx
    7f3a6b467596:	8b 55 80             	mov    -0x80(%rbp),%edx
    7f3a6b467599:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46759c:	0f be d2             	movsbl %dl,%edx
    7f3a6b46759f:	0f af ca             	imul   %edx,%ecx
    7f3a6b4675a2:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4675a8:	8b 95 30 ff ff ff    	mov    -0xd0(%rbp),%edx
    7f3a6b4675ae:	03 ca                	add    %edx,%ecx
    7f3a6b4675b0:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4675b6:	89 8d f0 fd ff ff    	mov    %ecx,-0x210(%rbp)
    7f3a6b4675bc:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7f3a6b4675c2:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b4675c5:	0f be c9             	movsbl %cl,%ecx
    7f3a6b4675c8:	8b 95 70 ff ff ff    	mov    -0x90(%rbp),%edx
    7f3a6b4675ce:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b4675d1:	0f be d2             	movsbl %dl,%edx
    7f3a6b4675d4:	0f af ca             	imul   %edx,%ecx
    7f3a6b4675d7:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4675dd:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7f3a6b4675e3:	03 ca                	add    %edx,%ecx
    7f3a6b4675e5:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4675eb:	89 8d e8 fd ff ff    	mov    %ecx,-0x218(%rbp)
    7f3a6b4675f1:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7f3a6b4675f4:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b4675f7:	0f be c9             	movsbl %cl,%ecx
    7f3a6b4675fa:	8b 95 58 ff ff ff    	mov    -0xa8(%rbp),%edx
    7f3a6b467600:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b467603:	0f be d2             	movsbl %dl,%edx
    7f3a6b467606:	0f af ca             	imul   %edx,%ecx
    7f3a6b467609:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46760f:	8b 95 08 ff ff ff    	mov    -0xf8(%rbp),%edx
    7f3a6b467615:	03 ca                	add    %edx,%ecx
    7f3a6b467617:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46761d:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7f3a6b467623:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7f3a6b467629:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b46762c:	0f be c9             	movsbl %cl,%ecx
    7f3a6b46762f:	0f b6 d3             	movzbl %bl,%edx
    7f3a6b467632:	0f be d2             	movsbl %dl,%edx
    7f3a6b467635:	0f af ca             	imul   %edx,%ecx
    7f3a6b467638:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46763e:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7f3a6b467644:	03 ca                	add    %edx,%ecx
    7f3a6b467646:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46764c:	89 8d d8 fd ff ff    	mov    %ecx,-0x228(%rbp)
    7f3a6b467652:	8b 8d 00 ff ff ff    	mov    -0x100(%rbp),%ecx
    7f3a6b467658:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b46765b:	0f be c9             	movsbl %cl,%ecx
    7f3a6b46765e:	8b 95 38 ff ff ff    	mov    -0xc8(%rbp),%edx
    7f3a6b467664:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b467667:	0f be d2             	movsbl %dl,%edx
    7f3a6b46766a:	0f af ca             	imul   %edx,%ecx
    7f3a6b46766d:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467673:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7f3a6b467679:	03 ca                	add    %edx,%ecx
    7f3a6b46767b:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467681:	89 8d d0 fd ff ff    	mov    %ecx,-0x230(%rbp)
    7f3a6b467687:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7f3a6b46768d:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b467690:	0f be c9             	movsbl %cl,%ecx
    7f3a6b467693:	8b 95 28 ff ff ff    	mov    -0xd8(%rbp),%edx
    7f3a6b467699:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46769c:	0f be d2             	movsbl %dl,%edx
    7f3a6b46769f:	0f af ca             	imul   %edx,%ecx
    7f3a6b4676a2:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4676a8:	8b 95 c8 fe ff ff    	mov    -0x138(%rbp),%edx
    7f3a6b4676ae:	03 ca                	add    %edx,%ecx
    7f3a6b4676b0:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4676b6:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7f3a6b4676bc:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7f3a6b4676bf:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b4676c2:	0f be c9             	movsbl %cl,%ecx
    7f3a6b4676c5:	8b 95 10 ff ff ff    	mov    -0xf0(%rbp),%edx
    7f3a6b4676cb:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b4676ce:	0f be d2             	movsbl %dl,%edx
    7f3a6b4676d1:	0f af ca             	imul   %edx,%ecx
    7f3a6b4676d4:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4676da:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7f3a6b4676e0:	03 ca                	add    %edx,%ecx
    7f3a6b4676e2:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b4676e8:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7f3a6b4676ee:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7f3a6b4676f4:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b4676f7:	0f be c9             	movsbl %cl,%ecx
    7f3a6b4676fa:	8b 95 f8 fe ff ff    	mov    -0x108(%rbp),%edx
    7f3a6b467700:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b467703:	0f be d2             	movsbl %dl,%edx
    7f3a6b467706:	0f af ca             	imul   %edx,%ecx
    7f3a6b467709:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46770f:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7f3a6b467715:	03 ca                	add    %edx,%ecx
    7f3a6b467717:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b46771d:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7f3a6b467723:	8b 8d b0 fe ff ff    	mov    -0x150(%rbp),%ecx
    7f3a6b467729:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b46772c:	0f be c9             	movsbl %cl,%ecx
    7f3a6b46772f:	8b 95 e0 fe ff ff    	mov    -0x120(%rbp),%edx
    7f3a6b467735:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b467738:	0f be d2             	movsbl %dl,%edx
    7f3a6b46773b:	0f af ca             	imul   %edx,%ecx
    7f3a6b46773e:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467744:	8b 95 98 fe ff ff    	mov    -0x168(%rbp),%edx
    7f3a6b46774a:	03 ca                	add    %edx,%ecx
    7f3a6b46774c:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467752:	89 8d b0 fd ff ff    	mov    %ecx,-0x250(%rbp)
    7f3a6b467758:	8b 8d a0 fe ff ff    	mov    -0x160(%rbp),%ecx
    7f3a6b46775e:	0f b6 c9             	movzbl %cl,%ecx
    7f3a6b467761:	0f be c9             	movsbl %cl,%ecx
    7f3a6b467764:	8b 95 d0 fe ff ff    	mov    -0x130(%rbp),%edx
    7f3a6b46776a:	0f b6 d2             	movzbl %dl,%edx
    7f3a6b46776d:	0f be d2             	movsbl %dl,%edx
    7f3a6b467770:	0f af ca             	imul   %edx,%ecx
    7f3a6b467773:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467779:	8b 95 90 fe ff ff    	mov    -0x170(%rbp),%edx
    7f3a6b46777f:	03 ca                	add    %edx,%ecx
    7f3a6b467781:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7f3a6b467787:	89 8d a8 fd ff ff    	mov    %ecx,-0x258(%rbp)
    7f3a6b46778d:	85 c0                	test   %eax,%eax
    7f3a6b46778f:	0f 84 a3 03 00 00    	je     0x7f3a6b467b38
    7f3a6b467795:	41 c7 87 98 01 00 00 	movl   $0x0,0x198(%r15)
    7f3a6b46779c:	00 00 00 00 
    7f3a6b4677a0:	c7 85 90 fe ff ff 00 	movl   $0x0,-0x170(%rbp)
    7f3a6b4677a7:	00 00 00 
    7f3a6b4677aa:	41 c7 87 90 01 00 00 	movl   $0x0,0x190(%r15)
    7f3a6b4677b1:	00 00 00 00 
    7f3a6b4677b5:	c7 85 98 fe ff ff 00 	movl   $0x0,-0x168(%rbp)
    7f3a6b4677bc:	00 00 00 
    7f3a6b4677bf:	41 c7 87 88 01 00 00 	movl   $0x0,0x188(%r15)
    7f3a6b4677c6:	00 00 00 00 
    7f3a6b4677ca:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7f3a6b4677d1:	00 00 00 
    7f3a6b4677d4:	41 c7 87 80 01 00 00 	movl   $0x0,0x180(%r15)
    7f3a6b4677db:	00 00 00 00 
    7f3a6b4677df:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7f3a6b4677e6:	00 00 00 
    7f3a6b4677e9:	41 c7 87 78 01 00 00 	movl   $0x0,0x178(%r15)
    7f3a6b4677f0:	00 00 00 00 
    7f3a6b4677f4:	c7 85 b0 fe ff ff 00 	movl   $0x0,-0x150(%rbp)
    7f3a6b4677fb:	00 00 00 
    7f3a6b4677fe:	41 c7 87 70 01 00 00 	movl   $0x0,0x170(%r15)
    7f3a6b467805:	00 00 00 00 
    7f3a6b467809:	c7 85 b8 fe ff ff 00 	movl   $0x0,-0x148(%rbp)
    7f3a6b467810:	00 00 00 
    7f3a6b467813:	41 c7 87 68 01 00 00 	movl   $0x0,0x168(%r15)
    7f3a6b46781a:	00 00 00 00 
    7f3a6b46781e:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7f3a6b467825:	00 00 00 
    7f3a6b467828:	41 c7 87 60 01 00 00 	movl   $0x0,0x160(%r15)
    7f3a6b46782f:	00 00 00 00 
    7f3a6b467833:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7f3a6b46783a:	00 00 00 
    7f3a6b46783d:	41 c7 87 58 01 00 00 	movl   $0x0,0x158(%r15)
    7f3a6b467844:	00 00 00 00 
    7f3a6b467848:	c7 85 d0 fe ff ff 00 	movl   $0x0,-0x130(%rbp)
    7f3a6b46784f:	00 00 00 
    7f3a6b467852:	41 c7 87 50 01 00 00 	movl   $0x0,0x150(%r15)
    7f3a6b467859:	00 00 00 00 
    7f3a6b46785d:	c7 85 d8 fe ff ff 00 	movl   $0x0,-0x128(%rbp)
    7f3a6b467864:	00 00 00 
    7f3a6b467867:	41 c7 87 48 01 00 00 	movl   $0x0,0x148(%r15)
    7f3a6b46786e:	00 00 00 00 
    7f3a6b467872:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7f3a6b467879:	00 00 00 
    7f3a6b46787c:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7f3a6b467883:	00 00 00 00 
    7f3a6b467887:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7f3a6b46788e:	00 00 00 
    7f3a6b467891:	41 c7 87 38 01 00 00 	movl   $0x0,0x138(%r15)
    7f3a6b467898:	00 00 00 00 
    7f3a6b46789c:	c7 85 f0 fe ff ff 00 	movl   $0x0,-0x110(%rbp)
    7f3a6b4678a3:	00 00 00 
    7f3a6b4678a6:	41 c7 87 30 01 00 00 	movl   $0x0,0x130(%r15)
    7f3a6b4678ad:	00 00 00 00 
    7f3a6b4678b1:	c7 85 f8 fe ff ff 00 	movl   $0x0,-0x108(%rbp)
    7f3a6b4678b8:	00 00 00 
    7f3a6b4678bb:	41 c7 87 28 01 00 00 	movl   $0x0,0x128(%r15)
    7f3a6b4678c2:	00 00 00 00 
    7f3a6b4678c6:	c7 85 00 ff ff ff 00 	movl   $0x0,-0x100(%rbp)
    7f3a6b4678cd:	00 00 00 
    7f3a6b4678d0:	41 c7 87 20 01 00 00 	movl   $0x0,0x120(%r15)
    7f3a6b4678d7:	00 00 00 00 
    7f3a6b4678db:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7f3a6b4678e2:	00 00 00 
    7f3a6b4678e5:	41 c7 87 18 01 00 00 	movl   $0x0,0x118(%r15)
    7f3a6b4678ec:	00 00 00 00 
    7f3a6b4678f0:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7f3a6b4678f7:	00 00 00 
    7f3a6b4678fa:	41 c7 87 10 01 00 00 	movl   $0x0,0x110(%r15)
    7f3a6b467901:	00 00 00 00 
    7f3a6b467905:	c7 85 18 ff ff ff 00 	movl   $0x0,-0xe8(%rbp)
    7f3a6b46790c:	00 00 00 
    7f3a6b46790f:	41 c7 87 08 01 00 00 	movl   $0x0,0x108(%r15)
    7f3a6b467916:	00 00 00 00 
    7f3a6b46791a:	c7 85 20 ff ff ff 00 	movl   $0x0,-0xe0(%rbp)
    7f3a6b467921:	00 00 00 
    7f3a6b467924:	41 c7 87 00 01 00 00 	movl   $0x0,0x100(%r15)
    7f3a6b46792b:	00 00 00 00 
    7f3a6b46792f:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7f3a6b467936:	00 00 00 
    7f3a6b467939:	41 c7 87 f8 00 00 00 	movl   $0x0,0xf8(%r15)
    7f3a6b467940:	00 00 00 00 
    7f3a6b467944:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7f3a6b46794b:	00 00 00 
    7f3a6b46794e:	41 c7 87 f0 00 00 00 	movl   $0x0,0xf0(%r15)
    7f3a6b467955:	00 00 00 00 
    7f3a6b467959:	c7 85 38 ff ff ff 00 	movl   $0x0,-0xc8(%rbp)
    7f3a6b467960:	00 00 00 
    7f3a6b467963:	41 c7 87 e8 00 00 00 	movl   $0x0,0xe8(%r15)
    7f3a6b46796a:	00 00 00 00 
    7f3a6b46796e:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7f3a6b467975:	00 00 00 
    7f3a6b467978:	41 c7 87 e0 00 00 00 	movl   $0x0,0xe0(%r15)
    7f3a6b46797f:	00 00 00 00 
    7f3a6b467983:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7f3a6b46798a:	00 00 00 
    7f3a6b46798d:	41 c7 87 d8 00 00 00 	movl   $0x0,0xd8(%r15)
    7f3a6b467994:	00 00 00 00 
    7f3a6b467998:	33 db                	xor    %ebx,%ebx
    7f3a6b46799a:	41 c7 87 d0 00 00 00 	movl   $0x0,0xd0(%r15)
    7f3a6b4679a1:	00 00 00 00 
    7f3a6b4679a5:	45 33 e4             	xor    %r12d,%r12d
    7f3a6b4679a8:	41 c7 87 c8 00 00 00 	movl   $0x0,0xc8(%r15)
    7f3a6b4679af:	00 00 00 00 
    7f3a6b4679b3:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7f3a6b4679ba:	00 00 00 
    7f3a6b4679bd:	41 c7 87 c0 00 00 00 	movl   $0x0,0xc0(%r15)
    7f3a6b4679c4:	00 00 00 00 
    7f3a6b4679c8:	c7 85 58 ff ff ff 00 	movl   $0x0,-0xa8(%rbp)
    7f3a6b4679cf:	00 00 00 
    7f3a6b4679d2:	41 c7 87 b8 00 00 00 	movl   $0x0,0xb8(%r15)
    7f3a6b4679d9:	00 00 00 00 
    7f3a6b4679dd:	c7 85 60 ff ff ff 00 	movl   $0x0,-0xa0(%rbp)
    7f3a6b4679e4:	00 00 00 
    7f3a6b4679e7:	41 c7 87 b0 00 00 00 	movl   $0x0,0xb0(%r15)
    7f3a6b4679ee:	00 00 00 00 
    7f3a6b4679f2:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7f3a6b4679f9:	00 00 00 
    7f3a6b4679fc:	41 c7 87 a8 00 00 00 	movl   $0x0,0xa8(%r15)
    7f3a6b467a03:	00 00 00 00 
    7f3a6b467a07:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7f3a6b467a0e:	00 00 00 
    7f3a6b467a11:	41 c7 87 a0 00 00 00 	movl   $0x0,0xa0(%r15)
    7f3a6b467a18:	00 00 00 00 
    7f3a6b467a1c:	c7 85 78 ff ff ff 00 	movl   $0x0,-0x88(%rbp)
    7f3a6b467a23:	00 00 00 
    7f3a6b467a26:	41 c7 87 98 00 00 00 	movl   $0x0,0x98(%r15)
    7f3a6b467a2d:	00 00 00 00 
    7f3a6b467a31:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
    7f3a6b467a38:	41 c7 87 90 00 00 00 	movl   $0x0,0x90(%r15)
    7f3a6b467a3f:	00 00 00 00 
    7f3a6b467a43:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
    7f3a6b467a4a:	41 c7 87 88 00 00 00 	movl   $0x0,0x88(%r15)
    7f3a6b467a51:	00 00 00 00 
    7f3a6b467a55:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7f3a6b467a5c:	41 c7 87 80 00 00 00 	movl   $0x0,0x80(%r15)
    7f3a6b467a63:	00 00 00 00 
    7f3a6b467a67:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7f3a6b467a6e:	41 c7 47 78 00 00 00 	movl   $0x0,0x78(%r15)
    7f3a6b467a75:	00 
    7f3a6b467a76:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7f3a6b467a7d:	41 c7 47 70 00 00 00 	movl   $0x0,0x70(%r15)
    7f3a6b467a84:	00 
    7f3a6b467a85:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
    7f3a6b467a8c:	41 c7 47 68 00 00 00 	movl   $0x0,0x68(%r15)
    7f3a6b467a93:	00 
    7f3a6b467a94:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7f3a6b467a9b:	41 c7 47 60 00 00 00 	movl   $0x0,0x60(%r15)
    7f3a6b467aa2:	00 
    7f3a6b467aa3:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7f3a6b467aaa:	41 c7 47 58 00 00 00 	movl   $0x0,0x58(%r15)
    7f3a6b467ab1:	00 
    7f3a6b467ab2:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    7f3a6b467ab9:	41 c7 47 48 00 00 00 	movl   $0x0,0x48(%r15)
    7f3a6b467ac0:	00 
    7f3a6b467ac1:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
    7f3a6b467ac8:	41 c7 47 50 00 00 00 	movl   $0x0,0x50(%r15)
    7f3a6b467acf:	00 
    7f3a6b467ad0:	41 c7 47 38 00 00 00 	movl   $0x0,0x38(%r15)
    7f3a6b467ad7:	00 
    7f3a6b467ad8:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7f3a6b467adf:	41 c7 47 40 00 00 00 	movl   $0x0,0x40(%r15)
    7f3a6b467ae6:	00 
    7f3a6b467ae7:	41 c7 47 30 00 00 00 	movl   $0x0,0x30(%r15)
    7f3a6b467aee:	00 
    7f3a6b467aef:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7f3a6b467af6:	41 c7 47 20 00 00 00 	movl   $0x0,0x20(%r15)
    7f3a6b467afd:	00 
    7f3a6b467afe:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
    7f3a6b467b05:	41 c7 47 28 00 00 00 	movl   $0x0,0x28(%r15)
    7f3a6b467b0c:	00 
    7f3a6b467b0d:	41 c7 47 10 00 00 00 	movl   $0x0,0x10(%r15)
    7f3a6b467b14:	00 
    7f3a6b467b15:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
    7f3a6b467b1c:	41 c7 47 18 00 00 00 	movl   $0x0,0x18(%r15)
    7f3a6b467b23:	00 
    7f3a6b467b24:	41 c7 47 08 00 00 00 	movl   $0x0,0x8(%r15)
    7f3a6b467b2b:	00 
    7f3a6b467b2c:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7f3a6b467b33:	e9 4f 03 00 00       	jmpq   0x7f3a6b467e87
    7f3a6b467b38:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f3a6b467b3e:	85 c0                	test   %eax,%eax
    7f3a6b467b40:	0f 84 41 03 00 00    	je     0x7f3a6b467e87
    7f3a6b467b46:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7f3a6b467b4c:	41 89 87 98 01 00 00 	mov    %eax,0x198(%r15)
    7f3a6b467b53:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7f3a6b467b59:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7f3a6b467b5f:	41 89 87 90 01 00 00 	mov    %eax,0x190(%r15)
    7f3a6b467b66:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f3a6b467b6c:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7f3a6b467b72:	41 89 87 88 01 00 00 	mov    %eax,0x188(%r15)
    7f3a6b467b79:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f3a6b467b7f:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7f3a6b467b85:	41 89 87 80 01 00 00 	mov    %eax,0x180(%r15)
    7f3a6b467b8c:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f3a6b467b92:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f3a6b467b98:	41 89 87 78 01 00 00 	mov    %eax,0x178(%r15)
    7f3a6b467b9f:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f3a6b467ba5:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7f3a6b467bab:	41 89 87 70 01 00 00 	mov    %eax,0x170(%r15)
    7f3a6b467bb2:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7f3a6b467bb8:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7f3a6b467bbb:	41 89 87 68 01 00 00 	mov    %eax,0x168(%r15)
    7f3a6b467bc2:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7f3a6b467bc8:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7f3a6b467bce:	41 89 87 60 01 00 00 	mov    %eax,0x160(%r15)
    7f3a6b467bd5:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f3a6b467bdb:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f3a6b467be1:	41 89 87 58 01 00 00 	mov    %eax,0x158(%r15)
    7f3a6b467be8:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7f3a6b467bee:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7f3a6b467bf4:	41 89 87 50 01 00 00 	mov    %eax,0x150(%r15)
    7f3a6b467bfb:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7f3a6b467c01:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f3a6b467c07:	41 89 87 48 01 00 00 	mov    %eax,0x148(%r15)
    7f3a6b467c0e:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f3a6b467c14:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f3a6b467c1a:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7f3a6b467c21:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f3a6b467c27:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7f3a6b467c2d:	41 89 87 38 01 00 00 	mov    %eax,0x138(%r15)
    7f3a6b467c34:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f3a6b467c3a:	41 89 9f 30 01 00 00 	mov    %ebx,0x130(%r15)
    7f3a6b467c41:	8b c3                	mov    %ebx,%eax
    7f3a6b467c43:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7f3a6b467c49:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f3a6b467c4f:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7f3a6b467c56:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f3a6b467c5c:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7f3a6b467c62:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7f3a6b467c69:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7f3a6b467c6f:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7f3a6b467c75:	41 89 87 18 01 00 00 	mov    %eax,0x118(%r15)
    7f3a6b467c7c:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f3a6b467c82:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7f3a6b467c85:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7f3a6b467c8c:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f3a6b467c92:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7f3a6b467c98:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7f3a6b467c9f:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f3a6b467ca5:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f3a6b467cab:	41 89 87 00 01 00 00 	mov    %eax,0x100(%r15)
    7f3a6b467cb2:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7f3a6b467cb8:	8b 85 f0 fd ff ff    	mov    -0x210(%rbp),%eax
    7f3a6b467cbe:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7f3a6b467cc5:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f3a6b467ccb:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f3a6b467cce:	41 89 87 f0 00 00 00 	mov    %eax,0xf0(%r15)
    7f3a6b467cd5:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f3a6b467cdb:	45 89 a7 e8 00 00 00 	mov    %r12d,0xe8(%r15)
    7f3a6b467ce2:	41 8b c4             	mov    %r12d,%eax
    7f3a6b467ce5:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7f3a6b467ceb:	8b 85 f8 fd ff ff    	mov    -0x208(%rbp),%eax
    7f3a6b467cf1:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7f3a6b467cf8:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7f3a6b467cfe:	8b 45 98             	mov    -0x68(%rbp),%eax
    7f3a6b467d01:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7f3a6b467d08:	48 8b d8             	mov    %rax,%rbx
    7f3a6b467d0b:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f3a6b467d11:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7f3a6b467d18:	4c 8b e0             	mov    %rax,%r12
    7f3a6b467d1b:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7f3a6b467d21:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7f3a6b467d28:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7f3a6b467d2e:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f3a6b467d31:	41 89 87 c0 00 00 00 	mov    %eax,0xc0(%r15)
    7f3a6b467d38:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7f3a6b467d3e:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7f3a6b467d41:	41 89 87 b8 00 00 00 	mov    %eax,0xb8(%r15)
    7f3a6b467d48:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f3a6b467d4e:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7f3a6b467d54:	41 89 87 b0 00 00 00 	mov    %eax,0xb0(%r15)
    7f3a6b467d5b:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f3a6b467d61:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7f3a6b467d64:	41 89 87 a8 00 00 00 	mov    %eax,0xa8(%r15)
    7f3a6b467d6b:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f3a6b467d71:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7f3a6b467d77:	41 89 87 a0 00 00 00 	mov    %eax,0xa0(%r15)
    7f3a6b467d7e:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f3a6b467d84:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7f3a6b467d87:	41 89 87 98 00 00 00 	mov    %eax,0x98(%r15)
    7f3a6b467d8e:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f3a6b467d91:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f3a6b467d94:	41 89 87 90 00 00 00 	mov    %eax,0x90(%r15)
    7f3a6b467d9b:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f3a6b467d9e:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f3a6b467da4:	41 89 87 88 00 00 00 	mov    %eax,0x88(%r15)
    7f3a6b467dab:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f3a6b467dae:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7f3a6b467db1:	41 89 87 80 00 00 00 	mov    %eax,0x80(%r15)
    7f3a6b467db8:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f3a6b467dbb:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f3a6b467dbe:	41 89 47 78          	mov    %eax,0x78(%r15)
    7f3a6b467dc2:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f3a6b467dc5:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7f3a6b467dcb:	41 89 47 70          	mov    %eax,0x70(%r15)
    7f3a6b467dcf:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f3a6b467dd2:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7f3a6b467dd8:	41 89 47 68          	mov    %eax,0x68(%r15)
    7f3a6b467ddc:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f3a6b467ddf:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7f3a6b467de5:	41 89 47 60          	mov    %eax,0x60(%r15)
    7f3a6b467de9:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f3a6b467dec:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7f3a6b467df2:	41 89 47 58          	mov    %eax,0x58(%r15)
    7f3a6b467df6:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f3a6b467df9:	41 8b 47 50          	mov    0x50(%r15),%eax
    7f3a6b467dfd:	8b c8                	mov    %eax,%ecx
    7f3a6b467dff:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f3a6b467e05:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7f3a6b467e09:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7f3a6b467e0c:	c1 e8 08             	shr    $0x8,%eax
    7f3a6b467e0f:	8b 8d 40 fe ff ff    	mov    -0x1c0(%rbp),%ecx
    7f3a6b467e15:	c1 e1 08             	shl    $0x8,%ecx
    7f3a6b467e18:	0b c1                	or     %ecx,%eax
    7f3a6b467e1a:	41 89 47 50          	mov    %eax,0x50(%r15)
    7f3a6b467e1e:	41 8b 47 40          	mov    0x40(%r15),%eax
    7f3a6b467e22:	41 89 47 38          	mov    %eax,0x38(%r15)
    7f3a6b467e26:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f3a6b467e29:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f3a6b467e2f:	41 89 47 40          	mov    %eax,0x40(%r15)
    7f3a6b467e33:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7f3a6b467e39:	41 89 47 30          	mov    %eax,0x30(%r15)
    7f3a6b467e3d:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7f3a6b467e40:	41 8b 47 28          	mov    0x28(%r15),%eax
    7f3a6b467e44:	8b c8                	mov    %eax,%ecx
    7f3a6b467e46:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f3a6b467e4c:	41 89 4f 20          	mov    %ecx,0x20(%r15)
    7f3a6b467e50:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7f3a6b467e53:	c1 e8 08             	shr    $0x8,%eax
    7f3a6b467e56:	8b 8d 58 fe ff ff    	mov    -0x1a8(%rbp),%ecx
    7f3a6b467e5c:	c1 e1 08             	shl    $0x8,%ecx
    7f3a6b467e5f:	0b c1                	or     %ecx,%eax
    7f3a6b467e61:	41 89 47 28          	mov    %eax,0x28(%r15)
    7f3a6b467e65:	41 8b 47 18          	mov    0x18(%r15),%eax
    7f3a6b467e69:	41 89 47 10          	mov    %eax,0x10(%r15)
    7f3a6b467e6d:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f3a6b467e70:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f3a6b467e76:	41 89 47 18          	mov    %eax,0x18(%r15)
    7f3a6b467e7a:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7f3a6b467e80:	41 89 47 08          	mov    %eax,0x8(%r15)
    7f3a6b467e84:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f3a6b467e87:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7f3a6b467e8d:	85 c0                	test   %eax,%eax
    7f3a6b467e8f:	0f 84 0f 00 00 00    	je     0x7f3a6b467ea4
    7f3a6b467e95:	41 c7 07 00 00 00 00 	movl   $0x0,(%r15)
    7f3a6b467e9c:	45 33 ed             	xor    %r13d,%r13d
    7f3a6b467e9f:	e9 1a 00 00 00       	jmpq   0x7f3a6b467ebe
    7f3a6b467ea4:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f3a6b467eaa:	85 c0                	test   %eax,%eax
    7f3a6b467eac:	0f 84 0c 00 00 00    	je     0x7f3a6b467ebe
    7f3a6b467eb2:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7f3a6b467eb8:	41 89 07             	mov    %eax,(%r15)
    7f3a6b467ebb:	4c 8b e8             	mov    %rax,%r13
    7f3a6b467ebe:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f3a6b467ec1:	8b c0                	mov    %eax,%eax
    7f3a6b467ec3:	48 c1 e0 18          	shl    $0x18,%rax
    7f3a6b467ec7:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7f3a6b467eca:	8b c9                	mov    %ecx,%ecx
    7f3a6b467ecc:	48 0b c1             	or     %rcx,%rax
    7f3a6b467ecf:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7f3a6b467ed5:	8b ca                	mov    %edx,%ecx
    7f3a6b467ed7:	48 c1 e1 30          	shl    $0x30,%rcx
    7f3a6b467edb:	48 0b c1             	or     %rcx,%rax
    7f3a6b467ede:	49 89 87 a0 01 00 00 	mov    %rax,0x1a0(%r15)
    7f3a6b467ee5:	c1 ea 10             	shr    $0x10,%edx
    7f3a6b467ee8:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7f3a6b467eee:	c1 e0 08             	shl    $0x8,%eax
    7f3a6b467ef1:	0b d0                	or     %eax,%edx
    7f3a6b467ef3:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7f3a6b467ef9:	8b c0                	mov    %eax,%eax
    7f3a6b467efb:	48 c1 e0 20          	shl    $0x20,%rax
    7f3a6b467eff:	8b ca                	mov    %edx,%ecx
    7f3a6b467f01:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f04:	8b 95 48 ff ff ff    	mov    -0xb8(%rbp),%edx
    7f3a6b467f0a:	8b ca                	mov    %edx,%ecx
    7f3a6b467f0c:	48 c1 e1 38          	shl    $0x38,%rcx
    7f3a6b467f10:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f13:	49 89 87 a8 01 00 00 	mov    %rax,0x1a8(%r15)
    7f3a6b467f1a:	c1 ea 08             	shr    $0x8,%edx
    7f3a6b467f1d:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f3a6b467f23:	8b c0                	mov    %eax,%eax
    7f3a6b467f25:	48 c1 e0 10          	shl    $0x10,%rax
    7f3a6b467f29:	8b ca                	mov    %edx,%ecx
    7f3a6b467f2b:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f2e:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7f3a6b467f34:	8b c9                	mov    %ecx,%ecx
    7f3a6b467f36:	48 c1 e1 28          	shl    $0x28,%rcx
    7f3a6b467f3a:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f3d:	49 89 87 b0 01 00 00 	mov    %rax,0x1b0(%r15)
    7f3a6b467f44:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f3a6b467f4a:	8b c0                	mov    %eax,%eax
    7f3a6b467f4c:	48 c1 e0 18          	shl    $0x18,%rax
    7f3a6b467f50:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7f3a6b467f56:	8b c9                	mov    %ecx,%ecx
    7f3a6b467f58:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f5b:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7f3a6b467f61:	8b ca                	mov    %edx,%ecx
    7f3a6b467f63:	48 c1 e1 30          	shl    $0x30,%rcx
    7f3a6b467f67:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f6a:	49 89 87 b8 01 00 00 	mov    %rax,0x1b8(%r15)
    7f3a6b467f71:	c1 ea 10             	shr    $0x10,%edx
    7f3a6b467f74:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7f3a6b467f7a:	c1 e0 08             	shl    $0x8,%eax
    7f3a6b467f7d:	0b d0                	or     %eax,%edx
    7f3a6b467f7f:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7f3a6b467f85:	8b c0                	mov    %eax,%eax
    7f3a6b467f87:	48 c1 e0 20          	shl    $0x20,%rax
    7f3a6b467f8b:	8b ca                	mov    %edx,%ecx
    7f3a6b467f8d:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f90:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7f3a6b467f96:	8b ca                	mov    %edx,%ecx
    7f3a6b467f98:	48 c1 e1 38          	shl    $0x38,%rcx
    7f3a6b467f9c:	48 0b c1             	or     %rcx,%rax
    7f3a6b467f9f:	49 89 87 c0 01 00 00 	mov    %rax,0x1c0(%r15)
    7f3a6b467fa6:	c1 ea 08             	shr    $0x8,%edx
    7f3a6b467fa9:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7f3a6b467faf:	8b c0                	mov    %eax,%eax
    7f3a6b467fb1:	48 c1 e0 10          	shl    $0x10,%rax
    7f3a6b467fb5:	8b ca                	mov    %edx,%ecx
    7f3a6b467fb7:	48 0b c1             	or     %rcx,%rax
    7f3a6b467fba:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7f3a6b467fc0:	8b c9                	mov    %ecx,%ecx
    7f3a6b467fc2:	48 c1 e1 28          	shl    $0x28,%rcx
    7f3a6b467fc6:	48 0b c1             	or     %rcx,%rax
    7f3a6b467fc9:	49 89 87 c8 01 00 00 	mov    %rax,0x1c8(%r15)
    7f3a6b467fd0:	49 8b 46 28          	mov    0x28(%r14),%rax
    7f3a6b467fd4:	49 8b cf             	mov    %r15,%rcx
    7f3a6b467fd7:	48 81 c1 a0 01 00 00 	add    $0x1a0,%rcx
    7f3a6b467fde:	0f 10 01             	movups (%rcx),%xmm0
    7f3a6b467fe1:	0f 11 00             	movups %xmm0,(%rax)
    7f3a6b467fe4:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7f3a6b467fe8:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7f3a6b467fec:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7f3a6b467ff0:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7f3a6b467ff4:	49 8b 46 30          	mov    0x30(%r14),%rax
    7f3a6b467ff8:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f3a6b467ffb:	89 08                	mov    %ecx,(%rax)
    7f3a6b467ffd:	33 c0                	xor    %eax,%eax
    7f3a6b467fff:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f3a6b468003:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f3a6b468008:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f3a6b46800d:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f3a6b468012:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f3a6b468017:	48 8b e5             	mov    %rbp,%rsp
    7f3a6b46801a:	5d                   	pop    %rbp
    7f3a6b46801b:	c3                   	retq   

end

