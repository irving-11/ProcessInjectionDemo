// #include <stdint.h>

// struct Mem
// {
//     uint32_t a;
//     //uint32_t b;
// };

// // mov r0, 0x1
// // ldxw r2, [r1]
// // lsh r2, 0x20
// // arsh r2, 0x20
// // mov r3, 0x1388
// // jsgt r3, r2, +4
// // ldxw r0, [r1+4]
// // add r0, r2
// // lsh r0, 0x20
// // arsh r0, 0x20
// // exit

// uint64_t fix_func(void *mem)
// {
//     struct Mem *bpf = (struct Mem *)mem;
//     int a = bpf->a;
//     //int b = bpf->b;

//     if (a > 5000)
//     {
//         return -1;
//     }
//     return 0;
// }

#include <stdint.h>
#include <string.h>
struct Mem
{
    uint32_t a;
    const char b[16];
};

struct Mem2
{
    uint32_t c;
    struct Mem d;
};

uint64_t fix_func(void *mem)
{
    struct Mem2 *bpf = (struct Mem2 *)mem;
    
    if (bpf->d.a > 2000 && bpf->d.b[0]=='g' && bpf->d.b[1]=='o' && bpf->d.b[2]=='o')
    {
        return 10;
    }
    return 0;
}
