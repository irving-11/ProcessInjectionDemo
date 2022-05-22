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
    avctx->priv_data = (void *)pictx;

    ret = dummy_cve_2017_7862_decode_frame(avctx, (void *)0, (int *)0, (AVPacket *)0);
    if (ret == -1) {
		printf("after patch\n");}
	else if (ret == 0){
		printf("before patch\n");}

    return 0;
}
