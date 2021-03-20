#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

char* strcpy(char* dest, const char* src) {

    assert((dest != NULL) && (src != NULL));

    char* addresss = dest;
    while ((*dest = *src) != '\0') {
        ++dest;
        ++src;
    }

    return addresss;
}

void* memcpy(void* dest, const void* src, size_t n) {
    
    assert((dest != NULL) && (src != NULL));

    char* tdest = dest;
    const char* tsrc = src;

    while (n--) {
        *tdest = *tsrc;
        ++tdest;
        ++tsrc;
    }

    return dest;
}

int main() {
    const char* str = "??? hello";
    char buf[20];
    strcpy(buf, str);
    printf("%s\n", buf);

    char buf2[20];
    memcpy(buf2, buf, sizeof(buf));
    printf("%s\n", buf2);

    return 0;
}
