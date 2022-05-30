/*
note: "An inconsistent bits-per-sample value may trigger an assertion violation while converting a crafted AVI file to MPEG4, leading to a denial of service."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2018_12459
commit link: https://github.com/FFmpeg/FFmpeg/commit/2fc108f60f98cd00813418a8754a46476b404a3c
*/

#include <stdio.h>
#include <stdlib.h>

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

int dummy_cve_2018_12459_ff_mpeg4_decode_picture_header(Mpeg4DecContext *ctx, void *gb) {
    MpegEncContext *s = &ctx->m;

    // patch
    if (!s->studio_profile && s->avctx->bits_per_raw_sample != 8)
        s->avctx->bits_per_raw_sample = 0;

    return 0;
}

int main() {
    Mpeg4DecContext *ctx;
    ctx = (Mpeg4DecContext *)malloc(sizeof(Mpeg4DecContext));
    MpegEncContext m;
    
    struct AVCodecContext *avctx;
    avctx = (struct AVCodecContext *)malloc(sizeof(struct AVCodecContext));
    avctx->bits_per_raw_sample = 1;
    m.studio_profile = 0;
    // OR
    // avctx->bits_per_raw_sample = 8;
    // m.studio_profile = 0;
    // OR
    // avctx->bits_per_raw_sample = 1;
    // m.studio_profile = 1;
    m.avctx = avctx;
    ctx->m = m;

    // ctx->m.studio_profile = 0;
    // ctx->m.avctx->bits_per_raw_sample = 1;
    
    dummy_cve_2018_12459_ff_mpeg4_decode_picture_header(ctx, (void *)0);
    if (ctx->m.avctx->bits_per_raw_sample == 0) {
        printf("after patch\n");
    } else if (ctx->m.avctx->bits_per_raw_sample == 1) {
        printf("before patch\n");
    }

    return 0;
}
