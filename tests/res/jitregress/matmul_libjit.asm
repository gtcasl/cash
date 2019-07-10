function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fc7d891712d <.text>:
    7fc7d891712d:	55                   	push   %rbp
    7fc7d891712e:	48 8b ec             	mov    %rsp,%rbp
    7fc7d8917131:	48 81 ec 90 02 00 00 	sub    $0x290,%rsp
    7fc7d8917138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fc7d891713c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fc7d8917141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fc7d8917146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fc7d891714b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fc7d8917150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fc7d8917154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fc7d8917158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fc7d891715c:	4c 8b 28             	mov    (%rax),%r13
    7fc7d891715f:	45 8b 37             	mov    (%r15),%r14d
    7fc7d8917162:	41 8b 47 08          	mov    0x8(%r15),%eax
    7fc7d8917166:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fc7d8917169:	41 8b 47 10          	mov    0x10(%r15),%eax
    7fc7d891716d:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fc7d8917170:	41 8b 47 20          	mov    0x20(%r15),%eax
    7fc7d8917174:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fc7d8917177:	41 8b 47 30          	mov    0x30(%r15),%eax
    7fc7d891717b:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fc7d891717e:	41 8b 47 38          	mov    0x38(%r15),%eax
    7fc7d8917182:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fc7d8917185:	41 8b 47 48          	mov    0x48(%r15),%eax
    7fc7d8917189:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fc7d891718c:	41 8b 47 58          	mov    0x58(%r15),%eax
    7fc7d8917190:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fc7d8917193:	41 8b 47 60          	mov    0x60(%r15),%eax
    7fc7d8917197:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fc7d891719a:	41 8b 47 68          	mov    0x68(%r15),%eax
    7fc7d891719e:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fc7d89171a1:	41 8b 47 70          	mov    0x70(%r15),%eax
    7fc7d89171a5:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fc7d89171a8:	41 8b 47 78          	mov    0x78(%r15),%eax
    7fc7d89171ac:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fc7d89171af:	41 8b 87 80 00 00 00 	mov    0x80(%r15),%eax
    7fc7d89171b6:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fc7d89171b9:	41 8b 87 88 00 00 00 	mov    0x88(%r15),%eax
    7fc7d89171c0:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fc7d89171c3:	41 8b 87 90 00 00 00 	mov    0x90(%r15),%eax
    7fc7d89171ca:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fc7d89171cd:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7fc7d89171d4:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fc7d89171d7:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7fc7d89171de:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fc7d89171e4:	41 8b 87 a8 00 00 00 	mov    0xa8(%r15),%eax
    7fc7d89171eb:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fc7d89171f1:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7fc7d89171f8:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fc7d89171fe:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7fc7d8917205:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7fc7d891720b:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7fc7d8917212:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fc7d8917218:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7fc7d891721f:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7fc7d8917225:	45 8b a7 d0 00 00 00 	mov    0xd0(%r15),%r12d
    7fc7d891722c:	41 8b 9f d8 00 00 00 	mov    0xd8(%r15),%ebx
    7fc7d8917233:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7fc7d891723a:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fc7d8917240:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7fc7d8917247:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fc7d891724d:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7fc7d8917254:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fc7d891725a:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7fc7d8917261:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fc7d8917267:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7fc7d891726e:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fc7d8917274:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7fc7d891727b:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fc7d8917281:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7fc7d8917288:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fc7d891728e:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7fc7d8917295:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fc7d891729b:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7fc7d89172a2:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fc7d89172a8:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7fc7d89172af:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fc7d89172b5:	41 8b 87 30 01 00 00 	mov    0x130(%r15),%eax
    7fc7d89172bc:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fc7d89172c2:	41 8b 87 38 01 00 00 	mov    0x138(%r15),%eax
    7fc7d89172c9:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7fc7d89172cf:	41 8b 87 40 01 00 00 	mov    0x140(%r15),%eax
    7fc7d89172d6:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fc7d89172dc:	41 8b 87 48 01 00 00 	mov    0x148(%r15),%eax
    7fc7d89172e3:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fc7d89172e9:	41 8b 87 50 01 00 00 	mov    0x150(%r15),%eax
    7fc7d89172f0:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fc7d89172f6:	41 8b 87 58 01 00 00 	mov    0x158(%r15),%eax
    7fc7d89172fd:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fc7d8917303:	41 8b 87 60 01 00 00 	mov    0x160(%r15),%eax
    7fc7d891730a:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fc7d8917310:	41 8b 87 68 01 00 00 	mov    0x168(%r15),%eax
    7fc7d8917317:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fc7d891731d:	41 8b 87 70 01 00 00 	mov    0x170(%r15),%eax
    7fc7d8917324:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fc7d891732a:	41 8b 87 78 01 00 00 	mov    0x178(%r15),%eax
    7fc7d8917331:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fc7d8917337:	41 8b 87 80 01 00 00 	mov    0x180(%r15),%eax
    7fc7d891733e:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fc7d8917344:	41 8b 87 88 01 00 00 	mov    0x188(%r15),%eax
    7fc7d891734b:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fc7d8917351:	41 8b 87 90 01 00 00 	mov    0x190(%r15),%eax
    7fc7d8917358:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fc7d891735e:	41 8b 87 98 01 00 00 	mov    0x198(%r15),%eax
    7fc7d8917365:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fc7d891736b:	49 8b 45 18          	mov    0x18(%r13),%rax
    7fc7d891736f:	8b 00                	mov    (%rax),%eax
    7fc7d8917371:	41 8b 8f d0 01 00 00 	mov    0x1d0(%r15),%ecx
    7fc7d8917378:	33 c8                	xor    %eax,%ecx
    7fc7d891737a:	23 c8                	and    %eax,%ecx
    7fc7d891737c:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7fc7d8917383:	85 c9                	test   %ecx,%ecx
    7fc7d8917385:	0f 84 88 0c 00 00    	je     0x7fc7d8918013
    7fc7d891738b:	49 8b 45 00          	mov    0x0(%r13),%rax
    7fc7d891738f:	8b 00                	mov    (%rax),%eax
    7fc7d8917391:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fc7d8917397:	41 83 fe 0b          	cmp    $0xb,%r14d
    7fc7d891739b:	0f 93 c0             	setae  %al
    7fc7d891739e:	0f b6 c0             	movzbl %al,%eax
    7fc7d89173a1:	41 8b ce             	mov    %r14d,%ecx
    7fc7d89173a4:	83 e9 0b             	sub    $0xb,%ecx
    7fc7d89173a7:	83 e1 0f             	and    $0xf,%ecx
    7fc7d89173aa:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7fc7d89173b0:	41 8b ce             	mov    %r14d,%ecx
    7fc7d89173b3:	ff c1                	inc    %ecx
    7fc7d89173b5:	83 e1 0f             	and    $0xf,%ecx
    7fc7d89173b8:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7fc7d89173be:	85 c0                	test   %eax,%eax
    7fc7d89173c0:	0f 85 0c 00 00 00    	jne    0x7fc7d89173d2
    7fc7d89173c6:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7fc7d89173cc:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fc7d89173d2:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fc7d89173d8:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fc7d89173de:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7fc7d89173e4:	85 c0                	test   %eax,%eax
    7fc7d89173e6:	0f 85 09 00 00 00    	jne    0x7fc7d89173f5
    7fc7d89173ec:	41 8b c6             	mov    %r14d,%eax
    7fc7d89173ef:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fc7d89173f5:	49 8b 45 20          	mov    0x20(%r13),%rax
    7fc7d89173f9:	8b 00                	mov    (%rax),%eax
    7fc7d89173fb:	8b c8                	mov    %eax,%ecx
    7fc7d89173fd:	83 c9 00             	or     $0x0,%ecx
    7fc7d8917400:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7fc7d8917406:	49 8b 4d 10          	mov    0x10(%r13),%rcx
    7fc7d891740a:	8b 09                	mov    (%rcx),%ecx
    7fc7d891740c:	8b d1                	mov    %ecx,%edx
    7fc7d891740e:	c1 ea 08             	shr    $0x8,%edx
    7fc7d8917411:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fc7d8917417:	89 95 60 fe ff ff    	mov    %edx,-0x1a0(%rbp)
    7fc7d891741d:	8b d1                	mov    %ecx,%edx
    7fc7d891741f:	c1 ea 10             	shr    $0x10,%edx
    7fc7d8917422:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fc7d8917428:	89 95 58 fe ff ff    	mov    %edx,-0x1a8(%rbp)
    7fc7d891742e:	8b d1                	mov    %ecx,%edx
    7fc7d8917430:	c1 ea 18             	shr    $0x18,%edx
    7fc7d8917433:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fc7d8917439:	89 95 50 fe ff ff    	mov    %edx,-0x1b0(%rbp)
    7fc7d891743f:	49 8b 55 08          	mov    0x8(%r13),%rdx
    7fc7d8917443:	8b 12                	mov    (%rdx),%edx
    7fc7d8917445:	8b f2                	mov    %edx,%esi
    7fc7d8917447:	c1 ee 08             	shr    $0x8,%esi
    7fc7d891744a:	81 e6 ff 00 00 00    	and    $0xff,%esi
    7fc7d8917450:	89 b5 48 fe ff ff    	mov    %esi,-0x1b8(%rbp)
    7fc7d8917456:	8b f2                	mov    %edx,%esi
    7fc7d8917458:	c1 ee 10             	shr    $0x10,%esi
    7fc7d891745b:	81 e6 ff 00 00 00    	and    $0xff,%esi
    7fc7d8917461:	89 b5 40 fe ff ff    	mov    %esi,-0x1c0(%rbp)
    7fc7d8917467:	8b f2                	mov    %edx,%esi
    7fc7d8917469:	c1 ee 18             	shr    $0x18,%esi
    7fc7d891746c:	81 e6 ff 00 00 00    	and    $0xff,%esi
    7fc7d8917472:	89 b5 38 fe ff ff    	mov    %esi,-0x1c8(%rbp)
    7fc7d8917478:	41 83 fe 0b          	cmp    $0xb,%r14d
    7fc7d891747c:	40 0f 94 c6          	sete   %sil
    7fc7d8917480:	40 0f b6 f6          	movzbl %sil,%esi
    7fc7d8917484:	89 b5 30 fe ff ff    	mov    %esi,-0x1d0(%rbp)
    7fc7d891748a:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fc7d8917490:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fc7d8917496:	89 95 28 fe ff ff    	mov    %edx,-0x1d8(%rbp)
    7fc7d891749c:	0f b6 d2             	movzbl %dl,%edx
    7fc7d891749f:	0f be d2             	movsbl %dl,%edx
    7fc7d89174a2:	89 8d 20 fe ff ff    	mov    %ecx,-0x1e0(%rbp)
    7fc7d89174a8:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d89174ab:	0f be c9             	movsbl %cl,%ecx
    7fc7d89174ae:	0f af d1             	imul   %ecx,%edx
    7fc7d89174b1:	81 e2 ff ff ff 00    	and    $0xffffff,%edx
    7fc7d89174b7:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fc7d89174ba:	03 d1                	add    %ecx,%edx
    7fc7d89174bc:	81 e2 ff ff ff 00    	and    $0xffffff,%edx
    7fc7d89174c2:	89 95 18 fe ff ff    	mov    %edx,-0x1e8(%rbp)
    7fc7d89174c8:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fc7d89174cb:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d89174ce:	0f be c9             	movsbl %cl,%ecx
    7fc7d89174d1:	8b 55 f0             	mov    -0x10(%rbp),%edx
    7fc7d89174d4:	0f b6 d2             	movzbl %dl,%edx
    7fc7d89174d7:	0f be d2             	movsbl %dl,%edx
    7fc7d89174da:	0f af ca             	imul   %edx,%ecx
    7fc7d89174dd:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89174e3:	8b 55 90             	mov    -0x70(%rbp),%edx
    7fc7d89174e6:	03 ca                	add    %edx,%ecx
    7fc7d89174e8:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89174ee:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7fc7d89174f4:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fc7d89174f7:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d89174fa:	0f be c9             	movsbl %cl,%ecx
    7fc7d89174fd:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fc7d8917500:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917503:	0f be d2             	movsbl %dl,%edx
    7fc7d8917506:	0f af ca             	imul   %edx,%ecx
    7fc7d8917509:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891750f:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7fc7d8917515:	03 ca                	add    %edx,%ecx
    7fc7d8917517:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891751d:	89 8d 08 fe ff ff    	mov    %ecx,-0x1f8(%rbp)
    7fc7d8917523:	8b 4d 88             	mov    -0x78(%rbp),%ecx
    7fc7d8917526:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d8917529:	0f be c9             	movsbl %cl,%ecx
    7fc7d891752c:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fc7d891752f:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917532:	0f be d2             	movsbl %dl,%edx
    7fc7d8917535:	0f af ca             	imul   %edx,%ecx
    7fc7d8917538:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891753e:	8b 95 68 ff ff ff    	mov    -0x98(%rbp),%edx
    7fc7d8917544:	03 ca                	add    %edx,%ecx
    7fc7d8917546:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891754c:	89 8d 00 fe ff ff    	mov    %ecx,-0x200(%rbp)
    7fc7d8917552:	8b 4d d8             	mov    -0x28(%rbp),%ecx
    7fc7d8917555:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d8917558:	0f be c9             	movsbl %cl,%ecx
    7fc7d891755b:	8b 55 b0             	mov    -0x50(%rbp),%edx
    7fc7d891755e:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917561:	0f be d2             	movsbl %dl,%edx
    7fc7d8917564:	0f af ca             	imul   %edx,%ecx
    7fc7d8917567:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891756d:	8b 95 50 ff ff ff    	mov    -0xb0(%rbp),%edx
    7fc7d8917573:	03 ca                	add    %edx,%ecx
    7fc7d8917575:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891757b:	89 8d f8 fd ff ff    	mov    %ecx,-0x208(%rbp)
    7fc7d8917581:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7fc7d8917587:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d891758a:	0f be c9             	movsbl %cl,%ecx
    7fc7d891758d:	8b 55 98             	mov    -0x68(%rbp),%edx
    7fc7d8917590:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917593:	0f be d2             	movsbl %dl,%edx
    7fc7d8917596:	0f af ca             	imul   %edx,%ecx
    7fc7d8917599:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891759f:	8b 95 48 ff ff ff    	mov    -0xb8(%rbp),%edx
    7fc7d89175a5:	03 ca                	add    %edx,%ecx
    7fc7d89175a7:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89175ad:	89 8d f0 fd ff ff    	mov    %ecx,-0x210(%rbp)
    7fc7d89175b3:	41 0f b6 cc          	movzbl %r12b,%ecx
    7fc7d89175b7:	0f be c9             	movsbl %cl,%ecx
    7fc7d89175ba:	8b 55 80             	mov    -0x80(%rbp),%edx
    7fc7d89175bd:	0f b6 d2             	movzbl %dl,%edx
    7fc7d89175c0:	0f be d2             	movsbl %dl,%edx
    7fc7d89175c3:	0f af ca             	imul   %edx,%ecx
    7fc7d89175c6:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89175cc:	8b 95 30 ff ff ff    	mov    -0xd0(%rbp),%edx
    7fc7d89175d2:	03 ca                	add    %edx,%ecx
    7fc7d89175d4:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89175da:	89 8d e8 fd ff ff    	mov    %ecx,-0x218(%rbp)
    7fc7d89175e0:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7fc7d89175e6:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d89175e9:	0f be c9             	movsbl %cl,%ecx
    7fc7d89175ec:	8b 95 70 ff ff ff    	mov    -0x90(%rbp),%edx
    7fc7d89175f2:	0f b6 d2             	movzbl %dl,%edx
    7fc7d89175f5:	0f be d2             	movsbl %dl,%edx
    7fc7d89175f8:	0f af ca             	imul   %edx,%ecx
    7fc7d89175fb:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917601:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7fc7d8917607:	03 ca                	add    %edx,%ecx
    7fc7d8917609:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891760f:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fc7d8917615:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7fc7d8917618:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d891761b:	0f be c9             	movsbl %cl,%ecx
    7fc7d891761e:	8b 95 58 ff ff ff    	mov    -0xa8(%rbp),%edx
    7fc7d8917624:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917627:	0f be d2             	movsbl %dl,%edx
    7fc7d891762a:	0f af ca             	imul   %edx,%ecx
    7fc7d891762d:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917633:	8b 95 08 ff ff ff    	mov    -0xf8(%rbp),%edx
    7fc7d8917639:	03 ca                	add    %edx,%ecx
    7fc7d891763b:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917641:	89 8d d8 fd ff ff    	mov    %ecx,-0x228(%rbp)
    7fc7d8917647:	8b 8d 18 ff ff ff    	mov    -0xe8(%rbp),%ecx
    7fc7d891764d:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d8917650:	0f be c9             	movsbl %cl,%ecx
    7fc7d8917653:	0f b6 d3             	movzbl %bl,%edx
    7fc7d8917656:	0f be d2             	movsbl %dl,%edx
    7fc7d8917659:	0f af ca             	imul   %edx,%ecx
    7fc7d891765c:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917662:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fc7d8917668:	03 ca                	add    %edx,%ecx
    7fc7d891766a:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917670:	89 8d d0 fd ff ff    	mov    %ecx,-0x230(%rbp)
    7fc7d8917676:	8b 8d 00 ff ff ff    	mov    -0x100(%rbp),%ecx
    7fc7d891767c:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d891767f:	0f be c9             	movsbl %cl,%ecx
    7fc7d8917682:	8b 95 38 ff ff ff    	mov    -0xc8(%rbp),%edx
    7fc7d8917688:	0f b6 d2             	movzbl %dl,%edx
    7fc7d891768b:	0f be d2             	movsbl %dl,%edx
    7fc7d891768e:	0f af ca             	imul   %edx,%ecx
    7fc7d8917691:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917697:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7fc7d891769d:	03 ca                	add    %edx,%ecx
    7fc7d891769f:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89176a5:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7fc7d89176ab:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7fc7d89176b1:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d89176b4:	0f be c9             	movsbl %cl,%ecx
    7fc7d89176b7:	8b 95 28 ff ff ff    	mov    -0xd8(%rbp),%edx
    7fc7d89176bd:	0f b6 d2             	movzbl %dl,%edx
    7fc7d89176c0:	0f be d2             	movsbl %dl,%edx
    7fc7d89176c3:	0f af ca             	imul   %edx,%ecx
    7fc7d89176c6:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89176cc:	8b 95 c8 fe ff ff    	mov    -0x138(%rbp),%edx
    7fc7d89176d2:	03 ca                	add    %edx,%ecx
    7fc7d89176d4:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89176da:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7fc7d89176e0:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7fc7d89176e3:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d89176e6:	0f be c9             	movsbl %cl,%ecx
    7fc7d89176e9:	8b 95 10 ff ff ff    	mov    -0xf0(%rbp),%edx
    7fc7d89176ef:	0f b6 d2             	movzbl %dl,%edx
    7fc7d89176f2:	0f be d2             	movsbl %dl,%edx
    7fc7d89176f5:	0f af ca             	imul   %edx,%ecx
    7fc7d89176f8:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89176fe:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7fc7d8917704:	03 ca                	add    %edx,%ecx
    7fc7d8917706:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891770c:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7fc7d8917712:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7fc7d8917718:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d891771b:	0f be c9             	movsbl %cl,%ecx
    7fc7d891771e:	8b 95 f8 fe ff ff    	mov    -0x108(%rbp),%edx
    7fc7d8917724:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917727:	0f be d2             	movsbl %dl,%edx
    7fc7d891772a:	0f af ca             	imul   %edx,%ecx
    7fc7d891772d:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917733:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7fc7d8917739:	03 ca                	add    %edx,%ecx
    7fc7d891773b:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917741:	89 8d b0 fd ff ff    	mov    %ecx,-0x250(%rbp)
    7fc7d8917747:	8b 8d b0 fe ff ff    	mov    -0x150(%rbp),%ecx
    7fc7d891774d:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d8917750:	0f be c9             	movsbl %cl,%ecx
    7fc7d8917753:	8b 95 e0 fe ff ff    	mov    -0x120(%rbp),%edx
    7fc7d8917759:	0f b6 d2             	movzbl %dl,%edx
    7fc7d891775c:	0f be d2             	movsbl %dl,%edx
    7fc7d891775f:	0f af ca             	imul   %edx,%ecx
    7fc7d8917762:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917768:	8b 95 98 fe ff ff    	mov    -0x168(%rbp),%edx
    7fc7d891776e:	03 ca                	add    %edx,%ecx
    7fc7d8917770:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d8917776:	89 8d a8 fd ff ff    	mov    %ecx,-0x258(%rbp)
    7fc7d891777c:	8b 8d a0 fe ff ff    	mov    -0x160(%rbp),%ecx
    7fc7d8917782:	0f b6 c9             	movzbl %cl,%ecx
    7fc7d8917785:	0f be c9             	movsbl %cl,%ecx
    7fc7d8917788:	8b 95 d0 fe ff ff    	mov    -0x130(%rbp),%edx
    7fc7d891778e:	0f b6 d2             	movzbl %dl,%edx
    7fc7d8917791:	0f be d2             	movsbl %dl,%edx
    7fc7d8917794:	0f af ca             	imul   %edx,%ecx
    7fc7d8917797:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d891779d:	8b 95 90 fe ff ff    	mov    -0x170(%rbp),%edx
    7fc7d89177a3:	03 ca                	add    %edx,%ecx
    7fc7d89177a5:	81 e1 ff ff ff 00    	and    $0xffffff,%ecx
    7fc7d89177ab:	89 8d a0 fd ff ff    	mov    %ecx,-0x260(%rbp)
    7fc7d89177b1:	85 c0                	test   %eax,%eax
    7fc7d89177b3:	0f 84 a3 03 00 00    	je     0x7fc7d8917b5c
    7fc7d89177b9:	41 c7 87 98 01 00 00 	movl   $0x0,0x198(%r15)
    7fc7d89177c0:	00 00 00 00 
    7fc7d89177c4:	c7 85 90 fe ff ff 00 	movl   $0x0,-0x170(%rbp)
    7fc7d89177cb:	00 00 00 
    7fc7d89177ce:	41 c7 87 90 01 00 00 	movl   $0x0,0x190(%r15)
    7fc7d89177d5:	00 00 00 00 
    7fc7d89177d9:	c7 85 98 fe ff ff 00 	movl   $0x0,-0x168(%rbp)
    7fc7d89177e0:	00 00 00 
    7fc7d89177e3:	41 c7 87 88 01 00 00 	movl   $0x0,0x188(%r15)
    7fc7d89177ea:	00 00 00 00 
    7fc7d89177ee:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7fc7d89177f5:	00 00 00 
    7fc7d89177f8:	41 c7 87 80 01 00 00 	movl   $0x0,0x180(%r15)
    7fc7d89177ff:	00 00 00 00 
    7fc7d8917803:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7fc7d891780a:	00 00 00 
    7fc7d891780d:	41 c7 87 78 01 00 00 	movl   $0x0,0x178(%r15)
    7fc7d8917814:	00 00 00 00 
    7fc7d8917818:	c7 85 b0 fe ff ff 00 	movl   $0x0,-0x150(%rbp)
    7fc7d891781f:	00 00 00 
    7fc7d8917822:	41 c7 87 70 01 00 00 	movl   $0x0,0x170(%r15)
    7fc7d8917829:	00 00 00 00 
    7fc7d891782d:	c7 85 b8 fe ff ff 00 	movl   $0x0,-0x148(%rbp)
    7fc7d8917834:	00 00 00 
    7fc7d8917837:	41 c7 87 68 01 00 00 	movl   $0x0,0x168(%r15)
    7fc7d891783e:	00 00 00 00 
    7fc7d8917842:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7fc7d8917849:	00 00 00 
    7fc7d891784c:	41 c7 87 60 01 00 00 	movl   $0x0,0x160(%r15)
    7fc7d8917853:	00 00 00 00 
    7fc7d8917857:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7fc7d891785e:	00 00 00 
    7fc7d8917861:	41 c7 87 58 01 00 00 	movl   $0x0,0x158(%r15)
    7fc7d8917868:	00 00 00 00 
    7fc7d891786c:	c7 85 d0 fe ff ff 00 	movl   $0x0,-0x130(%rbp)
    7fc7d8917873:	00 00 00 
    7fc7d8917876:	41 c7 87 50 01 00 00 	movl   $0x0,0x150(%r15)
    7fc7d891787d:	00 00 00 00 
    7fc7d8917881:	c7 85 d8 fe ff ff 00 	movl   $0x0,-0x128(%rbp)
    7fc7d8917888:	00 00 00 
    7fc7d891788b:	41 c7 87 48 01 00 00 	movl   $0x0,0x148(%r15)
    7fc7d8917892:	00 00 00 00 
    7fc7d8917896:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7fc7d891789d:	00 00 00 
    7fc7d89178a0:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7fc7d89178a7:	00 00 00 00 
    7fc7d89178ab:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7fc7d89178b2:	00 00 00 
    7fc7d89178b5:	41 c7 87 38 01 00 00 	movl   $0x0,0x138(%r15)
    7fc7d89178bc:	00 00 00 00 
    7fc7d89178c0:	c7 85 f0 fe ff ff 00 	movl   $0x0,-0x110(%rbp)
    7fc7d89178c7:	00 00 00 
    7fc7d89178ca:	41 c7 87 30 01 00 00 	movl   $0x0,0x130(%r15)
    7fc7d89178d1:	00 00 00 00 
    7fc7d89178d5:	c7 85 f8 fe ff ff 00 	movl   $0x0,-0x108(%rbp)
    7fc7d89178dc:	00 00 00 
    7fc7d89178df:	41 c7 87 28 01 00 00 	movl   $0x0,0x128(%r15)
    7fc7d89178e6:	00 00 00 00 
    7fc7d89178ea:	c7 85 00 ff ff ff 00 	movl   $0x0,-0x100(%rbp)
    7fc7d89178f1:	00 00 00 
    7fc7d89178f4:	41 c7 87 20 01 00 00 	movl   $0x0,0x120(%r15)
    7fc7d89178fb:	00 00 00 00 
    7fc7d89178ff:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7fc7d8917906:	00 00 00 
    7fc7d8917909:	41 c7 87 18 01 00 00 	movl   $0x0,0x118(%r15)
    7fc7d8917910:	00 00 00 00 
    7fc7d8917914:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7fc7d891791b:	00 00 00 
    7fc7d891791e:	41 c7 87 10 01 00 00 	movl   $0x0,0x110(%r15)
    7fc7d8917925:	00 00 00 00 
    7fc7d8917929:	c7 85 18 ff ff ff 00 	movl   $0x0,-0xe8(%rbp)
    7fc7d8917930:	00 00 00 
    7fc7d8917933:	41 c7 87 08 01 00 00 	movl   $0x0,0x108(%r15)
    7fc7d891793a:	00 00 00 00 
    7fc7d891793e:	c7 85 20 ff ff ff 00 	movl   $0x0,-0xe0(%rbp)
    7fc7d8917945:	00 00 00 
    7fc7d8917948:	41 c7 87 00 01 00 00 	movl   $0x0,0x100(%r15)
    7fc7d891794f:	00 00 00 00 
    7fc7d8917953:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7fc7d891795a:	00 00 00 
    7fc7d891795d:	41 c7 87 f8 00 00 00 	movl   $0x0,0xf8(%r15)
    7fc7d8917964:	00 00 00 00 
    7fc7d8917968:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7fc7d891796f:	00 00 00 
    7fc7d8917972:	41 c7 87 f0 00 00 00 	movl   $0x0,0xf0(%r15)
    7fc7d8917979:	00 00 00 00 
    7fc7d891797d:	c7 85 38 ff ff ff 00 	movl   $0x0,-0xc8(%rbp)
    7fc7d8917984:	00 00 00 
    7fc7d8917987:	41 c7 87 e8 00 00 00 	movl   $0x0,0xe8(%r15)
    7fc7d891798e:	00 00 00 00 
    7fc7d8917992:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7fc7d8917999:	00 00 00 
    7fc7d891799c:	41 c7 87 e0 00 00 00 	movl   $0x0,0xe0(%r15)
    7fc7d89179a3:	00 00 00 00 
    7fc7d89179a7:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7fc7d89179ae:	00 00 00 
    7fc7d89179b1:	41 c7 87 d8 00 00 00 	movl   $0x0,0xd8(%r15)
    7fc7d89179b8:	00 00 00 00 
    7fc7d89179bc:	33 db                	xor    %ebx,%ebx
    7fc7d89179be:	41 c7 87 d0 00 00 00 	movl   $0x0,0xd0(%r15)
    7fc7d89179c5:	00 00 00 00 
    7fc7d89179c9:	45 33 e4             	xor    %r12d,%r12d
    7fc7d89179cc:	41 c7 87 c8 00 00 00 	movl   $0x0,0xc8(%r15)
    7fc7d89179d3:	00 00 00 00 
    7fc7d89179d7:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7fc7d89179de:	00 00 00 
    7fc7d89179e1:	41 c7 87 c0 00 00 00 	movl   $0x0,0xc0(%r15)
    7fc7d89179e8:	00 00 00 00 
    7fc7d89179ec:	c7 85 58 ff ff ff 00 	movl   $0x0,-0xa8(%rbp)
    7fc7d89179f3:	00 00 00 
    7fc7d89179f6:	41 c7 87 b8 00 00 00 	movl   $0x0,0xb8(%r15)
    7fc7d89179fd:	00 00 00 00 
    7fc7d8917a01:	c7 85 60 ff ff ff 00 	movl   $0x0,-0xa0(%rbp)
    7fc7d8917a08:	00 00 00 
    7fc7d8917a0b:	41 c7 87 b0 00 00 00 	movl   $0x0,0xb0(%r15)
    7fc7d8917a12:	00 00 00 00 
    7fc7d8917a16:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7fc7d8917a1d:	00 00 00 
    7fc7d8917a20:	41 c7 87 a8 00 00 00 	movl   $0x0,0xa8(%r15)
    7fc7d8917a27:	00 00 00 00 
    7fc7d8917a2b:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7fc7d8917a32:	00 00 00 
    7fc7d8917a35:	41 c7 87 a0 00 00 00 	movl   $0x0,0xa0(%r15)
    7fc7d8917a3c:	00 00 00 00 
    7fc7d8917a40:	c7 85 78 ff ff ff 00 	movl   $0x0,-0x88(%rbp)
    7fc7d8917a47:	00 00 00 
    7fc7d8917a4a:	41 c7 87 98 00 00 00 	movl   $0x0,0x98(%r15)
    7fc7d8917a51:	00 00 00 00 
    7fc7d8917a55:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
    7fc7d8917a5c:	41 c7 87 90 00 00 00 	movl   $0x0,0x90(%r15)
    7fc7d8917a63:	00 00 00 00 
    7fc7d8917a67:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
    7fc7d8917a6e:	41 c7 87 88 00 00 00 	movl   $0x0,0x88(%r15)
    7fc7d8917a75:	00 00 00 00 
    7fc7d8917a79:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7fc7d8917a80:	41 c7 87 80 00 00 00 	movl   $0x0,0x80(%r15)
    7fc7d8917a87:	00 00 00 00 
    7fc7d8917a8b:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fc7d8917a92:	41 c7 47 78 00 00 00 	movl   $0x0,0x78(%r15)
    7fc7d8917a99:	00 
    7fc7d8917a9a:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7fc7d8917aa1:	41 c7 47 70 00 00 00 	movl   $0x0,0x70(%r15)
    7fc7d8917aa8:	00 
    7fc7d8917aa9:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
    7fc7d8917ab0:	41 c7 47 68 00 00 00 	movl   $0x0,0x68(%r15)
    7fc7d8917ab7:	00 
    7fc7d8917ab8:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7fc7d8917abf:	41 c7 47 60 00 00 00 	movl   $0x0,0x60(%r15)
    7fc7d8917ac6:	00 
    7fc7d8917ac7:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7fc7d8917ace:	41 c7 47 58 00 00 00 	movl   $0x0,0x58(%r15)
    7fc7d8917ad5:	00 
    7fc7d8917ad6:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    7fc7d8917add:	41 c7 47 48 00 00 00 	movl   $0x0,0x48(%r15)
    7fc7d8917ae4:	00 
    7fc7d8917ae5:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
    7fc7d8917aec:	41 c7 47 50 00 00 00 	movl   $0x0,0x50(%r15)
    7fc7d8917af3:	00 
    7fc7d8917af4:	41 c7 47 38 00 00 00 	movl   $0x0,0x38(%r15)
    7fc7d8917afb:	00 
    7fc7d8917afc:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7fc7d8917b03:	41 c7 47 40 00 00 00 	movl   $0x0,0x40(%r15)
    7fc7d8917b0a:	00 
    7fc7d8917b0b:	41 c7 47 30 00 00 00 	movl   $0x0,0x30(%r15)
    7fc7d8917b12:	00 
    7fc7d8917b13:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7fc7d8917b1a:	41 c7 47 20 00 00 00 	movl   $0x0,0x20(%r15)
    7fc7d8917b21:	00 
    7fc7d8917b22:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
    7fc7d8917b29:	41 c7 47 28 00 00 00 	movl   $0x0,0x28(%r15)
    7fc7d8917b30:	00 
    7fc7d8917b31:	41 c7 47 10 00 00 00 	movl   $0x0,0x10(%r15)
    7fc7d8917b38:	00 
    7fc7d8917b39:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
    7fc7d8917b40:	41 c7 47 18 00 00 00 	movl   $0x0,0x18(%r15)
    7fc7d8917b47:	00 
    7fc7d8917b48:	41 c7 47 08 00 00 00 	movl   $0x0,0x8(%r15)
    7fc7d8917b4f:	00 
    7fc7d8917b50:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7fc7d8917b57:	e9 4f 03 00 00       	jmpq   0x7fc7d8917eab
    7fc7d8917b5c:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7fc7d8917b62:	85 c0                	test   %eax,%eax
    7fc7d8917b64:	0f 84 41 03 00 00    	je     0x7fc7d8917eab
    7fc7d8917b6a:	8b 85 a0 fd ff ff    	mov    -0x260(%rbp),%eax
    7fc7d8917b70:	41 89 87 98 01 00 00 	mov    %eax,0x198(%r15)
    7fc7d8917b77:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fc7d8917b7d:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7fc7d8917b83:	41 89 87 90 01 00 00 	mov    %eax,0x190(%r15)
    7fc7d8917b8a:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fc7d8917b90:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7fc7d8917b96:	41 89 87 88 01 00 00 	mov    %eax,0x188(%r15)
    7fc7d8917b9d:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fc7d8917ba3:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fc7d8917ba9:	41 89 87 80 01 00 00 	mov    %eax,0x180(%r15)
    7fc7d8917bb0:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fc7d8917bb6:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fc7d8917bbc:	41 89 87 78 01 00 00 	mov    %eax,0x178(%r15)
    7fc7d8917bc3:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fc7d8917bc9:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7fc7d8917bcf:	41 89 87 70 01 00 00 	mov    %eax,0x170(%r15)
    7fc7d8917bd6:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fc7d8917bdc:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7fc7d8917bdf:	41 89 87 68 01 00 00 	mov    %eax,0x168(%r15)
    7fc7d8917be6:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fc7d8917bec:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fc7d8917bf2:	41 89 87 60 01 00 00 	mov    %eax,0x160(%r15)
    7fc7d8917bf9:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fc7d8917bff:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fc7d8917c05:	41 89 87 58 01 00 00 	mov    %eax,0x158(%r15)
    7fc7d8917c0c:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fc7d8917c12:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7fc7d8917c18:	41 89 87 50 01 00 00 	mov    %eax,0x150(%r15)
    7fc7d8917c1f:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fc7d8917c25:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fc7d8917c2b:	41 89 87 48 01 00 00 	mov    %eax,0x148(%r15)
    7fc7d8917c32:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fc7d8917c38:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fc7d8917c3e:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7fc7d8917c45:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fc7d8917c4b:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7fc7d8917c51:	41 89 87 38 01 00 00 	mov    %eax,0x138(%r15)
    7fc7d8917c58:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7fc7d8917c5e:	41 89 9f 30 01 00 00 	mov    %ebx,0x130(%r15)
    7fc7d8917c65:	8b c3                	mov    %ebx,%eax
    7fc7d8917c67:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fc7d8917c6d:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fc7d8917c73:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7fc7d8917c7a:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fc7d8917c80:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fc7d8917c86:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7fc7d8917c8d:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fc7d8917c93:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fc7d8917c99:	41 89 87 18 01 00 00 	mov    %eax,0x118(%r15)
    7fc7d8917ca0:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fc7d8917ca6:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fc7d8917ca9:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7fc7d8917cb0:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fc7d8917cb6:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7fc7d8917cbc:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7fc7d8917cc3:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fc7d8917cc9:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fc7d8917ccf:	41 89 87 00 01 00 00 	mov    %eax,0x100(%r15)
    7fc7d8917cd6:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fc7d8917cdc:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7fc7d8917ce2:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7fc7d8917ce9:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fc7d8917cef:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fc7d8917cf2:	41 89 87 f0 00 00 00 	mov    %eax,0xf0(%r15)
    7fc7d8917cf9:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fc7d8917cff:	45 89 a7 e8 00 00 00 	mov    %r12d,0xe8(%r15)
    7fc7d8917d06:	41 8b c4             	mov    %r12d,%eax
    7fc7d8917d09:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fc7d8917d0f:	8b 85 f0 fd ff ff    	mov    -0x210(%rbp),%eax
    7fc7d8917d15:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7fc7d8917d1c:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fc7d8917d22:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fc7d8917d25:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7fc7d8917d2c:	48 8b d8             	mov    %rax,%rbx
    7fc7d8917d2f:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fc7d8917d35:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7fc7d8917d3c:	4c 8b e0             	mov    %rax,%r12
    7fc7d8917d3f:	8b 85 f8 fd ff ff    	mov    -0x208(%rbp),%eax
    7fc7d8917d45:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7fc7d8917d4c:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7fc7d8917d52:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fc7d8917d55:	41 89 87 c0 00 00 00 	mov    %eax,0xc0(%r15)
    7fc7d8917d5c:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fc7d8917d62:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fc7d8917d65:	41 89 87 b8 00 00 00 	mov    %eax,0xb8(%r15)
    7fc7d8917d6c:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7fc7d8917d72:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7fc7d8917d78:	41 89 87 b0 00 00 00 	mov    %eax,0xb0(%r15)
    7fc7d8917d7f:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fc7d8917d85:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fc7d8917d88:	41 89 87 a8 00 00 00 	mov    %eax,0xa8(%r15)
    7fc7d8917d8f:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fc7d8917d95:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fc7d8917d9b:	41 89 87 a0 00 00 00 	mov    %eax,0xa0(%r15)
    7fc7d8917da2:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fc7d8917da8:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7fc7d8917dab:	41 89 87 98 00 00 00 	mov    %eax,0x98(%r15)
    7fc7d8917db2:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fc7d8917db5:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fc7d8917db8:	41 89 87 90 00 00 00 	mov    %eax,0x90(%r15)
    7fc7d8917dbf:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fc7d8917dc2:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fc7d8917dc8:	41 89 87 88 00 00 00 	mov    %eax,0x88(%r15)
    7fc7d8917dcf:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fc7d8917dd2:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fc7d8917dd5:	41 89 87 80 00 00 00 	mov    %eax,0x80(%r15)
    7fc7d8917ddc:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fc7d8917ddf:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7fc7d8917de2:	41 89 47 78          	mov    %eax,0x78(%r15)
    7fc7d8917de6:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fc7d8917de9:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fc7d8917def:	41 89 47 70          	mov    %eax,0x70(%r15)
    7fc7d8917df3:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fc7d8917df6:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fc7d8917dfc:	41 89 47 68          	mov    %eax,0x68(%r15)
    7fc7d8917e00:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fc7d8917e03:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7fc7d8917e09:	41 89 47 60          	mov    %eax,0x60(%r15)
    7fc7d8917e0d:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fc7d8917e10:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7fc7d8917e16:	41 89 47 58          	mov    %eax,0x58(%r15)
    7fc7d8917e1a:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fc7d8917e1d:	41 8b 47 50          	mov    0x50(%r15),%eax
    7fc7d8917e21:	8b c8                	mov    %eax,%ecx
    7fc7d8917e23:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fc7d8917e29:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7fc7d8917e2d:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7fc7d8917e30:	c1 e8 08             	shr    $0x8,%eax
    7fc7d8917e33:	8b 8d 38 fe ff ff    	mov    -0x1c8(%rbp),%ecx
    7fc7d8917e39:	c1 e1 08             	shl    $0x8,%ecx
    7fc7d8917e3c:	0b c1                	or     %ecx,%eax
    7fc7d8917e3e:	41 89 47 50          	mov    %eax,0x50(%r15)
    7fc7d8917e42:	41 8b 47 40          	mov    0x40(%r15),%eax
    7fc7d8917e46:	41 89 47 38          	mov    %eax,0x38(%r15)
    7fc7d8917e4a:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fc7d8917e4d:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fc7d8917e53:	41 89 47 40          	mov    %eax,0x40(%r15)
    7fc7d8917e57:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7fc7d8917e5d:	41 89 47 30          	mov    %eax,0x30(%r15)
    7fc7d8917e61:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fc7d8917e64:	41 8b 47 28          	mov    0x28(%r15),%eax
    7fc7d8917e68:	8b c8                	mov    %eax,%ecx
    7fc7d8917e6a:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fc7d8917e70:	41 89 4f 20          	mov    %ecx,0x20(%r15)
    7fc7d8917e74:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7fc7d8917e77:	c1 e8 08             	shr    $0x8,%eax
    7fc7d8917e7a:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7fc7d8917e80:	c1 e1 08             	shl    $0x8,%ecx
    7fc7d8917e83:	0b c1                	or     %ecx,%eax
    7fc7d8917e85:	41 89 47 28          	mov    %eax,0x28(%r15)
    7fc7d8917e89:	41 8b 47 18          	mov    0x18(%r15),%eax
    7fc7d8917e8d:	41 89 47 10          	mov    %eax,0x10(%r15)
    7fc7d8917e91:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fc7d8917e94:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fc7d8917e9a:	41 89 47 18          	mov    %eax,0x18(%r15)
    7fc7d8917e9e:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7fc7d8917ea4:	41 89 47 08          	mov    %eax,0x8(%r15)
    7fc7d8917ea8:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fc7d8917eab:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fc7d8917eb1:	85 c0                	test   %eax,%eax
    7fc7d8917eb3:	0f 84 0f 00 00 00    	je     0x7fc7d8917ec8
    7fc7d8917eb9:	41 c7 07 00 00 00 00 	movl   $0x0,(%r15)
    7fc7d8917ec0:	45 33 f6             	xor    %r14d,%r14d
    7fc7d8917ec3:	e9 0c 00 00 00       	jmpq   0x7fc7d8917ed4
    7fc7d8917ec8:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fc7d8917ece:	41 89 07             	mov    %eax,(%r15)
    7fc7d8917ed1:	4c 8b f0             	mov    %rax,%r14
    7fc7d8917ed4:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fc7d8917ed7:	8b c0                	mov    %eax,%eax
    7fc7d8917ed9:	48 c1 e0 18          	shl    $0x18,%rax
    7fc7d8917edd:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fc7d8917ee0:	8b c9                	mov    %ecx,%ecx
    7fc7d8917ee2:	48 0b c1             	or     %rcx,%rax
    7fc7d8917ee5:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7fc7d8917eeb:	8b ca                	mov    %edx,%ecx
    7fc7d8917eed:	48 c1 e1 30          	shl    $0x30,%rcx
    7fc7d8917ef1:	48 0b c1             	or     %rcx,%rax
    7fc7d8917ef4:	49 89 87 a0 01 00 00 	mov    %rax,0x1a0(%r15)
    7fc7d8917efb:	c1 ea 10             	shr    $0x10,%edx
    7fc7d8917efe:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fc7d8917f04:	c1 e0 08             	shl    $0x8,%eax
    7fc7d8917f07:	0b d0                	or     %eax,%edx
    7fc7d8917f09:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fc7d8917f0f:	8b c0                	mov    %eax,%eax
    7fc7d8917f11:	48 c1 e0 20          	shl    $0x20,%rax
    7fc7d8917f15:	8b ca                	mov    %edx,%ecx
    7fc7d8917f17:	48 0b c1             	or     %rcx,%rax
    7fc7d8917f1a:	8b 95 48 ff ff ff    	mov    -0xb8(%rbp),%edx
    7fc7d8917f20:	8b ca                	mov    %edx,%ecx
    7fc7d8917f22:	48 c1 e1 38          	shl    $0x38,%rcx
    7fc7d8917f26:	48 0b c1             	or     %rcx,%rax
    7fc7d8917f29:	49 89 87 a8 01 00 00 	mov    %rax,0x1a8(%r15)
    7fc7d8917f30:	c1 ea 08             	shr    $0x8,%edx
    7fc7d8917f33:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fc7d8917f39:	8b c0                	mov    %eax,%eax
    7fc7d8917f3b:	48 c1 e0 10          	shl    $0x10,%rax
    7fc7d8917f3f:	8b ca                	mov    %edx,%ecx
    7fc7d8917f41:	48 0b c1             	or     %rcx,%rax
    7fc7d8917f44:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7fc7d8917f4a:	8b c9                	mov    %ecx,%ecx
    7fc7d8917f4c:	48 c1 e1 28          	shl    $0x28,%rcx
    7fc7d8917f50:	48 0b c1             	or     %rcx,%rax
    7fc7d8917f53:	49 89 87 b0 01 00 00 	mov    %rax,0x1b0(%r15)
    7fc7d8917f5a:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7fc7d8917f60:	8b c0                	mov    %eax,%eax
    7fc7d8917f62:	48 c1 e0 18          	shl    $0x18,%rax
    7fc7d8917f66:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7fc7d8917f6c:	8b c9                	mov    %ecx,%ecx
    7fc7d8917f6e:	48 0b c1             	or     %rcx,%rax
    7fc7d8917f71:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7fc7d8917f77:	8b ca                	mov    %edx,%ecx
    7fc7d8917f79:	48 c1 e1 30          	shl    $0x30,%rcx
    7fc7d8917f7d:	48 0b c1             	or     %rcx,%rax
    7fc7d8917f80:	49 89 87 b8 01 00 00 	mov    %rax,0x1b8(%r15)
    7fc7d8917f87:	c1 ea 10             	shr    $0x10,%edx
    7fc7d8917f8a:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fc7d8917f90:	c1 e0 08             	shl    $0x8,%eax
    7fc7d8917f93:	0b d0                	or     %eax,%edx
    7fc7d8917f95:	8b 85 b8 fe ff ff    	mov    -0x148(%rbp),%eax
    7fc7d8917f9b:	8b c0                	mov    %eax,%eax
    7fc7d8917f9d:	48 c1 e0 20          	shl    $0x20,%rax
    7fc7d8917fa1:	8b ca                	mov    %edx,%ecx
    7fc7d8917fa3:	48 0b c1             	or     %rcx,%rax
    7fc7d8917fa6:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7fc7d8917fac:	8b ca                	mov    %edx,%ecx
    7fc7d8917fae:	48 c1 e1 38          	shl    $0x38,%rcx
    7fc7d8917fb2:	48 0b c1             	or     %rcx,%rax
    7fc7d8917fb5:	49 89 87 c0 01 00 00 	mov    %rax,0x1c0(%r15)
    7fc7d8917fbc:	c1 ea 08             	shr    $0x8,%edx
    7fc7d8917fbf:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fc7d8917fc5:	8b c0                	mov    %eax,%eax
    7fc7d8917fc7:	48 c1 e0 10          	shl    $0x10,%rax
    7fc7d8917fcb:	8b ca                	mov    %edx,%ecx
    7fc7d8917fcd:	48 0b c1             	or     %rcx,%rax
    7fc7d8917fd0:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fc7d8917fd6:	8b c9                	mov    %ecx,%ecx
    7fc7d8917fd8:	48 c1 e1 28          	shl    $0x28,%rcx
    7fc7d8917fdc:	48 0b c1             	or     %rcx,%rax
    7fc7d8917fdf:	49 89 87 c8 01 00 00 	mov    %rax,0x1c8(%r15)
    7fc7d8917fe6:	49 8b 45 28          	mov    0x28(%r13),%rax
    7fc7d8917fea:	49 8b cf             	mov    %r15,%rcx
    7fc7d8917fed:	48 81 c1 a0 01 00 00 	add    $0x1a0,%rcx
    7fc7d8917ff4:	0f 10 01             	movups (%rcx),%xmm0
    7fc7d8917ff7:	0f 11 00             	movups %xmm0,(%rax)
    7fc7d8917ffa:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fc7d8917ffe:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fc7d8918002:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fc7d8918006:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fc7d891800a:	49 8b 45 30          	mov    0x30(%r13),%rax
    7fc7d891800e:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fc7d8918011:	89 08                	mov    %ecx,(%rax)
    7fc7d8918013:	33 c0                	xor    %eax,%eax
    7fc7d8918015:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fc7d8918019:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fc7d891801e:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fc7d8918023:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fc7d8918028:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fc7d891802d:	48 8b e5             	mov    %rbp,%rsp
    7fc7d8918030:	5d                   	pop    %rbp
    7fc7d8918031:	c3                   	retq   

end

