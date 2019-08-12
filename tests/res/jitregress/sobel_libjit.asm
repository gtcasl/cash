function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f7dba79812d <.text>:
    7f7dba79812d:	55                   	push   %rbp
    7f7dba79812e:	48 8b ec             	mov    %rsp,%rbp
    7f7dba798131:	48 81 ec 30 02 00 00 	sub    $0x230,%rsp
    7f7dba798138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f7dba79813c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f7dba798141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f7dba798146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f7dba79814b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f7dba798150:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    7f7dba798154:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    7f7dba798158:	4c 8b 78 08          	mov    0x8(%rax),%r15
    7f7dba79815c:	4c 8b 30             	mov    (%rax),%r14
    7f7dba79815f:	41 8b 07             	mov    (%r15),%eax
    7f7dba798162:	89 45 f0             	mov    %eax,-0x10(%rbp)
    7f7dba798165:	41 8b 47 4c          	mov    0x4c(%r15),%eax
    7f7dba798169:	89 45 e8             	mov    %eax,-0x18(%rbp)
    7f7dba79816c:	41 8b 87 98 00 00 00 	mov    0x98(%r15),%eax
    7f7dba798173:	89 45 e0             	mov    %eax,-0x20(%rbp)
    7f7dba798176:	41 8b 87 a0 00 00 00 	mov    0xa0(%r15),%eax
    7f7dba79817d:	89 45 d8             	mov    %eax,-0x28(%rbp)
    7f7dba798180:	45 8b af a8 00 00 00 	mov    0xa8(%r15),%r13d
    7f7dba798187:	41 8b 87 b0 00 00 00 	mov    0xb0(%r15),%eax
    7f7dba79818e:	89 45 d0             	mov    %eax,-0x30(%rbp)
    7f7dba798191:	41 8b 87 b8 00 00 00 	mov    0xb8(%r15),%eax
    7f7dba798198:	89 45 c8             	mov    %eax,-0x38(%rbp)
    7f7dba79819b:	41 8b 87 c0 00 00 00 	mov    0xc0(%r15),%eax
    7f7dba7981a2:	89 45 c0             	mov    %eax,-0x40(%rbp)
    7f7dba7981a5:	41 8b 87 c8 00 00 00 	mov    0xc8(%r15),%eax
    7f7dba7981ac:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f7dba7981af:	41 8b 87 d0 00 00 00 	mov    0xd0(%r15),%eax
    7f7dba7981b6:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f7dba7981b9:	41 8b 87 d8 00 00 00 	mov    0xd8(%r15),%eax
    7f7dba7981c0:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f7dba7981c3:	41 8b 87 e0 00 00 00 	mov    0xe0(%r15),%eax
    7f7dba7981ca:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f7dba7981cd:	41 8b 87 e8 00 00 00 	mov    0xe8(%r15),%eax
    7f7dba7981d4:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f7dba7981d7:	41 8b 87 f0 00 00 00 	mov    0xf0(%r15),%eax
    7f7dba7981de:	89 45 90             	mov    %eax,-0x70(%rbp)
    7f7dba7981e1:	41 8b 87 00 01 00 00 	mov    0x100(%r15),%eax
    7f7dba7981e8:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f7dba7981eb:	41 8b 87 08 01 00 00 	mov    0x108(%r15),%eax
    7f7dba7981f2:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f7dba7981f5:	41 8b 87 10 01 00 00 	mov    0x110(%r15),%eax
    7f7dba7981fc:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f7dba798202:	41 8b 87 18 01 00 00 	mov    0x118(%r15),%eax
    7f7dba798209:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f7dba79820f:	41 8b 87 20 01 00 00 	mov    0x120(%r15),%eax
    7f7dba798216:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f7dba79821c:	41 8b 87 28 01 00 00 	mov    0x128(%r15),%eax
    7f7dba798223:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f7dba798229:	49 8b 46 18          	mov    0x18(%r14),%rax
    7f7dba79822d:	8b 00                	mov    (%rax),%eax
    7f7dba79822f:	41 8b 8f 30 01 00 00 	mov    0x130(%r15),%ecx
    7f7dba798236:	33 c8                	xor    %eax,%ecx
    7f7dba798238:	23 c8                	and    %eax,%ecx
    7f7dba79823a:	41 89 87 30 01 00 00 	mov    %eax,0x130(%r15)
    7f7dba798241:	85 c9                	test   %ecx,%ecx
    7f7dba798243:	0f 84 2e 07 00 00    	je     0x7f7dba798977
    7f7dba798249:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7f7dba79824c:	81 f9 00 10 00 00    	cmp    $0x1000,%ecx
    7f7dba798252:	0f 92 c0             	setb   %al
    7f7dba798255:	0f b6 c0             	movzbl %al,%eax
    7f7dba798258:	85 c0                	test   %eax,%eax
    7f7dba79825a:	0f 94 c0             	sete   %al
    7f7dba79825d:	0f b6 c0             	movzbl %al,%eax
    7f7dba798260:	85 c0                	test   %eax,%eax
    7f7dba798262:	0f 94 c0             	sete   %al
    7f7dba798265:	0f b6 c0             	movzbl %al,%eax
    7f7dba798268:	8b 55 88             	mov    -0x78(%rbp),%edx
    7f7dba79826b:	83 e2 01             	and    $0x1,%edx
    7f7dba79826e:	85 d2                	test   %edx,%edx
    7f7dba798270:	0f 94 c2             	sete   %dl
    7f7dba798273:	0f b6 d2             	movzbl %dl,%edx
    7f7dba798276:	89 95 58 ff ff ff    	mov    %edx,-0xa8(%rbp)
    7f7dba79827c:	85 d2                	test   %edx,%edx
    7f7dba79827e:	0f 94 c2             	sete   %dl
    7f7dba798281:	0f b6 d2             	movzbl %dl,%edx
    7f7dba798284:	23 c2                	and    %edx,%eax
    7f7dba798286:	85 c0                	test   %eax,%eax
    7f7dba798288:	0f 94 c0             	sete   %al
    7f7dba79828b:	0f b6 c0             	movzbl %al,%eax
    7f7dba79828e:	81 f9 87 00 00 00    	cmp    $0x87,%ecx
    7f7dba798294:	0f 93 c2             	setae  %dl
    7f7dba798297:	0f b6 d2             	movzbl %dl,%edx
    7f7dba79829a:	8b 75 98             	mov    -0x68(%rbp),%esi
    7f7dba79829d:	85 f6                	test   %esi,%esi
    7f7dba79829f:	40 0f 94 c6          	sete   %sil
    7f7dba7982a3:	40 0f b6 f6          	movzbl %sil,%esi
    7f7dba7982a7:	23 d6                	and    %esi,%edx
    7f7dba7982a9:	23 d0                	and    %eax,%edx
    7f7dba7982ab:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7f7dba7982b1:	c1 ee 02             	shr    $0x2,%esi
    7f7dba7982b4:	83 e6 01             	and    $0x1,%esi
    7f7dba7982b7:	85 f6                	test   %esi,%esi
    7f7dba7982b9:	40 0f 94 c6          	sete   %sil
    7f7dba7982bd:	40 0f b6 f6          	movzbl %sil,%esi
    7f7dba7982c1:	89 b5 50 ff ff ff    	mov    %esi,-0xb0(%rbp)
    7f7dba7982c7:	85 f6                	test   %esi,%esi
    7f7dba7982c9:	40 0f 94 c6          	sete   %sil
    7f7dba7982cd:	40 0f b6 f6          	movzbl %sil,%esi
    7f7dba7982d1:	89 95 48 ff ff ff    	mov    %edx,-0xb8(%rbp)
    7f7dba7982d7:	23 d6                	and    %esi,%edx
    7f7dba7982d9:	85 d2                	test   %edx,%edx
    7f7dba7982db:	0f 94 c2             	sete   %dl
    7f7dba7982de:	0f b6 d2             	movzbl %dl,%edx
    7f7dba7982e1:	89 95 40 ff ff ff    	mov    %edx,-0xc0(%rbp)
    7f7dba7982e7:	23 c2                	and    %edx,%eax
    7f7dba7982e9:	89 85 38 ff ff ff    	mov    %eax,-0xc8(%rbp)
    7f7dba7982ef:	81 f9 fe ff ff ff    	cmp    $0xfffffffe,%ecx
    7f7dba7982f5:	0f 93 c0             	setae  %al
    7f7dba7982f8:	0f b6 c0             	movzbl %al,%eax
    7f7dba7982fb:	81 e9 fe ff ff ff    	sub    $0xfffffffe,%ecx
    7f7dba798301:	89 8d 30 ff ff ff    	mov    %ecx,-0xd0(%rbp)
    7f7dba798307:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7f7dba79830a:	ff c1                	inc    %ecx
    7f7dba79830c:	89 8d 28 ff ff ff    	mov    %ecx,-0xd8(%rbp)
    7f7dba798312:	85 c0                	test   %eax,%eax
    7f7dba798314:	0f 85 0c 00 00 00    	jne    0x7f7dba798326
    7f7dba79831a:	8b 85 28 ff ff ff    	mov    -0xd8(%rbp),%eax
    7f7dba798320:	89 85 30 ff ff ff    	mov    %eax,-0xd0(%rbp)
    7f7dba798326:	49 8b 46 20          	mov    0x20(%r14),%rax
    7f7dba79832a:	8b 00                	mov    (%rax),%eax
    7f7dba79832c:	89 85 20 ff ff ff    	mov    %eax,-0xe0(%rbp)
    7f7dba798332:	83 c8 00             	or     $0x0,%eax
    7f7dba798335:	89 85 18 ff ff ff    	mov    %eax,-0xe8(%rbp)
    7f7dba79833b:	8b 45 a0             	mov    -0x60(%rbp),%eax
    7f7dba79833e:	3d 04 10 00 00       	cmp    $0x1004,%eax
    7f7dba798343:	0f 97 c0             	seta   %al
    7f7dba798346:	0f b6 c0             	movzbl %al,%eax
    7f7dba798349:	89 85 10 ff ff ff    	mov    %eax,-0xf0(%rbp)
    7f7dba79834f:	41 8b c5             	mov    %r13d,%eax
    7f7dba798352:	03 45 a8             	add    -0x58(%rbp),%eax
    7f7dba798355:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f7dba79835a:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f7dba79835d:	d1 e1                	shl    %ecx
    7f7dba79835f:	89 8d 08 ff ff ff    	mov    %ecx,-0xf8(%rbp)
    7f7dba798365:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7f7dba79836b:	89 85 00 ff ff ff    	mov    %eax,-0x100(%rbp)
    7f7dba798371:	03 c1                	add    %ecx,%eax
    7f7dba798373:	25 ff 03 00 00       	and    $0x3ff,%eax
    7f7dba798378:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7f7dba79837b:	03 4d b8             	add    -0x48(%rbp),%ecx
    7f7dba79837e:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7f7dba798384:	8b 55 d0             	mov    -0x30(%rbp),%edx
    7f7dba798387:	d1 e2                	shl    %edx
    7f7dba798389:	89 95 f8 fe ff ff    	mov    %edx,-0x108(%rbp)
    7f7dba79838f:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7f7dba798395:	89 8d f0 fe ff ff    	mov    %ecx,-0x110(%rbp)
    7f7dba79839b:	03 ca                	add    %edx,%ecx
    7f7dba79839d:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7f7dba7983a3:	3b c1                	cmp    %ecx,%eax
    7f7dba7983a5:	0f 97 c2             	seta   %dl
    7f7dba7983a8:	0f b6 d2             	movzbl %dl,%edx
    7f7dba7983ab:	8b f0                	mov    %eax,%esi
    7f7dba7983ad:	2b f1                	sub    %ecx,%esi
    7f7dba7983af:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7f7dba7983b5:	89 b5 e8 fe ff ff    	mov    %esi,-0x118(%rbp)
    7f7dba7983bb:	89 85 e0 fe ff ff    	mov    %eax,-0x120(%rbp)
    7f7dba7983c1:	2b c8                	sub    %eax,%ecx
    7f7dba7983c3:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7f7dba7983c9:	89 8d d8 fe ff ff    	mov    %ecx,-0x128(%rbp)
    7f7dba7983cf:	85 d2                	test   %edx,%edx
    7f7dba7983d1:	0f 85 0c 00 00 00    	jne    0x7f7dba7983e3
    7f7dba7983d7:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    7f7dba7983dd:	89 85 e8 fe ff ff    	mov    %eax,-0x118(%rbp)
    7f7dba7983e3:	8b 45 b8             	mov    -0x48(%rbp),%eax
    7f7dba7983e6:	03 45 a8             	add    -0x58(%rbp),%eax
    7f7dba7983e9:	25 ff 01 00 00       	and    $0x1ff,%eax
    7f7dba7983ee:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7f7dba7983f1:	d1 e1                	shl    %ecx
    7f7dba7983f3:	89 8d d0 fe ff ff    	mov    %ecx,-0x130(%rbp)
    7f7dba7983f9:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7f7dba7983ff:	89 85 c8 fe ff ff    	mov    %eax,-0x138(%rbp)
    7f7dba798405:	03 c1                	add    %ecx,%eax
    7f7dba798407:	25 ff 03 00 00       	and    $0x3ff,%eax
    7f7dba79840c:	8b 4d e0             	mov    -0x20(%rbp),%ecx
    7f7dba79840f:	41 03 cd             	add    %r13d,%ecx
    7f7dba798412:	81 e1 ff 01 00 00    	and    $0x1ff,%ecx
    7f7dba798418:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7f7dba79841b:	d1 e2                	shl    %edx
    7f7dba79841d:	89 95 c0 fe ff ff    	mov    %edx,-0x140(%rbp)
    7f7dba798423:	81 e2 ff 01 00 00    	and    $0x1ff,%edx
    7f7dba798429:	89 8d b8 fe ff ff    	mov    %ecx,-0x148(%rbp)
    7f7dba79842f:	03 ca                	add    %edx,%ecx
    7f7dba798431:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7f7dba798437:	3b c1                	cmp    %ecx,%eax
    7f7dba798439:	0f 97 c2             	seta   %dl
    7f7dba79843c:	0f b6 d2             	movzbl %dl,%edx
    7f7dba79843f:	8b f0                	mov    %eax,%esi
    7f7dba798441:	2b f1                	sub    %ecx,%esi
    7f7dba798443:	81 e6 ff 03 00 00    	and    $0x3ff,%esi
    7f7dba798449:	89 b5 b0 fe ff ff    	mov    %esi,-0x150(%rbp)
    7f7dba79844f:	89 85 a8 fe ff ff    	mov    %eax,-0x158(%rbp)
    7f7dba798455:	2b c8                	sub    %eax,%ecx
    7f7dba798457:	81 e1 ff 03 00 00    	and    $0x3ff,%ecx
    7f7dba79845d:	89 8d a0 fe ff ff    	mov    %ecx,-0x160(%rbp)
    7f7dba798463:	85 d2                	test   %edx,%edx
    7f7dba798465:	0f 85 0c 00 00 00    	jne    0x7f7dba798477
    7f7dba79846b:	8b 85 a0 fe ff ff    	mov    -0x160(%rbp),%eax
    7f7dba798471:	89 85 b0 fe ff ff    	mov    %eax,-0x150(%rbp)
    7f7dba798477:	8b 85 e8 fe ff ff    	mov    -0x118(%rbp),%eax
    7f7dba79847d:	03 85 b0 fe ff ff    	add    -0x150(%rbp),%eax
    7f7dba798483:	25 ff 07 00 00       	and    $0x7ff,%eax
    7f7dba798488:	3d ff 00 00 00       	cmp    $0xff,%eax
    7f7dba79848d:	0f 92 c1             	setb   %cl
    7f7dba798490:	0f b6 c9             	movzbl %cl,%ecx
    7f7dba798493:	25 ff 00 00 00       	and    $0xff,%eax
    7f7dba798498:	89 85 98 fe ff ff    	mov    %eax,-0x168(%rbp)
    7f7dba79849e:	85 c9                	test   %ecx,%ecx
    7f7dba7984a0:	0f 85 0a 00 00 00    	jne    0x7f7dba7984b0
    7f7dba7984a6:	c7 85 98 fe ff ff ff 	movl   $0xff,-0x168(%rbp)
    7f7dba7984ad:	00 00 00 
    7f7dba7984b0:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f7dba7984b3:	c1 e8 02             	shr    $0x2,%eax
    7f7dba7984b6:	83 e0 01             	and    $0x1,%eax
    7f7dba7984b9:	85 c0                	test   %eax,%eax
    7f7dba7984bb:	0f 94 c0             	sete   %al
    7f7dba7984be:	0f b6 c0             	movzbl %al,%eax
    7f7dba7984c1:	49 8b 4e 08          	mov    0x8(%r14),%rcx
    7f7dba7984c5:	8b 09                	mov    (%rcx),%ecx
    7f7dba7984c7:	23 c1                	and    %ecx,%eax
    7f7dba7984c9:	8b 8d 58 ff ff ff    	mov    -0xa8(%rbp),%ecx
    7f7dba7984cf:	23 8d 40 ff ff ff    	and    -0xc0(%rbp),%ecx
    7f7dba7984d5:	85 c9                	test   %ecx,%ecx
    7f7dba7984d7:	0f 94 c2             	sete   %dl
    7f7dba7984da:	0f b6 d2             	movzbl %dl,%edx
    7f7dba7984dd:	89 95 90 fe ff ff    	mov    %edx,-0x170(%rbp)
    7f7dba7984e3:	23 d0                	and    %eax,%edx
    7f7dba7984e5:	8b 75 88             	mov    -0x78(%rbp),%esi
    7f7dba7984e8:	83 e6 03             	and    $0x3,%esi
    7f7dba7984eb:	d1 e6                	shl    %esi
    7f7dba7984ed:	89 b5 88 fe ff ff    	mov    %esi,-0x178(%rbp)
    7f7dba7984f3:	89 85 80 fe ff ff    	mov    %eax,-0x180(%rbp)
    7f7dba7984f9:	85 c0                	test   %eax,%eax
    7f7dba7984fb:	0f 94 c0             	sete   %al
    7f7dba7984fe:	0f b6 c0             	movzbl %al,%eax
    7f7dba798501:	89 8d 78 fe ff ff    	mov    %ecx,-0x188(%rbp)
    7f7dba798507:	23 c8                	and    %eax,%ecx
    7f7dba798509:	89 8d 70 fe ff ff    	mov    %ecx,-0x190(%rbp)
    7f7dba79850f:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f7dba798512:	d1 e8                	shr    %eax
    7f7dba798514:	83 e0 03             	and    $0x3,%eax
    7f7dba798517:	89 85 68 fe ff ff    	mov    %eax,-0x198(%rbp)
    7f7dba79851d:	85 d2                	test   %edx,%edx
    7f7dba79851f:	0f 85 16 00 00 00    	jne    0x7f7dba79853b
    7f7dba798525:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f7dba79852b:	85 c0                	test   %eax,%eax
    7f7dba79852d:	0f 85 13 00 00 00    	jne    0x7f7dba798546
    7f7dba798533:	8b 5d 88             	mov    -0x78(%rbp),%ebx
    7f7dba798536:	e9 11 00 00 00       	jmpq   0x7f7dba79854c
    7f7dba79853b:	8b 9d 88 fe ff ff    	mov    -0x178(%rbp),%ebx
    7f7dba798541:	e9 06 00 00 00       	jmpq   0x7f7dba79854c
    7f7dba798546:	8b 9d 68 fe ff ff    	mov    -0x198(%rbp),%ebx
    7f7dba79854c:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f7dba79854f:	d1 e8                	shr    %eax
    7f7dba798551:	83 e0 01             	and    $0x1,%eax
    7f7dba798554:	89 85 60 fe ff ff    	mov    %eax,-0x1a0(%rbp)
    7f7dba79855a:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7f7dba798560:	0b c1                	or     %ecx,%eax
    7f7dba798562:	49 8b 0e             	mov    (%r14),%rcx
    7f7dba798565:	8b 09                	mov    (%rcx),%ecx
    7f7dba798567:	89 8d 58 fe ff ff    	mov    %ecx,-0x1a8(%rbp)
    7f7dba79856d:	89 8d 50 fe ff ff    	mov    %ecx,-0x1b0(%rbp)
    7f7dba798573:	85 c0                	test   %eax,%eax
    7f7dba798575:	0f 85 0c 00 00 00    	jne    0x7f7dba798587
    7f7dba79857b:	8b 85 78 ff ff ff    	mov    -0x88(%rbp),%eax
    7f7dba798581:	89 85 50 fe ff ff    	mov    %eax,-0x1b0(%rbp)
    7f7dba798587:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f7dba79858a:	83 e0 01             	and    $0x1,%eax
    7f7dba79858d:	8b 8d 80 fe ff ff    	mov    -0x180(%rbp),%ecx
    7f7dba798593:	23 c1                	and    %ecx,%eax
    7f7dba798595:	8b 95 78 fe ff ff    	mov    -0x188(%rbp),%edx
    7f7dba79859b:	0b c2                	or     %edx,%eax
    7f7dba79859d:	89 85 48 fe ff ff    	mov    %eax,-0x1b8(%rbp)
    7f7dba7985a3:	23 8d 60 fe ff ff    	and    -0x1a0(%rbp),%ecx
    7f7dba7985a9:	0b d1                	or     %ecx,%edx
    7f7dba7985ab:	89 95 40 fe ff ff    	mov    %edx,-0x1c0(%rbp)
    7f7dba7985b1:	8b 85 50 ff ff ff    	mov    -0xb0(%rbp),%eax
    7f7dba7985b7:	23 85 48 ff ff ff    	and    -0xb8(%rbp),%eax
    7f7dba7985bd:	8b 8d 70 ff ff ff    	mov    -0x90(%rbp),%ecx
    7f7dba7985c3:	83 e1 01             	and    $0x1,%ecx
    7f7dba7985c6:	85 c9                	test   %ecx,%ecx
    7f7dba7985c8:	0f 94 c1             	sete   %cl
    7f7dba7985cb:	0f b6 c9             	movzbl %cl,%ecx
    7f7dba7985ce:	49 8b 56 10          	mov    0x10(%r14),%rdx
    7f7dba7985d2:	8b 12                	mov    (%rdx),%edx
    7f7dba7985d4:	23 ca                	and    %edx,%ecx
    7f7dba7985d6:	85 c9                	test   %ecx,%ecx
    7f7dba7985d8:	0f 94 c2             	sete   %dl
    7f7dba7985db:	0f b6 d2             	movzbl %dl,%edx
    7f7dba7985de:	89 95 38 fe ff ff    	mov    %edx,-0x1c8(%rbp)
    7f7dba7985e4:	23 d0                	and    %eax,%edx
    7f7dba7985e6:	8b b5 70 ff ff ff    	mov    -0x90(%rbp),%esi
    7f7dba7985ec:	83 e6 03             	and    $0x3,%esi
    7f7dba7985ef:	d1 e6                	shl    %esi
    7f7dba7985f1:	89 b5 30 fe ff ff    	mov    %esi,-0x1d0(%rbp)
    7f7dba7985f7:	89 85 28 fe ff ff    	mov    %eax,-0x1d8(%rbp)
    7f7dba7985fd:	85 c0                	test   %eax,%eax
    7f7dba7985ff:	0f 94 c0             	sete   %al
    7f7dba798602:	0f b6 c0             	movzbl %al,%eax
    7f7dba798605:	89 8d 20 fe ff ff    	mov    %ecx,-0x1e0(%rbp)
    7f7dba79860b:	23 c8                	and    %eax,%ecx
    7f7dba79860d:	89 8d 18 fe ff ff    	mov    %ecx,-0x1e8(%rbp)
    7f7dba798613:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f7dba798619:	d1 e8                	shr    %eax
    7f7dba79861b:	83 e0 03             	and    $0x3,%eax
    7f7dba79861e:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7f7dba798624:	85 d2                	test   %edx,%edx
    7f7dba798626:	0f 85 1a 00 00 00    	jne    0x7f7dba798646
    7f7dba79862c:	8b 85 18 fe ff ff    	mov    -0x1e8(%rbp),%eax
    7f7dba798632:	85 c0                	test   %eax,%eax
    7f7dba798634:	0f 85 18 00 00 00    	jne    0x7f7dba798652
    7f7dba79863a:	44 8b a5 70 ff ff ff 	mov    -0x90(%rbp),%r12d
    7f7dba798641:	e9 13 00 00 00       	jmpq   0x7f7dba798659
    7f7dba798646:	44 8b a5 30 fe ff ff 	mov    -0x1d0(%rbp),%r12d
    7f7dba79864d:	e9 07 00 00 00       	jmpq   0x7f7dba798659
    7f7dba798652:	44 8b a5 10 fe ff ff 	mov    -0x1f0(%rbp),%r12d
    7f7dba798659:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f7dba79865f:	d1 e8                	shr    %eax
    7f7dba798661:	83 e0 01             	and    $0x1,%eax
    7f7dba798664:	89 85 08 fe ff ff    	mov    %eax,-0x1f8(%rbp)
    7f7dba79866a:	8b 8d 38 fe ff ff    	mov    -0x1c8(%rbp),%ecx
    7f7dba798670:	0b c1                	or     %ecx,%eax
    7f7dba798672:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7f7dba798675:	89 8d 00 fe ff ff    	mov    %ecx,-0x200(%rbp)
    7f7dba79867b:	85 c0                	test   %eax,%eax
    7f7dba79867d:	0f 85 0c 00 00 00    	jne    0x7f7dba79868f
    7f7dba798683:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f7dba798689:	89 85 00 fe ff ff    	mov    %eax,-0x200(%rbp)
    7f7dba79868f:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f7dba798695:	83 e0 01             	and    $0x1,%eax
    7f7dba798698:	8b 8d 28 fe ff ff    	mov    -0x1d8(%rbp),%ecx
    7f7dba79869e:	23 c1                	and    %ecx,%eax
    7f7dba7986a0:	8b 95 20 fe ff ff    	mov    -0x1e0(%rbp),%edx
    7f7dba7986a6:	0b c2                	or     %edx,%eax
    7f7dba7986a8:	89 85 f8 fd ff ff    	mov    %eax,-0x208(%rbp)
    7f7dba7986ae:	23 8d 08 fe ff ff    	and    -0x1f8(%rbp),%ecx
    7f7dba7986b4:	0b d1                	or     %ecx,%edx
    7f7dba7986b6:	85 d2                	test   %edx,%edx
    7f7dba7986b8:	0f 84 10 00 00 00    	je     0x7f7dba7986ce
    7f7dba7986be:	8b 45 90             	mov    -0x70(%rbp),%eax
    7f7dba7986c1:	41 89 87 28 01 00 00 	mov    %eax,0x128(%r15)
    7f7dba7986c8:	89 85 60 ff ff ff    	mov    %eax,-0xa0(%rbp)
    7f7dba7986ce:	8b 85 f8 fd ff ff    	mov    -0x208(%rbp),%eax
    7f7dba7986d4:	85 c0                	test   %eax,%eax
    7f7dba7986d6:	0f 84 13 00 00 00    	je     0x7f7dba7986ef
    7f7dba7986dc:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7f7dba7986e2:	41 89 87 20 01 00 00 	mov    %eax,0x120(%r15)
    7f7dba7986e9:	89 85 68 ff ff ff    	mov    %eax,-0x98(%rbp)
    7f7dba7986ef:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f7dba7986f5:	85 c0                	test   %eax,%eax
    7f7dba7986f7:	0f 84 1a 00 00 00    	je     0x7f7dba798717
    7f7dba7986fd:	41 c7 87 18 01 00 00 	movl   $0x1,0x118(%r15)
    7f7dba798704:	01 00 00 00 
    7f7dba798708:	c7 85 70 ff ff ff 01 	movl   $0x1,-0x90(%rbp)
    7f7dba79870f:	00 00 00 
    7f7dba798712:	e9 10 00 00 00       	jmpq   0x7f7dba798727
    7f7dba798717:	45 89 a7 18 01 00 00 	mov    %r12d,0x118(%r15)
    7f7dba79871e:	41 8b c4             	mov    %r12d,%eax
    7f7dba798721:	89 85 70 ff ff ff    	mov    %eax,-0x90(%rbp)
    7f7dba798727:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7f7dba79872d:	85 c0                	test   %eax,%eax
    7f7dba79872f:	0f 84 13 00 00 00    	je     0x7f7dba798748
    7f7dba798735:	8b 85 58 fe ff ff    	mov    -0x1a8(%rbp),%eax
    7f7dba79873b:	41 89 87 10 01 00 00 	mov    %eax,0x110(%r15)
    7f7dba798742:	89 85 78 ff ff ff    	mov    %eax,-0x88(%rbp)
    7f7dba798748:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f7dba79874e:	85 c0                	test   %eax,%eax
    7f7dba798750:	0f 84 17 00 00 00    	je     0x7f7dba79876d
    7f7dba798756:	41 c7 87 00 01 00 00 	movl   $0x1,0x100(%r15)
    7f7dba79875d:	01 00 00 00 
    7f7dba798761:	c7 45 88 01 00 00 00 	movl   $0x1,-0x78(%rbp)
    7f7dba798768:	e9 0c 00 00 00       	jmpq   0x7f7dba798779
    7f7dba79876d:	41 89 9f 00 01 00 00 	mov    %ebx,0x100(%r15)
    7f7dba798774:	8b c3                	mov    %ebx,%eax
    7f7dba798776:	89 45 88             	mov    %eax,-0x78(%rbp)
    7f7dba798779:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f7dba79877f:	85 c0                	test   %eax,%eax
    7f7dba798781:	0f 84 2e 00 00 00    	je     0x7f7dba7987b5
    7f7dba798787:	41 8b 87 f8 00 00 00 	mov    0xf8(%r15),%eax
    7f7dba79878e:	8b c8                	mov    %eax,%ecx
    7f7dba798790:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f7dba798796:	41 89 8f f0 00 00 00 	mov    %ecx,0xf0(%r15)
    7f7dba79879d:	89 4d 90             	mov    %ecx,-0x70(%rbp)
    7f7dba7987a0:	c1 e8 08             	shr    $0x8,%eax
    7f7dba7987a3:	8b 8d 98 fe ff ff    	mov    -0x168(%rbp),%ecx
    7f7dba7987a9:	c1 e1 10             	shl    $0x10,%ecx
    7f7dba7987ac:	0b c1                	or     %ecx,%eax
    7f7dba7987ae:	41 89 87 f8 00 00 00 	mov    %eax,0xf8(%r15)
    7f7dba7987b5:	8b 85 20 ff ff ff    	mov    -0xe0(%rbp),%eax
    7f7dba7987bb:	85 c0                	test   %eax,%eax
    7f7dba7987bd:	0f 84 17 00 00 00    	je     0x7f7dba7987da
    7f7dba7987c3:	41 c7 87 e8 00 00 00 	movl   $0x0,0xe8(%r15)
    7f7dba7987ca:	00 00 00 00 
    7f7dba7987ce:	c7 45 98 00 00 00 00 	movl   $0x0,-0x68(%rbp)
    7f7dba7987d5:	e9 10 00 00 00       	jmpq   0x7f7dba7987ea
    7f7dba7987da:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f7dba7987e0:	41 89 87 e8 00 00 00 	mov    %eax,0xe8(%r15)
    7f7dba7987e7:	89 45 98             	mov    %eax,-0x68(%rbp)
    7f7dba7987ea:	8b 85 18 ff ff ff    	mov    -0xe8(%rbp),%eax
    7f7dba7987f0:	85 c0                	test   %eax,%eax
    7f7dba7987f2:	0f 84 17 00 00 00    	je     0x7f7dba79880f
    7f7dba7987f8:	41 c7 87 e0 00 00 00 	movl   $0x0,0xe0(%r15)
    7f7dba7987ff:	00 00 00 00 
    7f7dba798803:	c7 45 a0 00 00 00 00 	movl   $0x0,-0x60(%rbp)
    7f7dba79880a:	e9 1e 00 00 00       	jmpq   0x7f7dba79882d
    7f7dba79880f:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f7dba798815:	85 c0                	test   %eax,%eax
    7f7dba798817:	0f 84 10 00 00 00    	je     0x7f7dba79882d
    7f7dba79881d:	8b 85 30 ff ff ff    	mov    -0xd0(%rbp),%eax
    7f7dba798823:	41 89 87 e0 00 00 00 	mov    %eax,0xe0(%r15)
    7f7dba79882a:	89 45 a0             	mov    %eax,-0x60(%rbp)
    7f7dba79882d:	8b 85 38 ff ff ff    	mov    -0xc8(%rbp),%eax
    7f7dba798833:	85 c0                	test   %eax,%eax
    7f7dba798835:	0f 84 db 00 00 00    	je     0x7f7dba798916
    7f7dba79883b:	8b 45 b0             	mov    -0x50(%rbp),%eax
    7f7dba79883e:	41 89 87 c8 00 00 00 	mov    %eax,0xc8(%r15)
    7f7dba798845:	89 45 b8             	mov    %eax,-0x48(%rbp)
    7f7dba798848:	8b 45 a8             	mov    -0x58(%rbp),%eax
    7f7dba79884b:	41 89 87 d0 00 00 00 	mov    %eax,0xd0(%r15)
    7f7dba798852:	89 45 b0             	mov    %eax,-0x50(%rbp)
    7f7dba798855:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f7dba798858:	41 89 87 d8 00 00 00 	mov    %eax,0xd8(%r15)
    7f7dba79885f:	89 45 a8             	mov    %eax,-0x58(%rbp)
    7f7dba798862:	8b 4d c8             	mov    -0x38(%rbp),%ecx
    7f7dba798865:	41 89 8f b0 00 00 00 	mov    %ecx,0xb0(%r15)
    7f7dba79886c:	89 4d d0             	mov    %ecx,-0x30(%rbp)
    7f7dba79886f:	8b 4d c0             	mov    -0x40(%rbp),%ecx
    7f7dba798872:	41 89 8f b8 00 00 00 	mov    %ecx,0xb8(%r15)
    7f7dba798879:	89 4d c8             	mov    %ecx,-0x38(%rbp)
    7f7dba79887c:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    7f7dba79887f:	41 89 8f c0 00 00 00 	mov    %ecx,0xc0(%r15)
    7f7dba798886:	89 4d c0             	mov    %ecx,-0x40(%rbp)
    7f7dba798889:	8b 55 d8             	mov    -0x28(%rbp),%edx
    7f7dba79888c:	41 89 97 98 00 00 00 	mov    %edx,0x98(%r15)
    7f7dba798893:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7f7dba798896:	45 89 af a0 00 00 00 	mov    %r13d,0xa0(%r15)
    7f7dba79889d:	41 8b d5             	mov    %r13d,%edx
    7f7dba7988a0:	89 55 d8             	mov    %edx,-0x28(%rbp)
    7f7dba7988a3:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f7dba7988a6:	41 89 97 a8 00 00 00 	mov    %edx,0xa8(%r15)
    7f7dba7988ad:	4c 8b ea             	mov    %rdx,%r13
    7f7dba7988b0:	41 8b 97 94 00 00 00 	mov    0x94(%r15),%edx
    7f7dba7988b7:	49 8b f7             	mov    %r15,%rsi
    7f7dba7988ba:	48 83 c6 54          	add    $0x54,%rsi
    7f7dba7988be:	8b fa                	mov    %edx,%edi
    7f7dba7988c0:	0f b6 3c 3e          	movzbl (%rsi,%rdi,1),%edi
    7f7dba7988c4:	41 89 7f 4c          	mov    %edi,0x4c(%r15)
    7f7dba7988c8:	89 7d e8             	mov    %edi,-0x18(%rbp)
    7f7dba7988cb:	0f b6 c9             	movzbl %cl,%ecx
    7f7dba7988ce:	8b fa                	mov    %edx,%edi
    7f7dba7988d0:	40 88 0c 3e          	mov    %cl,(%rsi,%rdi,1)
    7f7dba7988d4:	ff ca                	dec    %edx
    7f7dba7988d6:	b9 3e 00 00 00       	mov    $0x3e,%ecx
    7f7dba7988db:	3b d1                	cmp    %ecx,%edx
    7f7dba7988dd:	0f 47 d1             	cmova  %ecx,%edx
    7f7dba7988e0:	41 89 97 94 00 00 00 	mov    %edx,0x94(%r15)
    7f7dba7988e7:	41 8b 4f 48          	mov    0x48(%r15),%ecx
    7f7dba7988eb:	49 8b d7             	mov    %r15,%rdx
    7f7dba7988ee:	48 83 c2 08          	add    $0x8,%rdx
    7f7dba7988f2:	8b f1                	mov    %ecx,%esi
    7f7dba7988f4:	0f b6 34 32          	movzbl (%rdx,%rsi,1),%esi
    7f7dba7988f8:	41 89 37             	mov    %esi,(%r15)
    7f7dba7988fb:	89 75 f0             	mov    %esi,-0x10(%rbp)
    7f7dba7988fe:	0f b6 c0             	movzbl %al,%eax
    7f7dba798901:	8b f1                	mov    %ecx,%esi
    7f7dba798903:	88 04 32             	mov    %al,(%rdx,%rsi,1)
    7f7dba798906:	ff c9                	dec    %ecx
    7f7dba798908:	b8 3e 00 00 00       	mov    $0x3e,%eax
    7f7dba79890d:	3b c8                	cmp    %eax,%ecx
    7f7dba79890f:	0f 47 c8             	cmova  %eax,%ecx
    7f7dba798912:	41 89 4f 48          	mov    %ecx,0x48(%r15)
    7f7dba798916:	8b 85 48 fe ff ff    	mov    -0x1b8(%rbp),%eax
    7f7dba79891c:	85 c0                	test   %eax,%eax
    7f7dba79891e:	0f 84 10 00 00 00    	je     0x7f7dba798934
    7f7dba798924:	8b 85 50 fe ff ff    	mov    -0x1b0(%rbp),%eax
    7f7dba79892a:	41 89 87 08 01 00 00 	mov    %eax,0x108(%r15)
    7f7dba798931:	89 45 80             	mov    %eax,-0x80(%rbp)
    7f7dba798934:	8b 45 88             	mov    -0x78(%rbp),%eax
    7f7dba798937:	c1 e8 02             	shr    $0x2,%eax
    7f7dba79893a:	83 e0 01             	and    $0x1,%eax
    7f7dba79893d:	85 c0                	test   %eax,%eax
    7f7dba79893f:	0f 94 c0             	sete   %al
    7f7dba798942:	0f b6 c0             	movzbl %al,%eax
    7f7dba798945:	49 8b 4e 28          	mov    0x28(%r14),%rcx
    7f7dba798949:	89 01                	mov    %eax,(%rcx)
    7f7dba79894b:	49 8b 46 30          	mov    0x30(%r14),%rax
    7f7dba79894f:	8b 8d 68 ff ff ff    	mov    -0x98(%rbp),%ecx
    7f7dba798955:	89 08                	mov    %ecx,(%rax)
    7f7dba798957:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f7dba79895d:	83 e0 01             	and    $0x1,%eax
    7f7dba798960:	85 c0                	test   %eax,%eax
    7f7dba798962:	0f 94 c0             	sete   %al
    7f7dba798965:	0f b6 c0             	movzbl %al,%eax
    7f7dba798968:	49 8b 4e 38          	mov    0x38(%r14),%rcx
    7f7dba79896c:	89 01                	mov    %eax,(%rcx)
    7f7dba79896e:	49 8b 46 40          	mov    0x40(%r14),%rax
    7f7dba798972:	8b 4d 98             	mov    -0x68(%rbp),%ecx
    7f7dba798975:	89 08                	mov    %ecx,(%rax)
    7f7dba798977:	33 c0                	xor    %eax,%eax
    7f7dba798979:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f7dba79897d:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f7dba798982:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f7dba798987:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f7dba79898c:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f7dba798991:	48 8b e5             	mov    %rbp,%rsp
    7f7dba798994:	5d                   	pop    %rbp
    7f7dba798995:	c3                   	retq   

end

