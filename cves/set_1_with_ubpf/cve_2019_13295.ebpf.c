/*
note: "a heap-based buffer over-read, because a width of zero is mishandled."
cve link: https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE_2019_13295
commit link: https://github.com/ImageMagick/ImageMagick/commit/a7759f410b773a1dd57b0e1fb28112e1cd8b97bc
*/

#include <stdio.h>
#include <stdint.h>

typedef struct stack_frame {
	uint64_t a1;
	uint64_t a2;
	uint64_t a3;
	uint64_t a4;
	uint64_t a5;
} __attribute__ ((__packed__, aligned(4))) stack_frame;

//uint8_t *dummy_cve_2019_13295_AdaptiveThresholdImage(uint8_t *image, const size_t width, const size_t height, const double bias, uint8_t *exception) {
uint8_t *dummy_cve_2019_13295_AdaptiveThresholdImage(void *mem) {
	stack_frame *frame = (stack_frame *)mem;
	const size_t width = frame->a2;
	
    uint8_t *threshold_image;
    uint8_t *value_1 = malloc(sizeof(uint8_t));
    *value_1 = 11;
    uint8_t *value_2 = malloc(sizeof(uint8_t));
    *value_2 = 22;

    threshold_image = value_1;

    if (threshold_image == (uint8_t *)NULL)
        return ((uint8_t *)NULL);
    // patch
    if (width == 0)
        return threshold_image;
    threshold_image = value_2;
    return threshold_image;
    // 通过指针指向的值来区分threshold_image
}
