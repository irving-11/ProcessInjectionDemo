#include "../private/coder.h"
#include "../minirpc.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h>
#include <errno.h>
#include <math.h>
#include "ubpf_int.h"

typedef struct stack_frame
{
    uint64_t a1;
    uint64_t a2;
    uint64_t a3;
    uint64_t a4;
    uint64_t a5;
} __attribute__((__packed__, aligned(4))) stack_frame;

int run_ebpf(stack_frame *frame, const char *bytecode, unsigned long len);
int patch_dispatcher(stack_frame *frame);
void patch_handler();

int pid;
int cve_num;
static int8_t *bytecode;
uint64_t bytecode_len;

int dummy_cve_0(int);
int dummy_cve_1(int);
// cve_2017_7862
typedef struct AVCodecContext
{
    int bits_per_raw_sample;
    int width, height;
    void *priv_data;
} AVCodecContext;
typedef struct PicContext {
    int width, height;
    int nb_planes;
    // GetByteContext g;
} PicContext;
typedef struct AVPacket {
    int   size;
} AVPacket;
int dummy_cve_2(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt);

// typedef int (*BPF_CALL1)(void *);
// typedef void (*BPF_CALL2)(void *, void *);
// typedef void (*BPF_CALL3)(void *, void *, void *);

// typedef int (*FunctionCallback)(int);
// BPF_CALL1 functions[] = {&dummy_cve_0, &dummy_cve_1};

#define VERIFY(x)    \
    do               \
    {                \
        if (!(x))    \
        {            \
            abort(); \
        }            \
    } while (0)

static void mrpc_req_cb(const struct mrpc_response *res, void *data)
{
    VERIFY(res != NULL);
    // ifdefine  INT or  STRING 区分返回值类型?
    bytecode_len = res->result.value.varchar.len;
    bytecode = (uint8_t *)malloc(bytecode_len);
    for (int i = 0; i < bytecode_len; i++)
    {
        // printf("%x\n", res->result.value.varchar.val[i]);
        bytecode[i] = (unsigned char)res->result.value.varchar.val[i];
    }
    // bytecode = (uint8_t *)res->result.value.varchar.val;
    printf("get ebpf code, size: %ld\n", bytecode_len);
    mrpc_interrupt();
}

int dummy_cve_0(int val)
{
    if (val > 2000)
        return 1;
    return 0;
}

int dummy_cve_1(int val)
{
    if (val > 2000)
        return 1;
    return 0;
}

int dummy_cve_2(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt) {
    int ret = 0;
    PicContext *s = avctx->priv_data;

    if (s->width != avctx->width && s->height != avctx->height)
    // patch
    //if (s->width != avctx->width || s->height != avctx->height) 
        ret = -1;
    
    return ret;
}

static void *thread_main(void *par)
{
    // VERIFY(mrpc_request_async(mrpc_req_cb,NULL,5000,"127.0.0.1:12345",MRPC_FUNCTION,"Add","%u%u",1,3) == 0);
    VERIFY(mrpc_request_async(mrpc_req_cb, NULL, 5000, "127.0.0.1:12345", MRPC_FUNCTION, "do_patch", "%u%u", pid, cve_num) == 0);
    return NULL;
}

void rpc_patch()
{
    pthread_t thread_1;
    pthread_create(&thread_1, NULL, thread_main, NULL);
    pthread_join(thread_1, NULL);
    mrpc_run();
}

int main()
{
    char cmd_type[16];
    char cve_name[32];

    mrpc_init("log.txt", "127.0.0.1:12346", 1);
    // mrpc_run();
    pid = getpid();
    while(1) {
        printf("input what you want to do: ");
        scanf("%s", cmd_type);
        if(strcmp(cmd_type, "trigger") == 0) {
            printf("input the cve num: ");
            scanf("%d", &cve_num);
            // assert(cve_num < sizeof(functions));
            switch (cve_num)
            {
            case 0:
                printf("dummy_cve_0(3000): %d\n", dummy_cve_0(3000));
                break;
            case 1:
                printf("dummy_cve_1(3000): %d\n", dummy_cve_1(3000));
                break;
            case 2:
                AVCodecContext *avctx; PicContext *pictx;
                avctx = (AVCodecContext *)malloc(sizeof(AVCodecContext));
                avctx->height = 1; avctx->width = 1;

                pictx = (PicContext *)malloc(sizeof(PicContext));
                pictx->height = 2; pictx->width = 1;
                // OR
                // pictx->height = 2; pictx->width = 1;
                // OR
                // pictx->height = 1; pictx->width = 1;
                avctx->priv_data = (void *)pictx;
                printf("dummy_cve_2(): %d\n", dummy_cve_2(avctx, (void *)0, (int *)0, (AVPacket *)0));
                break;
            default:
                printf("wrong cve num\n");
                // break;
                return -1;
            }

            // BPF_CALL1 func1 = functions[cve_num];
            // printf("functions[%d]: %d\n", cve_num, func1(3000));
            // continue;
        }
        else if(strcmp(cmd_type, "patch") == 0){
            printf("input the cve num: ");
            scanf("%d", &cve_num);
            mrpc_poll();
            rpc_patch();
            // mrpc_run();
        }
        // else if(strcmp(cmd_type, "send") == 0){
        //     rpc_patch();
        //     // mrpc_run();
        // }
        else if(strcmp(cmd_type, "quit") == 0){
            break;
        }
    }
    return 0;
}

