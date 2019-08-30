function simjit(ptr) : uint

/tmp/libjit-dump.o:     file format elf64-x86-64


Disassembly of section .text:

00007fb40dba412d <.text>:
    7fb40dba412d:	55                   	push   %rbp
    7fb40dba412e:	48 8b ec             	mov    %rsp,%rbp
    7fb40dba4131:	48 81 ec 60 09 00 00 	sub    $0x960,%rsp
    7fb40dba4138:	48 89 1c 24          	mov    %rbx,(%rsp)
    7fb40dba413c:	4c 89 64 24 08       	mov    %r12,0x8(%rsp)
    7fb40dba4141:	4c 89 6c 24 10       	mov    %r13,0x10(%rsp)
    7fb40dba4146:	4c 89 74 24 18       	mov    %r14,0x18(%rsp)
    7fb40dba414b:	4c 89 7c 24 20       	mov    %r15,0x20(%rsp)
    7fb40dba4150:	4c 8b e7             	mov    %rdi,%r12
    7fb40dba4153:	4d 8b 7c 24 08       	mov    0x8(%r12),%r15
    7fb40dba4158:	4d 8b 34 24          	mov    (%r12),%r14
    7fb40dba415c:	45 8b af b0 01 00 00 	mov    0x1b0(%r15),%r13d
    7fb40dba4163:	49 8b 46 18          	mov    0x18(%r14),%rax
    7fb40dba4167:	8b 00                	mov    (%rax),%eax
    7fb40dba4169:	41 8b 8f b0 03 00 00 	mov    0x3b0(%r15),%ecx
    7fb40dba4170:	33 c8                	xor    %eax,%ecx
    7fb40dba4172:	23 c8                	and    %eax,%ecx
    7fb40dba4174:	41 89 87 b0 03 00 00 	mov    %eax,0x3b0(%r15)
    7fb40dba417b:	85 c9                	test   %ecx,%ecx
    7fb40dba417d:	0f 84 2f 46 00 00    	je     0x7fb40dba87b2
    7fb40dba4183:	49 8b 46 08          	mov    0x8(%r14),%rax
    7fb40dba4187:	49 8b 0e             	mov    (%r14),%rcx
    7fb40dba418a:	48 8b 10             	mov    (%rax),%rdx
    7fb40dba418d:	48 8b 19             	mov    (%rcx),%rbx
    7fb40dba4190:	48 33 d3             	xor    %rbx,%rdx
    7fb40dba4193:	49 89 97 00 03 00 00 	mov    %rdx,0x300(%r15)
    7fb40dba419a:	48 8b 40 08          	mov    0x8(%rax),%rax
    7fb40dba419e:	48 8b 51 08          	mov    0x8(%rcx),%rdx
    7fb40dba41a2:	48 33 c2             	xor    %rdx,%rax
    7fb40dba41a5:	49 89 87 08 03 00 00 	mov    %rax,0x308(%r15)
    7fb40dba41ac:	49 0f b6 87 00 01 00 	movzbq 0x100(%r15),%rax
    7fb40dba41b3:	00 
    7fb40dba41b4:	8b c0                	mov    %eax,%eax
    7fb40dba41b6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba41bb:	8b d0                	mov    %eax,%edx
    7fb40dba41bd:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba41c0:	d1 e2                	shl    %edx
    7fb40dba41c2:	8b d8                	mov    %eax,%ebx
    7fb40dba41c4:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba41c7:	83 e3 01             	and    $0x1,%ebx
    7fb40dba41ca:	8b f3                	mov    %ebx,%esi
    7fb40dba41cc:	d1 e6                	shl    %esi
    7fb40dba41ce:	0b f3                	or     %ebx,%esi
    7fb40dba41d0:	8b fb                	mov    %ebx,%edi
    7fb40dba41d2:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba41d5:	0b f7                	or     %edi,%esi
    7fb40dba41d7:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba41da:	0b f3                	or     %ebx,%esi
    7fb40dba41dc:	33 d6                	xor    %esi,%edx
    7fb40dba41de:	49 0f b6 9f 05 01 00 	movzbq 0x105(%r15),%rbx
    7fb40dba41e5:	00 
    7fb40dba41e6:	8b db                	mov    %ebx,%ebx
    7fb40dba41e8:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba41ed:	8b f3                	mov    %ebx,%esi
    7fb40dba41ef:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba41f2:	d1 e6                	shl    %esi
    7fb40dba41f4:	8b fb                	mov    %ebx,%edi
    7fb40dba41f6:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba41f9:	83 e7 01             	and    $0x1,%edi
    7fb40dba41fc:	44 8b c7             	mov    %edi,%r8d
    7fb40dba41ff:	41 d1 e0             	shl    %r8d
    7fb40dba4202:	44 0b c7             	or     %edi,%r8d
    7fb40dba4205:	44 8b cf             	mov    %edi,%r9d
    7fb40dba4208:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba420c:	45 0b c1             	or     %r9d,%r8d
    7fb40dba420f:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba4212:	44 0b c7             	or     %edi,%r8d
    7fb40dba4215:	41 33 f0             	xor    %r8d,%esi
    7fb40dba4218:	8b fe                	mov    %esi,%edi
    7fb40dba421a:	33 fb                	xor    %ebx,%edi
    7fb40dba421c:	33 fa                	xor    %edx,%edi
    7fb40dba421e:	4d 0f b6 87 0a 01 00 	movzbq 0x10a(%r15),%r8
    7fb40dba4225:	00 
    7fb40dba4226:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba4229:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba422e:	41 33 f8             	xor    %r8d,%edi
    7fb40dba4231:	4d 0f b6 8f 0f 01 00 	movzbq 0x10f(%r15),%r9
    7fb40dba4238:	00 
    7fb40dba4239:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba423c:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba4241:	41 33 f9             	xor    %r9d,%edi
    7fb40dba4244:	33 f0                	xor    %eax,%esi
    7fb40dba4246:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba4249:	41 83 e2 7f          	and    $0x7f,%r10d
    7fb40dba424d:	41 d1 e2             	shl    %r10d
    7fb40dba4250:	45 8b d8             	mov    %r8d,%r11d
    7fb40dba4253:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba4257:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba425b:	44 89 5d f8          	mov    %r11d,-0x8(%rbp)
    7fb40dba425f:	41 d1 e3             	shl    %r11d
    7fb40dba4262:	48 89 4d f0          	mov    %rcx,-0x10(%rbp)
    7fb40dba4266:	8b 4d f8             	mov    -0x8(%rbp),%ecx
    7fb40dba4269:	44 0b d9             	or     %ecx,%r11d
    7fb40dba426c:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba426f:	44 0b d9             	or     %ecx,%r11d
    7fb40dba4272:	8b 4d f8             	mov    -0x8(%rbp),%ecx
    7fb40dba4275:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba4278:	44 0b d9             	or     %ecx,%r11d
    7fb40dba427b:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba427e:	41 8b ca             	mov    %r10d,%ecx
    7fb40dba4281:	41 33 c8             	xor    %r8d,%ecx
    7fb40dba4284:	33 f1                	xor    %ecx,%esi
    7fb40dba4286:	41 33 f1             	xor    %r9d,%esi
    7fb40dba4289:	8b c8                	mov    %eax,%ecx
    7fb40dba428b:	33 cb                	xor    %ebx,%ecx
    7fb40dba428d:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba4290:	41 8b c9             	mov    %r9d,%ecx
    7fb40dba4293:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba4296:	d1 e1                	shl    %ecx
    7fb40dba4298:	45 8b d9             	mov    %r9d,%r11d
    7fb40dba429b:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba429f:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba42a3:	44 89 5d e8          	mov    %r11d,-0x18(%rbp)
    7fb40dba42a7:	41 d1 e3             	shl    %r11d
    7fb40dba42aa:	89 55 e0             	mov    %edx,-0x20(%rbp)
    7fb40dba42ad:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fb40dba42b0:	44 0b da             	or     %edx,%r11d
    7fb40dba42b3:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba42b6:	44 0b da             	or     %edx,%r11d
    7fb40dba42b9:	8b 55 e8             	mov    -0x18(%rbp),%edx
    7fb40dba42bc:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba42bf:	44 0b da             	or     %edx,%r11d
    7fb40dba42c2:	41 33 cb             	xor    %r11d,%ecx
    7fb40dba42c5:	44 33 c9             	xor    %ecx,%r9d
    7fb40dba42c8:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba42cb:	8b 55 e0             	mov    -0x20(%rbp),%edx
    7fb40dba42ce:	33 c2                	xor    %edx,%eax
    7fb40dba42d0:	33 d8                	xor    %eax,%ebx
    7fb40dba42d2:	44 33 c3             	xor    %ebx,%r8d
    7fb40dba42d5:	41 33 c8             	xor    %r8d,%ecx
    7fb40dba42d8:	49 0f b6 87 04 01 00 	movzbq 0x104(%r15),%rax
    7fb40dba42df:	00 
    7fb40dba42e0:	8b c0                	mov    %eax,%eax
    7fb40dba42e2:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba42e7:	8b d0                	mov    %eax,%edx
    7fb40dba42e9:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba42ec:	d1 e2                	shl    %edx
    7fb40dba42ee:	8b d8                	mov    %eax,%ebx
    7fb40dba42f0:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba42f3:	83 e3 01             	and    $0x1,%ebx
    7fb40dba42f6:	44 8b c3             	mov    %ebx,%r8d
    7fb40dba42f9:	41 d1 e0             	shl    %r8d
    7fb40dba42fc:	44 0b c3             	or     %ebx,%r8d
    7fb40dba42ff:	44 8b cb             	mov    %ebx,%r9d
    7fb40dba4302:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba4306:	45 0b c1             	or     %r9d,%r8d
    7fb40dba4309:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba430c:	44 0b c3             	or     %ebx,%r8d
    7fb40dba430f:	41 33 d0             	xor    %r8d,%edx
    7fb40dba4312:	49 0f b6 9f 09 01 00 	movzbq 0x109(%r15),%rbx
    7fb40dba4319:	00 
    7fb40dba431a:	8b db                	mov    %ebx,%ebx
    7fb40dba431c:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba4321:	44 8b c3             	mov    %ebx,%r8d
    7fb40dba4324:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba4328:	41 d1 e0             	shl    %r8d
    7fb40dba432b:	44 8b cb             	mov    %ebx,%r9d
    7fb40dba432e:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba4332:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba4336:	45 8b d9             	mov    %r9d,%r11d
    7fb40dba4339:	41 d1 e3             	shl    %r11d
    7fb40dba433c:	45 0b d9             	or     %r9d,%r11d
    7fb40dba433f:	44 89 4d d8          	mov    %r9d,-0x28(%rbp)
    7fb40dba4343:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba4347:	45 0b d9             	or     %r9d,%r11d
    7fb40dba434a:	44 8b 4d d8          	mov    -0x28(%rbp),%r9d
    7fb40dba434e:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba4352:	45 0b d9             	or     %r9d,%r11d
    7fb40dba4355:	45 33 c3             	xor    %r11d,%r8d
    7fb40dba4358:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba435b:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba435e:	44 33 ca             	xor    %edx,%r9d
    7fb40dba4361:	4d 0f b6 9f 0e 01 00 	movzbq 0x10e(%r15),%r11
    7fb40dba4368:	00 
    7fb40dba4369:	45 8b db             	mov    %r11d,%r11d
    7fb40dba436c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba4371:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba4374:	89 7d d0             	mov    %edi,-0x30(%rbp)
    7fb40dba4377:	49 0f b6 bf 03 01 00 	movzbq 0x103(%r15),%rdi
    7fb40dba437e:	00 
    7fb40dba437f:	8b ff                	mov    %edi,%edi
    7fb40dba4381:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba4386:	44 33 cf             	xor    %edi,%r9d
    7fb40dba4389:	44 33 c0             	xor    %eax,%r8d
    7fb40dba438c:	44 89 5d c8          	mov    %r11d,-0x38(%rbp)
    7fb40dba4390:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba4394:	41 d1 e3             	shl    %r11d
    7fb40dba4397:	89 75 c0             	mov    %esi,-0x40(%rbp)
    7fb40dba439a:	8b 75 c8             	mov    -0x38(%rbp),%esi
    7fb40dba439d:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba43a0:	83 e6 01             	and    $0x1,%esi
    7fb40dba43a3:	89 75 b8             	mov    %esi,-0x48(%rbp)
    7fb40dba43a6:	d1 e6                	shl    %esi
    7fb40dba43a8:	44 89 55 b0          	mov    %r10d,-0x50(%rbp)
    7fb40dba43ac:	44 8b 55 b8          	mov    -0x48(%rbp),%r10d
    7fb40dba43b0:	41 0b f2             	or     %r10d,%esi
    7fb40dba43b3:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba43b7:	41 0b f2             	or     %r10d,%esi
    7fb40dba43ba:	44 8b 55 b8          	mov    -0x48(%rbp),%r10d
    7fb40dba43be:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba43c2:	41 0b f2             	or     %r10d,%esi
    7fb40dba43c5:	44 33 de             	xor    %esi,%r11d
    7fb40dba43c8:	41 8b f3             	mov    %r11d,%esi
    7fb40dba43cb:	44 8b 55 c8          	mov    -0x38(%rbp),%r10d
    7fb40dba43cf:	41 33 f2             	xor    %r10d,%esi
    7fb40dba43d2:	44 33 c6             	xor    %esi,%r8d
    7fb40dba43d5:	44 33 c7             	xor    %edi,%r8d
    7fb40dba43d8:	8b f0                	mov    %eax,%esi
    7fb40dba43da:	33 f3                	xor    %ebx,%esi
    7fb40dba43dc:	44 33 de             	xor    %esi,%r11d
    7fb40dba43df:	8b f7                	mov    %edi,%esi
    7fb40dba43e1:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba43e4:	d1 e6                	shl    %esi
    7fb40dba43e6:	44 8b d7             	mov    %edi,%r10d
    7fb40dba43e9:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba43ed:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba43f1:	44 89 55 a8          	mov    %r10d,-0x58(%rbp)
    7fb40dba43f5:	41 d1 e2             	shl    %r10d
    7fb40dba43f8:	89 4d a0             	mov    %ecx,-0x60(%rbp)
    7fb40dba43fb:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fb40dba43fe:	44 0b d1             	or     %ecx,%r10d
    7fb40dba4401:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba4404:	44 0b d1             	or     %ecx,%r10d
    7fb40dba4407:	8b 4d a8             	mov    -0x58(%rbp),%ecx
    7fb40dba440a:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba440d:	44 0b d1             	or     %ecx,%r10d
    7fb40dba4410:	41 33 f2             	xor    %r10d,%esi
    7fb40dba4413:	33 fe                	xor    %esi,%edi
    7fb40dba4415:	44 33 df             	xor    %edi,%r11d
    7fb40dba4418:	33 d0                	xor    %eax,%edx
    7fb40dba441a:	33 da                	xor    %edx,%ebx
    7fb40dba441c:	33 5d c8             	xor    -0x38(%rbp),%ebx
    7fb40dba441f:	33 f3                	xor    %ebx,%esi
    7fb40dba4421:	49 0f b6 87 08 01 00 	movzbq 0x108(%r15),%rax
    7fb40dba4428:	00 
    7fb40dba4429:	8b c0                	mov    %eax,%eax
    7fb40dba442b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba4430:	8b c8                	mov    %eax,%ecx
    7fb40dba4432:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba4435:	d1 e1                	shl    %ecx
    7fb40dba4437:	8b d0                	mov    %eax,%edx
    7fb40dba4439:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba443c:	83 e2 01             	and    $0x1,%edx
    7fb40dba443f:	8b da                	mov    %edx,%ebx
    7fb40dba4441:	d1 e3                	shl    %ebx
    7fb40dba4443:	0b da                	or     %edx,%ebx
    7fb40dba4445:	8b fa                	mov    %edx,%edi
    7fb40dba4447:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba444a:	0b df                	or     %edi,%ebx
    7fb40dba444c:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba444f:	0b da                	or     %edx,%ebx
    7fb40dba4451:	33 cb                	xor    %ebx,%ecx
    7fb40dba4453:	49 0f b6 97 0d 01 00 	movzbq 0x10d(%r15),%rdx
    7fb40dba445a:	00 
    7fb40dba445b:	8b d2                	mov    %edx,%edx
    7fb40dba445d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba4462:	8b da                	mov    %edx,%ebx
    7fb40dba4464:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba4467:	d1 e3                	shl    %ebx
    7fb40dba4469:	8b fa                	mov    %edx,%edi
    7fb40dba446b:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba446e:	83 e7 01             	and    $0x1,%edi
    7fb40dba4471:	44 8b d7             	mov    %edi,%r10d
    7fb40dba4474:	41 d1 e2             	shl    %r10d
    7fb40dba4477:	44 0b d7             	or     %edi,%r10d
    7fb40dba447a:	89 7d 98             	mov    %edi,-0x68(%rbp)
    7fb40dba447d:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba4480:	44 0b d7             	or     %edi,%r10d
    7fb40dba4483:	8b 7d 98             	mov    -0x68(%rbp),%edi
    7fb40dba4486:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba4489:	44 0b d7             	or     %edi,%r10d
    7fb40dba448c:	41 33 da             	xor    %r10d,%ebx
    7fb40dba448f:	8b fb                	mov    %ebx,%edi
    7fb40dba4491:	33 fa                	xor    %edx,%edi
    7fb40dba4493:	33 f9                	xor    %ecx,%edi
    7fb40dba4495:	4d 0f b6 97 02 01 00 	movzbq 0x102(%r15),%r10
    7fb40dba449c:	00 
    7fb40dba449d:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba44a0:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba44a5:	41 33 fa             	xor    %r10d,%edi
    7fb40dba44a8:	44 89 4d 90          	mov    %r9d,-0x70(%rbp)
    7fb40dba44ac:	4d 0f b6 8f 07 01 00 	movzbq 0x107(%r15),%r9
    7fb40dba44b3:	00 
    7fb40dba44b4:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba44b7:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba44bc:	41 33 f9             	xor    %r9d,%edi
    7fb40dba44bf:	33 d8                	xor    %eax,%ebx
    7fb40dba44c1:	44 89 55 88          	mov    %r10d,-0x78(%rbp)
    7fb40dba44c5:	41 83 e2 7f          	and    $0x7f,%r10d
    7fb40dba44c9:	41 d1 e2             	shl    %r10d
    7fb40dba44cc:	44 89 45 80          	mov    %r8d,-0x80(%rbp)
    7fb40dba44d0:	44 8b 45 88          	mov    -0x78(%rbp),%r8d
    7fb40dba44d4:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba44d8:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba44dc:	44 89 85 78 ff ff ff 	mov    %r8d,-0x88(%rbp)
    7fb40dba44e3:	41 d1 e0             	shl    %r8d
    7fb40dba44e6:	44 89 9d 70 ff ff ff 	mov    %r11d,-0x90(%rbp)
    7fb40dba44ed:	44 8b 9d 78 ff ff ff 	mov    -0x88(%rbp),%r11d
    7fb40dba44f4:	45 0b c3             	or     %r11d,%r8d
    7fb40dba44f7:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba44fb:	45 0b c3             	or     %r11d,%r8d
    7fb40dba44fe:	44 8b 9d 78 ff ff ff 	mov    -0x88(%rbp),%r11d
    7fb40dba4505:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba4509:	45 0b c3             	or     %r11d,%r8d
    7fb40dba450c:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba450f:	45 8b c2             	mov    %r10d,%r8d
    7fb40dba4512:	44 8b 5d 88          	mov    -0x78(%rbp),%r11d
    7fb40dba4516:	45 33 c3             	xor    %r11d,%r8d
    7fb40dba4519:	41 33 d8             	xor    %r8d,%ebx
    7fb40dba451c:	41 33 d9             	xor    %r9d,%ebx
    7fb40dba451f:	44 8b c0             	mov    %eax,%r8d
    7fb40dba4522:	44 33 c2             	xor    %edx,%r8d
    7fb40dba4525:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba4528:	45 8b c1             	mov    %r9d,%r8d
    7fb40dba452b:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba452f:	41 d1 e0             	shl    %r8d
    7fb40dba4532:	45 8b d9             	mov    %r9d,%r11d
    7fb40dba4535:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba4539:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba453d:	44 89 9d 68 ff ff ff 	mov    %r11d,-0x98(%rbp)
    7fb40dba4544:	41 d1 e3             	shl    %r11d
    7fb40dba4547:	89 b5 60 ff ff ff    	mov    %esi,-0xa0(%rbp)
    7fb40dba454d:	8b b5 68 ff ff ff    	mov    -0x98(%rbp),%esi
    7fb40dba4553:	44 0b de             	or     %esi,%r11d
    7fb40dba4556:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba4559:	44 0b de             	or     %esi,%r11d
    7fb40dba455c:	8b b5 68 ff ff ff    	mov    -0x98(%rbp),%esi
    7fb40dba4562:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba4565:	44 0b de             	or     %esi,%r11d
    7fb40dba4568:	45 33 c3             	xor    %r11d,%r8d
    7fb40dba456b:	45 33 c8             	xor    %r8d,%r9d
    7fb40dba456e:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba4571:	33 c8                	xor    %eax,%ecx
    7fb40dba4573:	33 d1                	xor    %ecx,%edx
    7fb40dba4575:	33 55 88             	xor    -0x78(%rbp),%edx
    7fb40dba4578:	44 33 c2             	xor    %edx,%r8d
    7fb40dba457b:	49 0f b6 87 0c 01 00 	movzbq 0x10c(%r15),%rax
    7fb40dba4582:	00 
    7fb40dba4583:	8b c0                	mov    %eax,%eax
    7fb40dba4585:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba458a:	8b c8                	mov    %eax,%ecx
    7fb40dba458c:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba458f:	d1 e1                	shl    %ecx
    7fb40dba4591:	8b d0                	mov    %eax,%edx
    7fb40dba4593:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba4596:	83 e2 01             	and    $0x1,%edx
    7fb40dba4599:	8b f2                	mov    %edx,%esi
    7fb40dba459b:	d1 e6                	shl    %esi
    7fb40dba459d:	0b f2                	or     %edx,%esi
    7fb40dba459f:	44 8b ca             	mov    %edx,%r9d
    7fb40dba45a2:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba45a6:	41 0b f1             	or     %r9d,%esi
    7fb40dba45a9:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba45ac:	0b f2                	or     %edx,%esi
    7fb40dba45ae:	33 ce                	xor    %esi,%ecx
    7fb40dba45b0:	49 0f b6 97 01 01 00 	movzbq 0x101(%r15),%rdx
    7fb40dba45b7:	00 
    7fb40dba45b8:	8b d2                	mov    %edx,%edx
    7fb40dba45ba:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba45bf:	8b f2                	mov    %edx,%esi
    7fb40dba45c1:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba45c4:	d1 e6                	shl    %esi
    7fb40dba45c6:	44 8b ca             	mov    %edx,%r9d
    7fb40dba45c9:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba45cd:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba45d1:	45 8b d9             	mov    %r9d,%r11d
    7fb40dba45d4:	41 d1 e3             	shl    %r11d
    7fb40dba45d7:	45 0b d9             	or     %r9d,%r11d
    7fb40dba45da:	44 89 8d 58 ff ff ff 	mov    %r9d,-0xa8(%rbp)
    7fb40dba45e1:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba45e5:	45 0b d9             	or     %r9d,%r11d
    7fb40dba45e8:	44 8b 8d 58 ff ff ff 	mov    -0xa8(%rbp),%r9d
    7fb40dba45ef:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba45f3:	45 0b d9             	or     %r9d,%r11d
    7fb40dba45f6:	41 33 f3             	xor    %r11d,%esi
    7fb40dba45f9:	44 8b ce             	mov    %esi,%r9d
    7fb40dba45fc:	44 33 ca             	xor    %edx,%r9d
    7fb40dba45ff:	44 33 c9             	xor    %ecx,%r9d
    7fb40dba4602:	4d 0f b6 9f 06 01 00 	movzbq 0x106(%r15),%r11
    7fb40dba4609:	00 
    7fb40dba460a:	45 8b db             	mov    %r11d,%r11d
    7fb40dba460d:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba4612:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba4615:	89 bd 50 ff ff ff    	mov    %edi,-0xb0(%rbp)
    7fb40dba461b:	49 0f b6 bf 0b 01 00 	movzbq 0x10b(%r15),%rdi
    7fb40dba4622:	00 
    7fb40dba4623:	8b ff                	mov    %edi,%edi
    7fb40dba4625:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba462a:	44 33 cf             	xor    %edi,%r9d
    7fb40dba462d:	33 f0                	xor    %eax,%esi
    7fb40dba462f:	44 89 9d 48 ff ff ff 	mov    %r11d,-0xb8(%rbp)
    7fb40dba4636:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba463a:	41 d1 e3             	shl    %r11d
    7fb40dba463d:	89 9d 40 ff ff ff    	mov    %ebx,-0xc0(%rbp)
    7fb40dba4643:	8b 9d 48 ff ff ff    	mov    -0xb8(%rbp),%ebx
    7fb40dba4649:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba464c:	83 e3 01             	and    $0x1,%ebx
    7fb40dba464f:	89 9d 38 ff ff ff    	mov    %ebx,-0xc8(%rbp)
    7fb40dba4655:	d1 e3                	shl    %ebx
    7fb40dba4657:	44 89 95 30 ff ff ff 	mov    %r10d,-0xd0(%rbp)
    7fb40dba465e:	44 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%r10d
    7fb40dba4665:	41 0b da             	or     %r10d,%ebx
    7fb40dba4668:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba466c:	41 0b da             	or     %r10d,%ebx
    7fb40dba466f:	44 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%r10d
    7fb40dba4676:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba467a:	41 0b da             	or     %r10d,%ebx
    7fb40dba467d:	44 33 db             	xor    %ebx,%r11d
    7fb40dba4680:	41 8b db             	mov    %r11d,%ebx
    7fb40dba4683:	44 8b 95 48 ff ff ff 	mov    -0xb8(%rbp),%r10d
    7fb40dba468a:	41 33 da             	xor    %r10d,%ebx
    7fb40dba468d:	33 f3                	xor    %ebx,%esi
    7fb40dba468f:	33 f7                	xor    %edi,%esi
    7fb40dba4691:	8b d8                	mov    %eax,%ebx
    7fb40dba4693:	33 da                	xor    %edx,%ebx
    7fb40dba4695:	44 33 db             	xor    %ebx,%r11d
    7fb40dba4698:	8b df                	mov    %edi,%ebx
    7fb40dba469a:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba469d:	d1 e3                	shl    %ebx
    7fb40dba469f:	44 8b d7             	mov    %edi,%r10d
    7fb40dba46a2:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba46a6:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba46aa:	44 89 95 28 ff ff ff 	mov    %r10d,-0xd8(%rbp)
    7fb40dba46b1:	41 d1 e2             	shl    %r10d
    7fb40dba46b4:	44 89 85 20 ff ff ff 	mov    %r8d,-0xe0(%rbp)
    7fb40dba46bb:	44 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%r8d
    7fb40dba46c2:	45 0b d0             	or     %r8d,%r10d
    7fb40dba46c5:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba46c9:	45 0b d0             	or     %r8d,%r10d
    7fb40dba46cc:	44 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%r8d
    7fb40dba46d3:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba46d7:	45 0b d0             	or     %r8d,%r10d
    7fb40dba46da:	41 33 da             	xor    %r10d,%ebx
    7fb40dba46dd:	33 fb                	xor    %ebx,%edi
    7fb40dba46df:	44 33 df             	xor    %edi,%r11d
    7fb40dba46e2:	33 c8                	xor    %eax,%ecx
    7fb40dba46e4:	33 d1                	xor    %ecx,%edx
    7fb40dba46e6:	33 95 48 ff ff ff    	xor    -0xb8(%rbp),%edx
    7fb40dba46ec:	33 da                	xor    %edx,%ebx
    7fb40dba46ee:	8b 45 c0             	mov    -0x40(%rbp),%eax
    7fb40dba46f1:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba46f4:	8b 4d d0             	mov    -0x30(%rbp),%ecx
    7fb40dba46f7:	0b c1                	or     %ecx,%eax
    7fb40dba46f9:	8b 4d b0             	mov    -0x50(%rbp),%ecx
    7fb40dba46fc:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba46ff:	0b c1                	or     %ecx,%eax
    7fb40dba4701:	8b 4d a0             	mov    -0x60(%rbp),%ecx
    7fb40dba4704:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba4707:	0b c1                	or     %ecx,%eax
    7fb40dba4709:	8b 4d 90             	mov    -0x70(%rbp),%ecx
    7fb40dba470c:	8b c9                	mov    %ecx,%ecx
    7fb40dba470e:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba4712:	8b c0                	mov    %eax,%eax
    7fb40dba4714:	48 0b c8             	or     %rax,%rcx
    7fb40dba4717:	8b 45 80             	mov    -0x80(%rbp),%eax
    7fb40dba471a:	8b c0                	mov    %eax,%eax
    7fb40dba471c:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba4720:	48 0b c8             	or     %rax,%rcx
    7fb40dba4723:	8b 85 70 ff ff ff    	mov    -0x90(%rbp),%eax
    7fb40dba4729:	8b c0                	mov    %eax,%eax
    7fb40dba472b:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba472f:	48 0b c8             	or     %rax,%rcx
    7fb40dba4732:	8b 85 60 ff ff ff    	mov    -0xa0(%rbp),%eax
    7fb40dba4738:	8b c0                	mov    %eax,%eax
    7fb40dba473a:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba473e:	48 0b c8             	or     %rax,%rcx
    7fb40dba4741:	49 89 8f 60 02 00 00 	mov    %rcx,0x260(%r15)
    7fb40dba4748:	8b 85 40 ff ff ff    	mov    -0xc0(%rbp),%eax
    7fb40dba474e:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba4751:	8b 8d 50 ff ff ff    	mov    -0xb0(%rbp),%ecx
    7fb40dba4757:	0b c1                	or     %ecx,%eax
    7fb40dba4759:	8b 8d 30 ff ff ff    	mov    -0xd0(%rbp),%ecx
    7fb40dba475f:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba4762:	0b c1                	or     %ecx,%eax
    7fb40dba4764:	8b 8d 20 ff ff ff    	mov    -0xe0(%rbp),%ecx
    7fb40dba476a:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba476d:	0b c1                	or     %ecx,%eax
    7fb40dba476f:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba4772:	49 c1 e1 20          	shl    $0x20,%r9
    7fb40dba4776:	8b c0                	mov    %eax,%eax
    7fb40dba4778:	4c 0b c8             	or     %rax,%r9
    7fb40dba477b:	8b f6                	mov    %esi,%esi
    7fb40dba477d:	48 c1 e6 28          	shl    $0x28,%rsi
    7fb40dba4781:	4c 0b ce             	or     %rsi,%r9
    7fb40dba4784:	45 8b db             	mov    %r11d,%r11d
    7fb40dba4787:	49 c1 e3 30          	shl    $0x30,%r11
    7fb40dba478b:	4d 0b cb             	or     %r11,%r9
    7fb40dba478e:	8b db                	mov    %ebx,%ebx
    7fb40dba4790:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba4794:	4c 0b cb             	or     %rbx,%r9
    7fb40dba4797:	4d 89 8f 68 02 00 00 	mov    %r9,0x268(%r15)
    7fb40dba479e:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    7fb40dba47a2:	8b 41 0c             	mov    0xc(%rcx),%eax
    7fb40dba47a5:	8b 51 08             	mov    0x8(%rcx),%edx
    7fb40dba47a8:	8b 59 04             	mov    0x4(%rcx),%ebx
    7fb40dba47ab:	8b 31                	mov    (%rcx),%esi
    7fb40dba47ad:	48 0f b6 79 0c       	movzbq 0xc(%rcx),%rdi
    7fb40dba47b2:	8b ff                	mov    %edi,%edi
    7fb40dba47b4:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba47b9:	4c 0f b6 41 0f       	movzbq 0xf(%rcx),%r8
    7fb40dba47be:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba47c1:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba47c6:	4c 0f b6 49 0e       	movzbq 0xe(%rcx),%r9
    7fb40dba47cb:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba47ce:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba47d3:	48 0f b6 49 0d       	movzbq 0xd(%rcx),%rcx
    7fb40dba47d8:	8b c9                	mov    %ecx,%ecx
    7fb40dba47da:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba47df:	41 c1 e1 08          	shl    $0x8,%r9d
    7fb40dba47e3:	41 0b c9             	or     %r9d,%ecx
    7fb40dba47e6:	41 c1 e0 10          	shl    $0x10,%r8d
    7fb40dba47ea:	41 0b c8             	or     %r8d,%ecx
    7fb40dba47ed:	c1 e7 18             	shl    $0x18,%edi
    7fb40dba47f0:	0b cf                	or     %edi,%ecx
    7fb40dba47f2:	83 f1 01             	xor    $0x1,%ecx
    7fb40dba47f5:	33 f1                	xor    %ecx,%esi
    7fb40dba47f7:	33 de                	xor    %esi,%ebx
    7fb40dba47f9:	33 d3                	xor    %ebx,%edx
    7fb40dba47fb:	33 c2                	xor    %edx,%eax
    7fb40dba47fd:	8b cb                	mov    %ebx,%ecx
    7fb40dba47ff:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba4803:	8b fe                	mov    %esi,%edi
    7fb40dba4805:	48 0b cf             	or     %rdi,%rcx
    7fb40dba4808:	49 89 8f c0 01 00 00 	mov    %rcx,0x1c0(%r15)
    7fb40dba480f:	8b c8                	mov    %eax,%ecx
    7fb40dba4811:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba4815:	8b fa                	mov    %edx,%edi
    7fb40dba4817:	48 0b cf             	or     %rdi,%rcx
    7fb40dba481a:	49 89 8f c8 01 00 00 	mov    %rcx,0x1c8(%r15)
    7fb40dba4821:	49 8b 8f 60 02 00 00 	mov    0x260(%r15),%rcx
    7fb40dba4828:	49 8b bf c0 01 00 00 	mov    0x1c0(%r15),%rdi
    7fb40dba482f:	48 33 cf             	xor    %rdi,%rcx
    7fb40dba4832:	49 89 8f 10 03 00 00 	mov    %rcx,0x310(%r15)
    7fb40dba4839:	49 8b 8f 68 02 00 00 	mov    0x268(%r15),%rcx
    7fb40dba4840:	49 8b bf c8 01 00 00 	mov    0x1c8(%r15),%rdi
    7fb40dba4847:	48 33 cf             	xor    %rdi,%rcx
    7fb40dba484a:	49 89 8f 18 03 00 00 	mov    %rcx,0x318(%r15)
    7fb40dba4851:	49 0f b6 8f 10 01 00 	movzbq 0x110(%r15),%rcx
    7fb40dba4858:	00 
    7fb40dba4859:	8b c9                	mov    %ecx,%ecx
    7fb40dba485b:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba4860:	8b f9                	mov    %ecx,%edi
    7fb40dba4862:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba4865:	d1 e7                	shl    %edi
    7fb40dba4867:	44 8b c1             	mov    %ecx,%r8d
    7fb40dba486a:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba486e:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba4872:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba4875:	41 d1 e1             	shl    %r9d
    7fb40dba4878:	45 0b c8             	or     %r8d,%r9d
    7fb40dba487b:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba487e:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba4882:	45 0b ca             	or     %r10d,%r9d
    7fb40dba4885:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba4889:	45 0b c8             	or     %r8d,%r9d
    7fb40dba488c:	41 33 f9             	xor    %r9d,%edi
    7fb40dba488f:	4d 0f b6 87 15 01 00 	movzbq 0x115(%r15),%r8
    7fb40dba4896:	00 
    7fb40dba4897:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba489a:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba489f:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba48a2:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba48a6:	41 d1 e1             	shl    %r9d
    7fb40dba48a9:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba48ac:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba48b0:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba48b4:	45 8b da             	mov    %r10d,%r11d
    7fb40dba48b7:	41 d1 e3             	shl    %r11d
    7fb40dba48ba:	45 0b da             	or     %r10d,%r11d
    7fb40dba48bd:	44 89 95 18 ff ff ff 	mov    %r10d,-0xe8(%rbp)
    7fb40dba48c4:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba48c8:	45 0b da             	or     %r10d,%r11d
    7fb40dba48cb:	44 8b 95 18 ff ff ff 	mov    -0xe8(%rbp),%r10d
    7fb40dba48d2:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba48d6:	45 0b da             	or     %r10d,%r11d
    7fb40dba48d9:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba48dc:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba48df:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba48e2:	44 33 d7             	xor    %edi,%r10d
    7fb40dba48e5:	4d 0f b6 9f 1a 01 00 	movzbq 0x11a(%r15),%r11
    7fb40dba48ec:	00 
    7fb40dba48ed:	45 8b db             	mov    %r11d,%r11d
    7fb40dba48f0:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba48f5:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba48f8:	89 9d 10 ff ff ff    	mov    %ebx,-0xf0(%rbp)
    7fb40dba48fe:	49 0f b6 9f 1f 01 00 	movzbq 0x11f(%r15),%rbx
    7fb40dba4905:	00 
    7fb40dba4906:	8b db                	mov    %ebx,%ebx
    7fb40dba4908:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba490d:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba4910:	44 33 c9             	xor    %ecx,%r9d
    7fb40dba4913:	44 89 9d 08 ff ff ff 	mov    %r11d,-0xf8(%rbp)
    7fb40dba491a:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba491e:	41 d1 e3             	shl    %r11d
    7fb40dba4921:	89 b5 00 ff ff ff    	mov    %esi,-0x100(%rbp)
    7fb40dba4927:	8b b5 08 ff ff ff    	mov    -0xf8(%rbp),%esi
    7fb40dba492d:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba4930:	83 e6 01             	and    $0x1,%esi
    7fb40dba4933:	89 b5 f8 fe ff ff    	mov    %esi,-0x108(%rbp)
    7fb40dba4939:	d1 e6                	shl    %esi
    7fb40dba493b:	89 85 f0 fe ff ff    	mov    %eax,-0x110(%rbp)
    7fb40dba4941:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7fb40dba4947:	0b f0                	or     %eax,%esi
    7fb40dba4949:	c1 e0 03             	shl    $0x3,%eax
    7fb40dba494c:	0b f0                	or     %eax,%esi
    7fb40dba494e:	8b 85 f8 fe ff ff    	mov    -0x108(%rbp),%eax
    7fb40dba4954:	c1 e0 04             	shl    $0x4,%eax
    7fb40dba4957:	0b f0                	or     %eax,%esi
    7fb40dba4959:	44 33 de             	xor    %esi,%r11d
    7fb40dba495c:	41 8b c3             	mov    %r11d,%eax
    7fb40dba495f:	8b b5 08 ff ff ff    	mov    -0xf8(%rbp),%esi
    7fb40dba4965:	33 c6                	xor    %esi,%eax
    7fb40dba4967:	44 33 c8             	xor    %eax,%r9d
    7fb40dba496a:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba496d:	8b c1                	mov    %ecx,%eax
    7fb40dba496f:	41 33 c0             	xor    %r8d,%eax
    7fb40dba4972:	44 33 d8             	xor    %eax,%r11d
    7fb40dba4975:	8b c3                	mov    %ebx,%eax
    7fb40dba4977:	83 e0 7f             	and    $0x7f,%eax
    7fb40dba497a:	d1 e0                	shl    %eax
    7fb40dba497c:	8b f3                	mov    %ebx,%esi
    7fb40dba497e:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba4981:	83 e6 01             	and    $0x1,%esi
    7fb40dba4984:	89 b5 e8 fe ff ff    	mov    %esi,-0x118(%rbp)
    7fb40dba498a:	d1 e6                	shl    %esi
    7fb40dba498c:	89 95 e0 fe ff ff    	mov    %edx,-0x120(%rbp)
    7fb40dba4992:	8b 95 e8 fe ff ff    	mov    -0x118(%rbp),%edx
    7fb40dba4998:	0b f2                	or     %edx,%esi
    7fb40dba499a:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba499d:	0b f2                	or     %edx,%esi
    7fb40dba499f:	8b 95 e8 fe ff ff    	mov    -0x118(%rbp),%edx
    7fb40dba49a5:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba49a8:	0b f2                	or     %edx,%esi
    7fb40dba49aa:	33 c6                	xor    %esi,%eax
    7fb40dba49ac:	33 d8                	xor    %eax,%ebx
    7fb40dba49ae:	44 33 db             	xor    %ebx,%r11d
    7fb40dba49b1:	33 f9                	xor    %ecx,%edi
    7fb40dba49b3:	44 33 c7             	xor    %edi,%r8d
    7fb40dba49b6:	44 33 85 08 ff ff ff 	xor    -0xf8(%rbp),%r8d
    7fb40dba49bd:	41 33 c0             	xor    %r8d,%eax
    7fb40dba49c0:	49 0f b6 8f 14 01 00 	movzbq 0x114(%r15),%rcx
    7fb40dba49c7:	00 
    7fb40dba49c8:	8b c9                	mov    %ecx,%ecx
    7fb40dba49ca:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba49cf:	8b d1                	mov    %ecx,%edx
    7fb40dba49d1:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba49d4:	d1 e2                	shl    %edx
    7fb40dba49d6:	8b d9                	mov    %ecx,%ebx
    7fb40dba49d8:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba49db:	83 e3 01             	and    $0x1,%ebx
    7fb40dba49de:	8b f3                	mov    %ebx,%esi
    7fb40dba49e0:	d1 e6                	shl    %esi
    7fb40dba49e2:	0b f3                	or     %ebx,%esi
    7fb40dba49e4:	8b fb                	mov    %ebx,%edi
    7fb40dba49e6:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba49e9:	0b f7                	or     %edi,%esi
    7fb40dba49eb:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba49ee:	0b f3                	or     %ebx,%esi
    7fb40dba49f0:	33 d6                	xor    %esi,%edx
    7fb40dba49f2:	49 0f b6 9f 19 01 00 	movzbq 0x119(%r15),%rbx
    7fb40dba49f9:	00 
    7fb40dba49fa:	8b db                	mov    %ebx,%ebx
    7fb40dba49fc:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba4a01:	8b f3                	mov    %ebx,%esi
    7fb40dba4a03:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba4a06:	d1 e6                	shl    %esi
    7fb40dba4a08:	8b fb                	mov    %ebx,%edi
    7fb40dba4a0a:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba4a0d:	83 e7 01             	and    $0x1,%edi
    7fb40dba4a10:	44 8b c7             	mov    %edi,%r8d
    7fb40dba4a13:	41 d1 e0             	shl    %r8d
    7fb40dba4a16:	44 0b c7             	or     %edi,%r8d
    7fb40dba4a19:	89 bd d8 fe ff ff    	mov    %edi,-0x128(%rbp)
    7fb40dba4a1f:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba4a22:	44 0b c7             	or     %edi,%r8d
    7fb40dba4a25:	8b bd d8 fe ff ff    	mov    -0x128(%rbp),%edi
    7fb40dba4a2b:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba4a2e:	44 0b c7             	or     %edi,%r8d
    7fb40dba4a31:	41 33 f0             	xor    %r8d,%esi
    7fb40dba4a34:	8b fe                	mov    %esi,%edi
    7fb40dba4a36:	33 fb                	xor    %ebx,%edi
    7fb40dba4a38:	33 fa                	xor    %edx,%edi
    7fb40dba4a3a:	4d 0f b6 87 1e 01 00 	movzbq 0x11e(%r15),%r8
    7fb40dba4a41:	00 
    7fb40dba4a42:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba4a45:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba4a4a:	41 33 f8             	xor    %r8d,%edi
    7fb40dba4a4d:	44 89 95 d0 fe ff ff 	mov    %r10d,-0x130(%rbp)
    7fb40dba4a54:	4d 0f b6 97 13 01 00 	movzbq 0x113(%r15),%r10
    7fb40dba4a5b:	00 
    7fb40dba4a5c:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba4a5f:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba4a64:	41 33 fa             	xor    %r10d,%edi
    7fb40dba4a67:	33 f1                	xor    %ecx,%esi
    7fb40dba4a69:	44 89 85 c8 fe ff ff 	mov    %r8d,-0x138(%rbp)
    7fb40dba4a70:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba4a74:	41 d1 e0             	shl    %r8d
    7fb40dba4a77:	44 89 8d c0 fe ff ff 	mov    %r9d,-0x140(%rbp)
    7fb40dba4a7e:	44 8b 8d c8 fe ff ff 	mov    -0x138(%rbp),%r9d
    7fb40dba4a85:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba4a89:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba4a8d:	44 89 8d b8 fe ff ff 	mov    %r9d,-0x148(%rbp)
    7fb40dba4a94:	41 d1 e1             	shl    %r9d
    7fb40dba4a97:	44 89 9d b0 fe ff ff 	mov    %r11d,-0x150(%rbp)
    7fb40dba4a9e:	44 8b 9d b8 fe ff ff 	mov    -0x148(%rbp),%r11d
    7fb40dba4aa5:	45 0b cb             	or     %r11d,%r9d
    7fb40dba4aa8:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba4aac:	45 0b cb             	or     %r11d,%r9d
    7fb40dba4aaf:	44 8b 9d b8 fe ff ff 	mov    -0x148(%rbp),%r11d
    7fb40dba4ab6:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba4aba:	45 0b cb             	or     %r11d,%r9d
    7fb40dba4abd:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba4ac0:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba4ac3:	44 8b 9d c8 fe ff ff 	mov    -0x138(%rbp),%r11d
    7fb40dba4aca:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba4acd:	41 33 f1             	xor    %r9d,%esi
    7fb40dba4ad0:	41 33 f2             	xor    %r10d,%esi
    7fb40dba4ad3:	44 8b c9             	mov    %ecx,%r9d
    7fb40dba4ad6:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba4ad9:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba4adc:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba4adf:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba4ae3:	41 d1 e1             	shl    %r9d
    7fb40dba4ae6:	45 8b da             	mov    %r10d,%r11d
    7fb40dba4ae9:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba4aed:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba4af1:	44 89 9d a8 fe ff ff 	mov    %r11d,-0x158(%rbp)
    7fb40dba4af8:	41 d1 e3             	shl    %r11d
    7fb40dba4afb:	89 85 a0 fe ff ff    	mov    %eax,-0x160(%rbp)
    7fb40dba4b01:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fb40dba4b07:	44 0b d8             	or     %eax,%r11d
    7fb40dba4b0a:	c1 e0 03             	shl    $0x3,%eax
    7fb40dba4b0d:	44 0b d8             	or     %eax,%r11d
    7fb40dba4b10:	8b 85 a8 fe ff ff    	mov    -0x158(%rbp),%eax
    7fb40dba4b16:	c1 e0 04             	shl    $0x4,%eax
    7fb40dba4b19:	44 0b d8             	or     %eax,%r11d
    7fb40dba4b1c:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba4b1f:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba4b22:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba4b25:	33 d1                	xor    %ecx,%edx
    7fb40dba4b27:	33 da                	xor    %edx,%ebx
    7fb40dba4b29:	33 9d c8 fe ff ff    	xor    -0x138(%rbp),%ebx
    7fb40dba4b2f:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba4b32:	49 0f b6 87 18 01 00 	movzbq 0x118(%r15),%rax
    7fb40dba4b39:	00 
    7fb40dba4b3a:	8b c0                	mov    %eax,%eax
    7fb40dba4b3c:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba4b41:	8b c8                	mov    %eax,%ecx
    7fb40dba4b43:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba4b46:	d1 e1                	shl    %ecx
    7fb40dba4b48:	8b d0                	mov    %eax,%edx
    7fb40dba4b4a:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba4b4d:	83 e2 01             	and    $0x1,%edx
    7fb40dba4b50:	8b da                	mov    %edx,%ebx
    7fb40dba4b52:	d1 e3                	shl    %ebx
    7fb40dba4b54:	0b da                	or     %edx,%ebx
    7fb40dba4b56:	44 8b d2             	mov    %edx,%r10d
    7fb40dba4b59:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba4b5d:	41 0b da             	or     %r10d,%ebx
    7fb40dba4b60:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba4b63:	0b da                	or     %edx,%ebx
    7fb40dba4b65:	33 cb                	xor    %ebx,%ecx
    7fb40dba4b67:	49 0f b6 97 1d 01 00 	movzbq 0x11d(%r15),%rdx
    7fb40dba4b6e:	00 
    7fb40dba4b6f:	8b d2                	mov    %edx,%edx
    7fb40dba4b71:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba4b76:	8b da                	mov    %edx,%ebx
    7fb40dba4b78:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba4b7b:	d1 e3                	shl    %ebx
    7fb40dba4b7d:	44 8b d2             	mov    %edx,%r10d
    7fb40dba4b80:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba4b84:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba4b88:	45 8b da             	mov    %r10d,%r11d
    7fb40dba4b8b:	41 d1 e3             	shl    %r11d
    7fb40dba4b8e:	45 0b da             	or     %r10d,%r11d
    7fb40dba4b91:	44 89 95 98 fe ff ff 	mov    %r10d,-0x168(%rbp)
    7fb40dba4b98:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba4b9c:	45 0b da             	or     %r10d,%r11d
    7fb40dba4b9f:	44 8b 95 98 fe ff ff 	mov    -0x168(%rbp),%r10d
    7fb40dba4ba6:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba4baa:	45 0b da             	or     %r10d,%r11d
    7fb40dba4bad:	41 33 db             	xor    %r11d,%ebx
    7fb40dba4bb0:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba4bb3:	44 33 d2             	xor    %edx,%r10d
    7fb40dba4bb6:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba4bb9:	4d 0f b6 9f 12 01 00 	movzbq 0x112(%r15),%r11
    7fb40dba4bc0:	00 
    7fb40dba4bc1:	45 8b db             	mov    %r11d,%r11d
    7fb40dba4bc4:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba4bc9:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba4bcc:	89 bd 90 fe ff ff    	mov    %edi,-0x170(%rbp)
    7fb40dba4bd2:	49 0f b6 bf 17 01 00 	movzbq 0x117(%r15),%rdi
    7fb40dba4bd9:	00 
    7fb40dba4bda:	8b ff                	mov    %edi,%edi
    7fb40dba4bdc:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba4be1:	44 33 d7             	xor    %edi,%r10d
    7fb40dba4be4:	33 d8                	xor    %eax,%ebx
    7fb40dba4be6:	44 89 9d 88 fe ff ff 	mov    %r11d,-0x178(%rbp)
    7fb40dba4bed:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba4bf1:	41 d1 e3             	shl    %r11d
    7fb40dba4bf4:	89 b5 80 fe ff ff    	mov    %esi,-0x180(%rbp)
    7fb40dba4bfa:	8b b5 88 fe ff ff    	mov    -0x178(%rbp),%esi
    7fb40dba4c00:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba4c03:	83 e6 01             	and    $0x1,%esi
    7fb40dba4c06:	89 b5 78 fe ff ff    	mov    %esi,-0x188(%rbp)
    7fb40dba4c0c:	d1 e6                	shl    %esi
    7fb40dba4c0e:	44 89 85 70 fe ff ff 	mov    %r8d,-0x190(%rbp)
    7fb40dba4c15:	44 8b 85 78 fe ff ff 	mov    -0x188(%rbp),%r8d
    7fb40dba4c1c:	41 0b f0             	or     %r8d,%esi
    7fb40dba4c1f:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba4c23:	41 0b f0             	or     %r8d,%esi
    7fb40dba4c26:	44 8b 85 78 fe ff ff 	mov    -0x188(%rbp),%r8d
    7fb40dba4c2d:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba4c31:	41 0b f0             	or     %r8d,%esi
    7fb40dba4c34:	44 33 de             	xor    %esi,%r11d
    7fb40dba4c37:	41 8b f3             	mov    %r11d,%esi
    7fb40dba4c3a:	44 8b 85 88 fe ff ff 	mov    -0x178(%rbp),%r8d
    7fb40dba4c41:	41 33 f0             	xor    %r8d,%esi
    7fb40dba4c44:	33 de                	xor    %esi,%ebx
    7fb40dba4c46:	33 df                	xor    %edi,%ebx
    7fb40dba4c48:	8b f0                	mov    %eax,%esi
    7fb40dba4c4a:	33 f2                	xor    %edx,%esi
    7fb40dba4c4c:	44 33 de             	xor    %esi,%r11d
    7fb40dba4c4f:	8b f7                	mov    %edi,%esi
    7fb40dba4c51:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba4c54:	d1 e6                	shl    %esi
    7fb40dba4c56:	44 8b c7             	mov    %edi,%r8d
    7fb40dba4c59:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba4c5d:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba4c61:	44 89 85 68 fe ff ff 	mov    %r8d,-0x198(%rbp)
    7fb40dba4c68:	41 d1 e0             	shl    %r8d
    7fb40dba4c6b:	44 89 8d 60 fe ff ff 	mov    %r9d,-0x1a0(%rbp)
    7fb40dba4c72:	44 8b 8d 68 fe ff ff 	mov    -0x198(%rbp),%r9d
    7fb40dba4c79:	45 0b c1             	or     %r9d,%r8d
    7fb40dba4c7c:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba4c80:	45 0b c1             	or     %r9d,%r8d
    7fb40dba4c83:	44 8b 8d 68 fe ff ff 	mov    -0x198(%rbp),%r9d
    7fb40dba4c8a:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba4c8e:	45 0b c1             	or     %r9d,%r8d
    7fb40dba4c91:	41 33 f0             	xor    %r8d,%esi
    7fb40dba4c94:	33 fe                	xor    %esi,%edi
    7fb40dba4c96:	44 33 df             	xor    %edi,%r11d
    7fb40dba4c99:	33 c8                	xor    %eax,%ecx
    7fb40dba4c9b:	33 d1                	xor    %ecx,%edx
    7fb40dba4c9d:	33 95 88 fe ff ff    	xor    -0x178(%rbp),%edx
    7fb40dba4ca3:	33 f2                	xor    %edx,%esi
    7fb40dba4ca5:	49 0f b6 87 1c 01 00 	movzbq 0x11c(%r15),%rax
    7fb40dba4cac:	00 
    7fb40dba4cad:	8b c0                	mov    %eax,%eax
    7fb40dba4caf:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba4cb4:	8b c8                	mov    %eax,%ecx
    7fb40dba4cb6:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba4cb9:	d1 e1                	shl    %ecx
    7fb40dba4cbb:	8b d0                	mov    %eax,%edx
    7fb40dba4cbd:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba4cc0:	83 e2 01             	and    $0x1,%edx
    7fb40dba4cc3:	8b fa                	mov    %edx,%edi
    7fb40dba4cc5:	d1 e7                	shl    %edi
    7fb40dba4cc7:	0b fa                	or     %edx,%edi
    7fb40dba4cc9:	44 8b c2             	mov    %edx,%r8d
    7fb40dba4ccc:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba4cd0:	41 0b f8             	or     %r8d,%edi
    7fb40dba4cd3:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba4cd6:	0b fa                	or     %edx,%edi
    7fb40dba4cd8:	33 cf                	xor    %edi,%ecx
    7fb40dba4cda:	49 0f b6 97 11 01 00 	movzbq 0x111(%r15),%rdx
    7fb40dba4ce1:	00 
    7fb40dba4ce2:	8b d2                	mov    %edx,%edx
    7fb40dba4ce4:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba4ce9:	8b fa                	mov    %edx,%edi
    7fb40dba4ceb:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba4cee:	d1 e7                	shl    %edi
    7fb40dba4cf0:	44 8b c2             	mov    %edx,%r8d
    7fb40dba4cf3:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba4cf7:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba4cfb:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba4cfe:	41 d1 e1             	shl    %r9d
    7fb40dba4d01:	45 0b c8             	or     %r8d,%r9d
    7fb40dba4d04:	44 89 85 58 fe ff ff 	mov    %r8d,-0x1a8(%rbp)
    7fb40dba4d0b:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba4d0f:	45 0b c8             	or     %r8d,%r9d
    7fb40dba4d12:	44 8b 85 58 fe ff ff 	mov    -0x1a8(%rbp),%r8d
    7fb40dba4d19:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba4d1d:	45 0b c8             	or     %r8d,%r9d
    7fb40dba4d20:	41 33 f9             	xor    %r9d,%edi
    7fb40dba4d23:	44 8b c7             	mov    %edi,%r8d
    7fb40dba4d26:	44 33 c2             	xor    %edx,%r8d
    7fb40dba4d29:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba4d2c:	4d 0f b6 8f 16 01 00 	movzbq 0x116(%r15),%r9
    7fb40dba4d33:	00 
    7fb40dba4d34:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba4d37:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba4d3c:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba4d3f:	44 89 95 50 fe ff ff 	mov    %r10d,-0x1b0(%rbp)
    7fb40dba4d46:	4d 0f b6 97 1b 01 00 	movzbq 0x11b(%r15),%r10
    7fb40dba4d4d:	00 
    7fb40dba4d4e:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba4d51:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba4d56:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba4d59:	33 f8                	xor    %eax,%edi
    7fb40dba4d5b:	44 89 8d 48 fe ff ff 	mov    %r9d,-0x1b8(%rbp)
    7fb40dba4d62:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba4d66:	41 d1 e1             	shl    %r9d
    7fb40dba4d69:	89 9d 40 fe ff ff    	mov    %ebx,-0x1c0(%rbp)
    7fb40dba4d6f:	8b 9d 48 fe ff ff    	mov    -0x1b8(%rbp),%ebx
    7fb40dba4d75:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba4d78:	83 e3 01             	and    $0x1,%ebx
    7fb40dba4d7b:	89 9d 38 fe ff ff    	mov    %ebx,-0x1c8(%rbp)
    7fb40dba4d81:	d1 e3                	shl    %ebx
    7fb40dba4d83:	44 89 9d 30 fe ff ff 	mov    %r11d,-0x1d0(%rbp)
    7fb40dba4d8a:	44 8b 9d 38 fe ff ff 	mov    -0x1c8(%rbp),%r11d
    7fb40dba4d91:	41 0b db             	or     %r11d,%ebx
    7fb40dba4d94:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba4d98:	41 0b db             	or     %r11d,%ebx
    7fb40dba4d9b:	44 8b 9d 38 fe ff ff 	mov    -0x1c8(%rbp),%r11d
    7fb40dba4da2:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba4da6:	41 0b db             	or     %r11d,%ebx
    7fb40dba4da9:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba4dac:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba4daf:	44 8b 9d 48 fe ff ff 	mov    -0x1b8(%rbp),%r11d
    7fb40dba4db6:	41 33 db             	xor    %r11d,%ebx
    7fb40dba4db9:	33 fb                	xor    %ebx,%edi
    7fb40dba4dbb:	41 33 fa             	xor    %r10d,%edi
    7fb40dba4dbe:	8b d8                	mov    %eax,%ebx
    7fb40dba4dc0:	33 da                	xor    %edx,%ebx
    7fb40dba4dc2:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba4dc5:	41 8b da             	mov    %r10d,%ebx
    7fb40dba4dc8:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba4dcb:	d1 e3                	shl    %ebx
    7fb40dba4dcd:	45 8b da             	mov    %r10d,%r11d
    7fb40dba4dd0:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba4dd4:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba4dd8:	44 89 9d 28 fe ff ff 	mov    %r11d,-0x1d8(%rbp)
    7fb40dba4ddf:	41 d1 e3             	shl    %r11d
    7fb40dba4de2:	89 b5 20 fe ff ff    	mov    %esi,-0x1e0(%rbp)
    7fb40dba4de8:	8b b5 28 fe ff ff    	mov    -0x1d8(%rbp),%esi
    7fb40dba4dee:	44 0b de             	or     %esi,%r11d
    7fb40dba4df1:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba4df4:	44 0b de             	or     %esi,%r11d
    7fb40dba4df7:	8b b5 28 fe ff ff    	mov    -0x1d8(%rbp),%esi
    7fb40dba4dfd:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba4e00:	44 0b de             	or     %esi,%r11d
    7fb40dba4e03:	41 33 db             	xor    %r11d,%ebx
    7fb40dba4e06:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba4e09:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba4e0c:	33 c8                	xor    %eax,%ecx
    7fb40dba4e0e:	33 d1                	xor    %ecx,%edx
    7fb40dba4e10:	33 95 48 fe ff ff    	xor    -0x1b8(%rbp),%edx
    7fb40dba4e16:	33 da                	xor    %edx,%ebx
    7fb40dba4e18:	8b 85 c0 fe ff ff    	mov    -0x140(%rbp),%eax
    7fb40dba4e1e:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba4e21:	8b 8d d0 fe ff ff    	mov    -0x130(%rbp),%ecx
    7fb40dba4e27:	0b c1                	or     %ecx,%eax
    7fb40dba4e29:	8b 8d b0 fe ff ff    	mov    -0x150(%rbp),%ecx
    7fb40dba4e2f:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba4e32:	0b c1                	or     %ecx,%eax
    7fb40dba4e34:	8b 8d a0 fe ff ff    	mov    -0x160(%rbp),%ecx
    7fb40dba4e3a:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba4e3d:	0b c1                	or     %ecx,%eax
    7fb40dba4e3f:	8b 8d 90 fe ff ff    	mov    -0x170(%rbp),%ecx
    7fb40dba4e45:	8b c9                	mov    %ecx,%ecx
    7fb40dba4e47:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba4e4b:	8b c0                	mov    %eax,%eax
    7fb40dba4e4d:	48 0b c8             	or     %rax,%rcx
    7fb40dba4e50:	8b 85 80 fe ff ff    	mov    -0x180(%rbp),%eax
    7fb40dba4e56:	8b c0                	mov    %eax,%eax
    7fb40dba4e58:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba4e5c:	48 0b c8             	or     %rax,%rcx
    7fb40dba4e5f:	8b 85 70 fe ff ff    	mov    -0x190(%rbp),%eax
    7fb40dba4e65:	8b c0                	mov    %eax,%eax
    7fb40dba4e67:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba4e6b:	48 0b c8             	or     %rax,%rcx
    7fb40dba4e6e:	8b 85 60 fe ff ff    	mov    -0x1a0(%rbp),%eax
    7fb40dba4e74:	8b c0                	mov    %eax,%eax
    7fb40dba4e76:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba4e7a:	48 0b c8             	or     %rax,%rcx
    7fb40dba4e7d:	49 89 8f 70 02 00 00 	mov    %rcx,0x270(%r15)
    7fb40dba4e84:	8b 85 40 fe ff ff    	mov    -0x1c0(%rbp),%eax
    7fb40dba4e8a:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba4e8d:	8b 8d 50 fe ff ff    	mov    -0x1b0(%rbp),%ecx
    7fb40dba4e93:	0b c1                	or     %ecx,%eax
    7fb40dba4e95:	8b 8d 30 fe ff ff    	mov    -0x1d0(%rbp),%ecx
    7fb40dba4e9b:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba4e9e:	0b c1                	or     %ecx,%eax
    7fb40dba4ea0:	8b 8d 20 fe ff ff    	mov    -0x1e0(%rbp),%ecx
    7fb40dba4ea6:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba4ea9:	0b c1                	or     %ecx,%eax
    7fb40dba4eab:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba4eae:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba4eb2:	8b c0                	mov    %eax,%eax
    7fb40dba4eb4:	4c 0b c0             	or     %rax,%r8
    7fb40dba4eb7:	8b ff                	mov    %edi,%edi
    7fb40dba4eb9:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba4ebd:	4c 0b c7             	or     %rdi,%r8
    7fb40dba4ec0:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba4ec3:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba4ec7:	4d 0b c1             	or     %r9,%r8
    7fb40dba4eca:	8b db                	mov    %ebx,%ebx
    7fb40dba4ecc:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba4ed0:	4c 0b c3             	or     %rbx,%r8
    7fb40dba4ed3:	4d 89 87 78 02 00 00 	mov    %r8,0x278(%r15)
    7fb40dba4eda:	8b 85 f0 fe ff ff    	mov    -0x110(%rbp),%eax
    7fb40dba4ee0:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba4ee5:	8b c0                	mov    %eax,%eax
    7fb40dba4ee7:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba4eec:	8b 8d f0 fe ff ff    	mov    -0x110(%rbp),%ecx
    7fb40dba4ef2:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba4ef5:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba4efb:	8b c9                	mov    %ecx,%ecx
    7fb40dba4efd:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba4f02:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fb40dba4f08:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba4f0b:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba4f11:	8b d2                	mov    %edx,%edx
    7fb40dba4f13:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba4f18:	8b 9d f0 fe ff ff    	mov    -0x110(%rbp),%ebx
    7fb40dba4f1e:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba4f21:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba4f27:	8b db                	mov    %ebx,%ebx
    7fb40dba4f29:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba4f2e:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba4f31:	0b da                	or     %edx,%ebx
    7fb40dba4f33:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba4f36:	0b d9                	or     %ecx,%ebx
    7fb40dba4f38:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba4f3b:	0b d8                	or     %eax,%ebx
    7fb40dba4f3d:	83 f3 02             	xor    $0x2,%ebx
    7fb40dba4f40:	8b 85 00 ff ff ff    	mov    -0x100(%rbp),%eax
    7fb40dba4f46:	33 d8                	xor    %eax,%ebx
    7fb40dba4f48:	8b 85 10 ff ff ff    	mov    -0xf0(%rbp),%eax
    7fb40dba4f4e:	33 c3                	xor    %ebx,%eax
    7fb40dba4f50:	8b 8d e0 fe ff ff    	mov    -0x120(%rbp),%ecx
    7fb40dba4f56:	33 c8                	xor    %eax,%ecx
    7fb40dba4f58:	8b 95 f0 fe ff ff    	mov    -0x110(%rbp),%edx
    7fb40dba4f5e:	33 d1                	xor    %ecx,%edx
    7fb40dba4f60:	8b f0                	mov    %eax,%esi
    7fb40dba4f62:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba4f66:	8b fb                	mov    %ebx,%edi
    7fb40dba4f68:	48 0b f7             	or     %rdi,%rsi
    7fb40dba4f6b:	49 89 b7 d0 01 00 00 	mov    %rsi,0x1d0(%r15)
    7fb40dba4f72:	8b f2                	mov    %edx,%esi
    7fb40dba4f74:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba4f78:	8b f9                	mov    %ecx,%edi
    7fb40dba4f7a:	48 0b f7             	or     %rdi,%rsi
    7fb40dba4f7d:	49 89 b7 d8 01 00 00 	mov    %rsi,0x1d8(%r15)
    7fb40dba4f84:	49 8b b7 70 02 00 00 	mov    0x270(%r15),%rsi
    7fb40dba4f8b:	49 8b bf d0 01 00 00 	mov    0x1d0(%r15),%rdi
    7fb40dba4f92:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba4f95:	49 89 b7 20 03 00 00 	mov    %rsi,0x320(%r15)
    7fb40dba4f9c:	49 8b b7 78 02 00 00 	mov    0x278(%r15),%rsi
    7fb40dba4fa3:	49 8b bf d8 01 00 00 	mov    0x1d8(%r15),%rdi
    7fb40dba4faa:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba4fad:	49 89 b7 28 03 00 00 	mov    %rsi,0x328(%r15)
    7fb40dba4fb4:	49 0f b6 b7 20 01 00 	movzbq 0x120(%r15),%rsi
    7fb40dba4fbb:	00 
    7fb40dba4fbc:	8b f6                	mov    %esi,%esi
    7fb40dba4fbe:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba4fc3:	8b fe                	mov    %esi,%edi
    7fb40dba4fc5:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba4fc8:	d1 e7                	shl    %edi
    7fb40dba4fca:	44 8b c6             	mov    %esi,%r8d
    7fb40dba4fcd:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba4fd1:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba4fd5:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba4fd8:	41 d1 e1             	shl    %r9d
    7fb40dba4fdb:	45 0b c8             	or     %r8d,%r9d
    7fb40dba4fde:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba4fe1:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba4fe5:	45 0b ca             	or     %r10d,%r9d
    7fb40dba4fe8:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba4fec:	45 0b c8             	or     %r8d,%r9d
    7fb40dba4fef:	41 33 f9             	xor    %r9d,%edi
    7fb40dba4ff2:	4d 0f b6 87 25 01 00 	movzbq 0x125(%r15),%r8
    7fb40dba4ff9:	00 
    7fb40dba4ffa:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba4ffd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba5002:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5005:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba5009:	41 d1 e1             	shl    %r9d
    7fb40dba500c:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba500f:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba5013:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba5017:	45 8b da             	mov    %r10d,%r11d
    7fb40dba501a:	41 d1 e3             	shl    %r11d
    7fb40dba501d:	45 0b da             	or     %r10d,%r11d
    7fb40dba5020:	44 89 95 18 fe ff ff 	mov    %r10d,-0x1e8(%rbp)
    7fb40dba5027:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba502b:	45 0b da             	or     %r10d,%r11d
    7fb40dba502e:	44 8b 95 18 fe ff ff 	mov    -0x1e8(%rbp),%r10d
    7fb40dba5035:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba5039:	45 0b da             	or     %r10d,%r11d
    7fb40dba503c:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba503f:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba5042:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba5045:	44 33 d7             	xor    %edi,%r10d
    7fb40dba5048:	4d 0f b6 9f 2a 01 00 	movzbq 0x12a(%r15),%r11
    7fb40dba504f:	00 
    7fb40dba5050:	45 8b db             	mov    %r11d,%r11d
    7fb40dba5053:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba5058:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba505b:	89 85 10 fe ff ff    	mov    %eax,-0x1f0(%rbp)
    7fb40dba5061:	49 0f b6 87 2f 01 00 	movzbq 0x12f(%r15),%rax
    7fb40dba5068:	00 
    7fb40dba5069:	8b c0                	mov    %eax,%eax
    7fb40dba506b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5070:	44 33 d0             	xor    %eax,%r10d
    7fb40dba5073:	44 33 ce             	xor    %esi,%r9d
    7fb40dba5076:	44 89 9d 08 fe ff ff 	mov    %r11d,-0x1f8(%rbp)
    7fb40dba507d:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba5081:	41 d1 e3             	shl    %r11d
    7fb40dba5084:	89 9d 00 fe ff ff    	mov    %ebx,-0x200(%rbp)
    7fb40dba508a:	8b 9d 08 fe ff ff    	mov    -0x1f8(%rbp),%ebx
    7fb40dba5090:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba5093:	83 e3 01             	and    $0x1,%ebx
    7fb40dba5096:	89 9d f8 fd ff ff    	mov    %ebx,-0x208(%rbp)
    7fb40dba509c:	d1 e3                	shl    %ebx
    7fb40dba509e:	89 95 f0 fd ff ff    	mov    %edx,-0x210(%rbp)
    7fb40dba50a4:	8b 95 f8 fd ff ff    	mov    -0x208(%rbp),%edx
    7fb40dba50aa:	0b da                	or     %edx,%ebx
    7fb40dba50ac:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba50af:	0b da                	or     %edx,%ebx
    7fb40dba50b1:	8b 95 f8 fd ff ff    	mov    -0x208(%rbp),%edx
    7fb40dba50b7:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba50ba:	0b da                	or     %edx,%ebx
    7fb40dba50bc:	44 33 db             	xor    %ebx,%r11d
    7fb40dba50bf:	41 8b d3             	mov    %r11d,%edx
    7fb40dba50c2:	8b 9d 08 fe ff ff    	mov    -0x1f8(%rbp),%ebx
    7fb40dba50c8:	33 d3                	xor    %ebx,%edx
    7fb40dba50ca:	44 33 ca             	xor    %edx,%r9d
    7fb40dba50cd:	44 33 c8             	xor    %eax,%r9d
    7fb40dba50d0:	8b d6                	mov    %esi,%edx
    7fb40dba50d2:	41 33 d0             	xor    %r8d,%edx
    7fb40dba50d5:	44 33 da             	xor    %edx,%r11d
    7fb40dba50d8:	8b d0                	mov    %eax,%edx
    7fb40dba50da:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba50dd:	d1 e2                	shl    %edx
    7fb40dba50df:	8b d8                	mov    %eax,%ebx
    7fb40dba50e1:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba50e4:	83 e3 01             	and    $0x1,%ebx
    7fb40dba50e7:	89 9d e8 fd ff ff    	mov    %ebx,-0x218(%rbp)
    7fb40dba50ed:	d1 e3                	shl    %ebx
    7fb40dba50ef:	89 8d e0 fd ff ff    	mov    %ecx,-0x220(%rbp)
    7fb40dba50f5:	8b 8d e8 fd ff ff    	mov    -0x218(%rbp),%ecx
    7fb40dba50fb:	0b d9                	or     %ecx,%ebx
    7fb40dba50fd:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba5100:	0b d9                	or     %ecx,%ebx
    7fb40dba5102:	8b 8d e8 fd ff ff    	mov    -0x218(%rbp),%ecx
    7fb40dba5108:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba510b:	0b d9                	or     %ecx,%ebx
    7fb40dba510d:	33 d3                	xor    %ebx,%edx
    7fb40dba510f:	33 c2                	xor    %edx,%eax
    7fb40dba5111:	44 33 d8             	xor    %eax,%r11d
    7fb40dba5114:	33 fe                	xor    %esi,%edi
    7fb40dba5116:	44 33 c7             	xor    %edi,%r8d
    7fb40dba5119:	44 33 85 08 fe ff ff 	xor    -0x1f8(%rbp),%r8d
    7fb40dba5120:	41 33 d0             	xor    %r8d,%edx
    7fb40dba5123:	49 0f b6 87 24 01 00 	movzbq 0x124(%r15),%rax
    7fb40dba512a:	00 
    7fb40dba512b:	8b c0                	mov    %eax,%eax
    7fb40dba512d:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5132:	8b c8                	mov    %eax,%ecx
    7fb40dba5134:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba5137:	d1 e1                	shl    %ecx
    7fb40dba5139:	8b d8                	mov    %eax,%ebx
    7fb40dba513b:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba513e:	83 e3 01             	and    $0x1,%ebx
    7fb40dba5141:	8b f3                	mov    %ebx,%esi
    7fb40dba5143:	d1 e6                	shl    %esi
    7fb40dba5145:	0b f3                	or     %ebx,%esi
    7fb40dba5147:	8b fb                	mov    %ebx,%edi
    7fb40dba5149:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba514c:	0b f7                	or     %edi,%esi
    7fb40dba514e:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba5151:	0b f3                	or     %ebx,%esi
    7fb40dba5153:	33 ce                	xor    %esi,%ecx
    7fb40dba5155:	49 0f b6 9f 29 01 00 	movzbq 0x129(%r15),%rbx
    7fb40dba515c:	00 
    7fb40dba515d:	8b db                	mov    %ebx,%ebx
    7fb40dba515f:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba5164:	8b f3                	mov    %ebx,%esi
    7fb40dba5166:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba5169:	d1 e6                	shl    %esi
    7fb40dba516b:	8b fb                	mov    %ebx,%edi
    7fb40dba516d:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba5170:	83 e7 01             	and    $0x1,%edi
    7fb40dba5173:	44 8b c7             	mov    %edi,%r8d
    7fb40dba5176:	41 d1 e0             	shl    %r8d
    7fb40dba5179:	44 0b c7             	or     %edi,%r8d
    7fb40dba517c:	89 bd d8 fd ff ff    	mov    %edi,-0x228(%rbp)
    7fb40dba5182:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba5185:	44 0b c7             	or     %edi,%r8d
    7fb40dba5188:	8b bd d8 fd ff ff    	mov    -0x228(%rbp),%edi
    7fb40dba518e:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba5191:	44 0b c7             	or     %edi,%r8d
    7fb40dba5194:	41 33 f0             	xor    %r8d,%esi
    7fb40dba5197:	8b fe                	mov    %esi,%edi
    7fb40dba5199:	33 fb                	xor    %ebx,%edi
    7fb40dba519b:	33 f9                	xor    %ecx,%edi
    7fb40dba519d:	4d 0f b6 87 2e 01 00 	movzbq 0x12e(%r15),%r8
    7fb40dba51a4:	00 
    7fb40dba51a5:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba51a8:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba51ad:	41 33 f8             	xor    %r8d,%edi
    7fb40dba51b0:	44 89 95 d0 fd ff ff 	mov    %r10d,-0x230(%rbp)
    7fb40dba51b7:	4d 0f b6 97 23 01 00 	movzbq 0x123(%r15),%r10
    7fb40dba51be:	00 
    7fb40dba51bf:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba51c2:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba51c7:	41 33 fa             	xor    %r10d,%edi
    7fb40dba51ca:	33 f0                	xor    %eax,%esi
    7fb40dba51cc:	44 89 85 c8 fd ff ff 	mov    %r8d,-0x238(%rbp)
    7fb40dba51d3:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba51d7:	41 d1 e0             	shl    %r8d
    7fb40dba51da:	44 89 8d c0 fd ff ff 	mov    %r9d,-0x240(%rbp)
    7fb40dba51e1:	44 8b 8d c8 fd ff ff 	mov    -0x238(%rbp),%r9d
    7fb40dba51e8:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba51ec:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba51f0:	44 89 8d b8 fd ff ff 	mov    %r9d,-0x248(%rbp)
    7fb40dba51f7:	41 d1 e1             	shl    %r9d
    7fb40dba51fa:	44 89 9d b0 fd ff ff 	mov    %r11d,-0x250(%rbp)
    7fb40dba5201:	44 8b 9d b8 fd ff ff 	mov    -0x248(%rbp),%r11d
    7fb40dba5208:	45 0b cb             	or     %r11d,%r9d
    7fb40dba520b:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba520f:	45 0b cb             	or     %r11d,%r9d
    7fb40dba5212:	44 8b 9d b8 fd ff ff 	mov    -0x248(%rbp),%r11d
    7fb40dba5219:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba521d:	45 0b cb             	or     %r11d,%r9d
    7fb40dba5220:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba5223:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5226:	44 8b 9d c8 fd ff ff 	mov    -0x238(%rbp),%r11d
    7fb40dba522d:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba5230:	41 33 f1             	xor    %r9d,%esi
    7fb40dba5233:	41 33 f2             	xor    %r10d,%esi
    7fb40dba5236:	44 8b c8             	mov    %eax,%r9d
    7fb40dba5239:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba523c:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba523f:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba5242:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba5246:	41 d1 e1             	shl    %r9d
    7fb40dba5249:	45 8b da             	mov    %r10d,%r11d
    7fb40dba524c:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba5250:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba5254:	44 89 9d a8 fd ff ff 	mov    %r11d,-0x258(%rbp)
    7fb40dba525b:	41 d1 e3             	shl    %r11d
    7fb40dba525e:	89 95 a0 fd ff ff    	mov    %edx,-0x260(%rbp)
    7fb40dba5264:	8b 95 a8 fd ff ff    	mov    -0x258(%rbp),%edx
    7fb40dba526a:	44 0b da             	or     %edx,%r11d
    7fb40dba526d:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba5270:	44 0b da             	or     %edx,%r11d
    7fb40dba5273:	8b 95 a8 fd ff ff    	mov    -0x258(%rbp),%edx
    7fb40dba5279:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba527c:	44 0b da             	or     %edx,%r11d
    7fb40dba527f:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba5282:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba5285:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba5288:	33 c8                	xor    %eax,%ecx
    7fb40dba528a:	33 d9                	xor    %ecx,%ebx
    7fb40dba528c:	33 9d c8 fd ff ff    	xor    -0x238(%rbp),%ebx
    7fb40dba5292:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba5295:	49 0f b6 87 28 01 00 	movzbq 0x128(%r15),%rax
    7fb40dba529c:	00 
    7fb40dba529d:	8b c0                	mov    %eax,%eax
    7fb40dba529f:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba52a4:	8b c8                	mov    %eax,%ecx
    7fb40dba52a6:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba52a9:	d1 e1                	shl    %ecx
    7fb40dba52ab:	8b d0                	mov    %eax,%edx
    7fb40dba52ad:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba52b0:	83 e2 01             	and    $0x1,%edx
    7fb40dba52b3:	8b da                	mov    %edx,%ebx
    7fb40dba52b5:	d1 e3                	shl    %ebx
    7fb40dba52b7:	0b da                	or     %edx,%ebx
    7fb40dba52b9:	44 8b d2             	mov    %edx,%r10d
    7fb40dba52bc:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba52c0:	41 0b da             	or     %r10d,%ebx
    7fb40dba52c3:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba52c6:	0b da                	or     %edx,%ebx
    7fb40dba52c8:	33 cb                	xor    %ebx,%ecx
    7fb40dba52ca:	49 0f b6 97 2d 01 00 	movzbq 0x12d(%r15),%rdx
    7fb40dba52d1:	00 
    7fb40dba52d2:	8b d2                	mov    %edx,%edx
    7fb40dba52d4:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba52d9:	8b da                	mov    %edx,%ebx
    7fb40dba52db:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba52de:	d1 e3                	shl    %ebx
    7fb40dba52e0:	44 8b d2             	mov    %edx,%r10d
    7fb40dba52e3:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba52e7:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba52eb:	45 8b da             	mov    %r10d,%r11d
    7fb40dba52ee:	41 d1 e3             	shl    %r11d
    7fb40dba52f1:	45 0b da             	or     %r10d,%r11d
    7fb40dba52f4:	44 89 95 98 fd ff ff 	mov    %r10d,-0x268(%rbp)
    7fb40dba52fb:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba52ff:	45 0b da             	or     %r10d,%r11d
    7fb40dba5302:	44 8b 95 98 fd ff ff 	mov    -0x268(%rbp),%r10d
    7fb40dba5309:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba530d:	45 0b da             	or     %r10d,%r11d
    7fb40dba5310:	41 33 db             	xor    %r11d,%ebx
    7fb40dba5313:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba5316:	44 33 d2             	xor    %edx,%r10d
    7fb40dba5319:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba531c:	4d 0f b6 9f 22 01 00 	movzbq 0x122(%r15),%r11
    7fb40dba5323:	00 
    7fb40dba5324:	45 8b db             	mov    %r11d,%r11d
    7fb40dba5327:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba532c:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba532f:	89 bd 90 fd ff ff    	mov    %edi,-0x270(%rbp)
    7fb40dba5335:	49 0f b6 bf 27 01 00 	movzbq 0x127(%r15),%rdi
    7fb40dba533c:	00 
    7fb40dba533d:	8b ff                	mov    %edi,%edi
    7fb40dba533f:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba5344:	44 33 d7             	xor    %edi,%r10d
    7fb40dba5347:	33 d8                	xor    %eax,%ebx
    7fb40dba5349:	44 89 9d 88 fd ff ff 	mov    %r11d,-0x278(%rbp)
    7fb40dba5350:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba5354:	41 d1 e3             	shl    %r11d
    7fb40dba5357:	89 b5 80 fd ff ff    	mov    %esi,-0x280(%rbp)
    7fb40dba535d:	8b b5 88 fd ff ff    	mov    -0x278(%rbp),%esi
    7fb40dba5363:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba5366:	83 e6 01             	and    $0x1,%esi
    7fb40dba5369:	89 b5 78 fd ff ff    	mov    %esi,-0x288(%rbp)
    7fb40dba536f:	d1 e6                	shl    %esi
    7fb40dba5371:	44 89 85 70 fd ff ff 	mov    %r8d,-0x290(%rbp)
    7fb40dba5378:	44 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%r8d
    7fb40dba537f:	41 0b f0             	or     %r8d,%esi
    7fb40dba5382:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba5386:	41 0b f0             	or     %r8d,%esi
    7fb40dba5389:	44 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%r8d
    7fb40dba5390:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba5394:	41 0b f0             	or     %r8d,%esi
    7fb40dba5397:	44 33 de             	xor    %esi,%r11d
    7fb40dba539a:	41 8b f3             	mov    %r11d,%esi
    7fb40dba539d:	44 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%r8d
    7fb40dba53a4:	41 33 f0             	xor    %r8d,%esi
    7fb40dba53a7:	33 de                	xor    %esi,%ebx
    7fb40dba53a9:	33 df                	xor    %edi,%ebx
    7fb40dba53ab:	8b f0                	mov    %eax,%esi
    7fb40dba53ad:	33 f2                	xor    %edx,%esi
    7fb40dba53af:	44 33 de             	xor    %esi,%r11d
    7fb40dba53b2:	8b f7                	mov    %edi,%esi
    7fb40dba53b4:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba53b7:	d1 e6                	shl    %esi
    7fb40dba53b9:	44 8b c7             	mov    %edi,%r8d
    7fb40dba53bc:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba53c0:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba53c4:	44 89 85 68 fd ff ff 	mov    %r8d,-0x298(%rbp)
    7fb40dba53cb:	41 d1 e0             	shl    %r8d
    7fb40dba53ce:	44 89 8d 60 fd ff ff 	mov    %r9d,-0x2a0(%rbp)
    7fb40dba53d5:	44 8b 8d 68 fd ff ff 	mov    -0x298(%rbp),%r9d
    7fb40dba53dc:	45 0b c1             	or     %r9d,%r8d
    7fb40dba53df:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba53e3:	45 0b c1             	or     %r9d,%r8d
    7fb40dba53e6:	44 8b 8d 68 fd ff ff 	mov    -0x298(%rbp),%r9d
    7fb40dba53ed:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba53f1:	45 0b c1             	or     %r9d,%r8d
    7fb40dba53f4:	41 33 f0             	xor    %r8d,%esi
    7fb40dba53f7:	33 fe                	xor    %esi,%edi
    7fb40dba53f9:	44 33 df             	xor    %edi,%r11d
    7fb40dba53fc:	33 c8                	xor    %eax,%ecx
    7fb40dba53fe:	33 d1                	xor    %ecx,%edx
    7fb40dba5400:	33 95 88 fd ff ff    	xor    -0x278(%rbp),%edx
    7fb40dba5406:	33 f2                	xor    %edx,%esi
    7fb40dba5408:	49 0f b6 87 2c 01 00 	movzbq 0x12c(%r15),%rax
    7fb40dba540f:	00 
    7fb40dba5410:	8b c0                	mov    %eax,%eax
    7fb40dba5412:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5417:	8b c8                	mov    %eax,%ecx
    7fb40dba5419:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba541c:	d1 e1                	shl    %ecx
    7fb40dba541e:	8b d0                	mov    %eax,%edx
    7fb40dba5420:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba5423:	83 e2 01             	and    $0x1,%edx
    7fb40dba5426:	8b fa                	mov    %edx,%edi
    7fb40dba5428:	d1 e7                	shl    %edi
    7fb40dba542a:	0b fa                	or     %edx,%edi
    7fb40dba542c:	44 8b c2             	mov    %edx,%r8d
    7fb40dba542f:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba5433:	41 0b f8             	or     %r8d,%edi
    7fb40dba5436:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba5439:	0b fa                	or     %edx,%edi
    7fb40dba543b:	33 cf                	xor    %edi,%ecx
    7fb40dba543d:	49 0f b6 97 21 01 00 	movzbq 0x121(%r15),%rdx
    7fb40dba5444:	00 
    7fb40dba5445:	8b d2                	mov    %edx,%edx
    7fb40dba5447:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba544c:	8b fa                	mov    %edx,%edi
    7fb40dba544e:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba5451:	d1 e7                	shl    %edi
    7fb40dba5453:	44 8b c2             	mov    %edx,%r8d
    7fb40dba5456:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba545a:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba545e:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5461:	41 d1 e1             	shl    %r9d
    7fb40dba5464:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5467:	44 89 85 58 fd ff ff 	mov    %r8d,-0x2a8(%rbp)
    7fb40dba546e:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba5472:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5475:	44 8b 85 58 fd ff ff 	mov    -0x2a8(%rbp),%r8d
    7fb40dba547c:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba5480:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5483:	41 33 f9             	xor    %r9d,%edi
    7fb40dba5486:	44 8b c7             	mov    %edi,%r8d
    7fb40dba5489:	44 33 c2             	xor    %edx,%r8d
    7fb40dba548c:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba548f:	4d 0f b6 8f 26 01 00 	movzbq 0x126(%r15),%r9
    7fb40dba5496:	00 
    7fb40dba5497:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba549a:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba549f:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba54a2:	44 89 95 50 fd ff ff 	mov    %r10d,-0x2b0(%rbp)
    7fb40dba54a9:	4d 0f b6 97 2b 01 00 	movzbq 0x12b(%r15),%r10
    7fb40dba54b0:	00 
    7fb40dba54b1:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba54b4:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba54b9:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba54bc:	33 f8                	xor    %eax,%edi
    7fb40dba54be:	44 89 8d 48 fd ff ff 	mov    %r9d,-0x2b8(%rbp)
    7fb40dba54c5:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba54c9:	41 d1 e1             	shl    %r9d
    7fb40dba54cc:	89 9d 40 fd ff ff    	mov    %ebx,-0x2c0(%rbp)
    7fb40dba54d2:	8b 9d 48 fd ff ff    	mov    -0x2b8(%rbp),%ebx
    7fb40dba54d8:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba54db:	83 e3 01             	and    $0x1,%ebx
    7fb40dba54de:	89 9d 38 fd ff ff    	mov    %ebx,-0x2c8(%rbp)
    7fb40dba54e4:	d1 e3                	shl    %ebx
    7fb40dba54e6:	44 89 9d 30 fd ff ff 	mov    %r11d,-0x2d0(%rbp)
    7fb40dba54ed:	44 8b 9d 38 fd ff ff 	mov    -0x2c8(%rbp),%r11d
    7fb40dba54f4:	41 0b db             	or     %r11d,%ebx
    7fb40dba54f7:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba54fb:	41 0b db             	or     %r11d,%ebx
    7fb40dba54fe:	44 8b 9d 38 fd ff ff 	mov    -0x2c8(%rbp),%r11d
    7fb40dba5505:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba5509:	41 0b db             	or     %r11d,%ebx
    7fb40dba550c:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba550f:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba5512:	44 8b 9d 48 fd ff ff 	mov    -0x2b8(%rbp),%r11d
    7fb40dba5519:	41 33 db             	xor    %r11d,%ebx
    7fb40dba551c:	33 fb                	xor    %ebx,%edi
    7fb40dba551e:	41 33 fa             	xor    %r10d,%edi
    7fb40dba5521:	8b d8                	mov    %eax,%ebx
    7fb40dba5523:	33 da                	xor    %edx,%ebx
    7fb40dba5525:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba5528:	41 8b da             	mov    %r10d,%ebx
    7fb40dba552b:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba552e:	d1 e3                	shl    %ebx
    7fb40dba5530:	45 8b da             	mov    %r10d,%r11d
    7fb40dba5533:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba5537:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba553b:	44 89 9d 28 fd ff ff 	mov    %r11d,-0x2d8(%rbp)
    7fb40dba5542:	41 d1 e3             	shl    %r11d
    7fb40dba5545:	89 b5 20 fd ff ff    	mov    %esi,-0x2e0(%rbp)
    7fb40dba554b:	8b b5 28 fd ff ff    	mov    -0x2d8(%rbp),%esi
    7fb40dba5551:	44 0b de             	or     %esi,%r11d
    7fb40dba5554:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba5557:	44 0b de             	or     %esi,%r11d
    7fb40dba555a:	8b b5 28 fd ff ff    	mov    -0x2d8(%rbp),%esi
    7fb40dba5560:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba5563:	44 0b de             	or     %esi,%r11d
    7fb40dba5566:	41 33 db             	xor    %r11d,%ebx
    7fb40dba5569:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba556c:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba556f:	33 c8                	xor    %eax,%ecx
    7fb40dba5571:	33 d1                	xor    %ecx,%edx
    7fb40dba5573:	33 95 48 fd ff ff    	xor    -0x2b8(%rbp),%edx
    7fb40dba5579:	33 da                	xor    %edx,%ebx
    7fb40dba557b:	8b 85 c0 fd ff ff    	mov    -0x240(%rbp),%eax
    7fb40dba5581:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba5584:	8b 8d d0 fd ff ff    	mov    -0x230(%rbp),%ecx
    7fb40dba558a:	0b c1                	or     %ecx,%eax
    7fb40dba558c:	8b 8d b0 fd ff ff    	mov    -0x250(%rbp),%ecx
    7fb40dba5592:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba5595:	0b c1                	or     %ecx,%eax
    7fb40dba5597:	8b 8d a0 fd ff ff    	mov    -0x260(%rbp),%ecx
    7fb40dba559d:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba55a0:	0b c1                	or     %ecx,%eax
    7fb40dba55a2:	8b 8d 90 fd ff ff    	mov    -0x270(%rbp),%ecx
    7fb40dba55a8:	8b c9                	mov    %ecx,%ecx
    7fb40dba55aa:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba55ae:	8b c0                	mov    %eax,%eax
    7fb40dba55b0:	48 0b c8             	or     %rax,%rcx
    7fb40dba55b3:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
    7fb40dba55b9:	8b c0                	mov    %eax,%eax
    7fb40dba55bb:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba55bf:	48 0b c8             	or     %rax,%rcx
    7fb40dba55c2:	8b 85 70 fd ff ff    	mov    -0x290(%rbp),%eax
    7fb40dba55c8:	8b c0                	mov    %eax,%eax
    7fb40dba55ca:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba55ce:	48 0b c8             	or     %rax,%rcx
    7fb40dba55d1:	8b 85 60 fd ff ff    	mov    -0x2a0(%rbp),%eax
    7fb40dba55d7:	8b c0                	mov    %eax,%eax
    7fb40dba55d9:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba55dd:	48 0b c8             	or     %rax,%rcx
    7fb40dba55e0:	49 89 8f 80 02 00 00 	mov    %rcx,0x280(%r15)
    7fb40dba55e7:	8b 85 40 fd ff ff    	mov    -0x2c0(%rbp),%eax
    7fb40dba55ed:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba55f0:	8b 8d 50 fd ff ff    	mov    -0x2b0(%rbp),%ecx
    7fb40dba55f6:	0b c1                	or     %ecx,%eax
    7fb40dba55f8:	8b 8d 30 fd ff ff    	mov    -0x2d0(%rbp),%ecx
    7fb40dba55fe:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba5601:	0b c1                	or     %ecx,%eax
    7fb40dba5603:	8b 8d 20 fd ff ff    	mov    -0x2e0(%rbp),%ecx
    7fb40dba5609:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba560c:	0b c1                	or     %ecx,%eax
    7fb40dba560e:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba5611:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba5615:	8b c0                	mov    %eax,%eax
    7fb40dba5617:	4c 0b c0             	or     %rax,%r8
    7fb40dba561a:	8b ff                	mov    %edi,%edi
    7fb40dba561c:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba5620:	4c 0b c7             	or     %rdi,%r8
    7fb40dba5623:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba5626:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba562a:	4d 0b c1             	or     %r9,%r8
    7fb40dba562d:	8b db                	mov    %ebx,%ebx
    7fb40dba562f:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba5633:	4c 0b c3             	or     %rbx,%r8
    7fb40dba5636:	4d 89 87 88 02 00 00 	mov    %r8,0x288(%r15)
    7fb40dba563d:	8b 85 f0 fd ff ff    	mov    -0x210(%rbp),%eax
    7fb40dba5643:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba5648:	8b c0                	mov    %eax,%eax
    7fb40dba564a:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba564f:	8b 8d f0 fd ff ff    	mov    -0x210(%rbp),%ecx
    7fb40dba5655:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba5658:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba565e:	8b c9                	mov    %ecx,%ecx
    7fb40dba5660:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba5665:	8b 95 f0 fd ff ff    	mov    -0x210(%rbp),%edx
    7fb40dba566b:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba566e:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba5674:	8b d2                	mov    %edx,%edx
    7fb40dba5676:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba567b:	8b 9d f0 fd ff ff    	mov    -0x210(%rbp),%ebx
    7fb40dba5681:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba5684:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba568a:	8b db                	mov    %ebx,%ebx
    7fb40dba568c:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba5691:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba5694:	0b da                	or     %edx,%ebx
    7fb40dba5696:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba5699:	0b d9                	or     %ecx,%ebx
    7fb40dba569b:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba569e:	0b d8                	or     %eax,%ebx
    7fb40dba56a0:	83 f3 04             	xor    $0x4,%ebx
    7fb40dba56a3:	8b 85 00 fe ff ff    	mov    -0x200(%rbp),%eax
    7fb40dba56a9:	33 d8                	xor    %eax,%ebx
    7fb40dba56ab:	8b 85 10 fe ff ff    	mov    -0x1f0(%rbp),%eax
    7fb40dba56b1:	33 c3                	xor    %ebx,%eax
    7fb40dba56b3:	8b 8d e0 fd ff ff    	mov    -0x220(%rbp),%ecx
    7fb40dba56b9:	33 c8                	xor    %eax,%ecx
    7fb40dba56bb:	8b 95 f0 fd ff ff    	mov    -0x210(%rbp),%edx
    7fb40dba56c1:	33 d1                	xor    %ecx,%edx
    7fb40dba56c3:	8b f0                	mov    %eax,%esi
    7fb40dba56c5:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba56c9:	8b fb                	mov    %ebx,%edi
    7fb40dba56cb:	48 0b f7             	or     %rdi,%rsi
    7fb40dba56ce:	49 89 b7 e0 01 00 00 	mov    %rsi,0x1e0(%r15)
    7fb40dba56d5:	8b f2                	mov    %edx,%esi
    7fb40dba56d7:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba56db:	8b f9                	mov    %ecx,%edi
    7fb40dba56dd:	48 0b f7             	or     %rdi,%rsi
    7fb40dba56e0:	49 89 b7 e8 01 00 00 	mov    %rsi,0x1e8(%r15)
    7fb40dba56e7:	49 8b b7 80 02 00 00 	mov    0x280(%r15),%rsi
    7fb40dba56ee:	49 8b bf e0 01 00 00 	mov    0x1e0(%r15),%rdi
    7fb40dba56f5:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba56f8:	49 89 b7 30 03 00 00 	mov    %rsi,0x330(%r15)
    7fb40dba56ff:	49 8b b7 88 02 00 00 	mov    0x288(%r15),%rsi
    7fb40dba5706:	49 8b bf e8 01 00 00 	mov    0x1e8(%r15),%rdi
    7fb40dba570d:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba5710:	49 89 b7 38 03 00 00 	mov    %rsi,0x338(%r15)
    7fb40dba5717:	49 0f b6 b7 30 01 00 	movzbq 0x130(%r15),%rsi
    7fb40dba571e:	00 
    7fb40dba571f:	8b f6                	mov    %esi,%esi
    7fb40dba5721:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba5726:	8b fe                	mov    %esi,%edi
    7fb40dba5728:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba572b:	d1 e7                	shl    %edi
    7fb40dba572d:	44 8b c6             	mov    %esi,%r8d
    7fb40dba5730:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba5734:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba5738:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba573b:	41 d1 e1             	shl    %r9d
    7fb40dba573e:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5741:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba5744:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba5748:	45 0b ca             	or     %r10d,%r9d
    7fb40dba574b:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba574f:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5752:	41 33 f9             	xor    %r9d,%edi
    7fb40dba5755:	4d 0f b6 87 35 01 00 	movzbq 0x135(%r15),%r8
    7fb40dba575c:	00 
    7fb40dba575d:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba5760:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba5765:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5768:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba576c:	41 d1 e1             	shl    %r9d
    7fb40dba576f:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba5772:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba5776:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba577a:	45 8b da             	mov    %r10d,%r11d
    7fb40dba577d:	41 d1 e3             	shl    %r11d
    7fb40dba5780:	45 0b da             	or     %r10d,%r11d
    7fb40dba5783:	44 89 95 18 fd ff ff 	mov    %r10d,-0x2e8(%rbp)
    7fb40dba578a:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba578e:	45 0b da             	or     %r10d,%r11d
    7fb40dba5791:	44 8b 95 18 fd ff ff 	mov    -0x2e8(%rbp),%r10d
    7fb40dba5798:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba579c:	45 0b da             	or     %r10d,%r11d
    7fb40dba579f:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba57a2:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba57a5:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba57a8:	44 33 d7             	xor    %edi,%r10d
    7fb40dba57ab:	4d 0f b6 9f 3a 01 00 	movzbq 0x13a(%r15),%r11
    7fb40dba57b2:	00 
    7fb40dba57b3:	45 8b db             	mov    %r11d,%r11d
    7fb40dba57b6:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba57bb:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba57be:	89 85 10 fd ff ff    	mov    %eax,-0x2f0(%rbp)
    7fb40dba57c4:	49 0f b6 87 3f 01 00 	movzbq 0x13f(%r15),%rax
    7fb40dba57cb:	00 
    7fb40dba57cc:	8b c0                	mov    %eax,%eax
    7fb40dba57ce:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba57d3:	44 33 d0             	xor    %eax,%r10d
    7fb40dba57d6:	44 33 ce             	xor    %esi,%r9d
    7fb40dba57d9:	44 89 9d 08 fd ff ff 	mov    %r11d,-0x2f8(%rbp)
    7fb40dba57e0:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba57e4:	41 d1 e3             	shl    %r11d
    7fb40dba57e7:	89 9d 00 fd ff ff    	mov    %ebx,-0x300(%rbp)
    7fb40dba57ed:	8b 9d 08 fd ff ff    	mov    -0x2f8(%rbp),%ebx
    7fb40dba57f3:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba57f6:	83 e3 01             	and    $0x1,%ebx
    7fb40dba57f9:	89 9d f8 fc ff ff    	mov    %ebx,-0x308(%rbp)
    7fb40dba57ff:	d1 e3                	shl    %ebx
    7fb40dba5801:	89 95 f0 fc ff ff    	mov    %edx,-0x310(%rbp)
    7fb40dba5807:	8b 95 f8 fc ff ff    	mov    -0x308(%rbp),%edx
    7fb40dba580d:	0b da                	or     %edx,%ebx
    7fb40dba580f:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba5812:	0b da                	or     %edx,%ebx
    7fb40dba5814:	8b 95 f8 fc ff ff    	mov    -0x308(%rbp),%edx
    7fb40dba581a:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba581d:	0b da                	or     %edx,%ebx
    7fb40dba581f:	44 33 db             	xor    %ebx,%r11d
    7fb40dba5822:	41 8b d3             	mov    %r11d,%edx
    7fb40dba5825:	8b 9d 08 fd ff ff    	mov    -0x2f8(%rbp),%ebx
    7fb40dba582b:	33 d3                	xor    %ebx,%edx
    7fb40dba582d:	44 33 ca             	xor    %edx,%r9d
    7fb40dba5830:	44 33 c8             	xor    %eax,%r9d
    7fb40dba5833:	8b d6                	mov    %esi,%edx
    7fb40dba5835:	41 33 d0             	xor    %r8d,%edx
    7fb40dba5838:	44 33 da             	xor    %edx,%r11d
    7fb40dba583b:	8b d0                	mov    %eax,%edx
    7fb40dba583d:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba5840:	d1 e2                	shl    %edx
    7fb40dba5842:	8b d8                	mov    %eax,%ebx
    7fb40dba5844:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba5847:	83 e3 01             	and    $0x1,%ebx
    7fb40dba584a:	89 9d e8 fc ff ff    	mov    %ebx,-0x318(%rbp)
    7fb40dba5850:	d1 e3                	shl    %ebx
    7fb40dba5852:	89 8d e0 fc ff ff    	mov    %ecx,-0x320(%rbp)
    7fb40dba5858:	8b 8d e8 fc ff ff    	mov    -0x318(%rbp),%ecx
    7fb40dba585e:	0b d9                	or     %ecx,%ebx
    7fb40dba5860:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba5863:	0b d9                	or     %ecx,%ebx
    7fb40dba5865:	8b 8d e8 fc ff ff    	mov    -0x318(%rbp),%ecx
    7fb40dba586b:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba586e:	0b d9                	or     %ecx,%ebx
    7fb40dba5870:	33 d3                	xor    %ebx,%edx
    7fb40dba5872:	33 c2                	xor    %edx,%eax
    7fb40dba5874:	44 33 d8             	xor    %eax,%r11d
    7fb40dba5877:	33 fe                	xor    %esi,%edi
    7fb40dba5879:	44 33 c7             	xor    %edi,%r8d
    7fb40dba587c:	44 33 85 08 fd ff ff 	xor    -0x2f8(%rbp),%r8d
    7fb40dba5883:	41 33 d0             	xor    %r8d,%edx
    7fb40dba5886:	49 0f b6 87 34 01 00 	movzbq 0x134(%r15),%rax
    7fb40dba588d:	00 
    7fb40dba588e:	8b c0                	mov    %eax,%eax
    7fb40dba5890:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5895:	8b c8                	mov    %eax,%ecx
    7fb40dba5897:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba589a:	d1 e1                	shl    %ecx
    7fb40dba589c:	8b d8                	mov    %eax,%ebx
    7fb40dba589e:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba58a1:	83 e3 01             	and    $0x1,%ebx
    7fb40dba58a4:	8b f3                	mov    %ebx,%esi
    7fb40dba58a6:	d1 e6                	shl    %esi
    7fb40dba58a8:	0b f3                	or     %ebx,%esi
    7fb40dba58aa:	8b fb                	mov    %ebx,%edi
    7fb40dba58ac:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba58af:	0b f7                	or     %edi,%esi
    7fb40dba58b1:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba58b4:	0b f3                	or     %ebx,%esi
    7fb40dba58b6:	33 ce                	xor    %esi,%ecx
    7fb40dba58b8:	49 0f b6 9f 39 01 00 	movzbq 0x139(%r15),%rbx
    7fb40dba58bf:	00 
    7fb40dba58c0:	8b db                	mov    %ebx,%ebx
    7fb40dba58c2:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba58c7:	8b f3                	mov    %ebx,%esi
    7fb40dba58c9:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba58cc:	d1 e6                	shl    %esi
    7fb40dba58ce:	8b fb                	mov    %ebx,%edi
    7fb40dba58d0:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba58d3:	83 e7 01             	and    $0x1,%edi
    7fb40dba58d6:	44 8b c7             	mov    %edi,%r8d
    7fb40dba58d9:	41 d1 e0             	shl    %r8d
    7fb40dba58dc:	44 0b c7             	or     %edi,%r8d
    7fb40dba58df:	89 bd d8 fc ff ff    	mov    %edi,-0x328(%rbp)
    7fb40dba58e5:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba58e8:	44 0b c7             	or     %edi,%r8d
    7fb40dba58eb:	8b bd d8 fc ff ff    	mov    -0x328(%rbp),%edi
    7fb40dba58f1:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba58f4:	44 0b c7             	or     %edi,%r8d
    7fb40dba58f7:	41 33 f0             	xor    %r8d,%esi
    7fb40dba58fa:	8b fe                	mov    %esi,%edi
    7fb40dba58fc:	33 fb                	xor    %ebx,%edi
    7fb40dba58fe:	33 f9                	xor    %ecx,%edi
    7fb40dba5900:	4d 0f b6 87 3e 01 00 	movzbq 0x13e(%r15),%r8
    7fb40dba5907:	00 
    7fb40dba5908:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba590b:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba5910:	41 33 f8             	xor    %r8d,%edi
    7fb40dba5913:	44 89 95 d0 fc ff ff 	mov    %r10d,-0x330(%rbp)
    7fb40dba591a:	4d 0f b6 97 33 01 00 	movzbq 0x133(%r15),%r10
    7fb40dba5921:	00 
    7fb40dba5922:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba5925:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba592a:	41 33 fa             	xor    %r10d,%edi
    7fb40dba592d:	33 f0                	xor    %eax,%esi
    7fb40dba592f:	44 89 85 c8 fc ff ff 	mov    %r8d,-0x338(%rbp)
    7fb40dba5936:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba593a:	41 d1 e0             	shl    %r8d
    7fb40dba593d:	44 89 8d c0 fc ff ff 	mov    %r9d,-0x340(%rbp)
    7fb40dba5944:	44 8b 8d c8 fc ff ff 	mov    -0x338(%rbp),%r9d
    7fb40dba594b:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba594f:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba5953:	44 89 8d b8 fc ff ff 	mov    %r9d,-0x348(%rbp)
    7fb40dba595a:	41 d1 e1             	shl    %r9d
    7fb40dba595d:	44 89 9d b0 fc ff ff 	mov    %r11d,-0x350(%rbp)
    7fb40dba5964:	44 8b 9d b8 fc ff ff 	mov    -0x348(%rbp),%r11d
    7fb40dba596b:	45 0b cb             	or     %r11d,%r9d
    7fb40dba596e:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba5972:	45 0b cb             	or     %r11d,%r9d
    7fb40dba5975:	44 8b 9d b8 fc ff ff 	mov    -0x348(%rbp),%r11d
    7fb40dba597c:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba5980:	45 0b cb             	or     %r11d,%r9d
    7fb40dba5983:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba5986:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5989:	44 8b 9d c8 fc ff ff 	mov    -0x338(%rbp),%r11d
    7fb40dba5990:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba5993:	41 33 f1             	xor    %r9d,%esi
    7fb40dba5996:	41 33 f2             	xor    %r10d,%esi
    7fb40dba5999:	44 8b c8             	mov    %eax,%r9d
    7fb40dba599c:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba599f:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba59a2:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba59a5:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba59a9:	41 d1 e1             	shl    %r9d
    7fb40dba59ac:	45 8b da             	mov    %r10d,%r11d
    7fb40dba59af:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba59b3:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba59b7:	44 89 9d a8 fc ff ff 	mov    %r11d,-0x358(%rbp)
    7fb40dba59be:	41 d1 e3             	shl    %r11d
    7fb40dba59c1:	89 95 a0 fc ff ff    	mov    %edx,-0x360(%rbp)
    7fb40dba59c7:	8b 95 a8 fc ff ff    	mov    -0x358(%rbp),%edx
    7fb40dba59cd:	44 0b da             	or     %edx,%r11d
    7fb40dba59d0:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba59d3:	44 0b da             	or     %edx,%r11d
    7fb40dba59d6:	8b 95 a8 fc ff ff    	mov    -0x358(%rbp),%edx
    7fb40dba59dc:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba59df:	44 0b da             	or     %edx,%r11d
    7fb40dba59e2:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba59e5:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba59e8:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba59eb:	33 c8                	xor    %eax,%ecx
    7fb40dba59ed:	33 d9                	xor    %ecx,%ebx
    7fb40dba59ef:	33 9d c8 fc ff ff    	xor    -0x338(%rbp),%ebx
    7fb40dba59f5:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba59f8:	49 0f b6 87 38 01 00 	movzbq 0x138(%r15),%rax
    7fb40dba59ff:	00 
    7fb40dba5a00:	8b c0                	mov    %eax,%eax
    7fb40dba5a02:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5a07:	8b c8                	mov    %eax,%ecx
    7fb40dba5a09:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba5a0c:	d1 e1                	shl    %ecx
    7fb40dba5a0e:	8b d0                	mov    %eax,%edx
    7fb40dba5a10:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba5a13:	83 e2 01             	and    $0x1,%edx
    7fb40dba5a16:	8b da                	mov    %edx,%ebx
    7fb40dba5a18:	d1 e3                	shl    %ebx
    7fb40dba5a1a:	0b da                	or     %edx,%ebx
    7fb40dba5a1c:	44 8b d2             	mov    %edx,%r10d
    7fb40dba5a1f:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba5a23:	41 0b da             	or     %r10d,%ebx
    7fb40dba5a26:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba5a29:	0b da                	or     %edx,%ebx
    7fb40dba5a2b:	33 cb                	xor    %ebx,%ecx
    7fb40dba5a2d:	49 0f b6 97 3d 01 00 	movzbq 0x13d(%r15),%rdx
    7fb40dba5a34:	00 
    7fb40dba5a35:	8b d2                	mov    %edx,%edx
    7fb40dba5a37:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba5a3c:	8b da                	mov    %edx,%ebx
    7fb40dba5a3e:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba5a41:	d1 e3                	shl    %ebx
    7fb40dba5a43:	44 8b d2             	mov    %edx,%r10d
    7fb40dba5a46:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba5a4a:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba5a4e:	45 8b da             	mov    %r10d,%r11d
    7fb40dba5a51:	41 d1 e3             	shl    %r11d
    7fb40dba5a54:	45 0b da             	or     %r10d,%r11d
    7fb40dba5a57:	44 89 95 98 fc ff ff 	mov    %r10d,-0x368(%rbp)
    7fb40dba5a5e:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba5a62:	45 0b da             	or     %r10d,%r11d
    7fb40dba5a65:	44 8b 95 98 fc ff ff 	mov    -0x368(%rbp),%r10d
    7fb40dba5a6c:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba5a70:	45 0b da             	or     %r10d,%r11d
    7fb40dba5a73:	41 33 db             	xor    %r11d,%ebx
    7fb40dba5a76:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba5a79:	44 33 d2             	xor    %edx,%r10d
    7fb40dba5a7c:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba5a7f:	4d 0f b6 9f 32 01 00 	movzbq 0x132(%r15),%r11
    7fb40dba5a86:	00 
    7fb40dba5a87:	45 8b db             	mov    %r11d,%r11d
    7fb40dba5a8a:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba5a8f:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba5a92:	89 bd 90 fc ff ff    	mov    %edi,-0x370(%rbp)
    7fb40dba5a98:	49 0f b6 bf 37 01 00 	movzbq 0x137(%r15),%rdi
    7fb40dba5a9f:	00 
    7fb40dba5aa0:	8b ff                	mov    %edi,%edi
    7fb40dba5aa2:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba5aa7:	44 33 d7             	xor    %edi,%r10d
    7fb40dba5aaa:	33 d8                	xor    %eax,%ebx
    7fb40dba5aac:	44 89 9d 88 fc ff ff 	mov    %r11d,-0x378(%rbp)
    7fb40dba5ab3:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba5ab7:	41 d1 e3             	shl    %r11d
    7fb40dba5aba:	89 b5 80 fc ff ff    	mov    %esi,-0x380(%rbp)
    7fb40dba5ac0:	8b b5 88 fc ff ff    	mov    -0x378(%rbp),%esi
    7fb40dba5ac6:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba5ac9:	83 e6 01             	and    $0x1,%esi
    7fb40dba5acc:	89 b5 78 fc ff ff    	mov    %esi,-0x388(%rbp)
    7fb40dba5ad2:	d1 e6                	shl    %esi
    7fb40dba5ad4:	44 89 85 70 fc ff ff 	mov    %r8d,-0x390(%rbp)
    7fb40dba5adb:	44 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%r8d
    7fb40dba5ae2:	41 0b f0             	or     %r8d,%esi
    7fb40dba5ae5:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba5ae9:	41 0b f0             	or     %r8d,%esi
    7fb40dba5aec:	44 8b 85 78 fc ff ff 	mov    -0x388(%rbp),%r8d
    7fb40dba5af3:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba5af7:	41 0b f0             	or     %r8d,%esi
    7fb40dba5afa:	44 33 de             	xor    %esi,%r11d
    7fb40dba5afd:	41 8b f3             	mov    %r11d,%esi
    7fb40dba5b00:	44 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%r8d
    7fb40dba5b07:	41 33 f0             	xor    %r8d,%esi
    7fb40dba5b0a:	33 de                	xor    %esi,%ebx
    7fb40dba5b0c:	33 df                	xor    %edi,%ebx
    7fb40dba5b0e:	8b f0                	mov    %eax,%esi
    7fb40dba5b10:	33 f2                	xor    %edx,%esi
    7fb40dba5b12:	44 33 de             	xor    %esi,%r11d
    7fb40dba5b15:	8b f7                	mov    %edi,%esi
    7fb40dba5b17:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba5b1a:	d1 e6                	shl    %esi
    7fb40dba5b1c:	44 8b c7             	mov    %edi,%r8d
    7fb40dba5b1f:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba5b23:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba5b27:	44 89 85 68 fc ff ff 	mov    %r8d,-0x398(%rbp)
    7fb40dba5b2e:	41 d1 e0             	shl    %r8d
    7fb40dba5b31:	44 89 8d 60 fc ff ff 	mov    %r9d,-0x3a0(%rbp)
    7fb40dba5b38:	44 8b 8d 68 fc ff ff 	mov    -0x398(%rbp),%r9d
    7fb40dba5b3f:	45 0b c1             	or     %r9d,%r8d
    7fb40dba5b42:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba5b46:	45 0b c1             	or     %r9d,%r8d
    7fb40dba5b49:	44 8b 8d 68 fc ff ff 	mov    -0x398(%rbp),%r9d
    7fb40dba5b50:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba5b54:	45 0b c1             	or     %r9d,%r8d
    7fb40dba5b57:	41 33 f0             	xor    %r8d,%esi
    7fb40dba5b5a:	33 fe                	xor    %esi,%edi
    7fb40dba5b5c:	44 33 df             	xor    %edi,%r11d
    7fb40dba5b5f:	33 c8                	xor    %eax,%ecx
    7fb40dba5b61:	33 d1                	xor    %ecx,%edx
    7fb40dba5b63:	33 95 88 fc ff ff    	xor    -0x378(%rbp),%edx
    7fb40dba5b69:	33 f2                	xor    %edx,%esi
    7fb40dba5b6b:	49 0f b6 87 3c 01 00 	movzbq 0x13c(%r15),%rax
    7fb40dba5b72:	00 
    7fb40dba5b73:	8b c0                	mov    %eax,%eax
    7fb40dba5b75:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5b7a:	8b c8                	mov    %eax,%ecx
    7fb40dba5b7c:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba5b7f:	d1 e1                	shl    %ecx
    7fb40dba5b81:	8b d0                	mov    %eax,%edx
    7fb40dba5b83:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba5b86:	83 e2 01             	and    $0x1,%edx
    7fb40dba5b89:	8b fa                	mov    %edx,%edi
    7fb40dba5b8b:	d1 e7                	shl    %edi
    7fb40dba5b8d:	0b fa                	or     %edx,%edi
    7fb40dba5b8f:	44 8b c2             	mov    %edx,%r8d
    7fb40dba5b92:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba5b96:	41 0b f8             	or     %r8d,%edi
    7fb40dba5b99:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba5b9c:	0b fa                	or     %edx,%edi
    7fb40dba5b9e:	33 cf                	xor    %edi,%ecx
    7fb40dba5ba0:	49 0f b6 97 31 01 00 	movzbq 0x131(%r15),%rdx
    7fb40dba5ba7:	00 
    7fb40dba5ba8:	8b d2                	mov    %edx,%edx
    7fb40dba5baa:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba5baf:	8b fa                	mov    %edx,%edi
    7fb40dba5bb1:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba5bb4:	d1 e7                	shl    %edi
    7fb40dba5bb6:	44 8b c2             	mov    %edx,%r8d
    7fb40dba5bb9:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba5bbd:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba5bc1:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5bc4:	41 d1 e1             	shl    %r9d
    7fb40dba5bc7:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5bca:	44 89 85 58 fc ff ff 	mov    %r8d,-0x3a8(%rbp)
    7fb40dba5bd1:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba5bd5:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5bd8:	44 8b 85 58 fc ff ff 	mov    -0x3a8(%rbp),%r8d
    7fb40dba5bdf:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba5be3:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5be6:	41 33 f9             	xor    %r9d,%edi
    7fb40dba5be9:	44 8b c7             	mov    %edi,%r8d
    7fb40dba5bec:	44 33 c2             	xor    %edx,%r8d
    7fb40dba5bef:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba5bf2:	4d 0f b6 8f 36 01 00 	movzbq 0x136(%r15),%r9
    7fb40dba5bf9:	00 
    7fb40dba5bfa:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba5bfd:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba5c02:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba5c05:	44 89 95 50 fc ff ff 	mov    %r10d,-0x3b0(%rbp)
    7fb40dba5c0c:	4d 0f b6 97 3b 01 00 	movzbq 0x13b(%r15),%r10
    7fb40dba5c13:	00 
    7fb40dba5c14:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba5c17:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba5c1c:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba5c1f:	33 f8                	xor    %eax,%edi
    7fb40dba5c21:	44 89 8d 48 fc ff ff 	mov    %r9d,-0x3b8(%rbp)
    7fb40dba5c28:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba5c2c:	41 d1 e1             	shl    %r9d
    7fb40dba5c2f:	89 9d 40 fc ff ff    	mov    %ebx,-0x3c0(%rbp)
    7fb40dba5c35:	8b 9d 48 fc ff ff    	mov    -0x3b8(%rbp),%ebx
    7fb40dba5c3b:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba5c3e:	83 e3 01             	and    $0x1,%ebx
    7fb40dba5c41:	89 9d 38 fc ff ff    	mov    %ebx,-0x3c8(%rbp)
    7fb40dba5c47:	d1 e3                	shl    %ebx
    7fb40dba5c49:	44 89 9d 30 fc ff ff 	mov    %r11d,-0x3d0(%rbp)
    7fb40dba5c50:	44 8b 9d 38 fc ff ff 	mov    -0x3c8(%rbp),%r11d
    7fb40dba5c57:	41 0b db             	or     %r11d,%ebx
    7fb40dba5c5a:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba5c5e:	41 0b db             	or     %r11d,%ebx
    7fb40dba5c61:	44 8b 9d 38 fc ff ff 	mov    -0x3c8(%rbp),%r11d
    7fb40dba5c68:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba5c6c:	41 0b db             	or     %r11d,%ebx
    7fb40dba5c6f:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba5c72:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba5c75:	44 8b 9d 48 fc ff ff 	mov    -0x3b8(%rbp),%r11d
    7fb40dba5c7c:	41 33 db             	xor    %r11d,%ebx
    7fb40dba5c7f:	33 fb                	xor    %ebx,%edi
    7fb40dba5c81:	41 33 fa             	xor    %r10d,%edi
    7fb40dba5c84:	8b d8                	mov    %eax,%ebx
    7fb40dba5c86:	33 da                	xor    %edx,%ebx
    7fb40dba5c88:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba5c8b:	41 8b da             	mov    %r10d,%ebx
    7fb40dba5c8e:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba5c91:	d1 e3                	shl    %ebx
    7fb40dba5c93:	45 8b da             	mov    %r10d,%r11d
    7fb40dba5c96:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba5c9a:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba5c9e:	44 89 9d 28 fc ff ff 	mov    %r11d,-0x3d8(%rbp)
    7fb40dba5ca5:	41 d1 e3             	shl    %r11d
    7fb40dba5ca8:	89 b5 20 fc ff ff    	mov    %esi,-0x3e0(%rbp)
    7fb40dba5cae:	8b b5 28 fc ff ff    	mov    -0x3d8(%rbp),%esi
    7fb40dba5cb4:	44 0b de             	or     %esi,%r11d
    7fb40dba5cb7:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba5cba:	44 0b de             	or     %esi,%r11d
    7fb40dba5cbd:	8b b5 28 fc ff ff    	mov    -0x3d8(%rbp),%esi
    7fb40dba5cc3:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba5cc6:	44 0b de             	or     %esi,%r11d
    7fb40dba5cc9:	41 33 db             	xor    %r11d,%ebx
    7fb40dba5ccc:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba5ccf:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba5cd2:	33 c8                	xor    %eax,%ecx
    7fb40dba5cd4:	33 d1                	xor    %ecx,%edx
    7fb40dba5cd6:	33 95 48 fc ff ff    	xor    -0x3b8(%rbp),%edx
    7fb40dba5cdc:	33 da                	xor    %edx,%ebx
    7fb40dba5cde:	8b 85 c0 fc ff ff    	mov    -0x340(%rbp),%eax
    7fb40dba5ce4:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba5ce7:	8b 8d d0 fc ff ff    	mov    -0x330(%rbp),%ecx
    7fb40dba5ced:	0b c1                	or     %ecx,%eax
    7fb40dba5cef:	8b 8d b0 fc ff ff    	mov    -0x350(%rbp),%ecx
    7fb40dba5cf5:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba5cf8:	0b c1                	or     %ecx,%eax
    7fb40dba5cfa:	8b 8d a0 fc ff ff    	mov    -0x360(%rbp),%ecx
    7fb40dba5d00:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba5d03:	0b c1                	or     %ecx,%eax
    7fb40dba5d05:	8b 8d 90 fc ff ff    	mov    -0x370(%rbp),%ecx
    7fb40dba5d0b:	8b c9                	mov    %ecx,%ecx
    7fb40dba5d0d:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba5d11:	8b c0                	mov    %eax,%eax
    7fb40dba5d13:	48 0b c8             	or     %rax,%rcx
    7fb40dba5d16:	8b 85 80 fc ff ff    	mov    -0x380(%rbp),%eax
    7fb40dba5d1c:	8b c0                	mov    %eax,%eax
    7fb40dba5d1e:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba5d22:	48 0b c8             	or     %rax,%rcx
    7fb40dba5d25:	8b 85 70 fc ff ff    	mov    -0x390(%rbp),%eax
    7fb40dba5d2b:	8b c0                	mov    %eax,%eax
    7fb40dba5d2d:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba5d31:	48 0b c8             	or     %rax,%rcx
    7fb40dba5d34:	8b 85 60 fc ff ff    	mov    -0x3a0(%rbp),%eax
    7fb40dba5d3a:	8b c0                	mov    %eax,%eax
    7fb40dba5d3c:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba5d40:	48 0b c8             	or     %rax,%rcx
    7fb40dba5d43:	49 89 8f 90 02 00 00 	mov    %rcx,0x290(%r15)
    7fb40dba5d4a:	8b 85 40 fc ff ff    	mov    -0x3c0(%rbp),%eax
    7fb40dba5d50:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba5d53:	8b 8d 50 fc ff ff    	mov    -0x3b0(%rbp),%ecx
    7fb40dba5d59:	0b c1                	or     %ecx,%eax
    7fb40dba5d5b:	8b 8d 30 fc ff ff    	mov    -0x3d0(%rbp),%ecx
    7fb40dba5d61:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba5d64:	0b c1                	or     %ecx,%eax
    7fb40dba5d66:	8b 8d 20 fc ff ff    	mov    -0x3e0(%rbp),%ecx
    7fb40dba5d6c:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba5d6f:	0b c1                	or     %ecx,%eax
    7fb40dba5d71:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba5d74:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba5d78:	8b c0                	mov    %eax,%eax
    7fb40dba5d7a:	4c 0b c0             	or     %rax,%r8
    7fb40dba5d7d:	8b ff                	mov    %edi,%edi
    7fb40dba5d7f:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba5d83:	4c 0b c7             	or     %rdi,%r8
    7fb40dba5d86:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba5d89:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba5d8d:	4d 0b c1             	or     %r9,%r8
    7fb40dba5d90:	8b db                	mov    %ebx,%ebx
    7fb40dba5d92:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba5d96:	4c 0b c3             	or     %rbx,%r8
    7fb40dba5d99:	4d 89 87 98 02 00 00 	mov    %r8,0x298(%r15)
    7fb40dba5da0:	8b 85 f0 fc ff ff    	mov    -0x310(%rbp),%eax
    7fb40dba5da6:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba5dab:	8b c0                	mov    %eax,%eax
    7fb40dba5dad:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5db2:	8b 8d f0 fc ff ff    	mov    -0x310(%rbp),%ecx
    7fb40dba5db8:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba5dbb:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba5dc1:	8b c9                	mov    %ecx,%ecx
    7fb40dba5dc3:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba5dc8:	8b 95 f0 fc ff ff    	mov    -0x310(%rbp),%edx
    7fb40dba5dce:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba5dd1:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba5dd7:	8b d2                	mov    %edx,%edx
    7fb40dba5dd9:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba5dde:	8b 9d f0 fc ff ff    	mov    -0x310(%rbp),%ebx
    7fb40dba5de4:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba5de7:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba5ded:	8b db                	mov    %ebx,%ebx
    7fb40dba5def:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba5df4:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba5df7:	0b da                	or     %edx,%ebx
    7fb40dba5df9:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba5dfc:	0b d9                	or     %ecx,%ebx
    7fb40dba5dfe:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba5e01:	0b d8                	or     %eax,%ebx
    7fb40dba5e03:	83 f3 08             	xor    $0x8,%ebx
    7fb40dba5e06:	8b 85 00 fd ff ff    	mov    -0x300(%rbp),%eax
    7fb40dba5e0c:	33 d8                	xor    %eax,%ebx
    7fb40dba5e0e:	8b 85 10 fd ff ff    	mov    -0x2f0(%rbp),%eax
    7fb40dba5e14:	33 c3                	xor    %ebx,%eax
    7fb40dba5e16:	8b 8d e0 fc ff ff    	mov    -0x320(%rbp),%ecx
    7fb40dba5e1c:	33 c8                	xor    %eax,%ecx
    7fb40dba5e1e:	8b 95 f0 fc ff ff    	mov    -0x310(%rbp),%edx
    7fb40dba5e24:	33 d1                	xor    %ecx,%edx
    7fb40dba5e26:	8b f0                	mov    %eax,%esi
    7fb40dba5e28:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba5e2c:	8b fb                	mov    %ebx,%edi
    7fb40dba5e2e:	48 0b f7             	or     %rdi,%rsi
    7fb40dba5e31:	49 89 b7 f0 01 00 00 	mov    %rsi,0x1f0(%r15)
    7fb40dba5e38:	8b f2                	mov    %edx,%esi
    7fb40dba5e3a:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba5e3e:	8b f9                	mov    %ecx,%edi
    7fb40dba5e40:	48 0b f7             	or     %rdi,%rsi
    7fb40dba5e43:	49 89 b7 f8 01 00 00 	mov    %rsi,0x1f8(%r15)
    7fb40dba5e4a:	49 8b b7 90 02 00 00 	mov    0x290(%r15),%rsi
    7fb40dba5e51:	49 8b bf f0 01 00 00 	mov    0x1f0(%r15),%rdi
    7fb40dba5e58:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba5e5b:	49 89 b7 40 03 00 00 	mov    %rsi,0x340(%r15)
    7fb40dba5e62:	49 8b b7 98 02 00 00 	mov    0x298(%r15),%rsi
    7fb40dba5e69:	49 8b bf f8 01 00 00 	mov    0x1f8(%r15),%rdi
    7fb40dba5e70:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba5e73:	49 89 b7 48 03 00 00 	mov    %rsi,0x348(%r15)
    7fb40dba5e7a:	49 0f b6 b7 40 01 00 	movzbq 0x140(%r15),%rsi
    7fb40dba5e81:	00 
    7fb40dba5e82:	8b f6                	mov    %esi,%esi
    7fb40dba5e84:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba5e89:	8b fe                	mov    %esi,%edi
    7fb40dba5e8b:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba5e8e:	d1 e7                	shl    %edi
    7fb40dba5e90:	44 8b c6             	mov    %esi,%r8d
    7fb40dba5e93:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba5e97:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba5e9b:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5e9e:	41 d1 e1             	shl    %r9d
    7fb40dba5ea1:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5ea4:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba5ea7:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba5eab:	45 0b ca             	or     %r10d,%r9d
    7fb40dba5eae:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba5eb2:	45 0b c8             	or     %r8d,%r9d
    7fb40dba5eb5:	41 33 f9             	xor    %r9d,%edi
    7fb40dba5eb8:	4d 0f b6 87 45 01 00 	movzbq 0x145(%r15),%r8
    7fb40dba5ebf:	00 
    7fb40dba5ec0:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba5ec3:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba5ec8:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba5ecb:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba5ecf:	41 d1 e1             	shl    %r9d
    7fb40dba5ed2:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba5ed5:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba5ed9:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba5edd:	45 8b da             	mov    %r10d,%r11d
    7fb40dba5ee0:	41 d1 e3             	shl    %r11d
    7fb40dba5ee3:	45 0b da             	or     %r10d,%r11d
    7fb40dba5ee6:	44 89 95 18 fc ff ff 	mov    %r10d,-0x3e8(%rbp)
    7fb40dba5eed:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba5ef1:	45 0b da             	or     %r10d,%r11d
    7fb40dba5ef4:	44 8b 95 18 fc ff ff 	mov    -0x3e8(%rbp),%r10d
    7fb40dba5efb:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba5eff:	45 0b da             	or     %r10d,%r11d
    7fb40dba5f02:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba5f05:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba5f08:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba5f0b:	44 33 d7             	xor    %edi,%r10d
    7fb40dba5f0e:	4d 0f b6 9f 4a 01 00 	movzbq 0x14a(%r15),%r11
    7fb40dba5f15:	00 
    7fb40dba5f16:	45 8b db             	mov    %r11d,%r11d
    7fb40dba5f19:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba5f1e:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba5f21:	89 85 10 fc ff ff    	mov    %eax,-0x3f0(%rbp)
    7fb40dba5f27:	49 0f b6 87 4f 01 00 	movzbq 0x14f(%r15),%rax
    7fb40dba5f2e:	00 
    7fb40dba5f2f:	8b c0                	mov    %eax,%eax
    7fb40dba5f31:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5f36:	44 33 d0             	xor    %eax,%r10d
    7fb40dba5f39:	44 33 ce             	xor    %esi,%r9d
    7fb40dba5f3c:	44 89 9d 08 fc ff ff 	mov    %r11d,-0x3f8(%rbp)
    7fb40dba5f43:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba5f47:	41 d1 e3             	shl    %r11d
    7fb40dba5f4a:	89 9d 00 fc ff ff    	mov    %ebx,-0x400(%rbp)
    7fb40dba5f50:	8b 9d 08 fc ff ff    	mov    -0x3f8(%rbp),%ebx
    7fb40dba5f56:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba5f59:	83 e3 01             	and    $0x1,%ebx
    7fb40dba5f5c:	89 9d f8 fb ff ff    	mov    %ebx,-0x408(%rbp)
    7fb40dba5f62:	d1 e3                	shl    %ebx
    7fb40dba5f64:	89 95 f0 fb ff ff    	mov    %edx,-0x410(%rbp)
    7fb40dba5f6a:	8b 95 f8 fb ff ff    	mov    -0x408(%rbp),%edx
    7fb40dba5f70:	0b da                	or     %edx,%ebx
    7fb40dba5f72:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba5f75:	0b da                	or     %edx,%ebx
    7fb40dba5f77:	8b 95 f8 fb ff ff    	mov    -0x408(%rbp),%edx
    7fb40dba5f7d:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba5f80:	0b da                	or     %edx,%ebx
    7fb40dba5f82:	44 33 db             	xor    %ebx,%r11d
    7fb40dba5f85:	41 8b d3             	mov    %r11d,%edx
    7fb40dba5f88:	8b 9d 08 fc ff ff    	mov    -0x3f8(%rbp),%ebx
    7fb40dba5f8e:	33 d3                	xor    %ebx,%edx
    7fb40dba5f90:	44 33 ca             	xor    %edx,%r9d
    7fb40dba5f93:	44 33 c8             	xor    %eax,%r9d
    7fb40dba5f96:	8b d6                	mov    %esi,%edx
    7fb40dba5f98:	41 33 d0             	xor    %r8d,%edx
    7fb40dba5f9b:	44 33 da             	xor    %edx,%r11d
    7fb40dba5f9e:	8b d0                	mov    %eax,%edx
    7fb40dba5fa0:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba5fa3:	d1 e2                	shl    %edx
    7fb40dba5fa5:	8b d8                	mov    %eax,%ebx
    7fb40dba5fa7:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba5faa:	83 e3 01             	and    $0x1,%ebx
    7fb40dba5fad:	89 9d e8 fb ff ff    	mov    %ebx,-0x418(%rbp)
    7fb40dba5fb3:	d1 e3                	shl    %ebx
    7fb40dba5fb5:	89 8d e0 fb ff ff    	mov    %ecx,-0x420(%rbp)
    7fb40dba5fbb:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7fb40dba5fc1:	0b d9                	or     %ecx,%ebx
    7fb40dba5fc3:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba5fc6:	0b d9                	or     %ecx,%ebx
    7fb40dba5fc8:	8b 8d e8 fb ff ff    	mov    -0x418(%rbp),%ecx
    7fb40dba5fce:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba5fd1:	0b d9                	or     %ecx,%ebx
    7fb40dba5fd3:	33 d3                	xor    %ebx,%edx
    7fb40dba5fd5:	33 c2                	xor    %edx,%eax
    7fb40dba5fd7:	44 33 d8             	xor    %eax,%r11d
    7fb40dba5fda:	33 fe                	xor    %esi,%edi
    7fb40dba5fdc:	44 33 c7             	xor    %edi,%r8d
    7fb40dba5fdf:	44 33 85 08 fc ff ff 	xor    -0x3f8(%rbp),%r8d
    7fb40dba5fe6:	41 33 d0             	xor    %r8d,%edx
    7fb40dba5fe9:	49 0f b6 87 44 01 00 	movzbq 0x144(%r15),%rax
    7fb40dba5ff0:	00 
    7fb40dba5ff1:	8b c0                	mov    %eax,%eax
    7fb40dba5ff3:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba5ff8:	8b c8                	mov    %eax,%ecx
    7fb40dba5ffa:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba5ffd:	d1 e1                	shl    %ecx
    7fb40dba5fff:	8b d8                	mov    %eax,%ebx
    7fb40dba6001:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba6004:	83 e3 01             	and    $0x1,%ebx
    7fb40dba6007:	8b f3                	mov    %ebx,%esi
    7fb40dba6009:	d1 e6                	shl    %esi
    7fb40dba600b:	0b f3                	or     %ebx,%esi
    7fb40dba600d:	8b fb                	mov    %ebx,%edi
    7fb40dba600f:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba6012:	0b f7                	or     %edi,%esi
    7fb40dba6014:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba6017:	0b f3                	or     %ebx,%esi
    7fb40dba6019:	33 ce                	xor    %esi,%ecx
    7fb40dba601b:	49 0f b6 9f 49 01 00 	movzbq 0x149(%r15),%rbx
    7fb40dba6022:	00 
    7fb40dba6023:	8b db                	mov    %ebx,%ebx
    7fb40dba6025:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba602a:	8b f3                	mov    %ebx,%esi
    7fb40dba602c:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba602f:	d1 e6                	shl    %esi
    7fb40dba6031:	8b fb                	mov    %ebx,%edi
    7fb40dba6033:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba6036:	83 e7 01             	and    $0x1,%edi
    7fb40dba6039:	44 8b c7             	mov    %edi,%r8d
    7fb40dba603c:	41 d1 e0             	shl    %r8d
    7fb40dba603f:	44 0b c7             	or     %edi,%r8d
    7fb40dba6042:	89 bd d8 fb ff ff    	mov    %edi,-0x428(%rbp)
    7fb40dba6048:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba604b:	44 0b c7             	or     %edi,%r8d
    7fb40dba604e:	8b bd d8 fb ff ff    	mov    -0x428(%rbp),%edi
    7fb40dba6054:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba6057:	44 0b c7             	or     %edi,%r8d
    7fb40dba605a:	41 33 f0             	xor    %r8d,%esi
    7fb40dba605d:	8b fe                	mov    %esi,%edi
    7fb40dba605f:	33 fb                	xor    %ebx,%edi
    7fb40dba6061:	33 f9                	xor    %ecx,%edi
    7fb40dba6063:	4d 0f b6 87 4e 01 00 	movzbq 0x14e(%r15),%r8
    7fb40dba606a:	00 
    7fb40dba606b:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba606e:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba6073:	41 33 f8             	xor    %r8d,%edi
    7fb40dba6076:	44 89 95 d0 fb ff ff 	mov    %r10d,-0x430(%rbp)
    7fb40dba607d:	4d 0f b6 97 43 01 00 	movzbq 0x143(%r15),%r10
    7fb40dba6084:	00 
    7fb40dba6085:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba6088:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba608d:	41 33 fa             	xor    %r10d,%edi
    7fb40dba6090:	33 f0                	xor    %eax,%esi
    7fb40dba6092:	44 89 85 c8 fb ff ff 	mov    %r8d,-0x438(%rbp)
    7fb40dba6099:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba609d:	41 d1 e0             	shl    %r8d
    7fb40dba60a0:	44 89 8d c0 fb ff ff 	mov    %r9d,-0x440(%rbp)
    7fb40dba60a7:	44 8b 8d c8 fb ff ff 	mov    -0x438(%rbp),%r9d
    7fb40dba60ae:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba60b2:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba60b6:	44 89 8d b8 fb ff ff 	mov    %r9d,-0x448(%rbp)
    7fb40dba60bd:	41 d1 e1             	shl    %r9d
    7fb40dba60c0:	44 89 9d b0 fb ff ff 	mov    %r11d,-0x450(%rbp)
    7fb40dba60c7:	44 8b 9d b8 fb ff ff 	mov    -0x448(%rbp),%r11d
    7fb40dba60ce:	45 0b cb             	or     %r11d,%r9d
    7fb40dba60d1:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba60d5:	45 0b cb             	or     %r11d,%r9d
    7fb40dba60d8:	44 8b 9d b8 fb ff ff 	mov    -0x448(%rbp),%r11d
    7fb40dba60df:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba60e3:	45 0b cb             	or     %r11d,%r9d
    7fb40dba60e6:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba60e9:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba60ec:	44 8b 9d c8 fb ff ff 	mov    -0x438(%rbp),%r11d
    7fb40dba60f3:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba60f6:	41 33 f1             	xor    %r9d,%esi
    7fb40dba60f9:	41 33 f2             	xor    %r10d,%esi
    7fb40dba60fc:	44 8b c8             	mov    %eax,%r9d
    7fb40dba60ff:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba6102:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba6105:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba6108:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba610c:	41 d1 e1             	shl    %r9d
    7fb40dba610f:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6112:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba6116:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba611a:	44 89 9d a8 fb ff ff 	mov    %r11d,-0x458(%rbp)
    7fb40dba6121:	41 d1 e3             	shl    %r11d
    7fb40dba6124:	89 95 a0 fb ff ff    	mov    %edx,-0x460(%rbp)
    7fb40dba612a:	8b 95 a8 fb ff ff    	mov    -0x458(%rbp),%edx
    7fb40dba6130:	44 0b da             	or     %edx,%r11d
    7fb40dba6133:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba6136:	44 0b da             	or     %edx,%r11d
    7fb40dba6139:	8b 95 a8 fb ff ff    	mov    -0x458(%rbp),%edx
    7fb40dba613f:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba6142:	44 0b da             	or     %edx,%r11d
    7fb40dba6145:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba6148:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba614b:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba614e:	33 c8                	xor    %eax,%ecx
    7fb40dba6150:	33 d9                	xor    %ecx,%ebx
    7fb40dba6152:	33 9d c8 fb ff ff    	xor    -0x438(%rbp),%ebx
    7fb40dba6158:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba615b:	49 0f b6 87 48 01 00 	movzbq 0x148(%r15),%rax
    7fb40dba6162:	00 
    7fb40dba6163:	8b c0                	mov    %eax,%eax
    7fb40dba6165:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba616a:	8b c8                	mov    %eax,%ecx
    7fb40dba616c:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba616f:	d1 e1                	shl    %ecx
    7fb40dba6171:	8b d0                	mov    %eax,%edx
    7fb40dba6173:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba6176:	83 e2 01             	and    $0x1,%edx
    7fb40dba6179:	8b da                	mov    %edx,%ebx
    7fb40dba617b:	d1 e3                	shl    %ebx
    7fb40dba617d:	0b da                	or     %edx,%ebx
    7fb40dba617f:	44 8b d2             	mov    %edx,%r10d
    7fb40dba6182:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba6186:	41 0b da             	or     %r10d,%ebx
    7fb40dba6189:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba618c:	0b da                	or     %edx,%ebx
    7fb40dba618e:	33 cb                	xor    %ebx,%ecx
    7fb40dba6190:	49 0f b6 97 4d 01 00 	movzbq 0x14d(%r15),%rdx
    7fb40dba6197:	00 
    7fb40dba6198:	8b d2                	mov    %edx,%edx
    7fb40dba619a:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba619f:	8b da                	mov    %edx,%ebx
    7fb40dba61a1:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba61a4:	d1 e3                	shl    %ebx
    7fb40dba61a6:	44 8b d2             	mov    %edx,%r10d
    7fb40dba61a9:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba61ad:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba61b1:	45 8b da             	mov    %r10d,%r11d
    7fb40dba61b4:	41 d1 e3             	shl    %r11d
    7fb40dba61b7:	45 0b da             	or     %r10d,%r11d
    7fb40dba61ba:	44 89 95 98 fb ff ff 	mov    %r10d,-0x468(%rbp)
    7fb40dba61c1:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba61c5:	45 0b da             	or     %r10d,%r11d
    7fb40dba61c8:	44 8b 95 98 fb ff ff 	mov    -0x468(%rbp),%r10d
    7fb40dba61cf:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba61d3:	45 0b da             	or     %r10d,%r11d
    7fb40dba61d6:	41 33 db             	xor    %r11d,%ebx
    7fb40dba61d9:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba61dc:	44 33 d2             	xor    %edx,%r10d
    7fb40dba61df:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba61e2:	4d 0f b6 9f 42 01 00 	movzbq 0x142(%r15),%r11
    7fb40dba61e9:	00 
    7fb40dba61ea:	45 8b db             	mov    %r11d,%r11d
    7fb40dba61ed:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba61f2:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba61f5:	89 bd 90 fb ff ff    	mov    %edi,-0x470(%rbp)
    7fb40dba61fb:	49 0f b6 bf 47 01 00 	movzbq 0x147(%r15),%rdi
    7fb40dba6202:	00 
    7fb40dba6203:	8b ff                	mov    %edi,%edi
    7fb40dba6205:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba620a:	44 33 d7             	xor    %edi,%r10d
    7fb40dba620d:	33 d8                	xor    %eax,%ebx
    7fb40dba620f:	44 89 9d 88 fb ff ff 	mov    %r11d,-0x478(%rbp)
    7fb40dba6216:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba621a:	41 d1 e3             	shl    %r11d
    7fb40dba621d:	89 b5 80 fb ff ff    	mov    %esi,-0x480(%rbp)
    7fb40dba6223:	8b b5 88 fb ff ff    	mov    -0x478(%rbp),%esi
    7fb40dba6229:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba622c:	83 e6 01             	and    $0x1,%esi
    7fb40dba622f:	89 b5 78 fb ff ff    	mov    %esi,-0x488(%rbp)
    7fb40dba6235:	d1 e6                	shl    %esi
    7fb40dba6237:	44 89 85 70 fb ff ff 	mov    %r8d,-0x490(%rbp)
    7fb40dba623e:	44 8b 85 78 fb ff ff 	mov    -0x488(%rbp),%r8d
    7fb40dba6245:	41 0b f0             	or     %r8d,%esi
    7fb40dba6248:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba624c:	41 0b f0             	or     %r8d,%esi
    7fb40dba624f:	44 8b 85 78 fb ff ff 	mov    -0x488(%rbp),%r8d
    7fb40dba6256:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba625a:	41 0b f0             	or     %r8d,%esi
    7fb40dba625d:	44 33 de             	xor    %esi,%r11d
    7fb40dba6260:	41 8b f3             	mov    %r11d,%esi
    7fb40dba6263:	44 8b 85 88 fb ff ff 	mov    -0x478(%rbp),%r8d
    7fb40dba626a:	41 33 f0             	xor    %r8d,%esi
    7fb40dba626d:	33 de                	xor    %esi,%ebx
    7fb40dba626f:	33 df                	xor    %edi,%ebx
    7fb40dba6271:	8b f0                	mov    %eax,%esi
    7fb40dba6273:	33 f2                	xor    %edx,%esi
    7fb40dba6275:	44 33 de             	xor    %esi,%r11d
    7fb40dba6278:	8b f7                	mov    %edi,%esi
    7fb40dba627a:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba627d:	d1 e6                	shl    %esi
    7fb40dba627f:	44 8b c7             	mov    %edi,%r8d
    7fb40dba6282:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba6286:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba628a:	44 89 85 68 fb ff ff 	mov    %r8d,-0x498(%rbp)
    7fb40dba6291:	41 d1 e0             	shl    %r8d
    7fb40dba6294:	44 89 8d 60 fb ff ff 	mov    %r9d,-0x4a0(%rbp)
    7fb40dba629b:	44 8b 8d 68 fb ff ff 	mov    -0x498(%rbp),%r9d
    7fb40dba62a2:	45 0b c1             	or     %r9d,%r8d
    7fb40dba62a5:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba62a9:	45 0b c1             	or     %r9d,%r8d
    7fb40dba62ac:	44 8b 8d 68 fb ff ff 	mov    -0x498(%rbp),%r9d
    7fb40dba62b3:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba62b7:	45 0b c1             	or     %r9d,%r8d
    7fb40dba62ba:	41 33 f0             	xor    %r8d,%esi
    7fb40dba62bd:	33 fe                	xor    %esi,%edi
    7fb40dba62bf:	44 33 df             	xor    %edi,%r11d
    7fb40dba62c2:	33 c8                	xor    %eax,%ecx
    7fb40dba62c4:	33 d1                	xor    %ecx,%edx
    7fb40dba62c6:	33 95 88 fb ff ff    	xor    -0x478(%rbp),%edx
    7fb40dba62cc:	33 f2                	xor    %edx,%esi
    7fb40dba62ce:	49 0f b6 87 4c 01 00 	movzbq 0x14c(%r15),%rax
    7fb40dba62d5:	00 
    7fb40dba62d6:	8b c0                	mov    %eax,%eax
    7fb40dba62d8:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba62dd:	8b c8                	mov    %eax,%ecx
    7fb40dba62df:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba62e2:	d1 e1                	shl    %ecx
    7fb40dba62e4:	8b d0                	mov    %eax,%edx
    7fb40dba62e6:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba62e9:	83 e2 01             	and    $0x1,%edx
    7fb40dba62ec:	8b fa                	mov    %edx,%edi
    7fb40dba62ee:	d1 e7                	shl    %edi
    7fb40dba62f0:	0b fa                	or     %edx,%edi
    7fb40dba62f2:	44 8b c2             	mov    %edx,%r8d
    7fb40dba62f5:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba62f9:	41 0b f8             	or     %r8d,%edi
    7fb40dba62fc:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba62ff:	0b fa                	or     %edx,%edi
    7fb40dba6301:	33 cf                	xor    %edi,%ecx
    7fb40dba6303:	49 0f b6 97 41 01 00 	movzbq 0x141(%r15),%rdx
    7fb40dba630a:	00 
    7fb40dba630b:	8b d2                	mov    %edx,%edx
    7fb40dba630d:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba6312:	8b fa                	mov    %edx,%edi
    7fb40dba6314:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba6317:	d1 e7                	shl    %edi
    7fb40dba6319:	44 8b c2             	mov    %edx,%r8d
    7fb40dba631c:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba6320:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba6324:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba6327:	41 d1 e1             	shl    %r9d
    7fb40dba632a:	45 0b c8             	or     %r8d,%r9d
    7fb40dba632d:	44 89 85 58 fb ff ff 	mov    %r8d,-0x4a8(%rbp)
    7fb40dba6334:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba6338:	45 0b c8             	or     %r8d,%r9d
    7fb40dba633b:	44 8b 85 58 fb ff ff 	mov    -0x4a8(%rbp),%r8d
    7fb40dba6342:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba6346:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6349:	41 33 f9             	xor    %r9d,%edi
    7fb40dba634c:	44 8b c7             	mov    %edi,%r8d
    7fb40dba634f:	44 33 c2             	xor    %edx,%r8d
    7fb40dba6352:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba6355:	4d 0f b6 8f 46 01 00 	movzbq 0x146(%r15),%r9
    7fb40dba635c:	00 
    7fb40dba635d:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba6360:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba6365:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba6368:	44 89 95 50 fb ff ff 	mov    %r10d,-0x4b0(%rbp)
    7fb40dba636f:	4d 0f b6 97 4b 01 00 	movzbq 0x14b(%r15),%r10
    7fb40dba6376:	00 
    7fb40dba6377:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba637a:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba637f:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba6382:	33 f8                	xor    %eax,%edi
    7fb40dba6384:	44 89 8d 48 fb ff ff 	mov    %r9d,-0x4b8(%rbp)
    7fb40dba638b:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba638f:	41 d1 e1             	shl    %r9d
    7fb40dba6392:	89 9d 40 fb ff ff    	mov    %ebx,-0x4c0(%rbp)
    7fb40dba6398:	8b 9d 48 fb ff ff    	mov    -0x4b8(%rbp),%ebx
    7fb40dba639e:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba63a1:	83 e3 01             	and    $0x1,%ebx
    7fb40dba63a4:	89 9d 38 fb ff ff    	mov    %ebx,-0x4c8(%rbp)
    7fb40dba63aa:	d1 e3                	shl    %ebx
    7fb40dba63ac:	44 89 9d 30 fb ff ff 	mov    %r11d,-0x4d0(%rbp)
    7fb40dba63b3:	44 8b 9d 38 fb ff ff 	mov    -0x4c8(%rbp),%r11d
    7fb40dba63ba:	41 0b db             	or     %r11d,%ebx
    7fb40dba63bd:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba63c1:	41 0b db             	or     %r11d,%ebx
    7fb40dba63c4:	44 8b 9d 38 fb ff ff 	mov    -0x4c8(%rbp),%r11d
    7fb40dba63cb:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba63cf:	41 0b db             	or     %r11d,%ebx
    7fb40dba63d2:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba63d5:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba63d8:	44 8b 9d 48 fb ff ff 	mov    -0x4b8(%rbp),%r11d
    7fb40dba63df:	41 33 db             	xor    %r11d,%ebx
    7fb40dba63e2:	33 fb                	xor    %ebx,%edi
    7fb40dba63e4:	41 33 fa             	xor    %r10d,%edi
    7fb40dba63e7:	8b d8                	mov    %eax,%ebx
    7fb40dba63e9:	33 da                	xor    %edx,%ebx
    7fb40dba63eb:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba63ee:	41 8b da             	mov    %r10d,%ebx
    7fb40dba63f1:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba63f4:	d1 e3                	shl    %ebx
    7fb40dba63f6:	45 8b da             	mov    %r10d,%r11d
    7fb40dba63f9:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba63fd:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba6401:	44 89 9d 28 fb ff ff 	mov    %r11d,-0x4d8(%rbp)
    7fb40dba6408:	41 d1 e3             	shl    %r11d
    7fb40dba640b:	89 b5 20 fb ff ff    	mov    %esi,-0x4e0(%rbp)
    7fb40dba6411:	8b b5 28 fb ff ff    	mov    -0x4d8(%rbp),%esi
    7fb40dba6417:	44 0b de             	or     %esi,%r11d
    7fb40dba641a:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba641d:	44 0b de             	or     %esi,%r11d
    7fb40dba6420:	8b b5 28 fb ff ff    	mov    -0x4d8(%rbp),%esi
    7fb40dba6426:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba6429:	44 0b de             	or     %esi,%r11d
    7fb40dba642c:	41 33 db             	xor    %r11d,%ebx
    7fb40dba642f:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba6432:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba6435:	33 c8                	xor    %eax,%ecx
    7fb40dba6437:	33 d1                	xor    %ecx,%edx
    7fb40dba6439:	33 95 48 fb ff ff    	xor    -0x4b8(%rbp),%edx
    7fb40dba643f:	33 da                	xor    %edx,%ebx
    7fb40dba6441:	8b 85 c0 fb ff ff    	mov    -0x440(%rbp),%eax
    7fb40dba6447:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba644a:	8b 8d d0 fb ff ff    	mov    -0x430(%rbp),%ecx
    7fb40dba6450:	0b c1                	or     %ecx,%eax
    7fb40dba6452:	8b 8d b0 fb ff ff    	mov    -0x450(%rbp),%ecx
    7fb40dba6458:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba645b:	0b c1                	or     %ecx,%eax
    7fb40dba645d:	8b 8d a0 fb ff ff    	mov    -0x460(%rbp),%ecx
    7fb40dba6463:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba6466:	0b c1                	or     %ecx,%eax
    7fb40dba6468:	8b 8d 90 fb ff ff    	mov    -0x470(%rbp),%ecx
    7fb40dba646e:	8b c9                	mov    %ecx,%ecx
    7fb40dba6470:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba6474:	8b c0                	mov    %eax,%eax
    7fb40dba6476:	48 0b c8             	or     %rax,%rcx
    7fb40dba6479:	8b 85 80 fb ff ff    	mov    -0x480(%rbp),%eax
    7fb40dba647f:	8b c0                	mov    %eax,%eax
    7fb40dba6481:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba6485:	48 0b c8             	or     %rax,%rcx
    7fb40dba6488:	8b 85 70 fb ff ff    	mov    -0x490(%rbp),%eax
    7fb40dba648e:	8b c0                	mov    %eax,%eax
    7fb40dba6490:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba6494:	48 0b c8             	or     %rax,%rcx
    7fb40dba6497:	8b 85 60 fb ff ff    	mov    -0x4a0(%rbp),%eax
    7fb40dba649d:	8b c0                	mov    %eax,%eax
    7fb40dba649f:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba64a3:	48 0b c8             	or     %rax,%rcx
    7fb40dba64a6:	49 89 8f a0 02 00 00 	mov    %rcx,0x2a0(%r15)
    7fb40dba64ad:	8b 85 40 fb ff ff    	mov    -0x4c0(%rbp),%eax
    7fb40dba64b3:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba64b6:	8b 8d 50 fb ff ff    	mov    -0x4b0(%rbp),%ecx
    7fb40dba64bc:	0b c1                	or     %ecx,%eax
    7fb40dba64be:	8b 8d 30 fb ff ff    	mov    -0x4d0(%rbp),%ecx
    7fb40dba64c4:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba64c7:	0b c1                	or     %ecx,%eax
    7fb40dba64c9:	8b 8d 20 fb ff ff    	mov    -0x4e0(%rbp),%ecx
    7fb40dba64cf:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba64d2:	0b c1                	or     %ecx,%eax
    7fb40dba64d4:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba64d7:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba64db:	8b c0                	mov    %eax,%eax
    7fb40dba64dd:	4c 0b c0             	or     %rax,%r8
    7fb40dba64e0:	8b ff                	mov    %edi,%edi
    7fb40dba64e2:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba64e6:	4c 0b c7             	or     %rdi,%r8
    7fb40dba64e9:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba64ec:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba64f0:	4d 0b c1             	or     %r9,%r8
    7fb40dba64f3:	8b db                	mov    %ebx,%ebx
    7fb40dba64f5:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba64f9:	4c 0b c3             	or     %rbx,%r8
    7fb40dba64fc:	4d 89 87 a8 02 00 00 	mov    %r8,0x2a8(%r15)
    7fb40dba6503:	8b 85 f0 fb ff ff    	mov    -0x410(%rbp),%eax
    7fb40dba6509:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba650e:	8b c0                	mov    %eax,%eax
    7fb40dba6510:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba6515:	8b 8d f0 fb ff ff    	mov    -0x410(%rbp),%ecx
    7fb40dba651b:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba651e:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba6524:	8b c9                	mov    %ecx,%ecx
    7fb40dba6526:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba652b:	8b 95 f0 fb ff ff    	mov    -0x410(%rbp),%edx
    7fb40dba6531:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba6534:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba653a:	8b d2                	mov    %edx,%edx
    7fb40dba653c:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba6541:	8b 9d f0 fb ff ff    	mov    -0x410(%rbp),%ebx
    7fb40dba6547:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba654a:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba6550:	8b db                	mov    %ebx,%ebx
    7fb40dba6552:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba6557:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba655a:	0b da                	or     %edx,%ebx
    7fb40dba655c:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba655f:	0b d9                	or     %ecx,%ebx
    7fb40dba6561:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba6564:	0b d8                	or     %eax,%ebx
    7fb40dba6566:	83 f3 10             	xor    $0x10,%ebx
    7fb40dba6569:	8b 85 00 fc ff ff    	mov    -0x400(%rbp),%eax
    7fb40dba656f:	33 d8                	xor    %eax,%ebx
    7fb40dba6571:	8b 85 10 fc ff ff    	mov    -0x3f0(%rbp),%eax
    7fb40dba6577:	33 c3                	xor    %ebx,%eax
    7fb40dba6579:	8b 8d e0 fb ff ff    	mov    -0x420(%rbp),%ecx
    7fb40dba657f:	33 c8                	xor    %eax,%ecx
    7fb40dba6581:	8b 95 f0 fb ff ff    	mov    -0x410(%rbp),%edx
    7fb40dba6587:	33 d1                	xor    %ecx,%edx
    7fb40dba6589:	8b f0                	mov    %eax,%esi
    7fb40dba658b:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba658f:	8b fb                	mov    %ebx,%edi
    7fb40dba6591:	48 0b f7             	or     %rdi,%rsi
    7fb40dba6594:	49 89 b7 00 02 00 00 	mov    %rsi,0x200(%r15)
    7fb40dba659b:	8b f2                	mov    %edx,%esi
    7fb40dba659d:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba65a1:	8b f9                	mov    %ecx,%edi
    7fb40dba65a3:	48 0b f7             	or     %rdi,%rsi
    7fb40dba65a6:	49 89 b7 08 02 00 00 	mov    %rsi,0x208(%r15)
    7fb40dba65ad:	49 8b b7 a0 02 00 00 	mov    0x2a0(%r15),%rsi
    7fb40dba65b4:	49 8b bf 00 02 00 00 	mov    0x200(%r15),%rdi
    7fb40dba65bb:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba65be:	49 89 b7 50 03 00 00 	mov    %rsi,0x350(%r15)
    7fb40dba65c5:	49 8b b7 a8 02 00 00 	mov    0x2a8(%r15),%rsi
    7fb40dba65cc:	49 8b bf 08 02 00 00 	mov    0x208(%r15),%rdi
    7fb40dba65d3:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba65d6:	49 89 b7 58 03 00 00 	mov    %rsi,0x358(%r15)
    7fb40dba65dd:	49 0f b6 b7 50 01 00 	movzbq 0x150(%r15),%rsi
    7fb40dba65e4:	00 
    7fb40dba65e5:	8b f6                	mov    %esi,%esi
    7fb40dba65e7:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba65ec:	8b fe                	mov    %esi,%edi
    7fb40dba65ee:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba65f1:	d1 e7                	shl    %edi
    7fb40dba65f3:	44 8b c6             	mov    %esi,%r8d
    7fb40dba65f6:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba65fa:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba65fe:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba6601:	41 d1 e1             	shl    %r9d
    7fb40dba6604:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6607:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba660a:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba660e:	45 0b ca             	or     %r10d,%r9d
    7fb40dba6611:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba6615:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6618:	41 33 f9             	xor    %r9d,%edi
    7fb40dba661b:	4d 0f b6 87 55 01 00 	movzbq 0x155(%r15),%r8
    7fb40dba6622:	00 
    7fb40dba6623:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba6626:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba662b:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba662e:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba6632:	41 d1 e1             	shl    %r9d
    7fb40dba6635:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba6638:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba663c:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba6640:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6643:	41 d1 e3             	shl    %r11d
    7fb40dba6646:	45 0b da             	or     %r10d,%r11d
    7fb40dba6649:	44 89 95 18 fb ff ff 	mov    %r10d,-0x4e8(%rbp)
    7fb40dba6650:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba6654:	45 0b da             	or     %r10d,%r11d
    7fb40dba6657:	44 8b 95 18 fb ff ff 	mov    -0x4e8(%rbp),%r10d
    7fb40dba665e:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba6662:	45 0b da             	or     %r10d,%r11d
    7fb40dba6665:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba6668:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba666b:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba666e:	44 33 d7             	xor    %edi,%r10d
    7fb40dba6671:	4d 0f b6 9f 5a 01 00 	movzbq 0x15a(%r15),%r11
    7fb40dba6678:	00 
    7fb40dba6679:	45 8b db             	mov    %r11d,%r11d
    7fb40dba667c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba6681:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba6684:	89 85 10 fb ff ff    	mov    %eax,-0x4f0(%rbp)
    7fb40dba668a:	49 0f b6 87 5f 01 00 	movzbq 0x15f(%r15),%rax
    7fb40dba6691:	00 
    7fb40dba6692:	8b c0                	mov    %eax,%eax
    7fb40dba6694:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba6699:	44 33 d0             	xor    %eax,%r10d
    7fb40dba669c:	44 33 ce             	xor    %esi,%r9d
    7fb40dba669f:	44 89 9d 08 fb ff ff 	mov    %r11d,-0x4f8(%rbp)
    7fb40dba66a6:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba66aa:	41 d1 e3             	shl    %r11d
    7fb40dba66ad:	89 9d 00 fb ff ff    	mov    %ebx,-0x500(%rbp)
    7fb40dba66b3:	8b 9d 08 fb ff ff    	mov    -0x4f8(%rbp),%ebx
    7fb40dba66b9:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba66bc:	83 e3 01             	and    $0x1,%ebx
    7fb40dba66bf:	89 9d f8 fa ff ff    	mov    %ebx,-0x508(%rbp)
    7fb40dba66c5:	d1 e3                	shl    %ebx
    7fb40dba66c7:	89 95 f0 fa ff ff    	mov    %edx,-0x510(%rbp)
    7fb40dba66cd:	8b 95 f8 fa ff ff    	mov    -0x508(%rbp),%edx
    7fb40dba66d3:	0b da                	or     %edx,%ebx
    7fb40dba66d5:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba66d8:	0b da                	or     %edx,%ebx
    7fb40dba66da:	8b 95 f8 fa ff ff    	mov    -0x508(%rbp),%edx
    7fb40dba66e0:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba66e3:	0b da                	or     %edx,%ebx
    7fb40dba66e5:	44 33 db             	xor    %ebx,%r11d
    7fb40dba66e8:	41 8b d3             	mov    %r11d,%edx
    7fb40dba66eb:	8b 9d 08 fb ff ff    	mov    -0x4f8(%rbp),%ebx
    7fb40dba66f1:	33 d3                	xor    %ebx,%edx
    7fb40dba66f3:	44 33 ca             	xor    %edx,%r9d
    7fb40dba66f6:	44 33 c8             	xor    %eax,%r9d
    7fb40dba66f9:	8b d6                	mov    %esi,%edx
    7fb40dba66fb:	41 33 d0             	xor    %r8d,%edx
    7fb40dba66fe:	44 33 da             	xor    %edx,%r11d
    7fb40dba6701:	8b d0                	mov    %eax,%edx
    7fb40dba6703:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba6706:	d1 e2                	shl    %edx
    7fb40dba6708:	8b d8                	mov    %eax,%ebx
    7fb40dba670a:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba670d:	83 e3 01             	and    $0x1,%ebx
    7fb40dba6710:	89 9d e8 fa ff ff    	mov    %ebx,-0x518(%rbp)
    7fb40dba6716:	d1 e3                	shl    %ebx
    7fb40dba6718:	89 8d e0 fa ff ff    	mov    %ecx,-0x520(%rbp)
    7fb40dba671e:	8b 8d e8 fa ff ff    	mov    -0x518(%rbp),%ecx
    7fb40dba6724:	0b d9                	or     %ecx,%ebx
    7fb40dba6726:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba6729:	0b d9                	or     %ecx,%ebx
    7fb40dba672b:	8b 8d e8 fa ff ff    	mov    -0x518(%rbp),%ecx
    7fb40dba6731:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba6734:	0b d9                	or     %ecx,%ebx
    7fb40dba6736:	33 d3                	xor    %ebx,%edx
    7fb40dba6738:	33 c2                	xor    %edx,%eax
    7fb40dba673a:	44 33 d8             	xor    %eax,%r11d
    7fb40dba673d:	33 fe                	xor    %esi,%edi
    7fb40dba673f:	44 33 c7             	xor    %edi,%r8d
    7fb40dba6742:	44 33 85 08 fb ff ff 	xor    -0x4f8(%rbp),%r8d
    7fb40dba6749:	41 33 d0             	xor    %r8d,%edx
    7fb40dba674c:	49 0f b6 87 54 01 00 	movzbq 0x154(%r15),%rax
    7fb40dba6753:	00 
    7fb40dba6754:	8b c0                	mov    %eax,%eax
    7fb40dba6756:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba675b:	8b c8                	mov    %eax,%ecx
    7fb40dba675d:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba6760:	d1 e1                	shl    %ecx
    7fb40dba6762:	8b d8                	mov    %eax,%ebx
    7fb40dba6764:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba6767:	83 e3 01             	and    $0x1,%ebx
    7fb40dba676a:	8b f3                	mov    %ebx,%esi
    7fb40dba676c:	d1 e6                	shl    %esi
    7fb40dba676e:	0b f3                	or     %ebx,%esi
    7fb40dba6770:	8b fb                	mov    %ebx,%edi
    7fb40dba6772:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba6775:	0b f7                	or     %edi,%esi
    7fb40dba6777:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba677a:	0b f3                	or     %ebx,%esi
    7fb40dba677c:	33 ce                	xor    %esi,%ecx
    7fb40dba677e:	49 0f b6 9f 59 01 00 	movzbq 0x159(%r15),%rbx
    7fb40dba6785:	00 
    7fb40dba6786:	8b db                	mov    %ebx,%ebx
    7fb40dba6788:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba678d:	8b f3                	mov    %ebx,%esi
    7fb40dba678f:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba6792:	d1 e6                	shl    %esi
    7fb40dba6794:	8b fb                	mov    %ebx,%edi
    7fb40dba6796:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba6799:	83 e7 01             	and    $0x1,%edi
    7fb40dba679c:	44 8b c7             	mov    %edi,%r8d
    7fb40dba679f:	41 d1 e0             	shl    %r8d
    7fb40dba67a2:	44 0b c7             	or     %edi,%r8d
    7fb40dba67a5:	89 bd d8 fa ff ff    	mov    %edi,-0x528(%rbp)
    7fb40dba67ab:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba67ae:	44 0b c7             	or     %edi,%r8d
    7fb40dba67b1:	8b bd d8 fa ff ff    	mov    -0x528(%rbp),%edi
    7fb40dba67b7:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba67ba:	44 0b c7             	or     %edi,%r8d
    7fb40dba67bd:	41 33 f0             	xor    %r8d,%esi
    7fb40dba67c0:	8b fe                	mov    %esi,%edi
    7fb40dba67c2:	33 fb                	xor    %ebx,%edi
    7fb40dba67c4:	33 f9                	xor    %ecx,%edi
    7fb40dba67c6:	4d 0f b6 87 5e 01 00 	movzbq 0x15e(%r15),%r8
    7fb40dba67cd:	00 
    7fb40dba67ce:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba67d1:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba67d6:	41 33 f8             	xor    %r8d,%edi
    7fb40dba67d9:	44 89 95 d0 fa ff ff 	mov    %r10d,-0x530(%rbp)
    7fb40dba67e0:	4d 0f b6 97 53 01 00 	movzbq 0x153(%r15),%r10
    7fb40dba67e7:	00 
    7fb40dba67e8:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba67eb:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba67f0:	41 33 fa             	xor    %r10d,%edi
    7fb40dba67f3:	33 f0                	xor    %eax,%esi
    7fb40dba67f5:	44 89 85 c8 fa ff ff 	mov    %r8d,-0x538(%rbp)
    7fb40dba67fc:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba6800:	41 d1 e0             	shl    %r8d
    7fb40dba6803:	44 89 8d c0 fa ff ff 	mov    %r9d,-0x540(%rbp)
    7fb40dba680a:	44 8b 8d c8 fa ff ff 	mov    -0x538(%rbp),%r9d
    7fb40dba6811:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba6815:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba6819:	44 89 8d b8 fa ff ff 	mov    %r9d,-0x548(%rbp)
    7fb40dba6820:	41 d1 e1             	shl    %r9d
    7fb40dba6823:	44 89 9d b0 fa ff ff 	mov    %r11d,-0x550(%rbp)
    7fb40dba682a:	44 8b 9d b8 fa ff ff 	mov    -0x548(%rbp),%r11d
    7fb40dba6831:	45 0b cb             	or     %r11d,%r9d
    7fb40dba6834:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba6838:	45 0b cb             	or     %r11d,%r9d
    7fb40dba683b:	44 8b 9d b8 fa ff ff 	mov    -0x548(%rbp),%r11d
    7fb40dba6842:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba6846:	45 0b cb             	or     %r11d,%r9d
    7fb40dba6849:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba684c:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba684f:	44 8b 9d c8 fa ff ff 	mov    -0x538(%rbp),%r11d
    7fb40dba6856:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba6859:	41 33 f1             	xor    %r9d,%esi
    7fb40dba685c:	41 33 f2             	xor    %r10d,%esi
    7fb40dba685f:	44 8b c8             	mov    %eax,%r9d
    7fb40dba6862:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba6865:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba6868:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba686b:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba686f:	41 d1 e1             	shl    %r9d
    7fb40dba6872:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6875:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba6879:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba687d:	44 89 9d a8 fa ff ff 	mov    %r11d,-0x558(%rbp)
    7fb40dba6884:	41 d1 e3             	shl    %r11d
    7fb40dba6887:	89 95 a0 fa ff ff    	mov    %edx,-0x560(%rbp)
    7fb40dba688d:	8b 95 a8 fa ff ff    	mov    -0x558(%rbp),%edx
    7fb40dba6893:	44 0b da             	or     %edx,%r11d
    7fb40dba6896:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba6899:	44 0b da             	or     %edx,%r11d
    7fb40dba689c:	8b 95 a8 fa ff ff    	mov    -0x558(%rbp),%edx
    7fb40dba68a2:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba68a5:	44 0b da             	or     %edx,%r11d
    7fb40dba68a8:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba68ab:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba68ae:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba68b1:	33 c8                	xor    %eax,%ecx
    7fb40dba68b3:	33 d9                	xor    %ecx,%ebx
    7fb40dba68b5:	33 9d c8 fa ff ff    	xor    -0x538(%rbp),%ebx
    7fb40dba68bb:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba68be:	49 0f b6 87 58 01 00 	movzbq 0x158(%r15),%rax
    7fb40dba68c5:	00 
    7fb40dba68c6:	8b c0                	mov    %eax,%eax
    7fb40dba68c8:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba68cd:	8b c8                	mov    %eax,%ecx
    7fb40dba68cf:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba68d2:	d1 e1                	shl    %ecx
    7fb40dba68d4:	8b d0                	mov    %eax,%edx
    7fb40dba68d6:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba68d9:	83 e2 01             	and    $0x1,%edx
    7fb40dba68dc:	8b da                	mov    %edx,%ebx
    7fb40dba68de:	d1 e3                	shl    %ebx
    7fb40dba68e0:	0b da                	or     %edx,%ebx
    7fb40dba68e2:	44 8b d2             	mov    %edx,%r10d
    7fb40dba68e5:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba68e9:	41 0b da             	or     %r10d,%ebx
    7fb40dba68ec:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba68ef:	0b da                	or     %edx,%ebx
    7fb40dba68f1:	33 cb                	xor    %ebx,%ecx
    7fb40dba68f3:	49 0f b6 97 5d 01 00 	movzbq 0x15d(%r15),%rdx
    7fb40dba68fa:	00 
    7fb40dba68fb:	8b d2                	mov    %edx,%edx
    7fb40dba68fd:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba6902:	8b da                	mov    %edx,%ebx
    7fb40dba6904:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba6907:	d1 e3                	shl    %ebx
    7fb40dba6909:	44 8b d2             	mov    %edx,%r10d
    7fb40dba690c:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba6910:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba6914:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6917:	41 d1 e3             	shl    %r11d
    7fb40dba691a:	45 0b da             	or     %r10d,%r11d
    7fb40dba691d:	44 89 95 98 fa ff ff 	mov    %r10d,-0x568(%rbp)
    7fb40dba6924:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba6928:	45 0b da             	or     %r10d,%r11d
    7fb40dba692b:	44 8b 95 98 fa ff ff 	mov    -0x568(%rbp),%r10d
    7fb40dba6932:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba6936:	45 0b da             	or     %r10d,%r11d
    7fb40dba6939:	41 33 db             	xor    %r11d,%ebx
    7fb40dba693c:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba693f:	44 33 d2             	xor    %edx,%r10d
    7fb40dba6942:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba6945:	4d 0f b6 9f 52 01 00 	movzbq 0x152(%r15),%r11
    7fb40dba694c:	00 
    7fb40dba694d:	45 8b db             	mov    %r11d,%r11d
    7fb40dba6950:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba6955:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba6958:	89 bd 90 fa ff ff    	mov    %edi,-0x570(%rbp)
    7fb40dba695e:	49 0f b6 bf 57 01 00 	movzbq 0x157(%r15),%rdi
    7fb40dba6965:	00 
    7fb40dba6966:	8b ff                	mov    %edi,%edi
    7fb40dba6968:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba696d:	44 33 d7             	xor    %edi,%r10d
    7fb40dba6970:	33 d8                	xor    %eax,%ebx
    7fb40dba6972:	44 89 9d 88 fa ff ff 	mov    %r11d,-0x578(%rbp)
    7fb40dba6979:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba697d:	41 d1 e3             	shl    %r11d
    7fb40dba6980:	89 b5 80 fa ff ff    	mov    %esi,-0x580(%rbp)
    7fb40dba6986:	8b b5 88 fa ff ff    	mov    -0x578(%rbp),%esi
    7fb40dba698c:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba698f:	83 e6 01             	and    $0x1,%esi
    7fb40dba6992:	89 b5 78 fa ff ff    	mov    %esi,-0x588(%rbp)
    7fb40dba6998:	d1 e6                	shl    %esi
    7fb40dba699a:	44 89 85 70 fa ff ff 	mov    %r8d,-0x590(%rbp)
    7fb40dba69a1:	44 8b 85 78 fa ff ff 	mov    -0x588(%rbp),%r8d
    7fb40dba69a8:	41 0b f0             	or     %r8d,%esi
    7fb40dba69ab:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba69af:	41 0b f0             	or     %r8d,%esi
    7fb40dba69b2:	44 8b 85 78 fa ff ff 	mov    -0x588(%rbp),%r8d
    7fb40dba69b9:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba69bd:	41 0b f0             	or     %r8d,%esi
    7fb40dba69c0:	44 33 de             	xor    %esi,%r11d
    7fb40dba69c3:	41 8b f3             	mov    %r11d,%esi
    7fb40dba69c6:	44 8b 85 88 fa ff ff 	mov    -0x578(%rbp),%r8d
    7fb40dba69cd:	41 33 f0             	xor    %r8d,%esi
    7fb40dba69d0:	33 de                	xor    %esi,%ebx
    7fb40dba69d2:	33 df                	xor    %edi,%ebx
    7fb40dba69d4:	8b f0                	mov    %eax,%esi
    7fb40dba69d6:	33 f2                	xor    %edx,%esi
    7fb40dba69d8:	44 33 de             	xor    %esi,%r11d
    7fb40dba69db:	8b f7                	mov    %edi,%esi
    7fb40dba69dd:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba69e0:	d1 e6                	shl    %esi
    7fb40dba69e2:	44 8b c7             	mov    %edi,%r8d
    7fb40dba69e5:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba69e9:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba69ed:	44 89 85 68 fa ff ff 	mov    %r8d,-0x598(%rbp)
    7fb40dba69f4:	41 d1 e0             	shl    %r8d
    7fb40dba69f7:	44 89 8d 60 fa ff ff 	mov    %r9d,-0x5a0(%rbp)
    7fb40dba69fe:	44 8b 8d 68 fa ff ff 	mov    -0x598(%rbp),%r9d
    7fb40dba6a05:	45 0b c1             	or     %r9d,%r8d
    7fb40dba6a08:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba6a0c:	45 0b c1             	or     %r9d,%r8d
    7fb40dba6a0f:	44 8b 8d 68 fa ff ff 	mov    -0x598(%rbp),%r9d
    7fb40dba6a16:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba6a1a:	45 0b c1             	or     %r9d,%r8d
    7fb40dba6a1d:	41 33 f0             	xor    %r8d,%esi
    7fb40dba6a20:	33 fe                	xor    %esi,%edi
    7fb40dba6a22:	44 33 df             	xor    %edi,%r11d
    7fb40dba6a25:	33 c8                	xor    %eax,%ecx
    7fb40dba6a27:	33 d1                	xor    %ecx,%edx
    7fb40dba6a29:	33 95 88 fa ff ff    	xor    -0x578(%rbp),%edx
    7fb40dba6a2f:	33 f2                	xor    %edx,%esi
    7fb40dba6a31:	49 0f b6 87 5c 01 00 	movzbq 0x15c(%r15),%rax
    7fb40dba6a38:	00 
    7fb40dba6a39:	8b c0                	mov    %eax,%eax
    7fb40dba6a3b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba6a40:	8b c8                	mov    %eax,%ecx
    7fb40dba6a42:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba6a45:	d1 e1                	shl    %ecx
    7fb40dba6a47:	8b d0                	mov    %eax,%edx
    7fb40dba6a49:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba6a4c:	83 e2 01             	and    $0x1,%edx
    7fb40dba6a4f:	8b fa                	mov    %edx,%edi
    7fb40dba6a51:	d1 e7                	shl    %edi
    7fb40dba6a53:	0b fa                	or     %edx,%edi
    7fb40dba6a55:	44 8b c2             	mov    %edx,%r8d
    7fb40dba6a58:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba6a5c:	41 0b f8             	or     %r8d,%edi
    7fb40dba6a5f:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba6a62:	0b fa                	or     %edx,%edi
    7fb40dba6a64:	33 cf                	xor    %edi,%ecx
    7fb40dba6a66:	49 0f b6 97 51 01 00 	movzbq 0x151(%r15),%rdx
    7fb40dba6a6d:	00 
    7fb40dba6a6e:	8b d2                	mov    %edx,%edx
    7fb40dba6a70:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba6a75:	8b fa                	mov    %edx,%edi
    7fb40dba6a77:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba6a7a:	d1 e7                	shl    %edi
    7fb40dba6a7c:	44 8b c2             	mov    %edx,%r8d
    7fb40dba6a7f:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba6a83:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba6a87:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba6a8a:	41 d1 e1             	shl    %r9d
    7fb40dba6a8d:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6a90:	44 89 85 58 fa ff ff 	mov    %r8d,-0x5a8(%rbp)
    7fb40dba6a97:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba6a9b:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6a9e:	44 8b 85 58 fa ff ff 	mov    -0x5a8(%rbp),%r8d
    7fb40dba6aa5:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba6aa9:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6aac:	41 33 f9             	xor    %r9d,%edi
    7fb40dba6aaf:	44 8b c7             	mov    %edi,%r8d
    7fb40dba6ab2:	44 33 c2             	xor    %edx,%r8d
    7fb40dba6ab5:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba6ab8:	4d 0f b6 8f 56 01 00 	movzbq 0x156(%r15),%r9
    7fb40dba6abf:	00 
    7fb40dba6ac0:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba6ac3:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba6ac8:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba6acb:	44 89 95 50 fa ff ff 	mov    %r10d,-0x5b0(%rbp)
    7fb40dba6ad2:	4d 0f b6 97 5b 01 00 	movzbq 0x15b(%r15),%r10
    7fb40dba6ad9:	00 
    7fb40dba6ada:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba6add:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba6ae2:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba6ae5:	33 f8                	xor    %eax,%edi
    7fb40dba6ae7:	44 89 8d 48 fa ff ff 	mov    %r9d,-0x5b8(%rbp)
    7fb40dba6aee:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba6af2:	41 d1 e1             	shl    %r9d
    7fb40dba6af5:	89 9d 40 fa ff ff    	mov    %ebx,-0x5c0(%rbp)
    7fb40dba6afb:	8b 9d 48 fa ff ff    	mov    -0x5b8(%rbp),%ebx
    7fb40dba6b01:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba6b04:	83 e3 01             	and    $0x1,%ebx
    7fb40dba6b07:	89 9d 38 fa ff ff    	mov    %ebx,-0x5c8(%rbp)
    7fb40dba6b0d:	d1 e3                	shl    %ebx
    7fb40dba6b0f:	44 89 9d 30 fa ff ff 	mov    %r11d,-0x5d0(%rbp)
    7fb40dba6b16:	44 8b 9d 38 fa ff ff 	mov    -0x5c8(%rbp),%r11d
    7fb40dba6b1d:	41 0b db             	or     %r11d,%ebx
    7fb40dba6b20:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba6b24:	41 0b db             	or     %r11d,%ebx
    7fb40dba6b27:	44 8b 9d 38 fa ff ff 	mov    -0x5c8(%rbp),%r11d
    7fb40dba6b2e:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba6b32:	41 0b db             	or     %r11d,%ebx
    7fb40dba6b35:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba6b38:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba6b3b:	44 8b 9d 48 fa ff ff 	mov    -0x5b8(%rbp),%r11d
    7fb40dba6b42:	41 33 db             	xor    %r11d,%ebx
    7fb40dba6b45:	33 fb                	xor    %ebx,%edi
    7fb40dba6b47:	41 33 fa             	xor    %r10d,%edi
    7fb40dba6b4a:	8b d8                	mov    %eax,%ebx
    7fb40dba6b4c:	33 da                	xor    %edx,%ebx
    7fb40dba6b4e:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba6b51:	41 8b da             	mov    %r10d,%ebx
    7fb40dba6b54:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba6b57:	d1 e3                	shl    %ebx
    7fb40dba6b59:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6b5c:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba6b60:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba6b64:	44 89 9d 28 fa ff ff 	mov    %r11d,-0x5d8(%rbp)
    7fb40dba6b6b:	41 d1 e3             	shl    %r11d
    7fb40dba6b6e:	89 b5 20 fa ff ff    	mov    %esi,-0x5e0(%rbp)
    7fb40dba6b74:	8b b5 28 fa ff ff    	mov    -0x5d8(%rbp),%esi
    7fb40dba6b7a:	44 0b de             	or     %esi,%r11d
    7fb40dba6b7d:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba6b80:	44 0b de             	or     %esi,%r11d
    7fb40dba6b83:	8b b5 28 fa ff ff    	mov    -0x5d8(%rbp),%esi
    7fb40dba6b89:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba6b8c:	44 0b de             	or     %esi,%r11d
    7fb40dba6b8f:	41 33 db             	xor    %r11d,%ebx
    7fb40dba6b92:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba6b95:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba6b98:	33 c8                	xor    %eax,%ecx
    7fb40dba6b9a:	33 d1                	xor    %ecx,%edx
    7fb40dba6b9c:	33 95 48 fa ff ff    	xor    -0x5b8(%rbp),%edx
    7fb40dba6ba2:	33 da                	xor    %edx,%ebx
    7fb40dba6ba4:	8b 85 c0 fa ff ff    	mov    -0x540(%rbp),%eax
    7fb40dba6baa:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba6bad:	8b 8d d0 fa ff ff    	mov    -0x530(%rbp),%ecx
    7fb40dba6bb3:	0b c1                	or     %ecx,%eax
    7fb40dba6bb5:	8b 8d b0 fa ff ff    	mov    -0x550(%rbp),%ecx
    7fb40dba6bbb:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba6bbe:	0b c1                	or     %ecx,%eax
    7fb40dba6bc0:	8b 8d a0 fa ff ff    	mov    -0x560(%rbp),%ecx
    7fb40dba6bc6:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba6bc9:	0b c1                	or     %ecx,%eax
    7fb40dba6bcb:	8b 8d 90 fa ff ff    	mov    -0x570(%rbp),%ecx
    7fb40dba6bd1:	8b c9                	mov    %ecx,%ecx
    7fb40dba6bd3:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba6bd7:	8b c0                	mov    %eax,%eax
    7fb40dba6bd9:	48 0b c8             	or     %rax,%rcx
    7fb40dba6bdc:	8b 85 80 fa ff ff    	mov    -0x580(%rbp),%eax
    7fb40dba6be2:	8b c0                	mov    %eax,%eax
    7fb40dba6be4:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba6be8:	48 0b c8             	or     %rax,%rcx
    7fb40dba6beb:	8b 85 70 fa ff ff    	mov    -0x590(%rbp),%eax
    7fb40dba6bf1:	8b c0                	mov    %eax,%eax
    7fb40dba6bf3:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba6bf7:	48 0b c8             	or     %rax,%rcx
    7fb40dba6bfa:	8b 85 60 fa ff ff    	mov    -0x5a0(%rbp),%eax
    7fb40dba6c00:	8b c0                	mov    %eax,%eax
    7fb40dba6c02:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba6c06:	48 0b c8             	or     %rax,%rcx
    7fb40dba6c09:	49 89 8f b0 02 00 00 	mov    %rcx,0x2b0(%r15)
    7fb40dba6c10:	8b 85 40 fa ff ff    	mov    -0x5c0(%rbp),%eax
    7fb40dba6c16:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba6c19:	8b 8d 50 fa ff ff    	mov    -0x5b0(%rbp),%ecx
    7fb40dba6c1f:	0b c1                	or     %ecx,%eax
    7fb40dba6c21:	8b 8d 30 fa ff ff    	mov    -0x5d0(%rbp),%ecx
    7fb40dba6c27:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba6c2a:	0b c1                	or     %ecx,%eax
    7fb40dba6c2c:	8b 8d 20 fa ff ff    	mov    -0x5e0(%rbp),%ecx
    7fb40dba6c32:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba6c35:	0b c1                	or     %ecx,%eax
    7fb40dba6c37:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba6c3a:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba6c3e:	8b c0                	mov    %eax,%eax
    7fb40dba6c40:	4c 0b c0             	or     %rax,%r8
    7fb40dba6c43:	8b ff                	mov    %edi,%edi
    7fb40dba6c45:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba6c49:	4c 0b c7             	or     %rdi,%r8
    7fb40dba6c4c:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba6c4f:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba6c53:	4d 0b c1             	or     %r9,%r8
    7fb40dba6c56:	8b db                	mov    %ebx,%ebx
    7fb40dba6c58:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba6c5c:	4c 0b c3             	or     %rbx,%r8
    7fb40dba6c5f:	4d 89 87 b8 02 00 00 	mov    %r8,0x2b8(%r15)
    7fb40dba6c66:	8b 85 f0 fa ff ff    	mov    -0x510(%rbp),%eax
    7fb40dba6c6c:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba6c71:	8b c0                	mov    %eax,%eax
    7fb40dba6c73:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba6c78:	8b 8d f0 fa ff ff    	mov    -0x510(%rbp),%ecx
    7fb40dba6c7e:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba6c81:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba6c87:	8b c9                	mov    %ecx,%ecx
    7fb40dba6c89:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba6c8e:	8b 95 f0 fa ff ff    	mov    -0x510(%rbp),%edx
    7fb40dba6c94:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba6c97:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba6c9d:	8b d2                	mov    %edx,%edx
    7fb40dba6c9f:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba6ca4:	8b 9d f0 fa ff ff    	mov    -0x510(%rbp),%ebx
    7fb40dba6caa:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba6cad:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba6cb3:	8b db                	mov    %ebx,%ebx
    7fb40dba6cb5:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba6cba:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba6cbd:	0b da                	or     %edx,%ebx
    7fb40dba6cbf:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba6cc2:	0b d9                	or     %ecx,%ebx
    7fb40dba6cc4:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba6cc7:	0b d8                	or     %eax,%ebx
    7fb40dba6cc9:	83 f3 20             	xor    $0x20,%ebx
    7fb40dba6ccc:	8b 85 00 fb ff ff    	mov    -0x500(%rbp),%eax
    7fb40dba6cd2:	33 d8                	xor    %eax,%ebx
    7fb40dba6cd4:	8b 85 10 fb ff ff    	mov    -0x4f0(%rbp),%eax
    7fb40dba6cda:	33 c3                	xor    %ebx,%eax
    7fb40dba6cdc:	8b 8d e0 fa ff ff    	mov    -0x520(%rbp),%ecx
    7fb40dba6ce2:	33 c8                	xor    %eax,%ecx
    7fb40dba6ce4:	8b 95 f0 fa ff ff    	mov    -0x510(%rbp),%edx
    7fb40dba6cea:	33 d1                	xor    %ecx,%edx
    7fb40dba6cec:	8b f0                	mov    %eax,%esi
    7fb40dba6cee:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba6cf2:	8b fb                	mov    %ebx,%edi
    7fb40dba6cf4:	48 0b f7             	or     %rdi,%rsi
    7fb40dba6cf7:	49 89 b7 10 02 00 00 	mov    %rsi,0x210(%r15)
    7fb40dba6cfe:	8b f2                	mov    %edx,%esi
    7fb40dba6d00:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba6d04:	8b f9                	mov    %ecx,%edi
    7fb40dba6d06:	48 0b f7             	or     %rdi,%rsi
    7fb40dba6d09:	49 89 b7 18 02 00 00 	mov    %rsi,0x218(%r15)
    7fb40dba6d10:	49 8b b7 b0 02 00 00 	mov    0x2b0(%r15),%rsi
    7fb40dba6d17:	49 8b bf 10 02 00 00 	mov    0x210(%r15),%rdi
    7fb40dba6d1e:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba6d21:	49 89 b7 60 03 00 00 	mov    %rsi,0x360(%r15)
    7fb40dba6d28:	49 8b b7 b8 02 00 00 	mov    0x2b8(%r15),%rsi
    7fb40dba6d2f:	49 8b bf 18 02 00 00 	mov    0x218(%r15),%rdi
    7fb40dba6d36:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba6d39:	49 89 b7 68 03 00 00 	mov    %rsi,0x368(%r15)
    7fb40dba6d40:	49 0f b6 b7 60 01 00 	movzbq 0x160(%r15),%rsi
    7fb40dba6d47:	00 
    7fb40dba6d48:	8b f6                	mov    %esi,%esi
    7fb40dba6d4a:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba6d4f:	8b fe                	mov    %esi,%edi
    7fb40dba6d51:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba6d54:	d1 e7                	shl    %edi
    7fb40dba6d56:	44 8b c6             	mov    %esi,%r8d
    7fb40dba6d59:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba6d5d:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba6d61:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba6d64:	41 d1 e1             	shl    %r9d
    7fb40dba6d67:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6d6a:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba6d6d:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba6d71:	45 0b ca             	or     %r10d,%r9d
    7fb40dba6d74:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba6d78:	45 0b c8             	or     %r8d,%r9d
    7fb40dba6d7b:	41 33 f9             	xor    %r9d,%edi
    7fb40dba6d7e:	4d 0f b6 87 65 01 00 	movzbq 0x165(%r15),%r8
    7fb40dba6d85:	00 
    7fb40dba6d86:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba6d89:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba6d8e:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba6d91:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba6d95:	41 d1 e1             	shl    %r9d
    7fb40dba6d98:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba6d9b:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba6d9f:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba6da3:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6da6:	41 d1 e3             	shl    %r11d
    7fb40dba6da9:	45 0b da             	or     %r10d,%r11d
    7fb40dba6dac:	44 89 95 18 fa ff ff 	mov    %r10d,-0x5e8(%rbp)
    7fb40dba6db3:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba6db7:	45 0b da             	or     %r10d,%r11d
    7fb40dba6dba:	44 8b 95 18 fa ff ff 	mov    -0x5e8(%rbp),%r10d
    7fb40dba6dc1:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba6dc5:	45 0b da             	or     %r10d,%r11d
    7fb40dba6dc8:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba6dcb:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba6dce:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba6dd1:	44 33 d7             	xor    %edi,%r10d
    7fb40dba6dd4:	4d 0f b6 9f 6a 01 00 	movzbq 0x16a(%r15),%r11
    7fb40dba6ddb:	00 
    7fb40dba6ddc:	45 8b db             	mov    %r11d,%r11d
    7fb40dba6ddf:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba6de4:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba6de7:	89 85 10 fa ff ff    	mov    %eax,-0x5f0(%rbp)
    7fb40dba6ded:	49 0f b6 87 6f 01 00 	movzbq 0x16f(%r15),%rax
    7fb40dba6df4:	00 
    7fb40dba6df5:	8b c0                	mov    %eax,%eax
    7fb40dba6df7:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba6dfc:	44 33 d0             	xor    %eax,%r10d
    7fb40dba6dff:	44 33 ce             	xor    %esi,%r9d
    7fb40dba6e02:	44 89 9d 08 fa ff ff 	mov    %r11d,-0x5f8(%rbp)
    7fb40dba6e09:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba6e0d:	41 d1 e3             	shl    %r11d
    7fb40dba6e10:	89 9d 00 fa ff ff    	mov    %ebx,-0x600(%rbp)
    7fb40dba6e16:	8b 9d 08 fa ff ff    	mov    -0x5f8(%rbp),%ebx
    7fb40dba6e1c:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba6e1f:	83 e3 01             	and    $0x1,%ebx
    7fb40dba6e22:	89 9d f8 f9 ff ff    	mov    %ebx,-0x608(%rbp)
    7fb40dba6e28:	d1 e3                	shl    %ebx
    7fb40dba6e2a:	89 95 f0 f9 ff ff    	mov    %edx,-0x610(%rbp)
    7fb40dba6e30:	8b 95 f8 f9 ff ff    	mov    -0x608(%rbp),%edx
    7fb40dba6e36:	0b da                	or     %edx,%ebx
    7fb40dba6e38:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba6e3b:	0b da                	or     %edx,%ebx
    7fb40dba6e3d:	8b 95 f8 f9 ff ff    	mov    -0x608(%rbp),%edx
    7fb40dba6e43:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba6e46:	0b da                	or     %edx,%ebx
    7fb40dba6e48:	44 33 db             	xor    %ebx,%r11d
    7fb40dba6e4b:	41 8b d3             	mov    %r11d,%edx
    7fb40dba6e4e:	8b 9d 08 fa ff ff    	mov    -0x5f8(%rbp),%ebx
    7fb40dba6e54:	33 d3                	xor    %ebx,%edx
    7fb40dba6e56:	44 33 ca             	xor    %edx,%r9d
    7fb40dba6e59:	44 33 c8             	xor    %eax,%r9d
    7fb40dba6e5c:	8b d6                	mov    %esi,%edx
    7fb40dba6e5e:	41 33 d0             	xor    %r8d,%edx
    7fb40dba6e61:	44 33 da             	xor    %edx,%r11d
    7fb40dba6e64:	8b d0                	mov    %eax,%edx
    7fb40dba6e66:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba6e69:	d1 e2                	shl    %edx
    7fb40dba6e6b:	8b d8                	mov    %eax,%ebx
    7fb40dba6e6d:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba6e70:	83 e3 01             	and    $0x1,%ebx
    7fb40dba6e73:	89 9d e8 f9 ff ff    	mov    %ebx,-0x618(%rbp)
    7fb40dba6e79:	d1 e3                	shl    %ebx
    7fb40dba6e7b:	89 8d e0 f9 ff ff    	mov    %ecx,-0x620(%rbp)
    7fb40dba6e81:	8b 8d e8 f9 ff ff    	mov    -0x618(%rbp),%ecx
    7fb40dba6e87:	0b d9                	or     %ecx,%ebx
    7fb40dba6e89:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba6e8c:	0b d9                	or     %ecx,%ebx
    7fb40dba6e8e:	8b 8d e8 f9 ff ff    	mov    -0x618(%rbp),%ecx
    7fb40dba6e94:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba6e97:	0b d9                	or     %ecx,%ebx
    7fb40dba6e99:	33 d3                	xor    %ebx,%edx
    7fb40dba6e9b:	33 c2                	xor    %edx,%eax
    7fb40dba6e9d:	44 33 d8             	xor    %eax,%r11d
    7fb40dba6ea0:	33 fe                	xor    %esi,%edi
    7fb40dba6ea2:	44 33 c7             	xor    %edi,%r8d
    7fb40dba6ea5:	44 33 85 08 fa ff ff 	xor    -0x5f8(%rbp),%r8d
    7fb40dba6eac:	41 33 d0             	xor    %r8d,%edx
    7fb40dba6eaf:	49 0f b6 87 64 01 00 	movzbq 0x164(%r15),%rax
    7fb40dba6eb6:	00 
    7fb40dba6eb7:	8b c0                	mov    %eax,%eax
    7fb40dba6eb9:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba6ebe:	8b c8                	mov    %eax,%ecx
    7fb40dba6ec0:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba6ec3:	d1 e1                	shl    %ecx
    7fb40dba6ec5:	8b d8                	mov    %eax,%ebx
    7fb40dba6ec7:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba6eca:	83 e3 01             	and    $0x1,%ebx
    7fb40dba6ecd:	8b f3                	mov    %ebx,%esi
    7fb40dba6ecf:	d1 e6                	shl    %esi
    7fb40dba6ed1:	0b f3                	or     %ebx,%esi
    7fb40dba6ed3:	8b fb                	mov    %ebx,%edi
    7fb40dba6ed5:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba6ed8:	0b f7                	or     %edi,%esi
    7fb40dba6eda:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba6edd:	0b f3                	or     %ebx,%esi
    7fb40dba6edf:	33 ce                	xor    %esi,%ecx
    7fb40dba6ee1:	49 0f b6 9f 69 01 00 	movzbq 0x169(%r15),%rbx
    7fb40dba6ee8:	00 
    7fb40dba6ee9:	8b db                	mov    %ebx,%ebx
    7fb40dba6eeb:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba6ef0:	8b f3                	mov    %ebx,%esi
    7fb40dba6ef2:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba6ef5:	d1 e6                	shl    %esi
    7fb40dba6ef7:	8b fb                	mov    %ebx,%edi
    7fb40dba6ef9:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba6efc:	83 e7 01             	and    $0x1,%edi
    7fb40dba6eff:	44 8b c7             	mov    %edi,%r8d
    7fb40dba6f02:	41 d1 e0             	shl    %r8d
    7fb40dba6f05:	44 0b c7             	or     %edi,%r8d
    7fb40dba6f08:	89 bd d8 f9 ff ff    	mov    %edi,-0x628(%rbp)
    7fb40dba6f0e:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba6f11:	44 0b c7             	or     %edi,%r8d
    7fb40dba6f14:	8b bd d8 f9 ff ff    	mov    -0x628(%rbp),%edi
    7fb40dba6f1a:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba6f1d:	44 0b c7             	or     %edi,%r8d
    7fb40dba6f20:	41 33 f0             	xor    %r8d,%esi
    7fb40dba6f23:	8b fe                	mov    %esi,%edi
    7fb40dba6f25:	33 fb                	xor    %ebx,%edi
    7fb40dba6f27:	33 f9                	xor    %ecx,%edi
    7fb40dba6f29:	4d 0f b6 87 6e 01 00 	movzbq 0x16e(%r15),%r8
    7fb40dba6f30:	00 
    7fb40dba6f31:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba6f34:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba6f39:	41 33 f8             	xor    %r8d,%edi
    7fb40dba6f3c:	44 89 95 d0 f9 ff ff 	mov    %r10d,-0x630(%rbp)
    7fb40dba6f43:	4d 0f b6 97 63 01 00 	movzbq 0x163(%r15),%r10
    7fb40dba6f4a:	00 
    7fb40dba6f4b:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba6f4e:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba6f53:	41 33 fa             	xor    %r10d,%edi
    7fb40dba6f56:	33 f0                	xor    %eax,%esi
    7fb40dba6f58:	44 89 85 c8 f9 ff ff 	mov    %r8d,-0x638(%rbp)
    7fb40dba6f5f:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba6f63:	41 d1 e0             	shl    %r8d
    7fb40dba6f66:	44 89 8d c0 f9 ff ff 	mov    %r9d,-0x640(%rbp)
    7fb40dba6f6d:	44 8b 8d c8 f9 ff ff 	mov    -0x638(%rbp),%r9d
    7fb40dba6f74:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba6f78:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba6f7c:	44 89 8d b8 f9 ff ff 	mov    %r9d,-0x648(%rbp)
    7fb40dba6f83:	41 d1 e1             	shl    %r9d
    7fb40dba6f86:	44 89 9d b0 f9 ff ff 	mov    %r11d,-0x650(%rbp)
    7fb40dba6f8d:	44 8b 9d b8 f9 ff ff 	mov    -0x648(%rbp),%r11d
    7fb40dba6f94:	45 0b cb             	or     %r11d,%r9d
    7fb40dba6f97:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba6f9b:	45 0b cb             	or     %r11d,%r9d
    7fb40dba6f9e:	44 8b 9d b8 f9 ff ff 	mov    -0x648(%rbp),%r11d
    7fb40dba6fa5:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba6fa9:	45 0b cb             	or     %r11d,%r9d
    7fb40dba6fac:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba6faf:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba6fb2:	44 8b 9d c8 f9 ff ff 	mov    -0x638(%rbp),%r11d
    7fb40dba6fb9:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba6fbc:	41 33 f1             	xor    %r9d,%esi
    7fb40dba6fbf:	41 33 f2             	xor    %r10d,%esi
    7fb40dba6fc2:	44 8b c8             	mov    %eax,%r9d
    7fb40dba6fc5:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba6fc8:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba6fcb:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba6fce:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba6fd2:	41 d1 e1             	shl    %r9d
    7fb40dba6fd5:	45 8b da             	mov    %r10d,%r11d
    7fb40dba6fd8:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba6fdc:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba6fe0:	44 89 9d a8 f9 ff ff 	mov    %r11d,-0x658(%rbp)
    7fb40dba6fe7:	41 d1 e3             	shl    %r11d
    7fb40dba6fea:	89 95 a0 f9 ff ff    	mov    %edx,-0x660(%rbp)
    7fb40dba6ff0:	8b 95 a8 f9 ff ff    	mov    -0x658(%rbp),%edx
    7fb40dba6ff6:	44 0b da             	or     %edx,%r11d
    7fb40dba6ff9:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba6ffc:	44 0b da             	or     %edx,%r11d
    7fb40dba6fff:	8b 95 a8 f9 ff ff    	mov    -0x658(%rbp),%edx
    7fb40dba7005:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba7008:	44 0b da             	or     %edx,%r11d
    7fb40dba700b:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba700e:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba7011:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba7014:	33 c8                	xor    %eax,%ecx
    7fb40dba7016:	33 d9                	xor    %ecx,%ebx
    7fb40dba7018:	33 9d c8 f9 ff ff    	xor    -0x638(%rbp),%ebx
    7fb40dba701e:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba7021:	49 0f b6 87 68 01 00 	movzbq 0x168(%r15),%rax
    7fb40dba7028:	00 
    7fb40dba7029:	8b c0                	mov    %eax,%eax
    7fb40dba702b:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7030:	8b c8                	mov    %eax,%ecx
    7fb40dba7032:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba7035:	d1 e1                	shl    %ecx
    7fb40dba7037:	8b d0                	mov    %eax,%edx
    7fb40dba7039:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba703c:	83 e2 01             	and    $0x1,%edx
    7fb40dba703f:	8b da                	mov    %edx,%ebx
    7fb40dba7041:	d1 e3                	shl    %ebx
    7fb40dba7043:	0b da                	or     %edx,%ebx
    7fb40dba7045:	44 8b d2             	mov    %edx,%r10d
    7fb40dba7048:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba704c:	41 0b da             	or     %r10d,%ebx
    7fb40dba704f:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba7052:	0b da                	or     %edx,%ebx
    7fb40dba7054:	33 cb                	xor    %ebx,%ecx
    7fb40dba7056:	49 0f b6 97 6d 01 00 	movzbq 0x16d(%r15),%rdx
    7fb40dba705d:	00 
    7fb40dba705e:	8b d2                	mov    %edx,%edx
    7fb40dba7060:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba7065:	8b da                	mov    %edx,%ebx
    7fb40dba7067:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba706a:	d1 e3                	shl    %ebx
    7fb40dba706c:	44 8b d2             	mov    %edx,%r10d
    7fb40dba706f:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba7073:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba7077:	45 8b da             	mov    %r10d,%r11d
    7fb40dba707a:	41 d1 e3             	shl    %r11d
    7fb40dba707d:	45 0b da             	or     %r10d,%r11d
    7fb40dba7080:	44 89 95 98 f9 ff ff 	mov    %r10d,-0x668(%rbp)
    7fb40dba7087:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba708b:	45 0b da             	or     %r10d,%r11d
    7fb40dba708e:	44 8b 95 98 f9 ff ff 	mov    -0x668(%rbp),%r10d
    7fb40dba7095:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba7099:	45 0b da             	or     %r10d,%r11d
    7fb40dba709c:	41 33 db             	xor    %r11d,%ebx
    7fb40dba709f:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba70a2:	44 33 d2             	xor    %edx,%r10d
    7fb40dba70a5:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba70a8:	4d 0f b6 9f 62 01 00 	movzbq 0x162(%r15),%r11
    7fb40dba70af:	00 
    7fb40dba70b0:	45 8b db             	mov    %r11d,%r11d
    7fb40dba70b3:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba70b8:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba70bb:	89 bd 90 f9 ff ff    	mov    %edi,-0x670(%rbp)
    7fb40dba70c1:	49 0f b6 bf 67 01 00 	movzbq 0x167(%r15),%rdi
    7fb40dba70c8:	00 
    7fb40dba70c9:	8b ff                	mov    %edi,%edi
    7fb40dba70cb:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba70d0:	44 33 d7             	xor    %edi,%r10d
    7fb40dba70d3:	33 d8                	xor    %eax,%ebx
    7fb40dba70d5:	44 89 9d 88 f9 ff ff 	mov    %r11d,-0x678(%rbp)
    7fb40dba70dc:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba70e0:	41 d1 e3             	shl    %r11d
    7fb40dba70e3:	89 b5 80 f9 ff ff    	mov    %esi,-0x680(%rbp)
    7fb40dba70e9:	8b b5 88 f9 ff ff    	mov    -0x678(%rbp),%esi
    7fb40dba70ef:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba70f2:	83 e6 01             	and    $0x1,%esi
    7fb40dba70f5:	89 b5 78 f9 ff ff    	mov    %esi,-0x688(%rbp)
    7fb40dba70fb:	d1 e6                	shl    %esi
    7fb40dba70fd:	44 89 85 70 f9 ff ff 	mov    %r8d,-0x690(%rbp)
    7fb40dba7104:	44 8b 85 78 f9 ff ff 	mov    -0x688(%rbp),%r8d
    7fb40dba710b:	41 0b f0             	or     %r8d,%esi
    7fb40dba710e:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba7112:	41 0b f0             	or     %r8d,%esi
    7fb40dba7115:	44 8b 85 78 f9 ff ff 	mov    -0x688(%rbp),%r8d
    7fb40dba711c:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba7120:	41 0b f0             	or     %r8d,%esi
    7fb40dba7123:	44 33 de             	xor    %esi,%r11d
    7fb40dba7126:	41 8b f3             	mov    %r11d,%esi
    7fb40dba7129:	44 8b 85 88 f9 ff ff 	mov    -0x678(%rbp),%r8d
    7fb40dba7130:	41 33 f0             	xor    %r8d,%esi
    7fb40dba7133:	33 de                	xor    %esi,%ebx
    7fb40dba7135:	33 df                	xor    %edi,%ebx
    7fb40dba7137:	8b f0                	mov    %eax,%esi
    7fb40dba7139:	33 f2                	xor    %edx,%esi
    7fb40dba713b:	44 33 de             	xor    %esi,%r11d
    7fb40dba713e:	8b f7                	mov    %edi,%esi
    7fb40dba7140:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba7143:	d1 e6                	shl    %esi
    7fb40dba7145:	44 8b c7             	mov    %edi,%r8d
    7fb40dba7148:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba714c:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba7150:	44 89 85 68 f9 ff ff 	mov    %r8d,-0x698(%rbp)
    7fb40dba7157:	41 d1 e0             	shl    %r8d
    7fb40dba715a:	44 89 8d 60 f9 ff ff 	mov    %r9d,-0x6a0(%rbp)
    7fb40dba7161:	44 8b 8d 68 f9 ff ff 	mov    -0x698(%rbp),%r9d
    7fb40dba7168:	45 0b c1             	or     %r9d,%r8d
    7fb40dba716b:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba716f:	45 0b c1             	or     %r9d,%r8d
    7fb40dba7172:	44 8b 8d 68 f9 ff ff 	mov    -0x698(%rbp),%r9d
    7fb40dba7179:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba717d:	45 0b c1             	or     %r9d,%r8d
    7fb40dba7180:	41 33 f0             	xor    %r8d,%esi
    7fb40dba7183:	33 fe                	xor    %esi,%edi
    7fb40dba7185:	44 33 df             	xor    %edi,%r11d
    7fb40dba7188:	33 c8                	xor    %eax,%ecx
    7fb40dba718a:	33 d1                	xor    %ecx,%edx
    7fb40dba718c:	33 95 88 f9 ff ff    	xor    -0x678(%rbp),%edx
    7fb40dba7192:	33 f2                	xor    %edx,%esi
    7fb40dba7194:	49 0f b6 87 6c 01 00 	movzbq 0x16c(%r15),%rax
    7fb40dba719b:	00 
    7fb40dba719c:	8b c0                	mov    %eax,%eax
    7fb40dba719e:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba71a3:	8b c8                	mov    %eax,%ecx
    7fb40dba71a5:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba71a8:	d1 e1                	shl    %ecx
    7fb40dba71aa:	8b d0                	mov    %eax,%edx
    7fb40dba71ac:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba71af:	83 e2 01             	and    $0x1,%edx
    7fb40dba71b2:	8b fa                	mov    %edx,%edi
    7fb40dba71b4:	d1 e7                	shl    %edi
    7fb40dba71b6:	0b fa                	or     %edx,%edi
    7fb40dba71b8:	44 8b c2             	mov    %edx,%r8d
    7fb40dba71bb:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba71bf:	41 0b f8             	or     %r8d,%edi
    7fb40dba71c2:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba71c5:	0b fa                	or     %edx,%edi
    7fb40dba71c7:	33 cf                	xor    %edi,%ecx
    7fb40dba71c9:	49 0f b6 97 61 01 00 	movzbq 0x161(%r15),%rdx
    7fb40dba71d0:	00 
    7fb40dba71d1:	8b d2                	mov    %edx,%edx
    7fb40dba71d3:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba71d8:	8b fa                	mov    %edx,%edi
    7fb40dba71da:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba71dd:	d1 e7                	shl    %edi
    7fb40dba71df:	44 8b c2             	mov    %edx,%r8d
    7fb40dba71e2:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba71e6:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba71ea:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba71ed:	41 d1 e1             	shl    %r9d
    7fb40dba71f0:	45 0b c8             	or     %r8d,%r9d
    7fb40dba71f3:	44 89 85 58 f9 ff ff 	mov    %r8d,-0x6a8(%rbp)
    7fb40dba71fa:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba71fe:	45 0b c8             	or     %r8d,%r9d
    7fb40dba7201:	44 8b 85 58 f9 ff ff 	mov    -0x6a8(%rbp),%r8d
    7fb40dba7208:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba720c:	45 0b c8             	or     %r8d,%r9d
    7fb40dba720f:	41 33 f9             	xor    %r9d,%edi
    7fb40dba7212:	44 8b c7             	mov    %edi,%r8d
    7fb40dba7215:	44 33 c2             	xor    %edx,%r8d
    7fb40dba7218:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba721b:	4d 0f b6 8f 66 01 00 	movzbq 0x166(%r15),%r9
    7fb40dba7222:	00 
    7fb40dba7223:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba7226:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba722b:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba722e:	44 89 95 50 f9 ff ff 	mov    %r10d,-0x6b0(%rbp)
    7fb40dba7235:	4d 0f b6 97 6b 01 00 	movzbq 0x16b(%r15),%r10
    7fb40dba723c:	00 
    7fb40dba723d:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba7240:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba7245:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba7248:	33 f8                	xor    %eax,%edi
    7fb40dba724a:	44 89 8d 48 f9 ff ff 	mov    %r9d,-0x6b8(%rbp)
    7fb40dba7251:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba7255:	41 d1 e1             	shl    %r9d
    7fb40dba7258:	89 9d 40 f9 ff ff    	mov    %ebx,-0x6c0(%rbp)
    7fb40dba725e:	8b 9d 48 f9 ff ff    	mov    -0x6b8(%rbp),%ebx
    7fb40dba7264:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba7267:	83 e3 01             	and    $0x1,%ebx
    7fb40dba726a:	89 9d 38 f9 ff ff    	mov    %ebx,-0x6c8(%rbp)
    7fb40dba7270:	d1 e3                	shl    %ebx
    7fb40dba7272:	44 89 9d 30 f9 ff ff 	mov    %r11d,-0x6d0(%rbp)
    7fb40dba7279:	44 8b 9d 38 f9 ff ff 	mov    -0x6c8(%rbp),%r11d
    7fb40dba7280:	41 0b db             	or     %r11d,%ebx
    7fb40dba7283:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba7287:	41 0b db             	or     %r11d,%ebx
    7fb40dba728a:	44 8b 9d 38 f9 ff ff 	mov    -0x6c8(%rbp),%r11d
    7fb40dba7291:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba7295:	41 0b db             	or     %r11d,%ebx
    7fb40dba7298:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba729b:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba729e:	44 8b 9d 48 f9 ff ff 	mov    -0x6b8(%rbp),%r11d
    7fb40dba72a5:	41 33 db             	xor    %r11d,%ebx
    7fb40dba72a8:	33 fb                	xor    %ebx,%edi
    7fb40dba72aa:	41 33 fa             	xor    %r10d,%edi
    7fb40dba72ad:	8b d8                	mov    %eax,%ebx
    7fb40dba72af:	33 da                	xor    %edx,%ebx
    7fb40dba72b1:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba72b4:	41 8b da             	mov    %r10d,%ebx
    7fb40dba72b7:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba72ba:	d1 e3                	shl    %ebx
    7fb40dba72bc:	45 8b da             	mov    %r10d,%r11d
    7fb40dba72bf:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba72c3:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba72c7:	44 89 9d 28 f9 ff ff 	mov    %r11d,-0x6d8(%rbp)
    7fb40dba72ce:	41 d1 e3             	shl    %r11d
    7fb40dba72d1:	89 b5 20 f9 ff ff    	mov    %esi,-0x6e0(%rbp)
    7fb40dba72d7:	8b b5 28 f9 ff ff    	mov    -0x6d8(%rbp),%esi
    7fb40dba72dd:	44 0b de             	or     %esi,%r11d
    7fb40dba72e0:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba72e3:	44 0b de             	or     %esi,%r11d
    7fb40dba72e6:	8b b5 28 f9 ff ff    	mov    -0x6d8(%rbp),%esi
    7fb40dba72ec:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba72ef:	44 0b de             	or     %esi,%r11d
    7fb40dba72f2:	41 33 db             	xor    %r11d,%ebx
    7fb40dba72f5:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba72f8:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba72fb:	33 c8                	xor    %eax,%ecx
    7fb40dba72fd:	33 d1                	xor    %ecx,%edx
    7fb40dba72ff:	33 95 48 f9 ff ff    	xor    -0x6b8(%rbp),%edx
    7fb40dba7305:	33 da                	xor    %edx,%ebx
    7fb40dba7307:	8b 85 c0 f9 ff ff    	mov    -0x640(%rbp),%eax
    7fb40dba730d:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba7310:	8b 8d d0 f9 ff ff    	mov    -0x630(%rbp),%ecx
    7fb40dba7316:	0b c1                	or     %ecx,%eax
    7fb40dba7318:	8b 8d b0 f9 ff ff    	mov    -0x650(%rbp),%ecx
    7fb40dba731e:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba7321:	0b c1                	or     %ecx,%eax
    7fb40dba7323:	8b 8d a0 f9 ff ff    	mov    -0x660(%rbp),%ecx
    7fb40dba7329:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba732c:	0b c1                	or     %ecx,%eax
    7fb40dba732e:	8b 8d 90 f9 ff ff    	mov    -0x670(%rbp),%ecx
    7fb40dba7334:	8b c9                	mov    %ecx,%ecx
    7fb40dba7336:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba733a:	8b c0                	mov    %eax,%eax
    7fb40dba733c:	48 0b c8             	or     %rax,%rcx
    7fb40dba733f:	8b 85 80 f9 ff ff    	mov    -0x680(%rbp),%eax
    7fb40dba7345:	8b c0                	mov    %eax,%eax
    7fb40dba7347:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba734b:	48 0b c8             	or     %rax,%rcx
    7fb40dba734e:	8b 85 70 f9 ff ff    	mov    -0x690(%rbp),%eax
    7fb40dba7354:	8b c0                	mov    %eax,%eax
    7fb40dba7356:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba735a:	48 0b c8             	or     %rax,%rcx
    7fb40dba735d:	8b 85 60 f9 ff ff    	mov    -0x6a0(%rbp),%eax
    7fb40dba7363:	8b c0                	mov    %eax,%eax
    7fb40dba7365:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba7369:	48 0b c8             	or     %rax,%rcx
    7fb40dba736c:	49 89 8f c0 02 00 00 	mov    %rcx,0x2c0(%r15)
    7fb40dba7373:	8b 85 40 f9 ff ff    	mov    -0x6c0(%rbp),%eax
    7fb40dba7379:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba737c:	8b 8d 50 f9 ff ff    	mov    -0x6b0(%rbp),%ecx
    7fb40dba7382:	0b c1                	or     %ecx,%eax
    7fb40dba7384:	8b 8d 30 f9 ff ff    	mov    -0x6d0(%rbp),%ecx
    7fb40dba738a:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba738d:	0b c1                	or     %ecx,%eax
    7fb40dba738f:	8b 8d 20 f9 ff ff    	mov    -0x6e0(%rbp),%ecx
    7fb40dba7395:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba7398:	0b c1                	or     %ecx,%eax
    7fb40dba739a:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba739d:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba73a1:	8b c0                	mov    %eax,%eax
    7fb40dba73a3:	4c 0b c0             	or     %rax,%r8
    7fb40dba73a6:	8b ff                	mov    %edi,%edi
    7fb40dba73a8:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba73ac:	4c 0b c7             	or     %rdi,%r8
    7fb40dba73af:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba73b2:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba73b6:	4d 0b c1             	or     %r9,%r8
    7fb40dba73b9:	8b db                	mov    %ebx,%ebx
    7fb40dba73bb:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba73bf:	4c 0b c3             	or     %rbx,%r8
    7fb40dba73c2:	4d 89 87 c8 02 00 00 	mov    %r8,0x2c8(%r15)
    7fb40dba73c9:	8b 85 f0 f9 ff ff    	mov    -0x610(%rbp),%eax
    7fb40dba73cf:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba73d4:	8b c0                	mov    %eax,%eax
    7fb40dba73d6:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba73db:	8b 8d f0 f9 ff ff    	mov    -0x610(%rbp),%ecx
    7fb40dba73e1:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba73e4:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba73ea:	8b c9                	mov    %ecx,%ecx
    7fb40dba73ec:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba73f1:	8b 95 f0 f9 ff ff    	mov    -0x610(%rbp),%edx
    7fb40dba73f7:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba73fa:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba7400:	8b d2                	mov    %edx,%edx
    7fb40dba7402:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba7407:	8b 9d f0 f9 ff ff    	mov    -0x610(%rbp),%ebx
    7fb40dba740d:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba7410:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba7416:	8b db                	mov    %ebx,%ebx
    7fb40dba7418:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba741d:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba7420:	0b da                	or     %edx,%ebx
    7fb40dba7422:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba7425:	0b d9                	or     %ecx,%ebx
    7fb40dba7427:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba742a:	0b d8                	or     %eax,%ebx
    7fb40dba742c:	83 f3 40             	xor    $0x40,%ebx
    7fb40dba742f:	8b 85 00 fa ff ff    	mov    -0x600(%rbp),%eax
    7fb40dba7435:	33 d8                	xor    %eax,%ebx
    7fb40dba7437:	8b 85 10 fa ff ff    	mov    -0x5f0(%rbp),%eax
    7fb40dba743d:	33 c3                	xor    %ebx,%eax
    7fb40dba743f:	8b 8d e0 f9 ff ff    	mov    -0x620(%rbp),%ecx
    7fb40dba7445:	33 c8                	xor    %eax,%ecx
    7fb40dba7447:	8b 95 f0 f9 ff ff    	mov    -0x610(%rbp),%edx
    7fb40dba744d:	33 d1                	xor    %ecx,%edx
    7fb40dba744f:	8b f0                	mov    %eax,%esi
    7fb40dba7451:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba7455:	8b fb                	mov    %ebx,%edi
    7fb40dba7457:	48 0b f7             	or     %rdi,%rsi
    7fb40dba745a:	49 89 b7 20 02 00 00 	mov    %rsi,0x220(%r15)
    7fb40dba7461:	8b f2                	mov    %edx,%esi
    7fb40dba7463:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba7467:	8b f9                	mov    %ecx,%edi
    7fb40dba7469:	48 0b f7             	or     %rdi,%rsi
    7fb40dba746c:	49 89 b7 28 02 00 00 	mov    %rsi,0x228(%r15)
    7fb40dba7473:	49 8b b7 c0 02 00 00 	mov    0x2c0(%r15),%rsi
    7fb40dba747a:	49 8b bf 20 02 00 00 	mov    0x220(%r15),%rdi
    7fb40dba7481:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba7484:	49 89 b7 70 03 00 00 	mov    %rsi,0x370(%r15)
    7fb40dba748b:	49 8b b7 c8 02 00 00 	mov    0x2c8(%r15),%rsi
    7fb40dba7492:	49 8b bf 28 02 00 00 	mov    0x228(%r15),%rdi
    7fb40dba7499:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba749c:	49 89 b7 78 03 00 00 	mov    %rsi,0x378(%r15)
    7fb40dba74a3:	49 0f b6 b7 70 01 00 	movzbq 0x170(%r15),%rsi
    7fb40dba74aa:	00 
    7fb40dba74ab:	8b f6                	mov    %esi,%esi
    7fb40dba74ad:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba74b2:	8b fe                	mov    %esi,%edi
    7fb40dba74b4:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba74b7:	d1 e7                	shl    %edi
    7fb40dba74b9:	44 8b c6             	mov    %esi,%r8d
    7fb40dba74bc:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba74c0:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba74c4:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba74c7:	41 d1 e1             	shl    %r9d
    7fb40dba74ca:	45 0b c8             	or     %r8d,%r9d
    7fb40dba74cd:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba74d0:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba74d4:	45 0b ca             	or     %r10d,%r9d
    7fb40dba74d7:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba74db:	45 0b c8             	or     %r8d,%r9d
    7fb40dba74de:	41 33 f9             	xor    %r9d,%edi
    7fb40dba74e1:	4d 0f b6 87 75 01 00 	movzbq 0x175(%r15),%r8
    7fb40dba74e8:	00 
    7fb40dba74e9:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba74ec:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba74f1:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba74f4:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba74f8:	41 d1 e1             	shl    %r9d
    7fb40dba74fb:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba74fe:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba7502:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba7506:	45 8b da             	mov    %r10d,%r11d
    7fb40dba7509:	41 d1 e3             	shl    %r11d
    7fb40dba750c:	45 0b da             	or     %r10d,%r11d
    7fb40dba750f:	44 89 95 18 f9 ff ff 	mov    %r10d,-0x6e8(%rbp)
    7fb40dba7516:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba751a:	45 0b da             	or     %r10d,%r11d
    7fb40dba751d:	44 8b 95 18 f9 ff ff 	mov    -0x6e8(%rbp),%r10d
    7fb40dba7524:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba7528:	45 0b da             	or     %r10d,%r11d
    7fb40dba752b:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba752e:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba7531:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba7534:	44 33 d7             	xor    %edi,%r10d
    7fb40dba7537:	4d 0f b6 9f 7a 01 00 	movzbq 0x17a(%r15),%r11
    7fb40dba753e:	00 
    7fb40dba753f:	45 8b db             	mov    %r11d,%r11d
    7fb40dba7542:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba7547:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba754a:	89 85 10 f9 ff ff    	mov    %eax,-0x6f0(%rbp)
    7fb40dba7550:	49 0f b6 87 7f 01 00 	movzbq 0x17f(%r15),%rax
    7fb40dba7557:	00 
    7fb40dba7558:	8b c0                	mov    %eax,%eax
    7fb40dba755a:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba755f:	44 33 d0             	xor    %eax,%r10d
    7fb40dba7562:	44 33 ce             	xor    %esi,%r9d
    7fb40dba7565:	44 89 9d 08 f9 ff ff 	mov    %r11d,-0x6f8(%rbp)
    7fb40dba756c:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba7570:	41 d1 e3             	shl    %r11d
    7fb40dba7573:	89 9d 00 f9 ff ff    	mov    %ebx,-0x700(%rbp)
    7fb40dba7579:	8b 9d 08 f9 ff ff    	mov    -0x6f8(%rbp),%ebx
    7fb40dba757f:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba7582:	83 e3 01             	and    $0x1,%ebx
    7fb40dba7585:	89 9d f8 f8 ff ff    	mov    %ebx,-0x708(%rbp)
    7fb40dba758b:	d1 e3                	shl    %ebx
    7fb40dba758d:	89 95 f0 f8 ff ff    	mov    %edx,-0x710(%rbp)
    7fb40dba7593:	8b 95 f8 f8 ff ff    	mov    -0x708(%rbp),%edx
    7fb40dba7599:	0b da                	or     %edx,%ebx
    7fb40dba759b:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba759e:	0b da                	or     %edx,%ebx
    7fb40dba75a0:	8b 95 f8 f8 ff ff    	mov    -0x708(%rbp),%edx
    7fb40dba75a6:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba75a9:	0b da                	or     %edx,%ebx
    7fb40dba75ab:	44 33 db             	xor    %ebx,%r11d
    7fb40dba75ae:	41 8b d3             	mov    %r11d,%edx
    7fb40dba75b1:	8b 9d 08 f9 ff ff    	mov    -0x6f8(%rbp),%ebx
    7fb40dba75b7:	33 d3                	xor    %ebx,%edx
    7fb40dba75b9:	44 33 ca             	xor    %edx,%r9d
    7fb40dba75bc:	44 33 c8             	xor    %eax,%r9d
    7fb40dba75bf:	8b d6                	mov    %esi,%edx
    7fb40dba75c1:	41 33 d0             	xor    %r8d,%edx
    7fb40dba75c4:	44 33 da             	xor    %edx,%r11d
    7fb40dba75c7:	8b d0                	mov    %eax,%edx
    7fb40dba75c9:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba75cc:	d1 e2                	shl    %edx
    7fb40dba75ce:	8b d8                	mov    %eax,%ebx
    7fb40dba75d0:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba75d3:	83 e3 01             	and    $0x1,%ebx
    7fb40dba75d6:	89 9d e8 f8 ff ff    	mov    %ebx,-0x718(%rbp)
    7fb40dba75dc:	d1 e3                	shl    %ebx
    7fb40dba75de:	89 8d e0 f8 ff ff    	mov    %ecx,-0x720(%rbp)
    7fb40dba75e4:	8b 8d e8 f8 ff ff    	mov    -0x718(%rbp),%ecx
    7fb40dba75ea:	0b d9                	or     %ecx,%ebx
    7fb40dba75ec:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba75ef:	0b d9                	or     %ecx,%ebx
    7fb40dba75f1:	8b 8d e8 f8 ff ff    	mov    -0x718(%rbp),%ecx
    7fb40dba75f7:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba75fa:	0b d9                	or     %ecx,%ebx
    7fb40dba75fc:	33 d3                	xor    %ebx,%edx
    7fb40dba75fe:	33 c2                	xor    %edx,%eax
    7fb40dba7600:	44 33 d8             	xor    %eax,%r11d
    7fb40dba7603:	33 fe                	xor    %esi,%edi
    7fb40dba7605:	44 33 c7             	xor    %edi,%r8d
    7fb40dba7608:	44 33 85 08 f9 ff ff 	xor    -0x6f8(%rbp),%r8d
    7fb40dba760f:	41 33 d0             	xor    %r8d,%edx
    7fb40dba7612:	49 0f b6 87 74 01 00 	movzbq 0x174(%r15),%rax
    7fb40dba7619:	00 
    7fb40dba761a:	8b c0                	mov    %eax,%eax
    7fb40dba761c:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7621:	8b c8                	mov    %eax,%ecx
    7fb40dba7623:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba7626:	d1 e1                	shl    %ecx
    7fb40dba7628:	8b d8                	mov    %eax,%ebx
    7fb40dba762a:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba762d:	83 e3 01             	and    $0x1,%ebx
    7fb40dba7630:	8b f3                	mov    %ebx,%esi
    7fb40dba7632:	d1 e6                	shl    %esi
    7fb40dba7634:	0b f3                	or     %ebx,%esi
    7fb40dba7636:	8b fb                	mov    %ebx,%edi
    7fb40dba7638:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba763b:	0b f7                	or     %edi,%esi
    7fb40dba763d:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba7640:	0b f3                	or     %ebx,%esi
    7fb40dba7642:	33 ce                	xor    %esi,%ecx
    7fb40dba7644:	49 0f b6 9f 79 01 00 	movzbq 0x179(%r15),%rbx
    7fb40dba764b:	00 
    7fb40dba764c:	8b db                	mov    %ebx,%ebx
    7fb40dba764e:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba7653:	8b f3                	mov    %ebx,%esi
    7fb40dba7655:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba7658:	d1 e6                	shl    %esi
    7fb40dba765a:	8b fb                	mov    %ebx,%edi
    7fb40dba765c:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba765f:	83 e7 01             	and    $0x1,%edi
    7fb40dba7662:	44 8b c7             	mov    %edi,%r8d
    7fb40dba7665:	41 d1 e0             	shl    %r8d
    7fb40dba7668:	44 0b c7             	or     %edi,%r8d
    7fb40dba766b:	89 bd d8 f8 ff ff    	mov    %edi,-0x728(%rbp)
    7fb40dba7671:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba7674:	44 0b c7             	or     %edi,%r8d
    7fb40dba7677:	8b bd d8 f8 ff ff    	mov    -0x728(%rbp),%edi
    7fb40dba767d:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba7680:	44 0b c7             	or     %edi,%r8d
    7fb40dba7683:	41 33 f0             	xor    %r8d,%esi
    7fb40dba7686:	8b fe                	mov    %esi,%edi
    7fb40dba7688:	33 fb                	xor    %ebx,%edi
    7fb40dba768a:	33 f9                	xor    %ecx,%edi
    7fb40dba768c:	4d 0f b6 87 7e 01 00 	movzbq 0x17e(%r15),%r8
    7fb40dba7693:	00 
    7fb40dba7694:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba7697:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba769c:	41 33 f8             	xor    %r8d,%edi
    7fb40dba769f:	44 89 95 d0 f8 ff ff 	mov    %r10d,-0x730(%rbp)
    7fb40dba76a6:	4d 0f b6 97 73 01 00 	movzbq 0x173(%r15),%r10
    7fb40dba76ad:	00 
    7fb40dba76ae:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba76b1:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba76b6:	41 33 fa             	xor    %r10d,%edi
    7fb40dba76b9:	33 f0                	xor    %eax,%esi
    7fb40dba76bb:	44 89 85 c8 f8 ff ff 	mov    %r8d,-0x738(%rbp)
    7fb40dba76c2:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba76c6:	41 d1 e0             	shl    %r8d
    7fb40dba76c9:	44 89 8d c0 f8 ff ff 	mov    %r9d,-0x740(%rbp)
    7fb40dba76d0:	44 8b 8d c8 f8 ff ff 	mov    -0x738(%rbp),%r9d
    7fb40dba76d7:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba76db:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba76df:	44 89 8d b8 f8 ff ff 	mov    %r9d,-0x748(%rbp)
    7fb40dba76e6:	41 d1 e1             	shl    %r9d
    7fb40dba76e9:	44 89 9d b0 f8 ff ff 	mov    %r11d,-0x750(%rbp)
    7fb40dba76f0:	44 8b 9d b8 f8 ff ff 	mov    -0x748(%rbp),%r11d
    7fb40dba76f7:	45 0b cb             	or     %r11d,%r9d
    7fb40dba76fa:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba76fe:	45 0b cb             	or     %r11d,%r9d
    7fb40dba7701:	44 8b 9d b8 f8 ff ff 	mov    -0x748(%rbp),%r11d
    7fb40dba7708:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba770c:	45 0b cb             	or     %r11d,%r9d
    7fb40dba770f:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba7712:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba7715:	44 8b 9d c8 f8 ff ff 	mov    -0x738(%rbp),%r11d
    7fb40dba771c:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba771f:	41 33 f1             	xor    %r9d,%esi
    7fb40dba7722:	41 33 f2             	xor    %r10d,%esi
    7fb40dba7725:	44 8b c8             	mov    %eax,%r9d
    7fb40dba7728:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba772b:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba772e:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba7731:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba7735:	41 d1 e1             	shl    %r9d
    7fb40dba7738:	45 8b da             	mov    %r10d,%r11d
    7fb40dba773b:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba773f:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba7743:	44 89 9d a8 f8 ff ff 	mov    %r11d,-0x758(%rbp)
    7fb40dba774a:	41 d1 e3             	shl    %r11d
    7fb40dba774d:	89 95 a0 f8 ff ff    	mov    %edx,-0x760(%rbp)
    7fb40dba7753:	8b 95 a8 f8 ff ff    	mov    -0x758(%rbp),%edx
    7fb40dba7759:	44 0b da             	or     %edx,%r11d
    7fb40dba775c:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba775f:	44 0b da             	or     %edx,%r11d
    7fb40dba7762:	8b 95 a8 f8 ff ff    	mov    -0x758(%rbp),%edx
    7fb40dba7768:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba776b:	44 0b da             	or     %edx,%r11d
    7fb40dba776e:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba7771:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba7774:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba7777:	33 c8                	xor    %eax,%ecx
    7fb40dba7779:	33 d9                	xor    %ecx,%ebx
    7fb40dba777b:	33 9d c8 f8 ff ff    	xor    -0x738(%rbp),%ebx
    7fb40dba7781:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba7784:	49 0f b6 87 78 01 00 	movzbq 0x178(%r15),%rax
    7fb40dba778b:	00 
    7fb40dba778c:	8b c0                	mov    %eax,%eax
    7fb40dba778e:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7793:	8b c8                	mov    %eax,%ecx
    7fb40dba7795:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba7798:	d1 e1                	shl    %ecx
    7fb40dba779a:	8b d0                	mov    %eax,%edx
    7fb40dba779c:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba779f:	83 e2 01             	and    $0x1,%edx
    7fb40dba77a2:	8b da                	mov    %edx,%ebx
    7fb40dba77a4:	d1 e3                	shl    %ebx
    7fb40dba77a6:	0b da                	or     %edx,%ebx
    7fb40dba77a8:	44 8b d2             	mov    %edx,%r10d
    7fb40dba77ab:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba77af:	41 0b da             	or     %r10d,%ebx
    7fb40dba77b2:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba77b5:	0b da                	or     %edx,%ebx
    7fb40dba77b7:	33 cb                	xor    %ebx,%ecx
    7fb40dba77b9:	49 0f b6 97 7d 01 00 	movzbq 0x17d(%r15),%rdx
    7fb40dba77c0:	00 
    7fb40dba77c1:	8b d2                	mov    %edx,%edx
    7fb40dba77c3:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba77c8:	8b da                	mov    %edx,%ebx
    7fb40dba77ca:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba77cd:	d1 e3                	shl    %ebx
    7fb40dba77cf:	44 8b d2             	mov    %edx,%r10d
    7fb40dba77d2:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba77d6:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba77da:	45 8b da             	mov    %r10d,%r11d
    7fb40dba77dd:	41 d1 e3             	shl    %r11d
    7fb40dba77e0:	45 0b da             	or     %r10d,%r11d
    7fb40dba77e3:	44 89 95 98 f8 ff ff 	mov    %r10d,-0x768(%rbp)
    7fb40dba77ea:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba77ee:	45 0b da             	or     %r10d,%r11d
    7fb40dba77f1:	44 8b 95 98 f8 ff ff 	mov    -0x768(%rbp),%r10d
    7fb40dba77f8:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba77fc:	45 0b da             	or     %r10d,%r11d
    7fb40dba77ff:	41 33 db             	xor    %r11d,%ebx
    7fb40dba7802:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba7805:	44 33 d2             	xor    %edx,%r10d
    7fb40dba7808:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba780b:	4d 0f b6 9f 72 01 00 	movzbq 0x172(%r15),%r11
    7fb40dba7812:	00 
    7fb40dba7813:	45 8b db             	mov    %r11d,%r11d
    7fb40dba7816:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba781b:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba781e:	89 bd 90 f8 ff ff    	mov    %edi,-0x770(%rbp)
    7fb40dba7824:	49 0f b6 bf 77 01 00 	movzbq 0x177(%r15),%rdi
    7fb40dba782b:	00 
    7fb40dba782c:	8b ff                	mov    %edi,%edi
    7fb40dba782e:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba7833:	44 33 d7             	xor    %edi,%r10d
    7fb40dba7836:	33 d8                	xor    %eax,%ebx
    7fb40dba7838:	44 89 9d 88 f8 ff ff 	mov    %r11d,-0x778(%rbp)
    7fb40dba783f:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba7843:	41 d1 e3             	shl    %r11d
    7fb40dba7846:	89 b5 80 f8 ff ff    	mov    %esi,-0x780(%rbp)
    7fb40dba784c:	8b b5 88 f8 ff ff    	mov    -0x778(%rbp),%esi
    7fb40dba7852:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba7855:	83 e6 01             	and    $0x1,%esi
    7fb40dba7858:	89 b5 78 f8 ff ff    	mov    %esi,-0x788(%rbp)
    7fb40dba785e:	d1 e6                	shl    %esi
    7fb40dba7860:	44 89 85 70 f8 ff ff 	mov    %r8d,-0x790(%rbp)
    7fb40dba7867:	44 8b 85 78 f8 ff ff 	mov    -0x788(%rbp),%r8d
    7fb40dba786e:	41 0b f0             	or     %r8d,%esi
    7fb40dba7871:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba7875:	41 0b f0             	or     %r8d,%esi
    7fb40dba7878:	44 8b 85 78 f8 ff ff 	mov    -0x788(%rbp),%r8d
    7fb40dba787f:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba7883:	41 0b f0             	or     %r8d,%esi
    7fb40dba7886:	44 33 de             	xor    %esi,%r11d
    7fb40dba7889:	41 8b f3             	mov    %r11d,%esi
    7fb40dba788c:	44 8b 85 88 f8 ff ff 	mov    -0x778(%rbp),%r8d
    7fb40dba7893:	41 33 f0             	xor    %r8d,%esi
    7fb40dba7896:	33 de                	xor    %esi,%ebx
    7fb40dba7898:	33 df                	xor    %edi,%ebx
    7fb40dba789a:	8b f0                	mov    %eax,%esi
    7fb40dba789c:	33 f2                	xor    %edx,%esi
    7fb40dba789e:	44 33 de             	xor    %esi,%r11d
    7fb40dba78a1:	8b f7                	mov    %edi,%esi
    7fb40dba78a3:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba78a6:	d1 e6                	shl    %esi
    7fb40dba78a8:	44 8b c7             	mov    %edi,%r8d
    7fb40dba78ab:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba78af:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba78b3:	44 89 85 68 f8 ff ff 	mov    %r8d,-0x798(%rbp)
    7fb40dba78ba:	41 d1 e0             	shl    %r8d
    7fb40dba78bd:	44 89 8d 60 f8 ff ff 	mov    %r9d,-0x7a0(%rbp)
    7fb40dba78c4:	44 8b 8d 68 f8 ff ff 	mov    -0x798(%rbp),%r9d
    7fb40dba78cb:	45 0b c1             	or     %r9d,%r8d
    7fb40dba78ce:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba78d2:	45 0b c1             	or     %r9d,%r8d
    7fb40dba78d5:	44 8b 8d 68 f8 ff ff 	mov    -0x798(%rbp),%r9d
    7fb40dba78dc:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba78e0:	45 0b c1             	or     %r9d,%r8d
    7fb40dba78e3:	41 33 f0             	xor    %r8d,%esi
    7fb40dba78e6:	33 fe                	xor    %esi,%edi
    7fb40dba78e8:	44 33 df             	xor    %edi,%r11d
    7fb40dba78eb:	33 c8                	xor    %eax,%ecx
    7fb40dba78ed:	33 d1                	xor    %ecx,%edx
    7fb40dba78ef:	33 95 88 f8 ff ff    	xor    -0x778(%rbp),%edx
    7fb40dba78f5:	33 f2                	xor    %edx,%esi
    7fb40dba78f7:	49 0f b6 87 7c 01 00 	movzbq 0x17c(%r15),%rax
    7fb40dba78fe:	00 
    7fb40dba78ff:	8b c0                	mov    %eax,%eax
    7fb40dba7901:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7906:	8b c8                	mov    %eax,%ecx
    7fb40dba7908:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba790b:	d1 e1                	shl    %ecx
    7fb40dba790d:	8b d0                	mov    %eax,%edx
    7fb40dba790f:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba7912:	83 e2 01             	and    $0x1,%edx
    7fb40dba7915:	8b fa                	mov    %edx,%edi
    7fb40dba7917:	d1 e7                	shl    %edi
    7fb40dba7919:	0b fa                	or     %edx,%edi
    7fb40dba791b:	44 8b c2             	mov    %edx,%r8d
    7fb40dba791e:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba7922:	41 0b f8             	or     %r8d,%edi
    7fb40dba7925:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba7928:	0b fa                	or     %edx,%edi
    7fb40dba792a:	33 cf                	xor    %edi,%ecx
    7fb40dba792c:	49 0f b6 97 71 01 00 	movzbq 0x171(%r15),%rdx
    7fb40dba7933:	00 
    7fb40dba7934:	8b d2                	mov    %edx,%edx
    7fb40dba7936:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba793b:	8b fa                	mov    %edx,%edi
    7fb40dba793d:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba7940:	d1 e7                	shl    %edi
    7fb40dba7942:	44 8b c2             	mov    %edx,%r8d
    7fb40dba7945:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba7949:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba794d:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba7950:	41 d1 e1             	shl    %r9d
    7fb40dba7953:	45 0b c8             	or     %r8d,%r9d
    7fb40dba7956:	44 89 85 58 f8 ff ff 	mov    %r8d,-0x7a8(%rbp)
    7fb40dba795d:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba7961:	45 0b c8             	or     %r8d,%r9d
    7fb40dba7964:	44 8b 85 58 f8 ff ff 	mov    -0x7a8(%rbp),%r8d
    7fb40dba796b:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba796f:	45 0b c8             	or     %r8d,%r9d
    7fb40dba7972:	41 33 f9             	xor    %r9d,%edi
    7fb40dba7975:	44 8b c7             	mov    %edi,%r8d
    7fb40dba7978:	44 33 c2             	xor    %edx,%r8d
    7fb40dba797b:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba797e:	4d 0f b6 8f 76 01 00 	movzbq 0x176(%r15),%r9
    7fb40dba7985:	00 
    7fb40dba7986:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba7989:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba798e:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba7991:	44 89 95 50 f8 ff ff 	mov    %r10d,-0x7b0(%rbp)
    7fb40dba7998:	4d 0f b6 97 7b 01 00 	movzbq 0x17b(%r15),%r10
    7fb40dba799f:	00 
    7fb40dba79a0:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba79a3:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba79a8:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba79ab:	33 f8                	xor    %eax,%edi
    7fb40dba79ad:	44 89 8d 48 f8 ff ff 	mov    %r9d,-0x7b8(%rbp)
    7fb40dba79b4:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba79b8:	41 d1 e1             	shl    %r9d
    7fb40dba79bb:	89 9d 40 f8 ff ff    	mov    %ebx,-0x7c0(%rbp)
    7fb40dba79c1:	8b 9d 48 f8 ff ff    	mov    -0x7b8(%rbp),%ebx
    7fb40dba79c7:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba79ca:	83 e3 01             	and    $0x1,%ebx
    7fb40dba79cd:	89 9d 38 f8 ff ff    	mov    %ebx,-0x7c8(%rbp)
    7fb40dba79d3:	d1 e3                	shl    %ebx
    7fb40dba79d5:	44 89 9d 30 f8 ff ff 	mov    %r11d,-0x7d0(%rbp)
    7fb40dba79dc:	44 8b 9d 38 f8 ff ff 	mov    -0x7c8(%rbp),%r11d
    7fb40dba79e3:	41 0b db             	or     %r11d,%ebx
    7fb40dba79e6:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba79ea:	41 0b db             	or     %r11d,%ebx
    7fb40dba79ed:	44 8b 9d 38 f8 ff ff 	mov    -0x7c8(%rbp),%r11d
    7fb40dba79f4:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba79f8:	41 0b db             	or     %r11d,%ebx
    7fb40dba79fb:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba79fe:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba7a01:	44 8b 9d 48 f8 ff ff 	mov    -0x7b8(%rbp),%r11d
    7fb40dba7a08:	41 33 db             	xor    %r11d,%ebx
    7fb40dba7a0b:	33 fb                	xor    %ebx,%edi
    7fb40dba7a0d:	41 33 fa             	xor    %r10d,%edi
    7fb40dba7a10:	8b d8                	mov    %eax,%ebx
    7fb40dba7a12:	33 da                	xor    %edx,%ebx
    7fb40dba7a14:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba7a17:	41 8b da             	mov    %r10d,%ebx
    7fb40dba7a1a:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba7a1d:	d1 e3                	shl    %ebx
    7fb40dba7a1f:	45 8b da             	mov    %r10d,%r11d
    7fb40dba7a22:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba7a26:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba7a2a:	44 89 9d 28 f8 ff ff 	mov    %r11d,-0x7d8(%rbp)
    7fb40dba7a31:	41 d1 e3             	shl    %r11d
    7fb40dba7a34:	89 b5 20 f8 ff ff    	mov    %esi,-0x7e0(%rbp)
    7fb40dba7a3a:	8b b5 28 f8 ff ff    	mov    -0x7d8(%rbp),%esi
    7fb40dba7a40:	44 0b de             	or     %esi,%r11d
    7fb40dba7a43:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba7a46:	44 0b de             	or     %esi,%r11d
    7fb40dba7a49:	8b b5 28 f8 ff ff    	mov    -0x7d8(%rbp),%esi
    7fb40dba7a4f:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba7a52:	44 0b de             	or     %esi,%r11d
    7fb40dba7a55:	41 33 db             	xor    %r11d,%ebx
    7fb40dba7a58:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba7a5b:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba7a5e:	33 c8                	xor    %eax,%ecx
    7fb40dba7a60:	33 d1                	xor    %ecx,%edx
    7fb40dba7a62:	33 95 48 f8 ff ff    	xor    -0x7b8(%rbp),%edx
    7fb40dba7a68:	33 da                	xor    %edx,%ebx
    7fb40dba7a6a:	8b 85 c0 f8 ff ff    	mov    -0x740(%rbp),%eax
    7fb40dba7a70:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba7a73:	8b 8d d0 f8 ff ff    	mov    -0x730(%rbp),%ecx
    7fb40dba7a79:	0b c1                	or     %ecx,%eax
    7fb40dba7a7b:	8b 8d b0 f8 ff ff    	mov    -0x750(%rbp),%ecx
    7fb40dba7a81:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba7a84:	0b c1                	or     %ecx,%eax
    7fb40dba7a86:	8b 8d a0 f8 ff ff    	mov    -0x760(%rbp),%ecx
    7fb40dba7a8c:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba7a8f:	0b c1                	or     %ecx,%eax
    7fb40dba7a91:	8b 8d 90 f8 ff ff    	mov    -0x770(%rbp),%ecx
    7fb40dba7a97:	8b c9                	mov    %ecx,%ecx
    7fb40dba7a99:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba7a9d:	8b c0                	mov    %eax,%eax
    7fb40dba7a9f:	48 0b c8             	or     %rax,%rcx
    7fb40dba7aa2:	8b 85 80 f8 ff ff    	mov    -0x780(%rbp),%eax
    7fb40dba7aa8:	8b c0                	mov    %eax,%eax
    7fb40dba7aaa:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba7aae:	48 0b c8             	or     %rax,%rcx
    7fb40dba7ab1:	8b 85 70 f8 ff ff    	mov    -0x790(%rbp),%eax
    7fb40dba7ab7:	8b c0                	mov    %eax,%eax
    7fb40dba7ab9:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba7abd:	48 0b c8             	or     %rax,%rcx
    7fb40dba7ac0:	8b 85 60 f8 ff ff    	mov    -0x7a0(%rbp),%eax
    7fb40dba7ac6:	8b c0                	mov    %eax,%eax
    7fb40dba7ac8:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba7acc:	48 0b c8             	or     %rax,%rcx
    7fb40dba7acf:	49 89 8f d0 02 00 00 	mov    %rcx,0x2d0(%r15)
    7fb40dba7ad6:	8b 85 40 f8 ff ff    	mov    -0x7c0(%rbp),%eax
    7fb40dba7adc:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba7adf:	8b 8d 50 f8 ff ff    	mov    -0x7b0(%rbp),%ecx
    7fb40dba7ae5:	0b c1                	or     %ecx,%eax
    7fb40dba7ae7:	8b 8d 30 f8 ff ff    	mov    -0x7d0(%rbp),%ecx
    7fb40dba7aed:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba7af0:	0b c1                	or     %ecx,%eax
    7fb40dba7af2:	8b 8d 20 f8 ff ff    	mov    -0x7e0(%rbp),%ecx
    7fb40dba7af8:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba7afb:	0b c1                	or     %ecx,%eax
    7fb40dba7afd:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba7b00:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba7b04:	8b c0                	mov    %eax,%eax
    7fb40dba7b06:	4c 0b c0             	or     %rax,%r8
    7fb40dba7b09:	8b ff                	mov    %edi,%edi
    7fb40dba7b0b:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba7b0f:	4c 0b c7             	or     %rdi,%r8
    7fb40dba7b12:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba7b15:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba7b19:	4d 0b c1             	or     %r9,%r8
    7fb40dba7b1c:	8b db                	mov    %ebx,%ebx
    7fb40dba7b1e:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba7b22:	4c 0b c3             	or     %rbx,%r8
    7fb40dba7b25:	4d 89 87 d8 02 00 00 	mov    %r8,0x2d8(%r15)
    7fb40dba7b2c:	8b 85 f0 f8 ff ff    	mov    -0x710(%rbp),%eax
    7fb40dba7b32:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba7b37:	8b c0                	mov    %eax,%eax
    7fb40dba7b39:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7b3e:	8b 8d f0 f8 ff ff    	mov    -0x710(%rbp),%ecx
    7fb40dba7b44:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba7b47:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba7b4d:	8b c9                	mov    %ecx,%ecx
    7fb40dba7b4f:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba7b54:	8b 95 f0 f8 ff ff    	mov    -0x710(%rbp),%edx
    7fb40dba7b5a:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba7b5d:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba7b63:	8b d2                	mov    %edx,%edx
    7fb40dba7b65:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba7b6a:	8b 9d f0 f8 ff ff    	mov    -0x710(%rbp),%ebx
    7fb40dba7b70:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba7b73:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba7b79:	8b db                	mov    %ebx,%ebx
    7fb40dba7b7b:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba7b80:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba7b83:	0b da                	or     %edx,%ebx
    7fb40dba7b85:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba7b88:	0b d9                	or     %ecx,%ebx
    7fb40dba7b8a:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba7b8d:	0b d8                	or     %eax,%ebx
    7fb40dba7b8f:	81 f3 80 00 00 00    	xor    $0x80,%ebx
    7fb40dba7b95:	8b 85 00 f9 ff ff    	mov    -0x700(%rbp),%eax
    7fb40dba7b9b:	33 d8                	xor    %eax,%ebx
    7fb40dba7b9d:	8b 85 10 f9 ff ff    	mov    -0x6f0(%rbp),%eax
    7fb40dba7ba3:	33 c3                	xor    %ebx,%eax
    7fb40dba7ba5:	8b 8d e0 f8 ff ff    	mov    -0x720(%rbp),%ecx
    7fb40dba7bab:	33 c8                	xor    %eax,%ecx
    7fb40dba7bad:	8b 95 f0 f8 ff ff    	mov    -0x710(%rbp),%edx
    7fb40dba7bb3:	33 d1                	xor    %ecx,%edx
    7fb40dba7bb5:	8b f0                	mov    %eax,%esi
    7fb40dba7bb7:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba7bbb:	8b fb                	mov    %ebx,%edi
    7fb40dba7bbd:	48 0b f7             	or     %rdi,%rsi
    7fb40dba7bc0:	49 89 b7 30 02 00 00 	mov    %rsi,0x230(%r15)
    7fb40dba7bc7:	8b f2                	mov    %edx,%esi
    7fb40dba7bc9:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba7bcd:	8b f9                	mov    %ecx,%edi
    7fb40dba7bcf:	48 0b f7             	or     %rdi,%rsi
    7fb40dba7bd2:	49 89 b7 38 02 00 00 	mov    %rsi,0x238(%r15)
    7fb40dba7bd9:	49 8b b7 d0 02 00 00 	mov    0x2d0(%r15),%rsi
    7fb40dba7be0:	49 8b bf 30 02 00 00 	mov    0x230(%r15),%rdi
    7fb40dba7be7:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba7bea:	49 89 b7 80 03 00 00 	mov    %rsi,0x380(%r15)
    7fb40dba7bf1:	49 8b b7 d8 02 00 00 	mov    0x2d8(%r15),%rsi
    7fb40dba7bf8:	49 8b bf 38 02 00 00 	mov    0x238(%r15),%rdi
    7fb40dba7bff:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba7c02:	49 89 b7 88 03 00 00 	mov    %rsi,0x388(%r15)
    7fb40dba7c09:	49 0f b6 b7 80 01 00 	movzbq 0x180(%r15),%rsi
    7fb40dba7c10:	00 
    7fb40dba7c11:	8b f6                	mov    %esi,%esi
    7fb40dba7c13:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba7c18:	8b fe                	mov    %esi,%edi
    7fb40dba7c1a:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba7c1d:	d1 e7                	shl    %edi
    7fb40dba7c1f:	44 8b c6             	mov    %esi,%r8d
    7fb40dba7c22:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba7c26:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba7c2a:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba7c2d:	41 d1 e1             	shl    %r9d
    7fb40dba7c30:	45 0b c8             	or     %r8d,%r9d
    7fb40dba7c33:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba7c36:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba7c3a:	45 0b ca             	or     %r10d,%r9d
    7fb40dba7c3d:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba7c41:	45 0b c8             	or     %r8d,%r9d
    7fb40dba7c44:	41 33 f9             	xor    %r9d,%edi
    7fb40dba7c47:	4d 0f b6 87 85 01 00 	movzbq 0x185(%r15),%r8
    7fb40dba7c4e:	00 
    7fb40dba7c4f:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba7c52:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba7c57:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba7c5a:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba7c5e:	41 d1 e1             	shl    %r9d
    7fb40dba7c61:	45 8b d0             	mov    %r8d,%r10d
    7fb40dba7c64:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba7c68:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba7c6c:	45 8b da             	mov    %r10d,%r11d
    7fb40dba7c6f:	41 d1 e3             	shl    %r11d
    7fb40dba7c72:	45 0b da             	or     %r10d,%r11d
    7fb40dba7c75:	44 89 95 18 f8 ff ff 	mov    %r10d,-0x7e8(%rbp)
    7fb40dba7c7c:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba7c80:	45 0b da             	or     %r10d,%r11d
    7fb40dba7c83:	44 8b 95 18 f8 ff ff 	mov    -0x7e8(%rbp),%r10d
    7fb40dba7c8a:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba7c8e:	45 0b da             	or     %r10d,%r11d
    7fb40dba7c91:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba7c94:	45 8b d1             	mov    %r9d,%r10d
    7fb40dba7c97:	45 33 d0             	xor    %r8d,%r10d
    7fb40dba7c9a:	44 33 d7             	xor    %edi,%r10d
    7fb40dba7c9d:	4d 0f b6 9f 8a 01 00 	movzbq 0x18a(%r15),%r11
    7fb40dba7ca4:	00 
    7fb40dba7ca5:	45 8b db             	mov    %r11d,%r11d
    7fb40dba7ca8:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba7cad:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba7cb0:	89 85 10 f8 ff ff    	mov    %eax,-0x7f0(%rbp)
    7fb40dba7cb6:	49 0f b6 87 8f 01 00 	movzbq 0x18f(%r15),%rax
    7fb40dba7cbd:	00 
    7fb40dba7cbe:	8b c0                	mov    %eax,%eax
    7fb40dba7cc0:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7cc5:	44 33 d0             	xor    %eax,%r10d
    7fb40dba7cc8:	44 33 ce             	xor    %esi,%r9d
    7fb40dba7ccb:	44 89 9d 08 f8 ff ff 	mov    %r11d,-0x7f8(%rbp)
    7fb40dba7cd2:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba7cd6:	41 d1 e3             	shl    %r11d
    7fb40dba7cd9:	89 9d 00 f8 ff ff    	mov    %ebx,-0x800(%rbp)
    7fb40dba7cdf:	8b 9d 08 f8 ff ff    	mov    -0x7f8(%rbp),%ebx
    7fb40dba7ce5:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba7ce8:	83 e3 01             	and    $0x1,%ebx
    7fb40dba7ceb:	89 9d f8 f7 ff ff    	mov    %ebx,-0x808(%rbp)
    7fb40dba7cf1:	d1 e3                	shl    %ebx
    7fb40dba7cf3:	89 95 f0 f7 ff ff    	mov    %edx,-0x810(%rbp)
    7fb40dba7cf9:	8b 95 f8 f7 ff ff    	mov    -0x808(%rbp),%edx
    7fb40dba7cff:	0b da                	or     %edx,%ebx
    7fb40dba7d01:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba7d04:	0b da                	or     %edx,%ebx
    7fb40dba7d06:	8b 95 f8 f7 ff ff    	mov    -0x808(%rbp),%edx
    7fb40dba7d0c:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba7d0f:	0b da                	or     %edx,%ebx
    7fb40dba7d11:	44 33 db             	xor    %ebx,%r11d
    7fb40dba7d14:	41 8b d3             	mov    %r11d,%edx
    7fb40dba7d17:	8b 9d 08 f8 ff ff    	mov    -0x7f8(%rbp),%ebx
    7fb40dba7d1d:	33 d3                	xor    %ebx,%edx
    7fb40dba7d1f:	44 33 ca             	xor    %edx,%r9d
    7fb40dba7d22:	44 33 c8             	xor    %eax,%r9d
    7fb40dba7d25:	8b d6                	mov    %esi,%edx
    7fb40dba7d27:	41 33 d0             	xor    %r8d,%edx
    7fb40dba7d2a:	44 33 da             	xor    %edx,%r11d
    7fb40dba7d2d:	8b d0                	mov    %eax,%edx
    7fb40dba7d2f:	83 e2 7f             	and    $0x7f,%edx
    7fb40dba7d32:	d1 e2                	shl    %edx
    7fb40dba7d34:	8b d8                	mov    %eax,%ebx
    7fb40dba7d36:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba7d39:	83 e3 01             	and    $0x1,%ebx
    7fb40dba7d3c:	89 9d e8 f7 ff ff    	mov    %ebx,-0x818(%rbp)
    7fb40dba7d42:	d1 e3                	shl    %ebx
    7fb40dba7d44:	89 8d e0 f7 ff ff    	mov    %ecx,-0x820(%rbp)
    7fb40dba7d4a:	8b 8d e8 f7 ff ff    	mov    -0x818(%rbp),%ecx
    7fb40dba7d50:	0b d9                	or     %ecx,%ebx
    7fb40dba7d52:	c1 e1 03             	shl    $0x3,%ecx
    7fb40dba7d55:	0b d9                	or     %ecx,%ebx
    7fb40dba7d57:	8b 8d e8 f7 ff ff    	mov    -0x818(%rbp),%ecx
    7fb40dba7d5d:	c1 e1 04             	shl    $0x4,%ecx
    7fb40dba7d60:	0b d9                	or     %ecx,%ebx
    7fb40dba7d62:	33 d3                	xor    %ebx,%edx
    7fb40dba7d64:	33 c2                	xor    %edx,%eax
    7fb40dba7d66:	44 33 d8             	xor    %eax,%r11d
    7fb40dba7d69:	33 fe                	xor    %esi,%edi
    7fb40dba7d6b:	44 33 c7             	xor    %edi,%r8d
    7fb40dba7d6e:	44 33 85 08 f8 ff ff 	xor    -0x7f8(%rbp),%r8d
    7fb40dba7d75:	41 33 d0             	xor    %r8d,%edx
    7fb40dba7d78:	49 0f b6 87 84 01 00 	movzbq 0x184(%r15),%rax
    7fb40dba7d7f:	00 
    7fb40dba7d80:	8b c0                	mov    %eax,%eax
    7fb40dba7d82:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7d87:	8b c8                	mov    %eax,%ecx
    7fb40dba7d89:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba7d8c:	d1 e1                	shl    %ecx
    7fb40dba7d8e:	8b d8                	mov    %eax,%ebx
    7fb40dba7d90:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba7d93:	83 e3 01             	and    $0x1,%ebx
    7fb40dba7d96:	8b f3                	mov    %ebx,%esi
    7fb40dba7d98:	d1 e6                	shl    %esi
    7fb40dba7d9a:	0b f3                	or     %ebx,%esi
    7fb40dba7d9c:	8b fb                	mov    %ebx,%edi
    7fb40dba7d9e:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba7da1:	0b f7                	or     %edi,%esi
    7fb40dba7da3:	c1 e3 04             	shl    $0x4,%ebx
    7fb40dba7da6:	0b f3                	or     %ebx,%esi
    7fb40dba7da8:	33 ce                	xor    %esi,%ecx
    7fb40dba7daa:	49 0f b6 9f 89 01 00 	movzbq 0x189(%r15),%rbx
    7fb40dba7db1:	00 
    7fb40dba7db2:	8b db                	mov    %ebx,%ebx
    7fb40dba7db4:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba7db9:	8b f3                	mov    %ebx,%esi
    7fb40dba7dbb:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba7dbe:	d1 e6                	shl    %esi
    7fb40dba7dc0:	8b fb                	mov    %ebx,%edi
    7fb40dba7dc2:	c1 ef 07             	shr    $0x7,%edi
    7fb40dba7dc5:	83 e7 01             	and    $0x1,%edi
    7fb40dba7dc8:	44 8b c7             	mov    %edi,%r8d
    7fb40dba7dcb:	41 d1 e0             	shl    %r8d
    7fb40dba7dce:	44 0b c7             	or     %edi,%r8d
    7fb40dba7dd1:	89 bd d8 f7 ff ff    	mov    %edi,-0x828(%rbp)
    7fb40dba7dd7:	c1 e7 03             	shl    $0x3,%edi
    7fb40dba7dda:	44 0b c7             	or     %edi,%r8d
    7fb40dba7ddd:	8b bd d8 f7 ff ff    	mov    -0x828(%rbp),%edi
    7fb40dba7de3:	c1 e7 04             	shl    $0x4,%edi
    7fb40dba7de6:	44 0b c7             	or     %edi,%r8d
    7fb40dba7de9:	41 33 f0             	xor    %r8d,%esi
    7fb40dba7dec:	8b fe                	mov    %esi,%edi
    7fb40dba7dee:	33 fb                	xor    %ebx,%edi
    7fb40dba7df0:	33 f9                	xor    %ecx,%edi
    7fb40dba7df2:	4d 0f b6 87 8e 01 00 	movzbq 0x18e(%r15),%r8
    7fb40dba7df9:	00 
    7fb40dba7dfa:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba7dfd:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba7e02:	41 33 f8             	xor    %r8d,%edi
    7fb40dba7e05:	44 89 95 d0 f7 ff ff 	mov    %r10d,-0x830(%rbp)
    7fb40dba7e0c:	4d 0f b6 97 83 01 00 	movzbq 0x183(%r15),%r10
    7fb40dba7e13:	00 
    7fb40dba7e14:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba7e17:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba7e1c:	41 33 fa             	xor    %r10d,%edi
    7fb40dba7e1f:	33 f0                	xor    %eax,%esi
    7fb40dba7e21:	44 89 85 c8 f7 ff ff 	mov    %r8d,-0x838(%rbp)
    7fb40dba7e28:	41 83 e0 7f          	and    $0x7f,%r8d
    7fb40dba7e2c:	41 d1 e0             	shl    %r8d
    7fb40dba7e2f:	44 89 8d c0 f7 ff ff 	mov    %r9d,-0x840(%rbp)
    7fb40dba7e36:	44 8b 8d c8 f7 ff ff 	mov    -0x838(%rbp),%r9d
    7fb40dba7e3d:	41 c1 e9 07          	shr    $0x7,%r9d
    7fb40dba7e41:	41 83 e1 01          	and    $0x1,%r9d
    7fb40dba7e45:	44 89 8d b8 f7 ff ff 	mov    %r9d,-0x848(%rbp)
    7fb40dba7e4c:	41 d1 e1             	shl    %r9d
    7fb40dba7e4f:	44 89 9d b0 f7 ff ff 	mov    %r11d,-0x850(%rbp)
    7fb40dba7e56:	44 8b 9d b8 f7 ff ff 	mov    -0x848(%rbp),%r11d
    7fb40dba7e5d:	45 0b cb             	or     %r11d,%r9d
    7fb40dba7e60:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba7e64:	45 0b cb             	or     %r11d,%r9d
    7fb40dba7e67:	44 8b 9d b8 f7 ff ff 	mov    -0x848(%rbp),%r11d
    7fb40dba7e6e:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba7e72:	45 0b cb             	or     %r11d,%r9d
    7fb40dba7e75:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba7e78:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba7e7b:	44 8b 9d c8 f7 ff ff 	mov    -0x838(%rbp),%r11d
    7fb40dba7e82:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba7e85:	41 33 f1             	xor    %r9d,%esi
    7fb40dba7e88:	41 33 f2             	xor    %r10d,%esi
    7fb40dba7e8b:	44 8b c8             	mov    %eax,%r9d
    7fb40dba7e8e:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba7e91:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba7e94:	45 8b ca             	mov    %r10d,%r9d
    7fb40dba7e97:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba7e9b:	41 d1 e1             	shl    %r9d
    7fb40dba7e9e:	45 8b da             	mov    %r10d,%r11d
    7fb40dba7ea1:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba7ea5:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba7ea9:	44 89 9d a8 f7 ff ff 	mov    %r11d,-0x858(%rbp)
    7fb40dba7eb0:	41 d1 e3             	shl    %r11d
    7fb40dba7eb3:	89 95 a0 f7 ff ff    	mov    %edx,-0x860(%rbp)
    7fb40dba7eb9:	8b 95 a8 f7 ff ff    	mov    -0x858(%rbp),%edx
    7fb40dba7ebf:	44 0b da             	or     %edx,%r11d
    7fb40dba7ec2:	c1 e2 03             	shl    $0x3,%edx
    7fb40dba7ec5:	44 0b da             	or     %edx,%r11d
    7fb40dba7ec8:	8b 95 a8 f7 ff ff    	mov    -0x858(%rbp),%edx
    7fb40dba7ece:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba7ed1:	44 0b da             	or     %edx,%r11d
    7fb40dba7ed4:	45 33 cb             	xor    %r11d,%r9d
    7fb40dba7ed7:	45 33 d1             	xor    %r9d,%r10d
    7fb40dba7eda:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba7edd:	33 c8                	xor    %eax,%ecx
    7fb40dba7edf:	33 d9                	xor    %ecx,%ebx
    7fb40dba7ee1:	33 9d c8 f7 ff ff    	xor    -0x838(%rbp),%ebx
    7fb40dba7ee7:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba7eea:	49 0f b6 87 88 01 00 	movzbq 0x188(%r15),%rax
    7fb40dba7ef1:	00 
    7fb40dba7ef2:	8b c0                	mov    %eax,%eax
    7fb40dba7ef4:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba7ef9:	8b c8                	mov    %eax,%ecx
    7fb40dba7efb:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba7efe:	d1 e1                	shl    %ecx
    7fb40dba7f00:	8b d0                	mov    %eax,%edx
    7fb40dba7f02:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba7f05:	83 e2 01             	and    $0x1,%edx
    7fb40dba7f08:	8b da                	mov    %edx,%ebx
    7fb40dba7f0a:	d1 e3                	shl    %ebx
    7fb40dba7f0c:	0b da                	or     %edx,%ebx
    7fb40dba7f0e:	44 8b d2             	mov    %edx,%r10d
    7fb40dba7f11:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba7f15:	41 0b da             	or     %r10d,%ebx
    7fb40dba7f18:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba7f1b:	0b da                	or     %edx,%ebx
    7fb40dba7f1d:	33 cb                	xor    %ebx,%ecx
    7fb40dba7f1f:	49 0f b6 97 8d 01 00 	movzbq 0x18d(%r15),%rdx
    7fb40dba7f26:	00 
    7fb40dba7f27:	8b d2                	mov    %edx,%edx
    7fb40dba7f29:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba7f2e:	8b da                	mov    %edx,%ebx
    7fb40dba7f30:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba7f33:	d1 e3                	shl    %ebx
    7fb40dba7f35:	44 8b d2             	mov    %edx,%r10d
    7fb40dba7f38:	41 c1 ea 07          	shr    $0x7,%r10d
    7fb40dba7f3c:	41 83 e2 01          	and    $0x1,%r10d
    7fb40dba7f40:	45 8b da             	mov    %r10d,%r11d
    7fb40dba7f43:	41 d1 e3             	shl    %r11d
    7fb40dba7f46:	45 0b da             	or     %r10d,%r11d
    7fb40dba7f49:	44 89 95 98 f7 ff ff 	mov    %r10d,-0x868(%rbp)
    7fb40dba7f50:	41 c1 e2 03          	shl    $0x3,%r10d
    7fb40dba7f54:	45 0b da             	or     %r10d,%r11d
    7fb40dba7f57:	44 8b 95 98 f7 ff ff 	mov    -0x868(%rbp),%r10d
    7fb40dba7f5e:	41 c1 e2 04          	shl    $0x4,%r10d
    7fb40dba7f62:	45 0b da             	or     %r10d,%r11d
    7fb40dba7f65:	41 33 db             	xor    %r11d,%ebx
    7fb40dba7f68:	44 8b d3             	mov    %ebx,%r10d
    7fb40dba7f6b:	44 33 d2             	xor    %edx,%r10d
    7fb40dba7f6e:	44 33 d1             	xor    %ecx,%r10d
    7fb40dba7f71:	4d 0f b6 9f 82 01 00 	movzbq 0x182(%r15),%r11
    7fb40dba7f78:	00 
    7fb40dba7f79:	45 8b db             	mov    %r11d,%r11d
    7fb40dba7f7c:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba7f81:	45 33 d3             	xor    %r11d,%r10d
    7fb40dba7f84:	89 bd 90 f7 ff ff    	mov    %edi,-0x870(%rbp)
    7fb40dba7f8a:	49 0f b6 bf 87 01 00 	movzbq 0x187(%r15),%rdi
    7fb40dba7f91:	00 
    7fb40dba7f92:	8b ff                	mov    %edi,%edi
    7fb40dba7f94:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba7f99:	44 33 d7             	xor    %edi,%r10d
    7fb40dba7f9c:	33 d8                	xor    %eax,%ebx
    7fb40dba7f9e:	44 89 9d 88 f7 ff ff 	mov    %r11d,-0x878(%rbp)
    7fb40dba7fa5:	41 83 e3 7f          	and    $0x7f,%r11d
    7fb40dba7fa9:	41 d1 e3             	shl    %r11d
    7fb40dba7fac:	89 b5 80 f7 ff ff    	mov    %esi,-0x880(%rbp)
    7fb40dba7fb2:	8b b5 88 f7 ff ff    	mov    -0x878(%rbp),%esi
    7fb40dba7fb8:	c1 ee 07             	shr    $0x7,%esi
    7fb40dba7fbb:	83 e6 01             	and    $0x1,%esi
    7fb40dba7fbe:	89 b5 78 f7 ff ff    	mov    %esi,-0x888(%rbp)
    7fb40dba7fc4:	d1 e6                	shl    %esi
    7fb40dba7fc6:	44 89 85 70 f7 ff ff 	mov    %r8d,-0x890(%rbp)
    7fb40dba7fcd:	44 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%r8d
    7fb40dba7fd4:	41 0b f0             	or     %r8d,%esi
    7fb40dba7fd7:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba7fdb:	41 0b f0             	or     %r8d,%esi
    7fb40dba7fde:	44 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%r8d
    7fb40dba7fe5:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba7fe9:	41 0b f0             	or     %r8d,%esi
    7fb40dba7fec:	44 33 de             	xor    %esi,%r11d
    7fb40dba7fef:	41 8b f3             	mov    %r11d,%esi
    7fb40dba7ff2:	44 8b 85 88 f7 ff ff 	mov    -0x878(%rbp),%r8d
    7fb40dba7ff9:	41 33 f0             	xor    %r8d,%esi
    7fb40dba7ffc:	33 de                	xor    %esi,%ebx
    7fb40dba7ffe:	33 df                	xor    %edi,%ebx
    7fb40dba8000:	8b f0                	mov    %eax,%esi
    7fb40dba8002:	33 f2                	xor    %edx,%esi
    7fb40dba8004:	44 33 de             	xor    %esi,%r11d
    7fb40dba8007:	8b f7                	mov    %edi,%esi
    7fb40dba8009:	83 e6 7f             	and    $0x7f,%esi
    7fb40dba800c:	d1 e6                	shl    %esi
    7fb40dba800e:	44 8b c7             	mov    %edi,%r8d
    7fb40dba8011:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba8015:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba8019:	44 89 85 68 f7 ff ff 	mov    %r8d,-0x898(%rbp)
    7fb40dba8020:	41 d1 e0             	shl    %r8d
    7fb40dba8023:	44 89 8d 60 f7 ff ff 	mov    %r9d,-0x8a0(%rbp)
    7fb40dba802a:	44 8b 8d 68 f7 ff ff 	mov    -0x898(%rbp),%r9d
    7fb40dba8031:	45 0b c1             	or     %r9d,%r8d
    7fb40dba8034:	41 c1 e1 03          	shl    $0x3,%r9d
    7fb40dba8038:	45 0b c1             	or     %r9d,%r8d
    7fb40dba803b:	44 8b 8d 68 f7 ff ff 	mov    -0x898(%rbp),%r9d
    7fb40dba8042:	41 c1 e1 04          	shl    $0x4,%r9d
    7fb40dba8046:	45 0b c1             	or     %r9d,%r8d
    7fb40dba8049:	41 33 f0             	xor    %r8d,%esi
    7fb40dba804c:	33 fe                	xor    %esi,%edi
    7fb40dba804e:	44 33 df             	xor    %edi,%r11d
    7fb40dba8051:	33 c8                	xor    %eax,%ecx
    7fb40dba8053:	33 d1                	xor    %ecx,%edx
    7fb40dba8055:	33 95 88 f7 ff ff    	xor    -0x878(%rbp),%edx
    7fb40dba805b:	33 f2                	xor    %edx,%esi
    7fb40dba805d:	49 0f b6 87 8c 01 00 	movzbq 0x18c(%r15),%rax
    7fb40dba8064:	00 
    7fb40dba8065:	8b c0                	mov    %eax,%eax
    7fb40dba8067:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba806c:	8b c8                	mov    %eax,%ecx
    7fb40dba806e:	83 e1 7f             	and    $0x7f,%ecx
    7fb40dba8071:	d1 e1                	shl    %ecx
    7fb40dba8073:	8b d0                	mov    %eax,%edx
    7fb40dba8075:	c1 ea 07             	shr    $0x7,%edx
    7fb40dba8078:	83 e2 01             	and    $0x1,%edx
    7fb40dba807b:	8b fa                	mov    %edx,%edi
    7fb40dba807d:	d1 e7                	shl    %edi
    7fb40dba807f:	0b fa                	or     %edx,%edi
    7fb40dba8081:	44 8b c2             	mov    %edx,%r8d
    7fb40dba8084:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba8088:	41 0b f8             	or     %r8d,%edi
    7fb40dba808b:	c1 e2 04             	shl    $0x4,%edx
    7fb40dba808e:	0b fa                	or     %edx,%edi
    7fb40dba8090:	33 cf                	xor    %edi,%ecx
    7fb40dba8092:	49 0f b6 97 81 01 00 	movzbq 0x181(%r15),%rdx
    7fb40dba8099:	00 
    7fb40dba809a:	8b d2                	mov    %edx,%edx
    7fb40dba809c:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba80a1:	8b fa                	mov    %edx,%edi
    7fb40dba80a3:	83 e7 7f             	and    $0x7f,%edi
    7fb40dba80a6:	d1 e7                	shl    %edi
    7fb40dba80a8:	44 8b c2             	mov    %edx,%r8d
    7fb40dba80ab:	41 c1 e8 07          	shr    $0x7,%r8d
    7fb40dba80af:	41 83 e0 01          	and    $0x1,%r8d
    7fb40dba80b3:	45 8b c8             	mov    %r8d,%r9d
    7fb40dba80b6:	41 d1 e1             	shl    %r9d
    7fb40dba80b9:	45 0b c8             	or     %r8d,%r9d
    7fb40dba80bc:	44 89 85 58 f7 ff ff 	mov    %r8d,-0x8a8(%rbp)
    7fb40dba80c3:	41 c1 e0 03          	shl    $0x3,%r8d
    7fb40dba80c7:	45 0b c8             	or     %r8d,%r9d
    7fb40dba80ca:	44 8b 85 58 f7 ff ff 	mov    -0x8a8(%rbp),%r8d
    7fb40dba80d1:	41 c1 e0 04          	shl    $0x4,%r8d
    7fb40dba80d5:	45 0b c8             	or     %r8d,%r9d
    7fb40dba80d8:	41 33 f9             	xor    %r9d,%edi
    7fb40dba80db:	44 8b c7             	mov    %edi,%r8d
    7fb40dba80de:	44 33 c2             	xor    %edx,%r8d
    7fb40dba80e1:	44 33 c1             	xor    %ecx,%r8d
    7fb40dba80e4:	4d 0f b6 8f 86 01 00 	movzbq 0x186(%r15),%r9
    7fb40dba80eb:	00 
    7fb40dba80ec:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba80ef:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba80f4:	45 33 c1             	xor    %r9d,%r8d
    7fb40dba80f7:	44 89 95 50 f7 ff ff 	mov    %r10d,-0x8b0(%rbp)
    7fb40dba80fe:	4d 0f b6 97 8b 01 00 	movzbq 0x18b(%r15),%r10
    7fb40dba8105:	00 
    7fb40dba8106:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba8109:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba810e:	45 33 c2             	xor    %r10d,%r8d
    7fb40dba8111:	33 f8                	xor    %eax,%edi
    7fb40dba8113:	44 89 8d 48 f7 ff ff 	mov    %r9d,-0x8b8(%rbp)
    7fb40dba811a:	41 83 e1 7f          	and    $0x7f,%r9d
    7fb40dba811e:	41 d1 e1             	shl    %r9d
    7fb40dba8121:	89 9d 40 f7 ff ff    	mov    %ebx,-0x8c0(%rbp)
    7fb40dba8127:	8b 9d 48 f7 ff ff    	mov    -0x8b8(%rbp),%ebx
    7fb40dba812d:	c1 eb 07             	shr    $0x7,%ebx
    7fb40dba8130:	83 e3 01             	and    $0x1,%ebx
    7fb40dba8133:	89 9d 38 f7 ff ff    	mov    %ebx,-0x8c8(%rbp)
    7fb40dba8139:	d1 e3                	shl    %ebx
    7fb40dba813b:	44 89 9d 30 f7 ff ff 	mov    %r11d,-0x8d0(%rbp)
    7fb40dba8142:	44 8b 9d 38 f7 ff ff 	mov    -0x8c8(%rbp),%r11d
    7fb40dba8149:	41 0b db             	or     %r11d,%ebx
    7fb40dba814c:	41 c1 e3 03          	shl    $0x3,%r11d
    7fb40dba8150:	41 0b db             	or     %r11d,%ebx
    7fb40dba8153:	44 8b 9d 38 f7 ff ff 	mov    -0x8c8(%rbp),%r11d
    7fb40dba815a:	41 c1 e3 04          	shl    $0x4,%r11d
    7fb40dba815e:	41 0b db             	or     %r11d,%ebx
    7fb40dba8161:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba8164:	41 8b d9             	mov    %r9d,%ebx
    7fb40dba8167:	44 8b 9d 48 f7 ff ff 	mov    -0x8b8(%rbp),%r11d
    7fb40dba816e:	41 33 db             	xor    %r11d,%ebx
    7fb40dba8171:	33 fb                	xor    %ebx,%edi
    7fb40dba8173:	41 33 fa             	xor    %r10d,%edi
    7fb40dba8176:	8b d8                	mov    %eax,%ebx
    7fb40dba8178:	33 da                	xor    %edx,%ebx
    7fb40dba817a:	44 33 cb             	xor    %ebx,%r9d
    7fb40dba817d:	41 8b da             	mov    %r10d,%ebx
    7fb40dba8180:	83 e3 7f             	and    $0x7f,%ebx
    7fb40dba8183:	d1 e3                	shl    %ebx
    7fb40dba8185:	45 8b da             	mov    %r10d,%r11d
    7fb40dba8188:	41 c1 eb 07          	shr    $0x7,%r11d
    7fb40dba818c:	41 83 e3 01          	and    $0x1,%r11d
    7fb40dba8190:	44 89 9d 28 f7 ff ff 	mov    %r11d,-0x8d8(%rbp)
    7fb40dba8197:	41 d1 e3             	shl    %r11d
    7fb40dba819a:	89 b5 20 f7 ff ff    	mov    %esi,-0x8e0(%rbp)
    7fb40dba81a0:	8b b5 28 f7 ff ff    	mov    -0x8d8(%rbp),%esi
    7fb40dba81a6:	44 0b de             	or     %esi,%r11d
    7fb40dba81a9:	c1 e6 03             	shl    $0x3,%esi
    7fb40dba81ac:	44 0b de             	or     %esi,%r11d
    7fb40dba81af:	8b b5 28 f7 ff ff    	mov    -0x8d8(%rbp),%esi
    7fb40dba81b5:	c1 e6 04             	shl    $0x4,%esi
    7fb40dba81b8:	44 0b de             	or     %esi,%r11d
    7fb40dba81bb:	41 33 db             	xor    %r11d,%ebx
    7fb40dba81be:	44 33 d3             	xor    %ebx,%r10d
    7fb40dba81c1:	45 33 ca             	xor    %r10d,%r9d
    7fb40dba81c4:	33 c8                	xor    %eax,%ecx
    7fb40dba81c6:	33 d1                	xor    %ecx,%edx
    7fb40dba81c8:	33 95 48 f7 ff ff    	xor    -0x8b8(%rbp),%edx
    7fb40dba81ce:	33 da                	xor    %edx,%ebx
    7fb40dba81d0:	8b 85 c0 f7 ff ff    	mov    -0x840(%rbp),%eax
    7fb40dba81d6:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba81d9:	8b 8d d0 f7 ff ff    	mov    -0x830(%rbp),%ecx
    7fb40dba81df:	0b c1                	or     %ecx,%eax
    7fb40dba81e1:	8b 8d b0 f7 ff ff    	mov    -0x850(%rbp),%ecx
    7fb40dba81e7:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba81ea:	0b c1                	or     %ecx,%eax
    7fb40dba81ec:	8b 8d a0 f7 ff ff    	mov    -0x860(%rbp),%ecx
    7fb40dba81f2:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba81f5:	0b c1                	or     %ecx,%eax
    7fb40dba81f7:	8b 8d 90 f7 ff ff    	mov    -0x870(%rbp),%ecx
    7fb40dba81fd:	8b c9                	mov    %ecx,%ecx
    7fb40dba81ff:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba8203:	8b c0                	mov    %eax,%eax
    7fb40dba8205:	48 0b c8             	or     %rax,%rcx
    7fb40dba8208:	8b 85 80 f7 ff ff    	mov    -0x880(%rbp),%eax
    7fb40dba820e:	8b c0                	mov    %eax,%eax
    7fb40dba8210:	48 c1 e0 28          	shl    $0x28,%rax
    7fb40dba8214:	48 0b c8             	or     %rax,%rcx
    7fb40dba8217:	8b 85 70 f7 ff ff    	mov    -0x890(%rbp),%eax
    7fb40dba821d:	8b c0                	mov    %eax,%eax
    7fb40dba821f:	48 c1 e0 30          	shl    $0x30,%rax
    7fb40dba8223:	48 0b c8             	or     %rax,%rcx
    7fb40dba8226:	8b 85 60 f7 ff ff    	mov    -0x8a0(%rbp),%eax
    7fb40dba822c:	8b c0                	mov    %eax,%eax
    7fb40dba822e:	48 c1 e0 38          	shl    $0x38,%rax
    7fb40dba8232:	48 0b c8             	or     %rax,%rcx
    7fb40dba8235:	49 89 8f e0 02 00 00 	mov    %rcx,0x2e0(%r15)
    7fb40dba823c:	8b 85 40 f7 ff ff    	mov    -0x8c0(%rbp),%eax
    7fb40dba8242:	c1 e0 08             	shl    $0x8,%eax
    7fb40dba8245:	8b 8d 50 f7 ff ff    	mov    -0x8b0(%rbp),%ecx
    7fb40dba824b:	0b c1                	or     %ecx,%eax
    7fb40dba824d:	8b 8d 30 f7 ff ff    	mov    -0x8d0(%rbp),%ecx
    7fb40dba8253:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba8256:	0b c1                	or     %ecx,%eax
    7fb40dba8258:	8b 8d 20 f7 ff ff    	mov    -0x8e0(%rbp),%ecx
    7fb40dba825e:	c1 e1 18             	shl    $0x18,%ecx
    7fb40dba8261:	0b c1                	or     %ecx,%eax
    7fb40dba8263:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba8266:	49 c1 e0 20          	shl    $0x20,%r8
    7fb40dba826a:	8b c0                	mov    %eax,%eax
    7fb40dba826c:	4c 0b c0             	or     %rax,%r8
    7fb40dba826f:	8b ff                	mov    %edi,%edi
    7fb40dba8271:	48 c1 e7 28          	shl    $0x28,%rdi
    7fb40dba8275:	4c 0b c7             	or     %rdi,%r8
    7fb40dba8278:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba827b:	49 c1 e1 30          	shl    $0x30,%r9
    7fb40dba827f:	4d 0b c1             	or     %r9,%r8
    7fb40dba8282:	8b db                	mov    %ebx,%ebx
    7fb40dba8284:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba8288:	4c 0b c3             	or     %rbx,%r8
    7fb40dba828b:	4d 89 87 e8 02 00 00 	mov    %r8,0x2e8(%r15)
    7fb40dba8292:	8b 85 f0 f7 ff ff    	mov    -0x810(%rbp),%eax
    7fb40dba8298:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba829d:	8b c0                	mov    %eax,%eax
    7fb40dba829f:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba82a4:	8b 8d f0 f7 ff ff    	mov    -0x810(%rbp),%ecx
    7fb40dba82aa:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba82ad:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba82b3:	8b c9                	mov    %ecx,%ecx
    7fb40dba82b5:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba82ba:	8b 95 f0 f7 ff ff    	mov    -0x810(%rbp),%edx
    7fb40dba82c0:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba82c3:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba82c9:	8b d2                	mov    %edx,%edx
    7fb40dba82cb:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba82d0:	8b 9d f0 f7 ff ff    	mov    -0x810(%rbp),%ebx
    7fb40dba82d6:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba82d9:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba82df:	8b db                	mov    %ebx,%ebx
    7fb40dba82e1:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba82e6:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba82e9:	0b da                	or     %edx,%ebx
    7fb40dba82eb:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba82ee:	0b d9                	or     %ecx,%ebx
    7fb40dba82f0:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba82f3:	0b d8                	or     %eax,%ebx
    7fb40dba82f5:	83 f3 1b             	xor    $0x1b,%ebx
    7fb40dba82f8:	8b 85 00 f8 ff ff    	mov    -0x800(%rbp),%eax
    7fb40dba82fe:	33 d8                	xor    %eax,%ebx
    7fb40dba8300:	8b 85 10 f8 ff ff    	mov    -0x7f0(%rbp),%eax
    7fb40dba8306:	33 c3                	xor    %ebx,%eax
    7fb40dba8308:	8b 8d e0 f7 ff ff    	mov    -0x820(%rbp),%ecx
    7fb40dba830e:	33 c8                	xor    %eax,%ecx
    7fb40dba8310:	8b 95 f0 f7 ff ff    	mov    -0x810(%rbp),%edx
    7fb40dba8316:	33 d1                	xor    %ecx,%edx
    7fb40dba8318:	8b f0                	mov    %eax,%esi
    7fb40dba831a:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba831e:	8b fb                	mov    %ebx,%edi
    7fb40dba8320:	48 0b f7             	or     %rdi,%rsi
    7fb40dba8323:	49 89 b7 40 02 00 00 	mov    %rsi,0x240(%r15)
    7fb40dba832a:	8b f2                	mov    %edx,%esi
    7fb40dba832c:	48 c1 e6 20          	shl    $0x20,%rsi
    7fb40dba8330:	8b f9                	mov    %ecx,%edi
    7fb40dba8332:	48 0b f7             	or     %rdi,%rsi
    7fb40dba8335:	49 89 b7 48 02 00 00 	mov    %rsi,0x248(%r15)
    7fb40dba833c:	49 8b b7 e0 02 00 00 	mov    0x2e0(%r15),%rsi
    7fb40dba8343:	49 8b bf 40 02 00 00 	mov    0x240(%r15),%rdi
    7fb40dba834a:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba834d:	49 89 b7 90 03 00 00 	mov    %rsi,0x390(%r15)
    7fb40dba8354:	49 8b b7 e8 02 00 00 	mov    0x2e8(%r15),%rsi
    7fb40dba835b:	49 8b bf 48 02 00 00 	mov    0x248(%r15),%rdi
    7fb40dba8362:	48 33 f7             	xor    %rdi,%rsi
    7fb40dba8365:	49 89 b7 98 03 00 00 	mov    %rsi,0x398(%r15)
    7fb40dba836c:	49 0f b6 b7 9f 01 00 	movzbq 0x19f(%r15),%rsi
    7fb40dba8373:	00 
    7fb40dba8374:	8b f6                	mov    %esi,%esi
    7fb40dba8376:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba837b:	49 0f b6 bf 9e 01 00 	movzbq 0x19e(%r15),%rdi
    7fb40dba8382:	00 
    7fb40dba8383:	8b ff                	mov    %edi,%edi
    7fb40dba8385:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba838a:	4d 0f b6 87 9d 01 00 	movzbq 0x19d(%r15),%r8
    7fb40dba8391:	00 
    7fb40dba8392:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba8395:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba839a:	4d 0f b6 8f 9c 01 00 	movzbq 0x19c(%r15),%r9
    7fb40dba83a1:	00 
    7fb40dba83a2:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba83a5:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba83aa:	4d 0f b6 97 9a 01 00 	movzbq 0x19a(%r15),%r10
    7fb40dba83b1:	00 
    7fb40dba83b2:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba83b5:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba83ba:	4d 0f b6 9f 99 01 00 	movzbq 0x199(%r15),%r11
    7fb40dba83c1:	00 
    7fb40dba83c2:	45 8b db             	mov    %r11d,%r11d
    7fb40dba83c5:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba83ca:	89 85 18 f7 ff ff    	mov    %eax,-0x8e8(%rbp)
    7fb40dba83d0:	49 0f b6 87 98 01 00 	movzbq 0x198(%r15),%rax
    7fb40dba83d7:	00 
    7fb40dba83d8:	8b c0                	mov    %eax,%eax
    7fb40dba83da:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba83df:	89 9d 10 f7 ff ff    	mov    %ebx,-0x8f0(%rbp)
    7fb40dba83e5:	49 0f b6 9f 9b 01 00 	movzbq 0x19b(%r15),%rbx
    7fb40dba83ec:	00 
    7fb40dba83ed:	8b db                	mov    %ebx,%ebx
    7fb40dba83ef:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba83f4:	89 95 08 f7 ff ff    	mov    %edx,-0x8f8(%rbp)
    7fb40dba83fa:	49 0f b6 97 95 01 00 	movzbq 0x195(%r15),%rdx
    7fb40dba8401:	00 
    7fb40dba8402:	8b d2                	mov    %edx,%edx
    7fb40dba8404:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba8409:	89 8d 00 f7 ff ff    	mov    %ecx,-0x900(%rbp)
    7fb40dba840f:	49 0f b6 8f 94 01 00 	movzbq 0x194(%r15),%rcx
    7fb40dba8416:	00 
    7fb40dba8417:	8b c9                	mov    %ecx,%ecx
    7fb40dba8419:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba841e:	89 b5 f8 f6 ff ff    	mov    %esi,-0x908(%rbp)
    7fb40dba8424:	49 0f b6 b7 97 01 00 	movzbq 0x197(%r15),%rsi
    7fb40dba842b:	00 
    7fb40dba842c:	8b f6                	mov    %esi,%esi
    7fb40dba842e:	41 0f b6 34 37       	movzbl (%r15,%rsi,1),%esi
    7fb40dba8433:	89 bd f0 f6 ff ff    	mov    %edi,-0x910(%rbp)
    7fb40dba8439:	49 0f b6 bf 96 01 00 	movzbq 0x196(%r15),%rdi
    7fb40dba8440:	00 
    7fb40dba8441:	8b ff                	mov    %edi,%edi
    7fb40dba8443:	41 0f b6 3c 3f       	movzbl (%r15,%rdi,1),%edi
    7fb40dba8448:	44 89 85 e8 f6 ff ff 	mov    %r8d,-0x918(%rbp)
    7fb40dba844f:	4d 0f b6 87 90 01 00 	movzbq 0x190(%r15),%r8
    7fb40dba8456:	00 
    7fb40dba8457:	45 8b c0             	mov    %r8d,%r8d
    7fb40dba845a:	47 0f b6 04 07       	movzbl (%r15,%r8,1),%r8d
    7fb40dba845f:	44 89 8d e0 f6 ff ff 	mov    %r9d,-0x920(%rbp)
    7fb40dba8466:	4d 0f b6 8f 93 01 00 	movzbq 0x193(%r15),%r9
    7fb40dba846d:	00 
    7fb40dba846e:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba8471:	47 0f b6 0c 0f       	movzbl (%r15,%r9,1),%r9d
    7fb40dba8476:	44 89 95 d8 f6 ff ff 	mov    %r10d,-0x928(%rbp)
    7fb40dba847d:	4d 0f b6 97 92 01 00 	movzbq 0x192(%r15),%r10
    7fb40dba8484:	00 
    7fb40dba8485:	45 8b d2             	mov    %r10d,%r10d
    7fb40dba8488:	47 0f b6 14 17       	movzbl (%r15,%r10,1),%r10d
    7fb40dba848d:	44 89 9d d0 f6 ff ff 	mov    %r11d,-0x930(%rbp)
    7fb40dba8494:	4d 0f b6 9f 91 01 00 	movzbq 0x191(%r15),%r11
    7fb40dba849b:	00 
    7fb40dba849c:	45 8b db             	mov    %r11d,%r11d
    7fb40dba849f:	47 0f b6 1c 1f       	movzbl (%r15,%r11,1),%r11d
    7fb40dba84a4:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba84a7:	44 0b c2             	or     %edx,%r8d
    7fb40dba84aa:	8b 95 d8 f6 ff ff    	mov    -0x928(%rbp),%edx
    7fb40dba84b0:	c1 e2 10             	shl    $0x10,%edx
    7fb40dba84b3:	44 0b c2             	or     %edx,%r8d
    7fb40dba84b6:	8b 95 f8 f6 ff ff    	mov    -0x908(%rbp),%edx
    7fb40dba84bc:	c1 e2 18             	shl    $0x18,%edx
    7fb40dba84bf:	44 0b c2             	or     %edx,%r8d
    7fb40dba84c2:	8b c9                	mov    %ecx,%ecx
    7fb40dba84c4:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba84c8:	41 8b d0             	mov    %r8d,%edx
    7fb40dba84cb:	48 0b ca             	or     %rdx,%rcx
    7fb40dba84ce:	8b 95 d0 f6 ff ff    	mov    -0x930(%rbp),%edx
    7fb40dba84d4:	8b d2                	mov    %edx,%edx
    7fb40dba84d6:	48 c1 e2 28          	shl    $0x28,%rdx
    7fb40dba84da:	48 0b ca             	or     %rdx,%rcx
    7fb40dba84dd:	8b 95 f0 f6 ff ff    	mov    -0x910(%rbp),%edx
    7fb40dba84e3:	8b d2                	mov    %edx,%edx
    7fb40dba84e5:	48 c1 e2 30          	shl    $0x30,%rdx
    7fb40dba84e9:	48 0b ca             	or     %rdx,%rcx
    7fb40dba84ec:	45 8b c9             	mov    %r9d,%r9d
    7fb40dba84ef:	49 c1 e1 38          	shl    $0x38,%r9
    7fb40dba84f3:	49 0b c9             	or     %r9,%rcx
    7fb40dba84f6:	49 89 8f f0 02 00 00 	mov    %rcx,0x2f0(%r15)
    7fb40dba84fd:	8b 8d e8 f6 ff ff    	mov    -0x918(%rbp),%ecx
    7fb40dba8503:	c1 e1 08             	shl    $0x8,%ecx
    7fb40dba8506:	0b c1                	or     %ecx,%eax
    7fb40dba8508:	41 c1 e2 10          	shl    $0x10,%r10d
    7fb40dba850c:	41 0b c2             	or     %r10d,%eax
    7fb40dba850f:	c1 e6 18             	shl    $0x18,%esi
    7fb40dba8512:	0b c6                	or     %esi,%eax
    7fb40dba8514:	8b 8d e0 f6 ff ff    	mov    -0x920(%rbp),%ecx
    7fb40dba851a:	8b c9                	mov    %ecx,%ecx
    7fb40dba851c:	48 c1 e1 20          	shl    $0x20,%rcx
    7fb40dba8520:	8b c0                	mov    %eax,%eax
    7fb40dba8522:	48 0b c8             	or     %rax,%rcx
    7fb40dba8525:	45 8b db             	mov    %r11d,%r11d
    7fb40dba8528:	49 c1 e3 28          	shl    $0x28,%r11
    7fb40dba852c:	49 0b cb             	or     %r11,%rcx
    7fb40dba852f:	8b ff                	mov    %edi,%edi
    7fb40dba8531:	48 c1 e7 30          	shl    $0x30,%rdi
    7fb40dba8535:	48 0b cf             	or     %rdi,%rcx
    7fb40dba8538:	8b db                	mov    %ebx,%ebx
    7fb40dba853a:	48 c1 e3 38          	shl    $0x38,%rbx
    7fb40dba853e:	48 0b cb             	or     %rbx,%rcx
    7fb40dba8541:	49 89 8f f8 02 00 00 	mov    %rcx,0x2f8(%r15)
    7fb40dba8548:	8b 85 08 f7 ff ff    	mov    -0x8f8(%rbp),%eax
    7fb40dba854e:	25 ff 00 00 00       	and    $0xff,%eax
    7fb40dba8553:	8b c0                	mov    %eax,%eax
    7fb40dba8555:	41 0f b6 04 07       	movzbl (%r15,%rax,1),%eax
    7fb40dba855a:	8b 8d 08 f7 ff ff    	mov    -0x8f8(%rbp),%ecx
    7fb40dba8560:	c1 e9 18             	shr    $0x18,%ecx
    7fb40dba8563:	81 e1 ff 00 00 00    	and    $0xff,%ecx
    7fb40dba8569:	8b c9                	mov    %ecx,%ecx
    7fb40dba856b:	41 0f b6 0c 0f       	movzbl (%r15,%rcx,1),%ecx
    7fb40dba8570:	8b 95 08 f7 ff ff    	mov    -0x8f8(%rbp),%edx
    7fb40dba8576:	c1 ea 10             	shr    $0x10,%edx
    7fb40dba8579:	81 e2 ff 00 00 00    	and    $0xff,%edx
    7fb40dba857f:	8b d2                	mov    %edx,%edx
    7fb40dba8581:	41 0f b6 14 17       	movzbl (%r15,%rdx,1),%edx
    7fb40dba8586:	8b 9d 08 f7 ff ff    	mov    -0x8f8(%rbp),%ebx
    7fb40dba858c:	c1 eb 08             	shr    $0x8,%ebx
    7fb40dba858f:	81 e3 ff 00 00 00    	and    $0xff,%ebx
    7fb40dba8595:	8b db                	mov    %ebx,%ebx
    7fb40dba8597:	41 0f b6 1c 1f       	movzbl (%r15,%rbx,1),%ebx
    7fb40dba859c:	c1 e2 08             	shl    $0x8,%edx
    7fb40dba859f:	0b da                	or     %edx,%ebx
    7fb40dba85a1:	c1 e1 10             	shl    $0x10,%ecx
    7fb40dba85a4:	0b d9                	or     %ecx,%ebx
    7fb40dba85a6:	c1 e0 18             	shl    $0x18,%eax
    7fb40dba85a9:	0b d8                	or     %eax,%ebx
    7fb40dba85ab:	83 f3 36             	xor    $0x36,%ebx
    7fb40dba85ae:	8b 85 10 f7 ff ff    	mov    -0x8f0(%rbp),%eax
    7fb40dba85b4:	33 d8                	xor    %eax,%ebx
    7fb40dba85b6:	8b 85 18 f7 ff ff    	mov    -0x8e8(%rbp),%eax
    7fb40dba85bc:	33 c3                	xor    %ebx,%eax
    7fb40dba85be:	8b 8d 00 f7 ff ff    	mov    -0x900(%rbp),%ecx
    7fb40dba85c4:	33 c8                	xor    %eax,%ecx
    7fb40dba85c6:	8b 95 08 f7 ff ff    	mov    -0x8f8(%rbp),%edx
    7fb40dba85cc:	33 d1                	xor    %ecx,%edx
    7fb40dba85ce:	8b c0                	mov    %eax,%eax
    7fb40dba85d0:	48 c1 e0 20          	shl    $0x20,%rax
    7fb40dba85d4:	8b db                	mov    %ebx,%ebx
    7fb40dba85d6:	48 0b c3             	or     %rbx,%rax
    7fb40dba85d9:	49 89 87 50 02 00 00 	mov    %rax,0x250(%r15)
    7fb40dba85e0:	8b d2                	mov    %edx,%edx
    7fb40dba85e2:	48 c1 e2 20          	shl    $0x20,%rdx
    7fb40dba85e6:	8b c9                	mov    %ecx,%ecx
    7fb40dba85e8:	48 0b d1             	or     %rcx,%rdx
    7fb40dba85eb:	49 89 97 58 02 00 00 	mov    %rdx,0x258(%r15)
    7fb40dba85f2:	49 8b 87 f0 02 00 00 	mov    0x2f0(%r15),%rax
    7fb40dba85f9:	49 8b 8f 50 02 00 00 	mov    0x250(%r15),%rcx
    7fb40dba8600:	48 33 c1             	xor    %rcx,%rax
    7fb40dba8603:	49 89 87 a0 03 00 00 	mov    %rax,0x3a0(%r15)
    7fb40dba860a:	49 8b 87 f8 02 00 00 	mov    0x2f8(%r15),%rax
    7fb40dba8611:	49 8b 8f 58 02 00 00 	mov    0x258(%r15),%rcx
    7fb40dba8618:	48 33 c1             	xor    %rcx,%rax
    7fb40dba861b:	49 89 87 a8 03 00 00 	mov    %rax,0x3a8(%r15)
    7fb40dba8622:	49 8b 46 10          	mov    0x10(%r14),%rax
    7fb40dba8626:	8b 00                	mov    (%rax),%eax
    7fb40dba8628:	89 85 c8 f6 ff ff    	mov    %eax,-0x938(%rbp)
    7fb40dba862e:	49 8b 46 20          	mov    0x20(%r14),%rax
    7fb40dba8632:	8b 00                	mov    (%rax),%eax
    7fb40dba8634:	85 c0                	test   %eax,%eax
    7fb40dba8636:	0f 84 1e 00 00 00    	je     0x7fb40dba865a
    7fb40dba863c:	41 c7 87 b0 01 00 00 	movl   $0x0,0x1b0(%r15)
    7fb40dba8643:	00 00 00 00 
    7fb40dba8647:	45 33 ed             	xor    %r13d,%r13d
    7fb40dba864a:	41 c7 87 b8 01 00 00 	movl   $0x0,0x1b8(%r15)
    7fb40dba8651:	00 00 00 00 
    7fb40dba8655:	e9 2a 00 00 00       	jmpq   0x7fb40dba8684
    7fb40dba865a:	41 8b 87 b8 01 00 00 	mov    0x1b8(%r15),%eax
    7fb40dba8661:	8b c8                	mov    %eax,%ecx
    7fb40dba8663:	83 e1 01             	and    $0x1,%ecx
    7fb40dba8666:	41 89 8f b0 01 00 00 	mov    %ecx,0x1b0(%r15)
    7fb40dba866d:	4c 8b e9             	mov    %rcx,%r13
    7fb40dba8670:	d1 e8                	shr    %eax
    7fb40dba8672:	8b 8d c8 f6 ff ff    	mov    -0x938(%rbp),%ecx
    7fb40dba8678:	c1 e1 09             	shl    $0x9,%ecx
    7fb40dba867b:	0b c1                	or     %ecx,%eax
    7fb40dba867d:	41 89 87 b8 01 00 00 	mov    %eax,0x1b8(%r15)
    7fb40dba8684:	49 8b c7             	mov    %r15,%rax
    7fb40dba8687:	48 05 a0 01 00 00    	add    $0x1a0,%rax
    7fb40dba868d:	49 8b cf             	mov    %r15,%rcx
    7fb40dba8690:	48 81 c1 a0 03 00 00 	add    $0x3a0,%rcx
    7fb40dba8697:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba869a:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba869d:	49 8b c7             	mov    %r15,%rax
    7fb40dba86a0:	48 05 90 01 00 00    	add    $0x190,%rax
    7fb40dba86a6:	49 8b cf             	mov    %r15,%rcx
    7fb40dba86a9:	48 81 c1 90 03 00 00 	add    $0x390,%rcx
    7fb40dba86b0:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba86b3:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba86b6:	49 8b c7             	mov    %r15,%rax
    7fb40dba86b9:	48 05 80 01 00 00    	add    $0x180,%rax
    7fb40dba86bf:	49 8b cf             	mov    %r15,%rcx
    7fb40dba86c2:	48 81 c1 80 03 00 00 	add    $0x380,%rcx
    7fb40dba86c9:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba86cc:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba86cf:	49 8b c7             	mov    %r15,%rax
    7fb40dba86d2:	48 05 70 01 00 00    	add    $0x170,%rax
    7fb40dba86d8:	49 8b cf             	mov    %r15,%rcx
    7fb40dba86db:	48 81 c1 70 03 00 00 	add    $0x370,%rcx
    7fb40dba86e2:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba86e5:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba86e8:	49 8b c7             	mov    %r15,%rax
    7fb40dba86eb:	48 05 60 01 00 00    	add    $0x160,%rax
    7fb40dba86f1:	49 8b cf             	mov    %r15,%rcx
    7fb40dba86f4:	48 81 c1 60 03 00 00 	add    $0x360,%rcx
    7fb40dba86fb:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba86fe:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba8701:	49 8b c7             	mov    %r15,%rax
    7fb40dba8704:	48 05 50 01 00 00    	add    $0x150,%rax
    7fb40dba870a:	49 8b cf             	mov    %r15,%rcx
    7fb40dba870d:	48 81 c1 50 03 00 00 	add    $0x350,%rcx
    7fb40dba8714:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba8717:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba871a:	49 8b c7             	mov    %r15,%rax
    7fb40dba871d:	48 05 40 01 00 00    	add    $0x140,%rax
    7fb40dba8723:	49 8b cf             	mov    %r15,%rcx
    7fb40dba8726:	48 81 c1 40 03 00 00 	add    $0x340,%rcx
    7fb40dba872d:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba8730:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba8733:	49 8b c7             	mov    %r15,%rax
    7fb40dba8736:	48 05 30 01 00 00    	add    $0x130,%rax
    7fb40dba873c:	49 8b cf             	mov    %r15,%rcx
    7fb40dba873f:	48 81 c1 30 03 00 00 	add    $0x330,%rcx
    7fb40dba8746:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba8749:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba874c:	49 8b c7             	mov    %r15,%rax
    7fb40dba874f:	48 05 20 01 00 00    	add    $0x120,%rax
    7fb40dba8755:	49 8b cf             	mov    %r15,%rcx
    7fb40dba8758:	48 81 c1 20 03 00 00 	add    $0x320,%rcx
    7fb40dba875f:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba8762:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba8765:	49 8b c7             	mov    %r15,%rax
    7fb40dba8768:	48 05 10 01 00 00    	add    $0x110,%rax
    7fb40dba876e:	49 8b cf             	mov    %r15,%rcx
    7fb40dba8771:	48 81 c1 10 03 00 00 	add    $0x310,%rcx
    7fb40dba8778:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba877b:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba877e:	49 8b c7             	mov    %r15,%rax
    7fb40dba8781:	48 05 00 01 00 00    	add    $0x100,%rax
    7fb40dba8787:	49 8b cf             	mov    %r15,%rcx
    7fb40dba878a:	48 81 c1 00 03 00 00 	add    $0x300,%rcx
    7fb40dba8791:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba8794:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba8797:	49 8b 46 28          	mov    0x28(%r14),%rax
    7fb40dba879b:	49 8b cf             	mov    %r15,%rcx
    7fb40dba879e:	48 81 c1 a0 01 00 00 	add    $0x1a0,%rcx
    7fb40dba87a5:	0f 10 01             	movups (%rcx),%xmm0
    7fb40dba87a8:	0f 11 00             	movups %xmm0,(%rax)
    7fb40dba87ab:	49 8b 46 30          	mov    0x30(%r14),%rax
    7fb40dba87af:	44 89 28             	mov    %r13d,(%rax)
    7fb40dba87b2:	33 c0                	xor    %eax,%eax
    7fb40dba87b4:	48 8b 1c 24          	mov    (%rsp),%rbx
    7fb40dba87b8:	4c 8b 64 24 08       	mov    0x8(%rsp),%r12
    7fb40dba87bd:	4c 8b 6c 24 10       	mov    0x10(%rsp),%r13
    7fb40dba87c2:	4c 8b 74 24 18       	mov    0x18(%rsp),%r14
    7fb40dba87c7:	4c 8b 7c 24 20       	mov    0x20(%rsp),%r15
    7fb40dba87cc:	48 8b e5             	mov    %rbp,%rsp
    7fb40dba87cf:	5d                   	pop    %rbp
    7fb40dba87d0:	c3                   	retq   

end

