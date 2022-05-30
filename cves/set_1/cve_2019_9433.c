/*
note: "possible information disclosure due to improper input validation."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2019_9433
commit link: https://github.com/webmproject/libvpx/commit/52add5896661d186dec284ed646a4b33b607d2c7
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned char mode, uv_mode;
  unsigned char ref_frame;
} MB_MODE_INFO;

typedef struct {
  short row;
  short col;
} MV;
typedef union int_mv {
  unsigned int as_int;
  MV as_mv;
} int_mv; /* facilitates faster equality tests and copies */

typedef enum {
  B_DC_PRED, /* average of above and left pixels */
  B_MODE_COUNT
} B_PREDICTION_MODE;

union b_mode_info {
  B_PREDICTION_MODE as_mode;
  int_mv mv;
};

typedef struct modeinfo {
  MB_MODE_INFO mbmi;
  union b_mode_info bmi[16];
} MODE_INFO;

typedef struct VP8Common {
  int Width;

  MODE_INFO *mi;  /* Corresponds to upper left visible macroblock */
  MODE_INFO *show_frame_mi;
} VP8_COMMON;

void dummy_cve_2019_9433_vp8_deblock(VP8_COMMON *cm, int *source, int *post, int q, int low_var_thresh, int flag) {
    const MODE_INFO *mode_info_context = cm->show_frame_mi;
    // patch
    // const MODE_INFO *mode_info_context = cm->mi;
    int i = mode_info_context->bmi[0].mv.as_int;
    // printf("i: %d\n", i);
    
    *source = i;
    source = &i;
}

int main() {
	int b = 0;
    VP8_COMMON *cm; int *source = &b;
    cm = (VP8_COMMON *)malloc(sizeof(VP8_COMMON));
    MODE_INFO *show_frame_mi;
    show_frame_mi = (MODE_INFO *)malloc(sizeof(MODE_INFO));
    MODE_INFO *mi;
    mi = (MODE_INFO *)malloc(sizeof(MODE_INFO));
    // MB_MODE_INFO mbmi;
    union b_mode_info bmi_1[16], bmi_2[16];
    int_mv mv_1, mv_2;
    mv_1.as_int = 1;
    mv_2.as_int = 2;
    bmi_1[0].mv = mv_1;
    bmi_2[0].mv = mv_2;
    memcpy(show_frame_mi->bmi, bmi_1, sizeof(bmi_1));
    memcpy(mi->bmi, bmi_2, sizeof(bmi_2));
    
    cm->show_frame_mi = show_frame_mi;
    cm->mi = mi;

    // cm->show_frame_mi->bmi->mv.as_int = 1;
    // cm->mi->bmi->mv.as_int = 2;

    dummy_cve_2019_9433_vp8_deblock(cm, source, (int *)0, 0, 0, 0);

    if (*source == 2) {
		printf("after patch\n");}
	else if (*source == 1){
		printf("before patch\n");}
    return 0;
}
// what's wrong???