int run_ebpf(stack_frame *frame, const char *code, unsigned long code_len)
{
    struct ubpf_vm *vm = ubpf_create();
    if (!vm)
    {
        fprintf(stderr, "Failed to create VM\n");
        return 1;
    }

    vm->insts = malloc(code_len);
    if (vm->insts == NULL)
    {
        return -1;
    }
    memcpy(vm->insts, code, code_len);
    vm->num_insts = code_len / sizeof(vm->insts[0]);

    uint64_t ret;
    // jit
    char *errmsg;
    ubpf_jit_fn fn = ubpf_compile(vm, &errmsg);
    if (fn == NULL)
    {
        fprintf(stderr, "Failed to compile: %s\n", errmsg);
        free(errmsg);
        ret = UINT64_MAX;
        return ret;
    }
    ret = fn(frame, sizeof(*frame));

    // no jit
    // if (ubpf_exec(vm, frame, sizeof(*frame), &ret) < 0)
    //     ret = UINT64_MAX;
    ubpf_destroy(vm);
    return ret;
}

__attribute__((naked)) void patch_handler_0()
{
    __asm__ __volatile__(
        "push %rbp \n\t"

        // save arguments to stack
        "sub $0x8,%rsp \n\t"
        "mov %rsp,%rbp \n\t"
        "mov %rdi,0x00(%rbp) \n\t"

        // patch_dispatcher(stack_pointer)
        "mov %rbp, %rdi \n\t" // arg1 = sp
        "callq patch_dispatcher \n\t"

        // // restore context
        "mov %rbp, %rsp \n\t"
        "add $0x8,%rsp \n\t" // 16 byte aligned
        "pop %rbp \n\t"
        "retq \n\t");
}

int patch_dispatcher(stack_frame *frame)
{
    int ret = run_ebpf(frame, bytecode, bytecode_len);
    return ret;
}

__attribute__((naked)) void patch_handler_1()
{
    __asm__ __volatile__(
        "push %rbp \n\t"

        // save arguments to stack
        "sub $0x8,%rsp \n\t"
        "mov %rsp,%rbp \n\t"
        "mov %rdi,0x00(%rbp) \n\t"

        // patch_dispatcher(stack_pointer)
        "mov %rbp, %rdi \n\t" // arg1 = sp
        "callq patch_dispatcher \n\t"

        // // restore context
        "mov %rbp, %rsp \n\t"
        "add $0x8,%rsp \n\t" // 16 byte aligned
        "pop %rbp \n\t"
        "retq \n\t");
}

__attribute__((naked)) void patch_handler_2() {
	__asm__ __volatile__ (
		"push %rbp \n\t"

		// save arguments to stack
		"sub $0x20,%rsp \n\t"
		"mov %rsp,%rbp \n\t"
		"mov %rdi,0x00(%rbp) \n\t"
		"mov %rsi,0x08(%rbp) \n\t"
		"mov %rdx,0x10(%rbp) \n\t"
		"mov %rcx,0x18(%rbp) \n\t"
		//"mov %r8,0x20(%rbp) \n\t"
		//"mov %r9,0x28(%rbp) \n\t"

		// patch_dispatcher(stack_pointer)
		"mov %rbp, %rdi \n\t" // arg1 = sp
		"callq patch_dispatcher \n\t"

		"mov %rbp, %rsp \n\t"
		"add $0x20,%rsp \n\t" // 16 byte aligned
		"pop %rbp \n\t"
		"retq \n\t");
}
