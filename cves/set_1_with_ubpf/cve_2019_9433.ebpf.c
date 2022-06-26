/*
note: "possible information disclosure due to improper input validation."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2019_9433
commit link: https://github.com/webmproject/libvpx/commit/52add5896661d186dec284ed646a4b33b607d2c7
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
	uint64_t a5;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

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

//void dummy_cve_2019_9433_vp8_deblock(VP8_COMMON *cm, int *source, int *post, int q, int low_var_thresh, int flag) {
void dummy_cve_2019_9433_vp8_deblock(void *mem) {
	stack_frame *frame = (stack_frame *)mem;
	VP8_COMMON *cm = (VP8_COMMON *)(frame->a1);
	
    //const MODE_INFO *mode_info_context = cm->show_frame_mi;
    // patch
    const MODE_INFO *mode_info_context = cm->mi;
    int i = mode_info_context->bmi[0].mv.as_int;
    // printf("i: %d\n", i);
    
    *(int *)(uintptr_t)(frame->a2) = i;
    frame->a2 = &i;
    //*source = i;
    //source = &i;
}

