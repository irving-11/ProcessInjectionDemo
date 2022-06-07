
test1:     file format elf64-x86-64


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
    1020:	ff 35 82 2f 00 00    	pushq  0x2f82(%rip)        # 3fa8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 83 2f 00 00 	bnd jmpq *0x2f83(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x10>
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

Disassembly of section .plt.got:

0000000000001070 <__cxa_finalize@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 7d 2f 00 00 	bnd jmpq *0x2f7d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001080 <puts@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 2d 2f 00 00 	bnd jmpq *0x2f2d(%rip)        # 3fb8 <puts@GLIBC_2.2.5>
    108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001090 <__stack_chk_fail@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 25 2f 00 00 	bnd jmpq *0x2f25(%rip)        # 3fc0 <__stack_chk_fail@GLIBC_2.4>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010a0 <__assert_fail@plt>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	f2 ff 25 1d 2f 00 00 	bnd jmpq *0x2f1d(%rip)        # 3fc8 <__assert_fail@GLIBC_2.2.5>
    10ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010b0 <__printf_chk@plt>:
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	f2 ff 25 15 2f 00 00 	bnd jmpq *0x2f15(%rip)        # 3fd0 <__printf_chk@GLIBC_2.3.4>
    10bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010c0 <_start>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	31 ed                	xor    %ebp,%ebp
    10c6:	49 89 d1             	mov    %rdx,%r9
    10c9:	5e                   	pop    %rsi
    10ca:	48 89 e2             	mov    %rsp,%rdx
    10cd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10d1:	50                   	push   %rax
    10d2:	54                   	push   %rsp
    10d3:	4c 8d 05 26 07 00 00 	lea    0x726(%rip),%r8        # 1800 <__libc_csu_fini>
    10da:	48 8d 0d af 06 00 00 	lea    0x6af(%rip),%rcx        # 1790 <__libc_csu_init>
    10e1:	48 8d 3d 7f 06 00 00 	lea    0x67f(%rip),%rdi        # 1767 <main>
    10e8:	ff 15 f2 2e 00 00    	callq  *0x2ef2(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    10ee:	f4                   	hlt    
    10ef:	90                   	nop

00000000000010f0 <deregister_tm_clones>:
    10f0:	48 8d 3d 19 2f 00 00 	lea    0x2f19(%rip),%rdi        # 4010 <__TMC_END__>
    10f7:	48 8d 05 12 2f 00 00 	lea    0x2f12(%rip),%rax        # 4010 <__TMC_END__>
    10fe:	48 39 f8             	cmp    %rdi,%rax
    1101:	74 15                	je     1118 <deregister_tm_clones+0x28>
    1103:	48 8b 05 ce 2e 00 00 	mov    0x2ece(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    110a:	48 85 c0             	test   %rax,%rax
    110d:	74 09                	je     1118 <deregister_tm_clones+0x28>
    110f:	ff e0                	jmpq   *%rax
    1111:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1118:	c3                   	retq   
    1119:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001120 <register_tm_clones>:
    1120:	48 8d 3d e9 2e 00 00 	lea    0x2ee9(%rip),%rdi        # 4010 <__TMC_END__>
    1127:	48 8d 35 e2 2e 00 00 	lea    0x2ee2(%rip),%rsi        # 4010 <__TMC_END__>
    112e:	48 29 fe             	sub    %rdi,%rsi
    1131:	48 89 f0             	mov    %rsi,%rax
    1134:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1138:	48 c1 f8 03          	sar    $0x3,%rax
    113c:	48 01 c6             	add    %rax,%rsi
    113f:	48 d1 fe             	sar    %rsi
    1142:	74 14                	je     1158 <register_tm_clones+0x38>
    1144:	48 8b 05 a5 2e 00 00 	mov    0x2ea5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    114b:	48 85 c0             	test   %rax,%rax
    114e:	74 08                	je     1158 <register_tm_clones+0x38>
    1150:	ff e0                	jmpq   *%rax
    1152:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1158:	c3                   	retq   
    1159:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001160 <__do_global_dtors_aux>:
    1160:	f3 0f 1e fa          	endbr64 
    1164:	80 3d a5 2e 00 00 00 	cmpb   $0x0,0x2ea5(%rip)        # 4010 <__TMC_END__>
    116b:	75 2b                	jne    1198 <__do_global_dtors_aux+0x38>
    116d:	55                   	push   %rbp
    116e:	48 83 3d 82 2e 00 00 	cmpq   $0x0,0x2e82(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1175:	00 
    1176:	48 89 e5             	mov    %rsp,%rbp
    1179:	74 0c                	je     1187 <__do_global_dtors_aux+0x27>
    117b:	48 8b 3d 86 2e 00 00 	mov    0x2e86(%rip),%rdi        # 4008 <__dso_handle>
    1182:	e8 e9 fe ff ff       	callq  1070 <__cxa_finalize@plt>
    1187:	e8 64 ff ff ff       	callq  10f0 <deregister_tm_clones>
    118c:	c6 05 7d 2e 00 00 01 	movb   $0x1,0x2e7d(%rip)        # 4010 <__TMC_END__>
    1193:	5d                   	pop    %rbp
    1194:	c3                   	retq   
    1195:	0f 1f 00             	nopl   (%rax)
    1198:	c3                   	retq   
    1199:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011a0 <frame_dummy>:
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	e9 77 ff ff ff       	jmpq   1120 <register_tm_clones>

00000000000011a9 <test_variable_args>:
    11a9:	f3 0f 1e fa          	endbr64 
    11ad:	c3                   	retq   

00000000000011ae <dump_4args>:
    11ae:	f3 0f 1e fa          	endbr64 
    11b2:	41 56                	push   %r14
    11b4:	41 55                	push   %r13
    11b6:	41 54                	push   %r12
    11b8:	55                   	push   %rbp
    11b9:	53                   	push   %rbx
    11ba:	48 89 f5             	mov    %rsi,%rbp
    11bd:	49 89 fc             	mov    %rdi,%r12
    11c0:	49 89 d5             	mov    %rdx,%r13
    11c3:	49 89 ce             	mov    %rcx,%r14
    11c6:	41 51                	push   %r9
    11c8:	41 50                	push   %r8
    11ca:	49 89 c9             	mov    %rcx,%r9
    11cd:	49 89 d0             	mov    %rdx,%r8
    11d0:	48 89 f1             	mov    %rsi,%rcx
    11d3:	48 89 fa             	mov    %rdi,%rdx
    11d6:	48 8d 35 2b 0e 00 00 	lea    0xe2b(%rip),%rsi        # 2008 <_IO_stdin_used+0x8>
    11dd:	bf 01 00 00 00       	mov    $0x1,%edi
    11e2:	b8 00 00 00 00       	mov    $0x0,%eax
    11e7:	e8 c4 fe ff ff       	callq  10b0 <__printf_chk@plt>
    11ec:	45 8b 0e             	mov    (%r14),%r9d
    11ef:	4d 89 e8             	mov    %r13,%r8
    11f2:	8b 4d 00             	mov    0x0(%rbp),%ecx
    11f5:	4c 89 e2             	mov    %r12,%rdx
    11f8:	48 8d 35 49 0e 00 00 	lea    0xe49(%rip),%rsi        # 2048 <_IO_stdin_used+0x48>
    11ff:	bf 01 00 00 00       	mov    $0x1,%edi
    1204:	b8 00 00 00 00       	mov    $0x0,%eax
    1209:	e8 a2 fe ff ff       	callq  10b0 <__printf_chk@plt>
    120e:	44 8b 4d 00          	mov    0x0(%rbp),%r9d
    1212:	48 83 c4 10          	add    $0x10,%rsp
    1216:	48 39 ed             	cmp    %rbp,%rbp
    1219:	75 35                	jne    1250 <dump_4args+0xa2>
    121b:	8b 45 00             	mov    0x0(%rbp),%eax
    121e:	50                   	push   %rax
    121f:	55                   	push   %rbp
    1220:	49 89 e8             	mov    %rbp,%r8
    1223:	48 8d 0d 43 10 00 00 	lea    0x1043(%rip),%rcx        # 226d <_IO_stdin_used+0x26d>
    122a:	48 89 ea             	mov    %rbp,%rdx
    122d:	48 8d 35 3c 0e 00 00 	lea    0xe3c(%rip),%rsi        # 2070 <_IO_stdin_used+0x70>
    1234:	bf 01 00 00 00       	mov    $0x1,%edi
    1239:	b8 00 00 00 00       	mov    $0x0,%eax
    123e:	e8 6d fe ff ff       	callq  10b0 <__printf_chk@plt>
    1243:	48 83 c4 10          	add    $0x10,%rsp
    1247:	5b                   	pop    %rbx
    1248:	5d                   	pop    %rbp
    1249:	41 5c                	pop    %r12
    124b:	41 5d                	pop    %r13
    124d:	41 5e                	pop    %r14
    124f:	c3                   	retq   
    1250:	48 8d 0d 89 10 00 00 	lea    0x1089(%rip),%rcx        # 22e0 <__PRETTY_FUNCTION__.3268>
    1257:	ba 3b 00 00 00       	mov    $0x3b,%edx
    125c:	48 8d 35 ee 0f 00 00 	lea    0xfee(%rip),%rsi        # 2251 <_IO_stdin_used+0x251>
    1263:	48 8d 3d ef 0f 00 00 	lea    0xfef(%rip),%rdi        # 2259 <_IO_stdin_used+0x259>
    126a:	e8 31 fe ff ff       	callq  10a0 <__assert_fail@plt>

000000000000126f <dump_6args>:
    126f:	f3 0f 1e fa          	endbr64 
    1273:	41 57                	push   %r15
    1275:	41 56                	push   %r14
    1277:	41 55                	push   %r13
    1279:	41 54                	push   %r12
    127b:	55                   	push   %rbp
    127c:	53                   	push   %rbx
    127d:	48 83 ec 08          	sub    $0x8,%rsp
    1281:	48 89 fb             	mov    %rdi,%rbx
    1284:	48 89 f5             	mov    %rsi,%rbp
    1287:	49 89 d7             	mov    %rdx,%r15
    128a:	49 89 cc             	mov    %rcx,%r12
    128d:	4d 89 c5             	mov    %r8,%r13
    1290:	4d 89 ce             	mov    %r9,%r14
    1293:	41 51                	push   %r9
    1295:	41 50                	push   %r8
    1297:	49 89 c9             	mov    %rcx,%r9
    129a:	49 89 d0             	mov    %rdx,%r8
    129d:	48 89 f1             	mov    %rsi,%rcx
    12a0:	48 89 fa             	mov    %rdi,%rdx
    12a3:	48 8d 35 5e 0d 00 00 	lea    0xd5e(%rip),%rsi        # 2008 <_IO_stdin_used+0x8>
    12aa:	bf 01 00 00 00       	mov    $0x1,%edi
    12af:	b8 00 00 00 00       	mov    $0x0,%eax
    12b4:	e8 f7 fd ff ff       	callq  10b0 <__printf_chk@plt>
    12b9:	49 8b 07             	mov    (%r15),%rax
    12bc:	49 8b 16             	mov    (%r14),%rdx
    12bf:	8b 12                	mov    (%rdx),%edx
    12c1:	52                   	push   %rdx
    12c2:	41 8b 55 00          	mov    0x0(%r13),%edx
    12c6:	52                   	push   %rdx
    12c7:	4d 89 e1             	mov    %r12,%r9
    12ca:	44 8b 00             	mov    (%rax),%r8d
    12cd:	8b 4d 00             	mov    0x0(%rbp),%ecx
    12d0:	48 89 da             	mov    %rbx,%rdx
    12d3:	48 8d 35 be 0d 00 00 	lea    0xdbe(%rip),%rsi        # 2098 <_IO_stdin_used+0x98>
    12da:	bf 01 00 00 00       	mov    $0x1,%edi
    12df:	b8 00 00 00 00       	mov    $0x0,%eax
    12e4:	e8 c7 fd ff ff       	callq  10b0 <__printf_chk@plt>
    12e9:	48 83 c4 28          	add    $0x28,%rsp
    12ed:	5b                   	pop    %rbx
    12ee:	5d                   	pop    %rbp
    12ef:	41 5c                	pop    %r12
    12f1:	41 5d                	pop    %r13
    12f3:	41 5e                	pop    %r14
    12f5:	41 5f                	pop    %r15
    12f7:	c3                   	retq   

00000000000012f8 <dump_9args>:
    12f8:	f3 0f 1e fa          	endbr64 
    12fc:	41 57                	push   %r15
    12fe:	41 56                	push   %r14
    1300:	41 55                	push   %r13
    1302:	41 54                	push   %r12
    1304:	55                   	push   %rbp
    1305:	53                   	push   %rbx
    1306:	48 83 ec 28          	sub    $0x28,%rsp
    130a:	48 89 e8             	mov    %rbp,%rax
    130d:	48 89 7c 24 08       	mov    %rdi,0x8(%rsp)
    1312:	48 89 f3             	mov    %rsi,%rbx
    1315:	48 89 54 24 10       	mov    %rdx,0x10(%rsp)
    131a:	48 89 4c 24 18       	mov    %rcx,0x18(%rsp)
    131f:	4d 89 c4             	mov    %r8,%r12
    1322:	4d 89 cd             	mov    %r9,%r13
    1325:	4c 8b 75 10          	mov    0x10(%rbp),%r14
    1329:	4c 8b 7d 18          	mov    0x18(%rbp),%r15
    132d:	48 8b 6d 20          	mov    0x20(%rbp),%rbp
    1331:	4c 8d 44 24 f8       	lea    -0x8(%rsp),%r8
    1336:	48 89 e1             	mov    %rsp,%rcx
    1339:	48 89 c2             	mov    %rax,%rdx
    133c:	48 8d 35 2d 0f 00 00 	lea    0xf2d(%rip),%rsi        # 2270 <_IO_stdin_used+0x270>
    1343:	bf 01 00 00 00       	mov    $0x1,%edi
    1348:	b8 00 00 00 00       	mov    $0x0,%eax
    134d:	e8 5e fd ff ff       	callq  10b0 <__printf_chk@plt>
    1352:	41 55                	push   %r13
    1354:	41 54                	push   %r12
    1356:	4c 8b 4c 24 28       	mov    0x28(%rsp),%r9
    135b:	4c 8b 44 24 20       	mov    0x20(%rsp),%r8
    1360:	48 89 d9             	mov    %rbx,%rcx
    1363:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
    1368:	48 8d 35 99 0c 00 00 	lea    0xc99(%rip),%rsi        # 2008 <_IO_stdin_used+0x8>
    136f:	bf 01 00 00 00       	mov    $0x1,%edi
    1374:	b8 00 00 00 00       	mov    $0x0,%eax
    1379:	e8 32 fd ff ff       	callq  10b0 <__printf_chk@plt>
    137e:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
    1383:	48 8b 00             	mov    (%rax),%rax
    1386:	48 8b 55 00          	mov    0x0(%rbp),%rdx
    138a:	8b 12                	mov    (%rdx),%edx
    138c:	89 14 24             	mov    %edx,(%rsp)
    138f:	41 8b 17             	mov    (%r15),%edx
    1392:	52                   	push   %rdx
    1393:	41 56                	push   %r14
    1395:	49 8b 55 00          	mov    0x0(%r13),%rdx
    1399:	8b 12                	mov    (%rdx),%edx
    139b:	52                   	push   %rdx
    139c:	41 8b 14 24          	mov    (%r12),%edx
    13a0:	52                   	push   %rdx
    13a1:	4c 8b 4c 24 48       	mov    0x48(%rsp),%r9
    13a6:	44 8b 00             	mov    (%rax),%r8d
    13a9:	8b 0b                	mov    (%rbx),%ecx
    13ab:	48 8b 54 24 38       	mov    0x38(%rsp),%rdx
    13b0:	48 8d 35 19 0d 00 00 	lea    0xd19(%rip),%rsi        # 20d0 <_IO_stdin_used+0xd0>
    13b7:	bf 01 00 00 00       	mov    $0x1,%edi
    13bc:	b8 00 00 00 00       	mov    $0x0,%eax
    13c1:	e8 ea fc ff ff       	callq  10b0 <__printf_chk@plt>
    13c6:	48 83 c4 58          	add    $0x58,%rsp
    13ca:	5b                   	pop    %rbx
    13cb:	5d                   	pop    %rbp
    13cc:	41 5c                	pop    %r12
    13ce:	41 5d                	pop    %r13
    13d0:	41 5e                	pop    %r14
    13d2:	41 5f                	pop    %r15
    13d4:	c3                   	retq   

00000000000013d5 <dump_N_args>:
    13d5:	f3 0f 1e fa          	endbr64 
    13d9:	41 57                	push   %r15
    13db:	41 56                	push   %r14
    13dd:	41 55                	push   %r13
    13df:	41 54                	push   %r12
    13e1:	55                   	push   %rbp
    13e2:	53                   	push   %rbx
    13e3:	48 83 ec 18          	sub    $0x18,%rsp
    13e7:	48 89 d5             	mov    %rdx,%rbp
    13ea:	48 89 f3             	mov    %rsi,%rbx
    13ed:	49 89 cd             	mov    %rcx,%r13
    13f0:	4d 89 c6             	mov    %r8,%r14
    13f3:	4d 89 cf             	mov    %r9,%r15
    13f6:	41 51                	push   %r9
    13f8:	41 50                	push   %r8
    13fa:	49 89 c9             	mov    %rcx,%r9
    13fd:	49 89 d0             	mov    %rdx,%r8
    1400:	48 89 f1             	mov    %rsi,%rcx
    1403:	48 89 7c 24 18       	mov    %rdi,0x18(%rsp)
    1408:	48 89 fa             	mov    %rdi,%rdx
    140b:	48 8d 35 f6 0b 00 00 	lea    0xbf6(%rip),%rsi        # 2008 <_IO_stdin_used+0x8>
    1412:	bf 01 00 00 00       	mov    $0x1,%edi
    1417:	b8 00 00 00 00       	mov    $0x0,%eax
    141c:	e8 8f fc ff ff       	callq  10b0 <__printf_chk@plt>
    1421:	41 8b 07             	mov    (%r15),%eax
    1424:	50                   	push   %rax
    1425:	41 56                	push   %r14
    1427:	45 8b 4d 00          	mov    0x0(%r13),%r9d
    142b:	49 89 e8             	mov    %rbp,%r8
    142e:	8b 0b                	mov    (%rbx),%ecx
    1430:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
    1435:	48 8d 35 5c 0c 00 00 	lea    0xc5c(%rip),%rsi        # 2098 <_IO_stdin_used+0x98>
    143c:	bf 01 00 00 00       	mov    $0x1,%edi
    1441:	b8 00 00 00 00       	mov    $0x0,%eax
    1446:	e8 65 fc ff ff       	callq  10b0 <__printf_chk@plt>
    144b:	44 8b 0b             	mov    (%rbx),%r9d
    144e:	48 83 c4 20          	add    $0x20,%rsp
    1452:	48 39 dd             	cmp    %rbx,%rbp
    1455:	75 37                	jne    148e <dump_N_args+0xb9>
    1457:	8b 45 00             	mov    0x0(%rbp),%eax
    145a:	50                   	push   %rax
    145b:	55                   	push   %rbp
    145c:	49 89 d8             	mov    %rbx,%r8
    145f:	48 8d 0d 07 0e 00 00 	lea    0xe07(%rip),%rcx        # 226d <_IO_stdin_used+0x26d>
    1466:	48 89 da             	mov    %rbx,%rdx
    1469:	48 8d 35 b0 0c 00 00 	lea    0xcb0(%rip),%rsi        # 2120 <_IO_stdin_used+0x120>
    1470:	bf 01 00 00 00       	mov    $0x1,%edi
    1475:	b8 00 00 00 00       	mov    $0x0,%eax
    147a:	e8 31 fc ff ff       	callq  10b0 <__printf_chk@plt>
    147f:	48 83 c4 28          	add    $0x28,%rsp
    1483:	5b                   	pop    %rbx
    1484:	5d                   	pop    %rbp
    1485:	41 5c                	pop    %r12
    1487:	41 5d                	pop    %r13
    1489:	41 5e                	pop    %r14
    148b:	41 5f                	pop    %r15
    148d:	c3                   	retq   
    148e:	48 8d 0d 3b 0e 00 00 	lea    0xe3b(%rip),%rcx        # 22d0 <__PRETTY_FUNCTION__.3346>
    1495:	ba 6e 00 00 00       	mov    $0x6e,%edx
    149a:	48 8d 35 b0 0d 00 00 	lea    0xdb0(%rip),%rsi        # 2251 <_IO_stdin_used+0x251>
    14a1:	48 8d 3d e1 0d 00 00 	lea    0xde1(%rip),%rdi        # 2289 <_IO_stdin_used+0x289>
    14a8:	e8 f3 fb ff ff       	callq  10a0 <__assert_fail@plt>

00000000000014ad <test_normal_3args>:
    14ad:	f3 0f 1e fa          	endbr64 
    14b1:	55                   	push   %rbp
    14b2:	53                   	push   %rbx
    14b3:	48 83 ec 18          	sub    $0x18,%rsp
    14b7:	89 7c 24 0c          	mov    %edi,0xc(%rsp)
    14bb:	48 89 f3             	mov    %rsi,%rbx
    14be:	48 89 d5             	mov    %rdx,%rbp
    14c1:	48 8d 3d 80 0c 00 00 	lea    0xc80(%rip),%rdi        # 2148 <_IO_stdin_used+0x148>
    14c8:	e8 b3 fb ff ff       	callq  1080 <puts@plt>
    14cd:	48 8d 54 24 0c       	lea    0xc(%rsp),%rdx
    14d2:	48 83 ec 08          	sub    $0x8,%rsp
    14d6:	48 89 e8             	mov    %rbp,%rax
    14d9:	48 29 d8             	sub    %rbx,%rax
    14dc:	50                   	push   %rax
    14dd:	49 89 d9             	mov    %rbx,%r9
    14e0:	49 29 d1             	sub    %rdx,%r9
    14e3:	49 89 e8             	mov    %rbp,%r8
    14e6:	48 89 d9             	mov    %rbx,%rcx
    14e9:	48 8d 35 90 0c 00 00 	lea    0xc90(%rip),%rsi        # 2180 <_IO_stdin_used+0x180>
    14f0:	bf 01 00 00 00       	mov    $0x1,%edi
    14f5:	b8 00 00 00 00       	mov    $0x0,%eax
    14fa:	e8 b1 fb ff ff       	callq  10b0 <__printf_chk@plt>
    14ff:	48 8b 45 00          	mov    0x0(%rbp),%rax
    1503:	44 8b 00             	mov    (%rax),%r8d
    1506:	8b 0b                	mov    (%rbx),%ecx
    1508:	8b 54 24 1c          	mov    0x1c(%rsp),%edx
    150c:	48 8d 35 8a 0d 00 00 	lea    0xd8a(%rip),%rsi        # 229d <_IO_stdin_used+0x29d>
    1513:	bf 01 00 00 00       	mov    $0x1,%edi
    1518:	b8 00 00 00 00       	mov    $0x0,%eax
    151d:	e8 8e fb ff ff       	callq  10b0 <__printf_chk@plt>
    1522:	48 83 c4 28          	add    $0x28,%rsp
    1526:	5b                   	pop    %rbx
    1527:	5d                   	pop    %rbp
    1528:	c3                   	retq   

0000000000001529 <test_normal_4args>:
    1529:	f3 0f 1e fa          	endbr64 
    152d:	41 55                	push   %r13
    152f:	41 54                	push   %r12
    1531:	55                   	push   %rbp
    1532:	53                   	push   %rbx
    1533:	48 83 ec 08          	sub    $0x8,%rsp
    1537:	89 fd                	mov    %edi,%ebp
    1539:	49 89 f4             	mov    %rsi,%r12
    153c:	89 d3                	mov    %edx,%ebx
    153e:	49 89 cd             	mov    %rcx,%r13
    1541:	48 8d 3d 68 0c 00 00 	lea    0xc68(%rip),%rdi        # 21b0 <_IO_stdin_used+0x1b0>
    1548:	e8 33 fb ff ff       	callq  1080 <puts@plt>
    154d:	48 63 db             	movslq %ebx,%rbx
    1550:	48 63 ed             	movslq %ebp,%rbp
    1553:	4c 89 e9             	mov    %r13,%rcx
    1556:	48 89 da             	mov    %rbx,%rdx
    1559:	4c 89 e6             	mov    %r12,%rsi
    155c:	48 89 ef             	mov    %rbp,%rdi
    155f:	e8 4a fc ff ff       	callq  11ae <dump_4args>
    1564:	49 89 e8             	mov    %rbp,%r8
    1567:	4c 89 e9             	mov    %r13,%rcx
    156a:	48 89 da             	mov    %rbx,%rdx
    156d:	4c 89 e6             	mov    %r12,%rsi
    1570:	48 89 ef             	mov    %rbp,%rdi
    1573:	e8 36 fc ff ff       	callq  11ae <dump_4args>
    1578:	48 83 c4 08          	add    $0x8,%rsp
    157c:	5b                   	pop    %rbx
    157d:	5d                   	pop    %rbp
    157e:	41 5c                	pop    %r12
    1580:	41 5d                	pop    %r13
    1582:	c3                   	retq   

0000000000001583 <test_normal_5args>:
    1583:	f3 0f 1e fa          	endbr64 
    1587:	c3                   	retq   

0000000000001588 <test_normal_6args>:
    1588:	f3 0f 1e fa          	endbr64 
    158c:	41 57                	push   %r15
    158e:	41 56                	push   %r14
    1590:	41 55                	push   %r13
    1592:	41 54                	push   %r12
    1594:	55                   	push   %rbp
    1595:	53                   	push   %rbx
    1596:	48 83 ec 08          	sub    $0x8,%rsp
    159a:	89 fb                	mov    %edi,%ebx
    159c:	49 89 f4             	mov    %rsi,%r12
    159f:	49 89 d5             	mov    %rdx,%r13
    15a2:	89 cd                	mov    %ecx,%ebp
    15a4:	4d 89 c6             	mov    %r8,%r14
    15a7:	4d 89 cf             	mov    %r9,%r15
    15aa:	48 8d 3d 37 0c 00 00 	lea    0xc37(%rip),%rdi        # 21e8 <_IO_stdin_used+0x1e8>
    15b1:	e8 ca fa ff ff       	callq  1080 <puts@plt>
    15b6:	4d 89 f9             	mov    %r15,%r9
    15b9:	4d 89 f0             	mov    %r14,%r8
    15bc:	89 e9                	mov    %ebp,%ecx
    15be:	4c 89 ea             	mov    %r13,%rdx
    15c1:	4c 89 e6             	mov    %r12,%rsi
    15c4:	89 df                	mov    %ebx,%edi
    15c6:	e8 a4 fc ff ff       	callq  126f <dump_6args>
    15cb:	48 63 ed             	movslq %ebp,%rbp
    15ce:	48 63 db             	movslq %ebx,%rbx
    15d1:	4d 89 f9             	mov    %r15,%r9
    15d4:	4d 89 f0             	mov    %r14,%r8
    15d7:	48 89 e9             	mov    %rbp,%rcx
    15da:	4c 89 ea             	mov    %r13,%rdx
    15dd:	4c 89 e6             	mov    %r12,%rsi
    15e0:	48 89 df             	mov    %rbx,%rdi
    15e3:	e8 87 fc ff ff       	callq  126f <dump_6args>
    15e8:	48 83 ec 08          	sub    $0x8,%rsp
    15ec:	53                   	push   %rbx
    15ed:	4d 89 f9             	mov    %r15,%r9
    15f0:	4d 89 f0             	mov    %r14,%r8
    15f3:	48 89 e9             	mov    %rbp,%rcx
    15f6:	4c 89 ea             	mov    %r13,%rdx
    15f9:	4c 89 e6             	mov    %r12,%rsi
    15fc:	48 89 df             	mov    %rbx,%rdi
    15ff:	e8 6b fc ff ff       	callq  126f <dump_6args>
    1604:	41 54                	push   %r12
    1606:	53                   	push   %rbx
    1607:	4d 89 f9             	mov    %r15,%r9
    160a:	4d 89 f0             	mov    %r14,%r8
    160d:	48 89 e9             	mov    %rbp,%rcx
    1610:	4c 89 ea             	mov    %r13,%rdx
    1613:	4c 89 e6             	mov    %r12,%rsi
    1616:	48 89 df             	mov    %rbx,%rdi
    1619:	e8 51 fc ff ff       	callq  126f <dump_6args>
    161e:	48 83 c4 28          	add    $0x28,%rsp
    1622:	5b                   	pop    %rbx
    1623:	5d                   	pop    %rbp
    1624:	41 5c                	pop    %r12
    1626:	41 5d                	pop    %r13
    1628:	41 5e                	pop    %r14
    162a:	41 5f                	pop    %r15
    162c:	c3                   	retq   

000000000000162d <test_normal_8args>:
    162d:	f3 0f 1e fa          	endbr64 
    1631:	c3                   	retq   

0000000000001632 <test_normal_9args>:
    1632:	f3 0f 1e fa          	endbr64 
    1636:	41 57                	push   %r15
    1638:	41 56                	push   %r14
    163a:	41 55                	push   %r13
    163c:	41 54                	push   %r12
    163e:	55                   	push   %rbp
    163f:	53                   	push   %rbx
    1640:	48 83 ec 08          	sub    $0x8,%rsp
    1644:	89 fb                	mov    %edi,%ebx
    1646:	48 89 f5             	mov    %rsi,%rbp
    1649:	49 89 d4             	mov    %rdx,%r12
    164c:	41 89 cd             	mov    %ecx,%r13d
    164f:	4d 89 c6             	mov    %r8,%r14
    1652:	4d 89 cf             	mov    %r9,%r15
    1655:	48 8d 3d c4 0b 00 00 	lea    0xbc4(%rip),%rdi        # 2220 <_IO_stdin_used+0x220>
    165c:	e8 1f fa ff ff       	callq  1080 <puts@plt>
    1661:	48 83 ec 08          	sub    $0x8,%rsp
    1665:	ff 74 24 58          	pushq  0x58(%rsp)
    1669:	ff 74 24 58          	pushq  0x58(%rsp)
    166d:	8b 44 24 58          	mov    0x58(%rsp),%eax
    1671:	50                   	push   %rax
    1672:	4d 89 f9             	mov    %r15,%r9
    1675:	4d 89 f0             	mov    %r14,%r8
    1678:	44 89 e9             	mov    %r13d,%ecx
    167b:	4c 89 e2             	mov    %r12,%rdx
    167e:	48 89 ee             	mov    %rbp,%rsi
    1681:	89 df                	mov    %ebx,%edi
    1683:	e8 70 fc ff ff       	callq  12f8 <dump_9args>
    1688:	48 83 c4 28          	add    $0x28,%rsp
    168c:	5b                   	pop    %rbx
    168d:	5d                   	pop    %rbp
    168e:	41 5c                	pop    %r12
    1690:	41 5d                	pop    %r13
    1692:	41 5e                	pop    %r14
    1694:	41 5f                	pop    %r15
    1696:	c3                   	retq   

0000000000001697 <test_normal_12args>:
    1697:	f3 0f 1e fa          	endbr64 
    169b:	c3                   	retq   

000000000000169c <test_normal_args>:
    169c:	f3 0f 1e fa          	endbr64 
    16a0:	41 54                	push   %r12
    16a2:	55                   	push   %rbp
    16a3:	53                   	push   %rbx
    16a4:	48 83 ec 30          	sub    $0x30,%rsp
    16a8:	bd 28 00 00 00       	mov    $0x28,%ebp
    16ad:	64 48 8b 45 00       	mov    %fs:0x0(%rbp),%rax
    16b2:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
    16b7:	31 c0                	xor    %eax,%eax
    16b9:	c7 44 24 04 02 00 00 	movl   $0x2,0x4(%rsp)
    16c0:	00 
    16c1:	c7 44 24 08 03 00 00 	movl   $0x3,0x8(%rsp)
    16c8:	00 
    16c9:	c7 44 24 0c 04 00 00 	movl   $0x4,0xc(%rsp)
    16d0:	00 
    16d1:	c7 44 24 10 05 00 00 	movl   $0x5,0x10(%rsp)
    16d8:	00 
    16d9:	c7 44 24 14 06 00 00 	movl   $0x6,0x14(%rsp)
    16e0:	00 
    16e1:	48 8d 44 24 08       	lea    0x8(%rsp),%rax
    16e6:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
    16eb:	48 8d 44 24 14       	lea    0x14(%rsp),%rax
    16f0:	48 89 44 24 20       	mov    %rax,0x20(%rsp)
    16f5:	4c 8d 64 24 18       	lea    0x18(%rsp),%r12
    16fa:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx
    16ff:	4c 89 e2             	mov    %r12,%rdx
    1702:	48 89 de             	mov    %rbx,%rsi
    1705:	bf 01 00 00 00       	mov    $0x1,%edi
    170a:	e8 9e fd ff ff       	callq  14ad <test_normal_3args>
    170f:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
    1714:	8b 54 24 08          	mov    0x8(%rsp),%edx
    1718:	48 89 de             	mov    %rbx,%rsi
    171b:	bf 01 00 00 00       	mov    $0x1,%edi
    1720:	e8 04 fe ff ff       	callq  1529 <test_normal_4args>
    1725:	4c 8d 4c 24 20       	lea    0x20(%rsp),%r9
    172a:	4c 8d 44 24 10       	lea    0x10(%rsp),%r8
    172f:	8b 4c 24 0c          	mov    0xc(%rsp),%ecx
    1733:	4c 89 e2             	mov    %r12,%rdx
    1736:	48 89 de             	mov    %rbx,%rsi
    1739:	bf 01 00 00 00       	mov    $0x1,%edi
    173e:	e8 45 fe ff ff       	callq  1588 <test_normal_6args>
    1743:	48 8b 44 24 28       	mov    0x28(%rsp),%rax
    1748:	64 48 33 45 00       	xor    %fs:0x0(%rbp),%rax
    174d:	75 09                	jne    1758 <test_normal_args+0xbc>
    174f:	48 83 c4 30          	add    $0x30,%rsp
    1753:	5b                   	pop    %rbx
    1754:	5d                   	pop    %rbp
    1755:	41 5c                	pop    %r12
    1757:	c3                   	retq   
    1758:	e8 33 f9 ff ff       	callq  1090 <__stack_chk_fail@plt>

000000000000175d <standard_args>:
    175d:	f3 0f 1e fa          	endbr64 
    1761:	c3                   	retq   

0000000000001762 <test_complex_args>:
    1762:	f3 0f 1e fa          	endbr64 
    1766:	c3                   	retq   

0000000000001767 <main>:
    1767:	f3 0f 1e fa          	endbr64 
    176b:	48 83 ec 08          	sub    $0x8,%rsp
    176f:	48 8d 3d 3a 0b 00 00 	lea    0xb3a(%rip),%rdi        # 22b0 <_IO_stdin_used+0x2b0>
    1776:	e8 05 f9 ff ff       	callq  1080 <puts@plt>
    177b:	b8 00 00 00 00       	mov    $0x0,%eax
    1780:	e8 17 ff ff ff       	callq  169c <test_normal_args>
    1785:	b8 00 00 00 00       	mov    $0x0,%eax
    178a:	48 83 c4 08          	add    $0x8,%rsp
    178e:	c3                   	retq   
    178f:	90                   	nop

0000000000001790 <__libc_csu_init>:
    1790:	f3 0f 1e fa          	endbr64 
    1794:	41 57                	push   %r15
    1796:	4c 8d 3d 03 26 00 00 	lea    0x2603(%rip),%r15        # 3da0 <__frame_dummy_init_array_entry>
    179d:	41 56                	push   %r14
    179f:	49 89 d6             	mov    %rdx,%r14
    17a2:	41 55                	push   %r13
    17a4:	49 89 f5             	mov    %rsi,%r13
    17a7:	41 54                	push   %r12
    17a9:	41 89 fc             	mov    %edi,%r12d
    17ac:	55                   	push   %rbp
    17ad:	48 8d 2d f4 25 00 00 	lea    0x25f4(%rip),%rbp        # 3da8 <__do_global_dtors_aux_fini_array_entry>
    17b4:	53                   	push   %rbx
    17b5:	4c 29 fd             	sub    %r15,%rbp
    17b8:	48 83 ec 08          	sub    $0x8,%rsp
    17bc:	e8 3f f8 ff ff       	callq  1000 <_init>
    17c1:	48 c1 fd 03          	sar    $0x3,%rbp
    17c5:	74 1f                	je     17e6 <__libc_csu_init+0x56>
    17c7:	31 db                	xor    %ebx,%ebx
    17c9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    17d0:	4c 89 f2             	mov    %r14,%rdx
    17d3:	4c 89 ee             	mov    %r13,%rsi
    17d6:	44 89 e7             	mov    %r12d,%edi
    17d9:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    17dd:	48 83 c3 01          	add    $0x1,%rbx
    17e1:	48 39 dd             	cmp    %rbx,%rbp
    17e4:	75 ea                	jne    17d0 <__libc_csu_init+0x40>
    17e6:	48 83 c4 08          	add    $0x8,%rsp
    17ea:	5b                   	pop    %rbx
    17eb:	5d                   	pop    %rbp
    17ec:	41 5c                	pop    %r12
    17ee:	41 5d                	pop    %r13
    17f0:	41 5e                	pop    %r14
    17f2:	41 5f                	pop    %r15
    17f4:	c3                   	retq   
    17f5:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    17fc:	00 00 00 00 

0000000000001800 <__libc_csu_fini>:
    1800:	f3 0f 1e fa          	endbr64 
    1804:	c3                   	retq   

Disassembly of section .fini:

0000000000001808 <_fini>:
    1808:	f3 0f 1e fa          	endbr64 
    180c:	48 83 ec 08          	sub    $0x8,%rsp
    1810:	48 83 c4 08          	add    $0x8,%rsp
    1814:	c3                   	retq   
