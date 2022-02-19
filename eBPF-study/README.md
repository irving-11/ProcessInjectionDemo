

## 一. 试用eBPF功能

目标：掌握eBPF程序加载。理解eBPF用户态程序依赖库。

1. 理解eBPF基本概念

   https://imliuda.com/post/1047  

   https://docs.cilium.io/en/v1.9/bpf/  

2. 开发简单eBPF程序(上)  

   [https://github.com/bpftools/linux-observability-with-bpf/](https://github.com/bpftools/linux-observability-with-bpf/tree/master/code/chapter-2/hello_world)

3. 开发简单eBPF程序(下)  

   试用bcc工具链，利用python加载eBPF。  

   

## 二. 理解eBPF跨平台(CO-RE)

目标：理解eBPF为什么需要BTF，以及掌握BTF细节。

1. 读Towards_truly_portable_eBPF  

https://github.com/ehids/slide/blob/master/eBPF_advanced/LPC21_Towards_truly_portable_eBPF.pdf  

2. 理解bpf-bootstrap是如何利用BTF  

   https://github.com/libbpf/libbpf-bootstrap  

3. 思考如何给第三方库实现BTF  
4. 思考如何在BTF中增加更多的Metadata来帮助测试和验证Patch是否正确  