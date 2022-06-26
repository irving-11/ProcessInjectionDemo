/*
note: "Fixes use of freed memory." BY adding memset().
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2015-3417
commit link: https://github.com/FFmpeg/FFmpeg/commit/e8714f6f93d1a32f4e4655209960afcf4c185214
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
typedef struct H264Picture{
    int needs_realloc;
}H264Picture;

typedef struct H264Context
{
    H264Picture *DPB;
    H264Picture *delayed_pic[18];
}H264Context;

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	//uint64_t a3;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

//void dummy_cve_2015_3417_ff_h264_free_tables(H264Context *h, int free_rbsp) {
void dummy_cve_2015_3417_ff_h264_free_tables(void *mem) {
	stack_frame *frame = (stack_frame *)mem;
	
	H264Context *h = (H264Context *)(frame->a1);
	int free_rbsp = frame->a2;

    int i;
    if (free_rbsp && h->DPB) {
        /*for (i = 0; i < 36; i++)
            printf("1");*/
        // patch 
        memset(h->delayed_pic, 0, sizeof(h->delayed_pic));
        // av_freep(&h->DPB);
    } else if (h->DPB) {
        for (i = 0; i < 36; i++)
            h->DPB[i].needs_realloc = 1;
    }
}


