function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007f76ecc2b12d <.text>:
    7f76ecc2b12d:	55                   	push   %rbp
    7f76ecc2b12e:	48 8b ec             	mov    %rsp,%rbp
    7f76ecc2b131:	48 81 ec 60 09 00 00 	sub    $0x960,%rsp
    7f76ecc2b138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7f76ecc2b13c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7f76ecc2b141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7f76ecc2b146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7f76ecc2b14b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7f76ecc2b150:	4c 8b e7             	mov    %rdi,%r12
    7f76ecc2b153:	4d 8b 7c 24 08       	mov    0x8(%r12),%r15
    7f76ecc2b158:	4d 8b 34 24          	mov    (%r12),%r14
    7f76ecc2b15c:	45 8b af b0 01 00 00 	mov    0x1b0(%r15),%r13d
    7f76ecc2b163:	49 8b 46 18          	mov    0x18(%r14),%rax
    7f76ecc2b167:	8b 00                	mov    (%rax),%eax
    7f76ecc2b169:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7f76ecc2b170:	33 c8                	xor    %eax,%ecx
    7f76ecc2b172:	23 c8                	and    %eax,%ecx
    7f76ecc2b174:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7f76ecc2b17b:	85 c9                	test   %ecx,%ecx
    7f76ecc2b17d:	0f 84 0b 46 00 00    	je     0x7f76ecc2f78e
    7f76ecc2b183:	49 8b 46 08          	mov    0x8(%r14),%rax
    7f76ecc2b187:	49 8b 0e             	mov    (%r14),%rcx
    7f76ecc2b18a:	48 8b 10             	mov    (%rax),%rdx
    7f76ecc2b18d:	48 8b 19             	mov    (%rcx),%rbx
    7f76ecc2b190:	48 33 d3             	xor    %rbx,%rdx
    7f76ecc2b193:	49 89 97 00 03 00 00 	mov    %rdx,0x300(%r15)
    7f76ecc2b19a:	48 8b 40 08          	mov    0x8(%rax),%rax
    7f76ecc2b19e:	48 8b 51 08          	mov    0x8(%rcx),%rdx
    7f76ecc2b1a2:	48 33 c2             	xor    %rdx,%rax
    7f76ecc2b1a5:	49 89 87 08 03 00 00 	mov    %rax,0x308(%r15)
    7f76ecc2b1ac:	49 0f b6 87 00 01 00 	movzbq 0x100(%r15),%rax
    7f76ecc2b1b3:	00 
    7f76ecc2b1b4:	8b c0                	mov    %eax,%eax
    7f76ecc2b1b6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2b1bb:	8b d0                	mov    %eax,%edx
    7f76ecc2b1bd:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2b1c0:	d1 e2                	shl    %edx
    7f76ecc2b1c2:	8b d8                	mov    %eax,%ebx
    7f76ecc2b1c4:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2b1c7:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2b1ca:	8b f3                	mov    %ebx,%esi
    7f76ecc2b1cc:	d1 e6                	shl    %esi
    7f76ecc2b1ce:	0b f3                	or     %ebx,%esi
    7f76ecc2b1d0:	8b fb                	mov    %ebx,%edi
    7f76ecc2b1d2:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2b1d5:	0b f7                	or     %edi,%esi
    7f76ecc2b1d7:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2b1da:	0b f3                	or     %ebx,%esi
    7f76ecc2b1dc:	33 d6                	xor    %esi,%edx
    7f76ecc2b1de:	49 0f b6 9f 05 01 00 	movzbq 0x105(%r15),%rbx
    7f76ecc2b1e5:	00 
    7f76ecc2b1e6:	8b db                	mov    %ebx,%ebx
    7f76ecc2b1e8:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2b1ed:	8b f3                	mov    %ebx,%esi
    7f76ecc2b1ef:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2b1f2:	d1 e6                	shl    %esi
    7f76ecc2b1f4:	8b fb                	mov    %ebx,%edi
    7f76ecc2b1f6:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2b1f9:	83 e7 01             	and    $0x1,%edi
    7f76ecc2b1fc:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2b1ff:	41 d1 e0             	shl    %r8d
    7f76ecc2b202:	44 0b c7             	or     %edi,%r8d
    7f76ecc2b205:	44 8b cf             	mov    %edi,%r9d
    7f76ecc2b208:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2b20c:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2b20f:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2b212:	44 0b c7             	or     %edi,%r8d
    7f76ecc2b215:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2b218:	8b fe                	mov    %esi,%edi
    7f76ecc2b21a:	33 fb                	xor    %ebx,%edi
    7f76ecc2b21c:	33 fa                	xor    %edx,%edi
    7f76ecc2b21e:	4d 0f b6 87 0a 01 00 	movzbq 0x10a(%r15),%r8
    7f76ecc2b225:	00 
    7f76ecc2b226:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2b229:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2b22e:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2b231:	4d 0f b6 8f 0f 01 00 	movzbq 0x10f(%r15),%r9
    7f76ecc2b238:	00 
    7f76ecc2b239:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2b23c:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2b241:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2b244:	33 f0                	xor    %eax,%esi
    7f76ecc2b246:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2b249:	41 83 e2 7f          	and    $0x7f,%r10d
    7f76ecc2b24d:	41 d1 e2             	shl    %r10d
    7f76ecc2b250:	45 8b d8             	mov    %r8d,%r11d
    7f76ecc2b253:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2b257:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2b25b:	44 89 5d f8          	mov    %r11d,-0x8(%rbp)
    7f76ecc2b25f:	41 d1 e3             	shl    %r11d
    7f76ecc2b262:	48 89 4d f0          	mov    %rcx,-0x10(%rbp)
    7f76ecc2b266:	8b 4d f8             	mov    -0x8(%rbp),%ecx
    7f76ecc2b269:	44 0b d9             	or     %ecx,%r11d
    7f76ecc2b26c:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2b26f:	44 0b d9             	or     %ecx,%r11d
    7f76ecc2b272:	8b 4d f8             	mov    -0x8(%rbp),%ecx
    7f76ecc2b275:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2b278:	44 0b d9             	or     %ecx,%r11d
    7f76ecc2b27b:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2b27e:	41 8b ca             	mov    %r10d,%ecx
    7f76ecc2b281:	41 33 c8             	xor    %r8d,%ecx
    7f76ecc2b284:	33 f1                	xor    %ecx,%esi
    7f76ecc2b286:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2b289:	8b c8                	mov    %eax,%ecx
    7f76ecc2b28b:	33 cb                	xor    %ebx,%ecx
    7f76ecc2b28d:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2b290:	41 8b c9             	mov    %r9d,%ecx
    7f76ecc2b293:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2b296:	d1 e1                	shl    %ecx
    7f76ecc2b298:	45 8b d9             	mov    %r9d,%r11d
    7f76ecc2b29b:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2b29f:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2b2a3:	44 89 5d e8          	mov    %r11d,-0x18(%rbp)
    7f76ecc2b2a7:	41 d1 e3             	shl    %r11d
    7f76ecc2b2aa:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7f76ecc2b2ad:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f76ecc2b2b0:	44 0b da             	or     %edx,%r11d
    7f76ecc2b2b3:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2b2b6:	44 0b da             	or     %edx,%r11d
    7f76ecc2b2b9:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7f76ecc2b2bc:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2b2bf:	44 0b da             	or     %edx,%r11d
    7f76ecc2b2c2:	41 33 cb             	xor    %r11d,%ecx
    7f76ecc2b2c5:	44 33 c9             	xor    %ecx,%r9d
    7f76ecc2b2c8:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2b2cb:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7f76ecc2b2ce:	33 c2                	xor    %edx,%eax
    7f76ecc2b2d0:	33 d8                	xor    %eax,%ebx
    7f76ecc2b2d2:	44 33 c3             	xor    %ebx,%r8d
    7f76ecc2b2d5:	41 33 c8             	xor    %r8d,%ecx
    7f76ecc2b2d8:	49 0f b6 87 04 01 00 	movzbq 0x104(%r15),%rax
    7f76ecc2b2df:	00 
    7f76ecc2b2e0:	8b c0                	mov    %eax,%eax
    7f76ecc2b2e2:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2b2e7:	8b d0                	mov    %eax,%edx
    7f76ecc2b2e9:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2b2ec:	d1 e2                	shl    %edx
    7f76ecc2b2ee:	8b d8                	mov    %eax,%ebx
    7f76ecc2b2f0:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2b2f3:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2b2f6:	44 8b c3             	mov    %ebx,%r8d
    7f76ecc2b2f9:	41 d1 e0             	shl    %r8d
    7f76ecc2b2fc:	44 0b c3             	or     %ebx,%r8d
    7f76ecc2b2ff:	44 8b cb             	mov    %ebx,%r9d
    7f76ecc2b302:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2b306:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2b309:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2b30c:	44 0b c3             	or     %ebx,%r8d
    7f76ecc2b30f:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2b312:	49 0f b6 9f 09 01 00 	movzbq 0x109(%r15),%rbx
    7f76ecc2b319:	00 
    7f76ecc2b31a:	8b db                	mov    %ebx,%ebx
    7f76ecc2b31c:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2b321:	44 8b c3             	mov    %ebx,%r8d
    7f76ecc2b324:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2b328:	41 d1 e0             	shl    %r8d
    7f76ecc2b32b:	44 8b cb             	mov    %ebx,%r9d
    7f76ecc2b32e:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2b332:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2b336:	45 8b d9             	mov    %r9d,%r11d
    7f76ecc2b339:	41 d1 e3             	shl    %r11d
    7f76ecc2b33c:	45 0b d9             	or     %r9d,%r11d
    7f76ecc2b33f:	44 89 4d d8          	mov    %r9d,-0x28(%rbp)
    7f76ecc2b343:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2b347:	45 0b d9             	or     %r9d,%r11d
    7f76ecc2b34a:	44 8b 4d d8          	mov    -0x28(%rbp),%r9d
    7f76ecc2b34e:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2b352:	45 0b d9             	or     %r9d,%r11d
    7f76ecc2b355:	45 33 c3             	xor    %r11d,%r8d
    7f76ecc2b358:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2b35b:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2b35e:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2b361:	4d 0f b6 9f 0e 01 00 	movzbq 0x10e(%r15),%r11
    7f76ecc2b368:	00 
    7f76ecc2b369:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2b36c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2b371:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2b374:	89 7d d0             	mov    %edi,-0x30(%rbp)
    7f76ecc2b377:	49 0f b6 bf 03 01 00 	movzbq 0x103(%r15),%rdi
    7f76ecc2b37e:	00 
    7f76ecc2b37f:	8b ff                	mov    %edi,%edi
    7f76ecc2b381:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2b386:	44 33 cf             	xor    %edi,%r9d
    7f76ecc2b389:	44 33 c0             	xor    %eax,%r8d
    7f76ecc2b38c:	44 89 5d c8          	mov    %r11d,-0x38(%rbp)
    7f76ecc2b390:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2b394:	41 d1 e3             	shl    %r11d
    7f76ecc2b397:	89 75 c0             	mov    %esi,-0x40(%rbp)
    7f76ecc2b39a:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7f76ecc2b39d:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2b3a0:	83 e6 01             	and    $0x1,%esi
    7f76ecc2b3a3:	89 75 b8             	mov    %esi,-0x48(%rbp)
    7f76ecc2b3a6:	d1 e6                	shl    %esi
    7f76ecc2b3a8:	44 89 55 b0          	mov    %r10d,-0x50(%rbp)
    7f76ecc2b3ac:	44 8b 55 b8          	mov    -0x48(%rbp),%r10d
    7f76ecc2b3b0:	41 0b f2             	or     %r10d,%esi
    7f76ecc2b3b3:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2b3b7:	41 0b f2             	or     %r10d,%esi
    7f76ecc2b3ba:	44 8b 55 b8          	mov    -0x48(%rbp),%r10d
    7f76ecc2b3be:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2b3c2:	41 0b f2             	or     %r10d,%esi
    7f76ecc2b3c5:	44 33 de             	xor    %esi,%r11d
    7f76ecc2b3c8:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2b3cb:	44 8b 55 c8          	mov    -0x38(%rbp),%r10d
    7f76ecc2b3cf:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2b3d2:	44 33 c6             	xor    %esi,%r8d
    7f76ecc2b3d5:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2b3d8:	8b f0                	mov    %eax,%esi
    7f76ecc2b3da:	33 f3                	xor    %ebx,%esi
    7f76ecc2b3dc:	44 33 de             	xor    %esi,%r11d
    7f76ecc2b3df:	8b f7                	mov    %edi,%esi
    7f76ecc2b3e1:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2b3e4:	d1 e6                	shl    %esi
    7f76ecc2b3e6:	44 8b d7             	mov    %edi,%r10d
    7f76ecc2b3e9:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2b3ed:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2b3f1:	44 89 55 a8          	mov    %r10d,-0x58(%rbp)
    7f76ecc2b3f5:	41 d1 e2             	shl    %r10d
    7f76ecc2b3f8:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7f76ecc2b3fb:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7f76ecc2b3fe:	44 0b d1             	or     %ecx,%r10d
    7f76ecc2b401:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2b404:	44 0b d1             	or     %ecx,%r10d
    7f76ecc2b407:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7f76ecc2b40a:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2b40d:	44 0b d1             	or     %ecx,%r10d
    7f76ecc2b410:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2b413:	33 fe                	xor    %esi,%edi
    7f76ecc2b415:	44 33 df             	xor    %edi,%r11d
    7f76ecc2b418:	33 d0                	xor    %eax,%edx
    7f76ecc2b41a:	33 da                	xor    %edx,%ebx
    7f76ecc2b41c:	33 5d c8             	xor    -0x38(%rbp),%ebx
    7f76ecc2b41f:	33 f3                	xor    %ebx,%esi
    7f76ecc2b421:	49 0f b6 87 08 01 00 	movzbq 0x108(%r15),%rax
    7f76ecc2b428:	00 
    7f76ecc2b429:	8b c0                	mov    %eax,%eax
    7f76ecc2b42b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2b430:	8b c8                	mov    %eax,%ecx
    7f76ecc2b432:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2b435:	d1 e1                	shl    %ecx
    7f76ecc2b437:	8b d0                	mov    %eax,%edx
    7f76ecc2b439:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2b43c:	83 e2 01             	and    $0x1,%edx
    7f76ecc2b43f:	8b da                	mov    %edx,%ebx
    7f76ecc2b441:	d1 e3                	shl    %ebx
    7f76ecc2b443:	0b da                	or     %edx,%ebx
    7f76ecc2b445:	8b fa                	mov    %edx,%edi
    7f76ecc2b447:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2b44a:	0b df                	or     %edi,%ebx
    7f76ecc2b44c:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2b44f:	0b da                	or     %edx,%ebx
    7f76ecc2b451:	33 cb                	xor    %ebx,%ecx
    7f76ecc2b453:	49 0f b6 97 0d 01 00 	movzbq 0x10d(%r15),%rdx
    7f76ecc2b45a:	00 
    7f76ecc2b45b:	8b d2                	mov    %edx,%edx
    7f76ecc2b45d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2b462:	8b da                	mov    %edx,%ebx
    7f76ecc2b464:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2b467:	d1 e3                	shl    %ebx
    7f76ecc2b469:	8b fa                	mov    %edx,%edi
    7f76ecc2b46b:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2b46e:	83 e7 01             	and    $0x1,%edi
    7f76ecc2b471:	44 8b d7             	mov    %edi,%r10d
    7f76ecc2b474:	41 d1 e2             	shl    %r10d
    7f76ecc2b477:	44 0b d7             	or     %edi,%r10d
    7f76ecc2b47a:	89 7d 98             	mov    %edi,-0x68(%rbp)
    7f76ecc2b47d:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2b480:	44 0b d7             	or     %edi,%r10d
    7f76ecc2b483:	8b 7d 98             	mov    -0x68(%rbp),%edi
    7f76ecc2b486:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2b489:	44 0b d7             	or     %edi,%r10d
    7f76ecc2b48c:	41 33 da             	xor    %r10d,%ebx
    7f76ecc2b48f:	8b fb                	mov    %ebx,%edi
    7f76ecc2b491:	33 fa                	xor    %edx,%edi
    7f76ecc2b493:	33 f9                	xor    %ecx,%edi
    7f76ecc2b495:	4d 0f b6 97 02 01 00 	movzbq 0x102(%r15),%r10
    7f76ecc2b49c:	00 
    7f76ecc2b49d:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2b4a0:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2b4a5:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2b4a8:	44 89 4d 90          	mov    %r9d,-0x70(%rbp)
    7f76ecc2b4ac:	4d 0f b6 8f 07 01 00 	movzbq 0x107(%r15),%r9
    7f76ecc2b4b3:	00 
    7f76ecc2b4b4:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2b4b7:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2b4bc:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2b4bf:	33 d8                	xor    %eax,%ebx
    7f76ecc2b4c1:	44 89 55 88          	mov    %r10d,-0x78(%rbp)
    7f76ecc2b4c5:	41 83 e2 7f          	and    $0x7f,%r10d
    7f76ecc2b4c9:	41 d1 e2             	shl    %r10d
    7f76ecc2b4cc:	44 89 45 80          	mov    %r8d,-0x80(%rbp)
    7f76ecc2b4d0:	44 8b 45 88          	mov    -0x78(%rbp),%r8d
    7f76ecc2b4d4:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2b4d8:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2b4dc:	44 89 85 78 ff ff ff 	mov    %r8d,-0x88(%rbp)
    7f76ecc2b4e3:	41 d1 e0             	shl    %r8d
    7f76ecc2b4e6:	44 89 9d 70 ff ff ff 	mov    %r11d,-0x90(%rbp)
    7f76ecc2b4ed:	44 8b 9d 78 ff ff ff 	mov    -0x88(%rbp),%r11d
    7f76ecc2b4f4:	45 0b c3             	or     %r11d,%r8d
    7f76ecc2b4f7:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2b4fb:	45 0b c3             	or     %r11d,%r8d
    7f76ecc2b4fe:	44 8b 9d 78 ff ff ff 	mov    -0x88(%rbp),%r11d
    7f76ecc2b505:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2b509:	45 0b c3             	or     %r11d,%r8d
    7f76ecc2b50c:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2b50f:	45 8b c2             	mov    %r10d,%r8d
    7f76ecc2b512:	44 8b 5d 88          	mov    -0x78(%rbp),%r11d
    7f76ecc2b516:	45 33 c3             	xor    %r11d,%r8d
    7f76ecc2b519:	41 33 d8             	xor    %r8d,%ebx
    7f76ecc2b51c:	41 33 d9             	xor    %r9d,%ebx
    7f76ecc2b51f:	44 8b c0             	mov    %eax,%r8d
    7f76ecc2b522:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2b525:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2b528:	45 8b c1             	mov    %r9d,%r8d
    7f76ecc2b52b:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2b52f:	41 d1 e0             	shl    %r8d
    7f76ecc2b532:	45 8b d9             	mov    %r9d,%r11d
    7f76ecc2b535:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2b539:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2b53d:	44 89 9d 68 ff ff ff 	mov    %r11d,-0x98(%rbp)
    7f76ecc2b544:	41 d1 e3             	shl    %r11d
    7f76ecc2b547:	89 b5 60 ff ff ff    	mov    %esi,-0xa0(%rbp)
    7f76ecc2b54d:	8b b5 68 ff ff ff    	mov    -0x98(%rbp),%esi
    7f76ecc2b553:	44 0b de             	or     %esi,%r11d
    7f76ecc2b556:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2b559:	44 0b de             	or     %esi,%r11d
    7f76ecc2b55c:	8b b5 68 ff ff ff    	mov    -0x98(%rbp),%esi
    7f76ecc2b562:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2b565:	44 0b de             	or     %esi,%r11d
    7f76ecc2b568:	45 33 c3             	xor    %r11d,%r8d
    7f76ecc2b56b:	45 33 c8             	xor    %r8d,%r9d
    7f76ecc2b56e:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2b571:	33 c8                	xor    %eax,%ecx
    7f76ecc2b573:	33 d1                	xor    %ecx,%edx
    7f76ecc2b575:	33 55 88             	xor    -0x78(%rbp),%edx
    7f76ecc2b578:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2b57b:	49 0f b6 87 0c 01 00 	movzbq 0x10c(%r15),%rax
    7f76ecc2b582:	00 
    7f76ecc2b583:	8b c0                	mov    %eax,%eax
    7f76ecc2b585:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2b58a:	8b c8                	mov    %eax,%ecx
    7f76ecc2b58c:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2b58f:	d1 e1                	shl    %ecx
    7f76ecc2b591:	8b d0                	mov    %eax,%edx
    7f76ecc2b593:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2b596:	83 e2 01             	and    $0x1,%edx
    7f76ecc2b599:	8b f2                	mov    %edx,%esi
    7f76ecc2b59b:	d1 e6                	shl    %esi
    7f76ecc2b59d:	0b f2                	or     %edx,%esi
    7f76ecc2b59f:	44 8b ca             	mov    %edx,%r9d
    7f76ecc2b5a2:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2b5a6:	41 0b f1             	or     %r9d,%esi
    7f76ecc2b5a9:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2b5ac:	0b f2                	or     %edx,%esi
    7f76ecc2b5ae:	33 ce                	xor    %esi,%ecx
    7f76ecc2b5b0:	49 0f b6 97 01 01 00 	movzbq 0x101(%r15),%rdx
    7f76ecc2b5b7:	00 
    7f76ecc2b5b8:	8b d2                	mov    %edx,%edx
    7f76ecc2b5ba:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2b5bf:	8b f2                	mov    %edx,%esi
    7f76ecc2b5c1:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2b5c4:	d1 e6                	shl    %esi
    7f76ecc2b5c6:	44 8b ca             	mov    %edx,%r9d
    7f76ecc2b5c9:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2b5cd:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2b5d1:	45 8b d9             	mov    %r9d,%r11d
    7f76ecc2b5d4:	41 d1 e3             	shl    %r11d
    7f76ecc2b5d7:	45 0b d9             	or     %r9d,%r11d
    7f76ecc2b5da:	44 89 8d 58 ff ff ff 	mov    %r9d,-0xa8(%rbp)
    7f76ecc2b5e1:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2b5e5:	45 0b d9             	or     %r9d,%r11d
    7f76ecc2b5e8:	44 8b 8d 58 ff ff ff 	mov    -0xa8(%rbp),%r9d
    7f76ecc2b5ef:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2b5f3:	45 0b d9             	or     %r9d,%r11d
    7f76ecc2b5f6:	41 33 f3             	xor    %r11d,%esi
    7f76ecc2b5f9:	44 8b ce             	mov    %esi,%r9d
    7f76ecc2b5fc:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2b5ff:	44 33 c9             	xor    %ecx,%r9d
    7f76ecc2b602:	4d 0f b6 9f 06 01 00 	movzbq 0x106(%r15),%r11
    7f76ecc2b609:	00 
    7f76ecc2b60a:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2b60d:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2b612:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2b615:	89 bd 50 ff ff ff    	mov    %edi,-0xb0(%rbp)
    7f76ecc2b61b:	49 0f b6 bf 0b 01 00 	movzbq 0x10b(%r15),%rdi
    7f76ecc2b622:	00 
    7f76ecc2b623:	8b ff                	mov    %edi,%edi
    7f76ecc2b625:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2b62a:	44 33 cf             	xor    %edi,%r9d
    7f76ecc2b62d:	33 f0                	xor    %eax,%esi
    7f76ecc2b62f:	44 89 9d 48 ff ff ff 	mov    %r11d,-0xb8(%rbp)
    7f76ecc2b636:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2b63a:	41 d1 e3             	shl    %r11d
    7f76ecc2b63d:	89 9d 40 ff ff ff    	mov    %ebx,-0xc0(%rbp)
    7f76ecc2b643:	8b 9d 48 ff ff ff    	mov    -0xb8(%rbp),%ebx
    7f76ecc2b649:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2b64c:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2b64f:	89 9d 38 ff ff ff    	mov    %ebx,-0xc8(%rbp)
    7f76ecc2b655:	d1 e3                	shl    %ebx
    7f76ecc2b657:	44 89 95 30 ff ff ff 	mov    %r10d,-0xd0(%rbp)
    7f76ecc2b65e:	44 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%r10d
    7f76ecc2b665:	41 0b da             	or     %r10d,%ebx
    7f76ecc2b668:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2b66c:	41 0b da             	or     %r10d,%ebx
    7f76ecc2b66f:	44 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%r10d
    7f76ecc2b676:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2b67a:	41 0b da             	or     %r10d,%ebx
    7f76ecc2b67d:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2b680:	41 8b db             	mov    %r11d,%ebx
    7f76ecc2b683:	44 8b 95 48 ff ff ff 	mov    -0xb8(%rbp),%r10d
    7f76ecc2b68a:	41 33 da             	xor    %r10d,%ebx
    7f76ecc2b68d:	33 f3                	xor    %ebx,%esi
    7f76ecc2b68f:	33 f7                	xor    %edi,%esi
    7f76ecc2b691:	8b d8                	mov    %eax,%ebx
    7f76ecc2b693:	33 da                	xor    %edx,%ebx
    7f76ecc2b695:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2b698:	8b df                	mov    %edi,%ebx
    7f76ecc2b69a:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2b69d:	d1 e3                	shl    %ebx
    7f76ecc2b69f:	44 8b d7             	mov    %edi,%r10d
    7f76ecc2b6a2:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2b6a6:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2b6aa:	44 89 95 28 ff ff ff 	mov    %r10d,-0xd8(%rbp)
    7f76ecc2b6b1:	41 d1 e2             	shl    %r10d
    7f76ecc2b6b4:	44 89 85 20 ff ff ff 	mov    %r8d,-0xe0(%rbp)
    7f76ecc2b6bb:	44 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%r8d
    7f76ecc2b6c2:	45 0b d0             	or     %r8d,%r10d
    7f76ecc2b6c5:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2b6c9:	45 0b d0             	or     %r8d,%r10d
    7f76ecc2b6cc:	44 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%r8d
    7f76ecc2b6d3:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2b6d7:	45 0b d0             	or     %r8d,%r10d
    7f76ecc2b6da:	41 33 da             	xor    %r10d,%ebx
    7f76ecc2b6dd:	33 fb                	xor    %ebx,%edi
    7f76ecc2b6df:	44 33 df             	xor    %edi,%r11d
    7f76ecc2b6e2:	33 c8                	xor    %eax,%ecx
    7f76ecc2b6e4:	33 d1                	xor    %ecx,%edx
    7f76ecc2b6e6:	33 95 48 ff ff ff    	xor    -0xb8(%rbp),%edx
    7f76ecc2b6ec:	33 da                	xor    %edx,%ebx
    7f76ecc2b6ee:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7f76ecc2b6f1:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2b6f4:	0b 45 d0             	or     -0x30(%rbp),%eax
    7f76ecc2b6f7:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7f76ecc2b6fa:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2b6fd:	0b c1                	or     %ecx,%eax
    7f76ecc2b6ff:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7f76ecc2b702:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2b705:	0b c1                	or     %ecx,%eax
    7f76ecc2b707:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7f76ecc2b70a:	8b c9                	mov    %ecx,%ecx
    7f76ecc2b70c:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2b710:	8b c0                	mov    %eax,%eax
    7f76ecc2b712:	48 0b c8             	or     %rax,%rcx
    7f76ecc2b715:	8b 45 80             	mov    -0x80(%rbp),%eax
    7f76ecc2b718:	8b c0                	mov    %eax,%eax
    7f76ecc2b71a:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2b71e:	48 0b c8             	or     %rax,%rcx
    7f76ecc2b721:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7f76ecc2b727:	8b c0                	mov    %eax,%eax
    7f76ecc2b729:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2b72d:	48 0b c8             	or     %rax,%rcx
    7f76ecc2b730:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7f76ecc2b736:	8b c0                	mov    %eax,%eax
    7f76ecc2b738:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2b73c:	48 0b c8             	or     %rax,%rcx
    7f76ecc2b73f:	49 89 8f 60 02 00 00 	mov    %rcx,0x260(%r15)
    7f76ecc2b746:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7f76ecc2b74c:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2b74f:	0b 85 50 ff ff ff    	or     -0xb0(%rbp),%eax
    7f76ecc2b755:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7f76ecc2b75b:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2b75e:	0b c1                	or     %ecx,%eax
    7f76ecc2b760:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7f76ecc2b766:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2b769:	0b c1                	or     %ecx,%eax
    7f76ecc2b76b:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2b76e:	49 c1 e1 20          	shl    $0x20,%r9
    7f76ecc2b772:	8b c0                	mov    %eax,%eax
    7f76ecc2b774:	4c 0b c8             	or     %rax,%r9
    7f76ecc2b777:	8b f6                	mov    %esi,%esi
    7f76ecc2b779:	48 c1 e6 28          	shl    $0x28,%rsi
    7f76ecc2b77d:	4c 0b ce             	or     %rsi,%r9
    7f76ecc2b780:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2b783:	49 c1 e3 30          	shl    $0x30,%r11
    7f76ecc2b787:	4d 0b cb             	or     %r11,%r9
    7f76ecc2b78a:	8b db                	mov    %ebx,%ebx
    7f76ecc2b78c:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2b790:	4c 0b cb             	or     %rbx,%r9
    7f76ecc2b793:	4d 89 8f 68 02 00 00 	mov    %r9,0x268(%r15)
    7f76ecc2b79a:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    7f76ecc2b79e:	8b 41 0c             	mov    0xc(%rcx),%eax
    7f76ecc2b7a1:	8b 51 08             	mov    0x8(%rcx),%edx
    7f76ecc2b7a4:	8b 59 04             	mov    0x4(%rcx),%ebx
    7f76ecc2b7a7:	8b 31                	mov    (%rcx),%esi
    7f76ecc2b7a9:	48 0f b6 79 0c       	movzbq 0xc(%rcx),%rdi
    7f76ecc2b7ae:	8b ff                	mov    %edi,%edi
    7f76ecc2b7b0:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2b7b5:	4c 0f b6 41 0f       	movzbq 0xf(%rcx),%r8
    7f76ecc2b7ba:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2b7bd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2b7c2:	4c 0f b6 49 0e       	movzbq 0xe(%rcx),%r9
    7f76ecc2b7c7:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2b7ca:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2b7cf:	48 0f b6 49 0d       	movzbq 0xd(%rcx),%rcx
    7f76ecc2b7d4:	8b c9                	mov    %ecx,%ecx
    7f76ecc2b7d6:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2b7db:	41 c1 e1 08          	shl    $0x8,%r9d
    7f76ecc2b7df:	41 0b c9             	or     %r9d,%ecx
    7f76ecc2b7e2:	41 c1 e0 10          	shl    $0x10,%r8d
    7f76ecc2b7e6:	41 0b c8             	or     %r8d,%ecx
    7f76ecc2b7e9:	c1 e7 18             	shl    $0x18,%edi
    7f76ecc2b7ec:	0b cf                	or     %edi,%ecx
    7f76ecc2b7ee:	83 f1 01             	xor    $0x1,%ecx
    7f76ecc2b7f1:	33 f1                	xor    %ecx,%esi
    7f76ecc2b7f3:	33 de                	xor    %esi,%ebx
    7f76ecc2b7f5:	33 d3                	xor    %ebx,%edx
    7f76ecc2b7f7:	33 c2                	xor    %edx,%eax
    7f76ecc2b7f9:	8b cb                	mov    %ebx,%ecx
    7f76ecc2b7fb:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2b7ff:	8b fe                	mov    %esi,%edi
    7f76ecc2b801:	48 0b cf             	or     %rdi,%rcx
    7f76ecc2b804:	49 89 8f c0 01 00 00 	mov    %rcx,0x1c0(%r15)
    7f76ecc2b80b:	8b c8                	mov    %eax,%ecx
    7f76ecc2b80d:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2b811:	8b fa                	mov    %edx,%edi
    7f76ecc2b813:	48 0b cf             	or     %rdi,%rcx
    7f76ecc2b816:	49 89 8f c8 01 00 00 	mov    %rcx,0x1c8(%r15)
    7f76ecc2b81d:	49 8b 8f 60 02 00 00 	mov    0x260(%r15),%rcx
    7f76ecc2b824:	49 8b bf c0 01 00 00 	mov    0x1c0(%r15),%rdi
    7f76ecc2b82b:	48 33 cf             	xor    %rdi,%rcx
    7f76ecc2b82e:	49 89 8f 10 03 00 00 	mov    %rcx,0x310(%r15)
    7f76ecc2b835:	49 8b 8f 68 02 00 00 	mov    0x268(%r15),%rcx
    7f76ecc2b83c:	49 8b bf c8 01 00 00 	mov    0x1c8(%r15),%rdi
    7f76ecc2b843:	48 33 cf             	xor    %rdi,%rcx
    7f76ecc2b846:	49 89 8f 18 03 00 00 	mov    %rcx,0x318(%r15)
    7f76ecc2b84d:	49 0f b6 8f 10 01 00 	movzbq 0x110(%r15),%rcx
    7f76ecc2b854:	00 
    7f76ecc2b855:	8b c9                	mov    %ecx,%ecx
    7f76ecc2b857:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2b85c:	8b f9                	mov    %ecx,%edi
    7f76ecc2b85e:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2b861:	d1 e7                	shl    %edi
    7f76ecc2b863:	44 8b c1             	mov    %ecx,%r8d
    7f76ecc2b866:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2b86a:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2b86e:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2b871:	41 d1 e1             	shl    %r9d
    7f76ecc2b874:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2b877:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2b87a:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2b87e:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2b881:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2b885:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2b888:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2b88b:	4d 0f b6 87 15 01 00 	movzbq 0x115(%r15),%r8
    7f76ecc2b892:	00 
    7f76ecc2b893:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2b896:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2b89b:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2b89e:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2b8a2:	41 d1 e1             	shl    %r9d
    7f76ecc2b8a5:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2b8a8:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2b8ac:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2b8b0:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2b8b3:	41 d1 e3             	shl    %r11d
    7f76ecc2b8b6:	45 0b da             	or     %r10d,%r11d
    7f76ecc2b8b9:	44 89 95 18 ff ff ff 	mov    %r10d,-0xe8(%rbp)
    7f76ecc2b8c0:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2b8c4:	45 0b da             	or     %r10d,%r11d
    7f76ecc2b8c7:	44 8b 95 18 ff ff ff 	mov    -0xe8(%rbp),%r10d
    7f76ecc2b8ce:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2b8d2:	45 0b da             	or     %r10d,%r11d
    7f76ecc2b8d5:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2b8d8:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2b8db:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2b8de:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2b8e1:	4d 0f b6 9f 1a 01 00 	movzbq 0x11a(%r15),%r11
    7f76ecc2b8e8:	00 
    7f76ecc2b8e9:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2b8ec:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2b8f1:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2b8f4:	89 9d 10 ff ff ff    	mov    %ebx,-0xf0(%rbp)
    7f76ecc2b8fa:	49 0f b6 9f 1f 01 00 	movzbq 0x11f(%r15),%rbx
    7f76ecc2b901:	00 
    7f76ecc2b902:	8b db                	mov    %ebx,%ebx
    7f76ecc2b904:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2b909:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2b90c:	44 33 c9             	xor    %ecx,%r9d
    7f76ecc2b90f:	44 89 9d 08 ff ff ff 	mov    %r11d,-0xf8(%rbp)
    7f76ecc2b916:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2b91a:	41 d1 e3             	shl    %r11d
    7f76ecc2b91d:	89 b5 00 ff ff ff    	mov    %esi,-0x100(%rbp)
    7f76ecc2b923:	8b b5 08 ff ff ff    	mov    -0xf8(%rbp),%esi
    7f76ecc2b929:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2b92c:	83 e6 01             	and    $0x1,%esi
    7f76ecc2b92f:	89 b5 f8 fe ff ff    	mov    %esi,-0x108(%rbp)
    7f76ecc2b935:	d1 e6                	shl    %esi
    7f76ecc2b937:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7f76ecc2b93d:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7f76ecc2b943:	0b f0                	or     %eax,%esi
    7f76ecc2b945:	c1 e0 03             	shl    $0x3,%eax
    7f76ecc2b948:	0b f0                	or     %eax,%esi
    7f76ecc2b94a:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7f76ecc2b950:	c1 e0 04             	shl    $0x4,%eax
    7f76ecc2b953:	0b f0                	or     %eax,%esi
    7f76ecc2b955:	44 33 de             	xor    %esi,%r11d
    7f76ecc2b958:	41 8b c3             	mov    %r11d,%eax
    7f76ecc2b95b:	8b b5 08 ff ff ff    	mov    -0xf8(%rbp),%esi
    7f76ecc2b961:	33 c6                	xor    %esi,%eax
    7f76ecc2b963:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2b966:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2b969:	8b c1                	mov    %ecx,%eax
    7f76ecc2b96b:	41 33 c0             	xor    %r8d,%eax
    7f76ecc2b96e:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2b971:	8b c3                	mov    %ebx,%eax
    7f76ecc2b973:	83 e0 7f             	and    $0x7f,%eax
    7f76ecc2b976:	d1 e0                	shl    %eax
    7f76ecc2b978:	8b f3                	mov    %ebx,%esi
    7f76ecc2b97a:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2b97d:	83 e6 01             	and    $0x1,%esi
    7f76ecc2b980:	89 b5 e8 fe ff ff    	mov    %esi,-0x118(%rbp)
    7f76ecc2b986:	d1 e6                	shl    %esi
    7f76ecc2b988:	89 95 e0 fe ff ff    	mov    %edx,-0x120(%rbp)
    7f76ecc2b98e:	8b 95 e8 fe ff ff    	mov    -0x118(%rbp),%edx
    7f76ecc2b994:	0b f2                	or     %edx,%esi
    7f76ecc2b996:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2b999:	0b f2                	or     %edx,%esi
    7f76ecc2b99b:	8b 95 e8 fe ff ff    	mov    -0x118(%rbp),%edx
    7f76ecc2b9a1:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2b9a4:	0b f2                	or     %edx,%esi
    7f76ecc2b9a6:	33 c6                	xor    %esi,%eax
    7f76ecc2b9a8:	33 d8                	xor    %eax,%ebx
    7f76ecc2b9aa:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2b9ad:	33 f9                	xor    %ecx,%edi
    7f76ecc2b9af:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2b9b2:	44 33 85 08 ff ff ff 	xor    -0xf8(%rbp),%r8d
    7f76ecc2b9b9:	41 33 c0             	xor    %r8d,%eax
    7f76ecc2b9bc:	49 0f b6 8f 14 01 00 	movzbq 0x114(%r15),%rcx
    7f76ecc2b9c3:	00 
    7f76ecc2b9c4:	8b c9                	mov    %ecx,%ecx
    7f76ecc2b9c6:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2b9cb:	8b d1                	mov    %ecx,%edx
    7f76ecc2b9cd:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2b9d0:	d1 e2                	shl    %edx
    7f76ecc2b9d2:	8b d9                	mov    %ecx,%ebx
    7f76ecc2b9d4:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2b9d7:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2b9da:	8b f3                	mov    %ebx,%esi
    7f76ecc2b9dc:	d1 e6                	shl    %esi
    7f76ecc2b9de:	0b f3                	or     %ebx,%esi
    7f76ecc2b9e0:	8b fb                	mov    %ebx,%edi
    7f76ecc2b9e2:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2b9e5:	0b f7                	or     %edi,%esi
    7f76ecc2b9e7:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2b9ea:	0b f3                	or     %ebx,%esi
    7f76ecc2b9ec:	33 d6                	xor    %esi,%edx
    7f76ecc2b9ee:	49 0f b6 9f 19 01 00 	movzbq 0x119(%r15),%rbx
    7f76ecc2b9f5:	00 
    7f76ecc2b9f6:	8b db                	mov    %ebx,%ebx
    7f76ecc2b9f8:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2b9fd:	8b f3                	mov    %ebx,%esi
    7f76ecc2b9ff:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2ba02:	d1 e6                	shl    %esi
    7f76ecc2ba04:	8b fb                	mov    %ebx,%edi
    7f76ecc2ba06:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2ba09:	83 e7 01             	and    $0x1,%edi
    7f76ecc2ba0c:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2ba0f:	41 d1 e0             	shl    %r8d
    7f76ecc2ba12:	44 0b c7             	or     %edi,%r8d
    7f76ecc2ba15:	89 bd d8 fe ff ff    	mov    %edi,-0x128(%rbp)
    7f76ecc2ba1b:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2ba1e:	44 0b c7             	or     %edi,%r8d
    7f76ecc2ba21:	8b bd d8 fe ff ff    	mov    -0x128(%rbp),%edi
    7f76ecc2ba27:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2ba2a:	44 0b c7             	or     %edi,%r8d
    7f76ecc2ba2d:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2ba30:	8b fe                	mov    %esi,%edi
    7f76ecc2ba32:	33 fb                	xor    %ebx,%edi
    7f76ecc2ba34:	33 fa                	xor    %edx,%edi
    7f76ecc2ba36:	4d 0f b6 87 1e 01 00 	movzbq 0x11e(%r15),%r8
    7f76ecc2ba3d:	00 
    7f76ecc2ba3e:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2ba41:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2ba46:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2ba49:	44 89 95 d0 fe ff ff 	mov    %r10d,-0x130(%rbp)
    7f76ecc2ba50:	4d 0f b6 97 13 01 00 	movzbq 0x113(%r15),%r10
    7f76ecc2ba57:	00 
    7f76ecc2ba58:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2ba5b:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2ba60:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2ba63:	33 f1                	xor    %ecx,%esi
    7f76ecc2ba65:	44 89 85 c8 fe ff ff 	mov    %r8d,-0x138(%rbp)
    7f76ecc2ba6c:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2ba70:	41 d1 e0             	shl    %r8d
    7f76ecc2ba73:	44 89 8d c0 fe ff ff 	mov    %r9d,-0x140(%rbp)
    7f76ecc2ba7a:	44 8b 8d c8 fe ff ff 	mov    -0x138(%rbp),%r9d
    7f76ecc2ba81:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2ba85:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2ba89:	44 89 8d b8 fe ff ff 	mov    %r9d,-0x148(%rbp)
    7f76ecc2ba90:	41 d1 e1             	shl    %r9d
    7f76ecc2ba93:	44 89 9d b0 fe ff ff 	mov    %r11d,-0x150(%rbp)
    7f76ecc2ba9a:	44 8b 9d b8 fe ff ff 	mov    -0x148(%rbp),%r11d
    7f76ecc2baa1:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2baa4:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2baa8:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2baab:	44 8b 9d b8 fe ff ff 	mov    -0x148(%rbp),%r11d
    7f76ecc2bab2:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2bab6:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2bab9:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2babc:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2babf:	44 8b 9d c8 fe ff ff 	mov    -0x138(%rbp),%r11d
    7f76ecc2bac6:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2bac9:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2bacc:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2bacf:	44 8b c9             	mov    %ecx,%r9d
    7f76ecc2bad2:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2bad5:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2bad8:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2badb:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2badf:	41 d1 e1             	shl    %r9d
    7f76ecc2bae2:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2bae5:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2bae9:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2baed:	44 89 9d a8 fe ff ff 	mov    %r11d,-0x158(%rbp)
    7f76ecc2baf4:	41 d1 e3             	shl    %r11d
    7f76ecc2baf7:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7f76ecc2bafd:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f76ecc2bb03:	44 0b d8             	or     %eax,%r11d
    7f76ecc2bb06:	c1 e0 03             	shl    $0x3,%eax
    7f76ecc2bb09:	44 0b d8             	or     %eax,%r11d
    7f76ecc2bb0c:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7f76ecc2bb12:	c1 e0 04             	shl    $0x4,%eax
    7f76ecc2bb15:	44 0b d8             	or     %eax,%r11d
    7f76ecc2bb18:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2bb1b:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2bb1e:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2bb21:	33 d1                	xor    %ecx,%edx
    7f76ecc2bb23:	33 da                	xor    %edx,%ebx
    7f76ecc2bb25:	33 9d c8 fe ff ff    	xor    -0x138(%rbp),%ebx
    7f76ecc2bb2b:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2bb2e:	49 0f b6 87 18 01 00 	movzbq 0x118(%r15),%rax
    7f76ecc2bb35:	00 
    7f76ecc2bb36:	8b c0                	mov    %eax,%eax
    7f76ecc2bb38:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2bb3d:	8b c8                	mov    %eax,%ecx
    7f76ecc2bb3f:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2bb42:	d1 e1                	shl    %ecx
    7f76ecc2bb44:	8b d0                	mov    %eax,%edx
    7f76ecc2bb46:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2bb49:	83 e2 01             	and    $0x1,%edx
    7f76ecc2bb4c:	8b da                	mov    %edx,%ebx
    7f76ecc2bb4e:	d1 e3                	shl    %ebx
    7f76ecc2bb50:	0b da                	or     %edx,%ebx
    7f76ecc2bb52:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2bb55:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2bb59:	41 0b da             	or     %r10d,%ebx
    7f76ecc2bb5c:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2bb5f:	0b da                	or     %edx,%ebx
    7f76ecc2bb61:	33 cb                	xor    %ebx,%ecx
    7f76ecc2bb63:	49 0f b6 97 1d 01 00 	movzbq 0x11d(%r15),%rdx
    7f76ecc2bb6a:	00 
    7f76ecc2bb6b:	8b d2                	mov    %edx,%edx
    7f76ecc2bb6d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2bb72:	8b da                	mov    %edx,%ebx
    7f76ecc2bb74:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2bb77:	d1 e3                	shl    %ebx
    7f76ecc2bb79:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2bb7c:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2bb80:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2bb84:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2bb87:	41 d1 e3             	shl    %r11d
    7f76ecc2bb8a:	45 0b da             	or     %r10d,%r11d
    7f76ecc2bb8d:	44 89 95 98 fe ff ff 	mov    %r10d,-0x168(%rbp)
    7f76ecc2bb94:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2bb98:	45 0b da             	or     %r10d,%r11d
    7f76ecc2bb9b:	44 8b 95 98 fe ff ff 	mov    -0x168(%rbp),%r10d
    7f76ecc2bba2:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2bba6:	45 0b da             	or     %r10d,%r11d
    7f76ecc2bba9:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2bbac:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2bbaf:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2bbb2:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2bbb5:	4d 0f b6 9f 12 01 00 	movzbq 0x112(%r15),%r11
    7f76ecc2bbbc:	00 
    7f76ecc2bbbd:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2bbc0:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2bbc5:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2bbc8:	89 bd 90 fe ff ff    	mov    %edi,-0x170(%rbp)
    7f76ecc2bbce:	49 0f b6 bf 17 01 00 	movzbq 0x117(%r15),%rdi
    7f76ecc2bbd5:	00 
    7f76ecc2bbd6:	8b ff                	mov    %edi,%edi
    7f76ecc2bbd8:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2bbdd:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2bbe0:	33 d8                	xor    %eax,%ebx
    7f76ecc2bbe2:	44 89 9d 88 fe ff ff 	mov    %r11d,-0x178(%rbp)
    7f76ecc2bbe9:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2bbed:	41 d1 e3             	shl    %r11d
    7f76ecc2bbf0:	89 b5 80 fe ff ff    	mov    %esi,-0x180(%rbp)
    7f76ecc2bbf6:	8b b5 88 fe ff ff    	mov    -0x178(%rbp),%esi
    7f76ecc2bbfc:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2bbff:	83 e6 01             	and    $0x1,%esi
    7f76ecc2bc02:	89 b5 78 fe ff ff    	mov    %esi,-0x188(%rbp)
    7f76ecc2bc08:	d1 e6                	shl    %esi
    7f76ecc2bc0a:	44 89 85 70 fe ff ff 	mov    %r8d,-0x190(%rbp)
    7f76ecc2bc11:	44 8b 85 78 fe ff ff 	mov    -0x188(%rbp),%r8d
    7f76ecc2bc18:	41 0b f0             	or     %r8d,%esi
    7f76ecc2bc1b:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2bc1f:	41 0b f0             	or     %r8d,%esi
    7f76ecc2bc22:	44 8b 85 78 fe ff ff 	mov    -0x188(%rbp),%r8d
    7f76ecc2bc29:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2bc2d:	41 0b f0             	or     %r8d,%esi
    7f76ecc2bc30:	44 33 de             	xor    %esi,%r11d
    7f76ecc2bc33:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2bc36:	44 8b 85 88 fe ff ff 	mov    -0x178(%rbp),%r8d
    7f76ecc2bc3d:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2bc40:	33 de                	xor    %esi,%ebx
    7f76ecc2bc42:	33 df                	xor    %edi,%ebx
    7f76ecc2bc44:	8b f0                	mov    %eax,%esi
    7f76ecc2bc46:	33 f2                	xor    %edx,%esi
    7f76ecc2bc48:	44 33 de             	xor    %esi,%r11d
    7f76ecc2bc4b:	8b f7                	mov    %edi,%esi
    7f76ecc2bc4d:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2bc50:	d1 e6                	shl    %esi
    7f76ecc2bc52:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2bc55:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2bc59:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2bc5d:	44 89 85 68 fe ff ff 	mov    %r8d,-0x198(%rbp)
    7f76ecc2bc64:	41 d1 e0             	shl    %r8d
    7f76ecc2bc67:	44 89 8d 60 fe ff ff 	mov    %r9d,-0x1a0(%rbp)
    7f76ecc2bc6e:	44 8b 8d 68 fe ff ff 	mov    -0x198(%rbp),%r9d
    7f76ecc2bc75:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2bc78:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2bc7c:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2bc7f:	44 8b 8d 68 fe ff ff 	mov    -0x198(%rbp),%r9d
    7f76ecc2bc86:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2bc8a:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2bc8d:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2bc90:	33 fe                	xor    %esi,%edi
    7f76ecc2bc92:	44 33 df             	xor    %edi,%r11d
    7f76ecc2bc95:	33 c8                	xor    %eax,%ecx
    7f76ecc2bc97:	33 d1                	xor    %ecx,%edx
    7f76ecc2bc99:	33 95 88 fe ff ff    	xor    -0x178(%rbp),%edx
    7f76ecc2bc9f:	33 f2                	xor    %edx,%esi
    7f76ecc2bca1:	49 0f b6 87 1c 01 00 	movzbq 0x11c(%r15),%rax
    7f76ecc2bca8:	00 
    7f76ecc2bca9:	8b c0                	mov    %eax,%eax
    7f76ecc2bcab:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2bcb0:	8b c8                	mov    %eax,%ecx
    7f76ecc2bcb2:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2bcb5:	d1 e1                	shl    %ecx
    7f76ecc2bcb7:	8b d0                	mov    %eax,%edx
    7f76ecc2bcb9:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2bcbc:	83 e2 01             	and    $0x1,%edx
    7f76ecc2bcbf:	8b fa                	mov    %edx,%edi
    7f76ecc2bcc1:	d1 e7                	shl    %edi
    7f76ecc2bcc3:	0b fa                	or     %edx,%edi
    7f76ecc2bcc5:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2bcc8:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2bccc:	41 0b f8             	or     %r8d,%edi
    7f76ecc2bccf:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2bcd2:	0b fa                	or     %edx,%edi
    7f76ecc2bcd4:	33 cf                	xor    %edi,%ecx
    7f76ecc2bcd6:	49 0f b6 97 11 01 00 	movzbq 0x111(%r15),%rdx
    7f76ecc2bcdd:	00 
    7f76ecc2bcde:	8b d2                	mov    %edx,%edx
    7f76ecc2bce0:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2bce5:	8b fa                	mov    %edx,%edi
    7f76ecc2bce7:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2bcea:	d1 e7                	shl    %edi
    7f76ecc2bcec:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2bcef:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2bcf3:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2bcf7:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2bcfa:	41 d1 e1             	shl    %r9d
    7f76ecc2bcfd:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2bd00:	44 89 85 58 fe ff ff 	mov    %r8d,-0x1a8(%rbp)
    7f76ecc2bd07:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2bd0b:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2bd0e:	44 8b 85 58 fe ff ff 	mov    -0x1a8(%rbp),%r8d
    7f76ecc2bd15:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2bd19:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2bd1c:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2bd1f:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2bd22:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2bd25:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2bd28:	4d 0f b6 8f 16 01 00 	movzbq 0x116(%r15),%r9
    7f76ecc2bd2f:	00 
    7f76ecc2bd30:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2bd33:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2bd38:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2bd3b:	44 89 95 50 fe ff ff 	mov    %r10d,-0x1b0(%rbp)
    7f76ecc2bd42:	4d 0f b6 97 1b 01 00 	movzbq 0x11b(%r15),%r10
    7f76ecc2bd49:	00 
    7f76ecc2bd4a:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2bd4d:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2bd52:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2bd55:	33 f8                	xor    %eax,%edi
    7f76ecc2bd57:	44 89 8d 48 fe ff ff 	mov    %r9d,-0x1b8(%rbp)
    7f76ecc2bd5e:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2bd62:	41 d1 e1             	shl    %r9d
    7f76ecc2bd65:	89 9d 40 fe ff ff    	mov    %ebx,-0x1c0(%rbp)
    7f76ecc2bd6b:	8b 9d 48 fe ff ff    	mov    -0x1b8(%rbp),%ebx
    7f76ecc2bd71:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2bd74:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2bd77:	89 9d 38 fe ff ff    	mov    %ebx,-0x1c8(%rbp)
    7f76ecc2bd7d:	d1 e3                	shl    %ebx
    7f76ecc2bd7f:	44 89 9d 30 fe ff ff 	mov    %r11d,-0x1d0(%rbp)
    7f76ecc2bd86:	44 8b 9d 38 fe ff ff 	mov    -0x1c8(%rbp),%r11d
    7f76ecc2bd8d:	41 0b db             	or     %r11d,%ebx
    7f76ecc2bd90:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2bd94:	41 0b db             	or     %r11d,%ebx
    7f76ecc2bd97:	44 8b 9d 38 fe ff ff 	mov    -0x1c8(%rbp),%r11d
    7f76ecc2bd9e:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2bda2:	41 0b db             	or     %r11d,%ebx
    7f76ecc2bda5:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2bda8:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2bdab:	44 8b 9d 48 fe ff ff 	mov    -0x1b8(%rbp),%r11d
    7f76ecc2bdb2:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2bdb5:	33 fb                	xor    %ebx,%edi
    7f76ecc2bdb7:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2bdba:	8b d8                	mov    %eax,%ebx
    7f76ecc2bdbc:	33 da                	xor    %edx,%ebx
    7f76ecc2bdbe:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2bdc1:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2bdc4:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2bdc7:	d1 e3                	shl    %ebx
    7f76ecc2bdc9:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2bdcc:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2bdd0:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2bdd4:	44 89 9d 28 fe ff ff 	mov    %r11d,-0x1d8(%rbp)
    7f76ecc2bddb:	41 d1 e3             	shl    %r11d
    7f76ecc2bdde:	89 b5 20 fe ff ff    	mov    %esi,-0x1e0(%rbp)
    7f76ecc2bde4:	8b b5 28 fe ff ff    	mov    -0x1d8(%rbp),%esi
    7f76ecc2bdea:	44 0b de             	or     %esi,%r11d
    7f76ecc2bded:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2bdf0:	44 0b de             	or     %esi,%r11d
    7f76ecc2bdf3:	8b b5 28 fe ff ff    	mov    -0x1d8(%rbp),%esi
    7f76ecc2bdf9:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2bdfc:	44 0b de             	or     %esi,%r11d
    7f76ecc2bdff:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2be02:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2be05:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2be08:	33 c8                	xor    %eax,%ecx
    7f76ecc2be0a:	33 d1                	xor    %ecx,%edx
    7f76ecc2be0c:	33 95 48 fe ff ff    	xor    -0x1b8(%rbp),%edx
    7f76ecc2be12:	33 da                	xor    %edx,%ebx
    7f76ecc2be14:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7f76ecc2be1a:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2be1d:	0b 85 d0 fe ff ff    	or     -0x130(%rbp),%eax
    7f76ecc2be23:	8b 8d b0 fe ff ff    	mov    -0x150(%rbp),%ecx
    7f76ecc2be29:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2be2c:	0b c1                	or     %ecx,%eax
    7f76ecc2be2e:	8b 8d a0 fe ff ff    	mov    -0x160(%rbp),%ecx
    7f76ecc2be34:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2be37:	0b c1                	or     %ecx,%eax
    7f76ecc2be39:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7f76ecc2be3f:	8b c9                	mov    %ecx,%ecx
    7f76ecc2be41:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2be45:	8b c0                	mov    %eax,%eax
    7f76ecc2be47:	48 0b c8             	or     %rax,%rcx
    7f76ecc2be4a:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7f76ecc2be50:	8b c0                	mov    %eax,%eax
    7f76ecc2be52:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2be56:	48 0b c8             	or     %rax,%rcx
    7f76ecc2be59:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7f76ecc2be5f:	8b c0                	mov    %eax,%eax
    7f76ecc2be61:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2be65:	48 0b c8             	or     %rax,%rcx
    7f76ecc2be68:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7f76ecc2be6e:	8b c0                	mov    %eax,%eax
    7f76ecc2be70:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2be74:	48 0b c8             	or     %rax,%rcx
    7f76ecc2be77:	49 89 8f 70 02 00 00 	mov    %rcx,0x270(%r15)
    7f76ecc2be7e:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7f76ecc2be84:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2be87:	0b 85 50 fe ff ff    	or     -0x1b0(%rbp),%eax
    7f76ecc2be8d:	8b 8d 30 fe ff ff    	mov    -0x1d0(%rbp),%ecx
    7f76ecc2be93:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2be96:	0b c1                	or     %ecx,%eax
    7f76ecc2be98:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7f76ecc2be9e:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2bea1:	0b c1                	or     %ecx,%eax
    7f76ecc2bea3:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2bea6:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2beaa:	8b c0                	mov    %eax,%eax
    7f76ecc2beac:	4c 0b c0             	or     %rax,%r8
    7f76ecc2beaf:	8b ff                	mov    %edi,%edi
    7f76ecc2beb1:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2beb5:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2beb8:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2bebb:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2bebf:	4d 0b c1             	or     %r9,%r8
    7f76ecc2bec2:	8b db                	mov    %ebx,%ebx
    7f76ecc2bec4:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2bec8:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2becb:	4d 89 87 78 02 00 00 	mov    %r8,0x278(%r15)
    7f76ecc2bed2:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7f76ecc2bed8:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2bedd:	8b c0                	mov    %eax,%eax
    7f76ecc2bedf:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2bee4:	8b 8d f0 fe ff ff    	mov    -0x110(%rbp),%ecx
    7f76ecc2beea:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2beed:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2bef3:	8b c9                	mov    %ecx,%ecx
    7f76ecc2bef5:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2befa:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7f76ecc2bf00:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2bf03:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2bf09:	8b d2                	mov    %edx,%edx
    7f76ecc2bf0b:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2bf10:	8b 9d f0 fe ff ff    	mov    -0x110(%rbp),%ebx
    7f76ecc2bf16:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2bf19:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2bf1f:	8b db                	mov    %ebx,%ebx
    7f76ecc2bf21:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2bf26:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2bf29:	0b da                	or     %edx,%ebx
    7f76ecc2bf2b:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2bf2e:	0b d9                	or     %ecx,%ebx
    7f76ecc2bf30:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2bf33:	0b d8                	or     %eax,%ebx
    7f76ecc2bf35:	83 f3 02             	xor    $0x2,%ebx
    7f76ecc2bf38:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7f76ecc2bf3e:	33 d8                	xor    %eax,%ebx
    7f76ecc2bf40:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7f76ecc2bf46:	33 c3                	xor    %ebx,%eax
    7f76ecc2bf48:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7f76ecc2bf4e:	33 c8                	xor    %eax,%ecx
    7f76ecc2bf50:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7f76ecc2bf56:	33 d1                	xor    %ecx,%edx
    7f76ecc2bf58:	8b f0                	mov    %eax,%esi
    7f76ecc2bf5a:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2bf5e:	8b fb                	mov    %ebx,%edi
    7f76ecc2bf60:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2bf63:	49 89 b7 d0 01 00 00 	mov    %rsi,0x1d0(%r15)
    7f76ecc2bf6a:	8b f2                	mov    %edx,%esi
    7f76ecc2bf6c:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2bf70:	8b f9                	mov    %ecx,%edi
    7f76ecc2bf72:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2bf75:	49 89 b7 d8 01 00 00 	mov    %rsi,0x1d8(%r15)
    7f76ecc2bf7c:	49 8b b7 70 02 00 00 	mov    0x270(%r15),%rsi
    7f76ecc2bf83:	49 8b bf d0 01 00 00 	mov    0x1d0(%r15),%rdi
    7f76ecc2bf8a:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2bf8d:	49 89 b7 20 03 00 00 	mov    %rsi,0x320(%r15)
    7f76ecc2bf94:	49 8b b7 78 02 00 00 	mov    0x278(%r15),%rsi
    7f76ecc2bf9b:	49 8b bf d8 01 00 00 	mov    0x1d8(%r15),%rdi
    7f76ecc2bfa2:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2bfa5:	49 89 b7 28 03 00 00 	mov    %rsi,0x328(%r15)
    7f76ecc2bfac:	49 0f b6 b7 20 01 00 	movzbq 0x120(%r15),%rsi
    7f76ecc2bfb3:	00 
    7f76ecc2bfb4:	8b f6                	mov    %esi,%esi
    7f76ecc2bfb6:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2bfbb:	8b fe                	mov    %esi,%edi
    7f76ecc2bfbd:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2bfc0:	d1 e7                	shl    %edi
    7f76ecc2bfc2:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2bfc5:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2bfc9:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2bfcd:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2bfd0:	41 d1 e1             	shl    %r9d
    7f76ecc2bfd3:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2bfd6:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2bfd9:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2bfdd:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2bfe0:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2bfe4:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2bfe7:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2bfea:	4d 0f b6 87 25 01 00 	movzbq 0x125(%r15),%r8
    7f76ecc2bff1:	00 
    7f76ecc2bff2:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2bff5:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2bffa:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2bffd:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2c001:	41 d1 e1             	shl    %r9d
    7f76ecc2c004:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2c007:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2c00b:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2c00f:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2c012:	41 d1 e3             	shl    %r11d
    7f76ecc2c015:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c018:	44 89 95 18 fe ff ff 	mov    %r10d,-0x1e8(%rbp)
    7f76ecc2c01f:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2c023:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c026:	44 8b 95 18 fe ff ff 	mov    -0x1e8(%rbp),%r10d
    7f76ecc2c02d:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2c031:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c034:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2c037:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2c03a:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2c03d:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2c040:	4d 0f b6 9f 2a 01 00 	movzbq 0x12a(%r15),%r11
    7f76ecc2c047:	00 
    7f76ecc2c048:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2c04b:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2c050:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2c053:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7f76ecc2c059:	49 0f b6 87 2f 01 00 	movzbq 0x12f(%r15),%rax
    7f76ecc2c060:	00 
    7f76ecc2c061:	8b c0                	mov    %eax,%eax
    7f76ecc2c063:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c068:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2c06b:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2c06e:	44 89 9d 08 fe ff ff 	mov    %r11d,-0x1f8(%rbp)
    7f76ecc2c075:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2c079:	41 d1 e3             	shl    %r11d
    7f76ecc2c07c:	89 9d 00 fe ff ff    	mov    %ebx,-0x200(%rbp)
    7f76ecc2c082:	8b 9d 08 fe ff ff    	mov    -0x1f8(%rbp),%ebx
    7f76ecc2c088:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c08b:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c08e:	89 9d f8 fd ff ff    	mov    %ebx,-0x208(%rbp)
    7f76ecc2c094:	d1 e3                	shl    %ebx
    7f76ecc2c096:	89 95 f0 fd ff ff    	mov    %edx,-0x210(%rbp)
    7f76ecc2c09c:	8b 95 f8 fd ff ff    	mov    -0x208(%rbp),%edx
    7f76ecc2c0a2:	0b da                	or     %edx,%ebx
    7f76ecc2c0a4:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2c0a7:	0b da                	or     %edx,%ebx
    7f76ecc2c0a9:	8b 95 f8 fd ff ff    	mov    -0x208(%rbp),%edx
    7f76ecc2c0af:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2c0b2:	0b da                	or     %edx,%ebx
    7f76ecc2c0b4:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2c0b7:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2c0ba:	8b 9d 08 fe ff ff    	mov    -0x1f8(%rbp),%ebx
    7f76ecc2c0c0:	33 d3                	xor    %ebx,%edx
    7f76ecc2c0c2:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2c0c5:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2c0c8:	8b d6                	mov    %esi,%edx
    7f76ecc2c0ca:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2c0cd:	44 33 da             	xor    %edx,%r11d
    7f76ecc2c0d0:	8b d0                	mov    %eax,%edx
    7f76ecc2c0d2:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2c0d5:	d1 e2                	shl    %edx
    7f76ecc2c0d7:	8b d8                	mov    %eax,%ebx
    7f76ecc2c0d9:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c0dc:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c0df:	89 9d e8 fd ff ff    	mov    %ebx,-0x218(%rbp)
    7f76ecc2c0e5:	d1 e3                	shl    %ebx
    7f76ecc2c0e7:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7f76ecc2c0ed:	8b 8d e8 fd ff ff    	mov    -0x218(%rbp),%ecx
    7f76ecc2c0f3:	0b d9                	or     %ecx,%ebx
    7f76ecc2c0f5:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2c0f8:	0b d9                	or     %ecx,%ebx
    7f76ecc2c0fa:	8b 8d e8 fd ff ff    	mov    -0x218(%rbp),%ecx
    7f76ecc2c100:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2c103:	0b d9                	or     %ecx,%ebx
    7f76ecc2c105:	33 d3                	xor    %ebx,%edx
    7f76ecc2c107:	33 c2                	xor    %edx,%eax
    7f76ecc2c109:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2c10c:	33 fe                	xor    %esi,%edi
    7f76ecc2c10e:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2c111:	44 33 85 08 fe ff ff 	xor    -0x1f8(%rbp),%r8d
    7f76ecc2c118:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2c11b:	49 0f b6 87 24 01 00 	movzbq 0x124(%r15),%rax
    7f76ecc2c122:	00 
    7f76ecc2c123:	8b c0                	mov    %eax,%eax
    7f76ecc2c125:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c12a:	8b c8                	mov    %eax,%ecx
    7f76ecc2c12c:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2c12f:	d1 e1                	shl    %ecx
    7f76ecc2c131:	8b d8                	mov    %eax,%ebx
    7f76ecc2c133:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c136:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c139:	8b f3                	mov    %ebx,%esi
    7f76ecc2c13b:	d1 e6                	shl    %esi
    7f76ecc2c13d:	0b f3                	or     %ebx,%esi
    7f76ecc2c13f:	8b fb                	mov    %ebx,%edi
    7f76ecc2c141:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2c144:	0b f7                	or     %edi,%esi
    7f76ecc2c146:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2c149:	0b f3                	or     %ebx,%esi
    7f76ecc2c14b:	33 ce                	xor    %esi,%ecx
    7f76ecc2c14d:	49 0f b6 9f 29 01 00 	movzbq 0x129(%r15),%rbx
    7f76ecc2c154:	00 
    7f76ecc2c155:	8b db                	mov    %ebx,%ebx
    7f76ecc2c157:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2c15c:	8b f3                	mov    %ebx,%esi
    7f76ecc2c15e:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2c161:	d1 e6                	shl    %esi
    7f76ecc2c163:	8b fb                	mov    %ebx,%edi
    7f76ecc2c165:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2c168:	83 e7 01             	and    $0x1,%edi
    7f76ecc2c16b:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2c16e:	41 d1 e0             	shl    %r8d
    7f76ecc2c171:	44 0b c7             	or     %edi,%r8d
    7f76ecc2c174:	89 bd d8 fd ff ff    	mov    %edi,-0x228(%rbp)
    7f76ecc2c17a:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2c17d:	44 0b c7             	or     %edi,%r8d
    7f76ecc2c180:	8b bd d8 fd ff ff    	mov    -0x228(%rbp),%edi
    7f76ecc2c186:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2c189:	44 0b c7             	or     %edi,%r8d
    7f76ecc2c18c:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2c18f:	8b fe                	mov    %esi,%edi
    7f76ecc2c191:	33 fb                	xor    %ebx,%edi
    7f76ecc2c193:	33 f9                	xor    %ecx,%edi
    7f76ecc2c195:	4d 0f b6 87 2e 01 00 	movzbq 0x12e(%r15),%r8
    7f76ecc2c19c:	00 
    7f76ecc2c19d:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2c1a0:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2c1a5:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2c1a8:	44 89 95 d0 fd ff ff 	mov    %r10d,-0x230(%rbp)
    7f76ecc2c1af:	4d 0f b6 97 23 01 00 	movzbq 0x123(%r15),%r10
    7f76ecc2c1b6:	00 
    7f76ecc2c1b7:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2c1ba:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2c1bf:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2c1c2:	33 f0                	xor    %eax,%esi
    7f76ecc2c1c4:	44 89 85 c8 fd ff ff 	mov    %r8d,-0x238(%rbp)
    7f76ecc2c1cb:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2c1cf:	41 d1 e0             	shl    %r8d
    7f76ecc2c1d2:	44 89 8d c0 fd ff ff 	mov    %r9d,-0x240(%rbp)
    7f76ecc2c1d9:	44 8b 8d c8 fd ff ff 	mov    -0x238(%rbp),%r9d
    7f76ecc2c1e0:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2c1e4:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2c1e8:	44 89 8d b8 fd ff ff 	mov    %r9d,-0x248(%rbp)
    7f76ecc2c1ef:	41 d1 e1             	shl    %r9d
    7f76ecc2c1f2:	44 89 9d b0 fd ff ff 	mov    %r11d,-0x250(%rbp)
    7f76ecc2c1f9:	44 8b 9d b8 fd ff ff 	mov    -0x248(%rbp),%r11d
    7f76ecc2c200:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2c203:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2c207:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2c20a:	44 8b 9d b8 fd ff ff 	mov    -0x248(%rbp),%r11d
    7f76ecc2c211:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2c215:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2c218:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2c21b:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2c21e:	44 8b 9d c8 fd ff ff 	mov    -0x238(%rbp),%r11d
    7f76ecc2c225:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2c228:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2c22b:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2c22e:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2c231:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2c234:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2c237:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2c23a:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2c23e:	41 d1 e1             	shl    %r9d
    7f76ecc2c241:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2c244:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2c248:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2c24c:	44 89 9d a8 fd ff ff 	mov    %r11d,-0x258(%rbp)
    7f76ecc2c253:	41 d1 e3             	shl    %r11d
    7f76ecc2c256:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7f76ecc2c25c:	8b 95 a8 fd ff ff    	mov    -0x258(%rbp),%edx
    7f76ecc2c262:	44 0b da             	or     %edx,%r11d
    7f76ecc2c265:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2c268:	44 0b da             	or     %edx,%r11d
    7f76ecc2c26b:	8b 95 a8 fd ff ff    	mov    -0x258(%rbp),%edx
    7f76ecc2c271:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2c274:	44 0b da             	or     %edx,%r11d
    7f76ecc2c277:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2c27a:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2c27d:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2c280:	33 c8                	xor    %eax,%ecx
    7f76ecc2c282:	33 d9                	xor    %ecx,%ebx
    7f76ecc2c284:	33 9d c8 fd ff ff    	xor    -0x238(%rbp),%ebx
    7f76ecc2c28a:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2c28d:	49 0f b6 87 28 01 00 	movzbq 0x128(%r15),%rax
    7f76ecc2c294:	00 
    7f76ecc2c295:	8b c0                	mov    %eax,%eax
    7f76ecc2c297:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c29c:	8b c8                	mov    %eax,%ecx
    7f76ecc2c29e:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2c2a1:	d1 e1                	shl    %ecx
    7f76ecc2c2a3:	8b d0                	mov    %eax,%edx
    7f76ecc2c2a5:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2c2a8:	83 e2 01             	and    $0x1,%edx
    7f76ecc2c2ab:	8b da                	mov    %edx,%ebx
    7f76ecc2c2ad:	d1 e3                	shl    %ebx
    7f76ecc2c2af:	0b da                	or     %edx,%ebx
    7f76ecc2c2b1:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2c2b4:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2c2b8:	41 0b da             	or     %r10d,%ebx
    7f76ecc2c2bb:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2c2be:	0b da                	or     %edx,%ebx
    7f76ecc2c2c0:	33 cb                	xor    %ebx,%ecx
    7f76ecc2c2c2:	49 0f b6 97 2d 01 00 	movzbq 0x12d(%r15),%rdx
    7f76ecc2c2c9:	00 
    7f76ecc2c2ca:	8b d2                	mov    %edx,%edx
    7f76ecc2c2cc:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2c2d1:	8b da                	mov    %edx,%ebx
    7f76ecc2c2d3:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2c2d6:	d1 e3                	shl    %ebx
    7f76ecc2c2d8:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2c2db:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2c2df:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2c2e3:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2c2e6:	41 d1 e3             	shl    %r11d
    7f76ecc2c2e9:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c2ec:	44 89 95 98 fd ff ff 	mov    %r10d,-0x268(%rbp)
    7f76ecc2c2f3:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2c2f7:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c2fa:	44 8b 95 98 fd ff ff 	mov    -0x268(%rbp),%r10d
    7f76ecc2c301:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2c305:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c308:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2c30b:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2c30e:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2c311:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2c314:	4d 0f b6 9f 22 01 00 	movzbq 0x122(%r15),%r11
    7f76ecc2c31b:	00 
    7f76ecc2c31c:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2c31f:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2c324:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2c327:	89 bd 90 fd ff ff    	mov    %edi,-0x270(%rbp)
    7f76ecc2c32d:	49 0f b6 bf 27 01 00 	movzbq 0x127(%r15),%rdi
    7f76ecc2c334:	00 
    7f76ecc2c335:	8b ff                	mov    %edi,%edi
    7f76ecc2c337:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2c33c:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2c33f:	33 d8                	xor    %eax,%ebx
    7f76ecc2c341:	44 89 9d 88 fd ff ff 	mov    %r11d,-0x278(%rbp)
    7f76ecc2c348:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2c34c:	41 d1 e3             	shl    %r11d
    7f76ecc2c34f:	89 b5 80 fd ff ff    	mov    %esi,-0x280(%rbp)
    7f76ecc2c355:	8b b5 88 fd ff ff    	mov    -0x278(%rbp),%esi
    7f76ecc2c35b:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2c35e:	83 e6 01             	and    $0x1,%esi
    7f76ecc2c361:	89 b5 78 fd ff ff    	mov    %esi,-0x288(%rbp)
    7f76ecc2c367:	d1 e6                	shl    %esi
    7f76ecc2c369:	44 89 85 70 fd ff ff 	mov    %r8d,-0x290(%rbp)
    7f76ecc2c370:	44 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%r8d
    7f76ecc2c377:	41 0b f0             	or     %r8d,%esi
    7f76ecc2c37a:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2c37e:	41 0b f0             	or     %r8d,%esi
    7f76ecc2c381:	44 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%r8d
    7f76ecc2c388:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2c38c:	41 0b f0             	or     %r8d,%esi
    7f76ecc2c38f:	44 33 de             	xor    %esi,%r11d
    7f76ecc2c392:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2c395:	44 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%r8d
    7f76ecc2c39c:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2c39f:	33 de                	xor    %esi,%ebx
    7f76ecc2c3a1:	33 df                	xor    %edi,%ebx
    7f76ecc2c3a3:	8b f0                	mov    %eax,%esi
    7f76ecc2c3a5:	33 f2                	xor    %edx,%esi
    7f76ecc2c3a7:	44 33 de             	xor    %esi,%r11d
    7f76ecc2c3aa:	8b f7                	mov    %edi,%esi
    7f76ecc2c3ac:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2c3af:	d1 e6                	shl    %esi
    7f76ecc2c3b1:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2c3b4:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2c3b8:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2c3bc:	44 89 85 68 fd ff ff 	mov    %r8d,-0x298(%rbp)
    7f76ecc2c3c3:	41 d1 e0             	shl    %r8d
    7f76ecc2c3c6:	44 89 8d 60 fd ff ff 	mov    %r9d,-0x2a0(%rbp)
    7f76ecc2c3cd:	44 8b 8d 68 fd ff ff 	mov    -0x298(%rbp),%r9d
    7f76ecc2c3d4:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2c3d7:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2c3db:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2c3de:	44 8b 8d 68 fd ff ff 	mov    -0x298(%rbp),%r9d
    7f76ecc2c3e5:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2c3e9:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2c3ec:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2c3ef:	33 fe                	xor    %esi,%edi
    7f76ecc2c3f1:	44 33 df             	xor    %edi,%r11d
    7f76ecc2c3f4:	33 c8                	xor    %eax,%ecx
    7f76ecc2c3f6:	33 d1                	xor    %ecx,%edx
    7f76ecc2c3f8:	33 95 88 fd ff ff    	xor    -0x278(%rbp),%edx
    7f76ecc2c3fe:	33 f2                	xor    %edx,%esi
    7f76ecc2c400:	49 0f b6 87 2c 01 00 	movzbq 0x12c(%r15),%rax
    7f76ecc2c407:	00 
    7f76ecc2c408:	8b c0                	mov    %eax,%eax
    7f76ecc2c40a:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c40f:	8b c8                	mov    %eax,%ecx
    7f76ecc2c411:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2c414:	d1 e1                	shl    %ecx
    7f76ecc2c416:	8b d0                	mov    %eax,%edx
    7f76ecc2c418:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2c41b:	83 e2 01             	and    $0x1,%edx
    7f76ecc2c41e:	8b fa                	mov    %edx,%edi
    7f76ecc2c420:	d1 e7                	shl    %edi
    7f76ecc2c422:	0b fa                	or     %edx,%edi
    7f76ecc2c424:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2c427:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2c42b:	41 0b f8             	or     %r8d,%edi
    7f76ecc2c42e:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2c431:	0b fa                	or     %edx,%edi
    7f76ecc2c433:	33 cf                	xor    %edi,%ecx
    7f76ecc2c435:	49 0f b6 97 21 01 00 	movzbq 0x121(%r15),%rdx
    7f76ecc2c43c:	00 
    7f76ecc2c43d:	8b d2                	mov    %edx,%edx
    7f76ecc2c43f:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2c444:	8b fa                	mov    %edx,%edi
    7f76ecc2c446:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2c449:	d1 e7                	shl    %edi
    7f76ecc2c44b:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2c44e:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2c452:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2c456:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2c459:	41 d1 e1             	shl    %r9d
    7f76ecc2c45c:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2c45f:	44 89 85 58 fd ff ff 	mov    %r8d,-0x2a8(%rbp)
    7f76ecc2c466:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2c46a:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2c46d:	44 8b 85 58 fd ff ff 	mov    -0x2a8(%rbp),%r8d
    7f76ecc2c474:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2c478:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2c47b:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2c47e:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2c481:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2c484:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2c487:	4d 0f b6 8f 26 01 00 	movzbq 0x126(%r15),%r9
    7f76ecc2c48e:	00 
    7f76ecc2c48f:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2c492:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2c497:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2c49a:	44 89 95 50 fd ff ff 	mov    %r10d,-0x2b0(%rbp)
    7f76ecc2c4a1:	4d 0f b6 97 2b 01 00 	movzbq 0x12b(%r15),%r10
    7f76ecc2c4a8:	00 
    7f76ecc2c4a9:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2c4ac:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2c4b1:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2c4b4:	33 f8                	xor    %eax,%edi
    7f76ecc2c4b6:	44 89 8d 48 fd ff ff 	mov    %r9d,-0x2b8(%rbp)
    7f76ecc2c4bd:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2c4c1:	41 d1 e1             	shl    %r9d
    7f76ecc2c4c4:	89 9d 40 fd ff ff    	mov    %ebx,-0x2c0(%rbp)
    7f76ecc2c4ca:	8b 9d 48 fd ff ff    	mov    -0x2b8(%rbp),%ebx
    7f76ecc2c4d0:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c4d3:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c4d6:	89 9d 38 fd ff ff    	mov    %ebx,-0x2c8(%rbp)
    7f76ecc2c4dc:	d1 e3                	shl    %ebx
    7f76ecc2c4de:	44 89 9d 30 fd ff ff 	mov    %r11d,-0x2d0(%rbp)
    7f76ecc2c4e5:	44 8b 9d 38 fd ff ff 	mov    -0x2c8(%rbp),%r11d
    7f76ecc2c4ec:	41 0b db             	or     %r11d,%ebx
    7f76ecc2c4ef:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2c4f3:	41 0b db             	or     %r11d,%ebx
    7f76ecc2c4f6:	44 8b 9d 38 fd ff ff 	mov    -0x2c8(%rbp),%r11d
    7f76ecc2c4fd:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2c501:	41 0b db             	or     %r11d,%ebx
    7f76ecc2c504:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2c507:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2c50a:	44 8b 9d 48 fd ff ff 	mov    -0x2b8(%rbp),%r11d
    7f76ecc2c511:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2c514:	33 fb                	xor    %ebx,%edi
    7f76ecc2c516:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2c519:	8b d8                	mov    %eax,%ebx
    7f76ecc2c51b:	33 da                	xor    %edx,%ebx
    7f76ecc2c51d:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2c520:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2c523:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2c526:	d1 e3                	shl    %ebx
    7f76ecc2c528:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2c52b:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2c52f:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2c533:	44 89 9d 28 fd ff ff 	mov    %r11d,-0x2d8(%rbp)
    7f76ecc2c53a:	41 d1 e3             	shl    %r11d
    7f76ecc2c53d:	89 b5 20 fd ff ff    	mov    %esi,-0x2e0(%rbp)
    7f76ecc2c543:	8b b5 28 fd ff ff    	mov    -0x2d8(%rbp),%esi
    7f76ecc2c549:	44 0b de             	or     %esi,%r11d
    7f76ecc2c54c:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2c54f:	44 0b de             	or     %esi,%r11d
    7f76ecc2c552:	8b b5 28 fd ff ff    	mov    -0x2d8(%rbp),%esi
    7f76ecc2c558:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2c55b:	44 0b de             	or     %esi,%r11d
    7f76ecc2c55e:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2c561:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2c564:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2c567:	33 c8                	xor    %eax,%ecx
    7f76ecc2c569:	33 d1                	xor    %ecx,%edx
    7f76ecc2c56b:	33 95 48 fd ff ff    	xor    -0x2b8(%rbp),%edx
    7f76ecc2c571:	33 da                	xor    %edx,%ebx
    7f76ecc2c573:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7f76ecc2c579:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2c57c:	0b 85 d0 fd ff ff    	or     -0x230(%rbp),%eax
    7f76ecc2c582:	8b 8d b0 fd ff ff    	mov    -0x250(%rbp),%ecx
    7f76ecc2c588:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2c58b:	0b c1                	or     %ecx,%eax
    7f76ecc2c58d:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7f76ecc2c593:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2c596:	0b c1                	or     %ecx,%eax
    7f76ecc2c598:	8b 8d 90 fd ff ff    	mov    -0x270(%rbp),%ecx
    7f76ecc2c59e:	8b c9                	mov    %ecx,%ecx
    7f76ecc2c5a0:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2c5a4:	8b c0                	mov    %eax,%eax
    7f76ecc2c5a6:	48 0b c8             	or     %rax,%rcx
    7f76ecc2c5a9:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7f76ecc2c5af:	8b c0                	mov    %eax,%eax
    7f76ecc2c5b1:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2c5b5:	48 0b c8             	or     %rax,%rcx
    7f76ecc2c5b8:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7f76ecc2c5be:	8b c0                	mov    %eax,%eax
    7f76ecc2c5c0:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2c5c4:	48 0b c8             	or     %rax,%rcx
    7f76ecc2c5c7:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7f76ecc2c5cd:	8b c0                	mov    %eax,%eax
    7f76ecc2c5cf:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2c5d3:	48 0b c8             	or     %rax,%rcx
    7f76ecc2c5d6:	49 89 8f 80 02 00 00 	mov    %rcx,0x280(%r15)
    7f76ecc2c5dd:	8b 85 40 fd ff ff    	mov    -0x2c0(%rbp),%eax
    7f76ecc2c5e3:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2c5e6:	0b 85 50 fd ff ff    	or     -0x2b0(%rbp),%eax
    7f76ecc2c5ec:	8b 8d 30 fd ff ff    	mov    -0x2d0(%rbp),%ecx
    7f76ecc2c5f2:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2c5f5:	0b c1                	or     %ecx,%eax
    7f76ecc2c5f7:	8b 8d 20 fd ff ff    	mov    -0x2e0(%rbp),%ecx
    7f76ecc2c5fd:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2c600:	0b c1                	or     %ecx,%eax
    7f76ecc2c602:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2c605:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2c609:	8b c0                	mov    %eax,%eax
    7f76ecc2c60b:	4c 0b c0             	or     %rax,%r8
    7f76ecc2c60e:	8b ff                	mov    %edi,%edi
    7f76ecc2c610:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2c614:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2c617:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2c61a:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2c61e:	4d 0b c1             	or     %r9,%r8
    7f76ecc2c621:	8b db                	mov    %ebx,%ebx
    7f76ecc2c623:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2c627:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2c62a:	4d 89 87 88 02 00 00 	mov    %r8,0x288(%r15)
    7f76ecc2c631:	8b 85 f0 fd ff ff    	mov    -0x210(%rbp),%eax
    7f76ecc2c637:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2c63c:	8b c0                	mov    %eax,%eax
    7f76ecc2c63e:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c643:	8b 8d f0 fd ff ff    	mov    -0x210(%rbp),%ecx
    7f76ecc2c649:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2c64c:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2c652:	8b c9                	mov    %ecx,%ecx
    7f76ecc2c654:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2c659:	8b 95 f0 fd ff ff    	mov    -0x210(%rbp),%edx
    7f76ecc2c65f:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2c662:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2c668:	8b d2                	mov    %edx,%edx
    7f76ecc2c66a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2c66f:	8b 9d f0 fd ff ff    	mov    -0x210(%rbp),%ebx
    7f76ecc2c675:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2c678:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2c67e:	8b db                	mov    %ebx,%ebx
    7f76ecc2c680:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2c685:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2c688:	0b da                	or     %edx,%ebx
    7f76ecc2c68a:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2c68d:	0b d9                	or     %ecx,%ebx
    7f76ecc2c68f:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2c692:	0b d8                	or     %eax,%ebx
    7f76ecc2c694:	83 f3 04             	xor    $0x4,%ebx
    7f76ecc2c697:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7f76ecc2c69d:	33 d8                	xor    %eax,%ebx
    7f76ecc2c69f:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7f76ecc2c6a5:	33 c3                	xor    %ebx,%eax
    7f76ecc2c6a7:	8b 8d e0 fd ff ff    	mov    -0x220(%rbp),%ecx
    7f76ecc2c6ad:	33 c8                	xor    %eax,%ecx
    7f76ecc2c6af:	8b 95 f0 fd ff ff    	mov    -0x210(%rbp),%edx
    7f76ecc2c6b5:	33 d1                	xor    %ecx,%edx
    7f76ecc2c6b7:	8b f0                	mov    %eax,%esi
    7f76ecc2c6b9:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2c6bd:	8b fb                	mov    %ebx,%edi
    7f76ecc2c6bf:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2c6c2:	49 89 b7 e0 01 00 00 	mov    %rsi,0x1e0(%r15)
    7f76ecc2c6c9:	8b f2                	mov    %edx,%esi
    7f76ecc2c6cb:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2c6cf:	8b f9                	mov    %ecx,%edi
    7f76ecc2c6d1:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2c6d4:	49 89 b7 e8 01 00 00 	mov    %rsi,0x1e8(%r15)
    7f76ecc2c6db:	49 8b b7 80 02 00 00 	mov    0x280(%r15),%rsi
    7f76ecc2c6e2:	49 8b bf e0 01 00 00 	mov    0x1e0(%r15),%rdi
    7f76ecc2c6e9:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2c6ec:	49 89 b7 30 03 00 00 	mov    %rsi,0x330(%r15)
    7f76ecc2c6f3:	49 8b b7 88 02 00 00 	mov    0x288(%r15),%rsi
    7f76ecc2c6fa:	49 8b bf e8 01 00 00 	mov    0x1e8(%r15),%rdi
    7f76ecc2c701:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2c704:	49 89 b7 38 03 00 00 	mov    %rsi,0x338(%r15)
    7f76ecc2c70b:	49 0f b6 b7 30 01 00 	movzbq 0x130(%r15),%rsi
    7f76ecc2c712:	00 
    7f76ecc2c713:	8b f6                	mov    %esi,%esi
    7f76ecc2c715:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2c71a:	8b fe                	mov    %esi,%edi
    7f76ecc2c71c:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2c71f:	d1 e7                	shl    %edi
    7f76ecc2c721:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2c724:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2c728:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2c72c:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2c72f:	41 d1 e1             	shl    %r9d
    7f76ecc2c732:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2c735:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2c738:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2c73c:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2c73f:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2c743:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2c746:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2c749:	4d 0f b6 87 35 01 00 	movzbq 0x135(%r15),%r8
    7f76ecc2c750:	00 
    7f76ecc2c751:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2c754:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2c759:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2c75c:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2c760:	41 d1 e1             	shl    %r9d
    7f76ecc2c763:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2c766:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2c76a:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2c76e:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2c771:	41 d1 e3             	shl    %r11d
    7f76ecc2c774:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c777:	44 89 95 18 fd ff ff 	mov    %r10d,-0x2e8(%rbp)
    7f76ecc2c77e:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2c782:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c785:	44 8b 95 18 fd ff ff 	mov    -0x2e8(%rbp),%r10d
    7f76ecc2c78c:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2c790:	45 0b da             	or     %r10d,%r11d
    7f76ecc2c793:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2c796:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2c799:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2c79c:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2c79f:	4d 0f b6 9f 3a 01 00 	movzbq 0x13a(%r15),%r11
    7f76ecc2c7a6:	00 
    7f76ecc2c7a7:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2c7aa:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2c7af:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2c7b2:	89 85 10 fd ff ff    	mov    %eax,-0x2f0(%rbp)
    7f76ecc2c7b8:	49 0f b6 87 3f 01 00 	movzbq 0x13f(%r15),%rax
    7f76ecc2c7bf:	00 
    7f76ecc2c7c0:	8b c0                	mov    %eax,%eax
    7f76ecc2c7c2:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c7c7:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2c7ca:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2c7cd:	44 89 9d 08 fd ff ff 	mov    %r11d,-0x2f8(%rbp)
    7f76ecc2c7d4:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2c7d8:	41 d1 e3             	shl    %r11d
    7f76ecc2c7db:	89 9d 00 fd ff ff    	mov    %ebx,-0x300(%rbp)
    7f76ecc2c7e1:	8b 9d 08 fd ff ff    	mov    -0x2f8(%rbp),%ebx
    7f76ecc2c7e7:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c7ea:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c7ed:	89 9d f8 fc ff ff    	mov    %ebx,-0x308(%rbp)
    7f76ecc2c7f3:	d1 e3                	shl    %ebx
    7f76ecc2c7f5:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7f76ecc2c7fb:	8b 95 f8 fc ff ff    	mov    -0x308(%rbp),%edx
    7f76ecc2c801:	0b da                	or     %edx,%ebx
    7f76ecc2c803:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2c806:	0b da                	or     %edx,%ebx
    7f76ecc2c808:	8b 95 f8 fc ff ff    	mov    -0x308(%rbp),%edx
    7f76ecc2c80e:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2c811:	0b da                	or     %edx,%ebx
    7f76ecc2c813:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2c816:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2c819:	8b 9d 08 fd ff ff    	mov    -0x2f8(%rbp),%ebx
    7f76ecc2c81f:	33 d3                	xor    %ebx,%edx
    7f76ecc2c821:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2c824:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2c827:	8b d6                	mov    %esi,%edx
    7f76ecc2c829:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2c82c:	44 33 da             	xor    %edx,%r11d
    7f76ecc2c82f:	8b d0                	mov    %eax,%edx
    7f76ecc2c831:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2c834:	d1 e2                	shl    %edx
    7f76ecc2c836:	8b d8                	mov    %eax,%ebx
    7f76ecc2c838:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c83b:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c83e:	89 9d e8 fc ff ff    	mov    %ebx,-0x318(%rbp)
    7f76ecc2c844:	d1 e3                	shl    %ebx
    7f76ecc2c846:	89 8d e0 fc ff ff    	mov    %ecx,-0x320(%rbp)
    7f76ecc2c84c:	8b 8d e8 fc ff ff    	mov    -0x318(%rbp),%ecx
    7f76ecc2c852:	0b d9                	or     %ecx,%ebx
    7f76ecc2c854:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2c857:	0b d9                	or     %ecx,%ebx
    7f76ecc2c859:	8b 8d e8 fc ff ff    	mov    -0x318(%rbp),%ecx
    7f76ecc2c85f:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2c862:	0b d9                	or     %ecx,%ebx
    7f76ecc2c864:	33 d3                	xor    %ebx,%edx
    7f76ecc2c866:	33 c2                	xor    %edx,%eax
    7f76ecc2c868:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2c86b:	33 fe                	xor    %esi,%edi
    7f76ecc2c86d:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2c870:	44 33 85 08 fd ff ff 	xor    -0x2f8(%rbp),%r8d
    7f76ecc2c877:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2c87a:	49 0f b6 87 34 01 00 	movzbq 0x134(%r15),%rax
    7f76ecc2c881:	00 
    7f76ecc2c882:	8b c0                	mov    %eax,%eax
    7f76ecc2c884:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c889:	8b c8                	mov    %eax,%ecx
    7f76ecc2c88b:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2c88e:	d1 e1                	shl    %ecx
    7f76ecc2c890:	8b d8                	mov    %eax,%ebx
    7f76ecc2c892:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2c895:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2c898:	8b f3                	mov    %ebx,%esi
    7f76ecc2c89a:	d1 e6                	shl    %esi
    7f76ecc2c89c:	0b f3                	or     %ebx,%esi
    7f76ecc2c89e:	8b fb                	mov    %ebx,%edi
    7f76ecc2c8a0:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2c8a3:	0b f7                	or     %edi,%esi
    7f76ecc2c8a5:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2c8a8:	0b f3                	or     %ebx,%esi
    7f76ecc2c8aa:	33 ce                	xor    %esi,%ecx
    7f76ecc2c8ac:	49 0f b6 9f 39 01 00 	movzbq 0x139(%r15),%rbx
    7f76ecc2c8b3:	00 
    7f76ecc2c8b4:	8b db                	mov    %ebx,%ebx
    7f76ecc2c8b6:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2c8bb:	8b f3                	mov    %ebx,%esi
    7f76ecc2c8bd:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2c8c0:	d1 e6                	shl    %esi
    7f76ecc2c8c2:	8b fb                	mov    %ebx,%edi
    7f76ecc2c8c4:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2c8c7:	83 e7 01             	and    $0x1,%edi
    7f76ecc2c8ca:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2c8cd:	41 d1 e0             	shl    %r8d
    7f76ecc2c8d0:	44 0b c7             	or     %edi,%r8d
    7f76ecc2c8d3:	89 bd d8 fc ff ff    	mov    %edi,-0x328(%rbp)
    7f76ecc2c8d9:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2c8dc:	44 0b c7             	or     %edi,%r8d
    7f76ecc2c8df:	8b bd d8 fc ff ff    	mov    -0x328(%rbp),%edi
    7f76ecc2c8e5:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2c8e8:	44 0b c7             	or     %edi,%r8d
    7f76ecc2c8eb:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2c8ee:	8b fe                	mov    %esi,%edi
    7f76ecc2c8f0:	33 fb                	xor    %ebx,%edi
    7f76ecc2c8f2:	33 f9                	xor    %ecx,%edi
    7f76ecc2c8f4:	4d 0f b6 87 3e 01 00 	movzbq 0x13e(%r15),%r8
    7f76ecc2c8fb:	00 
    7f76ecc2c8fc:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2c8ff:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2c904:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2c907:	44 89 95 d0 fc ff ff 	mov    %r10d,-0x330(%rbp)
    7f76ecc2c90e:	4d 0f b6 97 33 01 00 	movzbq 0x133(%r15),%r10
    7f76ecc2c915:	00 
    7f76ecc2c916:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2c919:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2c91e:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2c921:	33 f0                	xor    %eax,%esi
    7f76ecc2c923:	44 89 85 c8 fc ff ff 	mov    %r8d,-0x338(%rbp)
    7f76ecc2c92a:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2c92e:	41 d1 e0             	shl    %r8d
    7f76ecc2c931:	44 89 8d c0 fc ff ff 	mov    %r9d,-0x340(%rbp)
    7f76ecc2c938:	44 8b 8d c8 fc ff ff 	mov    -0x338(%rbp),%r9d
    7f76ecc2c93f:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2c943:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2c947:	44 89 8d b8 fc ff ff 	mov    %r9d,-0x348(%rbp)
    7f76ecc2c94e:	41 d1 e1             	shl    %r9d
    7f76ecc2c951:	44 89 9d b0 fc ff ff 	mov    %r11d,-0x350(%rbp)
    7f76ecc2c958:	44 8b 9d b8 fc ff ff 	mov    -0x348(%rbp),%r11d
    7f76ecc2c95f:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2c962:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2c966:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2c969:	44 8b 9d b8 fc ff ff 	mov    -0x348(%rbp),%r11d
    7f76ecc2c970:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2c974:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2c977:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2c97a:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2c97d:	44 8b 9d c8 fc ff ff 	mov    -0x338(%rbp),%r11d
    7f76ecc2c984:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2c987:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2c98a:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2c98d:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2c990:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2c993:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2c996:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2c999:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2c99d:	41 d1 e1             	shl    %r9d
    7f76ecc2c9a0:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2c9a3:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2c9a7:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2c9ab:	44 89 9d a8 fc ff ff 	mov    %r11d,-0x358(%rbp)
    7f76ecc2c9b2:	41 d1 e3             	shl    %r11d
    7f76ecc2c9b5:	89 95 a0 fc ff ff    	mov    %edx,-0x360(%rbp)
    7f76ecc2c9bb:	8b 95 a8 fc ff ff    	mov    -0x358(%rbp),%edx
    7f76ecc2c9c1:	44 0b da             	or     %edx,%r11d
    7f76ecc2c9c4:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2c9c7:	44 0b da             	or     %edx,%r11d
    7f76ecc2c9ca:	8b 95 a8 fc ff ff    	mov    -0x358(%rbp),%edx
    7f76ecc2c9d0:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2c9d3:	44 0b da             	or     %edx,%r11d
    7f76ecc2c9d6:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2c9d9:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2c9dc:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2c9df:	33 c8                	xor    %eax,%ecx
    7f76ecc2c9e1:	33 d9                	xor    %ecx,%ebx
    7f76ecc2c9e3:	33 9d c8 fc ff ff    	xor    -0x338(%rbp),%ebx
    7f76ecc2c9e9:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2c9ec:	49 0f b6 87 38 01 00 	movzbq 0x138(%r15),%rax
    7f76ecc2c9f3:	00 
    7f76ecc2c9f4:	8b c0                	mov    %eax,%eax
    7f76ecc2c9f6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2c9fb:	8b c8                	mov    %eax,%ecx
    7f76ecc2c9fd:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2ca00:	d1 e1                	shl    %ecx
    7f76ecc2ca02:	8b d0                	mov    %eax,%edx
    7f76ecc2ca04:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2ca07:	83 e2 01             	and    $0x1,%edx
    7f76ecc2ca0a:	8b da                	mov    %edx,%ebx
    7f76ecc2ca0c:	d1 e3                	shl    %ebx
    7f76ecc2ca0e:	0b da                	or     %edx,%ebx
    7f76ecc2ca10:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2ca13:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2ca17:	41 0b da             	or     %r10d,%ebx
    7f76ecc2ca1a:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2ca1d:	0b da                	or     %edx,%ebx
    7f76ecc2ca1f:	33 cb                	xor    %ebx,%ecx
    7f76ecc2ca21:	49 0f b6 97 3d 01 00 	movzbq 0x13d(%r15),%rdx
    7f76ecc2ca28:	00 
    7f76ecc2ca29:	8b d2                	mov    %edx,%edx
    7f76ecc2ca2b:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2ca30:	8b da                	mov    %edx,%ebx
    7f76ecc2ca32:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2ca35:	d1 e3                	shl    %ebx
    7f76ecc2ca37:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2ca3a:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2ca3e:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2ca42:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2ca45:	41 d1 e3             	shl    %r11d
    7f76ecc2ca48:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ca4b:	44 89 95 98 fc ff ff 	mov    %r10d,-0x368(%rbp)
    7f76ecc2ca52:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2ca56:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ca59:	44 8b 95 98 fc ff ff 	mov    -0x368(%rbp),%r10d
    7f76ecc2ca60:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2ca64:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ca67:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2ca6a:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2ca6d:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2ca70:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2ca73:	4d 0f b6 9f 32 01 00 	movzbq 0x132(%r15),%r11
    7f76ecc2ca7a:	00 
    7f76ecc2ca7b:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2ca7e:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2ca83:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2ca86:	89 bd 90 fc ff ff    	mov    %edi,-0x370(%rbp)
    7f76ecc2ca8c:	49 0f b6 bf 37 01 00 	movzbq 0x137(%r15),%rdi
    7f76ecc2ca93:	00 
    7f76ecc2ca94:	8b ff                	mov    %edi,%edi
    7f76ecc2ca96:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2ca9b:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2ca9e:	33 d8                	xor    %eax,%ebx
    7f76ecc2caa0:	44 89 9d 88 fc ff ff 	mov    %r11d,-0x378(%rbp)
    7f76ecc2caa7:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2caab:	41 d1 e3             	shl    %r11d
    7f76ecc2caae:	89 b5 80 fc ff ff    	mov    %esi,-0x380(%rbp)
    7f76ecc2cab4:	8b b5 88 fc ff ff    	mov    -0x378(%rbp),%esi
    7f76ecc2caba:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2cabd:	83 e6 01             	and    $0x1,%esi
    7f76ecc2cac0:	89 b5 78 fc ff ff    	mov    %esi,-0x388(%rbp)
    7f76ecc2cac6:	d1 e6                	shl    %esi
    7f76ecc2cac8:	44 89 85 70 fc ff ff 	mov    %r8d,-0x390(%rbp)
    7f76ecc2cacf:	44 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%r8d
    7f76ecc2cad6:	41 0b f0             	or     %r8d,%esi
    7f76ecc2cad9:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2cadd:	41 0b f0             	or     %r8d,%esi
    7f76ecc2cae0:	44 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%r8d
    7f76ecc2cae7:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2caeb:	41 0b f0             	or     %r8d,%esi
    7f76ecc2caee:	44 33 de             	xor    %esi,%r11d
    7f76ecc2caf1:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2caf4:	44 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%r8d
    7f76ecc2cafb:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2cafe:	33 de                	xor    %esi,%ebx
    7f76ecc2cb00:	33 df                	xor    %edi,%ebx
    7f76ecc2cb02:	8b f0                	mov    %eax,%esi
    7f76ecc2cb04:	33 f2                	xor    %edx,%esi
    7f76ecc2cb06:	44 33 de             	xor    %esi,%r11d
    7f76ecc2cb09:	8b f7                	mov    %edi,%esi
    7f76ecc2cb0b:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2cb0e:	d1 e6                	shl    %esi
    7f76ecc2cb10:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2cb13:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2cb17:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2cb1b:	44 89 85 68 fc ff ff 	mov    %r8d,-0x398(%rbp)
    7f76ecc2cb22:	41 d1 e0             	shl    %r8d
    7f76ecc2cb25:	44 89 8d 60 fc ff ff 	mov    %r9d,-0x3a0(%rbp)
    7f76ecc2cb2c:	44 8b 8d 68 fc ff ff 	mov    -0x398(%rbp),%r9d
    7f76ecc2cb33:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2cb36:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2cb3a:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2cb3d:	44 8b 8d 68 fc ff ff 	mov    -0x398(%rbp),%r9d
    7f76ecc2cb44:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2cb48:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2cb4b:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2cb4e:	33 fe                	xor    %esi,%edi
    7f76ecc2cb50:	44 33 df             	xor    %edi,%r11d
    7f76ecc2cb53:	33 c8                	xor    %eax,%ecx
    7f76ecc2cb55:	33 d1                	xor    %ecx,%edx
    7f76ecc2cb57:	33 95 88 fc ff ff    	xor    -0x378(%rbp),%edx
    7f76ecc2cb5d:	33 f2                	xor    %edx,%esi
    7f76ecc2cb5f:	49 0f b6 87 3c 01 00 	movzbq 0x13c(%r15),%rax
    7f76ecc2cb66:	00 
    7f76ecc2cb67:	8b c0                	mov    %eax,%eax
    7f76ecc2cb69:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2cb6e:	8b c8                	mov    %eax,%ecx
    7f76ecc2cb70:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2cb73:	d1 e1                	shl    %ecx
    7f76ecc2cb75:	8b d0                	mov    %eax,%edx
    7f76ecc2cb77:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2cb7a:	83 e2 01             	and    $0x1,%edx
    7f76ecc2cb7d:	8b fa                	mov    %edx,%edi
    7f76ecc2cb7f:	d1 e7                	shl    %edi
    7f76ecc2cb81:	0b fa                	or     %edx,%edi
    7f76ecc2cb83:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2cb86:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2cb8a:	41 0b f8             	or     %r8d,%edi
    7f76ecc2cb8d:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2cb90:	0b fa                	or     %edx,%edi
    7f76ecc2cb92:	33 cf                	xor    %edi,%ecx
    7f76ecc2cb94:	49 0f b6 97 31 01 00 	movzbq 0x131(%r15),%rdx
    7f76ecc2cb9b:	00 
    7f76ecc2cb9c:	8b d2                	mov    %edx,%edx
    7f76ecc2cb9e:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2cba3:	8b fa                	mov    %edx,%edi
    7f76ecc2cba5:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2cba8:	d1 e7                	shl    %edi
    7f76ecc2cbaa:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2cbad:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2cbb1:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2cbb5:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2cbb8:	41 d1 e1             	shl    %r9d
    7f76ecc2cbbb:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2cbbe:	44 89 85 58 fc ff ff 	mov    %r8d,-0x3a8(%rbp)
    7f76ecc2cbc5:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2cbc9:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2cbcc:	44 8b 85 58 fc ff ff 	mov    -0x3a8(%rbp),%r8d
    7f76ecc2cbd3:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2cbd7:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2cbda:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2cbdd:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2cbe0:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2cbe3:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2cbe6:	4d 0f b6 8f 36 01 00 	movzbq 0x136(%r15),%r9
    7f76ecc2cbed:	00 
    7f76ecc2cbee:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2cbf1:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2cbf6:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2cbf9:	44 89 95 50 fc ff ff 	mov    %r10d,-0x3b0(%rbp)
    7f76ecc2cc00:	4d 0f b6 97 3b 01 00 	movzbq 0x13b(%r15),%r10
    7f76ecc2cc07:	00 
    7f76ecc2cc08:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2cc0b:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2cc10:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2cc13:	33 f8                	xor    %eax,%edi
    7f76ecc2cc15:	44 89 8d 48 fc ff ff 	mov    %r9d,-0x3b8(%rbp)
    7f76ecc2cc1c:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2cc20:	41 d1 e1             	shl    %r9d
    7f76ecc2cc23:	89 9d 40 fc ff ff    	mov    %ebx,-0x3c0(%rbp)
    7f76ecc2cc29:	8b 9d 48 fc ff ff    	mov    -0x3b8(%rbp),%ebx
    7f76ecc2cc2f:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2cc32:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2cc35:	89 9d 38 fc ff ff    	mov    %ebx,-0x3c8(%rbp)
    7f76ecc2cc3b:	d1 e3                	shl    %ebx
    7f76ecc2cc3d:	44 89 9d 30 fc ff ff 	mov    %r11d,-0x3d0(%rbp)
    7f76ecc2cc44:	44 8b 9d 38 fc ff ff 	mov    -0x3c8(%rbp),%r11d
    7f76ecc2cc4b:	41 0b db             	or     %r11d,%ebx
    7f76ecc2cc4e:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2cc52:	41 0b db             	or     %r11d,%ebx
    7f76ecc2cc55:	44 8b 9d 38 fc ff ff 	mov    -0x3c8(%rbp),%r11d
    7f76ecc2cc5c:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2cc60:	41 0b db             	or     %r11d,%ebx
    7f76ecc2cc63:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2cc66:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2cc69:	44 8b 9d 48 fc ff ff 	mov    -0x3b8(%rbp),%r11d
    7f76ecc2cc70:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2cc73:	33 fb                	xor    %ebx,%edi
    7f76ecc2cc75:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2cc78:	8b d8                	mov    %eax,%ebx
    7f76ecc2cc7a:	33 da                	xor    %edx,%ebx
    7f76ecc2cc7c:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2cc7f:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2cc82:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2cc85:	d1 e3                	shl    %ebx
    7f76ecc2cc87:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2cc8a:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2cc8e:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2cc92:	44 89 9d 28 fc ff ff 	mov    %r11d,-0x3d8(%rbp)
    7f76ecc2cc99:	41 d1 e3             	shl    %r11d
    7f76ecc2cc9c:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7f76ecc2cca2:	8b b5 28 fc ff ff    	mov    -0x3d8(%rbp),%esi
    7f76ecc2cca8:	44 0b de             	or     %esi,%r11d
    7f76ecc2ccab:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2ccae:	44 0b de             	or     %esi,%r11d
    7f76ecc2ccb1:	8b b5 28 fc ff ff    	mov    -0x3d8(%rbp),%esi
    7f76ecc2ccb7:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2ccba:	44 0b de             	or     %esi,%r11d
    7f76ecc2ccbd:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2ccc0:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2ccc3:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2ccc6:	33 c8                	xor    %eax,%ecx
    7f76ecc2ccc8:	33 d1                	xor    %ecx,%edx
    7f76ecc2ccca:	33 95 48 fc ff ff    	xor    -0x3b8(%rbp),%edx
    7f76ecc2ccd0:	33 da                	xor    %edx,%ebx
    7f76ecc2ccd2:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7f76ecc2ccd8:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2ccdb:	0b 85 d0 fc ff ff    	or     -0x330(%rbp),%eax
    7f76ecc2cce1:	8b 8d b0 fc ff ff    	mov    -0x350(%rbp),%ecx
    7f76ecc2cce7:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2ccea:	0b c1                	or     %ecx,%eax
    7f76ecc2ccec:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7f76ecc2ccf2:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2ccf5:	0b c1                	or     %ecx,%eax
    7f76ecc2ccf7:	8b 8d 90 fc ff ff    	mov    -0x370(%rbp),%ecx
    7f76ecc2ccfd:	8b c9                	mov    %ecx,%ecx
    7f76ecc2ccff:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2cd03:	8b c0                	mov    %eax,%eax
    7f76ecc2cd05:	48 0b c8             	or     %rax,%rcx
    7f76ecc2cd08:	8b 85 80 fc ff ff    	mov    -0x380(%rbp),%eax
    7f76ecc2cd0e:	8b c0                	mov    %eax,%eax
    7f76ecc2cd10:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2cd14:	48 0b c8             	or     %rax,%rcx
    7f76ecc2cd17:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7f76ecc2cd1d:	8b c0                	mov    %eax,%eax
    7f76ecc2cd1f:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2cd23:	48 0b c8             	or     %rax,%rcx
    7f76ecc2cd26:	8b 85 60 fc ff ff    	mov    -0x3a0(%rbp),%eax
    7f76ecc2cd2c:	8b c0                	mov    %eax,%eax
    7f76ecc2cd2e:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2cd32:	48 0b c8             	or     %rax,%rcx
    7f76ecc2cd35:	49 89 8f 90 02 00 00 	mov    %rcx,0x290(%r15)
    7f76ecc2cd3c:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7f76ecc2cd42:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2cd45:	0b 85 50 fc ff ff    	or     -0x3b0(%rbp),%eax
    7f76ecc2cd4b:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7f76ecc2cd51:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2cd54:	0b c1                	or     %ecx,%eax
    7f76ecc2cd56:	8b 8d 20 fc ff ff    	mov    -0x3e0(%rbp),%ecx
    7f76ecc2cd5c:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2cd5f:	0b c1                	or     %ecx,%eax
    7f76ecc2cd61:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2cd64:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2cd68:	8b c0                	mov    %eax,%eax
    7f76ecc2cd6a:	4c 0b c0             	or     %rax,%r8
    7f76ecc2cd6d:	8b ff                	mov    %edi,%edi
    7f76ecc2cd6f:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2cd73:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2cd76:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2cd79:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2cd7d:	4d 0b c1             	or     %r9,%r8
    7f76ecc2cd80:	8b db                	mov    %ebx,%ebx
    7f76ecc2cd82:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2cd86:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2cd89:	4d 89 87 98 02 00 00 	mov    %r8,0x298(%r15)
    7f76ecc2cd90:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7f76ecc2cd96:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2cd9b:	8b c0                	mov    %eax,%eax
    7f76ecc2cd9d:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2cda2:	8b 8d f0 fc ff ff    	mov    -0x310(%rbp),%ecx
    7f76ecc2cda8:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2cdab:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2cdb1:	8b c9                	mov    %ecx,%ecx
    7f76ecc2cdb3:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2cdb8:	8b 95 f0 fc ff ff    	mov    -0x310(%rbp),%edx
    7f76ecc2cdbe:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2cdc1:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2cdc7:	8b d2                	mov    %edx,%edx
    7f76ecc2cdc9:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2cdce:	8b 9d f0 fc ff ff    	mov    -0x310(%rbp),%ebx
    7f76ecc2cdd4:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2cdd7:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2cddd:	8b db                	mov    %ebx,%ebx
    7f76ecc2cddf:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2cde4:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2cde7:	0b da                	or     %edx,%ebx
    7f76ecc2cde9:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2cdec:	0b d9                	or     %ecx,%ebx
    7f76ecc2cdee:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2cdf1:	0b d8                	or     %eax,%ebx
    7f76ecc2cdf3:	83 f3 08             	xor    $0x8,%ebx
    7f76ecc2cdf6:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7f76ecc2cdfc:	33 d8                	xor    %eax,%ebx
    7f76ecc2cdfe:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7f76ecc2ce04:	33 c3                	xor    %ebx,%eax
    7f76ecc2ce06:	8b 8d e0 fc ff ff    	mov    -0x320(%rbp),%ecx
    7f76ecc2ce0c:	33 c8                	xor    %eax,%ecx
    7f76ecc2ce0e:	8b 95 f0 fc ff ff    	mov    -0x310(%rbp),%edx
    7f76ecc2ce14:	33 d1                	xor    %ecx,%edx
    7f76ecc2ce16:	8b f0                	mov    %eax,%esi
    7f76ecc2ce18:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2ce1c:	8b fb                	mov    %ebx,%edi
    7f76ecc2ce1e:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2ce21:	49 89 b7 f0 01 00 00 	mov    %rsi,0x1f0(%r15)
    7f76ecc2ce28:	8b f2                	mov    %edx,%esi
    7f76ecc2ce2a:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2ce2e:	8b f9                	mov    %ecx,%edi
    7f76ecc2ce30:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2ce33:	49 89 b7 f8 01 00 00 	mov    %rsi,0x1f8(%r15)
    7f76ecc2ce3a:	49 8b b7 90 02 00 00 	mov    0x290(%r15),%rsi
    7f76ecc2ce41:	49 8b bf f0 01 00 00 	mov    0x1f0(%r15),%rdi
    7f76ecc2ce48:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2ce4b:	49 89 b7 40 03 00 00 	mov    %rsi,0x340(%r15)
    7f76ecc2ce52:	49 8b b7 98 02 00 00 	mov    0x298(%r15),%rsi
    7f76ecc2ce59:	49 8b bf f8 01 00 00 	mov    0x1f8(%r15),%rdi
    7f76ecc2ce60:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2ce63:	49 89 b7 48 03 00 00 	mov    %rsi,0x348(%r15)
    7f76ecc2ce6a:	49 0f b6 b7 40 01 00 	movzbq 0x140(%r15),%rsi
    7f76ecc2ce71:	00 
    7f76ecc2ce72:	8b f6                	mov    %esi,%esi
    7f76ecc2ce74:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2ce79:	8b fe                	mov    %esi,%edi
    7f76ecc2ce7b:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2ce7e:	d1 e7                	shl    %edi
    7f76ecc2ce80:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2ce83:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2ce87:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2ce8b:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2ce8e:	41 d1 e1             	shl    %r9d
    7f76ecc2ce91:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2ce94:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2ce97:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2ce9b:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2ce9e:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2cea2:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2cea5:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2cea8:	4d 0f b6 87 45 01 00 	movzbq 0x145(%r15),%r8
    7f76ecc2ceaf:	00 
    7f76ecc2ceb0:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2ceb3:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2ceb8:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2cebb:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2cebf:	41 d1 e1             	shl    %r9d
    7f76ecc2cec2:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2cec5:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2cec9:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2cecd:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2ced0:	41 d1 e3             	shl    %r11d
    7f76ecc2ced3:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ced6:	44 89 95 18 fc ff ff 	mov    %r10d,-0x3e8(%rbp)
    7f76ecc2cedd:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2cee1:	45 0b da             	or     %r10d,%r11d
    7f76ecc2cee4:	44 8b 95 18 fc ff ff 	mov    -0x3e8(%rbp),%r10d
    7f76ecc2ceeb:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2ceef:	45 0b da             	or     %r10d,%r11d
    7f76ecc2cef2:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2cef5:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2cef8:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2cefb:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2cefe:	4d 0f b6 9f 4a 01 00 	movzbq 0x14a(%r15),%r11
    7f76ecc2cf05:	00 
    7f76ecc2cf06:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2cf09:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2cf0e:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2cf11:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7f76ecc2cf17:	49 0f b6 87 4f 01 00 	movzbq 0x14f(%r15),%rax
    7f76ecc2cf1e:	00 
    7f76ecc2cf1f:	8b c0                	mov    %eax,%eax
    7f76ecc2cf21:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2cf26:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2cf29:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2cf2c:	44 89 9d 08 fc ff ff 	mov    %r11d,-0x3f8(%rbp)
    7f76ecc2cf33:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2cf37:	41 d1 e3             	shl    %r11d
    7f76ecc2cf3a:	89 9d 00 fc ff ff    	mov    %ebx,-0x400(%rbp)
    7f76ecc2cf40:	8b 9d 08 fc ff ff    	mov    -0x3f8(%rbp),%ebx
    7f76ecc2cf46:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2cf49:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2cf4c:	89 9d f8 fb ff ff    	mov    %ebx,-0x408(%rbp)
    7f76ecc2cf52:	d1 e3                	shl    %ebx
    7f76ecc2cf54:	89 95 f0 fb ff ff    	mov    %edx,-0x410(%rbp)
    7f76ecc2cf5a:	8b 95 f8 fb ff ff    	mov    -0x408(%rbp),%edx
    7f76ecc2cf60:	0b da                	or     %edx,%ebx
    7f76ecc2cf62:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2cf65:	0b da                	or     %edx,%ebx
    7f76ecc2cf67:	8b 95 f8 fb ff ff    	mov    -0x408(%rbp),%edx
    7f76ecc2cf6d:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2cf70:	0b da                	or     %edx,%ebx
    7f76ecc2cf72:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2cf75:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2cf78:	8b 9d 08 fc ff ff    	mov    -0x3f8(%rbp),%ebx
    7f76ecc2cf7e:	33 d3                	xor    %ebx,%edx
    7f76ecc2cf80:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2cf83:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2cf86:	8b d6                	mov    %esi,%edx
    7f76ecc2cf88:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2cf8b:	44 33 da             	xor    %edx,%r11d
    7f76ecc2cf8e:	8b d0                	mov    %eax,%edx
    7f76ecc2cf90:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2cf93:	d1 e2                	shl    %edx
    7f76ecc2cf95:	8b d8                	mov    %eax,%ebx
    7f76ecc2cf97:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2cf9a:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2cf9d:	89 9d e8 fb ff ff    	mov    %ebx,-0x418(%rbp)
    7f76ecc2cfa3:	d1 e3                	shl    %ebx
    7f76ecc2cfa5:	89 8d e0 fb ff ff    	mov    %ecx,-0x420(%rbp)
    7f76ecc2cfab:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7f76ecc2cfb1:	0b d9                	or     %ecx,%ebx
    7f76ecc2cfb3:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2cfb6:	0b d9                	or     %ecx,%ebx
    7f76ecc2cfb8:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7f76ecc2cfbe:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2cfc1:	0b d9                	or     %ecx,%ebx
    7f76ecc2cfc3:	33 d3                	xor    %ebx,%edx
    7f76ecc2cfc5:	33 c2                	xor    %edx,%eax
    7f76ecc2cfc7:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2cfca:	33 fe                	xor    %esi,%edi
    7f76ecc2cfcc:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2cfcf:	44 33 85 08 fc ff ff 	xor    -0x3f8(%rbp),%r8d
    7f76ecc2cfd6:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2cfd9:	49 0f b6 87 44 01 00 	movzbq 0x144(%r15),%rax
    7f76ecc2cfe0:	00 
    7f76ecc2cfe1:	8b c0                	mov    %eax,%eax
    7f76ecc2cfe3:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2cfe8:	8b c8                	mov    %eax,%ecx
    7f76ecc2cfea:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2cfed:	d1 e1                	shl    %ecx
    7f76ecc2cfef:	8b d8                	mov    %eax,%ebx
    7f76ecc2cff1:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2cff4:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2cff7:	8b f3                	mov    %ebx,%esi
    7f76ecc2cff9:	d1 e6                	shl    %esi
    7f76ecc2cffb:	0b f3                	or     %ebx,%esi
    7f76ecc2cffd:	8b fb                	mov    %ebx,%edi
    7f76ecc2cfff:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2d002:	0b f7                	or     %edi,%esi
    7f76ecc2d004:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2d007:	0b f3                	or     %ebx,%esi
    7f76ecc2d009:	33 ce                	xor    %esi,%ecx
    7f76ecc2d00b:	49 0f b6 9f 49 01 00 	movzbq 0x149(%r15),%rbx
    7f76ecc2d012:	00 
    7f76ecc2d013:	8b db                	mov    %ebx,%ebx
    7f76ecc2d015:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2d01a:	8b f3                	mov    %ebx,%esi
    7f76ecc2d01c:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2d01f:	d1 e6                	shl    %esi
    7f76ecc2d021:	8b fb                	mov    %ebx,%edi
    7f76ecc2d023:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2d026:	83 e7 01             	and    $0x1,%edi
    7f76ecc2d029:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2d02c:	41 d1 e0             	shl    %r8d
    7f76ecc2d02f:	44 0b c7             	or     %edi,%r8d
    7f76ecc2d032:	89 bd d8 fb ff ff    	mov    %edi,-0x428(%rbp)
    7f76ecc2d038:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2d03b:	44 0b c7             	or     %edi,%r8d
    7f76ecc2d03e:	8b bd d8 fb ff ff    	mov    -0x428(%rbp),%edi
    7f76ecc2d044:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2d047:	44 0b c7             	or     %edi,%r8d
    7f76ecc2d04a:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2d04d:	8b fe                	mov    %esi,%edi
    7f76ecc2d04f:	33 fb                	xor    %ebx,%edi
    7f76ecc2d051:	33 f9                	xor    %ecx,%edi
    7f76ecc2d053:	4d 0f b6 87 4e 01 00 	movzbq 0x14e(%r15),%r8
    7f76ecc2d05a:	00 
    7f76ecc2d05b:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2d05e:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2d063:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2d066:	44 89 95 d0 fb ff ff 	mov    %r10d,-0x430(%rbp)
    7f76ecc2d06d:	4d 0f b6 97 43 01 00 	movzbq 0x143(%r15),%r10
    7f76ecc2d074:	00 
    7f76ecc2d075:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2d078:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2d07d:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2d080:	33 f0                	xor    %eax,%esi
    7f76ecc2d082:	44 89 85 c8 fb ff ff 	mov    %r8d,-0x438(%rbp)
    7f76ecc2d089:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2d08d:	41 d1 e0             	shl    %r8d
    7f76ecc2d090:	44 89 8d c0 fb ff ff 	mov    %r9d,-0x440(%rbp)
    7f76ecc2d097:	44 8b 8d c8 fb ff ff 	mov    -0x438(%rbp),%r9d
    7f76ecc2d09e:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2d0a2:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2d0a6:	44 89 8d b8 fb ff ff 	mov    %r9d,-0x448(%rbp)
    7f76ecc2d0ad:	41 d1 e1             	shl    %r9d
    7f76ecc2d0b0:	44 89 9d b0 fb ff ff 	mov    %r11d,-0x450(%rbp)
    7f76ecc2d0b7:	44 8b 9d b8 fb ff ff 	mov    -0x448(%rbp),%r11d
    7f76ecc2d0be:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2d0c1:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2d0c5:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2d0c8:	44 8b 9d b8 fb ff ff 	mov    -0x448(%rbp),%r11d
    7f76ecc2d0cf:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2d0d3:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2d0d6:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2d0d9:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2d0dc:	44 8b 9d c8 fb ff ff 	mov    -0x438(%rbp),%r11d
    7f76ecc2d0e3:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2d0e6:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2d0e9:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2d0ec:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2d0ef:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2d0f2:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2d0f5:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2d0f8:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2d0fc:	41 d1 e1             	shl    %r9d
    7f76ecc2d0ff:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2d102:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2d106:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2d10a:	44 89 9d a8 fb ff ff 	mov    %r11d,-0x458(%rbp)
    7f76ecc2d111:	41 d1 e3             	shl    %r11d
    7f76ecc2d114:	89 95 a0 fb ff ff    	mov    %edx,-0x460(%rbp)
    7f76ecc2d11a:	8b 95 a8 fb ff ff    	mov    -0x458(%rbp),%edx
    7f76ecc2d120:	44 0b da             	or     %edx,%r11d
    7f76ecc2d123:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2d126:	44 0b da             	or     %edx,%r11d
    7f76ecc2d129:	8b 95 a8 fb ff ff    	mov    -0x458(%rbp),%edx
    7f76ecc2d12f:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2d132:	44 0b da             	or     %edx,%r11d
    7f76ecc2d135:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2d138:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2d13b:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2d13e:	33 c8                	xor    %eax,%ecx
    7f76ecc2d140:	33 d9                	xor    %ecx,%ebx
    7f76ecc2d142:	33 9d c8 fb ff ff    	xor    -0x438(%rbp),%ebx
    7f76ecc2d148:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2d14b:	49 0f b6 87 48 01 00 	movzbq 0x148(%r15),%rax
    7f76ecc2d152:	00 
    7f76ecc2d153:	8b c0                	mov    %eax,%eax
    7f76ecc2d155:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2d15a:	8b c8                	mov    %eax,%ecx
    7f76ecc2d15c:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2d15f:	d1 e1                	shl    %ecx
    7f76ecc2d161:	8b d0                	mov    %eax,%edx
    7f76ecc2d163:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2d166:	83 e2 01             	and    $0x1,%edx
    7f76ecc2d169:	8b da                	mov    %edx,%ebx
    7f76ecc2d16b:	d1 e3                	shl    %ebx
    7f76ecc2d16d:	0b da                	or     %edx,%ebx
    7f76ecc2d16f:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2d172:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2d176:	41 0b da             	or     %r10d,%ebx
    7f76ecc2d179:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2d17c:	0b da                	or     %edx,%ebx
    7f76ecc2d17e:	33 cb                	xor    %ebx,%ecx
    7f76ecc2d180:	49 0f b6 97 4d 01 00 	movzbq 0x14d(%r15),%rdx
    7f76ecc2d187:	00 
    7f76ecc2d188:	8b d2                	mov    %edx,%edx
    7f76ecc2d18a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2d18f:	8b da                	mov    %edx,%ebx
    7f76ecc2d191:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2d194:	d1 e3                	shl    %ebx
    7f76ecc2d196:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2d199:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2d19d:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2d1a1:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2d1a4:	41 d1 e3             	shl    %r11d
    7f76ecc2d1a7:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d1aa:	44 89 95 98 fb ff ff 	mov    %r10d,-0x468(%rbp)
    7f76ecc2d1b1:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2d1b5:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d1b8:	44 8b 95 98 fb ff ff 	mov    -0x468(%rbp),%r10d
    7f76ecc2d1bf:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2d1c3:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d1c6:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2d1c9:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2d1cc:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2d1cf:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2d1d2:	4d 0f b6 9f 42 01 00 	movzbq 0x142(%r15),%r11
    7f76ecc2d1d9:	00 
    7f76ecc2d1da:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2d1dd:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2d1e2:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2d1e5:	89 bd 90 fb ff ff    	mov    %edi,-0x470(%rbp)
    7f76ecc2d1eb:	49 0f b6 bf 47 01 00 	movzbq 0x147(%r15),%rdi
    7f76ecc2d1f2:	00 
    7f76ecc2d1f3:	8b ff                	mov    %edi,%edi
    7f76ecc2d1f5:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2d1fa:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2d1fd:	33 d8                	xor    %eax,%ebx
    7f76ecc2d1ff:	44 89 9d 88 fb ff ff 	mov    %r11d,-0x478(%rbp)
    7f76ecc2d206:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2d20a:	41 d1 e3             	shl    %r11d
    7f76ecc2d20d:	89 b5 80 fb ff ff    	mov    %esi,-0x480(%rbp)
    7f76ecc2d213:	8b b5 88 fb ff ff    	mov    -0x478(%rbp),%esi
    7f76ecc2d219:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2d21c:	83 e6 01             	and    $0x1,%esi
    7f76ecc2d21f:	89 b5 78 fb ff ff    	mov    %esi,-0x488(%rbp)
    7f76ecc2d225:	d1 e6                	shl    %esi
    7f76ecc2d227:	44 89 85 70 fb ff ff 	mov    %r8d,-0x490(%rbp)
    7f76ecc2d22e:	44 8b 85 78 fb ff ff 	mov    -0x488(%rbp),%r8d
    7f76ecc2d235:	41 0b f0             	or     %r8d,%esi
    7f76ecc2d238:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2d23c:	41 0b f0             	or     %r8d,%esi
    7f76ecc2d23f:	44 8b 85 78 fb ff ff 	mov    -0x488(%rbp),%r8d
    7f76ecc2d246:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2d24a:	41 0b f0             	or     %r8d,%esi
    7f76ecc2d24d:	44 33 de             	xor    %esi,%r11d
    7f76ecc2d250:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2d253:	44 8b 85 88 fb ff ff 	mov    -0x478(%rbp),%r8d
    7f76ecc2d25a:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2d25d:	33 de                	xor    %esi,%ebx
    7f76ecc2d25f:	33 df                	xor    %edi,%ebx
    7f76ecc2d261:	8b f0                	mov    %eax,%esi
    7f76ecc2d263:	33 f2                	xor    %edx,%esi
    7f76ecc2d265:	44 33 de             	xor    %esi,%r11d
    7f76ecc2d268:	8b f7                	mov    %edi,%esi
    7f76ecc2d26a:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2d26d:	d1 e6                	shl    %esi
    7f76ecc2d26f:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2d272:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2d276:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2d27a:	44 89 85 68 fb ff ff 	mov    %r8d,-0x498(%rbp)
    7f76ecc2d281:	41 d1 e0             	shl    %r8d
    7f76ecc2d284:	44 89 8d 60 fb ff ff 	mov    %r9d,-0x4a0(%rbp)
    7f76ecc2d28b:	44 8b 8d 68 fb ff ff 	mov    -0x498(%rbp),%r9d
    7f76ecc2d292:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2d295:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2d299:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2d29c:	44 8b 8d 68 fb ff ff 	mov    -0x498(%rbp),%r9d
    7f76ecc2d2a3:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2d2a7:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2d2aa:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2d2ad:	33 fe                	xor    %esi,%edi
    7f76ecc2d2af:	44 33 df             	xor    %edi,%r11d
    7f76ecc2d2b2:	33 c8                	xor    %eax,%ecx
    7f76ecc2d2b4:	33 d1                	xor    %ecx,%edx
    7f76ecc2d2b6:	33 95 88 fb ff ff    	xor    -0x478(%rbp),%edx
    7f76ecc2d2bc:	33 f2                	xor    %edx,%esi
    7f76ecc2d2be:	49 0f b6 87 4c 01 00 	movzbq 0x14c(%r15),%rax
    7f76ecc2d2c5:	00 
    7f76ecc2d2c6:	8b c0                	mov    %eax,%eax
    7f76ecc2d2c8:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2d2cd:	8b c8                	mov    %eax,%ecx
    7f76ecc2d2cf:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2d2d2:	d1 e1                	shl    %ecx
    7f76ecc2d2d4:	8b d0                	mov    %eax,%edx
    7f76ecc2d2d6:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2d2d9:	83 e2 01             	and    $0x1,%edx
    7f76ecc2d2dc:	8b fa                	mov    %edx,%edi
    7f76ecc2d2de:	d1 e7                	shl    %edi
    7f76ecc2d2e0:	0b fa                	or     %edx,%edi
    7f76ecc2d2e2:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2d2e5:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2d2e9:	41 0b f8             	or     %r8d,%edi
    7f76ecc2d2ec:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2d2ef:	0b fa                	or     %edx,%edi
    7f76ecc2d2f1:	33 cf                	xor    %edi,%ecx
    7f76ecc2d2f3:	49 0f b6 97 41 01 00 	movzbq 0x141(%r15),%rdx
    7f76ecc2d2fa:	00 
    7f76ecc2d2fb:	8b d2                	mov    %edx,%edx
    7f76ecc2d2fd:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2d302:	8b fa                	mov    %edx,%edi
    7f76ecc2d304:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2d307:	d1 e7                	shl    %edi
    7f76ecc2d309:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2d30c:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2d310:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2d314:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2d317:	41 d1 e1             	shl    %r9d
    7f76ecc2d31a:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2d31d:	44 89 85 58 fb ff ff 	mov    %r8d,-0x4a8(%rbp)
    7f76ecc2d324:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2d328:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2d32b:	44 8b 85 58 fb ff ff 	mov    -0x4a8(%rbp),%r8d
    7f76ecc2d332:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2d336:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2d339:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2d33c:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2d33f:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2d342:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2d345:	4d 0f b6 8f 46 01 00 	movzbq 0x146(%r15),%r9
    7f76ecc2d34c:	00 
    7f76ecc2d34d:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2d350:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2d355:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2d358:	44 89 95 50 fb ff ff 	mov    %r10d,-0x4b0(%rbp)
    7f76ecc2d35f:	4d 0f b6 97 4b 01 00 	movzbq 0x14b(%r15),%r10
    7f76ecc2d366:	00 
    7f76ecc2d367:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2d36a:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2d36f:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2d372:	33 f8                	xor    %eax,%edi
    7f76ecc2d374:	44 89 8d 48 fb ff ff 	mov    %r9d,-0x4b8(%rbp)
    7f76ecc2d37b:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2d37f:	41 d1 e1             	shl    %r9d
    7f76ecc2d382:	89 9d 40 fb ff ff    	mov    %ebx,-0x4c0(%rbp)
    7f76ecc2d388:	8b 9d 48 fb ff ff    	mov    -0x4b8(%rbp),%ebx
    7f76ecc2d38e:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2d391:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2d394:	89 9d 38 fb ff ff    	mov    %ebx,-0x4c8(%rbp)
    7f76ecc2d39a:	d1 e3                	shl    %ebx
    7f76ecc2d39c:	44 89 9d 30 fb ff ff 	mov    %r11d,-0x4d0(%rbp)
    7f76ecc2d3a3:	44 8b 9d 38 fb ff ff 	mov    -0x4c8(%rbp),%r11d
    7f76ecc2d3aa:	41 0b db             	or     %r11d,%ebx
    7f76ecc2d3ad:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2d3b1:	41 0b db             	or     %r11d,%ebx
    7f76ecc2d3b4:	44 8b 9d 38 fb ff ff 	mov    -0x4c8(%rbp),%r11d
    7f76ecc2d3bb:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2d3bf:	41 0b db             	or     %r11d,%ebx
    7f76ecc2d3c2:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2d3c5:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2d3c8:	44 8b 9d 48 fb ff ff 	mov    -0x4b8(%rbp),%r11d
    7f76ecc2d3cf:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2d3d2:	33 fb                	xor    %ebx,%edi
    7f76ecc2d3d4:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2d3d7:	8b d8                	mov    %eax,%ebx
    7f76ecc2d3d9:	33 da                	xor    %edx,%ebx
    7f76ecc2d3db:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2d3de:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2d3e1:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2d3e4:	d1 e3                	shl    %ebx
    7f76ecc2d3e6:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2d3e9:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2d3ed:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2d3f1:	44 89 9d 28 fb ff ff 	mov    %r11d,-0x4d8(%rbp)
    7f76ecc2d3f8:	41 d1 e3             	shl    %r11d
    7f76ecc2d3fb:	89 b5 20 fb ff ff    	mov    %esi,-0x4e0(%rbp)
    7f76ecc2d401:	8b b5 28 fb ff ff    	mov    -0x4d8(%rbp),%esi
    7f76ecc2d407:	44 0b de             	or     %esi,%r11d
    7f76ecc2d40a:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2d40d:	44 0b de             	or     %esi,%r11d
    7f76ecc2d410:	8b b5 28 fb ff ff    	mov    -0x4d8(%rbp),%esi
    7f76ecc2d416:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2d419:	44 0b de             	or     %esi,%r11d
    7f76ecc2d41c:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2d41f:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2d422:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2d425:	33 c8                	xor    %eax,%ecx
    7f76ecc2d427:	33 d1                	xor    %ecx,%edx
    7f76ecc2d429:	33 95 48 fb ff ff    	xor    -0x4b8(%rbp),%edx
    7f76ecc2d42f:	33 da                	xor    %edx,%ebx
    7f76ecc2d431:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7f76ecc2d437:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2d43a:	0b 85 d0 fb ff ff    	or     -0x430(%rbp),%eax
    7f76ecc2d440:	8b 8d b0 fb ff ff    	mov    -0x450(%rbp),%ecx
    7f76ecc2d446:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2d449:	0b c1                	or     %ecx,%eax
    7f76ecc2d44b:	8b 8d a0 fb ff ff    	mov    -0x460(%rbp),%ecx
    7f76ecc2d451:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2d454:	0b c1                	or     %ecx,%eax
    7f76ecc2d456:	8b 8d 90 fb ff ff    	mov    -0x470(%rbp),%ecx
    7f76ecc2d45c:	8b c9                	mov    %ecx,%ecx
    7f76ecc2d45e:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2d462:	8b c0                	mov    %eax,%eax
    7f76ecc2d464:	48 0b c8             	or     %rax,%rcx
    7f76ecc2d467:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7f76ecc2d46d:	8b c0                	mov    %eax,%eax
    7f76ecc2d46f:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2d473:	48 0b c8             	or     %rax,%rcx
    7f76ecc2d476:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7f76ecc2d47c:	8b c0                	mov    %eax,%eax
    7f76ecc2d47e:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2d482:	48 0b c8             	or     %rax,%rcx
    7f76ecc2d485:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7f76ecc2d48b:	8b c0                	mov    %eax,%eax
    7f76ecc2d48d:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2d491:	48 0b c8             	or     %rax,%rcx
    7f76ecc2d494:	49 89 8f a0 02 00 00 	mov    %rcx,0x2a0(%r15)
    7f76ecc2d49b:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7f76ecc2d4a1:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2d4a4:	0b 85 50 fb ff ff    	or     -0x4b0(%rbp),%eax
    7f76ecc2d4aa:	8b 8d 30 fb ff ff    	mov    -0x4d0(%rbp),%ecx
    7f76ecc2d4b0:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2d4b3:	0b c1                	or     %ecx,%eax
    7f76ecc2d4b5:	8b 8d 20 fb ff ff    	mov    -0x4e0(%rbp),%ecx
    7f76ecc2d4bb:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2d4be:	0b c1                	or     %ecx,%eax
    7f76ecc2d4c0:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2d4c3:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2d4c7:	8b c0                	mov    %eax,%eax
    7f76ecc2d4c9:	4c 0b c0             	or     %rax,%r8
    7f76ecc2d4cc:	8b ff                	mov    %edi,%edi
    7f76ecc2d4ce:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2d4d2:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2d4d5:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2d4d8:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2d4dc:	4d 0b c1             	or     %r9,%r8
    7f76ecc2d4df:	8b db                	mov    %ebx,%ebx
    7f76ecc2d4e1:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2d4e5:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2d4e8:	4d 89 87 a8 02 00 00 	mov    %r8,0x2a8(%r15)
    7f76ecc2d4ef:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7f76ecc2d4f5:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2d4fa:	8b c0                	mov    %eax,%eax
    7f76ecc2d4fc:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2d501:	8b 8d f0 fb ff ff    	mov    -0x410(%rbp),%ecx
    7f76ecc2d507:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2d50a:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2d510:	8b c9                	mov    %ecx,%ecx
    7f76ecc2d512:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2d517:	8b 95 f0 fb ff ff    	mov    -0x410(%rbp),%edx
    7f76ecc2d51d:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2d520:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2d526:	8b d2                	mov    %edx,%edx
    7f76ecc2d528:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2d52d:	8b 9d f0 fb ff ff    	mov    -0x410(%rbp),%ebx
    7f76ecc2d533:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2d536:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2d53c:	8b db                	mov    %ebx,%ebx
    7f76ecc2d53e:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2d543:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2d546:	0b da                	or     %edx,%ebx
    7f76ecc2d548:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2d54b:	0b d9                	or     %ecx,%ebx
    7f76ecc2d54d:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2d550:	0b d8                	or     %eax,%ebx
    7f76ecc2d552:	83 f3 10             	xor    $0x10,%ebx
    7f76ecc2d555:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7f76ecc2d55b:	33 d8                	xor    %eax,%ebx
    7f76ecc2d55d:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7f76ecc2d563:	33 c3                	xor    %ebx,%eax
    7f76ecc2d565:	8b 8d e0 fb ff ff    	mov    -0x420(%rbp),%ecx
    7f76ecc2d56b:	33 c8                	xor    %eax,%ecx
    7f76ecc2d56d:	8b 95 f0 fb ff ff    	mov    -0x410(%rbp),%edx
    7f76ecc2d573:	33 d1                	xor    %ecx,%edx
    7f76ecc2d575:	8b f0                	mov    %eax,%esi
    7f76ecc2d577:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2d57b:	8b fb                	mov    %ebx,%edi
    7f76ecc2d57d:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2d580:	49 89 b7 00 02 00 00 	mov    %rsi,0x200(%r15)
    7f76ecc2d587:	8b f2                	mov    %edx,%esi
    7f76ecc2d589:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2d58d:	8b f9                	mov    %ecx,%edi
    7f76ecc2d58f:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2d592:	49 89 b7 08 02 00 00 	mov    %rsi,0x208(%r15)
    7f76ecc2d599:	49 8b b7 a0 02 00 00 	mov    0x2a0(%r15),%rsi
    7f76ecc2d5a0:	49 8b bf 00 02 00 00 	mov    0x200(%r15),%rdi
    7f76ecc2d5a7:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2d5aa:	49 89 b7 50 03 00 00 	mov    %rsi,0x350(%r15)
    7f76ecc2d5b1:	49 8b b7 a8 02 00 00 	mov    0x2a8(%r15),%rsi
    7f76ecc2d5b8:	49 8b bf 08 02 00 00 	mov    0x208(%r15),%rdi
    7f76ecc2d5bf:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2d5c2:	49 89 b7 58 03 00 00 	mov    %rsi,0x358(%r15)
    7f76ecc2d5c9:	49 0f b6 b7 50 01 00 	movzbq 0x150(%r15),%rsi
    7f76ecc2d5d0:	00 
    7f76ecc2d5d1:	8b f6                	mov    %esi,%esi
    7f76ecc2d5d3:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2d5d8:	8b fe                	mov    %esi,%edi
    7f76ecc2d5da:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2d5dd:	d1 e7                	shl    %edi
    7f76ecc2d5df:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2d5e2:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2d5e6:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2d5ea:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2d5ed:	41 d1 e1             	shl    %r9d
    7f76ecc2d5f0:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2d5f3:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2d5f6:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2d5fa:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2d5fd:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2d601:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2d604:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2d607:	4d 0f b6 87 55 01 00 	movzbq 0x155(%r15),%r8
    7f76ecc2d60e:	00 
    7f76ecc2d60f:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2d612:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2d617:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2d61a:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2d61e:	41 d1 e1             	shl    %r9d
    7f76ecc2d621:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2d624:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2d628:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2d62c:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2d62f:	41 d1 e3             	shl    %r11d
    7f76ecc2d632:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d635:	44 89 95 18 fb ff ff 	mov    %r10d,-0x4e8(%rbp)
    7f76ecc2d63c:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2d640:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d643:	44 8b 95 18 fb ff ff 	mov    -0x4e8(%rbp),%r10d
    7f76ecc2d64a:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2d64e:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d651:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2d654:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2d657:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2d65a:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2d65d:	4d 0f b6 9f 5a 01 00 	movzbq 0x15a(%r15),%r11
    7f76ecc2d664:	00 
    7f76ecc2d665:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2d668:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2d66d:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2d670:	89 85 10 fb ff ff    	mov    %eax,-0x4f0(%rbp)
    7f76ecc2d676:	49 0f b6 87 5f 01 00 	movzbq 0x15f(%r15),%rax
    7f76ecc2d67d:	00 
    7f76ecc2d67e:	8b c0                	mov    %eax,%eax
    7f76ecc2d680:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2d685:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2d688:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2d68b:	44 89 9d 08 fb ff ff 	mov    %r11d,-0x4f8(%rbp)
    7f76ecc2d692:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2d696:	41 d1 e3             	shl    %r11d
    7f76ecc2d699:	89 9d 00 fb ff ff    	mov    %ebx,-0x500(%rbp)
    7f76ecc2d69f:	8b 9d 08 fb ff ff    	mov    -0x4f8(%rbp),%ebx
    7f76ecc2d6a5:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2d6a8:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2d6ab:	89 9d f8 fa ff ff    	mov    %ebx,-0x508(%rbp)
    7f76ecc2d6b1:	d1 e3                	shl    %ebx
    7f76ecc2d6b3:	89 95 f0 fa ff ff    	mov    %edx,-0x510(%rbp)
    7f76ecc2d6b9:	8b 95 f8 fa ff ff    	mov    -0x508(%rbp),%edx
    7f76ecc2d6bf:	0b da                	or     %edx,%ebx
    7f76ecc2d6c1:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2d6c4:	0b da                	or     %edx,%ebx
    7f76ecc2d6c6:	8b 95 f8 fa ff ff    	mov    -0x508(%rbp),%edx
    7f76ecc2d6cc:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2d6cf:	0b da                	or     %edx,%ebx
    7f76ecc2d6d1:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2d6d4:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2d6d7:	8b 9d 08 fb ff ff    	mov    -0x4f8(%rbp),%ebx
    7f76ecc2d6dd:	33 d3                	xor    %ebx,%edx
    7f76ecc2d6df:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2d6e2:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2d6e5:	8b d6                	mov    %esi,%edx
    7f76ecc2d6e7:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2d6ea:	44 33 da             	xor    %edx,%r11d
    7f76ecc2d6ed:	8b d0                	mov    %eax,%edx
    7f76ecc2d6ef:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2d6f2:	d1 e2                	shl    %edx
    7f76ecc2d6f4:	8b d8                	mov    %eax,%ebx
    7f76ecc2d6f6:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2d6f9:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2d6fc:	89 9d e8 fa ff ff    	mov    %ebx,-0x518(%rbp)
    7f76ecc2d702:	d1 e3                	shl    %ebx
    7f76ecc2d704:	89 8d e0 fa ff ff    	mov    %ecx,-0x520(%rbp)
    7f76ecc2d70a:	8b 8d e8 fa ff ff    	mov    -0x518(%rbp),%ecx
    7f76ecc2d710:	0b d9                	or     %ecx,%ebx
    7f76ecc2d712:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2d715:	0b d9                	or     %ecx,%ebx
    7f76ecc2d717:	8b 8d e8 fa ff ff    	mov    -0x518(%rbp),%ecx
    7f76ecc2d71d:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2d720:	0b d9                	or     %ecx,%ebx
    7f76ecc2d722:	33 d3                	xor    %ebx,%edx
    7f76ecc2d724:	33 c2                	xor    %edx,%eax
    7f76ecc2d726:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2d729:	33 fe                	xor    %esi,%edi
    7f76ecc2d72b:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2d72e:	44 33 85 08 fb ff ff 	xor    -0x4f8(%rbp),%r8d
    7f76ecc2d735:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2d738:	49 0f b6 87 54 01 00 	movzbq 0x154(%r15),%rax
    7f76ecc2d73f:	00 
    7f76ecc2d740:	8b c0                	mov    %eax,%eax
    7f76ecc2d742:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2d747:	8b c8                	mov    %eax,%ecx
    7f76ecc2d749:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2d74c:	d1 e1                	shl    %ecx
    7f76ecc2d74e:	8b d8                	mov    %eax,%ebx
    7f76ecc2d750:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2d753:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2d756:	8b f3                	mov    %ebx,%esi
    7f76ecc2d758:	d1 e6                	shl    %esi
    7f76ecc2d75a:	0b f3                	or     %ebx,%esi
    7f76ecc2d75c:	8b fb                	mov    %ebx,%edi
    7f76ecc2d75e:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2d761:	0b f7                	or     %edi,%esi
    7f76ecc2d763:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2d766:	0b f3                	or     %ebx,%esi
    7f76ecc2d768:	33 ce                	xor    %esi,%ecx
    7f76ecc2d76a:	49 0f b6 9f 59 01 00 	movzbq 0x159(%r15),%rbx
    7f76ecc2d771:	00 
    7f76ecc2d772:	8b db                	mov    %ebx,%ebx
    7f76ecc2d774:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2d779:	8b f3                	mov    %ebx,%esi
    7f76ecc2d77b:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2d77e:	d1 e6                	shl    %esi
    7f76ecc2d780:	8b fb                	mov    %ebx,%edi
    7f76ecc2d782:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2d785:	83 e7 01             	and    $0x1,%edi
    7f76ecc2d788:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2d78b:	41 d1 e0             	shl    %r8d
    7f76ecc2d78e:	44 0b c7             	or     %edi,%r8d
    7f76ecc2d791:	89 bd d8 fa ff ff    	mov    %edi,-0x528(%rbp)
    7f76ecc2d797:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2d79a:	44 0b c7             	or     %edi,%r8d
    7f76ecc2d79d:	8b bd d8 fa ff ff    	mov    -0x528(%rbp),%edi
    7f76ecc2d7a3:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2d7a6:	44 0b c7             	or     %edi,%r8d
    7f76ecc2d7a9:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2d7ac:	8b fe                	mov    %esi,%edi
    7f76ecc2d7ae:	33 fb                	xor    %ebx,%edi
    7f76ecc2d7b0:	33 f9                	xor    %ecx,%edi
    7f76ecc2d7b2:	4d 0f b6 87 5e 01 00 	movzbq 0x15e(%r15),%r8
    7f76ecc2d7b9:	00 
    7f76ecc2d7ba:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2d7bd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2d7c2:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2d7c5:	44 89 95 d0 fa ff ff 	mov    %r10d,-0x530(%rbp)
    7f76ecc2d7cc:	4d 0f b6 97 53 01 00 	movzbq 0x153(%r15),%r10
    7f76ecc2d7d3:	00 
    7f76ecc2d7d4:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2d7d7:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2d7dc:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2d7df:	33 f0                	xor    %eax,%esi
    7f76ecc2d7e1:	44 89 85 c8 fa ff ff 	mov    %r8d,-0x538(%rbp)
    7f76ecc2d7e8:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2d7ec:	41 d1 e0             	shl    %r8d
    7f76ecc2d7ef:	44 89 8d c0 fa ff ff 	mov    %r9d,-0x540(%rbp)
    7f76ecc2d7f6:	44 8b 8d c8 fa ff ff 	mov    -0x538(%rbp),%r9d
    7f76ecc2d7fd:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2d801:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2d805:	44 89 8d b8 fa ff ff 	mov    %r9d,-0x548(%rbp)
    7f76ecc2d80c:	41 d1 e1             	shl    %r9d
    7f76ecc2d80f:	44 89 9d b0 fa ff ff 	mov    %r11d,-0x550(%rbp)
    7f76ecc2d816:	44 8b 9d b8 fa ff ff 	mov    -0x548(%rbp),%r11d
    7f76ecc2d81d:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2d820:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2d824:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2d827:	44 8b 9d b8 fa ff ff 	mov    -0x548(%rbp),%r11d
    7f76ecc2d82e:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2d832:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2d835:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2d838:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2d83b:	44 8b 9d c8 fa ff ff 	mov    -0x538(%rbp),%r11d
    7f76ecc2d842:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2d845:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2d848:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2d84b:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2d84e:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2d851:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2d854:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2d857:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2d85b:	41 d1 e1             	shl    %r9d
    7f76ecc2d85e:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2d861:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2d865:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2d869:	44 89 9d a8 fa ff ff 	mov    %r11d,-0x558(%rbp)
    7f76ecc2d870:	41 d1 e3             	shl    %r11d
    7f76ecc2d873:	89 95 a0 fa ff ff    	mov    %edx,-0x560(%rbp)
    7f76ecc2d879:	8b 95 a8 fa ff ff    	mov    -0x558(%rbp),%edx
    7f76ecc2d87f:	44 0b da             	or     %edx,%r11d
    7f76ecc2d882:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2d885:	44 0b da             	or     %edx,%r11d
    7f76ecc2d888:	8b 95 a8 fa ff ff    	mov    -0x558(%rbp),%edx
    7f76ecc2d88e:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2d891:	44 0b da             	or     %edx,%r11d
    7f76ecc2d894:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2d897:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2d89a:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2d89d:	33 c8                	xor    %eax,%ecx
    7f76ecc2d89f:	33 d9                	xor    %ecx,%ebx
    7f76ecc2d8a1:	33 9d c8 fa ff ff    	xor    -0x538(%rbp),%ebx
    7f76ecc2d8a7:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2d8aa:	49 0f b6 87 58 01 00 	movzbq 0x158(%r15),%rax
    7f76ecc2d8b1:	00 
    7f76ecc2d8b2:	8b c0                	mov    %eax,%eax
    7f76ecc2d8b4:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2d8b9:	8b c8                	mov    %eax,%ecx
    7f76ecc2d8bb:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2d8be:	d1 e1                	shl    %ecx
    7f76ecc2d8c0:	8b d0                	mov    %eax,%edx
    7f76ecc2d8c2:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2d8c5:	83 e2 01             	and    $0x1,%edx
    7f76ecc2d8c8:	8b da                	mov    %edx,%ebx
    7f76ecc2d8ca:	d1 e3                	shl    %ebx
    7f76ecc2d8cc:	0b da                	or     %edx,%ebx
    7f76ecc2d8ce:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2d8d1:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2d8d5:	41 0b da             	or     %r10d,%ebx
    7f76ecc2d8d8:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2d8db:	0b da                	or     %edx,%ebx
    7f76ecc2d8dd:	33 cb                	xor    %ebx,%ecx
    7f76ecc2d8df:	49 0f b6 97 5d 01 00 	movzbq 0x15d(%r15),%rdx
    7f76ecc2d8e6:	00 
    7f76ecc2d8e7:	8b d2                	mov    %edx,%edx
    7f76ecc2d8e9:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2d8ee:	8b da                	mov    %edx,%ebx
    7f76ecc2d8f0:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2d8f3:	d1 e3                	shl    %ebx
    7f76ecc2d8f5:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2d8f8:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2d8fc:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2d900:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2d903:	41 d1 e3             	shl    %r11d
    7f76ecc2d906:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d909:	44 89 95 98 fa ff ff 	mov    %r10d,-0x568(%rbp)
    7f76ecc2d910:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2d914:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d917:	44 8b 95 98 fa ff ff 	mov    -0x568(%rbp),%r10d
    7f76ecc2d91e:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2d922:	45 0b da             	or     %r10d,%r11d
    7f76ecc2d925:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2d928:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2d92b:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2d92e:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2d931:	4d 0f b6 9f 52 01 00 	movzbq 0x152(%r15),%r11
    7f76ecc2d938:	00 
    7f76ecc2d939:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2d93c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2d941:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2d944:	89 bd 90 fa ff ff    	mov    %edi,-0x570(%rbp)
    7f76ecc2d94a:	49 0f b6 bf 57 01 00 	movzbq 0x157(%r15),%rdi
    7f76ecc2d951:	00 
    7f76ecc2d952:	8b ff                	mov    %edi,%edi
    7f76ecc2d954:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2d959:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2d95c:	33 d8                	xor    %eax,%ebx
    7f76ecc2d95e:	44 89 9d 88 fa ff ff 	mov    %r11d,-0x578(%rbp)
    7f76ecc2d965:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2d969:	41 d1 e3             	shl    %r11d
    7f76ecc2d96c:	89 b5 80 fa ff ff    	mov    %esi,-0x580(%rbp)
    7f76ecc2d972:	8b b5 88 fa ff ff    	mov    -0x578(%rbp),%esi
    7f76ecc2d978:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2d97b:	83 e6 01             	and    $0x1,%esi
    7f76ecc2d97e:	89 b5 78 fa ff ff    	mov    %esi,-0x588(%rbp)
    7f76ecc2d984:	d1 e6                	shl    %esi
    7f76ecc2d986:	44 89 85 70 fa ff ff 	mov    %r8d,-0x590(%rbp)
    7f76ecc2d98d:	44 8b 85 78 fa ff ff 	mov    -0x588(%rbp),%r8d
    7f76ecc2d994:	41 0b f0             	or     %r8d,%esi
    7f76ecc2d997:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2d99b:	41 0b f0             	or     %r8d,%esi
    7f76ecc2d99e:	44 8b 85 78 fa ff ff 	mov    -0x588(%rbp),%r8d
    7f76ecc2d9a5:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2d9a9:	41 0b f0             	or     %r8d,%esi
    7f76ecc2d9ac:	44 33 de             	xor    %esi,%r11d
    7f76ecc2d9af:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2d9b2:	44 8b 85 88 fa ff ff 	mov    -0x578(%rbp),%r8d
    7f76ecc2d9b9:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2d9bc:	33 de                	xor    %esi,%ebx
    7f76ecc2d9be:	33 df                	xor    %edi,%ebx
    7f76ecc2d9c0:	8b f0                	mov    %eax,%esi
    7f76ecc2d9c2:	33 f2                	xor    %edx,%esi
    7f76ecc2d9c4:	44 33 de             	xor    %esi,%r11d
    7f76ecc2d9c7:	8b f7                	mov    %edi,%esi
    7f76ecc2d9c9:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2d9cc:	d1 e6                	shl    %esi
    7f76ecc2d9ce:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2d9d1:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2d9d5:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2d9d9:	44 89 85 68 fa ff ff 	mov    %r8d,-0x598(%rbp)
    7f76ecc2d9e0:	41 d1 e0             	shl    %r8d
    7f76ecc2d9e3:	44 89 8d 60 fa ff ff 	mov    %r9d,-0x5a0(%rbp)
    7f76ecc2d9ea:	44 8b 8d 68 fa ff ff 	mov    -0x598(%rbp),%r9d
    7f76ecc2d9f1:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2d9f4:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2d9f8:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2d9fb:	44 8b 8d 68 fa ff ff 	mov    -0x598(%rbp),%r9d
    7f76ecc2da02:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2da06:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2da09:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2da0c:	33 fe                	xor    %esi,%edi
    7f76ecc2da0e:	44 33 df             	xor    %edi,%r11d
    7f76ecc2da11:	33 c8                	xor    %eax,%ecx
    7f76ecc2da13:	33 d1                	xor    %ecx,%edx
    7f76ecc2da15:	33 95 88 fa ff ff    	xor    -0x578(%rbp),%edx
    7f76ecc2da1b:	33 f2                	xor    %edx,%esi
    7f76ecc2da1d:	49 0f b6 87 5c 01 00 	movzbq 0x15c(%r15),%rax
    7f76ecc2da24:	00 
    7f76ecc2da25:	8b c0                	mov    %eax,%eax
    7f76ecc2da27:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2da2c:	8b c8                	mov    %eax,%ecx
    7f76ecc2da2e:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2da31:	d1 e1                	shl    %ecx
    7f76ecc2da33:	8b d0                	mov    %eax,%edx
    7f76ecc2da35:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2da38:	83 e2 01             	and    $0x1,%edx
    7f76ecc2da3b:	8b fa                	mov    %edx,%edi
    7f76ecc2da3d:	d1 e7                	shl    %edi
    7f76ecc2da3f:	0b fa                	or     %edx,%edi
    7f76ecc2da41:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2da44:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2da48:	41 0b f8             	or     %r8d,%edi
    7f76ecc2da4b:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2da4e:	0b fa                	or     %edx,%edi
    7f76ecc2da50:	33 cf                	xor    %edi,%ecx
    7f76ecc2da52:	49 0f b6 97 51 01 00 	movzbq 0x151(%r15),%rdx
    7f76ecc2da59:	00 
    7f76ecc2da5a:	8b d2                	mov    %edx,%edx
    7f76ecc2da5c:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2da61:	8b fa                	mov    %edx,%edi
    7f76ecc2da63:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2da66:	d1 e7                	shl    %edi
    7f76ecc2da68:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2da6b:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2da6f:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2da73:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2da76:	41 d1 e1             	shl    %r9d
    7f76ecc2da79:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2da7c:	44 89 85 58 fa ff ff 	mov    %r8d,-0x5a8(%rbp)
    7f76ecc2da83:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2da87:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2da8a:	44 8b 85 58 fa ff ff 	mov    -0x5a8(%rbp),%r8d
    7f76ecc2da91:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2da95:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2da98:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2da9b:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2da9e:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2daa1:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2daa4:	4d 0f b6 8f 56 01 00 	movzbq 0x156(%r15),%r9
    7f76ecc2daab:	00 
    7f76ecc2daac:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2daaf:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2dab4:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2dab7:	44 89 95 50 fa ff ff 	mov    %r10d,-0x5b0(%rbp)
    7f76ecc2dabe:	4d 0f b6 97 5b 01 00 	movzbq 0x15b(%r15),%r10
    7f76ecc2dac5:	00 
    7f76ecc2dac6:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2dac9:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2dace:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2dad1:	33 f8                	xor    %eax,%edi
    7f76ecc2dad3:	44 89 8d 48 fa ff ff 	mov    %r9d,-0x5b8(%rbp)
    7f76ecc2dada:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2dade:	41 d1 e1             	shl    %r9d
    7f76ecc2dae1:	89 9d 40 fa ff ff    	mov    %ebx,-0x5c0(%rbp)
    7f76ecc2dae7:	8b 9d 48 fa ff ff    	mov    -0x5b8(%rbp),%ebx
    7f76ecc2daed:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2daf0:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2daf3:	89 9d 38 fa ff ff    	mov    %ebx,-0x5c8(%rbp)
    7f76ecc2daf9:	d1 e3                	shl    %ebx
    7f76ecc2dafb:	44 89 9d 30 fa ff ff 	mov    %r11d,-0x5d0(%rbp)
    7f76ecc2db02:	44 8b 9d 38 fa ff ff 	mov    -0x5c8(%rbp),%r11d
    7f76ecc2db09:	41 0b db             	or     %r11d,%ebx
    7f76ecc2db0c:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2db10:	41 0b db             	or     %r11d,%ebx
    7f76ecc2db13:	44 8b 9d 38 fa ff ff 	mov    -0x5c8(%rbp),%r11d
    7f76ecc2db1a:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2db1e:	41 0b db             	or     %r11d,%ebx
    7f76ecc2db21:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2db24:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2db27:	44 8b 9d 48 fa ff ff 	mov    -0x5b8(%rbp),%r11d
    7f76ecc2db2e:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2db31:	33 fb                	xor    %ebx,%edi
    7f76ecc2db33:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2db36:	8b d8                	mov    %eax,%ebx
    7f76ecc2db38:	33 da                	xor    %edx,%ebx
    7f76ecc2db3a:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2db3d:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2db40:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2db43:	d1 e3                	shl    %ebx
    7f76ecc2db45:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2db48:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2db4c:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2db50:	44 89 9d 28 fa ff ff 	mov    %r11d,-0x5d8(%rbp)
    7f76ecc2db57:	41 d1 e3             	shl    %r11d
    7f76ecc2db5a:	89 b5 20 fa ff ff    	mov    %esi,-0x5e0(%rbp)
    7f76ecc2db60:	8b b5 28 fa ff ff    	mov    -0x5d8(%rbp),%esi
    7f76ecc2db66:	44 0b de             	or     %esi,%r11d
    7f76ecc2db69:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2db6c:	44 0b de             	or     %esi,%r11d
    7f76ecc2db6f:	8b b5 28 fa ff ff    	mov    -0x5d8(%rbp),%esi
    7f76ecc2db75:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2db78:	44 0b de             	or     %esi,%r11d
    7f76ecc2db7b:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2db7e:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2db81:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2db84:	33 c8                	xor    %eax,%ecx
    7f76ecc2db86:	33 d1                	xor    %ecx,%edx
    7f76ecc2db88:	33 95 48 fa ff ff    	xor    -0x5b8(%rbp),%edx
    7f76ecc2db8e:	33 da                	xor    %edx,%ebx
    7f76ecc2db90:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7f76ecc2db96:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2db99:	0b 85 d0 fa ff ff    	or     -0x530(%rbp),%eax
    7f76ecc2db9f:	8b 8d b0 fa ff ff    	mov    -0x550(%rbp),%ecx
    7f76ecc2dba5:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2dba8:	0b c1                	or     %ecx,%eax
    7f76ecc2dbaa:	8b 8d a0 fa ff ff    	mov    -0x560(%rbp),%ecx
    7f76ecc2dbb0:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2dbb3:	0b c1                	or     %ecx,%eax
    7f76ecc2dbb5:	8b 8d 90 fa ff ff    	mov    -0x570(%rbp),%ecx
    7f76ecc2dbbb:	8b c9                	mov    %ecx,%ecx
    7f76ecc2dbbd:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2dbc1:	8b c0                	mov    %eax,%eax
    7f76ecc2dbc3:	48 0b c8             	or     %rax,%rcx
    7f76ecc2dbc6:	8b 85 80 fa ff ff    	mov    -0x580(%rbp),%eax
    7f76ecc2dbcc:	8b c0                	mov    %eax,%eax
    7f76ecc2dbce:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2dbd2:	48 0b c8             	or     %rax,%rcx
    7f76ecc2dbd5:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7f76ecc2dbdb:	8b c0                	mov    %eax,%eax
    7f76ecc2dbdd:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2dbe1:	48 0b c8             	or     %rax,%rcx
    7f76ecc2dbe4:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7f76ecc2dbea:	8b c0                	mov    %eax,%eax
    7f76ecc2dbec:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2dbf0:	48 0b c8             	or     %rax,%rcx
    7f76ecc2dbf3:	49 89 8f b0 02 00 00 	mov    %rcx,0x2b0(%r15)
    7f76ecc2dbfa:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7f76ecc2dc00:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2dc03:	0b 85 50 fa ff ff    	or     -0x5b0(%rbp),%eax
    7f76ecc2dc09:	8b 8d 30 fa ff ff    	mov    -0x5d0(%rbp),%ecx
    7f76ecc2dc0f:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2dc12:	0b c1                	or     %ecx,%eax
    7f76ecc2dc14:	8b 8d 20 fa ff ff    	mov    -0x5e0(%rbp),%ecx
    7f76ecc2dc1a:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2dc1d:	0b c1                	or     %ecx,%eax
    7f76ecc2dc1f:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2dc22:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2dc26:	8b c0                	mov    %eax,%eax
    7f76ecc2dc28:	4c 0b c0             	or     %rax,%r8
    7f76ecc2dc2b:	8b ff                	mov    %edi,%edi
    7f76ecc2dc2d:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2dc31:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2dc34:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2dc37:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2dc3b:	4d 0b c1             	or     %r9,%r8
    7f76ecc2dc3e:	8b db                	mov    %ebx,%ebx
    7f76ecc2dc40:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2dc44:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2dc47:	4d 89 87 b8 02 00 00 	mov    %r8,0x2b8(%r15)
    7f76ecc2dc4e:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7f76ecc2dc54:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2dc59:	8b c0                	mov    %eax,%eax
    7f76ecc2dc5b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2dc60:	8b 8d f0 fa ff ff    	mov    -0x510(%rbp),%ecx
    7f76ecc2dc66:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2dc69:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2dc6f:	8b c9                	mov    %ecx,%ecx
    7f76ecc2dc71:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2dc76:	8b 95 f0 fa ff ff    	mov    -0x510(%rbp),%edx
    7f76ecc2dc7c:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2dc7f:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2dc85:	8b d2                	mov    %edx,%edx
    7f76ecc2dc87:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2dc8c:	8b 9d f0 fa ff ff    	mov    -0x510(%rbp),%ebx
    7f76ecc2dc92:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2dc95:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2dc9b:	8b db                	mov    %ebx,%ebx
    7f76ecc2dc9d:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2dca2:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2dca5:	0b da                	or     %edx,%ebx
    7f76ecc2dca7:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2dcaa:	0b d9                	or     %ecx,%ebx
    7f76ecc2dcac:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2dcaf:	0b d8                	or     %eax,%ebx
    7f76ecc2dcb1:	83 f3 20             	xor    $0x20,%ebx
    7f76ecc2dcb4:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7f76ecc2dcba:	33 d8                	xor    %eax,%ebx
    7f76ecc2dcbc:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7f76ecc2dcc2:	33 c3                	xor    %ebx,%eax
    7f76ecc2dcc4:	8b 8d e0 fa ff ff    	mov    -0x520(%rbp),%ecx
    7f76ecc2dcca:	33 c8                	xor    %eax,%ecx
    7f76ecc2dccc:	8b 95 f0 fa ff ff    	mov    -0x510(%rbp),%edx
    7f76ecc2dcd2:	33 d1                	xor    %ecx,%edx
    7f76ecc2dcd4:	8b f0                	mov    %eax,%esi
    7f76ecc2dcd6:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2dcda:	8b fb                	mov    %ebx,%edi
    7f76ecc2dcdc:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2dcdf:	49 89 b7 10 02 00 00 	mov    %rsi,0x210(%r15)
    7f76ecc2dce6:	8b f2                	mov    %edx,%esi
    7f76ecc2dce8:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2dcec:	8b f9                	mov    %ecx,%edi
    7f76ecc2dcee:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2dcf1:	49 89 b7 18 02 00 00 	mov    %rsi,0x218(%r15)
    7f76ecc2dcf8:	49 8b b7 b0 02 00 00 	mov    0x2b0(%r15),%rsi
    7f76ecc2dcff:	49 8b bf 10 02 00 00 	mov    0x210(%r15),%rdi
    7f76ecc2dd06:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2dd09:	49 89 b7 60 03 00 00 	mov    %rsi,0x360(%r15)
    7f76ecc2dd10:	49 8b b7 b8 02 00 00 	mov    0x2b8(%r15),%rsi
    7f76ecc2dd17:	49 8b bf 18 02 00 00 	mov    0x218(%r15),%rdi
    7f76ecc2dd1e:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2dd21:	49 89 b7 68 03 00 00 	mov    %rsi,0x368(%r15)
    7f76ecc2dd28:	49 0f b6 b7 60 01 00 	movzbq 0x160(%r15),%rsi
    7f76ecc2dd2f:	00 
    7f76ecc2dd30:	8b f6                	mov    %esi,%esi
    7f76ecc2dd32:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2dd37:	8b fe                	mov    %esi,%edi
    7f76ecc2dd39:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2dd3c:	d1 e7                	shl    %edi
    7f76ecc2dd3e:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2dd41:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2dd45:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2dd49:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2dd4c:	41 d1 e1             	shl    %r9d
    7f76ecc2dd4f:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2dd52:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2dd55:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2dd59:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2dd5c:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2dd60:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2dd63:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2dd66:	4d 0f b6 87 65 01 00 	movzbq 0x165(%r15),%r8
    7f76ecc2dd6d:	00 
    7f76ecc2dd6e:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2dd71:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2dd76:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2dd79:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2dd7d:	41 d1 e1             	shl    %r9d
    7f76ecc2dd80:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2dd83:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2dd87:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2dd8b:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2dd8e:	41 d1 e3             	shl    %r11d
    7f76ecc2dd91:	45 0b da             	or     %r10d,%r11d
    7f76ecc2dd94:	44 89 95 18 fa ff ff 	mov    %r10d,-0x5e8(%rbp)
    7f76ecc2dd9b:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2dd9f:	45 0b da             	or     %r10d,%r11d
    7f76ecc2dda2:	44 8b 95 18 fa ff ff 	mov    -0x5e8(%rbp),%r10d
    7f76ecc2dda9:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2ddad:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ddb0:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2ddb3:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2ddb6:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2ddb9:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2ddbc:	4d 0f b6 9f 6a 01 00 	movzbq 0x16a(%r15),%r11
    7f76ecc2ddc3:	00 
    7f76ecc2ddc4:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2ddc7:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2ddcc:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2ddcf:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7f76ecc2ddd5:	49 0f b6 87 6f 01 00 	movzbq 0x16f(%r15),%rax
    7f76ecc2dddc:	00 
    7f76ecc2dddd:	8b c0                	mov    %eax,%eax
    7f76ecc2dddf:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2dde4:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2dde7:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2ddea:	44 89 9d 08 fa ff ff 	mov    %r11d,-0x5f8(%rbp)
    7f76ecc2ddf1:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2ddf5:	41 d1 e3             	shl    %r11d
    7f76ecc2ddf8:	89 9d 00 fa ff ff    	mov    %ebx,-0x600(%rbp)
    7f76ecc2ddfe:	8b 9d 08 fa ff ff    	mov    -0x5f8(%rbp),%ebx
    7f76ecc2de04:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2de07:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2de0a:	89 9d f8 f9 ff ff    	mov    %ebx,-0x608(%rbp)
    7f76ecc2de10:	d1 e3                	shl    %ebx
    7f76ecc2de12:	89 95 f0 f9 ff ff    	mov    %edx,-0x610(%rbp)
    7f76ecc2de18:	8b 95 f8 f9 ff ff    	mov    -0x608(%rbp),%edx
    7f76ecc2de1e:	0b da                	or     %edx,%ebx
    7f76ecc2de20:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2de23:	0b da                	or     %edx,%ebx
    7f76ecc2de25:	8b 95 f8 f9 ff ff    	mov    -0x608(%rbp),%edx
    7f76ecc2de2b:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2de2e:	0b da                	or     %edx,%ebx
    7f76ecc2de30:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2de33:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2de36:	8b 9d 08 fa ff ff    	mov    -0x5f8(%rbp),%ebx
    7f76ecc2de3c:	33 d3                	xor    %ebx,%edx
    7f76ecc2de3e:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2de41:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2de44:	8b d6                	mov    %esi,%edx
    7f76ecc2de46:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2de49:	44 33 da             	xor    %edx,%r11d
    7f76ecc2de4c:	8b d0                	mov    %eax,%edx
    7f76ecc2de4e:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2de51:	d1 e2                	shl    %edx
    7f76ecc2de53:	8b d8                	mov    %eax,%ebx
    7f76ecc2de55:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2de58:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2de5b:	89 9d e8 f9 ff ff    	mov    %ebx,-0x618(%rbp)
    7f76ecc2de61:	d1 e3                	shl    %ebx
    7f76ecc2de63:	89 8d e0 f9 ff ff    	mov    %ecx,-0x620(%rbp)
    7f76ecc2de69:	8b 8d e8 f9 ff ff    	mov    -0x618(%rbp),%ecx
    7f76ecc2de6f:	0b d9                	or     %ecx,%ebx
    7f76ecc2de71:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2de74:	0b d9                	or     %ecx,%ebx
    7f76ecc2de76:	8b 8d e8 f9 ff ff    	mov    -0x618(%rbp),%ecx
    7f76ecc2de7c:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2de7f:	0b d9                	or     %ecx,%ebx
    7f76ecc2de81:	33 d3                	xor    %ebx,%edx
    7f76ecc2de83:	33 c2                	xor    %edx,%eax
    7f76ecc2de85:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2de88:	33 fe                	xor    %esi,%edi
    7f76ecc2de8a:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2de8d:	44 33 85 08 fa ff ff 	xor    -0x5f8(%rbp),%r8d
    7f76ecc2de94:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2de97:	49 0f b6 87 64 01 00 	movzbq 0x164(%r15),%rax
    7f76ecc2de9e:	00 
    7f76ecc2de9f:	8b c0                	mov    %eax,%eax
    7f76ecc2dea1:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2dea6:	8b c8                	mov    %eax,%ecx
    7f76ecc2dea8:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2deab:	d1 e1                	shl    %ecx
    7f76ecc2dead:	8b d8                	mov    %eax,%ebx
    7f76ecc2deaf:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2deb2:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2deb5:	8b f3                	mov    %ebx,%esi
    7f76ecc2deb7:	d1 e6                	shl    %esi
    7f76ecc2deb9:	0b f3                	or     %ebx,%esi
    7f76ecc2debb:	8b fb                	mov    %ebx,%edi
    7f76ecc2debd:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2dec0:	0b f7                	or     %edi,%esi
    7f76ecc2dec2:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2dec5:	0b f3                	or     %ebx,%esi
    7f76ecc2dec7:	33 ce                	xor    %esi,%ecx
    7f76ecc2dec9:	49 0f b6 9f 69 01 00 	movzbq 0x169(%r15),%rbx
    7f76ecc2ded0:	00 
    7f76ecc2ded1:	8b db                	mov    %ebx,%ebx
    7f76ecc2ded3:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2ded8:	8b f3                	mov    %ebx,%esi
    7f76ecc2deda:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2dedd:	d1 e6                	shl    %esi
    7f76ecc2dedf:	8b fb                	mov    %ebx,%edi
    7f76ecc2dee1:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2dee4:	83 e7 01             	and    $0x1,%edi
    7f76ecc2dee7:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2deea:	41 d1 e0             	shl    %r8d
    7f76ecc2deed:	44 0b c7             	or     %edi,%r8d
    7f76ecc2def0:	89 bd d8 f9 ff ff    	mov    %edi,-0x628(%rbp)
    7f76ecc2def6:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2def9:	44 0b c7             	or     %edi,%r8d
    7f76ecc2defc:	8b bd d8 f9 ff ff    	mov    -0x628(%rbp),%edi
    7f76ecc2df02:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2df05:	44 0b c7             	or     %edi,%r8d
    7f76ecc2df08:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2df0b:	8b fe                	mov    %esi,%edi
    7f76ecc2df0d:	33 fb                	xor    %ebx,%edi
    7f76ecc2df0f:	33 f9                	xor    %ecx,%edi
    7f76ecc2df11:	4d 0f b6 87 6e 01 00 	movzbq 0x16e(%r15),%r8
    7f76ecc2df18:	00 
    7f76ecc2df19:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2df1c:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2df21:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2df24:	44 89 95 d0 f9 ff ff 	mov    %r10d,-0x630(%rbp)
    7f76ecc2df2b:	4d 0f b6 97 63 01 00 	movzbq 0x163(%r15),%r10
    7f76ecc2df32:	00 
    7f76ecc2df33:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2df36:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2df3b:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2df3e:	33 f0                	xor    %eax,%esi
    7f76ecc2df40:	44 89 85 c8 f9 ff ff 	mov    %r8d,-0x638(%rbp)
    7f76ecc2df47:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2df4b:	41 d1 e0             	shl    %r8d
    7f76ecc2df4e:	44 89 8d c0 f9 ff ff 	mov    %r9d,-0x640(%rbp)
    7f76ecc2df55:	44 8b 8d c8 f9 ff ff 	mov    -0x638(%rbp),%r9d
    7f76ecc2df5c:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2df60:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2df64:	44 89 8d b8 f9 ff ff 	mov    %r9d,-0x648(%rbp)
    7f76ecc2df6b:	41 d1 e1             	shl    %r9d
    7f76ecc2df6e:	44 89 9d b0 f9 ff ff 	mov    %r11d,-0x650(%rbp)
    7f76ecc2df75:	44 8b 9d b8 f9 ff ff 	mov    -0x648(%rbp),%r11d
    7f76ecc2df7c:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2df7f:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2df83:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2df86:	44 8b 9d b8 f9 ff ff 	mov    -0x648(%rbp),%r11d
    7f76ecc2df8d:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2df91:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2df94:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2df97:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2df9a:	44 8b 9d c8 f9 ff ff 	mov    -0x638(%rbp),%r11d
    7f76ecc2dfa1:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2dfa4:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2dfa7:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2dfaa:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2dfad:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2dfb0:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2dfb3:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2dfb6:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2dfba:	41 d1 e1             	shl    %r9d
    7f76ecc2dfbd:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2dfc0:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2dfc4:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2dfc8:	44 89 9d a8 f9 ff ff 	mov    %r11d,-0x658(%rbp)
    7f76ecc2dfcf:	41 d1 e3             	shl    %r11d
    7f76ecc2dfd2:	89 95 a0 f9 ff ff    	mov    %edx,-0x660(%rbp)
    7f76ecc2dfd8:	8b 95 a8 f9 ff ff    	mov    -0x658(%rbp),%edx
    7f76ecc2dfde:	44 0b da             	or     %edx,%r11d
    7f76ecc2dfe1:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2dfe4:	44 0b da             	or     %edx,%r11d
    7f76ecc2dfe7:	8b 95 a8 f9 ff ff    	mov    -0x658(%rbp),%edx
    7f76ecc2dfed:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2dff0:	44 0b da             	or     %edx,%r11d
    7f76ecc2dff3:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2dff6:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2dff9:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2dffc:	33 c8                	xor    %eax,%ecx
    7f76ecc2dffe:	33 d9                	xor    %ecx,%ebx
    7f76ecc2e000:	33 9d c8 f9 ff ff    	xor    -0x638(%rbp),%ebx
    7f76ecc2e006:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e009:	49 0f b6 87 68 01 00 	movzbq 0x168(%r15),%rax
    7f76ecc2e010:	00 
    7f76ecc2e011:	8b c0                	mov    %eax,%eax
    7f76ecc2e013:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e018:	8b c8                	mov    %eax,%ecx
    7f76ecc2e01a:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2e01d:	d1 e1                	shl    %ecx
    7f76ecc2e01f:	8b d0                	mov    %eax,%edx
    7f76ecc2e021:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2e024:	83 e2 01             	and    $0x1,%edx
    7f76ecc2e027:	8b da                	mov    %edx,%ebx
    7f76ecc2e029:	d1 e3                	shl    %ebx
    7f76ecc2e02b:	0b da                	or     %edx,%ebx
    7f76ecc2e02d:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2e030:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2e034:	41 0b da             	or     %r10d,%ebx
    7f76ecc2e037:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2e03a:	0b da                	or     %edx,%ebx
    7f76ecc2e03c:	33 cb                	xor    %ebx,%ecx
    7f76ecc2e03e:	49 0f b6 97 6d 01 00 	movzbq 0x16d(%r15),%rdx
    7f76ecc2e045:	00 
    7f76ecc2e046:	8b d2                	mov    %edx,%edx
    7f76ecc2e048:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2e04d:	8b da                	mov    %edx,%ebx
    7f76ecc2e04f:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2e052:	d1 e3                	shl    %ebx
    7f76ecc2e054:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2e057:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2e05b:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2e05f:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2e062:	41 d1 e3             	shl    %r11d
    7f76ecc2e065:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e068:	44 89 95 98 f9 ff ff 	mov    %r10d,-0x668(%rbp)
    7f76ecc2e06f:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2e073:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e076:	44 8b 95 98 f9 ff ff 	mov    -0x668(%rbp),%r10d
    7f76ecc2e07d:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2e081:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e084:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2e087:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2e08a:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2e08d:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2e090:	4d 0f b6 9f 62 01 00 	movzbq 0x162(%r15),%r11
    7f76ecc2e097:	00 
    7f76ecc2e098:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2e09b:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2e0a0:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2e0a3:	89 bd 90 f9 ff ff    	mov    %edi,-0x670(%rbp)
    7f76ecc2e0a9:	49 0f b6 bf 67 01 00 	movzbq 0x167(%r15),%rdi
    7f76ecc2e0b0:	00 
    7f76ecc2e0b1:	8b ff                	mov    %edi,%edi
    7f76ecc2e0b3:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2e0b8:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2e0bb:	33 d8                	xor    %eax,%ebx
    7f76ecc2e0bd:	44 89 9d 88 f9 ff ff 	mov    %r11d,-0x678(%rbp)
    7f76ecc2e0c4:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2e0c8:	41 d1 e3             	shl    %r11d
    7f76ecc2e0cb:	89 b5 80 f9 ff ff    	mov    %esi,-0x680(%rbp)
    7f76ecc2e0d1:	8b b5 88 f9 ff ff    	mov    -0x678(%rbp),%esi
    7f76ecc2e0d7:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2e0da:	83 e6 01             	and    $0x1,%esi
    7f76ecc2e0dd:	89 b5 78 f9 ff ff    	mov    %esi,-0x688(%rbp)
    7f76ecc2e0e3:	d1 e6                	shl    %esi
    7f76ecc2e0e5:	44 89 85 70 f9 ff ff 	mov    %r8d,-0x690(%rbp)
    7f76ecc2e0ec:	44 8b 85 78 f9 ff ff 	mov    -0x688(%rbp),%r8d
    7f76ecc2e0f3:	41 0b f0             	or     %r8d,%esi
    7f76ecc2e0f6:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2e0fa:	41 0b f0             	or     %r8d,%esi
    7f76ecc2e0fd:	44 8b 85 78 f9 ff ff 	mov    -0x688(%rbp),%r8d
    7f76ecc2e104:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2e108:	41 0b f0             	or     %r8d,%esi
    7f76ecc2e10b:	44 33 de             	xor    %esi,%r11d
    7f76ecc2e10e:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2e111:	44 8b 85 88 f9 ff ff 	mov    -0x678(%rbp),%r8d
    7f76ecc2e118:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2e11b:	33 de                	xor    %esi,%ebx
    7f76ecc2e11d:	33 df                	xor    %edi,%ebx
    7f76ecc2e11f:	8b f0                	mov    %eax,%esi
    7f76ecc2e121:	33 f2                	xor    %edx,%esi
    7f76ecc2e123:	44 33 de             	xor    %esi,%r11d
    7f76ecc2e126:	8b f7                	mov    %edi,%esi
    7f76ecc2e128:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2e12b:	d1 e6                	shl    %esi
    7f76ecc2e12d:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2e130:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2e134:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2e138:	44 89 85 68 f9 ff ff 	mov    %r8d,-0x698(%rbp)
    7f76ecc2e13f:	41 d1 e0             	shl    %r8d
    7f76ecc2e142:	44 89 8d 60 f9 ff ff 	mov    %r9d,-0x6a0(%rbp)
    7f76ecc2e149:	44 8b 8d 68 f9 ff ff 	mov    -0x698(%rbp),%r9d
    7f76ecc2e150:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2e153:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2e157:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2e15a:	44 8b 8d 68 f9 ff ff 	mov    -0x698(%rbp),%r9d
    7f76ecc2e161:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2e165:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2e168:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2e16b:	33 fe                	xor    %esi,%edi
    7f76ecc2e16d:	44 33 df             	xor    %edi,%r11d
    7f76ecc2e170:	33 c8                	xor    %eax,%ecx
    7f76ecc2e172:	33 d1                	xor    %ecx,%edx
    7f76ecc2e174:	33 95 88 f9 ff ff    	xor    -0x678(%rbp),%edx
    7f76ecc2e17a:	33 f2                	xor    %edx,%esi
    7f76ecc2e17c:	49 0f b6 87 6c 01 00 	movzbq 0x16c(%r15),%rax
    7f76ecc2e183:	00 
    7f76ecc2e184:	8b c0                	mov    %eax,%eax
    7f76ecc2e186:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e18b:	8b c8                	mov    %eax,%ecx
    7f76ecc2e18d:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2e190:	d1 e1                	shl    %ecx
    7f76ecc2e192:	8b d0                	mov    %eax,%edx
    7f76ecc2e194:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2e197:	83 e2 01             	and    $0x1,%edx
    7f76ecc2e19a:	8b fa                	mov    %edx,%edi
    7f76ecc2e19c:	d1 e7                	shl    %edi
    7f76ecc2e19e:	0b fa                	or     %edx,%edi
    7f76ecc2e1a0:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2e1a3:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2e1a7:	41 0b f8             	or     %r8d,%edi
    7f76ecc2e1aa:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2e1ad:	0b fa                	or     %edx,%edi
    7f76ecc2e1af:	33 cf                	xor    %edi,%ecx
    7f76ecc2e1b1:	49 0f b6 97 61 01 00 	movzbq 0x161(%r15),%rdx
    7f76ecc2e1b8:	00 
    7f76ecc2e1b9:	8b d2                	mov    %edx,%edx
    7f76ecc2e1bb:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2e1c0:	8b fa                	mov    %edx,%edi
    7f76ecc2e1c2:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2e1c5:	d1 e7                	shl    %edi
    7f76ecc2e1c7:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2e1ca:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2e1ce:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2e1d2:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2e1d5:	41 d1 e1             	shl    %r9d
    7f76ecc2e1d8:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e1db:	44 89 85 58 f9 ff ff 	mov    %r8d,-0x6a8(%rbp)
    7f76ecc2e1e2:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2e1e6:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e1e9:	44 8b 85 58 f9 ff ff 	mov    -0x6a8(%rbp),%r8d
    7f76ecc2e1f0:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2e1f4:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e1f7:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2e1fa:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2e1fd:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2e200:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2e203:	4d 0f b6 8f 66 01 00 	movzbq 0x166(%r15),%r9
    7f76ecc2e20a:	00 
    7f76ecc2e20b:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2e20e:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2e213:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2e216:	44 89 95 50 f9 ff ff 	mov    %r10d,-0x6b0(%rbp)
    7f76ecc2e21d:	4d 0f b6 97 6b 01 00 	movzbq 0x16b(%r15),%r10
    7f76ecc2e224:	00 
    7f76ecc2e225:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2e228:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2e22d:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2e230:	33 f8                	xor    %eax,%edi
    7f76ecc2e232:	44 89 8d 48 f9 ff ff 	mov    %r9d,-0x6b8(%rbp)
    7f76ecc2e239:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2e23d:	41 d1 e1             	shl    %r9d
    7f76ecc2e240:	89 9d 40 f9 ff ff    	mov    %ebx,-0x6c0(%rbp)
    7f76ecc2e246:	8b 9d 48 f9 ff ff    	mov    -0x6b8(%rbp),%ebx
    7f76ecc2e24c:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2e24f:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2e252:	89 9d 38 f9 ff ff    	mov    %ebx,-0x6c8(%rbp)
    7f76ecc2e258:	d1 e3                	shl    %ebx
    7f76ecc2e25a:	44 89 9d 30 f9 ff ff 	mov    %r11d,-0x6d0(%rbp)
    7f76ecc2e261:	44 8b 9d 38 f9 ff ff 	mov    -0x6c8(%rbp),%r11d
    7f76ecc2e268:	41 0b db             	or     %r11d,%ebx
    7f76ecc2e26b:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2e26f:	41 0b db             	or     %r11d,%ebx
    7f76ecc2e272:	44 8b 9d 38 f9 ff ff 	mov    -0x6c8(%rbp),%r11d
    7f76ecc2e279:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2e27d:	41 0b db             	or     %r11d,%ebx
    7f76ecc2e280:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e283:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2e286:	44 8b 9d 48 f9 ff ff 	mov    -0x6b8(%rbp),%r11d
    7f76ecc2e28d:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2e290:	33 fb                	xor    %ebx,%edi
    7f76ecc2e292:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2e295:	8b d8                	mov    %eax,%ebx
    7f76ecc2e297:	33 da                	xor    %edx,%ebx
    7f76ecc2e299:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e29c:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2e29f:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2e2a2:	d1 e3                	shl    %ebx
    7f76ecc2e2a4:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2e2a7:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2e2ab:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2e2af:	44 89 9d 28 f9 ff ff 	mov    %r11d,-0x6d8(%rbp)
    7f76ecc2e2b6:	41 d1 e3             	shl    %r11d
    7f76ecc2e2b9:	89 b5 20 f9 ff ff    	mov    %esi,-0x6e0(%rbp)
    7f76ecc2e2bf:	8b b5 28 f9 ff ff    	mov    -0x6d8(%rbp),%esi
    7f76ecc2e2c5:	44 0b de             	or     %esi,%r11d
    7f76ecc2e2c8:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2e2cb:	44 0b de             	or     %esi,%r11d
    7f76ecc2e2ce:	8b b5 28 f9 ff ff    	mov    -0x6d8(%rbp),%esi
    7f76ecc2e2d4:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2e2d7:	44 0b de             	or     %esi,%r11d
    7f76ecc2e2da:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2e2dd:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2e2e0:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2e2e3:	33 c8                	xor    %eax,%ecx
    7f76ecc2e2e5:	33 d1                	xor    %ecx,%edx
    7f76ecc2e2e7:	33 95 48 f9 ff ff    	xor    -0x6b8(%rbp),%edx
    7f76ecc2e2ed:	33 da                	xor    %edx,%ebx
    7f76ecc2e2ef:	8b 85 c0 f9 ff ff    	mov    -0x640(%rbp),%eax
    7f76ecc2e2f5:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2e2f8:	0b 85 d0 f9 ff ff    	or     -0x630(%rbp),%eax
    7f76ecc2e2fe:	8b 8d b0 f9 ff ff    	mov    -0x650(%rbp),%ecx
    7f76ecc2e304:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2e307:	0b c1                	or     %ecx,%eax
    7f76ecc2e309:	8b 8d a0 f9 ff ff    	mov    -0x660(%rbp),%ecx
    7f76ecc2e30f:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2e312:	0b c1                	or     %ecx,%eax
    7f76ecc2e314:	8b 8d 90 f9 ff ff    	mov    -0x670(%rbp),%ecx
    7f76ecc2e31a:	8b c9                	mov    %ecx,%ecx
    7f76ecc2e31c:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2e320:	8b c0                	mov    %eax,%eax
    7f76ecc2e322:	48 0b c8             	or     %rax,%rcx
    7f76ecc2e325:	8b 85 80 f9 ff ff    	mov    -0x680(%rbp),%eax
    7f76ecc2e32b:	8b c0                	mov    %eax,%eax
    7f76ecc2e32d:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2e331:	48 0b c8             	or     %rax,%rcx
    7f76ecc2e334:	8b 85 70 f9 ff ff    	mov    -0x690(%rbp),%eax
    7f76ecc2e33a:	8b c0                	mov    %eax,%eax
    7f76ecc2e33c:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2e340:	48 0b c8             	or     %rax,%rcx
    7f76ecc2e343:	8b 85 60 f9 ff ff    	mov    -0x6a0(%rbp),%eax
    7f76ecc2e349:	8b c0                	mov    %eax,%eax
    7f76ecc2e34b:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2e34f:	48 0b c8             	or     %rax,%rcx
    7f76ecc2e352:	49 89 8f c0 02 00 00 	mov    %rcx,0x2c0(%r15)
    7f76ecc2e359:	8b 85 40 f9 ff ff    	mov    -0x6c0(%rbp),%eax
    7f76ecc2e35f:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2e362:	0b 85 50 f9 ff ff    	or     -0x6b0(%rbp),%eax
    7f76ecc2e368:	8b 8d 30 f9 ff ff    	mov    -0x6d0(%rbp),%ecx
    7f76ecc2e36e:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2e371:	0b c1                	or     %ecx,%eax
    7f76ecc2e373:	8b 8d 20 f9 ff ff    	mov    -0x6e0(%rbp),%ecx
    7f76ecc2e379:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2e37c:	0b c1                	or     %ecx,%eax
    7f76ecc2e37e:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2e381:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2e385:	8b c0                	mov    %eax,%eax
    7f76ecc2e387:	4c 0b c0             	or     %rax,%r8
    7f76ecc2e38a:	8b ff                	mov    %edi,%edi
    7f76ecc2e38c:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2e390:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2e393:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2e396:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2e39a:	4d 0b c1             	or     %r9,%r8
    7f76ecc2e39d:	8b db                	mov    %ebx,%ebx
    7f76ecc2e39f:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2e3a3:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2e3a6:	4d 89 87 c8 02 00 00 	mov    %r8,0x2c8(%r15)
    7f76ecc2e3ad:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7f76ecc2e3b3:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2e3b8:	8b c0                	mov    %eax,%eax
    7f76ecc2e3ba:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e3bf:	8b 8d f0 f9 ff ff    	mov    -0x610(%rbp),%ecx
    7f76ecc2e3c5:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2e3c8:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2e3ce:	8b c9                	mov    %ecx,%ecx
    7f76ecc2e3d0:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2e3d5:	8b 95 f0 f9 ff ff    	mov    -0x610(%rbp),%edx
    7f76ecc2e3db:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2e3de:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2e3e4:	8b d2                	mov    %edx,%edx
    7f76ecc2e3e6:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2e3eb:	8b 9d f0 f9 ff ff    	mov    -0x610(%rbp),%ebx
    7f76ecc2e3f1:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2e3f4:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2e3fa:	8b db                	mov    %ebx,%ebx
    7f76ecc2e3fc:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2e401:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2e404:	0b da                	or     %edx,%ebx
    7f76ecc2e406:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2e409:	0b d9                	or     %ecx,%ebx
    7f76ecc2e40b:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2e40e:	0b d8                	or     %eax,%ebx
    7f76ecc2e410:	83 f3 40             	xor    $0x40,%ebx
    7f76ecc2e413:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7f76ecc2e419:	33 d8                	xor    %eax,%ebx
    7f76ecc2e41b:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7f76ecc2e421:	33 c3                	xor    %ebx,%eax
    7f76ecc2e423:	8b 8d e0 f9 ff ff    	mov    -0x620(%rbp),%ecx
    7f76ecc2e429:	33 c8                	xor    %eax,%ecx
    7f76ecc2e42b:	8b 95 f0 f9 ff ff    	mov    -0x610(%rbp),%edx
    7f76ecc2e431:	33 d1                	xor    %ecx,%edx
    7f76ecc2e433:	8b f0                	mov    %eax,%esi
    7f76ecc2e435:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2e439:	8b fb                	mov    %ebx,%edi
    7f76ecc2e43b:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2e43e:	49 89 b7 20 02 00 00 	mov    %rsi,0x220(%r15)
    7f76ecc2e445:	8b f2                	mov    %edx,%esi
    7f76ecc2e447:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2e44b:	8b f9                	mov    %ecx,%edi
    7f76ecc2e44d:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2e450:	49 89 b7 28 02 00 00 	mov    %rsi,0x228(%r15)
    7f76ecc2e457:	49 8b b7 c0 02 00 00 	mov    0x2c0(%r15),%rsi
    7f76ecc2e45e:	49 8b bf 20 02 00 00 	mov    0x220(%r15),%rdi
    7f76ecc2e465:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2e468:	49 89 b7 70 03 00 00 	mov    %rsi,0x370(%r15)
    7f76ecc2e46f:	49 8b b7 c8 02 00 00 	mov    0x2c8(%r15),%rsi
    7f76ecc2e476:	49 8b bf 28 02 00 00 	mov    0x228(%r15),%rdi
    7f76ecc2e47d:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2e480:	49 89 b7 78 03 00 00 	mov    %rsi,0x378(%r15)
    7f76ecc2e487:	49 0f b6 b7 70 01 00 	movzbq 0x170(%r15),%rsi
    7f76ecc2e48e:	00 
    7f76ecc2e48f:	8b f6                	mov    %esi,%esi
    7f76ecc2e491:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2e496:	8b fe                	mov    %esi,%edi
    7f76ecc2e498:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2e49b:	d1 e7                	shl    %edi
    7f76ecc2e49d:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2e4a0:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2e4a4:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2e4a8:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2e4ab:	41 d1 e1             	shl    %r9d
    7f76ecc2e4ae:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e4b1:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2e4b4:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2e4b8:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2e4bb:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2e4bf:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e4c2:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2e4c5:	4d 0f b6 87 75 01 00 	movzbq 0x175(%r15),%r8
    7f76ecc2e4cc:	00 
    7f76ecc2e4cd:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2e4d0:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2e4d5:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2e4d8:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2e4dc:	41 d1 e1             	shl    %r9d
    7f76ecc2e4df:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2e4e2:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2e4e6:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2e4ea:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2e4ed:	41 d1 e3             	shl    %r11d
    7f76ecc2e4f0:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e4f3:	44 89 95 18 f9 ff ff 	mov    %r10d,-0x6e8(%rbp)
    7f76ecc2e4fa:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2e4fe:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e501:	44 8b 95 18 f9 ff ff 	mov    -0x6e8(%rbp),%r10d
    7f76ecc2e508:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2e50c:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e50f:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2e512:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2e515:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2e518:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2e51b:	4d 0f b6 9f 7a 01 00 	movzbq 0x17a(%r15),%r11
    7f76ecc2e522:	00 
    7f76ecc2e523:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2e526:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2e52b:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2e52e:	89 85 10 f9 ff ff    	mov    %eax,-0x6f0(%rbp)
    7f76ecc2e534:	49 0f b6 87 7f 01 00 	movzbq 0x17f(%r15),%rax
    7f76ecc2e53b:	00 
    7f76ecc2e53c:	8b c0                	mov    %eax,%eax
    7f76ecc2e53e:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e543:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2e546:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2e549:	44 89 9d 08 f9 ff ff 	mov    %r11d,-0x6f8(%rbp)
    7f76ecc2e550:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2e554:	41 d1 e3             	shl    %r11d
    7f76ecc2e557:	89 9d 00 f9 ff ff    	mov    %ebx,-0x700(%rbp)
    7f76ecc2e55d:	8b 9d 08 f9 ff ff    	mov    -0x6f8(%rbp),%ebx
    7f76ecc2e563:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2e566:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2e569:	89 9d f8 f8 ff ff    	mov    %ebx,-0x708(%rbp)
    7f76ecc2e56f:	d1 e3                	shl    %ebx
    7f76ecc2e571:	89 95 f0 f8 ff ff    	mov    %edx,-0x710(%rbp)
    7f76ecc2e577:	8b 95 f8 f8 ff ff    	mov    -0x708(%rbp),%edx
    7f76ecc2e57d:	0b da                	or     %edx,%ebx
    7f76ecc2e57f:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2e582:	0b da                	or     %edx,%ebx
    7f76ecc2e584:	8b 95 f8 f8 ff ff    	mov    -0x708(%rbp),%edx
    7f76ecc2e58a:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2e58d:	0b da                	or     %edx,%ebx
    7f76ecc2e58f:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2e592:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2e595:	8b 9d 08 f9 ff ff    	mov    -0x6f8(%rbp),%ebx
    7f76ecc2e59b:	33 d3                	xor    %ebx,%edx
    7f76ecc2e59d:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2e5a0:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2e5a3:	8b d6                	mov    %esi,%edx
    7f76ecc2e5a5:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2e5a8:	44 33 da             	xor    %edx,%r11d
    7f76ecc2e5ab:	8b d0                	mov    %eax,%edx
    7f76ecc2e5ad:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2e5b0:	d1 e2                	shl    %edx
    7f76ecc2e5b2:	8b d8                	mov    %eax,%ebx
    7f76ecc2e5b4:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2e5b7:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2e5ba:	89 9d e8 f8 ff ff    	mov    %ebx,-0x718(%rbp)
    7f76ecc2e5c0:	d1 e3                	shl    %ebx
    7f76ecc2e5c2:	89 8d e0 f8 ff ff    	mov    %ecx,-0x720(%rbp)
    7f76ecc2e5c8:	8b 8d e8 f8 ff ff    	mov    -0x718(%rbp),%ecx
    7f76ecc2e5ce:	0b d9                	or     %ecx,%ebx
    7f76ecc2e5d0:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2e5d3:	0b d9                	or     %ecx,%ebx
    7f76ecc2e5d5:	8b 8d e8 f8 ff ff    	mov    -0x718(%rbp),%ecx
    7f76ecc2e5db:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2e5de:	0b d9                	or     %ecx,%ebx
    7f76ecc2e5e0:	33 d3                	xor    %ebx,%edx
    7f76ecc2e5e2:	33 c2                	xor    %edx,%eax
    7f76ecc2e5e4:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2e5e7:	33 fe                	xor    %esi,%edi
    7f76ecc2e5e9:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2e5ec:	44 33 85 08 f9 ff ff 	xor    -0x6f8(%rbp),%r8d
    7f76ecc2e5f3:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2e5f6:	49 0f b6 87 74 01 00 	movzbq 0x174(%r15),%rax
    7f76ecc2e5fd:	00 
    7f76ecc2e5fe:	8b c0                	mov    %eax,%eax
    7f76ecc2e600:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e605:	8b c8                	mov    %eax,%ecx
    7f76ecc2e607:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2e60a:	d1 e1                	shl    %ecx
    7f76ecc2e60c:	8b d8                	mov    %eax,%ebx
    7f76ecc2e60e:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2e611:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2e614:	8b f3                	mov    %ebx,%esi
    7f76ecc2e616:	d1 e6                	shl    %esi
    7f76ecc2e618:	0b f3                	or     %ebx,%esi
    7f76ecc2e61a:	8b fb                	mov    %ebx,%edi
    7f76ecc2e61c:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2e61f:	0b f7                	or     %edi,%esi
    7f76ecc2e621:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2e624:	0b f3                	or     %ebx,%esi
    7f76ecc2e626:	33 ce                	xor    %esi,%ecx
    7f76ecc2e628:	49 0f b6 9f 79 01 00 	movzbq 0x179(%r15),%rbx
    7f76ecc2e62f:	00 
    7f76ecc2e630:	8b db                	mov    %ebx,%ebx
    7f76ecc2e632:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2e637:	8b f3                	mov    %ebx,%esi
    7f76ecc2e639:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2e63c:	d1 e6                	shl    %esi
    7f76ecc2e63e:	8b fb                	mov    %ebx,%edi
    7f76ecc2e640:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2e643:	83 e7 01             	and    $0x1,%edi
    7f76ecc2e646:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2e649:	41 d1 e0             	shl    %r8d
    7f76ecc2e64c:	44 0b c7             	or     %edi,%r8d
    7f76ecc2e64f:	89 bd d8 f8 ff ff    	mov    %edi,-0x728(%rbp)
    7f76ecc2e655:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2e658:	44 0b c7             	or     %edi,%r8d
    7f76ecc2e65b:	8b bd d8 f8 ff ff    	mov    -0x728(%rbp),%edi
    7f76ecc2e661:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2e664:	44 0b c7             	or     %edi,%r8d
    7f76ecc2e667:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2e66a:	8b fe                	mov    %esi,%edi
    7f76ecc2e66c:	33 fb                	xor    %ebx,%edi
    7f76ecc2e66e:	33 f9                	xor    %ecx,%edi
    7f76ecc2e670:	4d 0f b6 87 7e 01 00 	movzbq 0x17e(%r15),%r8
    7f76ecc2e677:	00 
    7f76ecc2e678:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2e67b:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2e680:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2e683:	44 89 95 d0 f8 ff ff 	mov    %r10d,-0x730(%rbp)
    7f76ecc2e68a:	4d 0f b6 97 73 01 00 	movzbq 0x173(%r15),%r10
    7f76ecc2e691:	00 
    7f76ecc2e692:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2e695:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2e69a:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2e69d:	33 f0                	xor    %eax,%esi
    7f76ecc2e69f:	44 89 85 c8 f8 ff ff 	mov    %r8d,-0x738(%rbp)
    7f76ecc2e6a6:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2e6aa:	41 d1 e0             	shl    %r8d
    7f76ecc2e6ad:	44 89 8d c0 f8 ff ff 	mov    %r9d,-0x740(%rbp)
    7f76ecc2e6b4:	44 8b 8d c8 f8 ff ff 	mov    -0x738(%rbp),%r9d
    7f76ecc2e6bb:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2e6bf:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2e6c3:	44 89 8d b8 f8 ff ff 	mov    %r9d,-0x748(%rbp)
    7f76ecc2e6ca:	41 d1 e1             	shl    %r9d
    7f76ecc2e6cd:	44 89 9d b0 f8 ff ff 	mov    %r11d,-0x750(%rbp)
    7f76ecc2e6d4:	44 8b 9d b8 f8 ff ff 	mov    -0x748(%rbp),%r11d
    7f76ecc2e6db:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2e6de:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2e6e2:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2e6e5:	44 8b 9d b8 f8 ff ff 	mov    -0x748(%rbp),%r11d
    7f76ecc2e6ec:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2e6f0:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2e6f3:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2e6f6:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2e6f9:	44 8b 9d c8 f8 ff ff 	mov    -0x738(%rbp),%r11d
    7f76ecc2e700:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2e703:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2e706:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2e709:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2e70c:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e70f:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2e712:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2e715:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2e719:	41 d1 e1             	shl    %r9d
    7f76ecc2e71c:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2e71f:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2e723:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2e727:	44 89 9d a8 f8 ff ff 	mov    %r11d,-0x758(%rbp)
    7f76ecc2e72e:	41 d1 e3             	shl    %r11d
    7f76ecc2e731:	89 95 a0 f8 ff ff    	mov    %edx,-0x760(%rbp)
    7f76ecc2e737:	8b 95 a8 f8 ff ff    	mov    -0x758(%rbp),%edx
    7f76ecc2e73d:	44 0b da             	or     %edx,%r11d
    7f76ecc2e740:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2e743:	44 0b da             	or     %edx,%r11d
    7f76ecc2e746:	8b 95 a8 f8 ff ff    	mov    -0x758(%rbp),%edx
    7f76ecc2e74c:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2e74f:	44 0b da             	or     %edx,%r11d
    7f76ecc2e752:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2e755:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2e758:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2e75b:	33 c8                	xor    %eax,%ecx
    7f76ecc2e75d:	33 d9                	xor    %ecx,%ebx
    7f76ecc2e75f:	33 9d c8 f8 ff ff    	xor    -0x738(%rbp),%ebx
    7f76ecc2e765:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e768:	49 0f b6 87 78 01 00 	movzbq 0x178(%r15),%rax
    7f76ecc2e76f:	00 
    7f76ecc2e770:	8b c0                	mov    %eax,%eax
    7f76ecc2e772:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e777:	8b c8                	mov    %eax,%ecx
    7f76ecc2e779:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2e77c:	d1 e1                	shl    %ecx
    7f76ecc2e77e:	8b d0                	mov    %eax,%edx
    7f76ecc2e780:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2e783:	83 e2 01             	and    $0x1,%edx
    7f76ecc2e786:	8b da                	mov    %edx,%ebx
    7f76ecc2e788:	d1 e3                	shl    %ebx
    7f76ecc2e78a:	0b da                	or     %edx,%ebx
    7f76ecc2e78c:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2e78f:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2e793:	41 0b da             	or     %r10d,%ebx
    7f76ecc2e796:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2e799:	0b da                	or     %edx,%ebx
    7f76ecc2e79b:	33 cb                	xor    %ebx,%ecx
    7f76ecc2e79d:	49 0f b6 97 7d 01 00 	movzbq 0x17d(%r15),%rdx
    7f76ecc2e7a4:	00 
    7f76ecc2e7a5:	8b d2                	mov    %edx,%edx
    7f76ecc2e7a7:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2e7ac:	8b da                	mov    %edx,%ebx
    7f76ecc2e7ae:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2e7b1:	d1 e3                	shl    %ebx
    7f76ecc2e7b3:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2e7b6:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2e7ba:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2e7be:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2e7c1:	41 d1 e3             	shl    %r11d
    7f76ecc2e7c4:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e7c7:	44 89 95 98 f8 ff ff 	mov    %r10d,-0x768(%rbp)
    7f76ecc2e7ce:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2e7d2:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e7d5:	44 8b 95 98 f8 ff ff 	mov    -0x768(%rbp),%r10d
    7f76ecc2e7dc:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2e7e0:	45 0b da             	or     %r10d,%r11d
    7f76ecc2e7e3:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2e7e6:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2e7e9:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2e7ec:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2e7ef:	4d 0f b6 9f 72 01 00 	movzbq 0x172(%r15),%r11
    7f76ecc2e7f6:	00 
    7f76ecc2e7f7:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2e7fa:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2e7ff:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2e802:	89 bd 90 f8 ff ff    	mov    %edi,-0x770(%rbp)
    7f76ecc2e808:	49 0f b6 bf 77 01 00 	movzbq 0x177(%r15),%rdi
    7f76ecc2e80f:	00 
    7f76ecc2e810:	8b ff                	mov    %edi,%edi
    7f76ecc2e812:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2e817:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2e81a:	33 d8                	xor    %eax,%ebx
    7f76ecc2e81c:	44 89 9d 88 f8 ff ff 	mov    %r11d,-0x778(%rbp)
    7f76ecc2e823:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2e827:	41 d1 e3             	shl    %r11d
    7f76ecc2e82a:	89 b5 80 f8 ff ff    	mov    %esi,-0x780(%rbp)
    7f76ecc2e830:	8b b5 88 f8 ff ff    	mov    -0x778(%rbp),%esi
    7f76ecc2e836:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2e839:	83 e6 01             	and    $0x1,%esi
    7f76ecc2e83c:	89 b5 78 f8 ff ff    	mov    %esi,-0x788(%rbp)
    7f76ecc2e842:	d1 e6                	shl    %esi
    7f76ecc2e844:	44 89 85 70 f8 ff ff 	mov    %r8d,-0x790(%rbp)
    7f76ecc2e84b:	44 8b 85 78 f8 ff ff 	mov    -0x788(%rbp),%r8d
    7f76ecc2e852:	41 0b f0             	or     %r8d,%esi
    7f76ecc2e855:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2e859:	41 0b f0             	or     %r8d,%esi
    7f76ecc2e85c:	44 8b 85 78 f8 ff ff 	mov    -0x788(%rbp),%r8d
    7f76ecc2e863:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2e867:	41 0b f0             	or     %r8d,%esi
    7f76ecc2e86a:	44 33 de             	xor    %esi,%r11d
    7f76ecc2e86d:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2e870:	44 8b 85 88 f8 ff ff 	mov    -0x778(%rbp),%r8d
    7f76ecc2e877:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2e87a:	33 de                	xor    %esi,%ebx
    7f76ecc2e87c:	33 df                	xor    %edi,%ebx
    7f76ecc2e87e:	8b f0                	mov    %eax,%esi
    7f76ecc2e880:	33 f2                	xor    %edx,%esi
    7f76ecc2e882:	44 33 de             	xor    %esi,%r11d
    7f76ecc2e885:	8b f7                	mov    %edi,%esi
    7f76ecc2e887:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2e88a:	d1 e6                	shl    %esi
    7f76ecc2e88c:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2e88f:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2e893:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2e897:	44 89 85 68 f8 ff ff 	mov    %r8d,-0x798(%rbp)
    7f76ecc2e89e:	41 d1 e0             	shl    %r8d
    7f76ecc2e8a1:	44 89 8d 60 f8 ff ff 	mov    %r9d,-0x7a0(%rbp)
    7f76ecc2e8a8:	44 8b 8d 68 f8 ff ff 	mov    -0x798(%rbp),%r9d
    7f76ecc2e8af:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2e8b2:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2e8b6:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2e8b9:	44 8b 8d 68 f8 ff ff 	mov    -0x798(%rbp),%r9d
    7f76ecc2e8c0:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2e8c4:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2e8c7:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2e8ca:	33 fe                	xor    %esi,%edi
    7f76ecc2e8cc:	44 33 df             	xor    %edi,%r11d
    7f76ecc2e8cf:	33 c8                	xor    %eax,%ecx
    7f76ecc2e8d1:	33 d1                	xor    %ecx,%edx
    7f76ecc2e8d3:	33 95 88 f8 ff ff    	xor    -0x778(%rbp),%edx
    7f76ecc2e8d9:	33 f2                	xor    %edx,%esi
    7f76ecc2e8db:	49 0f b6 87 7c 01 00 	movzbq 0x17c(%r15),%rax
    7f76ecc2e8e2:	00 
    7f76ecc2e8e3:	8b c0                	mov    %eax,%eax
    7f76ecc2e8e5:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2e8ea:	8b c8                	mov    %eax,%ecx
    7f76ecc2e8ec:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2e8ef:	d1 e1                	shl    %ecx
    7f76ecc2e8f1:	8b d0                	mov    %eax,%edx
    7f76ecc2e8f3:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2e8f6:	83 e2 01             	and    $0x1,%edx
    7f76ecc2e8f9:	8b fa                	mov    %edx,%edi
    7f76ecc2e8fb:	d1 e7                	shl    %edi
    7f76ecc2e8fd:	0b fa                	or     %edx,%edi
    7f76ecc2e8ff:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2e902:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2e906:	41 0b f8             	or     %r8d,%edi
    7f76ecc2e909:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2e90c:	0b fa                	or     %edx,%edi
    7f76ecc2e90e:	33 cf                	xor    %edi,%ecx
    7f76ecc2e910:	49 0f b6 97 71 01 00 	movzbq 0x171(%r15),%rdx
    7f76ecc2e917:	00 
    7f76ecc2e918:	8b d2                	mov    %edx,%edx
    7f76ecc2e91a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2e91f:	8b fa                	mov    %edx,%edi
    7f76ecc2e921:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2e924:	d1 e7                	shl    %edi
    7f76ecc2e926:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2e929:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2e92d:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2e931:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2e934:	41 d1 e1             	shl    %r9d
    7f76ecc2e937:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e93a:	44 89 85 58 f8 ff ff 	mov    %r8d,-0x7a8(%rbp)
    7f76ecc2e941:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2e945:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e948:	44 8b 85 58 f8 ff ff 	mov    -0x7a8(%rbp),%r8d
    7f76ecc2e94f:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2e953:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2e956:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2e959:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2e95c:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2e95f:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2e962:	4d 0f b6 8f 76 01 00 	movzbq 0x176(%r15),%r9
    7f76ecc2e969:	00 
    7f76ecc2e96a:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2e96d:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2e972:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2e975:	44 89 95 50 f8 ff ff 	mov    %r10d,-0x7b0(%rbp)
    7f76ecc2e97c:	4d 0f b6 97 7b 01 00 	movzbq 0x17b(%r15),%r10
    7f76ecc2e983:	00 
    7f76ecc2e984:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2e987:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2e98c:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2e98f:	33 f8                	xor    %eax,%edi
    7f76ecc2e991:	44 89 8d 48 f8 ff ff 	mov    %r9d,-0x7b8(%rbp)
    7f76ecc2e998:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2e99c:	41 d1 e1             	shl    %r9d
    7f76ecc2e99f:	89 9d 40 f8 ff ff    	mov    %ebx,-0x7c0(%rbp)
    7f76ecc2e9a5:	8b 9d 48 f8 ff ff    	mov    -0x7b8(%rbp),%ebx
    7f76ecc2e9ab:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2e9ae:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2e9b1:	89 9d 38 f8 ff ff    	mov    %ebx,-0x7c8(%rbp)
    7f76ecc2e9b7:	d1 e3                	shl    %ebx
    7f76ecc2e9b9:	44 89 9d 30 f8 ff ff 	mov    %r11d,-0x7d0(%rbp)
    7f76ecc2e9c0:	44 8b 9d 38 f8 ff ff 	mov    -0x7c8(%rbp),%r11d
    7f76ecc2e9c7:	41 0b db             	or     %r11d,%ebx
    7f76ecc2e9ca:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2e9ce:	41 0b db             	or     %r11d,%ebx
    7f76ecc2e9d1:	44 8b 9d 38 f8 ff ff 	mov    -0x7c8(%rbp),%r11d
    7f76ecc2e9d8:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2e9dc:	41 0b db             	or     %r11d,%ebx
    7f76ecc2e9df:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e9e2:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2e9e5:	44 8b 9d 48 f8 ff ff 	mov    -0x7b8(%rbp),%r11d
    7f76ecc2e9ec:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2e9ef:	33 fb                	xor    %ebx,%edi
    7f76ecc2e9f1:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2e9f4:	8b d8                	mov    %eax,%ebx
    7f76ecc2e9f6:	33 da                	xor    %edx,%ebx
    7f76ecc2e9f8:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2e9fb:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2e9fe:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2ea01:	d1 e3                	shl    %ebx
    7f76ecc2ea03:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2ea06:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2ea0a:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2ea0e:	44 89 9d 28 f8 ff ff 	mov    %r11d,-0x7d8(%rbp)
    7f76ecc2ea15:	41 d1 e3             	shl    %r11d
    7f76ecc2ea18:	89 b5 20 f8 ff ff    	mov    %esi,-0x7e0(%rbp)
    7f76ecc2ea1e:	8b b5 28 f8 ff ff    	mov    -0x7d8(%rbp),%esi
    7f76ecc2ea24:	44 0b de             	or     %esi,%r11d
    7f76ecc2ea27:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2ea2a:	44 0b de             	or     %esi,%r11d
    7f76ecc2ea2d:	8b b5 28 f8 ff ff    	mov    -0x7d8(%rbp),%esi
    7f76ecc2ea33:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2ea36:	44 0b de             	or     %esi,%r11d
    7f76ecc2ea39:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2ea3c:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2ea3f:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2ea42:	33 c8                	xor    %eax,%ecx
    7f76ecc2ea44:	33 d1                	xor    %ecx,%edx
    7f76ecc2ea46:	33 95 48 f8 ff ff    	xor    -0x7b8(%rbp),%edx
    7f76ecc2ea4c:	33 da                	xor    %edx,%ebx
    7f76ecc2ea4e:	8b 85 c0 f8 ff ff    	mov    -0x740(%rbp),%eax
    7f76ecc2ea54:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2ea57:	0b 85 d0 f8 ff ff    	or     -0x730(%rbp),%eax
    7f76ecc2ea5d:	8b 8d b0 f8 ff ff    	mov    -0x750(%rbp),%ecx
    7f76ecc2ea63:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2ea66:	0b c1                	or     %ecx,%eax
    7f76ecc2ea68:	8b 8d a0 f8 ff ff    	mov    -0x760(%rbp),%ecx
    7f76ecc2ea6e:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2ea71:	0b c1                	or     %ecx,%eax
    7f76ecc2ea73:	8b 8d 90 f8 ff ff    	mov    -0x770(%rbp),%ecx
    7f76ecc2ea79:	8b c9                	mov    %ecx,%ecx
    7f76ecc2ea7b:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2ea7f:	8b c0                	mov    %eax,%eax
    7f76ecc2ea81:	48 0b c8             	or     %rax,%rcx
    7f76ecc2ea84:	8b 85 80 f8 ff ff    	mov    -0x780(%rbp),%eax
    7f76ecc2ea8a:	8b c0                	mov    %eax,%eax
    7f76ecc2ea8c:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2ea90:	48 0b c8             	or     %rax,%rcx
    7f76ecc2ea93:	8b 85 70 f8 ff ff    	mov    -0x790(%rbp),%eax
    7f76ecc2ea99:	8b c0                	mov    %eax,%eax
    7f76ecc2ea9b:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2ea9f:	48 0b c8             	or     %rax,%rcx
    7f76ecc2eaa2:	8b 85 60 f8 ff ff    	mov    -0x7a0(%rbp),%eax
    7f76ecc2eaa8:	8b c0                	mov    %eax,%eax
    7f76ecc2eaaa:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2eaae:	48 0b c8             	or     %rax,%rcx
    7f76ecc2eab1:	49 89 8f d0 02 00 00 	mov    %rcx,0x2d0(%r15)
    7f76ecc2eab8:	8b 85 40 f8 ff ff    	mov    -0x7c0(%rbp),%eax
    7f76ecc2eabe:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2eac1:	0b 85 50 f8 ff ff    	or     -0x7b0(%rbp),%eax
    7f76ecc2eac7:	8b 8d 30 f8 ff ff    	mov    -0x7d0(%rbp),%ecx
    7f76ecc2eacd:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2ead0:	0b c1                	or     %ecx,%eax
    7f76ecc2ead2:	8b 8d 20 f8 ff ff    	mov    -0x7e0(%rbp),%ecx
    7f76ecc2ead8:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2eadb:	0b c1                	or     %ecx,%eax
    7f76ecc2eadd:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2eae0:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2eae4:	8b c0                	mov    %eax,%eax
    7f76ecc2eae6:	4c 0b c0             	or     %rax,%r8
    7f76ecc2eae9:	8b ff                	mov    %edi,%edi
    7f76ecc2eaeb:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2eaef:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2eaf2:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2eaf5:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2eaf9:	4d 0b c1             	or     %r9,%r8
    7f76ecc2eafc:	8b db                	mov    %ebx,%ebx
    7f76ecc2eafe:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2eb02:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2eb05:	4d 89 87 d8 02 00 00 	mov    %r8,0x2d8(%r15)
    7f76ecc2eb0c:	8b 85 f0 f8 ff ff    	mov    -0x710(%rbp),%eax
    7f76ecc2eb12:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2eb17:	8b c0                	mov    %eax,%eax
    7f76ecc2eb19:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2eb1e:	8b 8d f0 f8 ff ff    	mov    -0x710(%rbp),%ecx
    7f76ecc2eb24:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2eb27:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2eb2d:	8b c9                	mov    %ecx,%ecx
    7f76ecc2eb2f:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2eb34:	8b 95 f0 f8 ff ff    	mov    -0x710(%rbp),%edx
    7f76ecc2eb3a:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2eb3d:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2eb43:	8b d2                	mov    %edx,%edx
    7f76ecc2eb45:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2eb4a:	8b 9d f0 f8 ff ff    	mov    -0x710(%rbp),%ebx
    7f76ecc2eb50:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2eb53:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2eb59:	8b db                	mov    %ebx,%ebx
    7f76ecc2eb5b:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2eb60:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2eb63:	0b da                	or     %edx,%ebx
    7f76ecc2eb65:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2eb68:	0b d9                	or     %ecx,%ebx
    7f76ecc2eb6a:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2eb6d:	0b d8                	or     %eax,%ebx
    7f76ecc2eb6f:	81 f3 80 00 00 00    	xor    $0x80,%ebx
    7f76ecc2eb75:	8b 85 00 f9 ff ff    	mov    -0x700(%rbp),%eax
    7f76ecc2eb7b:	33 d8                	xor    %eax,%ebx
    7f76ecc2eb7d:	8b 85 10 f9 ff ff    	mov    -0x6f0(%rbp),%eax
    7f76ecc2eb83:	33 c3                	xor    %ebx,%eax
    7f76ecc2eb85:	8b 8d e0 f8 ff ff    	mov    -0x720(%rbp),%ecx
    7f76ecc2eb8b:	33 c8                	xor    %eax,%ecx
    7f76ecc2eb8d:	8b 95 f0 f8 ff ff    	mov    -0x710(%rbp),%edx
    7f76ecc2eb93:	33 d1                	xor    %ecx,%edx
    7f76ecc2eb95:	8b f0                	mov    %eax,%esi
    7f76ecc2eb97:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2eb9b:	8b fb                	mov    %ebx,%edi
    7f76ecc2eb9d:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2eba0:	49 89 b7 30 02 00 00 	mov    %rsi,0x230(%r15)
    7f76ecc2eba7:	8b f2                	mov    %edx,%esi
    7f76ecc2eba9:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2ebad:	8b f9                	mov    %ecx,%edi
    7f76ecc2ebaf:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2ebb2:	49 89 b7 38 02 00 00 	mov    %rsi,0x238(%r15)
    7f76ecc2ebb9:	49 8b b7 d0 02 00 00 	mov    0x2d0(%r15),%rsi
    7f76ecc2ebc0:	49 8b bf 30 02 00 00 	mov    0x230(%r15),%rdi
    7f76ecc2ebc7:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2ebca:	49 89 b7 80 03 00 00 	mov    %rsi,0x380(%r15)
    7f76ecc2ebd1:	49 8b b7 d8 02 00 00 	mov    0x2d8(%r15),%rsi
    7f76ecc2ebd8:	49 8b bf 38 02 00 00 	mov    0x238(%r15),%rdi
    7f76ecc2ebdf:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2ebe2:	49 89 b7 88 03 00 00 	mov    %rsi,0x388(%r15)
    7f76ecc2ebe9:	49 0f b6 b7 80 01 00 	movzbq 0x180(%r15),%rsi
    7f76ecc2ebf0:	00 
    7f76ecc2ebf1:	8b f6                	mov    %esi,%esi
    7f76ecc2ebf3:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2ebf8:	8b fe                	mov    %esi,%edi
    7f76ecc2ebfa:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2ebfd:	d1 e7                	shl    %edi
    7f76ecc2ebff:	44 8b c6             	mov    %esi,%r8d
    7f76ecc2ec02:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2ec06:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2ec0a:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2ec0d:	41 d1 e1             	shl    %r9d
    7f76ecc2ec10:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2ec13:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2ec16:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2ec1a:	45 0b ca             	or     %r10d,%r9d
    7f76ecc2ec1d:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2ec21:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2ec24:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2ec27:	4d 0f b6 87 85 01 00 	movzbq 0x185(%r15),%r8
    7f76ecc2ec2e:	00 
    7f76ecc2ec2f:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2ec32:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2ec37:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2ec3a:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2ec3e:	41 d1 e1             	shl    %r9d
    7f76ecc2ec41:	45 8b d0             	mov    %r8d,%r10d
    7f76ecc2ec44:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2ec48:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2ec4c:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2ec4f:	41 d1 e3             	shl    %r11d
    7f76ecc2ec52:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ec55:	44 89 95 18 f8 ff ff 	mov    %r10d,-0x7e8(%rbp)
    7f76ecc2ec5c:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2ec60:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ec63:	44 8b 95 18 f8 ff ff 	mov    -0x7e8(%rbp),%r10d
    7f76ecc2ec6a:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2ec6e:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ec71:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2ec74:	45 8b d1             	mov    %r9d,%r10d
    7f76ecc2ec77:	45 33 d0             	xor    %r8d,%r10d
    7f76ecc2ec7a:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2ec7d:	4d 0f b6 9f 8a 01 00 	movzbq 0x18a(%r15),%r11
    7f76ecc2ec84:	00 
    7f76ecc2ec85:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2ec88:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2ec8d:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2ec90:	89 85 10 f8 ff ff    	mov    %eax,-0x7f0(%rbp)
    7f76ecc2ec96:	49 0f b6 87 8f 01 00 	movzbq 0x18f(%r15),%rax
    7f76ecc2ec9d:	00 
    7f76ecc2ec9e:	8b c0                	mov    %eax,%eax
    7f76ecc2eca0:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2eca5:	44 33 d0             	xor    %eax,%r10d
    7f76ecc2eca8:	44 33 ce             	xor    %esi,%r9d
    7f76ecc2ecab:	44 89 9d 08 f8 ff ff 	mov    %r11d,-0x7f8(%rbp)
    7f76ecc2ecb2:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2ecb6:	41 d1 e3             	shl    %r11d
    7f76ecc2ecb9:	89 9d 00 f8 ff ff    	mov    %ebx,-0x800(%rbp)
    7f76ecc2ecbf:	8b 9d 08 f8 ff ff    	mov    -0x7f8(%rbp),%ebx
    7f76ecc2ecc5:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2ecc8:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2eccb:	89 9d f8 f7 ff ff    	mov    %ebx,-0x808(%rbp)
    7f76ecc2ecd1:	d1 e3                	shl    %ebx
    7f76ecc2ecd3:	89 95 f0 f7 ff ff    	mov    %edx,-0x810(%rbp)
    7f76ecc2ecd9:	8b 95 f8 f7 ff ff    	mov    -0x808(%rbp),%edx
    7f76ecc2ecdf:	0b da                	or     %edx,%ebx
    7f76ecc2ece1:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2ece4:	0b da                	or     %edx,%ebx
    7f76ecc2ece6:	8b 95 f8 f7 ff ff    	mov    -0x808(%rbp),%edx
    7f76ecc2ecec:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2ecef:	0b da                	or     %edx,%ebx
    7f76ecc2ecf1:	44 33 db             	xor    %ebx,%r11d
    7f76ecc2ecf4:	41 8b d3             	mov    %r11d,%edx
    7f76ecc2ecf7:	8b 9d 08 f8 ff ff    	mov    -0x7f8(%rbp),%ebx
    7f76ecc2ecfd:	33 d3                	xor    %ebx,%edx
    7f76ecc2ecff:	44 33 ca             	xor    %edx,%r9d
    7f76ecc2ed02:	44 33 c8             	xor    %eax,%r9d
    7f76ecc2ed05:	8b d6                	mov    %esi,%edx
    7f76ecc2ed07:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2ed0a:	44 33 da             	xor    %edx,%r11d
    7f76ecc2ed0d:	8b d0                	mov    %eax,%edx
    7f76ecc2ed0f:	83 e2 7f             	and    $0x7f,%edx
    7f76ecc2ed12:	d1 e2                	shl    %edx
    7f76ecc2ed14:	8b d8                	mov    %eax,%ebx
    7f76ecc2ed16:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2ed19:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2ed1c:	89 9d e8 f7 ff ff    	mov    %ebx,-0x818(%rbp)
    7f76ecc2ed22:	d1 e3                	shl    %ebx
    7f76ecc2ed24:	89 8d e0 f7 ff ff    	mov    %ecx,-0x820(%rbp)
    7f76ecc2ed2a:	8b 8d e8 f7 ff ff    	mov    -0x818(%rbp),%ecx
    7f76ecc2ed30:	0b d9                	or     %ecx,%ebx
    7f76ecc2ed32:	c1 e1 03             	shl    $0x3,%ecx
    7f76ecc2ed35:	0b d9                	or     %ecx,%ebx
    7f76ecc2ed37:	8b 8d e8 f7 ff ff    	mov    -0x818(%rbp),%ecx
    7f76ecc2ed3d:	c1 e1 04             	shl    $0x4,%ecx
    7f76ecc2ed40:	0b d9                	or     %ecx,%ebx
    7f76ecc2ed42:	33 d3                	xor    %ebx,%edx
    7f76ecc2ed44:	33 c2                	xor    %edx,%eax
    7f76ecc2ed46:	44 33 d8             	xor    %eax,%r11d
    7f76ecc2ed49:	33 fe                	xor    %esi,%edi
    7f76ecc2ed4b:	44 33 c7             	xor    %edi,%r8d
    7f76ecc2ed4e:	44 33 85 08 f8 ff ff 	xor    -0x7f8(%rbp),%r8d
    7f76ecc2ed55:	41 33 d0             	xor    %r8d,%edx
    7f76ecc2ed58:	49 0f b6 87 84 01 00 	movzbq 0x184(%r15),%rax
    7f76ecc2ed5f:	00 
    7f76ecc2ed60:	8b c0                	mov    %eax,%eax
    7f76ecc2ed62:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2ed67:	8b c8                	mov    %eax,%ecx
    7f76ecc2ed69:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2ed6c:	d1 e1                	shl    %ecx
    7f76ecc2ed6e:	8b d8                	mov    %eax,%ebx
    7f76ecc2ed70:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2ed73:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2ed76:	8b f3                	mov    %ebx,%esi
    7f76ecc2ed78:	d1 e6                	shl    %esi
    7f76ecc2ed7a:	0b f3                	or     %ebx,%esi
    7f76ecc2ed7c:	8b fb                	mov    %ebx,%edi
    7f76ecc2ed7e:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2ed81:	0b f7                	or     %edi,%esi
    7f76ecc2ed83:	c1 e3 04             	shl    $0x4,%ebx
    7f76ecc2ed86:	0b f3                	or     %ebx,%esi
    7f76ecc2ed88:	33 ce                	xor    %esi,%ecx
    7f76ecc2ed8a:	49 0f b6 9f 89 01 00 	movzbq 0x189(%r15),%rbx
    7f76ecc2ed91:	00 
    7f76ecc2ed92:	8b db                	mov    %ebx,%ebx
    7f76ecc2ed94:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2ed99:	8b f3                	mov    %ebx,%esi
    7f76ecc2ed9b:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2ed9e:	d1 e6                	shl    %esi
    7f76ecc2eda0:	8b fb                	mov    %ebx,%edi
    7f76ecc2eda2:	c1 ef 07             	shr    $0x7,%edi
    7f76ecc2eda5:	83 e7 01             	and    $0x1,%edi
    7f76ecc2eda8:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2edab:	41 d1 e0             	shl    %r8d
    7f76ecc2edae:	44 0b c7             	or     %edi,%r8d
    7f76ecc2edb1:	89 bd d8 f7 ff ff    	mov    %edi,-0x828(%rbp)
    7f76ecc2edb7:	c1 e7 03             	shl    $0x3,%edi
    7f76ecc2edba:	44 0b c7             	or     %edi,%r8d
    7f76ecc2edbd:	8b bd d8 f7 ff ff    	mov    -0x828(%rbp),%edi
    7f76ecc2edc3:	c1 e7 04             	shl    $0x4,%edi
    7f76ecc2edc6:	44 0b c7             	or     %edi,%r8d
    7f76ecc2edc9:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2edcc:	8b fe                	mov    %esi,%edi
    7f76ecc2edce:	33 fb                	xor    %ebx,%edi
    7f76ecc2edd0:	33 f9                	xor    %ecx,%edi
    7f76ecc2edd2:	4d 0f b6 87 8e 01 00 	movzbq 0x18e(%r15),%r8
    7f76ecc2edd9:	00 
    7f76ecc2edda:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2eddd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2ede2:	41 33 f8             	xor    %r8d,%edi
    7f76ecc2ede5:	44 89 95 d0 f7 ff ff 	mov    %r10d,-0x830(%rbp)
    7f76ecc2edec:	4d 0f b6 97 83 01 00 	movzbq 0x183(%r15),%r10
    7f76ecc2edf3:	00 
    7f76ecc2edf4:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2edf7:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2edfc:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2edff:	33 f0                	xor    %eax,%esi
    7f76ecc2ee01:	44 89 85 c8 f7 ff ff 	mov    %r8d,-0x838(%rbp)
    7f76ecc2ee08:	41 83 e0 7f          	and    $0x7f,%r8d
    7f76ecc2ee0c:	41 d1 e0             	shl    %r8d
    7f76ecc2ee0f:	44 89 8d c0 f7 ff ff 	mov    %r9d,-0x840(%rbp)
    7f76ecc2ee16:	44 8b 8d c8 f7 ff ff 	mov    -0x838(%rbp),%r9d
    7f76ecc2ee1d:	41 c1 e9 07          	shr    $0x7,%r9d
    7f76ecc2ee21:	41 83 e1 01          	and    $0x1,%r9d
    7f76ecc2ee25:	44 89 8d b8 f7 ff ff 	mov    %r9d,-0x848(%rbp)
    7f76ecc2ee2c:	41 d1 e1             	shl    %r9d
    7f76ecc2ee2f:	44 89 9d b0 f7 ff ff 	mov    %r11d,-0x850(%rbp)
    7f76ecc2ee36:	44 8b 9d b8 f7 ff ff 	mov    -0x848(%rbp),%r11d
    7f76ecc2ee3d:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2ee40:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2ee44:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2ee47:	44 8b 9d b8 f7 ff ff 	mov    -0x848(%rbp),%r11d
    7f76ecc2ee4e:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2ee52:	45 0b cb             	or     %r11d,%r9d
    7f76ecc2ee55:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2ee58:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2ee5b:	44 8b 9d c8 f7 ff ff 	mov    -0x838(%rbp),%r11d
    7f76ecc2ee62:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2ee65:	41 33 f1             	xor    %r9d,%esi
    7f76ecc2ee68:	41 33 f2             	xor    %r10d,%esi
    7f76ecc2ee6b:	44 8b c8             	mov    %eax,%r9d
    7f76ecc2ee6e:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2ee71:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2ee74:	45 8b ca             	mov    %r10d,%r9d
    7f76ecc2ee77:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2ee7b:	41 d1 e1             	shl    %r9d
    7f76ecc2ee7e:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2ee81:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2ee85:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2ee89:	44 89 9d a8 f7 ff ff 	mov    %r11d,-0x858(%rbp)
    7f76ecc2ee90:	41 d1 e3             	shl    %r11d
    7f76ecc2ee93:	89 95 a0 f7 ff ff    	mov    %edx,-0x860(%rbp)
    7f76ecc2ee99:	8b 95 a8 f7 ff ff    	mov    -0x858(%rbp),%edx
    7f76ecc2ee9f:	44 0b da             	or     %edx,%r11d
    7f76ecc2eea2:	c1 e2 03             	shl    $0x3,%edx
    7f76ecc2eea5:	44 0b da             	or     %edx,%r11d
    7f76ecc2eea8:	8b 95 a8 f7 ff ff    	mov    -0x858(%rbp),%edx
    7f76ecc2eeae:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2eeb1:	44 0b da             	or     %edx,%r11d
    7f76ecc2eeb4:	45 33 cb             	xor    %r11d,%r9d
    7f76ecc2eeb7:	45 33 d1             	xor    %r9d,%r10d
    7f76ecc2eeba:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2eebd:	33 c8                	xor    %eax,%ecx
    7f76ecc2eebf:	33 d9                	xor    %ecx,%ebx
    7f76ecc2eec1:	33 9d c8 f7 ff ff    	xor    -0x838(%rbp),%ebx
    7f76ecc2eec7:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2eeca:	49 0f b6 87 88 01 00 	movzbq 0x188(%r15),%rax
    7f76ecc2eed1:	00 
    7f76ecc2eed2:	8b c0                	mov    %eax,%eax
    7f76ecc2eed4:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2eed9:	8b c8                	mov    %eax,%ecx
    7f76ecc2eedb:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2eede:	d1 e1                	shl    %ecx
    7f76ecc2eee0:	8b d0                	mov    %eax,%edx
    7f76ecc2eee2:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2eee5:	83 e2 01             	and    $0x1,%edx
    7f76ecc2eee8:	8b da                	mov    %edx,%ebx
    7f76ecc2eeea:	d1 e3                	shl    %ebx
    7f76ecc2eeec:	0b da                	or     %edx,%ebx
    7f76ecc2eeee:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2eef1:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2eef5:	41 0b da             	or     %r10d,%ebx
    7f76ecc2eef8:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2eefb:	0b da                	or     %edx,%ebx
    7f76ecc2eefd:	33 cb                	xor    %ebx,%ecx
    7f76ecc2eeff:	49 0f b6 97 8d 01 00 	movzbq 0x18d(%r15),%rdx
    7f76ecc2ef06:	00 
    7f76ecc2ef07:	8b d2                	mov    %edx,%edx
    7f76ecc2ef09:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2ef0e:	8b da                	mov    %edx,%ebx
    7f76ecc2ef10:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2ef13:	d1 e3                	shl    %ebx
    7f76ecc2ef15:	44 8b d2             	mov    %edx,%r10d
    7f76ecc2ef18:	41 c1 ea 07          	shr    $0x7,%r10d
    7f76ecc2ef1c:	41 83 e2 01          	and    $0x1,%r10d
    7f76ecc2ef20:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2ef23:	41 d1 e3             	shl    %r11d
    7f76ecc2ef26:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ef29:	44 89 95 98 f7 ff ff 	mov    %r10d,-0x868(%rbp)
    7f76ecc2ef30:	41 c1 e2 03          	shl    $0x3,%r10d
    7f76ecc2ef34:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ef37:	44 8b 95 98 f7 ff ff 	mov    -0x868(%rbp),%r10d
    7f76ecc2ef3e:	41 c1 e2 04          	shl    $0x4,%r10d
    7f76ecc2ef42:	45 0b da             	or     %r10d,%r11d
    7f76ecc2ef45:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2ef48:	44 8b d3             	mov    %ebx,%r10d
    7f76ecc2ef4b:	44 33 d2             	xor    %edx,%r10d
    7f76ecc2ef4e:	44 33 d1             	xor    %ecx,%r10d
    7f76ecc2ef51:	4d 0f b6 9f 82 01 00 	movzbq 0x182(%r15),%r11
    7f76ecc2ef58:	00 
    7f76ecc2ef59:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2ef5c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2ef61:	45 33 d3             	xor    %r11d,%r10d
    7f76ecc2ef64:	89 bd 90 f7 ff ff    	mov    %edi,-0x870(%rbp)
    7f76ecc2ef6a:	49 0f b6 bf 87 01 00 	movzbq 0x187(%r15),%rdi
    7f76ecc2ef71:	00 
    7f76ecc2ef72:	8b ff                	mov    %edi,%edi
    7f76ecc2ef74:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2ef79:	44 33 d7             	xor    %edi,%r10d
    7f76ecc2ef7c:	33 d8                	xor    %eax,%ebx
    7f76ecc2ef7e:	44 89 9d 88 f7 ff ff 	mov    %r11d,-0x878(%rbp)
    7f76ecc2ef85:	41 83 e3 7f          	and    $0x7f,%r11d
    7f76ecc2ef89:	41 d1 e3             	shl    %r11d
    7f76ecc2ef8c:	89 b5 80 f7 ff ff    	mov    %esi,-0x880(%rbp)
    7f76ecc2ef92:	8b b5 88 f7 ff ff    	mov    -0x878(%rbp),%esi
    7f76ecc2ef98:	c1 ee 07             	shr    $0x7,%esi
    7f76ecc2ef9b:	83 e6 01             	and    $0x1,%esi
    7f76ecc2ef9e:	89 b5 78 f7 ff ff    	mov    %esi,-0x888(%rbp)
    7f76ecc2efa4:	d1 e6                	shl    %esi
    7f76ecc2efa6:	44 89 85 70 f7 ff ff 	mov    %r8d,-0x890(%rbp)
    7f76ecc2efad:	44 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%r8d
    7f76ecc2efb4:	41 0b f0             	or     %r8d,%esi
    7f76ecc2efb7:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2efbb:	41 0b f0             	or     %r8d,%esi
    7f76ecc2efbe:	44 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%r8d
    7f76ecc2efc5:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2efc9:	41 0b f0             	or     %r8d,%esi
    7f76ecc2efcc:	44 33 de             	xor    %esi,%r11d
    7f76ecc2efcf:	41 8b f3             	mov    %r11d,%esi
    7f76ecc2efd2:	44 8b 85 88 f7 ff ff 	mov    -0x878(%rbp),%r8d
    7f76ecc2efd9:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2efdc:	33 de                	xor    %esi,%ebx
    7f76ecc2efde:	33 df                	xor    %edi,%ebx
    7f76ecc2efe0:	8b f0                	mov    %eax,%esi
    7f76ecc2efe2:	33 f2                	xor    %edx,%esi
    7f76ecc2efe4:	44 33 de             	xor    %esi,%r11d
    7f76ecc2efe7:	8b f7                	mov    %edi,%esi
    7f76ecc2efe9:	83 e6 7f             	and    $0x7f,%esi
    7f76ecc2efec:	d1 e6                	shl    %esi
    7f76ecc2efee:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2eff1:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2eff5:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2eff9:	44 89 85 68 f7 ff ff 	mov    %r8d,-0x898(%rbp)
    7f76ecc2f000:	41 d1 e0             	shl    %r8d
    7f76ecc2f003:	44 89 8d 60 f7 ff ff 	mov    %r9d,-0x8a0(%rbp)
    7f76ecc2f00a:	44 8b 8d 68 f7 ff ff 	mov    -0x898(%rbp),%r9d
    7f76ecc2f011:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2f014:	41 c1 e1 03          	shl    $0x3,%r9d
    7f76ecc2f018:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2f01b:	44 8b 8d 68 f7 ff ff 	mov    -0x898(%rbp),%r9d
    7f76ecc2f022:	41 c1 e1 04          	shl    $0x4,%r9d
    7f76ecc2f026:	45 0b c1             	or     %r9d,%r8d
    7f76ecc2f029:	41 33 f0             	xor    %r8d,%esi
    7f76ecc2f02c:	33 fe                	xor    %esi,%edi
    7f76ecc2f02e:	44 33 df             	xor    %edi,%r11d
    7f76ecc2f031:	33 c8                	xor    %eax,%ecx
    7f76ecc2f033:	33 d1                	xor    %ecx,%edx
    7f76ecc2f035:	33 95 88 f7 ff ff    	xor    -0x878(%rbp),%edx
    7f76ecc2f03b:	33 f2                	xor    %edx,%esi
    7f76ecc2f03d:	49 0f b6 87 8c 01 00 	movzbq 0x18c(%r15),%rax
    7f76ecc2f044:	00 
    7f76ecc2f045:	8b c0                	mov    %eax,%eax
    7f76ecc2f047:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2f04c:	8b c8                	mov    %eax,%ecx
    7f76ecc2f04e:	83 e1 7f             	and    $0x7f,%ecx
    7f76ecc2f051:	d1 e1                	shl    %ecx
    7f76ecc2f053:	8b d0                	mov    %eax,%edx
    7f76ecc2f055:	c1 ea 07             	shr    $0x7,%edx
    7f76ecc2f058:	83 e2 01             	and    $0x1,%edx
    7f76ecc2f05b:	8b fa                	mov    %edx,%edi
    7f76ecc2f05d:	d1 e7                	shl    %edi
    7f76ecc2f05f:	0b fa                	or     %edx,%edi
    7f76ecc2f061:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2f064:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2f068:	41 0b f8             	or     %r8d,%edi
    7f76ecc2f06b:	c1 e2 04             	shl    $0x4,%edx
    7f76ecc2f06e:	0b fa                	or     %edx,%edi
    7f76ecc2f070:	33 cf                	xor    %edi,%ecx
    7f76ecc2f072:	49 0f b6 97 81 01 00 	movzbq 0x181(%r15),%rdx
    7f76ecc2f079:	00 
    7f76ecc2f07a:	8b d2                	mov    %edx,%edx
    7f76ecc2f07c:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2f081:	8b fa                	mov    %edx,%edi
    7f76ecc2f083:	83 e7 7f             	and    $0x7f,%edi
    7f76ecc2f086:	d1 e7                	shl    %edi
    7f76ecc2f088:	44 8b c2             	mov    %edx,%r8d
    7f76ecc2f08b:	41 c1 e8 07          	shr    $0x7,%r8d
    7f76ecc2f08f:	41 83 e0 01          	and    $0x1,%r8d
    7f76ecc2f093:	45 8b c8             	mov    %r8d,%r9d
    7f76ecc2f096:	41 d1 e1             	shl    %r9d
    7f76ecc2f099:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2f09c:	44 89 85 58 f7 ff ff 	mov    %r8d,-0x8a8(%rbp)
    7f76ecc2f0a3:	41 c1 e0 03          	shl    $0x3,%r8d
    7f76ecc2f0a7:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2f0aa:	44 8b 85 58 f7 ff ff 	mov    -0x8a8(%rbp),%r8d
    7f76ecc2f0b1:	41 c1 e0 04          	shl    $0x4,%r8d
    7f76ecc2f0b5:	45 0b c8             	or     %r8d,%r9d
    7f76ecc2f0b8:	41 33 f9             	xor    %r9d,%edi
    7f76ecc2f0bb:	44 8b c7             	mov    %edi,%r8d
    7f76ecc2f0be:	44 33 c2             	xor    %edx,%r8d
    7f76ecc2f0c1:	44 33 c1             	xor    %ecx,%r8d
    7f76ecc2f0c4:	4d 0f b6 8f 86 01 00 	movzbq 0x186(%r15),%r9
    7f76ecc2f0cb:	00 
    7f76ecc2f0cc:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2f0cf:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2f0d4:	45 33 c1             	xor    %r9d,%r8d
    7f76ecc2f0d7:	44 89 95 50 f7 ff ff 	mov    %r10d,-0x8b0(%rbp)
    7f76ecc2f0de:	4d 0f b6 97 8b 01 00 	movzbq 0x18b(%r15),%r10
    7f76ecc2f0e5:	00 
    7f76ecc2f0e6:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2f0e9:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2f0ee:	45 33 c2             	xor    %r10d,%r8d
    7f76ecc2f0f1:	33 f8                	xor    %eax,%edi
    7f76ecc2f0f3:	44 89 8d 48 f7 ff ff 	mov    %r9d,-0x8b8(%rbp)
    7f76ecc2f0fa:	41 83 e1 7f          	and    $0x7f,%r9d
    7f76ecc2f0fe:	41 d1 e1             	shl    %r9d
    7f76ecc2f101:	89 9d 40 f7 ff ff    	mov    %ebx,-0x8c0(%rbp)
    7f76ecc2f107:	8b 9d 48 f7 ff ff    	mov    -0x8b8(%rbp),%ebx
    7f76ecc2f10d:	c1 eb 07             	shr    $0x7,%ebx
    7f76ecc2f110:	83 e3 01             	and    $0x1,%ebx
    7f76ecc2f113:	89 9d 38 f7 ff ff    	mov    %ebx,-0x8c8(%rbp)
    7f76ecc2f119:	d1 e3                	shl    %ebx
    7f76ecc2f11b:	44 89 9d 30 f7 ff ff 	mov    %r11d,-0x8d0(%rbp)
    7f76ecc2f122:	44 8b 9d 38 f7 ff ff 	mov    -0x8c8(%rbp),%r11d
    7f76ecc2f129:	41 0b db             	or     %r11d,%ebx
    7f76ecc2f12c:	41 c1 e3 03          	shl    $0x3,%r11d
    7f76ecc2f130:	41 0b db             	or     %r11d,%ebx
    7f76ecc2f133:	44 8b 9d 38 f7 ff ff 	mov    -0x8c8(%rbp),%r11d
    7f76ecc2f13a:	41 c1 e3 04          	shl    $0x4,%r11d
    7f76ecc2f13e:	41 0b db             	or     %r11d,%ebx
    7f76ecc2f141:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2f144:	41 8b d9             	mov    %r9d,%ebx
    7f76ecc2f147:	44 8b 9d 48 f7 ff ff 	mov    -0x8b8(%rbp),%r11d
    7f76ecc2f14e:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2f151:	33 fb                	xor    %ebx,%edi
    7f76ecc2f153:	41 33 fa             	xor    %r10d,%edi
    7f76ecc2f156:	8b d8                	mov    %eax,%ebx
    7f76ecc2f158:	33 da                	xor    %edx,%ebx
    7f76ecc2f15a:	44 33 cb             	xor    %ebx,%r9d
    7f76ecc2f15d:	41 8b da             	mov    %r10d,%ebx
    7f76ecc2f160:	83 e3 7f             	and    $0x7f,%ebx
    7f76ecc2f163:	d1 e3                	shl    %ebx
    7f76ecc2f165:	45 8b da             	mov    %r10d,%r11d
    7f76ecc2f168:	41 c1 eb 07          	shr    $0x7,%r11d
    7f76ecc2f16c:	41 83 e3 01          	and    $0x1,%r11d
    7f76ecc2f170:	44 89 9d 28 f7 ff ff 	mov    %r11d,-0x8d8(%rbp)
    7f76ecc2f177:	41 d1 e3             	shl    %r11d
    7f76ecc2f17a:	89 b5 20 f7 ff ff    	mov    %esi,-0x8e0(%rbp)
    7f76ecc2f180:	8b b5 28 f7 ff ff    	mov    -0x8d8(%rbp),%esi
    7f76ecc2f186:	44 0b de             	or     %esi,%r11d
    7f76ecc2f189:	c1 e6 03             	shl    $0x3,%esi
    7f76ecc2f18c:	44 0b de             	or     %esi,%r11d
    7f76ecc2f18f:	8b b5 28 f7 ff ff    	mov    -0x8d8(%rbp),%esi
    7f76ecc2f195:	c1 e6 04             	shl    $0x4,%esi
    7f76ecc2f198:	44 0b de             	or     %esi,%r11d
    7f76ecc2f19b:	41 33 db             	xor    %r11d,%ebx
    7f76ecc2f19e:	44 33 d3             	xor    %ebx,%r10d
    7f76ecc2f1a1:	45 33 ca             	xor    %r10d,%r9d
    7f76ecc2f1a4:	33 c8                	xor    %eax,%ecx
    7f76ecc2f1a6:	33 d1                	xor    %ecx,%edx
    7f76ecc2f1a8:	33 95 48 f7 ff ff    	xor    -0x8b8(%rbp),%edx
    7f76ecc2f1ae:	33 da                	xor    %edx,%ebx
    7f76ecc2f1b0:	8b 85 c0 f7 ff ff    	mov    -0x840(%rbp),%eax
    7f76ecc2f1b6:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2f1b9:	0b 85 d0 f7 ff ff    	or     -0x830(%rbp),%eax
    7f76ecc2f1bf:	8b 8d b0 f7 ff ff    	mov    -0x850(%rbp),%ecx
    7f76ecc2f1c5:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2f1c8:	0b c1                	or     %ecx,%eax
    7f76ecc2f1ca:	8b 8d a0 f7 ff ff    	mov    -0x860(%rbp),%ecx
    7f76ecc2f1d0:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2f1d3:	0b c1                	or     %ecx,%eax
    7f76ecc2f1d5:	8b 8d 90 f7 ff ff    	mov    -0x870(%rbp),%ecx
    7f76ecc2f1db:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f1dd:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2f1e1:	8b c0                	mov    %eax,%eax
    7f76ecc2f1e3:	48 0b c8             	or     %rax,%rcx
    7f76ecc2f1e6:	8b 85 80 f7 ff ff    	mov    -0x880(%rbp),%eax
    7f76ecc2f1ec:	8b c0                	mov    %eax,%eax
    7f76ecc2f1ee:	48 c1 e0 28          	shl    $0x28,%rax
    7f76ecc2f1f2:	48 0b c8             	or     %rax,%rcx
    7f76ecc2f1f5:	8b 85 70 f7 ff ff    	mov    -0x890(%rbp),%eax
    7f76ecc2f1fb:	8b c0                	mov    %eax,%eax
    7f76ecc2f1fd:	48 c1 e0 30          	shl    $0x30,%rax
    7f76ecc2f201:	48 0b c8             	or     %rax,%rcx
    7f76ecc2f204:	8b 85 60 f7 ff ff    	mov    -0x8a0(%rbp),%eax
    7f76ecc2f20a:	8b c0                	mov    %eax,%eax
    7f76ecc2f20c:	48 c1 e0 38          	shl    $0x38,%rax
    7f76ecc2f210:	48 0b c8             	or     %rax,%rcx
    7f76ecc2f213:	49 89 8f e0 02 00 00 	mov    %rcx,0x2e0(%r15)
    7f76ecc2f21a:	8b 85 40 f7 ff ff    	mov    -0x8c0(%rbp),%eax
    7f76ecc2f220:	c1 e0 08             	shl    $0x8,%eax
    7f76ecc2f223:	0b 85 50 f7 ff ff    	or     -0x8b0(%rbp),%eax
    7f76ecc2f229:	8b 8d 30 f7 ff ff    	mov    -0x8d0(%rbp),%ecx
    7f76ecc2f22f:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2f232:	0b c1                	or     %ecx,%eax
    7f76ecc2f234:	8b 8d 20 f7 ff ff    	mov    -0x8e0(%rbp),%ecx
    7f76ecc2f23a:	c1 e1 18             	shl    $0x18,%ecx
    7f76ecc2f23d:	0b c1                	or     %ecx,%eax
    7f76ecc2f23f:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2f242:	49 c1 e0 20          	shl    $0x20,%r8
    7f76ecc2f246:	8b c0                	mov    %eax,%eax
    7f76ecc2f248:	4c 0b c0             	or     %rax,%r8
    7f76ecc2f24b:	8b ff                	mov    %edi,%edi
    7f76ecc2f24d:	48 c1 e7 28          	shl    $0x28,%rdi
    7f76ecc2f251:	4c 0b c7             	or     %rdi,%r8
    7f76ecc2f254:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2f257:	49 c1 e1 30          	shl    $0x30,%r9
    7f76ecc2f25b:	4d 0b c1             	or     %r9,%r8
    7f76ecc2f25e:	8b db                	mov    %ebx,%ebx
    7f76ecc2f260:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2f264:	4c 0b c3             	or     %rbx,%r8
    7f76ecc2f267:	4d 89 87 e8 02 00 00 	mov    %r8,0x2e8(%r15)
    7f76ecc2f26e:	8b 85 f0 f7 ff ff    	mov    -0x810(%rbp),%eax
    7f76ecc2f274:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2f279:	8b c0                	mov    %eax,%eax
    7f76ecc2f27b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2f280:	8b 8d f0 f7 ff ff    	mov    -0x810(%rbp),%ecx
    7f76ecc2f286:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2f289:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2f28f:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f291:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2f296:	8b 95 f0 f7 ff ff    	mov    -0x810(%rbp),%edx
    7f76ecc2f29c:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2f29f:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2f2a5:	8b d2                	mov    %edx,%edx
    7f76ecc2f2a7:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2f2ac:	8b 9d f0 f7 ff ff    	mov    -0x810(%rbp),%ebx
    7f76ecc2f2b2:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2f2b5:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2f2bb:	8b db                	mov    %ebx,%ebx
    7f76ecc2f2bd:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2f2c2:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2f2c5:	0b da                	or     %edx,%ebx
    7f76ecc2f2c7:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2f2ca:	0b d9                	or     %ecx,%ebx
    7f76ecc2f2cc:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2f2cf:	0b d8                	or     %eax,%ebx
    7f76ecc2f2d1:	83 f3 1b             	xor    $0x1b,%ebx
    7f76ecc2f2d4:	8b 85 00 f8 ff ff    	mov    -0x800(%rbp),%eax
    7f76ecc2f2da:	33 d8                	xor    %eax,%ebx
    7f76ecc2f2dc:	8b 85 10 f8 ff ff    	mov    -0x7f0(%rbp),%eax
    7f76ecc2f2e2:	33 c3                	xor    %ebx,%eax
    7f76ecc2f2e4:	8b 8d e0 f7 ff ff    	mov    -0x820(%rbp),%ecx
    7f76ecc2f2ea:	33 c8                	xor    %eax,%ecx
    7f76ecc2f2ec:	8b 95 f0 f7 ff ff    	mov    -0x810(%rbp),%edx
    7f76ecc2f2f2:	33 d1                	xor    %ecx,%edx
    7f76ecc2f2f4:	8b f0                	mov    %eax,%esi
    7f76ecc2f2f6:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2f2fa:	8b fb                	mov    %ebx,%edi
    7f76ecc2f2fc:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2f2ff:	49 89 b7 40 02 00 00 	mov    %rsi,0x240(%r15)
    7f76ecc2f306:	8b f2                	mov    %edx,%esi
    7f76ecc2f308:	48 c1 e6 20          	shl    $0x20,%rsi
    7f76ecc2f30c:	8b f9                	mov    %ecx,%edi
    7f76ecc2f30e:	48 0b f7             	or     %rdi,%rsi
    7f76ecc2f311:	49 89 b7 48 02 00 00 	mov    %rsi,0x248(%r15)
    7f76ecc2f318:	49 8b b7 e0 02 00 00 	mov    0x2e0(%r15),%rsi
    7f76ecc2f31f:	49 8b bf 40 02 00 00 	mov    0x240(%r15),%rdi
    7f76ecc2f326:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2f329:	49 89 b7 90 03 00 00 	mov    %rsi,0x390(%r15)
    7f76ecc2f330:	49 8b b7 e8 02 00 00 	mov    0x2e8(%r15),%rsi
    7f76ecc2f337:	49 8b bf 48 02 00 00 	mov    0x248(%r15),%rdi
    7f76ecc2f33e:	48 33 f7             	xor    %rdi,%rsi
    7f76ecc2f341:	49 89 b7 98 03 00 00 	mov    %rsi,0x398(%r15)
    7f76ecc2f348:	49 0f b6 b7 9f 01 00 	movzbq 0x19f(%r15),%rsi
    7f76ecc2f34f:	00 
    7f76ecc2f350:	8b f6                	mov    %esi,%esi
    7f76ecc2f352:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2f357:	49 0f b6 bf 9e 01 00 	movzbq 0x19e(%r15),%rdi
    7f76ecc2f35e:	00 
    7f76ecc2f35f:	8b ff                	mov    %edi,%edi
    7f76ecc2f361:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2f366:	4d 0f b6 87 9d 01 00 	movzbq 0x19d(%r15),%r8
    7f76ecc2f36d:	00 
    7f76ecc2f36e:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2f371:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2f376:	4d 0f b6 8f 9c 01 00 	movzbq 0x19c(%r15),%r9
    7f76ecc2f37d:	00 
    7f76ecc2f37e:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2f381:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2f386:	4d 0f b6 97 9a 01 00 	movzbq 0x19a(%r15),%r10
    7f76ecc2f38d:	00 
    7f76ecc2f38e:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2f391:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2f396:	4d 0f b6 9f 99 01 00 	movzbq 0x199(%r15),%r11
    7f76ecc2f39d:	00 
    7f76ecc2f39e:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2f3a1:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2f3a6:	89 85 18 f7 ff ff    	mov    %eax,-0x8e8(%rbp)
    7f76ecc2f3ac:	49 0f b6 87 98 01 00 	movzbq 0x198(%r15),%rax
    7f76ecc2f3b3:	00 
    7f76ecc2f3b4:	8b c0                	mov    %eax,%eax
    7f76ecc2f3b6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2f3bb:	89 9d 10 f7 ff ff    	mov    %ebx,-0x8f0(%rbp)
    7f76ecc2f3c1:	49 0f b6 9f 9b 01 00 	movzbq 0x19b(%r15),%rbx
    7f76ecc2f3c8:	00 
    7f76ecc2f3c9:	8b db                	mov    %ebx,%ebx
    7f76ecc2f3cb:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2f3d0:	89 95 08 f7 ff ff    	mov    %edx,-0x8f8(%rbp)
    7f76ecc2f3d6:	49 0f b6 97 95 01 00 	movzbq 0x195(%r15),%rdx
    7f76ecc2f3dd:	00 
    7f76ecc2f3de:	8b d2                	mov    %edx,%edx
    7f76ecc2f3e0:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2f3e5:	89 8d 00 f7 ff ff    	mov    %ecx,-0x900(%rbp)
    7f76ecc2f3eb:	49 0f b6 8f 94 01 00 	movzbq 0x194(%r15),%rcx
    7f76ecc2f3f2:	00 
    7f76ecc2f3f3:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f3f5:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2f3fa:	89 b5 f8 f6 ff ff    	mov    %esi,-0x908(%rbp)
    7f76ecc2f400:	49 0f b6 b7 97 01 00 	movzbq 0x197(%r15),%rsi
    7f76ecc2f407:	00 
    7f76ecc2f408:	8b f6                	mov    %esi,%esi
    7f76ecc2f40a:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7f76ecc2f40f:	89 bd f0 f6 ff ff    	mov    %edi,-0x910(%rbp)
    7f76ecc2f415:	49 0f b6 bf 96 01 00 	movzbq 0x196(%r15),%rdi
    7f76ecc2f41c:	00 
    7f76ecc2f41d:	8b ff                	mov    %edi,%edi
    7f76ecc2f41f:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7f76ecc2f424:	44 89 85 e8 f6 ff ff 	mov    %r8d,-0x918(%rbp)
    7f76ecc2f42b:	4d 0f b6 87 90 01 00 	movzbq 0x190(%r15),%r8
    7f76ecc2f432:	00 
    7f76ecc2f433:	45 8b c0             	mov    %r8d,%r8d
    7f76ecc2f436:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7f76ecc2f43b:	44 89 8d e0 f6 ff ff 	mov    %r9d,-0x920(%rbp)
    7f76ecc2f442:	4d 0f b6 8f 93 01 00 	movzbq 0x193(%r15),%r9
    7f76ecc2f449:	00 
    7f76ecc2f44a:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2f44d:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7f76ecc2f452:	44 89 95 d8 f6 ff ff 	mov    %r10d,-0x928(%rbp)
    7f76ecc2f459:	4d 0f b6 97 92 01 00 	movzbq 0x192(%r15),%r10
    7f76ecc2f460:	00 
    7f76ecc2f461:	45 8b d2             	mov    %r10d,%r10d
    7f76ecc2f464:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7f76ecc2f469:	44 89 9d d0 f6 ff ff 	mov    %r11d,-0x930(%rbp)
    7f76ecc2f470:	4d 0f b6 9f 91 01 00 	movzbq 0x191(%r15),%r11
    7f76ecc2f477:	00 
    7f76ecc2f478:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2f47b:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7f76ecc2f480:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2f483:	44 0b c2             	or     %edx,%r8d
    7f76ecc2f486:	8b 95 d8 f6 ff ff    	mov    -0x928(%rbp),%edx
    7f76ecc2f48c:	c1 e2 10             	shl    $0x10,%edx
    7f76ecc2f48f:	44 0b c2             	or     %edx,%r8d
    7f76ecc2f492:	8b 95 f8 f6 ff ff    	mov    -0x908(%rbp),%edx
    7f76ecc2f498:	c1 e2 18             	shl    $0x18,%edx
    7f76ecc2f49b:	44 0b c2             	or     %edx,%r8d
    7f76ecc2f49e:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f4a0:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2f4a4:	41 8b d0             	mov    %r8d,%edx
    7f76ecc2f4a7:	48 0b ca             	or     %rdx,%rcx
    7f76ecc2f4aa:	8b 95 d0 f6 ff ff    	mov    -0x930(%rbp),%edx
    7f76ecc2f4b0:	8b d2                	mov    %edx,%edx
    7f76ecc2f4b2:	48 c1 e2 28          	shl    $0x28,%rdx
    7f76ecc2f4b6:	48 0b ca             	or     %rdx,%rcx
    7f76ecc2f4b9:	8b 95 f0 f6 ff ff    	mov    -0x910(%rbp),%edx
    7f76ecc2f4bf:	8b d2                	mov    %edx,%edx
    7f76ecc2f4c1:	48 c1 e2 30          	shl    $0x30,%rdx
    7f76ecc2f4c5:	48 0b ca             	or     %rdx,%rcx
    7f76ecc2f4c8:	45 8b c9             	mov    %r9d,%r9d
    7f76ecc2f4cb:	49 c1 e1 38          	shl    $0x38,%r9
    7f76ecc2f4cf:	49 0b c9             	or     %r9,%rcx
    7f76ecc2f4d2:	49 89 8f f0 02 00 00 	mov    %rcx,0x2f0(%r15)
    7f76ecc2f4d9:	8b 8d e8 f6 ff ff    	mov    -0x918(%rbp),%ecx
    7f76ecc2f4df:	c1 e1 08             	shl    $0x8,%ecx
    7f76ecc2f4e2:	0b c1                	or     %ecx,%eax
    7f76ecc2f4e4:	41 c1 e2 10          	shl    $0x10,%r10d
    7f76ecc2f4e8:	41 0b c2             	or     %r10d,%eax
    7f76ecc2f4eb:	c1 e6 18             	shl    $0x18,%esi
    7f76ecc2f4ee:	0b c6                	or     %esi,%eax
    7f76ecc2f4f0:	8b 8d e0 f6 ff ff    	mov    -0x920(%rbp),%ecx
    7f76ecc2f4f6:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f4f8:	48 c1 e1 20          	shl    $0x20,%rcx
    7f76ecc2f4fc:	8b c0                	mov    %eax,%eax
    7f76ecc2f4fe:	48 0b c8             	or     %rax,%rcx
    7f76ecc2f501:	45 8b db             	mov    %r11d,%r11d
    7f76ecc2f504:	49 c1 e3 28          	shl    $0x28,%r11
    7f76ecc2f508:	49 0b cb             	or     %r11,%rcx
    7f76ecc2f50b:	8b ff                	mov    %edi,%edi
    7f76ecc2f50d:	48 c1 e7 30          	shl    $0x30,%rdi
    7f76ecc2f511:	48 0b cf             	or     %rdi,%rcx
    7f76ecc2f514:	8b db                	mov    %ebx,%ebx
    7f76ecc2f516:	48 c1 e3 38          	shl    $0x38,%rbx
    7f76ecc2f51a:	48 0b cb             	or     %rbx,%rcx
    7f76ecc2f51d:	49 89 8f f8 02 00 00 	mov    %rcx,0x2f8(%r15)
    7f76ecc2f524:	8b 85 08 f7 ff ff    	mov    -0x8f8(%rbp),%eax
    7f76ecc2f52a:	25 ff 00 00 00       	and    $0xff,%eax
    7f76ecc2f52f:	8b c0                	mov    %eax,%eax
    7f76ecc2f531:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7f76ecc2f536:	8b 8d 08 f7 ff ff    	mov    -0x8f8(%rbp),%ecx
    7f76ecc2f53c:	c1 e9 18             	shr    $0x18,%ecx
    7f76ecc2f53f:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7f76ecc2f545:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f547:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7f76ecc2f54c:	8b 95 08 f7 ff ff    	mov    -0x8f8(%rbp),%edx
    7f76ecc2f552:	c1 ea 10             	shr    $0x10,%edx
    7f76ecc2f555:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7f76ecc2f55b:	8b d2                	mov    %edx,%edx
    7f76ecc2f55d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7f76ecc2f562:	8b 9d 08 f7 ff ff    	mov    -0x8f8(%rbp),%ebx
    7f76ecc2f568:	c1 eb 08             	shr    $0x8,%ebx
    7f76ecc2f56b:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7f76ecc2f571:	8b db                	mov    %ebx,%ebx
    7f76ecc2f573:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7f76ecc2f578:	c1 e2 08             	shl    $0x8,%edx
    7f76ecc2f57b:	0b da                	or     %edx,%ebx
    7f76ecc2f57d:	c1 e1 10             	shl    $0x10,%ecx
    7f76ecc2f580:	0b d9                	or     %ecx,%ebx
    7f76ecc2f582:	c1 e0 18             	shl    $0x18,%eax
    7f76ecc2f585:	0b d8                	or     %eax,%ebx
    7f76ecc2f587:	83 f3 36             	xor    $0x36,%ebx
    7f76ecc2f58a:	8b 85 10 f7 ff ff    	mov    -0x8f0(%rbp),%eax
    7f76ecc2f590:	33 d8                	xor    %eax,%ebx
    7f76ecc2f592:	8b 85 18 f7 ff ff    	mov    -0x8e8(%rbp),%eax
    7f76ecc2f598:	33 c3                	xor    %ebx,%eax
    7f76ecc2f59a:	8b 8d 00 f7 ff ff    	mov    -0x900(%rbp),%ecx
    7f76ecc2f5a0:	33 c8                	xor    %eax,%ecx
    7f76ecc2f5a2:	8b 95 08 f7 ff ff    	mov    -0x8f8(%rbp),%edx
    7f76ecc2f5a8:	33 d1                	xor    %ecx,%edx
    7f76ecc2f5aa:	8b c0                	mov    %eax,%eax
    7f76ecc2f5ac:	48 c1 e0 20          	shl    $0x20,%rax
    7f76ecc2f5b0:	8b db                	mov    %ebx,%ebx
    7f76ecc2f5b2:	48 0b c3             	or     %rbx,%rax
    7f76ecc2f5b5:	49 89 87 50 02 00 00 	mov    %rax,0x250(%r15)
    7f76ecc2f5bc:	8b d2                	mov    %edx,%edx
    7f76ecc2f5be:	48 c1 e2 20          	shl    $0x20,%rdx
    7f76ecc2f5c2:	8b c9                	mov    %ecx,%ecx
    7f76ecc2f5c4:	48 0b d1             	or     %rcx,%rdx
    7f76ecc2f5c7:	49 89 97 58 02 00 00 	mov    %rdx,0x258(%r15)
    7f76ecc2f5ce:	49 8b 87 f0 02 00 00 	mov    0x2f0(%r15),%rax
    7f76ecc2f5d5:	49 8b 8f 50 02 00 00 	mov    0x250(%r15),%rcx
    7f76ecc2f5dc:	48 33 c1             	xor    %rcx,%rax
    7f76ecc2f5df:	49 89 87 a0 03 00 00 	mov    %rax,0x3a0(%r15)
    7f76ecc2f5e6:	49 8b 87 f8 02 00 00 	mov    0x2f8(%r15),%rax
    7f76ecc2f5ed:	49 8b 8f 58 02 00 00 	mov    0x258(%r15),%rcx
    7f76ecc2f5f4:	48 33 c1             	xor    %rcx,%rax
    7f76ecc2f5f7:	49 89 87 a8 03 00 00 	mov    %rax,0x3a8(%r15)
    7f76ecc2f5fe:	49 8b 46 10          	mov    0x10(%r14),%rax
    7f76ecc2f602:	8b 00                	mov    (%rax),%eax
    7f76ecc2f604:	89 85 c8 f6 ff ff    	mov    %eax,-0x938(%rbp)
    7f76ecc2f60a:	49 8b 46 20          	mov    0x20(%r14),%rax
    7f76ecc2f60e:	8b 00                	mov    (%rax),%eax
    7f76ecc2f610:	85 c0                	test   %eax,%eax
    7f76ecc2f612:	0f 84 1e 00 00 00    	je     0x7f76ecc2f636
    7f76ecc2f618:	41 c7 87 b0 01 00 00 	movl   $0x0,0x1b0(%r15)
    7f76ecc2f61f:	00 00 00 00 
    7f76ecc2f623:	45 33 ed             	xor    %r13d,%r13d
    7f76ecc2f626:	41 c7 87 b8 01 00 00 	movl   $0x0,0x1b8(%r15)
    7f76ecc2f62d:	00 00 00 00 
    7f76ecc2f631:	e9 2a 00 00 00       	jmpq   0x7f76ecc2f660
    7f76ecc2f636:	41 8b 87 b8 01 00 00 	mov    0x1b8(%r15),%eax
    7f76ecc2f63d:	8b c8                	mov    %eax,%ecx
    7f76ecc2f63f:	83 e1 01             	and    $0x1,%ecx
    7f76ecc2f642:	41 89 8f b0 01 00 00 	mov    %ecx,0x1b0(%r15)
    7f76ecc2f649:	4c 8b e9             	mov    %rcx,%r13
    7f76ecc2f64c:	d1 e8                	shr    %eax
    7f76ecc2f64e:	8b 8d c8 f6 ff ff    	mov    -0x938(%rbp),%ecx
    7f76ecc2f654:	c1 e1 09             	shl    $0x9,%ecx
    7f76ecc2f657:	0b c1                	or     %ecx,%eax
    7f76ecc2f659:	41 89 87 b8 01 00 00 	mov    %eax,0x1b8(%r15)
    7f76ecc2f660:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f663:	48 05 a0 01 00 00    	add    $0x1a0,%rax
    7f76ecc2f669:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f66c:	48 81 c1 a0 03 00 00 	add    $0x3a0,%rcx
    7f76ecc2f673:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f676:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f679:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f67c:	48 05 90 01 00 00    	add    $0x190,%rax
    7f76ecc2f682:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f685:	48 81 c1 90 03 00 00 	add    $0x390,%rcx
    7f76ecc2f68c:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f68f:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f692:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f695:	48 05 80 01 00 00    	add    $0x180,%rax
    7f76ecc2f69b:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f69e:	48 81 c1 80 03 00 00 	add    $0x380,%rcx
    7f76ecc2f6a5:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f6a8:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f6ab:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f6ae:	48 05 70 01 00 00    	add    $0x170,%rax
    7f76ecc2f6b4:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f6b7:	48 81 c1 70 03 00 00 	add    $0x370,%rcx
    7f76ecc2f6be:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f6c1:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f6c4:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f6c7:	48 05 60 01 00 00    	add    $0x160,%rax
    7f76ecc2f6cd:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f6d0:	48 81 c1 60 03 00 00 	add    $0x360,%rcx
    7f76ecc2f6d7:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f6da:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f6dd:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f6e0:	48 05 50 01 00 00    	add    $0x150,%rax
    7f76ecc2f6e6:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f6e9:	48 81 c1 50 03 00 00 	add    $0x350,%rcx
    7f76ecc2f6f0:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f6f3:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f6f6:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f6f9:	48 05 40 01 00 00    	add    $0x140,%rax
    7f76ecc2f6ff:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f702:	48 81 c1 40 03 00 00 	add    $0x340,%rcx
    7f76ecc2f709:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f70c:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f70f:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f712:	48 05 30 01 00 00    	add    $0x130,%rax
    7f76ecc2f718:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f71b:	48 81 c1 30 03 00 00 	add    $0x330,%rcx
    7f76ecc2f722:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f725:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f728:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f72b:	48 05 20 01 00 00    	add    $0x120,%rax
    7f76ecc2f731:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f734:	48 81 c1 20 03 00 00 	add    $0x320,%rcx
    7f76ecc2f73b:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f73e:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f741:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f744:	48 05 10 01 00 00    	add    $0x110,%rax
    7f76ecc2f74a:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f74d:	48 81 c1 10 03 00 00 	add    $0x310,%rcx
    7f76ecc2f754:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f757:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f75a:	49 8b c7             	mov    %r15,%rax
    7f76ecc2f75d:	48 05 00 01 00 00    	add    $0x100,%rax
    7f76ecc2f763:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f766:	48 81 c1 00 03 00 00 	add    $0x300,%rcx
    7f76ecc2f76d:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f770:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f773:	49 8b 46 28          	mov    0x28(%r14),%rax
    7f76ecc2f777:	49 8b cf             	mov    %r15,%rcx
    7f76ecc2f77a:	48 81 c1 a0 01 00 00 	add    $0x1a0,%rcx
    7f76ecc2f781:	0f 10 01             	movups (%rcx),%xmm0
    7f76ecc2f784:	0f 11 00             	movups %xmm0,(%rax)
    7f76ecc2f787:	49 8b 46 30          	mov    0x30(%r14),%rax
    7f76ecc2f78b:	44 89 28             	mov    %r13d,(%rax)
    7f76ecc2f78e:	33 c0                	xor    %eax,%eax
    7f76ecc2f790:	48 8b 1c 24          	mov    (%rsp),%rbx
    7f76ecc2f794:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7f76ecc2f799:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7f76ecc2f79e:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7f76ecc2f7a3:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7f76ecc2f7a8:	48 8b e5             	mov    %rbp,%rsp
    7f76ecc2f7ab:	5d                   	pop    %rbp
    7f76ecc2f7ac:	c3                   	retq   

end

