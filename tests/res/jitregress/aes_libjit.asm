function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fa13499712d <.text>:
    7fa13499712d:	55                   	push   %rbp
    7fa13499712e:	48 8b ec             	mov    %rsp,%rbp
    7fa134997131:	48 81 ec 60 09 00 00 	sub    $0x960,%rsp
    7fa134997138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fa13499713c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fa134997141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fa134997146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fa13499714b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fa134997150:	4c 8b e7             	mov    %rdi,%r12
    7fa134997153:	4d 8b 7c 24 08       	mov    0x8(%r12),%r15
    7fa134997158:	4d 8b 34 24          	mov    (%r12),%r14
    7fa13499715c:	45 8b af b0 01 00 00 	mov    0x1b0(%r15),%r13d
    7fa134997163:	49 8b 46 18          	mov    0x18(%r14),%rax
    7fa134997167:	8b 00                	mov    (%rax),%eax
    7fa134997169:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7fa134997170:	33 c8                	xor    %eax,%ecx
    7fa134997172:	23 c8                	and    %eax,%ecx
    7fa134997174:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7fa13499717b:	85 c9                	test   %ecx,%ecx
    7fa13499717d:	0f 84 0b 46 00 00    	je     0x7fa13499b78e
    7fa134997183:	49 8b 46 08          	mov    0x8(%r14),%rax
    7fa134997187:	49 8b 0e             	mov    (%r14),%rcx
    7fa13499718a:	48 8b 10             	mov    (%rax),%rdx
    7fa13499718d:	48 8b 19             	mov    (%rcx),%rbx
    7fa134997190:	48 33 d3             	xor    %rbx,%rdx
    7fa134997193:	49 89 97 00 03 00 00 	mov    %rdx,0x300(%r15)
    7fa13499719a:	48 8b 40 08          	mov    0x8(%rax),%rax
    7fa13499719e:	48 8b 51 08          	mov    0x8(%rcx),%rdx
    7fa1349971a2:	48 33 c2             	xor    %rdx,%rax
    7fa1349971a5:	49 89 87 08 03 00 00 	mov    %rax,0x308(%r15)
    7fa1349971ac:	49 0f b6 87 00 01 00 	movzbq 0x100(%r15),%rax
    7fa1349971b3:	00 
    7fa1349971b4:	8b c0                	mov    %eax,%eax
    7fa1349971b6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa1349971bb:	8b d0                	mov    %eax,%edx
    7fa1349971bd:	83 e2 7f             	and    $0x7f,%edx
    7fa1349971c0:	d1 e2                	shl    %edx
    7fa1349971c2:	8b d8                	mov    %eax,%ebx
    7fa1349971c4:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349971c7:	83 e3 01             	and    $0x1,%ebx
    7fa1349971ca:	8b f3                	mov    %ebx,%esi
    7fa1349971cc:	d1 e6                	shl    %esi
    7fa1349971ce:	0b f3                	or     %ebx,%esi
    7fa1349971d0:	8b fb                	mov    %ebx,%edi
    7fa1349971d2:	c1 e7 03             	shl    $0x3,%edi
    7fa1349971d5:	0b f7                	or     %edi,%esi
    7fa1349971d7:	c1 e3 04             	shl    $0x4,%ebx
    7fa1349971da:	0b f3                	or     %ebx,%esi
    7fa1349971dc:	33 d6                	xor    %esi,%edx
    7fa1349971de:	49 0f b6 9f 05 01 00 	movzbq 0x105(%r15),%rbx
    7fa1349971e5:	00 
    7fa1349971e6:	8b db                	mov    %ebx,%ebx
    7fa1349971e8:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa1349971ed:	8b f3                	mov    %ebx,%esi
    7fa1349971ef:	83 e6 7f             	and    $0x7f,%esi
    7fa1349971f2:	d1 e6                	shl    %esi
    7fa1349971f4:	8b fb                	mov    %ebx,%edi
    7fa1349971f6:	c1 ef 07             	shr    $0x7,%edi
    7fa1349971f9:	83 e7 01             	and    $0x1,%edi
    7fa1349971fc:	44 8b c7             	mov    %edi,%r8d
    7fa1349971ff:	41 d1 e0             	shl    %r8d
    7fa134997202:	44 0b c7             	or     %edi,%r8d
    7fa134997205:	44 8b cf             	mov    %edi,%r9d
    7fa134997208:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa13499720c:	45 0b c1             	or     %r9d,%r8d
    7fa13499720f:	c1 e7 04             	shl    $0x4,%edi
    7fa134997212:	44 0b c7             	or     %edi,%r8d
    7fa134997215:	41 33 f0             	xor    %r8d,%esi
    7fa134997218:	8b fe                	mov    %esi,%edi
    7fa13499721a:	33 fb                	xor    %ebx,%edi
    7fa13499721c:	33 fa                	xor    %edx,%edi
    7fa13499721e:	4d 0f b6 87 0a 01 00 	movzbq 0x10a(%r15),%r8
    7fa134997225:	00 
    7fa134997226:	45 8b c0             	mov    %r8d,%r8d
    7fa134997229:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499722e:	41 33 f8             	xor    %r8d,%edi
    7fa134997231:	4d 0f b6 8f 0f 01 00 	movzbq 0x10f(%r15),%r9
    7fa134997238:	00 
    7fa134997239:	45 8b c9             	mov    %r9d,%r9d
    7fa13499723c:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa134997241:	41 33 f9             	xor    %r9d,%edi
    7fa134997244:	33 f0                	xor    %eax,%esi
    7fa134997246:	45 8b d0             	mov    %r8d,%r10d
    7fa134997249:	41 83 e2 7f          	and    $0x7f,%r10d
    7fa13499724d:	41 d1 e2             	shl    %r10d
    7fa134997250:	45 8b d8             	mov    %r8d,%r11d
    7fa134997253:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134997257:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499725b:	44 89 5d f8          	mov    %r11d,-0x8(%rbp)
    7fa13499725f:	41 d1 e3             	shl    %r11d
    7fa134997262:	48 89 4d f0          	mov    %rcx,-0x10(%rbp)
    7fa134997266:	8b 4d f8             	mov    -0x8(%rbp),%ecx
    7fa134997269:	44 0b d9             	or     %ecx,%r11d
    7fa13499726c:	c1 e1 03             	shl    $0x3,%ecx
    7fa13499726f:	44 0b d9             	or     %ecx,%r11d
    7fa134997272:	8b 4d f8             	mov    -0x8(%rbp),%ecx
    7fa134997275:	c1 e1 04             	shl    $0x4,%ecx
    7fa134997278:	44 0b d9             	or     %ecx,%r11d
    7fa13499727b:	45 33 d3             	xor    %r11d,%r10d
    7fa13499727e:	41 8b ca             	mov    %r10d,%ecx
    7fa134997281:	41 33 c8             	xor    %r8d,%ecx
    7fa134997284:	33 f1                	xor    %ecx,%esi
    7fa134997286:	41 33 f1             	xor    %r9d,%esi
    7fa134997289:	8b c8                	mov    %eax,%ecx
    7fa13499728b:	33 cb                	xor    %ebx,%ecx
    7fa13499728d:	44 33 d1             	xor    %ecx,%r10d
    7fa134997290:	41 8b c9             	mov    %r9d,%ecx
    7fa134997293:	83 e1 7f             	and    $0x7f,%ecx
    7fa134997296:	d1 e1                	shl    %ecx
    7fa134997298:	45 8b d9             	mov    %r9d,%r11d
    7fa13499729b:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499729f:	41 83 e3 01          	and    $0x1,%r11d
    7fa1349972a3:	44 89 5d e8          	mov    %r11d,-0x18(%rbp)
    7fa1349972a7:	41 d1 e3             	shl    %r11d
    7fa1349972aa:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7fa1349972ad:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fa1349972b0:	44 0b da             	or     %edx,%r11d
    7fa1349972b3:	c1 e2 03             	shl    $0x3,%edx
    7fa1349972b6:	44 0b da             	or     %edx,%r11d
    7fa1349972b9:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fa1349972bc:	c1 e2 04             	shl    $0x4,%edx
    7fa1349972bf:	44 0b da             	or     %edx,%r11d
    7fa1349972c2:	41 33 cb             	xor    %r11d,%ecx
    7fa1349972c5:	44 33 c9             	xor    %ecx,%r9d
    7fa1349972c8:	45 33 d1             	xor    %r9d,%r10d
    7fa1349972cb:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fa1349972ce:	33 c2                	xor    %edx,%eax
    7fa1349972d0:	33 d8                	xor    %eax,%ebx
    7fa1349972d2:	44 33 c3             	xor    %ebx,%r8d
    7fa1349972d5:	41 33 c8             	xor    %r8d,%ecx
    7fa1349972d8:	49 0f b6 87 04 01 00 	movzbq 0x104(%r15),%rax
    7fa1349972df:	00 
    7fa1349972e0:	8b c0                	mov    %eax,%eax
    7fa1349972e2:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa1349972e7:	8b d0                	mov    %eax,%edx
    7fa1349972e9:	83 e2 7f             	and    $0x7f,%edx
    7fa1349972ec:	d1 e2                	shl    %edx
    7fa1349972ee:	8b d8                	mov    %eax,%ebx
    7fa1349972f0:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349972f3:	83 e3 01             	and    $0x1,%ebx
    7fa1349972f6:	44 8b c3             	mov    %ebx,%r8d
    7fa1349972f9:	41 d1 e0             	shl    %r8d
    7fa1349972fc:	44 0b c3             	or     %ebx,%r8d
    7fa1349972ff:	44 8b cb             	mov    %ebx,%r9d
    7fa134997302:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa134997306:	45 0b c1             	or     %r9d,%r8d
    7fa134997309:	c1 e3 04             	shl    $0x4,%ebx
    7fa13499730c:	44 0b c3             	or     %ebx,%r8d
    7fa13499730f:	41 33 d0             	xor    %r8d,%edx
    7fa134997312:	49 0f b6 9f 09 01 00 	movzbq 0x109(%r15),%rbx
    7fa134997319:	00 
    7fa13499731a:	8b db                	mov    %ebx,%ebx
    7fa13499731c:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134997321:	44 8b c3             	mov    %ebx,%r8d
    7fa134997324:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa134997328:	41 d1 e0             	shl    %r8d
    7fa13499732b:	44 8b cb             	mov    %ebx,%r9d
    7fa13499732e:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa134997332:	41 83 e1 01          	and    $0x1,%r9d
    7fa134997336:	45 8b d9             	mov    %r9d,%r11d
    7fa134997339:	41 d1 e3             	shl    %r11d
    7fa13499733c:	45 0b d9             	or     %r9d,%r11d
    7fa13499733f:	44 89 4d d8          	mov    %r9d,-0x28(%rbp)
    7fa134997343:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa134997347:	45 0b d9             	or     %r9d,%r11d
    7fa13499734a:	44 8b 4d d8          	mov    -0x28(%rbp),%r9d
    7fa13499734e:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa134997352:	45 0b d9             	or     %r9d,%r11d
    7fa134997355:	45 33 c3             	xor    %r11d,%r8d
    7fa134997358:	45 8b c8             	mov    %r8d,%r9d
    7fa13499735b:	44 33 cb             	xor    %ebx,%r9d
    7fa13499735e:	44 33 ca             	xor    %edx,%r9d
    7fa134997361:	4d 0f b6 9f 0e 01 00 	movzbq 0x10e(%r15),%r11
    7fa134997368:	00 
    7fa134997369:	45 8b db             	mov    %r11d,%r11d
    7fa13499736c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134997371:	45 33 cb             	xor    %r11d,%r9d
    7fa134997374:	89 7d d0             	mov    %edi,-0x30(%rbp)
    7fa134997377:	49 0f b6 bf 03 01 00 	movzbq 0x103(%r15),%rdi
    7fa13499737e:	00 
    7fa13499737f:	8b ff                	mov    %edi,%edi
    7fa134997381:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa134997386:	44 33 cf             	xor    %edi,%r9d
    7fa134997389:	44 33 c0             	xor    %eax,%r8d
    7fa13499738c:	44 89 5d c8          	mov    %r11d,-0x38(%rbp)
    7fa134997390:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134997394:	41 d1 e3             	shl    %r11d
    7fa134997397:	89 75 c0             	mov    %esi,-0x40(%rbp)
    7fa13499739a:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7fa13499739d:	c1 ee 07             	shr    $0x7,%esi
    7fa1349973a0:	83 e6 01             	and    $0x1,%esi
    7fa1349973a3:	89 75 b8             	mov    %esi,-0x48(%rbp)
    7fa1349973a6:	d1 e6                	shl    %esi
    7fa1349973a8:	44 89 55 b0          	mov    %r10d,-0x50(%rbp)
    7fa1349973ac:	44 8b 55 b8          	mov    -0x48(%rbp),%r10d
    7fa1349973b0:	41 0b f2             	or     %r10d,%esi
    7fa1349973b3:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349973b7:	41 0b f2             	or     %r10d,%esi
    7fa1349973ba:	44 8b 55 b8          	mov    -0x48(%rbp),%r10d
    7fa1349973be:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa1349973c2:	41 0b f2             	or     %r10d,%esi
    7fa1349973c5:	44 33 de             	xor    %esi,%r11d
    7fa1349973c8:	41 8b f3             	mov    %r11d,%esi
    7fa1349973cb:	44 8b 55 c8          	mov    -0x38(%rbp),%r10d
    7fa1349973cf:	41 33 f2             	xor    %r10d,%esi
    7fa1349973d2:	44 33 c6             	xor    %esi,%r8d
    7fa1349973d5:	44 33 c7             	xor    %edi,%r8d
    7fa1349973d8:	8b f0                	mov    %eax,%esi
    7fa1349973da:	33 f3                	xor    %ebx,%esi
    7fa1349973dc:	44 33 de             	xor    %esi,%r11d
    7fa1349973df:	8b f7                	mov    %edi,%esi
    7fa1349973e1:	83 e6 7f             	and    $0x7f,%esi
    7fa1349973e4:	d1 e6                	shl    %esi
    7fa1349973e6:	44 8b d7             	mov    %edi,%r10d
    7fa1349973e9:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa1349973ed:	41 83 e2 01          	and    $0x1,%r10d
    7fa1349973f1:	44 89 55 a8          	mov    %r10d,-0x58(%rbp)
    7fa1349973f5:	41 d1 e2             	shl    %r10d
    7fa1349973f8:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7fa1349973fb:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fa1349973fe:	44 0b d1             	or     %ecx,%r10d
    7fa134997401:	c1 e1 03             	shl    $0x3,%ecx
    7fa134997404:	44 0b d1             	or     %ecx,%r10d
    7fa134997407:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fa13499740a:	c1 e1 04             	shl    $0x4,%ecx
    7fa13499740d:	44 0b d1             	or     %ecx,%r10d
    7fa134997410:	41 33 f2             	xor    %r10d,%esi
    7fa134997413:	33 fe                	xor    %esi,%edi
    7fa134997415:	44 33 df             	xor    %edi,%r11d
    7fa134997418:	33 d0                	xor    %eax,%edx
    7fa13499741a:	33 da                	xor    %edx,%ebx
    7fa13499741c:	33 5d c8             	xor    -0x38(%rbp),%ebx
    7fa13499741f:	33 f3                	xor    %ebx,%esi
    7fa134997421:	49 0f b6 87 08 01 00 	movzbq 0x108(%r15),%rax
    7fa134997428:	00 
    7fa134997429:	8b c0                	mov    %eax,%eax
    7fa13499742b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134997430:	8b c8                	mov    %eax,%ecx
    7fa134997432:	83 e1 7f             	and    $0x7f,%ecx
    7fa134997435:	d1 e1                	shl    %ecx
    7fa134997437:	8b d0                	mov    %eax,%edx
    7fa134997439:	c1 ea 07             	shr    $0x7,%edx
    7fa13499743c:	83 e2 01             	and    $0x1,%edx
    7fa13499743f:	8b da                	mov    %edx,%ebx
    7fa134997441:	d1 e3                	shl    %ebx
    7fa134997443:	0b da                	or     %edx,%ebx
    7fa134997445:	8b fa                	mov    %edx,%edi
    7fa134997447:	c1 e7 03             	shl    $0x3,%edi
    7fa13499744a:	0b df                	or     %edi,%ebx
    7fa13499744c:	c1 e2 04             	shl    $0x4,%edx
    7fa13499744f:	0b da                	or     %edx,%ebx
    7fa134997451:	33 cb                	xor    %ebx,%ecx
    7fa134997453:	49 0f b6 97 0d 01 00 	movzbq 0x10d(%r15),%rdx
    7fa13499745a:	00 
    7fa13499745b:	8b d2                	mov    %edx,%edx
    7fa13499745d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134997462:	8b da                	mov    %edx,%ebx
    7fa134997464:	83 e3 7f             	and    $0x7f,%ebx
    7fa134997467:	d1 e3                	shl    %ebx
    7fa134997469:	8b fa                	mov    %edx,%edi
    7fa13499746b:	c1 ef 07             	shr    $0x7,%edi
    7fa13499746e:	83 e7 01             	and    $0x1,%edi
    7fa134997471:	44 8b d7             	mov    %edi,%r10d
    7fa134997474:	41 d1 e2             	shl    %r10d
    7fa134997477:	44 0b d7             	or     %edi,%r10d
    7fa13499747a:	89 7d 98             	mov    %edi,-0x68(%rbp)
    7fa13499747d:	c1 e7 03             	shl    $0x3,%edi
    7fa134997480:	44 0b d7             	or     %edi,%r10d
    7fa134997483:	8b 7d 98             	mov    -0x68(%rbp),%edi
    7fa134997486:	c1 e7 04             	shl    $0x4,%edi
    7fa134997489:	44 0b d7             	or     %edi,%r10d
    7fa13499748c:	41 33 da             	xor    %r10d,%ebx
    7fa13499748f:	8b fb                	mov    %ebx,%edi
    7fa134997491:	33 fa                	xor    %edx,%edi
    7fa134997493:	33 f9                	xor    %ecx,%edi
    7fa134997495:	4d 0f b6 97 02 01 00 	movzbq 0x102(%r15),%r10
    7fa13499749c:	00 
    7fa13499749d:	45 8b d2             	mov    %r10d,%r10d
    7fa1349974a0:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa1349974a5:	41 33 fa             	xor    %r10d,%edi
    7fa1349974a8:	44 89 4d 90          	mov    %r9d,-0x70(%rbp)
    7fa1349974ac:	4d 0f b6 8f 07 01 00 	movzbq 0x107(%r15),%r9
    7fa1349974b3:	00 
    7fa1349974b4:	45 8b c9             	mov    %r9d,%r9d
    7fa1349974b7:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa1349974bc:	41 33 f9             	xor    %r9d,%edi
    7fa1349974bf:	33 d8                	xor    %eax,%ebx
    7fa1349974c1:	44 89 55 88          	mov    %r10d,-0x78(%rbp)
    7fa1349974c5:	41 83 e2 7f          	and    $0x7f,%r10d
    7fa1349974c9:	41 d1 e2             	shl    %r10d
    7fa1349974cc:	44 89 45 80          	mov    %r8d,-0x80(%rbp)
    7fa1349974d0:	44 8b 45 88          	mov    -0x78(%rbp),%r8d
    7fa1349974d4:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa1349974d8:	41 83 e0 01          	and    $0x1,%r8d
    7fa1349974dc:	44 89 85 78 ff ff ff 	mov    %r8d,-0x88(%rbp)
    7fa1349974e3:	41 d1 e0             	shl    %r8d
    7fa1349974e6:	44 89 9d 70 ff ff ff 	mov    %r11d,-0x90(%rbp)
    7fa1349974ed:	44 8b 9d 78 ff ff ff 	mov    -0x88(%rbp),%r11d
    7fa1349974f4:	45 0b c3             	or     %r11d,%r8d
    7fa1349974f7:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa1349974fb:	45 0b c3             	or     %r11d,%r8d
    7fa1349974fe:	44 8b 9d 78 ff ff ff 	mov    -0x88(%rbp),%r11d
    7fa134997505:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134997509:	45 0b c3             	or     %r11d,%r8d
    7fa13499750c:	45 33 d0             	xor    %r8d,%r10d
    7fa13499750f:	45 8b c2             	mov    %r10d,%r8d
    7fa134997512:	44 8b 5d 88          	mov    -0x78(%rbp),%r11d
    7fa134997516:	45 33 c3             	xor    %r11d,%r8d
    7fa134997519:	41 33 d8             	xor    %r8d,%ebx
    7fa13499751c:	41 33 d9             	xor    %r9d,%ebx
    7fa13499751f:	44 8b c0             	mov    %eax,%r8d
    7fa134997522:	44 33 c2             	xor    %edx,%r8d
    7fa134997525:	45 33 d0             	xor    %r8d,%r10d
    7fa134997528:	45 8b c1             	mov    %r9d,%r8d
    7fa13499752b:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa13499752f:	41 d1 e0             	shl    %r8d
    7fa134997532:	45 8b d9             	mov    %r9d,%r11d
    7fa134997535:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134997539:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499753d:	44 89 9d 68 ff ff ff 	mov    %r11d,-0x98(%rbp)
    7fa134997544:	41 d1 e3             	shl    %r11d
    7fa134997547:	89 b5 60 ff ff ff    	mov    %esi,-0xa0(%rbp)
    7fa13499754d:	8b b5 68 ff ff ff    	mov    -0x98(%rbp),%esi
    7fa134997553:	44 0b de             	or     %esi,%r11d
    7fa134997556:	c1 e6 03             	shl    $0x3,%esi
    7fa134997559:	44 0b de             	or     %esi,%r11d
    7fa13499755c:	8b b5 68 ff ff ff    	mov    -0x98(%rbp),%esi
    7fa134997562:	c1 e6 04             	shl    $0x4,%esi
    7fa134997565:	44 0b de             	or     %esi,%r11d
    7fa134997568:	45 33 c3             	xor    %r11d,%r8d
    7fa13499756b:	45 33 c8             	xor    %r8d,%r9d
    7fa13499756e:	45 33 d1             	xor    %r9d,%r10d
    7fa134997571:	33 c8                	xor    %eax,%ecx
    7fa134997573:	33 d1                	xor    %ecx,%edx
    7fa134997575:	33 55 88             	xor    -0x78(%rbp),%edx
    7fa134997578:	44 33 c2             	xor    %edx,%r8d
    7fa13499757b:	49 0f b6 87 0c 01 00 	movzbq 0x10c(%r15),%rax
    7fa134997582:	00 
    7fa134997583:	8b c0                	mov    %eax,%eax
    7fa134997585:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499758a:	8b c8                	mov    %eax,%ecx
    7fa13499758c:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499758f:	d1 e1                	shl    %ecx
    7fa134997591:	8b d0                	mov    %eax,%edx
    7fa134997593:	c1 ea 07             	shr    $0x7,%edx
    7fa134997596:	83 e2 01             	and    $0x1,%edx
    7fa134997599:	8b f2                	mov    %edx,%esi
    7fa13499759b:	d1 e6                	shl    %esi
    7fa13499759d:	0b f2                	or     %edx,%esi
    7fa13499759f:	44 8b ca             	mov    %edx,%r9d
    7fa1349975a2:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa1349975a6:	41 0b f1             	or     %r9d,%esi
    7fa1349975a9:	c1 e2 04             	shl    $0x4,%edx
    7fa1349975ac:	0b f2                	or     %edx,%esi
    7fa1349975ae:	33 ce                	xor    %esi,%ecx
    7fa1349975b0:	49 0f b6 97 01 01 00 	movzbq 0x101(%r15),%rdx
    7fa1349975b7:	00 
    7fa1349975b8:	8b d2                	mov    %edx,%edx
    7fa1349975ba:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa1349975bf:	8b f2                	mov    %edx,%esi
    7fa1349975c1:	83 e6 7f             	and    $0x7f,%esi
    7fa1349975c4:	d1 e6                	shl    %esi
    7fa1349975c6:	44 8b ca             	mov    %edx,%r9d
    7fa1349975c9:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa1349975cd:	41 83 e1 01          	and    $0x1,%r9d
    7fa1349975d1:	45 8b d9             	mov    %r9d,%r11d
    7fa1349975d4:	41 d1 e3             	shl    %r11d
    7fa1349975d7:	45 0b d9             	or     %r9d,%r11d
    7fa1349975da:	44 89 8d 58 ff ff ff 	mov    %r9d,-0xa8(%rbp)
    7fa1349975e1:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa1349975e5:	45 0b d9             	or     %r9d,%r11d
    7fa1349975e8:	44 8b 8d 58 ff ff ff 	mov    -0xa8(%rbp),%r9d
    7fa1349975ef:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa1349975f3:	45 0b d9             	or     %r9d,%r11d
    7fa1349975f6:	41 33 f3             	xor    %r11d,%esi
    7fa1349975f9:	44 8b ce             	mov    %esi,%r9d
    7fa1349975fc:	44 33 ca             	xor    %edx,%r9d
    7fa1349975ff:	44 33 c9             	xor    %ecx,%r9d
    7fa134997602:	4d 0f b6 9f 06 01 00 	movzbq 0x106(%r15),%r11
    7fa134997609:	00 
    7fa13499760a:	45 8b db             	mov    %r11d,%r11d
    7fa13499760d:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134997612:	45 33 cb             	xor    %r11d,%r9d
    7fa134997615:	89 bd 50 ff ff ff    	mov    %edi,-0xb0(%rbp)
    7fa13499761b:	49 0f b6 bf 0b 01 00 	movzbq 0x10b(%r15),%rdi
    7fa134997622:	00 
    7fa134997623:	8b ff                	mov    %edi,%edi
    7fa134997625:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499762a:	44 33 cf             	xor    %edi,%r9d
    7fa13499762d:	33 f0                	xor    %eax,%esi
    7fa13499762f:	44 89 9d 48 ff ff ff 	mov    %r11d,-0xb8(%rbp)
    7fa134997636:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499763a:	41 d1 e3             	shl    %r11d
    7fa13499763d:	89 9d 40 ff ff ff    	mov    %ebx,-0xc0(%rbp)
    7fa134997643:	8b 9d 48 ff ff ff    	mov    -0xb8(%rbp),%ebx
    7fa134997649:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499764c:	83 e3 01             	and    $0x1,%ebx
    7fa13499764f:	89 9d 38 ff ff ff    	mov    %ebx,-0xc8(%rbp)
    7fa134997655:	d1 e3                	shl    %ebx
    7fa134997657:	44 89 95 30 ff ff ff 	mov    %r10d,-0xd0(%rbp)
    7fa13499765e:	44 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%r10d
    7fa134997665:	41 0b da             	or     %r10d,%ebx
    7fa134997668:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499766c:	41 0b da             	or     %r10d,%ebx
    7fa13499766f:	44 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%r10d
    7fa134997676:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499767a:	41 0b da             	or     %r10d,%ebx
    7fa13499767d:	44 33 db             	xor    %ebx,%r11d
    7fa134997680:	41 8b db             	mov    %r11d,%ebx
    7fa134997683:	44 8b 95 48 ff ff ff 	mov    -0xb8(%rbp),%r10d
    7fa13499768a:	41 33 da             	xor    %r10d,%ebx
    7fa13499768d:	33 f3                	xor    %ebx,%esi
    7fa13499768f:	33 f7                	xor    %edi,%esi
    7fa134997691:	8b d8                	mov    %eax,%ebx
    7fa134997693:	33 da                	xor    %edx,%ebx
    7fa134997695:	44 33 db             	xor    %ebx,%r11d
    7fa134997698:	8b df                	mov    %edi,%ebx
    7fa13499769a:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499769d:	d1 e3                	shl    %ebx
    7fa13499769f:	44 8b d7             	mov    %edi,%r10d
    7fa1349976a2:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa1349976a6:	41 83 e2 01          	and    $0x1,%r10d
    7fa1349976aa:	44 89 95 28 ff ff ff 	mov    %r10d,-0xd8(%rbp)
    7fa1349976b1:	41 d1 e2             	shl    %r10d
    7fa1349976b4:	44 89 85 20 ff ff ff 	mov    %r8d,-0xe0(%rbp)
    7fa1349976bb:	44 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%r8d
    7fa1349976c2:	45 0b d0             	or     %r8d,%r10d
    7fa1349976c5:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa1349976c9:	45 0b d0             	or     %r8d,%r10d
    7fa1349976cc:	44 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%r8d
    7fa1349976d3:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa1349976d7:	45 0b d0             	or     %r8d,%r10d
    7fa1349976da:	41 33 da             	xor    %r10d,%ebx
    7fa1349976dd:	33 fb                	xor    %ebx,%edi
    7fa1349976df:	44 33 df             	xor    %edi,%r11d
    7fa1349976e2:	33 c8                	xor    %eax,%ecx
    7fa1349976e4:	33 d1                	xor    %ecx,%edx
    7fa1349976e6:	33 95 48 ff ff ff    	xor    -0xb8(%rbp),%edx
    7fa1349976ec:	33 da                	xor    %edx,%ebx
    7fa1349976ee:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fa1349976f1:	c1 e0 08             	shl    $0x8,%eax
    7fa1349976f4:	0b 45 d0             	or     -0x30(%rbp),%eax
    7fa1349976f7:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7fa1349976fa:	c1 e1 10             	shl    $0x10,%ecx
    7fa1349976fd:	0b c1                	or     %ecx,%eax
    7fa1349976ff:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fa134997702:	c1 e1 18             	shl    $0x18,%ecx
    7fa134997705:	0b c1                	or     %ecx,%eax
    7fa134997707:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7fa13499770a:	8b c9                	mov    %ecx,%ecx
    7fa13499770c:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa134997710:	8b c0                	mov    %eax,%eax
    7fa134997712:	48 0b c8             	or     %rax,%rcx
    7fa134997715:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fa134997718:	8b c0                	mov    %eax,%eax
    7fa13499771a:	48 c1 e0 28          	shl    $0x28,%rax
    7fa13499771e:	48 0b c8             	or     %rax,%rcx
    7fa134997721:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fa134997727:	8b c0                	mov    %eax,%eax
    7fa134997729:	48 c1 e0 30          	shl    $0x30,%rax
    7fa13499772d:	48 0b c8             	or     %rax,%rcx
    7fa134997730:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fa134997736:	8b c0                	mov    %eax,%eax
    7fa134997738:	48 c1 e0 38          	shl    $0x38,%rax
    7fa13499773c:	48 0b c8             	or     %rax,%rcx
    7fa13499773f:	49 89 8f 60 02 00 00 	mov    %rcx,0x260(%r15)
    7fa134997746:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7fa13499774c:	c1 e0 08             	shl    $0x8,%eax
    7fa13499774f:	0b 85 50 ff ff ff    	or     -0xb0(%rbp),%eax
    7fa134997755:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7fa13499775b:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499775e:	0b c1                	or     %ecx,%eax
    7fa134997760:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7fa134997766:	c1 e1 18             	shl    $0x18,%ecx
    7fa134997769:	0b c1                	or     %ecx,%eax
    7fa13499776b:	45 8b c9             	mov    %r9d,%r9d
    7fa13499776e:	49 c1 e1 20          	shl    $0x20,%r9
    7fa134997772:	8b c0                	mov    %eax,%eax
    7fa134997774:	4c 0b c8             	or     %rax,%r9
    7fa134997777:	8b f6                	mov    %esi,%esi
    7fa134997779:	48 c1 e6 28          	shl    $0x28,%rsi
    7fa13499777d:	4c 0b ce             	or     %rsi,%r9
    7fa134997780:	45 8b db             	mov    %r11d,%r11d
    7fa134997783:	49 c1 e3 30          	shl    $0x30,%r11
    7fa134997787:	4d 0b cb             	or     %r11,%r9
    7fa13499778a:	8b db                	mov    %ebx,%ebx
    7fa13499778c:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa134997790:	4c 0b cb             	or     %rbx,%r9
    7fa134997793:	4d 89 8f 68 02 00 00 	mov    %r9,0x268(%r15)
    7fa13499779a:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    7fa13499779e:	8b 41 0c             	mov    0xc(%rcx),%eax
    7fa1349977a1:	8b 51 08             	mov    0x8(%rcx),%edx
    7fa1349977a4:	8b 59 04             	mov    0x4(%rcx),%ebx
    7fa1349977a7:	8b 31                	mov    (%rcx),%esi
    7fa1349977a9:	48 0f b6 79 0c       	movzbq 0xc(%rcx),%rdi
    7fa1349977ae:	8b ff                	mov    %edi,%edi
    7fa1349977b0:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa1349977b5:	4c 0f b6 41 0f       	movzbq 0xf(%rcx),%r8
    7fa1349977ba:	45 8b c0             	mov    %r8d,%r8d
    7fa1349977bd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa1349977c2:	4c 0f b6 49 0e       	movzbq 0xe(%rcx),%r9
    7fa1349977c7:	45 8b c9             	mov    %r9d,%r9d
    7fa1349977ca:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa1349977cf:	48 0f b6 49 0d       	movzbq 0xd(%rcx),%rcx
    7fa1349977d4:	8b c9                	mov    %ecx,%ecx
    7fa1349977d6:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa1349977db:	41 c1 e1 08          	shl    $0x8,%r9d
    7fa1349977df:	41 0b c9             	or     %r9d,%ecx
    7fa1349977e2:	41 c1 e0 10          	shl    $0x10,%r8d
    7fa1349977e6:	41 0b c8             	or     %r8d,%ecx
    7fa1349977e9:	c1 e7 18             	shl    $0x18,%edi
    7fa1349977ec:	0b cf                	or     %edi,%ecx
    7fa1349977ee:	83 f1 01             	xor    $0x1,%ecx
    7fa1349977f1:	33 f1                	xor    %ecx,%esi
    7fa1349977f3:	33 de                	xor    %esi,%ebx
    7fa1349977f5:	33 d3                	xor    %ebx,%edx
    7fa1349977f7:	33 c2                	xor    %edx,%eax
    7fa1349977f9:	8b cb                	mov    %ebx,%ecx
    7fa1349977fb:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa1349977ff:	8b fe                	mov    %esi,%edi
    7fa134997801:	48 0b cf             	or     %rdi,%rcx
    7fa134997804:	49 89 8f c0 01 00 00 	mov    %rcx,0x1c0(%r15)
    7fa13499780b:	8b c8                	mov    %eax,%ecx
    7fa13499780d:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa134997811:	8b fa                	mov    %edx,%edi
    7fa134997813:	48 0b cf             	or     %rdi,%rcx
    7fa134997816:	49 89 8f c8 01 00 00 	mov    %rcx,0x1c8(%r15)
    7fa13499781d:	49 8b 8f 60 02 00 00 	mov    0x260(%r15),%rcx
    7fa134997824:	49 8b bf c0 01 00 00 	mov    0x1c0(%r15),%rdi
    7fa13499782b:	48 33 cf             	xor    %rdi,%rcx
    7fa13499782e:	49 89 8f 10 03 00 00 	mov    %rcx,0x310(%r15)
    7fa134997835:	49 8b 8f 68 02 00 00 	mov    0x268(%r15),%rcx
    7fa13499783c:	49 8b bf c8 01 00 00 	mov    0x1c8(%r15),%rdi
    7fa134997843:	48 33 cf             	xor    %rdi,%rcx
    7fa134997846:	49 89 8f 18 03 00 00 	mov    %rcx,0x318(%r15)
    7fa13499784d:	49 0f b6 8f 10 01 00 	movzbq 0x110(%r15),%rcx
    7fa134997854:	00 
    7fa134997855:	8b c9                	mov    %ecx,%ecx
    7fa134997857:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa13499785c:	8b f9                	mov    %ecx,%edi
    7fa13499785e:	83 e7 7f             	and    $0x7f,%edi
    7fa134997861:	d1 e7                	shl    %edi
    7fa134997863:	44 8b c1             	mov    %ecx,%r8d
    7fa134997866:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499786a:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499786e:	45 8b c8             	mov    %r8d,%r9d
    7fa134997871:	41 d1 e1             	shl    %r9d
    7fa134997874:	45 0b c8             	or     %r8d,%r9d
    7fa134997877:	45 8b d0             	mov    %r8d,%r10d
    7fa13499787a:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499787e:	45 0b ca             	or     %r10d,%r9d
    7fa134997881:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134997885:	45 0b c8             	or     %r8d,%r9d
    7fa134997888:	41 33 f9             	xor    %r9d,%edi
    7fa13499788b:	4d 0f b6 87 15 01 00 	movzbq 0x115(%r15),%r8
    7fa134997892:	00 
    7fa134997893:	45 8b c0             	mov    %r8d,%r8d
    7fa134997896:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499789b:	45 8b c8             	mov    %r8d,%r9d
    7fa13499789e:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa1349978a2:	41 d1 e1             	shl    %r9d
    7fa1349978a5:	45 8b d0             	mov    %r8d,%r10d
    7fa1349978a8:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa1349978ac:	41 83 e2 01          	and    $0x1,%r10d
    7fa1349978b0:	45 8b da             	mov    %r10d,%r11d
    7fa1349978b3:	41 d1 e3             	shl    %r11d
    7fa1349978b6:	45 0b da             	or     %r10d,%r11d
    7fa1349978b9:	44 89 95 18 ff ff ff 	mov    %r10d,-0xe8(%rbp)
    7fa1349978c0:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349978c4:	45 0b da             	or     %r10d,%r11d
    7fa1349978c7:	44 8b 95 18 ff ff ff 	mov    -0xe8(%rbp),%r10d
    7fa1349978ce:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa1349978d2:	45 0b da             	or     %r10d,%r11d
    7fa1349978d5:	45 33 cb             	xor    %r11d,%r9d
    7fa1349978d8:	45 8b d1             	mov    %r9d,%r10d
    7fa1349978db:	45 33 d0             	xor    %r8d,%r10d
    7fa1349978de:	44 33 d7             	xor    %edi,%r10d
    7fa1349978e1:	4d 0f b6 9f 1a 01 00 	movzbq 0x11a(%r15),%r11
    7fa1349978e8:	00 
    7fa1349978e9:	45 8b db             	mov    %r11d,%r11d
    7fa1349978ec:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa1349978f1:	45 33 d3             	xor    %r11d,%r10d
    7fa1349978f4:	89 9d 10 ff ff ff    	mov    %ebx,-0xf0(%rbp)
    7fa1349978fa:	49 0f b6 9f 1f 01 00 	movzbq 0x11f(%r15),%rbx
    7fa134997901:	00 
    7fa134997902:	8b db                	mov    %ebx,%ebx
    7fa134997904:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134997909:	44 33 d3             	xor    %ebx,%r10d
    7fa13499790c:	44 33 c9             	xor    %ecx,%r9d
    7fa13499790f:	44 89 9d 08 ff ff ff 	mov    %r11d,-0xf8(%rbp)
    7fa134997916:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499791a:	41 d1 e3             	shl    %r11d
    7fa13499791d:	89 b5 00 ff ff ff    	mov    %esi,-0x100(%rbp)
    7fa134997923:	8b b5 08 ff ff ff    	mov    -0xf8(%rbp),%esi
    7fa134997929:	c1 ee 07             	shr    $0x7,%esi
    7fa13499792c:	83 e6 01             	and    $0x1,%esi
    7fa13499792f:	89 b5 f8 fe ff ff    	mov    %esi,-0x108(%rbp)
    7fa134997935:	d1 e6                	shl    %esi
    7fa134997937:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7fa13499793d:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7fa134997943:	0b f0                	or     %eax,%esi
    7fa134997945:	c1 e0 03             	shl    $0x3,%eax
    7fa134997948:	0b f0                	or     %eax,%esi
    7fa13499794a:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7fa134997950:	c1 e0 04             	shl    $0x4,%eax
    7fa134997953:	0b f0                	or     %eax,%esi
    7fa134997955:	44 33 de             	xor    %esi,%r11d
    7fa134997958:	41 8b c3             	mov    %r11d,%eax
    7fa13499795b:	8b b5 08 ff ff ff    	mov    -0xf8(%rbp),%esi
    7fa134997961:	33 c6                	xor    %esi,%eax
    7fa134997963:	44 33 c8             	xor    %eax,%r9d
    7fa134997966:	44 33 cb             	xor    %ebx,%r9d
    7fa134997969:	8b c1                	mov    %ecx,%eax
    7fa13499796b:	41 33 c0             	xor    %r8d,%eax
    7fa13499796e:	44 33 d8             	xor    %eax,%r11d
    7fa134997971:	8b c3                	mov    %ebx,%eax
    7fa134997973:	83 e0 7f             	and    $0x7f,%eax
    7fa134997976:	d1 e0                	shl    %eax
    7fa134997978:	8b f3                	mov    %ebx,%esi
    7fa13499797a:	c1 ee 07             	shr    $0x7,%esi
    7fa13499797d:	83 e6 01             	and    $0x1,%esi
    7fa134997980:	89 b5 e8 fe ff ff    	mov    %esi,-0x118(%rbp)
    7fa134997986:	d1 e6                	shl    %esi
    7fa134997988:	89 95 e0 fe ff ff    	mov    %edx,-0x120(%rbp)
    7fa13499798e:	8b 95 e8 fe ff ff    	mov    -0x118(%rbp),%edx
    7fa134997994:	0b f2                	or     %edx,%esi
    7fa134997996:	c1 e2 03             	shl    $0x3,%edx
    7fa134997999:	0b f2                	or     %edx,%esi
    7fa13499799b:	8b 95 e8 fe ff ff    	mov    -0x118(%rbp),%edx
    7fa1349979a1:	c1 e2 04             	shl    $0x4,%edx
    7fa1349979a4:	0b f2                	or     %edx,%esi
    7fa1349979a6:	33 c6                	xor    %esi,%eax
    7fa1349979a8:	33 d8                	xor    %eax,%ebx
    7fa1349979aa:	44 33 db             	xor    %ebx,%r11d
    7fa1349979ad:	33 f9                	xor    %ecx,%edi
    7fa1349979af:	44 33 c7             	xor    %edi,%r8d
    7fa1349979b2:	44 33 85 08 ff ff ff 	xor    -0xf8(%rbp),%r8d
    7fa1349979b9:	41 33 c0             	xor    %r8d,%eax
    7fa1349979bc:	49 0f b6 8f 14 01 00 	movzbq 0x114(%r15),%rcx
    7fa1349979c3:	00 
    7fa1349979c4:	8b c9                	mov    %ecx,%ecx
    7fa1349979c6:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa1349979cb:	8b d1                	mov    %ecx,%edx
    7fa1349979cd:	83 e2 7f             	and    $0x7f,%edx
    7fa1349979d0:	d1 e2                	shl    %edx
    7fa1349979d2:	8b d9                	mov    %ecx,%ebx
    7fa1349979d4:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349979d7:	83 e3 01             	and    $0x1,%ebx
    7fa1349979da:	8b f3                	mov    %ebx,%esi
    7fa1349979dc:	d1 e6                	shl    %esi
    7fa1349979de:	0b f3                	or     %ebx,%esi
    7fa1349979e0:	8b fb                	mov    %ebx,%edi
    7fa1349979e2:	c1 e7 03             	shl    $0x3,%edi
    7fa1349979e5:	0b f7                	or     %edi,%esi
    7fa1349979e7:	c1 e3 04             	shl    $0x4,%ebx
    7fa1349979ea:	0b f3                	or     %ebx,%esi
    7fa1349979ec:	33 d6                	xor    %esi,%edx
    7fa1349979ee:	49 0f b6 9f 19 01 00 	movzbq 0x119(%r15),%rbx
    7fa1349979f5:	00 
    7fa1349979f6:	8b db                	mov    %ebx,%ebx
    7fa1349979f8:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa1349979fd:	8b f3                	mov    %ebx,%esi
    7fa1349979ff:	83 e6 7f             	and    $0x7f,%esi
    7fa134997a02:	d1 e6                	shl    %esi
    7fa134997a04:	8b fb                	mov    %ebx,%edi
    7fa134997a06:	c1 ef 07             	shr    $0x7,%edi
    7fa134997a09:	83 e7 01             	and    $0x1,%edi
    7fa134997a0c:	44 8b c7             	mov    %edi,%r8d
    7fa134997a0f:	41 d1 e0             	shl    %r8d
    7fa134997a12:	44 0b c7             	or     %edi,%r8d
    7fa134997a15:	89 bd d8 fe ff ff    	mov    %edi,-0x128(%rbp)
    7fa134997a1b:	c1 e7 03             	shl    $0x3,%edi
    7fa134997a1e:	44 0b c7             	or     %edi,%r8d
    7fa134997a21:	8b bd d8 fe ff ff    	mov    -0x128(%rbp),%edi
    7fa134997a27:	c1 e7 04             	shl    $0x4,%edi
    7fa134997a2a:	44 0b c7             	or     %edi,%r8d
    7fa134997a2d:	41 33 f0             	xor    %r8d,%esi
    7fa134997a30:	8b fe                	mov    %esi,%edi
    7fa134997a32:	33 fb                	xor    %ebx,%edi
    7fa134997a34:	33 fa                	xor    %edx,%edi
    7fa134997a36:	4d 0f b6 87 1e 01 00 	movzbq 0x11e(%r15),%r8
    7fa134997a3d:	00 
    7fa134997a3e:	45 8b c0             	mov    %r8d,%r8d
    7fa134997a41:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134997a46:	41 33 f8             	xor    %r8d,%edi
    7fa134997a49:	44 89 95 d0 fe ff ff 	mov    %r10d,-0x130(%rbp)
    7fa134997a50:	4d 0f b6 97 13 01 00 	movzbq 0x113(%r15),%r10
    7fa134997a57:	00 
    7fa134997a58:	45 8b d2             	mov    %r10d,%r10d
    7fa134997a5b:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa134997a60:	41 33 fa             	xor    %r10d,%edi
    7fa134997a63:	33 f1                	xor    %ecx,%esi
    7fa134997a65:	44 89 85 c8 fe ff ff 	mov    %r8d,-0x138(%rbp)
    7fa134997a6c:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa134997a70:	41 d1 e0             	shl    %r8d
    7fa134997a73:	44 89 8d c0 fe ff ff 	mov    %r9d,-0x140(%rbp)
    7fa134997a7a:	44 8b 8d c8 fe ff ff 	mov    -0x138(%rbp),%r9d
    7fa134997a81:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa134997a85:	41 83 e1 01          	and    $0x1,%r9d
    7fa134997a89:	44 89 8d b8 fe ff ff 	mov    %r9d,-0x148(%rbp)
    7fa134997a90:	41 d1 e1             	shl    %r9d
    7fa134997a93:	44 89 9d b0 fe ff ff 	mov    %r11d,-0x150(%rbp)
    7fa134997a9a:	44 8b 9d b8 fe ff ff 	mov    -0x148(%rbp),%r11d
    7fa134997aa1:	45 0b cb             	or     %r11d,%r9d
    7fa134997aa4:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134997aa8:	45 0b cb             	or     %r11d,%r9d
    7fa134997aab:	44 8b 9d b8 fe ff ff 	mov    -0x148(%rbp),%r11d
    7fa134997ab2:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134997ab6:	45 0b cb             	or     %r11d,%r9d
    7fa134997ab9:	45 33 c1             	xor    %r9d,%r8d
    7fa134997abc:	45 8b c8             	mov    %r8d,%r9d
    7fa134997abf:	44 8b 9d c8 fe ff ff 	mov    -0x138(%rbp),%r11d
    7fa134997ac6:	45 33 cb             	xor    %r11d,%r9d
    7fa134997ac9:	41 33 f1             	xor    %r9d,%esi
    7fa134997acc:	41 33 f2             	xor    %r10d,%esi
    7fa134997acf:	44 8b c9             	mov    %ecx,%r9d
    7fa134997ad2:	44 33 cb             	xor    %ebx,%r9d
    7fa134997ad5:	45 33 c1             	xor    %r9d,%r8d
    7fa134997ad8:	45 8b ca             	mov    %r10d,%r9d
    7fa134997adb:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134997adf:	41 d1 e1             	shl    %r9d
    7fa134997ae2:	45 8b da             	mov    %r10d,%r11d
    7fa134997ae5:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134997ae9:	41 83 e3 01          	and    $0x1,%r11d
    7fa134997aed:	44 89 9d a8 fe ff ff 	mov    %r11d,-0x158(%rbp)
    7fa134997af4:	41 d1 e3             	shl    %r11d
    7fa134997af7:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fa134997afd:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fa134997b03:	44 0b d8             	or     %eax,%r11d
    7fa134997b06:	c1 e0 03             	shl    $0x3,%eax
    7fa134997b09:	44 0b d8             	or     %eax,%r11d
    7fa134997b0c:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fa134997b12:	c1 e0 04             	shl    $0x4,%eax
    7fa134997b15:	44 0b d8             	or     %eax,%r11d
    7fa134997b18:	45 33 cb             	xor    %r11d,%r9d
    7fa134997b1b:	45 33 d1             	xor    %r9d,%r10d
    7fa134997b1e:	45 33 c2             	xor    %r10d,%r8d
    7fa134997b21:	33 d1                	xor    %ecx,%edx
    7fa134997b23:	33 da                	xor    %edx,%ebx
    7fa134997b25:	33 9d c8 fe ff ff    	xor    -0x138(%rbp),%ebx
    7fa134997b2b:	44 33 cb             	xor    %ebx,%r9d
    7fa134997b2e:	49 0f b6 87 18 01 00 	movzbq 0x118(%r15),%rax
    7fa134997b35:	00 
    7fa134997b36:	8b c0                	mov    %eax,%eax
    7fa134997b38:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134997b3d:	8b c8                	mov    %eax,%ecx
    7fa134997b3f:	83 e1 7f             	and    $0x7f,%ecx
    7fa134997b42:	d1 e1                	shl    %ecx
    7fa134997b44:	8b d0                	mov    %eax,%edx
    7fa134997b46:	c1 ea 07             	shr    $0x7,%edx
    7fa134997b49:	83 e2 01             	and    $0x1,%edx
    7fa134997b4c:	8b da                	mov    %edx,%ebx
    7fa134997b4e:	d1 e3                	shl    %ebx
    7fa134997b50:	0b da                	or     %edx,%ebx
    7fa134997b52:	44 8b d2             	mov    %edx,%r10d
    7fa134997b55:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134997b59:	41 0b da             	or     %r10d,%ebx
    7fa134997b5c:	c1 e2 04             	shl    $0x4,%edx
    7fa134997b5f:	0b da                	or     %edx,%ebx
    7fa134997b61:	33 cb                	xor    %ebx,%ecx
    7fa134997b63:	49 0f b6 97 1d 01 00 	movzbq 0x11d(%r15),%rdx
    7fa134997b6a:	00 
    7fa134997b6b:	8b d2                	mov    %edx,%edx
    7fa134997b6d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134997b72:	8b da                	mov    %edx,%ebx
    7fa134997b74:	83 e3 7f             	and    $0x7f,%ebx
    7fa134997b77:	d1 e3                	shl    %ebx
    7fa134997b79:	44 8b d2             	mov    %edx,%r10d
    7fa134997b7c:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa134997b80:	41 83 e2 01          	and    $0x1,%r10d
    7fa134997b84:	45 8b da             	mov    %r10d,%r11d
    7fa134997b87:	41 d1 e3             	shl    %r11d
    7fa134997b8a:	45 0b da             	or     %r10d,%r11d
    7fa134997b8d:	44 89 95 98 fe ff ff 	mov    %r10d,-0x168(%rbp)
    7fa134997b94:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134997b98:	45 0b da             	or     %r10d,%r11d
    7fa134997b9b:	44 8b 95 98 fe ff ff 	mov    -0x168(%rbp),%r10d
    7fa134997ba2:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134997ba6:	45 0b da             	or     %r10d,%r11d
    7fa134997ba9:	41 33 db             	xor    %r11d,%ebx
    7fa134997bac:	44 8b d3             	mov    %ebx,%r10d
    7fa134997baf:	44 33 d2             	xor    %edx,%r10d
    7fa134997bb2:	44 33 d1             	xor    %ecx,%r10d
    7fa134997bb5:	4d 0f b6 9f 12 01 00 	movzbq 0x112(%r15),%r11
    7fa134997bbc:	00 
    7fa134997bbd:	45 8b db             	mov    %r11d,%r11d
    7fa134997bc0:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134997bc5:	45 33 d3             	xor    %r11d,%r10d
    7fa134997bc8:	89 bd 90 fe ff ff    	mov    %edi,-0x170(%rbp)
    7fa134997bce:	49 0f b6 bf 17 01 00 	movzbq 0x117(%r15),%rdi
    7fa134997bd5:	00 
    7fa134997bd6:	8b ff                	mov    %edi,%edi
    7fa134997bd8:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa134997bdd:	44 33 d7             	xor    %edi,%r10d
    7fa134997be0:	33 d8                	xor    %eax,%ebx
    7fa134997be2:	44 89 9d 88 fe ff ff 	mov    %r11d,-0x178(%rbp)
    7fa134997be9:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134997bed:	41 d1 e3             	shl    %r11d
    7fa134997bf0:	89 b5 80 fe ff ff    	mov    %esi,-0x180(%rbp)
    7fa134997bf6:	8b b5 88 fe ff ff    	mov    -0x178(%rbp),%esi
    7fa134997bfc:	c1 ee 07             	shr    $0x7,%esi
    7fa134997bff:	83 e6 01             	and    $0x1,%esi
    7fa134997c02:	89 b5 78 fe ff ff    	mov    %esi,-0x188(%rbp)
    7fa134997c08:	d1 e6                	shl    %esi
    7fa134997c0a:	44 89 85 70 fe ff ff 	mov    %r8d,-0x190(%rbp)
    7fa134997c11:	44 8b 85 78 fe ff ff 	mov    -0x188(%rbp),%r8d
    7fa134997c18:	41 0b f0             	or     %r8d,%esi
    7fa134997c1b:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134997c1f:	41 0b f0             	or     %r8d,%esi
    7fa134997c22:	44 8b 85 78 fe ff ff 	mov    -0x188(%rbp),%r8d
    7fa134997c29:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134997c2d:	41 0b f0             	or     %r8d,%esi
    7fa134997c30:	44 33 de             	xor    %esi,%r11d
    7fa134997c33:	41 8b f3             	mov    %r11d,%esi
    7fa134997c36:	44 8b 85 88 fe ff ff 	mov    -0x178(%rbp),%r8d
    7fa134997c3d:	41 33 f0             	xor    %r8d,%esi
    7fa134997c40:	33 de                	xor    %esi,%ebx
    7fa134997c42:	33 df                	xor    %edi,%ebx
    7fa134997c44:	8b f0                	mov    %eax,%esi
    7fa134997c46:	33 f2                	xor    %edx,%esi
    7fa134997c48:	44 33 de             	xor    %esi,%r11d
    7fa134997c4b:	8b f7                	mov    %edi,%esi
    7fa134997c4d:	83 e6 7f             	and    $0x7f,%esi
    7fa134997c50:	d1 e6                	shl    %esi
    7fa134997c52:	44 8b c7             	mov    %edi,%r8d
    7fa134997c55:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134997c59:	41 83 e0 01          	and    $0x1,%r8d
    7fa134997c5d:	44 89 85 68 fe ff ff 	mov    %r8d,-0x198(%rbp)
    7fa134997c64:	41 d1 e0             	shl    %r8d
    7fa134997c67:	44 89 8d 60 fe ff ff 	mov    %r9d,-0x1a0(%rbp)
    7fa134997c6e:	44 8b 8d 68 fe ff ff 	mov    -0x198(%rbp),%r9d
    7fa134997c75:	45 0b c1             	or     %r9d,%r8d
    7fa134997c78:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa134997c7c:	45 0b c1             	or     %r9d,%r8d
    7fa134997c7f:	44 8b 8d 68 fe ff ff 	mov    -0x198(%rbp),%r9d
    7fa134997c86:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa134997c8a:	45 0b c1             	or     %r9d,%r8d
    7fa134997c8d:	41 33 f0             	xor    %r8d,%esi
    7fa134997c90:	33 fe                	xor    %esi,%edi
    7fa134997c92:	44 33 df             	xor    %edi,%r11d
    7fa134997c95:	33 c8                	xor    %eax,%ecx
    7fa134997c97:	33 d1                	xor    %ecx,%edx
    7fa134997c99:	33 95 88 fe ff ff    	xor    -0x178(%rbp),%edx
    7fa134997c9f:	33 f2                	xor    %edx,%esi
    7fa134997ca1:	49 0f b6 87 1c 01 00 	movzbq 0x11c(%r15),%rax
    7fa134997ca8:	00 
    7fa134997ca9:	8b c0                	mov    %eax,%eax
    7fa134997cab:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134997cb0:	8b c8                	mov    %eax,%ecx
    7fa134997cb2:	83 e1 7f             	and    $0x7f,%ecx
    7fa134997cb5:	d1 e1                	shl    %ecx
    7fa134997cb7:	8b d0                	mov    %eax,%edx
    7fa134997cb9:	c1 ea 07             	shr    $0x7,%edx
    7fa134997cbc:	83 e2 01             	and    $0x1,%edx
    7fa134997cbf:	8b fa                	mov    %edx,%edi
    7fa134997cc1:	d1 e7                	shl    %edi
    7fa134997cc3:	0b fa                	or     %edx,%edi
    7fa134997cc5:	44 8b c2             	mov    %edx,%r8d
    7fa134997cc8:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134997ccc:	41 0b f8             	or     %r8d,%edi
    7fa134997ccf:	c1 e2 04             	shl    $0x4,%edx
    7fa134997cd2:	0b fa                	or     %edx,%edi
    7fa134997cd4:	33 cf                	xor    %edi,%ecx
    7fa134997cd6:	49 0f b6 97 11 01 00 	movzbq 0x111(%r15),%rdx
    7fa134997cdd:	00 
    7fa134997cde:	8b d2                	mov    %edx,%edx
    7fa134997ce0:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134997ce5:	8b fa                	mov    %edx,%edi
    7fa134997ce7:	83 e7 7f             	and    $0x7f,%edi
    7fa134997cea:	d1 e7                	shl    %edi
    7fa134997cec:	44 8b c2             	mov    %edx,%r8d
    7fa134997cef:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134997cf3:	41 83 e0 01          	and    $0x1,%r8d
    7fa134997cf7:	45 8b c8             	mov    %r8d,%r9d
    7fa134997cfa:	41 d1 e1             	shl    %r9d
    7fa134997cfd:	45 0b c8             	or     %r8d,%r9d
    7fa134997d00:	44 89 85 58 fe ff ff 	mov    %r8d,-0x1a8(%rbp)
    7fa134997d07:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134997d0b:	45 0b c8             	or     %r8d,%r9d
    7fa134997d0e:	44 8b 85 58 fe ff ff 	mov    -0x1a8(%rbp),%r8d
    7fa134997d15:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134997d19:	45 0b c8             	or     %r8d,%r9d
    7fa134997d1c:	41 33 f9             	xor    %r9d,%edi
    7fa134997d1f:	44 8b c7             	mov    %edi,%r8d
    7fa134997d22:	44 33 c2             	xor    %edx,%r8d
    7fa134997d25:	44 33 c1             	xor    %ecx,%r8d
    7fa134997d28:	4d 0f b6 8f 16 01 00 	movzbq 0x116(%r15),%r9
    7fa134997d2f:	00 
    7fa134997d30:	45 8b c9             	mov    %r9d,%r9d
    7fa134997d33:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa134997d38:	45 33 c1             	xor    %r9d,%r8d
    7fa134997d3b:	44 89 95 50 fe ff ff 	mov    %r10d,-0x1b0(%rbp)
    7fa134997d42:	4d 0f b6 97 1b 01 00 	movzbq 0x11b(%r15),%r10
    7fa134997d49:	00 
    7fa134997d4a:	45 8b d2             	mov    %r10d,%r10d
    7fa134997d4d:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa134997d52:	45 33 c2             	xor    %r10d,%r8d
    7fa134997d55:	33 f8                	xor    %eax,%edi
    7fa134997d57:	44 89 8d 48 fe ff ff 	mov    %r9d,-0x1b8(%rbp)
    7fa134997d5e:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134997d62:	41 d1 e1             	shl    %r9d
    7fa134997d65:	89 9d 40 fe ff ff    	mov    %ebx,-0x1c0(%rbp)
    7fa134997d6b:	8b 9d 48 fe ff ff    	mov    -0x1b8(%rbp),%ebx
    7fa134997d71:	c1 eb 07             	shr    $0x7,%ebx
    7fa134997d74:	83 e3 01             	and    $0x1,%ebx
    7fa134997d77:	89 9d 38 fe ff ff    	mov    %ebx,-0x1c8(%rbp)
    7fa134997d7d:	d1 e3                	shl    %ebx
    7fa134997d7f:	44 89 9d 30 fe ff ff 	mov    %r11d,-0x1d0(%rbp)
    7fa134997d86:	44 8b 9d 38 fe ff ff 	mov    -0x1c8(%rbp),%r11d
    7fa134997d8d:	41 0b db             	or     %r11d,%ebx
    7fa134997d90:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134997d94:	41 0b db             	or     %r11d,%ebx
    7fa134997d97:	44 8b 9d 38 fe ff ff 	mov    -0x1c8(%rbp),%r11d
    7fa134997d9e:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134997da2:	41 0b db             	or     %r11d,%ebx
    7fa134997da5:	44 33 cb             	xor    %ebx,%r9d
    7fa134997da8:	41 8b d9             	mov    %r9d,%ebx
    7fa134997dab:	44 8b 9d 48 fe ff ff 	mov    -0x1b8(%rbp),%r11d
    7fa134997db2:	41 33 db             	xor    %r11d,%ebx
    7fa134997db5:	33 fb                	xor    %ebx,%edi
    7fa134997db7:	41 33 fa             	xor    %r10d,%edi
    7fa134997dba:	8b d8                	mov    %eax,%ebx
    7fa134997dbc:	33 da                	xor    %edx,%ebx
    7fa134997dbe:	44 33 cb             	xor    %ebx,%r9d
    7fa134997dc1:	41 8b da             	mov    %r10d,%ebx
    7fa134997dc4:	83 e3 7f             	and    $0x7f,%ebx
    7fa134997dc7:	d1 e3                	shl    %ebx
    7fa134997dc9:	45 8b da             	mov    %r10d,%r11d
    7fa134997dcc:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134997dd0:	41 83 e3 01          	and    $0x1,%r11d
    7fa134997dd4:	44 89 9d 28 fe ff ff 	mov    %r11d,-0x1d8(%rbp)
    7fa134997ddb:	41 d1 e3             	shl    %r11d
    7fa134997dde:	89 b5 20 fe ff ff    	mov    %esi,-0x1e0(%rbp)
    7fa134997de4:	8b b5 28 fe ff ff    	mov    -0x1d8(%rbp),%esi
    7fa134997dea:	44 0b de             	or     %esi,%r11d
    7fa134997ded:	c1 e6 03             	shl    $0x3,%esi
    7fa134997df0:	44 0b de             	or     %esi,%r11d
    7fa134997df3:	8b b5 28 fe ff ff    	mov    -0x1d8(%rbp),%esi
    7fa134997df9:	c1 e6 04             	shl    $0x4,%esi
    7fa134997dfc:	44 0b de             	or     %esi,%r11d
    7fa134997dff:	41 33 db             	xor    %r11d,%ebx
    7fa134997e02:	44 33 d3             	xor    %ebx,%r10d
    7fa134997e05:	45 33 ca             	xor    %r10d,%r9d
    7fa134997e08:	33 c8                	xor    %eax,%ecx
    7fa134997e0a:	33 d1                	xor    %ecx,%edx
    7fa134997e0c:	33 95 48 fe ff ff    	xor    -0x1b8(%rbp),%edx
    7fa134997e12:	33 da                	xor    %edx,%ebx
    7fa134997e14:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fa134997e1a:	c1 e0 08             	shl    $0x8,%eax
    7fa134997e1d:	0b 85 d0 fe ff ff    	or     -0x130(%rbp),%eax
    7fa134997e23:	8b 8d b0 fe ff ff    	mov    -0x150(%rbp),%ecx
    7fa134997e29:	c1 e1 10             	shl    $0x10,%ecx
    7fa134997e2c:	0b c1                	or     %ecx,%eax
    7fa134997e2e:	8b 8d a0 fe ff ff    	mov    -0x160(%rbp),%ecx
    7fa134997e34:	c1 e1 18             	shl    $0x18,%ecx
    7fa134997e37:	0b c1                	or     %ecx,%eax
    7fa134997e39:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fa134997e3f:	8b c9                	mov    %ecx,%ecx
    7fa134997e41:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa134997e45:	8b c0                	mov    %eax,%eax
    7fa134997e47:	48 0b c8             	or     %rax,%rcx
    7fa134997e4a:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fa134997e50:	8b c0                	mov    %eax,%eax
    7fa134997e52:	48 c1 e0 28          	shl    $0x28,%rax
    7fa134997e56:	48 0b c8             	or     %rax,%rcx
    7fa134997e59:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fa134997e5f:	8b c0                	mov    %eax,%eax
    7fa134997e61:	48 c1 e0 30          	shl    $0x30,%rax
    7fa134997e65:	48 0b c8             	or     %rax,%rcx
    7fa134997e68:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7fa134997e6e:	8b c0                	mov    %eax,%eax
    7fa134997e70:	48 c1 e0 38          	shl    $0x38,%rax
    7fa134997e74:	48 0b c8             	or     %rax,%rcx
    7fa134997e77:	49 89 8f 70 02 00 00 	mov    %rcx,0x270(%r15)
    7fa134997e7e:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fa134997e84:	c1 e0 08             	shl    $0x8,%eax
    7fa134997e87:	0b 85 50 fe ff ff    	or     -0x1b0(%rbp),%eax
    7fa134997e8d:	8b 8d 30 fe ff ff    	mov    -0x1d0(%rbp),%ecx
    7fa134997e93:	c1 e1 10             	shl    $0x10,%ecx
    7fa134997e96:	0b c1                	or     %ecx,%eax
    7fa134997e98:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7fa134997e9e:	c1 e1 18             	shl    $0x18,%ecx
    7fa134997ea1:	0b c1                	or     %ecx,%eax
    7fa134997ea3:	45 8b c0             	mov    %r8d,%r8d
    7fa134997ea6:	49 c1 e0 20          	shl    $0x20,%r8
    7fa134997eaa:	8b c0                	mov    %eax,%eax
    7fa134997eac:	4c 0b c0             	or     %rax,%r8
    7fa134997eaf:	8b ff                	mov    %edi,%edi
    7fa134997eb1:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa134997eb5:	4c 0b c7             	or     %rdi,%r8
    7fa134997eb8:	45 8b c9             	mov    %r9d,%r9d
    7fa134997ebb:	49 c1 e1 30          	shl    $0x30,%r9
    7fa134997ebf:	4d 0b c1             	or     %r9,%r8
    7fa134997ec2:	8b db                	mov    %ebx,%ebx
    7fa134997ec4:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa134997ec8:	4c 0b c3             	or     %rbx,%r8
    7fa134997ecb:	4d 89 87 78 02 00 00 	mov    %r8,0x278(%r15)
    7fa134997ed2:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7fa134997ed8:	25 ff 00 00 00       	and    $0xff,%eax
    7fa134997edd:	8b c0                	mov    %eax,%eax
    7fa134997edf:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134997ee4:	8b 8d f0 fe ff ff    	mov    -0x110(%rbp),%ecx
    7fa134997eea:	c1 e9 18             	shr    $0x18,%ecx
    7fa134997eed:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa134997ef3:	8b c9                	mov    %ecx,%ecx
    7fa134997ef5:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa134997efa:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fa134997f00:	c1 ea 10             	shr    $0x10,%edx
    7fa134997f03:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa134997f09:	8b d2                	mov    %edx,%edx
    7fa134997f0b:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134997f10:	8b 9d f0 fe ff ff    	mov    -0x110(%rbp),%ebx
    7fa134997f16:	c1 eb 08             	shr    $0x8,%ebx
    7fa134997f19:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa134997f1f:	8b db                	mov    %ebx,%ebx
    7fa134997f21:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134997f26:	c1 e2 08             	shl    $0x8,%edx
    7fa134997f29:	0b da                	or     %edx,%ebx
    7fa134997f2b:	c1 e1 10             	shl    $0x10,%ecx
    7fa134997f2e:	0b d9                	or     %ecx,%ebx
    7fa134997f30:	c1 e0 18             	shl    $0x18,%eax
    7fa134997f33:	0b d8                	or     %eax,%ebx
    7fa134997f35:	83 f3 02             	xor    $0x2,%ebx
    7fa134997f38:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fa134997f3e:	33 d8                	xor    %eax,%ebx
    7fa134997f40:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fa134997f46:	33 c3                	xor    %ebx,%eax
    7fa134997f48:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7fa134997f4e:	33 c8                	xor    %eax,%ecx
    7fa134997f50:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fa134997f56:	33 d1                	xor    %ecx,%edx
    7fa134997f58:	8b f0                	mov    %eax,%esi
    7fa134997f5a:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa134997f5e:	8b fb                	mov    %ebx,%edi
    7fa134997f60:	48 0b f7             	or     %rdi,%rsi
    7fa134997f63:	49 89 b7 d0 01 00 00 	mov    %rsi,0x1d0(%r15)
    7fa134997f6a:	8b f2                	mov    %edx,%esi
    7fa134997f6c:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa134997f70:	8b f9                	mov    %ecx,%edi
    7fa134997f72:	48 0b f7             	or     %rdi,%rsi
    7fa134997f75:	49 89 b7 d8 01 00 00 	mov    %rsi,0x1d8(%r15)
    7fa134997f7c:	49 8b b7 70 02 00 00 	mov    0x270(%r15),%rsi
    7fa134997f83:	49 8b bf d0 01 00 00 	mov    0x1d0(%r15),%rdi
    7fa134997f8a:	48 33 f7             	xor    %rdi,%rsi
    7fa134997f8d:	49 89 b7 20 03 00 00 	mov    %rsi,0x320(%r15)
    7fa134997f94:	49 8b b7 78 02 00 00 	mov    0x278(%r15),%rsi
    7fa134997f9b:	49 8b bf d8 01 00 00 	mov    0x1d8(%r15),%rdi
    7fa134997fa2:	48 33 f7             	xor    %rdi,%rsi
    7fa134997fa5:	49 89 b7 28 03 00 00 	mov    %rsi,0x328(%r15)
    7fa134997fac:	49 0f b6 b7 20 01 00 	movzbq 0x120(%r15),%rsi
    7fa134997fb3:	00 
    7fa134997fb4:	8b f6                	mov    %esi,%esi
    7fa134997fb6:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa134997fbb:	8b fe                	mov    %esi,%edi
    7fa134997fbd:	83 e7 7f             	and    $0x7f,%edi
    7fa134997fc0:	d1 e7                	shl    %edi
    7fa134997fc2:	44 8b c6             	mov    %esi,%r8d
    7fa134997fc5:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134997fc9:	41 83 e0 01          	and    $0x1,%r8d
    7fa134997fcd:	45 8b c8             	mov    %r8d,%r9d
    7fa134997fd0:	41 d1 e1             	shl    %r9d
    7fa134997fd3:	45 0b c8             	or     %r8d,%r9d
    7fa134997fd6:	45 8b d0             	mov    %r8d,%r10d
    7fa134997fd9:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134997fdd:	45 0b ca             	or     %r10d,%r9d
    7fa134997fe0:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134997fe4:	45 0b c8             	or     %r8d,%r9d
    7fa134997fe7:	41 33 f9             	xor    %r9d,%edi
    7fa134997fea:	4d 0f b6 87 25 01 00 	movzbq 0x125(%r15),%r8
    7fa134997ff1:	00 
    7fa134997ff2:	45 8b c0             	mov    %r8d,%r8d
    7fa134997ff5:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134997ffa:	45 8b c8             	mov    %r8d,%r9d
    7fa134997ffd:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134998001:	41 d1 e1             	shl    %r9d
    7fa134998004:	45 8b d0             	mov    %r8d,%r10d
    7fa134998007:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499800b:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499800f:	45 8b da             	mov    %r10d,%r11d
    7fa134998012:	41 d1 e3             	shl    %r11d
    7fa134998015:	45 0b da             	or     %r10d,%r11d
    7fa134998018:	44 89 95 18 fe ff ff 	mov    %r10d,-0x1e8(%rbp)
    7fa13499801f:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134998023:	45 0b da             	or     %r10d,%r11d
    7fa134998026:	44 8b 95 18 fe ff ff 	mov    -0x1e8(%rbp),%r10d
    7fa13499802d:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134998031:	45 0b da             	or     %r10d,%r11d
    7fa134998034:	45 33 cb             	xor    %r11d,%r9d
    7fa134998037:	45 8b d1             	mov    %r9d,%r10d
    7fa13499803a:	45 33 d0             	xor    %r8d,%r10d
    7fa13499803d:	44 33 d7             	xor    %edi,%r10d
    7fa134998040:	4d 0f b6 9f 2a 01 00 	movzbq 0x12a(%r15),%r11
    7fa134998047:	00 
    7fa134998048:	45 8b db             	mov    %r11d,%r11d
    7fa13499804b:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134998050:	45 33 d3             	xor    %r11d,%r10d
    7fa134998053:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7fa134998059:	49 0f b6 87 2f 01 00 	movzbq 0x12f(%r15),%rax
    7fa134998060:	00 
    7fa134998061:	8b c0                	mov    %eax,%eax
    7fa134998063:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998068:	44 33 d0             	xor    %eax,%r10d
    7fa13499806b:	44 33 ce             	xor    %esi,%r9d
    7fa13499806e:	44 89 9d 08 fe ff ff 	mov    %r11d,-0x1f8(%rbp)
    7fa134998075:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134998079:	41 d1 e3             	shl    %r11d
    7fa13499807c:	89 9d 00 fe ff ff    	mov    %ebx,-0x200(%rbp)
    7fa134998082:	8b 9d 08 fe ff ff    	mov    -0x1f8(%rbp),%ebx
    7fa134998088:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499808b:	83 e3 01             	and    $0x1,%ebx
    7fa13499808e:	89 9d f8 fd ff ff    	mov    %ebx,-0x208(%rbp)
    7fa134998094:	d1 e3                	shl    %ebx
    7fa134998096:	89 95 f0 fd ff ff    	mov    %edx,-0x210(%rbp)
    7fa13499809c:	8b 95 f8 fd ff ff    	mov    -0x208(%rbp),%edx
    7fa1349980a2:	0b da                	or     %edx,%ebx
    7fa1349980a4:	c1 e2 03             	shl    $0x3,%edx
    7fa1349980a7:	0b da                	or     %edx,%ebx
    7fa1349980a9:	8b 95 f8 fd ff ff    	mov    -0x208(%rbp),%edx
    7fa1349980af:	c1 e2 04             	shl    $0x4,%edx
    7fa1349980b2:	0b da                	or     %edx,%ebx
    7fa1349980b4:	44 33 db             	xor    %ebx,%r11d
    7fa1349980b7:	41 8b d3             	mov    %r11d,%edx
    7fa1349980ba:	8b 9d 08 fe ff ff    	mov    -0x1f8(%rbp),%ebx
    7fa1349980c0:	33 d3                	xor    %ebx,%edx
    7fa1349980c2:	44 33 ca             	xor    %edx,%r9d
    7fa1349980c5:	44 33 c8             	xor    %eax,%r9d
    7fa1349980c8:	8b d6                	mov    %esi,%edx
    7fa1349980ca:	41 33 d0             	xor    %r8d,%edx
    7fa1349980cd:	44 33 da             	xor    %edx,%r11d
    7fa1349980d0:	8b d0                	mov    %eax,%edx
    7fa1349980d2:	83 e2 7f             	and    $0x7f,%edx
    7fa1349980d5:	d1 e2                	shl    %edx
    7fa1349980d7:	8b d8                	mov    %eax,%ebx
    7fa1349980d9:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349980dc:	83 e3 01             	and    $0x1,%ebx
    7fa1349980df:	89 9d e8 fd ff ff    	mov    %ebx,-0x218(%rbp)
    7fa1349980e5:	d1 e3                	shl    %ebx
    7fa1349980e7:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fa1349980ed:	8b 8d e8 fd ff ff    	mov    -0x218(%rbp),%ecx
    7fa1349980f3:	0b d9                	or     %ecx,%ebx
    7fa1349980f5:	c1 e1 03             	shl    $0x3,%ecx
    7fa1349980f8:	0b d9                	or     %ecx,%ebx
    7fa1349980fa:	8b 8d e8 fd ff ff    	mov    -0x218(%rbp),%ecx
    7fa134998100:	c1 e1 04             	shl    $0x4,%ecx
    7fa134998103:	0b d9                	or     %ecx,%ebx
    7fa134998105:	33 d3                	xor    %ebx,%edx
    7fa134998107:	33 c2                	xor    %edx,%eax
    7fa134998109:	44 33 d8             	xor    %eax,%r11d
    7fa13499810c:	33 fe                	xor    %esi,%edi
    7fa13499810e:	44 33 c7             	xor    %edi,%r8d
    7fa134998111:	44 33 85 08 fe ff ff 	xor    -0x1f8(%rbp),%r8d
    7fa134998118:	41 33 d0             	xor    %r8d,%edx
    7fa13499811b:	49 0f b6 87 24 01 00 	movzbq 0x124(%r15),%rax
    7fa134998122:	00 
    7fa134998123:	8b c0                	mov    %eax,%eax
    7fa134998125:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499812a:	8b c8                	mov    %eax,%ecx
    7fa13499812c:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499812f:	d1 e1                	shl    %ecx
    7fa134998131:	8b d8                	mov    %eax,%ebx
    7fa134998133:	c1 eb 07             	shr    $0x7,%ebx
    7fa134998136:	83 e3 01             	and    $0x1,%ebx
    7fa134998139:	8b f3                	mov    %ebx,%esi
    7fa13499813b:	d1 e6                	shl    %esi
    7fa13499813d:	0b f3                	or     %ebx,%esi
    7fa13499813f:	8b fb                	mov    %ebx,%edi
    7fa134998141:	c1 e7 03             	shl    $0x3,%edi
    7fa134998144:	0b f7                	or     %edi,%esi
    7fa134998146:	c1 e3 04             	shl    $0x4,%ebx
    7fa134998149:	0b f3                	or     %ebx,%esi
    7fa13499814b:	33 ce                	xor    %esi,%ecx
    7fa13499814d:	49 0f b6 9f 29 01 00 	movzbq 0x129(%r15),%rbx
    7fa134998154:	00 
    7fa134998155:	8b db                	mov    %ebx,%ebx
    7fa134998157:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499815c:	8b f3                	mov    %ebx,%esi
    7fa13499815e:	83 e6 7f             	and    $0x7f,%esi
    7fa134998161:	d1 e6                	shl    %esi
    7fa134998163:	8b fb                	mov    %ebx,%edi
    7fa134998165:	c1 ef 07             	shr    $0x7,%edi
    7fa134998168:	83 e7 01             	and    $0x1,%edi
    7fa13499816b:	44 8b c7             	mov    %edi,%r8d
    7fa13499816e:	41 d1 e0             	shl    %r8d
    7fa134998171:	44 0b c7             	or     %edi,%r8d
    7fa134998174:	89 bd d8 fd ff ff    	mov    %edi,-0x228(%rbp)
    7fa13499817a:	c1 e7 03             	shl    $0x3,%edi
    7fa13499817d:	44 0b c7             	or     %edi,%r8d
    7fa134998180:	8b bd d8 fd ff ff    	mov    -0x228(%rbp),%edi
    7fa134998186:	c1 e7 04             	shl    $0x4,%edi
    7fa134998189:	44 0b c7             	or     %edi,%r8d
    7fa13499818c:	41 33 f0             	xor    %r8d,%esi
    7fa13499818f:	8b fe                	mov    %esi,%edi
    7fa134998191:	33 fb                	xor    %ebx,%edi
    7fa134998193:	33 f9                	xor    %ecx,%edi
    7fa134998195:	4d 0f b6 87 2e 01 00 	movzbq 0x12e(%r15),%r8
    7fa13499819c:	00 
    7fa13499819d:	45 8b c0             	mov    %r8d,%r8d
    7fa1349981a0:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa1349981a5:	41 33 f8             	xor    %r8d,%edi
    7fa1349981a8:	44 89 95 d0 fd ff ff 	mov    %r10d,-0x230(%rbp)
    7fa1349981af:	4d 0f b6 97 23 01 00 	movzbq 0x123(%r15),%r10
    7fa1349981b6:	00 
    7fa1349981b7:	45 8b d2             	mov    %r10d,%r10d
    7fa1349981ba:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa1349981bf:	41 33 fa             	xor    %r10d,%edi
    7fa1349981c2:	33 f0                	xor    %eax,%esi
    7fa1349981c4:	44 89 85 c8 fd ff ff 	mov    %r8d,-0x238(%rbp)
    7fa1349981cb:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa1349981cf:	41 d1 e0             	shl    %r8d
    7fa1349981d2:	44 89 8d c0 fd ff ff 	mov    %r9d,-0x240(%rbp)
    7fa1349981d9:	44 8b 8d c8 fd ff ff 	mov    -0x238(%rbp),%r9d
    7fa1349981e0:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa1349981e4:	41 83 e1 01          	and    $0x1,%r9d
    7fa1349981e8:	44 89 8d b8 fd ff ff 	mov    %r9d,-0x248(%rbp)
    7fa1349981ef:	41 d1 e1             	shl    %r9d
    7fa1349981f2:	44 89 9d b0 fd ff ff 	mov    %r11d,-0x250(%rbp)
    7fa1349981f9:	44 8b 9d b8 fd ff ff 	mov    -0x248(%rbp),%r11d
    7fa134998200:	45 0b cb             	or     %r11d,%r9d
    7fa134998203:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134998207:	45 0b cb             	or     %r11d,%r9d
    7fa13499820a:	44 8b 9d b8 fd ff ff 	mov    -0x248(%rbp),%r11d
    7fa134998211:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134998215:	45 0b cb             	or     %r11d,%r9d
    7fa134998218:	45 33 c1             	xor    %r9d,%r8d
    7fa13499821b:	45 8b c8             	mov    %r8d,%r9d
    7fa13499821e:	44 8b 9d c8 fd ff ff 	mov    -0x238(%rbp),%r11d
    7fa134998225:	45 33 cb             	xor    %r11d,%r9d
    7fa134998228:	41 33 f1             	xor    %r9d,%esi
    7fa13499822b:	41 33 f2             	xor    %r10d,%esi
    7fa13499822e:	44 8b c8             	mov    %eax,%r9d
    7fa134998231:	44 33 cb             	xor    %ebx,%r9d
    7fa134998234:	45 33 c1             	xor    %r9d,%r8d
    7fa134998237:	45 8b ca             	mov    %r10d,%r9d
    7fa13499823a:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499823e:	41 d1 e1             	shl    %r9d
    7fa134998241:	45 8b da             	mov    %r10d,%r11d
    7fa134998244:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134998248:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499824c:	44 89 9d a8 fd ff ff 	mov    %r11d,-0x258(%rbp)
    7fa134998253:	41 d1 e3             	shl    %r11d
    7fa134998256:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7fa13499825c:	8b 95 a8 fd ff ff    	mov    -0x258(%rbp),%edx
    7fa134998262:	44 0b da             	or     %edx,%r11d
    7fa134998265:	c1 e2 03             	shl    $0x3,%edx
    7fa134998268:	44 0b da             	or     %edx,%r11d
    7fa13499826b:	8b 95 a8 fd ff ff    	mov    -0x258(%rbp),%edx
    7fa134998271:	c1 e2 04             	shl    $0x4,%edx
    7fa134998274:	44 0b da             	or     %edx,%r11d
    7fa134998277:	45 33 cb             	xor    %r11d,%r9d
    7fa13499827a:	45 33 d1             	xor    %r9d,%r10d
    7fa13499827d:	45 33 c2             	xor    %r10d,%r8d
    7fa134998280:	33 c8                	xor    %eax,%ecx
    7fa134998282:	33 d9                	xor    %ecx,%ebx
    7fa134998284:	33 9d c8 fd ff ff    	xor    -0x238(%rbp),%ebx
    7fa13499828a:	44 33 cb             	xor    %ebx,%r9d
    7fa13499828d:	49 0f b6 87 28 01 00 	movzbq 0x128(%r15),%rax
    7fa134998294:	00 
    7fa134998295:	8b c0                	mov    %eax,%eax
    7fa134998297:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499829c:	8b c8                	mov    %eax,%ecx
    7fa13499829e:	83 e1 7f             	and    $0x7f,%ecx
    7fa1349982a1:	d1 e1                	shl    %ecx
    7fa1349982a3:	8b d0                	mov    %eax,%edx
    7fa1349982a5:	c1 ea 07             	shr    $0x7,%edx
    7fa1349982a8:	83 e2 01             	and    $0x1,%edx
    7fa1349982ab:	8b da                	mov    %edx,%ebx
    7fa1349982ad:	d1 e3                	shl    %ebx
    7fa1349982af:	0b da                	or     %edx,%ebx
    7fa1349982b1:	44 8b d2             	mov    %edx,%r10d
    7fa1349982b4:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349982b8:	41 0b da             	or     %r10d,%ebx
    7fa1349982bb:	c1 e2 04             	shl    $0x4,%edx
    7fa1349982be:	0b da                	or     %edx,%ebx
    7fa1349982c0:	33 cb                	xor    %ebx,%ecx
    7fa1349982c2:	49 0f b6 97 2d 01 00 	movzbq 0x12d(%r15),%rdx
    7fa1349982c9:	00 
    7fa1349982ca:	8b d2                	mov    %edx,%edx
    7fa1349982cc:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa1349982d1:	8b da                	mov    %edx,%ebx
    7fa1349982d3:	83 e3 7f             	and    $0x7f,%ebx
    7fa1349982d6:	d1 e3                	shl    %ebx
    7fa1349982d8:	44 8b d2             	mov    %edx,%r10d
    7fa1349982db:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa1349982df:	41 83 e2 01          	and    $0x1,%r10d
    7fa1349982e3:	45 8b da             	mov    %r10d,%r11d
    7fa1349982e6:	41 d1 e3             	shl    %r11d
    7fa1349982e9:	45 0b da             	or     %r10d,%r11d
    7fa1349982ec:	44 89 95 98 fd ff ff 	mov    %r10d,-0x268(%rbp)
    7fa1349982f3:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349982f7:	45 0b da             	or     %r10d,%r11d
    7fa1349982fa:	44 8b 95 98 fd ff ff 	mov    -0x268(%rbp),%r10d
    7fa134998301:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134998305:	45 0b da             	or     %r10d,%r11d
    7fa134998308:	41 33 db             	xor    %r11d,%ebx
    7fa13499830b:	44 8b d3             	mov    %ebx,%r10d
    7fa13499830e:	44 33 d2             	xor    %edx,%r10d
    7fa134998311:	44 33 d1             	xor    %ecx,%r10d
    7fa134998314:	4d 0f b6 9f 22 01 00 	movzbq 0x122(%r15),%r11
    7fa13499831b:	00 
    7fa13499831c:	45 8b db             	mov    %r11d,%r11d
    7fa13499831f:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134998324:	45 33 d3             	xor    %r11d,%r10d
    7fa134998327:	89 bd 90 fd ff ff    	mov    %edi,-0x270(%rbp)
    7fa13499832d:	49 0f b6 bf 27 01 00 	movzbq 0x127(%r15),%rdi
    7fa134998334:	00 
    7fa134998335:	8b ff                	mov    %edi,%edi
    7fa134998337:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499833c:	44 33 d7             	xor    %edi,%r10d
    7fa13499833f:	33 d8                	xor    %eax,%ebx
    7fa134998341:	44 89 9d 88 fd ff ff 	mov    %r11d,-0x278(%rbp)
    7fa134998348:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499834c:	41 d1 e3             	shl    %r11d
    7fa13499834f:	89 b5 80 fd ff ff    	mov    %esi,-0x280(%rbp)
    7fa134998355:	8b b5 88 fd ff ff    	mov    -0x278(%rbp),%esi
    7fa13499835b:	c1 ee 07             	shr    $0x7,%esi
    7fa13499835e:	83 e6 01             	and    $0x1,%esi
    7fa134998361:	89 b5 78 fd ff ff    	mov    %esi,-0x288(%rbp)
    7fa134998367:	d1 e6                	shl    %esi
    7fa134998369:	44 89 85 70 fd ff ff 	mov    %r8d,-0x290(%rbp)
    7fa134998370:	44 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%r8d
    7fa134998377:	41 0b f0             	or     %r8d,%esi
    7fa13499837a:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499837e:	41 0b f0             	or     %r8d,%esi
    7fa134998381:	44 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%r8d
    7fa134998388:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499838c:	41 0b f0             	or     %r8d,%esi
    7fa13499838f:	44 33 de             	xor    %esi,%r11d
    7fa134998392:	41 8b f3             	mov    %r11d,%esi
    7fa134998395:	44 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%r8d
    7fa13499839c:	41 33 f0             	xor    %r8d,%esi
    7fa13499839f:	33 de                	xor    %esi,%ebx
    7fa1349983a1:	33 df                	xor    %edi,%ebx
    7fa1349983a3:	8b f0                	mov    %eax,%esi
    7fa1349983a5:	33 f2                	xor    %edx,%esi
    7fa1349983a7:	44 33 de             	xor    %esi,%r11d
    7fa1349983aa:	8b f7                	mov    %edi,%esi
    7fa1349983ac:	83 e6 7f             	and    $0x7f,%esi
    7fa1349983af:	d1 e6                	shl    %esi
    7fa1349983b1:	44 8b c7             	mov    %edi,%r8d
    7fa1349983b4:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa1349983b8:	41 83 e0 01          	and    $0x1,%r8d
    7fa1349983bc:	44 89 85 68 fd ff ff 	mov    %r8d,-0x298(%rbp)
    7fa1349983c3:	41 d1 e0             	shl    %r8d
    7fa1349983c6:	44 89 8d 60 fd ff ff 	mov    %r9d,-0x2a0(%rbp)
    7fa1349983cd:	44 8b 8d 68 fd ff ff 	mov    -0x298(%rbp),%r9d
    7fa1349983d4:	45 0b c1             	or     %r9d,%r8d
    7fa1349983d7:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa1349983db:	45 0b c1             	or     %r9d,%r8d
    7fa1349983de:	44 8b 8d 68 fd ff ff 	mov    -0x298(%rbp),%r9d
    7fa1349983e5:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa1349983e9:	45 0b c1             	or     %r9d,%r8d
    7fa1349983ec:	41 33 f0             	xor    %r8d,%esi
    7fa1349983ef:	33 fe                	xor    %esi,%edi
    7fa1349983f1:	44 33 df             	xor    %edi,%r11d
    7fa1349983f4:	33 c8                	xor    %eax,%ecx
    7fa1349983f6:	33 d1                	xor    %ecx,%edx
    7fa1349983f8:	33 95 88 fd ff ff    	xor    -0x278(%rbp),%edx
    7fa1349983fe:	33 f2                	xor    %edx,%esi
    7fa134998400:	49 0f b6 87 2c 01 00 	movzbq 0x12c(%r15),%rax
    7fa134998407:	00 
    7fa134998408:	8b c0                	mov    %eax,%eax
    7fa13499840a:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499840f:	8b c8                	mov    %eax,%ecx
    7fa134998411:	83 e1 7f             	and    $0x7f,%ecx
    7fa134998414:	d1 e1                	shl    %ecx
    7fa134998416:	8b d0                	mov    %eax,%edx
    7fa134998418:	c1 ea 07             	shr    $0x7,%edx
    7fa13499841b:	83 e2 01             	and    $0x1,%edx
    7fa13499841e:	8b fa                	mov    %edx,%edi
    7fa134998420:	d1 e7                	shl    %edi
    7fa134998422:	0b fa                	or     %edx,%edi
    7fa134998424:	44 8b c2             	mov    %edx,%r8d
    7fa134998427:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499842b:	41 0b f8             	or     %r8d,%edi
    7fa13499842e:	c1 e2 04             	shl    $0x4,%edx
    7fa134998431:	0b fa                	or     %edx,%edi
    7fa134998433:	33 cf                	xor    %edi,%ecx
    7fa134998435:	49 0f b6 97 21 01 00 	movzbq 0x121(%r15),%rdx
    7fa13499843c:	00 
    7fa13499843d:	8b d2                	mov    %edx,%edx
    7fa13499843f:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134998444:	8b fa                	mov    %edx,%edi
    7fa134998446:	83 e7 7f             	and    $0x7f,%edi
    7fa134998449:	d1 e7                	shl    %edi
    7fa13499844b:	44 8b c2             	mov    %edx,%r8d
    7fa13499844e:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134998452:	41 83 e0 01          	and    $0x1,%r8d
    7fa134998456:	45 8b c8             	mov    %r8d,%r9d
    7fa134998459:	41 d1 e1             	shl    %r9d
    7fa13499845c:	45 0b c8             	or     %r8d,%r9d
    7fa13499845f:	44 89 85 58 fd ff ff 	mov    %r8d,-0x2a8(%rbp)
    7fa134998466:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499846a:	45 0b c8             	or     %r8d,%r9d
    7fa13499846d:	44 8b 85 58 fd ff ff 	mov    -0x2a8(%rbp),%r8d
    7fa134998474:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134998478:	45 0b c8             	or     %r8d,%r9d
    7fa13499847b:	41 33 f9             	xor    %r9d,%edi
    7fa13499847e:	44 8b c7             	mov    %edi,%r8d
    7fa134998481:	44 33 c2             	xor    %edx,%r8d
    7fa134998484:	44 33 c1             	xor    %ecx,%r8d
    7fa134998487:	4d 0f b6 8f 26 01 00 	movzbq 0x126(%r15),%r9
    7fa13499848e:	00 
    7fa13499848f:	45 8b c9             	mov    %r9d,%r9d
    7fa134998492:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa134998497:	45 33 c1             	xor    %r9d,%r8d
    7fa13499849a:	44 89 95 50 fd ff ff 	mov    %r10d,-0x2b0(%rbp)
    7fa1349984a1:	4d 0f b6 97 2b 01 00 	movzbq 0x12b(%r15),%r10
    7fa1349984a8:	00 
    7fa1349984a9:	45 8b d2             	mov    %r10d,%r10d
    7fa1349984ac:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa1349984b1:	45 33 c2             	xor    %r10d,%r8d
    7fa1349984b4:	33 f8                	xor    %eax,%edi
    7fa1349984b6:	44 89 8d 48 fd ff ff 	mov    %r9d,-0x2b8(%rbp)
    7fa1349984bd:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa1349984c1:	41 d1 e1             	shl    %r9d
    7fa1349984c4:	89 9d 40 fd ff ff    	mov    %ebx,-0x2c0(%rbp)
    7fa1349984ca:	8b 9d 48 fd ff ff    	mov    -0x2b8(%rbp),%ebx
    7fa1349984d0:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349984d3:	83 e3 01             	and    $0x1,%ebx
    7fa1349984d6:	89 9d 38 fd ff ff    	mov    %ebx,-0x2c8(%rbp)
    7fa1349984dc:	d1 e3                	shl    %ebx
    7fa1349984de:	44 89 9d 30 fd ff ff 	mov    %r11d,-0x2d0(%rbp)
    7fa1349984e5:	44 8b 9d 38 fd ff ff 	mov    -0x2c8(%rbp),%r11d
    7fa1349984ec:	41 0b db             	or     %r11d,%ebx
    7fa1349984ef:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa1349984f3:	41 0b db             	or     %r11d,%ebx
    7fa1349984f6:	44 8b 9d 38 fd ff ff 	mov    -0x2c8(%rbp),%r11d
    7fa1349984fd:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134998501:	41 0b db             	or     %r11d,%ebx
    7fa134998504:	44 33 cb             	xor    %ebx,%r9d
    7fa134998507:	41 8b d9             	mov    %r9d,%ebx
    7fa13499850a:	44 8b 9d 48 fd ff ff 	mov    -0x2b8(%rbp),%r11d
    7fa134998511:	41 33 db             	xor    %r11d,%ebx
    7fa134998514:	33 fb                	xor    %ebx,%edi
    7fa134998516:	41 33 fa             	xor    %r10d,%edi
    7fa134998519:	8b d8                	mov    %eax,%ebx
    7fa13499851b:	33 da                	xor    %edx,%ebx
    7fa13499851d:	44 33 cb             	xor    %ebx,%r9d
    7fa134998520:	41 8b da             	mov    %r10d,%ebx
    7fa134998523:	83 e3 7f             	and    $0x7f,%ebx
    7fa134998526:	d1 e3                	shl    %ebx
    7fa134998528:	45 8b da             	mov    %r10d,%r11d
    7fa13499852b:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499852f:	41 83 e3 01          	and    $0x1,%r11d
    7fa134998533:	44 89 9d 28 fd ff ff 	mov    %r11d,-0x2d8(%rbp)
    7fa13499853a:	41 d1 e3             	shl    %r11d
    7fa13499853d:	89 b5 20 fd ff ff    	mov    %esi,-0x2e0(%rbp)
    7fa134998543:	8b b5 28 fd ff ff    	mov    -0x2d8(%rbp),%esi
    7fa134998549:	44 0b de             	or     %esi,%r11d
    7fa13499854c:	c1 e6 03             	shl    $0x3,%esi
    7fa13499854f:	44 0b de             	or     %esi,%r11d
    7fa134998552:	8b b5 28 fd ff ff    	mov    -0x2d8(%rbp),%esi
    7fa134998558:	c1 e6 04             	shl    $0x4,%esi
    7fa13499855b:	44 0b de             	or     %esi,%r11d
    7fa13499855e:	41 33 db             	xor    %r11d,%ebx
    7fa134998561:	44 33 d3             	xor    %ebx,%r10d
    7fa134998564:	45 33 ca             	xor    %r10d,%r9d
    7fa134998567:	33 c8                	xor    %eax,%ecx
    7fa134998569:	33 d1                	xor    %ecx,%edx
    7fa13499856b:	33 95 48 fd ff ff    	xor    -0x2b8(%rbp),%edx
    7fa134998571:	33 da                	xor    %edx,%ebx
    7fa134998573:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fa134998579:	c1 e0 08             	shl    $0x8,%eax
    7fa13499857c:	0b 85 d0 fd ff ff    	or     -0x230(%rbp),%eax
    7fa134998582:	8b 8d b0 fd ff ff    	mov    -0x250(%rbp),%ecx
    7fa134998588:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499858b:	0b c1                	or     %ecx,%eax
    7fa13499858d:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fa134998593:	c1 e1 18             	shl    $0x18,%ecx
    7fa134998596:	0b c1                	or     %ecx,%eax
    7fa134998598:	8b 8d 90 fd ff ff    	mov    -0x270(%rbp),%ecx
    7fa13499859e:	8b c9                	mov    %ecx,%ecx
    7fa1349985a0:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa1349985a4:	8b c0                	mov    %eax,%eax
    7fa1349985a6:	48 0b c8             	or     %rax,%rcx
    7fa1349985a9:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fa1349985af:	8b c0                	mov    %eax,%eax
    7fa1349985b1:	48 c1 e0 28          	shl    $0x28,%rax
    7fa1349985b5:	48 0b c8             	or     %rax,%rcx
    7fa1349985b8:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fa1349985be:	8b c0                	mov    %eax,%eax
    7fa1349985c0:	48 c1 e0 30          	shl    $0x30,%rax
    7fa1349985c4:	48 0b c8             	or     %rax,%rcx
    7fa1349985c7:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7fa1349985cd:	8b c0                	mov    %eax,%eax
    7fa1349985cf:	48 c1 e0 38          	shl    $0x38,%rax
    7fa1349985d3:	48 0b c8             	or     %rax,%rcx
    7fa1349985d6:	49 89 8f 80 02 00 00 	mov    %rcx,0x280(%r15)
    7fa1349985dd:	8b 85 40 fd ff ff    	mov    -0x2c0(%rbp),%eax
    7fa1349985e3:	c1 e0 08             	shl    $0x8,%eax
    7fa1349985e6:	0b 85 50 fd ff ff    	or     -0x2b0(%rbp),%eax
    7fa1349985ec:	8b 8d 30 fd ff ff    	mov    -0x2d0(%rbp),%ecx
    7fa1349985f2:	c1 e1 10             	shl    $0x10,%ecx
    7fa1349985f5:	0b c1                	or     %ecx,%eax
    7fa1349985f7:	8b 8d 20 fd ff ff    	mov    -0x2e0(%rbp),%ecx
    7fa1349985fd:	c1 e1 18             	shl    $0x18,%ecx
    7fa134998600:	0b c1                	or     %ecx,%eax
    7fa134998602:	45 8b c0             	mov    %r8d,%r8d
    7fa134998605:	49 c1 e0 20          	shl    $0x20,%r8
    7fa134998609:	8b c0                	mov    %eax,%eax
    7fa13499860b:	4c 0b c0             	or     %rax,%r8
    7fa13499860e:	8b ff                	mov    %edi,%edi
    7fa134998610:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa134998614:	4c 0b c7             	or     %rdi,%r8
    7fa134998617:	45 8b c9             	mov    %r9d,%r9d
    7fa13499861a:	49 c1 e1 30          	shl    $0x30,%r9
    7fa13499861e:	4d 0b c1             	or     %r9,%r8
    7fa134998621:	8b db                	mov    %ebx,%ebx
    7fa134998623:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa134998627:	4c 0b c3             	or     %rbx,%r8
    7fa13499862a:	4d 89 87 88 02 00 00 	mov    %r8,0x288(%r15)
    7fa134998631:	8b 85 f0 fd ff ff    	mov    -0x210(%rbp),%eax
    7fa134998637:	25 ff 00 00 00       	and    $0xff,%eax
    7fa13499863c:	8b c0                	mov    %eax,%eax
    7fa13499863e:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998643:	8b 8d f0 fd ff ff    	mov    -0x210(%rbp),%ecx
    7fa134998649:	c1 e9 18             	shr    $0x18,%ecx
    7fa13499864c:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa134998652:	8b c9                	mov    %ecx,%ecx
    7fa134998654:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa134998659:	8b 95 f0 fd ff ff    	mov    -0x210(%rbp),%edx
    7fa13499865f:	c1 ea 10             	shr    $0x10,%edx
    7fa134998662:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa134998668:	8b d2                	mov    %edx,%edx
    7fa13499866a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499866f:	8b 9d f0 fd ff ff    	mov    -0x210(%rbp),%ebx
    7fa134998675:	c1 eb 08             	shr    $0x8,%ebx
    7fa134998678:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa13499867e:	8b db                	mov    %ebx,%ebx
    7fa134998680:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134998685:	c1 e2 08             	shl    $0x8,%edx
    7fa134998688:	0b da                	or     %edx,%ebx
    7fa13499868a:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499868d:	0b d9                	or     %ecx,%ebx
    7fa13499868f:	c1 e0 18             	shl    $0x18,%eax
    7fa134998692:	0b d8                	or     %eax,%ebx
    7fa134998694:	83 f3 04             	xor    $0x4,%ebx
    7fa134998697:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7fa13499869d:	33 d8                	xor    %eax,%ebx
    7fa13499869f:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fa1349986a5:	33 c3                	xor    %ebx,%eax
    7fa1349986a7:	8b 8d e0 fd ff ff    	mov    -0x220(%rbp),%ecx
    7fa1349986ad:	33 c8                	xor    %eax,%ecx
    7fa1349986af:	8b 95 f0 fd ff ff    	mov    -0x210(%rbp),%edx
    7fa1349986b5:	33 d1                	xor    %ecx,%edx
    7fa1349986b7:	8b f0                	mov    %eax,%esi
    7fa1349986b9:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa1349986bd:	8b fb                	mov    %ebx,%edi
    7fa1349986bf:	48 0b f7             	or     %rdi,%rsi
    7fa1349986c2:	49 89 b7 e0 01 00 00 	mov    %rsi,0x1e0(%r15)
    7fa1349986c9:	8b f2                	mov    %edx,%esi
    7fa1349986cb:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa1349986cf:	8b f9                	mov    %ecx,%edi
    7fa1349986d1:	48 0b f7             	or     %rdi,%rsi
    7fa1349986d4:	49 89 b7 e8 01 00 00 	mov    %rsi,0x1e8(%r15)
    7fa1349986db:	49 8b b7 80 02 00 00 	mov    0x280(%r15),%rsi
    7fa1349986e2:	49 8b bf e0 01 00 00 	mov    0x1e0(%r15),%rdi
    7fa1349986e9:	48 33 f7             	xor    %rdi,%rsi
    7fa1349986ec:	49 89 b7 30 03 00 00 	mov    %rsi,0x330(%r15)
    7fa1349986f3:	49 8b b7 88 02 00 00 	mov    0x288(%r15),%rsi
    7fa1349986fa:	49 8b bf e8 01 00 00 	mov    0x1e8(%r15),%rdi
    7fa134998701:	48 33 f7             	xor    %rdi,%rsi
    7fa134998704:	49 89 b7 38 03 00 00 	mov    %rsi,0x338(%r15)
    7fa13499870b:	49 0f b6 b7 30 01 00 	movzbq 0x130(%r15),%rsi
    7fa134998712:	00 
    7fa134998713:	8b f6                	mov    %esi,%esi
    7fa134998715:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa13499871a:	8b fe                	mov    %esi,%edi
    7fa13499871c:	83 e7 7f             	and    $0x7f,%edi
    7fa13499871f:	d1 e7                	shl    %edi
    7fa134998721:	44 8b c6             	mov    %esi,%r8d
    7fa134998724:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134998728:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499872c:	45 8b c8             	mov    %r8d,%r9d
    7fa13499872f:	41 d1 e1             	shl    %r9d
    7fa134998732:	45 0b c8             	or     %r8d,%r9d
    7fa134998735:	45 8b d0             	mov    %r8d,%r10d
    7fa134998738:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499873c:	45 0b ca             	or     %r10d,%r9d
    7fa13499873f:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134998743:	45 0b c8             	or     %r8d,%r9d
    7fa134998746:	41 33 f9             	xor    %r9d,%edi
    7fa134998749:	4d 0f b6 87 35 01 00 	movzbq 0x135(%r15),%r8
    7fa134998750:	00 
    7fa134998751:	45 8b c0             	mov    %r8d,%r8d
    7fa134998754:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134998759:	45 8b c8             	mov    %r8d,%r9d
    7fa13499875c:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134998760:	41 d1 e1             	shl    %r9d
    7fa134998763:	45 8b d0             	mov    %r8d,%r10d
    7fa134998766:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499876a:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499876e:	45 8b da             	mov    %r10d,%r11d
    7fa134998771:	41 d1 e3             	shl    %r11d
    7fa134998774:	45 0b da             	or     %r10d,%r11d
    7fa134998777:	44 89 95 18 fd ff ff 	mov    %r10d,-0x2e8(%rbp)
    7fa13499877e:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134998782:	45 0b da             	or     %r10d,%r11d
    7fa134998785:	44 8b 95 18 fd ff ff 	mov    -0x2e8(%rbp),%r10d
    7fa13499878c:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134998790:	45 0b da             	or     %r10d,%r11d
    7fa134998793:	45 33 cb             	xor    %r11d,%r9d
    7fa134998796:	45 8b d1             	mov    %r9d,%r10d
    7fa134998799:	45 33 d0             	xor    %r8d,%r10d
    7fa13499879c:	44 33 d7             	xor    %edi,%r10d
    7fa13499879f:	4d 0f b6 9f 3a 01 00 	movzbq 0x13a(%r15),%r11
    7fa1349987a6:	00 
    7fa1349987a7:	45 8b db             	mov    %r11d,%r11d
    7fa1349987aa:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa1349987af:	45 33 d3             	xor    %r11d,%r10d
    7fa1349987b2:	89 85 10 fd ff ff    	mov    %eax,-0x2f0(%rbp)
    7fa1349987b8:	49 0f b6 87 3f 01 00 	movzbq 0x13f(%r15),%rax
    7fa1349987bf:	00 
    7fa1349987c0:	8b c0                	mov    %eax,%eax
    7fa1349987c2:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa1349987c7:	44 33 d0             	xor    %eax,%r10d
    7fa1349987ca:	44 33 ce             	xor    %esi,%r9d
    7fa1349987cd:	44 89 9d 08 fd ff ff 	mov    %r11d,-0x2f8(%rbp)
    7fa1349987d4:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa1349987d8:	41 d1 e3             	shl    %r11d
    7fa1349987db:	89 9d 00 fd ff ff    	mov    %ebx,-0x300(%rbp)
    7fa1349987e1:	8b 9d 08 fd ff ff    	mov    -0x2f8(%rbp),%ebx
    7fa1349987e7:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349987ea:	83 e3 01             	and    $0x1,%ebx
    7fa1349987ed:	89 9d f8 fc ff ff    	mov    %ebx,-0x308(%rbp)
    7fa1349987f3:	d1 e3                	shl    %ebx
    7fa1349987f5:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7fa1349987fb:	8b 95 f8 fc ff ff    	mov    -0x308(%rbp),%edx
    7fa134998801:	0b da                	or     %edx,%ebx
    7fa134998803:	c1 e2 03             	shl    $0x3,%edx
    7fa134998806:	0b da                	or     %edx,%ebx
    7fa134998808:	8b 95 f8 fc ff ff    	mov    -0x308(%rbp),%edx
    7fa13499880e:	c1 e2 04             	shl    $0x4,%edx
    7fa134998811:	0b da                	or     %edx,%ebx
    7fa134998813:	44 33 db             	xor    %ebx,%r11d
    7fa134998816:	41 8b d3             	mov    %r11d,%edx
    7fa134998819:	8b 9d 08 fd ff ff    	mov    -0x2f8(%rbp),%ebx
    7fa13499881f:	33 d3                	xor    %ebx,%edx
    7fa134998821:	44 33 ca             	xor    %edx,%r9d
    7fa134998824:	44 33 c8             	xor    %eax,%r9d
    7fa134998827:	8b d6                	mov    %esi,%edx
    7fa134998829:	41 33 d0             	xor    %r8d,%edx
    7fa13499882c:	44 33 da             	xor    %edx,%r11d
    7fa13499882f:	8b d0                	mov    %eax,%edx
    7fa134998831:	83 e2 7f             	and    $0x7f,%edx
    7fa134998834:	d1 e2                	shl    %edx
    7fa134998836:	8b d8                	mov    %eax,%ebx
    7fa134998838:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499883b:	83 e3 01             	and    $0x1,%ebx
    7fa13499883e:	89 9d e8 fc ff ff    	mov    %ebx,-0x318(%rbp)
    7fa134998844:	d1 e3                	shl    %ebx
    7fa134998846:	89 8d e0 fc ff ff    	mov    %ecx,-0x320(%rbp)
    7fa13499884c:	8b 8d e8 fc ff ff    	mov    -0x318(%rbp),%ecx
    7fa134998852:	0b d9                	or     %ecx,%ebx
    7fa134998854:	c1 e1 03             	shl    $0x3,%ecx
    7fa134998857:	0b d9                	or     %ecx,%ebx
    7fa134998859:	8b 8d e8 fc ff ff    	mov    -0x318(%rbp),%ecx
    7fa13499885f:	c1 e1 04             	shl    $0x4,%ecx
    7fa134998862:	0b d9                	or     %ecx,%ebx
    7fa134998864:	33 d3                	xor    %ebx,%edx
    7fa134998866:	33 c2                	xor    %edx,%eax
    7fa134998868:	44 33 d8             	xor    %eax,%r11d
    7fa13499886b:	33 fe                	xor    %esi,%edi
    7fa13499886d:	44 33 c7             	xor    %edi,%r8d
    7fa134998870:	44 33 85 08 fd ff ff 	xor    -0x2f8(%rbp),%r8d
    7fa134998877:	41 33 d0             	xor    %r8d,%edx
    7fa13499887a:	49 0f b6 87 34 01 00 	movzbq 0x134(%r15),%rax
    7fa134998881:	00 
    7fa134998882:	8b c0                	mov    %eax,%eax
    7fa134998884:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998889:	8b c8                	mov    %eax,%ecx
    7fa13499888b:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499888e:	d1 e1                	shl    %ecx
    7fa134998890:	8b d8                	mov    %eax,%ebx
    7fa134998892:	c1 eb 07             	shr    $0x7,%ebx
    7fa134998895:	83 e3 01             	and    $0x1,%ebx
    7fa134998898:	8b f3                	mov    %ebx,%esi
    7fa13499889a:	d1 e6                	shl    %esi
    7fa13499889c:	0b f3                	or     %ebx,%esi
    7fa13499889e:	8b fb                	mov    %ebx,%edi
    7fa1349988a0:	c1 e7 03             	shl    $0x3,%edi
    7fa1349988a3:	0b f7                	or     %edi,%esi
    7fa1349988a5:	c1 e3 04             	shl    $0x4,%ebx
    7fa1349988a8:	0b f3                	or     %ebx,%esi
    7fa1349988aa:	33 ce                	xor    %esi,%ecx
    7fa1349988ac:	49 0f b6 9f 39 01 00 	movzbq 0x139(%r15),%rbx
    7fa1349988b3:	00 
    7fa1349988b4:	8b db                	mov    %ebx,%ebx
    7fa1349988b6:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa1349988bb:	8b f3                	mov    %ebx,%esi
    7fa1349988bd:	83 e6 7f             	and    $0x7f,%esi
    7fa1349988c0:	d1 e6                	shl    %esi
    7fa1349988c2:	8b fb                	mov    %ebx,%edi
    7fa1349988c4:	c1 ef 07             	shr    $0x7,%edi
    7fa1349988c7:	83 e7 01             	and    $0x1,%edi
    7fa1349988ca:	44 8b c7             	mov    %edi,%r8d
    7fa1349988cd:	41 d1 e0             	shl    %r8d
    7fa1349988d0:	44 0b c7             	or     %edi,%r8d
    7fa1349988d3:	89 bd d8 fc ff ff    	mov    %edi,-0x328(%rbp)
    7fa1349988d9:	c1 e7 03             	shl    $0x3,%edi
    7fa1349988dc:	44 0b c7             	or     %edi,%r8d
    7fa1349988df:	8b bd d8 fc ff ff    	mov    -0x328(%rbp),%edi
    7fa1349988e5:	c1 e7 04             	shl    $0x4,%edi
    7fa1349988e8:	44 0b c7             	or     %edi,%r8d
    7fa1349988eb:	41 33 f0             	xor    %r8d,%esi
    7fa1349988ee:	8b fe                	mov    %esi,%edi
    7fa1349988f0:	33 fb                	xor    %ebx,%edi
    7fa1349988f2:	33 f9                	xor    %ecx,%edi
    7fa1349988f4:	4d 0f b6 87 3e 01 00 	movzbq 0x13e(%r15),%r8
    7fa1349988fb:	00 
    7fa1349988fc:	45 8b c0             	mov    %r8d,%r8d
    7fa1349988ff:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134998904:	41 33 f8             	xor    %r8d,%edi
    7fa134998907:	44 89 95 d0 fc ff ff 	mov    %r10d,-0x330(%rbp)
    7fa13499890e:	4d 0f b6 97 33 01 00 	movzbq 0x133(%r15),%r10
    7fa134998915:	00 
    7fa134998916:	45 8b d2             	mov    %r10d,%r10d
    7fa134998919:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499891e:	41 33 fa             	xor    %r10d,%edi
    7fa134998921:	33 f0                	xor    %eax,%esi
    7fa134998923:	44 89 85 c8 fc ff ff 	mov    %r8d,-0x338(%rbp)
    7fa13499892a:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa13499892e:	41 d1 e0             	shl    %r8d
    7fa134998931:	44 89 8d c0 fc ff ff 	mov    %r9d,-0x340(%rbp)
    7fa134998938:	44 8b 8d c8 fc ff ff 	mov    -0x338(%rbp),%r9d
    7fa13499893f:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa134998943:	41 83 e1 01          	and    $0x1,%r9d
    7fa134998947:	44 89 8d b8 fc ff ff 	mov    %r9d,-0x348(%rbp)
    7fa13499894e:	41 d1 e1             	shl    %r9d
    7fa134998951:	44 89 9d b0 fc ff ff 	mov    %r11d,-0x350(%rbp)
    7fa134998958:	44 8b 9d b8 fc ff ff 	mov    -0x348(%rbp),%r11d
    7fa13499895f:	45 0b cb             	or     %r11d,%r9d
    7fa134998962:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134998966:	45 0b cb             	or     %r11d,%r9d
    7fa134998969:	44 8b 9d b8 fc ff ff 	mov    -0x348(%rbp),%r11d
    7fa134998970:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134998974:	45 0b cb             	or     %r11d,%r9d
    7fa134998977:	45 33 c1             	xor    %r9d,%r8d
    7fa13499897a:	45 8b c8             	mov    %r8d,%r9d
    7fa13499897d:	44 8b 9d c8 fc ff ff 	mov    -0x338(%rbp),%r11d
    7fa134998984:	45 33 cb             	xor    %r11d,%r9d
    7fa134998987:	41 33 f1             	xor    %r9d,%esi
    7fa13499898a:	41 33 f2             	xor    %r10d,%esi
    7fa13499898d:	44 8b c8             	mov    %eax,%r9d
    7fa134998990:	44 33 cb             	xor    %ebx,%r9d
    7fa134998993:	45 33 c1             	xor    %r9d,%r8d
    7fa134998996:	45 8b ca             	mov    %r10d,%r9d
    7fa134998999:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499899d:	41 d1 e1             	shl    %r9d
    7fa1349989a0:	45 8b da             	mov    %r10d,%r11d
    7fa1349989a3:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa1349989a7:	41 83 e3 01          	and    $0x1,%r11d
    7fa1349989ab:	44 89 9d a8 fc ff ff 	mov    %r11d,-0x358(%rbp)
    7fa1349989b2:	41 d1 e3             	shl    %r11d
    7fa1349989b5:	89 95 a0 fc ff ff    	mov    %edx,-0x360(%rbp)
    7fa1349989bb:	8b 95 a8 fc ff ff    	mov    -0x358(%rbp),%edx
    7fa1349989c1:	44 0b da             	or     %edx,%r11d
    7fa1349989c4:	c1 e2 03             	shl    $0x3,%edx
    7fa1349989c7:	44 0b da             	or     %edx,%r11d
    7fa1349989ca:	8b 95 a8 fc ff ff    	mov    -0x358(%rbp),%edx
    7fa1349989d0:	c1 e2 04             	shl    $0x4,%edx
    7fa1349989d3:	44 0b da             	or     %edx,%r11d
    7fa1349989d6:	45 33 cb             	xor    %r11d,%r9d
    7fa1349989d9:	45 33 d1             	xor    %r9d,%r10d
    7fa1349989dc:	45 33 c2             	xor    %r10d,%r8d
    7fa1349989df:	33 c8                	xor    %eax,%ecx
    7fa1349989e1:	33 d9                	xor    %ecx,%ebx
    7fa1349989e3:	33 9d c8 fc ff ff    	xor    -0x338(%rbp),%ebx
    7fa1349989e9:	44 33 cb             	xor    %ebx,%r9d
    7fa1349989ec:	49 0f b6 87 38 01 00 	movzbq 0x138(%r15),%rax
    7fa1349989f3:	00 
    7fa1349989f4:	8b c0                	mov    %eax,%eax
    7fa1349989f6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa1349989fb:	8b c8                	mov    %eax,%ecx
    7fa1349989fd:	83 e1 7f             	and    $0x7f,%ecx
    7fa134998a00:	d1 e1                	shl    %ecx
    7fa134998a02:	8b d0                	mov    %eax,%edx
    7fa134998a04:	c1 ea 07             	shr    $0x7,%edx
    7fa134998a07:	83 e2 01             	and    $0x1,%edx
    7fa134998a0a:	8b da                	mov    %edx,%ebx
    7fa134998a0c:	d1 e3                	shl    %ebx
    7fa134998a0e:	0b da                	or     %edx,%ebx
    7fa134998a10:	44 8b d2             	mov    %edx,%r10d
    7fa134998a13:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134998a17:	41 0b da             	or     %r10d,%ebx
    7fa134998a1a:	c1 e2 04             	shl    $0x4,%edx
    7fa134998a1d:	0b da                	or     %edx,%ebx
    7fa134998a1f:	33 cb                	xor    %ebx,%ecx
    7fa134998a21:	49 0f b6 97 3d 01 00 	movzbq 0x13d(%r15),%rdx
    7fa134998a28:	00 
    7fa134998a29:	8b d2                	mov    %edx,%edx
    7fa134998a2b:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134998a30:	8b da                	mov    %edx,%ebx
    7fa134998a32:	83 e3 7f             	and    $0x7f,%ebx
    7fa134998a35:	d1 e3                	shl    %ebx
    7fa134998a37:	44 8b d2             	mov    %edx,%r10d
    7fa134998a3a:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa134998a3e:	41 83 e2 01          	and    $0x1,%r10d
    7fa134998a42:	45 8b da             	mov    %r10d,%r11d
    7fa134998a45:	41 d1 e3             	shl    %r11d
    7fa134998a48:	45 0b da             	or     %r10d,%r11d
    7fa134998a4b:	44 89 95 98 fc ff ff 	mov    %r10d,-0x368(%rbp)
    7fa134998a52:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134998a56:	45 0b da             	or     %r10d,%r11d
    7fa134998a59:	44 8b 95 98 fc ff ff 	mov    -0x368(%rbp),%r10d
    7fa134998a60:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134998a64:	45 0b da             	or     %r10d,%r11d
    7fa134998a67:	41 33 db             	xor    %r11d,%ebx
    7fa134998a6a:	44 8b d3             	mov    %ebx,%r10d
    7fa134998a6d:	44 33 d2             	xor    %edx,%r10d
    7fa134998a70:	44 33 d1             	xor    %ecx,%r10d
    7fa134998a73:	4d 0f b6 9f 32 01 00 	movzbq 0x132(%r15),%r11
    7fa134998a7a:	00 
    7fa134998a7b:	45 8b db             	mov    %r11d,%r11d
    7fa134998a7e:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134998a83:	45 33 d3             	xor    %r11d,%r10d
    7fa134998a86:	89 bd 90 fc ff ff    	mov    %edi,-0x370(%rbp)
    7fa134998a8c:	49 0f b6 bf 37 01 00 	movzbq 0x137(%r15),%rdi
    7fa134998a93:	00 
    7fa134998a94:	8b ff                	mov    %edi,%edi
    7fa134998a96:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa134998a9b:	44 33 d7             	xor    %edi,%r10d
    7fa134998a9e:	33 d8                	xor    %eax,%ebx
    7fa134998aa0:	44 89 9d 88 fc ff ff 	mov    %r11d,-0x378(%rbp)
    7fa134998aa7:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134998aab:	41 d1 e3             	shl    %r11d
    7fa134998aae:	89 b5 80 fc ff ff    	mov    %esi,-0x380(%rbp)
    7fa134998ab4:	8b b5 88 fc ff ff    	mov    -0x378(%rbp),%esi
    7fa134998aba:	c1 ee 07             	shr    $0x7,%esi
    7fa134998abd:	83 e6 01             	and    $0x1,%esi
    7fa134998ac0:	89 b5 78 fc ff ff    	mov    %esi,-0x388(%rbp)
    7fa134998ac6:	d1 e6                	shl    %esi
    7fa134998ac8:	44 89 85 70 fc ff ff 	mov    %r8d,-0x390(%rbp)
    7fa134998acf:	44 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%r8d
    7fa134998ad6:	41 0b f0             	or     %r8d,%esi
    7fa134998ad9:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134998add:	41 0b f0             	or     %r8d,%esi
    7fa134998ae0:	44 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%r8d
    7fa134998ae7:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134998aeb:	41 0b f0             	or     %r8d,%esi
    7fa134998aee:	44 33 de             	xor    %esi,%r11d
    7fa134998af1:	41 8b f3             	mov    %r11d,%esi
    7fa134998af4:	44 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%r8d
    7fa134998afb:	41 33 f0             	xor    %r8d,%esi
    7fa134998afe:	33 de                	xor    %esi,%ebx
    7fa134998b00:	33 df                	xor    %edi,%ebx
    7fa134998b02:	8b f0                	mov    %eax,%esi
    7fa134998b04:	33 f2                	xor    %edx,%esi
    7fa134998b06:	44 33 de             	xor    %esi,%r11d
    7fa134998b09:	8b f7                	mov    %edi,%esi
    7fa134998b0b:	83 e6 7f             	and    $0x7f,%esi
    7fa134998b0e:	d1 e6                	shl    %esi
    7fa134998b10:	44 8b c7             	mov    %edi,%r8d
    7fa134998b13:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134998b17:	41 83 e0 01          	and    $0x1,%r8d
    7fa134998b1b:	44 89 85 68 fc ff ff 	mov    %r8d,-0x398(%rbp)
    7fa134998b22:	41 d1 e0             	shl    %r8d
    7fa134998b25:	44 89 8d 60 fc ff ff 	mov    %r9d,-0x3a0(%rbp)
    7fa134998b2c:	44 8b 8d 68 fc ff ff 	mov    -0x398(%rbp),%r9d
    7fa134998b33:	45 0b c1             	or     %r9d,%r8d
    7fa134998b36:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa134998b3a:	45 0b c1             	or     %r9d,%r8d
    7fa134998b3d:	44 8b 8d 68 fc ff ff 	mov    -0x398(%rbp),%r9d
    7fa134998b44:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa134998b48:	45 0b c1             	or     %r9d,%r8d
    7fa134998b4b:	41 33 f0             	xor    %r8d,%esi
    7fa134998b4e:	33 fe                	xor    %esi,%edi
    7fa134998b50:	44 33 df             	xor    %edi,%r11d
    7fa134998b53:	33 c8                	xor    %eax,%ecx
    7fa134998b55:	33 d1                	xor    %ecx,%edx
    7fa134998b57:	33 95 88 fc ff ff    	xor    -0x378(%rbp),%edx
    7fa134998b5d:	33 f2                	xor    %edx,%esi
    7fa134998b5f:	49 0f b6 87 3c 01 00 	movzbq 0x13c(%r15),%rax
    7fa134998b66:	00 
    7fa134998b67:	8b c0                	mov    %eax,%eax
    7fa134998b69:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998b6e:	8b c8                	mov    %eax,%ecx
    7fa134998b70:	83 e1 7f             	and    $0x7f,%ecx
    7fa134998b73:	d1 e1                	shl    %ecx
    7fa134998b75:	8b d0                	mov    %eax,%edx
    7fa134998b77:	c1 ea 07             	shr    $0x7,%edx
    7fa134998b7a:	83 e2 01             	and    $0x1,%edx
    7fa134998b7d:	8b fa                	mov    %edx,%edi
    7fa134998b7f:	d1 e7                	shl    %edi
    7fa134998b81:	0b fa                	or     %edx,%edi
    7fa134998b83:	44 8b c2             	mov    %edx,%r8d
    7fa134998b86:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134998b8a:	41 0b f8             	or     %r8d,%edi
    7fa134998b8d:	c1 e2 04             	shl    $0x4,%edx
    7fa134998b90:	0b fa                	or     %edx,%edi
    7fa134998b92:	33 cf                	xor    %edi,%ecx
    7fa134998b94:	49 0f b6 97 31 01 00 	movzbq 0x131(%r15),%rdx
    7fa134998b9b:	00 
    7fa134998b9c:	8b d2                	mov    %edx,%edx
    7fa134998b9e:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134998ba3:	8b fa                	mov    %edx,%edi
    7fa134998ba5:	83 e7 7f             	and    $0x7f,%edi
    7fa134998ba8:	d1 e7                	shl    %edi
    7fa134998baa:	44 8b c2             	mov    %edx,%r8d
    7fa134998bad:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134998bb1:	41 83 e0 01          	and    $0x1,%r8d
    7fa134998bb5:	45 8b c8             	mov    %r8d,%r9d
    7fa134998bb8:	41 d1 e1             	shl    %r9d
    7fa134998bbb:	45 0b c8             	or     %r8d,%r9d
    7fa134998bbe:	44 89 85 58 fc ff ff 	mov    %r8d,-0x3a8(%rbp)
    7fa134998bc5:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134998bc9:	45 0b c8             	or     %r8d,%r9d
    7fa134998bcc:	44 8b 85 58 fc ff ff 	mov    -0x3a8(%rbp),%r8d
    7fa134998bd3:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134998bd7:	45 0b c8             	or     %r8d,%r9d
    7fa134998bda:	41 33 f9             	xor    %r9d,%edi
    7fa134998bdd:	44 8b c7             	mov    %edi,%r8d
    7fa134998be0:	44 33 c2             	xor    %edx,%r8d
    7fa134998be3:	44 33 c1             	xor    %ecx,%r8d
    7fa134998be6:	4d 0f b6 8f 36 01 00 	movzbq 0x136(%r15),%r9
    7fa134998bed:	00 
    7fa134998bee:	45 8b c9             	mov    %r9d,%r9d
    7fa134998bf1:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa134998bf6:	45 33 c1             	xor    %r9d,%r8d
    7fa134998bf9:	44 89 95 50 fc ff ff 	mov    %r10d,-0x3b0(%rbp)
    7fa134998c00:	4d 0f b6 97 3b 01 00 	movzbq 0x13b(%r15),%r10
    7fa134998c07:	00 
    7fa134998c08:	45 8b d2             	mov    %r10d,%r10d
    7fa134998c0b:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa134998c10:	45 33 c2             	xor    %r10d,%r8d
    7fa134998c13:	33 f8                	xor    %eax,%edi
    7fa134998c15:	44 89 8d 48 fc ff ff 	mov    %r9d,-0x3b8(%rbp)
    7fa134998c1c:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134998c20:	41 d1 e1             	shl    %r9d
    7fa134998c23:	89 9d 40 fc ff ff    	mov    %ebx,-0x3c0(%rbp)
    7fa134998c29:	8b 9d 48 fc ff ff    	mov    -0x3b8(%rbp),%ebx
    7fa134998c2f:	c1 eb 07             	shr    $0x7,%ebx
    7fa134998c32:	83 e3 01             	and    $0x1,%ebx
    7fa134998c35:	89 9d 38 fc ff ff    	mov    %ebx,-0x3c8(%rbp)
    7fa134998c3b:	d1 e3                	shl    %ebx
    7fa134998c3d:	44 89 9d 30 fc ff ff 	mov    %r11d,-0x3d0(%rbp)
    7fa134998c44:	44 8b 9d 38 fc ff ff 	mov    -0x3c8(%rbp),%r11d
    7fa134998c4b:	41 0b db             	or     %r11d,%ebx
    7fa134998c4e:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134998c52:	41 0b db             	or     %r11d,%ebx
    7fa134998c55:	44 8b 9d 38 fc ff ff 	mov    -0x3c8(%rbp),%r11d
    7fa134998c5c:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134998c60:	41 0b db             	or     %r11d,%ebx
    7fa134998c63:	44 33 cb             	xor    %ebx,%r9d
    7fa134998c66:	41 8b d9             	mov    %r9d,%ebx
    7fa134998c69:	44 8b 9d 48 fc ff ff 	mov    -0x3b8(%rbp),%r11d
    7fa134998c70:	41 33 db             	xor    %r11d,%ebx
    7fa134998c73:	33 fb                	xor    %ebx,%edi
    7fa134998c75:	41 33 fa             	xor    %r10d,%edi
    7fa134998c78:	8b d8                	mov    %eax,%ebx
    7fa134998c7a:	33 da                	xor    %edx,%ebx
    7fa134998c7c:	44 33 cb             	xor    %ebx,%r9d
    7fa134998c7f:	41 8b da             	mov    %r10d,%ebx
    7fa134998c82:	83 e3 7f             	and    $0x7f,%ebx
    7fa134998c85:	d1 e3                	shl    %ebx
    7fa134998c87:	45 8b da             	mov    %r10d,%r11d
    7fa134998c8a:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134998c8e:	41 83 e3 01          	and    $0x1,%r11d
    7fa134998c92:	44 89 9d 28 fc ff ff 	mov    %r11d,-0x3d8(%rbp)
    7fa134998c99:	41 d1 e3             	shl    %r11d
    7fa134998c9c:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7fa134998ca2:	8b b5 28 fc ff ff    	mov    -0x3d8(%rbp),%esi
    7fa134998ca8:	44 0b de             	or     %esi,%r11d
    7fa134998cab:	c1 e6 03             	shl    $0x3,%esi
    7fa134998cae:	44 0b de             	or     %esi,%r11d
    7fa134998cb1:	8b b5 28 fc ff ff    	mov    -0x3d8(%rbp),%esi
    7fa134998cb7:	c1 e6 04             	shl    $0x4,%esi
    7fa134998cba:	44 0b de             	or     %esi,%r11d
    7fa134998cbd:	41 33 db             	xor    %r11d,%ebx
    7fa134998cc0:	44 33 d3             	xor    %ebx,%r10d
    7fa134998cc3:	45 33 ca             	xor    %r10d,%r9d
    7fa134998cc6:	33 c8                	xor    %eax,%ecx
    7fa134998cc8:	33 d1                	xor    %ecx,%edx
    7fa134998cca:	33 95 48 fc ff ff    	xor    -0x3b8(%rbp),%edx
    7fa134998cd0:	33 da                	xor    %edx,%ebx
    7fa134998cd2:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fa134998cd8:	c1 e0 08             	shl    $0x8,%eax
    7fa134998cdb:	0b 85 d0 fc ff ff    	or     -0x330(%rbp),%eax
    7fa134998ce1:	8b 8d b0 fc ff ff    	mov    -0x350(%rbp),%ecx
    7fa134998ce7:	c1 e1 10             	shl    $0x10,%ecx
    7fa134998cea:	0b c1                	or     %ecx,%eax
    7fa134998cec:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7fa134998cf2:	c1 e1 18             	shl    $0x18,%ecx
    7fa134998cf5:	0b c1                	or     %ecx,%eax
    7fa134998cf7:	8b 8d 90 fc ff ff    	mov    -0x370(%rbp),%ecx
    7fa134998cfd:	8b c9                	mov    %ecx,%ecx
    7fa134998cff:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa134998d03:	8b c0                	mov    %eax,%eax
    7fa134998d05:	48 0b c8             	or     %rax,%rcx
    7fa134998d08:	8b 85 80 fc ff ff    	mov    -0x380(%rbp),%eax
    7fa134998d0e:	8b c0                	mov    %eax,%eax
    7fa134998d10:	48 c1 e0 28          	shl    $0x28,%rax
    7fa134998d14:	48 0b c8             	or     %rax,%rcx
    7fa134998d17:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7fa134998d1d:	8b c0                	mov    %eax,%eax
    7fa134998d1f:	48 c1 e0 30          	shl    $0x30,%rax
    7fa134998d23:	48 0b c8             	or     %rax,%rcx
    7fa134998d26:	8b 85 60 fc ff ff    	mov    -0x3a0(%rbp),%eax
    7fa134998d2c:	8b c0                	mov    %eax,%eax
    7fa134998d2e:	48 c1 e0 38          	shl    $0x38,%rax
    7fa134998d32:	48 0b c8             	or     %rax,%rcx
    7fa134998d35:	49 89 8f 90 02 00 00 	mov    %rcx,0x290(%r15)
    7fa134998d3c:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fa134998d42:	c1 e0 08             	shl    $0x8,%eax
    7fa134998d45:	0b 85 50 fc ff ff    	or     -0x3b0(%rbp),%eax
    7fa134998d4b:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7fa134998d51:	c1 e1 10             	shl    $0x10,%ecx
    7fa134998d54:	0b c1                	or     %ecx,%eax
    7fa134998d56:	8b 8d 20 fc ff ff    	mov    -0x3e0(%rbp),%ecx
    7fa134998d5c:	c1 e1 18             	shl    $0x18,%ecx
    7fa134998d5f:	0b c1                	or     %ecx,%eax
    7fa134998d61:	45 8b c0             	mov    %r8d,%r8d
    7fa134998d64:	49 c1 e0 20          	shl    $0x20,%r8
    7fa134998d68:	8b c0                	mov    %eax,%eax
    7fa134998d6a:	4c 0b c0             	or     %rax,%r8
    7fa134998d6d:	8b ff                	mov    %edi,%edi
    7fa134998d6f:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa134998d73:	4c 0b c7             	or     %rdi,%r8
    7fa134998d76:	45 8b c9             	mov    %r9d,%r9d
    7fa134998d79:	49 c1 e1 30          	shl    $0x30,%r9
    7fa134998d7d:	4d 0b c1             	or     %r9,%r8
    7fa134998d80:	8b db                	mov    %ebx,%ebx
    7fa134998d82:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa134998d86:	4c 0b c3             	or     %rbx,%r8
    7fa134998d89:	4d 89 87 98 02 00 00 	mov    %r8,0x298(%r15)
    7fa134998d90:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7fa134998d96:	25 ff 00 00 00       	and    $0xff,%eax
    7fa134998d9b:	8b c0                	mov    %eax,%eax
    7fa134998d9d:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998da2:	8b 8d f0 fc ff ff    	mov    -0x310(%rbp),%ecx
    7fa134998da8:	c1 e9 18             	shr    $0x18,%ecx
    7fa134998dab:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa134998db1:	8b c9                	mov    %ecx,%ecx
    7fa134998db3:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa134998db8:	8b 95 f0 fc ff ff    	mov    -0x310(%rbp),%edx
    7fa134998dbe:	c1 ea 10             	shr    $0x10,%edx
    7fa134998dc1:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa134998dc7:	8b d2                	mov    %edx,%edx
    7fa134998dc9:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134998dce:	8b 9d f0 fc ff ff    	mov    -0x310(%rbp),%ebx
    7fa134998dd4:	c1 eb 08             	shr    $0x8,%ebx
    7fa134998dd7:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa134998ddd:	8b db                	mov    %ebx,%ebx
    7fa134998ddf:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134998de4:	c1 e2 08             	shl    $0x8,%edx
    7fa134998de7:	0b da                	or     %edx,%ebx
    7fa134998de9:	c1 e1 10             	shl    $0x10,%ecx
    7fa134998dec:	0b d9                	or     %ecx,%ebx
    7fa134998dee:	c1 e0 18             	shl    $0x18,%eax
    7fa134998df1:	0b d8                	or     %eax,%ebx
    7fa134998df3:	83 f3 08             	xor    $0x8,%ebx
    7fa134998df6:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fa134998dfc:	33 d8                	xor    %eax,%ebx
    7fa134998dfe:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fa134998e04:	33 c3                	xor    %ebx,%eax
    7fa134998e06:	8b 8d e0 fc ff ff    	mov    -0x320(%rbp),%ecx
    7fa134998e0c:	33 c8                	xor    %eax,%ecx
    7fa134998e0e:	8b 95 f0 fc ff ff    	mov    -0x310(%rbp),%edx
    7fa134998e14:	33 d1                	xor    %ecx,%edx
    7fa134998e16:	8b f0                	mov    %eax,%esi
    7fa134998e18:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa134998e1c:	8b fb                	mov    %ebx,%edi
    7fa134998e1e:	48 0b f7             	or     %rdi,%rsi
    7fa134998e21:	49 89 b7 f0 01 00 00 	mov    %rsi,0x1f0(%r15)
    7fa134998e28:	8b f2                	mov    %edx,%esi
    7fa134998e2a:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa134998e2e:	8b f9                	mov    %ecx,%edi
    7fa134998e30:	48 0b f7             	or     %rdi,%rsi
    7fa134998e33:	49 89 b7 f8 01 00 00 	mov    %rsi,0x1f8(%r15)
    7fa134998e3a:	49 8b b7 90 02 00 00 	mov    0x290(%r15),%rsi
    7fa134998e41:	49 8b bf f0 01 00 00 	mov    0x1f0(%r15),%rdi
    7fa134998e48:	48 33 f7             	xor    %rdi,%rsi
    7fa134998e4b:	49 89 b7 40 03 00 00 	mov    %rsi,0x340(%r15)
    7fa134998e52:	49 8b b7 98 02 00 00 	mov    0x298(%r15),%rsi
    7fa134998e59:	49 8b bf f8 01 00 00 	mov    0x1f8(%r15),%rdi
    7fa134998e60:	48 33 f7             	xor    %rdi,%rsi
    7fa134998e63:	49 89 b7 48 03 00 00 	mov    %rsi,0x348(%r15)
    7fa134998e6a:	49 0f b6 b7 40 01 00 	movzbq 0x140(%r15),%rsi
    7fa134998e71:	00 
    7fa134998e72:	8b f6                	mov    %esi,%esi
    7fa134998e74:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa134998e79:	8b fe                	mov    %esi,%edi
    7fa134998e7b:	83 e7 7f             	and    $0x7f,%edi
    7fa134998e7e:	d1 e7                	shl    %edi
    7fa134998e80:	44 8b c6             	mov    %esi,%r8d
    7fa134998e83:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134998e87:	41 83 e0 01          	and    $0x1,%r8d
    7fa134998e8b:	45 8b c8             	mov    %r8d,%r9d
    7fa134998e8e:	41 d1 e1             	shl    %r9d
    7fa134998e91:	45 0b c8             	or     %r8d,%r9d
    7fa134998e94:	45 8b d0             	mov    %r8d,%r10d
    7fa134998e97:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134998e9b:	45 0b ca             	or     %r10d,%r9d
    7fa134998e9e:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134998ea2:	45 0b c8             	or     %r8d,%r9d
    7fa134998ea5:	41 33 f9             	xor    %r9d,%edi
    7fa134998ea8:	4d 0f b6 87 45 01 00 	movzbq 0x145(%r15),%r8
    7fa134998eaf:	00 
    7fa134998eb0:	45 8b c0             	mov    %r8d,%r8d
    7fa134998eb3:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134998eb8:	45 8b c8             	mov    %r8d,%r9d
    7fa134998ebb:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134998ebf:	41 d1 e1             	shl    %r9d
    7fa134998ec2:	45 8b d0             	mov    %r8d,%r10d
    7fa134998ec5:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa134998ec9:	41 83 e2 01          	and    $0x1,%r10d
    7fa134998ecd:	45 8b da             	mov    %r10d,%r11d
    7fa134998ed0:	41 d1 e3             	shl    %r11d
    7fa134998ed3:	45 0b da             	or     %r10d,%r11d
    7fa134998ed6:	44 89 95 18 fc ff ff 	mov    %r10d,-0x3e8(%rbp)
    7fa134998edd:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134998ee1:	45 0b da             	or     %r10d,%r11d
    7fa134998ee4:	44 8b 95 18 fc ff ff 	mov    -0x3e8(%rbp),%r10d
    7fa134998eeb:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134998eef:	45 0b da             	or     %r10d,%r11d
    7fa134998ef2:	45 33 cb             	xor    %r11d,%r9d
    7fa134998ef5:	45 8b d1             	mov    %r9d,%r10d
    7fa134998ef8:	45 33 d0             	xor    %r8d,%r10d
    7fa134998efb:	44 33 d7             	xor    %edi,%r10d
    7fa134998efe:	4d 0f b6 9f 4a 01 00 	movzbq 0x14a(%r15),%r11
    7fa134998f05:	00 
    7fa134998f06:	45 8b db             	mov    %r11d,%r11d
    7fa134998f09:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134998f0e:	45 33 d3             	xor    %r11d,%r10d
    7fa134998f11:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7fa134998f17:	49 0f b6 87 4f 01 00 	movzbq 0x14f(%r15),%rax
    7fa134998f1e:	00 
    7fa134998f1f:	8b c0                	mov    %eax,%eax
    7fa134998f21:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998f26:	44 33 d0             	xor    %eax,%r10d
    7fa134998f29:	44 33 ce             	xor    %esi,%r9d
    7fa134998f2c:	44 89 9d 08 fc ff ff 	mov    %r11d,-0x3f8(%rbp)
    7fa134998f33:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134998f37:	41 d1 e3             	shl    %r11d
    7fa134998f3a:	89 9d 00 fc ff ff    	mov    %ebx,-0x400(%rbp)
    7fa134998f40:	8b 9d 08 fc ff ff    	mov    -0x3f8(%rbp),%ebx
    7fa134998f46:	c1 eb 07             	shr    $0x7,%ebx
    7fa134998f49:	83 e3 01             	and    $0x1,%ebx
    7fa134998f4c:	89 9d f8 fb ff ff    	mov    %ebx,-0x408(%rbp)
    7fa134998f52:	d1 e3                	shl    %ebx
    7fa134998f54:	89 95 f0 fb ff ff    	mov    %edx,-0x410(%rbp)
    7fa134998f5a:	8b 95 f8 fb ff ff    	mov    -0x408(%rbp),%edx
    7fa134998f60:	0b da                	or     %edx,%ebx
    7fa134998f62:	c1 e2 03             	shl    $0x3,%edx
    7fa134998f65:	0b da                	or     %edx,%ebx
    7fa134998f67:	8b 95 f8 fb ff ff    	mov    -0x408(%rbp),%edx
    7fa134998f6d:	c1 e2 04             	shl    $0x4,%edx
    7fa134998f70:	0b da                	or     %edx,%ebx
    7fa134998f72:	44 33 db             	xor    %ebx,%r11d
    7fa134998f75:	41 8b d3             	mov    %r11d,%edx
    7fa134998f78:	8b 9d 08 fc ff ff    	mov    -0x3f8(%rbp),%ebx
    7fa134998f7e:	33 d3                	xor    %ebx,%edx
    7fa134998f80:	44 33 ca             	xor    %edx,%r9d
    7fa134998f83:	44 33 c8             	xor    %eax,%r9d
    7fa134998f86:	8b d6                	mov    %esi,%edx
    7fa134998f88:	41 33 d0             	xor    %r8d,%edx
    7fa134998f8b:	44 33 da             	xor    %edx,%r11d
    7fa134998f8e:	8b d0                	mov    %eax,%edx
    7fa134998f90:	83 e2 7f             	and    $0x7f,%edx
    7fa134998f93:	d1 e2                	shl    %edx
    7fa134998f95:	8b d8                	mov    %eax,%ebx
    7fa134998f97:	c1 eb 07             	shr    $0x7,%ebx
    7fa134998f9a:	83 e3 01             	and    $0x1,%ebx
    7fa134998f9d:	89 9d e8 fb ff ff    	mov    %ebx,-0x418(%rbp)
    7fa134998fa3:	d1 e3                	shl    %ebx
    7fa134998fa5:	89 8d e0 fb ff ff    	mov    %ecx,-0x420(%rbp)
    7fa134998fab:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7fa134998fb1:	0b d9                	or     %ecx,%ebx
    7fa134998fb3:	c1 e1 03             	shl    $0x3,%ecx
    7fa134998fb6:	0b d9                	or     %ecx,%ebx
    7fa134998fb8:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7fa134998fbe:	c1 e1 04             	shl    $0x4,%ecx
    7fa134998fc1:	0b d9                	or     %ecx,%ebx
    7fa134998fc3:	33 d3                	xor    %ebx,%edx
    7fa134998fc5:	33 c2                	xor    %edx,%eax
    7fa134998fc7:	44 33 d8             	xor    %eax,%r11d
    7fa134998fca:	33 fe                	xor    %esi,%edi
    7fa134998fcc:	44 33 c7             	xor    %edi,%r8d
    7fa134998fcf:	44 33 85 08 fc ff ff 	xor    -0x3f8(%rbp),%r8d
    7fa134998fd6:	41 33 d0             	xor    %r8d,%edx
    7fa134998fd9:	49 0f b6 87 44 01 00 	movzbq 0x144(%r15),%rax
    7fa134998fe0:	00 
    7fa134998fe1:	8b c0                	mov    %eax,%eax
    7fa134998fe3:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134998fe8:	8b c8                	mov    %eax,%ecx
    7fa134998fea:	83 e1 7f             	and    $0x7f,%ecx
    7fa134998fed:	d1 e1                	shl    %ecx
    7fa134998fef:	8b d8                	mov    %eax,%ebx
    7fa134998ff1:	c1 eb 07             	shr    $0x7,%ebx
    7fa134998ff4:	83 e3 01             	and    $0x1,%ebx
    7fa134998ff7:	8b f3                	mov    %ebx,%esi
    7fa134998ff9:	d1 e6                	shl    %esi
    7fa134998ffb:	0b f3                	or     %ebx,%esi
    7fa134998ffd:	8b fb                	mov    %ebx,%edi
    7fa134998fff:	c1 e7 03             	shl    $0x3,%edi
    7fa134999002:	0b f7                	or     %edi,%esi
    7fa134999004:	c1 e3 04             	shl    $0x4,%ebx
    7fa134999007:	0b f3                	or     %ebx,%esi
    7fa134999009:	33 ce                	xor    %esi,%ecx
    7fa13499900b:	49 0f b6 9f 49 01 00 	movzbq 0x149(%r15),%rbx
    7fa134999012:	00 
    7fa134999013:	8b db                	mov    %ebx,%ebx
    7fa134999015:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499901a:	8b f3                	mov    %ebx,%esi
    7fa13499901c:	83 e6 7f             	and    $0x7f,%esi
    7fa13499901f:	d1 e6                	shl    %esi
    7fa134999021:	8b fb                	mov    %ebx,%edi
    7fa134999023:	c1 ef 07             	shr    $0x7,%edi
    7fa134999026:	83 e7 01             	and    $0x1,%edi
    7fa134999029:	44 8b c7             	mov    %edi,%r8d
    7fa13499902c:	41 d1 e0             	shl    %r8d
    7fa13499902f:	44 0b c7             	or     %edi,%r8d
    7fa134999032:	89 bd d8 fb ff ff    	mov    %edi,-0x428(%rbp)
    7fa134999038:	c1 e7 03             	shl    $0x3,%edi
    7fa13499903b:	44 0b c7             	or     %edi,%r8d
    7fa13499903e:	8b bd d8 fb ff ff    	mov    -0x428(%rbp),%edi
    7fa134999044:	c1 e7 04             	shl    $0x4,%edi
    7fa134999047:	44 0b c7             	or     %edi,%r8d
    7fa13499904a:	41 33 f0             	xor    %r8d,%esi
    7fa13499904d:	8b fe                	mov    %esi,%edi
    7fa13499904f:	33 fb                	xor    %ebx,%edi
    7fa134999051:	33 f9                	xor    %ecx,%edi
    7fa134999053:	4d 0f b6 87 4e 01 00 	movzbq 0x14e(%r15),%r8
    7fa13499905a:	00 
    7fa13499905b:	45 8b c0             	mov    %r8d,%r8d
    7fa13499905e:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134999063:	41 33 f8             	xor    %r8d,%edi
    7fa134999066:	44 89 95 d0 fb ff ff 	mov    %r10d,-0x430(%rbp)
    7fa13499906d:	4d 0f b6 97 43 01 00 	movzbq 0x143(%r15),%r10
    7fa134999074:	00 
    7fa134999075:	45 8b d2             	mov    %r10d,%r10d
    7fa134999078:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499907d:	41 33 fa             	xor    %r10d,%edi
    7fa134999080:	33 f0                	xor    %eax,%esi
    7fa134999082:	44 89 85 c8 fb ff ff 	mov    %r8d,-0x438(%rbp)
    7fa134999089:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa13499908d:	41 d1 e0             	shl    %r8d
    7fa134999090:	44 89 8d c0 fb ff ff 	mov    %r9d,-0x440(%rbp)
    7fa134999097:	44 8b 8d c8 fb ff ff 	mov    -0x438(%rbp),%r9d
    7fa13499909e:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa1349990a2:	41 83 e1 01          	and    $0x1,%r9d
    7fa1349990a6:	44 89 8d b8 fb ff ff 	mov    %r9d,-0x448(%rbp)
    7fa1349990ad:	41 d1 e1             	shl    %r9d
    7fa1349990b0:	44 89 9d b0 fb ff ff 	mov    %r11d,-0x450(%rbp)
    7fa1349990b7:	44 8b 9d b8 fb ff ff 	mov    -0x448(%rbp),%r11d
    7fa1349990be:	45 0b cb             	or     %r11d,%r9d
    7fa1349990c1:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa1349990c5:	45 0b cb             	or     %r11d,%r9d
    7fa1349990c8:	44 8b 9d b8 fb ff ff 	mov    -0x448(%rbp),%r11d
    7fa1349990cf:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa1349990d3:	45 0b cb             	or     %r11d,%r9d
    7fa1349990d6:	45 33 c1             	xor    %r9d,%r8d
    7fa1349990d9:	45 8b c8             	mov    %r8d,%r9d
    7fa1349990dc:	44 8b 9d c8 fb ff ff 	mov    -0x438(%rbp),%r11d
    7fa1349990e3:	45 33 cb             	xor    %r11d,%r9d
    7fa1349990e6:	41 33 f1             	xor    %r9d,%esi
    7fa1349990e9:	41 33 f2             	xor    %r10d,%esi
    7fa1349990ec:	44 8b c8             	mov    %eax,%r9d
    7fa1349990ef:	44 33 cb             	xor    %ebx,%r9d
    7fa1349990f2:	45 33 c1             	xor    %r9d,%r8d
    7fa1349990f5:	45 8b ca             	mov    %r10d,%r9d
    7fa1349990f8:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa1349990fc:	41 d1 e1             	shl    %r9d
    7fa1349990ff:	45 8b da             	mov    %r10d,%r11d
    7fa134999102:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134999106:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499910a:	44 89 9d a8 fb ff ff 	mov    %r11d,-0x458(%rbp)
    7fa134999111:	41 d1 e3             	shl    %r11d
    7fa134999114:	89 95 a0 fb ff ff    	mov    %edx,-0x460(%rbp)
    7fa13499911a:	8b 95 a8 fb ff ff    	mov    -0x458(%rbp),%edx
    7fa134999120:	44 0b da             	or     %edx,%r11d
    7fa134999123:	c1 e2 03             	shl    $0x3,%edx
    7fa134999126:	44 0b da             	or     %edx,%r11d
    7fa134999129:	8b 95 a8 fb ff ff    	mov    -0x458(%rbp),%edx
    7fa13499912f:	c1 e2 04             	shl    $0x4,%edx
    7fa134999132:	44 0b da             	or     %edx,%r11d
    7fa134999135:	45 33 cb             	xor    %r11d,%r9d
    7fa134999138:	45 33 d1             	xor    %r9d,%r10d
    7fa13499913b:	45 33 c2             	xor    %r10d,%r8d
    7fa13499913e:	33 c8                	xor    %eax,%ecx
    7fa134999140:	33 d9                	xor    %ecx,%ebx
    7fa134999142:	33 9d c8 fb ff ff    	xor    -0x438(%rbp),%ebx
    7fa134999148:	44 33 cb             	xor    %ebx,%r9d
    7fa13499914b:	49 0f b6 87 48 01 00 	movzbq 0x148(%r15),%rax
    7fa134999152:	00 
    7fa134999153:	8b c0                	mov    %eax,%eax
    7fa134999155:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499915a:	8b c8                	mov    %eax,%ecx
    7fa13499915c:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499915f:	d1 e1                	shl    %ecx
    7fa134999161:	8b d0                	mov    %eax,%edx
    7fa134999163:	c1 ea 07             	shr    $0x7,%edx
    7fa134999166:	83 e2 01             	and    $0x1,%edx
    7fa134999169:	8b da                	mov    %edx,%ebx
    7fa13499916b:	d1 e3                	shl    %ebx
    7fa13499916d:	0b da                	or     %edx,%ebx
    7fa13499916f:	44 8b d2             	mov    %edx,%r10d
    7fa134999172:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134999176:	41 0b da             	or     %r10d,%ebx
    7fa134999179:	c1 e2 04             	shl    $0x4,%edx
    7fa13499917c:	0b da                	or     %edx,%ebx
    7fa13499917e:	33 cb                	xor    %ebx,%ecx
    7fa134999180:	49 0f b6 97 4d 01 00 	movzbq 0x14d(%r15),%rdx
    7fa134999187:	00 
    7fa134999188:	8b d2                	mov    %edx,%edx
    7fa13499918a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499918f:	8b da                	mov    %edx,%ebx
    7fa134999191:	83 e3 7f             	and    $0x7f,%ebx
    7fa134999194:	d1 e3                	shl    %ebx
    7fa134999196:	44 8b d2             	mov    %edx,%r10d
    7fa134999199:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499919d:	41 83 e2 01          	and    $0x1,%r10d
    7fa1349991a1:	45 8b da             	mov    %r10d,%r11d
    7fa1349991a4:	41 d1 e3             	shl    %r11d
    7fa1349991a7:	45 0b da             	or     %r10d,%r11d
    7fa1349991aa:	44 89 95 98 fb ff ff 	mov    %r10d,-0x468(%rbp)
    7fa1349991b1:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349991b5:	45 0b da             	or     %r10d,%r11d
    7fa1349991b8:	44 8b 95 98 fb ff ff 	mov    -0x468(%rbp),%r10d
    7fa1349991bf:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa1349991c3:	45 0b da             	or     %r10d,%r11d
    7fa1349991c6:	41 33 db             	xor    %r11d,%ebx
    7fa1349991c9:	44 8b d3             	mov    %ebx,%r10d
    7fa1349991cc:	44 33 d2             	xor    %edx,%r10d
    7fa1349991cf:	44 33 d1             	xor    %ecx,%r10d
    7fa1349991d2:	4d 0f b6 9f 42 01 00 	movzbq 0x142(%r15),%r11
    7fa1349991d9:	00 
    7fa1349991da:	45 8b db             	mov    %r11d,%r11d
    7fa1349991dd:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa1349991e2:	45 33 d3             	xor    %r11d,%r10d
    7fa1349991e5:	89 bd 90 fb ff ff    	mov    %edi,-0x470(%rbp)
    7fa1349991eb:	49 0f b6 bf 47 01 00 	movzbq 0x147(%r15),%rdi
    7fa1349991f2:	00 
    7fa1349991f3:	8b ff                	mov    %edi,%edi
    7fa1349991f5:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa1349991fa:	44 33 d7             	xor    %edi,%r10d
    7fa1349991fd:	33 d8                	xor    %eax,%ebx
    7fa1349991ff:	44 89 9d 88 fb ff ff 	mov    %r11d,-0x478(%rbp)
    7fa134999206:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499920a:	41 d1 e3             	shl    %r11d
    7fa13499920d:	89 b5 80 fb ff ff    	mov    %esi,-0x480(%rbp)
    7fa134999213:	8b b5 88 fb ff ff    	mov    -0x478(%rbp),%esi
    7fa134999219:	c1 ee 07             	shr    $0x7,%esi
    7fa13499921c:	83 e6 01             	and    $0x1,%esi
    7fa13499921f:	89 b5 78 fb ff ff    	mov    %esi,-0x488(%rbp)
    7fa134999225:	d1 e6                	shl    %esi
    7fa134999227:	44 89 85 70 fb ff ff 	mov    %r8d,-0x490(%rbp)
    7fa13499922e:	44 8b 85 78 fb ff ff 	mov    -0x488(%rbp),%r8d
    7fa134999235:	41 0b f0             	or     %r8d,%esi
    7fa134999238:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499923c:	41 0b f0             	or     %r8d,%esi
    7fa13499923f:	44 8b 85 78 fb ff ff 	mov    -0x488(%rbp),%r8d
    7fa134999246:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499924a:	41 0b f0             	or     %r8d,%esi
    7fa13499924d:	44 33 de             	xor    %esi,%r11d
    7fa134999250:	41 8b f3             	mov    %r11d,%esi
    7fa134999253:	44 8b 85 88 fb ff ff 	mov    -0x478(%rbp),%r8d
    7fa13499925a:	41 33 f0             	xor    %r8d,%esi
    7fa13499925d:	33 de                	xor    %esi,%ebx
    7fa13499925f:	33 df                	xor    %edi,%ebx
    7fa134999261:	8b f0                	mov    %eax,%esi
    7fa134999263:	33 f2                	xor    %edx,%esi
    7fa134999265:	44 33 de             	xor    %esi,%r11d
    7fa134999268:	8b f7                	mov    %edi,%esi
    7fa13499926a:	83 e6 7f             	and    $0x7f,%esi
    7fa13499926d:	d1 e6                	shl    %esi
    7fa13499926f:	44 8b c7             	mov    %edi,%r8d
    7fa134999272:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134999276:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499927a:	44 89 85 68 fb ff ff 	mov    %r8d,-0x498(%rbp)
    7fa134999281:	41 d1 e0             	shl    %r8d
    7fa134999284:	44 89 8d 60 fb ff ff 	mov    %r9d,-0x4a0(%rbp)
    7fa13499928b:	44 8b 8d 68 fb ff ff 	mov    -0x498(%rbp),%r9d
    7fa134999292:	45 0b c1             	or     %r9d,%r8d
    7fa134999295:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa134999299:	45 0b c1             	or     %r9d,%r8d
    7fa13499929c:	44 8b 8d 68 fb ff ff 	mov    -0x498(%rbp),%r9d
    7fa1349992a3:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa1349992a7:	45 0b c1             	or     %r9d,%r8d
    7fa1349992aa:	41 33 f0             	xor    %r8d,%esi
    7fa1349992ad:	33 fe                	xor    %esi,%edi
    7fa1349992af:	44 33 df             	xor    %edi,%r11d
    7fa1349992b2:	33 c8                	xor    %eax,%ecx
    7fa1349992b4:	33 d1                	xor    %ecx,%edx
    7fa1349992b6:	33 95 88 fb ff ff    	xor    -0x478(%rbp),%edx
    7fa1349992bc:	33 f2                	xor    %edx,%esi
    7fa1349992be:	49 0f b6 87 4c 01 00 	movzbq 0x14c(%r15),%rax
    7fa1349992c5:	00 
    7fa1349992c6:	8b c0                	mov    %eax,%eax
    7fa1349992c8:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa1349992cd:	8b c8                	mov    %eax,%ecx
    7fa1349992cf:	83 e1 7f             	and    $0x7f,%ecx
    7fa1349992d2:	d1 e1                	shl    %ecx
    7fa1349992d4:	8b d0                	mov    %eax,%edx
    7fa1349992d6:	c1 ea 07             	shr    $0x7,%edx
    7fa1349992d9:	83 e2 01             	and    $0x1,%edx
    7fa1349992dc:	8b fa                	mov    %edx,%edi
    7fa1349992de:	d1 e7                	shl    %edi
    7fa1349992e0:	0b fa                	or     %edx,%edi
    7fa1349992e2:	44 8b c2             	mov    %edx,%r8d
    7fa1349992e5:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa1349992e9:	41 0b f8             	or     %r8d,%edi
    7fa1349992ec:	c1 e2 04             	shl    $0x4,%edx
    7fa1349992ef:	0b fa                	or     %edx,%edi
    7fa1349992f1:	33 cf                	xor    %edi,%ecx
    7fa1349992f3:	49 0f b6 97 41 01 00 	movzbq 0x141(%r15),%rdx
    7fa1349992fa:	00 
    7fa1349992fb:	8b d2                	mov    %edx,%edx
    7fa1349992fd:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134999302:	8b fa                	mov    %edx,%edi
    7fa134999304:	83 e7 7f             	and    $0x7f,%edi
    7fa134999307:	d1 e7                	shl    %edi
    7fa134999309:	44 8b c2             	mov    %edx,%r8d
    7fa13499930c:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134999310:	41 83 e0 01          	and    $0x1,%r8d
    7fa134999314:	45 8b c8             	mov    %r8d,%r9d
    7fa134999317:	41 d1 e1             	shl    %r9d
    7fa13499931a:	45 0b c8             	or     %r8d,%r9d
    7fa13499931d:	44 89 85 58 fb ff ff 	mov    %r8d,-0x4a8(%rbp)
    7fa134999324:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134999328:	45 0b c8             	or     %r8d,%r9d
    7fa13499932b:	44 8b 85 58 fb ff ff 	mov    -0x4a8(%rbp),%r8d
    7fa134999332:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134999336:	45 0b c8             	or     %r8d,%r9d
    7fa134999339:	41 33 f9             	xor    %r9d,%edi
    7fa13499933c:	44 8b c7             	mov    %edi,%r8d
    7fa13499933f:	44 33 c2             	xor    %edx,%r8d
    7fa134999342:	44 33 c1             	xor    %ecx,%r8d
    7fa134999345:	4d 0f b6 8f 46 01 00 	movzbq 0x146(%r15),%r9
    7fa13499934c:	00 
    7fa13499934d:	45 8b c9             	mov    %r9d,%r9d
    7fa134999350:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa134999355:	45 33 c1             	xor    %r9d,%r8d
    7fa134999358:	44 89 95 50 fb ff ff 	mov    %r10d,-0x4b0(%rbp)
    7fa13499935f:	4d 0f b6 97 4b 01 00 	movzbq 0x14b(%r15),%r10
    7fa134999366:	00 
    7fa134999367:	45 8b d2             	mov    %r10d,%r10d
    7fa13499936a:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499936f:	45 33 c2             	xor    %r10d,%r8d
    7fa134999372:	33 f8                	xor    %eax,%edi
    7fa134999374:	44 89 8d 48 fb ff ff 	mov    %r9d,-0x4b8(%rbp)
    7fa13499937b:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499937f:	41 d1 e1             	shl    %r9d
    7fa134999382:	89 9d 40 fb ff ff    	mov    %ebx,-0x4c0(%rbp)
    7fa134999388:	8b 9d 48 fb ff ff    	mov    -0x4b8(%rbp),%ebx
    7fa13499938e:	c1 eb 07             	shr    $0x7,%ebx
    7fa134999391:	83 e3 01             	and    $0x1,%ebx
    7fa134999394:	89 9d 38 fb ff ff    	mov    %ebx,-0x4c8(%rbp)
    7fa13499939a:	d1 e3                	shl    %ebx
    7fa13499939c:	44 89 9d 30 fb ff ff 	mov    %r11d,-0x4d0(%rbp)
    7fa1349993a3:	44 8b 9d 38 fb ff ff 	mov    -0x4c8(%rbp),%r11d
    7fa1349993aa:	41 0b db             	or     %r11d,%ebx
    7fa1349993ad:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa1349993b1:	41 0b db             	or     %r11d,%ebx
    7fa1349993b4:	44 8b 9d 38 fb ff ff 	mov    -0x4c8(%rbp),%r11d
    7fa1349993bb:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa1349993bf:	41 0b db             	or     %r11d,%ebx
    7fa1349993c2:	44 33 cb             	xor    %ebx,%r9d
    7fa1349993c5:	41 8b d9             	mov    %r9d,%ebx
    7fa1349993c8:	44 8b 9d 48 fb ff ff 	mov    -0x4b8(%rbp),%r11d
    7fa1349993cf:	41 33 db             	xor    %r11d,%ebx
    7fa1349993d2:	33 fb                	xor    %ebx,%edi
    7fa1349993d4:	41 33 fa             	xor    %r10d,%edi
    7fa1349993d7:	8b d8                	mov    %eax,%ebx
    7fa1349993d9:	33 da                	xor    %edx,%ebx
    7fa1349993db:	44 33 cb             	xor    %ebx,%r9d
    7fa1349993de:	41 8b da             	mov    %r10d,%ebx
    7fa1349993e1:	83 e3 7f             	and    $0x7f,%ebx
    7fa1349993e4:	d1 e3                	shl    %ebx
    7fa1349993e6:	45 8b da             	mov    %r10d,%r11d
    7fa1349993e9:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa1349993ed:	41 83 e3 01          	and    $0x1,%r11d
    7fa1349993f1:	44 89 9d 28 fb ff ff 	mov    %r11d,-0x4d8(%rbp)
    7fa1349993f8:	41 d1 e3             	shl    %r11d
    7fa1349993fb:	89 b5 20 fb ff ff    	mov    %esi,-0x4e0(%rbp)
    7fa134999401:	8b b5 28 fb ff ff    	mov    -0x4d8(%rbp),%esi
    7fa134999407:	44 0b de             	or     %esi,%r11d
    7fa13499940a:	c1 e6 03             	shl    $0x3,%esi
    7fa13499940d:	44 0b de             	or     %esi,%r11d
    7fa134999410:	8b b5 28 fb ff ff    	mov    -0x4d8(%rbp),%esi
    7fa134999416:	c1 e6 04             	shl    $0x4,%esi
    7fa134999419:	44 0b de             	or     %esi,%r11d
    7fa13499941c:	41 33 db             	xor    %r11d,%ebx
    7fa13499941f:	44 33 d3             	xor    %ebx,%r10d
    7fa134999422:	45 33 ca             	xor    %r10d,%r9d
    7fa134999425:	33 c8                	xor    %eax,%ecx
    7fa134999427:	33 d1                	xor    %ecx,%edx
    7fa134999429:	33 95 48 fb ff ff    	xor    -0x4b8(%rbp),%edx
    7fa13499942f:	33 da                	xor    %edx,%ebx
    7fa134999431:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fa134999437:	c1 e0 08             	shl    $0x8,%eax
    7fa13499943a:	0b 85 d0 fb ff ff    	or     -0x430(%rbp),%eax
    7fa134999440:	8b 8d b0 fb ff ff    	mov    -0x450(%rbp),%ecx
    7fa134999446:	c1 e1 10             	shl    $0x10,%ecx
    7fa134999449:	0b c1                	or     %ecx,%eax
    7fa13499944b:	8b 8d a0 fb ff ff    	mov    -0x460(%rbp),%ecx
    7fa134999451:	c1 e1 18             	shl    $0x18,%ecx
    7fa134999454:	0b c1                	or     %ecx,%eax
    7fa134999456:	8b 8d 90 fb ff ff    	mov    -0x470(%rbp),%ecx
    7fa13499945c:	8b c9                	mov    %ecx,%ecx
    7fa13499945e:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa134999462:	8b c0                	mov    %eax,%eax
    7fa134999464:	48 0b c8             	or     %rax,%rcx
    7fa134999467:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7fa13499946d:	8b c0                	mov    %eax,%eax
    7fa13499946f:	48 c1 e0 28          	shl    $0x28,%rax
    7fa134999473:	48 0b c8             	or     %rax,%rcx
    7fa134999476:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fa13499947c:	8b c0                	mov    %eax,%eax
    7fa13499947e:	48 c1 e0 30          	shl    $0x30,%rax
    7fa134999482:	48 0b c8             	or     %rax,%rcx
    7fa134999485:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7fa13499948b:	8b c0                	mov    %eax,%eax
    7fa13499948d:	48 c1 e0 38          	shl    $0x38,%rax
    7fa134999491:	48 0b c8             	or     %rax,%rcx
    7fa134999494:	49 89 8f a0 02 00 00 	mov    %rcx,0x2a0(%r15)
    7fa13499949b:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fa1349994a1:	c1 e0 08             	shl    $0x8,%eax
    7fa1349994a4:	0b 85 50 fb ff ff    	or     -0x4b0(%rbp),%eax
    7fa1349994aa:	8b 8d 30 fb ff ff    	mov    -0x4d0(%rbp),%ecx
    7fa1349994b0:	c1 e1 10             	shl    $0x10,%ecx
    7fa1349994b3:	0b c1                	or     %ecx,%eax
    7fa1349994b5:	8b 8d 20 fb ff ff    	mov    -0x4e0(%rbp),%ecx
    7fa1349994bb:	c1 e1 18             	shl    $0x18,%ecx
    7fa1349994be:	0b c1                	or     %ecx,%eax
    7fa1349994c0:	45 8b c0             	mov    %r8d,%r8d
    7fa1349994c3:	49 c1 e0 20          	shl    $0x20,%r8
    7fa1349994c7:	8b c0                	mov    %eax,%eax
    7fa1349994c9:	4c 0b c0             	or     %rax,%r8
    7fa1349994cc:	8b ff                	mov    %edi,%edi
    7fa1349994ce:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa1349994d2:	4c 0b c7             	or     %rdi,%r8
    7fa1349994d5:	45 8b c9             	mov    %r9d,%r9d
    7fa1349994d8:	49 c1 e1 30          	shl    $0x30,%r9
    7fa1349994dc:	4d 0b c1             	or     %r9,%r8
    7fa1349994df:	8b db                	mov    %ebx,%ebx
    7fa1349994e1:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa1349994e5:	4c 0b c3             	or     %rbx,%r8
    7fa1349994e8:	4d 89 87 a8 02 00 00 	mov    %r8,0x2a8(%r15)
    7fa1349994ef:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7fa1349994f5:	25 ff 00 00 00       	and    $0xff,%eax
    7fa1349994fa:	8b c0                	mov    %eax,%eax
    7fa1349994fc:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999501:	8b 8d f0 fb ff ff    	mov    -0x410(%rbp),%ecx
    7fa134999507:	c1 e9 18             	shr    $0x18,%ecx
    7fa13499950a:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa134999510:	8b c9                	mov    %ecx,%ecx
    7fa134999512:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa134999517:	8b 95 f0 fb ff ff    	mov    -0x410(%rbp),%edx
    7fa13499951d:	c1 ea 10             	shr    $0x10,%edx
    7fa134999520:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa134999526:	8b d2                	mov    %edx,%edx
    7fa134999528:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499952d:	8b 9d f0 fb ff ff    	mov    -0x410(%rbp),%ebx
    7fa134999533:	c1 eb 08             	shr    $0x8,%ebx
    7fa134999536:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa13499953c:	8b db                	mov    %ebx,%ebx
    7fa13499953e:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134999543:	c1 e2 08             	shl    $0x8,%edx
    7fa134999546:	0b da                	or     %edx,%ebx
    7fa134999548:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499954b:	0b d9                	or     %ecx,%ebx
    7fa13499954d:	c1 e0 18             	shl    $0x18,%eax
    7fa134999550:	0b d8                	or     %eax,%ebx
    7fa134999552:	83 f3 10             	xor    $0x10,%ebx
    7fa134999555:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fa13499955b:	33 d8                	xor    %eax,%ebx
    7fa13499955d:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7fa134999563:	33 c3                	xor    %ebx,%eax
    7fa134999565:	8b 8d e0 fb ff ff    	mov    -0x420(%rbp),%ecx
    7fa13499956b:	33 c8                	xor    %eax,%ecx
    7fa13499956d:	8b 95 f0 fb ff ff    	mov    -0x410(%rbp),%edx
    7fa134999573:	33 d1                	xor    %ecx,%edx
    7fa134999575:	8b f0                	mov    %eax,%esi
    7fa134999577:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499957b:	8b fb                	mov    %ebx,%edi
    7fa13499957d:	48 0b f7             	or     %rdi,%rsi
    7fa134999580:	49 89 b7 00 02 00 00 	mov    %rsi,0x200(%r15)
    7fa134999587:	8b f2                	mov    %edx,%esi
    7fa134999589:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499958d:	8b f9                	mov    %ecx,%edi
    7fa13499958f:	48 0b f7             	or     %rdi,%rsi
    7fa134999592:	49 89 b7 08 02 00 00 	mov    %rsi,0x208(%r15)
    7fa134999599:	49 8b b7 a0 02 00 00 	mov    0x2a0(%r15),%rsi
    7fa1349995a0:	49 8b bf 00 02 00 00 	mov    0x200(%r15),%rdi
    7fa1349995a7:	48 33 f7             	xor    %rdi,%rsi
    7fa1349995aa:	49 89 b7 50 03 00 00 	mov    %rsi,0x350(%r15)
    7fa1349995b1:	49 8b b7 a8 02 00 00 	mov    0x2a8(%r15),%rsi
    7fa1349995b8:	49 8b bf 08 02 00 00 	mov    0x208(%r15),%rdi
    7fa1349995bf:	48 33 f7             	xor    %rdi,%rsi
    7fa1349995c2:	49 89 b7 58 03 00 00 	mov    %rsi,0x358(%r15)
    7fa1349995c9:	49 0f b6 b7 50 01 00 	movzbq 0x150(%r15),%rsi
    7fa1349995d0:	00 
    7fa1349995d1:	8b f6                	mov    %esi,%esi
    7fa1349995d3:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa1349995d8:	8b fe                	mov    %esi,%edi
    7fa1349995da:	83 e7 7f             	and    $0x7f,%edi
    7fa1349995dd:	d1 e7                	shl    %edi
    7fa1349995df:	44 8b c6             	mov    %esi,%r8d
    7fa1349995e2:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa1349995e6:	41 83 e0 01          	and    $0x1,%r8d
    7fa1349995ea:	45 8b c8             	mov    %r8d,%r9d
    7fa1349995ed:	41 d1 e1             	shl    %r9d
    7fa1349995f0:	45 0b c8             	or     %r8d,%r9d
    7fa1349995f3:	45 8b d0             	mov    %r8d,%r10d
    7fa1349995f6:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349995fa:	45 0b ca             	or     %r10d,%r9d
    7fa1349995fd:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134999601:	45 0b c8             	or     %r8d,%r9d
    7fa134999604:	41 33 f9             	xor    %r9d,%edi
    7fa134999607:	4d 0f b6 87 55 01 00 	movzbq 0x155(%r15),%r8
    7fa13499960e:	00 
    7fa13499960f:	45 8b c0             	mov    %r8d,%r8d
    7fa134999612:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134999617:	45 8b c8             	mov    %r8d,%r9d
    7fa13499961a:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499961e:	41 d1 e1             	shl    %r9d
    7fa134999621:	45 8b d0             	mov    %r8d,%r10d
    7fa134999624:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa134999628:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499962c:	45 8b da             	mov    %r10d,%r11d
    7fa13499962f:	41 d1 e3             	shl    %r11d
    7fa134999632:	45 0b da             	or     %r10d,%r11d
    7fa134999635:	44 89 95 18 fb ff ff 	mov    %r10d,-0x4e8(%rbp)
    7fa13499963c:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134999640:	45 0b da             	or     %r10d,%r11d
    7fa134999643:	44 8b 95 18 fb ff ff 	mov    -0x4e8(%rbp),%r10d
    7fa13499964a:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499964e:	45 0b da             	or     %r10d,%r11d
    7fa134999651:	45 33 cb             	xor    %r11d,%r9d
    7fa134999654:	45 8b d1             	mov    %r9d,%r10d
    7fa134999657:	45 33 d0             	xor    %r8d,%r10d
    7fa13499965a:	44 33 d7             	xor    %edi,%r10d
    7fa13499965d:	4d 0f b6 9f 5a 01 00 	movzbq 0x15a(%r15),%r11
    7fa134999664:	00 
    7fa134999665:	45 8b db             	mov    %r11d,%r11d
    7fa134999668:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499966d:	45 33 d3             	xor    %r11d,%r10d
    7fa134999670:	89 85 10 fb ff ff    	mov    %eax,-0x4f0(%rbp)
    7fa134999676:	49 0f b6 87 5f 01 00 	movzbq 0x15f(%r15),%rax
    7fa13499967d:	00 
    7fa13499967e:	8b c0                	mov    %eax,%eax
    7fa134999680:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999685:	44 33 d0             	xor    %eax,%r10d
    7fa134999688:	44 33 ce             	xor    %esi,%r9d
    7fa13499968b:	44 89 9d 08 fb ff ff 	mov    %r11d,-0x4f8(%rbp)
    7fa134999692:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134999696:	41 d1 e3             	shl    %r11d
    7fa134999699:	89 9d 00 fb ff ff    	mov    %ebx,-0x500(%rbp)
    7fa13499969f:	8b 9d 08 fb ff ff    	mov    -0x4f8(%rbp),%ebx
    7fa1349996a5:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349996a8:	83 e3 01             	and    $0x1,%ebx
    7fa1349996ab:	89 9d f8 fa ff ff    	mov    %ebx,-0x508(%rbp)
    7fa1349996b1:	d1 e3                	shl    %ebx
    7fa1349996b3:	89 95 f0 fa ff ff    	mov    %edx,-0x510(%rbp)
    7fa1349996b9:	8b 95 f8 fa ff ff    	mov    -0x508(%rbp),%edx
    7fa1349996bf:	0b da                	or     %edx,%ebx
    7fa1349996c1:	c1 e2 03             	shl    $0x3,%edx
    7fa1349996c4:	0b da                	or     %edx,%ebx
    7fa1349996c6:	8b 95 f8 fa ff ff    	mov    -0x508(%rbp),%edx
    7fa1349996cc:	c1 e2 04             	shl    $0x4,%edx
    7fa1349996cf:	0b da                	or     %edx,%ebx
    7fa1349996d1:	44 33 db             	xor    %ebx,%r11d
    7fa1349996d4:	41 8b d3             	mov    %r11d,%edx
    7fa1349996d7:	8b 9d 08 fb ff ff    	mov    -0x4f8(%rbp),%ebx
    7fa1349996dd:	33 d3                	xor    %ebx,%edx
    7fa1349996df:	44 33 ca             	xor    %edx,%r9d
    7fa1349996e2:	44 33 c8             	xor    %eax,%r9d
    7fa1349996e5:	8b d6                	mov    %esi,%edx
    7fa1349996e7:	41 33 d0             	xor    %r8d,%edx
    7fa1349996ea:	44 33 da             	xor    %edx,%r11d
    7fa1349996ed:	8b d0                	mov    %eax,%edx
    7fa1349996ef:	83 e2 7f             	and    $0x7f,%edx
    7fa1349996f2:	d1 e2                	shl    %edx
    7fa1349996f4:	8b d8                	mov    %eax,%ebx
    7fa1349996f6:	c1 eb 07             	shr    $0x7,%ebx
    7fa1349996f9:	83 e3 01             	and    $0x1,%ebx
    7fa1349996fc:	89 9d e8 fa ff ff    	mov    %ebx,-0x518(%rbp)
    7fa134999702:	d1 e3                	shl    %ebx
    7fa134999704:	89 8d e0 fa ff ff    	mov    %ecx,-0x520(%rbp)
    7fa13499970a:	8b 8d e8 fa ff ff    	mov    -0x518(%rbp),%ecx
    7fa134999710:	0b d9                	or     %ecx,%ebx
    7fa134999712:	c1 e1 03             	shl    $0x3,%ecx
    7fa134999715:	0b d9                	or     %ecx,%ebx
    7fa134999717:	8b 8d e8 fa ff ff    	mov    -0x518(%rbp),%ecx
    7fa13499971d:	c1 e1 04             	shl    $0x4,%ecx
    7fa134999720:	0b d9                	or     %ecx,%ebx
    7fa134999722:	33 d3                	xor    %ebx,%edx
    7fa134999724:	33 c2                	xor    %edx,%eax
    7fa134999726:	44 33 d8             	xor    %eax,%r11d
    7fa134999729:	33 fe                	xor    %esi,%edi
    7fa13499972b:	44 33 c7             	xor    %edi,%r8d
    7fa13499972e:	44 33 85 08 fb ff ff 	xor    -0x4f8(%rbp),%r8d
    7fa134999735:	41 33 d0             	xor    %r8d,%edx
    7fa134999738:	49 0f b6 87 54 01 00 	movzbq 0x154(%r15),%rax
    7fa13499973f:	00 
    7fa134999740:	8b c0                	mov    %eax,%eax
    7fa134999742:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999747:	8b c8                	mov    %eax,%ecx
    7fa134999749:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499974c:	d1 e1                	shl    %ecx
    7fa13499974e:	8b d8                	mov    %eax,%ebx
    7fa134999750:	c1 eb 07             	shr    $0x7,%ebx
    7fa134999753:	83 e3 01             	and    $0x1,%ebx
    7fa134999756:	8b f3                	mov    %ebx,%esi
    7fa134999758:	d1 e6                	shl    %esi
    7fa13499975a:	0b f3                	or     %ebx,%esi
    7fa13499975c:	8b fb                	mov    %ebx,%edi
    7fa13499975e:	c1 e7 03             	shl    $0x3,%edi
    7fa134999761:	0b f7                	or     %edi,%esi
    7fa134999763:	c1 e3 04             	shl    $0x4,%ebx
    7fa134999766:	0b f3                	or     %ebx,%esi
    7fa134999768:	33 ce                	xor    %esi,%ecx
    7fa13499976a:	49 0f b6 9f 59 01 00 	movzbq 0x159(%r15),%rbx
    7fa134999771:	00 
    7fa134999772:	8b db                	mov    %ebx,%ebx
    7fa134999774:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134999779:	8b f3                	mov    %ebx,%esi
    7fa13499977b:	83 e6 7f             	and    $0x7f,%esi
    7fa13499977e:	d1 e6                	shl    %esi
    7fa134999780:	8b fb                	mov    %ebx,%edi
    7fa134999782:	c1 ef 07             	shr    $0x7,%edi
    7fa134999785:	83 e7 01             	and    $0x1,%edi
    7fa134999788:	44 8b c7             	mov    %edi,%r8d
    7fa13499978b:	41 d1 e0             	shl    %r8d
    7fa13499978e:	44 0b c7             	or     %edi,%r8d
    7fa134999791:	89 bd d8 fa ff ff    	mov    %edi,-0x528(%rbp)
    7fa134999797:	c1 e7 03             	shl    $0x3,%edi
    7fa13499979a:	44 0b c7             	or     %edi,%r8d
    7fa13499979d:	8b bd d8 fa ff ff    	mov    -0x528(%rbp),%edi
    7fa1349997a3:	c1 e7 04             	shl    $0x4,%edi
    7fa1349997a6:	44 0b c7             	or     %edi,%r8d
    7fa1349997a9:	41 33 f0             	xor    %r8d,%esi
    7fa1349997ac:	8b fe                	mov    %esi,%edi
    7fa1349997ae:	33 fb                	xor    %ebx,%edi
    7fa1349997b0:	33 f9                	xor    %ecx,%edi
    7fa1349997b2:	4d 0f b6 87 5e 01 00 	movzbq 0x15e(%r15),%r8
    7fa1349997b9:	00 
    7fa1349997ba:	45 8b c0             	mov    %r8d,%r8d
    7fa1349997bd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa1349997c2:	41 33 f8             	xor    %r8d,%edi
    7fa1349997c5:	44 89 95 d0 fa ff ff 	mov    %r10d,-0x530(%rbp)
    7fa1349997cc:	4d 0f b6 97 53 01 00 	movzbq 0x153(%r15),%r10
    7fa1349997d3:	00 
    7fa1349997d4:	45 8b d2             	mov    %r10d,%r10d
    7fa1349997d7:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa1349997dc:	41 33 fa             	xor    %r10d,%edi
    7fa1349997df:	33 f0                	xor    %eax,%esi
    7fa1349997e1:	44 89 85 c8 fa ff ff 	mov    %r8d,-0x538(%rbp)
    7fa1349997e8:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa1349997ec:	41 d1 e0             	shl    %r8d
    7fa1349997ef:	44 89 8d c0 fa ff ff 	mov    %r9d,-0x540(%rbp)
    7fa1349997f6:	44 8b 8d c8 fa ff ff 	mov    -0x538(%rbp),%r9d
    7fa1349997fd:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa134999801:	41 83 e1 01          	and    $0x1,%r9d
    7fa134999805:	44 89 8d b8 fa ff ff 	mov    %r9d,-0x548(%rbp)
    7fa13499980c:	41 d1 e1             	shl    %r9d
    7fa13499980f:	44 89 9d b0 fa ff ff 	mov    %r11d,-0x550(%rbp)
    7fa134999816:	44 8b 9d b8 fa ff ff 	mov    -0x548(%rbp),%r11d
    7fa13499981d:	45 0b cb             	or     %r11d,%r9d
    7fa134999820:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134999824:	45 0b cb             	or     %r11d,%r9d
    7fa134999827:	44 8b 9d b8 fa ff ff 	mov    -0x548(%rbp),%r11d
    7fa13499982e:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134999832:	45 0b cb             	or     %r11d,%r9d
    7fa134999835:	45 33 c1             	xor    %r9d,%r8d
    7fa134999838:	45 8b c8             	mov    %r8d,%r9d
    7fa13499983b:	44 8b 9d c8 fa ff ff 	mov    -0x538(%rbp),%r11d
    7fa134999842:	45 33 cb             	xor    %r11d,%r9d
    7fa134999845:	41 33 f1             	xor    %r9d,%esi
    7fa134999848:	41 33 f2             	xor    %r10d,%esi
    7fa13499984b:	44 8b c8             	mov    %eax,%r9d
    7fa13499984e:	44 33 cb             	xor    %ebx,%r9d
    7fa134999851:	45 33 c1             	xor    %r9d,%r8d
    7fa134999854:	45 8b ca             	mov    %r10d,%r9d
    7fa134999857:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499985b:	41 d1 e1             	shl    %r9d
    7fa13499985e:	45 8b da             	mov    %r10d,%r11d
    7fa134999861:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134999865:	41 83 e3 01          	and    $0x1,%r11d
    7fa134999869:	44 89 9d a8 fa ff ff 	mov    %r11d,-0x558(%rbp)
    7fa134999870:	41 d1 e3             	shl    %r11d
    7fa134999873:	89 95 a0 fa ff ff    	mov    %edx,-0x560(%rbp)
    7fa134999879:	8b 95 a8 fa ff ff    	mov    -0x558(%rbp),%edx
    7fa13499987f:	44 0b da             	or     %edx,%r11d
    7fa134999882:	c1 e2 03             	shl    $0x3,%edx
    7fa134999885:	44 0b da             	or     %edx,%r11d
    7fa134999888:	8b 95 a8 fa ff ff    	mov    -0x558(%rbp),%edx
    7fa13499988e:	c1 e2 04             	shl    $0x4,%edx
    7fa134999891:	44 0b da             	or     %edx,%r11d
    7fa134999894:	45 33 cb             	xor    %r11d,%r9d
    7fa134999897:	45 33 d1             	xor    %r9d,%r10d
    7fa13499989a:	45 33 c2             	xor    %r10d,%r8d
    7fa13499989d:	33 c8                	xor    %eax,%ecx
    7fa13499989f:	33 d9                	xor    %ecx,%ebx
    7fa1349998a1:	33 9d c8 fa ff ff    	xor    -0x538(%rbp),%ebx
    7fa1349998a7:	44 33 cb             	xor    %ebx,%r9d
    7fa1349998aa:	49 0f b6 87 58 01 00 	movzbq 0x158(%r15),%rax
    7fa1349998b1:	00 
    7fa1349998b2:	8b c0                	mov    %eax,%eax
    7fa1349998b4:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa1349998b9:	8b c8                	mov    %eax,%ecx
    7fa1349998bb:	83 e1 7f             	and    $0x7f,%ecx
    7fa1349998be:	d1 e1                	shl    %ecx
    7fa1349998c0:	8b d0                	mov    %eax,%edx
    7fa1349998c2:	c1 ea 07             	shr    $0x7,%edx
    7fa1349998c5:	83 e2 01             	and    $0x1,%edx
    7fa1349998c8:	8b da                	mov    %edx,%ebx
    7fa1349998ca:	d1 e3                	shl    %ebx
    7fa1349998cc:	0b da                	or     %edx,%ebx
    7fa1349998ce:	44 8b d2             	mov    %edx,%r10d
    7fa1349998d1:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa1349998d5:	41 0b da             	or     %r10d,%ebx
    7fa1349998d8:	c1 e2 04             	shl    $0x4,%edx
    7fa1349998db:	0b da                	or     %edx,%ebx
    7fa1349998dd:	33 cb                	xor    %ebx,%ecx
    7fa1349998df:	49 0f b6 97 5d 01 00 	movzbq 0x15d(%r15),%rdx
    7fa1349998e6:	00 
    7fa1349998e7:	8b d2                	mov    %edx,%edx
    7fa1349998e9:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa1349998ee:	8b da                	mov    %edx,%ebx
    7fa1349998f0:	83 e3 7f             	and    $0x7f,%ebx
    7fa1349998f3:	d1 e3                	shl    %ebx
    7fa1349998f5:	44 8b d2             	mov    %edx,%r10d
    7fa1349998f8:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa1349998fc:	41 83 e2 01          	and    $0x1,%r10d
    7fa134999900:	45 8b da             	mov    %r10d,%r11d
    7fa134999903:	41 d1 e3             	shl    %r11d
    7fa134999906:	45 0b da             	or     %r10d,%r11d
    7fa134999909:	44 89 95 98 fa ff ff 	mov    %r10d,-0x568(%rbp)
    7fa134999910:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134999914:	45 0b da             	or     %r10d,%r11d
    7fa134999917:	44 8b 95 98 fa ff ff 	mov    -0x568(%rbp),%r10d
    7fa13499991e:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134999922:	45 0b da             	or     %r10d,%r11d
    7fa134999925:	41 33 db             	xor    %r11d,%ebx
    7fa134999928:	44 8b d3             	mov    %ebx,%r10d
    7fa13499992b:	44 33 d2             	xor    %edx,%r10d
    7fa13499992e:	44 33 d1             	xor    %ecx,%r10d
    7fa134999931:	4d 0f b6 9f 52 01 00 	movzbq 0x152(%r15),%r11
    7fa134999938:	00 
    7fa134999939:	45 8b db             	mov    %r11d,%r11d
    7fa13499993c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134999941:	45 33 d3             	xor    %r11d,%r10d
    7fa134999944:	89 bd 90 fa ff ff    	mov    %edi,-0x570(%rbp)
    7fa13499994a:	49 0f b6 bf 57 01 00 	movzbq 0x157(%r15),%rdi
    7fa134999951:	00 
    7fa134999952:	8b ff                	mov    %edi,%edi
    7fa134999954:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa134999959:	44 33 d7             	xor    %edi,%r10d
    7fa13499995c:	33 d8                	xor    %eax,%ebx
    7fa13499995e:	44 89 9d 88 fa ff ff 	mov    %r11d,-0x578(%rbp)
    7fa134999965:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134999969:	41 d1 e3             	shl    %r11d
    7fa13499996c:	89 b5 80 fa ff ff    	mov    %esi,-0x580(%rbp)
    7fa134999972:	8b b5 88 fa ff ff    	mov    -0x578(%rbp),%esi
    7fa134999978:	c1 ee 07             	shr    $0x7,%esi
    7fa13499997b:	83 e6 01             	and    $0x1,%esi
    7fa13499997e:	89 b5 78 fa ff ff    	mov    %esi,-0x588(%rbp)
    7fa134999984:	d1 e6                	shl    %esi
    7fa134999986:	44 89 85 70 fa ff ff 	mov    %r8d,-0x590(%rbp)
    7fa13499998d:	44 8b 85 78 fa ff ff 	mov    -0x588(%rbp),%r8d
    7fa134999994:	41 0b f0             	or     %r8d,%esi
    7fa134999997:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499999b:	41 0b f0             	or     %r8d,%esi
    7fa13499999e:	44 8b 85 78 fa ff ff 	mov    -0x588(%rbp),%r8d
    7fa1349999a5:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa1349999a9:	41 0b f0             	or     %r8d,%esi
    7fa1349999ac:	44 33 de             	xor    %esi,%r11d
    7fa1349999af:	41 8b f3             	mov    %r11d,%esi
    7fa1349999b2:	44 8b 85 88 fa ff ff 	mov    -0x578(%rbp),%r8d
    7fa1349999b9:	41 33 f0             	xor    %r8d,%esi
    7fa1349999bc:	33 de                	xor    %esi,%ebx
    7fa1349999be:	33 df                	xor    %edi,%ebx
    7fa1349999c0:	8b f0                	mov    %eax,%esi
    7fa1349999c2:	33 f2                	xor    %edx,%esi
    7fa1349999c4:	44 33 de             	xor    %esi,%r11d
    7fa1349999c7:	8b f7                	mov    %edi,%esi
    7fa1349999c9:	83 e6 7f             	and    $0x7f,%esi
    7fa1349999cc:	d1 e6                	shl    %esi
    7fa1349999ce:	44 8b c7             	mov    %edi,%r8d
    7fa1349999d1:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa1349999d5:	41 83 e0 01          	and    $0x1,%r8d
    7fa1349999d9:	44 89 85 68 fa ff ff 	mov    %r8d,-0x598(%rbp)
    7fa1349999e0:	41 d1 e0             	shl    %r8d
    7fa1349999e3:	44 89 8d 60 fa ff ff 	mov    %r9d,-0x5a0(%rbp)
    7fa1349999ea:	44 8b 8d 68 fa ff ff 	mov    -0x598(%rbp),%r9d
    7fa1349999f1:	45 0b c1             	or     %r9d,%r8d
    7fa1349999f4:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa1349999f8:	45 0b c1             	or     %r9d,%r8d
    7fa1349999fb:	44 8b 8d 68 fa ff ff 	mov    -0x598(%rbp),%r9d
    7fa134999a02:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa134999a06:	45 0b c1             	or     %r9d,%r8d
    7fa134999a09:	41 33 f0             	xor    %r8d,%esi
    7fa134999a0c:	33 fe                	xor    %esi,%edi
    7fa134999a0e:	44 33 df             	xor    %edi,%r11d
    7fa134999a11:	33 c8                	xor    %eax,%ecx
    7fa134999a13:	33 d1                	xor    %ecx,%edx
    7fa134999a15:	33 95 88 fa ff ff    	xor    -0x578(%rbp),%edx
    7fa134999a1b:	33 f2                	xor    %edx,%esi
    7fa134999a1d:	49 0f b6 87 5c 01 00 	movzbq 0x15c(%r15),%rax
    7fa134999a24:	00 
    7fa134999a25:	8b c0                	mov    %eax,%eax
    7fa134999a27:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999a2c:	8b c8                	mov    %eax,%ecx
    7fa134999a2e:	83 e1 7f             	and    $0x7f,%ecx
    7fa134999a31:	d1 e1                	shl    %ecx
    7fa134999a33:	8b d0                	mov    %eax,%edx
    7fa134999a35:	c1 ea 07             	shr    $0x7,%edx
    7fa134999a38:	83 e2 01             	and    $0x1,%edx
    7fa134999a3b:	8b fa                	mov    %edx,%edi
    7fa134999a3d:	d1 e7                	shl    %edi
    7fa134999a3f:	0b fa                	or     %edx,%edi
    7fa134999a41:	44 8b c2             	mov    %edx,%r8d
    7fa134999a44:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134999a48:	41 0b f8             	or     %r8d,%edi
    7fa134999a4b:	c1 e2 04             	shl    $0x4,%edx
    7fa134999a4e:	0b fa                	or     %edx,%edi
    7fa134999a50:	33 cf                	xor    %edi,%ecx
    7fa134999a52:	49 0f b6 97 51 01 00 	movzbq 0x151(%r15),%rdx
    7fa134999a59:	00 
    7fa134999a5a:	8b d2                	mov    %edx,%edx
    7fa134999a5c:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134999a61:	8b fa                	mov    %edx,%edi
    7fa134999a63:	83 e7 7f             	and    $0x7f,%edi
    7fa134999a66:	d1 e7                	shl    %edi
    7fa134999a68:	44 8b c2             	mov    %edx,%r8d
    7fa134999a6b:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134999a6f:	41 83 e0 01          	and    $0x1,%r8d
    7fa134999a73:	45 8b c8             	mov    %r8d,%r9d
    7fa134999a76:	41 d1 e1             	shl    %r9d
    7fa134999a79:	45 0b c8             	or     %r8d,%r9d
    7fa134999a7c:	44 89 85 58 fa ff ff 	mov    %r8d,-0x5a8(%rbp)
    7fa134999a83:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa134999a87:	45 0b c8             	or     %r8d,%r9d
    7fa134999a8a:	44 8b 85 58 fa ff ff 	mov    -0x5a8(%rbp),%r8d
    7fa134999a91:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134999a95:	45 0b c8             	or     %r8d,%r9d
    7fa134999a98:	41 33 f9             	xor    %r9d,%edi
    7fa134999a9b:	44 8b c7             	mov    %edi,%r8d
    7fa134999a9e:	44 33 c2             	xor    %edx,%r8d
    7fa134999aa1:	44 33 c1             	xor    %ecx,%r8d
    7fa134999aa4:	4d 0f b6 8f 56 01 00 	movzbq 0x156(%r15),%r9
    7fa134999aab:	00 
    7fa134999aac:	45 8b c9             	mov    %r9d,%r9d
    7fa134999aaf:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa134999ab4:	45 33 c1             	xor    %r9d,%r8d
    7fa134999ab7:	44 89 95 50 fa ff ff 	mov    %r10d,-0x5b0(%rbp)
    7fa134999abe:	4d 0f b6 97 5b 01 00 	movzbq 0x15b(%r15),%r10
    7fa134999ac5:	00 
    7fa134999ac6:	45 8b d2             	mov    %r10d,%r10d
    7fa134999ac9:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa134999ace:	45 33 c2             	xor    %r10d,%r8d
    7fa134999ad1:	33 f8                	xor    %eax,%edi
    7fa134999ad3:	44 89 8d 48 fa ff ff 	mov    %r9d,-0x5b8(%rbp)
    7fa134999ada:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134999ade:	41 d1 e1             	shl    %r9d
    7fa134999ae1:	89 9d 40 fa ff ff    	mov    %ebx,-0x5c0(%rbp)
    7fa134999ae7:	8b 9d 48 fa ff ff    	mov    -0x5b8(%rbp),%ebx
    7fa134999aed:	c1 eb 07             	shr    $0x7,%ebx
    7fa134999af0:	83 e3 01             	and    $0x1,%ebx
    7fa134999af3:	89 9d 38 fa ff ff    	mov    %ebx,-0x5c8(%rbp)
    7fa134999af9:	d1 e3                	shl    %ebx
    7fa134999afb:	44 89 9d 30 fa ff ff 	mov    %r11d,-0x5d0(%rbp)
    7fa134999b02:	44 8b 9d 38 fa ff ff 	mov    -0x5c8(%rbp),%r11d
    7fa134999b09:	41 0b db             	or     %r11d,%ebx
    7fa134999b0c:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134999b10:	41 0b db             	or     %r11d,%ebx
    7fa134999b13:	44 8b 9d 38 fa ff ff 	mov    -0x5c8(%rbp),%r11d
    7fa134999b1a:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134999b1e:	41 0b db             	or     %r11d,%ebx
    7fa134999b21:	44 33 cb             	xor    %ebx,%r9d
    7fa134999b24:	41 8b d9             	mov    %r9d,%ebx
    7fa134999b27:	44 8b 9d 48 fa ff ff 	mov    -0x5b8(%rbp),%r11d
    7fa134999b2e:	41 33 db             	xor    %r11d,%ebx
    7fa134999b31:	33 fb                	xor    %ebx,%edi
    7fa134999b33:	41 33 fa             	xor    %r10d,%edi
    7fa134999b36:	8b d8                	mov    %eax,%ebx
    7fa134999b38:	33 da                	xor    %edx,%ebx
    7fa134999b3a:	44 33 cb             	xor    %ebx,%r9d
    7fa134999b3d:	41 8b da             	mov    %r10d,%ebx
    7fa134999b40:	83 e3 7f             	and    $0x7f,%ebx
    7fa134999b43:	d1 e3                	shl    %ebx
    7fa134999b45:	45 8b da             	mov    %r10d,%r11d
    7fa134999b48:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134999b4c:	41 83 e3 01          	and    $0x1,%r11d
    7fa134999b50:	44 89 9d 28 fa ff ff 	mov    %r11d,-0x5d8(%rbp)
    7fa134999b57:	41 d1 e3             	shl    %r11d
    7fa134999b5a:	89 b5 20 fa ff ff    	mov    %esi,-0x5e0(%rbp)
    7fa134999b60:	8b b5 28 fa ff ff    	mov    -0x5d8(%rbp),%esi
    7fa134999b66:	44 0b de             	or     %esi,%r11d
    7fa134999b69:	c1 e6 03             	shl    $0x3,%esi
    7fa134999b6c:	44 0b de             	or     %esi,%r11d
    7fa134999b6f:	8b b5 28 fa ff ff    	mov    -0x5d8(%rbp),%esi
    7fa134999b75:	c1 e6 04             	shl    $0x4,%esi
    7fa134999b78:	44 0b de             	or     %esi,%r11d
    7fa134999b7b:	41 33 db             	xor    %r11d,%ebx
    7fa134999b7e:	44 33 d3             	xor    %ebx,%r10d
    7fa134999b81:	45 33 ca             	xor    %r10d,%r9d
    7fa134999b84:	33 c8                	xor    %eax,%ecx
    7fa134999b86:	33 d1                	xor    %ecx,%edx
    7fa134999b88:	33 95 48 fa ff ff    	xor    -0x5b8(%rbp),%edx
    7fa134999b8e:	33 da                	xor    %edx,%ebx
    7fa134999b90:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fa134999b96:	c1 e0 08             	shl    $0x8,%eax
    7fa134999b99:	0b 85 d0 fa ff ff    	or     -0x530(%rbp),%eax
    7fa134999b9f:	8b 8d b0 fa ff ff    	mov    -0x550(%rbp),%ecx
    7fa134999ba5:	c1 e1 10             	shl    $0x10,%ecx
    7fa134999ba8:	0b c1                	or     %ecx,%eax
    7fa134999baa:	8b 8d a0 fa ff ff    	mov    -0x560(%rbp),%ecx
    7fa134999bb0:	c1 e1 18             	shl    $0x18,%ecx
    7fa134999bb3:	0b c1                	or     %ecx,%eax
    7fa134999bb5:	8b 8d 90 fa ff ff    	mov    -0x570(%rbp),%ecx
    7fa134999bbb:	8b c9                	mov    %ecx,%ecx
    7fa134999bbd:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa134999bc1:	8b c0                	mov    %eax,%eax
    7fa134999bc3:	48 0b c8             	or     %rax,%rcx
    7fa134999bc6:	8b 85 80 fa ff ff    	mov    -0x580(%rbp),%eax
    7fa134999bcc:	8b c0                	mov    %eax,%eax
    7fa134999bce:	48 c1 e0 28          	shl    $0x28,%rax
    7fa134999bd2:	48 0b c8             	or     %rax,%rcx
    7fa134999bd5:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7fa134999bdb:	8b c0                	mov    %eax,%eax
    7fa134999bdd:	48 c1 e0 30          	shl    $0x30,%rax
    7fa134999be1:	48 0b c8             	or     %rax,%rcx
    7fa134999be4:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7fa134999bea:	8b c0                	mov    %eax,%eax
    7fa134999bec:	48 c1 e0 38          	shl    $0x38,%rax
    7fa134999bf0:	48 0b c8             	or     %rax,%rcx
    7fa134999bf3:	49 89 8f b0 02 00 00 	mov    %rcx,0x2b0(%r15)
    7fa134999bfa:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7fa134999c00:	c1 e0 08             	shl    $0x8,%eax
    7fa134999c03:	0b 85 50 fa ff ff    	or     -0x5b0(%rbp),%eax
    7fa134999c09:	8b 8d 30 fa ff ff    	mov    -0x5d0(%rbp),%ecx
    7fa134999c0f:	c1 e1 10             	shl    $0x10,%ecx
    7fa134999c12:	0b c1                	or     %ecx,%eax
    7fa134999c14:	8b 8d 20 fa ff ff    	mov    -0x5e0(%rbp),%ecx
    7fa134999c1a:	c1 e1 18             	shl    $0x18,%ecx
    7fa134999c1d:	0b c1                	or     %ecx,%eax
    7fa134999c1f:	45 8b c0             	mov    %r8d,%r8d
    7fa134999c22:	49 c1 e0 20          	shl    $0x20,%r8
    7fa134999c26:	8b c0                	mov    %eax,%eax
    7fa134999c28:	4c 0b c0             	or     %rax,%r8
    7fa134999c2b:	8b ff                	mov    %edi,%edi
    7fa134999c2d:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa134999c31:	4c 0b c7             	or     %rdi,%r8
    7fa134999c34:	45 8b c9             	mov    %r9d,%r9d
    7fa134999c37:	49 c1 e1 30          	shl    $0x30,%r9
    7fa134999c3b:	4d 0b c1             	or     %r9,%r8
    7fa134999c3e:	8b db                	mov    %ebx,%ebx
    7fa134999c40:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa134999c44:	4c 0b c3             	or     %rbx,%r8
    7fa134999c47:	4d 89 87 b8 02 00 00 	mov    %r8,0x2b8(%r15)
    7fa134999c4e:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7fa134999c54:	25 ff 00 00 00       	and    $0xff,%eax
    7fa134999c59:	8b c0                	mov    %eax,%eax
    7fa134999c5b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999c60:	8b 8d f0 fa ff ff    	mov    -0x510(%rbp),%ecx
    7fa134999c66:	c1 e9 18             	shr    $0x18,%ecx
    7fa134999c69:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa134999c6f:	8b c9                	mov    %ecx,%ecx
    7fa134999c71:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa134999c76:	8b 95 f0 fa ff ff    	mov    -0x510(%rbp),%edx
    7fa134999c7c:	c1 ea 10             	shr    $0x10,%edx
    7fa134999c7f:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa134999c85:	8b d2                	mov    %edx,%edx
    7fa134999c87:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa134999c8c:	8b 9d f0 fa ff ff    	mov    -0x510(%rbp),%ebx
    7fa134999c92:	c1 eb 08             	shr    $0x8,%ebx
    7fa134999c95:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa134999c9b:	8b db                	mov    %ebx,%ebx
    7fa134999c9d:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134999ca2:	c1 e2 08             	shl    $0x8,%edx
    7fa134999ca5:	0b da                	or     %edx,%ebx
    7fa134999ca7:	c1 e1 10             	shl    $0x10,%ecx
    7fa134999caa:	0b d9                	or     %ecx,%ebx
    7fa134999cac:	c1 e0 18             	shl    $0x18,%eax
    7fa134999caf:	0b d8                	or     %eax,%ebx
    7fa134999cb1:	83 f3 20             	xor    $0x20,%ebx
    7fa134999cb4:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fa134999cba:	33 d8                	xor    %eax,%ebx
    7fa134999cbc:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fa134999cc2:	33 c3                	xor    %ebx,%eax
    7fa134999cc4:	8b 8d e0 fa ff ff    	mov    -0x520(%rbp),%ecx
    7fa134999cca:	33 c8                	xor    %eax,%ecx
    7fa134999ccc:	8b 95 f0 fa ff ff    	mov    -0x510(%rbp),%edx
    7fa134999cd2:	33 d1                	xor    %ecx,%edx
    7fa134999cd4:	8b f0                	mov    %eax,%esi
    7fa134999cd6:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa134999cda:	8b fb                	mov    %ebx,%edi
    7fa134999cdc:	48 0b f7             	or     %rdi,%rsi
    7fa134999cdf:	49 89 b7 10 02 00 00 	mov    %rsi,0x210(%r15)
    7fa134999ce6:	8b f2                	mov    %edx,%esi
    7fa134999ce8:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa134999cec:	8b f9                	mov    %ecx,%edi
    7fa134999cee:	48 0b f7             	or     %rdi,%rsi
    7fa134999cf1:	49 89 b7 18 02 00 00 	mov    %rsi,0x218(%r15)
    7fa134999cf8:	49 8b b7 b0 02 00 00 	mov    0x2b0(%r15),%rsi
    7fa134999cff:	49 8b bf 10 02 00 00 	mov    0x210(%r15),%rdi
    7fa134999d06:	48 33 f7             	xor    %rdi,%rsi
    7fa134999d09:	49 89 b7 60 03 00 00 	mov    %rsi,0x360(%r15)
    7fa134999d10:	49 8b b7 b8 02 00 00 	mov    0x2b8(%r15),%rsi
    7fa134999d17:	49 8b bf 18 02 00 00 	mov    0x218(%r15),%rdi
    7fa134999d1e:	48 33 f7             	xor    %rdi,%rsi
    7fa134999d21:	49 89 b7 68 03 00 00 	mov    %rsi,0x368(%r15)
    7fa134999d28:	49 0f b6 b7 60 01 00 	movzbq 0x160(%r15),%rsi
    7fa134999d2f:	00 
    7fa134999d30:	8b f6                	mov    %esi,%esi
    7fa134999d32:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa134999d37:	8b fe                	mov    %esi,%edi
    7fa134999d39:	83 e7 7f             	and    $0x7f,%edi
    7fa134999d3c:	d1 e7                	shl    %edi
    7fa134999d3e:	44 8b c6             	mov    %esi,%r8d
    7fa134999d41:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa134999d45:	41 83 e0 01          	and    $0x1,%r8d
    7fa134999d49:	45 8b c8             	mov    %r8d,%r9d
    7fa134999d4c:	41 d1 e1             	shl    %r9d
    7fa134999d4f:	45 0b c8             	or     %r8d,%r9d
    7fa134999d52:	45 8b d0             	mov    %r8d,%r10d
    7fa134999d55:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134999d59:	45 0b ca             	or     %r10d,%r9d
    7fa134999d5c:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa134999d60:	45 0b c8             	or     %r8d,%r9d
    7fa134999d63:	41 33 f9             	xor    %r9d,%edi
    7fa134999d66:	4d 0f b6 87 65 01 00 	movzbq 0x165(%r15),%r8
    7fa134999d6d:	00 
    7fa134999d6e:	45 8b c0             	mov    %r8d,%r8d
    7fa134999d71:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134999d76:	45 8b c8             	mov    %r8d,%r9d
    7fa134999d79:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134999d7d:	41 d1 e1             	shl    %r9d
    7fa134999d80:	45 8b d0             	mov    %r8d,%r10d
    7fa134999d83:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa134999d87:	41 83 e2 01          	and    $0x1,%r10d
    7fa134999d8b:	45 8b da             	mov    %r10d,%r11d
    7fa134999d8e:	41 d1 e3             	shl    %r11d
    7fa134999d91:	45 0b da             	or     %r10d,%r11d
    7fa134999d94:	44 89 95 18 fa ff ff 	mov    %r10d,-0x5e8(%rbp)
    7fa134999d9b:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa134999d9f:	45 0b da             	or     %r10d,%r11d
    7fa134999da2:	44 8b 95 18 fa ff ff 	mov    -0x5e8(%rbp),%r10d
    7fa134999da9:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa134999dad:	45 0b da             	or     %r10d,%r11d
    7fa134999db0:	45 33 cb             	xor    %r11d,%r9d
    7fa134999db3:	45 8b d1             	mov    %r9d,%r10d
    7fa134999db6:	45 33 d0             	xor    %r8d,%r10d
    7fa134999db9:	44 33 d7             	xor    %edi,%r10d
    7fa134999dbc:	4d 0f b6 9f 6a 01 00 	movzbq 0x16a(%r15),%r11
    7fa134999dc3:	00 
    7fa134999dc4:	45 8b db             	mov    %r11d,%r11d
    7fa134999dc7:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa134999dcc:	45 33 d3             	xor    %r11d,%r10d
    7fa134999dcf:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7fa134999dd5:	49 0f b6 87 6f 01 00 	movzbq 0x16f(%r15),%rax
    7fa134999ddc:	00 
    7fa134999ddd:	8b c0                	mov    %eax,%eax
    7fa134999ddf:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999de4:	44 33 d0             	xor    %eax,%r10d
    7fa134999de7:	44 33 ce             	xor    %esi,%r9d
    7fa134999dea:	44 89 9d 08 fa ff ff 	mov    %r11d,-0x5f8(%rbp)
    7fa134999df1:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa134999df5:	41 d1 e3             	shl    %r11d
    7fa134999df8:	89 9d 00 fa ff ff    	mov    %ebx,-0x600(%rbp)
    7fa134999dfe:	8b 9d 08 fa ff ff    	mov    -0x5f8(%rbp),%ebx
    7fa134999e04:	c1 eb 07             	shr    $0x7,%ebx
    7fa134999e07:	83 e3 01             	and    $0x1,%ebx
    7fa134999e0a:	89 9d f8 f9 ff ff    	mov    %ebx,-0x608(%rbp)
    7fa134999e10:	d1 e3                	shl    %ebx
    7fa134999e12:	89 95 f0 f9 ff ff    	mov    %edx,-0x610(%rbp)
    7fa134999e18:	8b 95 f8 f9 ff ff    	mov    -0x608(%rbp),%edx
    7fa134999e1e:	0b da                	or     %edx,%ebx
    7fa134999e20:	c1 e2 03             	shl    $0x3,%edx
    7fa134999e23:	0b da                	or     %edx,%ebx
    7fa134999e25:	8b 95 f8 f9 ff ff    	mov    -0x608(%rbp),%edx
    7fa134999e2b:	c1 e2 04             	shl    $0x4,%edx
    7fa134999e2e:	0b da                	or     %edx,%ebx
    7fa134999e30:	44 33 db             	xor    %ebx,%r11d
    7fa134999e33:	41 8b d3             	mov    %r11d,%edx
    7fa134999e36:	8b 9d 08 fa ff ff    	mov    -0x5f8(%rbp),%ebx
    7fa134999e3c:	33 d3                	xor    %ebx,%edx
    7fa134999e3e:	44 33 ca             	xor    %edx,%r9d
    7fa134999e41:	44 33 c8             	xor    %eax,%r9d
    7fa134999e44:	8b d6                	mov    %esi,%edx
    7fa134999e46:	41 33 d0             	xor    %r8d,%edx
    7fa134999e49:	44 33 da             	xor    %edx,%r11d
    7fa134999e4c:	8b d0                	mov    %eax,%edx
    7fa134999e4e:	83 e2 7f             	and    $0x7f,%edx
    7fa134999e51:	d1 e2                	shl    %edx
    7fa134999e53:	8b d8                	mov    %eax,%ebx
    7fa134999e55:	c1 eb 07             	shr    $0x7,%ebx
    7fa134999e58:	83 e3 01             	and    $0x1,%ebx
    7fa134999e5b:	89 9d e8 f9 ff ff    	mov    %ebx,-0x618(%rbp)
    7fa134999e61:	d1 e3                	shl    %ebx
    7fa134999e63:	89 8d e0 f9 ff ff    	mov    %ecx,-0x620(%rbp)
    7fa134999e69:	8b 8d e8 f9 ff ff    	mov    -0x618(%rbp),%ecx
    7fa134999e6f:	0b d9                	or     %ecx,%ebx
    7fa134999e71:	c1 e1 03             	shl    $0x3,%ecx
    7fa134999e74:	0b d9                	or     %ecx,%ebx
    7fa134999e76:	8b 8d e8 f9 ff ff    	mov    -0x618(%rbp),%ecx
    7fa134999e7c:	c1 e1 04             	shl    $0x4,%ecx
    7fa134999e7f:	0b d9                	or     %ecx,%ebx
    7fa134999e81:	33 d3                	xor    %ebx,%edx
    7fa134999e83:	33 c2                	xor    %edx,%eax
    7fa134999e85:	44 33 d8             	xor    %eax,%r11d
    7fa134999e88:	33 fe                	xor    %esi,%edi
    7fa134999e8a:	44 33 c7             	xor    %edi,%r8d
    7fa134999e8d:	44 33 85 08 fa ff ff 	xor    -0x5f8(%rbp),%r8d
    7fa134999e94:	41 33 d0             	xor    %r8d,%edx
    7fa134999e97:	49 0f b6 87 64 01 00 	movzbq 0x164(%r15),%rax
    7fa134999e9e:	00 
    7fa134999e9f:	8b c0                	mov    %eax,%eax
    7fa134999ea1:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa134999ea6:	8b c8                	mov    %eax,%ecx
    7fa134999ea8:	83 e1 7f             	and    $0x7f,%ecx
    7fa134999eab:	d1 e1                	shl    %ecx
    7fa134999ead:	8b d8                	mov    %eax,%ebx
    7fa134999eaf:	c1 eb 07             	shr    $0x7,%ebx
    7fa134999eb2:	83 e3 01             	and    $0x1,%ebx
    7fa134999eb5:	8b f3                	mov    %ebx,%esi
    7fa134999eb7:	d1 e6                	shl    %esi
    7fa134999eb9:	0b f3                	or     %ebx,%esi
    7fa134999ebb:	8b fb                	mov    %ebx,%edi
    7fa134999ebd:	c1 e7 03             	shl    $0x3,%edi
    7fa134999ec0:	0b f7                	or     %edi,%esi
    7fa134999ec2:	c1 e3 04             	shl    $0x4,%ebx
    7fa134999ec5:	0b f3                	or     %ebx,%esi
    7fa134999ec7:	33 ce                	xor    %esi,%ecx
    7fa134999ec9:	49 0f b6 9f 69 01 00 	movzbq 0x169(%r15),%rbx
    7fa134999ed0:	00 
    7fa134999ed1:	8b db                	mov    %ebx,%ebx
    7fa134999ed3:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa134999ed8:	8b f3                	mov    %ebx,%esi
    7fa134999eda:	83 e6 7f             	and    $0x7f,%esi
    7fa134999edd:	d1 e6                	shl    %esi
    7fa134999edf:	8b fb                	mov    %ebx,%edi
    7fa134999ee1:	c1 ef 07             	shr    $0x7,%edi
    7fa134999ee4:	83 e7 01             	and    $0x1,%edi
    7fa134999ee7:	44 8b c7             	mov    %edi,%r8d
    7fa134999eea:	41 d1 e0             	shl    %r8d
    7fa134999eed:	44 0b c7             	or     %edi,%r8d
    7fa134999ef0:	89 bd d8 f9 ff ff    	mov    %edi,-0x628(%rbp)
    7fa134999ef6:	c1 e7 03             	shl    $0x3,%edi
    7fa134999ef9:	44 0b c7             	or     %edi,%r8d
    7fa134999efc:	8b bd d8 f9 ff ff    	mov    -0x628(%rbp),%edi
    7fa134999f02:	c1 e7 04             	shl    $0x4,%edi
    7fa134999f05:	44 0b c7             	or     %edi,%r8d
    7fa134999f08:	41 33 f0             	xor    %r8d,%esi
    7fa134999f0b:	8b fe                	mov    %esi,%edi
    7fa134999f0d:	33 fb                	xor    %ebx,%edi
    7fa134999f0f:	33 f9                	xor    %ecx,%edi
    7fa134999f11:	4d 0f b6 87 6e 01 00 	movzbq 0x16e(%r15),%r8
    7fa134999f18:	00 
    7fa134999f19:	45 8b c0             	mov    %r8d,%r8d
    7fa134999f1c:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa134999f21:	41 33 f8             	xor    %r8d,%edi
    7fa134999f24:	44 89 95 d0 f9 ff ff 	mov    %r10d,-0x630(%rbp)
    7fa134999f2b:	4d 0f b6 97 63 01 00 	movzbq 0x163(%r15),%r10
    7fa134999f32:	00 
    7fa134999f33:	45 8b d2             	mov    %r10d,%r10d
    7fa134999f36:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa134999f3b:	41 33 fa             	xor    %r10d,%edi
    7fa134999f3e:	33 f0                	xor    %eax,%esi
    7fa134999f40:	44 89 85 c8 f9 ff ff 	mov    %r8d,-0x638(%rbp)
    7fa134999f47:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa134999f4b:	41 d1 e0             	shl    %r8d
    7fa134999f4e:	44 89 8d c0 f9 ff ff 	mov    %r9d,-0x640(%rbp)
    7fa134999f55:	44 8b 8d c8 f9 ff ff 	mov    -0x638(%rbp),%r9d
    7fa134999f5c:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa134999f60:	41 83 e1 01          	and    $0x1,%r9d
    7fa134999f64:	44 89 8d b8 f9 ff ff 	mov    %r9d,-0x648(%rbp)
    7fa134999f6b:	41 d1 e1             	shl    %r9d
    7fa134999f6e:	44 89 9d b0 f9 ff ff 	mov    %r11d,-0x650(%rbp)
    7fa134999f75:	44 8b 9d b8 f9 ff ff 	mov    -0x648(%rbp),%r11d
    7fa134999f7c:	45 0b cb             	or     %r11d,%r9d
    7fa134999f7f:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa134999f83:	45 0b cb             	or     %r11d,%r9d
    7fa134999f86:	44 8b 9d b8 f9 ff ff 	mov    -0x648(%rbp),%r11d
    7fa134999f8d:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa134999f91:	45 0b cb             	or     %r11d,%r9d
    7fa134999f94:	45 33 c1             	xor    %r9d,%r8d
    7fa134999f97:	45 8b c8             	mov    %r8d,%r9d
    7fa134999f9a:	44 8b 9d c8 f9 ff ff 	mov    -0x638(%rbp),%r11d
    7fa134999fa1:	45 33 cb             	xor    %r11d,%r9d
    7fa134999fa4:	41 33 f1             	xor    %r9d,%esi
    7fa134999fa7:	41 33 f2             	xor    %r10d,%esi
    7fa134999faa:	44 8b c8             	mov    %eax,%r9d
    7fa134999fad:	44 33 cb             	xor    %ebx,%r9d
    7fa134999fb0:	45 33 c1             	xor    %r9d,%r8d
    7fa134999fb3:	45 8b ca             	mov    %r10d,%r9d
    7fa134999fb6:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa134999fba:	41 d1 e1             	shl    %r9d
    7fa134999fbd:	45 8b da             	mov    %r10d,%r11d
    7fa134999fc0:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa134999fc4:	41 83 e3 01          	and    $0x1,%r11d
    7fa134999fc8:	44 89 9d a8 f9 ff ff 	mov    %r11d,-0x658(%rbp)
    7fa134999fcf:	41 d1 e3             	shl    %r11d
    7fa134999fd2:	89 95 a0 f9 ff ff    	mov    %edx,-0x660(%rbp)
    7fa134999fd8:	8b 95 a8 f9 ff ff    	mov    -0x658(%rbp),%edx
    7fa134999fde:	44 0b da             	or     %edx,%r11d
    7fa134999fe1:	c1 e2 03             	shl    $0x3,%edx
    7fa134999fe4:	44 0b da             	or     %edx,%r11d
    7fa134999fe7:	8b 95 a8 f9 ff ff    	mov    -0x658(%rbp),%edx
    7fa134999fed:	c1 e2 04             	shl    $0x4,%edx
    7fa134999ff0:	44 0b da             	or     %edx,%r11d
    7fa134999ff3:	45 33 cb             	xor    %r11d,%r9d
    7fa134999ff6:	45 33 d1             	xor    %r9d,%r10d
    7fa134999ff9:	45 33 c2             	xor    %r10d,%r8d
    7fa134999ffc:	33 c8                	xor    %eax,%ecx
    7fa134999ffe:	33 d9                	xor    %ecx,%ebx
    7fa13499a000:	33 9d c8 f9 ff ff    	xor    -0x638(%rbp),%ebx
    7fa13499a006:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a009:	49 0f b6 87 68 01 00 	movzbq 0x168(%r15),%rax
    7fa13499a010:	00 
    7fa13499a011:	8b c0                	mov    %eax,%eax
    7fa13499a013:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a018:	8b c8                	mov    %eax,%ecx
    7fa13499a01a:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499a01d:	d1 e1                	shl    %ecx
    7fa13499a01f:	8b d0                	mov    %eax,%edx
    7fa13499a021:	c1 ea 07             	shr    $0x7,%edx
    7fa13499a024:	83 e2 01             	and    $0x1,%edx
    7fa13499a027:	8b da                	mov    %edx,%ebx
    7fa13499a029:	d1 e3                	shl    %ebx
    7fa13499a02b:	0b da                	or     %edx,%ebx
    7fa13499a02d:	44 8b d2             	mov    %edx,%r10d
    7fa13499a030:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499a034:	41 0b da             	or     %r10d,%ebx
    7fa13499a037:	c1 e2 04             	shl    $0x4,%edx
    7fa13499a03a:	0b da                	or     %edx,%ebx
    7fa13499a03c:	33 cb                	xor    %ebx,%ecx
    7fa13499a03e:	49 0f b6 97 6d 01 00 	movzbq 0x16d(%r15),%rdx
    7fa13499a045:	00 
    7fa13499a046:	8b d2                	mov    %edx,%edx
    7fa13499a048:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499a04d:	8b da                	mov    %edx,%ebx
    7fa13499a04f:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499a052:	d1 e3                	shl    %ebx
    7fa13499a054:	44 8b d2             	mov    %edx,%r10d
    7fa13499a057:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499a05b:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499a05f:	45 8b da             	mov    %r10d,%r11d
    7fa13499a062:	41 d1 e3             	shl    %r11d
    7fa13499a065:	45 0b da             	or     %r10d,%r11d
    7fa13499a068:	44 89 95 98 f9 ff ff 	mov    %r10d,-0x668(%rbp)
    7fa13499a06f:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499a073:	45 0b da             	or     %r10d,%r11d
    7fa13499a076:	44 8b 95 98 f9 ff ff 	mov    -0x668(%rbp),%r10d
    7fa13499a07d:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499a081:	45 0b da             	or     %r10d,%r11d
    7fa13499a084:	41 33 db             	xor    %r11d,%ebx
    7fa13499a087:	44 8b d3             	mov    %ebx,%r10d
    7fa13499a08a:	44 33 d2             	xor    %edx,%r10d
    7fa13499a08d:	44 33 d1             	xor    %ecx,%r10d
    7fa13499a090:	4d 0f b6 9f 62 01 00 	movzbq 0x162(%r15),%r11
    7fa13499a097:	00 
    7fa13499a098:	45 8b db             	mov    %r11d,%r11d
    7fa13499a09b:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499a0a0:	45 33 d3             	xor    %r11d,%r10d
    7fa13499a0a3:	89 bd 90 f9 ff ff    	mov    %edi,-0x670(%rbp)
    7fa13499a0a9:	49 0f b6 bf 67 01 00 	movzbq 0x167(%r15),%rdi
    7fa13499a0b0:	00 
    7fa13499a0b1:	8b ff                	mov    %edi,%edi
    7fa13499a0b3:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499a0b8:	44 33 d7             	xor    %edi,%r10d
    7fa13499a0bb:	33 d8                	xor    %eax,%ebx
    7fa13499a0bd:	44 89 9d 88 f9 ff ff 	mov    %r11d,-0x678(%rbp)
    7fa13499a0c4:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499a0c8:	41 d1 e3             	shl    %r11d
    7fa13499a0cb:	89 b5 80 f9 ff ff    	mov    %esi,-0x680(%rbp)
    7fa13499a0d1:	8b b5 88 f9 ff ff    	mov    -0x678(%rbp),%esi
    7fa13499a0d7:	c1 ee 07             	shr    $0x7,%esi
    7fa13499a0da:	83 e6 01             	and    $0x1,%esi
    7fa13499a0dd:	89 b5 78 f9 ff ff    	mov    %esi,-0x688(%rbp)
    7fa13499a0e3:	d1 e6                	shl    %esi
    7fa13499a0e5:	44 89 85 70 f9 ff ff 	mov    %r8d,-0x690(%rbp)
    7fa13499a0ec:	44 8b 85 78 f9 ff ff 	mov    -0x688(%rbp),%r8d
    7fa13499a0f3:	41 0b f0             	or     %r8d,%esi
    7fa13499a0f6:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499a0fa:	41 0b f0             	or     %r8d,%esi
    7fa13499a0fd:	44 8b 85 78 f9 ff ff 	mov    -0x688(%rbp),%r8d
    7fa13499a104:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499a108:	41 0b f0             	or     %r8d,%esi
    7fa13499a10b:	44 33 de             	xor    %esi,%r11d
    7fa13499a10e:	41 8b f3             	mov    %r11d,%esi
    7fa13499a111:	44 8b 85 88 f9 ff ff 	mov    -0x678(%rbp),%r8d
    7fa13499a118:	41 33 f0             	xor    %r8d,%esi
    7fa13499a11b:	33 de                	xor    %esi,%ebx
    7fa13499a11d:	33 df                	xor    %edi,%ebx
    7fa13499a11f:	8b f0                	mov    %eax,%esi
    7fa13499a121:	33 f2                	xor    %edx,%esi
    7fa13499a123:	44 33 de             	xor    %esi,%r11d
    7fa13499a126:	8b f7                	mov    %edi,%esi
    7fa13499a128:	83 e6 7f             	and    $0x7f,%esi
    7fa13499a12b:	d1 e6                	shl    %esi
    7fa13499a12d:	44 8b c7             	mov    %edi,%r8d
    7fa13499a130:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499a134:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499a138:	44 89 85 68 f9 ff ff 	mov    %r8d,-0x698(%rbp)
    7fa13499a13f:	41 d1 e0             	shl    %r8d
    7fa13499a142:	44 89 8d 60 f9 ff ff 	mov    %r9d,-0x6a0(%rbp)
    7fa13499a149:	44 8b 8d 68 f9 ff ff 	mov    -0x698(%rbp),%r9d
    7fa13499a150:	45 0b c1             	or     %r9d,%r8d
    7fa13499a153:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa13499a157:	45 0b c1             	or     %r9d,%r8d
    7fa13499a15a:	44 8b 8d 68 f9 ff ff 	mov    -0x698(%rbp),%r9d
    7fa13499a161:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa13499a165:	45 0b c1             	or     %r9d,%r8d
    7fa13499a168:	41 33 f0             	xor    %r8d,%esi
    7fa13499a16b:	33 fe                	xor    %esi,%edi
    7fa13499a16d:	44 33 df             	xor    %edi,%r11d
    7fa13499a170:	33 c8                	xor    %eax,%ecx
    7fa13499a172:	33 d1                	xor    %ecx,%edx
    7fa13499a174:	33 95 88 f9 ff ff    	xor    -0x678(%rbp),%edx
    7fa13499a17a:	33 f2                	xor    %edx,%esi
    7fa13499a17c:	49 0f b6 87 6c 01 00 	movzbq 0x16c(%r15),%rax
    7fa13499a183:	00 
    7fa13499a184:	8b c0                	mov    %eax,%eax
    7fa13499a186:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a18b:	8b c8                	mov    %eax,%ecx
    7fa13499a18d:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499a190:	d1 e1                	shl    %ecx
    7fa13499a192:	8b d0                	mov    %eax,%edx
    7fa13499a194:	c1 ea 07             	shr    $0x7,%edx
    7fa13499a197:	83 e2 01             	and    $0x1,%edx
    7fa13499a19a:	8b fa                	mov    %edx,%edi
    7fa13499a19c:	d1 e7                	shl    %edi
    7fa13499a19e:	0b fa                	or     %edx,%edi
    7fa13499a1a0:	44 8b c2             	mov    %edx,%r8d
    7fa13499a1a3:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499a1a7:	41 0b f8             	or     %r8d,%edi
    7fa13499a1aa:	c1 e2 04             	shl    $0x4,%edx
    7fa13499a1ad:	0b fa                	or     %edx,%edi
    7fa13499a1af:	33 cf                	xor    %edi,%ecx
    7fa13499a1b1:	49 0f b6 97 61 01 00 	movzbq 0x161(%r15),%rdx
    7fa13499a1b8:	00 
    7fa13499a1b9:	8b d2                	mov    %edx,%edx
    7fa13499a1bb:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499a1c0:	8b fa                	mov    %edx,%edi
    7fa13499a1c2:	83 e7 7f             	and    $0x7f,%edi
    7fa13499a1c5:	d1 e7                	shl    %edi
    7fa13499a1c7:	44 8b c2             	mov    %edx,%r8d
    7fa13499a1ca:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499a1ce:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499a1d2:	45 8b c8             	mov    %r8d,%r9d
    7fa13499a1d5:	41 d1 e1             	shl    %r9d
    7fa13499a1d8:	45 0b c8             	or     %r8d,%r9d
    7fa13499a1db:	44 89 85 58 f9 ff ff 	mov    %r8d,-0x6a8(%rbp)
    7fa13499a1e2:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499a1e6:	45 0b c8             	or     %r8d,%r9d
    7fa13499a1e9:	44 8b 85 58 f9 ff ff 	mov    -0x6a8(%rbp),%r8d
    7fa13499a1f0:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499a1f4:	45 0b c8             	or     %r8d,%r9d
    7fa13499a1f7:	41 33 f9             	xor    %r9d,%edi
    7fa13499a1fa:	44 8b c7             	mov    %edi,%r8d
    7fa13499a1fd:	44 33 c2             	xor    %edx,%r8d
    7fa13499a200:	44 33 c1             	xor    %ecx,%r8d
    7fa13499a203:	4d 0f b6 8f 66 01 00 	movzbq 0x166(%r15),%r9
    7fa13499a20a:	00 
    7fa13499a20b:	45 8b c9             	mov    %r9d,%r9d
    7fa13499a20e:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa13499a213:	45 33 c1             	xor    %r9d,%r8d
    7fa13499a216:	44 89 95 50 f9 ff ff 	mov    %r10d,-0x6b0(%rbp)
    7fa13499a21d:	4d 0f b6 97 6b 01 00 	movzbq 0x16b(%r15),%r10
    7fa13499a224:	00 
    7fa13499a225:	45 8b d2             	mov    %r10d,%r10d
    7fa13499a228:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499a22d:	45 33 c2             	xor    %r10d,%r8d
    7fa13499a230:	33 f8                	xor    %eax,%edi
    7fa13499a232:	44 89 8d 48 f9 ff ff 	mov    %r9d,-0x6b8(%rbp)
    7fa13499a239:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499a23d:	41 d1 e1             	shl    %r9d
    7fa13499a240:	89 9d 40 f9 ff ff    	mov    %ebx,-0x6c0(%rbp)
    7fa13499a246:	8b 9d 48 f9 ff ff    	mov    -0x6b8(%rbp),%ebx
    7fa13499a24c:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499a24f:	83 e3 01             	and    $0x1,%ebx
    7fa13499a252:	89 9d 38 f9 ff ff    	mov    %ebx,-0x6c8(%rbp)
    7fa13499a258:	d1 e3                	shl    %ebx
    7fa13499a25a:	44 89 9d 30 f9 ff ff 	mov    %r11d,-0x6d0(%rbp)
    7fa13499a261:	44 8b 9d 38 f9 ff ff 	mov    -0x6c8(%rbp),%r11d
    7fa13499a268:	41 0b db             	or     %r11d,%ebx
    7fa13499a26b:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa13499a26f:	41 0b db             	or     %r11d,%ebx
    7fa13499a272:	44 8b 9d 38 f9 ff ff 	mov    -0x6c8(%rbp),%r11d
    7fa13499a279:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa13499a27d:	41 0b db             	or     %r11d,%ebx
    7fa13499a280:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a283:	41 8b d9             	mov    %r9d,%ebx
    7fa13499a286:	44 8b 9d 48 f9 ff ff 	mov    -0x6b8(%rbp),%r11d
    7fa13499a28d:	41 33 db             	xor    %r11d,%ebx
    7fa13499a290:	33 fb                	xor    %ebx,%edi
    7fa13499a292:	41 33 fa             	xor    %r10d,%edi
    7fa13499a295:	8b d8                	mov    %eax,%ebx
    7fa13499a297:	33 da                	xor    %edx,%ebx
    7fa13499a299:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a29c:	41 8b da             	mov    %r10d,%ebx
    7fa13499a29f:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499a2a2:	d1 e3                	shl    %ebx
    7fa13499a2a4:	45 8b da             	mov    %r10d,%r11d
    7fa13499a2a7:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499a2ab:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499a2af:	44 89 9d 28 f9 ff ff 	mov    %r11d,-0x6d8(%rbp)
    7fa13499a2b6:	41 d1 e3             	shl    %r11d
    7fa13499a2b9:	89 b5 20 f9 ff ff    	mov    %esi,-0x6e0(%rbp)
    7fa13499a2bf:	8b b5 28 f9 ff ff    	mov    -0x6d8(%rbp),%esi
    7fa13499a2c5:	44 0b de             	or     %esi,%r11d
    7fa13499a2c8:	c1 e6 03             	shl    $0x3,%esi
    7fa13499a2cb:	44 0b de             	or     %esi,%r11d
    7fa13499a2ce:	8b b5 28 f9 ff ff    	mov    -0x6d8(%rbp),%esi
    7fa13499a2d4:	c1 e6 04             	shl    $0x4,%esi
    7fa13499a2d7:	44 0b de             	or     %esi,%r11d
    7fa13499a2da:	41 33 db             	xor    %r11d,%ebx
    7fa13499a2dd:	44 33 d3             	xor    %ebx,%r10d
    7fa13499a2e0:	45 33 ca             	xor    %r10d,%r9d
    7fa13499a2e3:	33 c8                	xor    %eax,%ecx
    7fa13499a2e5:	33 d1                	xor    %ecx,%edx
    7fa13499a2e7:	33 95 48 f9 ff ff    	xor    -0x6b8(%rbp),%edx
    7fa13499a2ed:	33 da                	xor    %edx,%ebx
    7fa13499a2ef:	8b 85 c0 f9 ff ff    	mov    -0x640(%rbp),%eax
    7fa13499a2f5:	c1 e0 08             	shl    $0x8,%eax
    7fa13499a2f8:	0b 85 d0 f9 ff ff    	or     -0x630(%rbp),%eax
    7fa13499a2fe:	8b 8d b0 f9 ff ff    	mov    -0x650(%rbp),%ecx
    7fa13499a304:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499a307:	0b c1                	or     %ecx,%eax
    7fa13499a309:	8b 8d a0 f9 ff ff    	mov    -0x660(%rbp),%ecx
    7fa13499a30f:	c1 e1 18             	shl    $0x18,%ecx
    7fa13499a312:	0b c1                	or     %ecx,%eax
    7fa13499a314:	8b 8d 90 f9 ff ff    	mov    -0x670(%rbp),%ecx
    7fa13499a31a:	8b c9                	mov    %ecx,%ecx
    7fa13499a31c:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa13499a320:	8b c0                	mov    %eax,%eax
    7fa13499a322:	48 0b c8             	or     %rax,%rcx
    7fa13499a325:	8b 85 80 f9 ff ff    	mov    -0x680(%rbp),%eax
    7fa13499a32b:	8b c0                	mov    %eax,%eax
    7fa13499a32d:	48 c1 e0 28          	shl    $0x28,%rax
    7fa13499a331:	48 0b c8             	or     %rax,%rcx
    7fa13499a334:	8b 85 70 f9 ff ff    	mov    -0x690(%rbp),%eax
    7fa13499a33a:	8b c0                	mov    %eax,%eax
    7fa13499a33c:	48 c1 e0 30          	shl    $0x30,%rax
    7fa13499a340:	48 0b c8             	or     %rax,%rcx
    7fa13499a343:	8b 85 60 f9 ff ff    	mov    -0x6a0(%rbp),%eax
    7fa13499a349:	8b c0                	mov    %eax,%eax
    7fa13499a34b:	48 c1 e0 38          	shl    $0x38,%rax
    7fa13499a34f:	48 0b c8             	or     %rax,%rcx
    7fa13499a352:	49 89 8f c0 02 00 00 	mov    %rcx,0x2c0(%r15)
    7fa13499a359:	8b 85 40 f9 ff ff    	mov    -0x6c0(%rbp),%eax
    7fa13499a35f:	c1 e0 08             	shl    $0x8,%eax
    7fa13499a362:	0b 85 50 f9 ff ff    	or     -0x6b0(%rbp),%eax
    7fa13499a368:	8b 8d 30 f9 ff ff    	mov    -0x6d0(%rbp),%ecx
    7fa13499a36e:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499a371:	0b c1                	or     %ecx,%eax
    7fa13499a373:	8b 8d 20 f9 ff ff    	mov    -0x6e0(%rbp),%ecx
    7fa13499a379:	c1 e1 18             	shl    $0x18,%ecx
    7fa13499a37c:	0b c1                	or     %ecx,%eax
    7fa13499a37e:	45 8b c0             	mov    %r8d,%r8d
    7fa13499a381:	49 c1 e0 20          	shl    $0x20,%r8
    7fa13499a385:	8b c0                	mov    %eax,%eax
    7fa13499a387:	4c 0b c0             	or     %rax,%r8
    7fa13499a38a:	8b ff                	mov    %edi,%edi
    7fa13499a38c:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa13499a390:	4c 0b c7             	or     %rdi,%r8
    7fa13499a393:	45 8b c9             	mov    %r9d,%r9d
    7fa13499a396:	49 c1 e1 30          	shl    $0x30,%r9
    7fa13499a39a:	4d 0b c1             	or     %r9,%r8
    7fa13499a39d:	8b db                	mov    %ebx,%ebx
    7fa13499a39f:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa13499a3a3:	4c 0b c3             	or     %rbx,%r8
    7fa13499a3a6:	4d 89 87 c8 02 00 00 	mov    %r8,0x2c8(%r15)
    7fa13499a3ad:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7fa13499a3b3:	25 ff 00 00 00       	and    $0xff,%eax
    7fa13499a3b8:	8b c0                	mov    %eax,%eax
    7fa13499a3ba:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a3bf:	8b 8d f0 f9 ff ff    	mov    -0x610(%rbp),%ecx
    7fa13499a3c5:	c1 e9 18             	shr    $0x18,%ecx
    7fa13499a3c8:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa13499a3ce:	8b c9                	mov    %ecx,%ecx
    7fa13499a3d0:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa13499a3d5:	8b 95 f0 f9 ff ff    	mov    -0x610(%rbp),%edx
    7fa13499a3db:	c1 ea 10             	shr    $0x10,%edx
    7fa13499a3de:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa13499a3e4:	8b d2                	mov    %edx,%edx
    7fa13499a3e6:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499a3eb:	8b 9d f0 f9 ff ff    	mov    -0x610(%rbp),%ebx
    7fa13499a3f1:	c1 eb 08             	shr    $0x8,%ebx
    7fa13499a3f4:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa13499a3fa:	8b db                	mov    %ebx,%ebx
    7fa13499a3fc:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499a401:	c1 e2 08             	shl    $0x8,%edx
    7fa13499a404:	0b da                	or     %edx,%ebx
    7fa13499a406:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499a409:	0b d9                	or     %ecx,%ebx
    7fa13499a40b:	c1 e0 18             	shl    $0x18,%eax
    7fa13499a40e:	0b d8                	or     %eax,%ebx
    7fa13499a410:	83 f3 40             	xor    $0x40,%ebx
    7fa13499a413:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7fa13499a419:	33 d8                	xor    %eax,%ebx
    7fa13499a41b:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7fa13499a421:	33 c3                	xor    %ebx,%eax
    7fa13499a423:	8b 8d e0 f9 ff ff    	mov    -0x620(%rbp),%ecx
    7fa13499a429:	33 c8                	xor    %eax,%ecx
    7fa13499a42b:	8b 95 f0 f9 ff ff    	mov    -0x610(%rbp),%edx
    7fa13499a431:	33 d1                	xor    %ecx,%edx
    7fa13499a433:	8b f0                	mov    %eax,%esi
    7fa13499a435:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499a439:	8b fb                	mov    %ebx,%edi
    7fa13499a43b:	48 0b f7             	or     %rdi,%rsi
    7fa13499a43e:	49 89 b7 20 02 00 00 	mov    %rsi,0x220(%r15)
    7fa13499a445:	8b f2                	mov    %edx,%esi
    7fa13499a447:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499a44b:	8b f9                	mov    %ecx,%edi
    7fa13499a44d:	48 0b f7             	or     %rdi,%rsi
    7fa13499a450:	49 89 b7 28 02 00 00 	mov    %rsi,0x228(%r15)
    7fa13499a457:	49 8b b7 c0 02 00 00 	mov    0x2c0(%r15),%rsi
    7fa13499a45e:	49 8b bf 20 02 00 00 	mov    0x220(%r15),%rdi
    7fa13499a465:	48 33 f7             	xor    %rdi,%rsi
    7fa13499a468:	49 89 b7 70 03 00 00 	mov    %rsi,0x370(%r15)
    7fa13499a46f:	49 8b b7 c8 02 00 00 	mov    0x2c8(%r15),%rsi
    7fa13499a476:	49 8b bf 28 02 00 00 	mov    0x228(%r15),%rdi
    7fa13499a47d:	48 33 f7             	xor    %rdi,%rsi
    7fa13499a480:	49 89 b7 78 03 00 00 	mov    %rsi,0x378(%r15)
    7fa13499a487:	49 0f b6 b7 70 01 00 	movzbq 0x170(%r15),%rsi
    7fa13499a48e:	00 
    7fa13499a48f:	8b f6                	mov    %esi,%esi
    7fa13499a491:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa13499a496:	8b fe                	mov    %esi,%edi
    7fa13499a498:	83 e7 7f             	and    $0x7f,%edi
    7fa13499a49b:	d1 e7                	shl    %edi
    7fa13499a49d:	44 8b c6             	mov    %esi,%r8d
    7fa13499a4a0:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499a4a4:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499a4a8:	45 8b c8             	mov    %r8d,%r9d
    7fa13499a4ab:	41 d1 e1             	shl    %r9d
    7fa13499a4ae:	45 0b c8             	or     %r8d,%r9d
    7fa13499a4b1:	45 8b d0             	mov    %r8d,%r10d
    7fa13499a4b4:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499a4b8:	45 0b ca             	or     %r10d,%r9d
    7fa13499a4bb:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499a4bf:	45 0b c8             	or     %r8d,%r9d
    7fa13499a4c2:	41 33 f9             	xor    %r9d,%edi
    7fa13499a4c5:	4d 0f b6 87 75 01 00 	movzbq 0x175(%r15),%r8
    7fa13499a4cc:	00 
    7fa13499a4cd:	45 8b c0             	mov    %r8d,%r8d
    7fa13499a4d0:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499a4d5:	45 8b c8             	mov    %r8d,%r9d
    7fa13499a4d8:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499a4dc:	41 d1 e1             	shl    %r9d
    7fa13499a4df:	45 8b d0             	mov    %r8d,%r10d
    7fa13499a4e2:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499a4e6:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499a4ea:	45 8b da             	mov    %r10d,%r11d
    7fa13499a4ed:	41 d1 e3             	shl    %r11d
    7fa13499a4f0:	45 0b da             	or     %r10d,%r11d
    7fa13499a4f3:	44 89 95 18 f9 ff ff 	mov    %r10d,-0x6e8(%rbp)
    7fa13499a4fa:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499a4fe:	45 0b da             	or     %r10d,%r11d
    7fa13499a501:	44 8b 95 18 f9 ff ff 	mov    -0x6e8(%rbp),%r10d
    7fa13499a508:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499a50c:	45 0b da             	or     %r10d,%r11d
    7fa13499a50f:	45 33 cb             	xor    %r11d,%r9d
    7fa13499a512:	45 8b d1             	mov    %r9d,%r10d
    7fa13499a515:	45 33 d0             	xor    %r8d,%r10d
    7fa13499a518:	44 33 d7             	xor    %edi,%r10d
    7fa13499a51b:	4d 0f b6 9f 7a 01 00 	movzbq 0x17a(%r15),%r11
    7fa13499a522:	00 
    7fa13499a523:	45 8b db             	mov    %r11d,%r11d
    7fa13499a526:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499a52b:	45 33 d3             	xor    %r11d,%r10d
    7fa13499a52e:	89 85 10 f9 ff ff    	mov    %eax,-0x6f0(%rbp)
    7fa13499a534:	49 0f b6 87 7f 01 00 	movzbq 0x17f(%r15),%rax
    7fa13499a53b:	00 
    7fa13499a53c:	8b c0                	mov    %eax,%eax
    7fa13499a53e:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a543:	44 33 d0             	xor    %eax,%r10d
    7fa13499a546:	44 33 ce             	xor    %esi,%r9d
    7fa13499a549:	44 89 9d 08 f9 ff ff 	mov    %r11d,-0x6f8(%rbp)
    7fa13499a550:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499a554:	41 d1 e3             	shl    %r11d
    7fa13499a557:	89 9d 00 f9 ff ff    	mov    %ebx,-0x700(%rbp)
    7fa13499a55d:	8b 9d 08 f9 ff ff    	mov    -0x6f8(%rbp),%ebx
    7fa13499a563:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499a566:	83 e3 01             	and    $0x1,%ebx
    7fa13499a569:	89 9d f8 f8 ff ff    	mov    %ebx,-0x708(%rbp)
    7fa13499a56f:	d1 e3                	shl    %ebx
    7fa13499a571:	89 95 f0 f8 ff ff    	mov    %edx,-0x710(%rbp)
    7fa13499a577:	8b 95 f8 f8 ff ff    	mov    -0x708(%rbp),%edx
    7fa13499a57d:	0b da                	or     %edx,%ebx
    7fa13499a57f:	c1 e2 03             	shl    $0x3,%edx
    7fa13499a582:	0b da                	or     %edx,%ebx
    7fa13499a584:	8b 95 f8 f8 ff ff    	mov    -0x708(%rbp),%edx
    7fa13499a58a:	c1 e2 04             	shl    $0x4,%edx
    7fa13499a58d:	0b da                	or     %edx,%ebx
    7fa13499a58f:	44 33 db             	xor    %ebx,%r11d
    7fa13499a592:	41 8b d3             	mov    %r11d,%edx
    7fa13499a595:	8b 9d 08 f9 ff ff    	mov    -0x6f8(%rbp),%ebx
    7fa13499a59b:	33 d3                	xor    %ebx,%edx
    7fa13499a59d:	44 33 ca             	xor    %edx,%r9d
    7fa13499a5a0:	44 33 c8             	xor    %eax,%r9d
    7fa13499a5a3:	8b d6                	mov    %esi,%edx
    7fa13499a5a5:	41 33 d0             	xor    %r8d,%edx
    7fa13499a5a8:	44 33 da             	xor    %edx,%r11d
    7fa13499a5ab:	8b d0                	mov    %eax,%edx
    7fa13499a5ad:	83 e2 7f             	and    $0x7f,%edx
    7fa13499a5b0:	d1 e2                	shl    %edx
    7fa13499a5b2:	8b d8                	mov    %eax,%ebx
    7fa13499a5b4:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499a5b7:	83 e3 01             	and    $0x1,%ebx
    7fa13499a5ba:	89 9d e8 f8 ff ff    	mov    %ebx,-0x718(%rbp)
    7fa13499a5c0:	d1 e3                	shl    %ebx
    7fa13499a5c2:	89 8d e0 f8 ff ff    	mov    %ecx,-0x720(%rbp)
    7fa13499a5c8:	8b 8d e8 f8 ff ff    	mov    -0x718(%rbp),%ecx
    7fa13499a5ce:	0b d9                	or     %ecx,%ebx
    7fa13499a5d0:	c1 e1 03             	shl    $0x3,%ecx
    7fa13499a5d3:	0b d9                	or     %ecx,%ebx
    7fa13499a5d5:	8b 8d e8 f8 ff ff    	mov    -0x718(%rbp),%ecx
    7fa13499a5db:	c1 e1 04             	shl    $0x4,%ecx
    7fa13499a5de:	0b d9                	or     %ecx,%ebx
    7fa13499a5e0:	33 d3                	xor    %ebx,%edx
    7fa13499a5e2:	33 c2                	xor    %edx,%eax
    7fa13499a5e4:	44 33 d8             	xor    %eax,%r11d
    7fa13499a5e7:	33 fe                	xor    %esi,%edi
    7fa13499a5e9:	44 33 c7             	xor    %edi,%r8d
    7fa13499a5ec:	44 33 85 08 f9 ff ff 	xor    -0x6f8(%rbp),%r8d
    7fa13499a5f3:	41 33 d0             	xor    %r8d,%edx
    7fa13499a5f6:	49 0f b6 87 74 01 00 	movzbq 0x174(%r15),%rax
    7fa13499a5fd:	00 
    7fa13499a5fe:	8b c0                	mov    %eax,%eax
    7fa13499a600:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a605:	8b c8                	mov    %eax,%ecx
    7fa13499a607:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499a60a:	d1 e1                	shl    %ecx
    7fa13499a60c:	8b d8                	mov    %eax,%ebx
    7fa13499a60e:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499a611:	83 e3 01             	and    $0x1,%ebx
    7fa13499a614:	8b f3                	mov    %ebx,%esi
    7fa13499a616:	d1 e6                	shl    %esi
    7fa13499a618:	0b f3                	or     %ebx,%esi
    7fa13499a61a:	8b fb                	mov    %ebx,%edi
    7fa13499a61c:	c1 e7 03             	shl    $0x3,%edi
    7fa13499a61f:	0b f7                	or     %edi,%esi
    7fa13499a621:	c1 e3 04             	shl    $0x4,%ebx
    7fa13499a624:	0b f3                	or     %ebx,%esi
    7fa13499a626:	33 ce                	xor    %esi,%ecx
    7fa13499a628:	49 0f b6 9f 79 01 00 	movzbq 0x179(%r15),%rbx
    7fa13499a62f:	00 
    7fa13499a630:	8b db                	mov    %ebx,%ebx
    7fa13499a632:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499a637:	8b f3                	mov    %ebx,%esi
    7fa13499a639:	83 e6 7f             	and    $0x7f,%esi
    7fa13499a63c:	d1 e6                	shl    %esi
    7fa13499a63e:	8b fb                	mov    %ebx,%edi
    7fa13499a640:	c1 ef 07             	shr    $0x7,%edi
    7fa13499a643:	83 e7 01             	and    $0x1,%edi
    7fa13499a646:	44 8b c7             	mov    %edi,%r8d
    7fa13499a649:	41 d1 e0             	shl    %r8d
    7fa13499a64c:	44 0b c7             	or     %edi,%r8d
    7fa13499a64f:	89 bd d8 f8 ff ff    	mov    %edi,-0x728(%rbp)
    7fa13499a655:	c1 e7 03             	shl    $0x3,%edi
    7fa13499a658:	44 0b c7             	or     %edi,%r8d
    7fa13499a65b:	8b bd d8 f8 ff ff    	mov    -0x728(%rbp),%edi
    7fa13499a661:	c1 e7 04             	shl    $0x4,%edi
    7fa13499a664:	44 0b c7             	or     %edi,%r8d
    7fa13499a667:	41 33 f0             	xor    %r8d,%esi
    7fa13499a66a:	8b fe                	mov    %esi,%edi
    7fa13499a66c:	33 fb                	xor    %ebx,%edi
    7fa13499a66e:	33 f9                	xor    %ecx,%edi
    7fa13499a670:	4d 0f b6 87 7e 01 00 	movzbq 0x17e(%r15),%r8
    7fa13499a677:	00 
    7fa13499a678:	45 8b c0             	mov    %r8d,%r8d
    7fa13499a67b:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499a680:	41 33 f8             	xor    %r8d,%edi
    7fa13499a683:	44 89 95 d0 f8 ff ff 	mov    %r10d,-0x730(%rbp)
    7fa13499a68a:	4d 0f b6 97 73 01 00 	movzbq 0x173(%r15),%r10
    7fa13499a691:	00 
    7fa13499a692:	45 8b d2             	mov    %r10d,%r10d
    7fa13499a695:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499a69a:	41 33 fa             	xor    %r10d,%edi
    7fa13499a69d:	33 f0                	xor    %eax,%esi
    7fa13499a69f:	44 89 85 c8 f8 ff ff 	mov    %r8d,-0x738(%rbp)
    7fa13499a6a6:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa13499a6aa:	41 d1 e0             	shl    %r8d
    7fa13499a6ad:	44 89 8d c0 f8 ff ff 	mov    %r9d,-0x740(%rbp)
    7fa13499a6b4:	44 8b 8d c8 f8 ff ff 	mov    -0x738(%rbp),%r9d
    7fa13499a6bb:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa13499a6bf:	41 83 e1 01          	and    $0x1,%r9d
    7fa13499a6c3:	44 89 8d b8 f8 ff ff 	mov    %r9d,-0x748(%rbp)
    7fa13499a6ca:	41 d1 e1             	shl    %r9d
    7fa13499a6cd:	44 89 9d b0 f8 ff ff 	mov    %r11d,-0x750(%rbp)
    7fa13499a6d4:	44 8b 9d b8 f8 ff ff 	mov    -0x748(%rbp),%r11d
    7fa13499a6db:	45 0b cb             	or     %r11d,%r9d
    7fa13499a6de:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa13499a6e2:	45 0b cb             	or     %r11d,%r9d
    7fa13499a6e5:	44 8b 9d b8 f8 ff ff 	mov    -0x748(%rbp),%r11d
    7fa13499a6ec:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa13499a6f0:	45 0b cb             	or     %r11d,%r9d
    7fa13499a6f3:	45 33 c1             	xor    %r9d,%r8d
    7fa13499a6f6:	45 8b c8             	mov    %r8d,%r9d
    7fa13499a6f9:	44 8b 9d c8 f8 ff ff 	mov    -0x738(%rbp),%r11d
    7fa13499a700:	45 33 cb             	xor    %r11d,%r9d
    7fa13499a703:	41 33 f1             	xor    %r9d,%esi
    7fa13499a706:	41 33 f2             	xor    %r10d,%esi
    7fa13499a709:	44 8b c8             	mov    %eax,%r9d
    7fa13499a70c:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a70f:	45 33 c1             	xor    %r9d,%r8d
    7fa13499a712:	45 8b ca             	mov    %r10d,%r9d
    7fa13499a715:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499a719:	41 d1 e1             	shl    %r9d
    7fa13499a71c:	45 8b da             	mov    %r10d,%r11d
    7fa13499a71f:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499a723:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499a727:	44 89 9d a8 f8 ff ff 	mov    %r11d,-0x758(%rbp)
    7fa13499a72e:	41 d1 e3             	shl    %r11d
    7fa13499a731:	89 95 a0 f8 ff ff    	mov    %edx,-0x760(%rbp)
    7fa13499a737:	8b 95 a8 f8 ff ff    	mov    -0x758(%rbp),%edx
    7fa13499a73d:	44 0b da             	or     %edx,%r11d
    7fa13499a740:	c1 e2 03             	shl    $0x3,%edx
    7fa13499a743:	44 0b da             	or     %edx,%r11d
    7fa13499a746:	8b 95 a8 f8 ff ff    	mov    -0x758(%rbp),%edx
    7fa13499a74c:	c1 e2 04             	shl    $0x4,%edx
    7fa13499a74f:	44 0b da             	or     %edx,%r11d
    7fa13499a752:	45 33 cb             	xor    %r11d,%r9d
    7fa13499a755:	45 33 d1             	xor    %r9d,%r10d
    7fa13499a758:	45 33 c2             	xor    %r10d,%r8d
    7fa13499a75b:	33 c8                	xor    %eax,%ecx
    7fa13499a75d:	33 d9                	xor    %ecx,%ebx
    7fa13499a75f:	33 9d c8 f8 ff ff    	xor    -0x738(%rbp),%ebx
    7fa13499a765:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a768:	49 0f b6 87 78 01 00 	movzbq 0x178(%r15),%rax
    7fa13499a76f:	00 
    7fa13499a770:	8b c0                	mov    %eax,%eax
    7fa13499a772:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a777:	8b c8                	mov    %eax,%ecx
    7fa13499a779:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499a77c:	d1 e1                	shl    %ecx
    7fa13499a77e:	8b d0                	mov    %eax,%edx
    7fa13499a780:	c1 ea 07             	shr    $0x7,%edx
    7fa13499a783:	83 e2 01             	and    $0x1,%edx
    7fa13499a786:	8b da                	mov    %edx,%ebx
    7fa13499a788:	d1 e3                	shl    %ebx
    7fa13499a78a:	0b da                	or     %edx,%ebx
    7fa13499a78c:	44 8b d2             	mov    %edx,%r10d
    7fa13499a78f:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499a793:	41 0b da             	or     %r10d,%ebx
    7fa13499a796:	c1 e2 04             	shl    $0x4,%edx
    7fa13499a799:	0b da                	or     %edx,%ebx
    7fa13499a79b:	33 cb                	xor    %ebx,%ecx
    7fa13499a79d:	49 0f b6 97 7d 01 00 	movzbq 0x17d(%r15),%rdx
    7fa13499a7a4:	00 
    7fa13499a7a5:	8b d2                	mov    %edx,%edx
    7fa13499a7a7:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499a7ac:	8b da                	mov    %edx,%ebx
    7fa13499a7ae:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499a7b1:	d1 e3                	shl    %ebx
    7fa13499a7b3:	44 8b d2             	mov    %edx,%r10d
    7fa13499a7b6:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499a7ba:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499a7be:	45 8b da             	mov    %r10d,%r11d
    7fa13499a7c1:	41 d1 e3             	shl    %r11d
    7fa13499a7c4:	45 0b da             	or     %r10d,%r11d
    7fa13499a7c7:	44 89 95 98 f8 ff ff 	mov    %r10d,-0x768(%rbp)
    7fa13499a7ce:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499a7d2:	45 0b da             	or     %r10d,%r11d
    7fa13499a7d5:	44 8b 95 98 f8 ff ff 	mov    -0x768(%rbp),%r10d
    7fa13499a7dc:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499a7e0:	45 0b da             	or     %r10d,%r11d
    7fa13499a7e3:	41 33 db             	xor    %r11d,%ebx
    7fa13499a7e6:	44 8b d3             	mov    %ebx,%r10d
    7fa13499a7e9:	44 33 d2             	xor    %edx,%r10d
    7fa13499a7ec:	44 33 d1             	xor    %ecx,%r10d
    7fa13499a7ef:	4d 0f b6 9f 72 01 00 	movzbq 0x172(%r15),%r11
    7fa13499a7f6:	00 
    7fa13499a7f7:	45 8b db             	mov    %r11d,%r11d
    7fa13499a7fa:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499a7ff:	45 33 d3             	xor    %r11d,%r10d
    7fa13499a802:	89 bd 90 f8 ff ff    	mov    %edi,-0x770(%rbp)
    7fa13499a808:	49 0f b6 bf 77 01 00 	movzbq 0x177(%r15),%rdi
    7fa13499a80f:	00 
    7fa13499a810:	8b ff                	mov    %edi,%edi
    7fa13499a812:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499a817:	44 33 d7             	xor    %edi,%r10d
    7fa13499a81a:	33 d8                	xor    %eax,%ebx
    7fa13499a81c:	44 89 9d 88 f8 ff ff 	mov    %r11d,-0x778(%rbp)
    7fa13499a823:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499a827:	41 d1 e3             	shl    %r11d
    7fa13499a82a:	89 b5 80 f8 ff ff    	mov    %esi,-0x780(%rbp)
    7fa13499a830:	8b b5 88 f8 ff ff    	mov    -0x778(%rbp),%esi
    7fa13499a836:	c1 ee 07             	shr    $0x7,%esi
    7fa13499a839:	83 e6 01             	and    $0x1,%esi
    7fa13499a83c:	89 b5 78 f8 ff ff    	mov    %esi,-0x788(%rbp)
    7fa13499a842:	d1 e6                	shl    %esi
    7fa13499a844:	44 89 85 70 f8 ff ff 	mov    %r8d,-0x790(%rbp)
    7fa13499a84b:	44 8b 85 78 f8 ff ff 	mov    -0x788(%rbp),%r8d
    7fa13499a852:	41 0b f0             	or     %r8d,%esi
    7fa13499a855:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499a859:	41 0b f0             	or     %r8d,%esi
    7fa13499a85c:	44 8b 85 78 f8 ff ff 	mov    -0x788(%rbp),%r8d
    7fa13499a863:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499a867:	41 0b f0             	or     %r8d,%esi
    7fa13499a86a:	44 33 de             	xor    %esi,%r11d
    7fa13499a86d:	41 8b f3             	mov    %r11d,%esi
    7fa13499a870:	44 8b 85 88 f8 ff ff 	mov    -0x778(%rbp),%r8d
    7fa13499a877:	41 33 f0             	xor    %r8d,%esi
    7fa13499a87a:	33 de                	xor    %esi,%ebx
    7fa13499a87c:	33 df                	xor    %edi,%ebx
    7fa13499a87e:	8b f0                	mov    %eax,%esi
    7fa13499a880:	33 f2                	xor    %edx,%esi
    7fa13499a882:	44 33 de             	xor    %esi,%r11d
    7fa13499a885:	8b f7                	mov    %edi,%esi
    7fa13499a887:	83 e6 7f             	and    $0x7f,%esi
    7fa13499a88a:	d1 e6                	shl    %esi
    7fa13499a88c:	44 8b c7             	mov    %edi,%r8d
    7fa13499a88f:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499a893:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499a897:	44 89 85 68 f8 ff ff 	mov    %r8d,-0x798(%rbp)
    7fa13499a89e:	41 d1 e0             	shl    %r8d
    7fa13499a8a1:	44 89 8d 60 f8 ff ff 	mov    %r9d,-0x7a0(%rbp)
    7fa13499a8a8:	44 8b 8d 68 f8 ff ff 	mov    -0x798(%rbp),%r9d
    7fa13499a8af:	45 0b c1             	or     %r9d,%r8d
    7fa13499a8b2:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa13499a8b6:	45 0b c1             	or     %r9d,%r8d
    7fa13499a8b9:	44 8b 8d 68 f8 ff ff 	mov    -0x798(%rbp),%r9d
    7fa13499a8c0:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa13499a8c4:	45 0b c1             	or     %r9d,%r8d
    7fa13499a8c7:	41 33 f0             	xor    %r8d,%esi
    7fa13499a8ca:	33 fe                	xor    %esi,%edi
    7fa13499a8cc:	44 33 df             	xor    %edi,%r11d
    7fa13499a8cf:	33 c8                	xor    %eax,%ecx
    7fa13499a8d1:	33 d1                	xor    %ecx,%edx
    7fa13499a8d3:	33 95 88 f8 ff ff    	xor    -0x778(%rbp),%edx
    7fa13499a8d9:	33 f2                	xor    %edx,%esi
    7fa13499a8db:	49 0f b6 87 7c 01 00 	movzbq 0x17c(%r15),%rax
    7fa13499a8e2:	00 
    7fa13499a8e3:	8b c0                	mov    %eax,%eax
    7fa13499a8e5:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499a8ea:	8b c8                	mov    %eax,%ecx
    7fa13499a8ec:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499a8ef:	d1 e1                	shl    %ecx
    7fa13499a8f1:	8b d0                	mov    %eax,%edx
    7fa13499a8f3:	c1 ea 07             	shr    $0x7,%edx
    7fa13499a8f6:	83 e2 01             	and    $0x1,%edx
    7fa13499a8f9:	8b fa                	mov    %edx,%edi
    7fa13499a8fb:	d1 e7                	shl    %edi
    7fa13499a8fd:	0b fa                	or     %edx,%edi
    7fa13499a8ff:	44 8b c2             	mov    %edx,%r8d
    7fa13499a902:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499a906:	41 0b f8             	or     %r8d,%edi
    7fa13499a909:	c1 e2 04             	shl    $0x4,%edx
    7fa13499a90c:	0b fa                	or     %edx,%edi
    7fa13499a90e:	33 cf                	xor    %edi,%ecx
    7fa13499a910:	49 0f b6 97 71 01 00 	movzbq 0x171(%r15),%rdx
    7fa13499a917:	00 
    7fa13499a918:	8b d2                	mov    %edx,%edx
    7fa13499a91a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499a91f:	8b fa                	mov    %edx,%edi
    7fa13499a921:	83 e7 7f             	and    $0x7f,%edi
    7fa13499a924:	d1 e7                	shl    %edi
    7fa13499a926:	44 8b c2             	mov    %edx,%r8d
    7fa13499a929:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499a92d:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499a931:	45 8b c8             	mov    %r8d,%r9d
    7fa13499a934:	41 d1 e1             	shl    %r9d
    7fa13499a937:	45 0b c8             	or     %r8d,%r9d
    7fa13499a93a:	44 89 85 58 f8 ff ff 	mov    %r8d,-0x7a8(%rbp)
    7fa13499a941:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499a945:	45 0b c8             	or     %r8d,%r9d
    7fa13499a948:	44 8b 85 58 f8 ff ff 	mov    -0x7a8(%rbp),%r8d
    7fa13499a94f:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499a953:	45 0b c8             	or     %r8d,%r9d
    7fa13499a956:	41 33 f9             	xor    %r9d,%edi
    7fa13499a959:	44 8b c7             	mov    %edi,%r8d
    7fa13499a95c:	44 33 c2             	xor    %edx,%r8d
    7fa13499a95f:	44 33 c1             	xor    %ecx,%r8d
    7fa13499a962:	4d 0f b6 8f 76 01 00 	movzbq 0x176(%r15),%r9
    7fa13499a969:	00 
    7fa13499a96a:	45 8b c9             	mov    %r9d,%r9d
    7fa13499a96d:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa13499a972:	45 33 c1             	xor    %r9d,%r8d
    7fa13499a975:	44 89 95 50 f8 ff ff 	mov    %r10d,-0x7b0(%rbp)
    7fa13499a97c:	4d 0f b6 97 7b 01 00 	movzbq 0x17b(%r15),%r10
    7fa13499a983:	00 
    7fa13499a984:	45 8b d2             	mov    %r10d,%r10d
    7fa13499a987:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499a98c:	45 33 c2             	xor    %r10d,%r8d
    7fa13499a98f:	33 f8                	xor    %eax,%edi
    7fa13499a991:	44 89 8d 48 f8 ff ff 	mov    %r9d,-0x7b8(%rbp)
    7fa13499a998:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499a99c:	41 d1 e1             	shl    %r9d
    7fa13499a99f:	89 9d 40 f8 ff ff    	mov    %ebx,-0x7c0(%rbp)
    7fa13499a9a5:	8b 9d 48 f8 ff ff    	mov    -0x7b8(%rbp),%ebx
    7fa13499a9ab:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499a9ae:	83 e3 01             	and    $0x1,%ebx
    7fa13499a9b1:	89 9d 38 f8 ff ff    	mov    %ebx,-0x7c8(%rbp)
    7fa13499a9b7:	d1 e3                	shl    %ebx
    7fa13499a9b9:	44 89 9d 30 f8 ff ff 	mov    %r11d,-0x7d0(%rbp)
    7fa13499a9c0:	44 8b 9d 38 f8 ff ff 	mov    -0x7c8(%rbp),%r11d
    7fa13499a9c7:	41 0b db             	or     %r11d,%ebx
    7fa13499a9ca:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa13499a9ce:	41 0b db             	or     %r11d,%ebx
    7fa13499a9d1:	44 8b 9d 38 f8 ff ff 	mov    -0x7c8(%rbp),%r11d
    7fa13499a9d8:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa13499a9dc:	41 0b db             	or     %r11d,%ebx
    7fa13499a9df:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a9e2:	41 8b d9             	mov    %r9d,%ebx
    7fa13499a9e5:	44 8b 9d 48 f8 ff ff 	mov    -0x7b8(%rbp),%r11d
    7fa13499a9ec:	41 33 db             	xor    %r11d,%ebx
    7fa13499a9ef:	33 fb                	xor    %ebx,%edi
    7fa13499a9f1:	41 33 fa             	xor    %r10d,%edi
    7fa13499a9f4:	8b d8                	mov    %eax,%ebx
    7fa13499a9f6:	33 da                	xor    %edx,%ebx
    7fa13499a9f8:	44 33 cb             	xor    %ebx,%r9d
    7fa13499a9fb:	41 8b da             	mov    %r10d,%ebx
    7fa13499a9fe:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499aa01:	d1 e3                	shl    %ebx
    7fa13499aa03:	45 8b da             	mov    %r10d,%r11d
    7fa13499aa06:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499aa0a:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499aa0e:	44 89 9d 28 f8 ff ff 	mov    %r11d,-0x7d8(%rbp)
    7fa13499aa15:	41 d1 e3             	shl    %r11d
    7fa13499aa18:	89 b5 20 f8 ff ff    	mov    %esi,-0x7e0(%rbp)
    7fa13499aa1e:	8b b5 28 f8 ff ff    	mov    -0x7d8(%rbp),%esi
    7fa13499aa24:	44 0b de             	or     %esi,%r11d
    7fa13499aa27:	c1 e6 03             	shl    $0x3,%esi
    7fa13499aa2a:	44 0b de             	or     %esi,%r11d
    7fa13499aa2d:	8b b5 28 f8 ff ff    	mov    -0x7d8(%rbp),%esi
    7fa13499aa33:	c1 e6 04             	shl    $0x4,%esi
    7fa13499aa36:	44 0b de             	or     %esi,%r11d
    7fa13499aa39:	41 33 db             	xor    %r11d,%ebx
    7fa13499aa3c:	44 33 d3             	xor    %ebx,%r10d
    7fa13499aa3f:	45 33 ca             	xor    %r10d,%r9d
    7fa13499aa42:	33 c8                	xor    %eax,%ecx
    7fa13499aa44:	33 d1                	xor    %ecx,%edx
    7fa13499aa46:	33 95 48 f8 ff ff    	xor    -0x7b8(%rbp),%edx
    7fa13499aa4c:	33 da                	xor    %edx,%ebx
    7fa13499aa4e:	8b 85 c0 f8 ff ff    	mov    -0x740(%rbp),%eax
    7fa13499aa54:	c1 e0 08             	shl    $0x8,%eax
    7fa13499aa57:	0b 85 d0 f8 ff ff    	or     -0x730(%rbp),%eax
    7fa13499aa5d:	8b 8d b0 f8 ff ff    	mov    -0x750(%rbp),%ecx
    7fa13499aa63:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499aa66:	0b c1                	or     %ecx,%eax
    7fa13499aa68:	8b 8d a0 f8 ff ff    	mov    -0x760(%rbp),%ecx
    7fa13499aa6e:	c1 e1 18             	shl    $0x18,%ecx
    7fa13499aa71:	0b c1                	or     %ecx,%eax
    7fa13499aa73:	8b 8d 90 f8 ff ff    	mov    -0x770(%rbp),%ecx
    7fa13499aa79:	8b c9                	mov    %ecx,%ecx
    7fa13499aa7b:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa13499aa7f:	8b c0                	mov    %eax,%eax
    7fa13499aa81:	48 0b c8             	or     %rax,%rcx
    7fa13499aa84:	8b 85 80 f8 ff ff    	mov    -0x780(%rbp),%eax
    7fa13499aa8a:	8b c0                	mov    %eax,%eax
    7fa13499aa8c:	48 c1 e0 28          	shl    $0x28,%rax
    7fa13499aa90:	48 0b c8             	or     %rax,%rcx
    7fa13499aa93:	8b 85 70 f8 ff ff    	mov    -0x790(%rbp),%eax
    7fa13499aa99:	8b c0                	mov    %eax,%eax
    7fa13499aa9b:	48 c1 e0 30          	shl    $0x30,%rax
    7fa13499aa9f:	48 0b c8             	or     %rax,%rcx
    7fa13499aaa2:	8b 85 60 f8 ff ff    	mov    -0x7a0(%rbp),%eax
    7fa13499aaa8:	8b c0                	mov    %eax,%eax
    7fa13499aaaa:	48 c1 e0 38          	shl    $0x38,%rax
    7fa13499aaae:	48 0b c8             	or     %rax,%rcx
    7fa13499aab1:	49 89 8f d0 02 00 00 	mov    %rcx,0x2d0(%r15)
    7fa13499aab8:	8b 85 40 f8 ff ff    	mov    -0x7c0(%rbp),%eax
    7fa13499aabe:	c1 e0 08             	shl    $0x8,%eax
    7fa13499aac1:	0b 85 50 f8 ff ff    	or     -0x7b0(%rbp),%eax
    7fa13499aac7:	8b 8d 30 f8 ff ff    	mov    -0x7d0(%rbp),%ecx
    7fa13499aacd:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499aad0:	0b c1                	or     %ecx,%eax
    7fa13499aad2:	8b 8d 20 f8 ff ff    	mov    -0x7e0(%rbp),%ecx
    7fa13499aad8:	c1 e1 18             	shl    $0x18,%ecx
    7fa13499aadb:	0b c1                	or     %ecx,%eax
    7fa13499aadd:	45 8b c0             	mov    %r8d,%r8d
    7fa13499aae0:	49 c1 e0 20          	shl    $0x20,%r8
    7fa13499aae4:	8b c0                	mov    %eax,%eax
    7fa13499aae6:	4c 0b c0             	or     %rax,%r8
    7fa13499aae9:	8b ff                	mov    %edi,%edi
    7fa13499aaeb:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa13499aaef:	4c 0b c7             	or     %rdi,%r8
    7fa13499aaf2:	45 8b c9             	mov    %r9d,%r9d
    7fa13499aaf5:	49 c1 e1 30          	shl    $0x30,%r9
    7fa13499aaf9:	4d 0b c1             	or     %r9,%r8
    7fa13499aafc:	8b db                	mov    %ebx,%ebx
    7fa13499aafe:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa13499ab02:	4c 0b c3             	or     %rbx,%r8
    7fa13499ab05:	4d 89 87 d8 02 00 00 	mov    %r8,0x2d8(%r15)
    7fa13499ab0c:	8b 85 f0 f8 ff ff    	mov    -0x710(%rbp),%eax
    7fa13499ab12:	25 ff 00 00 00       	and    $0xff,%eax
    7fa13499ab17:	8b c0                	mov    %eax,%eax
    7fa13499ab19:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499ab1e:	8b 8d f0 f8 ff ff    	mov    -0x710(%rbp),%ecx
    7fa13499ab24:	c1 e9 18             	shr    $0x18,%ecx
    7fa13499ab27:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa13499ab2d:	8b c9                	mov    %ecx,%ecx
    7fa13499ab2f:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa13499ab34:	8b 95 f0 f8 ff ff    	mov    -0x710(%rbp),%edx
    7fa13499ab3a:	c1 ea 10             	shr    $0x10,%edx
    7fa13499ab3d:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa13499ab43:	8b d2                	mov    %edx,%edx
    7fa13499ab45:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499ab4a:	8b 9d f0 f8 ff ff    	mov    -0x710(%rbp),%ebx
    7fa13499ab50:	c1 eb 08             	shr    $0x8,%ebx
    7fa13499ab53:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa13499ab59:	8b db                	mov    %ebx,%ebx
    7fa13499ab5b:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499ab60:	c1 e2 08             	shl    $0x8,%edx
    7fa13499ab63:	0b da                	or     %edx,%ebx
    7fa13499ab65:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499ab68:	0b d9                	or     %ecx,%ebx
    7fa13499ab6a:	c1 e0 18             	shl    $0x18,%eax
    7fa13499ab6d:	0b d8                	or     %eax,%ebx
    7fa13499ab6f:	81 f3 80 00 00 00    	xor    $0x80,%ebx
    7fa13499ab75:	8b 85 00 f9 ff ff    	mov    -0x700(%rbp),%eax
    7fa13499ab7b:	33 d8                	xor    %eax,%ebx
    7fa13499ab7d:	8b 85 10 f9 ff ff    	mov    -0x6f0(%rbp),%eax
    7fa13499ab83:	33 c3                	xor    %ebx,%eax
    7fa13499ab85:	8b 8d e0 f8 ff ff    	mov    -0x720(%rbp),%ecx
    7fa13499ab8b:	33 c8                	xor    %eax,%ecx
    7fa13499ab8d:	8b 95 f0 f8 ff ff    	mov    -0x710(%rbp),%edx
    7fa13499ab93:	33 d1                	xor    %ecx,%edx
    7fa13499ab95:	8b f0                	mov    %eax,%esi
    7fa13499ab97:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499ab9b:	8b fb                	mov    %ebx,%edi
    7fa13499ab9d:	48 0b f7             	or     %rdi,%rsi
    7fa13499aba0:	49 89 b7 30 02 00 00 	mov    %rsi,0x230(%r15)
    7fa13499aba7:	8b f2                	mov    %edx,%esi
    7fa13499aba9:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499abad:	8b f9                	mov    %ecx,%edi
    7fa13499abaf:	48 0b f7             	or     %rdi,%rsi
    7fa13499abb2:	49 89 b7 38 02 00 00 	mov    %rsi,0x238(%r15)
    7fa13499abb9:	49 8b b7 d0 02 00 00 	mov    0x2d0(%r15),%rsi
    7fa13499abc0:	49 8b bf 30 02 00 00 	mov    0x230(%r15),%rdi
    7fa13499abc7:	48 33 f7             	xor    %rdi,%rsi
    7fa13499abca:	49 89 b7 80 03 00 00 	mov    %rsi,0x380(%r15)
    7fa13499abd1:	49 8b b7 d8 02 00 00 	mov    0x2d8(%r15),%rsi
    7fa13499abd8:	49 8b bf 38 02 00 00 	mov    0x238(%r15),%rdi
    7fa13499abdf:	48 33 f7             	xor    %rdi,%rsi
    7fa13499abe2:	49 89 b7 88 03 00 00 	mov    %rsi,0x388(%r15)
    7fa13499abe9:	49 0f b6 b7 80 01 00 	movzbq 0x180(%r15),%rsi
    7fa13499abf0:	00 
    7fa13499abf1:	8b f6                	mov    %esi,%esi
    7fa13499abf3:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa13499abf8:	8b fe                	mov    %esi,%edi
    7fa13499abfa:	83 e7 7f             	and    $0x7f,%edi
    7fa13499abfd:	d1 e7                	shl    %edi
    7fa13499abff:	44 8b c6             	mov    %esi,%r8d
    7fa13499ac02:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499ac06:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499ac0a:	45 8b c8             	mov    %r8d,%r9d
    7fa13499ac0d:	41 d1 e1             	shl    %r9d
    7fa13499ac10:	45 0b c8             	or     %r8d,%r9d
    7fa13499ac13:	45 8b d0             	mov    %r8d,%r10d
    7fa13499ac16:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499ac1a:	45 0b ca             	or     %r10d,%r9d
    7fa13499ac1d:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499ac21:	45 0b c8             	or     %r8d,%r9d
    7fa13499ac24:	41 33 f9             	xor    %r9d,%edi
    7fa13499ac27:	4d 0f b6 87 85 01 00 	movzbq 0x185(%r15),%r8
    7fa13499ac2e:	00 
    7fa13499ac2f:	45 8b c0             	mov    %r8d,%r8d
    7fa13499ac32:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499ac37:	45 8b c8             	mov    %r8d,%r9d
    7fa13499ac3a:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499ac3e:	41 d1 e1             	shl    %r9d
    7fa13499ac41:	45 8b d0             	mov    %r8d,%r10d
    7fa13499ac44:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499ac48:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499ac4c:	45 8b da             	mov    %r10d,%r11d
    7fa13499ac4f:	41 d1 e3             	shl    %r11d
    7fa13499ac52:	45 0b da             	or     %r10d,%r11d
    7fa13499ac55:	44 89 95 18 f8 ff ff 	mov    %r10d,-0x7e8(%rbp)
    7fa13499ac5c:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499ac60:	45 0b da             	or     %r10d,%r11d
    7fa13499ac63:	44 8b 95 18 f8 ff ff 	mov    -0x7e8(%rbp),%r10d
    7fa13499ac6a:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499ac6e:	45 0b da             	or     %r10d,%r11d
    7fa13499ac71:	45 33 cb             	xor    %r11d,%r9d
    7fa13499ac74:	45 8b d1             	mov    %r9d,%r10d
    7fa13499ac77:	45 33 d0             	xor    %r8d,%r10d
    7fa13499ac7a:	44 33 d7             	xor    %edi,%r10d
    7fa13499ac7d:	4d 0f b6 9f 8a 01 00 	movzbq 0x18a(%r15),%r11
    7fa13499ac84:	00 
    7fa13499ac85:	45 8b db             	mov    %r11d,%r11d
    7fa13499ac88:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499ac8d:	45 33 d3             	xor    %r11d,%r10d
    7fa13499ac90:	89 85 10 f8 ff ff    	mov    %eax,-0x7f0(%rbp)
    7fa13499ac96:	49 0f b6 87 8f 01 00 	movzbq 0x18f(%r15),%rax
    7fa13499ac9d:	00 
    7fa13499ac9e:	8b c0                	mov    %eax,%eax
    7fa13499aca0:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499aca5:	44 33 d0             	xor    %eax,%r10d
    7fa13499aca8:	44 33 ce             	xor    %esi,%r9d
    7fa13499acab:	44 89 9d 08 f8 ff ff 	mov    %r11d,-0x7f8(%rbp)
    7fa13499acb2:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499acb6:	41 d1 e3             	shl    %r11d
    7fa13499acb9:	89 9d 00 f8 ff ff    	mov    %ebx,-0x800(%rbp)
    7fa13499acbf:	8b 9d 08 f8 ff ff    	mov    -0x7f8(%rbp),%ebx
    7fa13499acc5:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499acc8:	83 e3 01             	and    $0x1,%ebx
    7fa13499accb:	89 9d f8 f7 ff ff    	mov    %ebx,-0x808(%rbp)
    7fa13499acd1:	d1 e3                	shl    %ebx
    7fa13499acd3:	89 95 f0 f7 ff ff    	mov    %edx,-0x810(%rbp)
    7fa13499acd9:	8b 95 f8 f7 ff ff    	mov    -0x808(%rbp),%edx
    7fa13499acdf:	0b da                	or     %edx,%ebx
    7fa13499ace1:	c1 e2 03             	shl    $0x3,%edx
    7fa13499ace4:	0b da                	or     %edx,%ebx
    7fa13499ace6:	8b 95 f8 f7 ff ff    	mov    -0x808(%rbp),%edx
    7fa13499acec:	c1 e2 04             	shl    $0x4,%edx
    7fa13499acef:	0b da                	or     %edx,%ebx
    7fa13499acf1:	44 33 db             	xor    %ebx,%r11d
    7fa13499acf4:	41 8b d3             	mov    %r11d,%edx
    7fa13499acf7:	8b 9d 08 f8 ff ff    	mov    -0x7f8(%rbp),%ebx
    7fa13499acfd:	33 d3                	xor    %ebx,%edx
    7fa13499acff:	44 33 ca             	xor    %edx,%r9d
    7fa13499ad02:	44 33 c8             	xor    %eax,%r9d
    7fa13499ad05:	8b d6                	mov    %esi,%edx
    7fa13499ad07:	41 33 d0             	xor    %r8d,%edx
    7fa13499ad0a:	44 33 da             	xor    %edx,%r11d
    7fa13499ad0d:	8b d0                	mov    %eax,%edx
    7fa13499ad0f:	83 e2 7f             	and    $0x7f,%edx
    7fa13499ad12:	d1 e2                	shl    %edx
    7fa13499ad14:	8b d8                	mov    %eax,%ebx
    7fa13499ad16:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499ad19:	83 e3 01             	and    $0x1,%ebx
    7fa13499ad1c:	89 9d e8 f7 ff ff    	mov    %ebx,-0x818(%rbp)
    7fa13499ad22:	d1 e3                	shl    %ebx
    7fa13499ad24:	89 8d e0 f7 ff ff    	mov    %ecx,-0x820(%rbp)
    7fa13499ad2a:	8b 8d e8 f7 ff ff    	mov    -0x818(%rbp),%ecx
    7fa13499ad30:	0b d9                	or     %ecx,%ebx
    7fa13499ad32:	c1 e1 03             	shl    $0x3,%ecx
    7fa13499ad35:	0b d9                	or     %ecx,%ebx
    7fa13499ad37:	8b 8d e8 f7 ff ff    	mov    -0x818(%rbp),%ecx
    7fa13499ad3d:	c1 e1 04             	shl    $0x4,%ecx
    7fa13499ad40:	0b d9                	or     %ecx,%ebx
    7fa13499ad42:	33 d3                	xor    %ebx,%edx
    7fa13499ad44:	33 c2                	xor    %edx,%eax
    7fa13499ad46:	44 33 d8             	xor    %eax,%r11d
    7fa13499ad49:	33 fe                	xor    %esi,%edi
    7fa13499ad4b:	44 33 c7             	xor    %edi,%r8d
    7fa13499ad4e:	44 33 85 08 f8 ff ff 	xor    -0x7f8(%rbp),%r8d
    7fa13499ad55:	41 33 d0             	xor    %r8d,%edx
    7fa13499ad58:	49 0f b6 87 84 01 00 	movzbq 0x184(%r15),%rax
    7fa13499ad5f:	00 
    7fa13499ad60:	8b c0                	mov    %eax,%eax
    7fa13499ad62:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499ad67:	8b c8                	mov    %eax,%ecx
    7fa13499ad69:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499ad6c:	d1 e1                	shl    %ecx
    7fa13499ad6e:	8b d8                	mov    %eax,%ebx
    7fa13499ad70:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499ad73:	83 e3 01             	and    $0x1,%ebx
    7fa13499ad76:	8b f3                	mov    %ebx,%esi
    7fa13499ad78:	d1 e6                	shl    %esi
    7fa13499ad7a:	0b f3                	or     %ebx,%esi
    7fa13499ad7c:	8b fb                	mov    %ebx,%edi
    7fa13499ad7e:	c1 e7 03             	shl    $0x3,%edi
    7fa13499ad81:	0b f7                	or     %edi,%esi
    7fa13499ad83:	c1 e3 04             	shl    $0x4,%ebx
    7fa13499ad86:	0b f3                	or     %ebx,%esi
    7fa13499ad88:	33 ce                	xor    %esi,%ecx
    7fa13499ad8a:	49 0f b6 9f 89 01 00 	movzbq 0x189(%r15),%rbx
    7fa13499ad91:	00 
    7fa13499ad92:	8b db                	mov    %ebx,%ebx
    7fa13499ad94:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499ad99:	8b f3                	mov    %ebx,%esi
    7fa13499ad9b:	83 e6 7f             	and    $0x7f,%esi
    7fa13499ad9e:	d1 e6                	shl    %esi
    7fa13499ada0:	8b fb                	mov    %ebx,%edi
    7fa13499ada2:	c1 ef 07             	shr    $0x7,%edi
    7fa13499ada5:	83 e7 01             	and    $0x1,%edi
    7fa13499ada8:	44 8b c7             	mov    %edi,%r8d
    7fa13499adab:	41 d1 e0             	shl    %r8d
    7fa13499adae:	44 0b c7             	or     %edi,%r8d
    7fa13499adb1:	89 bd d8 f7 ff ff    	mov    %edi,-0x828(%rbp)
    7fa13499adb7:	c1 e7 03             	shl    $0x3,%edi
    7fa13499adba:	44 0b c7             	or     %edi,%r8d
    7fa13499adbd:	8b bd d8 f7 ff ff    	mov    -0x828(%rbp),%edi
    7fa13499adc3:	c1 e7 04             	shl    $0x4,%edi
    7fa13499adc6:	44 0b c7             	or     %edi,%r8d
    7fa13499adc9:	41 33 f0             	xor    %r8d,%esi
    7fa13499adcc:	8b fe                	mov    %esi,%edi
    7fa13499adce:	33 fb                	xor    %ebx,%edi
    7fa13499add0:	33 f9                	xor    %ecx,%edi
    7fa13499add2:	4d 0f b6 87 8e 01 00 	movzbq 0x18e(%r15),%r8
    7fa13499add9:	00 
    7fa13499adda:	45 8b c0             	mov    %r8d,%r8d
    7fa13499addd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499ade2:	41 33 f8             	xor    %r8d,%edi
    7fa13499ade5:	44 89 95 d0 f7 ff ff 	mov    %r10d,-0x830(%rbp)
    7fa13499adec:	4d 0f b6 97 83 01 00 	movzbq 0x183(%r15),%r10
    7fa13499adf3:	00 
    7fa13499adf4:	45 8b d2             	mov    %r10d,%r10d
    7fa13499adf7:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499adfc:	41 33 fa             	xor    %r10d,%edi
    7fa13499adff:	33 f0                	xor    %eax,%esi
    7fa13499ae01:	44 89 85 c8 f7 ff ff 	mov    %r8d,-0x838(%rbp)
    7fa13499ae08:	41 83 e0 7f          	and    $0x7f,%r8d
    7fa13499ae0c:	41 d1 e0             	shl    %r8d
    7fa13499ae0f:	44 89 8d c0 f7 ff ff 	mov    %r9d,-0x840(%rbp)
    7fa13499ae16:	44 8b 8d c8 f7 ff ff 	mov    -0x838(%rbp),%r9d
    7fa13499ae1d:	41 c1 e9 07          	shr    $0x7,%r9d
    7fa13499ae21:	41 83 e1 01          	and    $0x1,%r9d
    7fa13499ae25:	44 89 8d b8 f7 ff ff 	mov    %r9d,-0x848(%rbp)
    7fa13499ae2c:	41 d1 e1             	shl    %r9d
    7fa13499ae2f:	44 89 9d b0 f7 ff ff 	mov    %r11d,-0x850(%rbp)
    7fa13499ae36:	44 8b 9d b8 f7 ff ff 	mov    -0x848(%rbp),%r11d
    7fa13499ae3d:	45 0b cb             	or     %r11d,%r9d
    7fa13499ae40:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa13499ae44:	45 0b cb             	or     %r11d,%r9d
    7fa13499ae47:	44 8b 9d b8 f7 ff ff 	mov    -0x848(%rbp),%r11d
    7fa13499ae4e:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa13499ae52:	45 0b cb             	or     %r11d,%r9d
    7fa13499ae55:	45 33 c1             	xor    %r9d,%r8d
    7fa13499ae58:	45 8b c8             	mov    %r8d,%r9d
    7fa13499ae5b:	44 8b 9d c8 f7 ff ff 	mov    -0x838(%rbp),%r11d
    7fa13499ae62:	45 33 cb             	xor    %r11d,%r9d
    7fa13499ae65:	41 33 f1             	xor    %r9d,%esi
    7fa13499ae68:	41 33 f2             	xor    %r10d,%esi
    7fa13499ae6b:	44 8b c8             	mov    %eax,%r9d
    7fa13499ae6e:	44 33 cb             	xor    %ebx,%r9d
    7fa13499ae71:	45 33 c1             	xor    %r9d,%r8d
    7fa13499ae74:	45 8b ca             	mov    %r10d,%r9d
    7fa13499ae77:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499ae7b:	41 d1 e1             	shl    %r9d
    7fa13499ae7e:	45 8b da             	mov    %r10d,%r11d
    7fa13499ae81:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499ae85:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499ae89:	44 89 9d a8 f7 ff ff 	mov    %r11d,-0x858(%rbp)
    7fa13499ae90:	41 d1 e3             	shl    %r11d
    7fa13499ae93:	89 95 a0 f7 ff ff    	mov    %edx,-0x860(%rbp)
    7fa13499ae99:	8b 95 a8 f7 ff ff    	mov    -0x858(%rbp),%edx
    7fa13499ae9f:	44 0b da             	or     %edx,%r11d
    7fa13499aea2:	c1 e2 03             	shl    $0x3,%edx
    7fa13499aea5:	44 0b da             	or     %edx,%r11d
    7fa13499aea8:	8b 95 a8 f7 ff ff    	mov    -0x858(%rbp),%edx
    7fa13499aeae:	c1 e2 04             	shl    $0x4,%edx
    7fa13499aeb1:	44 0b da             	or     %edx,%r11d
    7fa13499aeb4:	45 33 cb             	xor    %r11d,%r9d
    7fa13499aeb7:	45 33 d1             	xor    %r9d,%r10d
    7fa13499aeba:	45 33 c2             	xor    %r10d,%r8d
    7fa13499aebd:	33 c8                	xor    %eax,%ecx
    7fa13499aebf:	33 d9                	xor    %ecx,%ebx
    7fa13499aec1:	33 9d c8 f7 ff ff    	xor    -0x838(%rbp),%ebx
    7fa13499aec7:	44 33 cb             	xor    %ebx,%r9d
    7fa13499aeca:	49 0f b6 87 88 01 00 	movzbq 0x188(%r15),%rax
    7fa13499aed1:	00 
    7fa13499aed2:	8b c0                	mov    %eax,%eax
    7fa13499aed4:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499aed9:	8b c8                	mov    %eax,%ecx
    7fa13499aedb:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499aede:	d1 e1                	shl    %ecx
    7fa13499aee0:	8b d0                	mov    %eax,%edx
    7fa13499aee2:	c1 ea 07             	shr    $0x7,%edx
    7fa13499aee5:	83 e2 01             	and    $0x1,%edx
    7fa13499aee8:	8b da                	mov    %edx,%ebx
    7fa13499aeea:	d1 e3                	shl    %ebx
    7fa13499aeec:	0b da                	or     %edx,%ebx
    7fa13499aeee:	44 8b d2             	mov    %edx,%r10d
    7fa13499aef1:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499aef5:	41 0b da             	or     %r10d,%ebx
    7fa13499aef8:	c1 e2 04             	shl    $0x4,%edx
    7fa13499aefb:	0b da                	or     %edx,%ebx
    7fa13499aefd:	33 cb                	xor    %ebx,%ecx
    7fa13499aeff:	49 0f b6 97 8d 01 00 	movzbq 0x18d(%r15),%rdx
    7fa13499af06:	00 
    7fa13499af07:	8b d2                	mov    %edx,%edx
    7fa13499af09:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499af0e:	8b da                	mov    %edx,%ebx
    7fa13499af10:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499af13:	d1 e3                	shl    %ebx
    7fa13499af15:	44 8b d2             	mov    %edx,%r10d
    7fa13499af18:	41 c1 ea 07          	shr    $0x7,%r10d
    7fa13499af1c:	41 83 e2 01          	and    $0x1,%r10d
    7fa13499af20:	45 8b da             	mov    %r10d,%r11d
    7fa13499af23:	41 d1 e3             	shl    %r11d
    7fa13499af26:	45 0b da             	or     %r10d,%r11d
    7fa13499af29:	44 89 95 98 f7 ff ff 	mov    %r10d,-0x868(%rbp)
    7fa13499af30:	41 c1 e2 03          	shl    $0x3,%r10d
    7fa13499af34:	45 0b da             	or     %r10d,%r11d
    7fa13499af37:	44 8b 95 98 f7 ff ff 	mov    -0x868(%rbp),%r10d
    7fa13499af3e:	41 c1 e2 04          	shl    $0x4,%r10d
    7fa13499af42:	45 0b da             	or     %r10d,%r11d
    7fa13499af45:	41 33 db             	xor    %r11d,%ebx
    7fa13499af48:	44 8b d3             	mov    %ebx,%r10d
    7fa13499af4b:	44 33 d2             	xor    %edx,%r10d
    7fa13499af4e:	44 33 d1             	xor    %ecx,%r10d
    7fa13499af51:	4d 0f b6 9f 82 01 00 	movzbq 0x182(%r15),%r11
    7fa13499af58:	00 
    7fa13499af59:	45 8b db             	mov    %r11d,%r11d
    7fa13499af5c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499af61:	45 33 d3             	xor    %r11d,%r10d
    7fa13499af64:	89 bd 90 f7 ff ff    	mov    %edi,-0x870(%rbp)
    7fa13499af6a:	49 0f b6 bf 87 01 00 	movzbq 0x187(%r15),%rdi
    7fa13499af71:	00 
    7fa13499af72:	8b ff                	mov    %edi,%edi
    7fa13499af74:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499af79:	44 33 d7             	xor    %edi,%r10d
    7fa13499af7c:	33 d8                	xor    %eax,%ebx
    7fa13499af7e:	44 89 9d 88 f7 ff ff 	mov    %r11d,-0x878(%rbp)
    7fa13499af85:	41 83 e3 7f          	and    $0x7f,%r11d
    7fa13499af89:	41 d1 e3             	shl    %r11d
    7fa13499af8c:	89 b5 80 f7 ff ff    	mov    %esi,-0x880(%rbp)
    7fa13499af92:	8b b5 88 f7 ff ff    	mov    -0x878(%rbp),%esi
    7fa13499af98:	c1 ee 07             	shr    $0x7,%esi
    7fa13499af9b:	83 e6 01             	and    $0x1,%esi
    7fa13499af9e:	89 b5 78 f7 ff ff    	mov    %esi,-0x888(%rbp)
    7fa13499afa4:	d1 e6                	shl    %esi
    7fa13499afa6:	44 89 85 70 f7 ff ff 	mov    %r8d,-0x890(%rbp)
    7fa13499afad:	44 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%r8d
    7fa13499afb4:	41 0b f0             	or     %r8d,%esi
    7fa13499afb7:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499afbb:	41 0b f0             	or     %r8d,%esi
    7fa13499afbe:	44 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%r8d
    7fa13499afc5:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499afc9:	41 0b f0             	or     %r8d,%esi
    7fa13499afcc:	44 33 de             	xor    %esi,%r11d
    7fa13499afcf:	41 8b f3             	mov    %r11d,%esi
    7fa13499afd2:	44 8b 85 88 f7 ff ff 	mov    -0x878(%rbp),%r8d
    7fa13499afd9:	41 33 f0             	xor    %r8d,%esi
    7fa13499afdc:	33 de                	xor    %esi,%ebx
    7fa13499afde:	33 df                	xor    %edi,%ebx
    7fa13499afe0:	8b f0                	mov    %eax,%esi
    7fa13499afe2:	33 f2                	xor    %edx,%esi
    7fa13499afe4:	44 33 de             	xor    %esi,%r11d
    7fa13499afe7:	8b f7                	mov    %edi,%esi
    7fa13499afe9:	83 e6 7f             	and    $0x7f,%esi
    7fa13499afec:	d1 e6                	shl    %esi
    7fa13499afee:	44 8b c7             	mov    %edi,%r8d
    7fa13499aff1:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499aff5:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499aff9:	44 89 85 68 f7 ff ff 	mov    %r8d,-0x898(%rbp)
    7fa13499b000:	41 d1 e0             	shl    %r8d
    7fa13499b003:	44 89 8d 60 f7 ff ff 	mov    %r9d,-0x8a0(%rbp)
    7fa13499b00a:	44 8b 8d 68 f7 ff ff 	mov    -0x898(%rbp),%r9d
    7fa13499b011:	45 0b c1             	or     %r9d,%r8d
    7fa13499b014:	41 c1 e1 03          	shl    $0x3,%r9d
    7fa13499b018:	45 0b c1             	or     %r9d,%r8d
    7fa13499b01b:	44 8b 8d 68 f7 ff ff 	mov    -0x898(%rbp),%r9d
    7fa13499b022:	41 c1 e1 04          	shl    $0x4,%r9d
    7fa13499b026:	45 0b c1             	or     %r9d,%r8d
    7fa13499b029:	41 33 f0             	xor    %r8d,%esi
    7fa13499b02c:	33 fe                	xor    %esi,%edi
    7fa13499b02e:	44 33 df             	xor    %edi,%r11d
    7fa13499b031:	33 c8                	xor    %eax,%ecx
    7fa13499b033:	33 d1                	xor    %ecx,%edx
    7fa13499b035:	33 95 88 f7 ff ff    	xor    -0x878(%rbp),%edx
    7fa13499b03b:	33 f2                	xor    %edx,%esi
    7fa13499b03d:	49 0f b6 87 8c 01 00 	movzbq 0x18c(%r15),%rax
    7fa13499b044:	00 
    7fa13499b045:	8b c0                	mov    %eax,%eax
    7fa13499b047:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499b04c:	8b c8                	mov    %eax,%ecx
    7fa13499b04e:	83 e1 7f             	and    $0x7f,%ecx
    7fa13499b051:	d1 e1                	shl    %ecx
    7fa13499b053:	8b d0                	mov    %eax,%edx
    7fa13499b055:	c1 ea 07             	shr    $0x7,%edx
    7fa13499b058:	83 e2 01             	and    $0x1,%edx
    7fa13499b05b:	8b fa                	mov    %edx,%edi
    7fa13499b05d:	d1 e7                	shl    %edi
    7fa13499b05f:	0b fa                	or     %edx,%edi
    7fa13499b061:	44 8b c2             	mov    %edx,%r8d
    7fa13499b064:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499b068:	41 0b f8             	or     %r8d,%edi
    7fa13499b06b:	c1 e2 04             	shl    $0x4,%edx
    7fa13499b06e:	0b fa                	or     %edx,%edi
    7fa13499b070:	33 cf                	xor    %edi,%ecx
    7fa13499b072:	49 0f b6 97 81 01 00 	movzbq 0x181(%r15),%rdx
    7fa13499b079:	00 
    7fa13499b07a:	8b d2                	mov    %edx,%edx
    7fa13499b07c:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499b081:	8b fa                	mov    %edx,%edi
    7fa13499b083:	83 e7 7f             	and    $0x7f,%edi
    7fa13499b086:	d1 e7                	shl    %edi
    7fa13499b088:	44 8b c2             	mov    %edx,%r8d
    7fa13499b08b:	41 c1 e8 07          	shr    $0x7,%r8d
    7fa13499b08f:	41 83 e0 01          	and    $0x1,%r8d
    7fa13499b093:	45 8b c8             	mov    %r8d,%r9d
    7fa13499b096:	41 d1 e1             	shl    %r9d
    7fa13499b099:	45 0b c8             	or     %r8d,%r9d
    7fa13499b09c:	44 89 85 58 f7 ff ff 	mov    %r8d,-0x8a8(%rbp)
    7fa13499b0a3:	41 c1 e0 03          	shl    $0x3,%r8d
    7fa13499b0a7:	45 0b c8             	or     %r8d,%r9d
    7fa13499b0aa:	44 8b 85 58 f7 ff ff 	mov    -0x8a8(%rbp),%r8d
    7fa13499b0b1:	41 c1 e0 04          	shl    $0x4,%r8d
    7fa13499b0b5:	45 0b c8             	or     %r8d,%r9d
    7fa13499b0b8:	41 33 f9             	xor    %r9d,%edi
    7fa13499b0bb:	44 8b c7             	mov    %edi,%r8d
    7fa13499b0be:	44 33 c2             	xor    %edx,%r8d
    7fa13499b0c1:	44 33 c1             	xor    %ecx,%r8d
    7fa13499b0c4:	4d 0f b6 8f 86 01 00 	movzbq 0x186(%r15),%r9
    7fa13499b0cb:	00 
    7fa13499b0cc:	45 8b c9             	mov    %r9d,%r9d
    7fa13499b0cf:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa13499b0d4:	45 33 c1             	xor    %r9d,%r8d
    7fa13499b0d7:	44 89 95 50 f7 ff ff 	mov    %r10d,-0x8b0(%rbp)
    7fa13499b0de:	4d 0f b6 97 8b 01 00 	movzbq 0x18b(%r15),%r10
    7fa13499b0e5:	00 
    7fa13499b0e6:	45 8b d2             	mov    %r10d,%r10d
    7fa13499b0e9:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499b0ee:	45 33 c2             	xor    %r10d,%r8d
    7fa13499b0f1:	33 f8                	xor    %eax,%edi
    7fa13499b0f3:	44 89 8d 48 f7 ff ff 	mov    %r9d,-0x8b8(%rbp)
    7fa13499b0fa:	41 83 e1 7f          	and    $0x7f,%r9d
    7fa13499b0fe:	41 d1 e1             	shl    %r9d
    7fa13499b101:	89 9d 40 f7 ff ff    	mov    %ebx,-0x8c0(%rbp)
    7fa13499b107:	8b 9d 48 f7 ff ff    	mov    -0x8b8(%rbp),%ebx
    7fa13499b10d:	c1 eb 07             	shr    $0x7,%ebx
    7fa13499b110:	83 e3 01             	and    $0x1,%ebx
    7fa13499b113:	89 9d 38 f7 ff ff    	mov    %ebx,-0x8c8(%rbp)
    7fa13499b119:	d1 e3                	shl    %ebx
    7fa13499b11b:	44 89 9d 30 f7 ff ff 	mov    %r11d,-0x8d0(%rbp)
    7fa13499b122:	44 8b 9d 38 f7 ff ff 	mov    -0x8c8(%rbp),%r11d
    7fa13499b129:	41 0b db             	or     %r11d,%ebx
    7fa13499b12c:	41 c1 e3 03          	shl    $0x3,%r11d
    7fa13499b130:	41 0b db             	or     %r11d,%ebx
    7fa13499b133:	44 8b 9d 38 f7 ff ff 	mov    -0x8c8(%rbp),%r11d
    7fa13499b13a:	41 c1 e3 04          	shl    $0x4,%r11d
    7fa13499b13e:	41 0b db             	or     %r11d,%ebx
    7fa13499b141:	44 33 cb             	xor    %ebx,%r9d
    7fa13499b144:	41 8b d9             	mov    %r9d,%ebx
    7fa13499b147:	44 8b 9d 48 f7 ff ff 	mov    -0x8b8(%rbp),%r11d
    7fa13499b14e:	41 33 db             	xor    %r11d,%ebx
    7fa13499b151:	33 fb                	xor    %ebx,%edi
    7fa13499b153:	41 33 fa             	xor    %r10d,%edi
    7fa13499b156:	8b d8                	mov    %eax,%ebx
    7fa13499b158:	33 da                	xor    %edx,%ebx
    7fa13499b15a:	44 33 cb             	xor    %ebx,%r9d
    7fa13499b15d:	41 8b da             	mov    %r10d,%ebx
    7fa13499b160:	83 e3 7f             	and    $0x7f,%ebx
    7fa13499b163:	d1 e3                	shl    %ebx
    7fa13499b165:	45 8b da             	mov    %r10d,%r11d
    7fa13499b168:	41 c1 eb 07          	shr    $0x7,%r11d
    7fa13499b16c:	41 83 e3 01          	and    $0x1,%r11d
    7fa13499b170:	44 89 9d 28 f7 ff ff 	mov    %r11d,-0x8d8(%rbp)
    7fa13499b177:	41 d1 e3             	shl    %r11d
    7fa13499b17a:	89 b5 20 f7 ff ff    	mov    %esi,-0x8e0(%rbp)
    7fa13499b180:	8b b5 28 f7 ff ff    	mov    -0x8d8(%rbp),%esi
    7fa13499b186:	44 0b de             	or     %esi,%r11d
    7fa13499b189:	c1 e6 03             	shl    $0x3,%esi
    7fa13499b18c:	44 0b de             	or     %esi,%r11d
    7fa13499b18f:	8b b5 28 f7 ff ff    	mov    -0x8d8(%rbp),%esi
    7fa13499b195:	c1 e6 04             	shl    $0x4,%esi
    7fa13499b198:	44 0b de             	or     %esi,%r11d
    7fa13499b19b:	41 33 db             	xor    %r11d,%ebx
    7fa13499b19e:	44 33 d3             	xor    %ebx,%r10d
    7fa13499b1a1:	45 33 ca             	xor    %r10d,%r9d
    7fa13499b1a4:	33 c8                	xor    %eax,%ecx
    7fa13499b1a6:	33 d1                	xor    %ecx,%edx
    7fa13499b1a8:	33 95 48 f7 ff ff    	xor    -0x8b8(%rbp),%edx
    7fa13499b1ae:	33 da                	xor    %edx,%ebx
    7fa13499b1b0:	8b 85 c0 f7 ff ff    	mov    -0x840(%rbp),%eax
    7fa13499b1b6:	c1 e0 08             	shl    $0x8,%eax
    7fa13499b1b9:	0b 85 d0 f7 ff ff    	or     -0x830(%rbp),%eax
    7fa13499b1bf:	8b 8d b0 f7 ff ff    	mov    -0x850(%rbp),%ecx
    7fa13499b1c5:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499b1c8:	0b c1                	or     %ecx,%eax
    7fa13499b1ca:	8b 8d a0 f7 ff ff    	mov    -0x860(%rbp),%ecx
    7fa13499b1d0:	c1 e1 18             	shl    $0x18,%ecx
    7fa13499b1d3:	0b c1                	or     %ecx,%eax
    7fa13499b1d5:	8b 8d 90 f7 ff ff    	mov    -0x870(%rbp),%ecx
    7fa13499b1db:	8b c9                	mov    %ecx,%ecx
    7fa13499b1dd:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa13499b1e1:	8b c0                	mov    %eax,%eax
    7fa13499b1e3:	48 0b c8             	or     %rax,%rcx
    7fa13499b1e6:	8b 85 80 f7 ff ff    	mov    -0x880(%rbp),%eax
    7fa13499b1ec:	8b c0                	mov    %eax,%eax
    7fa13499b1ee:	48 c1 e0 28          	shl    $0x28,%rax
    7fa13499b1f2:	48 0b c8             	or     %rax,%rcx
    7fa13499b1f5:	8b 85 70 f7 ff ff    	mov    -0x890(%rbp),%eax
    7fa13499b1fb:	8b c0                	mov    %eax,%eax
    7fa13499b1fd:	48 c1 e0 30          	shl    $0x30,%rax
    7fa13499b201:	48 0b c8             	or     %rax,%rcx
    7fa13499b204:	8b 85 60 f7 ff ff    	mov    -0x8a0(%rbp),%eax
    7fa13499b20a:	8b c0                	mov    %eax,%eax
    7fa13499b20c:	48 c1 e0 38          	shl    $0x38,%rax
    7fa13499b210:	48 0b c8             	or     %rax,%rcx
    7fa13499b213:	49 89 8f e0 02 00 00 	mov    %rcx,0x2e0(%r15)
    7fa13499b21a:	8b 85 40 f7 ff ff    	mov    -0x8c0(%rbp),%eax
    7fa13499b220:	c1 e0 08             	shl    $0x8,%eax
    7fa13499b223:	0b 85 50 f7 ff ff    	or     -0x8b0(%rbp),%eax
    7fa13499b229:	8b 8d 30 f7 ff ff    	mov    -0x8d0(%rbp),%ecx
    7fa13499b22f:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499b232:	0b c1                	or     %ecx,%eax
    7fa13499b234:	8b 8d 20 f7 ff ff    	mov    -0x8e0(%rbp),%ecx
    7fa13499b23a:	c1 e1 18             	shl    $0x18,%ecx
    7fa13499b23d:	0b c1                	or     %ecx,%eax
    7fa13499b23f:	45 8b c0             	mov    %r8d,%r8d
    7fa13499b242:	49 c1 e0 20          	shl    $0x20,%r8
    7fa13499b246:	8b c0                	mov    %eax,%eax
    7fa13499b248:	4c 0b c0             	or     %rax,%r8
    7fa13499b24b:	8b ff                	mov    %edi,%edi
    7fa13499b24d:	48 c1 e7 28          	shl    $0x28,%rdi
    7fa13499b251:	4c 0b c7             	or     %rdi,%r8
    7fa13499b254:	45 8b c9             	mov    %r9d,%r9d
    7fa13499b257:	49 c1 e1 30          	shl    $0x30,%r9
    7fa13499b25b:	4d 0b c1             	or     %r9,%r8
    7fa13499b25e:	8b db                	mov    %ebx,%ebx
    7fa13499b260:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa13499b264:	4c 0b c3             	or     %rbx,%r8
    7fa13499b267:	4d 89 87 e8 02 00 00 	mov    %r8,0x2e8(%r15)
    7fa13499b26e:	8b 85 f0 f7 ff ff    	mov    -0x810(%rbp),%eax
    7fa13499b274:	25 ff 00 00 00       	and    $0xff,%eax
    7fa13499b279:	8b c0                	mov    %eax,%eax
    7fa13499b27b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499b280:	8b 8d f0 f7 ff ff    	mov    -0x810(%rbp),%ecx
    7fa13499b286:	c1 e9 18             	shr    $0x18,%ecx
    7fa13499b289:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa13499b28f:	8b c9                	mov    %ecx,%ecx
    7fa13499b291:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa13499b296:	8b 95 f0 f7 ff ff    	mov    -0x810(%rbp),%edx
    7fa13499b29c:	c1 ea 10             	shr    $0x10,%edx
    7fa13499b29f:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa13499b2a5:	8b d2                	mov    %edx,%edx
    7fa13499b2a7:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499b2ac:	8b 9d f0 f7 ff ff    	mov    -0x810(%rbp),%ebx
    7fa13499b2b2:	c1 eb 08             	shr    $0x8,%ebx
    7fa13499b2b5:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa13499b2bb:	8b db                	mov    %ebx,%ebx
    7fa13499b2bd:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499b2c2:	c1 e2 08             	shl    $0x8,%edx
    7fa13499b2c5:	0b da                	or     %edx,%ebx
    7fa13499b2c7:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499b2ca:	0b d9                	or     %ecx,%ebx
    7fa13499b2cc:	c1 e0 18             	shl    $0x18,%eax
    7fa13499b2cf:	0b d8                	or     %eax,%ebx
    7fa13499b2d1:	83 f3 1b             	xor    $0x1b,%ebx
    7fa13499b2d4:	8b 85 00 f8 ff ff    	mov    -0x800(%rbp),%eax
    7fa13499b2da:	33 d8                	xor    %eax,%ebx
    7fa13499b2dc:	8b 85 10 f8 ff ff    	mov    -0x7f0(%rbp),%eax
    7fa13499b2e2:	33 c3                	xor    %ebx,%eax
    7fa13499b2e4:	8b 8d e0 f7 ff ff    	mov    -0x820(%rbp),%ecx
    7fa13499b2ea:	33 c8                	xor    %eax,%ecx
    7fa13499b2ec:	8b 95 f0 f7 ff ff    	mov    -0x810(%rbp),%edx
    7fa13499b2f2:	33 d1                	xor    %ecx,%edx
    7fa13499b2f4:	8b f0                	mov    %eax,%esi
    7fa13499b2f6:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499b2fa:	8b fb                	mov    %ebx,%edi
    7fa13499b2fc:	48 0b f7             	or     %rdi,%rsi
    7fa13499b2ff:	49 89 b7 40 02 00 00 	mov    %rsi,0x240(%r15)
    7fa13499b306:	8b f2                	mov    %edx,%esi
    7fa13499b308:	48 c1 e6 20          	shl    $0x20,%rsi
    7fa13499b30c:	8b f9                	mov    %ecx,%edi
    7fa13499b30e:	48 0b f7             	or     %rdi,%rsi
    7fa13499b311:	49 89 b7 48 02 00 00 	mov    %rsi,0x248(%r15)
    7fa13499b318:	49 8b b7 e0 02 00 00 	mov    0x2e0(%r15),%rsi
    7fa13499b31f:	49 8b bf 40 02 00 00 	mov    0x240(%r15),%rdi
    7fa13499b326:	48 33 f7             	xor    %rdi,%rsi
    7fa13499b329:	49 89 b7 90 03 00 00 	mov    %rsi,0x390(%r15)
    7fa13499b330:	49 8b b7 e8 02 00 00 	mov    0x2e8(%r15),%rsi
    7fa13499b337:	49 8b bf 48 02 00 00 	mov    0x248(%r15),%rdi
    7fa13499b33e:	48 33 f7             	xor    %rdi,%rsi
    7fa13499b341:	49 89 b7 98 03 00 00 	mov    %rsi,0x398(%r15)
    7fa13499b348:	49 0f b6 b7 9f 01 00 	movzbq 0x19f(%r15),%rsi
    7fa13499b34f:	00 
    7fa13499b350:	8b f6                	mov    %esi,%esi
    7fa13499b352:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa13499b357:	49 0f b6 bf 9e 01 00 	movzbq 0x19e(%r15),%rdi
    7fa13499b35e:	00 
    7fa13499b35f:	8b ff                	mov    %edi,%edi
    7fa13499b361:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499b366:	4d 0f b6 87 9d 01 00 	movzbq 0x19d(%r15),%r8
    7fa13499b36d:	00 
    7fa13499b36e:	45 8b c0             	mov    %r8d,%r8d
    7fa13499b371:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499b376:	4d 0f b6 8f 9c 01 00 	movzbq 0x19c(%r15),%r9
    7fa13499b37d:	00 
    7fa13499b37e:	45 8b c9             	mov    %r9d,%r9d
    7fa13499b381:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa13499b386:	4d 0f b6 97 9a 01 00 	movzbq 0x19a(%r15),%r10
    7fa13499b38d:	00 
    7fa13499b38e:	45 8b d2             	mov    %r10d,%r10d
    7fa13499b391:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499b396:	4d 0f b6 9f 99 01 00 	movzbq 0x199(%r15),%r11
    7fa13499b39d:	00 
    7fa13499b39e:	45 8b db             	mov    %r11d,%r11d
    7fa13499b3a1:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499b3a6:	89 85 18 f7 ff ff    	mov    %eax,-0x8e8(%rbp)
    7fa13499b3ac:	49 0f b6 87 98 01 00 	movzbq 0x198(%r15),%rax
    7fa13499b3b3:	00 
    7fa13499b3b4:	8b c0                	mov    %eax,%eax
    7fa13499b3b6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499b3bb:	89 9d 10 f7 ff ff    	mov    %ebx,-0x8f0(%rbp)
    7fa13499b3c1:	49 0f b6 9f 9b 01 00 	movzbq 0x19b(%r15),%rbx
    7fa13499b3c8:	00 
    7fa13499b3c9:	8b db                	mov    %ebx,%ebx
    7fa13499b3cb:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499b3d0:	89 95 08 f7 ff ff    	mov    %edx,-0x8f8(%rbp)
    7fa13499b3d6:	49 0f b6 97 95 01 00 	movzbq 0x195(%r15),%rdx
    7fa13499b3dd:	00 
    7fa13499b3de:	8b d2                	mov    %edx,%edx
    7fa13499b3e0:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499b3e5:	89 8d 00 f7 ff ff    	mov    %ecx,-0x900(%rbp)
    7fa13499b3eb:	49 0f b6 8f 94 01 00 	movzbq 0x194(%r15),%rcx
    7fa13499b3f2:	00 
    7fa13499b3f3:	8b c9                	mov    %ecx,%ecx
    7fa13499b3f5:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa13499b3fa:	89 b5 f8 f6 ff ff    	mov    %esi,-0x908(%rbp)
    7fa13499b400:	49 0f b6 b7 97 01 00 	movzbq 0x197(%r15),%rsi
    7fa13499b407:	00 
    7fa13499b408:	8b f6                	mov    %esi,%esi
    7fa13499b40a:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fa13499b40f:	89 bd f0 f6 ff ff    	mov    %edi,-0x910(%rbp)
    7fa13499b415:	49 0f b6 bf 96 01 00 	movzbq 0x196(%r15),%rdi
    7fa13499b41c:	00 
    7fa13499b41d:	8b ff                	mov    %edi,%edi
    7fa13499b41f:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fa13499b424:	44 89 85 e8 f6 ff ff 	mov    %r8d,-0x918(%rbp)
    7fa13499b42b:	4d 0f b6 87 90 01 00 	movzbq 0x190(%r15),%r8
    7fa13499b432:	00 
    7fa13499b433:	45 8b c0             	mov    %r8d,%r8d
    7fa13499b436:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fa13499b43b:	44 89 8d e0 f6 ff ff 	mov    %r9d,-0x920(%rbp)
    7fa13499b442:	4d 0f b6 8f 93 01 00 	movzbq 0x193(%r15),%r9
    7fa13499b449:	00 
    7fa13499b44a:	45 8b c9             	mov    %r9d,%r9d
    7fa13499b44d:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fa13499b452:	44 89 95 d8 f6 ff ff 	mov    %r10d,-0x928(%rbp)
    7fa13499b459:	4d 0f b6 97 92 01 00 	movzbq 0x192(%r15),%r10
    7fa13499b460:	00 
    7fa13499b461:	45 8b d2             	mov    %r10d,%r10d
    7fa13499b464:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fa13499b469:	44 89 9d d0 f6 ff ff 	mov    %r11d,-0x930(%rbp)
    7fa13499b470:	4d 0f b6 9f 91 01 00 	movzbq 0x191(%r15),%r11
    7fa13499b477:	00 
    7fa13499b478:	45 8b db             	mov    %r11d,%r11d
    7fa13499b47b:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fa13499b480:	c1 e2 08             	shl    $0x8,%edx
    7fa13499b483:	44 0b c2             	or     %edx,%r8d
    7fa13499b486:	8b 95 d8 f6 ff ff    	mov    -0x928(%rbp),%edx
    7fa13499b48c:	c1 e2 10             	shl    $0x10,%edx
    7fa13499b48f:	44 0b c2             	or     %edx,%r8d
    7fa13499b492:	8b 95 f8 f6 ff ff    	mov    -0x908(%rbp),%edx
    7fa13499b498:	c1 e2 18             	shl    $0x18,%edx
    7fa13499b49b:	44 0b c2             	or     %edx,%r8d
    7fa13499b49e:	8b c9                	mov    %ecx,%ecx
    7fa13499b4a0:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa13499b4a4:	41 8b d0             	mov    %r8d,%edx
    7fa13499b4a7:	48 0b ca             	or     %rdx,%rcx
    7fa13499b4aa:	8b 95 d0 f6 ff ff    	mov    -0x930(%rbp),%edx
    7fa13499b4b0:	8b d2                	mov    %edx,%edx
    7fa13499b4b2:	48 c1 e2 28          	shl    $0x28,%rdx
    7fa13499b4b6:	48 0b ca             	or     %rdx,%rcx
    7fa13499b4b9:	8b 95 f0 f6 ff ff    	mov    -0x910(%rbp),%edx
    7fa13499b4bf:	8b d2                	mov    %edx,%edx
    7fa13499b4c1:	48 c1 e2 30          	shl    $0x30,%rdx
    7fa13499b4c5:	48 0b ca             	or     %rdx,%rcx
    7fa13499b4c8:	45 8b c9             	mov    %r9d,%r9d
    7fa13499b4cb:	49 c1 e1 38          	shl    $0x38,%r9
    7fa13499b4cf:	49 0b c9             	or     %r9,%rcx
    7fa13499b4d2:	49 89 8f f0 02 00 00 	mov    %rcx,0x2f0(%r15)
    7fa13499b4d9:	8b 8d e8 f6 ff ff    	mov    -0x918(%rbp),%ecx
    7fa13499b4df:	c1 e1 08             	shl    $0x8,%ecx
    7fa13499b4e2:	0b c1                	or     %ecx,%eax
    7fa13499b4e4:	41 c1 e2 10          	shl    $0x10,%r10d
    7fa13499b4e8:	41 0b c2             	or     %r10d,%eax
    7fa13499b4eb:	c1 e6 18             	shl    $0x18,%esi
    7fa13499b4ee:	0b c6                	or     %esi,%eax
    7fa13499b4f0:	8b 8d e0 f6 ff ff    	mov    -0x920(%rbp),%ecx
    7fa13499b4f6:	8b c9                	mov    %ecx,%ecx
    7fa13499b4f8:	48 c1 e1 20          	shl    $0x20,%rcx
    7fa13499b4fc:	8b c0                	mov    %eax,%eax
    7fa13499b4fe:	48 0b c8             	or     %rax,%rcx
    7fa13499b501:	45 8b db             	mov    %r11d,%r11d
    7fa13499b504:	49 c1 e3 28          	shl    $0x28,%r11
    7fa13499b508:	49 0b cb             	or     %r11,%rcx
    7fa13499b50b:	8b ff                	mov    %edi,%edi
    7fa13499b50d:	48 c1 e7 30          	shl    $0x30,%rdi
    7fa13499b511:	48 0b cf             	or     %rdi,%rcx
    7fa13499b514:	8b db                	mov    %ebx,%ebx
    7fa13499b516:	48 c1 e3 38          	shl    $0x38,%rbx
    7fa13499b51a:	48 0b cb             	or     %rbx,%rcx
    7fa13499b51d:	49 89 8f f8 02 00 00 	mov    %rcx,0x2f8(%r15)
    7fa13499b524:	8b 85 08 f7 ff ff    	mov    -0x8f8(%rbp),%eax
    7fa13499b52a:	25 ff 00 00 00       	and    $0xff,%eax
    7fa13499b52f:	8b c0                	mov    %eax,%eax
    7fa13499b531:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fa13499b536:	8b 8d 08 f7 ff ff    	mov    -0x8f8(%rbp),%ecx
    7fa13499b53c:	c1 e9 18             	shr    $0x18,%ecx
    7fa13499b53f:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fa13499b545:	8b c9                	mov    %ecx,%ecx
    7fa13499b547:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fa13499b54c:	8b 95 08 f7 ff ff    	mov    -0x8f8(%rbp),%edx
    7fa13499b552:	c1 ea 10             	shr    $0x10,%edx
    7fa13499b555:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fa13499b55b:	8b d2                	mov    %edx,%edx
    7fa13499b55d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fa13499b562:	8b 9d 08 f7 ff ff    	mov    -0x8f8(%rbp),%ebx
    7fa13499b568:	c1 eb 08             	shr    $0x8,%ebx
    7fa13499b56b:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fa13499b571:	8b db                	mov    %ebx,%ebx
    7fa13499b573:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fa13499b578:	c1 e2 08             	shl    $0x8,%edx
    7fa13499b57b:	0b da                	or     %edx,%ebx
    7fa13499b57d:	c1 e1 10             	shl    $0x10,%ecx
    7fa13499b580:	0b d9                	or     %ecx,%ebx
    7fa13499b582:	c1 e0 18             	shl    $0x18,%eax
    7fa13499b585:	0b d8                	or     %eax,%ebx
    7fa13499b587:	83 f3 36             	xor    $0x36,%ebx
    7fa13499b58a:	8b 85 10 f7 ff ff    	mov    -0x8f0(%rbp),%eax
    7fa13499b590:	33 d8                	xor    %eax,%ebx
    7fa13499b592:	8b 85 18 f7 ff ff    	mov    -0x8e8(%rbp),%eax
    7fa13499b598:	33 c3                	xor    %ebx,%eax
    7fa13499b59a:	8b 8d 00 f7 ff ff    	mov    -0x900(%rbp),%ecx
    7fa13499b5a0:	33 c8                	xor    %eax,%ecx
    7fa13499b5a2:	8b 95 08 f7 ff ff    	mov    -0x8f8(%rbp),%edx
    7fa13499b5a8:	33 d1                	xor    %ecx,%edx
    7fa13499b5aa:	8b c0                	mov    %eax,%eax
    7fa13499b5ac:	48 c1 e0 20          	shl    $0x20,%rax
    7fa13499b5b0:	8b db                	mov    %ebx,%ebx
    7fa13499b5b2:	48 0b c3             	or     %rbx,%rax
    7fa13499b5b5:	49 89 87 50 02 00 00 	mov    %rax,0x250(%r15)
    7fa13499b5bc:	8b d2                	mov    %edx,%edx
    7fa13499b5be:	48 c1 e2 20          	shl    $0x20,%rdx
    7fa13499b5c2:	8b c9                	mov    %ecx,%ecx
    7fa13499b5c4:	48 0b d1             	or     %rcx,%rdx
    7fa13499b5c7:	49 89 97 58 02 00 00 	mov    %rdx,0x258(%r15)
    7fa13499b5ce:	49 8b 87 f0 02 00 00 	mov    0x2f0(%r15),%rax
    7fa13499b5d5:	49 8b 8f 50 02 00 00 	mov    0x250(%r15),%rcx
    7fa13499b5dc:	48 33 c1             	xor    %rcx,%rax
    7fa13499b5df:	49 89 87 a0 03 00 00 	mov    %rax,0x3a0(%r15)
    7fa13499b5e6:	49 8b 87 f8 02 00 00 	mov    0x2f8(%r15),%rax
    7fa13499b5ed:	49 8b 8f 58 02 00 00 	mov    0x258(%r15),%rcx
    7fa13499b5f4:	48 33 c1             	xor    %rcx,%rax
    7fa13499b5f7:	49 89 87 a8 03 00 00 	mov    %rax,0x3a8(%r15)
    7fa13499b5fe:	49 8b 46 10          	mov    0x10(%r14),%rax
    7fa13499b602:	8b 00                	mov    (%rax),%eax
    7fa13499b604:	89 85 c8 f6 ff ff    	mov    %eax,-0x938(%rbp)
    7fa13499b60a:	49 8b 46 20          	mov    0x20(%r14),%rax
    7fa13499b60e:	8b 00                	mov    (%rax),%eax
    7fa13499b610:	85 c0                	test   %eax,%eax
    7fa13499b612:	0f 84 1e 00 00 00    	je     0x7fa13499b636
    7fa13499b618:	41 c7 87 b0 01 00 00 	movl   $0x0,0x1b0(%r15)
    7fa13499b61f:	00 00 00 00 
    7fa13499b623:	45 33 ed             	xor    %r13d,%r13d
    7fa13499b626:	41 c7 87 b8 01 00 00 	movl   $0x0,0x1b8(%r15)
    7fa13499b62d:	00 00 00 00 
    7fa13499b631:	e9 2a 00 00 00       	jmpq   0x7fa13499b660
    7fa13499b636:	41 8b 87 b8 01 00 00 	mov    0x1b8(%r15),%eax
    7fa13499b63d:	8b c8                	mov    %eax,%ecx
    7fa13499b63f:	83 e1 01             	and    $0x1,%ecx
    7fa13499b642:	41 89 8f b0 01 00 00 	mov    %ecx,0x1b0(%r15)
    7fa13499b649:	4c 8b e9             	mov    %rcx,%r13
    7fa13499b64c:	d1 e8                	shr    %eax
    7fa13499b64e:	8b 8d c8 f6 ff ff    	mov    -0x938(%rbp),%ecx
    7fa13499b654:	c1 e1 09             	shl    $0x9,%ecx
    7fa13499b657:	0b c1                	or     %ecx,%eax
    7fa13499b659:	41 89 87 b8 01 00 00 	mov    %eax,0x1b8(%r15)
    7fa13499b660:	49 8b c7             	mov    %r15,%rax
    7fa13499b663:	48 05 a0 01 00 00    	add    $0x1a0,%rax
    7fa13499b669:	49 8b cf             	mov    %r15,%rcx
    7fa13499b66c:	48 81 c1 a0 03 00 00 	add    $0x3a0,%rcx
    7fa13499b673:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b676:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b679:	49 8b c7             	mov    %r15,%rax
    7fa13499b67c:	48 05 90 01 00 00    	add    $0x190,%rax
    7fa13499b682:	49 8b cf             	mov    %r15,%rcx
    7fa13499b685:	48 81 c1 90 03 00 00 	add    $0x390,%rcx
    7fa13499b68c:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b68f:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b692:	49 8b c7             	mov    %r15,%rax
    7fa13499b695:	48 05 80 01 00 00    	add    $0x180,%rax
    7fa13499b69b:	49 8b cf             	mov    %r15,%rcx
    7fa13499b69e:	48 81 c1 80 03 00 00 	add    $0x380,%rcx
    7fa13499b6a5:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b6a8:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b6ab:	49 8b c7             	mov    %r15,%rax
    7fa13499b6ae:	48 05 70 01 00 00    	add    $0x170,%rax
    7fa13499b6b4:	49 8b cf             	mov    %r15,%rcx
    7fa13499b6b7:	48 81 c1 70 03 00 00 	add    $0x370,%rcx
    7fa13499b6be:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b6c1:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b6c4:	49 8b c7             	mov    %r15,%rax
    7fa13499b6c7:	48 05 60 01 00 00    	add    $0x160,%rax
    7fa13499b6cd:	49 8b cf             	mov    %r15,%rcx
    7fa13499b6d0:	48 81 c1 60 03 00 00 	add    $0x360,%rcx
    7fa13499b6d7:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b6da:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b6dd:	49 8b c7             	mov    %r15,%rax
    7fa13499b6e0:	48 05 50 01 00 00    	add    $0x150,%rax
    7fa13499b6e6:	49 8b cf             	mov    %r15,%rcx
    7fa13499b6e9:	48 81 c1 50 03 00 00 	add    $0x350,%rcx
    7fa13499b6f0:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b6f3:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b6f6:	49 8b c7             	mov    %r15,%rax
    7fa13499b6f9:	48 05 40 01 00 00    	add    $0x140,%rax
    7fa13499b6ff:	49 8b cf             	mov    %r15,%rcx
    7fa13499b702:	48 81 c1 40 03 00 00 	add    $0x340,%rcx
    7fa13499b709:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b70c:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b70f:	49 8b c7             	mov    %r15,%rax
    7fa13499b712:	48 05 30 01 00 00    	add    $0x130,%rax
    7fa13499b718:	49 8b cf             	mov    %r15,%rcx
    7fa13499b71b:	48 81 c1 30 03 00 00 	add    $0x330,%rcx
    7fa13499b722:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b725:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b728:	49 8b c7             	mov    %r15,%rax
    7fa13499b72b:	48 05 20 01 00 00    	add    $0x120,%rax
    7fa13499b731:	49 8b cf             	mov    %r15,%rcx
    7fa13499b734:	48 81 c1 20 03 00 00 	add    $0x320,%rcx
    7fa13499b73b:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b73e:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b741:	49 8b c7             	mov    %r15,%rax
    7fa13499b744:	48 05 10 01 00 00    	add    $0x110,%rax
    7fa13499b74a:	49 8b cf             	mov    %r15,%rcx
    7fa13499b74d:	48 81 c1 10 03 00 00 	add    $0x310,%rcx
    7fa13499b754:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b757:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b75a:	49 8b c7             	mov    %r15,%rax
    7fa13499b75d:	48 05 00 01 00 00    	add    $0x100,%rax
    7fa13499b763:	49 8b cf             	mov    %r15,%rcx
    7fa13499b766:	48 81 c1 00 03 00 00 	add    $0x300,%rcx
    7fa13499b76d:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b770:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b773:	49 8b 46 28          	mov    0x28(%r14),%rax
    7fa13499b777:	49 8b cf             	mov    %r15,%rcx
    7fa13499b77a:	48 81 c1 a0 01 00 00 	add    $0x1a0,%rcx
    7fa13499b781:	0f 10 01             	movups (%rcx),%xmm0
    7fa13499b784:	0f 11 00             	movups %xmm0,(%rax)
    7fa13499b787:	49 8b 46 30          	mov    0x30(%r14),%rax
    7fa13499b78b:	44 89 28             	mov    %r13d,(%rax)
    7fa13499b78e:	33 c0                	xor    %eax,%eax
    7fa13499b790:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fa13499b794:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fa13499b799:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fa13499b79e:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fa13499b7a3:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fa13499b7a8:	48 8b e5             	mov    %rbp,%rsp
    7fa13499b7ab:	5d                   	pop    %rbp
    7fa13499b7ac:	c3                   	retq   

end

