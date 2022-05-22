#include <stdio.h>
#include <stdint.h>

uint8_t *dummy_cve_2019_13295_AdaptiveThresholdImage(uint8_t *image, const size_t width, const size_t height, const double bias, uint8_t *exception) {
    uint8_t *threshold_image;
    uint8_t value_1 = 11;
    uint8_t value_2 = 22;

    threshold_image = &value_1;

    if (threshold_image == (uint8_t *)NULL)
        return ((uint8_t *)NULL);
    //if (width == 0)
        //return threshold_image;
    threshold_image = &value_2;
    return threshold_image;
    // 通过指针指向的值来区分threshold_image
}

int main() {
	uint8_t *ptr;
	ptr = dummy_cve_2019_13295_AdaptiveThresholdImage((void *)0, 0, 0, 0, (void *)0);
	//printf("%d\n", *ptr);
	if (*ptr == 11) {
		printf("after patch\n");}
	else if (*ptr == 22){
		printf("before patch\n");}
	return 0;
}

