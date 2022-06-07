
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
    1153:	4c 8d 05 16 07 00 00 	lea    0x716(%rip),%r8        # 1870 <__libc_csu_fini>
    115a:	48 8d 0d 9f 06 00 00 	lea    0x69f(%rip),%rcx        # 1800 <__libc_csu_init>
    1161:	48 8d 3d 89 04 00 00 	lea    0x489(%rip),%rdi        # 15f1 <main>
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

0000000000001229 <DSU>:
    1229:	f3 0f 1e fa          	endbr64 
    122d:	55                   	push   %rbp
    122e:	48 89 e5             	mov    %rsp,%rbp
    1231:	48 83 ec 30          	sub    $0x30,%rsp
    1235:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    1239:	48 89 75 d0          	mov    %rsi,-0x30(%rbp)
    123d:	bf 1e 00 00 00       	mov    $0x1e,%edi
    1242:	e8 e9 fe ff ff       	callq  1130 <sysconf@plt>
    1247:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    124b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    124f:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
    1255:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1259:	c7 45 ec 07 00 00 00 	movl   $0x7,-0x14(%rbp)
    1260:	48 8d 3d a1 0d 00 00 	lea    0xda1(%rip),%rdi        # 2008 <_IO_stdin_used+0x8>
    1267:	b8 00 00 00 00       	mov    $0x0,%eax
    126c:	e8 6f fe ff ff       	callq  10e0 <printf@plt>
    1271:	48 8b 05 98 2d 00 00 	mov    0x2d98(%rip),%rax        # 4010 <stdout@@GLIBC_2.2.5>
    1278:	48 89 c7             	mov    %rax,%rdi
    127b:	e8 90 fe ff ff       	callq  1110 <fflush@plt>
    1280:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1284:	48 8d 0c 00          	lea    (%rax,%rax,1),%rcx
    1288:	8b 55 ec             	mov    -0x14(%rbp),%edx
    128b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    128f:	48 89 ce             	mov    %rcx,%rsi
    1292:	48 89 c7             	mov    %rax,%rdi
    1295:	e8 86 fe ff ff       	callq  1120 <mprotect@plt>
    129a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    129e:	ba 02 00 00 00       	mov    $0x2,%edx
    12a3:	48 8d 35 77 0d 00 00 	lea    0xd77(%rip),%rsi        # 2021 <_IO_stdin_used+0x21>
    12aa:	48 89 c7             	mov    %rax,%rdi
    12ad:	e8 4e fe ff ff       	callq  1100 <memcpy@plt>
    12b2:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    12b6:	48 8d 50 02          	lea    0x2(%rax),%rdx
    12ba:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    12be:	48 89 02             	mov    %rax,(%rdx)
    12c1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    12c5:	48 83 c0 0a          	add    $0xa,%rax
    12c9:	ba 02 00 00 00       	mov    $0x2,%edx
    12ce:	48 8d 35 4f 0d 00 00 	lea    0xd4f(%rip),%rsi        # 2024 <_IO_stdin_used+0x24>
    12d5:	48 89 c7             	mov    %rax,%rdi
    12d8:	e8 23 fe ff ff       	callq  1100 <memcpy@plt>
    12dd:	8b 45 ec             	mov    -0x14(%rbp),%eax
    12e0:	83 e0 fd             	and    $0xfffffffd,%eax
    12e3:	89 c2                	mov    %eax,%edx
    12e5:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    12e9:	48 8d 0c 00          	lea    (%rax,%rax,1),%rcx
    12ed:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    12f1:	48 89 ce             	mov    %rcx,%rsi
    12f4:	48 89 c7             	mov    %rax,%rdi
    12f7:	e8 24 fe ff ff       	callq  1120 <mprotect@plt>
    12fc:	48 8d 3d 24 0d 00 00 	lea    0xd24(%rip),%rdi        # 2027 <_IO_stdin_used+0x27>
    1303:	e8 b8 fd ff ff       	callq  10c0 <puts@plt>
    1308:	48 8b 05 01 2d 00 00 	mov    0x2d01(%rip),%rax        # 4010 <stdout@@GLIBC_2.2.5>
    130f:	48 89 c7             	mov    %rax,%rdi
    1312:	e8 f9 fd ff ff       	callq  1110 <fflush@plt>
    1317:	90                   	nop
    1318:	c9                   	leaveq 
    1319:	c3                   	retq   

