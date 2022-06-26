#include <stdio.h>
#include <memory.h>
#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <elf.h>

int main(int argc, char* argv[])
{
	// 参数错误
	if (argc < 3)
	{
		printf("invalid arguments\n");
		exit(-1);
	}

	// 打开文件
	FILE *fp, *w_fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("fail to open the file\n");
		exit(-1);
	}
    w_fp = fopen(argv[2], "wb");
	if (w_fp == NULL)
	{
		printf("fail to open the w_file\n");
		exit(-1);
	}

	// 解析head
	Elf64_Ehdr elf_head;
	int ret;

	// 读取 head 到elf_head
	ret = fread(&elf_head, sizeof(Elf64_Ehdr), 1, fp);   //fread参数1：读取内容存储地址，参数2：读取内容大小，参数3：读取次数，参数4：文件读取引擎
	if (ret == 0)
	{
		printf("fail to read head\n");
		exit(-1);
	}

	// 判断elf文件类型
	if (elf_head.e_ident[0] != 0x7F ||
		elf_head.e_ident[1] != 'E' ||
		elf_head.e_ident[2] != 'L' ||
		elf_head.e_ident[3] != 'F')
	{
		printf("Not a ELF file\n");
		exit(-1);
	}

	// 解析section 分配内存 section * 数量
	Elf64_Shdr *shdr = (Elf64_Shdr*)malloc(sizeof(Elf64_Shdr) * elf_head.e_shnum);
	if (shdr == NULL)
	{
		printf("shdr malloc failed\n");
		exit(-1);
	}

	// 设置fp偏移量 offset，e_shoff含义
	ret = fseek(fp, elf_head.e_shoff, SEEK_SET); //fseek调整指针的位置，采用参考位置+偏移量
	if (ret != 0)
	{
		printf("faile to fseek\n");
		exit(-1);
	}

	// 读取section 到 shdr, 大小为shdr * 数量
	ret = fread(shdr, sizeof(Elf64_Shdr) * elf_head.e_shnum, 1, fp);
	if (ret == 0)
	{
		printf("fail to read section\n");
		exit(-1);
	}

	// 重置指针位置到文件流开头
	rewind(fp);

	// 将fp指针移到 '字符串表' 偏移位置处
	fseek(fp, shdr[elf_head.e_shstrndx].sh_offset, SEEK_SET);

	// 第e_shstrndx项是字符串表 定义 字节 长度 char类型 数组
	char shstrtab[shdr[elf_head.e_shstrndx].sh_size];
	char *temp = shstrtab;

	// 读取内容
	ret = fread(shstrtab, shdr[elf_head.e_shstrndx].sh_size, 1, fp);
	if (ret == 0)
	{
		printf("faile to read\n");
		exit(-1);
	}
    
	// 遍历
	for (int i = 0; i < elf_head.e_shnum; i++)
	{
		temp = shstrtab;
		temp = temp + shdr[i].sh_name;
        
        if (strcmp(temp, ".BTF") != 0) continue;//该section名称
		printf("节的名称: %s\n", temp);
		printf("节首的偏移: %lx\n", shdr[i].sh_offset);
		printf("节的大小: %lx\n", shdr[i].sh_size);
        uint8_t *sign_data=(uint8_t*)malloc(sizeof(uint8_t)*shdr[i].sh_size);
		// 依据此段在文件中的偏移读取出
		fseek(fp, shdr[i].sh_offset, SEEK_SET);
		fread(sign_data, sizeof(uint8_t)*shdr[i].sh_size, 1, fp);
		// 显示读取的内容
		// uint8_t *p = sign_data;
		for (int j = 0; j<shdr[i].sh_size; j++)
		{
		    printf("%x", *sign_data);
            fwrite(sign_data, sizeof(uint8_t)*shdr[i].sh_size, 1, w_fp);
            sign_data++;
		}
    }

    fclose(fp);
    fclose(w_fp);
	return 0;
}