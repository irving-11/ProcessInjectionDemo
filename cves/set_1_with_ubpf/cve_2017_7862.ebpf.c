/*
note: "out-of-bounds write caused by a heap-based buffer overflow." BY changing conditions.
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2017_7862
commit link: https://github.com/FFmpeg/FFmpeg/commit/8c2ea3030af7b40a3c4275696fb5c76cdb80950a
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
} __attribute__ ((__packed__, aligned(4))) stack_frame;


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

//int dummy_cve_2017_7862_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt) {
int dummy_cve_2017_7862_decode_frame(void *mem) 
{
	stack_frame *frame = (stack_frame *)mem;
	AVCodecContext *avctx = (AVCodecContext *)(frame->a1);
	
    int ret = 0;
    PicContext *s = avctx->priv_data;

    // if (s->width != avctx->width && s->height != avctx->height)
    // patch
    if (s->width != avctx->width || s->height != avctx->height) 
        ret = -1;
    
    return ret;
}