000000000000131a <old_func>:
    131a:	f3 0f 1e fa          	endbr64 
    131e:	55                   	push   %rbp
    131f:	48 89 e5             	mov    %rsp,%rbp
    1322:	48 8d 3d 03 0d 00 00 	lea    0xd03(%rip),%rdi        # 202c <_IO_stdin_used+0x2c>
    1329:	e8 92 fd ff ff       	callq  10c0 <puts@plt>
    132e:	90                   	nop
    132f:	5d                   	pop    %rbp
    1330:	c3                   	retq   

0000000000001331 <new_func>:
    1331:	f3 0f 1e fa          	endbr64 
    1335:	55                   	push   %rbp
    1336:	48 89 e5             	mov    %rsp,%rbp
    1339:	48 8d 3d 01 0d 00 00 	lea    0xd01(%rip),%rdi        # 2041 <_IO_stdin_used+0x41>
    1340:	e8 7b fd ff ff       	callq  10c0 <puts@plt>
    1345:	90                   	nop
    1346:	5d                   	pop    %rbp
    1347:	c3                   	retq   

0000000000001348 <func_to_patch>:
    1348:	f3 0f 1e fa          	endbr64 
    134c:	55                   	push   %rbp
    134d:	48 89 e5             	mov    %rsp,%rbp
    1350:	48 83 c4 80          	add    $0xffffffffffffff80,%rsp
    1354:	89 7d ac             	mov    %edi,-0x54(%rbp)
    1357:	48 89 75 a0          	mov    %rsi,-0x60(%rbp)
    135b:	48 89 55 98          	mov    %rdx,-0x68(%rbp)
    135f:	89 4d a8             	mov    %ecx,-0x58(%rbp)
    1362:	4c 89 45 90          	mov    %r8,-0x70(%rbp)
    1366:	4c 89 4d 88          	mov    %r9,-0x78(%rbp)
    136a:	48 89 6d c8          	mov    %rbp,-0x38(%rbp)
    136e:	48 89 7d d0          	mov    %rdi,-0x30(%rbp)
    1372:	48 89 75 d8          	mov    %rsi,-0x28(%rbp)
    1376:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
    137a:	48 89 4d e8          	mov    %rcx,-0x18(%rbp)
    137e:	4c 89 45 f0          	mov    %r8,-0x10(%rbp)
    1382:	4c 89 4d f8          	mov    %r9,-0x8(%rbp)
    1386:	48 89 e8             	mov    %rbp,%rax
    1389:	48 89 c6             	mov    %rax,%rsi
    138c:	48 8d 3d c3 0c 00 00 	lea    0xcc3(%rip),%rdi        # 2056 <_IO_stdin_used+0x56>
    1393:	b8 00 00 00 00       	mov    $0x0,%eax
    1398:	e8 43 fd ff ff       	callq  10e0 <printf@plt>
    139d:	48 8b 45 88          	mov    -0x78(%rbp),%rax
    13a1:	48 8b 00             	mov    (%rax),%rax
    13a4:	8b 30                	mov    (%rax),%esi
    13a6:	48 8b 45 90          	mov    -0x70(%rbp),%rax
    13aa:	44 8b 00             	mov    (%rax),%r8d
    13ad:	48 8b 45 98          	mov    -0x68(%rbp),%rax
    13b1:	48 8b 00             	mov    (%rax),%rax
    13b4:	8b 08                	mov    (%rax),%ecx
    13b6:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
    13ba:	8b 10                	mov    (%rax),%edx
    13bc:	8b 7d a8             	mov    -0x58(%rbp),%edi
    13bf:	8b 45 ac             	mov    -0x54(%rbp),%eax
    13c2:	48 83 ec 08          	sub    $0x8,%rsp
    13c6:	56                   	push   %rsi
    13c7:	45 89 c1             	mov    %r8d,%r9d
    13ca:	41 89 f8             	mov    %edi,%r8d
    13cd:	89 c6                	mov    %eax,%esi
    13cf:	48 8d 3d 8a 0c 00 00 	lea    0xc8a(%rip),%rdi        # 2060 <_IO_stdin_used+0x60>
    13d6:	b8 00 00 00 00       	mov    $0x0,%eax
    13db:	e8 00 fd ff ff       	callq  10e0 <printf@plt>
    13e0:	48 83 c4 10          	add    $0x10,%rsp
    13e4:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    13e8:	89 45 b0             	mov    %eax,-0x50(%rbp)
    13eb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    13ef:	8b 00                	mov    (%rax),%eax
    13f1:	89 45 b4             	mov    %eax,-0x4c(%rbp)
    13f4:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    13f8:	48 8b 00             	mov    (%rax),%rax
    13fb:	8b 00                	mov    (%rax),%eax
    13fd:	89 45 b8             	mov    %eax,-0x48(%rbp)
    1400:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1404:	89 45 bc             	mov    %eax,-0x44(%rbp)
    1407:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    140b:	8b 00                	mov    (%rax),%eax
    140d:	89 45 c0             	mov    %eax,-0x40(%rbp)
    1410:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1414:	48 8b 00             	mov    (%rax),%rax
    1417:	8b 00                	mov    (%rax),%eax
    1419:	89 45 c4             	mov    %eax,-0x3c(%rbp)
    141c:	44 8b 45 c0          	mov    -0x40(%rbp),%r8d
    1420:	8b 7d bc             	mov    -0x44(%rbp),%edi
    1423:	8b 4d b8             	mov    -0x48(%rbp),%ecx
    1426:	8b 55 b4             	mov    -0x4c(%rbp),%edx
    1429:	8b 45 b0             	mov    -0x50(%rbp),%eax
    142c:	48 83 ec 08          	sub    $0x8,%rsp
    1430:	8b 75 c4             	mov    -0x3c(%rbp),%esi
    1433:	56                   	push   %rsi
    1434:	45 89 c1             	mov    %r8d,%r9d
    1437:	41 89 f8             	mov    %edi,%r8d
    143a:	89 c6                	mov    %eax,%esi
    143c:	48 8d 3d 55 0c 00 00 	lea    0xc55(%rip),%rdi        # 2098 <_IO_stdin_used+0x98>
    1443:	b8 00 00 00 00       	mov    $0x0,%eax
    1448:	e8 93 fc ff ff       	callq  10e0 <printf@plt>
    144d:	48 83 c4 10          	add    $0x10,%rsp
    1451:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
    1455:	8b 10                	mov    (%rax),%edx
    1457:	8b 45 ac             	mov    -0x54(%rbp),%eax
    145a:	01 c2                	add    %eax,%edx
    145c:	48 8b 45 98          	mov    -0x68(%rbp),%rax
    1460:	48 8b 00             	mov    (%rax),%rax
    1463:	8b 00                	mov    (%rax),%eax
    1465:	01 c2                	add    %eax,%edx
    1467:	8b 45 a8             	mov    -0x58(%rbp),%eax
    146a:	01 c2                	add    %eax,%edx
    146c:	48 8b 45 90          	mov    -0x70(%rbp),%rax
    1470:	8b 00                	mov    (%rax),%eax
    1472:	01 c2                	add    %eax,%edx
    1474:	48 8b 45 88          	mov    -0x78(%rbp),%rax
    1478:	48 8b 00             	mov    (%rax),%rax
    147b:	8b 00                	mov    (%rax),%eax
    147d:	01 d0                	add    %edx,%eax
    147f:	c9                   	leaveq 
    1480:	c3                   	retq   

