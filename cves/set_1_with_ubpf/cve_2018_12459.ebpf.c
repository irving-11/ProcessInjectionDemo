/*
note: "An inconsistent bits-per-sample value may trigger an assertion violation while converting a crafted AVI file to MPEG4, leading to a denial of service."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2018_12459
commit link: https://github.com/FFmpeg/FFmpeg/commit/2fc108f60f98cd00813418a8754a46476b404a3c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	//uint64_t a3;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

typedef struct AVCodecContext
{
    int bits_per_raw_sample;
} AVCodecContext;

typedef struct MpegEncContext {
    struct AVCodecContext *avctx;
    int studio_profile;
} MpegEncContext;

typedef struct Mpeg4DecContext {
    MpegEncContext m;
    int rgb;
} Mpeg4DecContext;

//int dummy_cve_2018_12459_ff_mpeg4_decode_picture_header(Mpeg4DecContext *ctx, void *gb) 
int dummy_cve_2018_12459_ff_mpeg4_decode_picture_header(void *mem) 
{
	stack_frame *frame = (stack_frame *)mem;
	Mpeg4DecContext *ctx = (Mpeg4DecContext *)(frame->a1);
	
    MpegEncContext *s = &ctx->m;

    // patch
    if (!s->studio_profile && s->avctx->bits_per_raw_sample != 8)
        s->avctx->bits_per_raw_sample = 0;

    return 0;
}
