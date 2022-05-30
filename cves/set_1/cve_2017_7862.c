/*
note: "out-of-bounds write caused by a heap-based buffer overflow." BY changing conditions.
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2017_7862
commit link: https://github.com/FFmpeg/FFmpeg/commit/8c2ea3030af7b40a3c4275696fb5c76cdb80950a
*/

#include <stdio.h>
#include <stdlib.h>

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

int dummy_cve_2017_7862_decode_frame(AVCodecContext *avctx, void *data, int *got_frame, AVPacket *avpkt) {
    int ret = 0;
    PicContext *s = avctx->priv_data;

    if (s->width != avctx->width && s->height != avctx->height)
    // patch
    //if (s->width != avctx->width || s->height != avctx->height) 
        ret = -1;
    
    return ret;
}

int main(){
    AVCodecContext *avctx; PicContext *pictx; int ret;
    avctx = (AVCodecContext *)malloc(sizeof(AVCodecContext));
    avctx->height = 1; avctx->width = 1;

    pictx = (PicContext *)malloc(sizeof(PicContext));
    pictx->height = 1; pictx->width = 2;
    // OR
    // pictx->height = 2; pictx->width = 1;
    // OR
    // pictx->height = 1; pictx->width = 1;
    avctx->priv_data = (void *)pictx;

    ret = dummy_cve_2017_7862_decode_frame(avctx, (void *)0, (int *)0, (AVPacket *)0);
    if (ret == -1) {
		printf("after patch\n");}
	else if (ret == 0){
		printf("before patch\n");}

    return 0;
}