0000000000001481 <basic_test>:
    1481:	f3 0f 1e fa          	endbr64 
    1485:	55                   	push   %rbp
    1486:	48 89 e5             	mov    %rsp,%rbp
    1489:	b8 00 00 00 00       	mov    $0x0,%eax
    148e:	e8 87 fe ff ff       	callq  131a <old_func>
    1493:	48 8d 35 97 fe ff ff 	lea    -0x169(%rip),%rsi        # 1331 <new_func>
    149a:	48 8d 3d 79 fe ff ff 	lea    -0x187(%rip),%rdi        # 131a <old_func>
    14a1:	e8 83 fd ff ff       	callq  1229 <DSU>
    14a6:	b8 00 00 00 00       	mov    $0x0,%eax
    14ab:	e8 6a fe ff ff       	callq  131a <old_func>
    14b0:	b9 08 00 00 00       	mov    $0x8,%ecx
    14b5:	ba 00 00 00 00       	mov    $0x0,%edx
    14ba:	be 30 00 00 00       	mov    $0x30,%esi
    14bf:	48 8d 3d 0a 0c 00 00 	lea    0xc0a(%rip),%rdi        # 20d0 <_IO_stdin_used+0xd0>
    14c6:	b8 00 00 00 00       	mov    $0x0,%eax
    14cb:	e8 10 fc ff ff       	callq  10e0 <printf@plt>
    14d0:	90                   	nop
    14d1:	5d                   	pop    %rbp
    14d2:	c3                   	retq   

