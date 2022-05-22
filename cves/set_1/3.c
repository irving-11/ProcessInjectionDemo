#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct H264Picture{
    int needs_realloc;
}H264Picture;

typedef struct H264Context
{
    H264Picture *DPB;
    H264Picture *delayed_pic[18];
}H264Context;

/*void av_freep(void *arg)
{
    void **ptr = (void **)arg;
    free(*ptr);
    *ptr = NULL;
}*/
void dummy_cve_2015_3417_ff_h264_free_tables(H264Context *h, int free_rbsp) {
    int i;
    if (free_rbsp && h->DPB) {
        for (i = 0; i < 36; i++)
            // ff_h264_unref_picture(h, &h->DPB[i]);
            printf("1");
        memset(h->delayed_pic, 0, sizeof(h->delayed_pic));
        // av_freep(&h->DPB);
    } else if (h->DPB) {
        for (i = 0; i < 36; i++)
            h->DPB[i].needs_realloc = 1;
    }
}

int main() {
	int free_rbsp = 1;    
	H264Context *h; H264Picture *dpb; //H264Picture *d_p[18];
    dpb = (H264Picture *)malloc(sizeof(H264Picture));
    dpb->needs_realloc = 1;

	h = (H264Context *)malloc(sizeof(H264Context));
    h->DPB = dpb;
    h->delayed_pic[0] = dpb;
    h->delayed_pic[1] = dpb;
	dummy_cve_2015_3417_ff_h264_free_tables(h, free_rbsp);
	if (h->delayed_pic[0] == (H264Picture *)0){
		printf("after patch\n");}
	else if (h->delayed_pic[0]->needs_realloc == 1){
		printf("before patch\n");}

    return 0;
}
