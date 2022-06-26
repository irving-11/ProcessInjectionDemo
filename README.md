# ProcessInjectionDemo

BTFParse目录：生成、解析BTF信息等，脚本do.sh使用方法：**sh do.sh elf_file_path(need debuginfo)**

cves目录：其中set_1_with_ubpf目录是集成ubpf到patch后的一些cve

patch-demo/ubpf/vm目录：patch机制demo，simple-test.c集成ubpf。my_test.ebpf.c为补丁。ptrace-hook.c为hook源文件。


### 需要解决的问题  
1. 理解可变参数传参，如何将C函数传入到ebpf调用  
2. 稳定的Hook机制，回到原函数，undo hook  

### 任务（updated by 2-19）： 

1. 开始总结不同Patch机制（文档可写在Github），实现每一种机制的Demo进行性能对比。 TODO: 进一步细化任务。
   - 需要考虑哪几种机制，每一种原理写成文档
   - 对比各种机制，找出需要实现Demo的机制
   - 进行性能对比，如何准确的评估占用时间。如何在多线程多进程环境下测试。
   - 找到更合适的测试目标：tcpdump，openssl等专用库（参考yuan zhang的几篇patch的文章中用到的库）。
2. 试用和熟悉eBPF功能，理解BTF机制。 

参考：

1. linux下的hook方法  

https://xz.aliyun.com/t/6961

2. eBPF-study/README.md  

   