00000000000014d3 <patch_test>:
    14d3:	f3 0f 1e fa          	endbr64 
    14d7:	55                   	push   %rbp
    14d8:	48 89 e5             	mov    %rsp,%rbp
    14db:	48 83 ec 40          	sub    $0x40,%rsp
    14df:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    14e6:	00 00 
    14e8:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    14ec:	31 c0                	xor    %eax,%eax
    14ee:	c7 45 d8 01 00 00 00 	movl   $0x1,-0x28(%rbp)
    14f5:	c7 45 c8 02 00 00 00 	movl   $0x2,-0x38(%rbp)
    14fc:	c7 45 cc 03 00 00 00 	movl   $0x3,-0x34(%rbp)
    1503:	c7 45 dc 04 00 00 00 	movl   $0x4,-0x24(%rbp)
    150a:	c7 45 d0 05 00 00 00 	movl   $0x5,-0x30(%rbp)
    1511:	c7 45 d4 06 00 00 00 	movl   $0x6,-0x2c(%rbp)
    1518:	48 8d 45 cc          	lea    -0x34(%rbp),%rax
    151c:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1520:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
    1524:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    1528:	4c 8d 45 f0          	lea    -0x10(%rbp),%r8
    152c:	48 8d 7d d0          	lea    -0x30(%rbp),%rdi
    1530:	8b 4d dc             	mov    -0x24(%rbp),%ecx
    1533:	48 8d 55 e8          	lea    -0x18(%rbp),%rdx
    1537:	48 8d 75 c8          	lea    -0x38(%rbp),%rsi
    153b:	8b 45 d8             	mov    -0x28(%rbp),%eax
    153e:	4d 89 c1             	mov    %r8,%r9
    1541:	49 89 f8             	mov    %rdi,%r8
    1544:	89 c7                	mov    %eax,%edi
    1546:	e8 fd fd ff ff       	callq  1348 <func_to_patch>
    154b:	89 45 e0             	mov    %eax,-0x20(%rbp)
    154e:	8b 45 e0             	mov    -0x20(%rbp),%eax
    1551:	89 c6                	mov    %eax,%esi
    1553:	48 8d 3d 9b 0b 00 00 	lea    0xb9b(%rip),%rdi        # 20f5 <_IO_stdin_used+0xf5>
    155a:	b8 00 00 00 00       	mov    $0x0,%eax
    155f:	e8 7c fb ff ff       	callq  10e0 <printf@plt>
    1564:	48 8d 35 ab 00 00 00 	lea    0xab(%rip),%rsi        # 1616 <patch_handler>
    156b:	48 8d 3d d6 fd ff ff 	lea    -0x22a(%rip),%rdi        # 1348 <func_to_patch>
    1572:	e8 b2 fc ff ff       	callq  1229 <DSU>
    1577:	4c 8d 45 f0          	lea    -0x10(%rbp),%r8
    157b:	48 8d 7d d0          	lea    -0x30(%rbp),%rdi
    157f:	8b 4d dc             	mov    -0x24(%rbp),%ecx
    1582:	48 8d 55 e8          	lea    -0x18(%rbp),%rdx
    1586:	48 8d 75 c8          	lea    -0x38(%rbp),%rsi
    158a:	8b 45 d8             	mov    -0x28(%rbp),%eax
    158d:	4d 89 c1             	mov    %r8,%r9
    1590:	49 89 f8             	mov    %rdi,%r8
    1593:	89 c7                	mov    %eax,%edi
    1595:	e8 ae fd ff ff       	callq  1348 <func_to_patch>
    159a:	89 45 e4             	mov    %eax,-0x1c(%rbp)
    159d:	8b 45 e4             	mov    -0x1c(%rbp),%eax
    15a0:	89 c6                	mov    %eax,%esi
    15a2:	48 8d 3d 61 0b 00 00 	lea    0xb61(%rip),%rdi        # 210a <_IO_stdin_used+0x10a>
    15a9:	b8 00 00 00 00       	mov    $0x0,%eax
    15ae:	e8 2d fb ff ff       	callq  10e0 <printf@plt>
    15b3:	8b 45 e0             	mov    -0x20(%rbp),%eax
    15b6:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
    15b9:	74 1f                	je     15da <patch_test+0x107>
    15bb:	48 8d 0d 46 0c 00 00 	lea    0xc46(%rip),%rcx        # 2208 <__PRETTY_FUNCTION__.3257>
    15c2:	ba 67 00 00 00       	mov    $0x67,%edx
    15c7:	48 8d 35 50 0b 00 00 	lea    0xb50(%rip),%rsi        # 211e <_IO_stdin_used+0x11e>
    15ce:	48 8d 3d 55 0b 00 00 	lea    0xb55(%rip),%rdi        # 212a <_IO_stdin_used+0x12a>
    15d5:	e8 16 fb ff ff       	callq  10f0 <__assert_fail@plt>
    15da:	90                   	nop
    15db:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    15df:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
    15e6:	00 00 
    15e8:	74 05                	je     15ef <patch_test+0x11c>
    15ea:	e8 e1 fa ff ff       	callq  10d0 <__stack_chk_fail@plt>
    15ef:	c9                   	leaveq 
    15f0:	c3                   	retq   

