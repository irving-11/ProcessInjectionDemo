
patch_poc:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 62 2f 00 00    	pushq  0x2f62(%rip)        # 3f88 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 63 2f 00 00 	bnd jmpq *0x2f63(%rip)        # 3f90 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	pushq  $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmpq 1020 <.plt>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	pushq  $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmpq 1020 <.plt>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	pushq  $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmpq 1020 <.plt>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	pushq  $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmpq 1020 <.plt>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	pushq  $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmpq 1020 <.plt>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	pushq  $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmpq 1020 <.plt>
    108f:	90                   	nop
    1090:	f3 0f 1e fa          	endbr64 
    1094:	68 06 00 00 00       	pushq  $0x6
    1099:	f2 e9 81 ff ff ff    	bnd jmpq 1020 <.plt>
    109f:	90                   	nop
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	68 07 00 00 00       	pushq  $0x7
    10a9:	f2 e9 71 ff ff ff    	bnd jmpq 1020 <.plt>
    10af:	90                   	nop

Disassembly of section .plt.got:

00000000000010b0 <__cxa_finalize@plt>:
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	f2 ff 25 3d 2f 00 00 	bnd jmpq *0x2f3d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    10bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

00000000000010c0 <puts@plt>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	f2 ff 25 cd 2e 00 00 	bnd jmpq *0x2ecd(%rip)        # 3f98 <puts@GLIBC_2.2.5>
    10cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010d0 <__stack_chk_fail@plt>:
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	f2 ff 25 c5 2e 00 00 	bnd jmpq *0x2ec5(%rip)        # 3fa0 <__stack_chk_fail@GLIBC_2.4>
    10db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010e0 <printf@plt>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	f2 ff 25 bd 2e 00 00 	bnd jmpq *0x2ebd(%rip)        # 3fa8 <printf@GLIBC_2.2.5>
    10eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010f0 <__assert_fail@plt>:
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	f2 ff 25 b5 2e 00 00 	bnd jmpq *0x2eb5(%rip)        # 3fb0 <__assert_fail@GLIBC_2.2.5>
    10fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001100 <memcpy@plt>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	f2 ff 25 ad 2e 00 00 	bnd jmpq *0x2ead(%rip)        # 3fb8 <memcpy@GLIBC_2.14>
    110b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001110 <fflush@plt>:
    1110:	f3 0f 1e fa          	endbr64 
    1114:	f2 ff 25 a5 2e 00 00 	bnd jmpq *0x2ea5(%rip)        # 3fc0 <fflush@GLIBC_2.2.5>
    111b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001120 <mprotect@plt>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	f2 ff 25 9d 2e 00 00 	bnd jmpq *0x2e9d(%rip)        # 3fc8 <mprotect@GLIBC_2.2.5>
    112b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001130 <sysconf@plt>:
    1130:	f3 0f 1e fa          	endbr64 
    1134:	f2 ff 25 95 2e 00 00 	bnd jmpq *0x2e95(%rip)        # 3fd0 <sysconf@GLIBC_2.2.5>
    113b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001140 <_start>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	31 ed                	xor    %ebp,%ebp
    1146:	49 89 d1             	mov    %rdx,%r9
    1149:	5e                   	pop    %rsi
    114a:	48 89 e2             	mov    %rsp,%rdx
    114d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1151:	50                   	push   %rax
    1152:	54                   	push   %rsp
    1153:	4c 8d 05 d6 07 00 00 	lea    0x7d6(%rip),%r8        # 1930 <__libc_csu_fini>
    115a:	48 8d 0d 5f 07 00 00 	lea    0x75f(%rip),%rcx        # 18c0 <__libc_csu_init>
    1161:	48 8d 3d 7d 05 00 00 	lea    0x57d(%rip),%rdi        # 16e5 <main>
    1168:	ff 15 72 2e 00 00    	callq  *0x2e72(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    116e:	f4                   	hlt    
    116f:	90                   	nop

0000000000001170 <deregister_tm_clones>:
    1170:	48 8d 3d 99 2e 00 00 	lea    0x2e99(%rip),%rdi        # 4010 <stdout@@GLIBC_2.2.5>
    1177:	48 8d 05 92 2e 00 00 	lea    0x2e92(%rip),%rax        # 4010 <stdout@@GLIBC_2.2.5>
    117e:	48 39 f8             	cmp    %rdi,%rax
    1181:	74 15                	je     1198 <deregister_tm_clones+0x28>
    1183:	48 8b 05 4e 2e 00 00 	mov    0x2e4e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    118a:	48 85 c0             	test   %rax,%rax
    118d:	74 09                	je     1198 <deregister_tm_clones+0x28>
    118f:	ff e0                	jmpq   *%rax
    1191:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1198:	c3                   	retq   
    1199:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011a0 <register_tm_clones>:
    11a0:	48 8d 3d 69 2e 00 00 	lea    0x2e69(%rip),%rdi        # 4010 <stdout@@GLIBC_2.2.5>
    11a7:	48 8d 35 62 2e 00 00 	lea    0x2e62(%rip),%rsi        # 4010 <stdout@@GLIBC_2.2.5>
    11ae:	48 29 fe             	sub    %rdi,%rsi
    11b1:	48 89 f0             	mov    %rsi,%rax
    11b4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    11b8:	48 c1 f8 03          	sar    $0x3,%rax
    11bc:	48 01 c6             	add    %rax,%rsi
    11bf:	48 d1 fe             	sar    %rsi
    11c2:	74 14                	je     11d8 <register_tm_clones+0x38>
    11c4:	48 8b 05 25 2e 00 00 	mov    0x2e25(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    11cb:	48 85 c0             	test   %rax,%rax
    11ce:	74 08                	je     11d8 <register_tm_clones+0x38>
    11d0:	ff e0                	jmpq   *%rax
    11d2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    11d8:	c3                   	retq   
    11d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011e0 <__do_global_dtors_aux>:
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	80 3d 2d 2e 00 00 00 	cmpb   $0x0,0x2e2d(%rip)        # 4018 <completed.8061>
    11eb:	75 2b                	jne    1218 <__do_global_dtors_aux+0x38>
    11ed:	55                   	push   %rbp
    11ee:	48 83 3d 02 2e 00 00 	cmpq   $0x0,0x2e02(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    11f5:	00 
    11f6:	48 89 e5             	mov    %rsp,%rbp
    11f9:	74 0c                	je     1207 <__do_global_dtors_aux+0x27>
    11fb:	48 8b 3d 06 2e 00 00 	mov    0x2e06(%rip),%rdi        # 4008 <__dso_handle>
    1202:	e8 a9 fe ff ff       	callq  10b0 <__cxa_finalize@plt>
    1207:	e8 64 ff ff ff       	callq  1170 <deregister_tm_clones>
    120c:	c6 05 05 2e 00 00 01 	movb   $0x1,0x2e05(%rip)        # 4018 <completed.8061>
    1213:	5d                   	pop    %rbp
    1214:	c3                   	retq   
    1215:	0f 1f 00             	nopl   (%rax)
    1218:	c3                   	retq   
    1219:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001220 <frame_dummy>:
    1220:	f3 0f 1e fa          	endbr64 
    1224:	e9 77 ff ff ff       	jmpq   11a0 <register_tm_clones>

0000000000001229 <rdtsc>:
void patch_handler();

#define offsetof(type, member) ((size_t) &((type *)0)->member)

static __inline__ uint64_t rdtsc(void)
{
    1229:	55                   	push   %rbp
    122a:	48 89 e5             	mov    %rsp,%rbp
	unsigned hi, lo;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    122d:	0f 31                	rdtsc  
    122f:	89 45 f8             	mov    %eax,-0x8(%rbp)
    1232:	89 55 fc             	mov    %edx,-0x4(%rbp)
	return ((uint64_t)lo) | ((uint64_t)hi << 32);
    1235:	8b 45 f8             	mov    -0x8(%rbp),%eax
    1238:	8b 55 fc             	mov    -0x4(%rbp),%edx
    123b:	48 c1 e2 20          	shl    $0x20,%rdx
    123f:	48 09 d0             	or     %rdx,%rax
}
    1242:	5d                   	pop    %rbp
    1243:	c3                   	retq   

0000000000001244 <tick_to_us>:

static inline uint32_t tick_to_us(uint64_t tick) {
    1244:	55                   	push   %rbp
    1245:	48 89 e5             	mov    %rsp,%rbp
    1248:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
	#define CYCLES_PER_MSEC(t)	((t) * 1e6)
	double CPU_GHZ = 2.2;
    124c:	f2 0f 10 05 04 10 00 	movsd  0x1004(%rip),%xmm0        # 2258 <__PRETTY_FUNCTION__.3270+0x10>
    1253:	00 
    1254:	f2 0f 11 45 f8       	movsd  %xmm0,-0x8(%rbp)
	return (tick * 1000) / CYCLES_PER_MSEC(CPU_GHZ);
    1259:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    125d:	48 69 c0 e8 03 00 00 	imul   $0x3e8,%rax,%rax
    1264:	48 85 c0             	test   %rax,%rax
    1267:	78 07                	js     1270 <tick_to_us+0x2c>
    1269:	f2 48 0f 2a c0       	cvtsi2sd %rax,%xmm0
    126e:	eb 15                	jmp    1285 <tick_to_us+0x41>
    1270:	48 89 c2             	mov    %rax,%rdx
    1273:	48 d1 ea             	shr    %rdx
    1276:	83 e0 01             	and    $0x1,%eax
    1279:	48 09 c2             	or     %rax,%rdx
    127c:	f2 48 0f 2a c2       	cvtsi2sd %rdx,%xmm0
    1281:	f2 0f 58 c0          	addsd  %xmm0,%xmm0
    1285:	f2 0f 10 55 f8       	movsd  -0x8(%rbp),%xmm2
    128a:	f2 0f 10 0d ce 0f 00 	movsd  0xfce(%rip),%xmm1        # 2260 <__PRETTY_FUNCTION__.3270+0x18>
    1291:	00 
    1292:	f2 0f 59 ca          	mulsd  %xmm2,%xmm1
    1296:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
    129a:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
}
    129f:	5d                   	pop    %rbp
    12a0:	c3                   	retq   

00000000000012a1 <DSU>:

// 48 b8 ff ff ff ff ff ff ff ff    movabs $0xffffffffffffffff,%rax
// ff e0                            jmpq   *%rax
void DSU(void *old, void *new) {
    12a1:	f3 0f 1e fa          	endbr64 
    12a5:	55                   	push   %rbp
    12a6:	48 89 e5             	mov    %rsp,%rbp
    12a9:	48 83 ec 30          	sub    $0x30,%rsp
    12ad:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    12b1:	48 89 75 d0          	mov    %rsi,-0x30(%rbp)
	#define ROUNDDOWN(ptr) ((void *)(((uintptr_t)ptr) & ~0xfff))
	size_t pg_size = sysconf(_SC_PAGESIZE);
    12b5:	bf 1e 00 00 00       	mov    $0x1e,%edi
    12ba:	e8 71 fe ff ff       	callq  1130 <sysconf@plt>
    12bf:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
	char *pg_boundary = ROUNDDOWN(old);
    12c3:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    12c7:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
    12cd:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
	int flags = PROT_WRITE | PROT_READ | PROT_EXEC;
    12d1:	c7 45 ec 07 00 00 00 	movl   $0x7,-0x14(%rbp)

	printf("Dynamically updating... "); fflush(stdout);
    12d8:	48 8d 3d 29 0d 00 00 	lea    0xd29(%rip),%rdi        # 2008 <_IO_stdin_used+0x8>
    12df:	b8 00 00 00 00       	mov    $0x0,%eax
    12e4:	e8 f7 fd ff ff       	callq  10e0 <printf@plt>
    12e9:	48 8b 05 20 2d 00 00 	mov    0x2d20(%rip),%rax        # 4010 <stdout@@GLIBC_2.2.5>
    12f0:	48 89 c7             	mov    %rax,%rdi
    12f3:	e8 18 fe ff ff       	callq  1110 <fflush@plt>

	mprotect(pg_boundary, 2 * pg_size, flags);
    12f8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    12fc:	48 8d 0c 00          	lea    (%rax,%rax,1),%rcx
    1300:	8b 55 ec             	mov    -0x14(%rbp),%edx
    1303:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1307:	48 89 ce             	mov    %rcx,%rsi
    130a:	48 89 c7             	mov    %rax,%rdi
    130d:	e8 0e fe ff ff       	callq  1120 <mprotect@plt>
	memcpy(old +  0, "\x48\xb8", 2);
    1312:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1316:	ba 02 00 00 00       	mov    $0x2,%edx
    131b:	48 8d 35 ff 0c 00 00 	lea    0xcff(%rip),%rsi        # 2021 <_IO_stdin_used+0x21>
    1322:	48 89 c7             	mov    %rax,%rdi
    1325:	e8 d6 fd ff ff       	callq  1100 <memcpy@plt>
	memcpy(old +  2,       &new, 8);
    132a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    132e:	48 8d 50 02          	lea    0x2(%rax),%rdx
    1332:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1336:	48 89 02             	mov    %rax,(%rdx)
	memcpy(old + 10, "\xff\xe0", 2);
    1339:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    133d:	48 83 c0 0a          	add    $0xa,%rax
    1341:	ba 02 00 00 00       	mov    $0x2,%edx
    1346:	48 8d 35 d7 0c 00 00 	lea    0xcd7(%rip),%rsi        # 2024 <_IO_stdin_used+0x24>
    134d:	48 89 c7             	mov    %rax,%rdi
    1350:	e8 ab fd ff ff       	callq  1100 <memcpy@plt>
	mprotect(pg_boundary, 2 * pg_size, flags & ~PROT_WRITE);
    1355:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1358:	83 e0 fd             	and    $0xfffffffd,%eax
    135b:	89 c2                	mov    %eax,%edx
    135d:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1361:	48 8d 0c 00          	lea    (%rax,%rax,1),%rcx
    1365:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1369:	48 89 ce             	mov    %rcx,%rsi
    136c:	48 89 c7             	mov    %rax,%rdi
    136f:	e8 ac fd ff ff       	callq  1120 <mprotect@plt>

	printf("Done\n"); fflush(stdout);
    1374:	48 8d 3d ac 0c 00 00 	lea    0xcac(%rip),%rdi        # 2027 <_IO_stdin_used+0x27>
    137b:	e8 40 fd ff ff       	callq  10c0 <puts@plt>
    1380:	48 8b 05 89 2c 00 00 	mov    0x2c89(%rip),%rax        # 4010 <stdout@@GLIBC_2.2.5>
    1387:	48 89 c7             	mov    %rax,%rdi
    138a:	e8 81 fd ff ff       	callq  1110 <fflush@plt>
}
    138f:	90                   	nop
    1390:	c9                   	leaveq 
    1391:	c3                   	retq   

0000000000001392 <old_func>:

void old_func() {
    1392:	f3 0f 1e fa          	endbr64 
    1396:	55                   	push   %rbp
    1397:	48 89 e5             	mov    %rsp,%rbp
	printf("This is Old Function\n");
    139a:	48 8d 3d 8b 0c 00 00 	lea    0xc8b(%rip),%rdi        # 202c <_IO_stdin_used+0x2c>
    13a1:	e8 1a fd ff ff       	callq  10c0 <puts@plt>
}
    13a6:	90                   	nop
    13a7:	5d                   	pop    %rbp
    13a8:	c3                   	retq   

00000000000013a9 <new_func>:

void new_func() {
    13a9:	f3 0f 1e fa          	endbr64 
    13ad:	55                   	push   %rbp
    13ae:	48 89 e5             	mov    %rsp,%rbp
	printf("This is New Function\n");
    13b1:	48 8d 3d 89 0c 00 00 	lea    0xc89(%rip),%rdi        # 2041 <_IO_stdin_used+0x41>
    13b8:	e8 03 fd ff ff       	callq  10c0 <puts@plt>
}
    13bd:	90                   	nop
    13be:	5d                   	pop    %rbp
    13bf:	c3                   	retq   

00000000000013c0 <func_to_patch>:
};

/*
前6个参数用寄存器传参：
*/
int func_to_patch(int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6) {
    13c0:	f3 0f 1e fa          	endbr64 
    13c4:	55                   	push   %rbp
    13c5:	48 89 e5             	mov    %rsp,%rbp
    13c8:	48 83 c4 80          	add    $0xffffffffffffff80,%rsp
    13cc:	89 7d ac             	mov    %edi,-0x54(%rbp)
    13cf:	48 89 75 a0          	mov    %rsi,-0x60(%rbp)
    13d3:	48 89 55 98          	mov    %rdx,-0x68(%rbp)
    13d7:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    13da:	4c 89 45 90          	mov    %r8,-0x70(%rbp)
    13de:	4c 89 4d 88          	mov    %r9,-0x78(%rbp)
	register uint64_t rsi asm("rsi");
	register uint64_t rdx asm("rdx");
	register uint64_t rcx asm("rcx");
	register uint64_t r8 asm("r8");
	register uint64_t r9 asm("r9");
	uint64_t bp = rbp;
    13e2:	48 89 6d c8          	mov    %rbp,-0x38(%rbp)
	uint64_t s1 = rdi, s2 = rsi, s3 = rdx, s4 = rcx, s5 = r8, s6 = r9;
    13e6:	48 89 7d d0          	mov    %rdi,-0x30(%rbp)
    13ea:	48 89 75 d8          	mov    %rsi,-0x28(%rbp)
    13ee:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
    13f2:	48 89 4d e8          	mov    %rcx,-0x18(%rbp)
    13f6:	4c 89 45 f0          	mov    %r8,-0x10(%rbp)
    13fa:	4c 89 4d f8          	mov    %r9,-0x8(%rbp)
	printf("rbp: %p\n", rbp);
    13fe:	48 89 e8             	mov    %rbp,%rax
    1401:	48 89 c6             	mov    %rax,%rsi
    1404:	48 8d 3d 4b 0c 00 00 	lea    0xc4b(%rip),%rdi        # 2056 <_IO_stdin_used+0x56>
    140b:	b8 00 00 00 00       	mov    $0x0,%eax
    1410:	e8 cb fc ff ff       	callq  10e0 <printf@plt>
	printf("[func_to_patch]\n a1:%d a2:%d a3:%d a4:%d a5:%d a6:%d\n", a1, *a2, *p3->p, a4, *a5, *p6->p);
    1415:	48 8b 45 88          	mov    -0x78(%rbp),%rax
    1419:	48 8b 00             	mov    (%rax),%rax
    141c:	8b 30                	mov    (%rax),%esi
    141e:	48 8b 45 90          	mov    -0x70(%rbp),%rax
    1422:	44 8b 00             	mov    (%rax),%r8d
    1425:	48 8b 45 98          	mov    -0x68(%rbp),%rax
    1429:	48 8b 00             	mov    (%rax),%rax
    142c:	8b 08                	mov    (%rax),%ecx
    142e:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
    1432:	8b 10                	mov    (%rax),%edx
    1434:	8b 7d a8             	mov    -0x58(%rbp),%edi
    1437:	8b 45 ac             	mov    -0x54(%rbp),%eax
    143a:	48 83 ec 08          	sub    $0x8,%rsp
    143e:	56                   	push   %rsi
    143f:	45 89 c1             	mov    %r8d,%r9d
    1442:	41 89 f8             	mov    %edi,%r8d
    1445:	89 c6                	mov    %eax,%esi
    1447:	48 8d 3d 12 0c 00 00 	lea    0xc12(%rip),%rdi        # 2060 <_IO_stdin_used+0x60>
    144e:	b8 00 00 00 00       	mov    $0x0,%eax
    1453:	e8 88 fc ff ff       	callq  10e0 <printf@plt>
    1458:	48 83 c4 10          	add    $0x10,%rsp

	// 从寄存器再次获取参数
	int a1_ = s1;
    145c:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1460:	89 45 b0             	mov    %eax,-0x50(%rbp)
	int a2_ = *(int *)s2;
    1463:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1467:	8b 00                	mov    (%rax),%eax
    1469:	89 45 b4             	mov    %eax,-0x4c(%rbp)
	int a3_ = *((struct ptr *)s3)->p;
    146c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1470:	48 8b 00             	mov    (%rax),%rax
    1473:	8b 00                	mov    (%rax),%eax
    1475:	89 45 b8             	mov    %eax,-0x48(%rbp)
	int a4_ = s4;
    1478:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    147c:	89 45 bc             	mov    %eax,-0x44(%rbp)
	int a5_ = *(int *)s5;
    147f:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1483:	8b 00                	mov    (%rax),%eax
    1485:	89 45 c0             	mov    %eax,-0x40(%rbp)
	int a6_ = *((struct ptr *)s6)->p;
    1488:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    148c:	48 8b 00             	mov    (%rax),%rax
    148f:	8b 00                	mov    (%rax),%eax
    1491:	89 45 c4             	mov    %eax,-0x3c(%rbp)
	printf("[from_register]\n a1:%d a2:%d a3:%d a4:%d a5:%d a6:%d\n", a1_, a2_, a3_, a4_, a5_, a6_);
    1494:	44 8b 45 c0          	mov    -0x40(%rbp),%r8d
    1498:	8b 7d bc             	mov    -0x44(%rbp),%edi
    149b:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    149e:	8b 55 b4             	mov    -0x4c(%rbp),%edx
    14a1:	8b 45 b0             	mov    -0x50(%rbp),%eax
    14a4:	48 83 ec 08          	sub    $0x8,%rsp
    14a8:	8b 75 c4             	mov    -0x3c(%rbp),%esi
    14ab:	56                   	push   %rsi
    14ac:	45 89 c1             	mov    %r8d,%r9d
    14af:	41 89 f8             	mov    %edi,%r8d
    14b2:	89 c6                	mov    %eax,%esi
    14b4:	48 8d 3d dd 0b 00 00 	lea    0xbdd(%rip),%rdi        # 2098 <_IO_stdin_used+0x98>
    14bb:	b8 00 00 00 00       	mov    $0x0,%eax
    14c0:	e8 1b fc ff ff       	callq  10e0 <printf@plt>
    14c5:	48 83 c4 10          	add    $0x10,%rsp

	return a1 + *a2 + *p3->p + a4 + *a5 + *p6->p;
    14c9:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
    14cd:	8b 10                	mov    (%rax),%edx
    14cf:	8b 45 ac             	mov    -0x54(%rbp),%eax
    14d2:	01 c2                	add    %eax,%edx
    14d4:	48 8b 45 98          	mov    -0x68(%rbp),%rax
    14d8:	48 8b 00             	mov    (%rax),%rax
    14db:	8b 00                	mov    (%rax),%eax
    14dd:	01 c2                	add    %eax,%edx
    14df:	8b 45 a8             	mov    -0x58(%rbp),%eax
    14e2:	01 c2                	add    %eax,%edx
    14e4:	48 8b 45 90          	mov    -0x70(%rbp),%rax
    14e8:	8b 00                	mov    (%rax),%eax
    14ea:	01 c2                	add    %eax,%edx
    14ec:	48 8b 45 88          	mov    -0x78(%rbp),%rax
    14f0:	48 8b 00             	mov    (%rax),%rax
    14f3:	8b 00                	mov    (%rax),%eax
    14f5:	01 d0                	add    %edx,%eax
}
    14f7:	c9                   	leaveq 
    14f8:	c3                   	retq   

00000000000014f9 <basic_test>:


static void basic_test() {
    14f9:	f3 0f 1e fa          	endbr64 
    14fd:	55                   	push   %rbp
    14fe:	48 89 e5             	mov    %rsp,%rbp
    1501:	48 83 ec 10          	sub    $0x10,%rsp
	uint64_t t1 = rdtsc();
    1505:	e8 1f fd ff ff       	callq  1229 <rdtsc>
    150a:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
	old_func();
    150e:	b8 00 00 00 00       	mov    $0x0,%eax
    1513:	e8 7a fe ff ff       	callq  1392 <old_func>
	DSU(old_func, new_func);
    1518:	48 8d 35 8a fe ff ff 	lea    -0x176(%rip),%rsi        # 13a9 <new_func>
    151f:	48 8d 3d 6c fe ff ff 	lea    -0x194(%rip),%rdi        # 1392 <old_func>
    1526:	e8 76 fd ff ff       	callq  12a1 <DSU>
	old_func();
    152b:	b8 00 00 00 00       	mov    $0x0,%eax
    1530:	e8 5d fe ff ff       	callq  1392 <old_func>
	uint64_t t2 = rdtsc() - t1;
    1535:	e8 ef fc ff ff       	callq  1229 <rdtsc>
    153a:	48 2b 45 f0          	sub    -0x10(%rbp),%rax
    153e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
	
	printf("stack_frame size:%d off1:%d off2:%d\n", sizeof(stack_frame), offsetof(stack_frame, a1), offsetof(stack_frame, a2));
    1542:	b9 08 00 00 00       	mov    $0x8,%ecx
    1547:	ba 00 00 00 00       	mov    $0x0,%edx
    154c:	be 30 00 00 00       	mov    $0x30,%esi
    1551:	48 8d 3d 78 0b 00 00 	lea    0xb78(%rip),%rdi        # 20d0 <_IO_stdin_used+0xd0>
    1558:	b8 00 00 00 00       	mov    $0x0,%eax
    155d:	e8 7e fb ff ff       	callq  10e0 <printf@plt>
	printf("using time:%lu %dus\n", t2, tick_to_us(t2));
    1562:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1566:	48 89 c7             	mov    %rax,%rdi
    1569:	e8 d6 fc ff ff       	callq  1244 <tick_to_us>
    156e:	89 c2                	mov    %eax,%edx
    1570:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1574:	48 89 c6             	mov    %rax,%rsi
    1577:	48 8d 3d 77 0b 00 00 	lea    0xb77(%rip),%rdi        # 20f5 <_IO_stdin_used+0xf5>
    157e:	b8 00 00 00 00       	mov    $0x0,%eax
    1583:	e8 58 fb ff ff       	callq  10e0 <printf@plt>
	// patch_handler();
}
    1588:	90                   	nop
    1589:	c9                   	leaveq 
    158a:	c3                   	retq   

000000000000158b <patch_test>:


void patch_test() {
    158b:	f3 0f 1e fa          	endbr64 
    158f:	55                   	push   %rbp
    1590:	48 89 e5             	mov    %rsp,%rbp
    1593:	48 83 ec 50          	sub    $0x50,%rsp
    1597:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    159e:	00 00 
    15a0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    15a4:	31 c0                	xor    %eax,%eax
	int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5, a6 = 6;
    15a6:	c7 45 c8 01 00 00 00 	movl   $0x1,-0x38(%rbp)
    15ad:	c7 45 b8 02 00 00 00 	movl   $0x2,-0x48(%rbp)
    15b4:	c7 45 bc 03 00 00 00 	movl   $0x3,-0x44(%rbp)
    15bb:	c7 45 cc 04 00 00 00 	movl   $0x4,-0x34(%rbp)
    15c2:	c7 45 c0 05 00 00 00 	movl   $0x5,-0x40(%rbp)
    15c9:	c7 45 c4 06 00 00 00 	movl   $0x6,-0x3c(%rbp)
	struct ptr p3 = {&a3}, p6 = {&a6};
    15d0:	48 8d 45 bc          	lea    -0x44(%rbp),%rax
    15d4:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    15d8:	48 8d 45 c4          	lea    -0x3c(%rbp),%rax
    15dc:	48 89 45 e0          	mov    %rax,-0x20(%rbp)

	int ret1 = func_to_patch(a1, &a2, &p3, a4, &a5, &p6);
    15e0:	4c 8d 45 e0          	lea    -0x20(%rbp),%r8
    15e4:	48 8d 7d c0          	lea    -0x40(%rbp),%rdi
    15e8:	8b 4d cc             	mov    -0x34(%rbp),%ecx
    15eb:	48 8d 55 d8          	lea    -0x28(%rbp),%rdx
    15ef:	48 8d 75 b8          	lea    -0x48(%rbp),%rsi
    15f3:	8b 45 c8             	mov    -0x38(%rbp),%eax
    15f6:	4d 89 c1             	mov    %r8,%r9
    15f9:	49 89 f8             	mov    %rdi,%r8
    15fc:	89 c7                	mov    %eax,%edi
    15fe:	e8 bd fd ff ff       	callq  13c0 <func_to_patch>
    1603:	89 45 d0             	mov    %eax,-0x30(%rbp)
	printf("before patch ret:%d\n", ret1);
    1606:	8b 45 d0             	mov    -0x30(%rbp),%eax
    1609:	89 c6                	mov    %eax,%esi
    160b:	48 8d 3d f8 0a 00 00 	lea    0xaf8(%rip),%rdi        # 210a <_IO_stdin_used+0x10a>
    1612:	b8 00 00 00 00       	mov    $0x0,%eax
    1617:	e8 c4 fa ff ff       	callq  10e0 <printf@plt>
	uint64_t t1 = rdtsc();
    161c:	e8 08 fc ff ff       	callq  1229 <rdtsc>
    1621:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
	DSU(func_to_patch, patch_handler);
    1625:	48 8d 35 de 00 00 00 	lea    0xde(%rip),%rsi        # 170a <patch_handler>
    162c:	48 8d 3d 8d fd ff ff 	lea    -0x273(%rip),%rdi        # 13c0 <func_to_patch>
    1633:	e8 69 fc ff ff       	callq  12a1 <DSU>
	uint64_t t2 = rdtsc() - t1;
    1638:	e8 ec fb ff ff       	callq  1229 <rdtsc>
    163d:	48 2b 45 e8          	sub    -0x18(%rbp),%rax
    1641:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
	int ret2 = func_to_patch(a1, &a2, &p3, a4, &a5, &p6);
    1645:	4c 8d 45 e0          	lea    -0x20(%rbp),%r8
    1649:	48 8d 7d c0          	lea    -0x40(%rbp),%rdi
    164d:	8b 4d cc             	mov    -0x34(%rbp),%ecx
    1650:	48 8d 55 d8          	lea    -0x28(%rbp),%rdx
    1654:	48 8d 75 b8          	lea    -0x48(%rbp),%rsi
    1658:	8b 45 c8             	mov    -0x38(%rbp),%eax
    165b:	4d 89 c1             	mov    %r8,%r9
    165e:	49 89 f8             	mov    %rdi,%r8
    1661:	89 c7                	mov    %eax,%edi
    1663:	e8 58 fd ff ff       	callq  13c0 <func_to_patch>
    1668:	89 45 d4             	mov    %eax,-0x2c(%rbp)
	printf("after patch ret:%d\n", ret2);
    166b:	8b 45 d4             	mov    -0x2c(%rbp),%eax
    166e:	89 c6                	mov    %eax,%esi
    1670:	48 8d 3d a8 0a 00 00 	lea    0xaa8(%rip),%rdi        # 211f <_IO_stdin_used+0x11f>
    1677:	b8 00 00 00 00       	mov    $0x0,%eax
    167c:	e8 5f fa ff ff       	callq  10e0 <printf@plt>
	assert(ret1 == ret2);
    1681:	8b 45 d0             	mov    -0x30(%rbp),%eax
    1684:	3b 45 d4             	cmp    -0x2c(%rbp),%eax
    1687:	74 1f                	je     16a8 <patch_test+0x11d>
    1689:	48 8d 0d b8 0b 00 00 	lea    0xbb8(%rip),%rcx        # 2248 <__PRETTY_FUNCTION__.3270>
    1690:	ba 78 00 00 00       	mov    $0x78,%edx
    1695:	48 8d 35 97 0a 00 00 	lea    0xa97(%rip),%rsi        # 2133 <_IO_stdin_used+0x133>
    169c:	48 8d 3d 9c 0a 00 00 	lea    0xa9c(%rip),%rdi        # 213f <_IO_stdin_used+0x13f>
    16a3:	e8 48 fa ff ff       	callq  10f0 <__assert_fail@plt>
	printf("DSU finished in tick:%lu time:%dus\n", t2, tick_to_us(t2));
    16a8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    16ac:	48 89 c7             	mov    %rax,%rdi
    16af:	e8 90 fb ff ff       	callq  1244 <tick_to_us>
    16b4:	89 c2                	mov    %eax,%edx
    16b6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    16ba:	48 89 c6             	mov    %rax,%rsi
    16bd:	48 8d 3d 8c 0a 00 00 	lea    0xa8c(%rip),%rdi        # 2150 <_IO_stdin_used+0x150>
    16c4:	b8 00 00 00 00       	mov    $0x0,%eax
    16c9:	e8 12 fa ff ff       	callq  10e0 <printf@plt>
}
    16ce:	90                   	nop
    16cf:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    16d3:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    16da:	00 00 
    16dc:	74 05                	je     16e3 <patch_test+0x158>
    16de:	e8 ed f9 ff ff       	callq  10d0 <__stack_chk_fail@plt>
    16e3:	c9                   	leaveq 
    16e4:	c3                   	retq   

00000000000016e5 <main>:

int main() {
    16e5:	f3 0f 1e fa          	endbr64 
    16e9:	55                   	push   %rbp
    16ea:	48 89 e5             	mov    %rsp,%rbp
	printf("test variable number args\n");
    16ed:	48 8d 3d 80 0a 00 00 	lea    0xa80(%rip),%rdi        # 2174 <_IO_stdin_used+0x174>
    16f4:	e8 c7 f9 ff ff       	callq  10c0 <puts@plt>
	
	// basic_test();

	patch_test();
    16f9:	b8 00 00 00 00       	mov    $0x0,%eax
    16fe:	e8 88 fe ff ff       	callq  158b <patch_test>

	return 0;
    1703:	b8 00 00 00 00       	mov    $0x0,%eax
}
    1708:	5d                   	pop    %rbp
    1709:	c3                   	retq   

000000000000170a <patch_handler>:
"mov %r15, 0x20(%rbp) \n\t"
"mov %rbp, 0x28(%rbp) \n\t"
实际上这里不需要保存这些寄存器，因为patch_handler
*/
__attribute__((naked))
void patch_handler() {
    170a:	f3 0f 1e fa          	endbr64 
	__asm__ __volatile__ (
    170e:	55                   	push   %rbp
    170f:	48 83 ec 30          	sub    $0x30,%rsp
    1713:	48 89 e5             	mov    %rsp,%rbp
    1716:	48 89 7d 00          	mov    %rdi,0x0(%rbp)
    171a:	48 89 75 08          	mov    %rsi,0x8(%rbp)
    171e:	48 89 55 10          	mov    %rdx,0x10(%rbp)
    1722:	48 89 4d 18          	mov    %rcx,0x18(%rbp)
    1726:	4c 89 45 20          	mov    %r8,0x20(%rbp)
    172a:	4c 89 4d 28          	mov    %r9,0x28(%rbp)
    172e:	48 89 ef             	mov    %rbp,%rdi
    1731:	e8 0c 00 00 00       	callq  1742 <patch_dispatcher>
    1736:	48 89 ec             	mov    %rbp,%rsp
    1739:	48 83 c4 30          	add    $0x30,%rsp
    173d:	5d                   	pop    %rbp
    173e:	c3                   	retq   

		"mov %rbp, %rsp \n\t"
		"add $0x30,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}
    173f:	90                   	nop
    1740:	0f 0b                	ud2    

0000000000001742 <patch_dispatcher>:

uint64_t patch_dispatcher(stack_frame *frame) {
    1742:	f3 0f 1e fa          	endbr64 
    1746:	55                   	push   %rbp
    1747:	48 89 e5             	mov    %rsp,%rbp
    174a:	48 83 ec 30          	sub    $0x30,%rsp
    174e:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
	printf("patch_dispatcher: %p\n", (uint64_t)frame- 0x48);
    1752:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1756:	48 83 e8 48          	sub    $0x48,%rax
    175a:	48 89 c6             	mov    %rax,%rsi
    175d:	48 8d 3d 2a 0a 00 00 	lea    0xa2a(%rip),%rdi        # 218e <_IO_stdin_used+0x18e>
    1764:	b8 00 00 00 00       	mov    $0x0,%eax
    1769:	e8 72 f9 ff ff       	callq  10e0 <printf@plt>
	printf("Register: a1:%lx a2:%lx a3:%lx a4:%lx a5:%lx a6:%lx\n", frame->a1, frame->a2, frame->a3, frame->a4, frame->a5, frame->a6);
    176e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1772:	48 8b 70 28          	mov    0x28(%rax),%rsi
    1776:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    177a:	4c 8b 40 20          	mov    0x20(%rax),%r8
    177e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1782:	48 8b 78 18          	mov    0x18(%rax),%rdi
    1786:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    178a:	48 8b 48 10          	mov    0x10(%rax),%rcx
    178e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1792:	48 8b 50 08          	mov    0x8(%rax),%rdx
    1796:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    179a:	48 8b 00             	mov    (%rax),%rax
    179d:	48 83 ec 08          	sub    $0x8,%rsp
    17a1:	56                   	push   %rsi
    17a2:	4d 89 c1             	mov    %r8,%r9
    17a5:	49 89 f8             	mov    %rdi,%r8
    17a8:	48 89 c6             	mov    %rax,%rsi
    17ab:	48 8d 3d f6 09 00 00 	lea    0x9f6(%rip),%rdi        # 21a8 <_IO_stdin_used+0x1a8>
    17b2:	b8 00 00 00 00       	mov    $0x0,%eax
    17b7:	e8 24 f9 ff ff       	callq  10e0 <printf@plt>
    17bc:	48 83 c4 10          	add    $0x10,%rsp
	printf("Address: a1:%lx a2:%lx a3:%lx a4:%lx a5:%lx a6:%lx\n", &frame->a1, &frame->a2, &frame->a3, &frame->a4, &frame->a5, &frame->a6);
    17c0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    17c4:	48 8d 70 28          	lea    0x28(%rax),%rsi
    17c8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    17cc:	4c 8d 40 20          	lea    0x20(%rax),%r8
    17d0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    17d4:	48 8d 78 18          	lea    0x18(%rax),%rdi
    17d8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    17dc:	48 8d 48 10          	lea    0x10(%rax),%rcx
    17e0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    17e4:	48 8d 50 08          	lea    0x8(%rax),%rdx
    17e8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    17ec:	48 83 ec 08          	sub    $0x8,%rsp
    17f0:	56                   	push   %rsi
    17f1:	4d 89 c1             	mov    %r8,%r9
    17f4:	49 89 f8             	mov    %rdi,%r8
    17f7:	48 89 c6             	mov    %rax,%rsi
    17fa:	48 8d 3d df 09 00 00 	lea    0x9df(%rip),%rdi        # 21e0 <_IO_stdin_used+0x1e0>
    1801:	b8 00 00 00 00       	mov    $0x0,%eax
    1806:	e8 d5 f8 ff ff       	callq  10e0 <printf@plt>
    180b:	48 83 c4 10          	add    $0x10,%rsp
	assert((uintptr_t)&frame->a2 - (uintptr_t)&frame->a1 == 8);
	
	// int a1, int *a2, struct ptr *p3, int a4, int *a5, struct ptr *p6
	int a1, a2, a3, a4, a5, a6;
	
	a1 = frame->a1;
    180f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1813:	48 8b 00             	mov    (%rax),%rax
    1816:	89 45 e8             	mov    %eax,-0x18(%rbp)
	a2 = *(int *)(uintptr_t)(frame->a2);
    1819:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    181d:	48 8b 40 08          	mov    0x8(%rax),%rax
    1821:	8b 00                	mov    (%rax),%eax
    1823:	89 45 ec             	mov    %eax,-0x14(%rbp)
	a3 = *((struct ptr*)(uintptr_t)frame->a3)->p;
    1826:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    182a:	48 8b 40 10          	mov    0x10(%rax),%rax
    182e:	48 8b 00             	mov    (%rax),%rax
    1831:	8b 00                	mov    (%rax),%eax
    1833:	89 45 f0             	mov    %eax,-0x10(%rbp)
	a4 = frame->a4;
    1836:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    183a:	48 8b 40 18          	mov    0x18(%rax),%rax
    183e:	89 45 f4             	mov    %eax,-0xc(%rbp)
	a5 = *(int *)(uintptr_t)(frame->a5);
    1841:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1845:	48 8b 40 20          	mov    0x20(%rax),%rax
    1849:	8b 00                	mov    (%rax),%eax
    184b:	89 45 f8             	mov    %eax,-0x8(%rbp)
	a6 = *((struct ptr*)(uintptr_t)frame->a6)->p;
    184e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1852:	48 8b 40 28          	mov    0x28(%rax),%rax
    1856:	48 8b 00             	mov    (%rax),%rax
    1859:	8b 00                	mov    (%rax),%eax
    185b:	89 45 fc             	mov    %eax,-0x4(%rbp)
	// int a2 = frame->a2, a3 = frame->a3, a4 = frame->a4, a5 = frame->a5, a6 = frame->a6;
	printf("Argument: a1:%d a2:%d a3:%d a4:%d a5:%d a6:%d\n", a1, a2, a3, a4, a5, a6);
    185e:	44 8b 45 f8          	mov    -0x8(%rbp),%r8d
    1862:	8b 7d f4             	mov    -0xc(%rbp),%edi
    1865:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    1868:	8b 55 ec             	mov    -0x14(%rbp),%edx
    186b:	8b 45 e8             	mov    -0x18(%rbp),%eax
    186e:	48 83 ec 08          	sub    $0x8,%rsp
    1872:	8b 75 fc             	mov    -0x4(%rbp),%esi
    1875:	56                   	push   %rsi
    1876:	45 89 c1             	mov    %r8d,%r9d
    1879:	41 89 f8             	mov    %edi,%r8d
    187c:	89 c6                	mov    %eax,%esi
    187e:	48 8d 3d 93 09 00 00 	lea    0x993(%rip),%rdi        # 2218 <_IO_stdin_used+0x218>
    1885:	b8 00 00 00 00       	mov    $0x0,%eax
    188a:	e8 51 f8 ff ff       	callq  10e0 <printf@plt>
    188f:	48 83 c4 10          	add    $0x10,%rsp
	return a1 + a2 + a3 + a4 + a5 + a6;
    1893:	8b 55 e8             	mov    -0x18(%rbp),%edx
    1896:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1899:	01 c2                	add    %eax,%edx
    189b:	8b 45 f0             	mov    -0x10(%rbp),%eax
    189e:	01 c2                	add    %eax,%edx
    18a0:	8b 45 f4             	mov    -0xc(%rbp),%eax
    18a3:	01 c2                	add    %eax,%edx
    18a5:	8b 45 f8             	mov    -0x8(%rbp),%eax
    18a8:	01 c2                	add    %eax,%edx
    18aa:	8b 45 fc             	mov    -0x4(%rbp),%eax
    18ad:	01 d0                	add    %edx,%eax
    18af:	48 98                	cltq   
}
    18b1:	c9                   	leaveq 
    18b2:	c3                   	retq   
    18b3:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    18ba:	00 00 00 
    18bd:	0f 1f 00             	nopl   (%rax)

00000000000018c0 <__libc_csu_init>:
    18c0:	f3 0f 1e fa          	endbr64 
    18c4:	41 57                	push   %r15
    18c6:	4c 8d 3d b3 24 00 00 	lea    0x24b3(%rip),%r15        # 3d80 <__frame_dummy_init_array_entry>
    18cd:	41 56                	push   %r14
    18cf:	49 89 d6             	mov    %rdx,%r14
    18d2:	41 55                	push   %r13
    18d4:	49 89 f5             	mov    %rsi,%r13
    18d7:	41 54                	push   %r12
    18d9:	41 89 fc             	mov    %edi,%r12d
    18dc:	55                   	push   %rbp
    18dd:	48 8d 2d a4 24 00 00 	lea    0x24a4(%rip),%rbp        # 3d88 <__do_global_dtors_aux_fini_array_entry>
    18e4:	53                   	push   %rbx
    18e5:	4c 29 fd             	sub    %r15,%rbp
    18e8:	48 83 ec 08          	sub    $0x8,%rsp
    18ec:	e8 0f f7 ff ff       	callq  1000 <_init>
    18f1:	48 c1 fd 03          	sar    $0x3,%rbp
    18f5:	74 1f                	je     1916 <__libc_csu_init+0x56>
    18f7:	31 db                	xor    %ebx,%ebx
    18f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1900:	4c 89 f2             	mov    %r14,%rdx
    1903:	4c 89 ee             	mov    %r13,%rsi
    1906:	44 89 e7             	mov    %r12d,%edi
    1909:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    190d:	48 83 c3 01          	add    $0x1,%rbx
    1911:	48 39 dd             	cmp    %rbx,%rbp
    1914:	75 ea                	jne    1900 <__libc_csu_init+0x40>
    1916:	48 83 c4 08          	add    $0x8,%rsp
    191a:	5b                   	pop    %rbx
    191b:	5d                   	pop    %rbp
    191c:	41 5c                	pop    %r12
    191e:	41 5d                	pop    %r13
    1920:	41 5e                	pop    %r14
    1922:	41 5f                	pop    %r15
    1924:	c3                   	retq   
    1925:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    192c:	00 00 00 00 

0000000000001930 <__libc_csu_fini>:
    1930:	f3 0f 1e fa          	endbr64 
    1934:	c3                   	retq   

Disassembly of section .fini:

0000000000001938 <_fini>:
    1938:	f3 0f 1e fa          	endbr64 
    193c:	48 83 ec 08          	sub    $0x8,%rsp
    1940:	48 83 c4 08          	add    $0x8,%rsp
    1944:	c3                   	retq   
