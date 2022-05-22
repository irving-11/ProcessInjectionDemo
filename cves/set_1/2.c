#include <stdio.h>

#define EVP_PKT_SIGN    0x0010

int dummy_cve_2015_0205_ssl3_get_cert_verify(int *s) {
    int type = 1;
    int *peer;//, value = 11;
    peer = s;

    if ((peer != NULL) && (type & EVP_PKT_SIGN))
    //if (peer != NULL)
        return 1;

    return 0;
}

int main() {
	//int *s, i=0;
	//s=&i;
	int result = dummy_cve_2015_0205_ssl3_get_cert_verify((int *)11);
	if (result == 1) {
		printf("after patch\n");}
	else if (result == 0){
		printf("before patch\n");}
	//printf("%d\n", 26 & EVP_PKT_SIGN);
	return 0;
}