00000000000015f1 <main>:
    15f1:	f3 0f 1e fa          	endbr64 
    15f5:	55                   	push   %rbp
    15f6:	48 89 e5             	mov    %rsp,%rbp
    15f9:	48 8d 3d 37 0b 00 00 	lea    0xb37(%rip),%rdi        # 2137 <_IO_stdin_used+0x137>
    1600:	e8 bb fa ff ff       	callq  10c0 <puts@plt>
    1605:	b8 00 00 00 00       	mov    $0x0,%eax
    160a:	e8 c4 fe ff ff       	callq  14d3 <patch_test>
    160f:	b8 00 00 00 00       	mov    $0x0,%eax
    1614:	5d                   	pop    %rbp
    1615:	c3                   	retq   

0000000000001616 <patch_handler>:
    1616:	f3 0f 1e fa          	endbr64 
    161a:	55                   	push   %rbp
    161b:	48 83 ec 30          	sub    $0x30,%rsp
    161f:	48 89 e5             	mov    %rsp,%rbp
    1622:	48 89 7d 00          	mov    %rdi,0x0(%rbp)
    1626:	48 89 75 08          	mov    %rsi,0x8(%rbp)
    162a:	48 89 55 10          	mov    %rdx,0x10(%rbp)
    162e:	48 89 4d 18          	mov    %rcx,0x18(%rbp)
    1632:	4c 89 45 20          	mov    %r8,0x20(%rbp)
    1636:	4c 89 4d 28          	mov    %r9,0x28(%rbp)
    163a:	48 83 ec 30          	sub    $0x30,%rsp
    163e:	48 89 e5             	mov    %rsp,%rbp
    1641:	48 89 5d 00          	mov    %rbx,0x0(%rbp)
    1645:	4c 89 65 08          	mov    %r12,0x8(%rbp)
    1649:	4c 89 6d 10          	mov    %r13,0x10(%rbp)
    164d:	4c 89 75 18          	mov    %r14,0x18(%rbp)
    1651:	4c 89 7d 20          	mov    %r15,0x20(%rbp)
    1655:	48 89 6d 28          	mov    %rbp,0x28(%rbp)
    1659:	48 89 ef             	mov    %rbp,%rdi
    165c:	48 83 c7 30          	add    $0x30,%rdi
    1660:	e8 28 00 00 00       	callq  168d <patch_dispatcher>
    1665:	48 8b 5d 00          	mov    0x0(%rbp),%rbx
    1669:	4c 8b 65 08          	mov    0x8(%rbp),%r12
    166d:	4c 8b 6d 10          	mov    0x10(%rbp),%r13
    1671:	4c 8b 75 18          	mov    0x18(%rbp),%r14
    1675:	4c 8b 7d 20          	mov    0x20(%rbp),%r15
    1679:	48 8b 6d 28          	mov    0x28(%rbp),%rbp
    167d:	48 89 ec             	mov    %rbp,%rsp
    1680:	48 83 c4 30          	add    $0x30,%rsp
    1684:	48 83 c4 30          	add    $0x30,%rsp
    1688:	5d                   	pop    %rbp
    1689:	c3                   	retq   
    168a:	90                   	nop
    168b:	0f 0b                	ud2    

