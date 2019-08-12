function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fdb8bfb112d <.text>:
    7fdb8bfb112d:	55                   	push   %rbp
    7fdb8bfb112e:	48 8b ec             	mov    %rsp,%rbp
    7fdb8bfb1131:	48 81 ec 40 06 00 00 	sub    $0x640,%rsp
    7fdb8bfb1138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fdb8bfb113c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fdb8bfb1141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fdb8bfb1146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fdb8bfb114b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fdb8bfb1150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fdb8bfb1154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fdb8bfb1158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fdb8bfb115c:	4c 8b 30             	mov    (%rax),%r14
    7fdb8bfb115f:	41 8b 87 c0 0c 00 00 	mov    0xcc0(%r15),%eax
    7fdb8bfb1166:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fdb8bfb1169:	41 8b 87 c8 0c 00 00 	mov    0xcc8(%r15),%eax
    7fdb8bfb1170:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fdb8bfb1173:	41 8b 87 d0 0c 00 00 	mov    0xcd0(%r15),%eax
    7fdb8bfb117a:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fdb8bfb117d:	41 8b 87 e0 0c 00 00 	mov    0xce0(%r15),%eax
    7fdb8bfb1184:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fdb8bfb1187:	49 8b 87 f0 0c 00 00 	mov    0xcf0(%r15),%rax
    7fdb8bfb118e:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    7fdb8bfb1192:	41 8b 87 f8 0c 00 00 	mov    0xcf8(%r15),%eax
    7fdb8bfb1199:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fdb8bfb119c:	41 8b 87 00 0d 00 00 	mov    0xd00(%r15),%eax
    7fdb8bfb11a3:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fdb8bfb11a6:	41 8b 87 08 0d 00 00 	mov    0xd08(%r15),%eax
    7fdb8bfb11ad:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fdb8bfb11b0:	41 8b 87 10 0d 00 00 	mov    0xd10(%r15),%eax
    7fdb8bfb11b7:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fdb8bfb11ba:	41 8b 87 58 0d 00 00 	mov    0xd58(%r15),%eax
    7fdb8bfb11c1:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fdb8bfb11c4:	41 8b 87 60 0d 00 00 	mov    0xd60(%r15),%eax
    7fdb8bfb11cb:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fdb8bfb11ce:	41 8b 87 68 0d 00 00 	mov    0xd68(%r15),%eax
    7fdb8bfb11d5:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fdb8bfb11d8:	41 8b 87 70 0d 00 00 	mov    0xd70(%r15),%eax
    7fdb8bfb11df:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fdb8bfb11e2:	41 8b 87 78 0d 00 00 	mov    0xd78(%r15),%eax
    7fdb8bfb11e9:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fdb8bfb11ec:	41 8b 87 80 0d 00 00 	mov    0xd80(%r15),%eax
    7fdb8bfb11f3:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fdb8bfb11f6:	41 8b 87 88 0d 00 00 	mov    0xd88(%r15),%eax
    7fdb8bfb11fd:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fdb8bfb1203:	41 8b 87 90 0d 00 00 	mov    0xd90(%r15),%eax
    7fdb8bfb120a:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fdb8bfb1210:	41 8b 87 98 0d 00 00 	mov    0xd98(%r15),%eax
    7fdb8bfb1217:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fdb8bfb121d:	49 8b 87 20 0e 00 00 	mov    0xe20(%r15),%rax
    7fdb8bfb1224:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
    7fdb8bfb122b:	41 8b 87 28 0e 00 00 	mov    0xe28(%r15),%eax
    7fdb8bfb1232:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fdb8bfb1238:	41 8b 87 30 0e 00 00 	mov    0xe30(%r15),%eax
    7fdb8bfb123f:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7fdb8bfb1245:	41 8b 87 38 0e 00 00 	mov    0xe38(%r15),%eax
    7fdb8bfb124c:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fdb8bfb1252:	41 8b 87 40 0e 00 00 	mov    0xe40(%r15),%eax
    7fdb8bfb1259:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fdb8bfb125f:	41 8b 87 88 0e 00 00 	mov    0xe88(%r15),%eax
    7fdb8bfb1266:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fdb8bfb126c:	41 8b 87 90 0e 00 00 	mov    0xe90(%r15),%eax
    7fdb8bfb1273:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fdb8bfb1279:	41 8b 87 98 0e 00 00 	mov    0xe98(%r15),%eax
    7fdb8bfb1280:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fdb8bfb1286:	41 8b 87 a0 0e 00 00 	mov    0xea0(%r15),%eax
    7fdb8bfb128d:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fdb8bfb1293:	41 8b 87 a8 0e 00 00 	mov    0xea8(%r15),%eax
    7fdb8bfb129a:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fdb8bfb12a0:	41 8b 87 b0 0e 00 00 	mov    0xeb0(%r15),%eax
    7fdb8bfb12a7:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fdb8bfb12ad:	41 8b 87 b8 0e 00 00 	mov    0xeb8(%r15),%eax
    7fdb8bfb12b4:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fdb8bfb12ba:	41 8b 87 c0 0e 00 00 	mov    0xec0(%r15),%eax
    7fdb8bfb12c1:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fdb8bfb12c7:	41 8b 87 c8 0e 00 00 	mov    0xec8(%r15),%eax
    7fdb8bfb12ce:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fdb8bfb12d4:	49 8b 87 50 0f 00 00 	mov    0xf50(%r15),%rax
    7fdb8bfb12db:	48 89 85 f0 fe ff ff 	mov    %rax,-0x110(%rbp)
    7fdb8bfb12e2:	41 8b 87 58 0f 00 00 	mov    0xf58(%r15),%eax
    7fdb8bfb12e9:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fdb8bfb12ef:	41 8b 87 60 0f 00 00 	mov    0xf60(%r15),%eax
    7fdb8bfb12f6:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fdb8bfb12fc:	41 8b 87 68 0f 00 00 	mov    0xf68(%r15),%eax
    7fdb8bfb1303:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fdb8bfb1309:	41 8b 87 70 0f 00 00 	mov    0xf70(%r15),%eax
    7fdb8bfb1310:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fdb8bfb1316:	41 8b 87 b8 0f 00 00 	mov    0xfb8(%r15),%eax
    7fdb8bfb131d:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fdb8bfb1323:	41 8b 87 c0 0f 00 00 	mov    0xfc0(%r15),%eax
    7fdb8bfb132a:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fdb8bfb1330:	41 8b 87 c8 0f 00 00 	mov    0xfc8(%r15),%eax
    7fdb8bfb1337:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fdb8bfb133d:	45 8b a7 d0 0f 00 00 	mov    0xfd0(%r15),%r12d
    7fdb8bfb1344:	41 8b 87 d8 0f 00 00 	mov    0xfd8(%r15),%eax
    7fdb8bfb134b:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fdb8bfb1351:	41 8b 87 e0 0f 00 00 	mov    0xfe0(%r15),%eax
    7fdb8bfb1358:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fdb8bfb135e:	41 8b 87 e8 0f 00 00 	mov    0xfe8(%r15),%eax
    7fdb8bfb1365:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fdb8bfb136b:	41 8b 87 f0 0f 00 00 	mov    0xff0(%r15),%eax
    7fdb8bfb1372:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fdb8bfb1378:	41 8b 87 f8 0f 00 00 	mov    0xff8(%r15),%eax
    7fdb8bfb137f:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fdb8bfb1385:	41 8b 87 00 10 00 00 	mov    0x1000(%r15),%eax
    7fdb8bfb138c:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fdb8bfb1392:	49 8b 86 90 00 00 00 	mov    0x90(%r14),%rax
    7fdb8bfb1399:	8b 00                	mov    (%rax),%eax
    7fdb8bfb139b:	41 8b 8f 48 13 00 00 	mov    0x1348(%r15),%ecx
    7fdb8bfb13a2:	33 c8                	xor    %eax,%ecx
    7fdb8bfb13a4:	23 c8                	and    %eax,%ecx
    7fdb8bfb13a6:	41 89 87 48 13 00 00 	mov    %eax,0x1348(%r15)
    7fdb8bfb13ad:	85 c9                	test   %ecx,%ecx
    7fdb8bfb13af:	0f 84 43 22 00 00    	je     0x7fdb8bfb35f8
    7fdb8bfb13b5:	49 8b 46 20          	mov    0x20(%r14),%rax
    7fdb8bfb13b9:	8b 00                	mov    (%rax),%eax
    7fdb8bfb13bb:	c7 85 80 fe ff ff 01 	movl   $0x1,-0x180(%rbp)
    7fdb8bfb13c2:	00 00 00 
    7fdb8bfb13c5:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fdb8bfb13cb:	85 c0                	test   %eax,%eax
    7fdb8bfb13cd:	0f 85 09 00 00 00    	jne    0x7fdb8bfb13dc
    7fdb8bfb13d3:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb13d6:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fdb8bfb13dc:	33 c0                	xor    %eax,%eax
    7fdb8bfb13de:	3b 45 e8             	cmp    -0x18(%rbp),%eax
    7fdb8bfb13e1:	0f 94 c0             	sete   %al
    7fdb8bfb13e4:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb13e7:	c7 85 70 fe ff ff 02 	movl   $0x2,-0x190(%rbp)
    7fdb8bfb13ee:	00 00 00 
    7fdb8bfb13f1:	85 c0                	test   %eax,%eax
    7fdb8bfb13f3:	0f 85 09 00 00 00    	jne    0x7fdb8bfb1402
    7fdb8bfb13f9:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb13fc:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fdb8bfb1402:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fdb8bfb1408:	85 c0                	test   %eax,%eax
    7fdb8bfb140a:	0f 94 c0             	sete   %al
    7fdb8bfb140d:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1410:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7fdb8bfb1414:	8b 09                	mov    (%rcx),%ecx
    7fdb8bfb1416:	23 c1                	and    %ecx,%eax
    7fdb8bfb1418:	c7 85 68 fe ff ff 00 	movl   $0x0,-0x198(%rbp)
    7fdb8bfb141f:	00 00 00 
    7fdb8bfb1422:	85 c0                	test   %eax,%eax
    7fdb8bfb1424:	0f 85 09 00 00 00    	jne    0x7fdb8bfb1433
    7fdb8bfb142a:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb142d:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7fdb8bfb1433:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb1436:	85 c0                	test   %eax,%eax
    7fdb8bfb1438:	0f 84 26 00 00 00    	je     0x7fdb8bfb1464
    7fdb8bfb143e:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb1441:	83 f8 01             	cmp    $0x1,%eax
    7fdb8bfb1444:	0f 84 2b 00 00 00    	je     0x7fdb8bfb1475
    7fdb8bfb144a:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb144d:	83 f8 02             	cmp    $0x2,%eax
    7fdb8bfb1450:	0f 84 30 00 00 00    	je     0x7fdb8bfb1486
    7fdb8bfb1456:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb1459:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fdb8bfb145f:	e9 2e 00 00 00       	jmpq   0x7fdb8bfb1492
    7fdb8bfb1464:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fdb8bfb146a:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fdb8bfb1470:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb1492
    7fdb8bfb1475:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fdb8bfb147b:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fdb8bfb1481:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb1492
    7fdb8bfb1486:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fdb8bfb148c:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fdb8bfb1492:	49 8b 86 98 00 00 00 	mov    0x98(%r14),%rax
    7fdb8bfb1499:	44 8b 28             	mov    (%rax),%r13d
    7fdb8bfb149c:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb149f:	85 c0                	test   %eax,%eax
    7fdb8bfb14a1:	0f 94 c0             	sete   %al
    7fdb8bfb14a4:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb14a7:	8b 8d 78 fe ff ff    	mov    -0x188(%rbp),%ecx
    7fdb8bfb14ad:	23 c1                	and    %ecx,%eax
    7fdb8bfb14af:	49 8b 4e 18          	mov    0x18(%r14),%rcx
    7fdb8bfb14b3:	8b 09                	mov    (%rcx),%ecx
    7fdb8bfb14b5:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7fdb8bfb14bb:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7fdb8bfb14c1:	85 c9                	test   %ecx,%ecx
    7fdb8bfb14c3:	0f 94 c1             	sete   %cl
    7fdb8bfb14c6:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb14c9:	8b 95 a8 fe ff ff    	mov    -0x158(%rbp),%edx
    7fdb8bfb14cf:	85 d2                	test   %edx,%edx
    7fdb8bfb14d1:	0f 94 c2             	sete   %dl
    7fdb8bfb14d4:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb14d7:	89 95 50 fe ff ff    	mov    %edx,-0x1b0(%rbp)
    7fdb8bfb14dd:	0b ca                	or     %edx,%ecx
    7fdb8bfb14df:	89 8d 48 fe ff ff    	mov    %ecx,-0x1b8(%rbp)
    7fdb8bfb14e5:	23 4d d8             	and    -0x28(%rbp),%ecx
    7fdb8bfb14e8:	89 8d 40 fe ff ff    	mov    %ecx,-0x1c0(%rbp)
    7fdb8bfb14ee:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7fdb8bfb14f1:	ff c9                	dec    %ecx
    7fdb8bfb14f3:	89 8d 38 fe ff ff    	mov    %ecx,-0x1c8(%rbp)
    7fdb8bfb14f9:	48 8b d8             	mov    %rax,%rbx
    7fdb8bfb14fc:	85 c0                	test   %eax,%eax
    7fdb8bfb14fe:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1520
    7fdb8bfb1504:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fdb8bfb150a:	85 c0                	test   %eax,%eax
    7fdb8bfb150c:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1531
    7fdb8bfb1512:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7fdb8bfb1515:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fdb8bfb151b:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb153d
    7fdb8bfb1520:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fdb8bfb1526:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fdb8bfb152c:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb153d
    7fdb8bfb1531:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7fdb8bfb1537:	89 85 30 fe ff ff    	mov    %eax,-0x1d0(%rbp)
    7fdb8bfb153d:	41 8b 87 18 0d 00 00 	mov    0xd18(%r15),%eax
    7fdb8bfb1544:	41 8b 8f 48 0e 00 00 	mov    0xe48(%r15),%ecx
    7fdb8bfb154b:	03 c1                	add    %ecx,%eax
    7fdb8bfb154d:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7fdb8bfb1553:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fdb8bfb1556:	85 c0                	test   %eax,%eax
    7fdb8bfb1558:	0f 94 c0             	sete   %al
    7fdb8bfb155b:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb155e:	8b 8d 48 fe ff ff    	mov    -0x1b8(%rbp),%ecx
    7fdb8bfb1564:	0b c1                	or     %ecx,%eax
    7fdb8bfb1566:	89 85 20 fe ff ff    	mov    %eax,-0x1e0(%rbp)
    7fdb8bfb156c:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fdb8bfb156f:	23 85 38 ff ff ff    	and    -0xc8(%rbp),%eax
    7fdb8bfb1575:	89 85 18 fe ff ff    	mov    %eax,-0x1e8(%rbp)
    7fdb8bfb157b:	49 8b 46 08          	mov    0x8(%r14),%rax
    7fdb8bfb157f:	48 8b 00             	mov    (%rax),%rax
    7fdb8bfb1582:	48 89 85 10 fe ff ff 	mov    %rax,-0x1f0(%rbp)
    7fdb8bfb1589:	49 8b 46 60          	mov    0x60(%r14),%rax
    7fdb8bfb158d:	8b 00                	mov    (%rax),%eax
    7fdb8bfb158f:	85 c0                	test   %eax,%eax
    7fdb8bfb1591:	0f 94 c0             	sete   %al
    7fdb8bfb1594:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1597:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fdb8bfb159a:	23 c1                	and    %ecx,%eax
    7fdb8bfb159c:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7fdb8bfb15a2:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fdb8bfb15a5:	8b c0                	mov    %eax,%eax
    7fdb8bfb15a7:	48 c1 e0 06          	shl    $0x6,%rax
    7fdb8bfb15ab:	48 89 85 00 fe ff ff 	mov    %rax,-0x200(%rbp)
    7fdb8bfb15b2:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
    7fdb8bfb15b6:	48 03 c1             	add    %rcx,%rax
    7fdb8bfb15b9:	48 89 85 f8 fd ff ff 	mov    %rax,-0x208(%rbp)
    7fdb8bfb15c0:	85 db                	test   %ebx,%ebx
    7fdb8bfb15c2:	0f 85 1e 00 00 00    	jne    0x7fdb8bfb15e6
    7fdb8bfb15c8:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fdb8bfb15ce:	85 c0                	test   %eax,%eax
    7fdb8bfb15d0:	0f 85 23 00 00 00    	jne    0x7fdb8bfb15f9
    7fdb8bfb15d6:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    7fdb8bfb15da:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7fdb8bfb15e1:	e9 21 00 00 00       	jmpq   0x7fdb8bfb1607
    7fdb8bfb15e6:	48 8b 85 10 fe ff ff 	mov    -0x1f0(%rbp),%rax
    7fdb8bfb15ed:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7fdb8bfb15f4:	e9 0e 00 00 00       	jmpq   0x7fdb8bfb1607
    7fdb8bfb15f9:	48 8b 85 f8 fd ff ff 	mov    -0x208(%rbp),%rax
    7fdb8bfb1600:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
    7fdb8bfb1607:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fdb8bfb160a:	85 c0                	test   %eax,%eax
    7fdb8bfb160c:	0f 94 c0             	sete   %al
    7fdb8bfb160f:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1612:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7fdb8bfb1615:	85 d2                	test   %edx,%edx
    7fdb8bfb1617:	0f 94 c1             	sete   %cl
    7fdb8bfb161a:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb161d:	8b 75 a0             	mov    -0x60(%rbp),%esi
    7fdb8bfb1620:	83 fe 0f             	cmp    $0xf,%esi
    7fdb8bfb1623:	40 0f 94 c6          	sete   %sil
    7fdb8bfb1627:	40 0f b6 f6          	movzbl %sil,%esi
    7fdb8bfb162b:	8b bd 38 ff ff ff    	mov    -0xc8(%rbp),%edi
    7fdb8bfb1631:	85 ff                	test   %edi,%edi
    7fdb8bfb1633:	40 0f 94 c7          	sete   %dil
    7fdb8bfb1637:	40 0f b6 ff          	movzbl %dil,%edi
    7fdb8bfb163b:	23 d7                	and    %edi,%edx
    7fdb8bfb163d:	85 d2                	test   %edx,%edx
    7fdb8bfb163f:	0f 94 c2             	sete   %dl
    7fdb8bfb1642:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb1645:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7fdb8bfb164b:	23 d7                	and    %edi,%edx
    7fdb8bfb164d:	89 95 e8 fd ff ff    	mov    %edx,-0x218(%rbp)
    7fdb8bfb1653:	23 f2                	and    %edx,%esi
    7fdb8bfb1655:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fdb8bfb165b:	89 b5 d8 fd ff ff    	mov    %esi,-0x228(%rbp)
    7fdb8bfb1661:	0b ce                	or     %esi,%ecx
    7fdb8bfb1663:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7fdb8bfb1669:	89 8d c8 fd ff ff    	mov    %ecx,-0x238(%rbp)
    7fdb8bfb166f:	23 c1                	and    %ecx,%eax
    7fdb8bfb1671:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7fdb8bfb1674:	03 4d b0             	add    -0x50(%rbp),%ecx
    7fdb8bfb1677:	83 e1 1f             	and    $0x1f,%ecx
    7fdb8bfb167a:	89 8d c0 fd ff ff    	mov    %ecx,-0x240(%rbp)
    7fdb8bfb1680:	ff c9                	dec    %ecx
    7fdb8bfb1682:	83 e1 1f             	and    $0x1f,%ecx
    7fdb8bfb1685:	89 8d b8 fd ff ff    	mov    %ecx,-0x248(%rbp)
    7fdb8bfb168b:	89 85 b0 fd ff ff    	mov    %eax,-0x250(%rbp)
    7fdb8bfb1691:	85 c0                	test   %eax,%eax
    7fdb8bfb1693:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb16a5
    7fdb8bfb1699:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fdb8bfb169f:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7fdb8bfb16a5:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7fdb8bfb16a8:	ff c8                	dec    %eax
    7fdb8bfb16aa:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb16ad:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7fdb8bfb16b3:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fdb8bfb16b9:	85 c0                	test   %eax,%eax
    7fdb8bfb16bb:	0f 85 09 00 00 00    	jne    0x7fdb8bfb16ca
    7fdb8bfb16c1:	8b 45 c8             	mov    -0x38(%rbp),%eax
    7fdb8bfb16c4:	89 85 a8 fd ff ff    	mov    %eax,-0x258(%rbp)
    7fdb8bfb16ca:	85 db                	test   %ebx,%ebx
    7fdb8bfb16cc:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb16f1
    7fdb8bfb16d2:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fdb8bfb16d8:	85 c0                	test   %eax,%eax
    7fdb8bfb16da:	0f 85 20 00 00 00    	jne    0x7fdb8bfb1700
    7fdb8bfb16e0:	8b 85 a8 fd ff ff    	mov    -0x258(%rbp),%eax
    7fdb8bfb16e6:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7fdb8bfb16ec:	e9 1b 00 00 00       	jmpq   0x7fdb8bfb170c
    7fdb8bfb16f1:	c7 85 a0 fd ff ff 00 	movl   $0x0,-0x260(%rbp)
    7fdb8bfb16f8:	00 00 00 
    7fdb8bfb16fb:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb170c
    7fdb8bfb1700:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7fdb8bfb1706:	89 85 a0 fd ff ff    	mov    %eax,-0x260(%rbp)
    7fdb8bfb170c:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fdb8bfb1712:	c1 e0 05             	shl    $0x5,%eax
    7fdb8bfb1715:	05 ff 01 00 00       	add    $0x1ff,%eax
    7fdb8bfb171a:	c1 e8 09             	shr    $0x9,%eax
    7fdb8bfb171d:	89 85 98 fd ff ff    	mov    %eax,-0x268(%rbp)
    7fdb8bfb1723:	83 c0 10             	add    $0x10,%eax
    7fdb8bfb1726:	ff c8                	dec    %eax
    7fdb8bfb1728:	c1 e8 04             	shr    $0x4,%eax
    7fdb8bfb172b:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7fdb8bfb1731:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fdb8bfb1734:	ff c8                	dec    %eax
    7fdb8bfb1736:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7fdb8bfb173b:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7fdb8bfb1741:	85 db                	test   %ebx,%ebx
    7fdb8bfb1743:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1765
    7fdb8bfb1749:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fdb8bfb174f:	85 c0                	test   %eax,%eax
    7fdb8bfb1751:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1776
    7fdb8bfb1757:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fdb8bfb175a:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fdb8bfb1760:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb1782
    7fdb8bfb1765:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7fdb8bfb176b:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fdb8bfb1771:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb1782
    7fdb8bfb1776:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7fdb8bfb177c:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fdb8bfb1782:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7fdb8bfb1788:	85 c0                	test   %eax,%eax
    7fdb8bfb178a:	0f 95 c0             	setne  %al
    7fdb8bfb178d:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1790:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7fdb8bfb1796:	b8 01 00 00 00       	mov    $0x1,%eax
    7fdb8bfb179b:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7fdb8bfb179e:	3b c1                	cmp    %ecx,%eax
    7fdb8bfb17a0:	0f 94 c0             	sete   %al
    7fdb8bfb17a3:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb17a6:	8b 95 08 fe ff ff    	mov    -0x1f8(%rbp),%edx
    7fdb8bfb17ac:	23 c2                	and    %edx,%eax
    7fdb8bfb17ae:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7fdb8bfb17b4:	85 c9                	test   %ecx,%ecx
    7fdb8bfb17b6:	0f 95 c1             	setne  %cl
    7fdb8bfb17b9:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb17bc:	8b c1                	mov    %ecx,%eax
    7fdb8bfb17be:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fdb8bfb17c4:	83 f9 00             	cmp    $0x0,%ecx
    7fdb8bfb17c7:	0f 96 c1             	setbe  %cl
    7fdb8bfb17ca:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb17cd:	23 c1                	and    %ecx,%eax
    7fdb8bfb17cf:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7fdb8bfb17d5:	85 db                	test   %ebx,%ebx
    7fdb8bfb17d7:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb17fc
    7fdb8bfb17dd:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fdb8bfb17e3:	85 c0                	test   %eax,%eax
    7fdb8bfb17e5:	0f 85 22 00 00 00    	jne    0x7fdb8bfb180d
    7fdb8bfb17eb:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7fdb8bfb17f1:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7fdb8bfb17f7:	e9 1b 00 00 00       	jmpq   0x7fdb8bfb1817
    7fdb8bfb17fc:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fdb8bfb1802:	89 85 60 fd ff ff    	mov    %eax,-0x2a0(%rbp)
    7fdb8bfb1808:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb1817
    7fdb8bfb180d:	c7 85 60 fd ff ff 00 	movl   $0x0,-0x2a0(%rbp)
    7fdb8bfb1814:	00 00 00 
    7fdb8bfb1817:	8b 85 98 fd ff ff    	mov    -0x268(%rbp),%eax
    7fdb8bfb181d:	ff c8                	dec    %eax
    7fdb8bfb181f:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb1822:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb1825:	ff c0                	inc    %eax
    7fdb8bfb1827:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb182a:	89 85 58 fd ff ff    	mov    %eax,-0x2a8(%rbp)
    7fdb8bfb1830:	85 db                	test   %ebx,%ebx
    7fdb8bfb1832:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1854
    7fdb8bfb1838:	8b 85 08 fe ff ff    	mov    -0x1f8(%rbp),%eax
    7fdb8bfb183e:	85 c0                	test   %eax,%eax
    7fdb8bfb1840:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1865
    7fdb8bfb1846:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fdb8bfb1849:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7fdb8bfb184f:	e9 1b 00 00 00       	jmpq   0x7fdb8bfb186f
    7fdb8bfb1854:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7fdb8bfb185a:	89 85 50 fd ff ff    	mov    %eax,-0x2b0(%rbp)
    7fdb8bfb1860:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb186f
    7fdb8bfb1865:	c7 85 50 fd ff ff 10 	movl   $0x10,-0x2b0(%rbp)
    7fdb8bfb186c:	00 00 00 
    7fdb8bfb186f:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fdb8bfb1875:	85 c0                	test   %eax,%eax
    7fdb8bfb1877:	0f 85 36 00 00 00    	jne    0x7fdb8bfb18b3
    7fdb8bfb187d:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb1880:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7fdb8bfb1886:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb1889:	48 81 c1 e0 0d 00 00 	add    $0xde0,%rcx
    7fdb8bfb1890:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb1893:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb1896:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb189a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb189e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb18a2:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb18a6:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb18aa:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb18ae:	e9 31 00 00 00       	jmpq   0x7fdb8bfb18e4
    7fdb8bfb18b3:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb18b6:	48 05 c8 10 00 00    	add    $0x10c8,%rax
    7fdb8bfb18bc:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb18bf:	48 81 c1 a0 0d 00 00 	add    $0xda0,%rcx
    7fdb8bfb18c6:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb18c9:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb18cc:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb18d0:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb18d4:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb18d8:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb18dc:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb18e0:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb18e4:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fdb8bfb18e7:	23 85 e8 fd ff ff    	and    -0x218(%rbp),%eax
    7fdb8bfb18ed:	89 85 48 fd ff ff    	mov    %eax,-0x2b8(%rbp)
    7fdb8bfb18f3:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb18f6:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7fdb8bfb18fc:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb18ff:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7fdb8bfb1906:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7fdb8bfb190c:	48 89 8d 40 fd ff ff 	mov    %rcx,-0x2c0(%rbp)
    7fdb8bfb1913:	b9 00 02 00 00       	mov    $0x200,%ecx
    7fdb8bfb1918:	48 8b d0             	mov    %rax,%rdx
    7fdb8bfb191b:	be 00 02 00 00       	mov    $0x200,%esi
    7fdb8bfb1920:	48 8b bd 40 fd ff ff 	mov    -0x2c0(%rbp),%rdi
    7fdb8bfb1927:	48 89 85 38 fd ff ff 	mov    %rax,-0x2c8(%rbp)
    7fdb8bfb192e:	b8 08 00 00 00       	mov    $0x8,%eax
    7fdb8bfb1933:	e8 58 c9 b3 ff       	callq  0x7fdb8baee290
    7fdb8bfb1938:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fdb8bfb193e:	85 c0                	test   %eax,%eax
    7fdb8bfb1940:	0f 85 44 00 00 00    	jne    0x7fdb8bfb198a
    7fdb8bfb1946:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7fdb8bfb194c:	85 c0                	test   %eax,%eax
    7fdb8bfb194e:	0f 85 6c 00 00 00    	jne    0x7fdb8bfb19c0
    7fdb8bfb1954:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb1957:	48 05 88 10 00 00    	add    $0x1088,%rax
    7fdb8bfb195d:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb1960:	48 81 c1 18 0d 00 00 	add    $0xd18,%rcx
    7fdb8bfb1967:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb196a:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb196d:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb1971:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb1975:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb1979:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb197d:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb1981:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb1985:	e9 67 00 00 00       	jmpq   0x7fdb8bfb19f1
    7fdb8bfb198a:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb198d:	48 05 88 10 00 00    	add    $0x1088,%rax
    7fdb8bfb1993:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb1996:	48 81 c1 c8 10 00 00 	add    $0x10c8,%rcx
    7fdb8bfb199d:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb19a0:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb19a3:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb19a7:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb19ab:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb19af:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb19b3:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb19b7:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb19bb:	e9 31 00 00 00       	jmpq   0x7fdb8bfb19f1
    7fdb8bfb19c0:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb19c3:	48 05 88 10 00 00    	add    $0x1088,%rax
    7fdb8bfb19c9:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb19cc:	48 81 c1 08 12 00 00 	add    $0x1208,%rcx
    7fdb8bfb19d3:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb19d6:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb19d9:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb19dd:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb19e1:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb19e5:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb19e9:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb19ed:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb19f1:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fdb8bfb19f7:	85 c0                	test   %eax,%eax
    7fdb8bfb19f9:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1a1b
    7fdb8bfb19ff:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fdb8bfb1a05:	85 c0                	test   %eax,%eax
    7fdb8bfb1a07:	0f 85 1d 00 00 00    	jne    0x7fdb8bfb1a2a
    7fdb8bfb1a0d:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fdb8bfb1a10:	89 85 30 fd ff ff    	mov    %eax,-0x2d0(%rbp)
    7fdb8bfb1a16:	e9 19 00 00 00       	jmpq   0x7fdb8bfb1a34
    7fdb8bfb1a1b:	c7 85 30 fd ff ff 01 	movl   $0x1,-0x2d0(%rbp)
    7fdb8bfb1a22:	00 00 00 
    7fdb8bfb1a25:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb1a34
    7fdb8bfb1a2a:	c7 85 30 fd ff ff 00 	movl   $0x0,-0x2d0(%rbp)
    7fdb8bfb1a31:	00 00 00 
    7fdb8bfb1a34:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fdb8bfb1a37:	ff c0                	inc    %eax
    7fdb8bfb1a39:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb1a3c:	89 85 28 fd ff ff    	mov    %eax,-0x2d8(%rbp)
    7fdb8bfb1a42:	41 8b c5             	mov    %r13d,%eax
    7fdb8bfb1a45:	83 c8 00             	or     $0x0,%eax
    7fdb8bfb1a48:	89 85 20 fd ff ff    	mov    %eax,-0x2e0(%rbp)
    7fdb8bfb1a4e:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fdb8bfb1a51:	85 c0                	test   %eax,%eax
    7fdb8bfb1a53:	0f 94 c0             	sete   %al
    7fdb8bfb1a56:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1a59:	49 8b 4e 58          	mov    0x58(%r14),%rcx
    7fdb8bfb1a5d:	8b 09                	mov    (%rcx),%ecx
    7fdb8bfb1a5f:	23 c1                	and    %ecx,%eax
    7fdb8bfb1a61:	8b 8d d0 fd ff ff    	mov    -0x230(%rbp),%ecx
    7fdb8bfb1a67:	23 8d c8 fd ff ff    	and    -0x238(%rbp),%ecx
    7fdb8bfb1a6d:	85 c9                	test   %ecx,%ecx
    7fdb8bfb1a6f:	0f 94 c2             	sete   %dl
    7fdb8bfb1a72:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb1a75:	89 95 18 fd ff ff    	mov    %edx,-0x2e8(%rbp)
    7fdb8bfb1a7b:	23 d0                	and    %eax,%edx
    7fdb8bfb1a7d:	8b 75 98             	mov    -0x68(%rbp),%esi
    7fdb8bfb1a80:	ff c6                	inc    %esi
    7fdb8bfb1a82:	83 e6 1f             	and    $0x1f,%esi
    7fdb8bfb1a85:	89 b5 10 fd ff ff    	mov    %esi,-0x2f0(%rbp)
    7fdb8bfb1a8b:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7fdb8bfb1a91:	85 c0                	test   %eax,%eax
    7fdb8bfb1a93:	0f 94 c0             	sete   %al
    7fdb8bfb1a96:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1a99:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7fdb8bfb1a9f:	89 85 f8 fc ff ff    	mov    %eax,-0x308(%rbp)
    7fdb8bfb1aa5:	23 c8                	and    %eax,%ecx
    7fdb8bfb1aa7:	89 8d f0 fc ff ff    	mov    %ecx,-0x310(%rbp)
    7fdb8bfb1aad:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fdb8bfb1ab0:	ff c8                	dec    %eax
    7fdb8bfb1ab2:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb1ab5:	89 85 e8 fc ff ff    	mov    %eax,-0x318(%rbp)
    7fdb8bfb1abb:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7fdb8bfb1ac1:	85 d2                	test   %edx,%edx
    7fdb8bfb1ac3:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1ae5
    7fdb8bfb1ac9:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7fdb8bfb1acf:	85 c0                	test   %eax,%eax
    7fdb8bfb1ad1:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1af6
    7fdb8bfb1ad7:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fdb8bfb1ada:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fdb8bfb1ae0:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb1b02
    7fdb8bfb1ae5:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fdb8bfb1aeb:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fdb8bfb1af1:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb1b02
    7fdb8bfb1af6:	8b 85 e8 fc ff ff    	mov    -0x318(%rbp),%eax
    7fdb8bfb1afc:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fdb8bfb1b02:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fdb8bfb1b05:	83 f8 01             	cmp    $0x1,%eax
    7fdb8bfb1b08:	0f 94 c0             	sete   %al
    7fdb8bfb1b0b:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1b0e:	23 85 00 fd ff ff    	and    -0x300(%rbp),%eax
    7fdb8bfb1b14:	23 85 f8 fc ff ff    	and    -0x308(%rbp),%eax
    7fdb8bfb1b1a:	85 c0                	test   %eax,%eax
    7fdb8bfb1b1c:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1b3e
    7fdb8bfb1b22:	8b 85 e0 fc ff ff    	mov    -0x320(%rbp),%eax
    7fdb8bfb1b28:	85 c0                	test   %eax,%eax
    7fdb8bfb1b2a:	0f 85 1d 00 00 00    	jne    0x7fdb8bfb1b4d
    7fdb8bfb1b30:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fdb8bfb1b33:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7fdb8bfb1b39:	e9 19 00 00 00       	jmpq   0x7fdb8bfb1b57
    7fdb8bfb1b3e:	c7 85 d0 fc ff ff 01 	movl   $0x1,-0x330(%rbp)
    7fdb8bfb1b45:	00 00 00 
    7fdb8bfb1b48:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb1b57
    7fdb8bfb1b4d:	c7 85 d0 fc ff ff 00 	movl   $0x0,-0x330(%rbp)
    7fdb8bfb1b54:	00 00 00 
    7fdb8bfb1b57:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fdb8bfb1b5a:	83 f8 0f             	cmp    $0xf,%eax
    7fdb8bfb1b5d:	0f 94 c0             	sete   %al
    7fdb8bfb1b60:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1b63:	23 85 08 fd ff ff    	and    -0x2f8(%rbp),%eax
    7fdb8bfb1b69:	23 85 18 fd ff ff    	and    -0x2e8(%rbp),%eax
    7fdb8bfb1b6f:	85 c0                	test   %eax,%eax
    7fdb8bfb1b71:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb1b93
    7fdb8bfb1b77:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7fdb8bfb1b7d:	85 c0                	test   %eax,%eax
    7fdb8bfb1b7f:	0f 85 1d 00 00 00    	jne    0x7fdb8bfb1ba2
    7fdb8bfb1b85:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fdb8bfb1b88:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7fdb8bfb1b8e:	e9 19 00 00 00       	jmpq   0x7fdb8bfb1bac
    7fdb8bfb1b93:	c7 85 c8 fc ff ff 01 	movl   $0x1,-0x338(%rbp)
    7fdb8bfb1b9a:	00 00 00 
    7fdb8bfb1b9d:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb1bac
    7fdb8bfb1ba2:	c7 85 c8 fc ff ff 00 	movl   $0x0,-0x338(%rbp)
    7fdb8bfb1ba9:	00 00 00 
    7fdb8bfb1bac:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fdb8bfb1baf:	ff c0                	inc    %eax
    7fdb8bfb1bb1:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb1bb4:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7fdb8bfb1bba:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fdb8bfb1bc0:	83 c0 02             	add    $0x2,%eax
    7fdb8bfb1bc3:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb1bc6:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7fdb8bfb1bcc:	b8 01 00 00 00       	mov    $0x1,%eax
    7fdb8bfb1bd1:	3b 45 98             	cmp    -0x68(%rbp),%eax
    7fdb8bfb1bd4:	0f 94 c0             	sete   %al
    7fdb8bfb1bd7:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1bda:	8b 8d 00 fd ff ff    	mov    -0x300(%rbp),%ecx
    7fdb8bfb1be0:	23 c1                	and    %ecx,%eax
    7fdb8bfb1be2:	8b 55 90             	mov    -0x70(%rbp),%edx
    7fdb8bfb1be5:	0b c2                	or     %edx,%eax
    7fdb8bfb1be7:	8b 95 08 fd ff ff    	mov    -0x2f8(%rbp),%edx
    7fdb8bfb1bed:	23 c2                	and    %edx,%eax
    7fdb8bfb1bef:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7fdb8bfb1bf5:	49 8b 46 50          	mov    0x50(%r14),%rax
    7fdb8bfb1bf9:	48 89 85 a8 fc ff ff 	mov    %rax,-0x358(%rbp)
    7fdb8bfb1c00:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fdb8bfb1c06:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7fdb8bfb1c0c:	85 c9                	test   %ecx,%ecx
    7fdb8bfb1c0e:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb1c20
    7fdb8bfb1c14:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fdb8bfb1c1a:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
    7fdb8bfb1c20:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb1c23:	48 05 00 0c 00 00    	add    $0xc00,%rax
    7fdb8bfb1c29:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7fdb8bfb1c2f:	c1 e1 06             	shl    $0x6,%ecx
    7fdb8bfb1c32:	8b c9                	mov    %ecx,%ecx
    7fdb8bfb1c34:	49 03 cf             	add    %r15,%rcx
    7fdb8bfb1c37:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb1c3a:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb1c3d:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb1c41:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb1c45:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb1c49:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb1c4d:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb1c51:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb1c55:	49 8b 46 10          	mov    0x10(%r14),%rax
    7fdb8bfb1c59:	48 8b 00             	mov    (%rax),%rax
    7fdb8bfb1c5c:	48 89 85 98 fc ff ff 	mov    %rax,-0x368(%rbp)
    7fdb8bfb1c63:	49 8b 86 80 00 00 00 	mov    0x80(%r14),%rax
    7fdb8bfb1c6a:	8b 00                	mov    (%rax),%eax
    7fdb8bfb1c6c:	85 c0                	test   %eax,%eax
    7fdb8bfb1c6e:	0f 94 c0             	sete   %al
    7fdb8bfb1c71:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1c74:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7fdb8bfb1c7a:	23 c1                	and    %ecx,%eax
    7fdb8bfb1c7c:	89 85 90 fc ff ff    	mov    %eax,-0x370(%rbp)
    7fdb8bfb1c82:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7fdb8bfb1c88:	8b c0                	mov    %eax,%eax
    7fdb8bfb1c8a:	48 c1 e0 06          	shl    $0x6,%rax
    7fdb8bfb1c8e:	48 89 85 88 fc ff ff 	mov    %rax,-0x378(%rbp)
    7fdb8bfb1c95:	48 8b 8d 60 ff ff ff 	mov    -0xa0(%rbp),%rcx
    7fdb8bfb1c9c:	48 03 c1             	add    %rcx,%rax
    7fdb8bfb1c9f:	48 89 85 80 fc ff ff 	mov    %rax,-0x380(%rbp)
    7fdb8bfb1ca6:	85 db                	test   %ebx,%ebx
    7fdb8bfb1ca8:	0f 85 21 00 00 00    	jne    0x7fdb8bfb1ccf
    7fdb8bfb1cae:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fdb8bfb1cb4:	85 c0                	test   %eax,%eax
    7fdb8bfb1cb6:	0f 85 26 00 00 00    	jne    0x7fdb8bfb1ce2
    7fdb8bfb1cbc:	48 8b 85 60 ff ff ff 	mov    -0xa0(%rbp),%rax
    7fdb8bfb1cc3:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7fdb8bfb1cca:	e9 21 00 00 00       	jmpq   0x7fdb8bfb1cf0
    7fdb8bfb1ccf:	48 8b 85 98 fc ff ff 	mov    -0x368(%rbp),%rax
    7fdb8bfb1cd6:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7fdb8bfb1cdd:	e9 0e 00 00 00       	jmpq   0x7fdb8bfb1cf0
    7fdb8bfb1ce2:	48 8b 85 80 fc ff ff 	mov    -0x380(%rbp),%rax
    7fdb8bfb1ce9:	48 89 85 78 fc ff ff 	mov    %rax,-0x388(%rbp)
    7fdb8bfb1cf0:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fdb8bfb1cf6:	85 c0                	test   %eax,%eax
    7fdb8bfb1cf8:	0f 94 c0             	sete   %al
    7fdb8bfb1cfb:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1cfe:	8b 95 38 ff ff ff    	mov    -0xc8(%rbp),%edx
    7fdb8bfb1d04:	85 d2                	test   %edx,%edx
    7fdb8bfb1d06:	0f 94 c1             	sete   %cl
    7fdb8bfb1d09:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb1d0c:	8b b5 30 ff ff ff    	mov    -0xd0(%rbp),%esi
    7fdb8bfb1d12:	83 fe 0f             	cmp    $0xf,%esi
    7fdb8bfb1d15:	40 0f 94 c6          	sete   %sil
    7fdb8bfb1d19:	40 0f b6 f6          	movzbl %sil,%esi
    7fdb8bfb1d1d:	23 95 e0 fd ff ff    	and    -0x220(%rbp),%edx
    7fdb8bfb1d23:	85 d2                	test   %edx,%edx
    7fdb8bfb1d25:	0f 94 c2             	sete   %dl
    7fdb8bfb1d28:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb1d2b:	8b bd 20 fe ff ff    	mov    -0x1e0(%rbp),%edi
    7fdb8bfb1d31:	23 d7                	and    %edi,%edx
    7fdb8bfb1d33:	89 95 70 fc ff ff    	mov    %edx,-0x390(%rbp)
    7fdb8bfb1d39:	23 f2                	and    %edx,%esi
    7fdb8bfb1d3b:	89 b5 68 fc ff ff    	mov    %esi,-0x398(%rbp)
    7fdb8bfb1d41:	0b ce                	or     %esi,%ecx
    7fdb8bfb1d43:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7fdb8bfb1d49:	89 8d 58 fc ff ff    	mov    %ecx,-0x3a8(%rbp)
    7fdb8bfb1d4f:	23 c1                	and    %ecx,%eax
    7fdb8bfb1d51:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7fdb8bfb1d57:	03 8d 40 ff ff ff    	add    -0xc0(%rbp),%ecx
    7fdb8bfb1d5d:	83 e1 1f             	and    $0x1f,%ecx
    7fdb8bfb1d60:	89 8d 50 fc ff ff    	mov    %ecx,-0x3b0(%rbp)
    7fdb8bfb1d66:	ff c9                	dec    %ecx
    7fdb8bfb1d68:	83 e1 1f             	and    $0x1f,%ecx
    7fdb8bfb1d6b:	89 8d 48 fc ff ff    	mov    %ecx,-0x3b8(%rbp)
    7fdb8bfb1d71:	89 85 40 fc ff ff    	mov    %eax,-0x3c0(%rbp)
    7fdb8bfb1d77:	85 c0                	test   %eax,%eax
    7fdb8bfb1d79:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb1d8b
    7fdb8bfb1d7f:	8b 85 50 fc ff ff    	mov    -0x3b0(%rbp),%eax
    7fdb8bfb1d85:	89 85 48 fc ff ff    	mov    %eax,-0x3b8(%rbp)
    7fdb8bfb1d8b:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fdb8bfb1d91:	ff c8                	dec    %eax
    7fdb8bfb1d93:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb1d96:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7fdb8bfb1d9c:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fdb8bfb1da2:	85 c0                	test   %eax,%eax
    7fdb8bfb1da4:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb1db6
    7fdb8bfb1daa:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fdb8bfb1db0:	89 85 38 fc ff ff    	mov    %eax,-0x3c8(%rbp)
    7fdb8bfb1db6:	85 db                	test   %ebx,%ebx
    7fdb8bfb1db8:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1ddd
    7fdb8bfb1dbe:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fdb8bfb1dc4:	85 c0                	test   %eax,%eax
    7fdb8bfb1dc6:	0f 85 20 00 00 00    	jne    0x7fdb8bfb1dec
    7fdb8bfb1dcc:	8b 85 38 fc ff ff    	mov    -0x3c8(%rbp),%eax
    7fdb8bfb1dd2:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fdb8bfb1dd8:	e9 1b 00 00 00       	jmpq   0x7fdb8bfb1df8
    7fdb8bfb1ddd:	c7 85 30 fc ff ff 00 	movl   $0x0,-0x3d0(%rbp)
    7fdb8bfb1de4:	00 00 00 
    7fdb8bfb1de7:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb1df8
    7fdb8bfb1dec:	8b 85 48 fc ff ff    	mov    -0x3b8(%rbp),%eax
    7fdb8bfb1df2:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fdb8bfb1df8:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fdb8bfb1dfe:	ff c8                	dec    %eax
    7fdb8bfb1e00:	25 ff ff ff 0f       	and    $0xfffffff,%eax
    7fdb8bfb1e05:	89 85 28 fc ff ff    	mov    %eax,-0x3d8(%rbp)
    7fdb8bfb1e0b:	85 db                	test   %ebx,%ebx
    7fdb8bfb1e0d:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1e32
    7fdb8bfb1e13:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fdb8bfb1e19:	85 c0                	test   %eax,%eax
    7fdb8bfb1e1b:	0f 85 22 00 00 00    	jne    0x7fdb8bfb1e43
    7fdb8bfb1e21:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fdb8bfb1e27:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7fdb8bfb1e2d:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb1e4f
    7fdb8bfb1e32:	8b 85 90 fd ff ff    	mov    -0x270(%rbp),%eax
    7fdb8bfb1e38:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7fdb8bfb1e3e:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb1e4f
    7fdb8bfb1e43:	8b 85 28 fc ff ff    	mov    -0x3d8(%rbp),%eax
    7fdb8bfb1e49:	89 85 20 fc ff ff    	mov    %eax,-0x3e0(%rbp)
    7fdb8bfb1e4f:	b8 01 00 00 00       	mov    $0x1,%eax
    7fdb8bfb1e54:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7fdb8bfb1e5a:	3b c1                	cmp    %ecx,%eax
    7fdb8bfb1e5c:	0f 94 c0             	sete   %al
    7fdb8bfb1e5f:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb1e62:	8b 95 90 fc ff ff    	mov    -0x370(%rbp),%edx
    7fdb8bfb1e68:	23 c2                	and    %edx,%eax
    7fdb8bfb1e6a:	89 85 18 fc ff ff    	mov    %eax,-0x3e8(%rbp)
    7fdb8bfb1e70:	85 c9                	test   %ecx,%ecx
    7fdb8bfb1e72:	0f 95 c1             	setne  %cl
    7fdb8bfb1e75:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb1e78:	8b c1                	mov    %ecx,%eax
    7fdb8bfb1e7a:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7fdb8bfb1e80:	83 f9 00             	cmp    $0x0,%ecx
    7fdb8bfb1e83:	0f 96 c1             	setbe  %cl
    7fdb8bfb1e86:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb1e89:	23 c1                	and    %ecx,%eax
    7fdb8bfb1e8b:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7fdb8bfb1e91:	85 db                	test   %ebx,%ebx
    7fdb8bfb1e93:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1eb8
    7fdb8bfb1e99:	8b 85 18 fc ff ff    	mov    -0x3e8(%rbp),%eax
    7fdb8bfb1e9f:	85 c0                	test   %eax,%eax
    7fdb8bfb1ea1:	0f 85 22 00 00 00    	jne    0x7fdb8bfb1ec9
    7fdb8bfb1ea7:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7fdb8bfb1ead:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7fdb8bfb1eb3:	e9 1b 00 00 00       	jmpq   0x7fdb8bfb1ed3
    7fdb8bfb1eb8:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fdb8bfb1ebe:	89 85 08 fc ff ff    	mov    %eax,-0x3f8(%rbp)
    7fdb8bfb1ec4:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb1ed3
    7fdb8bfb1ec9:	c7 85 08 fc ff ff 00 	movl   $0x0,-0x3f8(%rbp)
    7fdb8bfb1ed0:	00 00 00 
    7fdb8bfb1ed3:	85 db                	test   %ebx,%ebx
    7fdb8bfb1ed5:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb1efa
    7fdb8bfb1edb:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
    7fdb8bfb1ee1:	85 c0                	test   %eax,%eax
    7fdb8bfb1ee3:	0f 85 22 00 00 00    	jne    0x7fdb8bfb1f0b
    7fdb8bfb1ee9:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7fdb8bfb1eef:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fdb8bfb1ef5:	e9 1b 00 00 00       	jmpq   0x7fdb8bfb1f15
    7fdb8bfb1efa:	8b 85 58 fd ff ff    	mov    -0x2a8(%rbp),%eax
    7fdb8bfb1f00:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fdb8bfb1f06:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb1f15
    7fdb8bfb1f0b:	c7 85 00 fc ff ff 10 	movl   $0x10,-0x400(%rbp)
    7fdb8bfb1f12:	00 00 00 
    7fdb8bfb1f15:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7fdb8bfb1f1b:	85 c0                	test   %eax,%eax
    7fdb8bfb1f1d:	0f 85 36 00 00 00    	jne    0x7fdb8bfb1f59
    7fdb8bfb1f23:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb1f26:	48 05 48 11 00 00    	add    $0x1148,%rax
    7fdb8bfb1f2c:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb1f2f:	48 81 c1 10 0f 00 00 	add    $0xf10,%rcx
    7fdb8bfb1f36:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb1f39:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb1f3c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb1f40:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb1f44:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb1f48:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb1f4c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb1f50:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb1f54:	e9 31 00 00 00       	jmpq   0x7fdb8bfb1f8a
    7fdb8bfb1f59:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb1f5c:	48 05 48 11 00 00    	add    $0x1148,%rax
    7fdb8bfb1f62:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb1f65:	48 81 c1 d0 0e 00 00 	add    $0xed0,%rcx
    7fdb8bfb1f6c:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb1f6f:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb1f72:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb1f76:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb1f7a:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb1f7e:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb1f82:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb1f86:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb1f8a:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fdb8bfb1f90:	23 85 70 fc ff ff    	and    -0x390(%rbp),%eax
    7fdb8bfb1f96:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7fdb8bfb1f9c:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb1f9f:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7fdb8bfb1fa5:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb1fa8:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7fdb8bfb1faf:	41 b8 20 00 00 00    	mov    $0x20,%r8d
    7fdb8bfb1fb5:	48 89 8d f0 fb ff ff 	mov    %rcx,-0x410(%rbp)
    7fdb8bfb1fbc:	b9 00 02 00 00       	mov    $0x200,%ecx
    7fdb8bfb1fc1:	48 8b d0             	mov    %rax,%rdx
    7fdb8bfb1fc4:	be 00 02 00 00       	mov    $0x200,%esi
    7fdb8bfb1fc9:	48 8b bd f0 fb ff ff 	mov    -0x410(%rbp),%rdi
    7fdb8bfb1fd0:	48 89 85 e8 fb ff ff 	mov    %rax,-0x418(%rbp)
    7fdb8bfb1fd7:	b8 08 00 00 00       	mov    $0x8,%eax
    7fdb8bfb1fdc:	e8 af c2 b3 ff       	callq  0x7fdb8baee290
    7fdb8bfb1fe1:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fdb8bfb1fe7:	85 c0                	test   %eax,%eax
    7fdb8bfb1fe9:	0f 85 44 00 00 00    	jne    0x7fdb8bfb2033
    7fdb8bfb1fef:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fdb8bfb1ff5:	85 c0                	test   %eax,%eax
    7fdb8bfb1ff7:	0f 85 6c 00 00 00    	jne    0x7fdb8bfb2069
    7fdb8bfb1ffd:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2000:	48 05 08 11 00 00    	add    $0x1108,%rax
    7fdb8bfb2006:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2009:	48 81 c1 48 0e 00 00 	add    $0xe48,%rcx
    7fdb8bfb2010:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2013:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2016:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb201a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb201e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2022:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2026:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb202a:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb202e:	e9 67 00 00 00       	jmpq   0x7fdb8bfb209a
    7fdb8bfb2033:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2036:	48 05 08 11 00 00    	add    $0x1108,%rax
    7fdb8bfb203c:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb203f:	48 81 c1 48 11 00 00 	add    $0x1148,%rcx
    7fdb8bfb2046:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2049:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb204c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2050:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2054:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2058:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb205c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2060:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2064:	e9 31 00 00 00       	jmpq   0x7fdb8bfb209a
    7fdb8bfb2069:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb206c:	48 05 08 11 00 00    	add    $0x1108,%rax
    7fdb8bfb2072:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2075:	48 81 c1 48 12 00 00 	add    $0x1248,%rcx
    7fdb8bfb207c:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb207f:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2082:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2086:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb208a:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb208e:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2092:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2096:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb209a:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fdb8bfb20a0:	85 c0                	test   %eax,%eax
    7fdb8bfb20a2:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb20c7
    7fdb8bfb20a8:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7fdb8bfb20ae:	85 c0                	test   %eax,%eax
    7fdb8bfb20b0:	0f 85 20 00 00 00    	jne    0x7fdb8bfb20d6
    7fdb8bfb20b6:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fdb8bfb20bc:	89 85 e0 fb ff ff    	mov    %eax,-0x420(%rbp)
    7fdb8bfb20c2:	e9 19 00 00 00       	jmpq   0x7fdb8bfb20e0
    7fdb8bfb20c7:	c7 85 e0 fb ff ff 01 	movl   $0x1,-0x420(%rbp)
    7fdb8bfb20ce:	00 00 00 
    7fdb8bfb20d1:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb20e0
    7fdb8bfb20d6:	c7 85 e0 fb ff ff 00 	movl   $0x0,-0x420(%rbp)
    7fdb8bfb20dd:	00 00 00 
    7fdb8bfb20e0:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fdb8bfb20e6:	ff c0                	inc    %eax
    7fdb8bfb20e8:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb20eb:	89 85 d8 fb ff ff    	mov    %eax,-0x428(%rbp)
    7fdb8bfb20f1:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fdb8bfb20f7:	85 c0                	test   %eax,%eax
    7fdb8bfb20f9:	0f 94 c0             	sete   %al
    7fdb8bfb20fc:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb20ff:	49 8b 4e 78          	mov    0x78(%r14),%rcx
    7fdb8bfb2103:	8b 09                	mov    (%rcx),%ecx
    7fdb8bfb2105:	23 c1                	and    %ecx,%eax
    7fdb8bfb2107:	8b 8d 60 fc ff ff    	mov    -0x3a0(%rbp),%ecx
    7fdb8bfb210d:	23 8d 58 fc ff ff    	and    -0x3a8(%rbp),%ecx
    7fdb8bfb2113:	85 c9                	test   %ecx,%ecx
    7fdb8bfb2115:	0f 94 c2             	sete   %dl
    7fdb8bfb2118:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb211b:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7fdb8bfb2121:	23 d0                	and    %eax,%edx
    7fdb8bfb2123:	8b b5 28 ff ff ff    	mov    -0xd8(%rbp),%esi
    7fdb8bfb2129:	ff c6                	inc    %esi
    7fdb8bfb212b:	83 e6 1f             	and    $0x1f,%esi
    7fdb8bfb212e:	89 b5 c8 fb ff ff    	mov    %esi,-0x438(%rbp)
    7fdb8bfb2134:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7fdb8bfb213a:	85 c0                	test   %eax,%eax
    7fdb8bfb213c:	0f 94 c0             	sete   %al
    7fdb8bfb213f:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb2142:	89 8d b8 fb ff ff    	mov    %ecx,-0x448(%rbp)
    7fdb8bfb2148:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7fdb8bfb214e:	23 c8                	and    %eax,%ecx
    7fdb8bfb2150:	89 8d a8 fb ff ff    	mov    %ecx,-0x458(%rbp)
    7fdb8bfb2156:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fdb8bfb215c:	ff c8                	dec    %eax
    7fdb8bfb215e:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb2161:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7fdb8bfb2167:	89 95 98 fb ff ff    	mov    %edx,-0x468(%rbp)
    7fdb8bfb216d:	85 d2                	test   %edx,%edx
    7fdb8bfb216f:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb2194
    7fdb8bfb2175:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fdb8bfb217b:	85 c0                	test   %eax,%eax
    7fdb8bfb217d:	0f 85 22 00 00 00    	jne    0x7fdb8bfb21a5
    7fdb8bfb2183:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fdb8bfb2189:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fdb8bfb218f:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb21b1
    7fdb8bfb2194:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7fdb8bfb219a:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fdb8bfb21a0:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb21b1
    7fdb8bfb21a5:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7fdb8bfb21ab:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fdb8bfb21b1:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fdb8bfb21b7:	83 f8 01             	cmp    $0x1,%eax
    7fdb8bfb21ba:	0f 94 c0             	sete   %al
    7fdb8bfb21bd:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb21c0:	23 85 b8 fb ff ff    	and    -0x448(%rbp),%eax
    7fdb8bfb21c6:	23 85 b0 fb ff ff    	and    -0x450(%rbp),%eax
    7fdb8bfb21cc:	85 c0                	test   %eax,%eax
    7fdb8bfb21ce:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb21f3
    7fdb8bfb21d4:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7fdb8bfb21da:	85 c0                	test   %eax,%eax
    7fdb8bfb21dc:	0f 85 20 00 00 00    	jne    0x7fdb8bfb2202
    7fdb8bfb21e2:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fdb8bfb21e8:	89 85 88 fb ff ff    	mov    %eax,-0x478(%rbp)
    7fdb8bfb21ee:	e9 19 00 00 00       	jmpq   0x7fdb8bfb220c
    7fdb8bfb21f3:	c7 85 88 fb ff ff 01 	movl   $0x1,-0x478(%rbp)
    7fdb8bfb21fa:	00 00 00 
    7fdb8bfb21fd:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb220c
    7fdb8bfb2202:	c7 85 88 fb ff ff 00 	movl   $0x0,-0x478(%rbp)
    7fdb8bfb2209:	00 00 00 
    7fdb8bfb220c:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fdb8bfb2212:	83 f8 0f             	cmp    $0xf,%eax
    7fdb8bfb2215:	0f 94 c0             	sete   %al
    7fdb8bfb2218:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb221b:	23 85 c0 fb ff ff    	and    -0x440(%rbp),%eax
    7fdb8bfb2221:	23 85 d0 fb ff ff    	and    -0x430(%rbp),%eax
    7fdb8bfb2227:	85 c0                	test   %eax,%eax
    7fdb8bfb2229:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb224e
    7fdb8bfb222f:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fdb8bfb2235:	85 c0                	test   %eax,%eax
    7fdb8bfb2237:	0f 85 20 00 00 00    	jne    0x7fdb8bfb225d
    7fdb8bfb223d:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fdb8bfb2243:	89 85 80 fb ff ff    	mov    %eax,-0x480(%rbp)
    7fdb8bfb2249:	e9 19 00 00 00       	jmpq   0x7fdb8bfb2267
    7fdb8bfb224e:	c7 85 80 fb ff ff 01 	movl   $0x1,-0x480(%rbp)
    7fdb8bfb2255:	00 00 00 
    7fdb8bfb2258:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb2267
    7fdb8bfb225d:	c7 85 80 fb ff ff 00 	movl   $0x0,-0x480(%rbp)
    7fdb8bfb2264:	00 00 00 
    7fdb8bfb2267:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fdb8bfb226d:	ff c0                	inc    %eax
    7fdb8bfb226f:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb2272:	89 85 78 fb ff ff    	mov    %eax,-0x488(%rbp)
    7fdb8bfb2278:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fdb8bfb227e:	83 c0 02             	add    $0x2,%eax
    7fdb8bfb2281:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb2284:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7fdb8bfb228a:	b8 01 00 00 00       	mov    $0x1,%eax
    7fdb8bfb228f:	3b 85 28 ff ff ff    	cmp    -0xd8(%rbp),%eax
    7fdb8bfb2295:	0f 94 c0             	sete   %al
    7fdb8bfb2298:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb229b:	8b 8d b8 fb ff ff    	mov    -0x448(%rbp),%ecx
    7fdb8bfb22a1:	23 c1                	and    %ecx,%eax
    7fdb8bfb22a3:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7fdb8bfb22a9:	0b c2                	or     %edx,%eax
    7fdb8bfb22ab:	8b 95 c0 fb ff ff    	mov    -0x440(%rbp),%edx
    7fdb8bfb22b1:	23 c2                	and    %edx,%eax
    7fdb8bfb22b3:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7fdb8bfb22b9:	49 8b 46 70          	mov    0x70(%r14),%rax
    7fdb8bfb22bd:	48 89 85 60 fb ff ff 	mov    %rax,-0x4a0(%rbp)
    7fdb8bfb22c4:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fdb8bfb22ca:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fdb8bfb22d0:	85 c9                	test   %ecx,%ecx
    7fdb8bfb22d2:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb22e4
    7fdb8bfb22d8:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fdb8bfb22de:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fdb8bfb22e4:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb22e7:	48 05 00 04 00 00    	add    $0x400,%rax
    7fdb8bfb22ed:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb22f0:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7fdb8bfb22f7:	8b 95 58 fb ff ff    	mov    -0x4a8(%rbp),%edx
    7fdb8bfb22fd:	c1 e2 06             	shl    $0x6,%edx
    7fdb8bfb2300:	8b d2                	mov    %edx,%edx
    7fdb8bfb2302:	48 03 c2             	add    %rdx,%rax
    7fdb8bfb2305:	0f 10 00             	movups (%rax),%xmm0
    7fdb8bfb2308:	0f 11 01             	movups %xmm0,(%rcx)
    7fdb8bfb230b:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7fdb8bfb230f:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7fdb8bfb2313:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7fdb8bfb2317:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7fdb8bfb231b:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7fdb8bfb231f:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7fdb8bfb2323:	49 8b 06             	mov    (%r14),%rax
    7fdb8bfb2326:	48 8b 00             	mov    (%rax),%rax
    7fdb8bfb2329:	48 89 85 50 fb ff ff 	mov    %rax,-0x4b0(%rbp)
    7fdb8bfb2330:	49 8b 46 40          	mov    0x40(%r14),%rax
    7fdb8bfb2334:	8b 00                	mov    (%rax),%eax
    7fdb8bfb2336:	85 c0                	test   %eax,%eax
    7fdb8bfb2338:	0f 94 c0             	sete   %al
    7fdb8bfb233b:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb233e:	89 85 48 fb ff ff    	mov    %eax,-0x4b8(%rbp)
    7fdb8bfb2344:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7fdb8bfb234a:	23 c1                	and    %ecx,%eax
    7fdb8bfb234c:	89 85 40 fb ff ff    	mov    %eax,-0x4c0(%rbp)
    7fdb8bfb2352:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
    7fdb8bfb2359:	48 83 c0 40          	add    $0x40,%rax
    7fdb8bfb235d:	48 89 85 38 fb ff ff 	mov    %rax,-0x4c8(%rbp)
    7fdb8bfb2364:	85 db                	test   %ebx,%ebx
    7fdb8bfb2366:	0f 85 21 00 00 00    	jne    0x7fdb8bfb238d
    7fdb8bfb236c:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fdb8bfb2372:	85 c0                	test   %eax,%eax
    7fdb8bfb2374:	0f 85 26 00 00 00    	jne    0x7fdb8bfb23a0
    7fdb8bfb237a:	48 8b 85 f0 fe ff ff 	mov    -0x110(%rbp),%rax
    7fdb8bfb2381:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7fdb8bfb2388:	e9 21 00 00 00       	jmpq   0x7fdb8bfb23ae
    7fdb8bfb238d:	48 8b 85 50 fb ff ff 	mov    -0x4b0(%rbp),%rax
    7fdb8bfb2394:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7fdb8bfb239b:	e9 0e 00 00 00       	jmpq   0x7fdb8bfb23ae
    7fdb8bfb23a0:	48 8b 85 38 fb ff ff 	mov    -0x4c8(%rbp),%rax
    7fdb8bfb23a7:	48 89 85 30 fb ff ff 	mov    %rax,-0x4d0(%rbp)
    7fdb8bfb23ae:	33 c0                	xor    %eax,%eax
    7fdb8bfb23b0:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7fdb8bfb23b6:	3b c1                	cmp    %ecx,%eax
    7fdb8bfb23b8:	0f 94 c0             	sete   %al
    7fdb8bfb23bb:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb23be:	8b 95 b0 fe ff ff    	mov    -0x150(%rbp),%edx
    7fdb8bfb23c4:	85 d2                	test   %edx,%edx
    7fdb8bfb23c6:	0f 94 c2             	sete   %dl
    7fdb8bfb23c9:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb23cc:	89 95 28 fb ff ff    	mov    %edx,-0x4d8(%rbp)
    7fdb8bfb23d2:	8b b5 b8 fe ff ff    	mov    -0x148(%rbp),%esi
    7fdb8bfb23d8:	23 d6                	and    %esi,%edx
    7fdb8bfb23da:	41 83 fc 10          	cmp    $0x10,%r12d
    7fdb8bfb23de:	40 0f 93 c7          	setae  %dil
    7fdb8bfb23e2:	40 0f b6 ff          	movzbl %dil,%edi
    7fdb8bfb23e6:	0b d7                	or     %edi,%edx
    7fdb8bfb23e8:	23 c2                	and    %edx,%eax
    7fdb8bfb23ea:	ba 01 00 00 00       	mov    $0x1,%edx
    7fdb8bfb23ef:	3b d1                	cmp    %ecx,%edx
    7fdb8bfb23f1:	0f 94 c2             	sete   %dl
    7fdb8bfb23f4:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb23f7:	89 95 20 fb ff ff    	mov    %edx,-0x4e0(%rbp)
    7fdb8bfb23fd:	23 95 48 fb ff ff    	and    -0x4b8(%rbp),%edx
    7fdb8bfb2403:	41 83 fc 01          	cmp    $0x1,%r12d
    7fdb8bfb2407:	40 0f 97 c7          	seta   %dil
    7fdb8bfb240b:	40 0f b6 ff          	movzbl %dil,%edi
    7fdb8bfb240f:	23 f7                	and    %edi,%esi
    7fdb8bfb2411:	41 83 fc 10          	cmp    $0x10,%r12d
    7fdb8bfb2415:	40 0f 97 c7          	seta   %dil
    7fdb8bfb2419:	40 0f b6 ff          	movzbl %dil,%edi
    7fdb8bfb241d:	0b f7                	or     %edi,%esi
    7fdb8bfb241f:	23 d6                	and    %esi,%edx
    7fdb8bfb2421:	0b c2                	or     %edx,%eax
    7fdb8bfb2423:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7fdb8bfb2429:	41 83 fc 10          	cmp    $0x10,%r12d
    7fdb8bfb242d:	0f 94 c0             	sete   %al
    7fdb8bfb2430:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb2433:	33 d2                	xor    %edx,%edx
    7fdb8bfb2435:	3b d1                	cmp    %ecx,%edx
    7fdb8bfb2437:	0f 94 c2             	sete   %dl
    7fdb8bfb243a:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb243d:	23 c2                	and    %edx,%eax
    7fdb8bfb243f:	0b f8                	or     %eax,%edi
    7fdb8bfb2441:	85 c9                	test   %ecx,%ecx
    7fdb8bfb2443:	0f 95 c1             	setne  %cl
    7fdb8bfb2446:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb2449:	8b c1                	mov    %ecx,%eax
    7fdb8bfb244b:	41 8b cc             	mov    %r12d,%ecx
    7fdb8bfb244e:	2b c8                	sub    %eax,%ecx
    7fdb8bfb2450:	83 e1 1f             	and    $0x1f,%ecx
    7fdb8bfb2453:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7fdb8bfb2459:	c7 85 08 fb ff ff 10 	movl   $0x10,-0x4f8(%rbp)
    7fdb8bfb2460:	00 00 00 
    7fdb8bfb2463:	85 ff                	test   %edi,%edi
    7fdb8bfb2465:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb2477
    7fdb8bfb246b:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fdb8bfb2471:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7fdb8bfb2477:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fdb8bfb247d:	ff c8                	dec    %eax
    7fdb8bfb247f:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb2482:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7fdb8bfb2488:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fdb8bfb248e:	85 c0                	test   %eax,%eax
    7fdb8bfb2490:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb24b5
    7fdb8bfb2496:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fdb8bfb249c:	85 c0                	test   %eax,%eax
    7fdb8bfb249e:	0f 85 22 00 00 00    	jne    0x7fdb8bfb24c6
    7fdb8bfb24a4:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fdb8bfb24aa:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7fdb8bfb24b0:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb24d2
    7fdb8bfb24b5:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fdb8bfb24bb:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7fdb8bfb24c1:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb24d2
    7fdb8bfb24c6:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fdb8bfb24cc:	89 85 f8 fa ff ff    	mov    %eax,-0x508(%rbp)
    7fdb8bfb24d2:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fdb8bfb24d8:	23 85 20 fb ff ff    	and    -0x4e0(%rbp),%eax
    7fdb8bfb24de:	89 85 f0 fa ff ff    	mov    %eax,-0x510(%rbp)
    7fdb8bfb24e4:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fdb8bfb24ea:	85 c0                	test   %eax,%eax
    7fdb8bfb24ec:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb2511
    7fdb8bfb24f2:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7fdb8bfb24f8:	85 c0                	test   %eax,%eax
    7fdb8bfb24fa:	0f 85 20 00 00 00    	jne    0x7fdb8bfb2520
    7fdb8bfb2500:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fdb8bfb2506:	89 85 e8 fa ff ff    	mov    %eax,-0x518(%rbp)
    7fdb8bfb250c:	e9 19 00 00 00       	jmpq   0x7fdb8bfb252a
    7fdb8bfb2511:	c7 85 e8 fa ff ff 01 	movl   $0x1,-0x518(%rbp)
    7fdb8bfb2518:	00 00 00 
    7fdb8bfb251b:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb252a
    7fdb8bfb2520:	c7 85 e8 fa ff ff 00 	movl   $0x0,-0x518(%rbp)
    7fdb8bfb2527:	00 00 00 
    7fdb8bfb252a:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fdb8bfb252d:	83 f8 02             	cmp    $0x2,%eax
    7fdb8bfb2530:	0f 94 c0             	sete   %al
    7fdb8bfb2533:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb2536:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7fdb8bfb253c:	85 c9                	test   %ecx,%ecx
    7fdb8bfb253e:	0f 95 c1             	setne  %cl
    7fdb8bfb2541:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb2544:	89 85 e0 fa ff ff    	mov    %eax,-0x520(%rbp)
    7fdb8bfb254a:	23 c8                	and    %eax,%ecx
    7fdb8bfb254c:	8b c1                	mov    %ecx,%eax
    7fdb8bfb254e:	89 85 d8 fa ff ff    	mov    %eax,-0x528(%rbp)
    7fdb8bfb2554:	8b 8d c8 fe ff ff    	mov    -0x138(%rbp),%ecx
    7fdb8bfb255a:	0b c1                	or     %ecx,%eax
    7fdb8bfb255c:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7fdb8bfb2562:	23 c1                	and    %ecx,%eax
    7fdb8bfb2564:	89 85 d0 fa ff ff    	mov    %eax,-0x530(%rbp)
    7fdb8bfb256a:	23 c8                	and    %eax,%ecx
    7fdb8bfb256c:	b8 01 00 00 00       	mov    $0x1,%eax
    7fdb8bfb2571:	41 3b c4             	cmp    %r12d,%eax
    7fdb8bfb2574:	0f 94 c0             	sete   %al
    7fdb8bfb2577:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb257a:	89 85 c8 fa ff ff    	mov    %eax,-0x538(%rbp)
    7fdb8bfb2580:	8b 95 40 fb ff ff    	mov    -0x4c0(%rbp),%edx
    7fdb8bfb2586:	23 c2                	and    %edx,%eax
    7fdb8bfb2588:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fdb8bfb258e:	85 c9                	test   %ecx,%ecx
    7fdb8bfb2590:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb25b5
    7fdb8bfb2596:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fdb8bfb259c:	85 c0                	test   %eax,%eax
    7fdb8bfb259e:	0f 85 20 00 00 00    	jne    0x7fdb8bfb25c4
    7fdb8bfb25a4:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fdb8bfb25aa:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7fdb8bfb25b0:	e9 19 00 00 00       	jmpq   0x7fdb8bfb25ce
    7fdb8bfb25b5:	c7 85 b8 fa ff ff 01 	movl   $0x1,-0x548(%rbp)
    7fdb8bfb25bc:	00 00 00 
    7fdb8bfb25bf:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb25ce
    7fdb8bfb25c4:	c7 85 b8 fa ff ff 00 	movl   $0x0,-0x548(%rbp)
    7fdb8bfb25cb:	00 00 00 
    7fdb8bfb25ce:	33 c0                	xor    %eax,%eax
    7fdb8bfb25d0:	8b 8d c0 fe ff ff    	mov    -0x140(%rbp),%ecx
    7fdb8bfb25d6:	3b c1                	cmp    %ecx,%eax
    7fdb8bfb25d8:	0f 94 c0             	sete   %al
    7fdb8bfb25db:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb25de:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fdb8bfb25e1:	8b d2                	mov    %edx,%edx
    7fdb8bfb25e3:	48 89 95 b0 fa ff ff 	mov    %rdx,-0x550(%rbp)
    7fdb8bfb25ea:	48 8d 95 b0 fa ff ff 	lea    -0x550(%rbp),%rdx
    7fdb8bfb25f1:	49 8b f7             	mov    %r15,%rsi
    7fdb8bfb25f4:	48 81 c6 88 12 00 00 	add    $0x1288,%rsi
    7fdb8bfb25fb:	b9 20 00 00 00       	mov    $0x20,%ecx
    7fdb8bfb2600:	48 89 95 a8 fa ff ff 	mov    %rdx,-0x558(%rbp)
    7fdb8bfb2607:	48 89 b5 a0 fa ff ff 	mov    %rsi,-0x560(%rbp)
    7fdb8bfb260e:	be 00 02 00 00       	mov    $0x200,%esi
    7fdb8bfb2613:	48 8b bd a0 fa ff ff 	mov    -0x560(%rbp),%rdi
    7fdb8bfb261a:	89 85 98 fa ff ff    	mov    %eax,-0x568(%rbp)
    7fdb8bfb2620:	b8 08 00 00 00       	mov    $0x8,%eax
    7fdb8bfb2625:	e8 06 ca b3 ff       	callq  0x7fdb8baef030
    7fdb8bfb262a:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fdb8bfb2630:	c1 e0 05             	shl    $0x5,%eax
    7fdb8bfb2633:	25 ff 01 00 00       	and    $0x1ff,%eax
    7fdb8bfb2638:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb263b:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7fdb8bfb2642:	49 8b d7             	mov    %r15,%rdx
    7fdb8bfb2645:	48 81 c2 c8 12 00 00 	add    $0x12c8,%rdx
    7fdb8bfb264c:	44 8b c0             	mov    %eax,%r8d
    7fdb8bfb264f:	48 89 8d 90 fa ff ff 	mov    %rcx,-0x570(%rbp)
    7fdb8bfb2656:	b9 00 02 00 00       	mov    $0x200,%ecx
    7fdb8bfb265b:	48 89 95 88 fa ff ff 	mov    %rdx,-0x578(%rbp)
    7fdb8bfb2662:	48 8b 95 90 fa ff ff 	mov    -0x570(%rbp),%rdx
    7fdb8bfb2669:	be 00 02 00 00       	mov    $0x200,%esi
    7fdb8bfb266e:	48 8b bd 88 fa ff ff 	mov    -0x578(%rbp),%rdi
    7fdb8bfb2675:	89 85 80 fa ff ff    	mov    %eax,-0x580(%rbp)
    7fdb8bfb267b:	b8 08 00 00 00       	mov    $0x8,%eax
    7fdb8bfb2680:	e8 7b b5 b3 ff       	callq  0x7fdb8baedc00
    7fdb8bfb2685:	49 8b 87 c8 12 00 00 	mov    0x12c8(%r15),%rax
    7fdb8bfb268c:	49 8b 8f 78 0f 00 00 	mov    0xf78(%r15),%rcx
    7fdb8bfb2693:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb2696:	49 89 87 08 13 00 00 	mov    %rax,0x1308(%r15)
    7fdb8bfb269d:	49 8b 87 d0 12 00 00 	mov    0x12d0(%r15),%rax
    7fdb8bfb26a4:	49 8b 8f 80 0f 00 00 	mov    0xf80(%r15),%rcx
    7fdb8bfb26ab:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb26ae:	49 89 87 10 13 00 00 	mov    %rax,0x1310(%r15)
    7fdb8bfb26b5:	49 8b 87 d8 12 00 00 	mov    0x12d8(%r15),%rax
    7fdb8bfb26bc:	49 8b 8f 88 0f 00 00 	mov    0xf88(%r15),%rcx
    7fdb8bfb26c3:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb26c6:	49 89 87 18 13 00 00 	mov    %rax,0x1318(%r15)
    7fdb8bfb26cd:	49 8b 87 e0 12 00 00 	mov    0x12e0(%r15),%rax
    7fdb8bfb26d4:	49 8b 8f 90 0f 00 00 	mov    0xf90(%r15),%rcx
    7fdb8bfb26db:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb26de:	49 89 87 20 13 00 00 	mov    %rax,0x1320(%r15)
    7fdb8bfb26e5:	49 8b 87 e8 12 00 00 	mov    0x12e8(%r15),%rax
    7fdb8bfb26ec:	49 8b 8f 98 0f 00 00 	mov    0xf98(%r15),%rcx
    7fdb8bfb26f3:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb26f6:	49 89 87 28 13 00 00 	mov    %rax,0x1328(%r15)
    7fdb8bfb26fd:	49 8b 87 f0 12 00 00 	mov    0x12f0(%r15),%rax
    7fdb8bfb2704:	49 8b 8f a0 0f 00 00 	mov    0xfa0(%r15),%rcx
    7fdb8bfb270b:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb270e:	49 89 87 30 13 00 00 	mov    %rax,0x1330(%r15)
    7fdb8bfb2715:	49 8b 87 f8 12 00 00 	mov    0x12f8(%r15),%rax
    7fdb8bfb271c:	49 8b 8f a8 0f 00 00 	mov    0xfa8(%r15),%rcx
    7fdb8bfb2723:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb2726:	49 89 87 38 13 00 00 	mov    %rax,0x1338(%r15)
    7fdb8bfb272d:	49 8b 87 00 13 00 00 	mov    0x1300(%r15),%rax
    7fdb8bfb2734:	49 8b 8f b0 0f 00 00 	mov    0xfb0(%r15),%rcx
    7fdb8bfb273b:	48 0b c1             	or     %rcx,%rax
    7fdb8bfb273e:	49 89 87 40 13 00 00 	mov    %rax,0x1340(%r15)
    7fdb8bfb2745:	8b 85 98 fa ff ff    	mov    -0x568(%rbp),%eax
    7fdb8bfb274b:	85 c0                	test   %eax,%eax
    7fdb8bfb274d:	0f 85 36 00 00 00    	jne    0x7fdb8bfb2789
    7fdb8bfb2753:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2756:	48 05 88 11 00 00    	add    $0x1188,%rax
    7fdb8bfb275c:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb275f:	48 81 c1 08 13 00 00 	add    $0x1308,%rcx
    7fdb8bfb2766:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2769:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb276c:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2770:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2774:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2778:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb277c:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2780:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2784:	e9 31 00 00 00       	jmpq   0x7fdb8bfb27ba
    7fdb8bfb2789:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb278c:	48 05 88 11 00 00    	add    $0x1188,%rax
    7fdb8bfb2792:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2795:	48 81 c1 88 12 00 00 	add    $0x1288,%rcx
    7fdb8bfb279c:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb279f:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb27a2:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb27a6:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb27aa:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb27ae:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb27b2:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb27b6:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb27ba:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fdb8bfb27bd:	23 85 48 fe ff ff    	and    -0x1b8(%rbp),%eax
    7fdb8bfb27c3:	89 85 78 fa ff ff    	mov    %eax,-0x588(%rbp)
    7fdb8bfb27c9:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fdb8bfb27cf:	83 f8 0f             	cmp    $0xf,%eax
    7fdb8bfb27d2:	0f 94 c0             	sete   %al
    7fdb8bfb27d5:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb27d8:	23 45 d8             	and    -0x28(%rbp),%eax
    7fdb8bfb27db:	85 c0                	test   %eax,%eax
    7fdb8bfb27dd:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb2802
    7fdb8bfb27e3:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7fdb8bfb27e9:	85 c0                	test   %eax,%eax
    7fdb8bfb27eb:	0f 85 20 00 00 00    	jne    0x7fdb8bfb2811
    7fdb8bfb27f1:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fdb8bfb27f7:	89 85 70 fa ff ff    	mov    %eax,-0x590(%rbp)
    7fdb8bfb27fd:	e9 19 00 00 00       	jmpq   0x7fdb8bfb281b
    7fdb8bfb2802:	c7 85 70 fa ff ff 01 	movl   $0x1,-0x590(%rbp)
    7fdb8bfb2809:	00 00 00 
    7fdb8bfb280c:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb281b
    7fdb8bfb2811:	c7 85 70 fa ff ff 00 	movl   $0x0,-0x590(%rbp)
    7fdb8bfb2818:	00 00 00 
    7fdb8bfb281b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fdb8bfb2821:	ff c0                	inc    %eax
    7fdb8bfb2823:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb2826:	89 85 68 fa ff ff    	mov    %eax,-0x598(%rbp)
    7fdb8bfb282c:	41 8b c5             	mov    %r13d,%eax
    7fdb8bfb282f:	0b 85 d8 fa ff ff    	or     -0x528(%rbp),%eax
    7fdb8bfb2835:	89 85 60 fa ff ff    	mov    %eax,-0x5a0(%rbp)
    7fdb8bfb283b:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7fdb8bfb2841:	23 85 d0 fa ff ff    	and    -0x530(%rbp),%eax
    7fdb8bfb2847:	8b 8d 28 fb ff ff    	mov    -0x4d8(%rbp),%ecx
    7fdb8bfb284d:	23 8d 40 fb ff ff    	and    -0x4c0(%rbp),%ecx
    7fdb8bfb2853:	85 c9                	test   %ecx,%ecx
    7fdb8bfb2855:	0f 94 c2             	sete   %dl
    7fdb8bfb2858:	0f b6 d2             	movzbl %dl,%edx
    7fdb8bfb285b:	89 95 58 fa ff ff    	mov    %edx,-0x5a8(%rbp)
    7fdb8bfb2861:	23 d0                	and    %eax,%edx
    7fdb8bfb2863:	41 8b f4             	mov    %r12d,%esi
    7fdb8bfb2866:	ff c6                	inc    %esi
    7fdb8bfb2868:	83 e6 1f             	and    $0x1f,%esi
    7fdb8bfb286b:	89 b5 50 fa ff ff    	mov    %esi,-0x5b0(%rbp)
    7fdb8bfb2871:	89 85 48 fa ff ff    	mov    %eax,-0x5b8(%rbp)
    7fdb8bfb2877:	85 c0                	test   %eax,%eax
    7fdb8bfb2879:	0f 94 c0             	sete   %al
    7fdb8bfb287c:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb287f:	89 8d 40 fa ff ff    	mov    %ecx,-0x5c0(%rbp)
    7fdb8bfb2885:	89 85 38 fa ff ff    	mov    %eax,-0x5c8(%rbp)
    7fdb8bfb288b:	23 c8                	and    %eax,%ecx
    7fdb8bfb288d:	89 8d 30 fa ff ff    	mov    %ecx,-0x5d0(%rbp)
    7fdb8bfb2893:	41 8b c4             	mov    %r12d,%eax
    7fdb8bfb2896:	ff c8                	dec    %eax
    7fdb8bfb2898:	83 e0 1f             	and    $0x1f,%eax
    7fdb8bfb289b:	89 85 28 fa ff ff    	mov    %eax,-0x5d8(%rbp)
    7fdb8bfb28a1:	85 d2                	test   %edx,%edx
    7fdb8bfb28a3:	0f 85 1c 00 00 00    	jne    0x7fdb8bfb28c5
    7fdb8bfb28a9:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7fdb8bfb28af:	85 c0                	test   %eax,%eax
    7fdb8bfb28b1:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb28d6
    7fdb8bfb28b7:	41 8b c4             	mov    %r12d,%eax
    7fdb8bfb28ba:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7fdb8bfb28c0:	e9 1d 00 00 00       	jmpq   0x7fdb8bfb28e2
    7fdb8bfb28c5:	8b 85 50 fa ff ff    	mov    -0x5b0(%rbp),%eax
    7fdb8bfb28cb:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7fdb8bfb28d1:	e9 0c 00 00 00       	jmpq   0x7fdb8bfb28e2
    7fdb8bfb28d6:	8b 85 28 fa ff ff    	mov    -0x5d8(%rbp),%eax
    7fdb8bfb28dc:	89 85 20 fa ff ff    	mov    %eax,-0x5e0(%rbp)
    7fdb8bfb28e2:	41 83 fc 01          	cmp    $0x1,%r12d
    7fdb8bfb28e6:	0f 94 c0             	sete   %al
    7fdb8bfb28e9:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb28ec:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7fdb8bfb28f2:	23 c1                	and    %ecx,%eax
    7fdb8bfb28f4:	23 85 38 fa ff ff    	and    -0x5c8(%rbp),%eax
    7fdb8bfb28fa:	85 c9                	test   %ecx,%ecx
    7fdb8bfb28fc:	0f 94 c1             	sete   %cl
    7fdb8bfb28ff:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb2902:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7fdb8bfb2908:	23 ca                	and    %edx,%ecx
    7fdb8bfb290a:	89 8d 18 fa ff ff    	mov    %ecx,-0x5e8(%rbp)
    7fdb8bfb2910:	85 c0                	test   %eax,%eax
    7fdb8bfb2912:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb2937
    7fdb8bfb2918:	8b 85 18 fa ff ff    	mov    -0x5e8(%rbp),%eax
    7fdb8bfb291e:	85 c0                	test   %eax,%eax
    7fdb8bfb2920:	0f 85 20 00 00 00    	jne    0x7fdb8bfb2946
    7fdb8bfb2926:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7fdb8bfb292c:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7fdb8bfb2932:	e9 19 00 00 00       	jmpq   0x7fdb8bfb2950
    7fdb8bfb2937:	c7 85 10 fa ff ff 01 	movl   $0x1,-0x5f0(%rbp)
    7fdb8bfb293e:	00 00 00 
    7fdb8bfb2941:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb2950
    7fdb8bfb2946:	c7 85 10 fa ff ff 00 	movl   $0x0,-0x5f0(%rbp)
    7fdb8bfb294d:	00 00 00 
    7fdb8bfb2950:	41 83 fc 0f          	cmp    $0xf,%r12d
    7fdb8bfb2954:	0f 94 c0             	sete   %al
    7fdb8bfb2957:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb295a:	23 85 48 fa ff ff    	and    -0x5b8(%rbp),%eax
    7fdb8bfb2960:	23 85 58 fa ff ff    	and    -0x5a8(%rbp),%eax
    7fdb8bfb2966:	85 c0                	test   %eax,%eax
    7fdb8bfb2968:	0f 85 1f 00 00 00    	jne    0x7fdb8bfb298d
    7fdb8bfb296e:	8b 85 30 fa ff ff    	mov    -0x5d0(%rbp),%eax
    7fdb8bfb2974:	85 c0                	test   %eax,%eax
    7fdb8bfb2976:	0f 85 20 00 00 00    	jne    0x7fdb8bfb299c
    7fdb8bfb297c:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fdb8bfb2982:	89 85 08 fa ff ff    	mov    %eax,-0x5f8(%rbp)
    7fdb8bfb2988:	e9 19 00 00 00       	jmpq   0x7fdb8bfb29a6
    7fdb8bfb298d:	c7 85 08 fa ff ff 01 	movl   $0x1,-0x5f8(%rbp)
    7fdb8bfb2994:	00 00 00 
    7fdb8bfb2997:	e9 0a 00 00 00       	jmpq   0x7fdb8bfb29a6
    7fdb8bfb299c:	c7 85 08 fa ff ff 00 	movl   $0x0,-0x5f8(%rbp)
    7fdb8bfb29a3:	00 00 00 
    7fdb8bfb29a6:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fdb8bfb29ac:	ff c0                	inc    %eax
    7fdb8bfb29ae:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb29b1:	89 85 00 fa ff ff    	mov    %eax,-0x600(%rbp)
    7fdb8bfb29b7:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fdb8bfb29bd:	83 c0 02             	add    $0x2,%eax
    7fdb8bfb29c0:	83 e0 0f             	and    $0xf,%eax
    7fdb8bfb29c3:	89 85 f8 f9 ff ff    	mov    %eax,-0x608(%rbp)
    7fdb8bfb29c9:	8b 85 c8 fa ff ff    	mov    -0x538(%rbp),%eax
    7fdb8bfb29cf:	8b 8d 40 fa ff ff    	mov    -0x5c0(%rbp),%ecx
    7fdb8bfb29d5:	23 c1                	and    %ecx,%eax
    7fdb8bfb29d7:	8b 95 b0 fe ff ff    	mov    -0x150(%rbp),%edx
    7fdb8bfb29dd:	0b c2                	or     %edx,%eax
    7fdb8bfb29df:	8b 95 48 fa ff ff    	mov    -0x5b8(%rbp),%edx
    7fdb8bfb29e5:	23 c2                	and    %edx,%eax
    7fdb8bfb29e7:	89 85 f0 f9 ff ff    	mov    %eax,-0x610(%rbp)
    7fdb8bfb29ed:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fdb8bfb29f3:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7fdb8bfb29f9:	85 c9                	test   %ecx,%ecx
    7fdb8bfb29fb:	0f 85 0c 00 00 00    	jne    0x7fdb8bfb2a0d
    7fdb8bfb2a01:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fdb8bfb2a07:	89 85 e8 f9 ff ff    	mov    %eax,-0x618(%rbp)
    7fdb8bfb2a0d:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2a10:	48 05 00 08 00 00    	add    $0x800,%rax
    7fdb8bfb2a16:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2a19:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7fdb8bfb2a20:	8b 95 e8 f9 ff ff    	mov    -0x618(%rbp),%edx
    7fdb8bfb2a26:	c1 e2 06             	shl    $0x6,%edx
    7fdb8bfb2a29:	8b d2                	mov    %edx,%edx
    7fdb8bfb2a2b:	48 03 c2             	add    %rdx,%rax
    7fdb8bfb2a2e:	0f 10 00             	movups (%rax),%xmm0
    7fdb8bfb2a31:	0f 11 01             	movups %xmm0,(%rcx)
    7fdb8bfb2a34:	0f 10 40 10          	movups 0x10(%rax),%xmm0
    7fdb8bfb2a38:	0f 11 41 10          	movups %xmm0,0x10(%rcx)
    7fdb8bfb2a3c:	0f 10 40 20          	movups 0x20(%rax),%xmm0
    7fdb8bfb2a40:	0f 11 41 20          	movups %xmm0,0x20(%rcx)
    7fdb8bfb2a44:	0f 10 40 30          	movups 0x30(%rax),%xmm0
    7fdb8bfb2a48:	0f 11 41 30          	movups %xmm0,0x30(%rcx)
    7fdb8bfb2a4c:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7fdb8bfb2a52:	85 c0                	test   %eax,%eax
    7fdb8bfb2a54:	0f 84 3f 00 00 00    	je     0x7fdb8bfb2a99
    7fdb8bfb2a5a:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2a5d:	48 05 00 08 00 00    	add    $0x800,%rax
    7fdb8bfb2a63:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2a66:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7fdb8bfb2a6d:	8b 95 a0 fe ff ff    	mov    -0x160(%rbp),%edx
    7fdb8bfb2a73:	c1 e2 06             	shl    $0x6,%edx
    7fdb8bfb2a76:	8b d2                	mov    %edx,%edx
    7fdb8bfb2a78:	48 03 c2             	add    %rdx,%rax
    7fdb8bfb2a7b:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2a7e:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2a81:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2a85:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2a89:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2a8d:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2a91:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2a95:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2a99:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fdb8bfb2a9f:	85 c0                	test   %eax,%eax
    7fdb8bfb2aa1:	0f 84 3c 00 00 00    	je     0x7fdb8bfb2ae3
    7fdb8bfb2aa7:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2aaa:	48 05 00 04 00 00    	add    $0x400,%rax
    7fdb8bfb2ab0:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7fdb8bfb2ab6:	c1 e1 06             	shl    $0x6,%ecx
    7fdb8bfb2ab9:	8b c9                	mov    %ecx,%ecx
    7fdb8bfb2abb:	48 03 c1             	add    %rcx,%rax
    7fdb8bfb2abe:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7fdb8bfb2ac5:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2ac8:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2acb:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2acf:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2ad3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2ad7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2adb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2adf:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2ae3:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fdb8bfb2ae9:	85 c0                	test   %eax,%eax
    7fdb8bfb2aeb:	0f 84 30 00 00 00    	je     0x7fdb8bfb2b21
    7fdb8bfb2af1:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fdb8bfb2af4:	c1 e0 06             	shl    $0x6,%eax
    7fdb8bfb2af7:	8b c0                	mov    %eax,%eax
    7fdb8bfb2af9:	49 03 c7             	add    %r15,%rax
    7fdb8bfb2afc:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7fdb8bfb2b03:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2b06:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2b09:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2b0d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2b11:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2b15:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2b19:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2b1d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2b21:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2b24:	48 05 48 10 00 00    	add    $0x1048,%rax
    7fdb8bfb2b2a:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2b2d:	48 81 c1 80 0c 00 00 	add    $0xc80,%rcx
    7fdb8bfb2b34:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2b37:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2b3a:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2b3e:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2b42:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2b46:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2b4a:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2b4e:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2b52:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2b55:	48 05 08 10 00 00    	add    $0x1008,%rax
    7fdb8bfb2b5b:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2b5e:	48 81 c1 78 0f 00 00 	add    $0xf78,%rcx
    7fdb8bfb2b65:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2b68:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2b6b:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2b6f:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2b73:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2b77:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2b7b:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2b7f:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2b83:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb2b86:	0f 84 44 00 00 00    	je     0x7fdb8bfb2bd0
    7fdb8bfb2b8c:	41 c7 87 00 10 00 00 	movl   $0x0,0x1000(%r15)
    7fdb8bfb2b93:	00 00 00 00 
    7fdb8bfb2b97:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%rbp)
    7fdb8bfb2b9e:	00 00 00 
    7fdb8bfb2ba1:	41 c7 87 f0 0f 00 00 	movl   $0x0,0xff0(%r15)
    7fdb8bfb2ba8:	00 00 00 00 
    7fdb8bfb2bac:	c7 85 98 fe ff ff 00 	movl   $0x0,-0x168(%rbp)
    7fdb8bfb2bb3:	00 00 00 
    7fdb8bfb2bb6:	41 c7 87 f8 0f 00 00 	movl   $0x1,0xff8(%r15)
    7fdb8bfb2bbd:	01 00 00 00 
    7fdb8bfb2bc1:	c7 85 90 fe ff ff 01 	movl   $0x1,-0x170(%rbp)
    7fdb8bfb2bc8:	00 00 00 
    7fdb8bfb2bcb:	e9 47 00 00 00       	jmpq   0x7fdb8bfb2c17
    7fdb8bfb2bd0:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7fdb8bfb2bd6:	41 89 87 00 10 00 00 	mov    %eax,0x1000(%r15)
    7fdb8bfb2bdd:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fdb8bfb2be3:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7fdb8bfb2be9:	85 c0                	test   %eax,%eax
    7fdb8bfb2beb:	0f 84 26 00 00 00    	je     0x7fdb8bfb2c17
    7fdb8bfb2bf1:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fdb8bfb2bf7:	41 89 87 f0 0f 00 00 	mov    %eax,0xff0(%r15)
    7fdb8bfb2bfe:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fdb8bfb2c04:	8b 85 f8 f9 ff ff    	mov    -0x608(%rbp),%eax
    7fdb8bfb2c0a:	41 89 87 f8 0f 00 00 	mov    %eax,0xff8(%r15)
    7fdb8bfb2c11:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fdb8bfb2c17:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fdb8bfb2c1d:	85 c0                	test   %eax,%eax
    7fdb8bfb2c1f:	0f 84 1a 00 00 00    	je     0x7fdb8bfb2c3f
    7fdb8bfb2c25:	41 c7 87 e8 0f 00 00 	movl   $0x0,0xfe8(%r15)
    7fdb8bfb2c2c:	00 00 00 00 
    7fdb8bfb2c30:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7fdb8bfb2c37:	00 00 00 
    7fdb8bfb2c3a:	e9 21 00 00 00       	jmpq   0x7fdb8bfb2c60
    7fdb8bfb2c3f:	8b 85 48 fa ff ff    	mov    -0x5b8(%rbp),%eax
    7fdb8bfb2c45:	85 c0                	test   %eax,%eax
    7fdb8bfb2c47:	0f 84 13 00 00 00    	je     0x7fdb8bfb2c60
    7fdb8bfb2c4d:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7fdb8bfb2c53:	41 89 87 e8 0f 00 00 	mov    %eax,0xfe8(%r15)
    7fdb8bfb2c5a:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fdb8bfb2c60:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb2c63:	0f 84 52 00 00 00    	je     0x7fdb8bfb2cbb
    7fdb8bfb2c69:	41 c7 87 e0 0f 00 00 	movl   $0x0,0xfe0(%r15)
    7fdb8bfb2c70:	00 00 00 00 
    7fdb8bfb2c74:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7fdb8bfb2c7b:	00 00 00 
    7fdb8bfb2c7e:	41 c7 87 d8 0f 00 00 	movl   $0x1,0xfd8(%r15)
    7fdb8bfb2c85:	01 00 00 00 
    7fdb8bfb2c89:	c7 85 b0 fe ff ff 01 	movl   $0x1,-0x150(%rbp)
    7fdb8bfb2c90:	00 00 00 
    7fdb8bfb2c93:	41 c7 87 d0 0f 00 00 	movl   $0x0,0xfd0(%r15)
    7fdb8bfb2c9a:	00 00 00 00 
    7fdb8bfb2c9e:	45 33 e4             	xor    %r12d,%r12d
    7fdb8bfb2ca1:	41 c7 87 c8 0f 00 00 	movl   $0x0,0xfc8(%r15)
    7fdb8bfb2ca8:	00 00 00 00 
    7fdb8bfb2cac:	c7 85 b8 fe ff ff 00 	movl   $0x0,-0x148(%rbp)
    7fdb8bfb2cb3:	00 00 00 
    7fdb8bfb2cb6:	e9 49 00 00 00       	jmpq   0x7fdb8bfb2d04
    7fdb8bfb2cbb:	8b 85 08 fa ff ff    	mov    -0x5f8(%rbp),%eax
    7fdb8bfb2cc1:	41 89 87 e0 0f 00 00 	mov    %eax,0xfe0(%r15)
    7fdb8bfb2cc8:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fdb8bfb2cce:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7fdb8bfb2cd4:	41 89 87 d8 0f 00 00 	mov    %eax,0xfd8(%r15)
    7fdb8bfb2cdb:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fdb8bfb2ce1:	8b 85 20 fa ff ff    	mov    -0x5e0(%rbp),%eax
    7fdb8bfb2ce7:	41 89 87 d0 0f 00 00 	mov    %eax,0xfd0(%r15)
    7fdb8bfb2cee:	4c 8b e0             	mov    %rax,%r12
    7fdb8bfb2cf1:	8b 85 e0 fa ff ff    	mov    -0x520(%rbp),%eax
    7fdb8bfb2cf7:	41 89 87 c8 0f 00 00 	mov    %eax,0xfc8(%r15)
    7fdb8bfb2cfe:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fdb8bfb2d04:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7fdb8bfb2d0a:	85 c0                	test   %eax,%eax
    7fdb8bfb2d0c:	0f 84 1a 00 00 00    	je     0x7fdb8bfb2d2c
    7fdb8bfb2d12:	41 c7 87 c0 0f 00 00 	movl   $0x0,0xfc0(%r15)
    7fdb8bfb2d19:	00 00 00 00 
    7fdb8bfb2d1d:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7fdb8bfb2d24:	00 00 00 
    7fdb8bfb2d27:	e9 21 00 00 00       	jmpq   0x7fdb8bfb2d4d
    7fdb8bfb2d2c:	8b 85 78 fa ff ff    	mov    -0x588(%rbp),%eax
    7fdb8bfb2d32:	85 c0                	test   %eax,%eax
    7fdb8bfb2d34:	0f 84 13 00 00 00    	je     0x7fdb8bfb2d4d
    7fdb8bfb2d3a:	8b 85 68 fa ff ff    	mov    -0x598(%rbp),%eax
    7fdb8bfb2d40:	41 89 87 c0 0f 00 00 	mov    %eax,0xfc0(%r15)
    7fdb8bfb2d47:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fdb8bfb2d4d:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb2d50:	0f 84 1a 00 00 00    	je     0x7fdb8bfb2d70
    7fdb8bfb2d56:	41 c7 87 b8 0f 00 00 	movl   $0x0,0xfb8(%r15)
    7fdb8bfb2d5d:	00 00 00 00 
    7fdb8bfb2d61:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7fdb8bfb2d68:	00 00 00 
    7fdb8bfb2d6b:	e9 13 00 00 00       	jmpq   0x7fdb8bfb2d83
    7fdb8bfb2d70:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7fdb8bfb2d76:	41 89 87 b8 0f 00 00 	mov    %eax,0xfb8(%r15)
    7fdb8bfb2d7d:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7fdb8bfb2d83:	8b 85 78 fa ff ff    	mov    -0x588(%rbp),%eax
    7fdb8bfb2d89:	85 c0                	test   %eax,%eax
    7fdb8bfb2d8b:	0f 84 31 00 00 00    	je     0x7fdb8bfb2dc2
    7fdb8bfb2d91:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2d94:	48 05 78 0f 00 00    	add    $0xf78,%rax
    7fdb8bfb2d9a:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2d9d:	48 81 c1 88 11 00 00 	add    $0x1188,%rcx
    7fdb8bfb2da4:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2da7:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2daa:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2dae:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2db2:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2db6:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2dba:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2dbe:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2dc2:	8b 85 18 fb ff ff    	mov    -0x4e8(%rbp),%eax
    7fdb8bfb2dc8:	85 c0                	test   %eax,%eax
    7fdb8bfb2dca:	0f 84 13 00 00 00    	je     0x7fdb8bfb2de3
    7fdb8bfb2dd0:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fdb8bfb2dd6:	41 89 87 70 0f 00 00 	mov    %eax,0xf70(%r15)
    7fdb8bfb2ddd:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fdb8bfb2de3:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb2de6:	0f 84 5a 00 00 00    	je     0x7fdb8bfb2e46
    7fdb8bfb2dec:	41 c7 87 68 0f 00 00 	movl   $0x0,0xf68(%r15)
    7fdb8bfb2df3:	00 00 00 00 
    7fdb8bfb2df7:	c7 85 d8 fe ff ff 00 	movl   $0x0,-0x128(%rbp)
    7fdb8bfb2dfe:	00 00 00 
    7fdb8bfb2e01:	41 c7 87 60 0f 00 00 	movl   $0x0,0xf60(%r15)
    7fdb8bfb2e08:	00 00 00 00 
    7fdb8bfb2e0c:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7fdb8bfb2e13:	00 00 00 
    7fdb8bfb2e16:	41 c7 87 58 0f 00 00 	movl   $0x0,0xf58(%r15)
    7fdb8bfb2e1d:	00 00 00 00 
    7fdb8bfb2e21:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7fdb8bfb2e28:	00 00 00 
    7fdb8bfb2e2b:	49 c7 87 50 0f 00 00 	movq   $0x0,0xf50(%r15)
    7fdb8bfb2e32:	00 00 00 00 
    7fdb8bfb2e36:	48 c7 85 f0 fe ff ff 	movq   $0x0,-0x110(%rbp)
    7fdb8bfb2e3d:	00 00 00 00 
    7fdb8bfb2e41:	e9 4e 00 00 00       	jmpq   0x7fdb8bfb2e94
    7fdb8bfb2e46:	8b 85 b8 fa ff ff    	mov    -0x548(%rbp),%eax
    7fdb8bfb2e4c:	41 89 87 68 0f 00 00 	mov    %eax,0xf68(%r15)
    7fdb8bfb2e53:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fdb8bfb2e59:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7fdb8bfb2e5f:	41 89 87 60 0f 00 00 	mov    %eax,0xf60(%r15)
    7fdb8bfb2e66:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fdb8bfb2e6c:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7fdb8bfb2e72:	41 89 87 58 0f 00 00 	mov    %eax,0xf58(%r15)
    7fdb8bfb2e79:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7fdb8bfb2e7f:	48 8b 85 30 fb ff ff 	mov    -0x4d0(%rbp),%rax
    7fdb8bfb2e86:	49 89 87 50 0f 00 00 	mov    %rax,0xf50(%r15)
    7fdb8bfb2e8d:	48 89 85 f0 fe ff ff 	mov    %rax,-0x110(%rbp)
    7fdb8bfb2e94:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2e97:	48 05 10 0f 00 00    	add    $0xf10,%rax
    7fdb8bfb2e9d:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb2ea0:	48 81 c1 40 0c 00 00 	add    $0xc40,%rcx
    7fdb8bfb2ea7:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2eaa:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2ead:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2eb1:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2eb5:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2eb9:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2ebd:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2ec1:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2ec5:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb2ec8:	48 05 d0 0e 00 00    	add    $0xed0,%rax
    7fdb8bfb2ece:	48 8b 8d 60 fb ff ff 	mov    -0x4a0(%rbp),%rcx
    7fdb8bfb2ed5:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb2ed8:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb2edb:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb2edf:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb2ee3:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb2ee7:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb2eeb:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb2eef:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb2ef3:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb2ef6:	0f 84 44 00 00 00    	je     0x7fdb8bfb2f40
    7fdb8bfb2efc:	41 c7 87 c8 0e 00 00 	movl   $0x0,0xec8(%r15)
    7fdb8bfb2f03:	00 00 00 00 
    7fdb8bfb2f07:	c7 85 f8 fe ff ff 00 	movl   $0x0,-0x108(%rbp)
    7fdb8bfb2f0e:	00 00 00 
    7fdb8bfb2f11:	41 c7 87 b8 0e 00 00 	movl   $0x0,0xeb8(%r15)
    7fdb8bfb2f18:	00 00 00 00 
    7fdb8bfb2f1c:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7fdb8bfb2f23:	00 00 00 
    7fdb8bfb2f26:	41 c7 87 c0 0e 00 00 	movl   $0x1,0xec0(%r15)
    7fdb8bfb2f2d:	01 00 00 00 
    7fdb8bfb2f31:	c7 85 00 ff ff ff 01 	movl   $0x1,-0x100(%rbp)
    7fdb8bfb2f38:	00 00 00 
    7fdb8bfb2f3b:	e9 47 00 00 00       	jmpq   0x7fdb8bfb2f87
    7fdb8bfb2f40:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7fdb8bfb2f46:	41 89 87 c8 0e 00 00 	mov    %eax,0xec8(%r15)
    7fdb8bfb2f4d:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fdb8bfb2f53:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7fdb8bfb2f59:	85 c0                	test   %eax,%eax
    7fdb8bfb2f5b:	0f 84 26 00 00 00    	je     0x7fdb8bfb2f87
    7fdb8bfb2f61:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fdb8bfb2f67:	41 89 87 b8 0e 00 00 	mov    %eax,0xeb8(%r15)
    7fdb8bfb2f6e:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fdb8bfb2f74:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fdb8bfb2f7a:	41 89 87 c0 0e 00 00 	mov    %eax,0xec0(%r15)
    7fdb8bfb2f81:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fdb8bfb2f87:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fdb8bfb2f8d:	85 c0                	test   %eax,%eax
    7fdb8bfb2f8f:	0f 84 1a 00 00 00    	je     0x7fdb8bfb2faf
    7fdb8bfb2f95:	41 c7 87 b0 0e 00 00 	movl   $0x0,0xeb0(%r15)
    7fdb8bfb2f9c:	00 00 00 00 
    7fdb8bfb2fa0:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7fdb8bfb2fa7:	00 00 00 
    7fdb8bfb2faa:	e9 21 00 00 00       	jmpq   0x7fdb8bfb2fd0
    7fdb8bfb2faf:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fdb8bfb2fb5:	85 c0                	test   %eax,%eax
    7fdb8bfb2fb7:	0f 84 13 00 00 00    	je     0x7fdb8bfb2fd0
    7fdb8bfb2fbd:	8b 85 78 fb ff ff    	mov    -0x488(%rbp),%eax
    7fdb8bfb2fc3:	41 89 87 b0 0e 00 00 	mov    %eax,0xeb0(%r15)
    7fdb8bfb2fca:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7fdb8bfb2fd0:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb2fd3:	0f 84 44 00 00 00    	je     0x7fdb8bfb301d
    7fdb8bfb2fd9:	41 c7 87 a8 0e 00 00 	movl   $0x0,0xea8(%r15)
    7fdb8bfb2fe0:	00 00 00 00 
    7fdb8bfb2fe4:	c7 85 18 ff ff ff 00 	movl   $0x0,-0xe8(%rbp)
    7fdb8bfb2feb:	00 00 00 
    7fdb8bfb2fee:	41 c7 87 a0 0e 00 00 	movl   $0x1,0xea0(%r15)
    7fdb8bfb2ff5:	01 00 00 00 
    7fdb8bfb2ff9:	c7 85 20 ff ff ff 01 	movl   $0x1,-0xe0(%rbp)
    7fdb8bfb3000:	00 00 00 
    7fdb8bfb3003:	41 c7 87 98 0e 00 00 	movl   $0x0,0xe98(%r15)
    7fdb8bfb300a:	00 00 00 00 
    7fdb8bfb300e:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7fdb8bfb3015:	00 00 00 
    7fdb8bfb3018:	e9 39 00 00 00       	jmpq   0x7fdb8bfb3056
    7fdb8bfb301d:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7fdb8bfb3023:	41 89 87 a8 0e 00 00 	mov    %eax,0xea8(%r15)
    7fdb8bfb302a:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fdb8bfb3030:	8b 85 88 fb ff ff    	mov    -0x478(%rbp),%eax
    7fdb8bfb3036:	41 89 87 a0 0e 00 00 	mov    %eax,0xea0(%r15)
    7fdb8bfb303d:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7fdb8bfb3043:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7fdb8bfb3049:	41 89 87 98 0e 00 00 	mov    %eax,0xe98(%r15)
    7fdb8bfb3050:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fdb8bfb3056:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fdb8bfb305c:	85 c0                	test   %eax,%eax
    7fdb8bfb305e:	0f 84 1a 00 00 00    	je     0x7fdb8bfb307e
    7fdb8bfb3064:	41 c7 87 90 0e 00 00 	movl   $0x0,0xe90(%r15)
    7fdb8bfb306b:	00 00 00 00 
    7fdb8bfb306f:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7fdb8bfb3076:	00 00 00 
    7fdb8bfb3079:	e9 21 00 00 00       	jmpq   0x7fdb8bfb309f
    7fdb8bfb307e:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fdb8bfb3084:	85 c0                	test   %eax,%eax
    7fdb8bfb3086:	0f 84 13 00 00 00    	je     0x7fdb8bfb309f
    7fdb8bfb308c:	8b 85 d8 fb ff ff    	mov    -0x428(%rbp),%eax
    7fdb8bfb3092:	41 89 87 90 0e 00 00 	mov    %eax,0xe90(%r15)
    7fdb8bfb3099:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fdb8bfb309f:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb30a2:	0f 84 1a 00 00 00    	je     0x7fdb8bfb30c2
    7fdb8bfb30a8:	41 c7 87 88 0e 00 00 	movl   $0x0,0xe88(%r15)
    7fdb8bfb30af:	00 00 00 00 
    7fdb8bfb30b3:	c7 85 38 ff ff ff 00 	movl   $0x0,-0xc8(%rbp)
    7fdb8bfb30ba:	00 00 00 
    7fdb8bfb30bd:	e9 13 00 00 00       	jmpq   0x7fdb8bfb30d5
    7fdb8bfb30c2:	8b 85 e0 fb ff ff    	mov    -0x420(%rbp),%eax
    7fdb8bfb30c8:	41 89 87 88 0e 00 00 	mov    %eax,0xe88(%r15)
    7fdb8bfb30cf:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fdb8bfb30d5:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb30d8:	48 05 48 0e 00 00    	add    $0xe48,%rax
    7fdb8bfb30de:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb30e1:	48 81 c1 08 11 00 00 	add    $0x1108,%rcx
    7fdb8bfb30e8:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb30eb:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb30ee:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb30f2:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb30f6:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb30fa:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb30fe:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb3102:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb3106:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb3109:	0f 84 6f 00 00 00    	je     0x7fdb8bfb317e
    7fdb8bfb310f:	41 c7 87 40 0e 00 00 	movl   $0x0,0xe40(%r15)
    7fdb8bfb3116:	00 00 00 00 
    7fdb8bfb311a:	c7 85 40 ff ff ff 00 	movl   $0x0,-0xc0(%rbp)
    7fdb8bfb3121:	00 00 00 
    7fdb8bfb3124:	41 c7 87 38 0e 00 00 	movl   $0x0,0xe38(%r15)
    7fdb8bfb312b:	00 00 00 00 
    7fdb8bfb312f:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7fdb8bfb3136:	00 00 00 
    7fdb8bfb3139:	41 c7 87 30 0e 00 00 	movl   $0x0,0xe30(%r15)
    7fdb8bfb3140:	00 00 00 00 
    7fdb8bfb3144:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7fdb8bfb314b:	00 00 00 
    7fdb8bfb314e:	41 c7 87 28 0e 00 00 	movl   $0x0,0xe28(%r15)
    7fdb8bfb3155:	00 00 00 00 
    7fdb8bfb3159:	c7 85 58 ff ff ff 00 	movl   $0x0,-0xa8(%rbp)
    7fdb8bfb3160:	00 00 00 
    7fdb8bfb3163:	49 c7 87 20 0e 00 00 	movq   $0x0,0xe20(%r15)
    7fdb8bfb316a:	00 00 00 00 
    7fdb8bfb316e:	48 c7 85 60 ff ff ff 	movq   $0x0,-0xa0(%rbp)
    7fdb8bfb3175:	00 00 00 00 
    7fdb8bfb3179:	e9 61 00 00 00       	jmpq   0x7fdb8bfb31df
    7fdb8bfb317e:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fdb8bfb3184:	41 89 87 40 0e 00 00 	mov    %eax,0xe40(%r15)
    7fdb8bfb318b:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fdb8bfb3191:	8b 85 08 fc ff ff    	mov    -0x3f8(%rbp),%eax
    7fdb8bfb3197:	41 89 87 38 0e 00 00 	mov    %eax,0xe38(%r15)
    7fdb8bfb319e:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fdb8bfb31a4:	8b 85 20 fc ff ff    	mov    -0x3e0(%rbp),%eax
    7fdb8bfb31aa:	41 89 87 30 0e 00 00 	mov    %eax,0xe30(%r15)
    7fdb8bfb31b1:	89 85 50 ff ff ff    	mov    %eax,-0xb0(%rbp)
    7fdb8bfb31b7:	8b 85 30 fc ff ff    	mov    -0x3d0(%rbp),%eax
    7fdb8bfb31bd:	41 89 87 28 0e 00 00 	mov    %eax,0xe28(%r15)
    7fdb8bfb31c4:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fdb8bfb31ca:	48 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%rax
    7fdb8bfb31d1:	49 89 87 20 0e 00 00 	mov    %rax,0xe20(%r15)
    7fdb8bfb31d8:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
    7fdb8bfb31df:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb31e2:	48 05 e0 0d 00 00    	add    $0xde0,%rax
    7fdb8bfb31e8:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb31eb:	48 81 c1 00 0c 00 00 	add    $0xc00,%rcx
    7fdb8bfb31f2:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb31f5:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb31f8:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb31fc:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb3200:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb3204:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb3208:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb320c:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb3210:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb3213:	48 05 a0 0d 00 00    	add    $0xda0,%rax
    7fdb8bfb3219:	48 8b 8d a8 fc ff ff 	mov    -0x358(%rbp),%rcx
    7fdb8bfb3220:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb3223:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb3226:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb322a:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb322e:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb3232:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb3236:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb323a:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb323e:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb3241:	0f 84 44 00 00 00    	je     0x7fdb8bfb328b
    7fdb8bfb3247:	41 c7 87 98 0d 00 00 	movl   $0x0,0xd98(%r15)
    7fdb8bfb324e:	00 00 00 00 
    7fdb8bfb3252:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7fdb8bfb3259:	00 00 00 
    7fdb8bfb325c:	41 c7 87 88 0d 00 00 	movl   $0x0,0xd88(%r15)
    7fdb8bfb3263:	00 00 00 00 
    7fdb8bfb3267:	c7 85 78 ff ff ff 00 	movl   $0x0,-0x88(%rbp)
    7fdb8bfb326e:	00 00 00 
    7fdb8bfb3271:	41 c7 87 90 0d 00 00 	movl   $0x1,0xd90(%r15)
    7fdb8bfb3278:	01 00 00 00 
    7fdb8bfb327c:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%rbp)
    7fdb8bfb3283:	00 00 00 
    7fdb8bfb3286:	e9 47 00 00 00       	jmpq   0x7fdb8bfb32d2
    7fdb8bfb328b:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7fdb8bfb3291:	41 89 87 98 0d 00 00 	mov    %eax,0xd98(%r15)
    7fdb8bfb3298:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fdb8bfb329e:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fdb8bfb32a4:	85 c0                	test   %eax,%eax
    7fdb8bfb32a6:	0f 84 26 00 00 00    	je     0x7fdb8bfb32d2
    7fdb8bfb32ac:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fdb8bfb32b2:	41 89 87 88 0d 00 00 	mov    %eax,0xd88(%r15)
    7fdb8bfb32b9:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7fdb8bfb32bf:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7fdb8bfb32c5:	41 89 87 90 0d 00 00 	mov    %eax,0xd90(%r15)
    7fdb8bfb32cc:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7fdb8bfb32d2:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fdb8bfb32d8:	85 c0                	test   %eax,%eax
    7fdb8bfb32da:	0f 84 17 00 00 00    	je     0x7fdb8bfb32f7
    7fdb8bfb32e0:	41 c7 87 80 0d 00 00 	movl   $0x0,0xd80(%r15)
    7fdb8bfb32e7:	00 00 00 00 
    7fdb8bfb32eb:	c7 45 80 00 00 00 00 	movl   $0x0,-0x80(%rbp)
    7fdb8bfb32f2:	e9 1e 00 00 00       	jmpq   0x7fdb8bfb3315
    7fdb8bfb32f7:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fdb8bfb32fd:	85 c0                	test   %eax,%eax
    7fdb8bfb32ff:	0f 84 10 00 00 00    	je     0x7fdb8bfb3315
    7fdb8bfb3305:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fdb8bfb330b:	41 89 87 80 0d 00 00 	mov    %eax,0xd80(%r15)
    7fdb8bfb3312:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fdb8bfb3315:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb3318:	0f 84 3b 00 00 00    	je     0x7fdb8bfb3359
    7fdb8bfb331e:	41 c7 87 78 0d 00 00 	movl   $0x0,0xd78(%r15)
    7fdb8bfb3325:	00 00 00 00 
    7fdb8bfb3329:	c7 45 88 00 00 00 00 	movl   $0x0,-0x78(%rbp)
    7fdb8bfb3330:	41 c7 87 70 0d 00 00 	movl   $0x1,0xd70(%r15)
    7fdb8bfb3337:	01 00 00 00 
    7fdb8bfb333b:	c7 45 90 01 00 00 00 	movl   $0x1,-0x70(%rbp)
    7fdb8bfb3342:	41 c7 87 68 0d 00 00 	movl   $0x0,0xd68(%r15)
    7fdb8bfb3349:	00 00 00 00 
    7fdb8bfb334d:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fdb8bfb3354:	e9 30 00 00 00       	jmpq   0x7fdb8bfb3389
    7fdb8bfb3359:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7fdb8bfb335f:	41 89 87 78 0d 00 00 	mov    %eax,0xd78(%r15)
    7fdb8bfb3366:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fdb8bfb3369:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7fdb8bfb336f:	41 89 87 70 0d 00 00 	mov    %eax,0xd70(%r15)
    7fdb8bfb3376:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fdb8bfb3379:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7fdb8bfb337f:	41 89 87 68 0d 00 00 	mov    %eax,0xd68(%r15)
    7fdb8bfb3386:	89 45 98             	mov    %eax,-0x68(%rbp)
    7fdb8bfb3389:	8b 85 20 fd ff ff    	mov    -0x2e0(%rbp),%eax
    7fdb8bfb338f:	85 c0                	test   %eax,%eax
    7fdb8bfb3391:	0f 84 17 00 00 00    	je     0x7fdb8bfb33ae
    7fdb8bfb3397:	41 c7 87 60 0d 00 00 	movl   $0x0,0xd60(%r15)
    7fdb8bfb339e:	00 00 00 00 
    7fdb8bfb33a2:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7fdb8bfb33a9:	e9 1e 00 00 00       	jmpq   0x7fdb8bfb33cc
    7fdb8bfb33ae:	8b 85 48 fd ff ff    	mov    -0x2b8(%rbp),%eax
    7fdb8bfb33b4:	85 c0                	test   %eax,%eax
    7fdb8bfb33b6:	0f 84 10 00 00 00    	je     0x7fdb8bfb33cc
    7fdb8bfb33bc:	8b 85 28 fd ff ff    	mov    -0x2d8(%rbp),%eax
    7fdb8bfb33c2:	41 89 87 60 0d 00 00 	mov    %eax,0xd60(%r15)
    7fdb8bfb33c9:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fdb8bfb33cc:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb33cf:	0f 84 17 00 00 00    	je     0x7fdb8bfb33ec
    7fdb8bfb33d5:	41 c7 87 58 0d 00 00 	movl   $0x0,0xd58(%r15)
    7fdb8bfb33dc:	00 00 00 00 
    7fdb8bfb33e0:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
    7fdb8bfb33e7:	e9 10 00 00 00       	jmpq   0x7fdb8bfb33fc
    7fdb8bfb33ec:	8b 85 30 fd ff ff    	mov    -0x2d0(%rbp),%eax
    7fdb8bfb33f2:	41 89 87 58 0d 00 00 	mov    %eax,0xd58(%r15)
    7fdb8bfb33f9:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7fdb8bfb33fc:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb33ff:	48 05 18 0d 00 00    	add    $0xd18,%rax
    7fdb8bfb3405:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb3408:	48 81 c1 88 10 00 00 	add    $0x1088,%rcx
    7fdb8bfb340f:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb3412:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb3415:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb3419:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb341d:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb3421:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb3425:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb3429:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb342d:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb3430:	0f 84 7d 00 00 00    	je     0x7fdb8bfb34b3
    7fdb8bfb3436:	41 c7 87 10 0d 00 00 	movl   $0x0,0xd10(%r15)
    7fdb8bfb343d:	00 00 00 00 
    7fdb8bfb3441:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7fdb8bfb3448:	41 c7 87 08 0d 00 00 	movl   $0x0,0xd08(%r15)
    7fdb8bfb344f:	00 00 00 00 
    7fdb8bfb3453:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7fdb8bfb345a:	41 c7 87 00 0d 00 00 	movl   $0x0,0xd00(%r15)
    7fdb8bfb3461:	00 00 00 00 
    7fdb8bfb3465:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    7fdb8bfb346c:	41 c7 87 f8 0c 00 00 	movl   $0x0,0xcf8(%r15)
    7fdb8bfb3473:	00 00 00 00 
    7fdb8bfb3477:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
    7fdb8bfb347e:	49 c7 87 f0 0c 00 00 	movq   $0x0,0xcf0(%r15)
    7fdb8bfb3485:	00 00 00 00 
    7fdb8bfb3489:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
    7fdb8bfb3490:	00 
    7fdb8bfb3491:	41 c7 87 e0 0c 00 00 	movl   $0x0,0xce0(%r15)
    7fdb8bfb3498:	00 00 00 00 
    7fdb8bfb349c:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7fdb8bfb34a3:	41 c7 87 e8 0c 00 00 	movl   $0x0,0xce8(%r15)
    7fdb8bfb34aa:	00 00 00 00 
    7fdb8bfb34ae:	e9 7e 00 00 00       	jmpq   0x7fdb8bfb3531
    7fdb8bfb34b3:	8b 85 50 fd ff ff    	mov    -0x2b0(%rbp),%eax
    7fdb8bfb34b9:	41 89 87 10 0d 00 00 	mov    %eax,0xd10(%r15)
    7fdb8bfb34c0:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fdb8bfb34c3:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7fdb8bfb34c9:	41 89 87 08 0d 00 00 	mov    %eax,0xd08(%r15)
    7fdb8bfb34d0:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fdb8bfb34d3:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fdb8bfb34d9:	41 89 87 00 0d 00 00 	mov    %eax,0xd00(%r15)
    7fdb8bfb34e0:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fdb8bfb34e3:	8b 85 a0 fd ff ff    	mov    -0x260(%rbp),%eax
    7fdb8bfb34e9:	41 89 87 f8 0c 00 00 	mov    %eax,0xcf8(%r15)
    7fdb8bfb34f0:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fdb8bfb34f3:	48 8b 85 f0 fd ff ff 	mov    -0x210(%rbp),%rax
    7fdb8bfb34fa:	49 89 87 f0 0c 00 00 	mov    %rax,0xcf0(%r15)
    7fdb8bfb3501:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    7fdb8bfb3505:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fdb8bfb350b:	85 c0                	test   %eax,%eax
    7fdb8bfb350d:	0f 84 1e 00 00 00    	je     0x7fdb8bfb3531
    7fdb8bfb3513:	41 8b 87 e8 0c 00 00 	mov    0xce8(%r15),%eax
    7fdb8bfb351a:	41 89 87 e0 0c 00 00 	mov    %eax,0xce0(%r15)
    7fdb8bfb3521:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7fdb8bfb3524:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fdb8bfb352a:	41 89 87 e8 0c 00 00 	mov    %eax,0xce8(%r15)
    7fdb8bfb3531:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fdb8bfb3537:	85 c0                	test   %eax,%eax
    7fdb8bfb3539:	0f 84 1e 00 00 00    	je     0x7fdb8bfb355d
    7fdb8bfb353f:	41 8b 87 d8 0c 00 00 	mov    0xcd8(%r15),%eax
    7fdb8bfb3546:	41 89 87 d0 0c 00 00 	mov    %eax,0xcd0(%r15)
    7fdb8bfb354d:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fdb8bfb3550:	8b 85 28 fe ff ff    	mov    -0x1d8(%rbp),%eax
    7fdb8bfb3556:	41 89 87 d8 0c 00 00 	mov    %eax,0xcd8(%r15)
    7fdb8bfb355d:	45 85 ed             	test   %r13d,%r13d
    7fdb8bfb3560:	0f 84 29 00 00 00    	je     0x7fdb8bfb358f
    7fdb8bfb3566:	41 c7 87 c8 0c 00 00 	movl   $0x0,0xcc8(%r15)
    7fdb8bfb356d:	00 00 00 00 
    7fdb8bfb3571:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
    7fdb8bfb3578:	41 c7 87 c0 0c 00 00 	movl   $0x0,0xcc0(%r15)
    7fdb8bfb357f:	00 00 00 00 
    7fdb8bfb3583:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7fdb8bfb358a:	e9 20 00 00 00       	jmpq   0x7fdb8bfb35af
    7fdb8bfb358f:	8b 85 30 fe ff ff    	mov    -0x1d0(%rbp),%eax
    7fdb8bfb3595:	41 89 87 c8 0c 00 00 	mov    %eax,0xcc8(%r15)
    7fdb8bfb359c:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7fdb8bfb359f:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7fdb8bfb35a5:	41 89 87 c0 0c 00 00 	mov    %eax,0xcc0(%r15)
    7fdb8bfb35ac:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fdb8bfb35af:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7fdb8bfb35b2:	85 c9                	test   %ecx,%ecx
    7fdb8bfb35b4:	0f 94 c0             	sete   %al
    7fdb8bfb35b7:	0f b6 c0             	movzbl %al,%eax
    7fdb8bfb35ba:	49 8b 96 a0 00 00 00 	mov    0xa0(%r14),%rdx
    7fdb8bfb35c1:	89 02                	mov    %eax,(%rdx)
    7fdb8bfb35c3:	83 f9 02             	cmp    $0x2,%ecx
    7fdb8bfb35c6:	0f 94 c1             	sete   %cl
    7fdb8bfb35c9:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb35cc:	8b c1                	mov    %ecx,%eax
    7fdb8bfb35ce:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7fdb8bfb35d4:	85 c9                	test   %ecx,%ecx
    7fdb8bfb35d6:	0f 94 c1             	sete   %cl
    7fdb8bfb35d9:	0f b6 c9             	movzbl %cl,%ecx
    7fdb8bfb35dc:	23 c1                	and    %ecx,%eax
    7fdb8bfb35de:	49 8b 8e a8 00 00 00 	mov    0xa8(%r14),%rcx
    7fdb8bfb35e5:	89 01                	mov    %eax,(%rcx)
    7fdb8bfb35e7:	49 8b 86 b0 00 00 00 	mov    0xb0(%r14),%rax
    7fdb8bfb35ee:	48 8b 8d f0 fe ff ff 	mov    -0x110(%rbp),%rcx
    7fdb8bfb35f5:	48 89 08             	mov    %rcx,(%rax)
    7fdb8bfb35f8:	49 8b 86 b8 00 00 00 	mov    0xb8(%r14),%rax
    7fdb8bfb35ff:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7fdb8bfb3605:	49 8b 86 c0 00 00 00 	mov    0xc0(%r14),%rax
    7fdb8bfb360c:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7fdb8bfb3612:	89 08                	mov    %ecx,(%rax)
    7fdb8bfb3614:	8b 85 88 fe ff ff    	mov    -0x178(%rbp),%eax
    7fdb8bfb361a:	85 c0                	test   %eax,%eax
    7fdb8bfb361c:	0f 85 36 00 00 00    	jne    0x7fdb8bfb3658
    7fdb8bfb3622:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb3625:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7fdb8bfb362b:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb362e:	48 81 c1 48 10 00 00 	add    $0x1048,%rcx
    7fdb8bfb3635:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb3638:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb363b:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb363f:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb3643:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb3647:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb364b:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb364f:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb3653:	e9 31 00 00 00       	jmpq   0x7fdb8bfb3689
    7fdb8bfb3658:	49 8b c7             	mov    %r15,%rax
    7fdb8bfb365b:	48 05 c8 11 00 00    	add    $0x11c8,%rax
    7fdb8bfb3661:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb3664:	48 81 c1 08 10 00 00 	add    $0x1008,%rcx
    7fdb8bfb366b:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb366e:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb3671:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb3675:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb3679:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb367d:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb3681:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb3685:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb3689:	49 8b 86 c8 00 00 00 	mov    0xc8(%r14),%rax
    7fdb8bfb3690:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb3693:	48 81 c1 c8 11 00 00 	add    $0x11c8,%rcx
    7fdb8bfb369a:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb369d:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb36a0:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb36a4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb36a8:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb36ac:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb36b0:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb36b4:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb36b8:	49 8b 86 d0 00 00 00 	mov    0xd0(%r14),%rax
    7fdb8bfb36bf:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7fdb8bfb36c6:	49 8b 86 d8 00 00 00 	mov    0xd8(%r14),%rax
    7fdb8bfb36cd:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7fdb8bfb36d3:	89 08                	mov    %ecx,(%rax)
    7fdb8bfb36d5:	49 8b 86 e0 00 00 00 	mov    0xe0(%r14),%rax
    7fdb8bfb36dc:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
    7fdb8bfb36e0:	48 89 08             	mov    %rcx,(%rax)
    7fdb8bfb36e3:	49 8b 86 e8 00 00 00 	mov    0xe8(%r14),%rax
    7fdb8bfb36ea:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fdb8bfb36ed:	89 08                	mov    %ecx,(%rax)
    7fdb8bfb36ef:	49 8b 86 f0 00 00 00 	mov    0xf0(%r14),%rax
    7fdb8bfb36f6:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7fdb8bfb36fc:	49 8b 86 f8 00 00 00 	mov    0xf8(%r14),%rax
    7fdb8bfb3703:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb3706:	48 81 c1 50 13 00 00 	add    $0x1350,%rcx
    7fdb8bfb370d:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb3710:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb3713:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb3717:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb371b:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb371f:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb3723:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb3727:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb372b:	49 8b 86 00 01 00 00 	mov    0x100(%r14),%rax
    7fdb8bfb3732:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7fdb8bfb3739:	49 8b 86 08 01 00 00 	mov    0x108(%r14),%rax
    7fdb8bfb3740:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7fdb8bfb3743:	89 08                	mov    %ecx,(%rax)
    7fdb8bfb3745:	49 8b 86 10 01 00 00 	mov    0x110(%r14),%rax
    7fdb8bfb374c:	48 8b 8d 60 ff ff ff 	mov    -0xa0(%rbp),%rcx
    7fdb8bfb3753:	48 89 08             	mov    %rcx,(%rax)
    7fdb8bfb3756:	49 8b 86 18 01 00 00 	mov    0x118(%r14),%rax
    7fdb8bfb375d:	8b 8d 48 ff ff ff    	mov    -0xb8(%rbp),%ecx
    7fdb8bfb3763:	89 08                	mov    %ecx,(%rax)
    7fdb8bfb3765:	49 8b 86 20 01 00 00 	mov    0x120(%r14),%rax
    7fdb8bfb376c:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    7fdb8bfb3772:	49 8b 86 28 01 00 00 	mov    0x128(%r14),%rax
    7fdb8bfb3779:	49 8b cf             	mov    %r15,%rcx
    7fdb8bfb377c:	48 81 c1 50 13 00 00 	add    $0x1350,%rcx
    7fdb8bfb3783:	0f 10 01             	movups (%rcx),%xmm0
    7fdb8bfb3786:	0f 11 00             	movups %xmm0,(%rax)
    7fdb8bfb3789:	0f 10 41 10          	movups 0x10(%rcx),%xmm0
    7fdb8bfb378d:	0f 11 40 10          	movups %xmm0,0x10(%rax)
    7fdb8bfb3791:	0f 10 41 20          	movups 0x20(%rcx),%xmm0
    7fdb8bfb3795:	0f 11 40 20          	movups %xmm0,0x20(%rax)
    7fdb8bfb3799:	0f 10 41 30          	movups 0x30(%rcx),%xmm0
    7fdb8bfb379d:	0f 11 40 30          	movups %xmm0,0x30(%rax)
    7fdb8bfb37a1:	49 8b 86 30 01 00 00 	mov    0x130(%r14),%rax
    7fdb8bfb37a8:	48 c7 00 ff ff ff ff 	movq   $0xffffffffffffffff,(%rax)
    7fdb8bfb37af:	49 8b 86 38 01 00 00 	mov    0x138(%r14),%rax
    7fdb8bfb37b6:	8b 8d 40 ff ff ff    	mov    -0xc0(%rbp),%ecx
    7fdb8bfb37bc:	89 08                	mov    %ecx,(%rax)
    7fdb8bfb37be:	33 c0                	xor    %eax,%eax
    7fdb8bfb37c0:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fdb8bfb37c4:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fdb8bfb37c9:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fdb8bfb37ce:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fdb8bfb37d3:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fdb8bfb37d8:	48 8b e5             	mov    %rbp,%rsp
    7fdb8bfb37db:	5d                   	pop    %rbp
    7fdb8bfb37dc:	c3                   	retq   

end

