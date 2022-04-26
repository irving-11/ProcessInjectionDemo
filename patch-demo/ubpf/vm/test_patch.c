#define _GNU_SOURCE

#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <elf.h>
#include <math.h>
#include "ubpf.h"

static uint8_t code0[] = ""
"\x61\x11\x00\x00\x00\x00\x00\x00\x07\x01\x00\x00\x2f\xf8\xff\xff\x67\x01\x00\x00\x20\x00\x00\x00\x77"
"\x01\x00\x00\x20\x00\x00\x00\xb7\x00\x00\x00\x01\x00\x00\x00\xb7\x02\x00\x00\xb8\x0b\x00\x00\x2d\x12"
"\x01\x00\x00\x00\x00\x00\xb7\x00\x00\x00\x00\x00\x00\x00\x67\x00\x00\x00\x20\x00\x00\x00\x95\x00\x00"
"\x00\x00\x00\x00\x00"
"";

struct Mem
{
    uint32_t a;
    uint32_t b;
};

static void usage(const char *name)
{
    fprintf(stderr, "usage: %s [-h] [-j|--jit] [-m|--mem PATH] BINARY\n", name);
    fprintf(stderr, "\nExecutes the eBPF code in BINARY and prints the result to stdout.\n");
    fprintf(stderr, "If --mem is given then the specified file will be read and a pointer\nto its data passed in r1.\n");
    fprintf(stderr, "If --jit is given then the JIT compiler will be used.\n");
    fprintf(stderr, "\nOther options:\n");
    fprintf(stderr, "  -r, --register-offset NUM: Change the mapping from eBPF to x86 registers\n");
}

/*static void *readfile(const char *path, size_t maxlen, size_t *len)
{
    FILE *file;
    if (!strcmp(path, "-")) {
        file = fdopen(STDIN_FILENO, "r");
    } else {
        file = fopen(path, "r");
    }

    if (file == NULL) {
        fprintf(stderr, "Failed to open %s: %s\n", path, strerror(errno));
        return NULL;
    }

    void *data = calloc(maxlen, 1);
    size_t offset = 0;
    size_t rv;
    while ((rv = fread(data+offset, 1, maxlen-offset, file)) > 0) {
        offset += rv;
    }

    if (ferror(file)) {
        fprintf(stderr, "Failed to read %s: %s\n", path, strerror(errno));
        fclose(file);
        free(data);
        return NULL;
    }

    if (!feof(file)) {
        fprintf(stderr, "Failed to read %s because it is too large (max %u bytes)\n",
                path, (unsigned)maxlen);
        fclose(file);
        free(data);
        return NULL;
    }

    fclose(file);
    if (len) {
        *len = offset;
    }
    return data;
}*/

int orig_c0(int v) {
	if (v > 2000) { // fixed: v > 5000 return -1
		//DEBUG_LOG("test_dynamic_bug-112: %d\n", v);
		return -1;
	}
	//DEBUG_LOG("test_dynamic_bug-: %d\n", v);
	return 0;
}

int main(int argc, char **argv) {
	struct Mem *bpf;// = (struct Mem *)mem;
    bpf->a = 3000;
    bpf->b = 1;

	struct option longopts[] = {
        { .name = "help", .val = 'h', },
        { .name = "mem", .val = 'm', .has_arg=1 },
        { .name = "jit", .val = 'j' },
        { .name = "register-offset", .val = 'r', .has_arg=1 },
        { }
    };

    const char *mem_filename = NULL;
    bool jit = false;

    int opt;
    while ((opt = getopt_long(argc, argv, "hm:jr:UR", longopts, NULL)) != -1) {
        switch (opt) {
        case 'm':
            mem_filename = optarg;
            break;
        case 'j':
            jit = true;
            break;
        case 'r':
            ubpf_set_register_offset(atoi(optarg));
            break;
        case 'h':
            usage(argv[0]);
            return 0;
        default:
            usage(argv[0]);
            return 1;
        }
    }

    if (argc != optind + 1) {
        usage(argv[0]);
        return 1;
    }

    const char *code_filename = argv[optind];
    size_t code_len;
    void *code = readfile(code_filename, 1024*1024, &code_len);
    if (code == NULL) {
        return 1;
    }

    size_t mem_len = 0;
    void *mem = NULL;
    if (mem_filename != NULL) {
        mem = readfile(mem_filename, 1024*1024, &mem_len);
        if (mem == NULL) {
            return 1;
        }
    }

    struct ubpf_vm *vm = ubpf_create();
    if (!vm) {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    register_functions(vm);
    
    /* 
     * The ELF magic corresponds to an RSH instruction with an offset,
     * which is invalid.
     */
    bool elf = code_len >= SELFMAG && !memcmp(code, ELFMAG, SELFMAG);

    char *errmsg;
    int rv;

    if (elf) {
	rv = ubpf_load_elf(vm, code, code_len, &errmsg);
    } else {
	rv = ubpf_load(vm, code, code_len, &errmsg);
    }

    free(code);

    if (rv < 0) {
        fprintf(stderr, "Failed to load code: %s\n", errmsg);
        free(errmsg);
        ubpf_destroy(vm);
        return 1;
    }

    uint64_t ret;
    if (jit) {
        ubpf_jit_fn fn = ubpf_compile(vm, &errmsg);
        if (fn == NULL) {
            fprintf(stderr, "Failed to compile: %s\n", errmsg);
            free(errmsg);
            free(mem);
            return 1;
        }
        ret = fn(mem, mem_len);
    } else {
        if (ubpf_exec(vm, mem, mem_len, &ret) < 0)
            ret = UINT64_MAX;
    }

    printf("0x%"PRIx64"\n", ret);

    ubpf_destroy(vm);
    free(mem);

	orig_c0(2500);

}