000000000000168d <patch_dispatcher>:
    168d:	f3 0f 1e fa          	endbr64 
    1691:	55                   	push   %rbp
    1692:	48 89 e5             	mov    %rsp,%rbp
    1695:	48 83 ec 30          	sub    $0x30,%rsp
    1699:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    169d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16a1:	48 83 e8 48          	sub    $0x48,%rax
    16a5:	48 89 c6             	mov    %rax,%rsi
    16a8:	48 8d 3d a2 0a 00 00 	lea    0xaa2(%rip),%rdi        # 2151 <_IO_stdin_used+0x151>
    16af:	b8 00 00 00 00       	mov    $0x0,%eax
    16b4:	e8 27 fa ff ff       	callq  10e0 <printf@plt>
    16b9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16bd:	48 8b 70 28          	mov    0x28(%rax),%rsi
    16c1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16c5:	4c 8b 40 20          	mov    0x20(%rax),%r8
    16c9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16cd:	48 8b 78 18          	mov    0x18(%rax),%rdi
    16d1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16d5:	48 8b 48 10          	mov    0x10(%rax),%rcx
    16d9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16dd:	48 8b 50 08          	mov    0x8(%rax),%rdx
    16e1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16e5:	48 8b 00             	mov    (%rax),%rax
    16e8:	48 83 ec 08          	sub    $0x8,%rsp
    16ec:	56                   	push   %rsi
    16ed:	4d 89 c1             	mov    %r8,%r9
    16f0:	49 89 f8             	mov    %rdi,%r8
    16f3:	48 89 c6             	mov    %rax,%rsi
    16f6:	48 8d 3d 6b 0a 00 00 	lea    0xa6b(%rip),%rdi        # 2168 <_IO_stdin_used+0x168>
    16fd:	b8 00 00 00 00       	mov    $0x0,%eax
    1702:	e8 d9 f9 ff ff       	callq  10e0 <printf@plt>
    1707:	48 83 c4 10          	add    $0x10,%rsp
    170b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    170f:	48 8d 70 28          	lea    0x28(%rax),%rsi
    1713:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1717:	4c 8d 40 20          	lea    0x20(%rax),%r8
    171b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    171f:	48 8d 78 18          	lea    0x18(%rax),%rdi
    1723:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1727:	48 8d 48 10          	lea    0x10(%rax),%rcx
    172b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    172f:	48 8d 50 08          	lea    0x8(%rax),%rdx
    1733:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1737:	48 83 ec 08          	sub    $0x8,%rsp
    173b:	56                   	push   %rsi
    173c:	4d 89 c1             	mov    %r8,%r9
    173f:	49 89 f8             	mov    %rdi,%r8
    1742:	48 89 c6             	mov    %rax,%rsi
    1745:	48 8d 3d 54 0a 00 00 	lea    0xa54(%rip),%rdi        # 21a0 <_IO_stdin_used+0x1a0>
    174c:	b8 00 00 00 00       	mov    $0x0,%eax
    1751:	e8 8a f9 ff ff       	callq  10e0 <printf@plt>
    1756:	48 83 c4 10          	add    $0x10,%rsp
    175a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    175e:	48 8b 00             	mov    (%rax),%rax
    1761:	89 45 e8             	mov    %eax,-0x18(%rbp)
    1764:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1768:	48 8b 40 08          	mov    0x8(%rax),%rax
    176c:	8b 00                	mov    (%rax),%eax
    176e:	89 45 ec             	mov    %eax,-0x14(%rbp)
    1771:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1775:	48 8b 40 10          	mov    0x10(%rax),%rax
    1779:	48 8b 00             	mov    (%rax),%rax
    177c:	8b 00                	mov    (%rax),%eax
    177e:	89 45 f0             	mov    %eax,-0x10(%rbp)
    1781:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1785:	48 8b 40 18          	mov    0x18(%rax),%rax
    1789:	89 45 f4             	mov    %eax,-0xc(%rbp)
    178c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1790:	48 8b 40 20          	mov    0x20(%rax),%rax
    1794:	8b 00                	mov    (%rax),%eax
    1796:	89 45 f8             	mov    %eax,-0x8(%rbp)
    1799:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    179d:	48 8b 40 28          	mov    0x28(%rax),%rax
    17a1:	48 8b 00             	mov    (%rax),%rax
    17a4:	8b 00                	mov    (%rax),%eax
    17a6:	89 45 fc             	mov    %eax,-0x4(%rbp)
    17a9:	44 8b 45 f8          	mov    -0x8(%rbp),%r8d
    17ad:	8b 7d f4             	mov    -0xc(%rbp),%edi
    17b0:	8b 4d f0             	mov    -0x10(%rbp),%ecx
    17b3:	8b 55 ec             	mov    -0x14(%rbp),%edx
    17b6:	8b 45 e8             	mov    -0x18(%rbp),%eax
    17b9:	48 83 ec 08          	sub    $0x8,%rsp
    17bd:	8b 75 fc             	mov    -0x4(%rbp),%esi
    17c0:	56                   	push   %rsi
    17c1:	45 89 c1             	mov    %r8d,%r9d
    17c4:	41 89 f8             	mov    %edi,%r8d
    17c7:	89 c6                	mov    %eax,%esi
    17c9:	48 8d 3d 08 0a 00 00 	lea    0xa08(%rip),%rdi        # 21d8 <_IO_stdin_used+0x1d8>
    17d0:	b8 00 00 00 00       	mov    $0x0,%eax
    17d5:	e8 06 f9 ff ff       	callq  10e0 <printf@plt>
    17da:	48 83 c4 10          	add    $0x10,%rsp
    17de:	8b 55 e8             	mov    -0x18(%rbp),%edx
    17e1:	8b 45 ec             	mov    -0x14(%rbp),%eax
    17e4:	01 c2                	add    %eax,%edx
    17e6:	8b 45 f0             	mov    -0x10(%rbp),%eax
    17e9:	01 c2                	add    %eax,%edx
    17eb:	8b 45 f4             	mov    -0xc(%rbp),%eax
    17ee:	01 c2                	add    %eax,%edx
    17f0:	8b 45 f8             	mov    -0x8(%rbp),%eax
    17f3:	01 c2                	add    %eax,%edx
    17f5:	8b 45 fc             	mov    -0x4(%rbp),%eax
    17f8:	01 d0                	add    %edx,%eax
    17fa:	48 98                	cltq   
    17fc:	c9                   	leaveq 
    17fd:	c3                   	retq   
    17fe:	66 90                	xchg   %ax,%ax

