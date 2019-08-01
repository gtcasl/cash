function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fd3e20e112d <.text>:
    7fd3e20e112d:	55                   	push   %rbp
    7fd3e20e112e:	48 8b ec             	mov    %rsp,%rbp
    7fd3e20e1131:	48 81 ec 80 05 00 00 	sub    $0x580,%rsp
    7fd3e20e1138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fd3e20e113c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fd3e20e1141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fd3e20e1146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fd3e20e114b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fd3e20e1150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7fd3e20e1154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7fd3e20e1158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7fd3e20e115c:	48 8b 00             	mov    (%rax),%rax
    7fd3e20e115f:	41 8b 8f 40 01 00 00 	mov    0x140(%r15),%ecx
    7fd3e20e1166:	89 4d f0             	mov    %ecx,-0x10(%rbp)
    7fd3e20e1169:	41 8b 8f 48 01 00 00 	mov    0x148(%r15),%ecx
    7fd3e20e1170:	89 4d e8             	mov    %ecx,-0x18(%rbp)
    7fd3e20e1173:	41 8b 8f d4 01 00 00 	mov    0x1d4(%r15),%ecx
    7fd3e20e117a:	89 4d e0             	mov    %ecx,-0x20(%rbp)
    7fd3e20e117d:	41 8b 8f dc 01 00 00 	mov    0x1dc(%r15),%ecx
    7fd3e20e1184:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7fd3e20e1187:	41 8b 8f ec 01 00 00 	mov    0x1ec(%r15),%ecx
    7fd3e20e118e:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7fd3e20e1191:	41 8b 8f f4 01 00 00 	mov    0x1f4(%r15),%ecx
    7fd3e20e1198:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7fd3e20e119b:	41 8b 8f fc 01 00 00 	mov    0x1fc(%r15),%ecx
    7fd3e20e11a2:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7fd3e20e11a5:	41 8b 8f 04 02 00 00 	mov    0x204(%r15),%ecx
    7fd3e20e11ac:	89 4d b8             	mov    %ecx,-0x48(%rbp)
    7fd3e20e11af:	41 8b 8f 0c 02 00 00 	mov    0x20c(%r15),%ecx
    7fd3e20e11b6:	89 4d b0             	mov    %ecx,-0x50(%rbp)
    7fd3e20e11b9:	41 8b 8f 14 02 00 00 	mov    0x214(%r15),%ecx
    7fd3e20e11c0:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    7fd3e20e11c3:	41 8b 8f 60 02 00 00 	mov    0x260(%r15),%ecx
    7fd3e20e11ca:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7fd3e20e11cd:	41 8b 8f 68 02 00 00 	mov    0x268(%r15),%ecx
    7fd3e20e11d4:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7fd3e20e11d7:	41 8b 8f 78 02 00 00 	mov    0x278(%r15),%ecx
    7fd3e20e11de:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7fd3e20e11e1:	41 8b 8f 80 02 00 00 	mov    0x280(%r15),%ecx
    7fd3e20e11e8:	89 4d 88             	mov    %ecx,-0x78(%rbp)
    7fd3e20e11eb:	41 8b 8f 88 02 00 00 	mov    0x288(%r15),%ecx
    7fd3e20e11f2:	89 4d 80             	mov    %ecx,-0x80(%rbp)
    7fd3e20e11f5:	41 8b 8f 90 02 00 00 	mov    0x290(%r15),%ecx
    7fd3e20e11fc:	89 8d 78 ff ff ff    	mov    %ecx,-0x88(%rbp)
    7fd3e20e1202:	41 8b 8f ac 02 00 00 	mov    0x2ac(%r15),%ecx
    7fd3e20e1209:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7fd3e20e120f:	41 8b 8f bc 02 00 00 	mov    0x2bc(%r15),%ecx
    7fd3e20e1216:	89 8d 68 ff ff ff    	mov    %ecx,-0x98(%rbp)
    7fd3e20e121c:	41 8b 8f c4 02 00 00 	mov    0x2c4(%r15),%ecx
    7fd3e20e1223:	89 8d 60 ff ff ff    	mov    %ecx,-0xa0(%rbp)
    7fd3e20e1229:	41 8b 8f f0 02 00 00 	mov    0x2f0(%r15),%ecx
    7fd3e20e1230:	89 8d 58 ff ff ff    	mov    %ecx,-0xa8(%rbp)
    7fd3e20e1236:	41 8b 8f f8 02 00 00 	mov    0x2f8(%r15),%ecx
    7fd3e20e123d:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7fd3e20e1243:	41 8b 8f 08 03 00 00 	mov    0x308(%r15),%ecx
    7fd3e20e124a:	89 8d 48 ff ff ff    	mov    %ecx,-0xb8(%rbp)
    7fd3e20e1250:	41 8b 8f 10 03 00 00 	mov    0x310(%r15),%ecx
    7fd3e20e1257:	89 8d 40 ff ff ff    	mov    %ecx,-0xc0(%rbp)
    7fd3e20e125d:	41 8b 8f 18 03 00 00 	mov    0x318(%r15),%ecx
    7fd3e20e1264:	89 8d 38 ff ff ff    	mov    %ecx,-0xc8(%rbp)
    7fd3e20e126a:	41 8b 8f 20 03 00 00 	mov    0x320(%r15),%ecx
    7fd3e20e1271:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7fd3e20e1277:	41 8b 8f 28 03 00 00 	mov    0x328(%r15),%ecx
    7fd3e20e127e:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7fd3e20e1284:	41 8b 8f 30 03 00 00 	mov    0x330(%r15),%ecx
    7fd3e20e128b:	89 8d 20 ff ff ff    	mov    %ecx,-0xe0(%rbp)
    7fd3e20e1291:	41 8b 8f 4c 03 00 00 	mov    0x34c(%r15),%ecx
    7fd3e20e1298:	89 8d 18 ff ff ff    	mov    %ecx,-0xe8(%rbp)
    7fd3e20e129e:	41 8b 8f 54 03 00 00 	mov    0x354(%r15),%ecx
    7fd3e20e12a5:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7fd3e20e12ab:	41 8b 8f 64 03 00 00 	mov    0x364(%r15),%ecx
    7fd3e20e12b2:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7fd3e20e12b8:	41 8b 8f 6c 03 00 00 	mov    0x36c(%r15),%ecx
    7fd3e20e12bf:	89 8d 00 ff ff ff    	mov    %ecx,-0x100(%rbp)
    7fd3e20e12c5:	41 8b 8f 74 03 00 00 	mov    0x374(%r15),%ecx
    7fd3e20e12cc:	89 8d f8 fe ff ff    	mov    %ecx,-0x108(%rbp)
    7fd3e20e12d2:	41 8b 8f 7c 03 00 00 	mov    0x37c(%r15),%ecx
    7fd3e20e12d9:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7fd3e20e12df:	41 8b 8f 98 03 00 00 	mov    0x398(%r15),%ecx
    7fd3e20e12e6:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fd3e20e12ec:	41 8b 8f a8 03 00 00 	mov    0x3a8(%r15),%ecx
    7fd3e20e12f3:	89 8d e0 fe ff ff    	mov    %ecx,-0x120(%rbp)
    7fd3e20e12f9:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7fd3e20e1300:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7fd3e20e1306:	41 8b 8f c0 03 00 00 	mov    0x3c0(%r15),%ecx
    7fd3e20e130d:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7fd3e20e1313:	41 8b 8f c8 03 00 00 	mov    0x3c8(%r15),%ecx
    7fd3e20e131a:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fd3e20e1320:	41 8b 8f d8 03 00 00 	mov    0x3d8(%r15),%ecx
    7fd3e20e1327:	89 8d c0 fe ff ff    	mov    %ecx,-0x140(%rbp)
    7fd3e20e132d:	41 8b 8f e0 03 00 00 	mov    0x3e0(%r15),%ecx
    7fd3e20e1334:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7fd3e20e133a:	41 8b 8f e8 03 00 00 	mov    0x3e8(%r15),%ecx
    7fd3e20e1341:	89 8d b0 fe ff ff    	mov    %ecx,-0x150(%rbp)
    7fd3e20e1347:	41 8b 8f f0 03 00 00 	mov    0x3f0(%r15),%ecx
    7fd3e20e134e:	89 8d a8 fe ff ff    	mov    %ecx,-0x158(%rbp)
    7fd3e20e1354:	41 8b 8f f8 03 00 00 	mov    0x3f8(%r15),%ecx
    7fd3e20e135b:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7fd3e20e1361:	41 8b 8f 00 04 00 00 	mov    0x400(%r15),%ecx
    7fd3e20e1368:	89 8d 98 fe ff ff    	mov    %ecx,-0x168(%rbp)
    7fd3e20e136e:	41 8b 8f 08 04 00 00 	mov    0x408(%r15),%ecx
    7fd3e20e1375:	89 8d 90 fe ff ff    	mov    %ecx,-0x170(%rbp)
    7fd3e20e137b:	41 8b 8f 10 04 00 00 	mov    0x410(%r15),%ecx
    7fd3e20e1382:	89 8d 88 fe ff ff    	mov    %ecx,-0x178(%rbp)
    7fd3e20e1388:	41 8b 8f 20 04 00 00 	mov    0x420(%r15),%ecx
    7fd3e20e138f:	89 8d 80 fe ff ff    	mov    %ecx,-0x180(%rbp)
    7fd3e20e1395:	41 8b 9f 28 04 00 00 	mov    0x428(%r15),%ebx
    7fd3e20e139c:	41 8b 8f 30 04 00 00 	mov    0x430(%r15),%ecx
    7fd3e20e13a3:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7fd3e20e13a9:	41 8b 8f 38 04 00 00 	mov    0x438(%r15),%ecx
    7fd3e20e13b0:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7fd3e20e13b6:	41 8b 8f 40 04 00 00 	mov    0x440(%r15),%ecx
    7fd3e20e13bd:	89 8d 68 fe ff ff    	mov    %ecx,-0x198(%rbp)
    7fd3e20e13c3:	41 8b 8f 48 04 00 00 	mov    0x448(%r15),%ecx
    7fd3e20e13ca:	89 8d 60 fe ff ff    	mov    %ecx,-0x1a0(%rbp)
    7fd3e20e13d0:	41 8b 8f 50 04 00 00 	mov    0x450(%r15),%ecx
    7fd3e20e13d7:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7fd3e20e13dd:	48 89 85 50 fe ff ff 	mov    %rax,-0x1b0(%rbp)
    7fd3e20e13e4:	48 8b 40 18          	mov    0x18(%rax),%rax
    7fd3e20e13e8:	8b 00                	mov    (%rax),%eax
    7fd3e20e13ea:	41 8b 8f 58 04 00 00 	mov    0x458(%r15),%ecx
    7fd3e20e13f1:	33 c8                	xor    %eax,%ecx
    7fd3e20e13f3:	23 c8                	and    %eax,%ecx
    7fd3e20e13f5:	41 89 87 58 04 00 00 	mov    %eax,0x458(%r15)
    7fd3e20e13fc:	85 c9                	test   %ecx,%ecx
    7fd3e20e13fe:	0f 84 44 17 00 00    	je     0x7fd3e20e2b48
    7fd3e20e1404:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fd3e20e1407:	ff c0                	inc    %eax
    7fd3e20e1409:	83 e0 3f             	and    $0x3f,%eax
    7fd3e20e140c:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7fd3e20e1412:	48 8b 85 50 fe ff ff 	mov    -0x1b0(%rbp),%rax
    7fd3e20e1419:	48 8b 40 20          	mov    0x20(%rax),%rax
    7fd3e20e141d:	44 8b 28             	mov    (%rax),%r13d
    7fd3e20e1420:	45 8b e5             	mov    %r13d,%r12d
    7fd3e20e1423:	41 83 cc 00          	or     $0x0,%r12d
    7fd3e20e1427:	33 c0                	xor    %eax,%eax
    7fd3e20e1429:	3b 85 80 fe ff ff    	cmp    -0x180(%rbp),%eax
    7fd3e20e142f:	0f 94 c0             	sete   %al
    7fd3e20e1432:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e1435:	85 c0                	test   %eax,%eax
    7fd3e20e1437:	0f 94 c0             	sete   %al
    7fd3e20e143a:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e143d:	8b cb                	mov    %ebx,%ecx
    7fd3e20e143f:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e1442:	85 c9                	test   %ecx,%ecx
    7fd3e20e1444:	0f 94 c1             	sete   %cl
    7fd3e20e1447:	0f b6 c9             	movzbl %cl,%ecx
    7fd3e20e144a:	85 c9                	test   %ecx,%ecx
    7fd3e20e144c:	0f 94 c2             	sete   %dl
    7fd3e20e144f:	0f b6 d2             	movzbl %dl,%edx
    7fd3e20e1452:	23 c2                	and    %edx,%eax
    7fd3e20e1454:	85 c0                	test   %eax,%eax
    7fd3e20e1456:	0f 94 c0             	sete   %al
    7fd3e20e1459:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e145c:	8b 95 88 fe ff ff    	mov    -0x178(%rbp),%edx
    7fd3e20e1462:	23 d0                	and    %eax,%edx
    7fd3e20e1464:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7fd3e20e146a:	c1 ee 02             	shr    $0x2,%esi
    7fd3e20e146d:	83 e6 01             	and    $0x1,%esi
    7fd3e20e1470:	85 f6                	test   %esi,%esi
    7fd3e20e1472:	40 0f 94 c6          	sete   %sil
    7fd3e20e1476:	40 0f b6 f6          	movzbl %sil,%esi
    7fd3e20e147a:	89 b5 40 fe ff ff    	mov    %esi,-0x1c0(%rbp)
    7fd3e20e1480:	85 f6                	test   %esi,%esi
    7fd3e20e1482:	40 0f 94 c6          	sete   %sil
    7fd3e20e1486:	40 0f b6 f6          	movzbl %sil,%esi
    7fd3e20e148a:	89 95 38 fe ff ff    	mov    %edx,-0x1c8(%rbp)
    7fd3e20e1490:	23 d6                	and    %esi,%edx
    7fd3e20e1492:	85 d2                	test   %edx,%edx
    7fd3e20e1494:	0f 94 c2             	sete   %dl
    7fd3e20e1497:	0f b6 d2             	movzbl %dl,%edx
    7fd3e20e149a:	89 8d 30 fe ff ff    	mov    %ecx,-0x1d0(%rbp)
    7fd3e20e14a0:	23 ca                	and    %edx,%ecx
    7fd3e20e14a2:	89 95 28 fe ff ff    	mov    %edx,-0x1d8(%rbp)
    7fd3e20e14a8:	23 c2                	and    %edx,%eax
    7fd3e20e14aa:	89 8d 20 fe ff ff    	mov    %ecx,-0x1e0(%rbp)
    7fd3e20e14b0:	4c 8b f0             	mov    %rax,%r14
    7fd3e20e14b3:	23 c8                	and    %eax,%ecx
    7fd3e20e14b5:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7fd3e20e14bb:	8b 45 f0             	mov    -0x10(%rbp),%eax
    7fd3e20e14be:	c1 e8 05             	shr    $0x5,%eax
    7fd3e20e14c1:	83 e0 01             	and    $0x1,%eax
    7fd3e20e14c4:	8b 4d e8             	mov    -0x18(%rbp),%ecx
    7fd3e20e14c7:	c1 e9 10             	shr    $0x10,%ecx
    7fd3e20e14ca:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e14d0:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7fd3e20e14d6:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e14d9:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e14df:	89 8d 10 fe ff ff    	mov    %ecx,-0x1f0(%rbp)
    7fd3e20e14e5:	89 95 08 fe ff ff    	mov    %edx,-0x1f8(%rbp)
    7fd3e20e14eb:	2b ca                	sub    %edx,%ecx
    7fd3e20e14ed:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e14f3:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fd3e20e14f6:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e14fc:	8b b5 78 fe ff ff    	mov    -0x188(%rbp),%esi
    7fd3e20e1502:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e1508:	89 95 00 fe ff ff    	mov    %edx,-0x200(%rbp)
    7fd3e20e150e:	89 b5 f8 fd ff ff    	mov    %esi,-0x208(%rbp)
    7fd3e20e1514:	2b d6                	sub    %esi,%edx
    7fd3e20e1516:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e151c:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e151f:	0b d1                	or     %ecx,%edx
    7fd3e20e1521:	89 95 f0 fd ff ff    	mov    %edx,-0x210(%rbp)
    7fd3e20e1527:	89 85 e8 fd ff ff    	mov    %eax,-0x218(%rbp)
    7fd3e20e152d:	85 c0                	test   %eax,%eax
    7fd3e20e152f:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1541
    7fd3e20e1535:	8b 85 78 fe ff ff    	mov    -0x188(%rbp),%eax
    7fd3e20e153b:	89 85 f0 fd ff ff    	mov    %eax,-0x210(%rbp)
    7fd3e20e1541:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fd3e20e1547:	03 85 08 fe ff ff    	add    -0x1f8(%rbp),%eax
    7fd3e20e154d:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1552:	8b 8d 00 fe ff ff    	mov    -0x200(%rbp),%ecx
    7fd3e20e1558:	03 8d f8 fd ff ff    	add    -0x208(%rbp),%ecx
    7fd3e20e155e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1564:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e1567:	0b c8                	or     %eax,%ecx
    7fd3e20e1569:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fd3e20e156f:	8b 85 e8 fd ff ff    	mov    -0x218(%rbp),%eax
    7fd3e20e1575:	85 c0                	test   %eax,%eax
    7fd3e20e1577:	0f 85 09 00 00 00    	jne    0x7fd3e20e1586
    7fd3e20e157d:	8b 45 e8             	mov    -0x18(%rbp),%eax
    7fd3e20e1580:	89 85 e0 fd ff ff    	mov    %eax,-0x220(%rbp)
    7fd3e20e1586:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fd3e20e1589:	ff c0                	inc    %eax
    7fd3e20e158b:	83 e0 3f             	and    $0x3f,%eax
    7fd3e20e158e:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
    7fd3e20e1594:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fd3e20e1597:	41 23 c6             	and    %r14d,%eax
    7fd3e20e159a:	89 85 d0 fd ff ff    	mov    %eax,-0x230(%rbp)
    7fd3e20e15a0:	8b 45 d0             	mov    -0x30(%rbp),%eax
    7fd3e20e15a3:	c1 e8 05             	shr    $0x5,%eax
    7fd3e20e15a6:	83 e0 01             	and    $0x1,%eax
    7fd3e20e15a9:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7fd3e20e15ac:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e15b2:	f7 d9                	neg    %ecx
    7fd3e20e15b4:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e15ba:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fd3e20e15bd:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e15c0:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e15c6:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e15c9:	0b d1                	or     %ecx,%edx
    7fd3e20e15cb:	89 95 c8 fd ff ff    	mov    %edx,-0x238(%rbp)
    7fd3e20e15d1:	85 c0                	test   %eax,%eax
    7fd3e20e15d3:	0f 85 09 00 00 00    	jne    0x7fd3e20e15e2
    7fd3e20e15d9:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fd3e20e15dc:	89 85 c8 fd ff ff    	mov    %eax,-0x238(%rbp)
    7fd3e20e15e2:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fd3e20e15e5:	ff c0                	inc    %eax
    7fd3e20e15e7:	83 e0 1f             	and    $0x1f,%eax
    7fd3e20e15ea:	89 85 c0 fd ff ff    	mov    %eax,-0x240(%rbp)
    7fd3e20e15f0:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7fd3e20e15f3:	41 23 c6             	and    %r14d,%eax
    7fd3e20e15f6:	89 85 b8 fd ff ff    	mov    %eax,-0x248(%rbp)
    7fd3e20e15fc:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7fd3e20e15ff:	c1 e8 04             	shr    $0x4,%eax
    7fd3e20e1602:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1605:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fd3e20e1608:	c1 e9 10             	shr    $0x10,%ecx
    7fd3e20e160b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1611:	8b 55 c8             	mov    -0x38(%rbp),%edx
    7fd3e20e1614:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e1617:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e161d:	89 8d b0 fd ff ff    	mov    %ecx,-0x250(%rbp)
    7fd3e20e1623:	89 95 a8 fd ff ff    	mov    %edx,-0x258(%rbp)
    7fd3e20e1629:	2b ca                	sub    %edx,%ecx
    7fd3e20e162b:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1631:	8b 55 a8             	mov    -0x58(%rbp),%edx
    7fd3e20e1634:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e163a:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7fd3e20e163d:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e1643:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7fd3e20e1649:	89 b5 98 fd ff ff    	mov    %esi,-0x268(%rbp)
    7fd3e20e164f:	2b d6                	sub    %esi,%edx
    7fd3e20e1651:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1657:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e165a:	0b d1                	or     %ecx,%edx
    7fd3e20e165c:	89 95 90 fd ff ff    	mov    %edx,-0x270(%rbp)
    7fd3e20e1662:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
    7fd3e20e1668:	85 c0                	test   %eax,%eax
    7fd3e20e166a:	0f 85 09 00 00 00    	jne    0x7fd3e20e1679
    7fd3e20e1670:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fd3e20e1673:	89 85 90 fd ff ff    	mov    %eax,-0x270(%rbp)
    7fd3e20e1679:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
    7fd3e20e167f:	03 85 a8 fd ff ff    	add    -0x258(%rbp),%eax
    7fd3e20e1685:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e168a:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fd3e20e1690:	03 8d 98 fd ff ff    	add    -0x268(%rbp),%ecx
    7fd3e20e1696:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e169c:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e169f:	0b c8                	or     %eax,%ecx
    7fd3e20e16a1:	89 8d 80 fd ff ff    	mov    %ecx,-0x280(%rbp)
    7fd3e20e16a7:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
    7fd3e20e16ad:	85 c0                	test   %eax,%eax
    7fd3e20e16af:	0f 85 09 00 00 00    	jne    0x7fd3e20e16be
    7fd3e20e16b5:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7fd3e20e16b8:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
    7fd3e20e16be:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fd3e20e16c1:	ff c0                	inc    %eax
    7fd3e20e16c3:	83 e0 3f             	and    $0x3f,%eax
    7fd3e20e16c6:	89 85 78 fd ff ff    	mov    %eax,-0x288(%rbp)
    7fd3e20e16cc:	8b 45 98             	mov    -0x68(%rbp),%eax
    7fd3e20e16cf:	41 23 c6             	and    %r14d,%eax
    7fd3e20e16d2:	89 85 70 fd ff ff    	mov    %eax,-0x290(%rbp)
    7fd3e20e16d8:	8b 45 90             	mov    -0x70(%rbp),%eax
    7fd3e20e16db:	8b c0                	mov    %eax,%eax
    7fd3e20e16dd:	41 8b 04 87          	mov    (%r15,%rax,4),%eax
    7fd3e20e16e1:	89 85 68 fd ff ff    	mov    %eax,-0x298(%rbp)
    7fd3e20e16e7:	8b 45 88             	mov    -0x78(%rbp),%eax
    7fd3e20e16ea:	c1 e8 10             	shr    $0x10,%eax
    7fd3e20e16ed:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e16f2:	8b 4d 80             	mov    -0x80(%rbp),%ecx
    7fd3e20e16f5:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e16fb:	0f b7 d0             	movzwl %ax,%edx
    7fd3e20e16fe:	0f bf d2             	movswl %dx,%edx
    7fd3e20e1701:	0f b7 f1             	movzwl %cx,%esi
    7fd3e20e1704:	0f bf f6             	movswl %si,%esi
    7fd3e20e1707:	0f af d6             	imul   %esi,%edx
    7fd3e20e170a:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fd3e20e1710:	8b 75 88             	mov    -0x78(%rbp),%esi
    7fd3e20e1713:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e1719:	8b 7d 80             	mov    -0x80(%rbp),%edi
    7fd3e20e171c:	c1 ef 10             	shr    $0x10,%edi
    7fd3e20e171f:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7fd3e20e1725:	44 0f b7 c6          	movzwl %si,%r8d
    7fd3e20e1729:	45 0f bf c0          	movswl %r8w,%r8d
    7fd3e20e172d:	44 0f b7 cf          	movzwl %di,%r9d
    7fd3e20e1731:	45 0f bf c9          	movswl %r9w,%r9d
    7fd3e20e1735:	45 0f af c1          	imul   %r9d,%r8d
    7fd3e20e1739:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7fd3e20e1740:	41 03 d0             	add    %r8d,%edx
    7fd3e20e1743:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fd3e20e1749:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7fd3e20e174f:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7fd3e20e1755:	89 95 60 fd ff ff    	mov    %edx,-0x2a0(%rbp)
    7fd3e20e175b:	c1 fa 0f             	sar    $0xf,%edx
    7fd3e20e175e:	89 95 58 fd ff ff    	mov    %edx,-0x2a8(%rbp)
    7fd3e20e1764:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e176a:	89 b5 50 fd ff ff    	mov    %esi,-0x2b0(%rbp)
    7fd3e20e1770:	0f b7 f6             	movzwl %si,%esi
    7fd3e20e1773:	0f bf f6             	movswl %si,%esi
    7fd3e20e1776:	89 8d 48 fd ff ff    	mov    %ecx,-0x2b8(%rbp)
    7fd3e20e177c:	0f b7 c9             	movzwl %cx,%ecx
    7fd3e20e177f:	0f bf c9             	movswl %cx,%ecx
    7fd3e20e1782:	0f af f1             	imul   %ecx,%esi
    7fd3e20e1785:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fd3e20e178b:	89 85 40 fd ff ff    	mov    %eax,-0x2c0(%rbp)
    7fd3e20e1791:	0f b7 c0             	movzwl %ax,%eax
    7fd3e20e1794:	0f bf c0             	movswl %ax,%eax
    7fd3e20e1797:	89 bd 38 fd ff ff    	mov    %edi,-0x2c8(%rbp)
    7fd3e20e179d:	0f b7 ff             	movzwl %di,%edi
    7fd3e20e17a0:	0f bf cf             	movswl %di,%ecx
    7fd3e20e17a3:	0f af c1             	imul   %ecx,%eax
    7fd3e20e17a6:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7fd3e20e17ab:	2b f0                	sub    %eax,%esi
    7fd3e20e17ad:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fd3e20e17b3:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7fd3e20e17b9:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7fd3e20e17bf:	89 b5 30 fd ff ff    	mov    %esi,-0x2d0(%rbp)
    7fd3e20e17c5:	c1 fe 0f             	sar    $0xf,%esi
    7fd3e20e17c8:	89 b5 28 fd ff ff    	mov    %esi,-0x2d8(%rbp)
    7fd3e20e17ce:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e17d4:	89 95 20 fd ff ff    	mov    %edx,-0x2e0(%rbp)
    7fd3e20e17da:	c1 e2 10             	shl    $0x10,%edx
    7fd3e20e17dd:	0b f2                	or     %edx,%esi
    7fd3e20e17df:	89 b5 18 fd ff ff    	mov    %esi,-0x2e8(%rbp)
    7fd3e20e17e5:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fd3e20e17eb:	ff c0                	inc    %eax
    7fd3e20e17ed:	83 e0 0f             	and    $0xf,%eax
    7fd3e20e17f0:	89 85 10 fd ff ff    	mov    %eax,-0x2f0(%rbp)
    7fd3e20e17f6:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fd3e20e17fc:	41 23 c6             	and    %r14d,%eax
    7fd3e20e17ff:	89 85 08 fd ff ff    	mov    %eax,-0x2f8(%rbp)
    7fd3e20e1805:	8b 85 68 ff ff ff    	mov    -0x98(%rbp),%eax
    7fd3e20e180b:	c1 e8 03             	shr    $0x3,%eax
    7fd3e20e180e:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1811:	8b 8d 60 ff ff ff    	mov    -0xa0(%rbp),%ecx
    7fd3e20e1817:	c1 e9 10             	shr    $0x10,%ecx
    7fd3e20e181a:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1820:	8b 95 78 ff ff ff    	mov    -0x88(%rbp),%edx
    7fd3e20e1826:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e1829:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e182f:	89 8d 00 fd ff ff    	mov    %ecx,-0x300(%rbp)
    7fd3e20e1835:	89 95 f8 fc ff ff    	mov    %edx,-0x308(%rbp)
    7fd3e20e183b:	2b ca                	sub    %edx,%ecx
    7fd3e20e183d:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1843:	8b 95 60 ff ff ff    	mov    -0xa0(%rbp),%edx
    7fd3e20e1849:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e184f:	8b b5 78 ff ff ff    	mov    -0x88(%rbp),%esi
    7fd3e20e1855:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e185b:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7fd3e20e1861:	89 b5 e8 fc ff ff    	mov    %esi,-0x318(%rbp)
    7fd3e20e1867:	2b d6                	sub    %esi,%edx
    7fd3e20e1869:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e186f:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e1872:	0b d1                	or     %ecx,%edx
    7fd3e20e1874:	89 95 e0 fc ff ff    	mov    %edx,-0x320(%rbp)
    7fd3e20e187a:	89 85 d8 fc ff ff    	mov    %eax,-0x328(%rbp)
    7fd3e20e1880:	85 c0                	test   %eax,%eax
    7fd3e20e1882:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1894
    7fd3e20e1888:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7fd3e20e188e:	89 85 e0 fc ff ff    	mov    %eax,-0x320(%rbp)
    7fd3e20e1894:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fd3e20e189a:	03 85 f8 fc ff ff    	add    -0x308(%rbp),%eax
    7fd3e20e18a0:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e18a5:	8b 8d f0 fc ff ff    	mov    -0x310(%rbp),%ecx
    7fd3e20e18ab:	03 8d e8 fc ff ff    	add    -0x318(%rbp),%ecx
    7fd3e20e18b1:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e18b7:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e18ba:	0b c8                	or     %eax,%ecx
    7fd3e20e18bc:	89 8d d0 fc ff ff    	mov    %ecx,-0x330(%rbp)
    7fd3e20e18c2:	8b 85 d8 fc ff ff    	mov    -0x328(%rbp),%eax
    7fd3e20e18c8:	85 c0                	test   %eax,%eax
    7fd3e20e18ca:	0f 85 0c 00 00 00    	jne    0x7fd3e20e18dc
    7fd3e20e18d0:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fd3e20e18d6:	89 85 d0 fc ff ff    	mov    %eax,-0x330(%rbp)
    7fd3e20e18dc:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fd3e20e18e2:	ff c0                	inc    %eax
    7fd3e20e18e4:	83 e0 0f             	and    $0xf,%eax
    7fd3e20e18e7:	89 85 c8 fc ff ff    	mov    %eax,-0x338(%rbp)
    7fd3e20e18ed:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fd3e20e18f3:	41 23 c6             	and    %r14d,%eax
    7fd3e20e18f6:	89 85 c0 fc ff ff    	mov    %eax,-0x340(%rbp)
    7fd3e20e18fc:	8b 85 48 ff ff ff    	mov    -0xb8(%rbp),%eax
    7fd3e20e1902:	c1 e8 03             	shr    $0x3,%eax
    7fd3e20e1905:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1908:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7fd3e20e190e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1914:	f7 d9                	neg    %ecx
    7fd3e20e1916:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e191c:	8b 95 58 ff ff ff    	mov    -0xa8(%rbp),%edx
    7fd3e20e1922:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e1925:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e192b:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e192e:	0b d1                	or     %ecx,%edx
    7fd3e20e1930:	89 95 b8 fc ff ff    	mov    %edx,-0x348(%rbp)
    7fd3e20e1936:	85 c0                	test   %eax,%eax
    7fd3e20e1938:	0f 85 0c 00 00 00    	jne    0x7fd3e20e194a
    7fd3e20e193e:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fd3e20e1944:	89 85 b8 fc ff ff    	mov    %eax,-0x348(%rbp)
    7fd3e20e194a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fd3e20e1950:	ff c0                	inc    %eax
    7fd3e20e1952:	83 e0 07             	and    $0x7,%eax
    7fd3e20e1955:	89 85 b0 fc ff ff    	mov    %eax,-0x350(%rbp)
    7fd3e20e195b:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7fd3e20e1961:	41 23 c6             	and    %r14d,%eax
    7fd3e20e1964:	89 85 a8 fc ff ff    	mov    %eax,-0x358(%rbp)
    7fd3e20e196a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7fd3e20e1970:	c1 e8 02             	shr    $0x2,%eax
    7fd3e20e1973:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1976:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7fd3e20e197c:	c1 e9 10             	shr    $0x10,%ecx
    7fd3e20e197f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1985:	8b 95 40 ff ff ff    	mov    -0xc0(%rbp),%edx
    7fd3e20e198b:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e198e:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1994:	89 8d a0 fc ff ff    	mov    %ecx,-0x360(%rbp)
    7fd3e20e199a:	89 95 98 fc ff ff    	mov    %edx,-0x368(%rbp)
    7fd3e20e19a0:	2b ca                	sub    %edx,%ecx
    7fd3e20e19a2:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e19a8:	8b 95 20 ff ff ff    	mov    -0xe0(%rbp),%edx
    7fd3e20e19ae:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e19b4:	8b b5 40 ff ff ff    	mov    -0xc0(%rbp),%esi
    7fd3e20e19ba:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e19c0:	89 95 90 fc ff ff    	mov    %edx,-0x370(%rbp)
    7fd3e20e19c6:	89 b5 88 fc ff ff    	mov    %esi,-0x378(%rbp)
    7fd3e20e19cc:	2b d6                	sub    %esi,%edx
    7fd3e20e19ce:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e19d4:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e19d7:	0b d1                	or     %ecx,%edx
    7fd3e20e19d9:	89 95 80 fc ff ff    	mov    %edx,-0x380(%rbp)
    7fd3e20e19df:	89 85 78 fc ff ff    	mov    %eax,-0x388(%rbp)
    7fd3e20e19e5:	85 c0                	test   %eax,%eax
    7fd3e20e19e7:	0f 85 0c 00 00 00    	jne    0x7fd3e20e19f9
    7fd3e20e19ed:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7fd3e20e19f3:	89 85 80 fc ff ff    	mov    %eax,-0x380(%rbp)
    7fd3e20e19f9:	8b 85 a0 fc ff ff    	mov    -0x360(%rbp),%eax
    7fd3e20e19ff:	03 85 98 fc ff ff    	add    -0x368(%rbp),%eax
    7fd3e20e1a05:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1a0a:	8b 8d 90 fc ff ff    	mov    -0x370(%rbp),%ecx
    7fd3e20e1a10:	03 8d 88 fc ff ff    	add    -0x378(%rbp),%ecx
    7fd3e20e1a16:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1a1c:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e1a1f:	0b c8                	or     %eax,%ecx
    7fd3e20e1a21:	89 8d 70 fc ff ff    	mov    %ecx,-0x390(%rbp)
    7fd3e20e1a27:	8b 85 78 fc ff ff    	mov    -0x388(%rbp),%eax
    7fd3e20e1a2d:	85 c0                	test   %eax,%eax
    7fd3e20e1a2f:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1a41
    7fd3e20e1a35:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7fd3e20e1a3b:	89 85 70 fc ff ff    	mov    %eax,-0x390(%rbp)
    7fd3e20e1a41:	8b 85 08 ff ff ff    	mov    -0xf8(%rbp),%eax
    7fd3e20e1a47:	ff c0                	inc    %eax
    7fd3e20e1a49:	83 e0 0f             	and    $0xf,%eax
    7fd3e20e1a4c:	89 85 68 fc ff ff    	mov    %eax,-0x398(%rbp)
    7fd3e20e1a52:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fd3e20e1a58:	41 23 c6             	and    %r14d,%eax
    7fd3e20e1a5b:	89 85 60 fc ff ff    	mov    %eax,-0x3a0(%rbp)
    7fd3e20e1a61:	49 8b c7             	mov    %r15,%rax
    7fd3e20e1a64:	48 05 00 01 00 00    	add    $0x100,%rax
    7fd3e20e1a6a:	8b 8d 08 ff ff ff    	mov    -0xf8(%rbp),%ecx
    7fd3e20e1a70:	8b c9                	mov    %ecx,%ecx
    7fd3e20e1a72:	8b 04 88             	mov    (%rax,%rcx,4),%eax
    7fd3e20e1a75:	89 85 58 fc ff ff    	mov    %eax,-0x3a8(%rbp)
    7fd3e20e1a7b:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fd3e20e1a81:	c1 e8 10             	shr    $0x10,%eax
    7fd3e20e1a84:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1a89:	8b 8d f8 fe ff ff    	mov    -0x108(%rbp),%ecx
    7fd3e20e1a8f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1a95:	0f b7 d0             	movzwl %ax,%edx
    7fd3e20e1a98:	0f bf d2             	movswl %dx,%edx
    7fd3e20e1a9b:	0f b7 f1             	movzwl %cx,%esi
    7fd3e20e1a9e:	0f bf f6             	movswl %si,%esi
    7fd3e20e1aa1:	0f af d6             	imul   %esi,%edx
    7fd3e20e1aa4:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fd3e20e1aaa:	8b b5 00 ff ff ff    	mov    -0x100(%rbp),%esi
    7fd3e20e1ab0:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e1ab6:	8b bd f8 fe ff ff    	mov    -0x108(%rbp),%edi
    7fd3e20e1abc:	c1 ef 10             	shr    $0x10,%edi
    7fd3e20e1abf:	81 e7 ff ff 00 00    	and    $0xffff,%edi
    7fd3e20e1ac5:	44 0f b7 c6          	movzwl %si,%r8d
    7fd3e20e1ac9:	45 0f bf c0          	movswl %r8w,%r8d
    7fd3e20e1acd:	44 0f b7 cf          	movzwl %di,%r9d
    7fd3e20e1ad1:	45 0f bf c9          	movswl %r9w,%r9d
    7fd3e20e1ad5:	45 0f af c1          	imul   %r9d,%r8d
    7fd3e20e1ad9:	41 81 e0 ff ff ff 7f 	and    $0x7fffffff,%r8d
    7fd3e20e1ae0:	41 03 d0             	add    %r8d,%edx
    7fd3e20e1ae3:	81 e2 ff ff ff 7f    	and    $0x7fffffff,%edx
    7fd3e20e1ae9:	81 f2 00 00 00 40    	xor    $0x40000000,%edx
    7fd3e20e1aef:	81 ea 00 00 00 40    	sub    $0x40000000,%edx
    7fd3e20e1af5:	89 95 50 fc ff ff    	mov    %edx,-0x3b0(%rbp)
    7fd3e20e1afb:	c1 fa 0f             	sar    $0xf,%edx
    7fd3e20e1afe:	89 95 48 fc ff ff    	mov    %edx,-0x3b8(%rbp)
    7fd3e20e1b04:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1b0a:	89 b5 40 fc ff ff    	mov    %esi,-0x3c0(%rbp)
    7fd3e20e1b10:	0f b7 f6             	movzwl %si,%esi
    7fd3e20e1b13:	0f bf f6             	movswl %si,%esi
    7fd3e20e1b16:	89 8d 38 fc ff ff    	mov    %ecx,-0x3c8(%rbp)
    7fd3e20e1b1c:	0f b7 c9             	movzwl %cx,%ecx
    7fd3e20e1b1f:	0f bf c9             	movswl %cx,%ecx
    7fd3e20e1b22:	0f af f1             	imul   %ecx,%esi
    7fd3e20e1b25:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fd3e20e1b2b:	89 85 30 fc ff ff    	mov    %eax,-0x3d0(%rbp)
    7fd3e20e1b31:	0f b7 c0             	movzwl %ax,%eax
    7fd3e20e1b34:	0f bf c0             	movswl %ax,%eax
    7fd3e20e1b37:	89 bd 28 fc ff ff    	mov    %edi,-0x3d8(%rbp)
    7fd3e20e1b3d:	0f b7 ff             	movzwl %di,%edi
    7fd3e20e1b40:	0f bf cf             	movswl %di,%ecx
    7fd3e20e1b43:	0f af c1             	imul   %ecx,%eax
    7fd3e20e1b46:	25 ff ff ff 7f       	and    $0x7fffffff,%eax
    7fd3e20e1b4b:	2b f0                	sub    %eax,%esi
    7fd3e20e1b4d:	81 e6 ff ff ff 7f    	and    $0x7fffffff,%esi
    7fd3e20e1b53:	81 f6 00 00 00 40    	xor    $0x40000000,%esi
    7fd3e20e1b59:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
    7fd3e20e1b5f:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7fd3e20e1b65:	c1 fe 0f             	sar    $0xf,%esi
    7fd3e20e1b68:	89 b5 18 fc ff ff    	mov    %esi,-0x3e8(%rbp)
    7fd3e20e1b6e:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e1b74:	89 95 10 fc ff ff    	mov    %edx,-0x3f0(%rbp)
    7fd3e20e1b7a:	c1 e2 10             	shl    $0x10,%edx
    7fd3e20e1b7d:	0b f2                	or     %edx,%esi
    7fd3e20e1b7f:	89 b5 08 fc ff ff    	mov    %esi,-0x3f8(%rbp)
    7fd3e20e1b85:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fd3e20e1b8b:	ff c0                	inc    %eax
    7fd3e20e1b8d:	83 e0 03             	and    $0x3,%eax
    7fd3e20e1b90:	89 85 00 fc ff ff    	mov    %eax,-0x400(%rbp)
    7fd3e20e1b96:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7fd3e20e1b9c:	41 23 c6             	and    %r14d,%eax
    7fd3e20e1b9f:	89 85 f8 fb ff ff    	mov    %eax,-0x408(%rbp)
    7fd3e20e1ba5:	8b 85 e0 fe ff ff    	mov    -0x120(%rbp),%eax
    7fd3e20e1bab:	d1 e8                	shr    %eax
    7fd3e20e1bad:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1bb0:	8b 8d d8 fe ff ff    	mov    -0x128(%rbp),%ecx
    7fd3e20e1bb6:	c1 e9 10             	shr    $0x10,%ecx
    7fd3e20e1bb9:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1bbf:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fd3e20e1bc5:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e1bc8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1bce:	89 8d f0 fb ff ff    	mov    %ecx,-0x410(%rbp)
    7fd3e20e1bd4:	89 95 e8 fb ff ff    	mov    %edx,-0x418(%rbp)
    7fd3e20e1bda:	2b ca                	sub    %edx,%ecx
    7fd3e20e1bdc:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1be2:	8b 95 d8 fe ff ff    	mov    -0x128(%rbp),%edx
    7fd3e20e1be8:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1bee:	8b b5 f0 fe ff ff    	mov    -0x110(%rbp),%esi
    7fd3e20e1bf4:	81 e6 ff ff 00 00    	and    $0xffff,%esi
    7fd3e20e1bfa:	89 95 e0 fb ff ff    	mov    %edx,-0x420(%rbp)
    7fd3e20e1c00:	89 b5 d8 fb ff ff    	mov    %esi,-0x428(%rbp)
    7fd3e20e1c06:	2b d6                	sub    %esi,%edx
    7fd3e20e1c08:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1c0e:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e1c11:	0b d1                	or     %ecx,%edx
    7fd3e20e1c13:	89 95 d0 fb ff ff    	mov    %edx,-0x430(%rbp)
    7fd3e20e1c19:	89 85 c8 fb ff ff    	mov    %eax,-0x438(%rbp)
    7fd3e20e1c1f:	85 c0                	test   %eax,%eax
    7fd3e20e1c21:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1c33
    7fd3e20e1c27:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7fd3e20e1c2d:	89 85 d0 fb ff ff    	mov    %eax,-0x430(%rbp)
    7fd3e20e1c33:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7fd3e20e1c39:	03 85 e8 fb ff ff    	add    -0x418(%rbp),%eax
    7fd3e20e1c3f:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1c44:	8b 8d e0 fb ff ff    	mov    -0x420(%rbp),%ecx
    7fd3e20e1c4a:	03 8d d8 fb ff ff    	add    -0x428(%rbp),%ecx
    7fd3e20e1c50:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1c56:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e1c59:	0b c8                	or     %eax,%ecx
    7fd3e20e1c5b:	89 8d c0 fb ff ff    	mov    %ecx,-0x440(%rbp)
    7fd3e20e1c61:	8b 85 c8 fb ff ff    	mov    -0x438(%rbp),%eax
    7fd3e20e1c67:	85 c0                	test   %eax,%eax
    7fd3e20e1c69:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1c7b
    7fd3e20e1c6f:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7fd3e20e1c75:	89 85 c0 fb ff ff    	mov    %eax,-0x440(%rbp)
    7fd3e20e1c7b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fd3e20e1c81:	ff c0                	inc    %eax
    7fd3e20e1c83:	83 e0 03             	and    $0x3,%eax
    7fd3e20e1c86:	89 85 b8 fb ff ff    	mov    %eax,-0x448(%rbp)
    7fd3e20e1c8c:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fd3e20e1c92:	41 23 c6             	and    %r14d,%eax
    7fd3e20e1c95:	89 85 b0 fb ff ff    	mov    %eax,-0x450(%rbp)
    7fd3e20e1c9b:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fd3e20e1ca1:	d1 e8                	shr    %eax
    7fd3e20e1ca3:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1ca6:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7fd3e20e1cac:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1cb2:	f7 d9                	neg    %ecx
    7fd3e20e1cb4:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1cba:	8b 95 d0 fe ff ff    	mov    -0x130(%rbp),%edx
    7fd3e20e1cc0:	c1 ea 10             	shr    $0x10,%edx
    7fd3e20e1cc3:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1cc9:	c1 e1 10             	shl    $0x10,%ecx
    7fd3e20e1ccc:	0b d1                	or     %ecx,%edx
    7fd3e20e1cce:	89 95 a8 fb ff ff    	mov    %edx,-0x458(%rbp)
    7fd3e20e1cd4:	85 c0                	test   %eax,%eax
    7fd3e20e1cd6:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1ce8
    7fd3e20e1cdc:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fd3e20e1ce2:	89 85 a8 fb ff ff    	mov    %eax,-0x458(%rbp)
    7fd3e20e1ce8:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fd3e20e1cee:	ff c0                	inc    %eax
    7fd3e20e1cf0:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1cf3:	89 85 a0 fb ff ff    	mov    %eax,-0x460(%rbp)
    7fd3e20e1cf9:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fd3e20e1cff:	41 23 c6             	and    %r14d,%eax
    7fd3e20e1d02:	89 85 98 fb ff ff    	mov    %eax,-0x468(%rbp)
    7fd3e20e1d08:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fd3e20e1d0e:	c1 e8 10             	shr    $0x10,%eax
    7fd3e20e1d11:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1d16:	8b 8d b8 fe ff ff    	mov    -0x148(%rbp),%ecx
    7fd3e20e1d1c:	c1 e9 10             	shr    $0x10,%ecx
    7fd3e20e1d1f:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1d25:	89 85 90 fb ff ff    	mov    %eax,-0x470(%rbp)
    7fd3e20e1d2b:	89 8d 88 fb ff ff    	mov    %ecx,-0x478(%rbp)
    7fd3e20e1d31:	2b c1                	sub    %ecx,%eax
    7fd3e20e1d33:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1d38:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7fd3e20e1d3e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1d44:	8b 95 b8 fe ff ff    	mov    -0x148(%rbp),%edx
    7fd3e20e1d4a:	81 e2 ff ff 00 00    	and    $0xffff,%edx
    7fd3e20e1d50:	89 8d 80 fb ff ff    	mov    %ecx,-0x480(%rbp)
    7fd3e20e1d56:	89 95 78 fb ff ff    	mov    %edx,-0x488(%rbp)
    7fd3e20e1d5c:	2b ca                	sub    %edx,%ecx
    7fd3e20e1d5e:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1d64:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e1d67:	0b c8                	or     %eax,%ecx
    7fd3e20e1d69:	89 8d 70 fb ff ff    	mov    %ecx,-0x490(%rbp)
    7fd3e20e1d6f:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fd3e20e1d75:	85 c0                	test   %eax,%eax
    7fd3e20e1d77:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1d89
    7fd3e20e1d7d:	8b 85 b0 fe ff ff    	mov    -0x150(%rbp),%eax
    7fd3e20e1d83:	89 85 70 fb ff ff    	mov    %eax,-0x490(%rbp)
    7fd3e20e1d89:	8b 85 90 fb ff ff    	mov    -0x470(%rbp),%eax
    7fd3e20e1d8f:	03 85 88 fb ff ff    	add    -0x478(%rbp),%eax
    7fd3e20e1d95:	25 ff ff 00 00       	and    $0xffff,%eax
    7fd3e20e1d9a:	8b 8d 80 fb ff ff    	mov    -0x480(%rbp),%ecx
    7fd3e20e1da0:	03 8d 78 fb ff ff    	add    -0x488(%rbp),%ecx
    7fd3e20e1da6:	81 e1 ff ff 00 00    	and    $0xffff,%ecx
    7fd3e20e1dac:	c1 e0 10             	shl    $0x10,%eax
    7fd3e20e1daf:	0b c8                	or     %eax,%ecx
    7fd3e20e1db1:	89 8d 68 fb ff ff    	mov    %ecx,-0x498(%rbp)
    7fd3e20e1db7:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7fd3e20e1dbd:	85 c0                	test   %eax,%eax
    7fd3e20e1dbf:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1dd1
    7fd3e20e1dc5:	8b 85 98 fe ff ff    	mov    -0x168(%rbp),%eax
    7fd3e20e1dcb:	89 85 68 fb ff ff    	mov    %eax,-0x498(%rbp)
    7fd3e20e1dd1:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fd3e20e1dd7:	ff c0                	inc    %eax
    7fd3e20e1dd9:	83 e0 3f             	and    $0x3f,%eax
    7fd3e20e1ddc:	89 85 60 fb ff ff    	mov    %eax,-0x4a0(%rbp)
    7fd3e20e1de2:	8b 85 20 fe ff ff    	mov    -0x1e0(%rbp),%eax
    7fd3e20e1de8:	41 23 c6             	and    %r14d,%eax
    7fd3e20e1deb:	89 85 58 fb ff ff    	mov    %eax,-0x4a8(%rbp)
    7fd3e20e1df1:	48 8b 85 50 fe ff ff 	mov    -0x1b0(%rbp),%rax
    7fd3e20e1df8:	48 8b 40 08          	mov    0x8(%rax),%rax
    7fd3e20e1dfc:	8b 00                	mov    (%rax),%eax
    7fd3e20e1dfe:	8b cb                	mov    %ebx,%ecx
    7fd3e20e1e00:	c1 e9 02             	shr    $0x2,%ecx
    7fd3e20e1e03:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e1e06:	85 c9                	test   %ecx,%ecx
    7fd3e20e1e08:	0f 94 c1             	sete   %cl
    7fd3e20e1e0b:	0f b6 c9             	movzbl %cl,%ecx
    7fd3e20e1e0e:	23 c1                	and    %ecx,%eax
    7fd3e20e1e10:	8b 8d 28 fe ff ff    	mov    -0x1d8(%rbp),%ecx
    7fd3e20e1e16:	23 8d 30 fe ff ff    	and    -0x1d0(%rbp),%ecx
    7fd3e20e1e1c:	85 c9                	test   %ecx,%ecx
    7fd3e20e1e1e:	0f 94 c2             	sete   %dl
    7fd3e20e1e21:	0f b6 d2             	movzbl %dl,%edx
    7fd3e20e1e24:	89 95 50 fb ff ff    	mov    %edx,-0x4b0(%rbp)
    7fd3e20e1e2a:	23 d0                	and    %eax,%edx
    7fd3e20e1e2c:	8b f3                	mov    %ebx,%esi
    7fd3e20e1e2e:	83 e6 03             	and    $0x3,%esi
    7fd3e20e1e31:	d1 e6                	shl    %esi
    7fd3e20e1e33:	89 b5 48 fb ff ff    	mov    %esi,-0x4b8(%rbp)
    7fd3e20e1e39:	89 85 40 fb ff ff    	mov    %eax,-0x4c0(%rbp)
    7fd3e20e1e3f:	85 c0                	test   %eax,%eax
    7fd3e20e1e41:	0f 94 c0             	sete   %al
    7fd3e20e1e44:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e1e47:	89 8d 38 fb ff ff    	mov    %ecx,-0x4c8(%rbp)
    7fd3e20e1e4d:	23 c8                	and    %eax,%ecx
    7fd3e20e1e4f:	89 8d 30 fb ff ff    	mov    %ecx,-0x4d0(%rbp)
    7fd3e20e1e55:	8b c3                	mov    %ebx,%eax
    7fd3e20e1e57:	d1 e8                	shr    %eax
    7fd3e20e1e59:	83 e0 03             	and    $0x3,%eax
    7fd3e20e1e5c:	89 85 28 fb ff ff    	mov    %eax,-0x4d8(%rbp)
    7fd3e20e1e62:	85 d2                	test   %edx,%edx
    7fd3e20e1e64:	0f 85 1b 00 00 00    	jne    0x7fd3e20e1e85
    7fd3e20e1e6a:	8b 85 30 fb ff ff    	mov    -0x4d0(%rbp),%eax
    7fd3e20e1e70:	85 c0                	test   %eax,%eax
    7fd3e20e1e72:	0f 85 1e 00 00 00    	jne    0x7fd3e20e1e96
    7fd3e20e1e78:	8b c3                	mov    %ebx,%eax
    7fd3e20e1e7a:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7fd3e20e1e80:	e9 1d 00 00 00       	jmpq   0x7fd3e20e1ea2
    7fd3e20e1e85:	8b 85 48 fb ff ff    	mov    -0x4b8(%rbp),%eax
    7fd3e20e1e8b:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7fd3e20e1e91:	e9 0c 00 00 00       	jmpq   0x7fd3e20e1ea2
    7fd3e20e1e96:	8b 85 28 fb ff ff    	mov    -0x4d8(%rbp),%eax
    7fd3e20e1e9c:	89 85 20 fb ff ff    	mov    %eax,-0x4e0(%rbp)
    7fd3e20e1ea2:	8b c3                	mov    %ebx,%eax
    7fd3e20e1ea4:	d1 e8                	shr    %eax
    7fd3e20e1ea6:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1ea9:	89 85 18 fb ff ff    	mov    %eax,-0x4e8(%rbp)
    7fd3e20e1eaf:	8b 8d 50 fb ff ff    	mov    -0x4b0(%rbp),%ecx
    7fd3e20e1eb5:	0b c1                	or     %ecx,%eax
    7fd3e20e1eb7:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7fd3e20e1ebe:	48 8b 09             	mov    (%rcx),%rcx
    7fd3e20e1ec1:	8b 09                	mov    (%rcx),%ecx
    7fd3e20e1ec3:	89 8d 10 fb ff ff    	mov    %ecx,-0x4f0(%rbp)
    7fd3e20e1ec9:	89 8d 08 fb ff ff    	mov    %ecx,-0x4f8(%rbp)
    7fd3e20e1ecf:	85 c0                	test   %eax,%eax
    7fd3e20e1ed1:	0f 85 0c 00 00 00    	jne    0x7fd3e20e1ee3
    7fd3e20e1ed7:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fd3e20e1edd:	89 85 08 fb ff ff    	mov    %eax,-0x4f8(%rbp)
    7fd3e20e1ee3:	8b c3                	mov    %ebx,%eax
    7fd3e20e1ee5:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1ee8:	8b 8d 40 fb ff ff    	mov    -0x4c0(%rbp),%ecx
    7fd3e20e1eee:	23 c1                	and    %ecx,%eax
    7fd3e20e1ef0:	8b 95 38 fb ff ff    	mov    -0x4c8(%rbp),%edx
    7fd3e20e1ef6:	0b c2                	or     %edx,%eax
    7fd3e20e1ef8:	89 85 00 fb ff ff    	mov    %eax,-0x500(%rbp)
    7fd3e20e1efe:	23 8d 18 fb ff ff    	and    -0x4e8(%rbp),%ecx
    7fd3e20e1f04:	0b d1                	or     %ecx,%edx
    7fd3e20e1f06:	89 95 f8 fa ff ff    	mov    %edx,-0x508(%rbp)
    7fd3e20e1f0c:	8b 85 38 fe ff ff    	mov    -0x1c8(%rbp),%eax
    7fd3e20e1f12:	23 85 40 fe ff ff    	and    -0x1c0(%rbp),%eax
    7fd3e20e1f18:	48 8b 8d 50 fe ff ff 	mov    -0x1b0(%rbp),%rcx
    7fd3e20e1f1f:	48 8b 49 10          	mov    0x10(%rcx),%rcx
    7fd3e20e1f23:	8b 09                	mov    (%rcx),%ecx
    7fd3e20e1f25:	8b 95 68 fe ff ff    	mov    -0x198(%rbp),%edx
    7fd3e20e1f2b:	83 e2 01             	and    $0x1,%edx
    7fd3e20e1f2e:	85 d2                	test   %edx,%edx
    7fd3e20e1f30:	0f 94 c2             	sete   %dl
    7fd3e20e1f33:	0f b6 d2             	movzbl %dl,%edx
    7fd3e20e1f36:	23 ca                	and    %edx,%ecx
    7fd3e20e1f38:	85 c9                	test   %ecx,%ecx
    7fd3e20e1f3a:	0f 94 c2             	sete   %dl
    7fd3e20e1f3d:	0f b6 d2             	movzbl %dl,%edx
    7fd3e20e1f40:	89 95 f0 fa ff ff    	mov    %edx,-0x510(%rbp)
    7fd3e20e1f46:	23 d0                	and    %eax,%edx
    7fd3e20e1f48:	8b b5 68 fe ff ff    	mov    -0x198(%rbp),%esi
    7fd3e20e1f4e:	83 e6 03             	and    $0x3,%esi
    7fd3e20e1f51:	d1 e6                	shl    %esi
    7fd3e20e1f53:	89 b5 e8 fa ff ff    	mov    %esi,-0x518(%rbp)
    7fd3e20e1f59:	89 85 e0 fa ff ff    	mov    %eax,-0x520(%rbp)
    7fd3e20e1f5f:	85 c0                	test   %eax,%eax
    7fd3e20e1f61:	0f 94 c0             	sete   %al
    7fd3e20e1f64:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e1f67:	89 8d d8 fa ff ff    	mov    %ecx,-0x528(%rbp)
    7fd3e20e1f6d:	23 c8                	and    %eax,%ecx
    7fd3e20e1f6f:	89 8d d0 fa ff ff    	mov    %ecx,-0x530(%rbp)
    7fd3e20e1f75:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fd3e20e1f7b:	d1 e8                	shr    %eax
    7fd3e20e1f7d:	83 e0 03             	and    $0x3,%eax
    7fd3e20e1f80:	89 85 c8 fa ff ff    	mov    %eax,-0x538(%rbp)
    7fd3e20e1f86:	85 d2                	test   %edx,%edx
    7fd3e20e1f88:	0f 85 1f 00 00 00    	jne    0x7fd3e20e1fad
    7fd3e20e1f8e:	8b 85 d0 fa ff ff    	mov    -0x530(%rbp),%eax
    7fd3e20e1f94:	85 c0                	test   %eax,%eax
    7fd3e20e1f96:	0f 85 22 00 00 00    	jne    0x7fd3e20e1fbe
    7fd3e20e1f9c:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fd3e20e1fa2:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fd3e20e1fa8:	e9 1d 00 00 00       	jmpq   0x7fd3e20e1fca
    7fd3e20e1fad:	8b 85 e8 fa ff ff    	mov    -0x518(%rbp),%eax
    7fd3e20e1fb3:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fd3e20e1fb9:	e9 0c 00 00 00       	jmpq   0x7fd3e20e1fca
    7fd3e20e1fbe:	8b 85 c8 fa ff ff    	mov    -0x538(%rbp),%eax
    7fd3e20e1fc4:	89 85 c0 fa ff ff    	mov    %eax,-0x540(%rbp)
    7fd3e20e1fca:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fd3e20e1fd0:	d1 e8                	shr    %eax
    7fd3e20e1fd2:	83 e0 01             	and    $0x1,%eax
    7fd3e20e1fd5:	89 85 b8 fa ff ff    	mov    %eax,-0x548(%rbp)
    7fd3e20e1fdb:	8b 8d f0 fa ff ff    	mov    -0x510(%rbp),%ecx
    7fd3e20e1fe1:	0b c1                	or     %ecx,%eax
    7fd3e20e1fe3:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fd3e20e1fe9:	89 8d b0 fa ff ff    	mov    %ecx,-0x550(%rbp)
    7fd3e20e1fef:	85 c0                	test   %eax,%eax
    7fd3e20e1ff1:	0f 85 0c 00 00 00    	jne    0x7fd3e20e2003
    7fd3e20e1ff7:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7fd3e20e1ffd:	89 85 b0 fa ff ff    	mov    %eax,-0x550(%rbp)
    7fd3e20e2003:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fd3e20e2009:	83 e0 01             	and    $0x1,%eax
    7fd3e20e200c:	8b 8d e0 fa ff ff    	mov    -0x520(%rbp),%ecx
    7fd3e20e2012:	23 c1                	and    %ecx,%eax
    7fd3e20e2014:	8b 95 d8 fa ff ff    	mov    -0x528(%rbp),%edx
    7fd3e20e201a:	0b c2                	or     %edx,%eax
    7fd3e20e201c:	89 85 a8 fa ff ff    	mov    %eax,-0x558(%rbp)
    7fd3e20e2022:	23 8d b8 fa ff ff    	and    -0x548(%rbp),%ecx
    7fd3e20e2028:	0b d1                	or     %ecx,%edx
    7fd3e20e202a:	85 d2                	test   %edx,%edx
    7fd3e20e202c:	0f 84 13 00 00 00    	je     0x7fd3e20e2045
    7fd3e20e2032:	8b 85 90 fe ff ff    	mov    -0x170(%rbp),%eax
    7fd3e20e2038:	41 89 87 50 04 00 00 	mov    %eax,0x450(%r15)
    7fd3e20e203f:	89 85 58 fe ff ff    	mov    %eax,-0x1a8(%rbp)
    7fd3e20e2045:	8b 85 a8 fa ff ff    	mov    -0x558(%rbp),%eax
    7fd3e20e204b:	85 c0                	test   %eax,%eax
    7fd3e20e204d:	0f 84 13 00 00 00    	je     0x7fd3e20e2066
    7fd3e20e2053:	8b 85 b0 fa ff ff    	mov    -0x550(%rbp),%eax
    7fd3e20e2059:	41 89 87 48 04 00 00 	mov    %eax,0x448(%r15)
    7fd3e20e2060:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7fd3e20e2066:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e2069:	0f 84 1a 00 00 00    	je     0x7fd3e20e2089
    7fd3e20e206f:	41 c7 87 40 04 00 00 	movl   $0x1,0x440(%r15)
    7fd3e20e2076:	01 00 00 00 
    7fd3e20e207a:	c7 85 68 fe ff ff 01 	movl   $0x1,-0x198(%rbp)
    7fd3e20e2081:	00 00 00 
    7fd3e20e2084:	e9 13 00 00 00       	jmpq   0x7fd3e20e209c
    7fd3e20e2089:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fd3e20e208f:	41 89 87 40 04 00 00 	mov    %eax,0x440(%r15)
    7fd3e20e2096:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7fd3e20e209c:	8b 85 f8 fa ff ff    	mov    -0x508(%rbp),%eax
    7fd3e20e20a2:	85 c0                	test   %eax,%eax
    7fd3e20e20a4:	0f 84 13 00 00 00    	je     0x7fd3e20e20bd
    7fd3e20e20aa:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fd3e20e20b0:	41 89 87 38 04 00 00 	mov    %eax,0x438(%r15)
    7fd3e20e20b7:	89 85 70 fe ff ff    	mov    %eax,-0x190(%rbp)
    7fd3e20e20bd:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fd3e20e20c3:	85 c0                	test   %eax,%eax
    7fd3e20e20c5:	0f 84 13 00 00 00    	je     0x7fd3e20e20de
    7fd3e20e20cb:	8b 85 08 fb ff ff    	mov    -0x4f8(%rbp),%eax
    7fd3e20e20d1:	41 89 87 30 04 00 00 	mov    %eax,0x430(%r15)
    7fd3e20e20d8:	89 85 78 fe ff ff    	mov    %eax,-0x188(%rbp)
    7fd3e20e20de:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e20e1:	0f 84 15 00 00 00    	je     0x7fd3e20e20fc
    7fd3e20e20e7:	41 c7 87 28 04 00 00 	movl   $0x1,0x428(%r15)
    7fd3e20e20ee:	01 00 00 00 
    7fd3e20e20f2:	bb 01 00 00 00       	mov    $0x1,%ebx
    7fd3e20e20f7:	e9 10 00 00 00       	jmpq   0x7fd3e20e210c
    7fd3e20e20fc:	8b 85 20 fb ff ff    	mov    -0x4e0(%rbp),%eax
    7fd3e20e2102:	41 89 87 28 04 00 00 	mov    %eax,0x428(%r15)
    7fd3e20e2109:	48 8b d8             	mov    %rax,%rbx
    7fd3e20e210c:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e210f:	0f 84 1a 00 00 00    	je     0x7fd3e20e212f
    7fd3e20e2115:	41 c7 87 20 04 00 00 	movl   $0x0,0x420(%r15)
    7fd3e20e211c:	00 00 00 00 
    7fd3e20e2120:	c7 85 80 fe ff ff 00 	movl   $0x0,-0x180(%rbp)
    7fd3e20e2127:	00 00 00 
    7fd3e20e212a:	e9 21 00 00 00       	jmpq   0x7fd3e20e2150
    7fd3e20e212f:	8b 85 58 fb ff ff    	mov    -0x4a8(%rbp),%eax
    7fd3e20e2135:	85 c0                	test   %eax,%eax
    7fd3e20e2137:	0f 84 13 00 00 00    	je     0x7fd3e20e2150
    7fd3e20e213d:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7fd3e20e2143:	41 89 87 20 04 00 00 	mov    %eax,0x420(%r15)
    7fd3e20e214a:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7fd3e20e2150:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e2153:	0f 84 25 00 00 00    	je     0x7fd3e20e217e
    7fd3e20e2159:	41 c7 87 10 04 00 00 	movl   $0x0,0x410(%r15)
    7fd3e20e2160:	00 00 00 00 
    7fd3e20e2164:	c7 85 88 fe ff ff 00 	movl   $0x0,-0x178(%rbp)
    7fd3e20e216b:	00 00 00 
    7fd3e20e216e:	41 c7 87 18 04 00 00 	movl   $0x0,0x418(%r15)
    7fd3e20e2175:	00 00 00 00 
    7fd3e20e2179:	e9 2a 00 00 00       	jmpq   0x7fd3e20e21a8
    7fd3e20e217e:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2181:	0f 84 21 00 00 00    	je     0x7fd3e20e21a8
    7fd3e20e2187:	41 8b 87 18 04 00 00 	mov    0x418(%r15),%eax
    7fd3e20e218e:	41 89 87 10 04 00 00 	mov    %eax,0x410(%r15)
    7fd3e20e2195:	89 85 88 fe ff ff    	mov    %eax,-0x178(%rbp)
    7fd3e20e219b:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fd3e20e21a1:	41 89 87 18 04 00 00 	mov    %eax,0x418(%r15)
    7fd3e20e21a8:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e21ab:	0f 84 26 00 00 00    	je     0x7fd3e20e21d7
    7fd3e20e21b1:	8b 85 68 fb ff ff    	mov    -0x498(%rbp),%eax
    7fd3e20e21b7:	41 89 87 08 04 00 00 	mov    %eax,0x408(%r15)
    7fd3e20e21be:	89 85 90 fe ff ff    	mov    %eax,-0x170(%rbp)
    7fd3e20e21c4:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fd3e20e21ca:	41 89 87 00 04 00 00 	mov    %eax,0x400(%r15)
    7fd3e20e21d1:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7fd3e20e21d7:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e21da:	0f 84 1a 00 00 00    	je     0x7fd3e20e21fa
    7fd3e20e21e0:	41 c7 87 f8 03 00 00 	movl   $0x0,0x3f8(%r15)
    7fd3e20e21e7:	00 00 00 00 
    7fd3e20e21eb:	c7 85 a0 fe ff ff 00 	movl   $0x0,-0x160(%rbp)
    7fd3e20e21f2:	00 00 00 
    7fd3e20e21f5:	e9 21 00 00 00       	jmpq   0x7fd3e20e221b
    7fd3e20e21fa:	8b 85 98 fb ff ff    	mov    -0x468(%rbp),%eax
    7fd3e20e2200:	85 c0                	test   %eax,%eax
    7fd3e20e2202:	0f 84 13 00 00 00    	je     0x7fd3e20e221b
    7fd3e20e2208:	8b 85 a0 fb ff ff    	mov    -0x460(%rbp),%eax
    7fd3e20e220e:	41 89 87 f8 03 00 00 	mov    %eax,0x3f8(%r15)
    7fd3e20e2215:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fd3e20e221b:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e221e:	0f 84 1a 00 00 00    	je     0x7fd3e20e223e
    7fd3e20e2224:	41 c7 87 f0 03 00 00 	movl   $0x0,0x3f0(%r15)
    7fd3e20e222b:	00 00 00 00 
    7fd3e20e222f:	c7 85 a8 fe ff ff 00 	movl   $0x0,-0x158(%rbp)
    7fd3e20e2236:	00 00 00 
    7fd3e20e2239:	e9 1c 00 00 00       	jmpq   0x7fd3e20e225a
    7fd3e20e223e:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2241:	0f 84 13 00 00 00    	je     0x7fd3e20e225a
    7fd3e20e2247:	8b 85 c8 fe ff ff    	mov    -0x138(%rbp),%eax
    7fd3e20e224d:	41 89 87 f0 03 00 00 	mov    %eax,0x3f0(%r15)
    7fd3e20e2254:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7fd3e20e225a:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e225d:	0f 84 26 00 00 00    	je     0x7fd3e20e2289
    7fd3e20e2263:	8b 85 d0 fe ff ff    	mov    -0x130(%rbp),%eax
    7fd3e20e2269:	41 89 87 e8 03 00 00 	mov    %eax,0x3e8(%r15)
    7fd3e20e2270:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7fd3e20e2276:	8b 85 a8 fb ff ff    	mov    -0x458(%rbp),%eax
    7fd3e20e227c:	41 89 87 e0 03 00 00 	mov    %eax,0x3e0(%r15)
    7fd3e20e2283:	89 85 b8 fe ff ff    	mov    %eax,-0x148(%rbp)
    7fd3e20e2289:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e228c:	0f 84 1a 00 00 00    	je     0x7fd3e20e22ac
    7fd3e20e2292:	41 c7 87 d8 03 00 00 	movl   $0x0,0x3d8(%r15)
    7fd3e20e2299:	00 00 00 00 
    7fd3e20e229d:	c7 85 c0 fe ff ff 00 	movl   $0x0,-0x140(%rbp)
    7fd3e20e22a4:	00 00 00 
    7fd3e20e22a7:	e9 21 00 00 00       	jmpq   0x7fd3e20e22cd
    7fd3e20e22ac:	8b 85 b0 fb ff ff    	mov    -0x450(%rbp),%eax
    7fd3e20e22b2:	85 c0                	test   %eax,%eax
    7fd3e20e22b4:	0f 84 13 00 00 00    	je     0x7fd3e20e22cd
    7fd3e20e22ba:	8b 85 b8 fb ff ff    	mov    -0x448(%rbp),%eax
    7fd3e20e22c0:	41 89 87 d8 03 00 00 	mov    %eax,0x3d8(%r15)
    7fd3e20e22c7:	89 85 c0 fe ff ff    	mov    %eax,-0x140(%rbp)
    7fd3e20e22cd:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e22d0:	0f 84 25 00 00 00    	je     0x7fd3e20e22fb
    7fd3e20e22d6:	41 c7 87 c8 03 00 00 	movl   $0x0,0x3c8(%r15)
    7fd3e20e22dd:	00 00 00 00 
    7fd3e20e22e1:	c7 85 c8 fe ff ff 00 	movl   $0x0,-0x138(%rbp)
    7fd3e20e22e8:	00 00 00 
    7fd3e20e22eb:	41 c7 87 d0 03 00 00 	movl   $0x0,0x3d0(%r15)
    7fd3e20e22f2:	00 00 00 00 
    7fd3e20e22f6:	e9 35 00 00 00       	jmpq   0x7fd3e20e2330
    7fd3e20e22fb:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e22fe:	0f 84 2c 00 00 00    	je     0x7fd3e20e2330
    7fd3e20e2304:	41 8b 87 d0 03 00 00 	mov    0x3d0(%r15),%eax
    7fd3e20e230b:	8b c8                	mov    %eax,%ecx
    7fd3e20e230d:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e2310:	41 89 8f c8 03 00 00 	mov    %ecx,0x3c8(%r15)
    7fd3e20e2317:	89 8d c8 fe ff ff    	mov    %ecx,-0x138(%rbp)
    7fd3e20e231d:	d1 e8                	shr    %eax
    7fd3e20e231f:	8b 8d e8 fe ff ff    	mov    -0x118(%rbp),%ecx
    7fd3e20e2325:	d1 e1                	shl    %ecx
    7fd3e20e2327:	0b c1                	or     %ecx,%eax
    7fd3e20e2329:	41 89 87 d0 03 00 00 	mov    %eax,0x3d0(%r15)
    7fd3e20e2330:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2333:	0f 84 34 00 00 00    	je     0x7fd3e20e236d
    7fd3e20e2339:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fd3e20e233f:	41 89 87 c0 03 00 00 	mov    %eax,0x3c0(%r15)
    7fd3e20e2346:	89 85 d0 fe ff ff    	mov    %eax,-0x130(%rbp)
    7fd3e20e234c:	41 8b 87 b8 03 00 00 	mov    0x3b8(%r15),%eax
    7fd3e20e2353:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7fd3e20e235a:	89 85 d8 fe ff ff    	mov    %eax,-0x128(%rbp)
    7fd3e20e2360:	8b 85 d0 fb ff ff    	mov    -0x430(%rbp),%eax
    7fd3e20e2366:	41 89 87 b8 03 00 00 	mov    %eax,0x3b8(%r15)
    7fd3e20e236d:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e2370:	0f 84 1a 00 00 00    	je     0x7fd3e20e2390
    7fd3e20e2376:	41 c7 87 a8 03 00 00 	movl   $0x0,0x3a8(%r15)
    7fd3e20e237d:	00 00 00 00 
    7fd3e20e2381:	c7 85 e0 fe ff ff 00 	movl   $0x0,-0x120(%rbp)
    7fd3e20e2388:	00 00 00 
    7fd3e20e238b:	e9 21 00 00 00       	jmpq   0x7fd3e20e23b1
    7fd3e20e2390:	8b 85 f8 fb ff ff    	mov    -0x408(%rbp),%eax
    7fd3e20e2396:	85 c0                	test   %eax,%eax
    7fd3e20e2398:	0f 84 13 00 00 00    	je     0x7fd3e20e23b1
    7fd3e20e239e:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fd3e20e23a4:	41 89 87 a8 03 00 00 	mov    %eax,0x3a8(%r15)
    7fd3e20e23ab:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7fd3e20e23b1:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e23b4:	0f 84 25 00 00 00    	je     0x7fd3e20e23df
    7fd3e20e23ba:	41 c7 87 98 03 00 00 	movl   $0x0,0x398(%r15)
    7fd3e20e23c1:	00 00 00 00 
    7fd3e20e23c5:	c7 85 e8 fe ff ff 00 	movl   $0x0,-0x118(%rbp)
    7fd3e20e23cc:	00 00 00 
    7fd3e20e23cf:	41 c7 87 a0 03 00 00 	movl   $0x0,0x3a0(%r15)
    7fd3e20e23d6:	00 00 00 00 
    7fd3e20e23da:	e9 36 00 00 00       	jmpq   0x7fd3e20e2415
    7fd3e20e23df:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e23e2:	0f 84 2d 00 00 00    	je     0x7fd3e20e2415
    7fd3e20e23e8:	41 8b 87 a0 03 00 00 	mov    0x3a0(%r15),%eax
    7fd3e20e23ef:	8b c8                	mov    %eax,%ecx
    7fd3e20e23f1:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e23f4:	41 89 8f 98 03 00 00 	mov    %ecx,0x398(%r15)
    7fd3e20e23fb:	89 8d e8 fe ff ff    	mov    %ecx,-0x118(%rbp)
    7fd3e20e2401:	d1 e8                	shr    %eax
    7fd3e20e2403:	8b 8d 10 ff ff ff    	mov    -0xf0(%rbp),%ecx
    7fd3e20e2409:	c1 e1 04             	shl    $0x4,%ecx
    7fd3e20e240c:	0b c1                	or     %ecx,%eax
    7fd3e20e240e:	41 89 87 a0 03 00 00 	mov    %eax,0x3a0(%r15)
    7fd3e20e2415:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2418:	0f 84 67 00 00 00    	je     0x7fd3e20e2485
    7fd3e20e241e:	41 8b 87 94 03 00 00 	mov    0x394(%r15),%eax
    7fd3e20e2425:	49 8b cf             	mov    %r15,%rcx
    7fd3e20e2428:	48 81 c1 84 03 00 00 	add    $0x384,%rcx
    7fd3e20e242f:	8b d0                	mov    %eax,%edx
    7fd3e20e2431:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fd3e20e2434:	41 89 97 7c 03 00 00 	mov    %edx,0x37c(%r15)
    7fd3e20e243b:	89 95 f0 fe ff ff    	mov    %edx,-0x110(%rbp)
    7fd3e20e2441:	8b d0                	mov    %eax,%edx
    7fd3e20e2443:	8b b5 08 fc ff ff    	mov    -0x3f8(%rbp),%esi
    7fd3e20e2449:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fd3e20e244c:	ff c8                	dec    %eax
    7fd3e20e244e:	b9 03 00 00 00       	mov    $0x3,%ecx
    7fd3e20e2453:	3b c1                	cmp    %ecx,%eax
    7fd3e20e2455:	0f 47 c1             	cmova  %ecx,%eax
    7fd3e20e2458:	41 89 87 94 03 00 00 	mov    %eax,0x394(%r15)
    7fd3e20e245f:	8b 85 58 fc ff ff    	mov    -0x3a8(%rbp),%eax
    7fd3e20e2465:	41 89 87 74 03 00 00 	mov    %eax,0x374(%r15)
    7fd3e20e246c:	89 85 f8 fe ff ff    	mov    %eax,-0x108(%rbp)
    7fd3e20e2472:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7fd3e20e2478:	41 89 87 6c 03 00 00 	mov    %eax,0x36c(%r15)
    7fd3e20e247f:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7fd3e20e2485:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e2488:	0f 84 1a 00 00 00    	je     0x7fd3e20e24a8
    7fd3e20e248e:	41 c7 87 64 03 00 00 	movl   $0x0,0x364(%r15)
    7fd3e20e2495:	00 00 00 00 
    7fd3e20e2499:	c7 85 08 ff ff ff 00 	movl   $0x0,-0xf8(%rbp)
    7fd3e20e24a0:	00 00 00 
    7fd3e20e24a3:	e9 21 00 00 00       	jmpq   0x7fd3e20e24c9
    7fd3e20e24a8:	8b 85 60 fc ff ff    	mov    -0x3a0(%rbp),%eax
    7fd3e20e24ae:	85 c0                	test   %eax,%eax
    7fd3e20e24b0:	0f 84 13 00 00 00    	je     0x7fd3e20e24c9
    7fd3e20e24b6:	8b 85 68 fc ff ff    	mov    -0x398(%rbp),%eax
    7fd3e20e24bc:	41 89 87 64 03 00 00 	mov    %eax,0x364(%r15)
    7fd3e20e24c3:	89 85 08 ff ff ff    	mov    %eax,-0xf8(%rbp)
    7fd3e20e24c9:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e24cc:	0f 84 25 00 00 00    	je     0x7fd3e20e24f7
    7fd3e20e24d2:	41 c7 87 54 03 00 00 	movl   $0x0,0x354(%r15)
    7fd3e20e24d9:	00 00 00 00 
    7fd3e20e24dd:	c7 85 10 ff ff ff 00 	movl   $0x0,-0xf0(%rbp)
    7fd3e20e24e4:	00 00 00 
    7fd3e20e24e7:	41 c7 87 5c 03 00 00 	movl   $0x0,0x35c(%r15)
    7fd3e20e24ee:	00 00 00 00 
    7fd3e20e24f2:	e9 36 00 00 00       	jmpq   0x7fd3e20e252d
    7fd3e20e24f7:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e24fa:	0f 84 2d 00 00 00    	je     0x7fd3e20e252d
    7fd3e20e2500:	41 8b 87 5c 03 00 00 	mov    0x35c(%r15),%eax
    7fd3e20e2507:	8b c8                	mov    %eax,%ecx
    7fd3e20e2509:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e250c:	41 89 8f 54 03 00 00 	mov    %ecx,0x354(%r15)
    7fd3e20e2513:	89 8d 10 ff ff ff    	mov    %ecx,-0xf0(%rbp)
    7fd3e20e2519:	d1 e8                	shr    %eax
    7fd3e20e251b:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7fd3e20e2521:	c1 e1 03             	shl    $0x3,%ecx
    7fd3e20e2524:	0b c1                	or     %ecx,%eax
    7fd3e20e2526:	41 89 87 5c 03 00 00 	mov    %eax,0x35c(%r15)
    7fd3e20e252d:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2530:	0f 84 54 00 00 00    	je     0x7fd3e20e258a
    7fd3e20e2536:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7fd3e20e253c:	41 89 87 4c 03 00 00 	mov    %eax,0x34c(%r15)
    7fd3e20e2543:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7fd3e20e2549:	41 8b 87 48 03 00 00 	mov    0x348(%r15),%eax
    7fd3e20e2550:	49 8b cf             	mov    %r15,%rcx
    7fd3e20e2553:	48 81 c1 38 03 00 00 	add    $0x338,%rcx
    7fd3e20e255a:	8b d0                	mov    %eax,%edx
    7fd3e20e255c:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fd3e20e255f:	41 89 97 30 03 00 00 	mov    %edx,0x330(%r15)
    7fd3e20e2566:	89 95 20 ff ff ff    	mov    %edx,-0xe0(%rbp)
    7fd3e20e256c:	8b d0                	mov    %eax,%edx
    7fd3e20e256e:	8b b5 80 fc ff ff    	mov    -0x380(%rbp),%esi
    7fd3e20e2574:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fd3e20e2577:	ff c8                	dec    %eax
    7fd3e20e2579:	b9 02 00 00 00       	mov    $0x2,%ecx
    7fd3e20e257e:	3b c1                	cmp    %ecx,%eax
    7fd3e20e2580:	0f 47 c1             	cmova  %ecx,%eax
    7fd3e20e2583:	41 89 87 48 03 00 00 	mov    %eax,0x348(%r15)
    7fd3e20e258a:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e258d:	0f 84 1a 00 00 00    	je     0x7fd3e20e25ad
    7fd3e20e2593:	41 c7 87 28 03 00 00 	movl   $0x0,0x328(%r15)
    7fd3e20e259a:	00 00 00 00 
    7fd3e20e259e:	c7 85 28 ff ff ff 00 	movl   $0x0,-0xd8(%rbp)
    7fd3e20e25a5:	00 00 00 
    7fd3e20e25a8:	e9 21 00 00 00       	jmpq   0x7fd3e20e25ce
    7fd3e20e25ad:	8b 85 a8 fc ff ff    	mov    -0x358(%rbp),%eax
    7fd3e20e25b3:	85 c0                	test   %eax,%eax
    7fd3e20e25b5:	0f 84 13 00 00 00    	je     0x7fd3e20e25ce
    7fd3e20e25bb:	8b 85 b0 fc ff ff    	mov    -0x350(%rbp),%eax
    7fd3e20e25c1:	41 89 87 28 03 00 00 	mov    %eax,0x328(%r15)
    7fd3e20e25c8:	89 85 28 ff ff ff    	mov    %eax,-0xd8(%rbp)
    7fd3e20e25ce:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e25d1:	0f 84 1a 00 00 00    	je     0x7fd3e20e25f1
    7fd3e20e25d7:	41 c7 87 20 03 00 00 	movl   $0x0,0x320(%r15)
    7fd3e20e25de:	00 00 00 00 
    7fd3e20e25e2:	c7 85 30 ff ff ff 00 	movl   $0x0,-0xd0(%rbp)
    7fd3e20e25e9:	00 00 00 
    7fd3e20e25ec:	e9 1c 00 00 00       	jmpq   0x7fd3e20e260d
    7fd3e20e25f1:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e25f4:	0f 84 13 00 00 00    	je     0x7fd3e20e260d
    7fd3e20e25fa:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7fd3e20e2600:	41 89 87 20 03 00 00 	mov    %eax,0x320(%r15)
    7fd3e20e2607:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7fd3e20e260d:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2610:	0f 84 26 00 00 00    	je     0x7fd3e20e263c
    7fd3e20e2616:	8b 85 58 ff ff ff    	mov    -0xa8(%rbp),%eax
    7fd3e20e261c:	41 89 87 18 03 00 00 	mov    %eax,0x318(%r15)
    7fd3e20e2623:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7fd3e20e2629:	8b 85 b8 fc ff ff    	mov    -0x348(%rbp),%eax
    7fd3e20e262f:	41 89 87 10 03 00 00 	mov    %eax,0x310(%r15)
    7fd3e20e2636:	89 85 40 ff ff ff    	mov    %eax,-0xc0(%rbp)
    7fd3e20e263c:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e263f:	0f 84 1a 00 00 00    	je     0x7fd3e20e265f
    7fd3e20e2645:	41 c7 87 08 03 00 00 	movl   $0x0,0x308(%r15)
    7fd3e20e264c:	00 00 00 00 
    7fd3e20e2650:	c7 85 48 ff ff ff 00 	movl   $0x0,-0xb8(%rbp)
    7fd3e20e2657:	00 00 00 
    7fd3e20e265a:	e9 21 00 00 00       	jmpq   0x7fd3e20e2680
    7fd3e20e265f:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fd3e20e2665:	85 c0                	test   %eax,%eax
    7fd3e20e2667:	0f 84 13 00 00 00    	je     0x7fd3e20e2680
    7fd3e20e266d:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
    7fd3e20e2673:	41 89 87 08 03 00 00 	mov    %eax,0x308(%r15)
    7fd3e20e267a:	89 85 48 ff ff ff    	mov    %eax,-0xb8(%rbp)
    7fd3e20e2680:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e2683:	0f 84 25 00 00 00    	je     0x7fd3e20e26ae
    7fd3e20e2689:	41 c7 87 f8 02 00 00 	movl   $0x0,0x2f8(%r15)
    7fd3e20e2690:	00 00 00 00 
    7fd3e20e2694:	c7 85 50 ff ff ff 00 	movl   $0x0,-0xb0(%rbp)
    7fd3e20e269b:	00 00 00 
    7fd3e20e269e:	41 c7 87 00 03 00 00 	movl   $0x0,0x300(%r15)
    7fd3e20e26a5:	00 00 00 00 
    7fd3e20e26a9:	e9 36 00 00 00       	jmpq   0x7fd3e20e26e4
    7fd3e20e26ae:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e26b1:	0f 84 2d 00 00 00    	je     0x7fd3e20e26e4
    7fd3e20e26b7:	41 8b 87 00 03 00 00 	mov    0x300(%r15),%eax
    7fd3e20e26be:	8b c8                	mov    %eax,%ecx
    7fd3e20e26c0:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e26c3:	41 89 8f f8 02 00 00 	mov    %ecx,0x2f8(%r15)
    7fd3e20e26ca:	89 8d 50 ff ff ff    	mov    %ecx,-0xb0(%rbp)
    7fd3e20e26d0:	d1 e8                	shr    %eax
    7fd3e20e26d2:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7fd3e20e26d8:	c1 e1 07             	shl    $0x7,%ecx
    7fd3e20e26db:	0b c1                	or     %ecx,%eax
    7fd3e20e26dd:	41 89 87 00 03 00 00 	mov    %eax,0x300(%r15)
    7fd3e20e26e4:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e26e7:	0f 84 54 00 00 00    	je     0x7fd3e20e2741
    7fd3e20e26ed:	8b 85 d0 fc ff ff    	mov    -0x330(%rbp),%eax
    7fd3e20e26f3:	41 89 87 f0 02 00 00 	mov    %eax,0x2f0(%r15)
    7fd3e20e26fa:	89 85 58 ff ff ff    	mov    %eax,-0xa8(%rbp)
    7fd3e20e2700:	41 8b 87 ec 02 00 00 	mov    0x2ec(%r15),%eax
    7fd3e20e2707:	49 8b cf             	mov    %r15,%rcx
    7fd3e20e270a:	48 81 c1 cc 02 00 00 	add    $0x2cc,%rcx
    7fd3e20e2711:	8b d0                	mov    %eax,%edx
    7fd3e20e2713:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fd3e20e2716:	41 89 97 c4 02 00 00 	mov    %edx,0x2c4(%r15)
    7fd3e20e271d:	89 95 60 ff ff ff    	mov    %edx,-0xa0(%rbp)
    7fd3e20e2723:	8b d0                	mov    %eax,%edx
    7fd3e20e2725:	8b b5 e0 fc ff ff    	mov    -0x320(%rbp),%esi
    7fd3e20e272b:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fd3e20e272e:	ff c8                	dec    %eax
    7fd3e20e2730:	b9 06 00 00 00       	mov    $0x6,%ecx
    7fd3e20e2735:	3b c1                	cmp    %ecx,%eax
    7fd3e20e2737:	0f 47 c1             	cmova  %ecx,%eax
    7fd3e20e273a:	41 89 87 ec 02 00 00 	mov    %eax,0x2ec(%r15)
    7fd3e20e2741:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e2744:	0f 84 1a 00 00 00    	je     0x7fd3e20e2764
    7fd3e20e274a:	41 c7 87 bc 02 00 00 	movl   $0x0,0x2bc(%r15)
    7fd3e20e2751:	00 00 00 00 
    7fd3e20e2755:	c7 85 68 ff ff ff 00 	movl   $0x0,-0x98(%rbp)
    7fd3e20e275c:	00 00 00 
    7fd3e20e275f:	e9 21 00 00 00       	jmpq   0x7fd3e20e2785
    7fd3e20e2764:	8b 85 08 fd ff ff    	mov    -0x2f8(%rbp),%eax
    7fd3e20e276a:	85 c0                	test   %eax,%eax
    7fd3e20e276c:	0f 84 13 00 00 00    	je     0x7fd3e20e2785
    7fd3e20e2772:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fd3e20e2778:	41 89 87 bc 02 00 00 	mov    %eax,0x2bc(%r15)
    7fd3e20e277f:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7fd3e20e2785:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e2788:	0f 84 25 00 00 00    	je     0x7fd3e20e27b3
    7fd3e20e278e:	41 c7 87 ac 02 00 00 	movl   $0x0,0x2ac(%r15)
    7fd3e20e2795:	00 00 00 00 
    7fd3e20e2799:	c7 85 70 ff ff ff 00 	movl   $0x0,-0x90(%rbp)
    7fd3e20e27a0:	00 00 00 
    7fd3e20e27a3:	41 c7 87 b4 02 00 00 	movl   $0x0,0x2b4(%r15)
    7fd3e20e27aa:	00 00 00 00 
    7fd3e20e27ae:	e9 33 00 00 00       	jmpq   0x7fd3e20e27e6
    7fd3e20e27b3:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e27b6:	0f 84 2a 00 00 00    	je     0x7fd3e20e27e6
    7fd3e20e27bc:	41 8b 87 b4 02 00 00 	mov    0x2b4(%r15),%eax
    7fd3e20e27c3:	8b c8                	mov    %eax,%ecx
    7fd3e20e27c5:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e27c8:	41 89 8f ac 02 00 00 	mov    %ecx,0x2ac(%r15)
    7fd3e20e27cf:	89 8d 70 ff ff ff    	mov    %ecx,-0x90(%rbp)
    7fd3e20e27d5:	d1 e8                	shr    %eax
    7fd3e20e27d7:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7fd3e20e27da:	c1 e1 04             	shl    $0x4,%ecx
    7fd3e20e27dd:	0b c1                	or     %ecx,%eax
    7fd3e20e27df:	41 89 87 b4 02 00 00 	mov    %eax,0x2b4(%r15)
    7fd3e20e27e6:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e27e9:	0f 84 5e 00 00 00    	je     0x7fd3e20e284d
    7fd3e20e27ef:	41 8b 87 a8 02 00 00 	mov    0x2a8(%r15),%eax
    7fd3e20e27f6:	49 8b cf             	mov    %r15,%rcx
    7fd3e20e27f9:	48 81 c1 98 02 00 00 	add    $0x298,%rcx
    7fd3e20e2800:	8b d0                	mov    %eax,%edx
    7fd3e20e2802:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fd3e20e2805:	41 89 97 90 02 00 00 	mov    %edx,0x290(%r15)
    7fd3e20e280c:	89 95 78 ff ff ff    	mov    %edx,-0x88(%rbp)
    7fd3e20e2812:	8b d0                	mov    %eax,%edx
    7fd3e20e2814:	8b b5 18 fd ff ff    	mov    -0x2e8(%rbp),%esi
    7fd3e20e281a:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fd3e20e281d:	ff c8                	dec    %eax
    7fd3e20e281f:	b9 03 00 00 00       	mov    $0x3,%ecx
    7fd3e20e2824:	3b c1                	cmp    %ecx,%eax
    7fd3e20e2826:	0f 47 c1             	cmova  %ecx,%eax
    7fd3e20e2829:	41 89 87 a8 02 00 00 	mov    %eax,0x2a8(%r15)
    7fd3e20e2830:	8b 85 68 fd ff ff    	mov    -0x298(%rbp),%eax
    7fd3e20e2836:	41 89 87 88 02 00 00 	mov    %eax,0x288(%r15)
    7fd3e20e283d:	89 45 80             	mov    %eax,-0x80(%rbp)
    7fd3e20e2840:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7fd3e20e2843:	41 89 87 80 02 00 00 	mov    %eax,0x280(%r15)
    7fd3e20e284a:	89 45 88             	mov    %eax,-0x78(%rbp)
    7fd3e20e284d:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e2850:	0f 84 17 00 00 00    	je     0x7fd3e20e286d
    7fd3e20e2856:	41 c7 87 78 02 00 00 	movl   $0x0,0x278(%r15)
    7fd3e20e285d:	00 00 00 00 
    7fd3e20e2861:	c7 45 90 00 00 00 00 	movl   $0x0,-0x70(%rbp)
    7fd3e20e2868:	e9 1e 00 00 00       	jmpq   0x7fd3e20e288b
    7fd3e20e286d:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fd3e20e2873:	85 c0                	test   %eax,%eax
    7fd3e20e2875:	0f 84 10 00 00 00    	je     0x7fd3e20e288b
    7fd3e20e287b:	8b 85 78 fd ff ff    	mov    -0x288(%rbp),%eax
    7fd3e20e2881:	41 89 87 78 02 00 00 	mov    %eax,0x278(%r15)
    7fd3e20e2888:	89 45 90             	mov    %eax,-0x70(%rbp)
    7fd3e20e288b:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e288e:	0f 84 22 00 00 00    	je     0x7fd3e20e28b6
    7fd3e20e2894:	41 c7 87 68 02 00 00 	movl   $0x0,0x268(%r15)
    7fd3e20e289b:	00 00 00 00 
    7fd3e20e289f:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7fd3e20e28a6:	41 c7 87 70 02 00 00 	movl   $0x0,0x270(%r15)
    7fd3e20e28ad:	00 00 00 00 
    7fd3e20e28b1:	e9 30 00 00 00       	jmpq   0x7fd3e20e28e6
    7fd3e20e28b6:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e28b9:	0f 84 27 00 00 00    	je     0x7fd3e20e28e6
    7fd3e20e28bf:	41 8b 87 70 02 00 00 	mov    0x270(%r15),%eax
    7fd3e20e28c6:	8b c8                	mov    %eax,%ecx
    7fd3e20e28c8:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e28cb:	41 89 8f 68 02 00 00 	mov    %ecx,0x268(%r15)
    7fd3e20e28d2:	89 4d 98             	mov    %ecx,-0x68(%rbp)
    7fd3e20e28d5:	d1 e8                	shr    %eax
    7fd3e20e28d7:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    7fd3e20e28da:	c1 e1 0f             	shl    $0xf,%ecx
    7fd3e20e28dd:	0b c1                	or     %ecx,%eax
    7fd3e20e28df:	41 89 87 70 02 00 00 	mov    %eax,0x270(%r15)
    7fd3e20e28e6:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e28e9:	0f 84 4e 00 00 00    	je     0x7fd3e20e293d
    7fd3e20e28ef:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fd3e20e28f5:	41 89 87 60 02 00 00 	mov    %eax,0x260(%r15)
    7fd3e20e28fc:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7fd3e20e28ff:	41 8b 87 5c 02 00 00 	mov    0x25c(%r15),%eax
    7fd3e20e2906:	49 8b cf             	mov    %r15,%rcx
    7fd3e20e2909:	48 81 c1 1c 02 00 00 	add    $0x21c,%rcx
    7fd3e20e2910:	8b d0                	mov    %eax,%edx
    7fd3e20e2912:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fd3e20e2915:	41 89 97 14 02 00 00 	mov    %edx,0x214(%r15)
    7fd3e20e291c:	89 55 a8             	mov    %edx,-0x58(%rbp)
    7fd3e20e291f:	8b d0                	mov    %eax,%edx
    7fd3e20e2921:	8b b5 90 fd ff ff    	mov    -0x270(%rbp),%esi
    7fd3e20e2927:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fd3e20e292a:	ff c8                	dec    %eax
    7fd3e20e292c:	b9 0e 00 00 00       	mov    $0xe,%ecx
    7fd3e20e2931:	3b c1                	cmp    %ecx,%eax
    7fd3e20e2933:	0f 47 c1             	cmova  %ecx,%eax
    7fd3e20e2936:	41 89 87 5c 02 00 00 	mov    %eax,0x25c(%r15)
    7fd3e20e293d:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e2940:	0f 84 17 00 00 00    	je     0x7fd3e20e295d
    7fd3e20e2946:	41 c7 87 0c 02 00 00 	movl   $0x0,0x20c(%r15)
    7fd3e20e294d:	00 00 00 00 
    7fd3e20e2951:	c7 45 b0 00 00 00 00 	movl   $0x0,-0x50(%rbp)
    7fd3e20e2958:	e9 1e 00 00 00       	jmpq   0x7fd3e20e297b
    7fd3e20e295d:	8b 85 b8 fd ff ff    	mov    -0x248(%rbp),%eax
    7fd3e20e2963:	85 c0                	test   %eax,%eax
    7fd3e20e2965:	0f 84 10 00 00 00    	je     0x7fd3e20e297b
    7fd3e20e296b:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fd3e20e2971:	41 89 87 0c 02 00 00 	mov    %eax,0x20c(%r15)
    7fd3e20e2978:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7fd3e20e297b:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e297e:	0f 84 17 00 00 00    	je     0x7fd3e20e299b
    7fd3e20e2984:	41 c7 87 04 02 00 00 	movl   $0x0,0x204(%r15)
    7fd3e20e298b:	00 00 00 00 
    7fd3e20e298f:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
    7fd3e20e2996:	e9 16 00 00 00       	jmpq   0x7fd3e20e29b1
    7fd3e20e299b:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e299e:	0f 84 0d 00 00 00    	je     0x7fd3e20e29b1
    7fd3e20e29a4:	8b 45 d8             	mov    -0x28(%rbp),%eax
    7fd3e20e29a7:	41 89 87 04 02 00 00 	mov    %eax,0x204(%r15)
    7fd3e20e29ae:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7fd3e20e29b1:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e29b4:	0f 84 1d 00 00 00    	je     0x7fd3e20e29d7
    7fd3e20e29ba:	8b 45 e0             	mov    -0x20(%rbp),%eax
    7fd3e20e29bd:	41 89 87 fc 01 00 00 	mov    %eax,0x1fc(%r15)
    7fd3e20e29c4:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7fd3e20e29c7:	8b 85 c8 fd ff ff    	mov    -0x238(%rbp),%eax
    7fd3e20e29cd:	41 89 87 f4 01 00 00 	mov    %eax,0x1f4(%r15)
    7fd3e20e29d4:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7fd3e20e29d7:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e29da:	0f 84 17 00 00 00    	je     0x7fd3e20e29f7
    7fd3e20e29e0:	41 c7 87 ec 01 00 00 	movl   $0x0,0x1ec(%r15)
    7fd3e20e29e7:	00 00 00 00 
    7fd3e20e29eb:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
    7fd3e20e29f2:	e9 1e 00 00 00       	jmpq   0x7fd3e20e2a15
    7fd3e20e29f7:	8b 85 d0 fd ff ff    	mov    -0x230(%rbp),%eax
    7fd3e20e29fd:	85 c0                	test   %eax,%eax
    7fd3e20e29ff:	0f 84 10 00 00 00    	je     0x7fd3e20e2a15
    7fd3e20e2a05:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
    7fd3e20e2a0b:	41 89 87 ec 01 00 00 	mov    %eax,0x1ec(%r15)
    7fd3e20e2a12:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7fd3e20e2a15:	45 85 ed             	test   %r13d,%r13d
    7fd3e20e2a18:	0f 84 22 00 00 00    	je     0x7fd3e20e2a40
    7fd3e20e2a1e:	41 c7 87 dc 01 00 00 	movl   $0x0,0x1dc(%r15)
    7fd3e20e2a25:	00 00 00 00 
    7fd3e20e2a29:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    7fd3e20e2a30:	41 c7 87 e4 01 00 00 	movl   $0x0,0x1e4(%r15)
    7fd3e20e2a37:	00 00 00 00 
    7fd3e20e2a3b:	e9 33 00 00 00       	jmpq   0x7fd3e20e2a73
    7fd3e20e2a40:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2a43:	0f 84 2a 00 00 00    	je     0x7fd3e20e2a73
    7fd3e20e2a49:	41 8b 87 e4 01 00 00 	mov    0x1e4(%r15),%eax
    7fd3e20e2a50:	8b c8                	mov    %eax,%ecx
    7fd3e20e2a52:	83 e1 01             	and    $0x1,%ecx
    7fd3e20e2a55:	41 89 8f dc 01 00 00 	mov    %ecx,0x1dc(%r15)
    7fd3e20e2a5c:	89 4d d8             	mov    %ecx,-0x28(%rbp)
    7fd3e20e2a5f:	d1 e8                	shr    %eax
    7fd3e20e2a61:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7fd3e20e2a67:	c1 e1 1f             	shl    $0x1f,%ecx
    7fd3e20e2a6a:	0b c1                	or     %ecx,%eax
    7fd3e20e2a6c:	41 89 87 e4 01 00 00 	mov    %eax,0x1e4(%r15)
    7fd3e20e2a73:	45 85 f6             	test   %r14d,%r14d
    7fd3e20e2a76:	0f 84 4e 00 00 00    	je     0x7fd3e20e2aca
    7fd3e20e2a7c:	8b 85 e0 fd ff ff    	mov    -0x220(%rbp),%eax
    7fd3e20e2a82:	41 89 87 d4 01 00 00 	mov    %eax,0x1d4(%r15)
    7fd3e20e2a89:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7fd3e20e2a8c:	41 8b 87 d0 01 00 00 	mov    0x1d0(%r15),%eax
    7fd3e20e2a93:	49 8b cf             	mov    %r15,%rcx
    7fd3e20e2a96:	48 81 c1 50 01 00 00 	add    $0x150,%rcx
    7fd3e20e2a9d:	8b d0                	mov    %eax,%edx
    7fd3e20e2a9f:	8b 14 91             	mov    (%rcx,%rdx,4),%edx
    7fd3e20e2aa2:	41 89 97 48 01 00 00 	mov    %edx,0x148(%r15)
    7fd3e20e2aa9:	89 55 e8             	mov    %edx,-0x18(%rbp)
    7fd3e20e2aac:	8b d0                	mov    %eax,%edx
    7fd3e20e2aae:	8b b5 f0 fd ff ff    	mov    -0x210(%rbp),%esi
    7fd3e20e2ab4:	89 34 91             	mov    %esi,(%rcx,%rdx,4)
    7fd3e20e2ab7:	ff c8                	dec    %eax
    7fd3e20e2ab9:	b9 1e 00 00 00       	mov    $0x1e,%ecx
    7fd3e20e2abe:	3b c1                	cmp    %ecx,%eax
    7fd3e20e2ac0:	0f 47 c1             	cmova  %ecx,%eax
    7fd3e20e2ac3:	41 89 87 d0 01 00 00 	mov    %eax,0x1d0(%r15)
    7fd3e20e2aca:	45 85 e4             	test   %r12d,%r12d
    7fd3e20e2acd:	0f 84 17 00 00 00    	je     0x7fd3e20e2aea
    7fd3e20e2ad3:	41 c7 87 40 01 00 00 	movl   $0x0,0x140(%r15)
    7fd3e20e2ada:	00 00 00 00 
    7fd3e20e2ade:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    7fd3e20e2ae5:	e9 1e 00 00 00       	jmpq   0x7fd3e20e2b08
    7fd3e20e2aea:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7fd3e20e2af0:	85 c0                	test   %eax,%eax
    7fd3e20e2af2:	0f 84 10 00 00 00    	je     0x7fd3e20e2b08
    7fd3e20e2af8:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7fd3e20e2afe:	41 89 87 40 01 00 00 	mov    %eax,0x140(%r15)
    7fd3e20e2b05:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7fd3e20e2b08:	8b c3                	mov    %ebx,%eax
    7fd3e20e2b0a:	c1 e8 02             	shr    $0x2,%eax
    7fd3e20e2b0d:	83 e0 01             	and    $0x1,%eax
    7fd3e20e2b10:	85 c0                	test   %eax,%eax
    7fd3e20e2b12:	0f 94 c0             	sete   %al
    7fd3e20e2b15:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e2b18:	48 8b 95 50 fe ff ff 	mov    -0x1b0(%rbp),%rdx
    7fd3e20e2b1f:	48 8b 4a 28          	mov    0x28(%rdx),%rcx
    7fd3e20e2b23:	89 01                	mov    %eax,(%rcx)
    7fd3e20e2b25:	48 8b 42 30          	mov    0x30(%rdx),%rax
    7fd3e20e2b29:	8b 8d 60 fe ff ff    	mov    -0x1a0(%rbp),%ecx
    7fd3e20e2b2f:	89 08                	mov    %ecx,(%rax)
    7fd3e20e2b31:	8b 85 68 fe ff ff    	mov    -0x198(%rbp),%eax
    7fd3e20e2b37:	83 e0 01             	and    $0x1,%eax
    7fd3e20e2b3a:	85 c0                	test   %eax,%eax
    7fd3e20e2b3c:	0f 94 c0             	sete   %al
    7fd3e20e2b3f:	0f b6 c0             	movzbl %al,%eax
    7fd3e20e2b42:	48 8b 52 38          	mov    0x38(%rdx),%rdx
    7fd3e20e2b46:	89 02                	mov    %eax,(%rdx)
    7fd3e20e2b48:	33 c0                	xor    %eax,%eax
    7fd3e20e2b4a:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fd3e20e2b4e:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fd3e20e2b53:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fd3e20e2b58:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fd3e20e2b5d:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fd3e20e2b62:	48 8b e5             	mov    %rbp,%rsp
    7fd3e20e2b65:	5d                   	pop    %rbp
    7fd3e20e2b66:	c3                   	retq   

end