0000000000001800 <__libc_csu_init>:
    1800:	f3 0f 1e fa          	endbr64 
    1804:	41 57                	push   %r15
    1806:	4c 8d 3d 73 25 00 00 	lea    0x2573(%rip),%r15        # 3d80 <__frame_dummy_init_array_entry>
    180d:	41 56                	push   %r14
    180f:	49 89 d6             	mov    %rdx,%r14
    1812:	41 55                	push   %r13
    1814:	49 89 f5             	mov    %rsi,%r13
    1817:	41 54                	push   %r12
    1819:	41 89 fc             	mov    %edi,%r12d
    181c:	55                   	push   %rbp
    181d:	48 8d 2d 64 25 00 00 	lea    0x2564(%rip),%rbp        # 3d88 <__do_global_dtors_aux_fini_array_entry>
    1824:	53                   	push   %rbx
    1825:	4c 29 fd             	sub    %r15,%rbp
    1828:	48 83 ec 08          	sub    $0x8,%rsp
    182c:	e8 cf f7 ff ff       	callq  1000 <_init>
    1831:	48 c1 fd 03          	sar    $0x3,%rbp
    1835:	74 1f                	je     1856 <__libc_csu_init+0x56>
    1837:	31 db                	xor    %ebx,%ebx
    1839:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1840:	4c 89 f2             	mov    %r14,%rdx
    1843:	4c 89 ee             	mov    %r13,%rsi
    1846:	44 89 e7             	mov    %r12d,%edi
    1849:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    184d:	48 83 c3 01          	add    $0x1,%rbx
    1851:	48 39 dd             	cmp    %rbx,%rbp
    1854:	75 ea                	jne    1840 <__libc_csu_init+0x40>
    1856:	48 83 c4 08          	add    $0x8,%rsp
    185a:	5b                   	pop    %rbx
    185b:	5d                   	pop    %rbp
    185c:	41 5c                	pop    %r12
    185e:	41 5d                	pop    %r13
    1860:	41 5e                	pop    %r14
    1862:	41 5f                	pop    %r15
    1864:	c3                   	retq   
    1865:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    186c:	00 00 00 00 

0000000000001870 <__libc_csu_fini>:
    1870:	f3 0f 1e fa          	endbr64 
    1874:	c3                   	retq   

Disassembly of section .fini:

0000000000001878 <_fini>:
    1878:	f3 0f 1e fa          	endbr64 
    187c:	48 83 ec 08          	sub    $0x8,%rsp
    1880:	48 83 c4 08          	add    $0x8,%rsp
    1884:	c3                   	retq   
